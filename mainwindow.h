#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <windows.h>
#include "WaveCat64ch_Lib.h"
#include "canvas.h"

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
    QCheckBox* saveWfLabel;
    QPushButton* saveOptButton;

    QFrame* horizontalLine1;

    QLabel* selectChannelLabel;
    QComboBox* selectChannelBox;

    QLabel* channelScaleLabel;
    QComboBox* channelScaleBox;
    QLabel* channelScaleLabel2;
    QPushButton* channelScaleApplyToAllButton;
    QLabel* channelOffsetLabel;
    QSpinBox* channelOffsetBox;
    QLabel* channelOffsetLabel2;

    QSpacerItem* rightPanelSpacer;

public slots:
    void DrawWaveforms(const WAVECAT64CH_ChannelDataStruct* ChannelData);

private slots:
    void ChannedEnDis();

signals:

private:
    QWidget* cw;
    QMainCanvas* scope;

    QMenu* channelsMenu;

    // actions
    QAction* channelsAction[N_CHANNELS];

    void ConstructGUI();
    void CreateActions();
    void ConstructMenus();
};

#endif // MAINWINDOW_H
