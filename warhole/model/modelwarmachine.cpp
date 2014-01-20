#include "modelwarmachine.h"

ModelWarMachine::ModelWarMachine():
    ModelAbstract()
{
}

ModelWarMachine::ModelWarMachine(const QString &n, const QString &move, const QString &weaponS,
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

ModelWarMachine::~ModelWarMachine()
{
}

void ModelWarMachine::initModelWarMachine()
{
    qRegisterMetaTypeStreamOperators<ModelWarMachine>("ModelWarMachine");
    qMetaTypeId<ModelWarMachine>();
}

ModelWarMachine *ModelWarMachine::clone(QString path)
{
    ModelWarMachine* tmp = new ModelWarMachine(*this);
    tmp->load(path);

    return tmp;
}

void ModelWarMachine::load(QString path)
{
    ModelWarMachine temp;

    QSettings readFile(path, QSettings::IniFormat);
    temp = readFile.value("ModelWarMachine", qVariantFromValue(ModelWarMachine())).value<ModelWarMachine>();

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

void ModelWarMachine::save(QString path)
{
    QFile::remove(path);
    QSettings savedFile(path, QSettings::IniFormat);
    savedFile.setValue("ModelWarMachine", qVariantFromValue(*this));
    savedFile.sync();
}

QString ModelWarMachine::getSpecialRules() const
{
    return specialRules;
}

void ModelWarMachine::setSpecialRules(const QString &value)
{
    specialRules = value;
}

QDataStream & operator <<(QDataStream & out, const ModelWarMachine & obj)
{
    out << static_cast<ModelAbstract>(obj)
        << obj.specialRules;

    return out;
}

QDataStream & operator >>(QDataStream & in, ModelWarMachine & obj)
{
    in >> static_cast<ModelAbstract&>(obj);
    in >> obj.specialRules;

    return in;
}
