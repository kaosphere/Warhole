#include "rulergraphics.h"

const int RulerGraphics::DEFAULT_RULER_LENGTH = 6;
const int RulerGraphics::DEFAULT_RULER_WIDTH = ONE_INCH;
const int RulerGraphics::GRADUATION_SIZE = ONE_INCH/5;
const int RulerGraphics::GRADUATION_NUMBER_WIDTH = RulerGraphics::DEFAULT_RULER_WIDTH/2;
const int RulerGraphics::GRADUATION_NUMBER_HIGHT = RulerGraphics::DEFAULT_RULER_WIDTH/2;
const int RulerGraphics::PEN_WIDTH = 3;

RulerGraphics::RulerGraphics(QGraphicsItem* parent) :
    EnhanceGraphicsObject(parent)
{
    length = DEFAULT_RULER_LENGTH;
    initRulerGraphics();
}

RulerGraphics::RulerGraphics(const int &l, const QString& i, QGraphicsItem *parent) :
    EnhanceGraphicsObject(parent)
{
    length = l;
    id = i;
    initRulerGraphics();
}

void RulerGraphics::initRulerGraphics()
{
    width = DEFAULT_RULER_WIDTH;
    cnt = 1;

    setZValue(RULER_Z_VALUE);

    actionRemoveRuler = new QAction(tr("Retirer"), this);
    connect(actionRemoveRuler, SIGNAL(triggered()),this, SLOT(removeRulerRequest()));

    rot = false;
    firstRot = true;

    setFlag(ItemIsMovable);
    setFlag(ItemIsFocusable);
    setFlag(ItemIsSelectable);
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

QDataStream& RulerGraphics::serializeOut(QDataStream& out)
{
    out << (*this);
    return out;
}

QDataStream& RulerGraphics::serializeIn(QDataStream& in)
{
    in >> (*this);
    return in;
}

QDataStream& operator<<(QDataStream& out, const RulerGraphics& obj)
{
    obj.serializeOutBase(out);
    out << obj.id
        << obj.length
        << obj.pos()
        << obj.transform();

    return out;
}

QDataStream& operator>>(QDataStream& in, RulerGraphics& obj)
{
    QPointF position;
    QTransform trans;

    obj.serializeInBase(in);
    in >> obj.id;
    in >> obj.length;
    in >> position;

    obj.setPos(position);

    in >> trans;

    obj.setTransform(trans);

    return in;
}

void RulerGraphics::sendObjectMovedSignal()
{
    emit rulerMoved(id, pos(), transform(), previousRot);
}

