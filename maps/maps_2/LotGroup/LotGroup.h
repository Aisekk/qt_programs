#ifndef LOTGROUP_H
#define LOTGROUP_H

#include <QMap>
#include <QDebug>
#include "Lot.h"

class LotGroup
{
public:
    LotGroup();
    shared_ptr<Lot> getLot(size_t lotNum) const;
    void addLot(shared_ptr<Lot> spLot);
    void deleteLot(size_t lotNum);
    void deleteAllLots();

private:
    QMap<size_t,shared_ptr<Lot>> m_map_spLotGroup;
};

#endif // LOTGROUP_H
