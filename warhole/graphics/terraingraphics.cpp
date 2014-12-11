#include "terraingraphics.h"

TerrainGraphics::TerrainGraphics(QGraphicsItem *parent) :
    EnhanceGraphicsObject(parent)
{
    setFlag(ItemIsFocusable);
    setFlag(ItemIsMovable);
    setFlag(ItemIsSelectable);

    rot = false;
    firstRot = true;
    previousRot = 0;
    lock = false;
    setZValue(TERRAIN_Z_VALUE);

    actionRemoveTerrain = new QAction(tr("Retirer"), this);
    connect(actionRemoveTerrain, SIGNAL(triggered()),this, SLOT(removeTerrainRequest()));
    actionLockTerrain = new QAction(tr("Vérouiller"), this);
    connect(actionLockTerrain, SIGNAL(triggered()), this, SLOT(lockTerrainRequest()));
    actionSeeTerrainInfo = new QAction(tr("Voir les infos du décor"), this);
    connect(actionSeeTerrainInfo, SIGNAL(triggered()), this, SLOT(displayTerrainInfo()));
    actionUnlockTerrain = new QAction(tr("Dévérouiller"), this);
    connect(actionUnlockTerrain, SIGNAL(triggered()), this, SLOT(unlockTerrainRequest()));
}

TerrainGraphics::TerrainGraphics(Terrain ter, QGraphicsItem *parent):
    EnhanceGraphicsObject(parent)
{
    t = ter;
    prepareGeometryChange();

    setFlag(ItemIsFocusable);
    setFlag(ItemIsMovable);
    setFlag(ItemIsSelectable);

    rot = false;
    firstRot = true;
    previousRot = 0;
    lock = false;
    setZValue(TERRAIN_Z_VALUE);

    actionRemoveTerrain = new QAction(tr("Retirer"), this);
    connect(actionRemoveTerrain, SIGNAL(triggered()),this, SLOT(removeTerrainRequest()));
    actionLockTerrain = new QAction(tr("Vérouiller"), this);
    connect(actionLockTerrain, SIGNAL(triggered()), this, SLOT(lockTerrainRequest()));
    actionSeeTerrainInfo = new QAction(tr("Voir les infos du décor"), this);
    connect(actionSeeTerrainInfo, SIGNAL(triggered()), this, SLOT(displayTerrainInfo()));
    actionUnlockTerrain = new QAction(tr("Dévérouiller"), this);
    connect(actionUnlockTerrain, SIGNAL(triggered()), this, SLOT(unlockTerrainRequest()));
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

void TerrainGraphics::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    static qreal translation;

    static int cnt = 0;
    if(rot && !lock)
    {
        static int offset = 0;

        if(firstRot)
        {

            if(event->pos().x() < boundingRect().center().x())
            {
                translation = boundingRect().right();
                offset = 180;
            }
            else
            {
                translation = 0;
                offset = 0;
            }
            firstRot = false;
        }

        QPointF originPoint = mapToScene(translation, 0);

        qreal a1 = event->scenePos().x() - originPoint.x();
        qreal a2 = event->scenePos().y() - originPoint.y();
        qreal angle = qAtan2(a2, a1);

        QTransform trans;
        trans.translate(translation,0).rotate(-previousRot).rotate((angle * 180 / 3.14) + offset).translate(-translation,0);
        setTransform(trans, true);
        previousRot = ((angle * 180 / 3.14) + offset);

        if((++cnt)%6 == 0)
        {
            cnt = 1;
            emit terrainMoved(id, pos(), transform(), previousRot);
        }
    }
    else
    {
        if((++cnt)%6 == 0)
        {
            cnt = 1;
            emit terrainMoved(id, pos(), transform(), previousRot);
        }
        QGraphicsItem::mouseMoveEvent(event);
    }
}

void TerrainGraphics::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_R)
    {
        rot = true;
    }
    QGraphicsItem::keyPressEvent(event);
}

void TerrainGraphics::keyReleaseEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_R && !event->isAutoRepeat())
    {
        rot = false;
        firstRot = true;
    }
    QGraphicsItem::keyReleaseEvent(event);
}

void TerrainGraphics::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    // End of movement, send final position
    emit terrainMoved(id, pos(), transform(), previousRot);

    QGraphicsItem::mouseReleaseEvent(event);
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


QString TerrainGraphics::getId() const
{
    return id;
}

void TerrainGraphics::setId(const QString &value)
{
    id = value;
}


bool TerrainGraphics::isLocked() const
{
    return lock;
}

void TerrainGraphics::setLock(bool value)
{
    lock = value;
    updateLock();
}

void TerrainGraphics::updateLock()
{
    if(lock)
    {
        setFlag(ItemIsMovable, false);
        setFlag(ItemIsSelectable, false);
    }
    else
    {
        setFlag(ItemIsMovable);
        setFlag(ItemIsSelectable, false);
    }
}

void TerrainGraphics::contextMenuEvent(QGraphicsSceneContextMenuEvent *event)
{
    QMenu *menu = new QMenu;
    menu->addAction(actionRemoveTerrain);
    if(lock)
        menu->addAction(actionUnlockTerrain);
    else
        menu->addAction(actionLockTerrain);
    menu->addAction(actionSeeTerrainInfo);
    menu->popup(event->screenPos());
}


void TerrainGraphics::removeTerrainRequest()
{
    emit removeTerrainRequest(id);
}

void TerrainGraphics::lockTerrainRequest()
{
    emit lockTerrainRequest(id, true);
}

void TerrainGraphics::unlockTerrainRequest()
{
    emit lockTerrainRequest(id, false);
}

void TerrainGraphics::displayTerrainInfo()
{
}

QDataStream& TerrainGraphics::serializeOut(QDataStream& out)
{
    out << (*this);
    return out;
}
QDataStream& TerrainGraphics::serializeIn(QDataStream& in)
{
    in >> (*this);
    return in;
}

QDataStream& operator<<(QDataStream& out, const TerrainGraphics& obj)
{
    out << obj.id
        << obj.t
        << obj.lock
        << obj.pos()
        << obj.transform()
        << obj.previousRot;

    return out;
}

QDataStream& operator>>(QDataStream& in, TerrainGraphics& obj)
{
    bool l;
    QPointF position;
    QTransform matrix;
    
    in >> obj.id;
    in >> obj.t;
    in >> l;
    
    obj.setLock(l);
    
    in >> position;
    obj.setPos(position);
    
    in >> matrix;
    in >> obj.previousRot;
    obj.setTransform(matrix);
    
    return in;
}

qreal TerrainGraphics::getPreviousRot() const
{
    return previousRot;
}

void TerrainGraphics::setPreviousRot(const qreal &value)
{
    previousRot = value;
}

