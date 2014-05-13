#ifndef PLAYER_H
#define PLAYER_H

#include <QObject>
#include <QtCore>

#include "army/army.h"

//! Player
/*!
* Player class. Each time a player connects to the game, a new object is
* created. It contains principally the army played by the player and its
* state during the game. Each player is serialized and saved in the game.
*/
class Player
{
public:
    //! Player
    /*!
    * Constructor of Player class.
    */
    explicit Player();
    
    QString getName() const;
    void setName(const QString &value);

    Army &getArmy();
    void setArmy(const Army &value);

    //! operator==
    /*!
    * Overloading of operator== for Player Class.
    * @param obj Object that will be compared to.
    * @return true if the object is the same than obj.
    */
    bool operator==(const Player& obj);

signals:
    
public slots:

private:
    //! name
    /*!
    * Name of the game
    */
    QString name;

    //! army
    /*!
    * Army played by the Player in the game.
    */
    Army army;
};

#endif // PLAYER_H
