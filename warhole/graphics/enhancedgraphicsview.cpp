#include "graphics/enhancedgraphicsview.h"

const double EnhancedGraphicsView::MAX_SCALE_FACTOR = 2;
const double EnhancedGraphicsView::MIN_SCALE_FACTOR = 0.2;

const QString EnhancedGraphicsView::LOG_ID_INFO = "EnhancedGraphicsView_info";
const QString EnhancedGraphicsView::LOG_ID_TRACE = "EnhancedGraphicsView_trace";
const QString EnhancedGraphicsView::LOG_ID_WARN = "EnhancedGraphicsView_warm";
const QString EnhancedGraphicsView::LOG_ID_ERR = "EnhancedGraphicsView_err";

using namespace QLogger;

EnhancedGraphicsView::EnhancedGraphicsView(QWidget *parent) : QGraphicsView(parent)
{
    QLoggerManager *manager = QLoggerManager::getInstance();
    manager->addDestination("./logs/lastrun.log", QStringList(LOG_ID_TRACE), QLogger::TraceLevel);
    manager->addDestination("./logs/lastrun.log", QStringList(LOG_ID_INFO), QLogger::InfoLevel);
    manager->addDestination("./logs/lastrun.log", QStringList(LOG_ID_ERR), QLogger::ErrorLevel);
    manager->addDestination("./logs/lastrun.log", QStringList(LOG_ID_WARN), QLogger::WarnLevel);

    // init scale factor
    scaleFactor = 1.0;

    setDragMode(ScrollHandDrag);

    setRenderHints(QPainter::Antialiasing|
                   QPainter::TextAntialiasing);

    setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
}

EnhancedGraphicsView::~EnhancedGraphicsView()
{

}

void EnhancedGraphicsView::zoomIn()
{
    scaleBy(1.1);
}

void EnhancedGraphicsView::zoomOut()
{
    scaleBy(1.0 / 1.1);
}

void EnhancedGraphicsView::wheelEvent(QWheelEvent *event)
{
    double factor = std::pow(4.0 / 3.0, (event->delta() / 240.0));

    qDebug() << factor;

    if((factor*scaleFactor) <= MAX_SCALE_FACTOR && (factor*scaleFactor) >= MIN_SCALE_FACTOR)
    {
        scaleFactor *= factor;
        scaleBy(factor);
    }
}

void EnhancedGraphicsView::scaleBy(double factor)
{
    scale(factor, factor);
}
