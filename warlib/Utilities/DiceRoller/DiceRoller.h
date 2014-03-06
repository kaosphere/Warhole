#ifndef DICE_ROLLER_H
#define DICE_ROLLER_H

#include "Utilities/QLogger/QLogger.h"

#include <QList>
#include <QString>
#include <QPair>
#include <time.h>
#include <stdlib.h>

class DiceRoller
{
public:
    enum Dice { D2 = 0, D3, D4, D6, D8, D10, D12, D20};

    static void initDiceRoller();
    static int rollSingleDie(Dice die);
    static QList<int> rollDiceInt(Dice die, int nbDice);
    static QString rollDiceString(Dice die, int nbDice);
    static QPair<QPair<int, QString>, QString> computeDispersionDice();

private:
    static int computeDiceOutput(Dice d);
};

#endif // DICE_ROLLER_H
