#include "modelcharacter.h"

using namespace QLogger;

const QString ModelCharacter::LOG_ID_INFO = "ModelCharacter_info";
const QString ModelCharacter::LOG_ID_TRACE = "ModelCharacter_trace";
const QString ModelCharacter::LOG_ID_WARN = "ModelCharacter_warn";
const QString ModelCharacter::LOG_ID_ERR = "ModelCharacter_err";

ModelCharacter::ModelCharacter(QObject* parent):
    ModelAbstract(parent)
{
    QLoggerManager *manager = QLoggerManager::getInstance();
    manager->addDestination("./logs/lastrun.log", QStringList(LOG_ID_TRACE), QLogger::TraceLevel);
    manager->addDestination("./logs/lastrun.log", QStringList(LOG_ID_INFO), QLogger::InfoLevel);
    manager->addDestination("./logs/lastrun.log", QStringList(LOG_ID_ERR), QLogger::ErrorLevel);
    manager->addDestination("./logs/lastrun.log", QStringList(LOG_ID_WARN), QLogger::WarnLevel);
}

ModelCharacter::ModelCharacter(const QString &n, const QString &move, const QString &weaponS,
                               const QString &balisticS, const QString &strength, const QString &toughness,
                               const QString &wounds, const QString &init, const QString &attacks,
                               const QString &leadership, const QString &save, const QString &invSave, const int points,
                               const int &widthBase, const int &lengthBase, const int &unitP, const QString &urlImage,
                               bool figSup, const QString &specRules, bool lord, bool general, bool mage,
                               bool mounted, bool gb, QObject *parent) :
    ModelAbstract(n,move,weaponS,balisticS, strength, toughness, wounds, init, attacks, leadership, save,
                  invSave, points, widthBase, lengthBase, unitP, urlImage, figSup, parent)
{
    QLoggerManager *manager = QLoggerManager::getInstance();
    manager->addDestination("./logs/lastrun.log", QStringList(LOG_ID_TRACE), QLogger::TraceLevel);
    manager->addDestination("./logs/lastrun.log", QStringList(LOG_ID_INFO), QLogger::InfoLevel);
    manager->addDestination("./logs/lastrun.log", QStringList(LOG_ID_ERR), QLogger::ErrorLevel);
    manager->addDestination("./logs/lastrun.log", QStringList(LOG_ID_WARN), QLogger::WarnLevel);

    specialRules = specRules;
    isALord = lord;
    isTheGeneral = general;
    isAMage = mage;
    isMounted = mounted;
    hasGB = gb;
}

ModelCharacter::ModelCharacter(const ModelCharacter &copy) : ModelAbstract(copy)
{
    QLoggerManager *manager = QLoggerManager::getInstance();
    manager->addDestination("./logs/lastrun.log", QStringList(LOG_ID_TRACE), QLogger::TraceLevel);
    manager->addDestination("./logs/lastrun.log", QStringList(LOG_ID_INFO), QLogger::InfoLevel);
    manager->addDestination("./logs/lastrun.log", QStringList(LOG_ID_ERR), QLogger::ErrorLevel);
    manager->addDestination("./logs/lastrun.log", QStringList(LOG_ID_WARN), QLogger::WarnLevel);
    specialRules = copy.specialRules;
    isALord = copy.isALord;
    isTheGeneral = copy.isTheGeneral;
    isAMage = copy.isAMage;
    isMounted = copy.isMounted;
    mount = copy.mount;
    hasGB = copy.hasGB;
}

ModelCharacter::~ModelCharacter()
{
}

void ModelCharacter::initModelCharacterSystem()
{
    qRegisterMetaTypeStreamOperators<ModelCharacter>("ModelCharacter");
    qMetaTypeId<ModelCharacter>();
}

ModelCharacter *ModelCharacter::setFromFile(QString path)
{
    ModelCharacter* tmp = new ModelCharacter(*this);
    tmp->load(path);
    
    return tmp;
}

QDataStream& ModelCharacter::serializeOut(QDataStream& out)
{
    out << (*this);
    return out;
}

QDataStream & ModelCharacter::serializeIn(QDataStream &in)
{
    in >> (*this);
    return in;
}

ModelAbstract *ModelCharacter::clone()
{
    return new ModelCharacter(*this);
}

ModelCharacter *ModelCharacter::setFromUI(const ParamsfromUImodel *params)
{
    qDebug() << "yay this is setfromUI in modelCHARACTER !";
    
    ModelCharacter* tmp = new ModelCharacter(*this);
    // ModelAbstract params
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
    
    // ModelCharacter params
    tmp->setSpecialRules(params->getSpecRules());
    if(!params->getMorC().isEmpty())
        tmp->setMount(params->getMorC().first());
    else
        QLog_Error(LOG_ID_ERR, "setFromUI : mOrC list is empty, can't load mount.");
    tmp->setIsALord(params->getLord());
    tmp->setIsAMage(params->getMage());
    tmp->setIsTheGeneral(params->getGeneral());
    tmp->setIsMounted(params->getMounted());
    tmp->setHasGB(params->getHasGB());
    
    return tmp;
}

