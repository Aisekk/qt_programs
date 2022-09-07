#ifndef PQ_H
#define PQ_H

template <class Item>
void exch(Item& A, Item& B){ Item t = A; A = B; B = t; }

//реализация очереди с использованием массивов
//хранит элементы в неупорядоченном массиве
template <class Item>
class PQ
{
private:
    Item *pq;
    int N;
    Item nullitem{};
public:
    PQ(int maxN)
    { pq = new Item[maxN]; N = 0; }
    int empty() const{ return N == 0; }
    void insert(Item item){ pq[N++] = item; }
    Item getMax()
    {
        int max = 0;
        for(int j = 1; j < N; j++)
            if(pq[max] < pq[j]) max = j;
        exch(pq[max], pq[N-1]);
        return pq[--N];
    }
    Item getItem(int index)
    {
        if(index >=0 && index < N)
            return pq[index];
        return nullitem;
    }
};

#endif // PQ_H
