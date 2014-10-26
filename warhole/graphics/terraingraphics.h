#ifndef TERRAINGRAPHICS_H
#define TERRAINGRAPHICS_H

#include <QGraphicsObject>
#include <QPainter>
#include "game/terrain/terrain.h"
#include "distances.h"

class TerrainGraphics : public QGraphicsObject
{
    Q_OBJECT
public:
    explicit TerrainGraphics(QGraphicsItem *parent = 0);
    TerrainGraphics(Terrain ter, QGraphicsItem *parent = 0);
    
    virtual QRectF boundingRect() const;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    Terrain getT() const;
    void setT(const Terrain &value);

    void changeResize(bool r);
signals:
    
public slots:

private:
    Terrain t;
    
};

#endif // TERRAINGRAPHICS_H
