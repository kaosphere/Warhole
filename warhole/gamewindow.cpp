#include "gamewindow.h"
#include "ui_gamewindow.h"

const QString GameWindow::LOG_ID_INFO = "testGI_info";
const QString GameWindow::LOG_ID_TRACE = "testGI_trace";
const QString GameWindow::LOG_ID_WARN = "testGI_warm";
const QString GameWindow::LOG_ID_ERR = "testGI_err";

using namespace QLogger;

GameWindow::GameWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::GameWindow)
{
    ui->setupUi(this);

    QLoggerManager *manager = QLoggerManager::getInstance();
    manager->addDestination("./logs/lastrun.log", QStringList(LOG_ID_TRACE), QLogger::TraceLevel);
    manager->addDestination("./logs/lastrun.log", QStringList(LOG_ID_INFO), QLogger::InfoLevel);
    manager->addDestination("./logs/lastrun.log", QStringList(LOG_ID_ERR), QLogger::ErrorLevel);
    manager->addDestination("./logs/lastrun.log", QStringList(LOG_ID_WARN), QLogger::WarnLevel);

    //ui parameters
    view.setScene(&scene);

    ui->horizontalLayout->addWidget(&view);

    //background of the game (To be removed afterwards)
    if(!background.load("C:/Users/Psycko/Documents/GitHub/Warhole/warhole/ressources/floor_grass5.jpg"))
    {
        qDebug()<<"GAMEWINDOW : Can't load background image";
    }

    backGroundBrush = new QBrush(QColor(51,102,0));
    backGroundBrush = new QBrush(background);
    scene.setBackgroundBrush(*backGroundBrush);

    back = new BackGroundItem(5400,2700);
    scene.addItem(back);
    regiment = new testGI();
    regiment2 = new testGI();
    scene.addItem(regiment2);
    scene.addItem(regiment);
    QObject::connect(regiment, SIGNAL(objectCoordinateChanged()), this, SLOT(graphicalObjectCoordinateUpdate()));
    QObject::connect(regiment2, SIGNAL(objectCoordinateChanged()), this, SLOT(graphicalObjectCoordinateUpdate()));
}

//drag and drop on the scene
void GameWindow::mousePressEvent(QGraphicsSceneWheelEvent *event)
{
    QMimeData *data = new QMimeData;
    //data->setColor(Qt::green);

    QDrag *drag = new QDrag(event->widget());
    drag->setMimeData(data);
    drag->start();
}

void GameWindow::graphicalObjectCoordinateUpdate()
{
    QLog_Info(LOG_ID_INFO, "X : " + QString::number(qobject_cast<QGraphicsObject*>(sender())->scenePos().x()) +
                           ", Y : " + QString::number(qobject_cast<QGraphicsObject*>(sender())->scenePos().y()));
}

GameWindow::~GameWindow()
{
    delete ui;
}
