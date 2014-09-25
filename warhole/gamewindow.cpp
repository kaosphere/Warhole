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
    initGameWindow();
}

void GameWindow::initGameWindow()
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
        QLog_Error(LOG_ID_ERR, "GAMEWINDOW : Can't load background image");
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
}

GameWindow::~GameWindow()
{
    delete ui;
}
