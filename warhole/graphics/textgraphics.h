#ifndef TEXTGRAPHICS_H
#define TEXTGRAPHICS_H

#include <QGraphicsObject>
#include <QtCore>
#include <QGraphicsTextItem>
#include <QFont>
#include <QInputDialog>
#include <QGraphicsSceneMouseEvent>
#include <QKeyEvent>
#include <QAction>
#include <QMenu>
#include "distances.h"
#include "components/enhancegraphicsobject.h"

class TextGraphics : public EnhanceGraphicsObject
{
    Q_OBJECT
public:
    explicit TextGraphics(QGraphicsItem *parent = 0);
    ~TextGraphics();

    virtual QRectF boundingRect() const;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event);
    
    QString getText() const;
    void setText(const QString &value);

    QString getId() const;
    void setId(const QString &value);

    void initTextItem();
    void refreshItemText();

    QDataStream &serializeIn(QDataStream& in);
    QDataStream& serializeOut(QDataStream& out);

    friend QDataStream& operator<<(QDataStream& out, const TextGraphics& obj);
    friend QDataStream& operator>>(QDataStream& in, TextGraphics& obj);

    void contextMenuEvent(QGraphicsSceneContextMenuEvent *event);

    void setTextWithoutSignal(const QString &value);

    virtual void sendObjectMovedSignal();

signals:
    void textDoubleClicked();
    void textChanged(QString, QString, QPointF, QTransform, qreal);
    void removeTextRequest(QString);
    
public slots:
    void removeText();

private:
    QGraphicsTextItem* item;
    QString text;
    QString id;
    QAction* actionRemove;

    bool rot;
    bool firstRot;

    static const QString DEFAULT_TEXT;
    
};

#endif // TEXTGRAPHICS_H
