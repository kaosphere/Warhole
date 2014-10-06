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
#include "graphics/rulergraphics.h"
#include "chatwidget.h"
#include "core/network/networkthread.h"
#include "core/messagequeue.h"
#include "gameconfiguratordialog.h"

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
    void addRulerToScene(int l);

    void createNetworkInterface(NetworkType t);
public slots:
    void openArmyMenuClicked();
    void openArmyModelContextMenu(QPoint pos);
    void deployRegiment();
    void add6InchesRuler();
    void add12InchesRuler();
    void add18InchesRuler();
    void add24InchesRuler();
    void printNetworkState(QString state);

private slots:

    void on_actionHost_Game_triggered();

    void on_actionConnect_to_a_game_2_triggered();

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

    ChatWidget* cw;

    void initGameWindow();

    QList<RegimentGraphics*> regimentsGraphics;

    NetworkInterface* netInterface;
    MessageQueue inQueue;
    MessageQueue outQueue;

    Game* game;
    Army army;
};

#endif // GAMEWINDOW_H
