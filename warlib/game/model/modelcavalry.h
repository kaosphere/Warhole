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
    Q_OBJECT
public:
    ModelCavalry(QObject* parent = 0);

    ModelCavalry(const QString &n, const QString &move, const QString &weaponS, const QString &balisticS,
                 const QString &strength, const QString &toughness, const QString &wounds,
                 const QString &init, const QString &attacks, const QString &leadership,
                 const QString &save, const QString &invSave, const int points, const int &widthBase,
                 const int &lengthBase, const int &unitP, const QString& urlImage , bool figSup,
                 const QString& specRules, const ModelType &t, QObject* parent = 0);
    ModelCavalry(const ModelCavalry &copy);
    virtual ~ModelCavalry();

    QString getSpecialRules() const;
    void setSpecialRules(const QString &value);

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

    static void initModelCavalrySystem();
    virtual ModelCavalry* setFromFile(QString path);
    virtual ModelCavalry* setFromUI(const ParamsfromUImodel* params);
    virtual void load(QString path);
    virtual void save(QString path);

    //! clone
    /*!
    * VIRTUAL : Method that returns a copy of the object. This is used to copy a pointer
    * to a derived class.
    */
    virtual ModelAbstract* clone();
    
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

#endif // MODELCAVALRY_H
