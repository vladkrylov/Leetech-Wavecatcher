#include "controller.h"

#include <QApplication>
#include <QDebug>

#include <TApplication.h>
#include <TSystem.h>

int main(int argc, char *argv[])
{
    TApplication rootapp("Simple Qt ROOT Application", &argc, argv);
    QApplication a(argc, argv);

    Controller ctr;

    return a.exec();
}


