#ifndef DICE_ROLLER_H
#define DICE_ROLLER_H

#include "Utilities/QLogger/QLogger.h"

#include <QList>
#include <QString>
#include <QPair>
#include <Time>
#include <stdlib.h>

class DiceRoller
{
public:
    enum Dice { D2 = 0, D3, D4, D6, D8, D10, D12, D20};
    
    // Pure virtual destructor to prevent the class from being instanciated
    virtual ~DiceRoller() = 0;
    static void initDiceRoller();
    static int rollSingleDie(Dice die);
    static QList<int> rollDiceInt(Dice die, int nbDice);
    static QString rollDiceString(Dice die, int nbDice);
    static QPair<QPair<int, QString>, QString> computeDispertionDice();

private:
	int computeDiceOutput(Dice d);
};

#endif // DICE_ROLLER_H
