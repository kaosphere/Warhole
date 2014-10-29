#include "blowtemplategraphics.h"

const qreal BlowTemplateGraphics::WIDTH = 2.5;
const qreal BlowTemplateGraphics::LENGTH = 8.5;

BlowTemplateGraphics::BlowTemplateGraphics(QGraphicsItem *parent) :
    QGraphicsObject(parent)
{
    initRoundTemplateGraphics();
}

BlowTemplateGraphics::BlowTemplateGraphics(QString i, QGraphicsItem *parent)
{
    initRoundTemplateGraphics();
}

void BlowTemplateGraphics::initRoundTemplateGraphics()
{
    id = "";

    actionRemoveTemplate = new QAction(tr("Retirer"), this);
    connect(actionRemoveTemplate, SIGNAL(triggered()),this, SLOT(actionRemoveTemplateRequest()));

    rot = false;
    firstRot = true;

    setFlag(ItemIsMovable);
    setFlag(ItemIsFocusable);

    setOpacity(0.7);
    setZValue(1);
}

QRectF BlowTemplateGraphics::boundingRect() const
{
    return QRectF(0,0,LENGTH * ONE_INCH, WIDTH * ONE_INCH);
}

QPainterPath BlowTemplateGraphics::shape() const
{
    QPainterPath p;

    p.moveTo(0,(WIDTH/2)*ONE_INCH);
    p.lineTo((LENGTH - WIDTH/2)*ONE_INCH, WIDTH * ONE_INCH);
    p.arcTo(QRectF((LENGTH - WIDTH)*ONE_INCH, 0, WIDTH*ONE_INCH, WIDTH*ONE_INCH), 270, 180);
    p.lineTo(0,(WIDTH/2)*ONE_INCH);

    return p;
}

void BlowTemplateGraphics::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    // Paint main circle, do this in a path to empty the middle circle
    QPainterPath p = shape();

    QLinearGradient gradient(0, 0, 0, WIDTH * ONE_INCH);
    gradient.setColorAt(0, QColor::fromRgba(qRgba(221, 209, 92, 0.8)));
    gradient.setColorAt(1, QColor::fromRgba(qRgba(80, 80, 20, 0.8)));

    QBrush brush(gradient);
    QPen pen(QColor(0,20,40),3);

    painter->setBrush(brush);
    painter->setPen(pen);

    painter->drawPath(p);
}

void BlowTemplateGraphics::setId(QString value)
{
}

void BlowTemplateGraphics::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsItem::mouseMoveEvent(event);
}

void BlowTemplateGraphics::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsItem::mouseReleaseEvent(event);
}

void BlowTemplateGraphics::contextMenuEvent(QGraphicsSceneContextMenuEvent *event)
{
}

QDataStream &BlowTemplateGraphics::serializeOut(QDataStream &out)
{
    out << (*this);
    return out;
}

QDataStream &BlowTemplateGraphics::serializeIn(QDataStream &in)
{
    in >> (*this);
    return in;
}

QDataStream &operator <<(QDataStream &out, const BlowTemplateGraphics &obj)
{
}

QDataStream &operator >>(QDataStream &in, BlowTemplateGraphics &obj)
{
}

QString BlowTemplateGraphics::getId() const
{
}


void BlowTemplateGraphics::removeTemplate()
{
}
