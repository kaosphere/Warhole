#include "unitabstract.h"

UnitAbstract::UnitAbstract()
{
    name = "";
    models.clear();
    type = "UNKNOWN";
    musician = false;
    champion = false;
    skirmishers = false;
    banner = false;
}

UnitAbstract::UnitAbstract(const QString &n, const QList<ModelAbstract *> &l, const QString &t, const bool &m, const bool &s, const bool &c, const bool &b,
                           const StatsModel& st)
{
    name = n;
    models = l;
    type = t;
    musician = m;
    skirmishers = s;
    champion = c;
    banner = b;
    championStats = st;
}

UnitAbstract::UnitAbstract(const UnitAbstract &u)
{
    name = u.name;
    models = u.models;
    type = u.type;
    musician = u.musician;
    skirmishers = u.skirmishers;
    champion = u.champion;
    banner = u.banner;
    championStats = u.championStats;
}

bool UnitAbstract::operator==(const UnitAbstract &u)
{
    if(musician == u.musician && skirmishers == u.skirmishers && champion == u.champion &&
            name == u.name && models.size() == u.models.size() && banner == u.banner &&
            type == u.type)
        return true;
    else return false;
}

QString UnitAbstract::getType() const
{
    return type;
}

void UnitAbstract::setType(const QString &value)
{
    type = value;
}


bool UnitAbstract::getMusician() const
{
    return musician;
}

void UnitAbstract::setMusician(bool value)
{
    musician = value;
}

bool UnitAbstract::getSkirmishers() const
{
    return skirmishers;
}

void UnitAbstract::setSkirmishers(bool value)
{
    skirmishers = value;
}

bool UnitAbstract::getChampion() const
{
    return champion;
}

void UnitAbstract::setChampion(bool value)
{
    champion = value;
}

QString UnitAbstract::getName() const
{
    return name;
}

void UnitAbstract::setName(const QString &value)
{
    name = value;
}

QList<ModelAbstract *> UnitAbstract::getModels() const
{
    return models;
}

void UnitAbstract::setModels(const QList<ModelAbstract *> &value)
{
    models = value;
}

void UnitAbstract::addModel(ModelAbstract * m)
{
    models.append(m);
}

void UnitAbstract::removeModel(ModelAbstract * m)
{
    models.removeOne(m);
}

bool UnitAbstract::getBanner() const
{
    return banner;
}

void UnitAbstract::setBanner(bool value)
{
    banner = value;
}

StatsModel UnitAbstract::getChampionStats() const
{
    return championStats;
}

void UnitAbstract::setChampionStats(const StatsModel &value)
{
    championStats = value;
}

