/*********************************************************************//**
* DiceHistoricItem.h
* DiceHistoricItem class
*
* AUTEUR: Alexandre Jumeline
* DATE: 03-04-2014
*************************************************************************/

#ifndef DICEHISTORICITEM_H_
#define DICEHISTORICITEM_H_

#include "HistoricAbstractItem.h"
#include <Utilities/DiceRoller/DiceRoller.h>

//! DiceHistoricItem class
/*!
* Derived class for historic dice items
* DiceHistoricItems hold data of passed dice rolls.
*/
class DiceHistoricItem: public HistoricAbstractItem
{
public:
    //! Constructor.
    /*!
		Default constructor of DiceHistoricItem class
		*/
    DiceHistoricItem();

    //! Copy Constructor.
    /*!
	* Copy constructor of DiceHistoricItem class
	* \param copy Object to be copied.
	*/
    DiceHistoricItem(DiceHistoricItem & copy);
    //! Destructor.
    /*!
	* VIRTUAL : Base destructor of DiceHistoricItem class
	*/
    virtual ~DiceHistoricItem();

    Dice getDiceType() const;
    int getNbDice() const;
    QList<int> getResults() const;
    void setDiceType(Dice diceType);
    void setNbDice(int nbDice);
    void setResults(QList<int> results);

private:
	//! diceType
	/*!
	* Type of the dice rolled : D2, D3, ... , D20
	*/
	Dice diceType;

	//! nbDice
	/*!
	* Number of dice rolled
	*/
	int nbDice;

	//! results
	/*!
	* List of results obtained with the dice rolled.
	*/
	QList<int> results;

};

#endif /* DICEHISTORICITEM_H_ */
