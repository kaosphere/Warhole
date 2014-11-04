#ifndef CLIENT_H
#define CLIENT_H

#include <QtGui>
#include <QtNetwork>

#include "Utilities/QLogger/QLogger.h"

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

    quint32 getMessageSize() const;
    void setMessageSize(const quint32 &value);

    bool operator=(const Client& other);

    QString getName() const;
    void setName(const QString &value);

public slots:
    void printBufferInfo(qint64 n);

signals:
    void donnees();
    void disco();

private:
    static const QString LOG_ID_INFO;
    static const QString LOG_ID_TRACE;
    static const QString LOG_ID_WARN;
    static const QString LOG_ID_ERR;

    QTcpSocket* sock;
    QString name;
    quint32 messageSize;
};

#endif // CLIENT_H
