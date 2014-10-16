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

RegimentGraphics::RegimentGraphics(const RegimentAbstract &r, bool owned, QGraphicsItem *parent) :
    QGraphicsObject(parent)
{
    initialized = false;
    regiment = r;
    isOwnedByMe = owned;
    hasImage = true;

    initRegimentGraphics();

    initModels();

    initialized = true;
}

RegimentGraphics::~RegimentGraphics()
{
    delete childrenPen;
    for(int i=0; i < models.size(); ++i)
    {
        delete models[i];
    }
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
    
    childrenPen = new QPen(QColor(0,20,40),3);

    actionRemoveRegiment = new QAction(tr("Retirer"), this);
    connect(actionRemoveRegiment, SIGNAL(triggered()), this, SLOT(removeRegimentRequest()));
    actionRemoveDeads = new QAction(tr("Retirer des figurines mortes"), this);
    connect(actionRemoveDeads, SIGNAL(triggered()), this, SLOT(removeDeadRequest()));
    actionAddModels = new QAction(tr("Ajouter des figurines"), this);
    connect(actionAddModels, SIGNAL(triggered()), this, SLOT(addModelRequest()));
    actionChangeRegimentWidth = new QAction(tr("Changer la disposition"), this);
    connect(actionChangeRegimentWidth, SIGNAL(triggered()), this, SLOT(changeRegimentWidthRequest()));
    actionChangeRegInfo = new QAction(tr("Changer les infos"), this);
    connect(actionChangeRegInfo, SIGNAL(triggered()), this, SLOT(changeRegimentInfoRequest()));

    // Item will be enabled for drag and drop if owned only
    connect(this, SIGNAL(ownerChanged()), this, SLOT(updateOwnership()));
    emit ownerChanged();
}

void RegimentGraphics::initModels()
{
    models.clear();
    int nb = regiment.computeTotalNb();
    
    for(int i=0; i < regiment.getGroups().size(); ++i)
    {
        if(regiment.getGroups().at(i).getModel()->getImage().isNull())
        {
            hasImage = false;
        }
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
                                                 &(regiment.getGroups().at(i).getModel()->getImage()),
                                                 this);
            r->setBrush(childrenBrush);
            r->setPen(*childrenPen);
            r->setFlag(ItemStacksBehindParent);
            models.append(r);
        }
    }
}

void RegimentGraphics::updateChildrenPositions()
{
    for(int j = 0; j < models.size(); ++j)
    {
        // TODO, to adapt when regiment fusion added
        models[j]->setPosXY(j%regimentWidth * regiment.getGroups().first().getModel()->getSquareBaseW() * ONE_MILLIMETER,
                          (j/regimentWidth)* regiment.getGroups().first().getModel()->getSquareBaseL() * ONE_MILLIMETER);
        // Change bounding rect
        prepareGeometryChange();
    }
}

void RegimentGraphics::addModels(int nb)
{
    int currentNb = models.size();
    for(int i = currentNb; i < currentNb+nb; ++i)
    {
        // Add a rectangle item for each model in the regiment
        // X position is the number of the model modulo the regiment width
        ModelGraphics* r = new ModelGraphics(i%regimentWidth * regiment.getGroups().first().getModel()->getSquareBaseW() * ONE_MILLIMETER,
                                             // Y position is the number of the model divided by regiment width
                                             (i/regimentWidth) * regiment.getGroups().first().getModel()->getSquareBaseL() * ONE_MILLIMETER,
                                             regiment.getGroups().first().getModel()->getSquareBaseW() * ONE_MILLIMETER,
                                             regiment.getGroups().first().getModel()->getSquareBaseL() * ONE_MILLIMETER,
                                             regiment.getGroups().first().getModel()->getStats().getName(),
                                             &(regiment.getGroups().first().getModel()->getImage()),
                                             this);
        r->setBrush(childrenBrush);
        r->setPen(*childrenPen);
        r->setFlag(ItemStacksBehindParent);
        models.append(r);
    }
    // Add the number to the regiment
    regiment.getGroups().first().setNb(regiment.getGroups().first().getNb() + nb);
    prepareGeometryChange();
}

void RegimentGraphics::updateChildrenBrushes()
{
    for(int j = 0; j < models.size(); ++j)
    {
        models[j]->setBrush(childrenBrush);
    }
}


QString RegimentGraphics::getRegimentID() const
{
    return regimentID;
}

void RegimentGraphics::setRegimentID(QString value)
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
    
    // Display graphics overlay, depending on ownership
    if(!isOwnedByMe && hasImage)
    {
        QBrush b(QColor::fromRgba(qRgba(255, 0, 0, 30)));
        painter->setBrush(b);
        painter->drawPath(shape());
    }

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
    
    // Signal that the object has been moved by the mouse
    // This permits not to create infinite loop if we cast the signal
    // when the coordinates are changed

    static int cnt = 0;
    if(++cnt % 16)
    {
        cnt = 0;
        emit regimentMoved(regimentID, pos(), transform());
    }
    
    QGraphicsItem::mouseMoveEvent(event);
}

