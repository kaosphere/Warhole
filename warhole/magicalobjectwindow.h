#ifndef MAGICALOBJECTWINDOW_H
#define MAGICALOBJECTWINDOW_H

#include <QDialog>

namespace Ui {
class MagicalObjectWindow;
}

class MagicalObjectWindow : public QDialog
{
    Q_OBJECT

public:
    explicit MagicalObjectWindow(QWidget *parent = 0);
    ~MagicalObjectWindow();

private:
    Ui::MagicalObjectWindow *ui;
};

#endif // MAGICALOBJECTWINDOW_H
