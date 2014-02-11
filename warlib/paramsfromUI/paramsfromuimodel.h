#ifndef PARAMSFROMUIMODEL_H
#define PARAMSFROMUIMODEL_H

#include <QString>
#include "stats/statsmodel.h"
#include "option/optionmodel.h"

class ParamsfromUImodel
{
public:
    ParamsfromUImodel();
    virtual ~ParamsfromUImodel();


    StatsModel getStats() const;
    void setStats(const StatsModel &value);

    QList<OptionModel> getOptions() const;
    void setOptions(const QList<OptionModel> &value);

    QString getName() const;
    void setName(const QString &value);

    QString getMove() const;
    void setMove(const QString &value);

    QString getWeaponS() const;
    void setWeaponS(const QString &value);

    QString getBalisticS() const;
    void setBalisticS(const QString &value);

    QString getStrength() const;
    void setStrength(const QString &value);

    QString getToughness() const;
    void setToughness(const QString &value);

    QString getWounds() const;
    void setWounds(const QString &value);

    QString getInit() const;
    void setInit(const QString &value);

    QString getAttacks() const;
    void setAttacks(const QString &value);

    QString getLeadership() const;
    void setLeadership(const QString &value);

    QString getSave() const;
    void setSave(const QString &value);

    QString getInvSave() const;
    void setInvSave(const QString &value);

    int getPoints() const;
    void setPoints(int value);

    int getWidthBase() const;
    void setWidthBase(int value);

    int getLengthBase() const;
    void setLengthBase(int value);

    int getUnitP() const;
    void setUnitP(int value);

    QString getUrlImage() const;
    void setUrlImage(const QString &value);

    bool getFigSup() const;
    void setFigSup(bool value);

    QString getSpecRules() const;
    void setSpecRules(const QString &value);

    bool getLord() const;
    void setLord(bool value);

    bool getGeneral() const;
    void setGeneral(bool value);

    bool getMage() const;
    void setMage(bool value);

    bool getMounted() const;
    void setMounted(bool value);

    bool getHasCrew() const;
    void setHasCrew(bool value);

    QList<StatsModel> getMorC() const;
    void setMorC(const QList<StatsModel> &value);

private:
    // modelabstract params
    StatsModel stats;
    QList<OptionModel> options;
    QString name;
    QString move;
    QString weaponS;
    QString balisticS;
    QString strength;
    QString toughness;
    QString wounds;
    QString init;
    QString attacks;
    QString leadership;
    QString save;
    QString invSave;
    int points;
    int widthBase;
    int lengthBase;
    int unitP;
    QString urlImage;
    bool figSup;
    // warMachine, monster, infantery, charriot, character, cavalery params
    QString specRules;
    // character params
    bool lord;
    bool general;
    bool mage;
    bool mounted;
    // monster params
    bool hasCrew;
    // mount or crew
    QList<StatsModel> mOrC;

};

#endif // PARAMSFROMUIMODEL_H