void RegimentGraphics::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    emit regimentMoved(regimentID, pos(), transform());
    QGraphicsItem::mouseReleaseEvent(event);
}

void RegimentGraphics::updateOwnership()
{
    QBrush* brush;
    int nb = regiment.computeTotalNb();
    // set movable flag so that an item not owned cannot be moved
    if(isOwnedByMe)
    {
        setFlag(ItemIsMovable);
        setFlag(ItemIsSelectable);

        QLinearGradient gradient(0,
                                 ((nb/regimentWidth)+1)*regiment.getGroupsConst().first().getModel()->getSquareBaseL() * ONE_MILLIMETER,
                                 regimentWidth*regiment.getGroupsConst().first().getModel()->getSquareBaseW() * ONE_MILLIMETER,
                                 0);
        gradient.setColorAt(0, QColor::fromRgb(qRgba(6, 52, 69, 0)));
        gradient.setColorAt(1, QColor::fromRgb(qRgba(9, 85, 112, 0)));
        brush = new QBrush(gradient);
    }
    else
    {
        setFlag(ItemIsMovable, false);
        setFlag(ItemIsSelectable, false);

        QLinearGradient gradient(0,
                                 ((nb/regimentWidth)+1)*regiment.getGroupsConst().first().getModel()->getSquareBaseL() * ONE_MILLIMETER,
                                 regimentWidth*regiment.getGroupsConst().first().getModel()->getSquareBaseW() * ONE_MILLIMETER,
                                 0);
        gradient.setColorAt(0, QColor::fromRgb(qRgba(69, 52, 6, 0)));
        gradient.setColorAt(1, QColor::fromRgb(qRgba(112, 85, 9, 0)));
        brush = new QBrush(gradient);
    }

    childrenBrush = *brush;

    if(initialized) updateChildrenBrushes();
}

void RegimentGraphics::removeRegimentRequest()
{
    emit removeRegimentRequest(regimentID);
}

void RegimentGraphics::removeDeadRequest()
{
    int nb = 0;
    GetIntDialog d(tr("Nombre de morts"));
    d.setModal(true);
    d.setNb(&nb);
    if(d.exec())
    {
        // If there is more deads than models in the regiment, remove the regiment
        if(regiment.computeTotalNb() > nb)
        {
            emit removeDeadsRequest(regimentID, nb);
        }
        else
        {
            emit removeRegimentRequest(regimentID);
        }
    }
}

void RegimentGraphics::changeRegimentWidthRequest()
{
    int nb = 0;
    GetIntDialog d(tr("Largeur du régiment"));
    d.setModal(true);
    d.setNb(&nb);
    if(d.exec())
    {
        emit changeWidthRequest(regimentID, nb);
    }
}

void RegimentGraphics::addModelRequest()
{
    int nb = 0;
    GetIntDialog d(tr("Nombre de figurines"));
    d.setModal(true);
    d.setNb(&nb);
    if(d.exec())
    {
        emit addModelRequest(regimentID, nb);
    }
}

void RegimentGraphics::changeRegimentInfoRequest()
{
    emit changeRegimentInfoRequest(regimentID, regiment);
}

void RegimentGraphics::contextMenuEvent(QGraphicsSceneContextMenuEvent *event)
{
    QMenu *menu = new QMenu;
    menu->addAction(actionRemoveRegiment);
    menu->addAction(actionChangeRegimentWidth);
    menu->addAction(actionRemoveDeads);
    menu->addAction(actionAddModels);
    menu->addAction(actionChangeRegInfo);
    menu->popup(event->screenPos());
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
    prepareGeometryChange();
}

bool RegimentGraphics::getIsOwnedByMe() const
{
    return isOwnedByMe;
}

void RegimentGraphics::setIsOwnedByMe(bool value)
{
    isOwnedByMe = value;

    emit ownerChanged();
}

void RegimentGraphics::removeDeads(int nb)
{
    regiment.getGroups().first().setCasualties(
                regiment.getGroups().first().getCasualties() + nb);
    for(int i=0; i< nb; ++i)
    {
        ModelGraphics* m = models.takeLast();
        // Remove object from the parent
        m->setParentItem(NULL);
        // Remove object from the scene
        scene()->removeItem(m);
        delete m;
    }
}

QString RegimentGraphics::getOwner() const
{
    return owner;
}

void RegimentGraphics::setOwner(const QString &value)
{
    owner = value;
}

int RegimentGraphics::getRegimentWidth() const
{
    return regimentWidth;
}

void RegimentGraphics::setRegimentWidth(int value)
{
    if(value > regiment.computeTotalNb())
    {
        regimentWidth = regiment.computeTotalNb();
    }
    else
    {
        regimentWidth = value;
    }
    updateChildrenPositions();
}

