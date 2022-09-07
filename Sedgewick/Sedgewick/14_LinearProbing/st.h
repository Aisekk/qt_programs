#ifndef ST_H
#define ST_H
#include "item.h"
#include "hashf.cpp"
//Метод хеширования с открытой адресацией
//ключи - неотрицательные целые числа: 0 =< key <= M0-1
//M0 - зарезервированное (максимальное) значение ключа
//N - количество элементов в таблице, N <= M0; M - размер таблицы; M > N
//a = N/M < 1 - коэффициент загрузки хеш-таблицы (доля занятых позиций таблицы): N = a*M
//Cредняя длина кластеров: N/2N = 1/2; сумма длин кластеров равна N
//insert: O(N,M) как при поиске;
//search: O(N,M) = 1 + N/2M + t(t+1)/2M (t - длина кластера) -
//среднее количество зондирований пропорционально сумме квадратов длин кластеров;
/*аналитический результат (лемма 14.3):
 * O(a) = 1/2(1 + 1/(1-a)) - для попаданий,
 * O(a) = 1/2(1 + 1/(1-a)^2) - для промахов*/
//remove: O()
//дублированные ключи необязательно размещаются в соседних позициях
template<class Key, class Item>
class ST
{
private:
    Item *st; int N, M; Item nullitem; int (*hashF)(int,int);
public:
    ST(int maxN, int (*hashf)(int,int))
    {
        N = 0; M = 2*maxN; /* a=1/2 */ st = new Item[M];
        for(int i = 0; i < M; i++) st[i] = nullitem;
        hashF = hashf;
    }
    int count() const{ return N; }
    Item search(Key v)
    {
        int i = hashF(v, M);
        while(!st[i].null())
            if(v == st[i].key()) return st[i]; else i = (i+1) % M;
        return nullitem;
    }

    void insert(Item x)
    { int i = hashF(x.key(), M); while(!st[i].null()) i = (i+1) % M; st[i] = x; N++; }
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
    }

    void show(ostream& os = cout)
    {
        os << "Key\tHash\tValue" << endl;
        for(int i = 0; i < M; ++i)
        {
            Key key = st[i].key();
            os << key << "\t" << hashF(key, M) << "\t"; st[i].showValue();
            os << endl;
        }
    }
};

#endif // ST_H
