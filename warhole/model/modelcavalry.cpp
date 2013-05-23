#include "modelcavalry.h"

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
        << obj.specialRules;
    return out;
}

// Overloading of >> operator
QDataStream & operator >> (QDataStream & in, ModelCavalry & obj)
{
    in >> static_cast<ModelAbstract&>(obj);
    in >> obj.specialRules;

    return in;
}
