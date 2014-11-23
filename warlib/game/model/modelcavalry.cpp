#include "modelcavalry.h"
#include <QDebug>

using namespace QLogger;

const QString ModelCavalry::LOG_ID_INFO = "ModelCavalry_info";
const QString ModelCavalry::LOG_ID_TRACE = "ModelCavalry_trace";
const QString ModelCavalry::LOG_ID_WARN = "ModelCavalry_warn";
const QString ModelCavalry::LOG_ID_ERR = "ModelCavalry_err";

ModelCavalry::ModelCavalry(QObject* parent):
    ModelAbstract(parent)
{
    QLoggerManager *manager = QLoggerManager::getInstance();
    manager->addDestination("./logs/lastrun.log", QStringList(LOG_ID_TRACE), QLogger::TraceLevel);
    manager->addDestination("./logs/lastrun.log", QStringList(LOG_ID_INFO), QLogger::InfoLevel);
    manager->addDestination("./logs/lastrun.log", QStringList(LOG_ID_ERR), QLogger::ErrorLevel);
    manager->addDestination("./logs/lastrun.log", QStringList(LOG_ID_WARN), QLogger::WarnLevel);

}

ModelCavalry::ModelCavalry(const QString &n, const QString &move, const QString &weaponS,
                           const QString &balisticS, const QString &strength, const QString &toughness,
                           const QString &wounds, const QString &init, const QString &attacks,
                           const QString &leadership, const QString &save, const QString &invSave, const int points,
                           const int &widthBase, const int &lengthBase, const int &unitP, const QString &urlImage,
                           bool figSup, const QString &specRules, const ModelType &t, QObject *parent) :
    ModelAbstract(n,move,weaponS,balisticS, strength, toughness, wounds, init, attacks, leadership, save,
                  invSave, points, widthBase, lengthBase, unitP, urlImage, figSup, parent)
{
    QLoggerManager *manager = QLoggerManager::getInstance();
    manager->addDestination("./logs/lastrun.log", QStringList(LOG_ID_TRACE), QLogger::TraceLevel);
    manager->addDestination("./logs/lastrun.log", QStringList(LOG_ID_INFO), QLogger::InfoLevel);
    manager->addDestination("./logs/lastrun.log", QStringList(LOG_ID_ERR), QLogger::ErrorLevel);
    manager->addDestination("./logs/lastrun.log", QStringList(LOG_ID_WARN), QLogger::WarnLevel);
    
    specialRules = specRules;
    type = t;
    // TODO : This one isn't up to date, but is never used.
}

// Copy constructor
ModelCavalry::ModelCavalry(const ModelCavalry &copy) : ModelAbstract(copy)
{
    QLoggerManager *manager = QLoggerManager::getInstance();
    manager->addDestination("./logs/lastrun.log", QStringList(LOG_ID_TRACE), QLogger::TraceLevel);
    manager->addDestination("./logs/lastrun.log", QStringList(LOG_ID_INFO), QLogger::InfoLevel);
    manager->addDestination("./logs/lastrun.log", QStringList(LOG_ID_ERR), QLogger::ErrorLevel);
    manager->addDestination("./logs/lastrun.log", QStringList(LOG_ID_WARN), QLogger::WarnLevel);

    specialRules = copy.specialRules;
    mount = copy.mount;
    type = copy.type;

}

//Destructor
ModelCavalry::~ModelCavalry()
{
}

QString ModelCavalry::getSpecialRules() const
{
    return specialRules;
}

void ModelCavalry::setSpecialRules(const QString &value)
{
    specialRules = value;
}

QDataStream& ModelCavalry::serializeOut(QDataStream& out)
{
    out << (*this);
    return out;
}

QDataStream & ModelCavalry::serializeIn(QDataStream &in)
{
    in >> (*this);
    return in;
}

// Init for serialization
void ModelCavalry::initModelCavalrySystem()
{
    qRegisterMetaTypeStreamOperators<ModelCavalry>("ModelCavalry");
    qMetaTypeId<ModelCavalry>();
}

ModelCavalry *ModelCavalry::setFromFile(QString path)
{
    ModelCavalry* tmp = new ModelCavalry(*this);
    tmp->load(path);

    return tmp;
}

