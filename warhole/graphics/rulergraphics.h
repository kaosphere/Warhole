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

#include "distances.h"

class RulerGraphics : public QGraphicsObject
{
    Q_OBJECT
public:
    RulerGraphics();
    RulerGraphics(const int& l, const QString &id);
    virtual ~RulerGraphics();

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    int getLength() const;
    void setLength(int value);

    int getWidth() const;
    void setWidth(int value);

    void contextMenuEvent(QGraphicsSceneContextMenuEvent *event);
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    QString getId() const;
    void setId(const QString &value);

public slots:

signals:
    void rulerMoved(QString, QTransform);

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
