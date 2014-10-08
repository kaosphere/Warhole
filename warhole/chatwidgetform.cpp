#include "chatwidgetform.h"
#include "ui_chatwidgetform.h"

ChatWidgetForm::ChatWidgetForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ChatWidgetForm)
{
    ui->setupUi(this);

    QObject::connect(ui->lineEdit, SIGNAL(returnPressed()),this,SLOT(on_pushButton_clicked()));
}

ChatWidgetForm::~ChatWidgetForm()
{
    delete ui;
}

void ChatWidgetForm::on_pushButton_clicked()
{
    emit newMessageToSend(ui->lineEdit->text());
    ui->lineEdit->clear(); // On vide la zone d'écriture du message
    ui->lineEdit->setFocus(); // Et on remet le curseur à l'intérieur
}

void ChatWidgetForm::printNewChatMessage(QString sender, QString msg)
{
    QString s;
    QTextStream stream(&s);
    stream << "<strong>" << sender << " : </strong>" << msg;
    appendString(s);
}

void ChatWidgetForm::appendString(QString s)
{
    ui->textEdit->append(s);
}
