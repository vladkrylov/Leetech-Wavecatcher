/***************************************************************
*	File	: 	wavecatcher.h                   			    *
*															    *
*	Date	:	June 2015   								    *
*															    *
*	Authors	:	Dominique Breton	LAL Orsay					*
*	            Jihane    Maalmi	LAL Orsay					*
*                                                               *
* 	Contributor	:	Vlad Krylov 	LAL / KNU                  	*
*															    *
***************************************************************/

#ifndef WAVECATCHER_H
#define WAVECATCHER_H

#include <windows.h>
#include <ansi_c.h>
#include "WaveCat64Ch_Lib.h"
#include "WaveCat64Ch_Sample.h"
#include "WaveCat64Ch_RatePanel.h"

#include <utility.h>
#include <cvirte.h>
#include <userint.h>

#include <QObject>
#include <QThread>

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

const int N_CHANNELS = 8;

typedef int Boolean;

typedef enum {

   SYSTEM_TRIGGER_SOFT,
   SYSTEM_TRIGGER_NORMAL,
   SYSTEM_TRIGGER_AUTO,
   SYSTEM_TRIGGER_EXTERN

}TriggerType_t;

typedef enum {
    RUN_MODE_CONTINUOUS,
    RUN_MODE_FINITE
}RunMode_t;

class Wavecatcher : public QObject
{
    Q_OBJECT
public:
    explicit Wavecatcher(QObject *parent = 0);
    ~Wavecatcher();

    int Open(int* handle);

signals:
    void EventsAcquired(int numEvents);
    void DataReceived(const WAVECAT64CH_ChannelDataStruct*);
    void PlotDataReceived(const WAVECAT64CH_ChannelDataStruct*);
    void PlotData(const WAVECAT64CH_ChannelDataStruct*);
    void AcquisitionFinished();

public slots:
    void Stop_run();
    void Start_Acquisition();
    void onStart(int mode, int N);
    void onStop();
    void Process();
    void SetSamplingFrequency(int timelengthOfWaveform);
    void SetTriggerType(int trigger);
    void SetTriggerSource(int channel);
    void SetTriggerThreshold(int channel, float thr);
    void SetRunMode(int m, int param);

private:
//    bool run;
    void Init_LocalVariables();
    void Start_run();
    void Prepare_Event();
    int  Run_WithRateCounters();
    int  Read_EventBuffer();
    int  Get_NumberOfEvents();
    int  Decode_Event(int eventNumber);
    void Update_Panel();
    void Set_ChannelSelectionList(int panelHandle, int controlName);
    void Set_FourChannelGroupSelectionList(int panelHandle, int controlName);
    int  Set_Color(int channel);

    RunMode_t runMode;
    int numberOfAquisitions;

    int DeviceHandle;
    int EventNumber;
    int StopAcquisition;
    WAVECAT64CH_DeviceInfoStruct DeviceInfo;

    int NbOfChannels;

    int VerticalScale;
    int AcquisitionRunning;

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

    Boolean DisplayON;
    Boolean EnableRateStats;

    double CurrentTimer;
    double FormerTimer;
    int FormerEventNumber;

    int FirstChannelToDisplay;

    int ChannelInCoincidenceForRateHandle[MAX_NB_OF_FE_FPGAS_IN_SYSTEM];

    int LabelInCoincidenceForRateHandle[NB_OF_CHANNELS_IN_FE_FPGA];

    unsigned short CoincidenceMask[MAX_NB_OF_FE_FPGAS_IN_SYSTEM];
    int ChannelForRateStats;
    int ChannelForRatePlot;
    float PlotIntervalForRateStripchart;
    float ChannelHitRate[MAX_NB_OF_CHANNELS];
    Boolean RateRunStopRequested;
};

#endif // WAVECATCHER_H
