#include "ItemsContainer.h"

ItemsContainer::ItemsContainer(QMultiMap<double, QPair<double, double> > &mmap_Square_and_ItemSizes)
    : m_mmap_Square_and_ItemSizes(mmap_Square_and_ItemSizes)
{}

ItemsContainer::iterator ItemsContainer::begin() const
{
    map_iterator it(m_mmap_Square_and_ItemSizes.end() - 1);
    return it;
}
ItemsContainer::iterator ItemsContainer::end() const
{
    map_iterator it(m_mmap_Square_and_ItemSizes.begin() - 1);
    return it;
}

