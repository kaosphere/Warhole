#include "RoundTemplateGraphics.h"

RoundTemplateGraphics::RoundTemplateGraphics(QGraphicsItem *parent) :
    QGraphicsObject(parent)
{
    // Default diameter
    diameter = 5;

    initRoundTemplateGraphics();
}

RoundTemplateGraphics::RoundTemplateGraphics(int d, QString i, QGraphicsItem* parent):
    QGraphicsObject(parent)
{
    diameter = d;
    id = i;

    initRoundTemplateGraphics();
}

void RoundTemplateGraphics::initRoundTemplateGraphics()
{
    setFlag(ItemIsMovable);
    setFlag(ItemIsSelectable);
    setFlag(ItemIsFocusable);

    setOpacity(0.7);
    setZValue(1);
}

QRectF RoundTemplateGraphics::boundingRect() const
{
    return QRectF(0,0,diameter * ONE_INCH, diameter * ONE_INCH);
}

void RoundTemplateGraphics::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    // Paint main circle, do this in a path to empty the middle circle
    QPainterPath p;

    p.addEllipse(boundingRect());
    p.addEllipse(boundingRect().center(), ONE_INCH/4, ONE_INCH/4);

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

void RoundTemplateGraphics::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    static int cnt = 0;
    if(++cnt % 6 == 0)
    {
        emit templateMoved(id, pos());
    }
    QGraphicsItem::mouseMoveEvent(event);
}

void RoundTemplateGraphics::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    // Finalize movement
    emit templateMoved(id, pos());
    QGraphicsItem::mouseReleaseEvent(event);
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
