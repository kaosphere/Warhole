#ifndef TEXTGRAPHICS_H
#define TEXTGRAPHICS_H

#include <QGraphicsObject>
#include <QtCore>
#include <QGraphicsTextItem>
#include <QFont>
#include <QInputDialog>

class TextGraphics : public QGraphicsObject
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
signals:
    void textDoubleClicked();
    
public slots:

private:
    QGraphicsTextItem* item;
    QString text;
    QString id;

    static const QString DEFAULT_TEXT;
    
};

#endif // TEXTGRAPHICS_H
