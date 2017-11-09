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

SOURCES += \
    components/enhancedgraphicsscene.cpp \
    components/enhancegraphicsobject.cpp \
    core/commandManager/commandmanager.cpp \
    core/network/client.cpp \
    core/network/networkclient.cpp \
    core/network/networkinterface.cpp \
    core/network/networkserver.cpp \
    core/PlayerAdmninistrator/playeradministrator.cpp \
    core/gamecontroller.cpp \
    core/message.cpp \
    core/messagequeue.cpp \
    game/army/army.cpp \
    game/historic/ChatHistoricItem.cpp \
    game/historic/DiceHistoricItem.cpp \
    game/historic/historic.cpp \
    game/historic/HistoricAbstractItem.cpp \
    game/magicalObject/magicalobject.cpp \
    game/model/modelabstract.cpp \
    game/model/modelcavalry.cpp \
    game/model/modelcharacter.cpp \
    game/model/modelcharriot.cpp \
    game/model/modelfactory.cpp \
    game/model/modelinfantery.cpp \
    game/model/modelmonster.cpp \
    game/model/modelwarmachine.cpp \
    game/option/optionmodel.cpp \
    game/paramsfromUI/paramsfromuimodel.cpp \
    game/regiment/recruitsgroup.cpp \
    game/regiment/regimentabstract.cpp \
    game/stats/statsmodel.cpp \
    game/terrain/terrain.cpp \
    game/game.cpp \
    game/player.cpp \
    graphics/blowtemplategraphics.cpp \
    graphics/dispersiongraphics.cpp \
    graphics/enhancedgraphicsview.cpp \
    graphics/fieldlimits.cpp \
    graphics/lineofsightgraphics.cpp \
    graphics/modelgraphics.cpp \
    graphics/regimentgraphics.cpp \
    graphics/roundtemplategraphics.cpp \
    graphics/rulergraphics.cpp \
    graphics/terraingraphics.cpp \
    graphics/testgi.cpp \
    graphics/textgraphics.cpp \
    UI/addregimentdialog.cpp \
    UI/armywindow.cpp \
    UI/armywindowevolved.cpp \
    UI/backgroundselectiondialog.cpp \
    UI/chatwidgetform.cpp \
    UI/connecttoserverdialog.cpp \
    UI/gameconfiguratordialog.cpp \
    UI/gamewindow.cpp \
    UI/getintdialog.cpp \
    UI/magicalobjectwindow.cpp \
    UI/mainwindow.cpp \
    UI/modelwindow.cpp \
    UI/regimentinfodialog.cpp \
    UI/statsdisplayform.cpp \
    UI/statsdisplaywidget.cpp \
    UI/terraininfodisplayform.cpp \
    UI/terrainwindow.cpp \
    UI/warholeinfodialog.cpp \
    Utilities/DiceRoller/DiceRoller.cpp \
    Utilities/PdfExporter/pdfexporter.cpp \
    Utilities/QLogger/QLogger.cpp \
    Utilities/RandomIdGenerator/idgenerator.cpp \
    main.cpp \
    warlibinitializer.cpp

HEADERS  += \
    components/enhancedgraphicsscene.h \
    components/enhancegraphicsobject.h \
    core/commandManager/commandmanager.h \
    core/network/client.h \
    core/network/networkclient.h \
    core/network/networkinterface.h \
    core/network/networkserver.h \
    core/PlayerAdmninistrator/playeradministrator.h \
    core/gamecontroller.h \
    core/message.h \
    core/messagequeue.h \
    core/warlibexception.h \
    game/army/army.h \
    game/historic/ChatHistoricItem.h \
    game/historic/DiceHistoricItem.h \
    game/historic/historic.h \
    game/historic/HistoricAbstractItem.h \
    game/magicalObject/magicalobject.h \
    game/model/modelabstract.h \
    game/model/modelcavalry.h \
    game/model/modelcharacter.h \
    game/model/modelcharriot.h \
    game/model/modelfactory.h \
    game/model/modelinfantery.h \
    game/model/modelmonster.h \
    game/model/modelwarmachine.h \
    game/option/optionmodel.h \
    game/paramsfromUI/paramsfromuimodel.h \
    game/regiment/recruitsgroup.h \
    game/regiment/regimentabstract.h \
    game/stats/statsmodel.h \
    game/terrain/terrain.h \
    game/game.h \
    game/player.h \
    graphics/backgroundtypes.h \
    graphics/blowtemplategraphics.h \
    graphics/dispersiongraphics.h \
    graphics/distances.h \
    graphics/enhancedgraphicsview.h \
    graphics/fieldlimits.h \
    graphics/lineofsightgraphics.h \
    graphics/modelgraphics.h \
    graphics/regimentgraphics.h \
    graphics/roundtemplategraphics.h \
    graphics/rulergraphics.h \
    graphics/terraingraphics.h \
    graphics/testgi.h \
    graphics/textgraphics.h \
    UI/addregimentdialog.h \
    UI/armywindow.h \
    UI/armywindowevolved.h \
    UI/backgroundselectiondialog.h \
    UI/chatwidgetform.h \
    UI/connecttoserverdialog.h \
    UI/gameconfiguratordialog.h \
    UI/gamewindow.h \
    UI/getintdialog.h \
    UI/magicalobjectwindow.h \
    UI/mainwindow.h \
    UI/modelwindow.h \
    UI/regimentinfodialog.h \
    UI/statsdisplayform.h \
    UI/statsdisplaywidget.h \
    UI/terraininfodisplayform.h \
    UI/terrainwindow.h \
    UI/warholeinfodialog.h \
    Utilities/DiceRoller/DiceRoller.h \
    Utilities/PdfExporter/pdfexporter.h \
    Utilities/QLogger/QLogger.h \
    Utilities/RandomIdGenerator/idgenerator.h \
    defines.h \
    version.h \
    warlibinitializer.h

TRANSLATIONS = warhole_en.ts


FORMS += \
    UI/modelwindow.ui \
    UI/armywindow.ui \
    UI/gamewindow.ui \
    UI/magicalobjectwindow.ui \
    UI/mainwindow.ui \
    UI/gameconfiguratordialog.ui \
    UI/connecttoserverdialog.ui \
    UI/chatwidgetform.ui \
    UI/statsdisplayform.ui \
    UI/getintdialog.ui \
    UI/statsdisplaywidget.ui \
    UI/terrainwindow.ui \
    UI/regimentinfodialog.ui \
    UI/warholeinfodialog.ui \
    UI/terraininfodisplayform.ui \
    UI/backgroundselectiondialog.ui \
    UI/armywindowevolved.ui \
    UI/addregimentdialog.ui

RESOURCES += \
    resources.qrc
