#include "TestElemData.h"

TestElemData::TestElemData(){}
//-------------------------------------------------------------------------------------------
size_t TestElemData::getSlotIndex() const{                          return m_slotIndex;}
size_t TestElemData::getTestIndex() const{                          return m_testIndex;}
double TestElemData::getCriterionDn() const{                        return m_criterionDn;}
double TestElemData::getCriterionUp() const{                        return m_criterionUp;}
MapType TestElemData::getMapType() const{                           return m_mapType;}
NormsID TestElemData::getNormsID() const{                           return m_NormsID;}

MapImage* TestElemData::getMapImage() const{                        return m_pMapImage;}
shared_ptr<Lot> TestElemData::getLot() const{                       return m_spLot;}
unique_ptr<TestElemStatistics> TestElemData::getTestElemStatistics()
{
    return move(m_upTestElemStats);
}
unique_ptr<MaskData> TestElemData::getTestElemMaskData()
{
    return move(m_upMaskData);
}
//-------------------------------------------------------------------------------------------
void TestElemData::setSlotIndex(size_t slotIndex)
{
    m_slotIndex = slotIndex;
}
void TestElemData::setTestIndex(size_t testIndex)
{
    m_testIndex = testIndex;
}
void TestElemData::setCriterionDn(double dn)
{
    m_criterionDn = dn;
}
void TestElemData::setCriterionUp(double up)
{
    m_criterionUp = up;
}
void TestElemData::setNormsID(NormsID id)
{
    m_NormsID = id;
}

void TestElemData::setMapType(MapType mapType)
{
    m_mapType = mapType;
}
void TestElemData::setMapImage(MapImage *pMapImage)
{
    m_pMapImage = pMapImage;
}
void TestElemData::setLot(shared_ptr<Lot> spLot)
{
    m_spLot = spLot;
}
//-------------------------------------------------------------------------------------------
void TestElemData::moveStatistics(unique_ptr<TestElemStatistics> upTestElemStats)
{
    m_upTestElemStats = std::move(upTestElemStats);
}
void TestElemData::moveMaskData(unique_ptr<MaskData> upMaskData)
{
    m_upMaskData = std::move(upMaskData);
}
//-------------------------------------------------------------------------------------------
