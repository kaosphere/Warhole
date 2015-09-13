#include "modelinfantery.h"

ModelInfantery::ModelInfantery(QObject *parent):
    ModelAbstract(parent)
{
}

ModelInfantery::ModelInfantery(const QString &n, const QString &move, const QString &weaponS,
                               const QString &balisticS, const QString &strength, const QString &toughness,
                               const QString &wounds, const QString &init, const QString &attacks,
                               const QString &leadership, const QString &save, const QString &invSave, const int points,
                               const int &widthBase, const int &lengthBase, const int &unitP, const QString &urlImage,
                               bool figSup, const QString &specRules, const ModelType &t, QObject* parent) :
    ModelAbstract(n,move,weaponS,balisticS, strength, toughness, wounds, init, attacks, leadership, save,
                  invSave, points, widthBase, lengthBase, unitP, urlImage, figSup, t, parent)
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

ModelInfantery *ModelInfantery::setFromFile(QString path)
{
    ModelInfantery* tmp = new ModelInfantery(*this);
    tmp->load(path);

    return tmp;
}

QDataStream& ModelInfantery::serializeOut(QDataStream& out)
{
    out << (*this);
    return out;
}

QDataStream & ModelInfantery::serializeIn(QDataStream &in)
{
    in >> (*this);
    return in;
}

ModelAbstract *ModelInfantery::clone()
{
    return new ModelInfantery(*this);
}

ModelInfantery *ModelInfantery::setFromUI(const ParamsfromUImodel *params)
{
    qDebug() << "yay this is setfromUI in ModelInfantery !";

    ModelInfantery* tmp = new ModelInfantery(*this);
    // ModelAbstract params
    tmp->setType(params->getType());
    tmp->setStats(params->getStats());
    tmp->setSquareBaseW(params->getWidthBase());
    tmp->setSquareBaseL(params->getLengthBase());
    tmp->setUnitPower(params->getUnitP());
    tmp->setFigSupInd(params->getFigSup());
    tmp->setUrlImage(params->getUrlImage());
    QPixmap p;
    p.load(params->getUrlImage());
    tmp->setImage(p);
    tmp->setOptions(params->getOptions());

    // ModelInfantery params
    tmp->setSpecialRules(params->getSpecRules());

    tmp->setBanner(params->getBanner());
    tmp->setBannerPoints(params->getBannerPoints());
    tmp->setChampion(params->getChampion());
    tmp->setChampionStats(params->getChampionStats());
    tmp->setMusician(params->getMusician());
    tmp->setMusicianPoints(params->getMusicianPoints());

    return tmp;
}

void ModelInfantery::load(QString path)
{
    ModelInfantery temp;

    QSettings readFile(path, QSettings::IniFormat);
    temp = readFile.value("ModelInfantery", qVariantFromValue(ModelInfantery())).value<ModelInfantery>();

    type = temp.getType();
    stats = temp.getStats();
    squareBaseW = temp.getSquareBaseW();
    squareBaseL = temp.getSquareBaseL();
    unitPower = temp.getUnitPower();

    urlImage = temp.getUrlImage();

    if(!temp.getImage().isNull())
    {
        image = temp.getImage();
    }

    figSupInd = temp.getFigSupInd();
    specialRules = temp.getSpecialRules();

    options = temp.getOptions();

    banner = temp.getBanner();
    bannerPoints = temp.getBannerPoints();
    musician = temp.getMusician();
    musicianPoints = temp.getMusicianPoints();
    champion = temp.getChampion();
    championStats = temp.getChampionStats();
}

void ModelInfantery::save(QString path)
{
    QFile::remove(path);
    QSettings savedFile(path, QSettings::IniFormat);
    savedFile.setValue("ModelInfantery", qVariantFromValue(*this));
    savedFile.sync();
}

QString ModelInfantery::displayStringInfo()
{
    QString s;
    QTextStream info(&s);
    info << "Model Infantery : " << endl;
    info << displayBaseInfo();
    info << "====================================================" << endl;
    info << QString(QString::fromUtf8("Règles additionnelles : ")) << endl;
    info << specialRules << endl;
    info << "====================================================" << endl;
    return s;
}

QString ModelInfantery::getHtml()
{
    QString html;
    html += getBaseHtml();
    html += "Règles additionnelles : <br/>\n";
    html += QString(specialRules.toHtmlEscaped() + "<br/>\n");
    html += "<br/>\n";

    return html;
}

QString ModelInfantery::getSpecialRules() const
{
    return specialRules;
}

void ModelInfantery::setSpecialRules(const QString &value)
{
    specialRules = value;
}

int ModelInfantery::computePoints()
{
    //compute whole points of the model
    int points = computeBasePoints();

    return points;
}

int ModelInfantery::computePointsWithoutOptions()
{
    return computeBasePointsWithoutOptions();
}

QDataStream & operator <<(QDataStream & out, const ModelInfantery & obj)
{
    out << SAVE_VERSION;
    obj.serializeOutBase(out);
    out << obj.specialRules;
    return out;
}

QDataStream & operator >>(QDataStream & in, ModelInfantery & obj)
{
    int version = 0;

    in >> version;
    obj.serializeInBase(in);
    if( version < 3)
    {
        int type = 0;
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
        case 3:
            obj.type = CHARACTER;
            break;
        default:
            break;
        }
    }
    in >> obj.specialRules;

    return in;
}

