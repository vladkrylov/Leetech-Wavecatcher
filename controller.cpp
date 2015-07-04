#include "controller.h"
#include "wavecatcher.h"
#include "mainwindow.h"

#include <QDebug>

Controller::Controller(QObject *parent) : QObject(parent)
{
    WCthread = new QThread(this);
    wc = new Wavecatcher();
    wc->moveToThread(WCthread);

    connect(WCthread, SIGNAL(started()), wc, SLOT(Start_Acquisition()));

    WCthread->start();


    view = new MainWindow();
    view->resize(view->sizeHint());
    view->setWindowTitle("Qt Example - Canvas");
    view->setGeometry(100, 100, 700, 500);
    view->show();

    ConnectSignalSlots();

//    wc->start();
}

Controller::~Controller()
{
    delete wc;
    delete view;
}

void Controller::ConnectSignalSlots()
{
    connect(wc, SIGNAL(DataReceived(const WAVECAT64CH_ChannelDataStruct*)), view, SLOT(DrawWaveforms(const WAVECAT64CH_ChannelDataStruct*)));

    connect(view->stopButton, SIGNAL(clicked(bool)), wc, SLOT(Stop_run()));
}
