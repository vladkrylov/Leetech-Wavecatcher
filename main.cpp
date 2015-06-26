#include "mainwindow.h"
#include <QApplication>
#include <QDebug>
#include <QFile>

/***************************************************************
*	File	: 	WaveCat64ch_Sample.c						    *
*															    *
*	Date	:	July 2014   								    *
*															    *
*	Authors	:	Dominique Breton	LAL Orsay					*
*	            Jihane    Maalmi	LAL Orsay					*
*															    *
***************************************************************/

#include <ansi_c.h>
#include "windows.h"
#include "WaveCat64Ch_Lib.h"
#include "WaveCat64Ch_Sample.h"
#include "WaveCat64Ch_RatePanel.h"

#include <utility.h>
#include <cvirte.h>
#include <userint.h>

/* ============================================================================ */
/* ============================ Constantes ==================================== */
/* ============================================================================ */

#define TRUE 1
#define FALSE 0

#define MAX_NB_OF_CHANNELS 	72
#define NB_OF_CHANNELS_IN_FE_FPGA 4
#define MAX_NB_OF_FE_FPGAS_IN_SYSTEM 16
#define MIN_DAC_RAW_VALUE	-1.25
#define MAX_DAC_RAW_VALUE	1.25

#define	 WAVECAT64CH_ADCTOVOLTS			 0.00061
#define  VOLTSTOADC			 1638

#define SOFTWARE_VERSION "V1.1.2"

#define MAX_NB_OF_CHANNELS_TO_PLOT 16

typedef int Boolean;

typedef enum {

   SYSTEM_TRIGGER_SOFT,
   SYSTEM_TRIGGER_NORMAL,
   SYSTEM_TRIGGER_AUTO,
   SYSTEM_TRIGGER_EXTERN

}TriggerType_t;

//* ============================================================================= */
//* ============================   GLOBAL VARIABLES ============================= */
//* ============================================================================= */

/* ==================  local global variables ================== */

static int ThreadID;
static void *ThreadData;
static int RunRateThreadID;
static void *RunRateThreadData;

static int MainPanelHandle;
static int RateStatisticsPanelHandle;

int DeviceHandle = -1;
int EventNumber;
int StopAcquisition = TRUE;
WAVECAT64CH_DeviceInfoStruct DeviceInfo;

int NbOfChannels = 0;

int VerticalScale  = 500; //mV/Div
int AcquisitionRunning = FALSE;

float DCOffset[MAX_NB_OF_CHANNELS];
float TriggerThreshold[MAX_NB_OF_CHANNELS];
WAVECAT64CH_TriggerEdgeType TriggerPolarity[MAX_NB_OF_CHANNELS];
unsigned char TriggerDelay;

WAVECAT64CH_SamplingFrequencyType SamplingFrequency;

WAVECAT64CH_TriggerType TriggerType;

WAVECAT64CH_StateType ChannelTriggerEnable[MAX_NB_OF_CHANNELS];

WAVECAT64CH_TriggerEdgeType TriggerEdge[MAX_NB_OF_CHANNELS];

unsigned short PulsePattern[MAX_NB_OF_CHANNELS];
int EnablePulseChannels[MAX_NB_OF_CHANNELS];

unsigned int *ReadoutBuffer;
int ReadoutBufferSize;

WAVECAT64CH_EventStruct CurrentEvent;

Boolean DisplayON = TRUE;
Boolean EnableRateStats = FALSE;

double CurrentTimer =0;
double FormerTimer =0;
int FormerEventNumber = 0;

int FirstChannelToDisplay = 0;

int ChannelInCoincidenceForRateHandle[MAX_NB_OF_FE_FPGAS_IN_SYSTEM]={
               PANEL_RATE_COINCBOX0_0,PANEL_RATE_COINCBOX0_1,PANEL_RATE_COINCBOX0_2,PANEL_RATE_COINCBOX0_3,
               PANEL_RATE_COINCBOX1_0,PANEL_RATE_COINCBOX1_1,PANEL_RATE_COINCBOX1_2,PANEL_RATE_COINCBOX1_3,
               PANEL_RATE_COINCBOX2_0,PANEL_RATE_COINCBOX2_1,PANEL_RATE_COINCBOX2_2,PANEL_RATE_COINCBOX2_3,
               PANEL_RATE_COINCBOX3_0,PANEL_RATE_COINCBOX3_1,PANEL_RATE_COINCBOX3_2,PANEL_RATE_COINCBOX3_3};

int LabelInCoincidenceForRateHandle[NB_OF_CHANNELS_IN_FE_FPGA]={
               PANEL_RATE_TEXTMSG_41,PANEL_RATE_TEXTMSG_42,PANEL_RATE_TEXTMSG_43,PANEL_RATE_TEXTMSG_44};

unsigned short CoincidenceMask[MAX_NB_OF_FE_FPGAS_IN_SYSTEM];
int ChannelForRateStats;
int ChannelForRatePlot;
float PlotIntervalForRateStripchart;
float ChannelHitRate[MAX_NB_OF_CHANNELS];
Boolean RateRunStopRequested = FALSE;

/* ============================================================================= */
/* ========================= Static functions ================================== */
/* ============================================================================= */

static int Start_Acquisition ();

static void Stop_run (void);
static void Start_run (void);
static void	Prepare_Event(void);
static int  Run_WithRateCounters(void* unused);
static int	Read_EventBuffer(void);
static int  Get_NumberOfEvents(void);
static int  Decode_Event(int eventNumber);
static void Init_LocalVariables(void);
static void Update_Panel(void);
static void Set_ChannelSelectionList(int panelHandle, int controlName);
static void Set_FourChannelGroupSelectionList(int panelHandle, int controlName);
static int 	Set_Color(int channel);

