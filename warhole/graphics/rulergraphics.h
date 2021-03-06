#ifndef RULERGRAPHICS_H
#define RULERGRAPHICS_H

#include <QGraphicsObject>
#include <QLinearGradient>
#include <QPainter>
#include <QtCore>
#include <QMenu>
#include <QGraphicsSceneContextMenuEvent>
#include <QKeyEvent>
#include <QCursor>

#include <qmath.h>

#include "distances.h"
#include "components/enhancegraphicsobject.h"

class RulerGraphics : public EnhanceGraphicsObject
{
    Q_OBJECT
public:
    RulerGraphics(QGraphicsItem *parent = 0);
    RulerGraphics(const int& l, const QString &id, QGraphicsItem* parent = 0);
    virtual ~RulerGraphics();

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    int getLength() const;
    void setLength(int value);

    int getWidth() const;
    void setWidth(int value);

    void contextMenuEvent(QGraphicsSceneContextMenuEvent *event);
    QString getId() const;
    void setId(const QString &value);

    
    QDataStream& serializeOut(QDataStream& out);
    QDataStream& serializeIn(QDataStream& in);

    friend QDataStream& operator<<(QDataStream& out, const RulerGraphics& obj);
    friend QDataStream& operator>>(QDataStream& in, RulerGraphics& obj);

    virtual void sendObjectMovedSignal();

public slots:
    void removeRulerRequest();

signals:
    void rulerMoved(QString, QPointF, QTransform, qreal);
    void removeRuler(QString);

private:
    //! length.
    /*!
    * Length of the ruler expressed in inches
    */
    int length;

    QString id;

    //! width.
    /*!
    * Length of the ruler expressed in pixels
    */
    int width;

    int cnt;

    static const int DEFAULT_RULER_LENGTH;
    static const int DEFAULT_RULER_WIDTH;
    static const int GRADUATION_SIZE;
    static const int GRADUATION_NUMBER_WIDTH;
    static const int GRADUATION_NUMBER_HIGHT;
    static const int PEN_WIDTH;

    QAction* actionRemoveRuler;
    bool rot;
    bool firstRot;
    QPointF initialPos;

    void initRulerGraphics();
};

#endif // RULERGRAPHICS_H
