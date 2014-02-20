#ifndef WARLIB_H
#define WARLIB_H

#include "model/modelabstract.h"
#include "model/modelcavalry.h"
#include "model/modelcharacter.h"
#include "model/modelcharriot.h"
#include "model/modelfactory.h"
#include "model/modelinfantery.h"
#include "model/modelmonster.h"
#include "model/modelwarmachine.h"

#include "army/army.h"

#include "Utilities/QLogger/QLogger.h"

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
