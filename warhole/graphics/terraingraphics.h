#ifndef TERRAINGRAPHICS_H
#define TERRAINGRAPHICS_H

#include <QGraphicsObject>
#include <QPainter>
#include <QGraphicsSceneMouseEvent>
#include <QKeyEvent>
#include <QAction>
#include <QMenu>
#include "game/terrain/terrain.h"
#include "distances.h"
#include "components/enhancegraphicsobject.h"
#include <QGraphicsRectItem>

class TerrainGraphics : public EnhanceGraphicsObject
{
    Q_OBJECT
public:
    explicit TerrainGraphics(bool *iv, QGraphicsItem *parent = 0);
    TerrainGraphics(Terrain ter, bool *iv, QGraphicsItem *parent = 0);
    
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

    void contextMenuEvent(QGraphicsSceneContextMenuEvent *event);
    
    QDataStream& serializeOut(QDataStream& out);
    QDataStream& serializeIn(QDataStream& in);
    
    friend QDataStream& operator<<(QDataStream& out, const TerrainGraphics& obj);
    friend QDataStream& operator>>(QDataStream& in, TerrainGraphics& obj);

    virtual void sendObjectMovedSignal();

    bool *getInvertedView() const;
    void setInvertedView(bool *value);

protected:

signals:
    void terrainMoved(QString, QPointF, QTransform, qreal);
    void removeTerrainRequest(QString);
    void lockTerrainRequest(QString, bool);
    
public slots:
    void removeTerrainRequest();
    void lockTerrainRequest();
    void unlockTerrainRequest();
    void displayTerrainInfo();
    void closeInfoRect();

private:
    Terrain t;
    QString id;

    QGraphicsRectItem* infoRect;

    bool rot;
    bool firstRot;

    bool lock;
    bool* invertedView;

    QAction* actionRemoveTerrain;
    QAction* actionLockTerrain;
    QAction* actionUnlockTerrain;
    QAction* actionSeeTerrainInfo;
};

#endif // TERRAINGRAPHICS_H
