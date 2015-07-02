#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <windows.h>
#include "WaveCat64ch_Lib.h"

#include <QMainWindow>

class QMainCanvas;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void Test();

public slots:
    void DrawWaveforms(const WAVECAT64CH_ChannelDataStruct* ChannelData);

private:
    QMainCanvas* scope;

};

#endif // MAINWINDOW_H
