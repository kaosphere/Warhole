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
#include <QHBoxLayout>

#include "graphics/testgi.h"
#include "graphics/fieldlimits.h"
#include "graphics/enhancedgraphicsview.h"
#include "game/game.h"


namespace Ui {
class GameWindow;
}

class GameWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit GameWindow(QWidget *parent = 0);
    ~GameWindow();
    
    bool addPlayerToGame(Player p);
    bool addArmyToPlayer(Army a, QString playerName);

public slots:

private slots:

private:
    static const QString LOG_ID_TRACE;
    static const QString LOG_ID_INFO;
    static const QString LOG_ID_WARN;
    static const QString LOG_ID_ERR;

    Ui::GameWindow *ui;
    QGraphicsScene scene;
    EnhancedGraphicsView view;

    BackGroundItem* back;
    QBrush* backGroundBrush;
    QPixmap background;

    testGI* regiment;
    testGI* regiment2;
    void initGameWindow();

    Game game;
};

#endif // GAMEWINDOW_H
