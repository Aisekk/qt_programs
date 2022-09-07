#include "Wafer.h"

Wafer::Wafer(size_t slotIndex, size_t slotNum) : m_slotIndex(slotIndex), m_slotNum(slotNum){}
//-------------------------------------------------------------------------------------------
size_t Wafer::getSlotIndex() const{                         return m_slotIndex;}
size_t Wafer::getSlotNum() const{                           return m_slotNum;}
size_t Wafer::getTestElemCount() const{                     return m_map_spTestElems.size();}
shared_ptr<TestElem> Wafer::getTestElem(size_t testIndex)
{
    return m_map_spTestElems.value(testIndex);
}
//-------------------------------------------------------------------------------------------
void Wafer::addTestElem(shared_ptr<TestElem> spTestElem, size_t testIndex)
{
    m_map_spTestElems.insert(testIndex, spTestElem);
}
//--------------------------------------------------------------------------------------------
