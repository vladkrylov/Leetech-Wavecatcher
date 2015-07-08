#include "waveformssaver.h"

#include <QDebug>

WaveformsSaver::WaveformsSaver(QObject *parent) : QObject(parent)
{
    txtOutFile = new QFile("out.txt", this);
    if (!txtOutFile->open(QIODevice::WriteOnly | QIODevice::Text))
        qDebug() << "Cannot create a file!";
    out = new QTextStream(txtOutFile);
}

void WaveformsSaver::SaveData(const WAVECAT64CH_ChannelDataStruct* channel)
{
    qDebug() << channel[0].Peak;
}

