#include "modelcavalry.h"
#include <QDebug>

ModelCavalry::ModelCavalry():
    ModelAbstract()
{
}

ModelCavalry::ModelCavalry(const QString &n, const QString &move, const QString &weaponS,
                           const QString &balisticS, const QString &strength, const QString &toughness,
                           const QString &wounds, const QString &init, const QString &attacks,
                           const QString &leadership, const QString &save, const QString &invSave, const int points,
                           const int &widthBase, const int &lengthBase, const int &unitP, const QString &urlImage,
                           bool figSup, const QString &specRules) :
    ModelAbstract(n,move,weaponS,balisticS, strength, toughness, wounds, init, attacks, leadership, save,
                  invSave, points, widthBase, lengthBase, unitP, urlImage, figSup)
{
    specialRules = specRules;
}

// Copy constructor
ModelCavalry::ModelCavalry(const ModelCavalry &copy) : ModelAbstract(copy)
{
    specialRules = copy.specialRules;
    mount = copy.mount;
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
    tmp->setStats(params->getStats());
    tmp->setSquareBaseW(params->getWidthBase());
    tmp->setSquareBaseL(params->getLengthBase());
    tmp->setUnitPower(params->getUnitP());
    tmp->setFigSupInd(params->getFigSup());
    tmp->setUrlImage(params->getUrlImage());
    tmp->setOptions(params->getOptions());

    // modelcavalery params
    tmp->setSpecialRules(params->getSpecRules());
    tmp->setMount(params->getMorC());

    return tmp;
}

void  ModelCavalry::load(QString path)
{
    ModelCavalry temp;

    QSettings readFile(path, QSettings::IniFormat);
    temp = readFile.value("ModelCavalry", qVariantFromValue(ModelCavalry())).value< ModelCavalry>();

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
    int nb;
    nb = obj.mount.size();

    out << static_cast<ModelAbstract>(obj)
        << obj.specialRules
        << nb;

    for(int i = 0 ; i < obj.mount.size() ; i++)
    {
        out << obj.mount[i];
    }
    return out;
}

// Overloading of >> operator
QDataStream & operator >> (QDataStream & in, ModelCavalry & obj)
{
    int nb;

    in >> static_cast<ModelAbstract&>(obj);
    in >> obj.specialRules;
    in >> nb;

    for(int i = 0 ; i < nb ; i++)
    {
        StatsModel s;
        in >> s;
        obj.addMount(s);
    }

    return in;
}

QString ModelCavalry::displayStringInfo()
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
    info << "Mount stats : " << endl;
    info << mount.first().displayString();
    info << "====================================================" << endl;
    return s;
}

QList<StatsModel> ModelCavalry::getMount() const
{
    return mount;
}

void ModelCavalry::setMount(const QList<StatsModel> &value)
{
    mount = value;
}

void ModelCavalry::addMount(StatsModel m)
{
    mount << m;
}

void ModelCavalry::clearMount()
{
    mount.clear();
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
    points += mount.first().getPoints();
    return points;
}
