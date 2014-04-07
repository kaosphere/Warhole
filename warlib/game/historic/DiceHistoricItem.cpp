/*
 * DiceHistoricItem.cpp
 *
 *  Created on: 2014-04-07
 *      Author: jumelina
 */

#include "DiceHistoricItem.h"

DiceHistoricItem::DiceHistoricItem() : HistoricAbstractItem()
{
	// TODO Auto-generated constructor stub

}

DiceHistoricItem::DiceHistoricItem(DiceHistoricItem& copy) : HistoricAbstractItem(copy)
{

}

DiceHistoricItem::~DiceHistoricItem() {
	// TODO Auto-generated destructor stub
}

Dice DiceHistoricItem::getDiceType() const
{
    return diceType;
}

int DiceHistoricItem::getNbDice() const
{
    return nbDice;
}

QList<int> DiceHistoricItem::getResults() const
{
    return results;
}

void DiceHistoricItem::setDiceType(Dice diceType)
{
    this->diceType = diceType;
}

void DiceHistoricItem::setNbDice(int nbDice)
{
    this->nbDice = nbDice;
}

void DiceHistoricItem::setResults(QList<int> results)
{
    this->results = results;
}



