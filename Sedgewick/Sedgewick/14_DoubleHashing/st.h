#ifndef ST_H
#define ST_H
#include "item.h"
#include "hashf.cpp"
//Двойное хеширование
//ключи - неотрицательные целые числа: 0 =< key <= M0-1
//M0 - зарезервированное (максимальное) значение ключа
//N - количество элементов в таблице, N <= M0; M - размер таблицы; M > N
//a = N/M < 1 - коэффициент загрузки хеш-таблицы (доля занятых позиций таблицы): N = a*M
//Cредняя длина кластеров: N/2N = 1/2; сумма длин кластеров равна N
/* Вторая хеш-функция:
 * 1) != 0, иначе бесконечный цикл;
 * 2) значение 2-й хеш-функции и размер таблицы - взаимно простые числа. */
//insert: O(N,M) как при поиске;
//search: O(N,M) = O(a) - лемма 14.4 (асимптотические формулы)
/* аналитический результат (лемма 14.4):
 * O(a) = 1/a*ln(1/(1-a)) - для попаданий,
 * O(a) = 1/(1-a) - для промахов */
//remove: O()
//дублированные ключи необязательно размещаются в соседних позициях
template<class Key, class Item>
class ST
{
private:
    Item *st; int N, M; Item nullitem; int (*hash1)(int,int);
    int hash2(Key v){ return (v % 97) + 1; }
public:
    ST(int maxN, int (*hashf)(int,int))
    {
        N = 0; M = 2*maxN; /* a=1/2 */ st = new Item[M];
        for(int i = 0; i < M; i++) st[i] = nullitem;
        hash1 = hashf;
    }
    int count() const{ return N; }
    Item search(Key v)
    {
        int i = hash1(v, M), k = hash2(v);
        while(!st[i].null())
            if(v == st[i].key()) return st[i]; else i = (i+k) % M;
        return nullitem;
    }

    void insert(Item x)
    {
        Key v = x.key(); int i = hash1(v, M), k = hash2(v);
        while(!st[i].null()) i = (i+k) % M; st[i] = x; N++;
    }
    void show(ostream& os = cout)
    {
        os << "Key\tHash1\tHash2\tValue" << endl;
        for(int i = 0; i < M; ++i)
        {
            Key key = st[i].key();
            os << key << "\t" << hash1(key, M) << "\t" << hash2(key) << "\t";
            st[i].showValue();
            os << endl;
        }
    }
};

#endif // ST_H
