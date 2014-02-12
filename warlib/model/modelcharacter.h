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
    virtual ~ModelCharacter();

    static void initModelCharacterSystem();
    virtual ModelCharacter* setFromFile(QString path);
    virtual ModelCharacter* setFromUI(const ParamsfromUImodel* params);
    virtual void load(QString path);
    virtual void save(QString path);

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

    QList<StatsModel> getMount() const;
    void setMount(const QList<StatsModel> &value);
    void addMount(StatsModel m);
    void clearMount();

    virtual int computePoints();

private:
    QString specialRules;
    bool isALord;
    bool isTheGeneral;
    bool isAMage;
    bool isMounted;

    QList<StatsModel> mount;

    friend QDataStream & operator << (QDataStream &, const ModelCharacter &);
    friend QDataStream & operator >> (QDataStream &, ModelCharacter &);

    //ModelAbstract *mount;
};

Q_DECLARE_METATYPE( ModelCharacter)
QDataStream & operator << (QDataStream & out, const  ModelCharacter &);
QDataStream & operator >> (QDataStream & in,  ModelCharacter &);

#endif // MODELCHARACTER_H
