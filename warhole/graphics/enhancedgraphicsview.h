#ifndef ENHANCEDGRAPHICSVIEW_H
#define ENHANCEDGRAPHICSVIEW_H

#include <QGraphicsView>
#include <QObject>
#include <QWheelEvent>
#include <cmath>
#include <QDebug>
#include "Utilities/QLogger/QLogger.h"

class EnhancedGraphicsView : public QGraphicsView
{
    Q_OBJECT
public:
    explicit EnhancedGraphicsView(QWidget *parent=0);
    virtual ~EnhancedGraphicsView();

public slots:
    void zoomIn();
    void zoomOut();
protected:
    void wheelEvent(QWheelEvent *event);

private:
    void scaleBy(double factor);

    double scaleFactor;

    static const double MAX_SCALE_FACTOR;
    static const double MIN_SCALE_FACTOR;

    static const QString LOG_ID_TRACE;
    static const QString LOG_ID_INFO;
    static const QString LOG_ID_WARN;
    static const QString LOG_ID_ERR;
};

#endif // ENHANCEDGRAPHICSVIEW_H
