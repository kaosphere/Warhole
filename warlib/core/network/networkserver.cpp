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

    inQueue = in;
    outQueue = out;

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
            QLog_Info(LOG_ID_INFO, "NetworkServer() : Server started on port " + QString::number(serveur->serverPort()));
            // Si le serveur a été démarré correctement
            emit networkEvent(tr("<em><font color=\"DimGray\">Le serveur a été démarré sur le port <strong>") +
                              QString::number(serveur->serverPort()) +
                              tr("</strong>.<br />Des clients peuvent maintenant se connecter.</em></font>"));
            connect(serveur, SIGNAL(newConnection()), this, SLOT(newClientConnected()));
        }
    }
    catch(const WarlibException& e)
    {
        QLog_Error(LOG_ID_ERR, e.what());
        QLog_Info(LOG_ID_ERR, "<em><font color=\"Red\">ERREUR : Le serveur n'a pas pu être démarré. Raison : " + serveur->errorString());
    }
}

NetworkServer::~NetworkServer()
{
    //serveur->deleteLater();
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
    quint32 tailleMsg;
    QString name;
    int dest;
    QTcpSocket* s;
    // 1 : on reçoit un paquet (ou un sous-paquet) d'un des clients

    // On détermine quel client envoie le message (recherche du QTcpSocket du client)
    Client *c = qobject_cast<Client *>(sender());
    if (c == 0) // Si par hasard on n'a pas trouvé le client à l'origine du signal, on arrête la méthode
        return;
    s = c->getSocket();

    // Si tout va bien, on continue : on récupère le message
    QDataStream in(s);

    do
        {

        if (c->getMessageSize() == 0) // Si on ne connaît pas encore la taille du message, on essaie de la récupérer
        {
            if (s->bytesAvailable() < (int)sizeof(quint32)) // On n'a pas reçu la taille du message en entier
                return;

            in >> tailleMsg; // Si on a reçu la taille du message en entier, on la récupère
            c->setMessageSize(tailleMsg);
        }

        // Si on connaît la taille du message, on vérifie si on a reçu le message en entier
        if (s->bytesAvailable() < c->getMessageSize())
        {
            QLog_Info(LOG_ID_INFO, "receiveData(): received network message is incomplete.");
            QLog_Info(LOG_ID_INFO, "receiveData(): arrived bytes : " + QString::number(sock->bytesAvailable()));
            QLog_Info(LOG_ID_INFO, "receiveData(): expecting " + QString::number(messageSize) + " bytes.");
            return;    
        }


        // Si ces lignes s'exécutent, c'est qu'on a reçu tout le message : on peut le récupérer !
        Message m;
        QByteArray d;
        in >> name;
        in >> dest;
        in >> d;
        m.setMessageSender(name);
        m.setDest(dest);
        m.setData(d);

        QLog_Info(LOG_ID_INFO, "receiveData() : message received from "+ m.getMessageSender() +
                  " Destination : " + QString::number(m.getDest()) + " Data : " + QString::number(m.getData().toUShort()));

        if(c->getName().isEmpty())
        {
            // It's the first time we receive a message from this client
            // set his name, and add it to the connected clients list
            QLog_Info(LOG_ID_INFO, "receiveData() : first time we receive a message from client " + name);
            c->setName(name);
            emit networkEvent(tr("<em><font color=\"DimGray\"><strong>")+ name + tr("</strong> s'est connecté à la partie.</font></em>"));
            emit newPlayerConnected(*c);
        }

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

        // Transfer message to every one
        if(m.getDest() != ME)
        {
            QLog_Info(LOG_ID_INFO, "receiveData() : message dest is different from ME, put in outqueue to transfer.");
            if(outQueue)
            {
                outQueue->addMessage(m);
            }
        }

        // Do nothig if dest is ME, because it means that a special answer is need, and will
        // be treated by command manager

        // set message size to 0 to be able to receive new packets from this client
        c->setMessageSize(0);
    }while(c->getSocket()->bytesAvailable());
}

void NetworkServer::newClientConnected()
{
    QTcpSocket *newClientSocket = serveur->nextPendingConnection();
    Client* newClient = new Client(newClientSocket, 0);
    clients << newClient;

    QLog_Info(LOG_ID_INFO, "newClientConnected() : un nouveau client s'est connecté au réseau");

    connect((QObject*)newClient, SIGNAL(donnees()), this, SLOT(receiveData()));
    connect((QObject*)newClient, SIGNAL(disco()), this, SLOT(deconnectionClient()));
}

