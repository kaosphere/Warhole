#ifndef ARMYWINDOWEVOLVED_H
#define ARMYWINDOWEVOLVED_H

#include <QWidget>
#include "addregimentdialog.h"

namespace Ui {
class ArmyWindowEvolved;
}

class ArmyWindowEvolved : public QWidget
{
    Q_OBJECT

public:
    explicit ArmyWindowEvolved(QWidget *parent = 0);
    ~ArmyWindowEvolved();

protected:
    void initArmyWindow();
    void appendRegimentToTreeViewCategory(RegimentAbstract *r, QStandardItem *category);

private slots:
    void on_toolButtonAdd_clicked();

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
};

#endif // ARMYWINDOWEVOLVED_H
