#ifndef WAVEFORMSSAVER_H
#define WAVEFORMSSAVER_H

#include <windows.h>
#include "WaveCat64ch_Lib.h"

#include <QObject>
#include <QFile>
#include <QTextStream>

class WaveformsSaver : public QObject
{
    Q_OBJECT
public:
    explicit WaveformsSaver(QObject *parent = 0);

public slots:
    void SaveData(const WAVECAT64CH_ChannelDataStruct *channel);

signals:

private:
    QFile* txtOutFile;
    QTextStream* out;

};

#endif // WAVEFORMSSAVER_H
