#ifndef RoundTemplateGraphics_H
#define RoundTemplateGraphics_H

#include <QGraphicsObject>
#include <QtCore>
#include <QLinearGradient>
#include <QMenu>
#include <QGraphicsSceneContextMenuEvent>
#include <QPainter>
#include "distances.h"
#include "components/enhancegraphicsobject.h"

class RoundTemplateGraphics : public EnhanceGraphicsObject
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

    void contextMenuEvent(QGraphicsSceneContextMenuEvent *event);
    
    QDataStream& serializeOut(QDataStream& out);
    QDataStream& serializeIn(QDataStream& in);

    friend QDataStream& operator<<(QDataStream& out, const RoundTemplateGraphics& obj);
    friend QDataStream& operator>>(QDataStream& in, RoundTemplateGraphics& obj);

    virtual void sendObjectMovedSignal();

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
