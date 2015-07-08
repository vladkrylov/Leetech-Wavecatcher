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
    SetValidastors();
    SetScales(channelScaleBox->currentData().toFloat());
    SetOffsets();

    // this must be called at pre-last
    ConnectSignalsSlots();
    // display actual channels settings
    emit selectChannelBox->currentIndexChanged(selectChannelBox->currentIndex());
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
    CreateActions();
    ConstructMenus();

    QHBoxLayout* mainLayout = new QHBoxLayout(cw);
    mainLayout->addWidget(scope);
    cw->setLayout(mainLayout);
    scope->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    QVBoxLayout* rightPanelLayout = new QVBoxLayout();
    mainLayout->addLayout(rightPanelLayout);

    rightPanelLayout->addWidget(runModeBox = new QGroupBox(tr("Run Mode"), this));
    QVBoxLayout* runModeLayout = new QVBoxLayout(runModeBox);
    runModeLayout->addWidget(continuousMode = new QRadioButton(tr("Continuous mode"), runModeBox));
    continuousMode->setChecked(true);
    runModeLayout->addWidget(finiteMode = new QRadioButton(tr("Finite mode"), runModeBox));

    QHBoxLayout* eventsRequiredLayout = new QHBoxLayout();
    rightPanelLayout->addLayout(eventsRequiredLayout);
    eventsRequiredLayout->addWidget(eventsRequiredLabel = new QLabel(tr("Events required:"), this));
    eventsRequiredLabel->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
    eventsRequiredLayout->addWidget(eventsRequiredBox = new QLineEdit(this));
    eventsRequiredBox->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Maximum);

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
        selectChannelBox->addItem(QString::number(ch), ch);
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
    channelOffsetLayout->addWidget(channelOffsetLabel2 = new QLabel(tr("%"), this));
    channelOffsetLabel2->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);

    rightPanelLayout->addWidget(horizontalLine2 = new QFrame(this));
    horizontalLine2->setFrameShape(QFrame::HLine);

    rightPanelLayout->addWidget(typeOfTriggerBox = new QGroupBox(tr("Type of trigger:"), this));
    QVBoxLayout* typeOfTriggerLayout = new QVBoxLayout(typeOfTriggerBox);

    typeOfTriggerLayout->addWidget(triggerType1 = new QRadioButton(tr("Software"), typeOfTriggerBox));
    triggerType1->setEnabled(false);
    typeOfTriggerLayout->addWidget(triggerType2 = new QRadioButton(tr("Normal"), typeOfTriggerBox));
    typeOfTriggerLayout->addWidget(triggerType3 = new QRadioButton(tr("Internal"), typeOfTriggerBox));
    triggerType3->setChecked(true);
    typeOfTriggerLayout->addWidget(triggerType4 = new QRadioButton(tr("External"), typeOfTriggerBox));
    triggerType4->setEnabled(false);
    typeOfTriggerLayout->addWidget(triggerType5 = new QRadioButton(tr("Coincidence"), typeOfTriggerBox));
    triggerType5->setEnabled(false);

    QHBoxLayout* triggerSourceLayout = new QHBoxLayout();
    rightPanelLayout->addLayout(triggerSourceLayout);
    triggerSourceLayout->addWidget(triggerSourceLabel = new QLabel(tr("Trigger source:"), this));
    triggerSourceLabel->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
    triggerSourceLayout->addWidget(triggerSourceBox = new QComboBox(this));
    for (int ch = 0; ch < N_CHANNELS; ++ch) {
        triggerSourceBox->addItem("Ch " + QString::number(ch), ch);
    }

    QHBoxLayout* triggerLevelLayout = new QHBoxLayout();
    rightPanelLayout->addLayout(triggerLevelLayout);
    triggerLevelLayout->addWidget(triggerLevelLabel = new QLabel(tr("Trigger level:"), this));
    triggerLevelLabel->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
    triggerLevelLayout->addWidget(triggerLevelBox = new QLineEdit(this));
    triggerLevelBox->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Maximum);
    triggerLevelLayout->addWidget(triggerLevelLabel2 = new QLabel(tr("mV"), this));
    triggerLevelLabel2->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
    triggerLevelLayout->addWidget(setTriggerLevelButton = new QPushButton(tr("Set"), this));


    rightPanelLayout->addSpacerItem(rightPanelSpacer = new QSpacerItem(20, 2000, QSizePolicy::Maximum, QSizePolicy::Expanding));
}

