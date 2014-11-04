#include "blowtemplategraphics.h"

const qreal BlowTemplateGraphics::WIDTH = 2.5;
const qreal BlowTemplateGraphics::LENGTH = 8.5;

BlowTemplateGraphics::BlowTemplateGraphics(QGraphicsItem *parent) :
    QGraphicsObject(parent)
{
    id = "";
    initRoundTemplateGraphics();
}

BlowTemplateGraphics::BlowTemplateGraphics(QString i, QGraphicsItem *parent)
{
    id = i;
    initRoundTemplateGraphics();
}

void BlowTemplateGraphics::initRoundTemplateGraphics()
{
    actionRemoveTemplate = new QAction(tr("Retirer"), this);
    connect(actionRemoveTemplate, SIGNAL(triggered()),this, SLOT(removeTemplate()));

    rot = false;
    firstRot = true;
    previousRot = 0;

    setFlag(ItemIsMovable);
    setFlag(ItemIsFocusable);
    setFlag(ItemIsSelectable);

    setOpacity(0.7);
    setZValue(1);
}

QRectF BlowTemplateGraphics::boundingRect() const
{
    return QRectF(0,0,LENGTH * ONE_INCH, WIDTH * ONE_INCH);
}

QPainterPath BlowTemplateGraphics::shape() const
{
    QPainterPath p;

    p.moveTo(0,(WIDTH/2)*ONE_INCH);
    p.lineTo((LENGTH - WIDTH/2)*ONE_INCH, WIDTH * ONE_INCH);
    p.arcTo(QRectF((LENGTH - WIDTH)*ONE_INCH, 0, WIDTH*ONE_INCH, WIDTH*ONE_INCH), 270, 180);
    p.lineTo(0,(WIDTH/2)*ONE_INCH);

    return p;
}

void BlowTemplateGraphics::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    // Paint main circle, do this in a path to empty the middle circle
    QPainterPath p = shape();

    QLinearGradient gradient(0, 0, 0, WIDTH * ONE_INCH);
    gradient.setColorAt(0, QColor::fromRgb(qRgba(221, 209, 92, 0.8)));
    gradient.setColorAt(1, QColor::fromRgb(qRgba(80, 80, 20, 0.8)));

    QBrush brush(gradient);
    QPen pen(QColor(0,20,40),3);

    painter->setBrush(brush);
    painter->setPen(pen);

    painter->drawPath(p);
}

void BlowTemplateGraphics::setId(QString value)
{
    id = value;
}

QString BlowTemplateGraphics::getId() const
{
    return id;
}

void BlowTemplateGraphics::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    static qreal translation;
    static int cnt = 0;
    if(rot)
    {
        static int offset = 0;
        if(firstRot)
        {
            if(event->pos().x() < boundingRect().center().x())
            {
                translation = boundingRect().right();
                offset = 180;
            }
            else
            {
                translation = 0;
                offset = 0;
            }
            firstRot = false;
        }
    
        QPointF originPoint = mapToScene(translation, 0);
        qreal a1 = event->scenePos().x() - originPoint.x();
        qreal a2 = event->scenePos().y() - originPoint.y();
        qreal angle = qAtan2(a2, a1);
        
        QTransform trans;
        trans.translate(translation,0).rotate(-previousRot).rotate((angle * 180 / 3.14) + offset).translate(-translation,0);
        setTransform(trans, true);
        
        previousRot = ((angle * 180 / 3.14) + offset);
    
        if((++cnt)%6 == 0)
        {
            cnt = 1;
            emit templateMoved(id, pos(), transform());
        }
    }
    else
    {
        if((++cnt)%6 == 0)
        {
            cnt = 1;
            emit templateMoved(id, pos(), transform());
        }
        QGraphicsItem::mouseMoveEvent(event);
    }
}

void BlowTemplateGraphics::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    // End of movement, send final position
    emit templateMoved(id, pos(), transform());
    
    QGraphicsItem::mouseReleaseEvent(event);
}

void BlowTemplateGraphics::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_R)
    {
        rot = true;
    }
    QGraphicsItem::keyPressEvent(event);
}

void BlowTemplateGraphics::keyReleaseEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_R && !event->isAutoRepeat())
    {
        rot = false;
        firstRot = true;
        previousRot = 0;
    }
    QGraphicsItem::keyReleaseEvent(event);
}

void BlowTemplateGraphics::contextMenuEvent(QGraphicsSceneContextMenuEvent *event)
{
    QMenu *menu = new QMenu;
    menu->addAction(actionRemoveTemplate);
    menu->popup(event->screenPos());
}

QDataStream &BlowTemplateGraphics::serializeOut(QDataStream &out)
{
    out << (*this);
    return out;
}

QDataStream &BlowTemplateGraphics::serializeIn(QDataStream &in)
{
    in >> (*this);
    return in;
}

QDataStream &operator <<(QDataStream &out, const BlowTemplateGraphics &obj)
{
    out << obj.id
        << obj.pos()
        << obj.transform();
        
    return out;
}

QDataStream &operator >>(QDataStream &in, BlowTemplateGraphics &obj)
{
    QPointF position; 
    QTransform matrix;
    
    in >> obj.id;
    in >> position;
    in >> matrix;
    
    obj.setPos(position);
    obj.setTransform(matrix);
    
    return in;
}

void BlowTemplateGraphics::removeTemplate()
{
    emit removeTemplateRequest(id);
}
