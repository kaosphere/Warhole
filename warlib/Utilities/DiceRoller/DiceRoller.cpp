#include "DiceRoller.h"

DiceRoller::DiceRoller()
{
	
}

void DiceRoller::initDiceRoller()
{
	//init random generator
	srand(time(NULL));
}

int DiceRoller::rollSingleDie(Dice die)
{
	return computeDiceOutput(die);
}

QList<int> DiceRoller::rollDiceInt(Dice die, int nbDice)
{
	QList<int> l;
	for(int i = 0; i < nbDice; ++i)
	{
		l.append(computeDiceOutput(die));
	}
	return l;
}


QString DiceRoller::rollDiceString(Dice die, int nbDice)
{
	QList<QString> l;
	for(int i = 0; i < nbDice; ++i)
	{
		l.append(QString::number(computeDiceOutput(die)));
	}
	QString out = "Launched " + QString::number(nbDice) + " dice : ";
	
	return out;
}

int DiceRoller::computeDiceOutput(Dice d)
{
	if(d != Dispersion)
	{
		return rand() % d + 1;
	}
	else
		return 0;
}

QPair<QPair<int, QString>, QString> DiceRoller::computeDispersionDice()
{
	// Dispersion
	QPair<int, QString> disp;
	disp.first = rand() % 360 + 1;
	int hit = rand() % 3 + 1;
	if(hit == 1) disp.second = "hit";
	else disp.second = "miss";
	// Deviation
	QPair<QPair<int, QString>, QString> artillery;
	int dev = rand() % 6 + 1
	if(dev == 6) artillery.second = "Incident de tir";
	else artillery = QString::number(dev * 2);
	
	artillery.first = disp;
	
	return artillery;
}	


