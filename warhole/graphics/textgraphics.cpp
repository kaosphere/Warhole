#include "textgraphics.h"

const QString TextGraphics::DEFAULT_TEXT = tr("Entrez votre texte");

TextGraphics::TextGraphics(QGraphicsItem *parent) :
    QGraphicsObject(parent)
{
    item = NULL;
    text = DEFAULT_TEXT;

    initTextItem();
}

TextGraphics::~TextGraphics()
{
    if(item) delete item;
}

void TextGraphics::initTextItem()
{
    item = new QGraphicsTextItem(this);
    refreshItemText();
    item->setFont(QFont("Times", 48, QFont::Bold));
    setFlag(ItemIsMovable);
    setFlag(ItemIsFocusable);
}

QRectF TextGraphics::boundingRect() const
{
    if(item) return item->boundingRect();
}

void TextGraphics::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
}

void TextGraphics::refreshItemText()
{
    item->setHtml("<font color=\"Blue\"strong>" + text + "</font></strong>");
}

void TextGraphics::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
    emit textDoubleClicked();

    QGraphicsItem::mouseDoubleClickEvent(event);
}

QString TextGraphics::getId() const
{
    return id;
}

void TextGraphics::setId(const QString &value)
{
    id = value;
}

QString TextGraphics::getText() const
{
    return text;
}

void TextGraphics::setText(const QString &value)
{
    text = value;
    refreshItemText();
}




