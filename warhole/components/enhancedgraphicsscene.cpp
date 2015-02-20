#include "enhancedgraphicsscene.h"

#include <QGraphicsItem>
#include <QGraphicsSceneMouseEvent>
#include <QDebug>
#include <qmath.h>
#include "components/enhancegraphicsobject.h"

EnhancedGraphicsScene::EnhancedGraphicsScene(QObject *parent) :
    QGraphicsScene(parent)
{
    rubberBandOn = false;
    rot = false;
    firstRot = true;
    clicked = false;
}

void EnhancedGraphicsScene::refreshItemPositionsOnNetwork()
{
    // Get all selected items
    QList<QGraphicsItem *> items = selectedItems();

    for (int i=0; i<items.count(); ++i)
    {
        // Do what you want to do when a mouse move over a selected item.
        EnhanceGraphicsObject* tmp =  dynamic_cast<EnhanceGraphicsObject*>(items[i]->toGraphicsObject());
        if(tmp != 0)
                tmp->sendObjectMovedSignal();
    }
}

void EnhancedGraphicsScene::mouseMoveEvent(QGraphicsSceneMouseEvent * mouseEvent)
{
    static int cnt = 0;
    QPointF mousePosition = mouseEvent->scenePos();
    QGraphicsItem* pItem = itemAt(mousePosition.x(), mousePosition.y(), QTransform());

    if (pItem == 0)
    {
        QGraphicsScene::mouseMoveEvent(mouseEvent);
        return;
    }

    if (pItem->isSelected() == false)
    {
        QGraphicsScene::mouseMoveEvent(mouseEvent);
        return;
    }

    // We want to move the items only if the mouse is clicked and not in rubberband
    if((rubberBandOn == false) && clicked)
    {
        if(rot)
        {
            // we must find the most east point of all selected object as well
            // as the most west point. With this, we determine if we turn around
            // one or the other
            QGraphicsItemGroup *group = createItemGroup(selectedItems());
            QList<QGraphicsItem *> items = selectedItems();

            // Get the bounding rect of the group to determine the rotation

            int offset = 0;
            qreal translation = 0;


            if(firstRot)
            {

                if(mouseEvent->pos().x() < group->boundingRect().center().x())
                {
                    translation = group->boundingRect().right();
                    offset = 180;
                }
                else
                {
                    translation = 0;
                    offset = 0;
                }
                firstRot = false;
            }

            QPointF originPoint(translation, 0);

            qreal a1 = mouseEvent->scenePos().x() - originPoint.x();
            qreal a2 = mouseEvent->scenePos().y() - originPoint.y();
            qreal angle = qAtan2(a2, a1);

            for (int i=0; i<items.count(); ++i)
            {
                EnhanceGraphicsObject* tmp = dynamic_cast<EnhanceGraphicsObject*>(items[i]->toGraphicsObject());
                if(tmp != 0)
                    tmp->applyRotation(originPoint, angle, offset);
            }

            // In case of a rotation, we don't want the graphics items
            // to get the mouse move event, so we return without
            // calling mouse move event of qgraphicsscene
            return;
        }

        if(cnt++ % 6 == 0)
        {
            cnt = 0;
            refreshItemPositionsOnNetwork();
        }
    }

    QGraphicsScene::mouseMoveEvent(mouseEvent);
}

void EnhancedGraphicsScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    clicked = true;
    QPointF mousePosition = event->scenePos();
    QGraphicsItem* pItem = itemAt(mousePosition.x(), mousePosition.y(), QTransform());

    // If no item is under the mouse when clicking, its a rubberband selection
    if (pItem != 0)
    {
        if((pItem->flags() & QGraphicsItem::ItemIsMovable) == 0)
        {
            rubberBandOn = true;
            qDebug() << "rubberband ON";
        }
    }

    QGraphicsScene::mousePressEvent(event);
}

void EnhancedGraphicsScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    rubberBandOn = false;
    clicked = false;

    // Updata selected objects positions on the network
    refreshItemPositionsOnNetwork();

    QGraphicsScene::mouseReleaseEvent(event);
}

void EnhancedGraphicsScene::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_R)
    {
        rot = true;
    }
    QGraphicsScene::keyPressEvent(event);
}

void EnhancedGraphicsScene::keyReleaseEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_R && !event->isAutoRepeat())
    {
        rot = false;
        firstRot = true;
    }
    QGraphicsScene::keyReleaseEvent(event);
}


