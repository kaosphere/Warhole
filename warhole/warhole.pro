#-------------------------------------------------
#
# Project created by QtCreator 2013-05-03T11:40:20
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = warhole
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    model/modelabstract.cpp

HEADERS  += mainwindow.h \
    model/modelabstract.h
