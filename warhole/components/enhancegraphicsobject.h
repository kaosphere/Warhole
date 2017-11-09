#ifndef ENHANCEGRAPHICSOBJECT_H
#define ENHANCEGRAPHICSOBJECT_H

#include <QGraphicsObject>
#include "enhancedgraphicsscene.h"

class EnhanceGraphicsObject : public QGraphicsObject
{
    Q_OBJECT
    friend class EnhancedGraphicsScene;
public:
    explicit EnhanceGraphicsObject(QGraphicsItem *parent = 0);
    virtual ~EnhanceGraphicsObject();

    virtual void sendObjectMovedSignal() = 0;

    QDataStream& serializeInBase(QDataStream& in);
    QDataStream &serializeOutBase(QDataStream& out) const;

    friend QDataStream& operator<<(QDataStream& out, const EnhancedGraphicsScene& obj);
    friend QDataStream& operator>>(QDataStream& in, EnhancedGraphicsScene& obj);

protected:
    qreal previousRot;
};

#endif // ENHANCEGRAPHICSOBJECT_H
