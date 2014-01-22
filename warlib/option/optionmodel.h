#ifndef OPTIONMODEL_H
#define OPTIONMODEL_H

#include <QObject>
#include <QtCore>
#include <QtWidgets>

class OptionModel
{
public:
    explicit OptionModel();

    OptionModel(const QString &n, const int& pts, const bool& act, const QString& specRules);

    OptionModel(const OptionModel & obj);

    bool operator==(const OptionModel&);
    OptionModel& operator=(const OptionModel&);

    QString getName() const;
    void setName(const QString &value);

    int getNbPoints() const;
    void setNbPoints(int value);

    bool isActivated() const;
    void setActivated(bool value);

    QString getSpecialRules() const;
    void setSpecialRules(const QString &value);

protected:
    QString name;
    int nbPoints;
    bool activated;
    QString specialRules;

    friend QDataStream & operator << (QDataStream &, const OptionModel &);
    friend QDataStream & operator >> (QDataStream &, OptionModel &);
    
signals:
    
public slots:
    
};

#endif // OPTIONMODEL_H
