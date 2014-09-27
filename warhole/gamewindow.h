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
#include "graphics/regimentgraphics.h"


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

    void loadArmy();
    void updateArmyList();

public slots:
    void openArmyMenuClicked();
    void openArmyModelContextMenu(QPoint pos);
    void deployRegiment();

private slots:

private:
    static const QString LOG_ID_TRACE;
    static const QString LOG_ID_INFO;
    static const QString LOG_ID_WARN;
    static const QString LOG_ID_ERR;

    Ui::GameWindow *ui;
    QGraphicsScene scene;
    EnhancedGraphicsView view;
    QStandardItemModel* armyModel;

    BackGroundItem* back;
    QBrush* backGroundBrush;
    QPixmap background;

    QAction* actionDeploy;
    QModelIndex indexArmy;

    void initGameWindow();

    QList<RegimentGraphics*> regimentsGraphics;

    Game game;
    Army army;
};

#endif // GAMEWINDOW_H
