#include "Wafer.h"

Wafer::Wafer(const size_t slotIndex, const size_t slotNum) :
    m_slotIndex(slotIndex), m_slotNum(slotNum){}
//-------------------------------------------------------------------------------------------
size_t Wafer::getSlotIndex() const{                         return m_slotIndex;}
size_t Wafer::getSlotNum() const{                           return m_slotNum;}
size_t Wafer::getTestElemCount() const{                     return m_map_spTestElems.size();}
shared_ptr<TestElem> Wafer::getTestElem(const size_t testIndex)
{
    return m_map_spTestElems.value(testIndex);
}
QMap<size_t, shared_ptr<TestElem>> Wafer::getTestElems()
{
    return m_map_spTestElems;
}
//-------------------------------------------------------------------------------------------
void Wafer::addTestElem(shared_ptr<TestElem> spTestElem, const size_t testIndex)
{
    m_map_spTestElems.insert(testIndex, spTestElem);
}
//--------------------------------------------------------------------------------------------
void Wafer::deleteTestElems()
{
    shared_ptr<TestElem> spTestElem;
    auto it = m_map_spTestElems.begin();
    while(!m_map_spTestElems.isEmpty())
    {
        spTestElem = it.value();
        spTestElem->deleteDies();
        QString testName = spTestElem->getTestName();
        spTestElem = nullptr;
        auto it_next = m_map_spTestElems.erase(it);
        it = it_next;

        qDebug() << "      test elem " << testName << "deleted: " << spTestElem.get();
    }

    if(!m_map_spTestElems.isEmpty())     m_map_spTestElems.clear();
}
