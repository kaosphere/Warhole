#ifndef OPTIONMODEL_H
#define OPTIONMODEL_H

#include <QObject>
#include <QtCore>
#include <QtWidgets>

class OptionModel : public QObject
{
    Q_OBJECT
public:
    explicit OptionModel(QObject *parent = 0);

    OptionModel(const QString &n, const int& pts, const bool& act, const QString& specRules,
                QObject *parent = 0);

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
    
signals:
    
public slots:
    
};

#endif // OPTIONMODEL_H
