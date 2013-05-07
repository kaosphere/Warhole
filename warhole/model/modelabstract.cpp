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

ModelAbstract::ModelAbstract(const QString &n, const QString &move, const QString &weaponS, const QString &balisticS, const QString &strength, const QString &toughness, const QString &wounds, const QString &init, const QString &attacks, const QString &leadership, const QString &save, const QString &invSave, const int &widthBase, const int &lengthBase, const int &unitP, const QString &url, bool figSup)
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
}

ModelAbstract::~ModelAbstract(){}


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

void ModelAbstract::addOption(OptionModel opt)
{
    options<<opt;
}

void ModelAbstract::removeOption(OptionModel opt)
{
    options.removeOne(opt);
}

QString ModelAbstract::getUrlImage() const
{
    return urlImage;
}

void ModelAbstract::setUrlImage(const QString &value)
{
    urlImage = value;
}



QDataStream & ModelAbstract::streamOut() const
{
    QDataStream out;
    //out << stats
    out << squareBaseW
        << squareBaseL
        << unitPower
        << figSupInd
        << urlImage;


    return out;
}

void ModelAbstract::streamIn(QDataStream & in)
{
    //in >> stats;
    in >> squareBaseW;
    in >> squareBaseL;
    in >> unitPower;
    in >> figSupInd;
    in >> urlImage;
}
