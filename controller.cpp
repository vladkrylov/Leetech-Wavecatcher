#include "controller.h"
#include "wavecatcher.h"
#include "mainwindow.h"

#include <QDebug>

Controller::Controller(QObject *parent) : QObject(parent)
{
    wc = new Wavecatcher(this);
    view = new MainWindow(0);
    view->resize(view->sizeHint());
    view->setWindowTitle("Qt Example - Canvas");
    view->setGeometry(100, 100, 700, 500);
    view->show();

    ConnectSignalSlots();

    wc->Start_Acquisition();
}

Controller::~Controller()
{
    delete view;
}

void Controller::ConnectSignalSlots()
{
    connect(wc, SIGNAL(DataReceived(const WAVECAT64CH_ChannelDataStruct*)), view, SLOT(DrawWaveforms(const WAVECAT64CH_ChannelDataStruct*)));

    connect(view->updateButton, SIGNAL(clicked(bool)), wc, SLOT(PlotEnable(bool)));
    connect(view->stopButton, SIGNAL(clicked(bool)), wc, SLOT(Stop_run()));
}
