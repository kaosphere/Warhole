#include "modelcharacter.h"


ModelCharacter::ModelCharacter():
    ModelAbstract()
{
}

ModelCharacter::ModelCharacter(const QString &n, const QString &move, const QString &weaponS,
                               const QString &balisticS, const QString &strength, const QString &toughness,
                               const QString &wounds, const QString &init, const QString &attacks,
                               const QString &leadership, const QString &save, const QString &invSave, const int points,
                               const int &widthBase, const int &lengthBase, const int &unitP, const QString &urlImage,
                               bool figSup, const QString &specRules, bool lord, bool general, bool mage,
                               bool mounted) :
    ModelAbstract(n,move,weaponS,balisticS, strength, toughness, wounds, init, attacks, leadership, save,
                  invSave, points, widthBase, lengthBase, unitP, urlImage, figSup)
{
    specialRules = specRules;
    isALord = lord;
    isTheGeneral = general;
    isAMage = mage;
    isMounted = mounted;
}

ModelCharacter::ModelCharacter(const ModelCharacter &copy) : ModelAbstract(copy)
{
    specialRules = copy.specialRules;
    isALord = copy.isALord;
    isTheGeneral = copy.isTheGeneral;
    isAMage = copy.isAMage;
    isMounted = copy.isMounted;
}

ModelCharacter::~ModelCharacter()
{
}

void ModelCharacter::initModelCharacterSystem()
{
    qRegisterMetaTypeStreamOperators<ModelCharacter>("ModelCharacter");
    qMetaTypeId<ModelCharacter>();
}

void ModelCharacter::load(QString path)
{
    ModelCharacter temp;
    QSettings readFile(path, QSettings::IniFormat);
    temp = readFile.value("ModelCharacter", qVariantFromValue( ModelCharacter())).value< ModelCharacter>();

    stats = temp.getStats();
    squareBaseW = temp.getSquareBaseW();
    squareBaseL = temp.getSquareBaseL();
    unitPower = temp.getUnitPower();

    urlImage = temp.getUrlImage();

    //image->load(urlImage);

    figSupInd = temp.getFigSupInd();
    specialRules = temp.getSpecialRules();
    isALord = temp.getIsALord();
    isTheGeneral = temp.getIsTheGeneral();
    isAMage = temp.getIsAMage();
    isMounted = temp.getIsMounted();
}

void ModelCharacter::save(QString path)
{
    QFile::remove(path);
    QSettings savedFile(path, QSettings::IniFormat);
    savedFile.setValue("ModelCharacter", qVariantFromValue(*this));
    savedFile.sync();
}

QString ModelCharacter::getSpecialRules() const
{
    return specialRules;
}

void ModelCharacter::setSpecialRules(const QString &value)
{
    specialRules = value;
}


bool ModelCharacter::getIsALord() const
{
    return isALord;
}

void ModelCharacter::setIsALord(bool value)
{
    isALord = value;
}

bool ModelCharacter::getIsTheGeneral() const
{
    return isTheGeneral;
}

void ModelCharacter::setIsTheGeneral(bool value)
{
    isTheGeneral = value;
}
bool ModelCharacter::getIsAMage() const
{
    return isAMage;
}

void ModelCharacter::setIsAMage(bool value)
{
    isAMage = value;
}

bool ModelCharacter::getIsMounted() const
{
    return isMounted;
}

void ModelCharacter::setIsMounted(bool value)
{
    isMounted = value;
}

QDataStream & operator <<(QDataStream & out, const ModelCharacter & obj)
{
    //out << obj.streamOut();
    out << obj.stats
        << obj.squareBaseW
        << obj.squareBaseL
        << obj.unitPower
        << obj.figSupInd
        << obj.urlImage
        << obj.specialRules
        << obj.isALord
        << obj.isTheGeneral
        << obj.isAMage
        << obj.isMounted;
    return out;
}

QDataStream & operator >>(QDataStream & in, ModelCharacter & obj)
{
    in >> obj.stats;
    in >> obj.squareBaseW;
    in >> obj.squareBaseL;
    in >> obj.unitPower;
    in >> obj.figSupInd;
    in >> obj.urlImage;
    in >> obj.specialRules;
    in >> obj.isALord;
    in >> obj.isTheGeneral;
    in >> obj.isAMage;
    in >> obj.isMounted;

    return in;
}
