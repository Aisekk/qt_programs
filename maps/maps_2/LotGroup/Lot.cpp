#include "Lot.h"

Lot::Lot(){}

//-------------------------------------------------------------------------------
size_t Lot::getLotNum() const{                                return m_lotNum;}
size_t Lot::getWaferCount() const{                            return m_vecSlotNums.size();}
size_t Lot::getWaferMaxCount() const{                         return int(25);}
size_t Lot::getSlotIndex(const int slotNum) const{            return m_mapSlotIndexNums.value(slotNum);}
QString Lot::getLotName() const{                              return m_lotName;}
shared_ptr<Wafer> Lot::getWafer(const int slotIndex) const{   return m_map_spWafers.value(slotIndex);}
QPersistentModelIndex Lot::getTestModelIndex() const{         return m_persModelIndex;}
QVector<size_t> Lot::getSlotNums() const{                     return m_vecSlotNums;}
//--------------------------------------------------------------------------------
void Lot::setLotName(const QString& lotName)
{
    m_lotName = lotName;
}
void Lot::setLotNum(const size_t lotNum)
{
    m_lotNum = lotNum;
}
void Lot::setModelIndex(const QPersistentModelIndex& modelIndex)
{
    m_persModelIndex = modelIndex;
}

void Lot::addWafer(shared_ptr<Wafer> spWafer,
                   const size_t slotNum, const size_t slotIndex, const size_t testCount)
{
    m_map_spWafers.insert(slotIndex, spWafer);
    m_mapSlotIndexNums.insert(slotNum, slotIndex);
    m_vecSlotNums.push_back(slotNum);
    m_vecTestCountOneWafer.push_back(testCount);
}
//--------------------------------------------------------------------------------
void Lot::deleteWafers()
{
    shared_ptr<Wafer> spWafer;
    auto it = m_map_spWafers.begin();
    while(!m_map_spWafers.isEmpty())
    {
        spWafer = it.value();
        spWafer->deleteTestElems();
        int slotNum = spWafer->getSlotNum();
        spWafer = nullptr;
        auto it_next = m_map_spWafers.erase(it);
        it = it_next;

        qDebug() << "    slotNum " << slotNum << "deleted: " << spWafer.get();
    }

    if(!m_map_spWafers.isEmpty())        m_map_spWafers.clear();
}
