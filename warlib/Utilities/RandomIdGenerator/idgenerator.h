#ifndef IDGENERATOR_H
#define IDGENERATOR_H

#include <QtCore>
#include <cstdlib>
#include <time.h>

class IdGenerator
{
private:
    static const char ALPHANUM[];

public:

    static const int ID_SIZE;

    IdGenerator();
    static QString generateRandomID(int length);
};

#endif // IDGENERATOR_H
