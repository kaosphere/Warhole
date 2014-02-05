#include "unitabstract.h"

UnitAbstract::UnitAbstract()
{
    name = "";
    path = "";
    nbModels = 0;
    models.clear();
    type = UNKNOWN;
    musician = false;
    champion = false;
    skirmishers = false;
    banner = false;
}

UnitAbstract::UnitAbstract(const QString &n,
                           const QString &p,
                           const QList<ModelAbstract*> &l,
                           const int &t,
                           const bool &m,
                           const bool &s,
                           const bool &c,
                           const bool &b,
                           const StatsModel& st,
                           const int &nb)
{
    name = n;
    path = p;
    models = l;
    type = t;
    musician = m;
    skirmishers = s;
    champion = c;
    banner = b;
    championStats = st;
    nbModels = nb;
}

UnitAbstract::UnitAbstract(const UnitAbstract &u)
{
    name = u.name;
    path = u.path;
    models = u.models;
    type = u.type;
    musician = u.musician;
    skirmishers = u.skirmishers;
    champion = u.champion;
    banner = u.banner;
    championStats = u.championStats;
    nbModels = u.nbModels;
}

bool UnitAbstract::operator==(const UnitAbstract &u)
{
    if(musician == u.musician &&
            skirmishers == u.skirmishers &&
            champion == u.champion &&
            name == u.name &&
            models.size() == u.models.size() &&
            banner == u.banner &&
            type == u.type &&
            path == u.path &&
            nbModels == u.nbModels)
        return true;
    else return false;
}

int UnitAbstract::getType() const
{
    return type;
}

void UnitAbstract::setType(const int &value)
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

QList<ModelAbstract*> UnitAbstract::getModels() const
{
    return models;
}

void UnitAbstract::setModels(const QList<ModelAbstract*> &value)
{
    models = value;
}

void UnitAbstract::addModel(ModelAbstract* m)
{
    models.append(m);
}

void UnitAbstract::removeModel(ModelAbstract *m)
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

QDataStream &operator <<(QDataStream & out, const UnitAbstract & obj)
{
    out << obj.name
        << obj.type
        << obj.banner
        << obj.musician
        << obj.champion
        << obj.skirmishers
        << obj.championStats
        << obj.nbModels
        << obj.path;


    return out;
}

QDataStream &operator >>(QDataStream & in, UnitAbstract & obj)
{
    in >> obj.name;
    in >> obj.type;
    in  >> obj.banner;
    in  >> obj.musician;
    in  >> obj.champion;
    in  >> obj.skirmishers;
    in  >> obj.championStats;
    in  >> obj.nbModels;
    in  >> obj.path;

    //add all models to the list
    obj.loadAllModels();

    return in;
}

void UnitAbstract::loadAllModels()
{
    ModelAbstract * m;

    for(int i = 0; i < nbModels; i++)
    {
        switch(type)
        {
        case INFANTERY_TYPE:
            m = new ModelInfantery();
            static_cast<ModelCavalry*>(m)->load(path);
            models.append(m);
            break;
        case CAVALERY_TYPE:
            m = new ModelCavalry();
            static_cast<ModelCavalry*>(m)->load(path);
            models.append(m);
            break;
        case CHARACTER_TYPE:
            m = new ModelCharacter();
            static_cast<ModelCavalry*>(m)->load(path);
            models.append(m);
            break;
        case CHARRIOT_TYPE:
            m = new ModelCharriot();
            static_cast<ModelCavalry*>(m)->load(path);
            models.append(m);
            break;
        case MONSTER_TYPE:
            m = new ModelMonster();
            static_cast<ModelCavalry*>(m)->load(path);
            models.append(m);
            break;
        case WARMACHINE_TYPE:
            m = new ModelWarMachine();
            static_cast<ModelCavalry*>(m)->load(path);
            models.append(m);
            break;
        default:
            break;
        }
    }
}

void UnitAbstract::updateNbModels()
{
    nbModels = models.size();
}

QString UnitAbstract::getPath() const
{
    return path;
}

void UnitAbstract::setPath(const QString &value)
{
    path = value;
}

int UnitAbstract::getNbModels() const
{
    return nbModels;
}

void UnitAbstract::setNbModels(int value)
{
    nbModels = value;
}

