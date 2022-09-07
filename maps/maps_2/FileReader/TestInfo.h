#ifndef TESTINFO_H
#define TESTINFO_H

#include <QString>
#include "Types.h"

class TestInfo
{
public:
    TestInfo(const QString& testName, const int testIndex, const int slotIndex,
             ValuePrefix testValuesPrefix);

    int getTestIndex() const;
    int getSlotIndex() const;
    ValuePrefix getTestValuesPrefix() const;
    QString getTestName() const;

    void setTestName(const QString& testName);
    void setTestValuesPrefix(const ValuePrefix valuePrefix);

private:
    int m_testIndex;
    int m_slotIndex;
    QString m_testName;
    ValuePrefix m_testValuesPrefix;
};

#endif // TESTINFO_H
