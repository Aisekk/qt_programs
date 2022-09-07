#include "LotGroup.h"

LotGroup::LotGroup(){}
//------------------------------------------------------------------------------
shared_ptr<Lot> LotGroup::getLot(size_t lotNum) const
{
    return m_map_spLotGroup.value(lotNum);
}
//------------------------------------------------------------------------------
void LotGroup::addLot(shared_ptr<Lot> spLot)
{
    size_t lotNum = spLot->getLotNum();
    m_map_spLotGroup.insert(lotNum, spLot);
}
//------------------------------------------------------------------------------
void LotGroup::deleteLot(size_t lotNum)
{
    m_map_spLotGroup.remove(lotNum);
}
