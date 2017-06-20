#ifndef ARMYWINDOWEVOLVED_H
#define ARMYWINDOWEVOLVED_H

#include <QWidget>

namespace Ui {
class ArmyWindowEvolved;
}

class ArmyWindowEvolved : public QWidget
{
    Q_OBJECT

public:
    explicit ArmyWindowEvolved(QWidget *parent = 0);
    ~ArmyWindowEvolved();

    void initArmyWindow();

private:
    static const QString LOG_ID_TRACE;
    static const QString LOG_ID_INFO;
    static const QString LOG_ID_WARN;
    static const QString LOG_ID_ERR;

    Ui::ArmyWindowEvolved *ui;
};

#endif // ARMYWINDOWEVOLVED_H
