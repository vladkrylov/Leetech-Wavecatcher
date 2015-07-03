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

int Wavecatcher::Start_Acquisition()
{
//int channel, channelToPlot;
//double yOffset;
    int channel = 0;
    WAVECAT64CH_ErrCode errCode;

    QElapsedTimer eltim;
    eltim.start();

    StopAcquisition = FALSE;

    EventNumber = 0;

    Start_run();

    AcquisitionRunning = TRUE;

    for(;;)
//    for(int i=0; i < 4000; i++)
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
        if (eltim.elapsed() > 1000) {
            eltim.restart();
            emit DataReceived(CurrentEvent.ChannelData);
        }
//        if (plot) {
//            emit PlotData(CurrentEvent.ChannelData);
//            plot = false;
//        }

        if(errCode < 0)
            break;

//        StopAcquisition = TRUE;
        if(StopAcquisition == TRUE)
            break;
    }

    Stop_run();

    AcquisitionRunning = FALSE;

    return 0;
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

 void Wavecatcher::PlotEnable(bool a)
 {
     plot = true;
     qDebug() << "!";
 }

