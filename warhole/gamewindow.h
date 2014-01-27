#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsItem>
#include <QGraphicsEllipseItem>
#include <QTransform>
#include <QWheelEvent>
#include <QGraphicsSceneWheelEvent>
#include <QDebug>
#include <QMimeData>
#include <QDrag>
#include <QPixmap>
#include <QException>

#include "game/testgi.h"
#include "game/fieldlimits.h"


namespace Ui {
class GameWindow;
}

class GameWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit GameWindow(QWidget *parent = 0);
    ~GameWindow();
    void wheelEvent(QGraphicsSceneWheelEvent *event);
    void mousePressEvent(QGraphicsSceneWheelEvent *event);
    bool eventFilter(QObject *object, QEvent *event);
    void setSceneZoomFactor(double zoomFactor);
    void resetZoom();
    
private slots:

private:
    Ui::GameWindow *ui;
    QGraphicsScene scene;
    BackGroundItem* back;
    QBrush* backGroundBrush;
    double scaleFactor;
    QPixmap background;
    testGI* regiment;

    const double maxScaleFactor = 2;
    const double minScaleFactor = 0.2;
};

#endif // GAMEWINDOW_H
