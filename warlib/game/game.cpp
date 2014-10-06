#include "game.h"

using namespace QLogger;

const QString Game::LOG_ID_INFO = "Game_info";
const QString Game::LOG_ID_TRACE = "Game_trace";
const QString Game::LOG_ID_WARN = "Game_warn";
const QString Game::LOG_ID_ERR = "Game_err";

Game::Game(QObject *parent) :
    QObject(parent)
{
    QLoggerManager *manager = QLoggerManager::getInstance();
    manager->addDestination("./logs/lastrun.log", QStringList(LOG_ID_TRACE), QLogger::TraceLevel);
    manager->addDestination("./logs/lastrun.log", QStringList(LOG_ID_INFO), QLogger::InfoLevel);
    manager->addDestination("./logs/lastrun.log", QStringList(LOG_ID_ERR), QLogger::ErrorLevel);
    manager->addDestination("./logs/lastrun.log", QStringList(LOG_ID_WARN), QLogger::WarnLevel);
}

QString Game::getName() const
{
    return name;
}

void Game::setName(const QString &value)
{
    name = value;
}

bool Game::getSpectators() const
{
    return spectators;
}

void Game::setSpectators(bool value)
{
    spectators = value;
}

int Game::getPlayerNumber() const
{
    return playerNumber;
}

void Game::setPlayerNumber(int value)
{
    playerNumber = value;
}

QList<Player> Game::getPlayers() const
{
    return players;
}

void Game::setPlayers(const QList<Player> &value)
{
    players = value;
}

bool Game::addPlayer(Player &p)
{
    bool nameTaken = true;
    // Add player if the name isn't already taken
    for(int i = 0; i< players.size(); ++i)
    {
        if(players.at(i).getName() == p.getName())
        {
            nameTaken = false;
            players.append(p);
            return true;
        }
    }
    if(nameTaken)
    {
        QLog_Error(LOG_ID_ERR, "addPlayer() : Player name : " + p.getName() + " is already used.");
    }
    return false;
}

void Game::removePlayer(const Player &p)
{
    players.removeOne(p);
}

bool Game::addArmyToPlayer(Army a, QString playerName)
{
    bool playerFound = false;
    for(int i = 0; i<players.size(); ++i)
    {
        if(players.at(i).getName() == playerName)
        {
            players[i].setArmy(a);
            playerFound = true;
            return playerFound;
        }
    }
    QLog_Error(LOG_ID_ERR, "addArmyToPlayer() : Couldn't find player " + playerName + ". Can't add Army.");
    return playerFound;
}

QString Game::getInformation() const
{
    return information;
}

void Game::setInformation(const QString &value)
{
    information = value;
}

Historic Game::getHistoric() const
{
    return historic;
}

void Game::setHistoric(const Historic &value)
{
    historic = value;
}


int Game::getPoints() const
{
    return points;
}

void Game::setPoints(int value)
{
    points = value;
}
