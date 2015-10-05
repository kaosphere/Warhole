#include "lineofsightgraphics.h"
#include <QtMath>
#include <QBrush>
#include <QPen>

LineOfSightGraphics::LineOfSightGraphics(QGraphicsItem *parent) :
    QGraphicsItem(parent)
{}

LineOfSightGraphics::LineOfSightGraphics(int bw,
                                         QPointF origin1,
                                         QPointF origin2,
                                         int l,
                                         QGraphicsItem* parent) :
    QGraphicsItem(parent)
{
    baseWidth = bw;
    O1 = origin1;
    O2 = origin2;
    length = l;

    computeXPoints();
}

QRectF LineOfSightGraphics::boundingRect() const
{
    return QRectF(QPointF(-radius + baseWidth/2, -radius + baseWidth/2), QPointF(radius + baseWidth/2, radius + baseWidth/2));
}

QPainterPath LineOfSightGraphics::shape() const
{
    QPainterPath p;

    //p.moveTo(0,(WIDTH/2)*ONE_INCH);
    p.lineTo(X1);
    p.arcTo(QRectF(QPointF(-radius + baseWidth/2, -radius + baseWidth/2),
                   QPointF(radius + baseWidth/2, radius + baseWidth/2)),
            135,
            -90);
    p.lineTo(baseWidth, 0);
    p.closeSubpath();

    return p;
}

void LineOfSightGraphics::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    // Paint main circle, do this in a path to empty the middle circle
    QPainterPath p = shape();

    QBrush brush(QColor(200, 200, 200, 100));
    QPen pen(QColor(0,20,40),3);

    painter->setBrush(brush);
    painter->setPen(pen);

    painter->drawPath(p);
}

void LineOfSightGraphics::computeXPoints()
{
    qreal quarterOfPi = qDegreesToRadians(45.0f);
    // Compute the coordinates of the two X points
    X1.setY(-length * qCos(quarterOfPi));
    X1.setX(-length * qSin(quarterOfPi));
    X2.setX(length * qCos(quarterOfPi) + O2.x());
    X2.setY(length * qCos(quarterOfPi) + O2.y());

    radius = qSqrt((baseWidth * baseWidth / 2)) + length;
}
