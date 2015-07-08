/***************************************************************
*	File	: 	wavecatcher.cpp                   			    *
*															    *
*	Date	:	June 2015   								    *
*															    *
*	Authors	:	Dominique Breton	LAL Orsay					*
*	            Jihane    Maalmi	LAL Orsay					*
*                                                               *
* 	Contributor	:	Vlad Krylov 	LAL / KNU                  	*
*															    *
***************************************************************/

#include "wavecatcher.h"

#include <QDebug>
#include <QElapsedTimer>

Wavecatcher::Wavecatcher(QObject *parent) : QObject(parent)
//    ChannelInCoincidenceForRateHandle {
//                 PANEL_RATE_COINCBOX0_0,PANEL_RATE_COINCBOX0_1,PANEL_RATE_COINCBOX0_2,PANEL_RATE_COINCBOX0_3,
//                 PANEL_RATE_COINCBOX1_0,PANEL_RATE_COINCBOX1_1,PANEL_RATE_COINCBOX1_2,PANEL_RATE_COINCBOX1_3,
//                 PANEL_RATE_COINCBOX2_0,PANEL_RATE_COINCBOX2_1,PANEL_RATE_COINCBOX2_2,PANEL_RATE_COINCBOX2_3,
//                 PANEL_RATE_COINCBOX3_0,PANEL_RATE_COINCBOX3_1,PANEL_RATE_COINCBOX3_2,PANEL_RATE_COINCBOX3_3},
//    LabelInCoincidenceForRateHandle {
//                   PANEL_RATE_TEXTMSG_41,PANEL_RATE_TEXTMSG_42,PANEL_RATE_TEXTMSG_43,PANEL_RATE_TEXTMSG_44}

{
    DeviceHandle = -1;
    StopAcquisition = TRUE;
    numberOfAquisitions = 0;

    NbOfChannels = 0;

    VerticalScale  = 500; //mV/Div
    AcquisitionRunning = FALSE;

    DisplayON = TRUE;
    EnableRateStats = FALSE;

    CurrentTimer = 0;
    FormerTimer = 0;
    FormerEventNumber = 0;

    FirstChannelToDisplay = 0;

    RateRunStopRequested = FALSE;

    int errCode = Open(&DeviceHandle);
    if(errCode == WAVECAT64CH_Success)
    {
        WAVECAT64CH_GetDeviceInfo(&DeviceInfo);
        WAVECAT64CH_ResetDevice();
        Init_LocalVariables();
        WAVECAT64CH_StopRun();
    }
}

Wavecatcher::~Wavecatcher()
{
    Stop_run();
    WAVECAT64CH_CloseDevice();
}

void Wavecatcher::Init_LocalVariables()
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

void Wavecatcher::Start_Acquisition()
{
//int channel, channelToPlot;
//double yOffset;
//    int channel = 0;
    WAVECAT64CH_ErrCode errCode;

    QElapsedTimer eltim;
    eltim.start();

    StopAcquisition = FALSE;

    EventNumber = 0;

    Start_run();

    AcquisitionRunning = TRUE;

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

        if(errCode  < 0) // error
        {
            StopAcquisition = TRUE;
            break;
        }

        errCode = WAVECAT64CH_DecodeEvent(&CurrentEvent);
        EventNumber++;
        qDebug() << CurrentEvent.ChannelData[0].Peak;
        if (eltim.elapsed() > 25) {
            eltim.restart();
            emit PlotDataReceived(CurrentEvent.ChannelData);
        }

        if(errCode < 0)
            break;

        if(StopAcquisition == TRUE)
            break;

        if (EventNumber >= numberOfAquisitions)
            break;
    }

    Stop_run();

    AcquisitionRunning = FALSE;
    StopAcquisition = TRUE;
}

int Wavecatcher::Open(int* handle)
{
    return WAVECAT64CH_OpenDevice(handle);
}

void Wavecatcher::Start_run()
{
    WAVECAT64CH_AllocateEventStructure(&CurrentEvent);
    WAVECAT64CH_StartRun();
}

void Wavecatcher::Stop_run()
{
    WAVECAT64CH_StopRun();
    WAVECAT64CH_FreeEventStructure(&CurrentEvent);
}

void Wavecatcher::Prepare_Event()
{
    WAVECAT64CH_PrepareEvent();
}

void Wavecatcher::onStart(int mode, int N)
{
    runMode = (RunMode_t)mode;
    numberOfAquisitions = N;
    if (runMode == RUN_MODE_CONTINUOUS) {
        numberOfAquisitions = 1e9;
    }
    StopAcquisition = FALSE;
}

void Wavecatcher::onStop()
{
    StopAcquisition = TRUE;
}

void Wavecatcher::Process()
{
    while(1) {
        if (!StopAcquisition)
            Start_Acquisition();
    }
}

void Wavecatcher::SetTriggerType(int trigger)
{
    qDebug() << WAVECAT64CH_SetTriggerMode(TriggerType = (WAVECAT64CH_TriggerType)trigger);
}

void Wavecatcher::SetTriggerSource(int channel)
{
    for (int ch = 0; ch < N_CHANNELS; ++ch) {
        WAVECAT64CH_SetTriggerSourceState(WAVECAT64CH_FRONT_CHANNEL, ch, ChannelTriggerEnable[ch] = WAVECAT64CH_STATE_OFF);
    }
    qDebug() << WAVECAT64CH_SetTriggerSourceState(WAVECAT64CH_FRONT_CHANNEL, channel, ChannelTriggerEnable[channel] = WAVECAT64CH_STATE_ON);
}

void Wavecatcher::SetTriggerThreshold(int channel, float thr)
{
    qDebug() << WAVECAT64CH_SetTriggerThreshold(WAVECAT64CH_FRONT_CHANNEL, channel, TriggerThreshold[channel] = thr);
}

void Wavecatcher::SetRunMode(int m, int param)
{
    runMode = (RunMode_t)m;
    if (runMode = RUN_MODE_FINITE) {
        numberOfAquisitions = param;
    }
}

void Wavecatcher::SetSamplingFrequency(int timelengthOfWaveform)
{
    WAVECAT64CH_SamplingFrequencyType f;
    switch(timelengthOfWaveform) { // in nanoseconds
    case 320:
        f = WAVECAT64CH_3_2GHZ;
        break;
    case 480:
        f = WAVECAT64CH_2_13GHZ;
        break;
    case 640:
        f = WAVECAT64CH_1_6GHZ;
        break;
    case 960:
        f = WAVECAT64CH_1_07GHZ;
        break;
    case 1280:
        f = WAVECAT64CH_800MHZ;
        break;
    case 1920:
        f = WAVECAT64CH_533MHZ;
        break;
    case 2560:
        f = WAVECAT64CH_400MHZ;
        break;
    default:
        break;
    }
    qDebug() << WAVECAT64CH_SetSamplingFrequency(f);
}
