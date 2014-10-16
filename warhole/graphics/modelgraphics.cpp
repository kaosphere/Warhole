#include "modelgraphics.h"

ModelGraphics::ModelGraphics(QGraphicsItem* parent):
    QGraphicsItem(parent)
{
}

ModelGraphics::ModelGraphics(int x, int y, int w, int h, QString n, QPixmap* i, QGraphicsItem* parent):
    QGraphicsItem(parent)
{
    modelName = n;
    width = w;
    hight = h;
    image = i;
    posx = x;
    posy = y;
}

ModelGraphics::~ModelGraphics()
{

}

QRectF ModelGraphics::boundingRect() const
{
    return QRectF(posx,posy,width,hight);
}

void ModelGraphics::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    if(!image->isNull())
    {
        painter->drawPixmap(boundingRect().toRect(), *image);
    }
    else
    {
        painter->setBrush(brush);
        painter->setPen(pen);
        painter->drawRect(boundingRect().toRect());
    }
}

QBrush ModelGraphics::getBrush() const
{
    return brush;
}

void ModelGraphics::setBrush(const QBrush &value)
{
    brush = value;
}


QString ModelGraphics::getModelName() const
{
    return modelName;
}

void ModelGraphics::setModelName(const QString &value)
{
    modelName = value;
}

QPen ModelGraphics::getPen() const
{
    return pen;
}

void ModelGraphics::setPen(const QPen &value)
{
    pen = value;
}

void ModelGraphics::setPosXY(qreal x, qreal y)
{
    posx = x;
    posy = y;
    prepareGeometryChange();
}

