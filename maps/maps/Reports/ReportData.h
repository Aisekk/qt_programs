#ifndef REPORTDATA_H
#define REPORTDATA_H

#include "Types.h"
#include "MapImage.h"
#include "LotGroup/Lot.h"

#include <memory>
using namespace std;

class ReportData
{
public:
    ReportData();

    ReportFormat getReportFormat() const;
    NormsID getNormsID() const;
    MapType getMapType() const;
    MapImage* getMapImage() const;
    shared_ptr<Lot> getLot() const;

    void setReportFormat(ReportFormat repFormat);
    void setNormsID(NormsID id);
    void setMapType(MapType mapType);
    void setMapImage(MapImage* mapImage);
    void setLot(shared_ptr<Lot> spLot);

private:
    int m_slotNum{};
    ReportFormat m_reportFormat{};
    NormsID m_normsID{};
    MapType m_mapType{};
    MapImage *m_pMapImage{};
    shared_ptr<Lot> m_spLot;
};

#endif // REPORTDATA_H
