#ifndef ENHANCEDGRAPHICSSCENE_H
#define ENHANCEDGRAPHICSSCENE_H

#include <QGraphicsScene>

class EnhancedGraphicsScene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit EnhancedGraphicsScene(QObject *parent = 0);

protected:
    virtual void mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent);
signals:
    
public slots:
    
};

#endif // ENHANCEDGRAPHICSSCENE_H
