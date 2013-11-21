#include "unitabstract.h"

UnitAbstract::UnitAbstract()
{
}

bool UnitAbstract::operator ==(const UnitAbstract &u)
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



