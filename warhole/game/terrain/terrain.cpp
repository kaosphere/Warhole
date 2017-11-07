#include "terrain.h"

using namespace QLogger;

const QString Terrain::LOG_ID_INFO = "Terrain_info";
const QString Terrain::LOG_ID_TRACE = "Terrain_trace";
const QString Terrain::LOG_ID_WARN = "Terrain_warn";
const QString Terrain::LOG_ID_ERR = "Terrain_err";

Terrain::Terrain(QObject *parent) : QObject(parent)
{
    QLoggerManager *manager = QLoggerManager::getInstance();
    manager->addDestination("./logs/lastrun.log", QStringList(LOG_ID_TRACE), QLogger::TraceLevel);
    manager->addDestination("./logs/lastrun.log", QStringList(LOG_ID_INFO), QLogger::InfoLevel);
    manager->addDestination("./logs/lastrun.log", QStringList(LOG_ID_ERR), QLogger::ErrorLevel);
    manager->addDestination("./logs/lastrun.log", QStringList(LOG_ID_WARN), QLogger::WarnLevel);

    name = "";
    type = OTHER;
    cover = NO_COVER;
    sightBreaker = false;
    dangerous = false;
    surmountable = false;
    resize = false;
    width = 0;
    heigth = 0;
    specialRules = "";
}

Terrain::Terrain(QString n, TerrainType t, CoverType c, bool sb, bool d,
                 bool s, bool r, int w, int h, QPixmap i, QString sr, QObject *parent) :
    QObject(parent)
{
    QLoggerManager *manager = QLoggerManager::getInstance();
    manager->addDestination("./logs/lastrun.log", QStringList(LOG_ID_TRACE), QLogger::TraceLevel);
    manager->addDestination("./logs/lastrun.log", QStringList(LOG_ID_INFO), QLogger::InfoLevel);
    manager->addDestination("./logs/lastrun.log", QStringList(LOG_ID_ERR), QLogger::ErrorLevel);
    manager->addDestination("./logs/lastrun.log", QStringList(LOG_ID_WARN), QLogger::WarnLevel);

    name = n;
    type = t;
    cover = c;
    sightBreaker = sb;
    dangerous = d;
    surmountable = s;
    resize = r;
    width = w;
    heigth = h;
    terrainImage = i;
    specialRules = sr;
}

Terrain::Terrain(const Terrain &other, QObject *parent) : QObject(parent)
{
    QLoggerManager *manager = QLoggerManager::getInstance();
    manager->addDestination("./logs/lastrun.log", QStringList(LOG_ID_TRACE), QLogger::TraceLevel);
    manager->addDestination("./logs/lastrun.log", QStringList(LOG_ID_INFO), QLogger::InfoLevel);
    manager->addDestination("./logs/lastrun.log", QStringList(LOG_ID_ERR), QLogger::ErrorLevel);
    manager->addDestination("./logs/lastrun.log", QStringList(LOG_ID_WARN), QLogger::WarnLevel);

    name = other.name;
    type = other.type;
    cover = other.cover;
    sightBreaker = other.sightBreaker;
    dangerous = other.dangerous;
    surmountable = other.surmountable;
    resize = other.resize;
    terrainImage = other.terrainImage;
    width = other.width;
    heigth = other.heigth;
    specialRules = other.specialRules;
}

Terrain::~Terrain()
{
}

Terrain& Terrain::operator =(const Terrain& other)
{
    name = other.name;
    type = other.type;
    cover = other.cover;
    sightBreaker = other.sightBreaker;
    dangerous = other.dangerous;
    surmountable = other.surmountable;
    resize = other.resize;
    terrainImage = other.terrainImage;
    width = other.width;
    heigth = other.heigth;
    specialRules = other.specialRules;

    return (*this);
}

bool Terrain::operator ==(const Terrain &other)
{
    if(name == other.name &&
            type == other.type &&
            cover == other.cover &&
            sightBreaker == other.sightBreaker &&
            dangerous == other.dangerous &&
            surmountable == other.surmountable &&
            resize == other.resize &&
            width == other.width &&
            heigth == other.heigth &&
            specialRules == other.specialRules)
        return true;
    else
        return false;
}

QDataStream& operator<<(QDataStream& out, const Terrain& obj)
{
    out << SAVE_VERSION
        << obj.name
        << obj.type
        << obj.cover
        << obj.sightBreaker
        << obj.dangerous
        << obj.surmountable
        << obj.resize
        << obj.terrainImage
        << obj.width
        << obj.heigth
        << obj.specialRules;

    return out;
}

