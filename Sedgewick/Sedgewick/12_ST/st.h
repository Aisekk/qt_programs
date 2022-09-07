#ifndef ST_H
#define ST_H
#include "item.h"

template<class Key, class Item>
class ST
{
public:
    ST(int);
    int count();
    Item search(Key);
    void insert(Item);
    void remove(Item);
    Item select(int);
    void show(ostream&);
};

#endif // ST_H
