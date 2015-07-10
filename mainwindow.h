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
    QGroupBox* runModeBox;
    QRadioButton* continuousMode;
    QRadioButton* finiteMode;

    QLabel* eventsRequiredLabel;
    QLineEdit* eventsRequiredBox;

    QPushButton* startButton;
    QPushButton* stopButton;
    QCheckBox* saveWfLabel;
    QPushButton* saveDirButton;

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

    QLabel* channelHScaleLabel;
    QComboBox* channelHScaleBox;
    QLabel* channelHScaleLabel2;

    QLabel* horizontalPositionLabel;
    QLineEdit* horizontalPositionBox;
    QLabel* horizontalPositionLabel2;
    QPushButton* horizontalPositionButton;

    QFrame* horizontalLine2;

    QLabel* triggerMenuLabel;
    QGroupBox* typeOfTriggerBox;
    QRadioButton* triggerType1;
    QRadioButton* triggerType2;
    QRadioButton* triggerType3;
    QRadioButton* triggerType4;
    QRadioButton* triggerType5;

    QLabel* triggerSourceLabel;
    QComboBox* triggerSourceBox;

    QLabel* triggerLevelLabel;
    QLineEdit* triggerLevelBox;
    QLabel* triggerLevelLabel2;
    QPushButton* setTriggerLevelButton;

    QSpacerItem* rightPanelSpacer;

public slots:
    void DrawWaveforms(const WAVECAT64CH_ChannelDataStruct* ChannelData);
    void DisplayEventsAcquired(int nEvents);
    void UpdateInterfaceOnStopRun();
    void ChannelsSave();

private slots:
    void ChannelEnDis();
    void OnStartButtonClicked();
    void OnStopButtonClicked();
    void SetVerticalScale();
    void SetHorizontalScale();
    void SetScales();
    void SetOffset(int val);
    void DisplayChannelSettings();
    void TriggerTypeChanged();
    void TriggerLevelChanged();
    void RunModeChanged();
    void OnPositionButtonClicked();
    void OnSaveDirButtonClicked();

signals:
    void RunStarted(int runMode, int numberOfAcquisitions);
    void RunStopped();
    void SetTriggerType(int);
    void TriggerSourceChanged(int channel);
    void TriggerLevelChanged(int channel, float threshold);
    void SetRunMode(int runmode, int param);
    void HorizontalScaleChanged(int timelengthOfWaveform);
    void HorizonatalPositionChanged(unsigned char pos);
    void SaveChannelsChanged(int channel, bool status);
    void RunDirectoryChanged(QString path);

private:
    QWidget* cw;
    QMainCanvas* scope;

    QMenu* displayChannelsMenu;
    QMenu* saveChannelsMenu;

    QList<QWidget*> disableWhenAcquisitionRunning;

    // actions
    QAction* displayChannelsAction[N_CHANNELS];
    QAction* saveChannelsAction[N_CHANNELS];

    void ConnectSignalsSlots();
    void SetValidastors();
    void ConstructGUI();
    void CreateActions();
    void ConstructMenus();

    void SetScales(float val);
    void SetOffsets();
};

#endif // MAINWINDOW_H
