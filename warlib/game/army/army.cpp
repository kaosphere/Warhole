#include "army.h"

using namespace QLogger;

const QString Army::LOG_ID_INFO = "Army_info";
const QString Army::LOG_ID_TRACE = "Army_trace";
const QString Army::LOG_ID_WARN = "Army_warn";
const QString Army::LOG_ID_ERR = "Army_err";

Army::Army(QObject* parent) : QObject(parent)
{
    QLoggerManager *manager = QLoggerManager::getInstance();
    manager->addDestination("./logs/lastrun.log", QStringList(LOG_ID_TRACE), QLogger::TraceLevel);
    manager->addDestination("./logs/lastrun.log", QStringList(LOG_ID_INFO), QLogger::InfoLevel);
    manager->addDestination("./logs/lastrun.log", QStringList(LOG_ID_ERR), QLogger::ErrorLevel);
    manager->addDestination("./logs/lastrun.log", QStringList(LOG_ID_WARN), QLogger::WarnLevel);
}

Army::Army(const Army &copy) : QObject(copy.parent())
{
    QLoggerManager *manager = QLoggerManager::getInstance();
    manager->addDestination("./logs/lastrun.log", QStringList(LOG_ID_TRACE), QLogger::TraceLevel);
    manager->addDestination("./logs/lastrun.log", QStringList(LOG_ID_INFO), QLogger::InfoLevel);
    manager->addDestination("./logs/lastrun.log", QStringList(LOG_ID_ERR), QLogger::ErrorLevel);
    manager->addDestination("./logs/lastrun.log", QStringList(LOG_ID_WARN), QLogger::WarnLevel);


    name = copy.name;
    units = copy.units;
}

Army::~Army()
{
    // Nothing !!
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
    units.removeOne(u);
}

void Army::save(const QString& path)
{
    if(!QFile::remove(path)) throw WarlibException(0,tr("QFile::remove() failed for an un"), EXCEPTION_LOW);
    QSettings savedFile(path, QSettings::IniFormat);
    savedFile.setValue("Army", qVariantFromValue(*this));
    savedFile.sync();
}

void Army::load(const QString& path)
{
    Army temp;

    QSettings readFile(path, QSettings::IniFormat);
    temp = readFile.value("Army", qVariantFromValue(Army())).value<Army>();

    name = temp.name;
    units = temp.units;
}

QDataStream &operator <<(QDataStream & out, const Army & obj)
{
    out << SAVE_VERSION
        << obj.name
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
    int version = 0;

    in >> version;
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
    html += QString("<body style=\"font-size:10pt\">\n");
    html += QString("<h1 align='center'>Armée : %1</h1>\n")
            .arg(name.toHtmlEscaped());
    html += QString("<h2>Nb de points total de l'armee : %1 pts</h2>\n")
            .arg(QString::number(computePoints()));
    html += "<br/>\n";
    for(int i = 0; i < units.size() ; ++i)
    {
        html += units[i].getHtml();
    }
    html += QString("</body>\n");
    html += QString("</html>\n");

    QLog_Info(LOG_ID_INFO, html);
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


bool Army::operator ==(const Army &obj)
{
    if(name == obj.name && units == obj.units)
        return true;
    else return false;
}

Army &Army::operator =(const Army &obj)
{
    name = obj.name;
    units = obj.units;
    return *this;
}
