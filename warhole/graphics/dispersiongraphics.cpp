#include "dispersiongraphics.h"

const int DispersionGraphics::LENGTH = (4 * ONE_INCH);
const int DispersionGraphics::PEN_SIZE = 20;

DispersionGraphics::DispersionGraphics(QGraphicsItem *parent) :
    EnhanceGraphicsObject(parent)
{
    angle = 0;
    id = "";
    setFlag(ItemIsMovable);
    setFlag(ItemIsFocusable);
    setFlag(ItemIsSelectable);

    setZValue(SCATTER_Z_VALUE);

    actionRemove = new QAction(tr("Retirer"), this);
    connect(actionRemove, SIGNAL(triggered()), this, SLOT(removeScatter()));
}

DispersionGraphics::DispersionGraphics(QString i, qreal a, QGraphicsItem *parent):
    EnhanceGraphicsObject(parent)
{
    angle = a;
    id = i;

    setRotation(angle);

    actionRemove = new QAction(tr("Retirer"), this);
    connect(actionRemove, SIGNAL(triggered()), this, SLOT(removeScatter()));

    setZValue(SCATTER_Z_VALUE);

    setFlag(ItemIsMovable);
    setFlag(ItemIsFocusable);
    setFlag(ItemIsSelectable);
}

QRectF DispersionGraphics::boundingRect() const
{
    return QRectF(-ONE_INCH - PEN_SIZE/2, -PEN_SIZE/2, 2*ONE_INCH + PEN_SIZE, LENGTH + PEN_SIZE);
}

void DispersionGraphics::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QColor myColor = Qt::blue;
    painter->setPen(QPen(myColor, PEN_SIZE, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));

    painter->drawLine(0,0,0,LENGTH);
    painter->drawLine(0,LENGTH, -ONE_INCH, LENGTH - ONE_INCH);
    painter->drawLine(0, LENGTH, ONE_INCH, LENGTH - ONE_INCH);
}

void DispersionGraphics::sendObjectMovedSignal()
{
    emit scatterMoved(id, pos());
}

void DispersionGraphics::contextMenuEvent(QGraphicsSceneContextMenuEvent *event)
{
    QMenu *menu = new QMenu;
    menu->addAction(actionRemove);
    menu->popup(event->screenPos());
}

QDataStream &DispersionGraphics::serializeOut(QDataStream &out)
{
    out << (*this);
    return out;
}

QDataStream &DispersionGraphics::serializeIn(QDataStream &in)
{
    in >> (*this);
    return in;
}

QDataStream& operator<<(QDataStream& out, const DispersionGraphics& obj)
{
    obj.serializeOutBase(out);
    out << obj.id;
    out << obj.angle;
    out << obj.pos();

    return out;
}

QDataStream& operator>>(QDataStream& in, DispersionGraphics& obj)
{
    int angle;
    QPointF pos;

    obj.serializeInBase(in);
    in >> obj.id;
    in >> angle;
    in >> pos;

    obj.setAngle(angle);
    obj.setPos(pos);

    return in;
}

int DispersionGraphics::getAngle() const
{
    return angle;
}

void DispersionGraphics::setAngle(const int &value)
{
    angle = value;
    setRotation((qreal)angle);
}

QString DispersionGraphics::getId() const
{
    return id;
}

void DispersionGraphics::setId(const QString &value)
{
    id = value;
}

void DispersionGraphics::removeScatter()
{
    emit removeScatter(id);
}
