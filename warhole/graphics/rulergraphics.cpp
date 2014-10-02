#include "rulergraphics.h"

const int RulerGraphics::DEFAULT_RULER_LENGTH = 6;
const int RulerGraphics::DEFAULT_RULER_WIDTH = ONE_INCH;

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

    setFlag(ItemIsMovable);
}

RulerGraphics::~RulerGraphics()
{

}

QRectF RulerGraphics::boundingRect() const
{
    return QRect(0,
                 0,
                 length*ONE_INCH,
                 width);
}

void RulerGraphics::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QRectF rec = boundingRect();
    QLinearGradient gradient(0, length*ONE_INCH, width, 0);
    gradient.setColorAt(0, QColor::fromRgb(qRgba(221, 209, 92, 0.8)));
    gradient.setColorAt(1, QColor::fromRgb(qRgba(240, 238, 151, 0.8)));

    QBrush brush(gradient);
    QPen pen(QColor(0,20,40),3);

    painter->fillRect(rec,brush);

    painter->setPen(pen);
    painter->drawRect(rec);
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


