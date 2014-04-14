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
                  const QString& specRules,const ModelType &t);
    ModelInfantery(const ModelInfantery &copy);
    virtual ~ModelInfantery();

    static void initModelInfanterySystem();
    virtual ModelInfantery* setFromFile(QString path);
    virtual ModelInfantery* setFromUI(const ParamsfromUImodel *params);
    virtual void load(QString path);
    virtual void save(QString path);

    //! SerializeOut
    /*!
     * VIRTUAL : Method to serialize unknown modelabstract pointer.
     */
    virtual QDataStream& serializeOut(QDataStream& out);

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

    int computePoints();

    ModelType getType() const;
    void setType(const ModelType &value);

private:
    ModelType type;
    QString specialRules;

    friend QDataStream & operator << (QDataStream &, const ModelInfantery &);
    friend QDataStream & operator >> (QDataStream &, ModelInfantery &);

};

Q_DECLARE_METATYPE(ModelInfantery)

#endif // MODELINFANTERY_H
