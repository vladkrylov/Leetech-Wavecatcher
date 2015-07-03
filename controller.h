#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>

class Wavecatcher;
class MainWindow;

class Controller : public QObject
{
    Q_OBJECT
public:
    explicit Controller(QObject *parent = 0);
    ~Controller();

private:
    Wavecatcher* wc;
    MainWindow* view;

    void ConnectSignalSlots();

signals:

public slots:
};

#endif // CONTROLLER_H
