#ifndef OPTIONMODEL_H
#define OPTIONMODEL_H

#include <QObject>
#include <QtCore>
#include <QtWidgets>

#include "defines.h"

class OptionModel : public QObject
{
    Q_OBJECT
public:
    explicit OptionModel(QObject* parent = 0);

    OptionModel(const QString &n, const int& pts, const bool& act, const QString& specRules, const bool &ro, QObject* parent = 0);

    OptionModel(const OptionModel & obj);

    ~OptionModel();

    bool operator==(const OptionModel&);
    OptionModel& operator=(const OptionModel&);
    
    QString displayString();
    
    QString getHtml();

    QString getName() const;
    void setName(const QString &value);

    int getNbPoints() const;
    void setNbPoints(int value);

    bool isActivated() const;
    void setActivated(bool value);

    QString getSpecialRules() const;
    void setSpecialRules(const QString &value);

    bool isRegimentOptions() const;
    void setRegimentOptions(bool value);

protected:
    QString name;
    int nbPoints;
    bool activated;
    QString specialRules;
    bool regimentOptions;

    friend QDataStream & operator << (QDataStream &, const OptionModel &);
    friend QDataStream & operator >> (QDataStream &, OptionModel &);
    
signals:
    
public slots:
    
};

#endif // OPTIONMODEL_H
