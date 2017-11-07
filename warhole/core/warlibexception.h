#ifndef WARLIBEXCEPTION_H
#define WARLIBEXCEPTION_H

#include <exception>
#include <QString>
#include <QtCore>

#define EXCEPTION_LOW 0
#define EXCEPTION_CRITICAL 1
#define EXCEPTION_FATAL 2

using namespace std;

class WarlibException : public exception
{
public:
    WarlibException(int numero=0, QString const& phrase="", int niveau=0) throw()
             :m_num(numero),m_phrase(phrase),m_level(niveau)
    {}

    virtual const char* what() const throw()
    {
        return m_phrase.toStdString().c_str();
    }
    int getNiveau() const throw()
    {
         return m_level;
    }

    virtual ~WarlibException() throw()
    {}

private:
        int m_num;               //Numéro de l'erreur
        QString m_phrase;            //Description de l'erreur
        int m_level;               //Niveau de l'erreur
};

#endif // WARLIBEXCEPTION_H
