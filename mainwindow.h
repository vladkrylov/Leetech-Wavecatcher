#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <windows.h>
#include "WaveCat64ch_Lib.h"

#include <QMainWindow>
#include <QtWidgets>

class QMainCanvas;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void Test();

    // GUI elements
    QPushButton* startButton;
    QPushButton* stopButton;

public slots:
    void DrawWaveforms(const WAVECAT64CH_ChannelDataStruct* ChannelData);

private:
    QWidget* cw;
    QMainCanvas* scope;

    void ConstructGUI();

};

#endif // MAINWINDOW_H
