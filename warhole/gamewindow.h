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
#include "getintdialog.h"
#include "graphics/terraingraphics.h"
#include "graphics/blowtemplategraphics.h"
#include "graphics/textgraphics.h"


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


    void getGlobalInfo(QDataStream &stream);
    void setGlobalInfo(QDataStream &stream);

    void clearAllMaps();
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
    void removeRoundTemplate(QString id);
    void removeRulerFromScene(QString id);
    void addRegimentToGameScene(QString id, QString owner, RegimentAbstract r);
    void moveRegiment(QString id, QPointF p, QTransform matrix);
    void removeRegiment(QString id);
    void removeDeadsFromRegiment(QString id, int nb);
    void changeRegimentWidth(QString id, int w);
    void addModelToRegiment(QString id, int nb);
    void changeRegInfo(QString id, RegimentAbstract r);
    void packGameDataForGlobalUpdate(QString sender);
    void loadGlobalInfoUpdate(QByteArray info);
    void placeTerrainRequest();
    void addNewTerrainToScene(QString id, Terrain t);
    void removeTerrain(QString id);
    void lockTerrain(QString id, bool l);
    void moveTerrain(QString id, QPointF p, QTransform matrix);
    void addNewBlowTemplateToScene(QString id);
    void moveBlowTemplate(QString id, QPointF p, QTransform matrix);
    void removeBlowTemplate(QString id);
    void editText();
    void addNewTextToScene(QString id, QString text);
    void moveText(QString i, QString text, QPointF p, QTransform matrix);
    void removeText(QString i);

private slots:

    void on_actionHost_Game_triggered();
    void on_actionConnect_to_a_game_2_triggered();
    void on_actionExpTemplateSmall_triggered();
    void on_actionExpTemplateBig_triggered();
    void on_actionSave_Game_triggered();
    void on_actionCharger_une_partie_triggered();
    void on_treeViewTerrains_customContextMenuRequested(const QPoint &pos);
    void rotateView();
    void requestNewText();

signals:
    void requestNewRuler(int l);
    void requestNewRoundTemplate(int d);
    void newRegimentRequest(QString, RegimentAbstract);
    void sendGlobalInfoUpdate(QString, QByteArray);
    void requestNewTerrain(Terrain);
    void requestNewText(QString);

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

    QMap<QString, RulerGraphics*> rulerList;
    QMap<QString, RoundTemplateGraphics*> roundTemplateList;
    QMap<QString, BlowTemplateGraphics*> blowTemplateList;
    QMap<QString, RegimentGraphics*> regimentMap;
    QMap<QString, TerrainGraphics*> terrainMap;
    QMap<QString, TextGraphics*> textMap;

    GameController controller;

    Army army;

    QFileSystemModel* terrainsModel;
    QModelIndex indexTerrain;
    QString currentSelectedTerrainPath;
    QAction* placeTerrain;
};

#endif // GAMEWINDOW_H
