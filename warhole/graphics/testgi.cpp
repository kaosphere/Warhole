#include "testgi.h"

const QString testGI::LOG_ID_INFO = "testGI_info";
const QString testGI::LOG_ID_TRACE = "testGI_trace";
const QString testGI::LOG_ID_WARN = "testGI_warm";
const QString testGI::LOG_ID_ERR = "testGI_err";

using namespace QLogger;

testGI::testGI()
{
    QLoggerManager *manager = QLoggerManager::getInstance();
    manager->addDestination("./logs/lastrun.log", QStringList(LOG_ID_TRACE), QLogger::TraceLevel);
    manager->addDestination("./logs/lastrun.log", QStringList(LOG_ID_INFO), QLogger::InfoLevel);
    manager->addDestination("./logs/lastrun.log", QStringList(LOG_ID_ERR), QLogger::ErrorLevel);
    manager->addDestination("./logs/lastrun.log", QStringList(LOG_ID_WARN), QLogger::WarnLevel);

    pressed = false;
    h = 60;
    w = 60;
    nbRectW = 5;
    nbRectH = 4;
    setFlag(ItemIsMovable);

    deads=7;

    QPixmap* logoTmp = new QPixmap();
    if(!logoTmp->load("..\\..\\pix\\orcbanner.png"))
    {
        QLog_Error(LOG_ID_ERR, "testGI : Can't load logo image");
    }
    logo = logoTmp->scaled((nbRectW*w)/2,
                           (nbRectH*h)/2);

    QPixmap* deadTmp = new QPixmap();
    if(!deadTmp->load("..\\..\\pix\\whiteskull.png"))
    {
        QLog_Error(LOG_ID_ERR, "testGI : Can't load dead image");
    }
    dead = deadTmp->scaled(w, h);

    QObject::connect((QObject*)this, SIGNAL(xChanged()), (QObject*)this, SIGNAL(objectCoordinateChanged()));
    QObject::connect((QObject*)this, SIGNAL(yChanged()), (QObject*)this, SIGNAL(objectCoordinateChanged()));
    QObject::connect((QObject*)this, SIGNAL(rotationChanged()), (QObject*)this, SIGNAL(objectCoordinateChanged()));

}

testGI::~testGI()
{

}


QRectF testGI::boundingRect() const
{
    return QRectF(0,
                  0,
                  (nbRectW*w),
                  (nbRectH*h));
}

void testGI::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QRectF rec = boundingRect();
    QLinearGradient gradient(0, nbRectH*h, nbRectW*w, 0);
    gradient.setColorAt(0, QColor::fromRgb(qRgba(6, 52, 69, 0)));
    gradient.setColorAt(1, QColor::fromRgb(qRgba(9, 85, 112, 0)));

    QBrush brush(gradient);
    QPen pen(QColor(0,20,40),3);


    painter->setBackgroundMode(Qt::TransparentMode);
    painter->fillRect(rec,brush);
    painter->drawPixmap((nbRectW*w)/2-(nbRectW*w/4),
                        (nbRectH*h)/2-(nbRectH*h/4),
                        logo.width(),
                        logo.height(),
                        logo);
    painter->setPen(pen);
    painter->drawRect(rec);

    for(int i=0;i<nbRectH;i++)
    {
        for(int j=0;j<nbRectW;j++)
        {
            if(((i*nbRectW)+j)>=((nbRectH*nbRectW)-deads))
            {
                painter->fillRect(
                            QRect((j*w),(i*h),w,h),
                            QColor(50,50,50,100));
                painter->drawPixmap((j*w),(i*h),w,h,dead);
            }
            painter->drawRect((j*w),(i*h),w,h);
        }
    }


    static const QPointF points[3] = {
        QPointF((nbRectW*w)/2 - (nbRectW*w)/8, 0),
        QPointF((nbRectW*w)/2 + (nbRectW*w)/8, 0),
        QPointF(((nbRectW*w)/2), 30)
        };
    painter->drawPolygon(points,3);
}

void testGI::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    pressed = true;
    update();
    QGraphicsItem::mousePressEvent(event);
}

void testGI::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    pressed = false;
    update();
    QGraphicsItem::mouseReleaseEvent(event);
}

int testGI::getW() const
{
    return w;
}

void testGI::setW(int value)
{
    w = value;
}

int testGI::getNbRectH() const
{
    return nbRectH;
}

int testGI::getNbRectW() const
{
    return nbRectW;
}

void testGI::setNbRectW(int value)
{
    nbRectW = value;
}

void testGI::setNbRectH(int value)
{
    nbRectH = value;
}

int testGI::getH() const
{
    return h;
}

void testGI::setH(int value)
{
    h = value;
}


int testGI::getDeads() const
{
    return deads;
}

void testGI::setDeads(int value)
{
    deads = value;
}



