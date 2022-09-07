#ifndef LOT_H
#define LOT_H

#include <QMap>
#include <QVector>
#include <QString>
#include <QDebug>
#include <QPersistentModelIndex>

#include "Wafer.h"


class Lot
{
public:
    Lot();

    size_t getLotNum() const;
    size_t getWaferCount() const;
    size_t getWaferMaxCount() const;
    size_t getSlotIndex(int slotNum) const;
    QString getLotName() const;
    shared_ptr<Wafer> getWafer(int slotIndex) const;
    QPersistentModelIndex getTestModelIndex() const;
    QVector<size_t> getSlotNums() const;

    void setLotName(const QString &lotName);
    void setLotNum(size_t lotNum);
    void setModelIndex(const QPersistentModelIndex& modelIndex);

    void addWafer(shared_ptr<Wafer> spWafer, size_t slotNum, size_t slotIndex);

private:
    size_t m_lotNum;
    QString m_lotName;
    QPersistentModelIndex m_persModelIndex;

    QVector<size_t> m_vecSlotNums;
    QMap<size_t,shared_ptr<Wafer>> m_map_spWafers;
    QMap<size_t,size_t> m_mapSlotIndexNums;
};

#endif // LOT_H
