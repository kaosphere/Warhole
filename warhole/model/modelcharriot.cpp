#include "modelcharriot.h"


ModelCharriot::ModelCharriot():
    ModelAbstract()
{
}

ModelCharriot::ModelCharriot(const QString &n, const QString &move, const QString &weaponS,
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

ModelCharriot::~ModelCharriot()
{
}

void ModelCharriot::initModelCharriotSystem()
{
    qRegisterMetaTypeStreamOperators<ModelCharriot>("ModelCharriot");
    qMetaTypeId<ModelCharriot>();
}

void ModelCharriot::load(QString path)
{
    ModelCharriot temp;

    QSettings readFile(path, QSettings::IniFormat);
    temp = readFile.value("ModelCharriot", qVariantFromValue(ModelCharriot())).value<ModelCharriot>();

    stats = temp.getStats();
    squareBaseW = temp.getSquareBaseW();
    squareBaseL = temp.getSquareBaseL();
    unitPower = temp.getUnitPower();

    urlImage = temp.getUrlImage();

    //image->load(urlImage);

    figSupInd = temp.getFigSupInd();
    specialRules = temp.getSpecialRules();
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

QList<ModelAnimal *> ModelCharriot::getMount() const
{
    return mounts;
}

void ModelCharriot::setMount(const QList<ModelAnimal *> &value)
{
    mounts = value;
}

void ModelCharriot::addMount(ModelAnimal *m)
{
    mounts<<m;
}

void ModelCharriot::removeMount(ModelAnimal *m)
{
    mounts.removeOne(m);
}

QList<ModelInfantery *> ModelCharriot::getCrew() const
{
    return crew;
}

void ModelCharriot::setCrew(const QList<ModelInfantery *> &value)
{
    crew = value;
}

void ModelCharriot::addCrew(ModelInfantery *c)
{
    crew<<c;
}

void ModelCharriot::removeCrew(ModelInfantery *c)
{
    crew.removeOne(c);
}

QDataStream & operator <<(QDataStream & out, const ModelCharriot & obj)
{
    out << obj.stats
        << obj.squareBaseW
        << obj.squareBaseL
        << obj.unitPower
        << obj.figSupInd
        << obj.urlImage
        << obj.specialRules;
    return out;
}

QDataStream & operator >>(QDataStream & in, ModelCharriot & obj)
{
    in >> obj.stats;
    in >> obj.squareBaseW;
    in >> obj.squareBaseL;
    in >> obj.unitPower;
    in >> obj.figSupInd;
    in >> obj.urlImage;
    in >> obj.specialRules;

    return in;
}
