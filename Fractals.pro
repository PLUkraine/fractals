#-------------------------------------------------
#
# Project created by QtCreator 2015-02-22T16:13:23
#
#-------------------------------------------------

QT       += core gui concurrent

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Fractals
TEMPLATE = app
CONFIG += c++11


SOURCES += main.cpp \
    Fractals/heighwaydragon.cpp \
    Fractals/sierpinskifractal.cpp \
    Util/imageproxy.cpp \
    fractalview.cpp \
    mainwindow.cpp

HEADERS  += \
    Fractals/fractalbuilder.h \
    Fractals/heighwaydragon.h \
    Fractals/sierpinskifractal.h \
    Util/channel.h \
    Util/imageproxy.h \
    fractalview.h \
    mainwindow.h

FORMS    += \
    mainwindow.ui
