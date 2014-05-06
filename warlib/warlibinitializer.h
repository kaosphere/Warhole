#ifndef WARLIB_H
#define WARLIB_H

#include "game/model/modelabstract.h"
#include "game/model/modelcavalry.h"
#include "game/model/modelcharacter.h"
#include "game/model/modelcharriot.h"
#include "game/model/modelfactory.h"
#include "game/model/modelinfantery.h"
#include "game/model/modelmonster.h"
#include "game/model/modelwarmachine.h"

#include "game/army/army.h"

#include "Utilities/QLogger/QLogger.h"
#include "Utilities/DiceRoller/DiceRoller.h"
#include "Utilities/PdfExporter/pdfexporter.h"

#include "defines.h"

class WarlibInit
{
    
public:
    WarlibInit();

    static void initWarlib();

private:
    static void initModelSerialization();
    static void initModelFactory();
};

#endif // WARLIB_H
