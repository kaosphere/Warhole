#ifndef CLIENT_H
#define CLIENT_H

#include <QtGui>
#include <QtNetwork>

class Client : public QObject
{
    Q_OBJECT
public:
    Client();
    ~Client();
    Client(const Client& other);
    Client(QTcpSocket* s, quint16 t);
    QTcpSocket* getSocket();
    void setSocket(QTcpSocket* s);

    quint16 getMessageSize() const;
    void setMessageSize(const quint16 &value);

    bool operator=(const Client& other);

    QString getName() const;
    void setName(const QString &value);

public slots:

signals:
    void donnees();
    void disco();

private:
    QTcpSocket* sock;
    QString name;
    quint16 messageSize;
};

#endif // CLIENT_H
