#ifndef MODELINFANTERY_H
#define MODELINFANTERY_H

#include <QObject>
#include <QtCore>
#include <QtWidgets>

#include "modelabstract.h"

class ModelInfantery : public ModelAbstract
{
public:
    ModelInfantery();

    ModelInfantery(const QString &n, const QString &move, const QString &weaponS, const QString &balisticS,
                  const QString &strength, const QString &toughness, const QString &wounds,
                  const QString &init, const QString &attacks, const QString &leadership,
                  const QString &save, const QString &invSave, const int points, const int &widthBase,
                  const int &lengthBase, const int &unitP, const QString& urlImage , bool figSup,
                  const QString& specRules);
    ModelInfantery(const ModelInfantery &copy);
    ~ModelInfantery();

    static void initModelInfanterySystem();
    virtual ModelInfantery* clone(QString path);
    virtual void load(QString path);
    void save(QString path);

    QString getSpecialRules() const;
    void setSpecialRules(const QString &value);

private:
    QString specialRules;

    friend QDataStream & operator << (QDataStream &, const ModelInfantery &);
    friend QDataStream & operator >> (QDataStream &, ModelInfantery &);

};

Q_DECLARE_METATYPE(ModelInfantery)
QDataStream & operator << (QDataStream & out, const  ModelInfantery &);
QDataStream & operator >> (QDataStream & in,  ModelInfantery &);

#endif // MODELINFANTERY_H
