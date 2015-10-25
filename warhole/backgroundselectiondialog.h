#ifndef BACKGROUNDSELECTIONDIALOG_H
#define BACKGROUNDSELECTIONDIALOG_H

#include <QDialog>
#include <QStandardItemModel>

namespace Ui {
class backGroundSelectionDialog;
}

class backGroundSelectionDialog : public QDialog
{
    Q_OBJECT

public:
    explicit backGroundSelectionDialog(QWidget *parent = 0);
    ~backGroundSelectionDialog();

    int *getChoice() const;
    void setChoice(int *value);

    virtual void accept();

private:
    Ui::backGroundSelectionDialog *ui;
    QStandardItemModel* model;
    int *choice;
};

#endif // BACKGROUNDSELECTIONDIALOG_H