void NetworkServer::deconnectionClient()
{
    // On détermine quel client se déconnecte
    Client *c = qobject_cast<Client *>(sender());
    if (c == 0) // Si par hasard on n'a pas trouvé le client à l'origine du signal, on arrête la méthode
        return;

    QLog_Info(LOG_ID_INFO, "deconnectionClient() : Player " + c->getName() +
              " disconnection detected.");

    // send notification
    emit networkEvent(tr("<em><font color=\"DimGray\"><strong>") + c->getName() + tr("</strong> s'est déconnecté.</font></em>"));
    emit playerDisconnected(*c);

    clients.removeOne(c);

    c->deleteLater();
}


void NetworkServer::sendToAllButMe(const QByteArray& m, QString sender)
{
    // Send message to all clients (but sender if a sender is defined
    for(int i = 0; i < clients.size(); ++i)
    {
        if(sender != clients[i]->getName())
        {
            clients[i]->getSocket()->write(m);
            // Be sure to send packet now
            //clients[i]->getSocket()->flush();
            QLog_Info(LOG_ID_INFO, "sendToAllButMe() : sending message to " + clients[i]->getName());
        }
    }
}

void NetworkServer::sendToAll(const QByteArray& m)
{
    // Send message to all clients (but sender if a sender is defined
    for(int i = 0; i < clients.size(); ++i)
    {
         QLog_Info(LOG_ID_INFO, "sendToAll() : sending message to " + clients[i]->getName());
         clients[i]->getSocket()->write(m);
         // Be sure to send packet now
         //clients[i]->getSocket()->flush();
    }
}

void NetworkServer::disconnection()
{
    QLog_Info(LOG_ID_INFO, "disconnection() : Closing server...");
    serveur->close();
}

void NetworkServer::sendBackToSender(const QByteArray& m, QString sender)
{
    // Send message only to the one who sended first
    // TODO : make this in a better way, with a QMap for example
    for(int i = 0; i < clients.size(); ++i)
    {
        if(sender == clients[i]->getName())
        {
            clients[i]->getSocket()->write(m);
            // Be sure to send packet now
            //clients[i]->getSocket()->flush();
            QLog_Info(LOG_ID_INFO, "sendBackToSender() : sending message to " + clients[i]->getName());
        }
    }
}

QByteArray NetworkServer::fillPacketWithMessage(const Message& m)
{
    // Préparation du paquet
    QByteArray packet;
    QDataStream out(&packet, QIODevice::WriteOnly);

    // TODO : put message serialization in message class

    out << (quint32) 0; // On écrit 0 au début du paquet pour réserver la place pour écrire la taille
    out << m.getMessageSender(); // Envoyeur
    out << (int)m.getDest(); // Destinataire (utilisé par le server seulement)
    out << m.getData(); // On ajoute le message à la suite
    out.device()->seek(0); // On se replace au début du paquet
    out << (quint32) (packet.size() - sizeof(quint32)); // On écrase le 0 qu'on avait réservé par la longueur du message

    return packet;
}

void NetworkServer::send()
{
    Message m;

    // TODO protect null pointer
    // While there are messages in the queue
    while(!outQueue->isMessageListEmpty())
    {
        m = outQueue->getAndRemoveFirstMessage();

        QLog_Info(LOG_ID_INFO, "send() : handling message from outQueue");
        QLog_Info(LOG_ID_INFO, "send() : still " + QString::number(outQueue->getMessageList().size()) +
                  " messages in outQueue");

        QByteArray packet = fillPacketWithMessage(m);

        if(m.getMessageSender().contains("_SERVER") && m.getDest() == ALL)
        {
            // If server is sending this message to everyone, in queue in its proper inqueue
            QLog_Info(LOG_ID_INFO, "send() : message to be sent to all, also add my message to my queue.");
            if(inQueue) inQueue->addMessage(m);
        }

        // Also add the command to the in message queue so that the server
        // gets the changed too
        switch(m.getDest())
        {
        case ALL:
            // send message to every clients
            QLog_Info(LOG_ID_INFO, "send() : sending to all...");
            sendToAll(packet);
            break;
        case ALL_BUT_ME:
            QLog_Info(LOG_ID_INFO, "send() : sending to all but " + m.getMessageSender());
            sendToAllButMe(packet, m.getMessageSender());
            // If
            break;
        case ME:
            QLog_Info(LOG_ID_INFO, "send() : sending to " + m.getMessageSender());
            sendBackToSender(packet, m.getMessageSender());
            break;
        default:
            QLog_Error(LOG_ID_ERR, "send() : Destination " + QString::number(m.getDest()) + " not recognised in message, message won't be sent");
            break;
        }
    }
}