void ModelCharacter::load(QString path)
{
    ModelCharacter temp;
    QSettings readFile(path, QSettings::IniFormat);
    temp = readFile.value("ModelCharacter", qVariantFromValue( ModelCharacter())).value< ModelCharacter>();
    
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
    isALord = temp.getIsALord();
    isTheGeneral = temp.getIsTheGeneral();
    isAMage = temp.getIsAMage();
    isMounted = temp.getIsMounted();
    hasGB = temp.getHasGB();
    
    options = temp.getOptions();
    
    mount = temp.getMount();

    // fill those to prevent problems
    musicianPoints = 0;
    bannerPoints = 0;
    banner = false;
    musician = false;
    champion = false;
}

void ModelCharacter::save(QString path)
{
    QFile::remove(path);
    QSettings savedFile(path, QSettings::IniFormat);
    savedFile.setValue("ModelCharacter", qVariantFromValue(*this));
    savedFile.sync();
}

QString ModelCharacter::displayStringInfo()
{
    QString s;
    QTextStream info(&s);
    info << endl << "====================================================" << endl;
    info << "Model Character : " << endl;
    info << displayBaseInfo();
    info << "====================================================" << endl;
    info << QString(QString::fromUtf8("Règles additionnelles : ")) << endl;
    info << specialRules << endl;
    info << "====================================================" << endl;
    info << QString(QString::fromUtf8("Général de l'armée : ")) << isTheGeneral << endl;
    info << "Est un seigneur : " << isALord << endl;
    info << "Est un mage : " << isAMage << endl;
    info << QString(QString::fromUtf8("Est monté : ")) << isMounted << endl;
    info << QString(QString::fromUtf8("Porteur de la grande bannière : ")) << hasGB << endl;
    if(isMounted)
    {
        info << "=============" << endl;
        info << "Mount : " << mount.getName() << endl;
        info << mount.displayString();
    }
    info << "====================================================" << endl;
    return s;
}

QString ModelCharacter::getHtml()
{
    QString html;
    if(isALord) html += QString("<h2>Seigneur");
    if(isAMage) html += QString(" Mage</h2>\n");
    else html += QString("</h2>\n");
    if(hasGB) html += QString("<i>Porteur de la Grande Bannière.</i>\n");
    if(isTheGeneral) html += QString("<i>Général de l'armée.</i>\n");
    html += getBaseHtml();
    html += "Règles additionnelles : <br/>\n";
    html += QString(specialRules.toHtmlEscaped() + "<br/>\n");
    html += "<br/>\n";
    if(isMounted)
    {
        html += QString("Statistique de la monture (%1)<br/>\n").arg(mount.getName());
        html += mount.getHtml();
    }
    return html;
}

QString ModelCharacter::getSpecialRules() const
{
    return specialRules;
}

void ModelCharacter::setSpecialRules(const QString &value)
{
    specialRules = value;
}


bool ModelCharacter::getIsALord() const
{
    return isALord;
}

void ModelCharacter::setIsALord(bool value)
{
    isALord = value;
}

bool ModelCharacter::getIsTheGeneral() const
{
    return isTheGeneral;
}

void ModelCharacter::setIsTheGeneral(bool value)
{
    isTheGeneral = value;
}
bool ModelCharacter::getIsAMage() const
{
    return isAMage;
}

void ModelCharacter::setIsAMage(bool value)
{
    isAMage = value;
}

bool ModelCharacter::getIsMounted() const
{
    return isMounted;
}

void ModelCharacter::setIsMounted(bool value)
{
    isMounted = value;
}

bool ModelCharacter::getHasGB() const
{
    return hasGB;
}

void ModelCharacter::setHasGB(bool value)
{
    hasGB = value;
}

QDataStream & operator <<(QDataStream & out, const ModelCharacter & obj)
{
    out << SAVE_VERSION;
    obj.serializeOutBase(out);
    out << obj.specialRules
        << obj.isALord
        << obj.isTheGeneral
        << obj.isAMage
        << obj.isMounted
        << obj.hasGB
        << obj.mount;
    
    return out;
}

QDataStream & operator >>(QDataStream & in, ModelCharacter & obj)
{
    int version = 0;

    in >> version;
    obj.serializeInBase(in);
    in >> obj.specialRules;
    in >> obj.isALord;
    in >> obj.isTheGeneral;
    in >> obj.isAMage;
    in >> obj.isMounted;
    in >> obj.hasGB;
    in >> obj.mount;
    
    return in;
}

StatsModel ModelCharacter::getMount() const
{
    return mount;
}

void ModelCharacter::setMount(const StatsModel &value)
{
    mount = value;
}

int ModelCharacter::computePoints()
{
    //compute whole points of the model
    int points = computeBasePoints();
    if(isMounted)
        points += mount.getPoints();
    return points;
}

int ModelCharacter::computePointsWithoutOptions()
{
    //compute whole points of the model
    int points = computeBasePointsWithoutOptions();
    points += mount.getPoints();
    return points;
}
