#include "chatwidget.h"

ChatWidget::ChatWidget(QWidget *parent) :
    QWidget(parent)
{

    QVBoxLayout* v = new QVBoxLayout(this);
    QHBoxLayout* h = new QHBoxLayout();
    QHBoxLayout* h2 = new QHBoxLayout();

    QLabel* ipserv = new QLabel(tr("IP du serveur :"));
    QLabel* portserv = new QLabel(tr("Port :"));;
    QLabel* pseudo = new QLabel(tr("Pseudo :"));;
    QLabel* message = new QLabel(tr("Message :"));;

    ip = new QLineEdit("127.0.0.1");
    port = new QSpinBox();
    port->setMaximum(65735);

    connect = new QPushButton(tr("Connexion"));
    QObject::connect(connect, SIGNAL(clicked()),this,SLOT(connectionSlot()));

    chat = new QTextEdit();
    nick = new QLineEdit();
    msg = new QLineEdit();
    QObject::connect(msg, SIGNAL(returnPressed()),this,SLOT(sendSlot()));
    send = new QPushButton(tr("Envoyer"));
    QObject::connect(send, SIGNAL(clicked()),this,SLOT(sendSlot()));

    h->addWidget(ipserv);
    h->addWidget(ip);
    h->addWidget(portserv);
    h->addWidget(port);
    h->addWidget(connect);
    h->addStretch();

    h2->addWidget(pseudo);
    h2->addWidget(nick);
    h2->addWidget(message);
    h2->addWidget(msg);
    h2->addWidget(send);

    v->addLayout(h);
    v->addWidget(chat);
    v->addLayout(h2);
}

void ChatWidget::connectionSlot()
{
    if(!ip->text().isEmpty() && port->value() && !nick->text().isEmpty())
    {
        //netClient->connection(ip->text(),port->value());
    }
    else
    {
        QMessageBox::critical(this, "Erreur", "Entrez une IP, un numero de port et un pseudo valide.");
    }
}

void ChatWidget::sendSlot()
{
    if(!nick->text().isEmpty())
    {
        emit newMessageToSend(msg->text());
        msg->clear(); // On vide la zone d'écriture du message
        msg->setFocus(); // Et on remet le curseur à l'intérieur
    }
    else
    {
        QMessageBox::critical(this, "Erreur", "Avant de pouvoir chatter, entrez un pseudo.");
    }
}

void ChatWidget::printNewChatMessage(QString sender, QString msg)
{
    QString s;
    QTextStream stream(&s);
    stream << "<strong>" << sender << " : </strong>" << msg;
    appendString(s);
}

QString ChatWidget::getIpString()
{
    return ip->text();
}

int ChatWidget::getPort()
{
    return port->value();
}

void ChatWidget::appendString(QString s)
{
    chat->append(s);
}
