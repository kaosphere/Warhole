#include "paramsfromuimodel.h"

ParamsfromUImodel::ParamsfromUImodel()
{
    name = "";
    move = "";
     weaponS = "";
     balisticS = "";
     strength = "";
     toughness = "";
     wounds = "";
     init = "";
     attacks = "";
     leadership = "";
     save = "";
     invSave = "";
     points = 0;
     widthBase = 0;
     lengthBase = 0;
     unitP = 0;
     urlImage = "";
     figSup = false;
    // warMachine, monster, infantery, charriot, character, cavalery params
     specRules = "";
    // character params
     lord = false;
     general = false;
     mage = false;
     mounted = false;
    // monster params
     hasCrew = false;
}

ParamsfromUImodel::~ParamsfromUImodel()
{
}

QString ParamsfromUImodel::getName() const
{
    return name;
}

void ParamsfromUImodel::setName(const QString &value)
{
    name = value;
}

QList<OptionModel> ParamsfromUImodel::getOptions() const
{
    return options;
}

void ParamsfromUImodel::setOptions(const QList<OptionModel> &value)
{
    options = value;
}

StatsModel ParamsfromUImodel::getStats() const
{
    return stats;
}

void ParamsfromUImodel::setStats(const StatsModel &value)
{
    stats = value;
}

bool ParamsfromUImodel::getHasCrew() const
{
    return hasCrew;
}

void ParamsfromUImodel::setHasCrew(bool value)
{
    hasCrew = value;
}

bool ParamsfromUImodel::getMounted() const
{
    return mounted;
}

void ParamsfromUImodel::setMounted(bool value)
{
    mounted = value;
}

bool ParamsfromUImodel::getMage() const
{
    return mage;
}

void ParamsfromUImodel::setMage(bool value)
{
    mage = value;
}

bool ParamsfromUImodel::getGeneral() const
{
    return general;
}

void ParamsfromUImodel::setGeneral(bool value)
{
    general = value;
}

bool ParamsfromUImodel::getLord() const
{
    return lord;
}

void ParamsfromUImodel::setLord(bool value)
{
    lord = value;
}

QString ParamsfromUImodel::getSpecRules() const
{
    return specRules;
}

void ParamsfromUImodel::setSpecRules(const QString &value)
{
    specRules = value;
}

bool ParamsfromUImodel::getFigSup() const
{
    return figSup;
}

void ParamsfromUImodel::setFigSup(bool value)
{
    figSup = value;
}

QString ParamsfromUImodel::getUrlImage() const
{
    return urlImage;
}

void ParamsfromUImodel::setUrlImage(const QString &value)
{
    urlImage = value;
}

int ParamsfromUImodel::getUnitP() const
{
    return unitP;
}

void ParamsfromUImodel::setUnitP(int value)
{
    unitP = value;
}

int ParamsfromUImodel::getLengthBase() const
{
    return lengthBase;
}

void ParamsfromUImodel::setLengthBase(int value)
{
    lengthBase = value;
}

int ParamsfromUImodel::getWidthBase() const
{
    return widthBase;
}

void ParamsfromUImodel::setWidthBase(int value)
{
    widthBase = value;
}

int ParamsfromUImodel::getPoints() const
{
    return points;
}

void ParamsfromUImodel::setPoints(int value)
{
    points = value;
}

QString ParamsfromUImodel::getInvSave() const
{
    return invSave;
}

void ParamsfromUImodel::setInvSave(const QString &value)
{
    invSave = value;
}

QString ParamsfromUImodel::getSave() const
{
    return save;
}

void ParamsfromUImodel::setSave(const QString &value)
{
    save = value;
}

QString ParamsfromUImodel::getLeadership() const
{
    return leadership;
}

void ParamsfromUImodel::setLeadership(const QString &value)
{
    leadership = value;
}

QString ParamsfromUImodel::getAttacks() const
{
    return attacks;
}

void ParamsfromUImodel::setAttacks(const QString &value)
{
    attacks = value;
}

QString ParamsfromUImodel::getInit() const
{
    return init;
}

void ParamsfromUImodel::setInit(const QString &value)
{
    init = value;
}

QString ParamsfromUImodel::getWounds() const
{
    return wounds;
}

void ParamsfromUImodel::setWounds(const QString &value)
{
    wounds = value;
}

QString ParamsfromUImodel::getToughness() const
{
    return toughness;
}

void ParamsfromUImodel::setToughness(const QString &value)
{
    toughness = value;
}

QString ParamsfromUImodel::getStrength() const
{
    return strength;
}

void ParamsfromUImodel::setStrength(const QString &value)
{
    strength = value;
}

QString ParamsfromUImodel::getBalisticS() const
{
    return balisticS;
}

void ParamsfromUImodel::setBalisticS(const QString &value)
{
    balisticS = value;
}

QString ParamsfromUImodel::getWeaponS() const
{
    return weaponS;
}

void ParamsfromUImodel::setWeaponS(const QString &value)
{
    weaponS = value;
}

QString ParamsfromUImodel::getMove() const
{
    return move;
}

void ParamsfromUImodel::setMove(const QString &value)
{
    move = value;
}

QList<StatsModel> ParamsfromUImodel::getMorC() const
{
    return mOrC;
}

void ParamsfromUImodel::setMorC(const QList<StatsModel> &value)
{
    mOrC = value;
}
