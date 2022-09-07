#ifndef PARSER_4082_H
#define PARSER_4082_H

#include <QFile>
#include <QTextStream>
#include <QString>
#include <QStringList>
#include <QRegExp>
#include <QVector>
#include <QMultiMap>

#include <memory>
#include <vector>
#include <map>

//#include "Lot/Die.h"
//#include "Lot/TestElem.h"
#include "TestInfo.h"
//#include "Lot/Wafer.h"
#include "Lot/Lot.h"
using namespace std;

class Parser4082
{
public:
    Parser4082();

    void doParsing(QFile &ReadFile);

    shared_ptr<Lot> getLot() const;
    void RegProcess(QRegExp& regInput, QString& strReg) const;

private:
    const size_t m_maxCountTestElem;
    //объект партии пластин
    shared_ptr<Lot> m_spLot;
};

#endif // PARSER_4082_H
