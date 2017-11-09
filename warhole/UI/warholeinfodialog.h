#ifndef WARHOLEINFODIALOG_H
#define WARHOLEINFODIALOG_H

#include <QDialog>

namespace Ui {
class WarholeInfoDialog;
}

class WarholeInfoDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit WarholeInfoDialog(QWidget *parent = 0);
    ~WarholeInfoDialog();
    
private:
    Ui::WarholeInfoDialog *ui;
};

#endif // WARHOLEINFODIALOG_H
