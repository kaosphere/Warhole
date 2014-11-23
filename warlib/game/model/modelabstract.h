/*! ********************************************************************
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

#include "game/option/optionmodel.h"
#include "game/stats/statsmodel.h"
#include "game/paramsfromUI/paramsfromuimodel.h"
#include "defines.h"

//! ModelAbstract class
/*!
* Main data structure storing model characteristics.
* This is the base class for all types of models.
*/
class ModelAbstract : public QObject
{
public:
	//! Constructor.
	/*!
	Base constructor of ModelAbstract class
	*/
    explicit ModelAbstract(QObject* parent = 0);
	
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
                  const int &lengthBase, const int &unitP, const QString& url, bool figSup, QObject* parent = 0);
	
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
                  const int &lengthBase, const int &unitP, const QString& url, bool figSup, QObject* parent = 0);
	
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
    virtual void save(const QString path) = 0;

    //! SerializeOut
    /*!
     * VIRTUAL : Method to serialize unknown modelabstract pointer.
     */
    virtual QDataStream &serializeOut(QDataStream &out) = 0;

    //! SerializeIn
    /*!
     * VIRTUAL : Method to serialize unknown modelabstract pointer.
     * \param in QDataStream from which the data is read to feed the object.
     */
    virtual QDataStream &serializeIn(QDataStream& in) = 0;
	
	//! setFromFile
	/*!
	* VIRTUAL : Method that loads a model from a previously saved file.
	* \param path File path of the file to be loaded.
	*/
    virtual ModelAbstract* setFromFile(const QString path) = 0;
    
    //! setFromUI
	/*!
	* VIRTUAL : Method that loads a model from a form in the UI.
	* \param params parameter object containing every model possible parameters.
	*/
    virtual ModelAbstract* setFromUI(const ParamsfromUImodel* params) = 0;
    
    //! Load
	/*!
	* VIRTUAL : Method that initiate the loading of the model object from a file.
	* \param path File path of the file to be loaded.
	*/
    virtual void load(const QString path) = 0;
    
    //! displayStringInfo
	/*!
	* VIRTUAL Method that returns a string summerizing the values in the object.
	* \return String containing information.
	*/
    virtual QString displayStringInfo() = 0;
    
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
    virtual QString getHtml() = 0;
    
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
    virtual ModelAbstract* clone() = 0;

    //! operator=
    /*!
     * \brief Operator= overload
     * \return
     */
    ModelAbstract& operator=(const ModelAbstract& other);

    //! serializeInBase
    /*!
     * \brief Helper to serialize content of base class ModelAbstract
     * \param in Data stream in which data is serialized
     * \return Data stream serialized
     */
    QDataStream& serializeInBase(QDataStream& in);

    //! serializeOutBase
    /*!
     * \brief Helper to serialize content of base class ModelAbstract
     * \param out Data stream from which data is deserialized
     * \return data stream
     */
    QDataStream& serializeOutBase(QDataStream& out) const;

    // Fucking ugly hack TODO change later
    virtual QString getSpecialRules() const = 0;
    virtual void setSpecialRules(const QString &value) = 0;

    StatsModel getStats() const;
    void setStats(const StatsModel &value);

    int getSquareBaseW() const;
    void setSquareBaseW(int value);

    int getSquareBaseL() const;
    void setSquareBaseL(int value);

    int getUnitPower() const;
    void setUnitPower(int value);

    QPixmap& getImage();
    void setImage(QPixmap value);

    bool getFigSupInd() const;
    void setFigSupInd(bool value);

    QList<OptionModel> getOptions() const;
    void setOptions(const QList<OptionModel> &value);

    bool getBanner() const;
    void setBanner(bool value);

    int getBannerPoints() const;
    void setBannerPoints(int value);

    bool getMusician() const;
    void setMusician(bool value);

    int getMusicianPoints() const;
    void setMusicianPoints(int value);

    bool getChampion() const;
    void setChampion(bool value);

    StatsModel getChampionStats() const;
    void setChampionStats(const StatsModel &value);
    
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

    int computeBasePointsWithoutOptions();
    virtual int computePointsWithoutOptions() = 0;
protected:

	//! stats
	/*!
	* StatsModel object of the model
	*/
    StatsModel stats;
    //QList<ModelAbstract *> champion; //list of possible champion

    /// Width of the square base in millimeters
    int squareBaseW;

    /// Length of the square base in millimeters
    int squareBaseL;

    /// Unit power of the model
    int unitPower;

    // TODO : AJ 2014-05-06 This one isn't used : to be removed.
    /// Independant models (for charriots, war machines and monsters)
    bool figSupInd;

    /// Image of the model to be used in the graphics
    QPixmap image;

    // TODO : AJ 2014-05-06 Change name with path (confusing with internet link)
    /// Path to the image
    QString urlImage;

    /// List of options possible for model
    QList<OptionModel> options;

    /// Note : it is more easy to have the banner, musician and champion informations
    /// in the model class because we don't want to enter them each time we make a regiment
    /// If they are in the model, this is just a box to check at regiment creation.

    /// Does the model have a banner ? True if yes, false if not.
    bool banner;

    /// Points for the banner to be added in the regiment.
    int bannerPoints;

    /// Does the model have a musician ? True if yes, false if not.
    bool musician;

    /// Points for the musician to be added to the regiment.
    int musicianPoints;

    /// Does the model have a champion ? True if yes, false if not.
    bool champion;

    /// Stats of the champion that the model can be assigned to.
    StatsModel championStats;
	
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
