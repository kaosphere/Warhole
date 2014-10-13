#ifndef RoundTemplateGraphics_H
#define RoundTemplateGraphics_H

#include <QGraphicsObject>
#include <QtCore>
#include <QLinearGradient>
#include <QPainter>
#include "distances.h"

class RoundTemplateGraphics : public QGraphicsObject
{
    Q_OBJECT
public:
    explicit RoundTemplateGraphics(QGraphicsItem *parent = 0);
    RoundTemplateGraphics(int d, QString i, QGraphicsItem *parent = 0);
    
    int getDiameter() const;
    void setDiameter(int value);

    virtual QRectF boundingRect() const;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    virtual QPainterPath shape() const;

    QString getId() const;
    void setId(QString value);

    void initRoundTemplateGraphics();
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
signals:
    void templateMoved(QString, QPointF);
    
public slots:

private:
    int diameter;
    QString id;
    
};

#endif // RoundTemplateGraphics_H
