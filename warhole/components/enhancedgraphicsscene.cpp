#include "enhancedgraphicsscene.h"

#include <QGraphicsItem>
#include <QGraphicsSceneMouseEvent>
#include "components/enhancegraphicsobject.h"

EnhancedGraphicsScene::EnhancedGraphicsScene(QObject *parent) :
    QGraphicsScene(parent)
{
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
    // Get all selected items
    QList<QGraphicsItem *> items = selectedItems();

    for (int i=0; i<items.count(); ++i)
        // Do what you want to do when a mouse move over a selected item.
        dynamic_cast<EnhanceGraphicsObject*>(items[i]->toGraphicsObject())->mouseMoveEvent(mouseEvent);

    QGraphicsScene::mouseMoveEvent(mouseEvent);
}
