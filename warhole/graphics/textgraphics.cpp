#include "textgraphics.h"

const QString TextGraphics::DEFAULT_TEXT = tr("Entrez votre texte");

TextGraphics::TextGraphics(QGraphicsItem *parent) :
    EnhanceGraphicsObject(parent)
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
    rot = false;
    firstRot = true;
    setZValue(TEXT_Z_VALUE);

    actionRemove = new QAction(tr("Retirer"), this);
    connect(actionRemove, SIGNAL(triggered()), this, SLOT(removeText()));

    item = new QGraphicsTextItem(this);
    refreshItemText();
    item->setFont(QFont("Times", 48, QFont::Bold));
    setFlag(ItemIsMovable);
    setFlag(ItemIsFocusable);
    setFlag(ItemIsSelectable);
}

QRectF TextGraphics::boundingRect() const
{
    if(item) return item->boundingRect();
}

void TextGraphics::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(painter);
    Q_UNUSED(option);
    Q_UNUSED(widget);
}

void TextGraphics::refreshItemText()
{
    item->setHtml("<font color=\"Blue\"strong>" + text + "</font></strong>");
}

QDataStream &TextGraphics::serializeIn(QDataStream &in)
{
    in >> (*this);
    return in;
}

QDataStream &TextGraphics::serializeOut(QDataStream &out)
{
    out << (*this);
    return out;
}

QDataStream& operator<<(QDataStream& out, const TextGraphics& obj)
{
    obj.serializeOutBase(out);
    out << obj.id;
    out << obj.text;
    out << obj.pos();
    out << obj.transform();

    return out;
}

QDataStream& operator>>(QDataStream& in, TextGraphics& obj)
{
    QPointF position;
    QTransform matrix;

    obj.serializeInBase(in);
    in >> obj.id;
    in >> obj.text;
    in >> position;
    in >> matrix;

    obj.setPos(position);
    obj.setTransform(matrix);

    obj.refreshItemText();

    return in;
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
    emit textChanged(id, text, pos(), transform(), previousRot);
}

void TextGraphics::setTextWithoutSignal(const QString &value)
{
    text = value;
    refreshItemText();
}

void TextGraphics::contextMenuEvent(QGraphicsSceneContextMenuEvent *event)
{
    QMenu *menu = new QMenu;
    menu->addAction(actionRemove);
    menu->popup(event->screenPos());
}

void TextGraphics::removeText()
{
    emit removeTextRequest(id);
}

void TextGraphics::sendObjectMovedSignal()
{
    emit textChanged(id, text, pos(), transform(), previousRot);
}

