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
                                 bool figSup, const QString &specRules, bool hasCrew) :
    ModelAbstract(n,move,weaponS,balisticS, strength, toughness, wounds, init, attacks, leadership, save,
                  invSave, points, widthBase, lengthBase, unitP, urlImage, figSup)
{
    specialRules = specRules;
    hasACrew = hasCrew;
}

ModelMonster::~ModelMonster()
{
}

void ModelMonster::initModelMonsterSystem()
{
    qRegisterMetaTypeStreamOperators<ModelMonster>("ModelMonster");
    qMetaTypeId<ModelMonster>();
}

void ModelMonster::load(QString path)
{
    ModelMonster temp;

    QSettings readFile(path, QSettings::IniFormat);
    temp = readFile.value("ModelMonster", qVariantFromValue(ModelMonster())).value<ModelMonster>();

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
        << obj.specialRules
        << obj.hasACrew;
    return out;
}

QDataStream & operator >>(QDataStream & in, ModelMonster & obj)
{
    in >> static_cast<ModelAbstract&>(obj);
    in >> obj.specialRules;
    in >> obj.hasACrew;

     return in;
}
