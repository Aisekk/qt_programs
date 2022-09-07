#include "ReportData.h"

ReportData::ReportData(){}
//-------------------------------------------------------------------------------------------------
ReportFormat ReportData::getReportFormat() const{                   return m_reportFormat;}
NormsID ReportData::getNormsID() const{                             return m_normsID;}
MapType ReportData::getMapType() const{                             return m_mapType;}
MapImage* ReportData::getMapImage() const{                          return m_pMapImage;}
shared_ptr<Lot> ReportData::getLot() const{                         return m_spLot;}
//-------------------------------------------------------------------------------------------------
void ReportData::setReportFormat(ReportFormat repFormat)
{
    m_reportFormat = repFormat;
}
void ReportData::setNormsID(NormsID id)
{
    m_normsID = id;
}
void ReportData::setMapType(MapType mapType)
{
    m_mapType = mapType;
}
void ReportData::setMapImage(MapImage* pMapImage)
{
    m_pMapImage = pMapImage;
}
void ReportData::setLot(shared_ptr<Lot> spLot)
{
    m_spLot = spLot;
}
//-------------------------------------------------------------------------------------------------
