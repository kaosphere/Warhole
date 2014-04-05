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
                                 bool figSup, const QString &specRules, const ModelType &t) :
    ModelAbstract(n,move,weaponS,balisticS, strength, toughness, wounds, init, attacks, leadership, save,
        invSave, points, widthBase, lengthBase, unitP, urlImage, figSup)
{
    type = t;
    specialRules = specRules;
}

ModelWarMachine::ModelWarMachine(const ModelWarMachine &copy) : ModelAbstract(copy)
{
    specialRules = copy.specialRules;
    type = copy.type;
}

ModelWarMachine::~ModelWarMachine()
{
}

void ModelWarMachine::initModelWarMachine()
{
    qRegisterMetaTypeStreamOperators<ModelWarMachine>("ModelWarMachine");
    qMetaTypeId<ModelWarMachine>();
}

ModelWarMachine *ModelWarMachine::setFromFile(QString path)
{
    ModelWarMachine* tmp = new ModelWarMachine(*this);
    tmp->load(path);

    return tmp;
}

QDataStream &ModelWarMachine::serializeOut(QDataStream& out)
{
    out << (*this);
    return out;
}

QDataStream & ModelWarMachine::serializeIn(QDataStream &in)
{
    in >> (*this);
    return in;
}

ModelWarMachine *ModelWarMachine::setFromUI(const ParamsfromUImodel *params)
{
    ModelWarMachine* tmp = new ModelWarMachine(*this);

    // modelabstract params
    tmp->setType(params->getType());
    tmp->setStats(params->getStats());
    tmp->setSquareBaseW(params->getWidthBase());
    tmp->setSquareBaseL(params->getLengthBase());
    tmp->setUnitPower(params->getUnitP());
    tmp->setFigSupInd(params->getFigSup());
    tmp->setUrlImage(params->getUrlImage());
    tmp->setOptions(params->getOptions());

    // modelcavalery params
    tmp->setSpecialRules(params->getSpecRules());

    return tmp;
}

void ModelWarMachine::load(QString path)
{
    ModelWarMachine temp;

    QSettings readFile(path, QSettings::IniFormat);
    temp = readFile.value("ModelWarMachine", qVariantFromValue(ModelWarMachine())).value<ModelWarMachine>();

    type = temp.getType();
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

int ModelWarMachine::computePoints()
{
    //compute whole points of the model
    int points = computeBasePoints();
    return points;
}

QString ModelWarMachine::displayStringInfo()
{
    QString s;
    QTextStream info(&s);
    info << endl << "====================================================" << endl;
    info << "Unité ";
    switch(type)
    {
    case 0:
        info << "Base" << endl;
        break;
    case 1:
        info << "Spciale" << endl;
        break;
    case 2:
        info << "Rare" << endl;
        break;
    default:
        info << "ERROR" << endl;
        break;
    }
    info << endl << "====================================================" << endl;
    info << "Model Cavalry : " << endl;
    info << displayBaseInfo();
    info << "====================================================" << endl;
    info << "Special Rules : " << endl;
    info << specialRules << endl;
    info << "====================================================" << endl;
    return s;
}

QString ModelWarMachine::getHtml()
{
    QString html;
    html += getBaseHtml();
    html += "Règles additionnelles : <br/>\n";
    html += QString(specialRules.toHtmlEscaped() + "<br/>\n");
    html += "<br/>\n";

    return html;
}

QString ModelWarMachine::getSpecialRules() const
{
    return specialRules;
}

void ModelWarMachine::setSpecialRules(const QString &value)
{
    specialRules = value;
}

ModelType ModelWarMachine::getType() const
{
return type;
}

void ModelWarMachine::setType(const ModelType &value)
{
type = value;
}

QDataStream & operator <<(QDataStream & out, const ModelWarMachine & obj)
{
    out << static_cast<ModelAbstract>(obj)
        << obj.type
        << obj.specialRules;

    return out;
}

QDataStream & operator >>(QDataStream & in, ModelWarMachine & obj)
{
    int type;

    in >> static_cast<ModelAbstract&>(obj);
    in >> type;
    switch(type)
    {
    case 0:
        obj.type = BASE;
        break;
    case 1:
        obj.type = SPECIAL;
        break;
    case 2:
        obj.type = RARE;
        break;
    default:
        break;
    }
    in >> obj.specialRules;

    return in;
}
