#ifndef CHATWIDGET_H
#define CHATWIDGET_H

#include <QWidget>
#include <QTextEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QApplication>
#include <QLabel>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QTextEdit>
#include <QMessageBox>
#include <QSpinBox>


class ChatWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ChatWidget(QWidget *parent = 0);
    

    QString getIpString();
    int getPort();
    void appendString(QString s);
private:
    QSpinBox* port;
    QLineEdit* ip;
    QTextEdit* chat;
    QLineEdit* nick;
    QLineEdit* msg;
    QPushButton* connect;
    QPushButton* send;

signals:
    
public slots:
    void connectionSlot();
    void sendSlot();
    
};

#endif // CHATWIDGET_H