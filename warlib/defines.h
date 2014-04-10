#ifndef DEFINES_H
#define DEFINES_H

#include <QString>
#include <QStringList>

const QString MODEL_PATH("./models");

const QString CAVALERY_STRING("Cavalerie");
const QString CHARACTER_STRING("Personnage");
const QString CHARRIOT_STRING("Char");
const QString INFANTERY_STRING("Infanterie");
const QString MONSTER_STRING("Monstre");
const QString WARMACHINE_STRING("Machine de Guerre");

const QStringList OPTION_HEADER(QStringList()
                                << QObject::tr("Choisir")
                                << QObject::tr("Nom")
                                << QObject::tr("Pts")
                                << QObject::tr("Règles"));

#define CAVALERY_TYPE 0
#define CHARACTER_TYPE 1
#define CHARRIOT_TYPE 2
#define INFANTERY_TYPE 3
#define MONSTER_TYPE 4
#define WARMACHINE_TYPE 5
#define UNKNOWN 99

enum ModelType { BASE, SPECIAL, RARE };


#endif // DEFINES_H
