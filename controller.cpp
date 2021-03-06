#include "controller.h"
#include "wavecatcher.h"
#include "mainwindow.h"
#include "waveformssaver.h"

#include <QDebug>

Controller::Controller(QObject *parent) : QObject(parent)
{
    WCthread = new QThread(this);
    wc = new Wavecatcher();
    wc->moveToThread(WCthread);

    view = new MainWindow();
    view->resize(view->sizeHint());
    view->setWindowTitle("LEETECH USB Wavecatcher software");
    view->setGeometry(100, 100, 1700, 900);
    view->show();

//    saverThread = new QThread(this);
    saver = new WaveformsSaver();
//    saver->moveToThread(saverThread);

    ConnectSignalSlots();

    // set channels to save
    view->ChannelsSave();

    WCthread->start();
}

Controller::~Controller()
{
//    WCthread->quit();
//    WCthread->wait();

    delete saver;
    delete wc;
    delete view;
}

void Controller::ConnectSignalSlots()
{
    connect(WCthread, SIGNAL(started()), wc, SLOT(Process()));
    connect(WCthread, SIGNAL(finished()), WCthread, SLOT(deleteLater()));
    connect(WCthread, SIGNAL(finished()), this, SLOT(Test()));

    connect(wc, SIGNAL(EventsAcquired(int)), view, SLOT(DisplayEventsAcquired(int)));
    connect(wc, SIGNAL(PlotDataReceived(const WAVECAT64CH_ChannelDataStruct*)), view, SLOT(DrawWaveforms(const WAVECAT64CH_ChannelDataStruct*)));
    connect(wc, SIGNAL(FiniteRunFinished()), view, SLOT(UpdateInterfaceOnStopRun()));

    connect(view, SIGNAL(RunStopped()), wc, SLOT(onStop()), Qt::DirectConnection);
    connect(view, SIGNAL(RunStarted(int,int)), wc, SLOT(onStart(int,int)), Qt::DirectConnection);
    connect(view, SIGNAL(HorizontalScaleChanged(int)), wc, SLOT(SetSamplingFrequency(int)), Qt::DirectConnection);
    connect(view, SIGNAL(SetTriggerType(int)), wc, SLOT(SetTriggerType(int)), Qt::DirectConnection);
    connect(view, SIGNAL(TriggerSourceChanged(int)), wc, SLOT(SetTriggerSource(int)), Qt::DirectConnection);
    connect(view, SIGNAL(TriggerLevelChanged(int,float)), wc, SLOT(SetTriggerThreshold(int,float)), Qt::DirectConnection);
    connect(view, SIGNAL(HorizonatalPositionChanged(unsigned char)), wc, SLOT(SetTriggerDelay(unsigned char)), Qt::DirectConnection);

    connect(wc, SIGNAL(DataReceived(const WAVECAT64CH_ChannelDataStruct*)), saver, SLOT(SaveData(const WAVECAT64CH_ChannelDataStruct*)), Qt::DirectConnection);
    connect(view, SIGNAL(SaveChannelsChanged(int,bool)), saver, SLOT(SetChannelsToSave(int,bool)), Qt::DirectConnection);
    connect(view, SIGNAL(RunDirectoryChanged(QString)), saver, SLOT(SetRunDir(QString)), Qt::DirectConnection);
    connect(view, SIGNAL(SetSaveStatus(bool)), saver, SLOT(Enable(bool)), Qt::DirectConnection);
}

void Controller::Test()
{
    qDebug() << "thread finished";
}



