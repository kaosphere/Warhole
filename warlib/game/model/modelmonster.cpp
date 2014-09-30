#include "modelmonster.h"

ModelMonster::ModelMonster(QObject *parent):
    ModelAbstract(parent)
{
}

ModelMonster::ModelMonster(const QString &n, const QString &move, const QString &weaponS,
      const QString &balisticS, const QString &strength, const QString &toughness,
      const QString &wounds, const QString &init, const QString &attacks,
      const QString &leadership, const QString &save, const QString &invSave, const int points,
      const int &widthBase, const int &lengthBase, const int &unitP, const QString &urlImage,
      bool figSup, const QString &specRules, const ModelType &t, QObject* parent) :
    ModelAbstract(n,move,weaponS,balisticS, strength, toughness, wounds, init, attacks, leadership, save,
                  invSave, points, widthBase, lengthBase, unitP, urlImage, figSup, parent)
{
    type = t;
    specialRules = specRules;
}

// Copy constructor
ModelMonster::ModelMonster(const ModelMonster &copy) : ModelAbstract(copy)
{
    specialRules = copy.specialRules;
    type = copy.type;
    crew = copy.crew;
}

ModelMonster::~ModelMonster()
{
}

void ModelMonster::initModelMonsterSystem()
{
    qRegisterMetaTypeStreamOperators<ModelMonster>("ModelMonster");
    qMetaTypeId<ModelMonster>();
}

ModelMonster *ModelMonster::setFromFile(QString path)
{
    ModelMonster* tmp = new ModelMonster(*this);
    tmp->load(path);

    return tmp;
}

QDataStream& ModelMonster::serializeOut(QDataStream& out)
{
    out << (*this);
    return out;
}

QDataStream & ModelMonster::serializeIn(QDataStream &in)
{
    in >> (*this);
    return in;
}

ModelAbstract *ModelMonster::clone()
{
    return new ModelMonster(*this);
}

ModelMonster *ModelMonster::setFromUI(const ParamsfromUImodel *params)
{
    ModelMonster* tmp = new ModelMonster(*this);
    // ModelAbstract params
    tmp->setType(params->getType());
    tmp->setStats(params->getStats());
    tmp->setSquareBaseW(params->getWidthBase());
    tmp->setSquareBaseL(params->getLengthBase());
    tmp->setUnitPower(params->getUnitP());
    tmp->setFigSupInd(params->getFigSup());
    tmp->setUrlImage(params->getUrlImage());
    tmp->setOptions(params->getOptions());

    // ModelMonster params
    tmp->setSpecialRules(params->getSpecRules());
    tmp->setCrew(params->getMorC());
    return tmp;
}

void ModelMonster::load(QString path)
{
    ModelMonster temp;

    QSettings readFile(path, QSettings::IniFormat);
    temp = readFile.value("ModelMonster", qVariantFromValue(ModelMonster())).value<ModelMonster>();

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

    crew = temp.getCrew();
}

void ModelMonster::save(QString path)
{
    if(!QFile::remove(path)) throw WarlibException(0,tr("QFile::remove() failed for an un"), EXCEPTION_LOW);
    QSettings savedFile(path, QSettings::IniFormat);
    savedFile.setValue("ModelMonster", qVariantFromValue(*this));
    savedFile.sync();
}

QString ModelMonster::displayStringInfo()
{
    QString s;
    QTextStream info(&s);
    info << endl << "====================================================" << endl;
    info << QString(QString::fromUtf8("Unité "));
    switch(type)
    {
    case 0:
        info << "Base" << endl;
        break;
    case 1:
        info << QString(QString::fromUtf8("Spéciale")) << endl;
        break;
    case 2:
        info << "Rare" << endl;
        break;
    default:
        info << "ERROR" << endl;
        break;
    }
    info << endl << "====================================================" << endl;
    info << "Model Monster : " << endl;
    info << displayBaseInfo();
    info << "====================================================" << endl;
    info << QString(QString::fromUtf8("Règles additionnelles : ")) << endl;
    info << specialRules << endl;
    info << "====================================================" << endl;
    info << QString(QString::fromUtf8("Statistique de l'équipage : ")) << endl;
    QList<StatsModel>::iterator i;
    for(i = crew.begin(); i < crew.end() ; ++i)
    {
        info << "------------------" << endl;
        info << i->displayString() << endl;;
    }
    info << "====================================================" << endl;
    return s;
}

QString ModelMonster::getHtml()
{
    QString html;
    html += getBaseHtml();
    html += "Règles additionnelles : <br/>\n";
    html += QString(specialRules.toHtmlEscaped() + "<br/>\n");
    if(crew.size() != 0)
    {
        html += QString("Equipage : <br/>\n");
        QList<StatsModel>::iterator i;
        for(i = crew.begin(); i < crew.end() ; ++i)
        {
            html += QString("<li>\n");
            html += QString("%1 : <br/>\n").arg(i->getName());
            html += i->getHtml();
            html += QString("</li>\n");
        }
    }
    html += "<br/>\n";

    return html;
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
    out << SAVE_VERSION;
    obj.serializeOutBase(out);
    out << obj.type
        << obj.specialRules
        << obj.crew.size();

    for(int i = 0 ; i < obj.crew.size() ; i++)
    {
        out << obj.crew[i];
    }
    return out;
}

QDataStream & operator >>(QDataStream & in, ModelMonster & obj)
{
    int type;
    int nb;
    int version = 0;

    in >> version;
    obj.serializeInBase(in);
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
    in >> nb;

    for(int i = 0 ; i < nb ; i++)
    {
        StatsModel s;
        in >> s;
        obj.addCrew(s);
    }

    return in;
}

ModelType ModelMonster::getType() const
{
    return type;
}

void ModelMonster::setType(const ModelType &value)
{
    type = value;
}

QList<StatsModel> ModelMonster::getCrew() const
{
    return crew;
}

void ModelMonster::setCrew(const QList<StatsModel> &value)
{
    crew = value;
}

void ModelMonster::addCrew(StatsModel c)
{
    crew << c;
}

void ModelMonster::clearCrew()
{
    crew.clear();
}


int ModelMonster::computePoints()
{
    //compute whole points of the model
    int points = computeBasePoints();
    QList<StatsModel>::Iterator j;
    for(j = crew.begin(); j < crew.end(); ++j)
    {
        points += j->getPoints();
    }
    return points;
}

