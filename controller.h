#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>
#include <QThread>

class Wavecatcher;
class MainWindow;
class WaveformsSaver;

class Controller : public QObject
{
    Q_OBJECT
public:
    explicit Controller(QObject *parent = 0);
    ~Controller();

private:
    QThread* WCthread;
    QThread* saverThread;

    Wavecatcher* wc;
    MainWindow* view;
    WaveformsSaver* saver;

    void ConnectSignalSlots();

signals:

public slots:
    void Test();
};

#endif // CONTROLLER_H
