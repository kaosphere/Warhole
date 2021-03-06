#include "chatwidgetform.h"
#include "ui_chatwidgetform.h"

ChatWidgetForm::ChatWidgetForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ChatWidgetForm)
{
    ui->setupUi(this);

    players = new QStandardItemModel();
    ui->treeView->setModel(players);

    ui->textEdit->ensureCursorVisible();

    QObject::connect(ui->lineEdit, SIGNAL(returnPressed()),this,SLOT(on_pushButton_clicked()));
}

ChatWidgetForm::~ChatWidgetForm()
{
    delete ui;
}

void ChatWidgetForm::on_pushButton_clicked()
{
    emit newMessageToSend(ui->lineEdit->text(), false);
    ui->lineEdit->clear(); // On vide la zone d'écriture du message
    ui->lineEdit->setFocus(); // Et on remet le curseur à l'intérieur
}

void ChatWidgetForm::printNewChatMessage(QString sender, QString msg)
{
    QString s;
    QTextStream stream(&s);
    if(!sender.isEmpty())
        stream << "<strong>" << sender << " : </strong>";
    stream << msg;
    appendString(s);
}

void ChatWidgetForm::refreshPlayerListDisplay(QList<Player> l)
{
    players->clear();
    for(int i = 0; i < l.size(); ++i)
    {
        if(l.at(i).getConnected())
        {
            QStandardItem* item = new QStandardItem(l.at(i).getName());
            players->appendRow(item);
        }
    }
}

void ChatWidgetForm::appendString(QString s)
{
    ui->textEdit->append(s);
}

void ChatWidgetForm::on_pushButton_2_clicked()
{
    emit newMessageToSend(DiceRoller::rollDiceString(D6, ui->spinBox->value()), false);
}
