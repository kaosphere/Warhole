#-------------------------------------------------
#
# Project created by QtCreator 2014-01-19T14:50:11
#
#-------------------------------------------------

QT       += widgets network

TARGET = warlib


TEMPLATE = lib
CONFIG += staticlib

SOURCES += \
    stats/statsmodel.cpp \
    army/army.cpp \
    model/modelwarmachine.cpp \
    model/modelmonster.cpp \
    model/modelinfantery.cpp \
    model/modelfactory.cpp \
    model/modelcharriot.cpp \
    model/modelcharacter.cpp \
    model/modelcavalry.cpp \
    model/modelabstract.cpp \
    option/optionmodel.cpp \
    unit/unitabstract.cpp \
    warlibinitializer.cpp

HEADERS += \
    stats/statsmodel.h \
    army/army.h \
    model/modelwarmachine.h \
    model/modelmonster.h \
    model/modelinfantery.h \
    model/modelfactory.h \
    model/modelcharriot.h \
    model/modelcharacter.h \
    model/modelcavalry.h \
    model/modelabstract.h \
    option/optionmodel.h \
    unit/unitabstract.h \
    warlibinitializer.h \
    defines.h

INSTALLS += target

