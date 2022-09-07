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
NormsID TestElem::getNormsID() const{                           return m_NormsID; }
double TestElem::getCriterionDn() const{                        return m_criterionDn;}
double TestElem::getCriterionUp() const{                        return m_criterionUp;}
ValuePrefix TestElem::getTestValuesPrefix() const{              return m_testValuePrefix;}
QString TestElem::getTestName() const
{
    //QString& ref = m_testName; return ref;
    return m_testName;
}
QString TestElem::getParamName() const
{
    //QString& ref = m_paramName; return ref;
    return m_paramName;
}
QString TestElem::getAlgName() const
{
    //QString& ref = m_algName; return ref;
    return m_algName;
}
QString TestElem::getUnitName() const
{
    //QString& ref = m_unitName; return ref;
    return m_unitName;
}
QVector<shared_ptr<Die>>& TestElem::getDies()
{
    QVector<shared_ptr<Die>>& ref = m_vec_spDies;
    return ref;
}
//---------------------------------------------------------------------------------
void TestElem::setSlotIndex(const size_t slotIndex)
{
    m_slotIndex = slotIndex;
}
void TestElem::setNormsID(const NormsID id)
{
    m_NormsID = id;
}
void TestElem::setCriterionDn(const double& dn)
{
    m_criterionDn = dn;
}
void TestElem::setCriterionUp(const double& up)
{
    m_criterionUp = up;
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
void TestElem::addDie(shared_ptr<Die>& spDie)
{
    m_vec_spDies.push_back(spDie);
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
}
