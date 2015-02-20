#include "enhancegraphicsobject.h"

EnhanceGraphicsObject::EnhanceGraphicsObject(QGraphicsItem *parent) :
    QGraphicsObject(parent)
{
    previousRot = 0;
}

void EnhanceGraphicsObject::applyRotation(QPointF center, qreal angle, qreal offset)
{
    QPointF relativeCenter = mapFromItem(this, center);

    QTransform trans;
    trans.translate(relativeCenter.x(),relativeCenter.y())
            .rotate(-previousRot)
            .rotate((angle * 180 / 3.14) + offset)
            .translate(-relativeCenter.x(),-relativeCenter.y());

    setTransform(trans, true);

    previousRot = ((angle * 180 / 3.14) + offset);
}

qreal EnhanceGraphicsObject::getPreviousRot() const
{
    return previousRot;
}

void EnhanceGraphicsObject::setPreviousRot(const qreal &value)
{
    previousRot = value;
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


bool EnhanceGraphicsObject::isUpsideDown()
{
}

