#ifndef MODELCAVALRY_H
#define MODELCAVALRY_H

#include <QObject>
#include <QtCore>
#include <QtWidgets>

#include "modelabstract.h"
#include "Utilities/QLogger/QLogger.h"

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
    
    virtual QString displayStringInfo();

    QList<StatsModel> getMount() const;
    void setMount(const QList<StatsModel> &value);

    void addMount(StatsModel m);
    void clearMount();

    virtual int computePoints();

private:
	static const QString LOG_ID_INFO;
    static const QString LOG_ID_TRACE;
    static const QString LOG_ID_WARN;
    static const QString LOG_ID_ERR;

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
