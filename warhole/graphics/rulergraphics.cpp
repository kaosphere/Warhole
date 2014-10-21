#include "rulergraphics.h"

const int RulerGraphics::DEFAULT_RULER_LENGTH = 6;
const int RulerGraphics::DEFAULT_RULER_WIDTH = ONE_INCH;
const int RulerGraphics::GRADUATION_SIZE = ONE_INCH/5;
const int RulerGraphics::GRADUATION_NUMBER_WIDTH = RulerGraphics::DEFAULT_RULER_WIDTH/2;
const int RulerGraphics::GRADUATION_NUMBER_HIGHT = RulerGraphics::DEFAULT_RULER_WIDTH/2;
const int RulerGraphics::PEN_WIDTH = 3;

RulerGraphics::RulerGraphics(QGraphicsItem* parent) : QGraphicsObject(parent)
{
    length = DEFAULT_RULER_LENGTH;
    initRulerGraphics();
}

RulerGraphics::RulerGraphics(const int &l, const QString& i, QGraphicsItem *parent) :
    QGraphicsObject(parent)
{
    length = l;
    id = i;
    initRulerGraphics();
}

void RulerGraphics::initRulerGraphics()
{
    width = DEFAULT_RULER_WIDTH;
    cnt = 1;

    actionRemoveRuler = new QAction(tr("Retirer"), this);
    connect(actionRemoveRuler, SIGNAL(triggered()),this, SLOT(removeRulerRequest()));

    rot = false;
    firstRot = true;

    setFlag(ItemIsMovable);
    setFlag(ItemIsSelectable);
    setFlag(ItemIsFocusable);
}

RulerGraphics::~RulerGraphics()
{
}

QRectF RulerGraphics::boundingRect() const
{
    return QRect(-PEN_WIDTH,
                 -PEN_WIDTH,
                 length*ONE_INCH + PEN_WIDTH,
                 width + PEN_WIDTH);
}

void RulerGraphics::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QRectF rec = boundingRect();
    QLinearGradient gradient(0, 0, 0, width);
    gradient.setColorAt(0, QColor::fromRgb(qRgba(221, 209, 92, 0.8)));
    gradient.setColorAt(1, QColor::fromRgb(qRgba(80, 80, 20, 0.8)));

    QBrush brush(gradient);
    QPen pen(QColor(0,20,40),3);

    painter->fillRect(rec,brush);

    painter->setPen(pen);
    painter->drawRect(rec);

    QFont font;
    font.setPixelSize(36);
    painter->setFont(font);

    // Draw ruler graduation
    for(int i = 1; i< length; ++i)
    {
        painter->drawLine(i*ONE_INCH,0,i*ONE_INCH, GRADUATION_SIZE);
        painter->drawLine(i*ONE_INCH,width-GRADUATION_SIZE,i*ONE_INCH,width);
        painter->drawText(i*ONE_INCH - GRADUATION_NUMBER_HIGHT/2,
                          width/2 - GRADUATION_NUMBER_WIDTH/2,
                          GRADUATION_NUMBER_WIDTH,
                          GRADUATION_NUMBER_HIGHT,
                          Qt::AlignHCenter || Qt::AlignVCenter,
                          QString::number(i));
    }
}

int RulerGraphics::getLength() const
{
    return length;
}

void RulerGraphics::setLength(int value)
{
    length = value;
}

int RulerGraphics::getWidth() const
{
    return width;
}

void RulerGraphics::setWidth(int value)
{
    width = value;
}

void RulerGraphics::contextMenuEvent(QGraphicsSceneContextMenuEvent *event)
{
    QMenu *menu = new QMenu;
    menu->addAction(actionRemoveRuler);
    menu->popup(event->screenPos());
}

void RulerGraphics::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    static QPointF previousPos = scenePos();
    if(rot)
    {
        static int offset = 0;

        if(firstRot)
        {
            if(event->pos().x() < boundingRect().center().x())
            {
                setTransformOriginPoint(boundingRect().right(),0);
                offset = 180;
            }
            else
            {
                setTransformOriginPoint(0,0);
                offset = 0;
            }
            firstRot = false;
        }

        QPointF originPoint = mapToScene(transformOriginPoint());

        qreal a1 = event->scenePos().x() - originPoint.x();
        qreal a2 = event->scenePos().y() - originPoint.y();
        qreal angle = qAtan2(a2, a1);

        setRotation((angle * 180 / 3.14) + offset);

        //setTransform(transform() * QTransform().translate(cX,cY).rotate(rotation() + angle).translate(-cX,-cY));

        if((++cnt)%6 == 0)
        {
            cnt = 1;
            emit rulerMoved(id, pos(), transform());
        }
    }
    else
    {
        if((++cnt)%6 == 0)
        {
            cnt = 1;
            emit rulerMoved(id, pos(), transform());
        }
        QGraphicsItem::mouseMoveEvent(event);
    }
}

void RulerGraphics::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_R)
    {
        rot = true;
    }
    QGraphicsItem::keyPressEvent(event);
}

void RulerGraphics::keyReleaseEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_R && !event->isAutoRepeat())
    {
        rot = false;
        firstRot = true;
    }
    QGraphicsItem::keyReleaseEvent(event);
}

void RulerGraphics::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    // End of movement, send final position
    qDebug() << "Finalizing movement";
    emit rulerMoved(id, pos(), transform());

    QGraphicsItem::mouseReleaseEvent(event);
}

QString RulerGraphics::getId() const
{
    return id;
}

void RulerGraphics::setId(const QString &value)
{
    id = value;
}

void RulerGraphics::removeRulerRequest()
{
    emit removeRuler(id);
}
