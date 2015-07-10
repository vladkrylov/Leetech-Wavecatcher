#ifndef WAVEFORMSSAVER_H
#define WAVEFORMSSAVER_H

#include <windows.h>
#include "WaveCat64ch_Lib.h"
#include "wavecatcher.h"

#include <QObject>
#include <QFile>
#include <QTextStream>
#include <QString>

class WaveformsSaver : public QObject
{
    Q_OBJECT
public:
    explicit WaveformsSaver(QObject *parent = 0);
    ~WaveformsSaver();

public slots:
    void SaveData(const WAVECAT64CH_ChannelDataStruct *channel);
    void SetChannelsToSave(int channel, bool status);
    void SetRunDir(QString path);
    void Enable(bool status);

signals:

private:
    bool saveEnabled;
    QString wfFilenameBase;
    QString ampFilenameBase;

    QFile** txtWaveformFiles;
    QFile** txtAmpFiles;
    QTextStream* out;

    bool saveChannel[N_CHANNELS];

};

#endif // WAVEFORMSSAVER_H
