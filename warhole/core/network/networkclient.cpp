#include "networkclient.h"

using namespace QLogger;

const QString NetworkClient::LOG_ID_INFO = "NetworkClient_info";
const QString NetworkClient::LOG_ID_TRACE = "NetworkClient_trace";
const QString NetworkClient::LOG_ID_WARN = "NetworkClient_warm";
const QString NetworkClient::LOG_ID_ERR = "NetworkClient_err";

NetworkClient::NetworkClient(MessageQueue *in, MessageQueue* out, QObject *parent, QString ip, int port) :
    NetworkInterface(in, out, parent)
{
    QLoggerManager *manager = QLoggerManager::getInstance();
    manager->addDestination("./logs/lastrun.log", QStringList(LOG_ID_TRACE), QLogger::TraceLevel);
    manager->addDestination("./logs/lastrun.log", QStringList(LOG_ID_INFO), QLogger::InfoLevel);
    manager->addDestination("./logs/lastrun.log", QStringList(LOG_ID_ERR), QLogger::ErrorLevel);
    manager->addDestination("./logs/lastrun.log", QStringList(LOG_ID_WARN), QLogger::WarnLevel);

    connect(this, SIGNAL(clientStateChanged(QString)), this, SIGNAL(stateChanged(QString)));

    sock = new QTcpSocket(this);

    QObject::connect(sock, SIGNAL(readyRead()), this, SLOT(receiveData()));
    QObject::connect(sock, SIGNAL(connected()), this, SLOT(connected()));
    QObject::connect(sock, SIGNAL(disconnected()), this, SLOT(deconnected()));
    QObject::connect(sock, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(errorSocket(QAbstractSocket::SocketError)));

    messageSize = 0;

    inQueue = in;
    outQueue = out;

    connection(ip, port);
}

NetworkClient::~NetworkClient()
{

}

void NetworkClient::connection(QString ip, int port)
{
    // On annonce sur la fenêtre qu'on est en train de se connecter
    setClientState(tr("<em><font color=\"DimGray\">Tentative de connexion en cours...</em></font>"));

    //boutonConnexion->setEnabled(false);
    QLog_Info(LOG_ID_INFO, "connection() : atempting connection to " + ip + " on port " + QString::number(port));
    sock->abort(); // On désactive les connexions précédentes s'il y en a
    sock->connectToHost(ip, port); // On se connecte au serveur demandé
}

void NetworkClient::disconnection()
{
    // Deactivate current connection
    sock->abort();
}

void NetworkClient::send()
{
    //TODO protect null pointer
    while(!outQueue->isMessageListEmpty())
    {
        Message m = outQueue->getAndRemoveFirstMessage();
        sendToServer(m);
    }
}

void NetworkClient::sendToServer(const Message& m)
{
    QLog_Info(LOG_ID_INFO, "sendToServer() : sending to server with sender "+ m.getMessageSender() +
              " Destination : " + QString::number(m.getDest()) + " Data : " + QString::number(m.getData().toUShort()));

    // Préparation du paquet
    QByteArray packet;
    QDataStream out(&packet, QIODevice::WriteOnly);

    out << (quint16) 0; // On écrit 0 au début du paquet pour réserver la place pour écrire la taille
    out << m.getMessageSender();
    out << (int)m.getDest();
    out << m.getData(); // On ajoute le message à la suite
    out.device()->seek(0); // On se replace au début du paquet
    out << (quint16) (packet.size() - sizeof(quint16)); // On écrase le 0 qu'on avait réservé par la longueur du message

    sock->write(packet); // On envoie le paquet
    // Ensure to send the data right away
    sock->flush();
}

void NetworkClient::receiveData()
{
    QDataStream in(sock);
    QString name;

    if (messageSize == 0)
    {
        if (sock->bytesAvailable() < (int)sizeof(quint16))
            return;

        in >> messageSize;
    }

    if (sock->bytesAvailable() < messageSize)
        return;


    // Si on arrive jusqu'à cette ligne, on peut récupérer le message entier
    Message m;
    QByteArray d;
    int dest;

    in >> name;
    in >> dest;
    in >> d;
    m.setMessageSender(name);
    m.setDest(dest);
    m.setData(d);

    QLog_Info(LOG_ID_INFO, "Client message received from " + m.getMessageSender() + " with dest " + QString::number(dest));

    try
    {
        if(!inQueue)
        {
            throw(WarlibException(EXCEPTION_CRITICAL,
                                  tr("inQueue pointer is NULL"),
                                  0));
        }
        else
        {
            inQueue->addMessage(m);
        }
    }
    catch(const WarlibException& e)
    {
        QLog_Error(LOG_ID_ERR, "receiveData() : " + QString::fromStdString(e.what()));
    }

    // On remet la taille du message à 0 pour pouvoir recevoir de futurs messages
    messageSize = 0;
}

void NetworkClient::connected()
{
    emit networkEvent(CLIENT_IS_CONNECTED, "");
}

void NetworkClient::deconnected()
{
    emit networkEvent(CLIENT_IS_DISCONNECTED, "");
}

// This slot is called when an error is detected
void NetworkClient::errorSocket(QAbstractSocket::SocketError erreur)
{
    QLog_Info(LOG_ID_ERR, "errorSocket() : " + sock->errorString());
    switch(erreur)
    {
    case QAbstractSocket::HostNotFoundError:
        QLog_Info(LOG_ID_ERR, "errorSocket() : server not found");
        setClientState(tr("<em><font color=\"Red\">ERREUR : le serveur n'a pas pu être trouvé. Vérifiez l'IP et le port.</em></font>"));
        break;
    case QAbstractSocket::ConnectionRefusedError:
        QLog_Info(LOG_ID_ERR, "errorSocket() : server rejected connection.");
        setClientState(tr("<em><font color=\"Red\">ERREUR : le serveur a refusé la connexion. Vérifiez si le programme \"serveur\" a bien été lancé. Vérifiez aussi l'IP et le port.</em></font>"));
        break;
    case QAbstractSocket::RemoteHostClosedError:
        QLog_Info(LOG_ID_ERR, "errorSocket() : server ended connection.");
        setClientState(tr("<em><font color=\"Red\">ERREUR : le serveur a coupé la connexion.</em></font>"));
        break;
    default:
        QLog_Info(LOG_ID_ERR, "errorSocket() : other error : " + sock->errorString());
        setClientState(tr("<em>ERREUR : ") + sock->errorString() + tr("</em>"));
    }
}

QTcpSocket* NetworkClient::getSock() const
{
    return sock;
}

void NetworkClient::setSock(QTcpSocket *value)
{
    sock = value;
}

quint16 NetworkClient::getMessageSize() const
{
    return messageSize;
}

void NetworkClient::setMessageSize(const quint16 &value)
{
    messageSize = value;
}

QString NetworkClient::getState() const
{
    return clientState;
}

void NetworkClient::setClientState(const QString &value)
{
    clientState = value;
    emit clientStateChanged(clientState);
}
