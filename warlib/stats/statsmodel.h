/*********************************************************************//**
* modelabstract.h
* StatsModel class
*
* AUTEUR: Alexandre Jumeline
* DATE: 03-04-2014
*************************************************************************/

#ifndef STATSMODEL_H
#define STATSMODEL_H

#include <QObject>
#include <QtCore>
#include <QtWidgets>
#include <QDataStream>
#include <QTextStream>


//! StatsModel class
/*!
* This class holds all the common attributes of a model.
*/
class StatsModel
{
public:
	//! Constructor.
	/*!
	* Base constructor of StatsModel class
	*/
    StatsModel();
    
    //! Copy Constructor.
	/*!
	* Copy constructor of StatsModel class
	*/
    StatsModel(const StatsModel&);
    
    //! Constructor.
	/*!
	* Constructor of StatsModel class
	* \param n Name of the model
	* \param move Movement speed
	* \param weaponS Weapon skills
	* \param balisticS Balistic skills
	* \param streangth Strength of the model
	* \param toughness Toughness of the model
	* \param wounds Wounds of the model
	* \param init Initiative of the model
	* \param attacks Number of attacks of the model
	* \param leadership Leadership value of the model
	* \param save Armor save of the model
	* \param invSave Invulnerable armor save of the model
	* \param p Points of the model
	*/
    StatsModel(const QString &n, const QString &move, const QString &weaponS, const QString &balisticS,
               const QString &strength, const QString &toughness, const QString &wounds,
               const QString &init, const QString &attacks, const QString &leadership,
               const QString &save, const QString &invSave, int p);
	
	//! Destructor.
	/*!
	* Base destructor of StatsModel class
	*/
    ~StatsModel();
	
	//! operator=
	/*!
	* Overload of operator= for StatsModel class
	* \param s StatsModel whose values will be assigned from.
	*/
    StatsModel& operator=(const StatsModel&);
	
	//! operator==
	/*!
	* Overload of operator== for StatsModel class
	* \param s StatsModel whose values will be compared to.
	*/
    bool operator==(const StatsModel&);
	
	//! displayString
	/*!
	* Method that returns a string summerizing the values in the object.
	* \return String containing information.
	*/
    QString displayString() const;
    
    //! getHtml
	/*!
	* Virtual Method that returns a string summerizing the values in the object
	* using HTML format. Used principally to export data as pdf files.
	* \return String containing information using HTML.
	*/
    QString getHtml() const;
	
	//! getName
	/*!
	* get accessor for name value.
	* \return name Returns the name of the model.
	*/
    QString getName() const;
    void setName(const QString &value);

	//! getM
	/*!
	* get accessor for m value.
	* \return name Returns the movement speed of the model.
	*/
    QString getM() const;
    void setM(const QString &value);
	
	//! getWs
	/*!
	* get accessor for ws value.
	* \return name Returns the movement weapon skills of the model.
	*/
    QString getWs() const;
    void setWs(const QString &value);

	//! getBs
	/*!
	* get accessor for bs value.
	* \return name Returns the movement balistic skills of the model.
	*/
    QString getBs() const;
    void setBs(const QString &value);

	//! getS
	/*!
	* get accessor for ws value.
	* \return name Returns the movement strength of the model.
	*/
    QString getS() const;
    void setS(const QString &value);
	
	//! getT
	/*!
	* get accessor for ws value.
	* \return name Returns the toughness of the model.
	*/
    QString getT() const;
    void setT(const QString &value);
	
	//! getW
	/*!
	* get accessor for ws value.
	* \return name Returns the wounds of the model.
	*/
    QString getW() const;
    void setW(const QString &value);
	
	//! getI
	/*!
	* get accessor for ws value.
	* \return name Returns the initiative of the model.
	*/
    QString getI() const;
    void setI(const QString &value);
	
	//! getA
	/*!
	* get accessor for ws value.
	* \return name Returns the number of attacks of the model.
	*/
    QString getA() const;
    void setA(const QString &value);

	//! getLd
	/*!
	* get accessor for ws value.
	* \return name Returns the leadership of the model.
	*/
    QString getLd() const;
    void setLd(const QString &value);
	
	//! getSvg
	/*!
	* get accessor for ws value.
	* \return name Returns the armor save of the model.
	*/
    QString getSvg() const;
    void setSvg(const QString &value);
	
	//! getSvgInv
	/*!
	* get accessor for ws value.
	* \return name Returns the invulnerable armor save of the model.
	*/
    QString getSvgInv() const;
    void setSvgInv(const QString &value);
	
	//! getPoints
	/*!
	* get accessor for ws value.
	* \return name Returns the points of the model.
	*/
    int getPoints() const;
    void setPoints(int value);

protected:

    QString name;	/// Name of the model
    QString m;      /// Movement of the model
    QString ws;     /// Weapon skill of the model
    QString bs;     /// Balistic skill of the model
    QString s;      /// Strength of the model
    QString t;      /// Toughtness of the model
    QString w;      /// Wounds of the model
    QString i;      /// Initiative of the model
    QString a;      /// Attacks of the model
    QString ld;     /// Leadership of the model
    QString svg;    /// Armor save of the model
    QString svgInv; /// Invulnerable armor save of the model

    int points;     /// Points of the model

	//! QDataStream & operator <<
	/*!
	* Friend QDataStream operator << used to serialize data and save files.
	* \param QDataStream& stream where the data will be inputed.
	* \param StatsModel& object to be serialized.
	* \return The stream containing the data.
	*/
    friend QDataStream & operator << (QDataStream &, const StatsModel &);
    
    //! QDataStream & operator >>
	/*!
	* Friend QDataStream operator >> used to serialize data and load files.
	* \param QDataStream& stream from where the data will be outputed.
	* \param StatsModel& object to be serialized.
	* \return The stream containing the data.
	*/
    friend QDataStream & operator >> (QDataStream &, StatsModel &);

};

#endif // STATSMODEL_H
