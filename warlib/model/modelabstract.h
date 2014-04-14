/*********************************************************************//**
* modelabstract.h
* ModelAbstract class
*
* AUTEUR: Alexandre Jumeline
* DATE: 03-04-2014
*************************************************************************/

#ifndef MODELABSTRACT_H
#define MODELABSTRACT_H

#include <QObject>
#include <QtCore>
#include <QtWidgets>
#include <iostream>
#include <QTextDocument>

#include "option/optionmodel.h"
#include "stats/statsmodel.h"
#include "paramsfromUI/paramsfromuimodel.h"
#include "defines.h"

//! ModelAbstract class
/*!
* Main data structure storing model characteristics.
* This is the base class for all types of models.
*/
class ModelAbstract
{
public:
	//! Constructor.
	/*!
	Base constructor of ModelAbstract class
	*/
    explicit ModelAbstract();
	
	//! Constructor.
	/*!
	* Constructor of ModelAbstract class
	* \param stat A StatsModel object.
	* \param widthBase width of the model's base.
	* \param lengthBase length of the model's base.
	* \param unitP Unit power of the model
	* \param url Path of the model image
	* \param figSup DEPRECATED. TODO: Remove
	*/
    ModelAbstract(const StatsModel& stat, const int &widthBase,
                  const int &lengthBase, const int &unitP, const QString& url, bool figSup);
	
	//! A constructor.
	/*!
	* Constructor of ModelAbstract class
	* \param stat A StatsModel object.
	* \param widthBase width of the model's base.
	* \param lengthBase length of the model's base.
	* \param unitP Unit power of the model
	* \param url Path of the model image
	* \param figSup DEPRECATED. TODO: Remove
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
    ModelAbstract(const QString &n, const QString &move, const QString &weaponS,
                  const QString &balisticS, const QString &strength, const QString &toughness,
                  const QString &wounds, const QString &init, const QString &attacks,
                  const QString &leadership, const QString &save, const QString &invSave, const int points, const int &widthBase,
                  const int &lengthBase, const int &unitP, const QString& url, bool figSup);
	
	//! Copy Constructor.
	/*!
	* Copy constructor of ModelAbstract class
	*/
    ModelAbstract(const ModelAbstract &Copy);
	
	//! Destructor.
	/*!
	* Base destructor of ModelAbstract class
	*/
    virtual ~ModelAbstract();
	
	//! Save
	/*!
	* VIRTUAL : Method that initiate the saving of the model object in a file.
	* \param path File path of the file to be saved.
	*/
    virtual void save(const QString path);

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
	
	//! setFromFile
	/*!
	* VIRTUAL : Method that loads a model from a previously saved file.
	* \param path File path of the file to be loaded.
	*/
    virtual ModelAbstract* setFromFile(const QString path);
    
    //! setFromUI
	/*!
	* VIRTUAL : Method that loads a model from a form in the UI.
	* \param params parameter object containing every model possible parameters.
	*/
    virtual ModelAbstract* setFromUI(const ParamsfromUImodel* params);
    
    //! Load
	/*!
	* VIRTUAL : Method that initiate the loading of the model object from a file.
	* \param path File path of the file to be loaded.
	*/
    virtual void load(const QString path);
    
    //! displayStringInfo
	/*!
	* VIRTUAL Method that returns a string summerizing the values in the object.
	* \return String containing information.
	*/
    virtual QString displayStringInfo();
    
    //! displayBaseInfo
	/*!
	* Method that returns a string summerizing the values in the base class object.
	* \return String containing information.
	*/
    QString displayBaseInfo();
    
    //! getHtml
	/*!
	* Virtual Method that returns a string summerizing the values in the object
	* using HTML format. Used principally to export data as pdf files.
	* \return String containing information using HTML.
	*/
    virtual QString getHtml();
    
    //! getBaseHtml
	/*!
	* Method that returns a string summerizing the values in the base class object
	* using HTML format. Used principally to export data as pdf files.
	* \return String containing information using HTML.
	*/
    QString getBaseHtml();

    //! clone
    /*!
    * VIRTUAL : Method that returns a copy of the object. This is used to copy a pointer
    * to a derived class.
    */
    virtual ModelAbstract* clone();

    StatsModel getStats() const;
    void setStats(const StatsModel &value);

    int getSquareBaseW() const;
    void setSquareBaseW(int value);

    int getSquareBaseL() const;
    void setSquareBaseL(int value);

    int getUnitPower() const;
    void setUnitPower(int value);

    QPixmap *getImage() const;
    void setImage(QPixmap *value);

    bool getFigSupInd() const;
    void setFigSupInd(bool value);

    QList<OptionModel> getOptions() const;
    void setOptions(const QList<OptionModel> &value);
    
    //! addOption
	/*!
	* Method that adds an option to the list of options
	* \param opt option to be added
	*/
    void addOption(const OptionModel& opt);
    
    //! removeOption
	/*!
	* Method that removes an option to the list of options
	* \param opt option to be removed
	*/
    void removeOption(const OptionModel &opt);
    
    //! clearOptions
	/*!
	* Method that clears all options of the list of options
	*/
    void clearOptions();

    QString getUrlImage() const;
    void setUrlImage(const QString &value);

	//! clearOptions
	/*!
	* Virtual method that computes the global number of points of a model
	* included chosen options.
	*/
    virtual int computePoints();

    int getRegimentPoints();
    int computeBasePoints();

protected:

	//! stats
	/*!
	* StatsModel object of the model
	*/
    StatsModel stats;
    //QList<ModelAbstract *> champion; //list of possible champion

    int squareBaseW;    /// Width of the square base
    int squareBaseL;    /// Length of the square base

    int unitPower;      /// Unit power of the model

    bool figSupInd;     /// Independant models (for charriots, war machines and monsters)

    QPixmap *image;     /// Image of the model to be used in the graphics
    QString urlImage;	/// Path to the image

    QList<OptionModel> options;   /// List of options possible for model
	
	//! QDataStream & operator <<
	/*!
	* Friend QDataStream operator << used to serialize data and save files.
	* \param QDataStream& stream where the data will be inputed.
	* \param ModelAbstract& object to be serialized.
	* \return The stream containing the data.
	*/
    friend QDataStream & operator << (QDataStream &, const ModelAbstract &);
    
    //! QDataStream & operator >>
	/*!
	* Friend QDataStream operator >> used to serialize data and load files.
	* \param QDataStream& stream from where the data will be outputed.
	* \param ModelAbstract& object to be serialized.
	* \return The stream containing the data.
	*/
    friend QDataStream & operator >> (QDataStream &, ModelAbstract &);   
};

#endif // MODELABSTRACT_H
