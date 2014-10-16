#ifndef MODELGRAPHICS_H
#define MODELGRAPHICS_H

#include <QGraphicsRectItem>
#include <QBrush>
#include <QPen>
#include <QPainter>


//! ModelGraphics class
/*!
* This class inheritates QGraphicsRectItem and enhance it with
* the name of the model that it's represented.
*/
class ModelGraphics : public QGraphicsItem
{
public:
    ModelGraphics(QGraphicsItem *parent = 0);
    ModelGraphics(int x, int y, int w, int h, QString n, QPixmap *i = NULL, QGraphicsItem *parent = 0);

    virtual ~ModelGraphics();

    QString getModelName() const;
    void setModelName(const QString &value);

    virtual QRectF boundingRect() const;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    QBrush getBrush() const;
    void setBrush(const QBrush &value);

    QPen getPen() const;
    void setPen(const QPen &value);

    void setPosXY(qreal x, qreal y);
private:
    QString modelName;
    QPixmap* image;
    int width;
    int hight;
    int posx;
    int posy;

    QBrush brush;
    QPen pen;
};

#endif // MODELGRAPHICS_H
