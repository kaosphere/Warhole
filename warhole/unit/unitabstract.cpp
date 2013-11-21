#include "unitabstract.h"

bool UnitAbstract::getMusician() const
{
    return musician;
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

void UnitAbstract::addModel(const ModelAbstract &m)
{
    models.append(&m);
}

void UnitAbstract::removeModel(const ModelAbstract &m)
{
    models.removeOne(&m);
}

bool UnitAbstract::getBanner() const
{
    return banner;
}

void UnitAbstract::setBanner(bool value)
{
    banner = value;
}

void UnitAbstract::setMusician(bool value)
{
    musician = value;
}

UnitAbstract::UnitAbstract()
{
}
