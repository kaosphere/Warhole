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
#include "core/messagequeue.h"
#include "gameconfiguratordialog.h"
#include "connecttoserverdialog.h"
#include "core/commandManager/commandmanager.h"
#include "chatwidgetform.h"
#include "statsdisplayform.h"
#include "core/gamecontroller.h"
#include "Utilities/RandomIdGenerator/idgenerator.h"
#include "graphics/roundtemplategraphics.h"


namespace Ui {
class GameWindow;
}

class ClientInfo
{
public:
    QString ip;
    int port;
};

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

    void createNetworkInterface(NetworkType t, QString ip);
    virtual void closeEvent(QCloseEvent *);

public slots:
    void openArmyMenuClicked();
    void openArmyModelContextMenu(QPoint pos);
    void deployRegiment();
    void add6InchesRuler();
    void add12InchesRuler();
    void add18InchesRuler();
    void add24InchesRuler();
    void printSpecialMessage(QString state);
    void addRulerToScene(QString id, int l);
    void moveRuler(QString id, QPointF p, QTransform matrix);
    void addRoundTemplateToScene(QString id, int d);
    void moveTemplate(QString id, QPointF p);
    void removeRulerFromScene(QString id);

private slots:

    void on_actionHost_Game_triggered();
    void on_actionConnect_to_a_game_2_triggered();

    void on_actionExpTemplateSmall_triggered();

    void on_actionExpTemplateBig_triggered();

signals:
    void requestNewRuler(int l);
    void requestNewRoundTemplate(int d);

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

    ChatWidgetForm* cw;
    StatsDisplayForm* sd;

    void initGameWindow();

    QMap<QString, QGraphicsItem*> toolItemList;

    QList<RegimentGraphics*> regimentsGraphics;

    GameController controller;

    Army army;
};

#endif // GAMEWINDOW_H
