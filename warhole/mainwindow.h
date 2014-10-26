#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QObject>
#include <QtCore>
#include <QtWidgets>

#include "modelwindow.h"
#include "armywindow.h"
#include "gamewindow.h"
#include "magicalobjectwindow.h"
#include "terrainwindow.h"
#include "Utilities/QLogger/QLogger.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
   void openModelWindow();
   void openEditModelWindow();
   void openArmyWindow();
   void openEditArmyWindow();
   void openGameWindow();
   void openMagicalObjectWindow();
   void openTerrainWindow();
   void updateLogOutput(QString message);

private:
    Ui::MainWindow *ui;
    QWidget* s;
    QPushButton* p;

    ModelWindow* mod;
    ArmyWindow* arm;
    GameWindow* game;
    MagicalObjectWindow* obj;
    TerrainWindow *ter;
};

#endif // MAINWINDOW_H
