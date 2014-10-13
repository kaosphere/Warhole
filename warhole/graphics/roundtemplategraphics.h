#ifndef RoundTemplateGraphics_H
#define RoundTemplateGraphics_H

#include <QGraphicsObject>
#include <QtCore>
#include <QLinearGradient>
#include <QMenu>
#include <QGraphicsSceneContextMenuEvent>
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

    void contextMenuEvent(QGraphicsSceneContextMenuEvent *event);


signals:
    void templateMoved(QString, QPointF);
    void removeTemplateRequest(QString);
    
public slots:
    void removeTemplate();
private:
    int diameter;
    QString id;
    QAction* actionRemoveTemplate;
    
};

#endif // RoundTemplateGraphics_H
