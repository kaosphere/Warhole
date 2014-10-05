#-------------------------------------------------
#
# Project created by QtCreator 2013-05-03T11:40:20
#
#-------------------------------------------------

QT       += core gui network printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

win32: TARGET = ../bin/warhole

TEMPLATE = app

win32:debug:LIBS += -L../../warlib/build/debug -lwarlib
win32:release:LIBS += -L../../warlib/build/release -lwarlib

unix:debug:LIBS += -L../../../warlib/build/debug -lwarlib
unix:release:LIBS += -L../../../warlib/build/release -lwarlib

INCLUDEPATH += ../../warlib/warlib

SOURCES += main.cpp\
        mainwindow.cpp \
    modelwindow.cpp \
    armywindow.cpp \
    gamewindow.cpp \
    graphics/testgi.cpp \
    graphics/fieldlimits.cpp \
    magicalobjectwindow.cpp \
    graphics/enhancedgraphicsview.cpp \
    graphics/regimentgraphics.cpp \
    graphics/modelgraphics.cpp \
    graphics/rulergraphics.cpp \
    chatwidget.cpp \
    core/network/networkinterface.cpp \
    core/network/networkserver.cpp \
    core/network/networkclient.cpp \
    core/network/client.cpp \
    core/network/networkthread.cpp

HEADERS  += mainwindow.h \
    modelwindow.h \
    armywindow.h \
    version.h \
    gamewindow.h \
    graphics/testgi.h \
    graphics/fieldlimits.h \
    game/distances.h \
    magicalobjectwindow.h \
    graphics/distances.h \
    graphics/enhancedgraphicsview.h \
    graphics/regimentgraphics.h \
    graphics/modelgraphics.h \
    graphics/rulergraphics.h \
    chatwidget.h \
    core/network/networkinterface.h \
    core/network/networkserver.h \
    core/network/networkclient.h \
    core/network/client.h \
    core/network/networkthread.h

TRANSLATIONS = warhole_en.ts


FORMS += \
    modelwindow.ui \
    armywindow.ui \
    gamewindow.ui \
    magicalobjectwindow.ui \
    mainwindow.ui

RESOURCES += \
    resources.qrc
