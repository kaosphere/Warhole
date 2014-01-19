#ifndef ARMYWINDOW_H
#define ARMYWINDOW_H

#include <QWidget>
#include <QDirModel>
#include <QDebug>
#include <QMessageBox>
#include "defines.h"
#include <QStandardItemModel>

namespace Ui {
class ArmyWindow;
}

class ArmyWindow : public QWidget
{
    Q_OBJECT
    
public:
    explicit ArmyWindow(QWidget *parent = 0);
    ArmyWindow(QString fileName);
    ~ArmyWindow();
    
private slots:

    void on_comboBoxRace_currentIndexChanged(const QString &raceDir);

private:
    Ui::ArmyWindow *ui;
    QDirModel *model;
    QStringList existingRaces;
};

#endif // ARMYWINDOW_H
