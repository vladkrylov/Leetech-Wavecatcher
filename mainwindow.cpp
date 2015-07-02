#include "mainwindow.h"
#include "canvas.h"

#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    scope = new QMainCanvas(this);
    setCentralWidget(scope);
}

MainWindow::~MainWindow()
{
}

void MainWindow::DrawWaveforms(const WAVECAT64CH_ChannelDataStruct* ChannelData)
{
    scope->DrawWaveforms(ChannelData);
}





