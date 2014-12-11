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
    
signals:
    
public slots:
    
};

#endif // ENHANCEGRAPHICSOBJECT_H
