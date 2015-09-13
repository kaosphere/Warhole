#ifndef MODELCHARRIOT_H
#define MODELCHARRIOT_H

#include <QObject>
#include <QtCore>
#include <QtWidgets>

#include "modelabstract.h"
#include "modelinfantery.h"

class ModelCharriot : public ModelAbstract
{
    Q_OBJECT
public:
    ModelCharriot(QObject* parent = 0);

    ModelCharriot(const QString &n, const QString &move, const QString &weaponS, const QString &balisticS,
                  const QString &strength, const QString &toughness, const QString &wounds,
                  const QString &init, const QString &attacks, const QString &leadership,
                  const QString &save, const QString &invSave, const int points, const int &widthBase,
                  const int &lengthBase, const int &unitP, const QString& urlImage , bool figSup,
                  const QString& specRules, const ModelType &t, QObject *parent = 0);
    ModelCharriot(const ModelCharriot &copy);
    virtual ~ModelCharriot();

    static void initModelCharriotSystem();
    virtual ModelCharriot* setFromFile(QString path);
    virtual ModelCharriot* setFromUI(const ParamsfromUImodel *params);
    virtual void load(QString path);
    virtual void save(QString path);

    //! SerializeOut
    /*!
     * VIRTUAL : Method to serialize unknown modelabstract pointer.
     */
    virtual QDataStream &serializeOut(QDataStream &out);

    //! SerializeIn
    /*!
     * VIRTUAL : Method to serialize unknown modelabstract pointer.
     * \param in QDataStream from which the data is read to feed the object.
     */
    virtual QDataStream &serializeIn(QDataStream& in);

    //! clone
    /*!
    * VIRTUAL : Method that returns a copy of the object. This is used to copy a pointer
    * to a derived class.
    */
    virtual ModelAbstract* clone();
    
    virtual QString displayStringInfo();
    virtual QString getHtml();

    QString getSpecialRules() const;
    void setSpecialRules(const QString &value);

    QList<StatsModel> getCrew() const;
    void setCrew(const QList<StatsModel> &value);
    void addCrew(StatsModel c);
    void clearCrew();

    virtual int computePoints();
    virtual int computePointsWithoutOptions();

private:
    QString specialRules;
    QList<StatsModel> crew;

    friend QDataStream & operator << (QDataStream &, const ModelCharriot &);
    friend QDataStream & operator >> (QDataStream &, ModelCharriot &);
};

Q_DECLARE_METATYPE(ModelCharriot)

#endif // MODELCHARRIOT_H
