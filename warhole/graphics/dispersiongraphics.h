#ifndef DISPERSIONGRAPHICS_H
#define DISPERSIONGRAPHICS_H

#include <QGraphicsObject>
#include <QMenu>
#include <QPainter>
#include <QGraphicsSceneMouseEvent>
#include "distances.h"
#include "components/enhancegraphicsobject.h"

class DispersionGraphics : public EnhanceGraphicsObject
{
    Q_OBJECT
public:
    explicit DispersionGraphics(QGraphicsItem *parent = 0);
    DispersionGraphics(QString i, qreal a, QGraphicsItem* parent = 0);

    virtual QRectF boundingRect() const;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    
    QString getId() const;
    void setId(const QString &value);

    int getAngle() const;
    void setAngle(const int &value);

    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);

    QDataStream& serializeOut(QDataStream& out);
    QDataStream& serializeIn(QDataStream& in);

    friend QDataStream& operator<<(QDataStream& out, const DispersionGraphics& obj);
    friend QDataStream& operator>>(QDataStream& in, DispersionGraphics& obj);

    void contextMenuEvent(QGraphicsSceneContextMenuEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
signals:
    void scatterMoved(QString, QPointF);
    void removeScatter(QString);

public slots:
    void removeScatter();

private:
    QString id;
    int angle;
    QAction* actionRemove;
    static const int LENGTH;
    static const int PEN_SIZE;
};

#endif // DISPERSIONGRAPHICS_H
