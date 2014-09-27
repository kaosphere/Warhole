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

    initModels();
}

RegimentGraphics::~RegimentGraphics()
{

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

   // Allow the item to be dragged and dropped
    setFlag(ItemIsMovable);

    // Set default regiment width
    regimentWidth = DEFAULT_REGIMENT_WIDTH;
}

void RegimentGraphics::initModels()
{
    models.clear();
    for(int i=0; i < regiment.getGroups().size(); ++i)
    {
        // Add only rectangle for living models
        int nb = regiment.getGroups().at(i).getNb() - regiment.getGroups().at(i).getCasualties();
        for(int j = 0; j < nb; ++j)
        {
            // Add a rectangle item for each model in the regiment
            ModelGraphics* r = new ModelGraphics(((i*j)+j) * 50,
                                0,
                                regiment.getGroups().at(i).getModel()->getSquareBaseW(),
                                regiment.getGroups().at(i).getModel()->getSquareBaseL(),
                                regiment.getGroups().at(i).getModel()->getStats().getName(),
                                this);
            models.append(r);
        }
    }
}

QRectF RegimentGraphics::boundingRect() const
{
    // Dumb
    return QRect(0,80,80,80);
}

void RegimentGraphics::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    // Paint all rectangles
    // Paint all models
    QList<ModelGraphics*>::iterator i;
     for (i = models.begin(); i != models.end(); ++i)
         (*i)->paint(painter, option, widget);
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

