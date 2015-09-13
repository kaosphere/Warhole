#include "modelabstract.h"

ModelAbstract::ModelAbstract(QObject *parent) : QObject(parent)
{
    bannerPoints = 0;
    musicianPoints = 0;
    banner = false;
    musician = false;
    champion = false;
    type = BASE;
}

ModelAbstract::ModelAbstract(const StatsModel &stat,
                             const int &widthBase,
                             const int &lengthBase,
                             const int &unitP,
                             const QString &url,
                             bool figSup, QObject* parent) : QObject (parent)
{
    stats = stat;
    squareBaseW = widthBase;
    squareBaseL = lengthBase;
    unitPower = unitP;
    
    image.load(urlImage);

    urlImage = url;
    
    figSupInd = figSup;
}

ModelAbstract::ModelAbstract(const QString &n,
                             const QString &move,
                             const QString &weaponS,
                             const QString &balisticS,
                             const QString &strength,
                             const QString &toughness,
                             const QString &wounds,
                             const QString &init,
                             const QString &attacks,
                             const QString &leadership,
                             const QString &save,
                             const QString &invSave,
                             const int points,
                             const int &widthBase,
                             const int &lengthBase,
                             const int &unitP,
                             const QString &url,
                             bool figSup,
                             ModelType modType,
                             QObject *parent) : QObject(parent)
{
    stats.setName(n);
    stats.setM(move);
    stats.setWs(weaponS);
    stats.setBs(balisticS);
    stats.setS(strength);
    stats.setT(toughness);
    stats.setW(wounds);
    stats.setI(init);
    stats.setA(attacks);
    stats.setLd(leadership);
    stats.setSvg(save);
    stats.setSvgInv(invSave);
    stats.setPoints(points);

    squareBaseW = widthBase;
    squareBaseL = lengthBase;
    unitPower = unitP;

    image.load(urlImage);

    urlImage = url;

    figSupInd = figSup;
    type = modType;

}

ModelAbstract::ModelAbstract(const ModelAbstract &copy) : QObject(copy.parent())
{
    stats = copy.stats;
    urlImage = copy.urlImage;
    image = copy.image;
    squareBaseW = copy.squareBaseW;
    squareBaseL = copy.squareBaseL;
    unitPower = copy.unitPower;
    options = copy.options;
    banner = copy.banner;
    bannerPoints = copy.bannerPoints;
    musician = copy.musician;
    musicianPoints = copy.musicianPoints;
    champion = copy.champion;
    championStats = copy.championStats;
    type = copy.type;
}

ModelAbstract::~ModelAbstract()
{
}


QString ModelAbstract::displayBaseInfo()
{
    QString s;
    QTextStream info(&s);
    info << endl << "====================================================" << endl;
    info << QString(QString::fromUtf8("Unité"));
    switch(type)
    {
    case 0:
        info << "Base" << endl;
        break;
    case 1:
        info << QString(QString::fromUtf8("Spéciale")) << endl;
        break;
    case 2:
        info << "Rare" << endl;
        break;
    case 3:
        info << "Personnage" << endl;
        break;
    default:
        info << "ERROR" << endl;
        break;
    }
    info << endl << "====================================================" << endl;
    info << stats.getName() << endl;
    info << "Points : " << computePoints() << endl;
    info << "====================================================" << endl;
    info << stats.displayString();
    info << "====================================================" << endl;
    info << "Available options : " << endl;
    QList<OptionModel>::iterator i;
    for(i = options.begin(); i < options.end() ; ++i)
    {
        info << "----------------------------" << endl;
        info << i->displayString() << endl;
    }
    if(musician)
    {
        info << "Has a musician for " << musicianPoints << " points." << endl;
    }
    else info << "Has no musician (" << musicianPoints << " pts)" << endl;
    if(banner)
    {
        info << "Has a banner for " << bannerPoints << " points." << endl;
    }
    else info << "Has no banner (" << musicianPoints << " pts)" << endl;
    if(champion)
    {
        info << "Has a champion : " << endl;
        info << championStats.displayString();
    }
    else
    {
        info << "Has no champion." << endl;
        info << championStats.displayString();
    }

    return s;
}

QString ModelAbstract::getBaseHtml()
{
    QString html;
    html += QString("%1</h2>\n").arg(stats.getName());
	html += stats.getHtml();
	QList<OptionModel>::iterator i;
    for(i = options.begin(); i < options.end() ; ++i)
    {
        if(i->isActivated())
        {
            html += "<li>";
            html += i->getHtml();
            html += "</li>\n";
        }
	}
	html += "<br/>\n";
	
    return html;
}

ModelAbstract &ModelAbstract::operator =(const ModelAbstract &other)
{
    stats = other.stats;
    squareBaseW = other.squareBaseW;
    squareBaseL = other.squareBaseL;
    unitPower = other.unitPower;
    figSupInd = other.figSupInd;
    urlImage = other.urlImage;
    image = other.image;
    options = other.options;
    banner = other.banner;
    bannerPoints = other.bannerPoints;
    musician = other.musician;
    musicianPoints = other.musicianPoints;
    champion = other.champion;
    championStats = other.championStats;
    type = other.type;

    return *this;
}


StatsModel ModelAbstract::getStats() const
{
    return stats;
}

void ModelAbstract::setStats(const StatsModel &value)
{
    stats = value;
}


int ModelAbstract::getUnitPower() const
{
    return unitPower;
}

