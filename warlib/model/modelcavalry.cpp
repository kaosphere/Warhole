#include "modelcavalry.h"
#include <QDebug>

using namespace QLogger;

const QString ModelCavalry::LOG_ID_INFO = "ModelCavalry_info";
const QString ModelCavalry::LOG_ID_TRACE = "ModelCavalry_trace";
const QString ModelCavalry::LOG_ID_WARN = "ModelCavalry_warn";
const QString ModelCavalry::LOG_ID_ERR = "ModelCavalry_err";

ModelCavalry::ModelCavalry():
    ModelAbstract()
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
                           bool figSup, const QString &specRules, const ModelType &t) :
    ModelAbstract(n,move,weaponS,balisticS, strength, toughness, wounds, init, attacks, leadership, save,
                  invSave, points, widthBase, lengthBase, unitP, urlImage, figSup)
{
    QLoggerManager *manager = QLoggerManager::getInstance();
    manager->addDestination("./logs/lastrun.log", QStringList(LOG_ID_TRACE), QLogger::TraceLevel);
    manager->addDestination("./logs/lastrun.log", QStringList(LOG_ID_INFO), QLogger::InfoLevel);
    manager->addDestination("./logs/lastrun.log", QStringList(LOG_ID_ERR), QLogger::ErrorLevel);
    manager->addDestination("./logs/lastrun.log", QStringList(LOG_ID_WARN), QLogger::WarnLevel);
    
    specialRules = specRules;
    type = t;
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

    //image->load(urlImage);

    figSupInd = temp.getFigSupInd();
    specialRules = temp.getSpecialRules();

    options = temp.getOptions();

    mount = temp.getMount();
}

void ModelCavalry::save(QString path)
{
    QFile::remove(path);
    QSettings savedFile(path, QSettings::IniFormat);
    savedFile.setValue("ModelCavalry", qVariantFromValue(*this));
    savedFile.sync();
}

// Overloading of << operator
QDataStream & operator << (QDataStream & out, const ModelCavalry & obj)
{
    out << static_cast<ModelAbstract>(obj)
        << obj.type
        << obj.specialRules
        << obj.mount;

    return out;
}

// Overloading of >> operator
QDataStream & operator >> (QDataStream & in, ModelCavalry & obj)
{
    int type;

    in >> static_cast<ModelAbstract&>(obj);
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
    info << "Unité ";
    switch(type)
    {
    case 0:
        info << "Base" << endl;
        break;
    case 1:
        info << "Spciale" << endl;
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
    info << "Special Rules : " << endl;
    info << specialRules << endl;
    info << "====================================================" << endl;
    info << "Mount : " << mount.getName() << endl;
    info << mount.displayString();
    info << "====================================================" << endl;
    return s;
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
    int points = stats.getPoints();
    QList<OptionModel>::iterator i;
    for (i = options.begin(); i != options.end(); ++i)
    {
        points += i->getNbPoints();
    }
    points += mount.getPoints();
    return points;
}
