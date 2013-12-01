#ifndef TESTGI_H
#define TESTGI_H

#include <QGraphicsItem>
#include <QBrush>
#include <QPainter>
#include <QGraphicsScene>


class testGI : public QGraphicsItem
{
public:
    testGI();
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    int getH() const;
    void setH(int value);

    int getNbRectW() const;
    void setNbRectW(int value);

    int getW() const;
    void setW(int value);
    bool pressed;
    int getNbRectH() const;
    void setNbRectH(int value);

    void setPosition(QPointF pos);

signals:
    
public slots:

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

private:
    int nbRectW;
    int nbRectH;
    int h;
    int w;
};

#endif // TESTGI_H
