/*! ********************************************************************
* EnhancedGraphicsView.h
* EnhancedGraphicsView class
*
* AUTEUR: Alexandre Jumeline
* DATE: 16-09-2014
*************************************************************************/

#ifndef ENHANCEDGRAPHICSVIEW_H
#define ENHANCEDGRAPHICSVIEW_H

#include <QGraphicsView>
#include <QObject>
#include <QWheelEvent>
#include <cmath>
#include <QDebug>
#include "Utilities/QLogger/QLogger.h"

//! EnhancedGraphicsView class
/*!
* This class inheritates QGraphicsView and enhance it with
* a zoom using the mouse wheel.
*/
class EnhancedGraphicsView : public QGraphicsView
{
    Q_OBJECT
public:
    //! Constructor.
    /*!
    * Base constructor of EnhancedGraphicsView class
    */
    explicit EnhancedGraphicsView(QWidget *parent=0);

    //! Destructor.
    /*!
    * Destructor of EnhancedGraphicsView class
    */
    virtual ~EnhancedGraphicsView();

public slots:
    //! zoomIn.
    /*!
    * Slot that zooms in the view.
    */
    void zoomIn();

    //! zoomOut.
    /*!
    * Slot that zooms out from the view.
    */
    void zoomOut();
protected:
    //! wheelEvent.
    /*!
    * Reimplementation of the mouse wheel event from QGraphicsView
    * to perform a zoom instead of scrolling the view.
    */
    virtual void wheelEvent(QWheelEvent *event);

private:
    //! scaleBy.
    /*!
    * Function that performs the scaling
    * @param factor Factor of the scaling
    */
    void scaleBy(double factor);

    //! scaleFactor.
    /*!
    * Factor of scaling applied currently to the view.
    */
    double scaleFactor;

    //! MAX_SCALE_FACTOR.
    /*!
    * Maximum factor of scaling that can be applied to the view.
    */
    static const double MAX_SCALE_FACTOR;

    //! MIN_SCALE_FACTOR.
    /*!
    * Minimum factor of scaling that can be applied to the view.
    */
    static const double MIN_SCALE_FACTOR;

    static const QString LOG_ID_TRACE;
    static const QString LOG_ID_INFO;
    static const QString LOG_ID_WARN;
    static const QString LOG_ID_ERR;
};

#endif // ENHANCEDGRAPHICSVIEW_H
