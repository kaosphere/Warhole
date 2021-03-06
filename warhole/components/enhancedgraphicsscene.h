#ifndef ENHANCEDGRAPHICSSCENE_H
#define ENHANCEDGRAPHICSSCENE_H

#include <QGraphicsScene>
#include <QKeyEvent>
#include "QPointF"
#include "Utilities/QLogger/QLogger.h"

class EnhancedGraphicsScene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit EnhancedGraphicsScene(QObject *parent = 0);
    virtual ~EnhancedGraphicsScene();

protected:
    void refreshItemPositionsOnNetwork();
    virtual void mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent);
    virtual void mousePressEvent(QGraphicsSceneMouseEvent *event);
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    virtual void keyPressEvent(QKeyEvent *event);
    virtual void keyReleaseEvent(QKeyEvent *event);
    QPointF findRotationPivot(QList<QGraphicsItem*>& list, bool right);

signals:
    
public slots:

private:
    static const QString LOG_ID_TRACE;
    static const QString LOG_ID_INFO;
    static const QString LOG_ID_WARN;
    static const QString LOG_ID_ERR;

    bool rubberBandOn;
    bool clicked;
    bool rot;
    bool firstRot;

    int offset;
    qreal previousAngle;
    qreal translation0;
    qreal previousRot;
    QPointF originPoint;
};

#endif // ENHANCEDGRAPHICSSCENE_H
