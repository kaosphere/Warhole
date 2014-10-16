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
    gameconfiguratordialog.cpp \
    connecttoserverdialog.cpp \
    chatwidgetform.cpp \
    statsdisplayform.cpp \
    graphics/roundtemplategraphics.cpp \
    getintdialog.cpp

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
    gameconfiguratordialog.h \
    connecttoserverdialog.h \
    chatwidgetform.h \
    statsdisplayform.h \
    graphics/roundtemplategraphics.h \
    getintdialog.h

TRANSLATIONS = warhole_en.ts


FORMS += \
    modelwindow.ui \
    armywindow.ui \
    gamewindow.ui \
    magicalobjectwindow.ui \
    mainwindow.ui \
    gameconfiguratordialog.ui \
    connecttoserverdialog.ui \
    chatwidgetform.ui \
    statsdisplayform.ui \
    getintdialog.ui

RESOURCES += \
    resources.qrc
