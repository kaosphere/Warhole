#include "testgi.h"

testGI::testGI()
{
    pressed = false;
    h = 60;
    w = 60;
    nbRectW = 5;
    nbRectH = 2;
    setFlag(ItemIsMovable);
}

QRectF testGI::boundingRect() const
{
    return QRectF(0,
                  0,
                  (nbRectW*w),
                  (nbRectH*h));
}

void testGI::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QRectF rec = boundingRect();
    QBrush brush(Qt::blue);

    painter->fillRect(rec,brush);
    painter->drawRect(rec);
    for(int i=0;i<nbRectH;i++)
    {
        for(int j=0;j<nbRectW;j++)
        {
            painter->drawRect((j*w),(i*h),w,h);
        }
    }
}

void testGI::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    pressed = true;
    update();
    QGraphicsItem::mousePressEvent(event);
}

void testGI::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    pressed = false;
    update();
    QGraphicsItem::mouseReleaseEvent(event);
}

int testGI::getW() const
{
    return w;
}

void testGI::setW(int value)
{
    w = value;
}

int testGI::getNbRectH() const
{
    return nbRectH;
}

int testGI::getNbRectW() const
{
    return nbRectW;
}

void testGI::setNbRectW(int value)
{
    nbRectW = value;
}

void testGI::setNbRectH(int value)
{
    nbRectH = value;
}

int testGI::getH() const
{
    return h;
}

void testGI::setH(int value)
{
    h = value;
}


