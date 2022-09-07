#ifndef WAFER_H
#define WAFER_H

#include "TestElem.h"
#include <QMap>
#include <QDebug>

class Wafer
{
public:
    Wafer(const size_t slotIndex, const size_t slotNum);

    size_t getSlotIndex() const;
    size_t getSlotNum() const;
    size_t getTestElemCount() const;
    shared_ptr<TestElem> getTestElem(const size_t testIndex);
    QMap<size_t, shared_ptr<TestElem>> getTestElems();

    void addTestElem(shared_ptr<TestElem> spTestElem, const size_t testIndex);

    void deleteTestElems();

private:
    size_t m_slotIndex;
    size_t m_slotNum;
    QMap<size_t, shared_ptr<TestElem>> m_map_spTestElems;
};

#endif // WAFER_H
