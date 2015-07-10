#include "mainwindow.h"
#include "canvas.h"

#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    cw = new QWidget(this);
    scope = new QMainCanvas(cw);
    setCentralWidget(cw);

    saveDir = "";

    ConstructGUI();

    SetValidators();
    SetScales(channelScaleBox->currentData().toFloat());
    SetOffsets();
    ConnectSignalsSlots();

    // display actual channels settings
    emit selectChannelBox->currentIndexChanged(selectChannelBox->currentIndex());
    runIDLine->setText("1");

    disableWhenAcquisitionRunning << triggerSourceBox
                                  << typeOfTriggerBox
                                  << triggerLevelBox
                                  << setTriggerLevelButton
                                  << channelHScaleBox
                                  << eventsRequiredBox
                                  << horizontalPositionBox
                                  << horizontalPositionButton
                                  << saveChannelsMenu
                                  << saveWfBox
                                  << runIDLine
                                  ;
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
    eventsRequiredBox->setAlignment(Qt::AlignCenter);
    eventsRequiredBox->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Maximum);

    QHBoxLayout* startStopLayout = new QHBoxLayout();
    rightPanelLayout->addLayout(startStopLayout);
    startStopLayout->addWidget(startButton = new QPushButton(tr("Start"), this));
    startButton->setMinimumHeight(50);
    startStopLayout->addWidget(stopButton = new QPushButton(tr("Stop"), this));
    stopButton->setMinimumHeight(50);

    rightPanelLayout->addWidget(saveWfBox = new QCheckBox(tr("Save waveforms"), this));
    rightPanelLayout->addWidget(saveDirButton = new QPushButton(tr("Choose Save Directory"), this));

    QHBoxLayout* runIDLayout = new QHBoxLayout();
    rightPanelLayout->addLayout(runIDLayout);
    runIDLayout->addWidget(runIDLabel = new QLabel(tr("Run ID"), this));
    runIDLabel->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
    runIDLayout->addWidget(runIDLine = new QLineEdit(this));
    runIDLine->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Maximum);
    runIDLine->setAlignment(Qt::AlignCenter);

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
    int Vscales[9] = {500, 200, 100, 50, 20, 10, 5, 2, 1}; // mV
    for (int i = 0; i < 9; ++i) {
        channelScaleBox->addItem(QString::number(Vscales[i]), Vscales[i]);
    }
    rightPanelLayout->addWidget(channelScaleApplyToAllButton = new QPushButton(tr("Apply scale to all channels"), this));

    QHBoxLayout* channelHScaleLayout = new QHBoxLayout();
    rightPanelLayout->addLayout(channelHScaleLayout);
    channelHScaleLayout->addWidget(channelHScaleLabel = new QLabel(tr("Time Scale:"), this));
    channelHScaleLabel->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
    channelHScaleLayout->addWidget(channelHScaleBox = new QComboBox(this));
    channelHScaleLayout->addWidget(channelHScaleLabel2 = new QLabel(tr("ns"), this));
    channelScaleLabel2->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
    int Hscales[8] = {20, 30, 40, 50, 60, 80, 120, 160}; // ns
    for (int i = 0; i < 8; ++i) {
        channelHScaleBox->addItem(QString::number(Hscales[i]), Hscales[i]);
    }

    QHBoxLayout* horizontalPositionLayout = new QHBoxLayout();
    rightPanelLayout->addLayout(horizontalPositionLayout);
    horizontalPositionLayout->addWidget(horizontalPositionLabel = new QLabel(tr("Position:"), this));
    horizontalPositionLabel->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
    horizontalPositionLayout->addWidget(horizontalPositionBox = new QLineEdit(this));
    horizontalPositionBox->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Maximum);
    horizontalPositionLayout->addWidget(horizontalPositionLabel2 = new QLabel(tr("?"), this));
    horizontalPositionLabel2->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
    horizontalPositionLayout->addWidget(horizontalPositionButton = new QPushButton(tr("Set"), this));


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
    connect(channelScaleBox, SIGNAL(currentIndexChanged(int)), this, SLOT(SetVerticalScale()));
    connect(channelHScaleBox, SIGNAL(currentIndexChanged(int)), this, SLOT(SetHorizontalScale()));
    connect(channelScaleApplyToAllButton, SIGNAL(clicked(bool)), this, SLOT(SetScales()));
    connect(channelOffsetBox, SIGNAL(valueChanged(int)), this, SLOT(SetOffset(int)));
    connect(horizontalPositionButton, SIGNAL(clicked(bool)), this, SLOT(OnPositionButtonClicked()));
    connect(saveDirButton, SIGNAL(clicked(bool)), this, SLOT(OnSaveDirButtonClicked()));
    connect(saveWfBox, SIGNAL(clicked(bool)), this, SLOT(OnSaveBoxClicked()));

    connect(triggerType1, SIGNAL(clicked(bool)), this, SLOT(TriggerTypeChanged()));
    connect(triggerType2, SIGNAL(clicked(bool)), this, SLOT(TriggerTypeChanged()));
    connect(triggerType3, SIGNAL(clicked(bool)), this, SLOT(TriggerTypeChanged()));
    connect(triggerType4, SIGNAL(clicked(bool)), this, SLOT(TriggerTypeChanged()));
    connect(triggerType5, SIGNAL(clicked(bool)), this, SLOT(TriggerTypeChanged()));

    connect(triggerSourceBox, SIGNAL(currentIndexChanged(int)), this, SIGNAL(TriggerSourceChanged(int)));
    connect(setTriggerLevelButton, SIGNAL(clicked(bool)), this, SLOT(TriggerLevelChanged()));
}