/* ============================================================================ */
/* ============================== Main ======================================= */
/* ============================================================================ */
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    int errCode = WAVECAT64CH_OpenDevice(&DeviceHandle);

    if (errCode == WAVECAT64CH_Success) {
        WAVECAT64CH_GetDeviceInfo(&DeviceInfo);
        qDebug() << DeviceInfo.BoardConnected;

        WAVECAT64CH_ResetDevice();

        Init_LocalVariables();

        WAVECAT64CH_StopRun();

        Start_Acquisition();
    }

    return a.exec();
}

/* ============================================================================ */
static void Init_LocalVariables(void)
/* ============================================================================ */
{
int i, channel, fourChannelGroup;
unsigned char coincidenceMask;

    NbOfChannels = DeviceInfo.NbOfFeChannels + DeviceInfo.NbOfBackExtraChannels;

    WAVECAT64CH_GetSamplingFrequency(&SamplingFrequency);

    for(channel = 0; channel < NbOfChannels; channel++)
        WAVECAT64CH_GetChannelDCOffset(WAVECAT64CH_FRONT_CHANNEL, channel, &DCOffset[channel]);

    WAVECAT64CH_GetTriggerDelay(&TriggerDelay);

    WAVECAT64CH_GetTriggerMode(&TriggerType);

    for(channel = 0; channel < NbOfChannels; channel++)
         WAVECAT64CH_GetTriggerSourceState(WAVECAT64CH_FRONT_CHANNEL, channel, &ChannelTriggerEnable[channel]);

    for(channel = 0; channel < NbOfChannels; channel++)
        WAVECAT64CH_GetTriggerThreshold(WAVECAT64CH_FRONT_CHANNEL, channel, &TriggerThreshold[channel]);

    for(channel = 0; channel < NbOfChannels; channel++)
        WAVECAT64CH_GetTriggerEdge(WAVECAT64CH_FRONT_CHANNEL, channel, &TriggerPolarity[channel]);

    for(channel = 0; channel < NbOfChannels; channel++)
        PulsePattern[channel] = 0x01;

    for(channel = 0; channel < NbOfChannels; channel++)
        EnablePulseChannels[channel] = 0;

    for(fourChannelGroup = 0; fourChannelGroup < DeviceInfo.NbOfFeFPGAs; fourChannelGroup++)
    {
         CoincidenceMask[fourChannelGroup] = 0;

         for(i = 0; i < NB_OF_CHANNELS_IN_FE_FPGA; i++)
         {
             WAVECAT64CH_GetRateCounterCoincidenceMask(fourChannelGroup, i, &coincidenceMask);
             CoincidenceMask[fourChannelGroup] += (coincidenceMask << (i * NB_OF_CHANNELS_IN_FE_FPGA));
         }
    }

    PlotIntervalForRateStripchart = 1000.0; // en ms
    ChannelForRateStats = 0;
    ChannelForRatePlot = -1; // All channels
}

/* ============================================================================ */
static int Start_Acquisition ()
/* ============================================================================ */
{
//int channel, channelToPlot;
//double yOffset;
    int channel = 0;
    WAVECAT64CH_ErrCode errCode;

    StopAcquisition = FALSE;

    EventNumber = 0;

    QString filename = "Data.txt";
    QFile file(filename);
    file.open(QIODevice::ReadWrite);
    QTextStream out(&file);

    Start_run();

    AcquisitionRunning = TRUE;

    //SetAxisScalingMode (MainPanelHandle, MAINPANEL_GRAPH, VAL_LEFT_YAXIS, VAL_MANUAL, -5, 5);
//    SetAxisScalingMode (MainPanelHandle, MAINPANEL_GRAPH, VAL_BOTTOM_XAXIS, VAL_MANUAL, 0, 1024);

    for(;;)
    {
        Prepare_Event();
        errCode = WAVECAT64CH_CommError;

        for(;;)
        {
            if(StopAcquisition == TRUE)
                break;

            errCode = WAVECAT64CH_ReadEventBuffer();
            if((errCode == WAVECAT64CH_Success) || (errCode == WAVECAT64CH_ReadoutError))
                break;

            Delay(0.001);
        }

        if(errCode  < 0) // erreur
        {
            StopAcquisition = TRUE;
            break;
        }

        errCode = WAVECAT64CH_DecodeEvent(&CurrentEvent);
        EventNumber++;

        for (int i = 0; i < CurrentEvent.ChannelData[channel].WaveformDataSize; ++i) {
            out << CurrentEvent.ChannelData[channel].WaveformData[i] << endl;
        }

        if(errCode < 0)
            break;

        StopAcquisition = TRUE;
        if(StopAcquisition == TRUE)
            break;
    }

    Stop_run();
    file.close();
    qDebug() << "done";

    AcquisitionRunning = FALSE;

//    SetCtrlAttribute(MainPanelHandle, MAINPANEL_START, ATTR_DIMMED, 0);

    return 0;
}

/* =========================================================================== */
static void Start_run (void)
/* =========================================================================== */
{
    WAVECAT64CH_AllocateEventStructure(&CurrentEvent);

    WAVECAT64CH_StartRun();
}

/* =========================================================================== */
static void Stop_run (void)
/* =========================================================================== */
{
    WAVECAT64CH_StopRun();

    WAVECAT64CH_FreeEventStructure(&CurrentEvent);
}

/* =========================================================================== */
static void	Prepare_Event(void)
/* =========================================================================== */
{
    WAVECAT64CH_PrepareEvent();
}



