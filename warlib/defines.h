#ifndef DEFINES_H
#define DEFINES_H

#include <QString>
#include <QStringList>
#include "core/warlibexception.h"

const int SAVE_VERSION(3);

const QString MODEL_PATH("models");
const QString ARMY_PATH("armies");
const QString MAGICAL_OBJECT_PATH("magical_objects");
const QString TERRAIN_PATH("terrains");

const QString CAVALERY_STRING("Cavalerie");
const QString CHARACTER_STRING("Personnage");
const QString CHARRIOT_STRING("Char");
const QString INFANTERY_STRING("Infanterie");
const QString MONSTER_STRING("Monstre");
const QString WARMACHINE_STRING("Machine de Guerre");

const QString MESSAGE_LIST_ARGUMENT("ml");
const QString NO_GRAPHICS_ARGUMENT("no-graphics");

#define CAVALERY_TYPE 0
#define CHARACTER_TYPE 1
#define CHARRIOT_TYPE 2
#define INFANTERY_TYPE 3
#define MONSTER_TYPE 4
#define WARMACHINE_TYPE 5
#define UNKNOWN 99

enum ModelType { BASE, SPECIAL, RARE, CHARACTER };

#endif // DEFINES_H
