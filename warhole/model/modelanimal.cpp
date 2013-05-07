#include "modelanimal.h"

// Default constructor
ModelAnimal::ModelAnimal():
    ModelAbstract()
{
}

// Constructor
ModelAnimal::ModelAnimal(const QString &n, const QString &move, const QString &weaponS,
                              const QString &balisticS, const QString &strength, const QString &toughness,
                              const QString &wounds, const QString &init, const QString &attacks,
                              const QString &leadership, const QString &save, const QString &invSave, const int &widthBase,
                              const int &lengthBase, const int &unitP, const QString &urlImage, bool figSup,
                              const QString &specRules) :
    ModelAbstract(n,move,weaponS,balisticS, strength, toughness, wounds, init, attacks, leadership, save,
                  invSave, widthBase, lengthBase, unitP, urlImage, figSup)
{
    specialRules = specRules;
}

// Copy constructor
ModelAnimal::ModelAnimal(const ModelAnimal &copy) : ModelAbstract(copy)
{
    specialRules = copy.specialRules;
}

//Destructor
ModelAnimal::~ModelAnimal()
{

}



QString ModelAnimal::getSpecialRules() const
{
    return specialRules;
}

void ModelAnimal::setSpecialRules(const QString &value)
{
    specialRules = value;
}

// Init for serialization
void ModelAnimal::initModelAnimalSystem()
{
    qRegisterMetaTypeStreamOperators<ModelAnimal>("ModelAnimal");
    qMetaTypeId<ModelAnimal>();
}

// Overloading of << operator
QDataStream & operator << (QDataStream & out, const ModelAnimal & obj)
{
    //out << obj.streamOut();
    out << obj.stats
        << obj.squareBaseW
        << obj.squareBaseL
        << obj.unitPower
        << obj.figSupInd
        << obj.urlImage
        << obj.specialRules;
    return out;
}

// Overloading of >> operator
QDataStream & operator >> (QDataStream & in, ModelAnimal & obj)
{
    //obj.streamIn(in);
    in >> obj.stats;
    in >> obj.squareBaseW;
    in >> obj.squareBaseL;
    in >> obj.unitPower;
    in >> obj.figSupInd;
    in >> obj.urlImage;
    in >> obj.specialRules;

    return in;
}
