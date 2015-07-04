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
    view->setGeometry(100, 100, 700, 500);
    view->show();

    ConnectSignalSlots();
    WCthread->start();
}

Controller::~Controller()
{
    WCthread->quit();
//    WCthread->wait();

    delete wc;
    delete view;
}

void Controller::ConnectSignalSlots()
{
    connect(WCthread, SIGNAL(started()), wc, SLOT(Process()));
    connect(WCthread, SIGNAL(finished()), WCthread, SLOT(deleteLater()));
//    connect(wc, SIGNAL(AcquisitionFinished()), WCthread, SLOT(quit()));
    connect(WCthread, SIGNAL(finished()), this, SLOT(Test()));

    connect(wc, SIGNAL(DataReceived(const WAVECAT64CH_ChannelDataStruct*)), view, SLOT(DrawWaveforms(const WAVECAT64CH_ChannelDataStruct*)));

    connect(view->stopButton, SIGNAL(clicked(bool)), wc, SLOT(onStop()), Qt::DirectConnection);
    connect(view->startButton, SIGNAL(clicked(bool)), wc, SLOT(onStart()), Qt::DirectConnection);
}

void Controller::Test()
{
    qDebug() << "thread finished";
}

