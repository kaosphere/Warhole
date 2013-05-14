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

QList<ModelInfantery *> ModelMonster::getCrew() const
{
    return crew;
}

void ModelMonster::setCrew(const QList<ModelInfantery *> &value)
{
    crew = value;
}

void ModelMonster::addCrewMember(ModelInfantery *c)
{
    crew<<c;
}

void ModelMonster::removeCrewMember(ModelInfantery *c)
{
    crew.removeOne(c);
}


bool ModelMonster::getHasACrew() const
{
    return hasACrew;
}

void ModelMonster::setHasACrew(bool value)
{
    hasACrew = value;
}

QDataStream & operator <<(QDataStream & out, const ModelMonster & obj)
{
    out << obj.stats
        << obj.squareBaseW
        << obj.squareBaseL
        << obj.unitPower
        << obj.figSupInd
        << obj.urlImage
        << obj.specialRules
        << obj.hasACrew;
    return out;
}

QDataStream & operator >>(QDataStream & in, ModelMonster & obj)
{
    in >> obj.stats;
    in >> obj.squareBaseW;
    in >> obj.squareBaseL;
    in >> obj.unitPower;
    in >> obj.figSupInd;
    in >> obj.urlImage;
    in >> obj.specialRules;
    in >> obj.hasACrew;

     return in;
}
