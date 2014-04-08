#ifndef MODELMONSTER_H
#define MODELMONSTER_H

#include <QObject>
#include <QtCore>
#include <QtWidgets>

#include "modelabstract.h"
#include "modelinfantery.h"

class ModelMonster : public ModelAbstract
{

public:
    ModelMonster();

    ModelMonster(const QString &n, const QString &move, const QString &weaponS, const QString &balisticS,
                 const QString &strength, const QString &toughness, const QString &wounds,
                 const QString &init, const QString &attacks, const QString &leadership,
                 const QString &save, const QString &invSave, const int points, const int &widthBase,
                 const int &lengthBase, const int &unitP, const QString& urlImage , bool figSup,
                 const QString& specRules, bool hasCrew,const ModelType &t);
    ModelMonster(const ModelMonster &copy);

    virtual ~ModelMonster();

    static void initModelMonsterSystem();
    virtual ModelMonster* setFromFile(QString path);
    virtual ModelMonster* setFromUI(const ParamsfromUImodel *params);
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

    bool getHasACrew() const;
    void setHasACrew(bool value);

    int computePoints();

    QList<ModelInfantery *> getCrew() const;
    void setCrew(const QList<ModelInfantery *> &value);

    ModelType getType() const;
    void setType(const ModelType &value);

private:
    ModelType type;
    QString specialRules;
    QList<ModelInfantery *> crew;
    bool hasACrew;

    friend QDataStream & operator << (QDataStream &, const ModelMonster &);
    friend QDataStream & operator >> (QDataStream &, ModelMonster &);
};

Q_DECLARE_METATYPE(ModelMonster)
QDataStream & operator << (QDataStream & out, const  ModelMonster &);
QDataStream & operator >> (QDataStream & in,  ModelMonster &);

#endif // MODELMONSTER_H
