#include "terraingraphics.h"
#include "terraininfodisplayform.h"
#include <QGraphicsProxyWidget>
#include <QDebug>

TerrainGraphics::TerrainGraphics(bool* iv, QGraphicsItem *parent) :
    EnhanceGraphicsObject(parent)
{
    setFlag(ItemIsFocusable);
    setFlag(ItemIsMovable);
    setFlag(ItemIsSelectable);

    rot = false;
    firstRot = true;
    lock = false;
    invertedView = iv;
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

TerrainGraphics::TerrainGraphics(Terrain ter, bool* iv, QGraphicsItem *parent):
    EnhanceGraphicsObject(parent)
{
    t = ter;
    prepareGeometryChange();

    setFlag(ItemIsFocusable);
    setFlag(ItemIsMovable);
    setFlag(ItemIsSelectable);

    rot = false;
    firstRot = true;
    lock = false;
    invertedView = iv;
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
    TerrainInfoDisplayForm* s = new TerrainInfoDisplayForm(t);
    QGraphicsProxyWidget* w = new QGraphicsProxyWidget();
    w->setWidget(s);

    QPointF origin(pos().x() + boundingRect().width(), pos().y());
    infoRect = new QGraphicsRectItem(0,
                                     0,
                                     s->width(),
                                     s->height());

    infoRect->setFlag(ItemIsMovable);
    infoRect->setFlag(ItemIsSelectable);

    w->setParentItem(infoRect);
    w->setPos(infoRect->boundingRect().topLeft());
    w->setOpacity(0.9);
    infoRect->setZValue(REGIMENT_INFO_Z_VALUE);


    connect(s,SIGNAL(destroyed()), this, SLOT(closeInfoRect()));

    scene()->addItem(infoRect);

    QTransform trans;
    if(*invertedView)
    {
        // Display stats according to view side
        trans.rotate(180)
             .translate(-origin.x(), -origin.y());
    }
    else
    {
        trans.translate(origin.x(), origin.y());
    }
    infoRect->setTransform(trans);
}

void TerrainGraphics::closeInfoRect()
{
    scene()->removeItem(infoRect);
    delete infoRect;
    infoRect = NULL;
}

bool *TerrainGraphics::getInvertedView() const
{
    return invertedView;
}

void TerrainGraphics::setInvertedView(bool *value)
{
    invertedView = value;
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
    obj.serializeOutBase(out);
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
    
    obj.serializeInBase(in);
    in >> obj.id;
    in >> obj.t;
    in >> l;
    
    obj.setLock(l);
    
    in >> position;
    obj.setPos(position);
    
    in >> matrix;
    obj.setTransform(matrix);

    in >> obj.previousRot;
    
    return in;
}

void TerrainGraphics::sendObjectMovedSignal()
{
    emit terrainMoved(id, pos(), transform(), previousRot);
}

