#ifndef PARSERRESMAP_H
#define PARSERRESMAP_H

#include <QFile>
#include <QTextStream>
#include <QString>
#include <QStringList>
#include <QRegExp>
#include <QVector>
#include "Types.h"
using namespace std;

class ParserResMap
{
public:
    ParserResMap();
    void doParsing(QFile &ReadFile);
private:

};




#endif // PARSERRESMAP_H
