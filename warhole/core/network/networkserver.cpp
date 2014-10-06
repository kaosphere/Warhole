#include "networkserver.h"

using namespace QLogger;

const QString NetworkServer::LOG_ID_INFO = "NetworkServer_info";
const QString NetworkServer::LOG_ID_TRACE = "NetworkServer_trace";
const QString NetworkServer::LOG_ID_WARN = "NetworkServer_warm";
const QString NetworkServer::LOG_ID_ERR = "NetworkServer_err";

NetworkServer::NetworkServer(MessageQueue *in, MessageQueue *out, QObject *parent) :
    NetworkInterface(in, out, parent)
{
    QLoggerManager *manager = QLoggerManager::getInstance();
    manager->addDestination("./logs/lastrun.log", QStringList(LOG_ID_TRACE), QLogger::TraceLevel);
    manager->addDestination("./logs/lastrun.log", QStringList(LOG_ID_INFO), QLogger::InfoLevel);
    manager->addDestination("./logs/lastrun.log", QStringList(LOG_ID_ERR), QLogger::ErrorLevel);
    manager->addDestination("./logs/lastrun.log", QStringList(LOG_ID_WARN), QLogger::WarnLevel);

    connect(this, SIGNAL(serverStateChanged(QString)), this, SIGNAL(stateChanged(QString)));

    // Gestion du serveur
    try
    {
        serveur = new QTcpServer(this);
        if (!serveur->listen(QHostAddress::Any, NET_PORT)) // Démarrage du serveur sur toutes les IP disponibles et sur le port 50585
        {
            throw(WarlibException(EXCEPTION_FATAL,
                                  tr("Le serveur n'a pas pu être démarré. Raison :<br />") + serveur->errorString(),
                                  0));
        }
        else
        {
            // Si le serveur a été démarré correctement
            setServerState(tr("Le serveur a été démarré sur le port <strong>") +
                           QString::number(serveur->serverPort()) +
                           tr("</strong>.<br />Des clients peuvent maintenant se connecter."));
            emit serverStateChanged(serverState);
            connect(serveur, SIGNAL(newConnection()), this, SLOT(newClientConnected()));
        }
    }
    catch(const WarlibException& e)
    {
        QLog_Error(LOG_ID_ERR, e.what());
    }
}



QList<Client*> NetworkServer::getClients() const
{
    return clients;
}

void NetworkServer::setClients(const QList<Client*> &value)
{
    clients = value;
}

void NetworkServer::addClient(Client* c)
{
    clients.append(c);
}

void NetworkServer::removeClient(Client* c)
{
    clients.removeOne(c);
}

void NetworkServer::receiveData()
{
    // Receive data, and put it in inQueue
    quint16 tailleMsg;
    QTcpSocket* s;
    // 1 : on reçoit un paquet (ou un sous-paquet) d'un des clients

    // On détermine quel client envoie le message (recherche du QTcpSocket du client)
    Client *c = qobject_cast<Client *>(sender());
    if (c == 0) // Si par hasard on n'a pas trouvé le client à l'origine du signal, on arrête la méthode
        return;
    s = c->getSocket();

    // Si tout va bien, on continue : on récupère le message
    QDataStream in(s);

    if (c->getMessageSize() == 0) // Si on ne connaît pas encore la taille du message, on essaie de la récupérer
    {
        if (s->bytesAvailable() < (int)sizeof(quint16)) // On n'a pas reçu la taille du message en entier
            return;

        in >> tailleMsg; // Si on a reçu la taille du message en entier, on la récupère
        c->setMessageSize(tailleMsg);
    }

    // Si on connaît la taille du message, on vérifie si on a reçu le message en entier
    if (s->bytesAvailable() < c->getMessageSize()) // Si on n'a pas encore tout reçu, on arrête la méthode
        return;


    // Si ces lignes s'exécutent, c'est qu'on a reçu tout le message : on peut le récupérer !
    Message m;
    QByteArray d;
    in >> d;
    m.setData(d);

    // Put in inQueue
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


    // Transfer to everyone
    sendToAll(m);

    // set message size to 0 to be able to receive new packets from this client
    c->setMessageSize(0);
}

void NetworkServer::newClientConnected()
{
    QTcpSocket *newClientSocket = serveur->nextPendingConnection();
    Client* newClient = new Client(newClientSocket, 0);
    clients << newClient;
    setServerState(tr("Un nouveau client s'est connecté"));

    connect((QObject*)newClient, SIGNAL(donnees()), this, SLOT(receiveData()));
    connect((QObject*)newClient, SIGNAL(disco()), this, SLOT(deconnectionClient()));
}

void NetworkServer::deconnectionClient()
{
    // On détermine quel client se déconnecte
    Client *c = qobject_cast<Client *>(sender());
    if (c == 0) // Si par hasard on n'a pas trouvé le client à l'origine du signal, on arrête la méthode
        return;

    // send notification

    clients.removeOne(c);

    c->deleteLater();
}


void NetworkServer::sendToAll(const Message &m)
{
    // Préparation du paquet
    QByteArray packet;
    QDataStream out(&packet, QIODevice::WriteOnly);

    out << (quint16) 0; // On écrit 0 au début du paquet pour réserver la place pour écrire la taille
    out << m.getData(); // On ajoute le message à la suite
    out.device()->seek(0); // On se replace au début du paquet
    out << (quint16) (packet.size() - sizeof(quint16)); // On écrase le 0 qu'on avait réservé par la longueur du message

    // Send message to all clients
    for(int i = 0; i < clients.size(); ++i)
    {
        clients[i]->getSocket()->write(packet);
    }
}

void NetworkServer::send()
{
    Message m;
    // TODO protect null pointer
    // While there are messages in the queue
    while(!outQueue->isMessageListEmpty())
    {
        m = outQueue->getAndRemoveFirstMessage();

        // send message to every clients
        sendToAll(m);

        // Also add the command to the in message queue so that the server
        // gets the changed too

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
            QLog_Error(LOG_ID_ERR, "send() : " + QString::fromStdString(e.what()));
        }
    }
}

QString NetworkServer::getState() const
{
    return serverState;
}

void NetworkServer::setServerState(const QString &value)
{
    serverState = value;
    emit serverStateChanged(serverState);
}
