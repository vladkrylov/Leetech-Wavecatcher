#include "controller.h"
#include "wavecatcher.h"
#include "mainwindow.h"

#include <QDebug>

Controller::Controller(QObject *parent) : QObject(parent)
{
    WCthread = new QThread(this);
    wc = new Wavecatcher();
    wc->moveToThread(WCthread);

    view = new MainWindow();
    view->resize(view->sizeHint());
    view->setWindowTitle("Qt Example - Canvas");
    view->setGeometry(100, 100, 1700, 900);
    view->show();

    ConnectSignalSlots();
    WCthread->start();
}

Controller::~Controller()
{
//    WCthread->quit();
//    WCthread->wait();

    delete wc;
    delete view;
}

void Controller::ConnectSignalSlots()
{
    connect(WCthread, SIGNAL(started()), wc, SLOT(Process()));
    connect(WCthread, SIGNAL(finished()), WCthread, SLOT(deleteLater()));
    connect(WCthread, SIGNAL(finished()), this, SLOT(Test()));

    connect(wc, SIGNAL(PlotDataReceived(const WAVECAT64CH_ChannelDataStruct*)), view, SLOT(DrawWaveforms(const WAVECAT64CH_ChannelDataStruct*)));

    connect(view, SIGNAL(RunStopped()), wc, SLOT(onStop()), Qt::DirectConnection);
    connect(view, SIGNAL(RunStarted(int,int)), wc, SLOT(onStart(int,int)), Qt::DirectConnection);

    connect(view, SIGNAL(HorizontalScaleChanged(int)), wc, SLOT(SetSamplingFrequency(int)), Qt::DirectConnection);

    connect(view, SIGNAL(SetTriggerType(int)), wc, SLOT(SetTriggerType(int)), Qt::DirectConnection);
    connect(view, SIGNAL(TriggerSourceChanged(int)), wc, SLOT(SetTriggerSource(int)), Qt::DirectConnection);
    connect(view, SIGNAL(TriggerLevelChanged(int,float)), wc, SLOT(SetTriggerThreshold(int,float)), Qt::DirectConnection);
}

void Controller::Test()
{
    qDebug() << "thread finished";
}

