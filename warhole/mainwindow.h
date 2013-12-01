#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QObject>
#include <QtCore>
#include <QtWidgets>

#include "modelwindow.h"
#include "armywindow.h"
#include "gamewindow.h"

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

private:
    QWidget* s;
    QPushButton* p;

    ModelWindow* mod;
    ArmyWindow* arm;
    GameWindow* game;
};

#endif // MAINWINDOW_H
