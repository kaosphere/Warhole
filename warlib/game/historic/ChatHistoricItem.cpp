/*********************************************************************//**
* ChatHistoricItem.cpp
* ChatHistoricItem class
*
* AUTEUR: Alexandre Jumeline
* DATE: 11-04-2014
*************************************************************************/

#include "ChatHistoricItem.h"

ChatHistoricItem::ChatHistoricItem() {
	// TODO Auto-generated constructor stub

}

ChatHistoricItem::~ChatHistoricItem() {
	// TODO Auto-generated destructor stub
}

ChatHistoricItem::ChatHistoricItem(ChatHistoricItem & copy)
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



