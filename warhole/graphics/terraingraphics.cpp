#include "terraingraphics.h"

TerrainGraphics::TerrainGraphics(QGraphicsItem *parent) :
    QGraphicsObject(parent)
{
}

TerrainGraphics::TerrainGraphics(Terrain ter, QGraphicsItem *parent):
    QGraphicsObject(parent)
{
    t = ter;
    prepareGeometryChange();
}

QRectF TerrainGraphics::boundingRect() const
{
    if(t.getResize())
        return QRectF(0,0, t.getWidth()*ONE_INCH, t.getHeigth()*ONE_INCH);
    else
        return QRectF(0,0, t.getTerrainImage().width(), t.getTerrainImage().height());
}

void TerrainGraphics::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->drawPixmap(boundingRect().toRect(), t.getTerrainImage());
}

Terrain TerrainGraphics::getT() const
{
    return t;
}

void TerrainGraphics::setT(const Terrain &value)
{
    t = value;
    prepareGeometryChange();
}

void TerrainGraphics::changeResize(bool r)
{
    t.setResize(r);
    prepareGeometryChange();
}
