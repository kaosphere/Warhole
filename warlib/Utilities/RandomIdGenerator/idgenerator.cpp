#include "idgenerator.h"

const char IdGenerator::ALPHANUM[] =
        "0123456789"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz";

const int IdGenerator::ID_SIZE = 16;

IdGenerator::IdGenerator()
{
    /* initialize random seed: */
    srand (time(NULL));
}

QString IdGenerator::generateRandomID(int length)
{
    QString s;

    for(int i = 0; i< length; ++i)
    {
        s += ALPHANUM[rand() % (sizeof(ALPHANUM) - 1)];
    }
    return s;
}
