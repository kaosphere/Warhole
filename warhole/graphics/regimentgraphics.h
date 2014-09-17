#ifndef REGIMENTGRAPHICS_H
#define REGIMENTGRAPHICS_H

#include <QGraphicsItem>

class RegimentGraphics : public QGraphicsItem
{
public:
    RegimentGraphics();
    virtual ~RegimentGraphics();

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
};

#endif // REGIMENTGRAPHICS_H
