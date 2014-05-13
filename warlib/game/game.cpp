#include "game.h"

Game::Game(QObject *parent) :
    QObject(parent)
{
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

QList<Player *> Game::getPlayers() const
{
    return players;
}

void Game::setPlayers(const QList<Player*> &value)
{
    players = value;
}

void Game::addPlayer(Player *p)
{
    players.append(p);
}

void Game::removePlayer(Player *p)
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
