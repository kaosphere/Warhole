#include "enhancegraphicsobject.h"

EnhanceGraphicsObject::EnhanceGraphicsObject(QGraphicsItem *parent) :
    QGraphicsObject(parent)
{

}

QDataStream &EnhanceGraphicsObject::serializeInBase(QDataStream &in)
{
    //in >> (*this);
    return in;
}

QDataStream& EnhanceGraphicsObject::serializeOutBase(QDataStream &out) const
{
    //out << (*this);
    return out;
}

QDataStream &operator <<(QDataStream &out, const EnhanceGraphicsObject &obj)
{
   // out << obj.previousRot;

    return out;
}

QDataStream &operator >>(QDataStream &in, EnhanceGraphicsObject &obj)
{
    //in >> obj.previousRot;

    return in;
}


