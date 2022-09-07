#ifndef ST_H
#define ST_H
#include "item.h"
//интерполяционный поиск: Q(N) ~ lglgN
//эффективен, если ключи распределены равномерно и для больших N
//упорядоченная таблица символов
//ключи - неотрицательные целые числа: 0 =< key <= M-1
//M - зарезервированное (максимальное) значение ключа
//N - количество элементов в таблице, N <= M
//insert, search, remove:
//initialize, select, sort:
template<class Key, class Item>
class ST
{
    Item nullitem, *st;
    int N;
    Item searchR(int l, int r, Key v)
    {
        if(l > r) return nullitem;
        //m = (l+r)/2 = l + (r-l)*0.5 = { 0.5 -> (v-kl)/(kr-kl]) } =
        int m = l + (r-l)*(v-st[l].key())/(st[r].key()-st[l].key());
        if(v == st[m].key()) return st[m];
        if(l == r) return nullitem;
        if(v < st[m].key()) return searchR(l, m-1, v);
        else return searchR(m+1, r, v);
    }
public:
    ST(int maxN){ st = new Item[maxN+1]; N = 0; }
    int count(){ return N; }
    Item search(Key v){ return searchR(0, N-1, v); }
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
