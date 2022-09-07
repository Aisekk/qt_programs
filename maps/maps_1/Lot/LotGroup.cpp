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
//    int lotCountRemoved =
//    qDebug() << "Lot count removed: " << lotCountRemoved
//             << "LotNum " << lotNum << " deleted.";
    m_map_spLotGroup.remove(lotNum);
}
void LotGroup::deleteAllLots()
{
    shared_ptr<Lot> spLot;
    auto it = m_map_spLotGroup.begin();
    while(!m_map_spLotGroup.isEmpty())
    {
        spLot = it.value();
        spLot->deleteWafers();
        size_t lotNum = spLot->getLotNum();
        spLot = nullptr;

        auto it_next = m_map_spLotGroup.erase(it);
        it = it_next;

        qDebug() << "  lotNum " << lotNum << " deleted: " << spLot.get();
    }

    if(!m_map_spLotGroup.isEmpty())  m_map_spLotGroup.clear();
}
