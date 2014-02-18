#include "modelinfantery.h"

ModelInfantery::ModelInfantery():
    ModelAbstract()
{
}

ModelInfantery::ModelInfantery(const QString &n, const QString &move, const QString &weaponS,
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

ModelInfantery::ModelInfantery(const ModelInfantery &copy) : ModelAbstract(copy)
{
    specialRules = copy.specialRules;
}

ModelInfantery::~ModelInfantery()
{
}

void ModelInfantery::initModelInfanterySystem()
{
    qRegisterMetaTypeStreamOperators<ModelInfantery>("ModelInfantery");
    qMetaTypeId<ModelInfantery>();
}

ModelInfantery *ModelInfantery::setFromFile(QString path)
{
    ModelInfantery* tmp = new ModelInfantery(*this);
    tmp->load(path);

    return tmp;
}

ModelInfantery *ModelInfantery::setFromUI(const ParamsfromUImodel *params)
{
    qDebug() << "yay this is setfromUI in ModelInfantery !";

    ModelInfantery* tmp = new ModelInfantery(*this);
    // ModelAbstract params
    tmp->setStats(params->getStats());
    tmp->setSquareBaseW(params->getWidthBase());
    tmp->setSquareBaseL(params->getLengthBase());
    tmp->setUnitPower(params->getUnitP());
    tmp->setFigSupInd(params->getFigSup());
    tmp->setUrlImage(params->getUrlImage());
    tmp->setOptions(params->getOptions());

    // ModelInfantery params
    tmp->setSpecialRules(params->getSpecRules());
    return tmp;
}

void ModelInfantery::load(QString path)
{
    ModelInfantery temp;

    QSettings readFile(path, QSettings::IniFormat);
    temp = readFile.value("ModelInfantery", qVariantFromValue(ModelInfantery())).value<ModelInfantery>();

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

void ModelInfantery::save(QString path)
{
    QFile::remove(path);
    QSettings savedFile(path, QSettings::IniFormat);
    savedFile.setValue("ModelInfantery", qVariantFromValue(*this));
    savedFile.sync();
}

QString ModelInfantery::displayStringInfo()
{
    QString s;
    QTextStream info(&s);
    info << endl << "====================================================" << endl;
    info << "Model Infantery : " << endl;
    info << displayBaseInfo();
    info << "====================================================" << endl;
    info << "Special Rules : " << endl;
    info << specialRules << endl;
    info << "====================================================" << endl;
    return s;
}

QString ModelInfantery::getSpecialRules() const
{
    return specialRules;
}

void ModelInfantery::setSpecialRules(const QString &value)
{
    specialRules = value;
}

int ModelInfantery::computePoints()
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

QDataStream & operator <<(QDataStream & out, const ModelInfantery & obj)
{
    out << static_cast<ModelAbstract>(obj)
        << obj.specialRules;
    return out;
}

QDataStream & operator >>(QDataStream & in, ModelInfantery & obj)
{
    in >> static_cast<ModelAbstract&>(obj);
    in >> obj.specialRules;

    return in;
}

