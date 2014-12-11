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
    virtual void mousePressEvent(QGraphicsSceneMouseEvent *event);
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
signals:
    
public slots:

private:
    bool rubberBandOn;
    bool clicked;
};

#endif // ENHANCEDGRAPHICSSCENE_H
