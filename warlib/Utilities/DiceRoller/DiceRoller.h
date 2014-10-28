#ifndef DICE_ROLLER_H
#define DICE_ROLLER_H

#include "Utilities/QLogger/QLogger.h"

#include <QList>
#include <QtCore>
#include <QObject>
#include <QTranslator>
#include <QPair>
#include <time.h>
#include <stdlib.h>
#include <QTextStream>
#include <QtAlgorithms>

enum Dice { D2 = 2,
            D3 = 3,
            D4 = 4,
            D6 = 6,
            D8 = 8,
            D10 = 10,
            D12 = 12,
            D20 = 20};

class DiceRoller
{
public:
    static void initDiceRoller();
    static int rollSingleDie(Dice die);
    static QList<int> rollDiceInt(Dice die, int nbDice);
    static QString rollDiceString(Dice die, int nbDice);
    static QPair<QPair<int, QString>, QString> computeDispersionDice();

private:
    static int computeDiceOutput(Dice d);
};

#endif // DICE_ROLLER_H
