#include "regimentgraphics.h"

using namespace QLogger;

const QString RegimentGraphics::LOG_ID_INFO = "RegimentGraphics_info";
const QString RegimentGraphics::LOG_ID_TRACE = "RegimentGraphics_trace";
const QString RegimentGraphics::LOG_ID_WARN = "RegimentGraphics_warm";
const QString RegimentGraphics::LOG_ID_ERR = "RegimentGraphics_err";

RegimentGraphics::RegimentGraphics()
{
    initRegimentGraphics();
}

RegimentGraphics::RegimentGraphics(const RegimentAbstract &r)
{
    initRegimentGraphics();

    regiment = r;
}

void RegimentGraphics::initRegimentGraphics()
{
    QLoggerManager *manager = QLoggerManager::getInstance();
    manager->addDestination("./logs/lastrun.log", QStringList(LOG_ID_TRACE), QLogger::TraceLevel);
    manager->addDestination("./logs/lastrun.log", QStringList(LOG_ID_INFO), QLogger::InfoLevel);
    manager->addDestination("./logs/lastrun.log", QStringList(LOG_ID_ERR), QLogger::ErrorLevel);
    manager->addDestination("./logs/lastrun.log", QStringList(LOG_ID_WARN), QLogger::WarnLevel);

    // Redraw regiment if the regimentAbstract object is replaced
    QObject::connect(this, SIGNAL(regimentUpdated()), this, SLOT(updateRegiment()));
}

QRectF RegimentGraphics::boundingRect() const
{

}

void RegimentGraphics::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{

}

void RegimentGraphics::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    QLog_Info(LOG_ID_INFO, "X : " + QString::number(scenePos().x()) +
                           ", Y : " + QString::number(scenePos().y()));

    // Signal that the object has been moved by the mouse
    // This permits not to create infinite loop if we cast the signal
    // when the coordinates are changed
    emit(SIGNAL(regimentMoved()));

    QGraphicsItem::mouseMoveEvent(event);
}

void RegimentGraphics::updateRegiment()
{
    this->update();
}

RegimentAbstract RegimentGraphics::getRegiment() const
{
    return regiment;
}

void RegimentGraphics::setRegiment(const RegimentAbstract &value)
{
    regiment = value;
    emit(SIGNAL(regimentChanged()));
}

