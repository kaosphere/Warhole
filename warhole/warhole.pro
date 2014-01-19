#-------------------------------------------------
#
# Project created by QtCreator 2013-05-03T11:40:20
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

win32: TARGET = ../bin/warhole

TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    model/modelabstract.cpp \
    model/modelinfantery.cpp \
    option/optionmodel.cpp \
    model/modelcavalry.cpp \
    model/modelwarmachine.cpp \
    model/modelcharacter.cpp \
    model/modelmonster.cpp \
    model/modelcharriot.cpp \
    modelwindow.cpp \
    stats/statsmodel.cpp \
    armywindow.cpp \
    unit/unitabstract.cpp \
    army/army.cpp \
    gamewindow.cpp \
    game/testgi.cpp \
    game/fieldlimits.cpp

HEADERS  += mainwindow.h \
    model/modelabstract.h \
    model/modelinfantery.h \
    option/optionmodel.h \
    model/modelcavalry.h \
    model/modelwarmachine.h \
    model/modelcharacter.h \
    model/modelmonster.h \
    model/modelcharriot.h \
    modelwindow.h \
    stats/statsmodel.h \
    armywindow.h \
    unit/unitabstract.h \
    army/army.h \
    version.h \
    gamewindow.h \
    game/testgi.h \
    game/fieldlimits.h \
    game/distances.h \
    defines.h

FORMS += \
    modelwindow.ui \
    armywindow.ui \
    gamewindow.ui

RESOURCES += \
    resources.qrc
