#include "statsmodel.h"

StatsModel::StatsModel(QObject *parent) : QObject(parent)
{
}

StatsModel::StatsModel(const StatsModel &stat) : QObject(stat.parent())
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

StatsModel::StatsModel(const QString &n,
                       const QString &move,
                       const QString &weaponS,
                       const QString &balisticS,
                       const QString &strength,
                       const QString &toughness,
                       const QString &wounds,
                       const QString &init,
                       const QString &attacks,
                       const QString &leadership,
                       const QString &save,
                       const QString &invSave,
                       int p,
                       QObject *parent) : QObject(parent)
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

    return *this;
}

bool StatsModel::operator ==(const StatsModel & stat)
{
    if(name == stat.name &&
        m == stat.m &&
        ws == stat.ws &&
        bs == stat.bs &&
        s == stat.s &&
        t == stat.t &&
        w == stat.w &&
        i == stat.i &&
        a == stat.a &&
        ld == stat.ld &&
        svg == stat.svg &&
        svgInv == stat.svgInv &&
        points == stat.points)
    {
        return true;
    }
    else return false;
}

// Overloading of << operator
QDataStream & operator << (QDataStream & out, const StatsModel & obj)
{
    //out << obj.streamOut();
    out << SAVE_VERSION
        << obj.name
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
    int version = 0;
    //obj.streamIn(in);
    in >> version;
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

QString StatsModel::displayString() const
{
    QString str;
    QTextStream info(&str);
    info << "Model points :             " << points << endl;
    info << "Move :                     " << m << endl;
    info << "Weapon skill :             " << ws << endl;
    info << "Balistic skill :           " << bs << endl;
    info << "Strength :                 " << s << endl;
    info << "Toughness :                " << t << endl;
    info << "Wounds :                   " << w << endl;
    info << "Initiative :               " << i << endl;
    info << "Attacks :                  " << a << endl;
    info << "Leadership :               " << ld << endl;
    info << "Armor save :               " << svg << endl;
    info << "Invulnerable Armor save :  " << svgInv << endl;

    return str;
}

QString StatsModel::getHtml() const
{
    QString html("<table cols=11 border=1 cellpadding=5>\n");
	html += "<tr>\n";
    html += "<td align='center'>M</td>\n";
    html += "<td align='center'>CC</td>\n";
    html += "<td align='center'>CT</td>\n";
    html += "<td align='center'>F</td>\n";
    html += "<td align='center'>E</td>\n";
    html += "<td align='center'>PV</td>\n";
    html += "<td align='center'>I</td>\n";
    html += "<td align='center'>A</td>\n";
    html += "<td align='center'>Cmd</td>\n";
    html += "<td align='center'>Svg</td>\n";
    html += "<td align='center'>SvgInv</td>\n";
	html += "</tr>\n";
	html += "<tr>\n";
	html += QString("<td align='center'>%1</td>\n").arg(m);
	html += QString("<td align='center'>%1</td>\n").arg(ws);
	html += QString("<td align='center'>%1</td>\n").arg(bs);
	html += QString("<td align='center'>%1</td>\n").arg(s);
	html += QString("<td align='center'>%1</td>\n").arg(t);
	html += QString("<td align='center'>%1</td>\n").arg(w);
	html += QString("<td align='center'>%1</td>\n").arg(i);
	html += QString("<td align='center'>%1</td>\n").arg(a);
	html += QString("<td align='center'>%1</td>\n").arg(ld);
	html += QString("<td align='center'>%1</td>\n").arg(svg);
	html += QString("<td align='center'>%1</td>\n").arg(svgInv);
	html += "</tr>\n";
	html += "</table>\n";

    return html;
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
