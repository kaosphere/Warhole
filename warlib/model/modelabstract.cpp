#include "modelabstract.h"

ModelAbstract::ModelAbstract()
{
}

ModelAbstract::ModelAbstract(const StatsModel &stat,
                             const int &widthBase, const int &lengthBase, const int &unitP, const QString &url,
                             bool figSup)
{
    stats = stat;
    squareBaseW = widthBase;
    squareBaseL = lengthBase;
    unitPower = unitP;
    
    image = new QPixmap(urlImage);

    urlImage = url;
    
    figSupInd = figSup;
}

ModelAbstract::ModelAbstract(const QString &n, const QString &move, const QString &weaponS, const QString &balisticS, const QString &strength, const QString &toughness, const QString &wounds, const QString &init, const QString &attacks, const QString &leadership, const QString &save, const QString &invSave, const int points, const int &widthBase, const int &lengthBase, const int &unitP, const QString &url, bool figSup)
{
    stats.setName(n);
    stats.setM(move);
    stats.setWs(weaponS);
    stats.setBs(balisticS);
    stats.setS(strength);
    stats.setT(toughness);
    stats.setW(wounds);
    stats.setI(init);
    stats.setA(attacks);
    stats.setLd(leadership);
    stats.setSvg(save);
    stats.setSvgInv(invSave);
    stats.setPoints(points);

    squareBaseW = widthBase;
    squareBaseL = lengthBase;
    unitPower = unitP;

    image = new QPixmap(urlImage);

    urlImage = url;

    figSupInd = figSup;

}

ModelAbstract::ModelAbstract(const ModelAbstract &copy)
{
    stats = copy.stats;
    urlImage = copy.urlImage;
    squareBaseW = copy.squareBaseW;
    squareBaseL = copy.squareBaseL;
    unitPower = copy.unitPower;
    options = copy.options;
}

ModelAbstract::~ModelAbstract(){}

void ModelAbstract::save(const QString path)
{
}

ModelAbstract *ModelAbstract::setFromFile(const QString path)
{
}

QString ModelAbstract::displayStringInfo()
{
}

QString ModelAbstract::displayBaseInfo()
{
    QString s;
    QTextStream info(&s);
    info << stats.getName() << endl;
    info << "Points : " << computePoints() << endl;
    info << "====================================================" << endl;
    info << stats.displayString();
    info << "====================================================" << endl;
    info << "Available options : " << endl;
	QList<OptionModel>::iterator i;
	for(i = options.begin(); i < options.end() ; ++i)
	{
        info << "----------------------------" << endl;
        info << i->displayString() << endl;
	}
    return s;
}

ModelAbstract *ModelAbstract::setFromUI(const ParamsfromUImodel *params)
{
    qDebug() << "damned this is setfromUI of MODELABSTRACT...";


}


void ModelAbstract::load(const QString path)
{
}


StatsModel ModelAbstract::getStats() const
{
    return stats;
}

void ModelAbstract::setStats(const StatsModel &value)
{
    stats = value;
}


int ModelAbstract::getUnitPower() const
{
    return unitPower;
}

void ModelAbstract::setUnitPower(int value)
{
    unitPower = value;
}

QPixmap *ModelAbstract::getImage() const
{
    return image;
}

void ModelAbstract::setImage(QPixmap *value)
{
    image = value;
}

int ModelAbstract::getSquareBaseL() const
{
    return squareBaseL;
}

void ModelAbstract::setSquareBaseL(int value)
{
    squareBaseL = value;
}

int ModelAbstract::getSquareBaseW() const
{
    return squareBaseW;
}

void ModelAbstract::setSquareBaseW(int value)
{
    squareBaseW = value;
}

bool ModelAbstract::getFigSupInd() const
{
    return figSupInd;
}

void ModelAbstract::setFigSupInd(bool value)
{
    figSupInd = value;
}


QList<OptionModel> ModelAbstract::getOptions() const
{
    return options;
}

void ModelAbstract::setOptions(const QList<OptionModel> &value)
{
    options = value;
}

void ModelAbstract::addOption(const OptionModel &opt)
{
    options << opt;

    //std::cout << options[0].getName().toStdString();
}

void ModelAbstract::removeOption(const OptionModel& opt)
{
    options.removeOne(opt);
}

void ModelAbstract::clearOptions()
{
    options.clear();
}

QString ModelAbstract::getUrlImage() const
{
    return urlImage;
}

void ModelAbstract::setUrlImage(const QString &value)
{
    urlImage = value;
}

int ModelAbstract::computePoints()
{
}

QDataStream &operator <<(QDataStream & out, const ModelAbstract & obj)
{
    out << obj.stats
        << obj.squareBaseW
        << obj.squareBaseL
        << obj.unitPower
        << obj.figSupInd
        << obj.urlImage
        << obj.options.size();

    for(int i = 0 ; i < obj.options.size() ; i++)
    {
        out << obj.options[i];
    }

    return out;
}

QDataStream &operator >>(QDataStream & in, ModelAbstract & obj)
{
    int nb;

    in >> obj.stats;
    in >> obj.squareBaseW;
    in >> obj.squareBaseL;
    in >> obj.unitPower;
    in >> obj.figSupInd;
    in >> obj.urlImage;

    in >> nb;

    for(int i = 0 ; i < nb ; i++)
    {
        OptionModel o;
        in >> o;
        obj.addOption(o);
    }

    return in;
}
