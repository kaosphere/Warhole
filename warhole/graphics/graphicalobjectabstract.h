#ifndef GRAPHICALOBJECTABSTRACT_H
#define GRAPHICALOBJECTABSTRACT_H

#include <QGraphicsObject>
#include <QDataStream>

class GraphicalObjectAbstract : public QGraphicsObject
{
    Q_OBJECT
public:
    explicit GraphicalObjectAbstract(QGraphicsItem *parent = 0);

    virtual QDataStream& serializeIn(QDataStream& in) = 0;
    virtual QDataStream& serializeOut(QDataStream& out) = 0;
    
signals:
    
public slots:
    
};

#endif // GRAPHICALOBJECTABSTRACT_H
