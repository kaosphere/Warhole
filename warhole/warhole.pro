#
# Copyright (c), 2014 
#       Alexandre Jumeline 
#       Perrine Fauconnier
# All rights reserved.
#
#    This program is free software: you can redistribute it and/or modify
#    it under the terms of the GNU General Public License as published by
#    the Free Software Foundation, either version 3 of the License, or
#    any later version.
#
#    This program is distributed in the hope that it will be useful,
#    but WITHOUT ANY WARRANTY; without even the implied warranty of
#    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#    GNU General Public License for more details.
#
#    You should have received a copy of the GNU General Public License
#    along with this program.  If not, see <http://www.gnu.org/licenses/>.
#

QT       += core gui network printsupport

greaterThan(QT_MAJOR_VERSION, 5): QT += widgets

win32: TARGET = ../bin/warhole

TEMPLATE = app

win32:debug:LIBS += -L../../warlib/build/debug -lwarlib
win32:release:LIBS += -L../../warlib/build/release -lwarlib

unix:debug:LIBS += -L../../warlib/build/debug -lwarlib
unix:release:LIBS += -L../../warlib/build/release -lwarlib

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
    getintdialog.cpp \
    statsdisplaywidget.cpp \
    terrainwindow.cpp \
    graphics/terraingraphics.cpp \
    regimentinfodialog.cpp \
    graphics/blowtemplategraphics.cpp \
    graphics/textgraphics.cpp \
    graphics/dispersiongraphics.cpp \
    warholeinfodialog.cpp \
    components/enhancedgraphicsscene.cpp \
    components/enhancegraphicsobject.cpp \
    graphics/lineofsightgraphics.cpp \
    terraininfodisplayform.cpp \
    backgroundselectiondialog.cpp \
    armywindowevolved.cpp \
    addregimentdialog.cpp

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
    getintdialog.h \
    statsdisplaywidget.h \
    terrainwindow.h \
    graphics/terraingraphics.h \
    regimentinfodialog.h \
    graphics/blowtemplategraphics.h \
    graphics/textgraphics.h \
    graphics/dispersiongraphics.h \
    warholeinfodialog.h \
    components/enhancedgraphicsscene.h \
    components/enhancegraphicsobject.h \
    graphics/lineofsightgraphics.h \
    terraininfodisplayform.h \
    backgroundselectiondialog.h \
    graphics/backgroundtypes.h \
    armywindowevolved.h \
    addregimentdialog.h

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
    getintdialog.ui \
    statsdisplaywidget.ui \
    terrainwindow.ui \
    regimentinfodialog.ui \
    warholeinfodialog.ui \
    terraininfodisplayform.ui \
    backgroundselectiondialog.ui \
    armywindowevolved.ui \
    addregimentdialog.ui

RESOURCES += \
    resources.qrc
