#ifndef LINEOFSIGHTGRAPHICS_H
#define LINEOFSIGHTGRAPHICS_H

#include <QGraphicsItem>
#include <QPointF>
#include <QPainterPath>
#include <QPainter>

//////////////////////////////////////////////////////////////////////////////
/// \brief The LineOfSightGraphics class
///
///  This is the graphical object used to draw a regiment's line of sight.
///  Here is how it works
///
/// X1 +      |                             |      + X2
///     \     |                             |     /
///      \    |                             |    /
///       \45¤|             LOS             |45¤/
///     l  \  |                             |  / l
///         \ |                             | /
///          \|         <-length->          |/
///        O1 +-----------------------------+ O2
///           |     |     |     |     |     |
///           |     |     |     |     |     |
///           |-----|-----|-----|-----|-----|
///           |     |     |     |     |     |
///           |     |     |     |     |     |
///           |-----|-----|-----|-----|-----|
///           |     |     |     |     |     |
///           |     |     |     |     |     |
///           |-----|-----|-----|-----|-----|
///
///  Parameters are L, O1, O2 and l
///  They are used to find the position of X1(x1,y1) and X2(x2,y2)
///  relatively to the origin O1 which is also the origin of the regiment.
///
///  x1 = -l*sin(45)          x2 = l*sin(45) + xO2
///  y1 = -l*cos(45)           y2 = l*cos(45) + yO2
///
//////////////////////////////////////////////////////////////////////////////


class LineOfSightGraphics : public QGraphicsItem
{
public:
    LineOfSightGraphics(QGraphicsItem* parent = 0);
    LineOfSightGraphics(int bw,
                        QPointF origin1,
                        QPointF origin2,
                        int l,
                        QGraphicsItem *parent = 0);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QRectF boundingRect() const;
    QPainterPath shape() const;

    void computeXPoints();

private:
    int baseWidth;
    QPointF O1;
    QPointF O2;
    int length;

    QPointF X1;
    QPointF X2;

    qreal radius;
};

#endif // LINEOFSIGHTGRAPHICS_H
