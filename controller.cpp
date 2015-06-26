#include "controller.h"
#include "wavecatcher.h"
#include "canvas.h"

Controller::Controller(QObject *parent) : QObject(parent)
{
    wc = new Wavecatcher(this);
    view = new QMainCanvas(0);
    view->resize(view->sizeHint());
    view->setWindowTitle("Qt Example - Canvas");
    view->setGeometry(100, 100, 700, 500);
    view->show();

    connect(wc, SIGNAL(DataReceived(const WAVECAT64CH_ChannelDataStruct*)), view, SLOT(DrawWaveform(const WAVECAT64CH_ChannelDataStruct*)));

    wc->Start_Acquisition();
}

Controller::~Controller()
{
    delete view;
}
