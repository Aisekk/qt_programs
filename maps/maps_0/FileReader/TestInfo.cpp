#include "TestInfo.h"

TestInfo::TestInfo(const QString &testName, int testIndex, int slotIndex,
                   ValuePrefix testValuesPrefix):
    m_testIndex(testIndex), m_slotIndex(slotIndex),  m_testName(testName),
    m_testValuesPrefix(testValuesPrefix)
{}
//------------------------------------------------------------------------------------------------
int TestInfo::getTestIndex() const{ return m_testIndex;}
int TestInfo::getSlotIndex() const{ return m_slotIndex;}
ValuePrefix TestInfo::getTestValuesPrefix() const{ return m_testValuesPrefix;}
QString TestInfo::getTestName() const{ return m_testName;}
//------------------------------------------------------------------------------------------------
void TestInfo::setTestName(const QString &testName)
{
    m_testName = testName;
}
void TestInfo::setTestValuesPrefix(const ValuePrefix valuePrefix)
{
    m_testValuesPrefix = valuePrefix;
}
