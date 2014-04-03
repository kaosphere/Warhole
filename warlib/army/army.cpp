#include "army.h"

Army::Army()
{
}

void Army::initArmySystem()
{
    qRegisterMetaTypeStreamOperators<Army>("Army");
    qMetaTypeId<Army>();
}

QString Army::getName() const
{
    return name;
}

void Army::setName(const QString &value)
{
    name = value;
}


QList<RegimentAbstract>& Army::getUnits()
{
    return units;
}

void Army::setUnits(const QList<RegimentAbstract> &value)
{
    units = value;
}


void Army::addUnit(const RegimentAbstract &u)
{
    units.append(u);
}

void Army::removeUnit(const RegimentAbstract &u)
{
	// Since Army will not be used as a game descriptor, we don't care 
	// removing one or the other if two regiments are identical
    units.removeOne(u);
}

void Army::save(const QString& path)
{
	QFile::remove(path);
    QSettings savedFile(path, QSettings::IniFormat);
    savedFile.setValue("Army", qVariantFromValue(*this));
    savedFile.sync();
}

void Army::load(const QString& path)
{
	Army temp;

    QSettings readFile(path, QSettings::IniFormat);
    temp = readFile.value("Army", qVariantFromValue(Army())).value< Army>();

    name = temp.name;
    units = temp.units;
}

QDataStream &operator <<(QDataStream & out, const Army & obj)
{
    out << obj.name
        << obj.units.size();
    for(int i = 0; i < obj.units.size(); i++)
    {
        out << obj.units[i];
    }

    return out;
}

QDataStream &operator >>(QDataStream & in, Army & obj)
{
    int nb;

    in >> obj.name;
    in >> nb;

    for(int i = 0 ; i < nb ; i++)
    {
        RegimentAbstract u;
        in >> u;
        obj.addUnit(u);
    }

    return in;
}

QString Army::displayShortInfo() const
{
	QString s;
	QTextStream info(&s);
	info << "////////////////////////////////////////////////////////" << endl;
	info << "//////                    ARMY                    //////" << endl;
	info << "////////////////////////////////////////////////////////" << endl;
	info << "Name : " << name << endl;
	info << "////////////////////////////////////////////////////////" << endl;

	for(int i = 0; i < units.size() ; ++i)
	{
		info << "////////////////////////////////////////////////////////" << endl;
		info << units[i].displayShortInfo() << endl;
	}
	info << "////////////////////////////////////////////////////////" << endl;
	info << "////////////////////////////////////////////////////////" << endl;
    return s;
}

QString Army::getHtml()
{
    QString html("<html>\n");
    html += QString("<body>\n");
    html += QString("<h1 align='center'>Armée : %1</h1>\n")
            .arg(name.toHtmlEscaped());
    html += QString("<h2>Nb de points total de l'armee : %1 pts</h2>\n")
            .arg(QString::number(computePoints()));

    for(int i = 0; i < units.size() ; ++i)
    {
        html += units[i].getHtml();
    }
    html += QString("</body>\n");
    html += QString("</html>\n");
    return html;
}

int Army::computePoints()
{
    int p = 0;
    for(int i = 0; i < units.size() ; ++i)
    {
        p += units[i].computePoints();
    }
    return p;
}

QString Army::displayInfo() const
{
	QString s;
    QTextStream info(&s);
    info << "////////////////////////////////////////////////////////" << endl;
    info << "//////                    ARMY                    //////" << endl;
    info << "////////////////////////////////////////////////////////" << endl;
    info << "Name : " << name << endl;
    info << "////////////////////////////////////////////////////////" << endl;
    
    for(int i = 0; i < units.size() ; ++i)
	{
        info << "////////////////////////////////////////////////////////" << endl;
        info << units[i].displayInfo() << endl;
    }
    info << "////////////////////////////////////////////////////////" << endl;
    info << "////////////////////////////////////////////////////////" << endl;
    return s;
}
