#include "player.h"

Player::Player()
{
}

QString Player::getName() const
{
    return name;
}

void Player::setName(const QString &value)
{
    name = value;
}

Army Player::getArmy() const
{
    return army;
}

void Player::setArmy(const Army &value)
{
    army = value;
}

bool Player::operator ==(const Player &obj)
{
    if(name == obj.name && army == obj.army)
        return true;
    else return false;
}
