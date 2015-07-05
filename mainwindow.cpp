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
    QHBoxLayout* mainLayout = new QHBoxLayout(cw);
    mainLayout->addWidget(scope);
    cw->setLayout(mainLayout);
    scope->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    QVBoxLayout* rightPanelLayout = new QVBoxLayout();
    mainLayout->addLayout(rightPanelLayout);

    QHBoxLayout* startStopLayout = new QHBoxLayout();
    rightPanelLayout->addLayout(startStopLayout);
    startStopLayout->addWidget(startButton = new QPushButton(tr("Start"), this));
    startButton->setMinimumHeight(50);
    startStopLayout->addWidget(stopButton = new QPushButton(tr("Stop"), this));
    stopButton->setMinimumHeight(50);

    rightPanelLayout->addWidget(saveWfLabel = new QCheckBox(tr("Save waveforms"), this));
    rightPanelLayout->addWidget(saveOptButton = new QPushButton(tr("Save Options"), this));

    rightPanelLayout->addWidget(horizontalLine1 = new QFrame(this));
    horizontalLine1->setFrameShape(QFrame::HLine);
//    horizontalLine1->setStyleSheet("background-color: #c0c0c0;");

    QHBoxLayout* selectChannelLayout = new QHBoxLayout();
    rightPanelLayout->addLayout(selectChannelLayout);
    selectChannelLayout->addWidget(selectChannelLabel = new QLabel(tr("Channel N:"), this));
    selectChannelLabel->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
    selectChannelLayout->addWidget(selectChannelBox = new QComboBox(this));
    for (int ch = 0; ch < N_CHANNELS; ++ch) {
        selectChannelBox->addItem(QString::number(ch+1), ch);
    }

    QHBoxLayout* channelScaleLayout = new QHBoxLayout();
    rightPanelLayout->addLayout(channelScaleLayout);
    channelScaleLayout->addWidget(channelScaleLabel = new QLabel(tr("Scale:"), this));
    channelScaleLabel->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
    channelScaleLayout->addWidget(channelScaleBox = new QComboBox(this));
    channelScaleLayout->addWidget(channelScaleLabel2 = new QLabel(tr("mV/div"), this));
    channelScaleLabel2->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
    int scales[9] = {500, 200, 100, 50, 20, 10, 5, 2, 1}; // mV
    for (int i = 0; i < 9; ++i) {
        channelScaleBox->addItem(QString::number(scales[i]), scales[i]);
    }
    rightPanelLayout->addWidget(channelScaleApplyToAllButton = new QPushButton(tr("Apply scale to all channels"), this));

    QHBoxLayout* channelHScaleLayout = new QHBoxLayout();
    rightPanelLayout->addLayout(channelHScaleLayout);
    channelHScaleLayout->addWidget(channelHScaleLabel = new QLabel(tr("Time Scale:"), this));
    channelHScaleLabel->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
    channelHScaleLayout->addWidget(channelHScaleBox = new QComboBox(this));
    channelHScaleLayout->addWidget(channelHScaleLabel2 = new QLabel(tr("ns"), this));
    channelScaleLabel2->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
    int Hscales[9] = {500, 200, 100, 50, 20, 10, 5, 2, 1}; // ns
    for (int i = 0; i < 9; ++i) {
        channelHScaleBox->addItem(QString::number(Hscales[i]), Hscales[i]);
    }


    QHBoxLayout* channelOffsetLayout = new QHBoxLayout();
    rightPanelLayout->addLayout(channelOffsetLayout);
    channelOffsetLayout->addWidget(channelOffsetLabel = new QLabel(tr("Offset:"), this));
    channelOffsetLabel->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
    channelOffsetLayout->addWidget(channelOffsetBox = new QSpinBox(this));
    channelOffsetLayout->addWidget(channelOffsetLabel2 = new QLabel(tr("mV"), this));
    channelOffsetLabel2->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);

    rightPanelLayout->addWidget(horizontalLine2 = new QFrame(this));
    horizontalLine2->setFrameShape(QFrame::HLine);

    rightPanelLayout->addWidget(typeOfTriggerBox = new QGroupBox(tr("Type of trigger:"), this));
    QVBoxLayout* typeOfTriggerLayout = new QVBoxLayout(typeOfTriggerBox);

    typeOfTriggerLayout->addWidget(triggerType1 = new QRadioButton(tr("Software"), typeOfTriggerBox));
    typeOfTriggerLayout->addWidget(triggerType2 = new QRadioButton(tr("Normal"), typeOfTriggerBox));
    typeOfTriggerLayout->addWidget(triggerType3 = new QRadioButton(tr("Internal"), typeOfTriggerBox));
    triggerType3->setChecked(true);
    typeOfTriggerLayout->addWidget(triggerType4 = new QRadioButton(tr("External"), typeOfTriggerBox));
    typeOfTriggerLayout->addWidget(triggerType5 = new QRadioButton(tr("Coincidence"), typeOfTriggerBox));

    QHBoxLayout* triggerLevelLayout = new QHBoxLayout();
    rightPanelLayout->addLayout(triggerLevelLayout);
    triggerLevelLayout->addWidget(triggerLevelLabel = new QLabel(tr("Trigger level:"), this));
    triggerLevelLabel->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
    triggerLevelLayout->addWidget(triggerLevelBox = new QSpinBox(this));
    triggerLevelLayout->addWidget(triggerLevelLabel2 = new QLabel(tr("mV"), this));
    triggerLevelLabel2->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);



    rightPanelLayout->addSpacerItem(rightPanelSpacer = new QSpacerItem(20, 2000, QSizePolicy::Maximum, QSizePolicy::Expanding));

    CreateActions();
    ConstructMenus();
}

void MainWindow::ConstructMenus()
{
    channelsMenu = menuBar()->addMenu(tr("&Channels"));
    for (int ch = 0; ch < N_CHANNELS; ++ch) {
        channelsMenu->addAction(channelsAction[ch]);
    }
}

void MainWindow::CreateActions()
{
    bool defaultStatus = true;
    for (int ch = 0; ch < N_CHANNELS; ++ch) {
        channelsAction[ch] = new QAction(QString("Channel ") + QString::number(ch+1), this);
        channelsAction[ch]->setCheckable(true);
        channelsAction[ch]->setChecked(defaultStatus);

        connect(channelsAction[ch], SIGNAL(toggled(bool)), this, SLOT(ChannedEnDis()));
    }
}

void MainWindow::ChannedEnDis()
{
    for (int ch = 0; ch < N_CHANNELS; ++ch) {
        scope->enabled[ch] = channelsAction[ch]->isChecked();
        qDebug() << "Channel " << ch+1 << (channelsAction[ch]->isChecked() ? "enabled" : "disabled");
    }
}
