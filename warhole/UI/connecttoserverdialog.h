#ifndef CONNECTTOSERVERDIALOG_H
#define CONNECTTOSERVERDIALOG_H

#include <QDialog>
#include "gamewindow.h"

namespace Ui {
class ConnectToServerDialog;
}

class ClientInfo;

class ConnectToServerDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit ConnectToServerDialog(QWidget *parent = 0);
    ~ConnectToServerDialog();
    
    Game *getG() const;
    void setG(Game *value);

    ClientInfo *getInfo() const;
    void setInfo(ClientInfo *value);

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::ConnectToServerDialog *ui;
    Game* g;
    ClientInfo* info;
};

#endif // CONNECTTOSERVERDIALOG_H
