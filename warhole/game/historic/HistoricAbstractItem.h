/*********************************************************************//**
* HistoricAbstractItem.h
* HistoricAbstractItem class
*
* AUTEUR: Alexandre Jumeline
* DATE: 03-04-2014
*************************************************************************/

#ifndef HISTORICABSTRACTITEM_H
#define HISTORICABSTRACTITEM_H

#include <QObject>
#include <QtCore>
#include <QtWidgets>
#include <QDate>
#include <iostream>

#include "defines.h"

//! HistoricAbstractItem class
/*!
* Base class for historic items
* Historic items are objects that represents an event that occurred
* during the game. This event can be a dice roll or a chat message.
* Everything is kept in a list that permits to keep track of all the
* event of a game when the game is saved. This class is pure virtual.
*/
class HistoricAbstractItem
{
public:
	//! Constructor.
	/*!
	Default constructor of HistoricAbstractItem class
	*/
	HistoricAbstractItem();

	//! Copy Constructor.
	/*!
	* Copy constructor of HistoricAbstractItem class
	* \param copy Object to be copied.
	*/
	HistoricAbstractItem(HistoricAbstractItem& copy);

	//! Destructor.
	/*!
	* VIRTUAL : Base destructor of ModelAbstract class
	*/
    virtual ~HistoricAbstractItem() = 0;

    //! operator <<
	/*!
	* FRIEND : operator << of QDataStream Class in order to serialize HistoricAbstractItem data.
	*/
    friend QDataStream & operator << (QDataStream &, const HistoricAbstractItem &);

    //! operator <<
	/*!
	* FRIEND : operator >> of QDataStream Class in order to serialize HistoricAbstractItem data.
	*/
    friend QDataStream & operator >> (QDataStream &, HistoricAbstractItem &);

    QString getMessage() const;
    QString getSource() const;
    QDate getTimeStamp() const;
    void setMessage(QString message);
    void setSource(QString source);
    void setTimeStamp(QDate timeStamp);

private:
    //! message
	/*!
	* String containing message to be displayed in the historic viewing widget
	* (chat, server, ...)
	*/
    QString message;

    //! timeStamp
	/*!
	* Time at which the historicItem has been created.
	*/
    QDate timeStamp;

    //! source
	/*!
	* Source that created the historicItem (player or server).
	*/
    QString source;

};

#endif
