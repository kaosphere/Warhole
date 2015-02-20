#include "blowtemplategraphics.h"

const qreal BlowTemplateGraphics::WIDTH = 2.5;
const qreal BlowTemplateGraphics::LENGTH = 8.5;

BlowTemplateGraphics::BlowTemplateGraphics(QGraphicsItem *parent) :
    EnhanceGraphicsObject(parent)
{
    id = "";
    initRoundTemplateGraphics();
}

BlowTemplateGraphics::BlowTemplateGraphics(QString i, QGraphicsItem *parent) :
    EnhanceGraphicsObject(parent)
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
    setZValue(TEMPLATE_Z_VALUE);

    setFlag(ItemIsMovable);
    setFlag(ItemIsFocusable);
    setFlag(ItemIsSelectable);

    setOpacity(0.7);
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
    obj.serializeOutBase(out);
    out << obj.id
        << obj.pos()
        << obj.transform();

    return out;
}

QDataStream &operator >>(QDataStream &in, BlowTemplateGraphics &obj)
{
    QPointF position;
    QTransform matrix;
    
    obj.serializeInBase(in);
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

void BlowTemplateGraphics::sendObjectMovedSignal()
{
    emit templateMoved(id, pos(), transform(), previousRot);
}

bool BlowTemplateGraphics::isUpsideDown()
{
    if(pos().x() >= mapToScene(QPointF(boundingRect().right(), boundingRect().top())).x()) return true;
    else return false;
}
