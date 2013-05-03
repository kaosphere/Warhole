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
    model/modelabstract.cpp \
    model/modelinfantery.cpp \
    option/optionmodel.cpp \
    model/modelanimal.cpp \
    model/modelcavalry.cpp \
    model/modelwarmachine.cpp \
    model/modelcharacter.cpp

HEADERS  += mainwindow.h \
    model/modelabstract.h \
    model/modelinfantery.h \
    option/optionmodel.h \
    model/modelanimal.h \
    model/modelcavalry.h \
    model/modelwarmachine.h \
    model/modelcharacter.h
