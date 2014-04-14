/*********************************************************************//**
* ChatHistoricItem.cpp
* ChatHistoricItem class
*
* AUTEUR: Alexandre Jumeline
* DATE: 11-04-2014
*************************************************************************/

#include "game/historic/ChatHistoricItem.h"

ChatHistoricItem::ChatHistoricItem() {
	// TODO Auto-generated constructor stub

}

ChatHistoricItem::~ChatHistoricItem() {
	// TODO Auto-generated destructor stub
}

ChatHistoricItem::ChatHistoricItem(ChatHistoricItem & copy) : HistoricAbstractItem(copy)
{
	type = copy.type;
	destinationPlayer = copy.destinationPlayer;
}

QString ChatHistoricItem::getDestinationPlayer() const
{
    return destinationPlayer;
}

ChatType ChatHistoricItem::getType() const
{
    return type;
}

void ChatHistoricItem::setDestinationPlayer(QString destinationPlayer)
{
    this->destinationPlayer = destinationPlayer;
}

void ChatHistoricItem::setType(ChatType type)
{
    this->type = type;
}

// Overloading of << operator
QDataStream & operator << (QDataStream & out, ChatHistoricItem & obj)
{
    out << static_cast<HistoricAbstractItem&>(obj)
        << obj.type
        << obj.destinationPlayer;

    return out;
}

// Overloading of >> operator
QDataStream & operator >> (QDataStream & in, ChatHistoricItem & obj)
{
    int type = 0;

    in >> static_cast<HistoricAbstractItem&>(obj);
    in >> type;

    switch(type)
    {
    case 0:
        type = NORMAL;
        break;
    case 1:
        type = WISPER;
        break;
    }

    in >> obj.destinationPlayer;

    return in;
}


