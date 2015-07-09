#include "waveformssaver.h"

#include <QDebug>
#include <QString>
#include <QElapsedTimer>

WaveformsSaver::WaveformsSaver(QObject *parent) : QObject(parent)
{
    txtOutFile = new QFile("out.txt", this);
    if (!txtOutFile->open(QIODevice::WriteOnly | QIODevice::Text))
        qDebug() << "Cannot create a file!";
    out = new QTextStream(txtOutFile);

//    QElapsedTimer eltim;
//    eltim.start();
//    for (int i = 0; i < 1000; ++i) {
//        for (int j = 0; j < 1024; ++j) {
//            *out << "-408.104,";
//        }
//        *out << endl;
//    }
//    qDebug() << eltim.elapsed();
}

void WaveformsSaver::SaveData(const WAVECAT64CH_ChannelDataStruct* channel)
{
//    qDebug() << channel[0].Peak;
    for(int i = 0; i < channel[0].WaveformDataSize; i++) {
        *out << QString::number(WAVECAT64CH_ADCTOVOLTS * channel[0].WaveformData[i]) << ",";
    }
    *out << endl;
}