void MainWindow::ConnectSignalsSlots()
{
    connect(continuousMode, SIGNAL(clicked(bool)), this, SLOT(RunModeChanged()));
    connect(finiteMode, SIGNAL(clicked(bool)), this, SLOT(RunModeChanged()));

    connect(startButton, SIGNAL(clicked(bool)), this, SLOT(OnStartButtonClicked()));
    connect(stopButton, SIGNAL(clicked(bool)), this, SLOT(OnStopButtonClicked()));

    connect(selectChannelBox, SIGNAL(currentIndexChanged(int)), this, SLOT(DisplayChannelSettings()));
    connect(channelScaleBox, SIGNAL(currentIndexChanged(int)), this, SLOT(SetScale()));
    connect(channelScaleApplyToAllButton, SIGNAL(clicked(bool)), this, SLOT(SetScales()));
    connect(channelOffsetBox, SIGNAL(valueChanged(int)), this, SLOT(SetOffset(int)));

    connect(triggerType1, SIGNAL(clicked(bool)), this, SLOT(TriggerTypeChanged()));
    connect(triggerType2, SIGNAL(clicked(bool)), this, SLOT(TriggerTypeChanged()));
    connect(triggerType3, SIGNAL(clicked(bool)), this, SLOT(TriggerTypeChanged()));
    connect(triggerType4, SIGNAL(clicked(bool)), this, SLOT(TriggerTypeChanged()));
    connect(triggerType5, SIGNAL(clicked(bool)), this, SLOT(TriggerTypeChanged()));

    connect(triggerSourceBox, SIGNAL(currentIndexChanged(int)), this, SIGNAL(TriggerSourceChanged(int)));
    connect(setTriggerLevelButton, SIGNAL(clicked(bool)), this, SLOT(TriggerLevelChanged()));
}

void MainWindow::SetValidastors()
{
    QIntValidator* nrunsValidator = new QIntValidator(0, 1e9, this);
    eventsRequiredBox->setValidator(nrunsValidator);

    QIntValidator* triggerLevelValidator = new QIntValidator(-1250, 1250, this);
    triggerLevelBox->setValidator(triggerLevelValidator);
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

void MainWindow::SetScale()
{
    int channel = selectChannelBox->currentData().toInt();
    float val = channelScaleBox->currentData().toFloat();
    if ((channel >=0) && (channel < N_CHANNELS))
        scope->scales[channel] = val;
}

void MainWindow::SetScales()
{
    float val = channelScaleBox->currentData().toFloat();
    SetScales(val);
}

void MainWindow::SetScales(float val)
{
    for (int ch = 0; ch < N_CHANNELS; ++ch) {
        scope->scales[ch] = val;
    }
}

void MainWindow::SetOffset(int val)
{
    int channel = selectChannelBox->currentData().toInt();
    if ((channel >=0) && (channel < N_CHANNELS))
        scope->baselines[channel] = val;
}

void MainWindow::SetOffsets()
{
    for (int ch = 0; ch < N_CHANNELS; ++ch) {
        scope->baselines[ch] = (ch+1) * 100 / (N_CHANNELS + 1); // in %
    }
}

void MainWindow::DisplayChannelSettings()
{
    int index;
    int channel = selectChannelBox->currentData().toInt();
    if ((channel >= 0) && (channel < N_CHANNELS)) {
        // set scale
        index = channelScaleBox->findData(scope->scales[channel]);
        if (index >= 0)
            channelScaleBox->setCurrentIndex(index);
        else
            qDebug() << "Channel " << channel << " has wrong scale";

        // set offset
        channelOffsetBox->setValue((int)scope->baselines[channel]);
    }
}

void MainWindow::TriggerTypeChanged()
{
    if (triggerType1->isChecked()) emit SetTriggerType(0);
    else if (triggerType2->isChecked()) emit SetTriggerType(1);
    else if (triggerType3->isChecked()) emit SetTriggerType(2);
    else if (triggerType4->isChecked()) emit SetTriggerType(3);
    else if (triggerType5->isChecked()) emit SetTriggerType(4);
}

void MainWindow::TriggerLevelChanged()
{
    int channel = triggerSourceBox->currentData().toInt();
    float threshold = triggerLevelBox->text().toFloat() / 1000.;
    emit TriggerLevelChanged(channel, threshold);
}

void MainWindow::RunModeChanged()
{
    if (continuousMode->isChecked()) {
        emit SetRunMode(0, 0);
    }
    else if (finiteMode->isChecked()) {
        emit SetRunMode(1, eventsRequiredBox->text().toInt());
    }
}

void MainWindow::OnStartButtonClicked()
{
    triggerSourceBox->setEnabled(false);
    typeOfTriggerBox->setEnabled(false);
    triggerLevelBox->setEnabled(false);
    setTriggerLevelButton->setEnabled(false);
}

void MainWindow::OnStopButtonClicked()
{
    triggerSourceBox->setEnabled(true);
    typeOfTriggerBox->setEnabled(true);
    triggerLevelBox->setEnabled(true);
    setTriggerLevelButton->setEnabled(true);
}

