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
ModelAnimal::ModelAnimal(const ModelAnimal &copy)
{
    name = copy.name;
    m = copy.m;
    ws = copy.ws;
    bs = copy.bs;
    s = copy.s;
    t = copy.t;
    w = copy.w;
    i = copy.i;
    a = copy.a;
    ld = copy.ld;
    svg = copy.svg;
    svgInv = copy.svgInv;
    squareBaseW = copy.squareBaseW;
    squareBaseL = copy.squareBaseL;
    unitPower = copy.unitPower;
    specialRules = copy.specialRules;
}

//Destructor
ModelAnimal::~ModelAnimal(){}



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
    out << obj.name
        << obj.m
        << obj.ws
        << obj.bs
        << obj.s
        << obj.t
        << obj.w
        << obj.i
        << obj.a
        << obj.ld
        << obj.svg
        << obj.svgInv
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
    in >> obj.name;
    in >> obj.m;
    in >> obj.ws;
    in >> obj.bs;
    in >> obj.s;
    in >> obj.t;
    in >> obj.w;
    in >> obj.i;
    in >> obj.a;
    in >> obj.ld;
    in >> obj.svg;
    in >> obj.svgInv;
    in >> obj.squareBaseW;
    in >> obj.squareBaseL;
    in >> obj.unitPower;
    in >> obj.figSupInd;
    in >> obj.urlImage;
    in >> obj.specialRules;

    return in;
}
