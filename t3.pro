#-------------------------------------------------
#
# Project created by QtCreator 2015-06-25T22:50:09
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = t3
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h \
    WaveCat64ch_Lib.h \
    WaveCat64Ch_RatePanel.h \
    WaveCat64Ch_Sample.h

INCLUDEPATH += "C:\Program Files (x86)\National Instruments\CVI2009\include"

FORMS    += mainwindow.ui

LIBS += -L"C:\Program Files (x86)\National Instruments\CVI2009\extlib\msvc" \
        -lcvirt -lcvi_lvrt -linstrsup
LIBS += -L"C:\LEETECH\Eclipse_workspace\Wavecatcher" -lWaveCat64Ch


