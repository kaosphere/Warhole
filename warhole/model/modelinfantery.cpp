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

ModelInfantery *ModelInfantery::clone(QString path)
{
    ModelInfantery* tmp = new ModelInfantery(*this);
    tmp->load(path);

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

QString ModelInfantery::getSpecialRules() const
{
    return specialRules;
}

void ModelInfantery::setSpecialRules(const QString &value)
{
    specialRules = value;
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

