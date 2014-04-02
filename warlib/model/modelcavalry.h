#ifndef MODELCAVALRY_H
#define MODELCAVALRY_H

#include <QObject>
#include <QtCore>
#include <QtWidgets>
#include <Qt>
#include <QTextDocument>

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
                 const QString& specRules, const ModelType &t);
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
    virtual QString getHtml();

    StatsModel getMount() const;
    void setMount(const StatsModel &value);

    virtual int computePoints();

    ModelType getType() const;
    void setType(const ModelType &value);

private:
    static const QString LOG_ID_INFO;
    static const QString LOG_ID_TRACE;
    static const QString LOG_ID_WARN;
    static const QString LOG_ID_ERR;

    ModelType type;
    QString specialRules;
    StatsModel mount;

    //ModelAbstract* mount;
    friend QDataStream & operator << (QDataStream &, const ModelCavalry &);
    friend QDataStream & operator >> (QDataStream &, ModelCavalry &);
};

Q_DECLARE_METATYPE(ModelCavalry)
QDataStream & operator << (QDataStream & out, const ModelCavalry &);
QDataStream & operator >> (QDataStream & in, ModelCavalry &);

#endif // MODELCAVALRY_H
