#ifndef BACKGROUND_H
#define BACKGROUND_H

#include <QGraphicsItem>
#include <QBrush>
#include <QPainter>

#include "distances.h"

class BackGroundItem : public QGraphicsItem
{
public:
    BackGroundItem(int width, int hight);
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    int getH() const;
    void setH(int value);

    int getW() const;
    void setW(int value);

signals:

public slots:

protected:

private:
    int h;
    int w;
};

#endif // TESTGI_H
