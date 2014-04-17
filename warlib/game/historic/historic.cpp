#include "historic.h"

Historic::Historic()
{
}

Historic::~Historic()
{
    qDeleteAll(historicList);
}

void Historic::addHistoricItem(HistoricAbstractItem* h)
{
    historicList.append(h);
}

void Historic::removeHistoricItem(HistoricAbstractItem &h)
{
    historicList.removeOne(&h);
}

void Historic::removeHistoricItem(HistoricAbstractItem *h)
{
    historicList.removeOne(h);
}


QList<HistoricAbstractItem *> &Historic::getHistoric()
{
    return historicList;
}

void Historic::setHistoric(const QList<HistoricAbstractItem*> &h)
{
    historicList = h;
}

QString Historic::getHistoricString()
{
    QString s;
    QTextStream info(&s);

    for(int i = 0; i < historicList.size(); ++i)
    {
        info << historicList[i]->getMessage() << endl;
    }
}
