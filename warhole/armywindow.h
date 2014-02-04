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
#include <unit/unitabstract.h>

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
    
private slots:

    void on_comboBoxRace_currentIndexChanged(const QString &raceDir);


    void on_treeViewExistingModels_clicked(const QModelIndex &index);

    void on_pushButton_clicked();

private:
    Ui::ArmyWindow *ui;
    QDirModel *model;
    QStringList existingRaces;
    ModelFactory fac;
    ModelAbstract* ma;
    QStandardItemModel* options;
    QGraphicsScene* scene;
    QStandardItemModel* reg;
    QList<UnitAbstract*> regiments;
    QModelIndex selectedModel;
};

#endif // ARMYWINDOW_H
