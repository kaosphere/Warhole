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

    virtual void sendObjectMovedSignal() = 0;
    virtual void applyRotation(QPointF center, qreal angle, qreal offset);

    qreal getPreviousRot() const;
    void setPreviousRot(const qreal &value);

    QDataStream& serializeInBase(QDataStream& in);
    QDataStream &serializeOutBase(QDataStream& out) const;

    friend QDataStream& operator<<(QDataStream& out, const EnhancedGraphicsScene& obj);
    friend QDataStream& operator>>(QDataStream& in, EnhancedGraphicsScene& obj);

    virtual bool isUpsideDown();

protected:
    qreal previousRot;

};

#endif // ENHANCEGRAPHICSOBJECT_H
