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

Game::Game(const Game &other) :
    QObject(other.parent())
{
    name = other.name;
    spectators = other.spectators;
    playerNumber = other.playerNumber;
    players = other.players;
    information = other.information;
    me = other.me;
    historic = other.historic;
    points = other.points;
    autosave = other.autosave;
    autosaveIntervalInMinutes = other.autosaveIntervalInMinutes;
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

QString Game::getMe() const
{
    return me;
}

void Game::setMe(const QString &value)
{
    me = value;
}

Game &Game::operator=(const Game &other)
{
    name = other.name;
    spectators = other.spectators;
    playerNumber = other.playerNumber;
    players = other.players;
    information = other.information;
    me = other.me;
    historic = other.historic;
    points = other.points;
    autosave = other.autosave;
    autosaveIntervalInMinutes = other.autosaveIntervalInMinutes;

    return (*this);
}

bool Game::getAutosave() const
{
    return autosave;
}

void Game::setAutosave(bool value)
{
    autosave = value;
}

int Game::getAutosaveIntervalInMinutes() const
{
    return autosaveIntervalInMinutes;
}

void Game::setAutosaveIntervalInMinutes(int value)
{
    autosaveIntervalInMinutes = value;
}

QDataStream& operator<<(QDataStream& out, const Game& obj)
{
    // TODO historic and players not streamed
    
    out << obj.name
        << obj.spectators
        << obj.playerNumber
        << obj.information
        << obj.me
        << obj.points;

    return out;
}

QDataStream& operator>>(QDataStream& in, Game& obj)
{
    in >> obj.name;
    in >> obj.spectators;
    in >> obj.playerNumber;
    in >> obj.information;
    in >> obj.me;
    in >> obj.points;

    return in;
}
