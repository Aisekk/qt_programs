#ifndef TESTELEMDATA_H
#define TESTELEMDATA_H

#include "Lot/Lot.h"
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

    void setSlotIndex(const size_t slotIndex);
    void setTestIndex(const size_t testIndex);
    void setCriteriumDn(const double dn);
    void setCriteriumUp(const double up);
    void setNormsID(const NormsID id);
    void setMapType(MapType mapType);
    void setMapImage(MapImage* pMapImage);
    void setLot(shared_ptr<Lot> spLot);
    void moveStatistics(unique_ptr<TestElemStatistics> upTestElemStats);
    void moveMaskData(unique_ptr<MaskData> upMaskData);

private:
    size_t m_slotIndex{};
    size_t m_testIndex{};
    double m_criteriumDn{};
    double m_criteriumUp{};
    MapType m_mapType;
    NormsID m_NormsID;

    MapImage *m_pMapImage{};
    shared_ptr<Lot> m_spLot;
    unique_ptr<TestElemStatistics> m_upTestElemStats;
    unique_ptr<MaskData> m_upMaskData;
};

#endif // TESTELEMDATA_H
