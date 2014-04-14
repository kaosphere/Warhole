#include "gamewindow.h"
#include "ui_gamewindow.h"

const double GameWindow::maxScaleFactor = 2;
const double GameWindow::minScaleFactor = 0.2;

GameWindow::GameWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::GameWindow)
{
    ui->setupUi(this);

    //ui parameters
    ui->graphicsView->setScene(&scene);
    ui->graphicsView->installEventFilter(this);
    ui->graphicsView->setDragMode(QGraphicsView::ScrollHandDrag);

    //zoom initialization
    scaleFactor = 1.0;
    scene.installEventFilter(this);

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
    scene.addItem(regiment);
}

void GameWindow::setSceneZoomFactor(double zoomFactor)
{
    QMatrix mat = ui->graphicsView->matrix();
    ui->graphicsView->setMatrix(QMatrix(zoomFactor, mat.m12(), mat.m21(), zoomFactor, mat.dx(), mat.dy()));
}

void GameWindow::resetZoom()
{
    scaleFactor = 1;
    QMatrix mat = ui->graphicsView->matrix();
    ui->graphicsView->setMatrix(QMatrix(scaleFactor, mat.m12(), mat.m21(), scaleFactor, mat.dx(), mat.dy()));
}

//zooming/dezooming with the mouse wheel
void GameWindow::wheelEvent(QGraphicsSceneWheelEvent *event)
{
    const int degrees = event->delta() / 8;
    int steps = degrees / 15;
    QMatrix matrix;

    if(steps>0 && scaleFactor<maxScaleFactor)
    {
        scaleFactor*=1.2;
    }
    else if(steps<0 && scaleFactor>minScaleFactor)
    {
        scaleFactor/=1.2;
    }
    ui->graphicsView->setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
    QMatrix mat = ui->graphicsView->matrix();
    ui->graphicsView->setMatrix(QMatrix(scaleFactor, mat.m12(), mat.m21(), scaleFactor, mat.dx(), mat.dy()));
}

//event filter to prevent wheel event to scroll instead of zooming
bool GameWindow::eventFilter(QObject *object, QEvent *event)
{
   if(event->type() == QEvent::GraphicsSceneWheel)
   {
      event->setAccepted(true);
      //qDebug("Mouse wheel detected !");
      QGraphicsSceneWheelEvent *whl = dynamic_cast<QGraphicsSceneWheelEvent *>(event);
      if(whl!=0)
      {
         wheelEvent(whl);
      }
      return true;
    }
    else
    {
       // standard event processing
       return QObject::eventFilter(object, event);
    }
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

GameWindow::~GameWindow()
{
    delete ui;
}
