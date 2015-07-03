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
    mainLayout->addWidget(updateButton = new QPushButton("Update", this));
    mainLayout->addWidget(stopButton = new QPushButton("Stop", this));

    cw->setLayout(mainLayout);
}




