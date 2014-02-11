#include "regimentabstract.h"

RegimentAbstract::RegimentAbstract()
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

RegimentAbstract::RegimentAbstract(const QString &n,
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

RegimentAbstract::RegimentAbstract(const RegimentAbstract &u)
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

bool RegimentAbstract::operator==(const RegimentAbstract &u)
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

int RegimentAbstract::getType() const
{
    return type;
}

void RegimentAbstract::setType(const int &value)
{
    type = value;
}


bool RegimentAbstract::getMusician() const
{
    return musician;
}

void RegimentAbstract::setMusician(bool value)
{
    musician = value;
}

bool RegimentAbstract::getSkirmishers() const
{
    return skirmishers;
}

void RegimentAbstract::setSkirmishers(bool value)
{
    skirmishers = value;
}

bool RegimentAbstract::getChampion() const
{
    return champion;
}

void RegimentAbstract::setChampion(bool value)
{
    champion = value;
}

QString RegimentAbstract::getName() const
{
    return name;
}

void RegimentAbstract::setName(const QString &value)
{
    name = value;
}

QList<ModelAbstract*> RegimentAbstract::getModels() const
{
    return models;
}

void RegimentAbstract::setModels(const QList<ModelAbstract*> &value)
{
    models = value;
}

void RegimentAbstract::addModel(ModelAbstract* m)
{
    models.append(m);
}

void RegimentAbstract::removeModel(ModelAbstract *m)
{
    models.removeOne(m);
}

bool RegimentAbstract::getBanner() const
{
    return banner;
}

void RegimentAbstract::setBanner(bool value)
{
    banner = value;
}

StatsModel RegimentAbstract::getChampionStats() const
{
    return championStats;
}

void RegimentAbstract::setChampionStats(const StatsModel &value)
{
    championStats = value;
}

QDataStream &operator <<(QDataStream & out, const RegimentAbstract & obj)
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

QDataStream &operator >>(QDataStream & in, RegimentAbstract & obj)
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

void RegimentAbstract::loadAllModels()
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

void RegimentAbstract::updateNbModels()
{
    nbModels = models.size();
}

QString RegimentAbstract::getPath() const
{
    return path;
}

void RegimentAbstract::setPath(const QString &value)
{
    path = value;
}

int RegimentAbstract::getNbModels() const
{
    return nbModels;
}

void RegimentAbstract::setNbModels(int value)
{
    nbModels = value;
}

