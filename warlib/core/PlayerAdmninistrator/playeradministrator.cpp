#include "playeradministrator.h"

using namespace QLogger;

const QString PlayerAdministrator::LOG_ID_INFO = "PlayerAdministrator_info";
const QString PlayerAdministrator::LOG_ID_TRACE = "PlayerAdministrator_trace";
const QString PlayerAdministrator::LOG_ID_WARN = "PlayerAdministrator_warm";
const QString PlayerAdministrator::LOG_ID_ERR = "PlayerAdministrator_err";

PlayerAdministrator::PlayerAdministrator(QObject *parent) :
    QObject(parent)
{
    QLoggerManager *manager = QLoggerManager::getInstance();
    manager->addDestination("./logs/lastrun.log", QStringList(LOG_ID_TRACE), QLogger::TraceLevel);
    manager->addDestination("./logs/lastrun.log", QStringList(LOG_ID_INFO), QLogger::InfoLevel);
    manager->addDestination("./logs/lastrun.log", QStringList(LOG_ID_ERR), QLogger::ErrorLevel);
    manager->addDestination("./logs/lastrun.log", QStringList(LOG_ID_WARN), QLogger::WarnLevel);
}

QList<Player> PlayerAdministrator::getPlayerList() const
{
    return playerList;
}

void PlayerAdministrator::setPlayerList(const QList<Player> &value)
{
    playerList = value;
}

void PlayerAdministrator::authorizePlayer(const Player &p)
{
    QLog_Info(LOG_ID_INFO, "authorizePlayer() : Authorizing player " + p.getName());
    if(playerList.contains(p))
    {
        QLog_Info(LOG_ID_INFO, "authorizePlayer() : Player " + p.getName() +
                  " was already in the player list, reconnect him.");
        // If player was already in the list, just reconnect him
        playerList[playerList.indexOf(p)].setConnected(true);
        emit playerListChanged(playerList);
    }
    else
    {
        QLog_Info(LOG_ID_INFO, "authorizePlayer() : Player " + p.getName() +
                  " was not found in the player list, add him.");
        bool nameTaken = false;
        // Verify that no one in the game already has this name
        for(int i = 0; i < playerList.size(); ++i)
        {
            if(playerList.at(i).getName() == p.getName())
            {
                QLog_Info(LOG_ID_INFO, "authorizePlayer() : Player namefound in the list");
                nameTaken = true;
            }
        }
        if(!nameTaken)
        {
            QLog_Info(LOG_ID_INFO, "authorizePlayer() : Player name " + p.getName() +
                      " is free, add him to the list.");
            playerList.append(p);
            emit playerListChanged(playerList);
        }
        else
        {
            Player p2(p);
            p2.setName(p.getName() + "_2");
            QLog_Info(LOG_ID_INFO, "authorizePlayer() : Player name " + p.getName() +
                      " is already taken, inform him to change name for " + p2.getName());
            playerList.append(p2);

            // Notify the player that he has to change name
            // TODO finish implementation of player name change
            emit playerNameToChange(p.getName(), p2.getName());
            emit playerListChanged(playerList);
        }
    }
}

void PlayerAdministrator::handleNewPlayerConnection(Client c)
{
    Player p(c.getName(), c.getSocket()->localAddress().toString(), true);
    QLog_Info(LOG_ID_INFO, "handleNewPlayerConnection() : New player connected : " +
              p.getName() + " Ip : " + p.getHostAddress());
    authorizePlayer(p);
}

void PlayerAdministrator::handlePlayerDisconnection(Client c)
{
    Player p(c.getName(), c.getSocket()->localAddress().toString(), false);
    QLog_Info(LOG_ID_INFO, "handleNewPlayerConnection() : Player disconnected : " +
              p.getName() + " Ip : " + p.getHostAddress());
    if(playerList.contains(p))
    {
        QLog_Info(LOG_ID_INFO, "handleNewPlayerConnection() : Player found in list, remove him from player list.");
        playerList[playerList.indexOf(p)].setConnected(false);
        emit playerListChanged(playerList);
    }
}

