#ifndef WAFER_H
#define WAFER_H

#include "TestElem.h"
#include <QMap>
#include <QDebug>

class Wafer
{
public:
    Wafer(size_t slotIndex, size_t slotNum);

    size_t getSlotIndex() const;
    size_t getSlotNum() const;
    size_t getTestElemCount() const;
    shared_ptr<TestElem> getTestElem(size_t testIndex);

    void addTestElem(shared_ptr<TestElem> spTestElem, size_t testIndex);

private:
    size_t m_slotIndex;
    size_t m_slotNum;
    QMap<size_t, shared_ptr<TestElem>> m_map_spTestElems;
};

#endif // WAFER_H
