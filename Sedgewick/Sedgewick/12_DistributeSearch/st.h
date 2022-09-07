#ifndef ST_H
#define ST_H
#include "item.h"
//распределяющий поиск
//Неупорядоченная таблица символов
//ключи - неотрицательные целые числа: 0 =< key <= M-1
//M - зарезервированное (максимальное) значение ключа
//N - количество элементов в таблице, N <= M
//не обрабатывает дублированные ключи
//insert, search, remove: O(1)
//initialize, select, sort: O ~ M
template<class Key, class Item>
class ST
{
    Item nullitem, *st;
    int M;
public:
    ST(){ M = nullitem.key(); st = new Item[M]; }
    int count()
    {
        int N = 0;
        for(int i = 0; i < M; i++) if(!st[i].null()) N++;
        return N;
    }
    Item search(Key v){ return st[v]; }
    Item select(int k)
    {
        for(int i = 0; i < M; i++)
            if(!st[i].null())
                if(k-- == 0) return st[i];
        return nullitem;
    }

    void insert(Item x){ st[x.key()] = x; }
    void remove(Item x){ st[x.key()] = nullitem; }
    void show(ostream& os = cout){ for(int i = 0; i < M; i++) if(!st[i].null()) st[i].show(os); }
};

#endif // ST_H
