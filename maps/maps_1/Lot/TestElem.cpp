#include "TestElem.h"

TestElem::TestElem(){}

TestElem::TestElem(const size_t testIndex, const QString& testName, const QString& paramName,
                   const QString& algName, ValuePrefix testValuesPrefix) :
    m_testIndex(testIndex), m_testName(testName), m_paramName(paramName),
    m_algName(algName), m_testValuePrefix(testValuesPrefix)
{}
//---------------------------------------------------------------------------------
size_t TestElem::getSlotIndex() const{                          return m_slotIndex;}
size_t TestElem::getTestIndex() const{                          return m_testIndex;}
size_t TestElem::getDieCount() const{                           return m_vec_spDies.size();}
double TestElem::getCriterionDn() const{                        return m_criteriumDn;}
double TestElem::getCriterionUp() const{                        return m_criteriumUp;}
QString TestElem::getTestName() const{                          return m_testName;}
QString TestElem::getParamName() const{                         return m_paramName;}
QString TestElem::getAlgName() const{                           return m_algName;}
QString TestElem::getUnitName() const{                          return m_unitName;}
ValuePrefix TestElem::getTestValuesPrefix() const{              return m_testValuePrefix;}
QVector<shared_ptr<Die>>& TestElem::getDies()
{
    QVector<shared_ptr<Die>>& ref = m_vec_spDies;
    return ref;
    //return m_vec_spDies;
}
//---------------------------------------------------------------------------------
void TestElem::setSlotIndex(const size_t slotIndex)
{
    m_slotIndex = slotIndex;
}
void TestElem::setCriterionDn(const double dn)
{
    m_criteriumDn = dn;
}
void TestElem::setCriterionUp(const double up)
{
    m_criteriumUp = up;
}
void TestElem::setTestName(const QString &testName)
{
    m_testName = testName;
}
void TestElem::setTestValuesPrefix(const ValuePrefix valuePrefix)
{
    m_testValuePrefix = valuePrefix;
}
void TestElem::setUnitName(const QString& unitName)
{
    m_unitName = unitName;
}
//----------------------------------------------------------------------------------
void TestElem::addDie(shared_ptr<Die> spDie)
{
    m_vec_spDies.push_back(spDie);
    //m_map_spDies.insert(dieNum, spDie);
}
void TestElem::deleteDies()
{
    shared_ptr<Die> spDie;
    size_t dieNum = 0;
    while(!m_vec_spDies.isEmpty())
    {
        spDie = m_vec_spDies.back();
        int X = spDie->getX();
        int Y = spDie->getY();
        spDie = nullptr;
        m_vec_spDies.pop_back();
        dieNum++;

        qDebug() << "          die " << dieNum
                 << " (" << X << "," << Y << ")" << "deleted: " << spDie.get();
    }

    if(!m_vec_spDies.isEmpty())  m_vec_spDies.clear();
    //if(!m_map_spDies.isEmpty())  m_map_spDies.clear();
}
