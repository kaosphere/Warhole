#include "enhancedgraphicsscene.h"

#include <QGraphicsItem>
#include <QGraphicsSceneMouseEvent>
#include <QDebug>
#include <qmath.h>
#include "components/enhancegraphicsobject.h"

using namespace QLogger;

const QString EnhancedGraphicsScene::LOG_ID_INFO = "EnhancedGraphicsScene_info";
const QString EnhancedGraphicsScene::LOG_ID_TRACE = "EnhancedGraphicsScene_trace";
const QString EnhancedGraphicsScene::LOG_ID_WARN = "EnhancedGraphicsScene_warm";
const QString EnhancedGraphicsScene::LOG_ID_ERR = "EnhancedGraphicsScene_err";

EnhancedGraphicsScene::EnhancedGraphicsScene(QObject *parent) :
    QGraphicsScene(parent)
{
    QLoggerManager *manager = QLoggerManager::getInstance();
    manager->addDestination("./logs/lastrun.log", QStringList(LOG_ID_TRACE), QLogger::TraceLevel);
    manager->addDestination("./logs/lastrun.log", QStringList(LOG_ID_INFO), QLogger::InfoLevel);
    manager->addDestination("./logs/lastrun.log", QStringList(LOG_ID_ERR), QLogger::ErrorLevel);
    manager->addDestination("./logs/lastrun.log", QStringList(LOG_ID_WARN), QLogger::WarnLevel);

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
        if(!rot && !selectedItems().isEmpty())
        {
            QGraphicsScene::mouseMoveEvent(mouseEvent);
            return;
        }
    }
    else if (pItem->isSelected() == false && !rot && !selectedItems().isEmpty())
    {
        QGraphicsScene::mouseMoveEvent(mouseEvent);
        return;
    }

    // We want to move the items only if the mouse is clicked and not in rubberband
    if((rubberBandOn == false) && clicked)
    {
        if(rot)
        {
            QLog_Info(LOG_ID_INFO, "entering rotation code");
            // we must find the most east point of all selected object as well
            // as the most west point. With this, we determine if we turn around
            // one or the other
            QList<QGraphicsItem*> selectionList = selectedItems();
            QGraphicsItemGroup *group = createItemGroup(selectionList);

            // Get the bounding rect of the group to determine the rotation
            if(firstRot)
            {
                // Calculate X coordinate of the center of the top segment, we need to separate cases if there is only
                // one selected object, and to use this object's bounding rect. Otherwise, the bounding rect of the group
                // won't fit the object
                qreal center = 0;
                if(selectionList.size() == 1)
                {
                    center = (selectionList.first()->mapToScene(0,0).x() + selectionList.first()->mapToScene(selectionList.first()->boundingRect().topRight()).x()) / 2;
                }
                else
                    center = group->boundingRect().center().x();

                if(mouseEvent->scenePos().x() < center)
                {
                    qDebug() << "left";
                    qDebug() << "Mouse x: " << mouseEvent->scenePos().x() << ", group center : " << center;
                    originPoint = findRotationPivot(selectionList, false);
                    previousRot = 0;
                }
                else
                {
                    qDebug() << "right";
                    qDebug() << "Mouse x: " << mouseEvent->scenePos().x() << ", group center : " << center;
                    originPoint = findRotationPivot(selectionList, true);
                    previousRot = 0;
                }

                // Check the rotation offset of the position of the mouse
                qreal a1 = mouseEvent->scenePos().x() - originPoint.x();
                qreal a2 = mouseEvent->scenePos().y() - originPoint.y();
                previousAngle = qAtan2(a2, a1);

                firstRot = false;
            }

            qDebug() << "Origin point :  " << originPoint;
            qDebug() << "Mouse point :  " << mouseEvent->scenePos();

            qreal a1 = mouseEvent->scenePos().x() - originPoint.x();
            qreal a2 = mouseEvent->scenePos().y() - originPoint.y();
            qreal angle = qAtan2(a2, a1);

            qDebug() << "Previous angle : " << previousAngle;
            qDebug() << "a1 : " << a1 << " ; a2 : " << a2;
            qDebug() << "Angle : " << angle;
            qDebug() << "Rotation : " << angle - previousAngle;

            QTransform trans;
            trans.translate(originPoint.x(), originPoint.y())
                    .rotate(-previousRot)
                    .rotate(( (angle - previousAngle) * 180 / 3.14))
                    .translate(-originPoint.x(), -originPoint.y());

            previousRot = ((angle - previousAngle) * 180 / 3.14);

            group->setTransform(trans, true);

            // group must be destroyed so that we can interact with the items
            destroyItemGroup(group);
        }

        if(cnt++ % 6 == 0)
        {
            cnt = 0;
            refreshItemPositionsOnNetwork();
        }
        // In case of a rotation, we don't want the graphics items
        // to get the mouse move event, so we return without
        // calling mouse move event of qgraphicsscene
        if(rot) return;
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
    if(event->key() == Qt::Key_R && !event->isAutoRepeat())
    {
        qDebug() << "début de rotation";
        rot = true;
    }
    QGraphicsScene::keyPressEvent(event);
}

void EnhancedGraphicsScene::keyReleaseEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_R && !event->isAutoRepeat())
    {
        qDebug() << "fin de rotation";
        rot = false;
        firstRot = true;
    }
    QGraphicsScene::keyReleaseEvent(event);
}


QPointF EnhancedGraphicsScene::findRotationPivot(QList<QGraphicsItem*>& list, bool right)
{
    QPointF origin;

    // We set the origin with the first selected graphics item in order to compare it to every other selected items
    if(!list.isEmpty())
    {
        QPointF p = list.first()->mapToScene(list.first()->boundingRect().topRight());
        if(right)
        {
            if(list.first()->scenePos().x() < p.x())
                origin = list.first()->scenePos();
            else
                origin = p;
        }
        else
        {
            if(list.first()->scenePos().x() > p.x())
                origin = list.first()->scenePos();
            else
                origin = p;
        }
    }
    else return origin;

    // Find pivot of the rotation

    for(int i = 1 ; i < list.size(); ++i)
    {
        // pivot is on the right of the center of the group's bounding rect
        if(right)
        {
            QPointF p = list.at(i)->mapToScene(list.at(i)->boundingRect().topRight());
            if (list.at(i)->x() < origin.x())
                origin = list.at(i)->scenePos();
            if ( p.x() < origin.x())
                origin = p;
        }
        // pivot is on the left of the center of the group's bounding rect
        else
        {
            QPointF p = list.at(i)->mapToScene(list.at(i)->boundingRect().topRight());
            if ( p.x() > origin.x())
                origin = p;
            if (list.at(i)->x() > origin.x())
                origin = list.at(i)->scenePos();
        }
    }
    return origin;
}
