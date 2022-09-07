#ifndef TESTELEMDATA_H
#define TESTELEMDATA_H

#include "LotGroup/Lot.h"
#include "Masking/MaskData.h"
#include "Reports/TestElemStatistics.h"
#include "MapImage.h"

#include <memory>
using namespace std;

class TestElemData
{
public:
    TestElemData();

    size_t getSlotIndex() const;
    size_t getTestIndex() const;
    double getCriterionDn() const;
    double getCriterionUp() const;
    MapType getMapType() const;
    NormsID getNormsID() const;
    MapImage* getMapImage() const;
    shared_ptr<Lot> getLot() const;
    unique_ptr<TestElemStatistics> getTestElemStatistics();
    unique_ptr<MaskData> getTestElemMaskData();

    void setSlotIndex(size_t slotIndex);
    void setTestIndex(size_t testIndex);
    void setCriterionDn(double dn);
    void setCriterionUp(double up);
    void setNormsID(NormsID id);
    void setMapType(MapType mapType);
    void setMapImage(MapImage* pMapImage);
    void setLot(shared_ptr<Lot> spLot);
    void moveStatistics(unique_ptr<TestElemStatistics> upTestElemStats);
    void moveMaskData(unique_ptr<MaskData> upMaskData);

private:
    size_t m_slotIndex{};
    size_t m_testIndex{};
    double m_criterionDn{};
    double m_criterionUp{};
    MapType m_mapType;
    NormsID m_NormsID;

    MapImage *m_pMapImage{};
    shared_ptr<Lot> m_spLot;
    unique_ptr<TestElemStatistics> m_upTestElemStats;
    unique_ptr<MaskData> m_upMaskData;
};

#endif // TESTELEMDATA_H
