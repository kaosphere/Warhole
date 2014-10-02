#ifndef RULERGRAPHICS_H
#define RULERGRAPHICS_H

#include <QGraphicsObject>
#include <QLinearGradient>
#include <QPainter>
#include <QtCore>
#include <QMenu>
#include <QGraphicsSceneContextMenuEvent>

#include "distances.h"

class RulerGraphics : public QGraphicsObject
{
    Q_OBJECT
public:
    RulerGraphics();
    RulerGraphics(const int& l);
    virtual ~RulerGraphics();

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    int getLength() const;
    void setLength(int value);

    int getWidth() const;
    void setWidth(int value);

    void contextMenuEvent(QGraphicsSceneContextMenuEvent *event);
public slots:

private:
    //! length.
    /*!
    * Length of the ruler expressed in inches
    */
    int length;

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

    void initRulerGraphics();
};

#endif // RULERGRAPHICS_H