ModelCavalry *ModelCavalry::setFromUI(const ParamsfromUImodel *params)
{
    ModelCavalry* tmp = new ModelCavalry(*this);

    // modelabstract params
    tmp->setType(params->getType());
    tmp->setStats(params->getStats());
    tmp->setSquareBaseW(params->getWidthBase());
    tmp->setSquareBaseL(params->getLengthBase());
    tmp->setUnitPower(params->getUnitP());
    tmp->setFigSupInd(params->getFigSup());
    tmp->setUrlImage(params->getUrlImage());

    QPixmap p;
    p.load(params->getUrlImage());
    tmp->setImage(p);
    tmp->setOptions(params->getOptions());

    // modelcavalery params
    tmp->setSpecialRules(params->getSpecRules());
    if(!params->getMorC().isEmpty())
    {
        tmp->setMount(params->getMorC().first());
    }
    else
    {
        QLog_Error(LOG_ID_ERR, "setFromUI : mOrC is empty, can't set mount.");
    }

    tmp->setBanner(params->getBanner());
    tmp->setBannerPoints(params->getBannerPoints());
    tmp->setChampion(params->getChampion());
    tmp->setChampionStats(params->getChampionStats());
    tmp->setMusician(params->getMusician());
    tmp->setMusicianPoints(params->getMusicianPoints());

    return tmp;
}

void  ModelCavalry::load(QString path)
{
    ModelCavalry temp;

    QSettings readFile(path, QSettings::IniFormat);
    temp = readFile.value("ModelCavalry", qVariantFromValue(ModelCavalry())).value< ModelCavalry>();

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

    mount = temp.getMount();

    banner = temp.getBanner();
    bannerPoints = temp.getBannerPoints();
    musician = temp.getMusician();
    musicianPoints = temp.getMusicianPoints();
    champion = temp.getChampion();
    championStats = temp.getChampionStats();
}

void ModelCavalry::save(QString path)
{
    QFile::remove(path);
    QSettings savedFile(path, QSettings::IniFormat);
    savedFile.setValue("ModelCavalry", qVariantFromValue(*this));
    savedFile.sync();
}

ModelAbstract *ModelCavalry::clone()
{
    return new ModelCavalry(*this);
}

// Overloading of << operator
QDataStream & operator << (QDataStream & out, const ModelCavalry & obj)
{
    out << SAVE_VERSION;
    obj.serializeOutBase(out);
    out << obj.type
        << obj.specialRules
        << obj.mount;

    return out;
}

// Overloading of >> operator
QDataStream & operator >> (QDataStream & in, ModelCavalry & obj)
{
    int type;
    int version = 0;

    in >> version;
    obj.serializeInBase(in);
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
    default:
        break;
    }
    in >> obj.specialRules;
    in >> obj.mount;

    return in;
}

QString ModelCavalry::displayStringInfo()
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
    default:
        info << "ERROR" << endl;
        break;
    }
    info << endl << "====================================================" << endl;
    info << "Model Cavalry : " << endl;
    info << displayBaseInfo();
    info << "====================================================" << endl;
    info << QString(QString::fromUtf8("Règles additionnelles : ")) << endl;
    info << specialRules << endl;
    info << "====================================================" << endl;
    info << "Monture : " << mount.getName() << endl;
    info << mount.displayString();
    info << "====================================================" << endl;
    return s;
}

QString ModelCavalry::getHtml()
{
    QString html;
    html += getBaseHtml();
    html += QString("<i>%1</i><br/>\n").arg(specialRules.toHtmlEscaped());
    html += QString("Statistique de la monture (%1)<br/>\n").arg(mount.getName());
    html += mount.getHtml();

    return html;
}

StatsModel ModelCavalry::getMount() const
{
    return mount;
}

void ModelCavalry::setMount(const StatsModel &value)
{
    mount = value;
}

ModelType ModelCavalry::getType() const
{
    return type;
}

void ModelCavalry::setType(const ModelType &value)
{
    type = value;
}

int ModelCavalry::computePoints()
{
    //compute whole points of the model
    int points = computeBasePoints();

    points += mount.getPoints();

    return points;
}

int ModelCavalry::computePointsWithoutOptions()
{
    //compute whole points of the model
    int points = computeBasePointsWithoutOptions();

    points += mount.getPoints();

    return points;
}
