#ifndef REGIMENTGRAPHICS_H
#define REGIMENTGRAPHICS_H

#include <QGraphicsItem>

#include "modelgraphics.h"
#include "distances.h"
#include "game/regiment/regimentabstract.h"
#include "Utilities/QLogger/QLogger.h"

class RegimentGraphics : public QGraphicsObject
{
    Q_OBJECT
public:
    RegimentGraphics(QGraphicsItem* parent = 0);
    RegimentGraphics(const RegimentAbstract& r, QGraphicsItem* parent = 0);
    virtual ~RegimentGraphics();

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    RegimentAbstract getRegiment() const;
    void setRegiment(const RegimentAbstract &value);

    virtual QPainterPath shape() const;
    int getRegimentID() const;
    void setRegimentID(int value);

protected:
    virtual void mouseMoveEvent(QGraphicsSceneMouseEvent* event);

private:
    void initRegimentGraphics();

    void initModels();

    void paintClassicRegiment(QPainter *painter);
    void paintSkirmishRegiment(QPainter *painter);

    static const QString LOG_ID_TRACE;
    static const QString LOG_ID_INFO;
    static const QString LOG_ID_WARN;
    static const QString LOG_ID_ERR;

    static const int DEFAULT_REGIMENT_WIDTH;

    RegimentAbstract regiment;

    //! regimentWidth.
    /*!
    * Stores the number of models wide of the regiment to be displayed.
    * Default value is 5 models wide.
    */
    int regimentWidth;

    QList<ModelGraphics*> models;

    QPen* childrenPen;

    int regimentID;


private slots:
    void updateRegiment();

signals:
    //! regimentDataChanged.
    /*!
    * This signal is sent when a value has changed in the regiment.
    */
    void regimentDataChanged();

    //! regimentMoved.
    /*!
    * This signal is sent when the graphic regiment is moved.
    */
    void regimentMoved();

    //! regimentUpdated.
    /*!
    * This signal is casted when a new regiment is set in place of the previous
    * one. This signal is different from regimentDataChanged() because we don't
    * want to repaint the graphical object each time we change a value in the regiment.
    * But when a new regiment is set, it means that the display has to be updated.
    */
    void regimentUpdated();

};

#endif // REGIMENTGRAPHICS_H
