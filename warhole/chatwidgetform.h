#ifndef CHATWIDGETFORM_H
#define CHATWIDGETFORM_H

#include <QWidget>
#include <QTextStream>

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

signals:
    void newMessageToSend(QString m);

private:
    Ui::ChatWidgetForm *ui;
};

#endif // CHATWIDGETFORM_H
