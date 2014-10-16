#ifndef GETINTDIALOG_H
#define GETINTDIALOG_H

#include <QDialog>

namespace Ui {
class GetIntDialog;
}

class GetIntDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit GetIntDialog(QString title, QWidget *parent = 0);
    ~GetIntDialog();
    
    void setNb(int *value);

    void accept();
private:
    Ui::GetIntDialog *ui;
    int* nb;
};

#endif // GETINTDIALOG_H
