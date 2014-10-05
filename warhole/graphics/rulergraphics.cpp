#include "rulergraphics.h"

const int RulerGraphics::DEFAULT_RULER_LENGTH = 6;
const int RulerGraphics::DEFAULT_RULER_WIDTH = ONE_INCH;
const int RulerGraphics::GRADUATION_SIZE = ONE_INCH/5;
const int RulerGraphics::GRADUATION_NUMBER_WIDTH = RulerGraphics::DEFAULT_RULER_WIDTH/2;
const int RulerGraphics::GRADUATION_NUMBER_HIGHT = RulerGraphics::DEFAULT_RULER_WIDTH/2;
const int RulerGraphics::PEN_WIDTH = 3;

RulerGraphics::RulerGraphics()
{
    length = DEFAULT_RULER_LENGTH;
    initRulerGraphics();
}

RulerGraphics::RulerGraphics(const int &l)
{
    length = l;
    initRulerGraphics();
}

void RulerGraphics::initRulerGraphics()
{
    width = DEFAULT_RULER_WIDTH;

    actionRemoveRuler = new QAction(tr("Retirer"), this);
    connect(actionRemoveRuler, SIGNAL(triggered()),this, SLOT(deleteLater()));

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
    if(rot)
    {
        if(firstRot)
        {
            initialPos = event->scenePos();
            firstRot = false;
        }
        int cX = boundingRect().center().x();
        int cY = boundingRect().center().y();
        qreal angle = event->scenePos().manhattanLength() - initialPos.manhattanLength();
        setTransform(transform() * QTransform().translate(cX, cY).rotate(rotation() + angle / 100).translate(-cX, -cY));
    }
    else
    {
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
