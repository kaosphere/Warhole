#include "DiceRoller.h"

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
	QStringList l;
	for(int i = 0; i < nbDice; ++i)
	{
		l << QString::number(computeDiceOutput(die));
	}
	QString str;
	QTextStream info(&str);
	info << "Launched " << QString::number(nbDice) << " dice : ";
	for (int i = 0; i < l.size(); ++i)
          info << l.at(i).toLocal8Bit().constData() << ", ";
    out << endl;
	return str;
}

int DiceRoller::computeDiceOutput(Dice d)
{
    return rand() % d + 1;
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
    int dev = rand() % 6 + 1;
	if(dev == 6) artillery.second = "Incident de tir";
    else artillery.second = QString::number(dev * 2);
	
	artillery.first = disp;
	
	return artillery;
}	


