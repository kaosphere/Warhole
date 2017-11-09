#ifndef GAMECONFIGURATORDIALOG_H
#define GAMECONFIGURATORDIALOG_H

#include <QDialog>
#include "game/game.h"

namespace Ui {
class GameConfiguratorDialog;
}

class GameConfiguratorDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit GameConfiguratorDialog(QWidget *parent = 0);
    ~GameConfiguratorDialog();
    
    Game *getG() const;
    void setG(Game *value);

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::GameConfiguratorDialog *ui;
    Game* g;
    bool validConditions;
};

#endif // GAMECONFIGURATORDIALOG_H
