#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <windows.h>
#include "WaveCat64ch_Lib.h"

#include <QMainWindow>
#include <QtWidgets>

const int N_WCHANNELS = 8;

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

signals:
    ChannelEnabled(short chId);
    ChannelDisabled(short chId);

private:
    QWidget* cw;
    QMainCanvas* scope;

    QMenu* channelsMenu;

    // actions
    QAction* channelsAction[N_WCHANNELS];

    void ConstructGUI();
    void CreateActions();
    void ConstructMenus();

};

#endif // MAINWINDOW_H
