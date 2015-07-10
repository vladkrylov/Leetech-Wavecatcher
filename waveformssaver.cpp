#include "waveformssaver.h"

#include <QDebug>
#include <QString>
#include <QElapsedTimer>
#include <QDir>

WaveformsSaver::WaveformsSaver(QObject *parent) : QObject(parent)
{
    saveEnabled = false;
    wfFilenameBase = "Ch_";
    ampFilenameBase = "Amp_Ch_";

    txtWaveformFiles = new QFile*[N_CHANNELS];
    txtAmpFiles = new QFile*[N_CHANNELS];
    QString fWaveformsName, fAmpsName;
    for (int i = 0; i < N_CHANNELS; ++i) {
        fWaveformsName = wfFilenameBase + QString::number(i) + ".txt";
        txtWaveformFiles[i] = new QFile(fWaveformsName, this);
        if (!txtWaveformFiles[i]->open(QIODevice::WriteOnly | QIODevice::Text))
            qDebug() << "Cannot create a file!";

        fAmpsName = ampFilenameBase + QString::number(i) + ".txt";
        txtAmpFiles[i] = new QFile(fAmpsName, this);
        if (!txtAmpFiles[i]->open(QIODevice::WriteOnly | QIODevice::Text))
            qDebug() << "Cannot create a file!";
    }
    out = new QTextStream();

//    QElapsedTimer eltim;
//    eltim.start();
//    for (int i = 0; i < N_CHANNELS; ++i) {
//        out->setDevice(txtOutFiles[i]);
//        for (int i = 0; i < 1000; ++i) {
//            for (int j = 0; j < 1024; ++j) {
//                *out << QString::number(-408.104 * j + i);
//            }
//            *out << endl;
//        }
//    }
//    qDebug() << eltim.elapsed();
}

WaveformsSaver::~WaveformsSaver()
{
//    for (int i = 0; i < N_CHANNELS; ++i) {
//        delete txtOutFiles[i];
//    }
//    delete[] txtOutFiles;
//    delete out;
}

void WaveformsSaver::SaveData(const WAVECAT64CH_ChannelDataStruct* channel)
{
    if (saveEnabled) {
        for (int ch = 0; ch < N_CHANNELS; ++ch) {
            if (saveChannel[ch]) {
                out->setDevice(txtWaveformFiles[ch]);
                for(int i = 0; i < channel[0].WaveformDataSize; i++) {
                    *out << QString::number(WAVECAT64CH_ADCTOVOLTS * channel[ch].WaveformData[i]) << ",";
                }
                *out << endl;

                out->setDevice(txtAmpFiles[ch]);
                *out << channel[ch].Peak << endl;
            }
        }
    }
}

void WaveformsSaver::SetChannelsToSave(int channel, bool status)
{
    saveChannel[channel] = status;
//    qDebug() << status;
}

void WaveformsSaver::SetRunDir(QString path)
{
//    qDebug() << path;
    QString fName;

    // delete existing files
    for (int i = 0; i < N_CHANNELS; ++i) {
        delete txtWaveformFiles[i];
    }

    // construct new files
    QDir d(path);
    if (!d.exists()) d.mkpath(".");

    for (int i = 0; i < N_CHANNELS; ++i) {
        fName = path + "\\" + wfFilenameBase + QString::number(i) + ".txt";
        txtWaveformFiles[i] = new QFile(fName, this);
        if (!txtWaveformFiles[i]->open(QIODevice::WriteOnly | QIODevice::Text))
            qDebug() << "Cannot create a file!";

        fName = path + "\\" + ampFilenameBase + QString::number(i) + ".txt";
        txtAmpFiles[i] = new QFile(fName, this);
        if (!txtAmpFiles[i]->open(QIODevice::WriteOnly | QIODevice::Text))
            qDebug() << "Cannot create a file!";
    }
}

void WaveformsSaver::Enable(bool status)
{
    saveEnabled = status;
}
