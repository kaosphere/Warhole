#include "statsmodel.h"

StatsModel::StatsModel()
{
}


QString StatsModel::getName() const
{
    return name;
}


QString StatsModel::getSvgInv() const
{
    return svgInv;
}

void StatsModel::setSvgInv(const QString &value)
{
    svgInv = value;
}

QString StatsModel::getSvg() const
{
    return svg;
}

void StatsModel::setSvg(const QString &value)
{
    svg = value;
}

QString StatsModel::getLd() const
{
    return ld;
}

void StatsModel::setLd(const QString &value)
{
    ld = value;
}

QString StatsModel::getA() const
{
    return a;
}

void StatsModel::setA(const QString &value)
{
    a = value;
}

QString StatsModel::getI() const
{
    return i;
}

void StatsModel::setI(const QString &value)
{
    i = value;
}

QString StatsModel::getW() const
{
    return w;
}

void StatsModel::setW(const QString &value)
{
    w = value;
}

QString StatsModel::getT() const
{
    return t;
}

void StatsModel::setT(const QString &value)
{
    t = value;
}

QString StatsModel::getS() const
{
    return s;
}

void StatsModel::setS(const QString &value)
{
    s = value;
}

QString StatsModel::getBs() const
{
    return bs;
}

void StatsModel::setBs(const QString &value)
{
    bs = value;
}

QString StatsModel::getWs() const
{
    return ws;
}

void StatsModel::setWs(const QString &value)
{
    ws = value;
}

QString StatsModel::getM() const
{
    return m;
}

void StatsModel::setM(const QString &value)
{
    m = value;
}
void StatsModel::setName(const QString &value)
{
    name = value;
}

