#include "modelabstract.h"

ModelAbstract::ModelAbstract(QObject *parent) :
    QObject(parent)
{
}

ModelAbstract::ModelAbstract(const QString &n, const QString &move, const QString &weaponS,
                             const QString &balisticS, const QString &strength, const QString &toughness,
                             const QString &wounds, const QString &init, const QString &attacks,
                             const QString &leadership, const QString &save, const QString &invSave,
                             const int &widthBase, const int &lengthBase, const int &unitP, const QString &urlImage,
                             bool figSup, QObject *parent) :
    QObject(parent)
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


QList<ModelAbstract *> ModelAbstract::getChampion() const
{
    return champion;
}

void ModelAbstract::setChampion(QList<ModelAbstract *> value)
{
    champion += value;
}

void ModelAbstract::addChampion(ModelAbstract *ch)
{
    champion<<ch;
}

void ModelAbstract::removeChampion(ModelAbstract *ch)
{
    champion.removeOne(ch);
}


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
