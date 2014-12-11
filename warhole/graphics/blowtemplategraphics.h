#ifndef BLOWTEMPLATEGRAPHICS_H
#define BLOWTEMPLATEGRAPHICS_H

#include <QGraphicsObject>
#include <QAction>
#include <QPainter>
#include <QGraphicsSceneMouseEvent>
#include <qmath.h>
#include <QKeyEvent>
#include <QMenu>
#include "distances.h"
#include "components/enhancegraphicsobject.h"

class BlowTemplateGraphics : public EnhanceGraphicsObject
{
    Q_OBJECT
public:
    explicit BlowTemplateGraphics(QGraphicsItem *parent = 0);
    BlowTemplateGraphics(QString i, QGraphicsItem *parent = 0);

    virtual QRectF boundingRect() const;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    virtual QPainterPath shape() const;

    QString getId() const;
    void setId(QString value);

    void initRoundTemplateGraphics();
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);

    void contextMenuEvent(QGraphicsSceneContextMenuEvent *event);

    QDataStream &serializeOut(QDataStream& out);
    QDataStream& serializeIn(QDataStream& in);

    friend QDataStream& operator<<(QDataStream& out, const BlowTemplateGraphics& obj);
    friend QDataStream& operator>>(QDataStream& in, BlowTemplateGraphics& obj);
    
    qreal getPreviousRot() const;
    void setPreviousRot(const qreal &value);

signals:
    void templateMoved(QString, QPointF, QTransform, qreal);
    void removeTemplateRequest(QString);

public slots:
    void removeTemplate();

private:
    QString id;
    QAction* actionRemoveTemplate;
    bool rot;
    bool firstRot;
    qreal previousRot;

    static const qreal WIDTH;
    static const qreal LENGTH;
    
};

#endif // BLOWTEMPLATEGRAPHICS_H
