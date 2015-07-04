#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>
#include <QThread>

class Wavecatcher;
class MainWindow;

class Controller : public QObject
{
    Q_OBJECT
public:
    explicit Controller(QObject *parent = 0);
    ~Controller();

private:
    QThread* WCthread;
    Wavecatcher* wc;
    MainWindow* view;

    void ConnectSignalSlots();

signals:

public slots:
};

#endif // CONTROLLER_H
