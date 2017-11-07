/*
 * DiceHistoricItem.cpp
 *
 *  Created on: 2014-04-07
 *      Author: jumelina
 */

#include "game/historic/DiceHistoricItem.h"

DiceHistoricItem::DiceHistoricItem() : HistoricAbstractItem()
{
	// TODO Auto-generated constructor stub

}

DiceHistoricItem::DiceHistoricItem(DiceHistoricItem& copy) : HistoricAbstractItem(copy)
{
	diceType = copy.diceType;
	nbDice = copy.nbDice;
	results = copy.results;
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


// Overloading of << operator
QDataStream & operator << (QDataStream & out, DiceHistoricItem & obj)
{
    out << static_cast<HistoricAbstractItem&>(obj)
        << obj.diceType
        << obj.nbDice
        << obj.results.size();

    for(int i = 0; i<obj.results.size(); ++i)
    {
    	out << obj.results[i];
    }

    return out;
}

// Overloading of >> operator
QDataStream & operator >> (QDataStream & in, DiceHistoricItem & obj)
{
    int size = 0;
    int type = 0;

    in >> static_cast<HistoricAbstractItem&>(obj);
    in >> type;
    switch(type)
    {
    case 0:
        obj.diceType = D2;
        break;
    case 1:
        obj.diceType = D3;
        break;
    case 2:
        obj.diceType = D4;
        break;
    case 3:
        obj.diceType = D6;
        break;
    case 4:
        obj.diceType = D8;
        break;
    case 5:
        obj.diceType = D10;
        break;
    case 6:
        obj.diceType = D12;
        break;
    case 7:
        obj.diceType = D20;
        break;
    }

    in >> obj.nbDice;
    in >> size;

    for(int i = 0; i<size; ++i)
    {
    	int res = 0;
    	in >> res;
    	obj.results.append(res);
    }

    return in;
}
