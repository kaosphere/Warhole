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
    rot = false;
    firstRot = true;

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

void TextGraphics::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    static qreal translation;
    static qreal previousRot = 0;
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
            emit textChanged(id, text, pos(), transform());
        }
    }
    else
    {
        if((++cnt)%6 == 0)
        {
            cnt = 1;
            emit textChanged(id, text, pos(), transform());
        }
        QGraphicsItem::mouseMoveEvent(event);
    }
}

void TextGraphics::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_R)
    {
        rot = true;
    }
    QGraphicsItem::keyPressEvent(event);
}

void TextGraphics::keyReleaseEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_R && !event->isAutoRepeat())
    {
        rot = false;
        firstRot = true;
    }
    QGraphicsItem::keyReleaseEvent(event);
}

void TextGraphics::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    // End of movement, send final position
    emit textChanged(id, text, pos(), transform());

    QGraphicsItem::mouseReleaseEvent(event);
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
    emit textChanged(id, text, pos(), transform());
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

