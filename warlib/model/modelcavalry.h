#ifndef MODELCAVALRY_H
#define MODELCAVALRY_H

#include <QObject>
#include <QtCore>
#include <QtWidgets>

#include "modelabstract.h"

class ModelCavalry : public ModelAbstract
{
public:
    ModelCavalry();

    ModelCavalry(const QString &n, const QString &move, const QString &weaponS, const QString &balisticS,
                  const QString &strength, const QString &toughness, const QString &wounds,
                  const QString &init, const QString &attacks, const QString &leadership,
                  const QString &save, const QString &invSave, const int points, const int &widthBase,
                  const int &lengthBase, const int &unitP, const QString& urlImage , bool figSup,
                  const QString& specRules);
    ModelCavalry(const ModelCavalry &copy);
    virtual ~ModelCavalry();

    QString getSpecialRules() const;
    void setSpecialRules(const QString &value);

    static void initModelCavalrySystem();
    virtual ModelCavalry* setFromFile(QString path);
    virtual ModelCavalry* setFromUI(const ParamsfromUImodel* params);
    virtual void load(QString path);
    virtual void save(QString path);

    QList<StatsModel> getMount() const;
    void setMount(const QList<StatsModel> &value);

    void addMount(StatsModel m);
    void clearMount();

private:
    QString specialRules;
    QList<StatsModel> mount;

    //ModelAbstract* mount;
    friend QDataStream & operator << (QDataStream &, const ModelCavalry &);
    friend QDataStream & operator >> (QDataStream &, ModelCavalry &);
};

Q_DECLARE_METATYPE(ModelCavalry)
QDataStream & operator << (QDataStream & out, const ModelCavalry &);
QDataStream & operator >> (QDataStream & in, ModelCavalry &);

#endif // MODELCAVALRY_H
