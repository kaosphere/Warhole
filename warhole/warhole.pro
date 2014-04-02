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

unix:debug:LIBS += -L../../warlib/build/Debug -lwarlib
unix:release:LIBS += -L../../warlib/build/Release -lwarlib

INCLUDEPATH += ../../warlib/warlib

SOURCES += main.cpp\
        mainwindow.cpp \
    modelwindow.cpp \
    armywindow.cpp \
    gamewindow.cpp \
    game/testgi.cpp \
    game/fieldlimits.cpp

HEADERS  += mainwindow.h \
    modelwindow.h \
    armywindow.h \
    version.h \
    gamewindow.h \
    game/testgi.h \
    game/fieldlimits.h \
    game/distances.h \


FORMS += \
    modelwindow.ui \
    armywindow.ui \
    gamewindow.ui

RESOURCES += \
    resources.qrc
