#include "enhancedgraphicsscene.h"

#include <QGraphicsItem>
#include <QGraphicsSceneMouseEvent>
#include <QDebug>
#include "components/enhancegraphicsobject.h"

EnhancedGraphicsScene::EnhancedGraphicsScene(QObject *parent) :
    QGraphicsScene(parent)
{
    rubberBandOn = false;
    clicked = false;
}

void EnhancedGraphicsScene::mouseMoveEvent(QGraphicsSceneMouseEvent * mouseEvent)
{
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
        qDebug() << "If iS met bitch!";
        // Get all selected items
        QList<QGraphicsItem *> items = selectedItems();

        for (int i=0; i<items.count(); ++i)
            // Do what you want to do when a mouse move over a selected item.
            dynamic_cast<EnhanceGraphicsObject*>(items[i]->toGraphicsObject())->mouseMoveEvent(mouseEvent);
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
    QGraphicsScene::mouseReleaseEvent(event);
}


