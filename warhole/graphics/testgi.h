#ifndef TESTGI_H
#define TESTGI_H

#include <QGraphicsItem>
#include <QBrush>
#include <QPainter>
#include <QGraphicsScene>
#include <QDebug>
#include <QPointF>
#include <QLinearGradient>

#include "Utilities/QLogger/QLogger.h"

class testGI : public QGraphicsItem
{
public:
    testGI();
    virtual ~testGI();
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

    int getDeads() const;
    void setDeads(int value);

signals:

public slots:

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent* event);

private:
    static const QString LOG_ID_TRACE;
    static const QString LOG_ID_INFO;
    static const QString LOG_ID_WARN;
    static const QString LOG_ID_ERR;


    int nbRectW;
    int nbRectH;
    int h;
    int w;
    QPixmap logo;
    QPixmap dead;
    int deads;

    QPointF* points;
};

#endif // TESTGI_H
