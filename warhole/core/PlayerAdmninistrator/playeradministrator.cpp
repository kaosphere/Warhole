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
    if(playerList.contains(p))
    {
        // If player was already in the list, just reconnect him
        playerList[playerList.indexOf(p)].setConnected(true);
        emit playerListChanged(playerList);
    }
    else
    {
        bool nameTaken = false;
        // Verify that no one in the game already has this name
        for(int i = 0; i < playerList.size(); ++i)
        {
            if(playerList.at(i).getName() == p.getName())
            {
                nameTaken = true;
            }
        }
        if(!nameTaken)
        {
            playerList.append(p);
            emit playerListChanged(playerList);
        }
        else
        {
            Player p2(p);
            p2.setName(p.getName() + "_2");
            playerList.append(p2);

            // Notify the player that he has to change name
            emit playerNameToChange(p);
            emit playerListChanged(playerList);
        }
    }
}

void PlayerAdministrator::disconnectPlayer(QString p)
{
    for(int i = 0; i < playerList.size(); ++i)
    {
        if(playerList.at(i).getName() == p)
        {
            playerList[i].setConnected(false);
            emit playerListChanged(playerList);
        }
    }
}

void PlayerAdministrator::handleNewPlayerConnection(Client c)
{
    Player p(c.getName(), c.getSocket()->localAddress().toString(), true);
    authorizePlayer(p);
}

