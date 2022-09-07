#ifndef ST_H
#define ST_H
#include "item.h"
//линейный поиск: O(N) ~ N
//упорядоченная таблица символов
//ключи - неотрицательные целые числа: 0 =< key <= M-1
//M - зарезервированное (максимальное) значение ключа
//N - количество элементов в таблице, N <= M
//не обрабатывает дублированные ключи
//insert, search, remove:
//initialize, select, sort:
template<class Key, class Item>
class ST
{
    Item nullitem, *st;
    int N;
public:
    ST(int maxN){ st = new Item[maxN+1]; N = 0; }
    int count(){ return N; }
    Item search(Key v)
    {
        int i;
        for(i = 0; i < N; i++) if(!(st[i].key() < v)) break;
        if(v == st[i].key()) return st[i];
        return nullitem;
    }
    Item select(int k){ return st[k]; }

    void insert(Item x)
    {
        int i = N++; Key v = x.key();
        while(i > 0 && v < st[i-1].key())
        { st[i] = st[i-1]; i--; }
        st[i] = x;
    }
    void show(ostream& os = cout)
    { int i = 0; while(i < N) st[i++].show(os); }
};

#endif // ST_H
