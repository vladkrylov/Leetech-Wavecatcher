#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>

class QMainCanvas;
class Wavecatcher;

class Controller : public QObject
{
    Q_OBJECT
public:
    explicit Controller(QObject *parent = 0);
    ~Controller();

private:
    Wavecatcher* wc;
    QMainCanvas* view;

signals:

public slots:
};

#endif // CONTROLLER_H
