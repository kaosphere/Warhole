#ifndef ARMYWINDOW_H
#define ARMYWINDOW_H

#include <QWidget>
#include <QDirModel>
#include <QDebug>
#include <QMessageBox>
#include "defines.h"
#include <QStandardItemModel>
#include <model/modelfactory.h>
#include <option/optionmodel.h>
#include <regiment/regimentabstract.h>
#include <army/army.h>

#include <QDebug>

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
    
    void setEnableChampionStats(bool checked);
    void clearRegimentDisplay();
private slots:
    void on_comboBoxRace_currentIndexChanged(const QString &raceDir);
    void on_treeViewExistingModels_clicked(const QModelIndex &index);
    void on_checkBoxChampion_toggled(bool checked);
    void on_addGroupButton_clicked();
    void on_addRegButton_clicked();

private:
    Ui::ArmyWindow *ui;
    QDirModel *model;
    QStringList existingRaces;
    ModelFactory fac;
    ModelAbstract* ma;
    QStandardItemModel* options;
    QStandardItemModel* reg;
    QStandardItemModel* models;
    QList<RegimentAbstract*> regiments;
    QModelIndex selectedModel;
    QString currentSelectedPath;
    Army currentArmy;
};

#endif // ARMYWINDOW_H
