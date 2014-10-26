#ifndef TERRAINGRAPHICS_H
#define TERRAINGRAPHICS_H

#include <QGraphicsObject>
#include <QPainter>
#include <QGraphicsSceneMouseEvent>
#include <QKeyEvent>
#include <QAction>
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
    QString getId() const;
    void setId(const QString &value);

    bool isLocked() const;
    void setLock(bool value);

    void updateLock();

protected:
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

signals:
    void terrainMoved(QString, QPointF, QTransform);
    void removeTerrainRequest(QString);
    void lockTerrainRequest(QString);
    
public slots:
    void removeTerrainRequest();
    void lockTerrainRequest();
    void displayTerrainInfo();

private:
    Terrain t;
    QString id;

    bool rot;
    bool firstRot;

    bool lock;

    QAction* actionRemoveTerrain;
    QAction* actionLockTerrain;
    QAction* actionSeeTerrainInfo;
};

#endif // TERRAINGRAPHICS_H
