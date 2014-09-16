#include "fieldlimits.h"

BackGroundItem::BackGroundItem(int width, int hight)
{
    w = width;
    h = hight;
}

QRectF BackGroundItem::boundingRect() const
{
    return QRectF(0,
                  0,
                  w,
                  h);
}

void BackGroundItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QRectF rec = boundingRect();
    QBrush brush(Qt::blue);
    QPen pen(Qt::black,25);

    painter->setPen(pen);
    painter->drawRect(rec);

    pen.setColor(QColor(25,51,0));
    pen.setWidth(10);
    pen.setStyle(Qt::DashDotLine);
    painter->setPen(pen);
    painter->drawLine(0,(h/2)-TWELVE_INCHES,w,(h/2)-TWELVE_INCHES);
    painter->drawLine(0,(h/2)+TWELVE_INCHES,w,(h/2)+TWELVE_INCHES);
}

int BackGroundItem::getW() const
{
    return w;
}

void BackGroundItem::setW(int value)
{
    w = value;
}

int BackGroundItem::getH() const
{
    return h;
}

void BackGroundItem::setH(int value)
{
    h = value;
}



