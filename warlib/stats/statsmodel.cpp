#include "statsmodel.h"

StatsModel::StatsModel()
{
}

StatsModel::StatsModel(const StatsModel &stat)
{
    name = stat.name;
    m = stat.m;
    ws = stat.ws;
    bs = stat.bs;
    s = stat.s;
    t = stat.t;
    w = stat.w;
    i = stat.i;
    a = stat.a;
    ld = stat.ld;
    svg = stat.svg;
    svgInv = stat.svgInv;
    points = stat.points;
}

StatsModel::StatsModel(const QString &n, const QString &move, const QString &weaponS, const QString &balisticS, const QString &strength, const QString &toughness, const QString &wounds, const QString &init, const QString &attacks, const QString &leadership, const QString &save, const QString &invSave, int p)
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
    points = p;
}

StatsModel::~StatsModel()
{
}

StatsModel & StatsModel::operator =(const StatsModel &stat)
{
    name = stat.name;
    m = stat.m;
    ws = stat.ws;
    bs = stat.bs;
    s = stat.s;
    t = stat.t;
    w = stat.w;
    i = stat.i;
    a = stat.a;
    ld = stat.ld;
    svg = stat.svg;
    svgInv = stat.svgInv;
    points = stat.points;
}

// Overloading of << operator
QDataStream & operator << (QDataStream & out, const StatsModel & obj)
{
    //out << obj.streamOut();
    out << obj.name
        << obj.m
        << obj.ws
        << obj.bs
        << obj.s
        << obj.t
        << obj.w
        << obj.i
        << obj.a
        << obj.ld
        << obj.svg
        << obj.svgInv
        << obj.points;

    return out;
}

// Overloading of >> operator
QDataStream & operator >> (QDataStream & in, StatsModel & obj)
{
    //obj.streamIn(in);
    in >> obj.name;
    in >> obj.m;
    in >> obj.ws;
    in >> obj.bs;
    in >> obj.s;
    in >> obj.t;
    in >> obj.w;
    in >> obj.i;
    in >> obj.a;
    in >> obj.ld;
    in >> obj.svg;
    in >> obj.svgInv;
    in >> obj.points;
    
    return in;
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


int StatsModel::getPoints() const
{
    return points;
}

void StatsModel::setPoints(int value)
{
    points = value;
}
