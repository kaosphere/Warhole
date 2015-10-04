#include "lineofsightgraphics.h"

LineOfSightGraphics::LineOfSightGraphics(){}

LineOfSightGraphics::LineOfSightGraphics(int bw, QPoint origin1, QPoint origin2, int l)
{
    baseWidth = bw;
    O1 = origin1;
    O2 = origin2;
    length = l;
}

QRectF LineOfSightGraphics::boundingRect() const
{
    //return QRectF(posx,posy,width,hight);
}

void LineOfSightGraphics::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    // Calculate the X1 and X2 coordinates
}
