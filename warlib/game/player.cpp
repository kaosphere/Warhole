#include "player.h"

Player::Player()
{
}

Player::Player(QString n, QString ha, bool c)
{
    name = n;
    hostAddress = ha;
    connected = c;
}

QString Player::getHostAddress() const
{
    return hostAddress;
}

void Player::setHostAddress(const QString &value)
{
    hostAddress = value;
}

bool Player::getConnected() const
{
    return connected;
}

void Player::setConnected(const bool &value)
{
    connected = value;
}

QString Player::getName() const
{
    return name;
}

void Player::setName(const QString &value)
{
    name = value;
}

bool Player::operator ==(const Player &obj)
{
    if(name == obj.name &&
       hostAddress == obj.hostAddress &&
       connected == obj.connected)
        return true;
    else return false;
}

QDataStream &operator <<(QDataStream & out, const Player &obj)
{
    out << obj.name;
    out << obj.hostAddress;
    out << obj.connected;

    return out;
}

QDataStream &operator >>(QDataStream & in, Player &obj)
{
    in >> obj.name;
    in >> obj.hostAddress;
    in >> obj.connected;

    return in;
}
