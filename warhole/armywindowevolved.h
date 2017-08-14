#ifndef ARMYWINDOWEVOLVED_H
#define ARMYWINDOWEVOLVED_H

#include <QWidget>
#include "addregimentdialog.h"

#define ITEM_ID_COLUMN 4

namespace Ui {
class ArmyWindowEvolved;
}

class ArmyWindowEvolved : public QWidget
{
    Q_OBJECT

public:
    explicit ArmyWindowEvolved(QWidget *parent = 0);
    ArmyWindowEvolved(QString path, QWidget *parent = 0);
    ~ArmyWindowEvolved();

public slots:


protected:
    void initArmyWindow();
    void appendRegimentToTreeViewCategory(int id, RegimentAbstract r, QStandardItem *category);
    void load(QString path);

private slots:
    void on_toolButtonAdd_clicked();
    void on_toolButtonPdf_clicked();
    void updateGlobalArmyPoints();
    void refreshArmyList();
    void clearAllCategories();
    void on_treeView_customContextMenuRequested(const QPoint &pos);
    void deleteRegiment();
    void duplicateRegiment();
    void editRegiment();
    void on_toolButtonSave_clicked();
    void on_toolButton_Load_clicked();

private:
    static const QString LOG_ID_TRACE;
    static const QString LOG_ID_INFO;
    static const QString LOG_ID_WARN;
    static const QString LOG_ID_ERR;

    static const QStringList OPTION_HEADER;

    Ui::ArmyWindowEvolved *ui;
    QString currentSelectedPath;
    AddRegimentDialog* regDialog;
    Army currentArmy;
    QStandardItemModel* armyModel;

    QStandardItem* baseItem;
    QStandardItem* specialItem;
    QStandardItem* rareItem;
    QStandardItem* characterItem;

    QAction* deleteRegimentAction;
    QAction* duplicateRegimentAction;
    QAction* editRegimentAction;

    int currentSelectedRegimentId;
};

#endif // ARMYWINDOWEVOLVED_H
