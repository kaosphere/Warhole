#include "modelcharriot.h"


ModelCharriot::ModelCharriot(QObject *parent):
    ModelAbstract(parent)
{
}

ModelCharriot::ModelCharriot(const QString &n, const QString &move, const QString &weaponS,
                             const QString &balisticS, const QString &strength, const QString &toughness,
                             const QString &wounds, const QString &init, const QString &attacks,
                             const QString &leadership, const QString &save, const QString &invSave, const int points,
                             const int &widthBase, const int &lengthBase, const int &unitP, const QString &urlImage,
                             bool figSup, const QString &specRules,const ModelType &t, QObject* parent) :
    ModelAbstract(n,move,weaponS,balisticS, strength, toughness, wounds, init, attacks, leadership, save,
                  invSave, points, widthBase, lengthBase, unitP, urlImage, figSup, t, parent)
{
    specialRules = specRules;
}

// Copy constructor
ModelCharriot::ModelCharriot(const ModelCharriot &copy) : ModelAbstract(copy)
{
    specialRules = copy.specialRules;
    crew = copy.crew;
}

ModelCharriot::~ModelCharriot()
{
}

void ModelCharriot::initModelCharriotSystem()
{
    qRegisterMetaTypeStreamOperators<ModelCharriot>("ModelCharriot");
    qMetaTypeId<ModelCharriot>();
}

ModelCharriot *ModelCharriot::setFromFile(QString path)
{
    ModelCharriot* tmp = new ModelCharriot(*this);
    tmp->load(path);

    return tmp;
}

QDataStream& ModelCharriot::serializeOut(QDataStream& out)
{
    out << (*this);
    return out;
}

QDataStream & ModelCharriot::serializeIn(QDataStream &in)
{
    in >> (*this);
    return in;
}

ModelAbstract *ModelCharriot::clone()
{
    return new ModelCharriot(*this);
}

ModelCharriot *ModelCharriot::setFromUI(const ParamsfromUImodel *params)
{
    ModelCharriot* tmp = new ModelCharriot(*this);
    // ModelAbstract params
    tmp->setType(params->getType());
    tmp->setStats(params->getStats());
    tmp->setSquareBaseW(params->getWidthBase());
    tmp->setSquareBaseL(params->getLengthBase());
    tmp->setUnitPower(params->getUnitP());
    tmp->setFigSupInd(params->getFigSup());
    tmp->setUrlImage(params->getUrlImage());
    tmp->setImage(params->getImage());
    tmp->setOptions(params->getOptions());

    // ModelCharriot params
    tmp->setSpecialRules(params->getSpecRules());
    tmp->setCrew(params->getMorC());

    tmp->setBanner(params->getBanner());
    tmp->setBannerPoints(params->getBannerPoints());
    tmp->setChampion(params->getChampion());
    tmp->setChampionStats(params->getChampionStats());
    tmp->setMusician(params->getMusician());
    tmp->setMusicianPoints(params->getMusicianPoints());

    return tmp;
}

void ModelCharriot::load(QString path)
{
    ModelCharriot temp;
    
    QSettings readFile(path, QSettings::IniFormat);
    temp = readFile.value("ModelCharriot", qVariantFromValue(ModelCharriot())).value<ModelCharriot>();
    
    type = temp.getType();
    stats = temp.getStats();
    squareBaseW = temp.getSquareBaseW();
    squareBaseL = temp.getSquareBaseL();
    unitPower = temp.getUnitPower();
    
    urlImage = temp.getUrlImage();
    
    if(!temp.getImage().isNull())
    {
        image = temp.getImage();
    }
    
    figSupInd = temp.getFigSupInd();
    specialRules = temp.getSpecialRules();
    
    options = temp.getOptions();

    crew = temp.getCrew();

    banner = temp.getBanner();
    bannerPoints = temp.getBannerPoints();
    musician = temp.getMusician();
    musicianPoints = temp.getMusicianPoints();
    champion = temp.getChampion();
    championStats = temp.getChampionStats();
}

void ModelCharriot::save(QString path)
{
    QFile::remove(path);
    QSettings savedFile(path, QSettings::IniFormat);
    savedFile.setValue("ModelCharriot", qVariantFromValue(*this));
    savedFile.sync();
}

QString ModelCharriot::getSpecialRules() const
{
    return specialRules;
}

void ModelCharriot::setSpecialRules(const QString &value)
{
    specialRules = value;
}

QDataStream & operator <<(QDataStream & out, const ModelCharriot & obj)
{
    int nb;
    nb = obj.crew.size();

    out << SAVE_VERSION;
    obj.serializeOutBase(out);
    out << obj.specialRules
        << nb;

    for(int i = 0 ; i < obj.crew.size() ; i++)
    {
        out << obj.crew[i];
    }

    return out;
}

QDataStream & operator >>(QDataStream & in, ModelCharriot & obj)
{
    int nb;
    int version;

    in >> version;
    obj.serializeInBase(in);

    if( version < 3)
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
    in >> obj.specialRules;
    in >> nb;

    for(int i = 0 ; i < nb ; i++)
    {
        StatsModel s;
        in >> s;
        obj.addCrew(s);
    }
    
    return in;
}

QString ModelCharriot::displayStringInfo()
{
    QString s;
    QTextStream info(&s);
    info << "Model Cavalry : " << endl;
    info << displayBaseInfo();
    info << "====================================================" << endl;
    info << QString(QString::fromUtf8("Règles additionnelles : ")) << endl;
    info << specialRules << endl;
    info << "====================================================" << endl;
    info << QString(QString::fromUtf8("Statistique de l'équipage' : ")) << endl;
    QList<StatsModel>::iterator i;
    for(i = crew.begin(); i < crew.end() ; ++i)
    {
        info << "------------------" << endl;
        info << i->displayString() << endl;;
    }
    info << "====================================================" << endl;
    return s;
}

QString ModelCharriot::getHtml()
{
    QString html;
    html += getBaseHtml();
    html += "Règles additionnelles : <br/>\n";
    html += QString(specialRules.toHtmlEscaped() + "<br/>\n");
    html += "<br/>\n";
    html += QString("Liste de l'équipage : <br/>\n");
    QList<StatsModel>::iterator i;
    for(i = crew.begin(); i < crew.end() ; ++i)
    {
        html += QString("<li>\n");
        html += QString("%1 : <br/>\n").arg(i->getName());
        html += i->getHtml();
        html += QString("</li>\n");
    }
    html += "<br/>\n";

    return html;
}

QList<StatsModel> ModelCharriot::getCrew() const
{
    return crew;
}

void ModelCharriot::setCrew(const QList<StatsModel> &value)
{
    crew = value;
}

void ModelCharriot::addCrew(StatsModel c)
{
    crew << c;
}

void ModelCharriot::clearCrew()
{
    crew.clear();
}

int ModelCharriot::computePoints()
{
    //compute whole points of the model
    int points = computeBasePoints();
    QList<StatsModel>::Iterator j;
    for(j = crew.begin(); j < crew.end(); ++j)
    {
        points += j->getPoints();
    }
    return points;
}

int ModelCharriot::computePointsWithoutOptions()
{
    //compute whole points of the model
    int points = computeBasePointsWithoutOptions();
    QList<StatsModel>::Iterator j;
    for(j = crew.begin(); j < crew.end(); ++j)
    {
        points += j->getPoints();
    }
    return points;
}
