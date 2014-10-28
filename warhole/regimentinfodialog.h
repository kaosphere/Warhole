#ifndef REGIMENTINFODIALOG_H
#define REGIMENTINFODIALOG_H

#include <QDialog>
#include "game/regiment/regimentabstract.h"

namespace Ui {
class RegimentInfoDialog;
}

class RegimentInfoDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit RegimentInfoDialog(RegimentAbstract *reg, QWidget *parent = 0);
    ~RegimentInfoDialog();
    
    RegimentAbstract* &getR();
    void setR(RegimentAbstract *value);

    void accept();
private:
    Ui::RegimentInfoDialog *ui;

    RegimentAbstract* r;
};

#endif // REGIMENTINFODIALOG_H
