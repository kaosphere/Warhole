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
    game/stats/statsmodel.cpp \
    game/army/army.cpp \
    game/model/modelwarmachine.cpp \
    game/model/modelmonster.cpp \
    game/model/modelinfantery.cpp \
    game/model/modelfactory.cpp \
    game/model/modelcharriot.cpp \
    game/model/modelcharacter.cpp \
    game/model/modelcavalry.cpp \
    game/model/modelabstract.cpp \
    game/option/optionmodel.cpp \
    warlibinitializer.cpp \
    game/paramsfromUI/paramsfromuimodel.cpp \
    game/regiment/regimentabstract.cpp \
    game/regiment/recruitsgroup.cpp \
    Utilities/QLogger/QLogger.cpp \
    Utilities/DiceRoller/DiceRoller.cpp \ 
    Utilities/PdfExporter/pdfexporter.cpp \
    game/historic/ChatHistoricItem.cpp \
    game/historic/DiceHistoricItem.cpp \
    game/historic/HistoricAbstractItem.cpp \
    game/historic/historic.cpp \
    core/messagequeue.cpp \
    core/message.cpp \
    game/game.cpp \
    game/player.cpp \
    game/magicalObject/magicalobject.cpp \
    Utilities/RandomIdGenerator/idgenerator.cpp
	
HEADERS += \
    game/stats/statsmodel.h \
    game/army/army.h \
    game/model/modelwarmachine.h \
    game/model/modelmonster.h \
    game/model/modelinfantery.h \
    game/model/modelfactory.h \
    game/model/modelcharriot.h \
    game/model/modelcharacter.h \
    game/model/modelcavalry.h \
    game/model/modelabstract.h \
    game/option/optionmodel.h \
    warlibinitializer.h \
    defines.h \
    game/paramsfromUI/paramsfromuimodel.h \
    game/regiment/regimentabstract.h \
    game/regiment/recruitsgroup.h \
    Utilities/QLogger/QLogger.h \
    Utilities/DiceRoller/DiceRoller.h \ 
    Utilities/PdfExporter/pdfexporter.h \
    game/historic/ChatHistoricItem.h \
    game/historic/DiceHistoricItem.h \
    game/historic/HistoricAbstractItem.h \
    game/historic/historic.h \
    core/messagequeue.h \
    core/message.h \
    game/game.h \
    game/player.h \
    game/magicalObject/magicalobject.h \
    core/warlibexception.h \
    Utilities/RandomIdGenerator/idgenerator.h

INSTALLS += target

