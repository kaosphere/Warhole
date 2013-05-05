#include "modelabstract.h"

ModelAbstract::ModelAbstract()
{
}

ModelAbstract::ModelAbstract(const QString &n, const QString &move, const QString &weaponS,
                             const QString &balisticS, const QString &strength, const QString &toughness,
                             const QString &wounds, const QString &init, const QString &attacks,
                             const QString &leadership, const QString &save, const QString &invSave,
                             const int &widthBase, const int &lengthBase, const int &unitP, const QString &urlImage,
                             bool figSup)
{
    name = n;
    m = move;
    ws = weaponS;
    bs = balisticS;
    s = strength;
    t = toughness;
    w = wounds;
    i = init;
    a = attacks;
    ld = leadership;
    svg = save;
    svgInv = invSave;
    squareBaseW = widthBase;
    squareBaseL = lengthBase;
    unitPower = unitP;
    
    image = new QPixmap(urlImage);
    
    figSupInd = figSup;
}

ModelAbstract::ModelAbstract(const ModelAbstract &Copy)
{
    name = Copy.name;
    m = Copy.m;
    ws = Copy.ws;
    bs = Copy.bs;
    s = Copy.s;
    t = Copy.t;
    w = Copy.w;
    i = Copy.i;
    a = Copy.a;
    ld = Copy.ld;
    svg = Copy.svg;
    svgInv = Copy.svgInv;
    squareBaseW = Copy.squareBaseW;
    squareBaseL = Copy.squareBaseL;
    unitPower = Copy.unitPower;
}

ModelAbstract::~ModelAbstract(){}


QString ModelAbstract::getSvgInv() const
{
    return svgInv;
}

void ModelAbstract::setSvgInv(const QString &value)
{
    svgInv = value;
}

QString ModelAbstract::getSvg() const
{
    return svg;
}

void ModelAbstract::setSvg(const QString &value)
{
    svg = value;
}

QString ModelAbstract::getLd() const
{
    return ld;
}

void ModelAbstract::setLd(const QString &value)
{
    ld = value;
}

QString ModelAbstract::getA() const
{
    return a;
}

void ModelAbstract::setA(const QString &value)
{
    a = value;
}

QString ModelAbstract::getI() const
{
    return i;
}

void ModelAbstract::setI(const QString &value)
{
    i = value;
}

QString ModelAbstract::getW() const
{
    return w;
}

void ModelAbstract::setW(const QString &value)
{
    w = value;
}

QString ModelAbstract::getT() const
{
    return t;
}

void ModelAbstract::setT(const QString &value)
{
    t = value;
}

QString ModelAbstract::getS() const
{
    return s;
}

void ModelAbstract::setS(const QString &value)
{
    s = value;
}

QString ModelAbstract::getBs() const
{
    return bs;
}

void ModelAbstract::setBs(const QString &value)
{
    bs = value;
}

QString ModelAbstract::getWs() const
{
    return ws;
}

void ModelAbstract::setWs(const QString &value)
{
    ws = value;
}

QString ModelAbstract::getM() const
{
    return m;
}

void ModelAbstract::setM(const QString &value)
{
    m = value;
}
QString ModelAbstract::getName() const
{
    return name;
}

void ModelAbstract::setName(const QString &value)
{
    name = value;
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


QList<OptionModel *> ModelAbstract::getOptions() const
{
    return options;
}

void ModelAbstract::setOptions(const QList<OptionModel *> &value)
{
    options = value;
}

void ModelAbstract::addOption(OptionModel *opt)
{
    options<<opt;
}

void ModelAbstract::removeOption(OptionModel *opt)
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
