#include "roundtemplategraphics.h"

RoundTemplateGraphics::RoundTemplateGraphics(QGraphicsItem *parent) :
    EnhanceGraphicsObject(parent)
{
    // Default diameter
    diameter = 5;

    initRoundTemplateGraphics();
}

RoundTemplateGraphics::RoundTemplateGraphics(int d, QString i, QGraphicsItem* parent):
    EnhanceGraphicsObject(parent)
{
    diameter = d;
    id = i;

    initRoundTemplateGraphics();
}

void RoundTemplateGraphics::initRoundTemplateGraphics()
{
    setFlag(ItemIsMovable);
    setFlag(ItemIsFocusable);
    setFlag(ItemIsSelectable);

    setZValue(TEMPLATE_Z_VALUE);

    actionRemoveTemplate = new QAction(tr("Retirer"), this);
    connect(actionRemoveTemplate, SIGNAL(triggered()),this, SLOT(removeTemplate()));

    setOpacity(0.7);
}

QRectF RoundTemplateGraphics::boundingRect() const
{
    return QRectF(0,0,diameter * ONE_INCH, diameter * ONE_INCH);
}

void RoundTemplateGraphics::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    // Paint main circle, do this in a path to empty the middle circle
    QPainterPath p = shape();

    QLinearGradient gradient(0, 0, diameter * ONE_INCH, 0);
    gradient.setColorAt(0, QColor::fromRgb(qRgba(221, 209, 92, 0.8)));
    gradient.setColorAt(1, QColor::fromRgb(qRgba(80, 80, 20, 0.8)));

    QBrush brush(gradient);
    QPen pen(QColor(0,20,40),3);

    painter->setBrush(brush);
    painter->setPen(pen);

    painter->drawPath(p);
}

QPainterPath RoundTemplateGraphics::shape() const
{
    QPainterPath p;

    p.addEllipse(boundingRect());
    p.addEllipse(boundingRect().center(), ONE_INCH/4, ONE_INCH/4);

    return p;
}

void RoundTemplateGraphics::contextMenuEvent(QGraphicsSceneContextMenuEvent *event)
{
    QMenu *menu = new QMenu;
    menu->addAction(actionRemoveTemplate);
    menu->popup(event->screenPos());
}


void RoundTemplateGraphics::removeTemplate()
{
    emit removeTemplateRequest(id);
}

QString RoundTemplateGraphics::getId() const
{
    return id;
}

void RoundTemplateGraphics::setId(QString value)
{
    id = value;
}

int RoundTemplateGraphics::getDiameter() const
{
    return diameter;
}

void RoundTemplateGraphics::setDiameter(int value)
{
    diameter = value;
}

QDataStream& RoundTemplateGraphics::serializeOut(QDataStream& out)
{
    out << (*this);
    return out;
}

QDataStream& RoundTemplateGraphics::serializeIn(QDataStream& in)
{
    in >> (*this);
    return in;
}

QDataStream& operator<<(QDataStream& out, const RoundTemplateGraphics& obj)
{
    obj.serializeOutBase(out);
    out << obj.id
        << obj.diameter
        << obj.pos();

    return out;
}

QDataStream& operator>>(QDataStream& in, RoundTemplateGraphics& obj)
{
    QPointF position;

    obj.serializeInBase(in);
    in >> obj.id;
    in >> obj.diameter;
    in >> position;

    obj.setPos(position);

    return in;
}

void RoundTemplateGraphics::sendObjectMovedSignal()
{
    emit templateMoved(id, pos());
}

