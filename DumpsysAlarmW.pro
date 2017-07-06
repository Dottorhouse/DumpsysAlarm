#-------------------------------------------------
#
# Project created by QtCreator 2017-07-06T10:51:31
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = DumpsysAlarmW
TEMPLATE = app


SOURCES += main.cpp\
        MainWindow.cpp \
    Alarm.cpp \
    Batch.cpp \
    ModelTreeBatch.cpp \
    ParseUtils.cpp \
    SharedData.cpp

HEADERS  += MainWindow.h \
    Alarm.h \
    Batch.h \
    ModelTreeBatch.h \
    ParseUtils.h \
    SharedData.h
