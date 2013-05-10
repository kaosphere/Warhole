#ifndef MODELCHARACTER_H
#define MODELCHARACTER_H

#include <QObject>
#include <QtCore>
#include <QtWidgets>

#include "modelabstract.h"


class ModelCharacter : public ModelAbstract
{
public:
    ModelCharacter();

    ModelCharacter(const QString &n, const QString &move, const QString &weaponS, const QString &balisticS,
                  const QString &strength, const QString &toughness, const QString &wounds,
                  const QString &init, const QString &attacks, const QString &leadership,
                  const QString &save, const QString &invSave, const int points, const int &widthBase,
                  const int &lengthBase, const int &unitP, const QString& urlImage , bool figSup,
                  const QString& specRules, bool lord, bool general, bool mage, bool mounted);
    ModelCharacter(const ModelCharacter &copy);

    QString getSpecialRules() const;
    void setSpecialRules(const QString &value);

    bool getIsALord() const;
    void setIsALord(bool value);

    bool getIsTheGeneral() const;
    void setIsTheGeneral(bool value);

    bool getIsAMage() const;
    void setIsAMage(bool value);

    bool getIsMounted() const;
    void setIsMounted(bool value);

private:
    QString specialRules;
    bool isALord;
    bool isTheGeneral;
    bool isAMage;
    bool isMounted;

    //ModelAbstract *mount;
};

#endif // MODELCHARACTER_H
