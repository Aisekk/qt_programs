#ifndef ST_H
#define ST_H
#include "item.h"
#include "hashf.cpp"
//Динамическая хеш-таблица - линейное опробование с расширением путем удвоения
/* Недостатки:
 * 1) затраты на повторное хеширование;
 * 2) затраты на повторное распределение памяти при расширении и сжатии таблицы */
//ключи - неотрицательные целые числа: 0 =< key <= M0-1
//M0 - зарезервированное (максимальное) значение ключа
//N - количество элементов в таблице, N <= M0; M - размер таблицы; M > N
//a = N/M < 1 - коэффициент загрузки хеш-таблицы (доля занятых позиций таблицы): N = a*M
//Cредняя длина кластеров: N/2N = 1/2; сумма длин кластеров равна N
//insert: O(N,M) как при поиске;
//search: O(N,M) = 1 + N/2M + t(t+1)/2M (t - длина кластера) -
//среднее количество зондирований пропорционально сумме квадратов длин кластеров;
/* аналитический результат (лемма 14.3):
 * O(a) = 1/2(1 + 1/(1-a)) - для попаданий,
 * O(a) = 1/2(1 + 1/(1-a)^2) - для промахов */
//remove: O()
//дублированные ключи необязательно размещаются в соседних позициях
template<class Key, class Item>
class ST
{
private:
    Item *st; int N, M; Item nullitem; int (*hashF)(int,int);
    void expand()
    {
        Item *t = st; init(M+M);
        for(int i = 0; i < M/2; i++) if(!t[i].null()) insert(t[i]);
        delete t;
    }
    void shrink()
    {
        Item *t = st; init(M/2);
        for(int i = 0; i < 2*M; i++) if(!t[i].null()) insert(t[i]);
        delete t;
    }
public:
    ST(int (*hashf)(int,int)){ init(4); hashF = hashf; }
    void init(int maxN)
    {
        N = 0; M = maxN; /* a=1 */ st = new Item[M];
        for(int i = 0; i < M; i++) st[i] = nullitem;
    }
    int count() const{ return N; }
    int size() const{ return M; }
    Item search(Key v)
    {
        int i = hashF(v, M);
        while(!st[i].null())
            if(v == st[i].key()) return st[i]; else i = (i+1) % M;
        return nullitem;
    }

    void insert(Item x)
    {
        int i = hashF(x.key(), M);
        while(!st[i].null()) i = (i+1) % M;
        st[i] = x;
        if(N++ >= M/2) expand();
    }
    void remove(Item x)
    {
        int i = hashF(x.key(), M), j;
        while(!st[i].null())
            if(x.key() == st[i].key()) break; else i = (i+1) % M;
        if(st[i].null()) return;
        st[i] = nullitem; N--;
        //повторное хеширование элементов, расположенных справа от удаленного
        for(j = i+1; !st[j].null(); j = (j+1) % M, N--)
        { Item v = st[j]; st[j] = nullitem; insert(v); }
        //сжатие таблицы в два раза с повторным хешированием
        if(N <= M/8) shrink();
    }

    void show(ostream& os = cout)
    {
        os << "Num\tKey\tHash\tValue" << endl;
        for(int i = 0; i < M; ++i)
        {
            Key key = st[i].key();
            os << i+1 << ")\t" << key << "\t" << hashF(key, M) << "\t"; st[i].showValue();
            os << endl;
        }
    }
};

#endif // ST_H
