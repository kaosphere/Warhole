#include "regimentgraphics.h"

using namespace QLogger;

const QString RegimentGraphics::LOG_ID_INFO = "RegimentGraphics_info";
const QString RegimentGraphics::LOG_ID_TRACE = "RegimentGraphics_trace";
const QString RegimentGraphics::LOG_ID_WARN = "RegimentGraphics_warm";
const QString RegimentGraphics::LOG_ID_ERR = "RegimentGraphics_err";

const int RegimentGraphics::DEFAULT_REGIMENT_WIDTH = 5;

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

    // Set default regiment width
    regimentWidth = DEFAULT_REGIMENT_WIDTH;
}

void RegimentGraphics::initModels()
{
    models.clear();
    int k = 0;
    for(int i=0; i < regiment.getGroups().size(); ++i)
    {
        // Add only rectangle for living models
        int nb = regiment.getGroups()[i].getNb() - regiment.getGroups()[i].getCasualties();
        for(int j = 0; j < i; ++j)
        {
            // Add a rectangle item for each model in the regiment
            QGraphicsRectItem* r = new QGraphicsRectItem(k * 50,
                                0,
                                regiment.getGroups()[i].getModel()->getSquareBaseW(),
                                regiment.getGroups()[i].getModel()->getSquareBaseL(),
                                this);
            models[k++] = r;
        }
    }
}

QRectF RegimentGraphics::boundingRect() const
{

}

void RegimentGraphics::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{


    // Paint all rectangles
    QHash<int, QGraphicsRectItem>::const_iterator i = models.constBegin();
     while (i != models.constEnd()) {
         i.value().paint();
     }
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