QDataStream& operator>>(QDataStream& in, Terrain& obj)
{
    int version = 0;
    int cover;
    int type;

    in >> version;
    in >> obj.name;
    in >> type;
    obj.type = (TerrainType)type;
    in >> cover;
    obj.cover = (CoverType)cover;
    in >> obj.sightBreaker;
    in >> obj.dangerous;
    in >> obj.surmountable;
    in >> obj.resize;
    in >> obj.terrainImage;
    in >> obj.width;
    in >> obj.heigth;
    in >> obj.specialRules;

    return in;
}

void  Terrain::load(QString path)
{
    Terrain temp;

    QSettings readFile(path, QSettings::IniFormat);
    temp = readFile.value("Terrain", qVariantFromValue(Terrain())).value< Terrain>();

    name = temp.name;
    type = temp.type;
    cover = temp.cover;
    sightBreaker = temp.sightBreaker;
    dangerous = temp.dangerous;
    surmountable = temp.surmountable;
    resize = temp.resize;
    terrainImage = temp.terrainImage;
    width = temp.width;
    heigth = temp.heigth;
    specialRules = temp.specialRules;

    QLog_Info(LOG_ID_INFO,"Terrain loaded : \n" + displayString());
}

void Terrain::save(QString path)
{
    QLog_Info(LOG_ID_INFO, "save() : Saving Terrain file to path : " + path);

    QFile::remove(path);
    QSettings savedFile(path, QSettings::IniFormat);
    savedFile.setValue("Terrain", qVariantFromValue(*this));
    savedFile.sync();
}

void Terrain::initTerrainSystem()
{
    qRegisterMetaTypeStreamOperators<Terrain>("Terrain");
    qMetaTypeId<Terrain>();
}

QString Terrain::displayString()
{
    QString s;
    QTextStream info(&s);
    info << name << endl;
    switch(type)
    {
    case FOREST:
        info << tr("Forêt");
        break;
    case RIVER:
        info << tr("Rivière");
        break;
    case OBSTACLE:
        info << tr("Obstacle");
        break;
    case BUILDING:
        info << tr("Bâtiment");
        break;
    case HILL:
        info << tr("Colline");
        break;
    case CLIFF:
        info << tr("Falaise");
        break;
    case MARSHES:
        info << tr("Marécage");
        break;
    default:
        info << tr("Autre");
        break;
    }
    info << " (";
    switch(cover)
    {
    case LIGHT_COVER:
        info << tr("Couvert léger");
        break;
    case HEAVY_COVER:
        info << tr("Couvert lourd");
        break;
    default:
        info << tr("Pas de couvert");
        break;
    }
    info << ")" << endl;

    if(sightBreaker) info << tr("Bloque les lignes de vue") << endl;
    if(dangerous) info << tr("Terrain dangereux") << endl;
    if(!surmountable) info << tr("Terrain infranchissable") << endl;
    info << specialRules;

    return s;
}

QString Terrain::getSpecialRules() const
{
    return specialRules;
}

void Terrain::setSpecialRules(const QString &value)
{
    specialRules = value;
}


QString Terrain::getName() const
{
    return name;
}

void Terrain::setName(const QString &value)
{
    name = value;
}

int Terrain::getHeigth() const
{
    return heigth;
}

void Terrain::setHeigth(int value)
{
    heigth = value;
}

int Terrain::getWidth() const
{
    return width;
}

void Terrain::setWidth(int value)
{
    width = value;
}

bool Terrain::getResize() const
{
    return resize;
}

void Terrain::setResize(bool value)
{
    resize = value;
}

QPixmap Terrain::getTerrainImage() const
{
    return terrainImage;
}

void Terrain::setTerrainImage(const QPixmap &value)
{
    terrainImage = value;
}

bool Terrain::getSurmountable() const
{
    return surmountable;
}

void Terrain::setSurmountable(bool value)
{
    surmountable = value;
}

bool Terrain::getDangerous() const
{
    return dangerous;
}

void Terrain::setDangerous(bool value)
{
    dangerous = value;
}

bool Terrain::getSightBreaker() const
{
    return sightBreaker;
}

void Terrain::setSightBreaker(bool value)
{
    sightBreaker = value;
}

CoverType Terrain::getCover() const
{
    return cover;
}

void Terrain::setCover(const CoverType &value)
{
    cover = value;
}

TerrainType Terrain::getType() const
{
    return type;
}

void Terrain::setType(const TerrainType &value)
{
    type = value;
}
