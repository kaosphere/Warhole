#include "regimentgraphics.h"

using namespace QLogger;

const QString RegimentGraphics::LOG_ID_INFO = "RegimentGraphics_info";
const QString RegimentGraphics::LOG_ID_TRACE = "RegimentGraphics_trace";
const QString RegimentGraphics::LOG_ID_WARN = "RegimentGraphics_warm";
const QString RegimentGraphics::LOG_ID_ERR = "RegimentGraphics_err";

const int RegimentGraphics::DEFAULT_REGIMENT_WIDTH = 5;

RegimentGraphics::RegimentGraphics(QGraphicsItem *parent) : QGraphicsObject(parent)
{
    initRegimentGraphics();
}

RegimentGraphics::RegimentGraphics(const RegimentAbstract &r, QGraphicsItem *parent) :
    QGraphicsObject(parent)
{
    initRegimentGraphics();

    regiment = r;

    initModels();
}

RegimentGraphics::~RegimentGraphics()
{
    delete childrenPen;
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
    setFlag(ItemIsSelectable);

    // Set default regiment width
    regimentWidth = DEFAULT_REGIMENT_WIDTH;

    childrenPen = new QPen(QColor(0,20,40),3);
}

void RegimentGraphics::initModels()
{
    models.clear();
    int nb = regiment.computeTotalNb();
    QLinearGradient gradient(0,
                             ((nb/regimentWidth)+1)*regiment.getGroupsConst().first().getModel()->getSquareBaseL() * ONE_MILLIMETER,
                             regimentWidth*regiment.getGroupsConst().first().getModel()->getSquareBaseW() * ONE_MILLIMETER,
                             0);
    gradient.setColorAt(0, QColor::fromRgb(qRgba(6, 52, 69, 0)));
    gradient.setColorAt(1, QColor::fromRgb(qRgba(9, 85, 112, 0)));
    QBrush brush(gradient);

    for(int i=0; i < regiment.getGroups().size(); ++i)
    {
        // Add only rectangle for living models
        for(int j = 0; j < nb; ++j)
        {
            // Add a rectangle item for each model in the regiment
            // X position is the number of the model modulo the regiment width
            ModelGraphics* r = new ModelGraphics(((i*j)+j)%regimentWidth * regiment.getGroups().at(i).getModel()->getSquareBaseW() * ONE_MILLIMETER,
                                // Y position is the number of the model divided by regiment width
                                (((i*j)+j)/regimentWidth) * regiment.getGroups().at(i).getModel()->getSquareBaseL() * ONE_MILLIMETER,
                                regiment.getGroups().at(i).getModel()->getSquareBaseW() * ONE_MILLIMETER,
                                regiment.getGroups().at(i).getModel()->getSquareBaseL() * ONE_MILLIMETER,
                                regiment.getGroups().at(i).getModel()->getStats().getName(),
                                regiment.getGroups().at(i).getModel()->getImage(),
                                this);
            r->setBrush(brush);
            r->setPen(*childrenPen);
            r->setFlag(ItemStacksBehindParent);
            models.append(r);
        }
    }
}
int RegimentGraphics::getRegimentID() const
{
    return regimentID;
}

void RegimentGraphics::setRegimentID(int value)
{
    regimentID = value;
}


QRectF RegimentGraphics::boundingRect() const
{
    int nb = regiment.computeTotalNb();
    return QRect(0,
                 0,
                 regimentWidth*regiment.getGroupsConst().first().getModel()->getSquareBaseW() * ONE_MILLIMETER,
                 ((nb/regimentWidth)+1)*regiment.getGroupsConst().first().getModel()->getSquareBaseL() * ONE_MILLIMETER);
}

QPainterPath RegimentGraphics::shape() const
{
    QPainterPath path;

    for(int i=0; i < models.size(); ++i)
    {
        path.addRect(models.at(i)->boundingRect());
    }

    return path;
}

void RegimentGraphics::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    // Handle selection
    if(this->isSelected())
    {
        QBrush b(QColor::fromRgba(qRgba(255, 255, 255, 75)));
        painter->setBrush(b);
        painter->drawPath(shape());
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

