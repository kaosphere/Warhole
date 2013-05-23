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

    options = temp.getOptions();
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
    out << static_cast<ModelAbstract>(obj)
        << obj.specialRules;
    return out;
}

QDataStream & operator >>(QDataStream & in, ModelCharriot & obj)
{
    in >> static_cast<ModelAbstract&>(obj);
    in >> obj.specialRules;

    return in;
}
