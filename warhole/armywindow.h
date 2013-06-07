#ifndef ARMYWINDOW_H
#define ARMYWINDOW_H

#include <QWidget>

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
    
private:
    Ui::ArmyWindow *ui;
};

#endif // ARMYWINDOW_H
