#ifndef MODELCHARACTER_H
#define MODELCHARACTER_H

#include <QObject>
#include <QtCore>
#include <QtWidgets>

#include "modelabstract.h"
#include "Utilities/QLogger/QLogger.h"

class ModelCharacter : public ModelAbstract
{
public:
    ModelCharacter();

    ModelCharacter(const QString &n, const QString &move, const QString &weaponS, const QString &balisticS,
                  const QString &strength, const QString &toughness, const QString &wounds,
                  const QString &init, const QString &attacks, const QString &leadership,
                  const QString &save, const QString &invSave, const int points, const int &widthBase,
                  const int &lengthBase, const int &unitP, const QString& urlImage , bool figSup,
                  const QString& specRules, bool lord, bool general, bool mage, bool mounted, bool gb);
    ModelCharacter(const ModelCharacter &copy);
    virtual ~ModelCharacter();

    static void initModelCharacterSystem();
    virtual ModelCharacter* setFromFile(QString path);
    virtual ModelCharacter* setFromUI(const ParamsfromUImodel* params);
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
    virtual QDataStream & serializeIn(QDataStream& in);

    //! clone
    /*!
    * VIRTUAL : Method that returns a copy of the object. This is used to copy a pointer
    * to a derived class.
    */
    virtual ModelAbstract *clone();

    virtual QString displayStringInfo();
    virtual QString getHtml();

    QString getSpecialRules() const;
    void setSpecialRules(const QString &value);

    bool getIsALord() const;
    void setIsALord(bool value);

    bool getIsTheGeneral() const;
    void setIsTheGeneral(bool value);

    bool getIsAMage() const;
    void setIsAMage(bool value);

    bool getIsMounted() const;
    void setIsMounted(bool value);

    StatsModel getMount() const;
    void setMount(const StatsModel &value);

    virtual int computePoints();

    bool getHasGB() const;
    void setHasGB(bool value);

private:
    static const QString LOG_ID_INFO;
    static const QString LOG_ID_TRACE;
	static const QString LOG_ID_WARN;
	static const QString LOG_ID_ERR;

    QString specialRules;
    bool isALord;
    bool isTheGeneral;
    bool isAMage;
    bool isMounted;
    bool hasGB;

    StatsModel mount;

    friend QDataStream & operator << (QDataStream &, const ModelCharacter &);
    friend QDataStream & operator >> (QDataStream &, ModelCharacter &);

    //ModelAbstract *mount;
};

Q_DECLARE_METATYPE( ModelCharacter)
QDataStream & operator << (QDataStream & out, const  ModelCharacter &);
QDataStream & operator >> (QDataStream & in,  ModelCharacter &);

#endif // MODELCHARACTER_H
