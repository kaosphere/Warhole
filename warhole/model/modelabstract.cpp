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
    out << name
        << m
        << ws
        << bs
        << s
        << t
        << w
        << i
        << a
        << ld
        << svg
        << svgInv
        << squareBaseW
        << squareBaseL
        << unitPower
        << figSupInd
        << urlImage;


    return out;
}

void ModelAbstract::streamIn(QDataStream & in)
{
    in >> name;
    in >> m;
    in >> ws;
    in >> bs;
    in >> s;
    in >> t;
    in >> w;
    in >> i;
    in >> a;
    in >> ld;
    in >> svg;
    in >> svgInv;
    in >> squareBaseW;
    in >> squareBaseL;
    in >> unitPower;
    in >> figSupInd;
    in >> urlImage;
}
