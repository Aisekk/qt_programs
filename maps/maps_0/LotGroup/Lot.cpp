#include "Lot.h"

Lot::Lot(){}

//-------------------------------------------------------------------------------
size_t Lot::getLotNum() const{ return m_lotNum;}
size_t Lot::getWaferCount() const{ return m_vecSlotNums.size();}
size_t Lot::getWaferMaxCount() const{ return size_t(25);}
size_t Lot::getSlotIndex(int slotNum) const{ return m_mapSlotIndexNums.value(slotNum);}
QString Lot::getLotName() const{ return m_lotName;}
shared_ptr<Wafer> Lot::getWafer(int slotIndex) const{ return m_map_spWafers.value(slotIndex);}
QPersistentModelIndex Lot::getTestModelIndex() const{ return m_persModelIndex;}
QVector<size_t> Lot::getSlotNums() const{ return m_vecSlotNums;}
//--------------------------------------------------------------------------------
void Lot::setLotName(const QString& lotName)
{
    m_lotName = lotName;
}
void Lot::setLotNum(size_t lotNum)
{
    m_lotNum = lotNum;
}
void Lot::setModelIndex(const QPersistentModelIndex& modelIndex)
{
    m_persModelIndex = modelIndex;
}

void Lot::addWafer(shared_ptr<Wafer> spWafer, size_t slotNum, size_t slotIndex)
{
    m_map_spWafers.insert(slotIndex, spWafer);
    m_mapSlotIndexNums.insert(slotNum, slotIndex);
    m_vecSlotNums.push_back(slotNum);
}
//--------------------------------------------------------------------------------
