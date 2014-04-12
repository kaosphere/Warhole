/*********************************************************************//**
* ChatHistoricItem.h
* ChatHistoricItem class
*
* AUTEUR: Alexandre Jumeline
* DATE: 11-04-2014
*************************************************************************/
#ifndef CHATHISTORICITEM_H_
#define CHATHISTORICITEM_H_

#include "HistoricAbstractItem.h"

enum ChatType{NORMAL, WISPER};

//! ChatHistoricItem class
/*!
* Derived class for historic chat items
* DiceHistoricItems hold data of passed chats.
*/
class ChatHistoricItem: public HistoricAbstractItem {
public:
	//! Constructor.
	/*!
	 *Default constructor of ChatHistoricItem class
	 */
	ChatHistoricItem();

	//! Copy Constructor.
	/*!
	* Copy constructor of ChatHistoricItem class
	* \param copy Object to be copied.
	*/
	ChatHistoricItem(ChatHistoricItem & copy);

	//! Destructor.
	/*!
	* VIRTUAL : Base destructor of ChatHistoricItem class
	*/
	virtual ~ChatHistoricItem();
    QString getDestinationPlayer() const;
    ChatType getType() const;
    void setDestinationPlayer(QString destinationPlayer);
    void setType(ChatType type);

    //! operator <<
	/*!
	* FRIEND : operator << of QDataStream Class in order to serialize ChatHistoricItem data.
	*/
    friend QDataStream & operator << (QDataStream &, ChatHistoricItem &);

	//! operator <<
	/*!
	* FRIEND : operator >> of QDataStream Class in order to serialize ChatHistoricItem data.
	*/
	friend QDataStream & operator >> (QDataStream &, ChatHistoricItem &);


private:
    //! type.
	/*!
	* Type of the communication
	*/
	ChatType type;

	//! destinationPlayer.
	/*!
	* Player to whom the message is destined
	*/
	QString destinationPlayer;
};

#endif /* CHATHISTORICITEM_H_ */