void ModelAbstract::setUnitPower(int value)
{
    unitPower = value;
}

QPixmap &ModelAbstract::getImage()
{
    return image;
}

void ModelAbstract::setImage(QPixmap value)
{
    image = value;
}

int ModelAbstract::getSquareBaseL() const
{
    return squareBaseL;
}

void ModelAbstract::setSquareBaseL(int value)
{
    squareBaseL = value;
}

int ModelAbstract::getSquareBaseW() const
{
    return squareBaseW;
}

void ModelAbstract::setSquareBaseW(int value)
{
    squareBaseW = value;
}

bool ModelAbstract::getFigSupInd() const
{
    return figSupInd;
}

void ModelAbstract::setFigSupInd(bool value)
{
    figSupInd = value;
}


QList<OptionModel> ModelAbstract::getOptions() const
{
    return options;
}

void ModelAbstract::setOptions(const QList<OptionModel> &value)
{
    options = value;
}

void ModelAbstract::addOption(const OptionModel &opt)
{
    options << opt;
}

void ModelAbstract::removeOption(const OptionModel& opt)
{
    options.removeOne(opt);
}

void ModelAbstract::clearOptions()
{
    options.clear();
}

QString ModelAbstract::getUrlImage() const
{
    return urlImage;
}

void ModelAbstract::setUrlImage(const QString &value)
{
    urlImage = value;
}

StatsModel ModelAbstract::getChampionStats() const
{
    return championStats;
}

void ModelAbstract::setChampionStats(const StatsModel &value)
{
    championStats = value;
}

bool ModelAbstract::getChampion() const
{
    return champion;
}

void ModelAbstract::setChampion(bool value)
{
    champion = value;
}

int ModelAbstract::getMusicianPoints() const
{
    return musicianPoints;
}

void ModelAbstract::setMusicianPoints(int value)
{
    musicianPoints = value;
}

bool ModelAbstract::getMusician() const
{
    return musician;
}

void ModelAbstract::setMusician(bool value)
{
    musician = value;
}


bool ModelAbstract::getBanner() const
{
    return banner;
}

void ModelAbstract::setBanner(bool value)
{
    banner = value;
}

int ModelAbstract::getBannerPoints() const
{
    return bannerPoints;
}

void ModelAbstract::setBannerPoints(int value)
{
    bannerPoints = value;
}

int ModelAbstract::computePoints()
{
    return 0;
}

int ModelAbstract::getRegimentPoints()
{
    int points = 0;
    QList<OptionModel>::iterator i;
    for (i = options.begin(); i != options.end(); ++i)
    {
        if(i->isActivated() && i->isRegimentOptions())
            points += i->getNbPoints();
    }
    return points;
}

int ModelAbstract::computeBasePoints()
{
    int points = stats.getPoints();
    QList<OptionModel>::iterator i;
    for (i = options.begin(); i != options.end(); ++i)
    {
        if(i->isActivated() && !i->isRegimentOptions())
            points += i->getNbPoints();
    }
    return points;
}

int ModelAbstract::computeBasePointsWithoutOptions()
{
    return stats.getPoints();
}

ModelType ModelAbstract::getType() const
{
    return type;
}

void ModelAbstract::setType(const ModelType &value)
{
    type = value;
}


QDataStream &ModelAbstract::serializeInBase(QDataStream &in)
{
    in >> (*this);
    return in;
}

QDataStream &ModelAbstract::serializeOutBase(QDataStream &out) const
{
    out << (*this);
    return out;
}


QDataStream &operator <<(QDataStream & out, const ModelAbstract & obj)
{
    bool i;
    out << SAVE_VERSION
        << obj.stats
        << obj.squareBaseW
        << obj.squareBaseL
        << obj.unitPower
        << obj.figSupInd
        << obj.urlImage;

    if(!obj.image.isNull())
    {
        i = true;
        out << i;
        out << obj.image;
    }
    else
    {
        i = false;
        out << i;
    }
    out << obj.options.size();

    for(int i = 0 ; i < obj.options.size() ; i++)
    {
        out << obj.options[i];
    }

    out << obj.banner
        << obj.bannerPoints
        << obj.musician
        << obj.musicianPoints
        << obj.champion
        << obj.championStats
        << obj.type;

    return out;
}

QDataStream &operator >>(QDataStream & in, ModelAbstract & obj)
{
    int nb;
    int version = 0;
    bool i = false;

    in >> version;
    in >> obj.stats;
    in >> obj.squareBaseW;
    in >> obj.squareBaseL;
    in >> obj.unitPower;
    in >> obj.figSupInd;
    in >> obj.urlImage;

    if(version >= 2)
    {
        in >> i;
        if(i)
        {
            in >> obj.image;
        }
    }

    in >> nb;

    for(int i = 0 ; i < nb ; i++)
    {
        OptionModel o;
        in >> o;
        obj.addOption(o);
    }

    in >> obj.banner;
    in >> obj.bannerPoints;
    in >> obj.musician;
    in >> obj.musicianPoints;
    in >> obj.champion;
    in >> obj.championStats;

    if (version >= 3)
    {
        int type = 0;
        in >> type;

        switch(type)
        {
        case 0:
            obj.type = BASE;
            break;
        case 1:
            obj.type = SPECIAL;
            break;
        case 2:
            obj.type = RARE;
            break;
        case 3:
            obj.type = CHARACTER;
            break;
        default:
            break;
        }
     }

    return in;
}