void MainWindow::SetValidators()
{
    QIntValidator* nrunsValidator = new QIntValidator(0, 1e9, this);
    eventsRequiredBox->setValidator(nrunsValidator);

    QIntValidator* triggerLevelValidator = new QIntValidator(-1250, 1250, this);
    triggerLevelBox->setValidator(triggerLevelValidator);

    QIntValidator* horizontalPositionValidator = new QIntValidator(0, 255, this);
    horizontalPositionBox->setValidator(horizontalPositionValidator);

    QIntValidator* runIDValidator = new QIntValidator(0, 1e9, this);
    runIDLine->setValidator(runIDValidator);
}

void MainWindow::ConstructMenus()
{
    displayChannelsMenu = menuBar()->addMenu(tr("&Display Channels"));
    for (int ch = 0; ch < N_CHANNELS; ++ch) {
        displayChannelsMenu->addAction(displayChannelsAction[ch]);
        if ((ch != 1)
            && (ch != 5)
            )
            displayChannelsAction[ch]->toggle();
    }

    saveChannelsMenu = menuBar()->addMenu(tr("&Save Channels"));
    for (int ch = 0; ch < N_CHANNELS; ++ch) {
        saveChannelsMenu->addAction(saveChannelsAction[ch]);
        if ((ch != 1)
            && (ch != 5)
            )
            saveChannelsAction[ch]->toggle();
    }
}

void MainWindow::CreateActions()
{
    bool defaultStatus = true;
    for (int ch = 0; ch < N_CHANNELS; ++ch) {
        displayChannelsAction[ch] = new QAction(QString("Channel ") + QString::number(ch), this);
        displayChannelsAction[ch]->setCheckable(true);
        displayChannelsAction[ch]->setChecked(defaultStatus);

        connect(displayChannelsAction[ch], SIGNAL(toggled(bool)), this, SLOT(ChannelEnDis()));
    }

    for (int ch = 0; ch < N_CHANNELS; ++ch) {
        saveChannelsAction[ch] = new QAction(QString("Channel ") + QString::number(ch), this);
        saveChannelsAction[ch]->setCheckable(true);
        saveChannelsAction[ch]->setChecked(defaultStatus);

        connect(saveChannelsAction[ch], SIGNAL(toggled(bool)), this, SLOT(ChannelsSave()));
    }
}

void MainWindow::ChannelEnDis()
{
    for (int ch = 0; ch < N_CHANNELS; ++ch) {
        scope->enabled[ch] = displayChannelsAction[ch]->isChecked();
//        qDebug() << "Channel " << ch << (displayChannelsAction[ch]->isChecked() ? "enabled" : "disabled");
    }
}

void MainWindow::ChannelsSave()
{
    for (int ch = 0; ch < N_CHANNELS; ++ch) {
        emit SaveChannelsChanged(ch, saveChannelsAction[ch]->isChecked());
    }
}

void MainWindow::SetVerticalScale()
{
    int channel = selectChannelBox->currentData().toInt();
    float val = channelScaleBox->currentData().toFloat();
    if ((channel >=0) && (channel < N_CHANNELS))
        scope->scales[channel] = val;
}

void MainWindow::SetHorizontalScale()
{
    int val = channelHScaleBox->currentData().toInt();
    emit HorizontalScaleChanged(val * scope->N_HORIZONTAL_DIVISIONS);
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
    if (saveWfBox->isChecked()) {
        QDir d(saveDir);
        emit RunDirectoryChanged(d.absoluteFilePath(runIDLine->text()));
    }

    // set run mode and number of acquisitions
    int runMode = 0;
    int nacq = 0;
    if (continuousMode->isChecked()) runMode = 0;
    else if (finiteMode->isChecked()) {
        runMode = 1;
        nacq = eventsRequiredBox->text().toInt();
        if (!nacq) {
            QMessageBox::critical(this
                                  , tr("Error")
                                  , tr("Number of acquisitions must be set before running.")
                                  );
            return;
        }
    }

    foreach (QWidget* w, disableWhenAcquisitionRunning) {
        w->setEnabled(false);
    }

    emit RunStarted(runMode, nacq);
}

void MainWindow::OnStopButtonClicked()
{
    UpdateInterfaceOnStopRun();
    emit RunStopped();
}

void MainWindow::DisplayEventsAcquired(int nEvents)
{
    if (continuousMode->isChecked())
        eventsRequiredBox->setText(QString::number(nEvents));
    else if (finiteMode->isChecked()) {
        QStringList l = eventsRequiredBox->text().split("/");
        eventsRequiredBox->setText(QString::number(nEvents)
                                   + "/"
                                   + l.last());
    }
}

void MainWindow::UpdateInterfaceOnStopRun()
{
    foreach (QWidget* w, disableWhenAcquisitionRunning) {
        w->setEnabled(true);
    }
    QStringList l = eventsRequiredBox->text().split("/");
    eventsRequiredBox->setText(l.first());
    runIDLine->setText(QString::number(runIDLine->text().toInt() + 1));
}

void MainWindow::OnPositionButtonClicked()
{
    unsigned char pos = horizontalPositionBox->text().toShort();
    emit HorizonatalPositionChanged(pos);
}

void MainWindow::OnSaveDirButtonClicked()
{
    saveDir = QFileDialog::getExistingDirectory(this, tr("Choose directory"));
}

void MainWindow::OnSaveBoxClicked()
{
    if (saveWfBox->isChecked()) {
        if (saveDir.isEmpty()) OnSaveDirButtonClicked();
        emit SetSaveStatus(true);
    } else {
        emit SetSaveStatus(false);
    }
}
