#include "modelcharacter.h"

using namespace QLogger;

const QString ModelCharacter::LOG_ID_INFO = "ModelCharacter_info";
const QString ModelCharacter::LOG_ID_TRACE = "ModelCharacter_trace";
const QString ModelCharacter::LOG_ID_WARN = "ModelCharacter_warn";
const QString ModelCharacter::LOG_ID_ERR = "ModelCharacter_err";

ModelCharacter::ModelCharacter():
    ModelAbstract()
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
                               bool mounted) :
    ModelAbstract(n,move,weaponS,balisticS, strength, toughness, wounds, init, attacks, leadership, save,
                  invSave, points, widthBase, lengthBase, unitP, urlImage, figSup)
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
    
    //image->load(urlImage);
    
    figSupInd = temp.getFigSupInd();
    specialRules = temp.getSpecialRules();
    isALord = temp.getIsALord();
    isTheGeneral = temp.getIsTheGeneral();
    isAMage = temp.getIsAMage();
    isMounted = temp.getIsMounted();
    
    options = temp.getOptions();

    mount = temp.getMount();
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
    info << "Model Cavalry : " << endl;
    info << displayBaseInfo();
    info << "====================================================" << endl;
    info << "Special Rules : " << endl;
    info << specialRules << endl;
    info << "====================================================" << endl;
    info << "Is the general : " << isTheGeneral << endl;
    info << "Is a lord : " << isALord << endl;
    info << "Is a mage : " << isAMage << endl;
    info << "Is mounted : " << isMounted << endl;
	if(isMounted)
	{
        info << "=============" << endl;
        info << "Mount stats : " << endl;
        info << mount.displayString();
	}
    info << "====================================================" << endl;
    return s;
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

QDataStream & operator <<(QDataStream & out, const ModelCharacter & obj)
{
    out << static_cast<ModelAbstract>(obj)
        << obj.specialRules
        << obj.isALord
        << obj.isTheGeneral
        << obj.isAMage
        << obj.isMounted
        << obj.mount;

    return out;
}

QDataStream & operator >>(QDataStream & in, ModelCharacter & obj)
{
    in >> static_cast<ModelAbstract&>(obj);
    in >> obj.specialRules;
    in >> obj.isALord;
    in >> obj.isTheGeneral;
    in >> obj.isAMage;
    in >> obj.isMounted;
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
    int points = stats.getPoints();
    QList<OptionModel>::iterator i;
    for (i = options.begin(); i != options.end(); ++i)
    {
        points += i->getNbPoints();
    }
    points += mount.getPoints();
    return points;
}
