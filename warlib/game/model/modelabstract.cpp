#include "modelabstract.h"

ModelAbstract::ModelAbstract()
{
}

ModelAbstract::ModelAbstract(const StatsModel &stat,
                             const int &widthBase,
                             const int &lengthBase,
                             const int &unitP,
                             const QString &url,
                             bool figSup)
{
    stats = stat;
    squareBaseW = widthBase;
    squareBaseL = lengthBase;
    unitPower = unitP;
    
    image = new QPixmap(urlImage);

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
                             bool figSup)
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

    image = new QPixmap(urlImage);

    urlImage = url;

    figSupInd = figSup;

}

ModelAbstract::ModelAbstract(const ModelAbstract &copy)
{
    stats = copy.stats;
    urlImage = copy.urlImage;
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
}

ModelAbstract::~ModelAbstract(){}

void ModelAbstract::save(const QString path)
{
    Q_UNUSED(path);
    // We should never pass here
}

QDataStream& ModelAbstract::serializeOut(QDataStream& out)
{
    // We Should never pass here
    return out;
}

QDataStream& ModelAbstract::serializeIn(QDataStream &in)
{
    // We should never pass here
    return in;
}

ModelAbstract *ModelAbstract::setFromFile(const QString path)
{
    Q_UNUSED(path);
    return NULL;
}

QString ModelAbstract::displayStringInfo()
{
    return QString("ERROR");
}

QString ModelAbstract::displayBaseInfo()
{
    QString s;
    QTextStream info(&s);
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

QString ModelAbstract::getHtml()
{
    return QString("ERROR");
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

ModelAbstract *ModelAbstract::clone()
{
    // We should never pass here
    return NULL;
}

ModelAbstract *ModelAbstract::setFromUI(const ParamsfromUImodel *params)
{
    Q_UNUSED(params);
    //We should never pass here
    return NULL;
}


void ModelAbstract::load(const QString path)
{
    Q_UNUSED(path);
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

QPixmap *ModelAbstract::getImage() const
{
    return image;
}

void ModelAbstract::setImage(QPixmap *value)
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

QDataStream &operator <<(QDataStream & out, const ModelAbstract & obj)
{
    out << SAVE_VERSION
        << obj.stats
        << obj.squareBaseW
        << obj.squareBaseL
        << obj.unitPower
        << obj.figSupInd
        << obj.urlImage
        << obj.options.size();

    for(int i = 0 ; i < obj.options.size() ; i++)
    {
        out << obj.options[i];
    }

    out << obj.banner
        << obj.bannerPoints
        << obj.musician
        << obj.musicianPoints
        << obj.champion
        << obj.championStats;

    return out;
}

QDataStream &operator >>(QDataStream & in, ModelAbstract & obj)
{
    int nb;
    int version = 0;

    in >> version;
    in >> obj.stats;
    in >> obj.squareBaseW;
    in >> obj.squareBaseL;
    in >> obj.unitPower;
    in >> obj.figSupInd;
    in >> obj.urlImage;

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

    return in;
}
