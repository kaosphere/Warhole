#include "game/historic/HistoricAbstractItem.h"


HistoricAbstractItem::HistoricAbstractItem()
{
}

HistoricAbstractItem::HistoricAbstractItem(HistoricAbstractItem & copy)
{
	message = copy.message;
	timeStamp = copy.timeStamp;
    source = copy.source;
}

QString HistoricAbstractItem::getMessage() const
{
    return message;
}

QString HistoricAbstractItem::getSource() const
{
    return source;
}

QDate HistoricAbstractItem::getTimeStamp() const
{
    return timeStamp;
}

void HistoricAbstractItem::setMessage(QString message)
{
    this->message = message;
}

void HistoricAbstractItem::setSource(QString source)
{
    this->source = source;
}

void HistoricAbstractItem::setTimeStamp(QDate timeStamp)
{
    this->timeStamp = timeStamp;
}

QDataStream &operator <<(QDataStream & out, const HistoricAbstractItem & obj)
{
    out << obj.message
    	<< obj.timeStamp
    	<< obj.source;

    return out;
}

QDataStream &operator >>(QDataStream & in, HistoricAbstractItem & obj)
{
    in >> obj.message;
    in >> obj.timeStamp;
    in >> obj.source;

    return in;
}

