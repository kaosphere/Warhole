#ifndef HISTORIC_H
#define HISTORIC_H

#include <game/historic/HistoricAbstractItem.h>
#include <QString>
#include <QtCore>
#include <QTextStream>

class Historic
{
public:
    Historic();
    ~Historic();
    void addHistoricItem(HistoricAbstractItem* h);
    void removeHistoricItem(HistoricAbstractItem &h);
    void removeHistoricItem(HistoricAbstractItem *h);
    QList<HistoricAbstractItem*>& getHistoric();
    void setHistoric(const QList<HistoricAbstractItem *> &h);
    QString getHistoricString();

private:
    QList<HistoricAbstractItem*> historicList;
};

#endif // HISTORIC_H
