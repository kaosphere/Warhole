#ifndef CHATWIDGETFORM_H
#define CHATWIDGETFORM_H

#include <QWidget>
#include <QTextStream>
#include <QStandardItemModel>
#include "game/player.h"
#include "Utilities/DiceRoller/DiceRoller.h"

namespace Ui {
class ChatWidgetForm;
}

class ChatWidgetForm : public QWidget
{
    Q_OBJECT
    
public:
    explicit ChatWidgetForm(QWidget *parent = 0);
    ~ChatWidgetForm();

    void appendString(QString s);
private slots:
    void on_pushButton_clicked();
    void printNewChatMessage(QString sender, QString msg);
    void refreshPlayerListDisplay(QList<Player> l);

    void on_pushButton_2_clicked();

signals:
    void newMessageToSend(QString m, bool previous, QString sender="");

private:
    Ui::ChatWidgetForm *ui;
    QStandardItemModel* players;
};

#endif // CHATWIDGETFORM_H
