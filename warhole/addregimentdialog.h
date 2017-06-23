#ifndef AddRegimentDialog_H
#define AddRegimentDialog_H

#include <QWidget>
#include <QDirModel>
#include <QFileSystemModel>
#include <QDebug>
#include <QMessageBox>
#include "defines.h"
#include <QStandardItemModel>
#include <game/model/modelfactory.h>
#include <game/option/optionmodel.h>
#include <game/regiment/regimentabstract.h>
#include <game/army/army.h>
#include <Utilities/QLogger/QLogger.h>
#include <Utilities/PdfExporter/pdfexporter.h>

#include <QDebug>

namespace Ui {
class AddRegimentDialog;
}

class AddRegimentDialog : public QDialog
{
    Q_OBJECT

public:
    AddRegimentDialog(QString armyRace, RegimentAbstract* r,QWidget *parent = 0);
    ~AddRegimentDialog();

    void updateTreeView(QString raceDir);

    void initAddRegimentDialog();
private slots:
    void loadRaceModels(const QString &raceDir);
    void on_treeViewExistingModels_clicked(const QModelIndex &index);
    void on_checkBoxChampion_toggled(bool checked);
    bool fillRegimentInfo();
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
    void evaluateMagicalObjectPoints();

    void on_spinBoxNB_valueChanged(int arg1);
    void on_spinBoxPtsBanner_valueChanged(const QString &arg1);
    void on_spinBoxPtsMusician_valueChanged(int arg1);
    void on_spinPoints_valueChanged(const int &arg1);

    void on_button_box_ok();
    void on_button_box_cancel();


private:
    static const QString LOG_ID_TRACE;
    static const QString LOG_ID_INFO;
    static const QString LOG_ID_WARN;
    static const QString LOG_ID_ERR;

    void setEnableChampionStats(bool checked);
    void clearRegimentDisplay();
    void updateRegModel();
    void loadRegimentInUI(const RegimentAbstract &r);
    void load(QString path);
    void enableChampionUI(bool checked);

    Ui::AddRegimentDialog *ui;
    QFileSystemModel *model;
    QString currentRace;
    ModelFactory fac;
    ModelAbstract* ma;
    RegimentAbstract regiment;
    RegimentAbstract *extReg;
    QStandardItemModel* options;
    QStandardItemModel* regOptions;
    QStandardItemModel* objects;
    QString currentSelectedPath;
    Army currentArmy;
    bool editing;
    bool armyFileLoading;
    QGraphicsScene *scene;
    QPixmap* image;

    static const QStringList OPTION_HEADER;
    static const QStringList OBJECT_HEADER;
    void closeEvent(QCloseEvent *event);
};

#endif // AddRegimentDialog_H
