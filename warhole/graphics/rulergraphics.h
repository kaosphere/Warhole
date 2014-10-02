#ifndef RULERGRAPHICS_H
#define RULERGRAPHICS_H

#include <QGraphicsObject>
#include <QLinearGradient>
#include <QPainter>

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

    void initRulerGraphics();
};

#endif // RULERGRAPHICS_H
