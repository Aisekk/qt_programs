#ifndef FILEREADER_4082_H
#define FILEREADER_4082_H

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

#include "TestInfo.h"
#include "LotGroup/Lot.h"
using namespace std;

class FileReader4082
{
public:
    FileReader4082();

    void fileReading(QFile &ReadFile);

    shared_ptr<Lot> getLot() const;
    void RegProcess(QRegExp& regInput, QString& strReg) const;

private:
    const size_t m_maxCountTestElem;
    //объект партии пластин
    shared_ptr<Lot> m_spLot;
};

#endif // FILEREADER_4082_H
