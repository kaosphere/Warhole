#include "modelmonster.h"

ModelMonster::ModelMonster():
    ModelAbstract()
{
}

ModelMonster::ModelMonster(const QString &n, const QString &move, const QString &weaponS,
      const QString &balisticS, const QString &strength, const QString &toughness,
      const QString &wounds, const QString &init, const QString &attacks,
      const QString &leadership, const QString &save, const QString &invSave, const int points,
      const int &widthBase, const int &lengthBase, const int &unitP, const QString &urlImage,
      bool figSup, const QString &specRules, bool hasCrew,const ModelType &t) :
    ModelAbstract(n,move,weaponS,balisticS, strength, toughness, wounds, init, attacks, leadership, save,
                  invSave, points, widthBase, lengthBase, unitP, urlImage, figSup)
{
    type = t;
    specialRules = specRules;
    hasACrew = hasCrew;
}

// Copy constructor
ModelMonster::ModelMonster(const ModelMonster &copy) : ModelAbstract(copy)
{
    specialRules = copy.specialRules;
    type = copy.type;
}

ModelMonster::~ModelMonster()
{
}

void ModelMonster::initModelMonsterSystem()
{
    qRegisterMetaTypeStreamOperators<ModelMonster>("ModelMonster");
    qMetaTypeId<ModelMonster>();
}

ModelMonster *ModelMonster::setFromFile(QString path)
{
    ModelMonster* tmp = new ModelMonster(*this);
    tmp->load(path);

    return tmp;
}

ModelMonster *ModelMonster::setFromUI(const ParamsfromUImodel *params)
{
    ModelMonster* tmp = new ModelMonster(*this);
    // ModelAbstract params
    tmp->setType(params->getType());
    tmp->setStats(params->getStats());
    tmp->setSquareBaseW(params->getWidthBase());
    tmp->setSquareBaseL(params->getLengthBase());
    tmp->setUnitPower(params->getUnitP());
    tmp->setFigSupInd(params->getFigSup());
    tmp->setUrlImage(params->getUrlImage());
    tmp->setOptions(params->getOptions());

    // ModelMonster params
    tmp->setSpecialRules(params->getSpecRules());
    tmp->setHasACrew(params->getHasCrew());
    // TODO CREW
    return tmp;
}

void ModelMonster::load(QString path)
{
    ModelMonster temp;

    QSettings readFile(path, QSettings::IniFormat);
    temp = readFile.value("ModelMonster", qVariantFromValue(ModelMonster())).value<ModelMonster>();

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
}

void ModelMonster::save(QString path)
{
    QFile::remove(path);
    QSettings savedFile(path, QSettings::IniFormat);
    savedFile.setValue("ModelMonster", qVariantFromValue(*this));
    savedFile.sync();
}

QString ModelMonster::displayStringInfo()
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
    info << "Model Monster : " << endl;
    info << displayBaseInfo();
    info << "====================================================" << endl;
    info << "Special Rules : " << endl;
    info << specialRules << endl;
    info << "====================================================" << endl;
    return s;
}

QString ModelMonster::getSpecialRules() const
{
    return specialRules;
}

void ModelMonster::setSpecialRules(const QString &value)
{
    specialRules = value;
}


QDataStream & operator <<(QDataStream & out, const ModelMonster & obj)
{
    out << static_cast<ModelAbstract>(obj)
        << obj.type
        << obj.specialRules
        << obj.hasACrew;
    return out;
}

QDataStream & operator >>(QDataStream & in, ModelMonster & obj)
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
    in >> obj.hasACrew;
}


QList<ModelInfantery *> ModelMonster::getCrew() const
{
    return crew;
}

void ModelMonster::setCrew(const QList<ModelInfantery *> &value)
{
    crew = value;
}

bool ModelMonster::getHasACrew() const
{
    return hasACrew;
}

void ModelMonster::setHasACrew(bool value)
{
    hasACrew = value;
}

ModelType ModelMonster::getType() const
{
    return type;
}

void ModelMonster::setType(const ModelType &value)
{
    type = value;
}


int ModelMonster::computePoints()
{
    //compute whole points of the model
    int points = stats.getPoints();
    QList<OptionModel>::iterator i;
    for (i = options.begin(); i != options.end(); ++i)
    {
        points += i->getNbPoints();
    }
    return points;
}

