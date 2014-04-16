#ifndef ARMYWINDOW_H
#define ARMYWINDOW_H

#include <QWidget>
#include <QDirModel>
#include <QFileSystemModel>
#include <QDebug>
#include <QMessageBox>
#include "defines.h"
#include <QStandardItemModel>
#include <model/modelfactory.h>
#include <option/optionmodel.h>
#include <regiment/regimentabstract.h>
#include <army/army.h>
#include <Utilities/QLogger/QLogger.h>
#include <Utilities/PdfExporter/pdfexporter.h>

#include <QDebug>

namespace Ui {
class ArmyWindow;
}

class ArmyWindow : public QWidget
{
    Q_OBJECT
    
public:
    explicit ArmyWindow(QWidget *parent = 0);
    ArmyWindow(QString fileName, QWidget *parent = 0);
    ~ArmyWindow();

private slots:
    void on_comboBoxRace_currentIndexChanged(const QString &raceDir);
    void on_treeViewExistingModels_clicked(const QModelIndex &index);
    void on_checkBoxChampion_toggled(bool checked);
    void on_addRegButton_clicked();
    void on_removeRegButton_clicked();
    void on_editRegButton_clicked();
    void on_checkBoxBanner_toggled(bool checked);
    void on_checkBoxMusician_toggled(bool checked);
    void on_pushButtonDuplicate_clicked();
    void on_pushButtonQuit_clicked();
    void on_pushButtonSave_clicked();
    void on_pushButtonLoad_clicked();
    void on_pushButtonExport_clicked();
    void evaluateOptionsPoints();
    void evaluateRegimentOptionsPoints();
    void updateRegimentPoints();

    void on_spinBoxNB_valueChanged(int arg1);
    void on_spinBoxPtsBanner_valueChanged(const QString &arg1);
    void on_spinBoxPtsMusician_valueChanged(int arg1);
    void on_spinPoints_valueChanged(const int &arg1);

private:
    static const QString LOG_ID_TRACE;
    static const QString LOG_ID_INFO;
    static const QString LOG_ID_WARN;
    static const QString LOG_ID_ERR;

    void setEnableChampionStats(bool checked);
    void clearRegimentDisplay();
    void updateRegModel();
    void updateGlobalArmyPoints();
    void loadRegimentInUI(RegimentAbstract &r);
    void load(QString path);
    void enableChampionUI(bool checked);

    bool changeRace;
    Ui::ArmyWindow *ui;
    QFileSystemModel *model;
    QStringList existingRaces;
    ModelFactory fac;
    ModelAbstract* ma;
    RegimentAbstract regiment;
    QStandardItemModel* options;
    QStandardItemModel* regOptions;
    QStandardItemModel* reg;
    QString currentSelectedPath;
    Army currentArmy;
    bool editing;

    static const QStringList OPTION_HEADER;
};

#endif // ARMYWINDOW_H
