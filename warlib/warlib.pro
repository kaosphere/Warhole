#-------------------------------------------------
#
# Project created by QtCreator 2014-01-19T14:50:11
#
#-------------------------------------------------

QT       += widgets network printsupport

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
    warlibinitializer.cpp \
    paramsfromUI/paramsfromuimodel.cpp \
    regiment/regimentabstract.cpp \
    regiment/recruitsgroup.cpp \
    Utilities/QLogger/QLogger.cpp \
    Utilities/DiceRoller/DiceRoller.cpp \ 
    Utilities/PdfExporter/pdfexporter.cpp \
    game/Historic/HistoricAbstractItem.cpp \
	game/Historic/DiceHistoricItem.cpp
	
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
    warlibinitializer.h \
    defines.h \
    paramsfromUI/paramsfromuimodel.h \
    regiment/regimentabstract.h \
    regiment/recruitsgroup.h \
    Utilities/QLogger/QLogger.h \
    Utilities/DiceRoller/DiceRoller.h \ 
    Utilities/PdfExporter/pdfexporter.h \
    game/Historic/HistoricAbstractItem.h \
    game/Historic/DiceHistoricItem.h

INSTALLS += target

