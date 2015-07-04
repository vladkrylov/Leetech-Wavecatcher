#include "mainwindow.h"
#include "canvas.h"

#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    cw = new QWidget(this);
    scope = new QMainCanvas(cw);
    setCentralWidget(cw);

    ConstructGUI();
}

MainWindow::~MainWindow()
{
}

void MainWindow::DrawWaveforms(const WAVECAT64CH_ChannelDataStruct* ChannelData)
{
    scope->DrawWaveforms(ChannelData);
}

void MainWindow::ConstructGUI()
{
    QVBoxLayout* mainLayout = new QVBoxLayout(cw);
    mainLayout->addWidget(scope);
    mainLayout->addWidget(startButton = new QPushButton("Start", this));
    mainLayout->addWidget(stopButton = new QPushButton("Stop", this));

    cw->setLayout(mainLayout);

    CreateActions();
    ConstructMenus();
}

void MainWindow::ConstructMenus()
{
    channelsMenu = menuBar()->addMenu(tr("&Channels"));
    for (int i = 0; i < N_WCHANNELS; ++i) {
        channelsMenu->addAction(channelsAction[i]);
    }
}

void MainWindow::CreateActions()
{
    for (int i = 0; i < N_WCHANNELS; ++i) {
        channelsAction[i] = new QAction(QString("Channel ") + QString::number(i+1), this);
        channelsAction[i]->setCheckable(true);
        channelsAction[i]->setChecked(true);
    }
}
