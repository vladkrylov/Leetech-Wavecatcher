#include "waveformssaver.h"
#include "wavecatcher.h"

#include <QDebug>
#include <QString>
#include <QElapsedTimer>

WaveformsSaver::WaveformsSaver(QObject *parent) : QObject(parent)
{
    filenameBase = "Ch_";

    txtOutFiles = new QFile*[N_CHANNELS];
    QString fName;
    for (int i = 0; i < N_CHANNELS; ++i) {
        fName = filenameBase + QString::number(i) + ".txt";
        txtOutFiles[i] = new QFile(fName, this);

        if (!txtOutFiles[i]->open(QIODevice::WriteOnly | QIODevice::Text))
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
//    qDebug() << channel[0].Peak;
    for (int ch = 0; ch < N_CHANNELS; ++ch) {
        out->setDevice(txtOutFiles[ch]);
        for(int i = 0; i < channel[0].WaveformDataSize; i++) {
            *out << QString::number(WAVECAT64CH_ADCTOVOLTS * channel[ch].WaveformData[i]) << ",";
        }
        *out << endl;
    }
}

