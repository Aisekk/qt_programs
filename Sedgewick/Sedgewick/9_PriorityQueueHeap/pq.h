#ifndef PQ_H
#define PQ_H

template <class Item>
void exch(Item& A, Item& B){ Item t = A; A = B; B = t; }
//восходящая установка пирамидальной упорядоченности
template <class Item>
void fixUp(Item a[], int k)
{
    while(k > 1 && a[k/2] < a[k])
    { exch(a[k], a[k/2]); k = k/2; }//родитель узла в k находится в позиции k/2
}
//нисходящая установка пирамидальной упорядоченности
template <class Item>
void fixDown(Item a[], int k, int N)
{
    while(2*k <= N)// - потомок не может быть больше размера массива
    {//потомки k - в позициях 2k и 2k+1
        int j = 2*k;
        if(j < N && a[j] < a[j+1]) j++;//достигает нижнего уровня дерева, если не происходит break
        if(!(a[k] < a[j])) break;//выход, когда остановка внутри дерева
        exch(a[k], a[j]); k = j;
    }
}
//пирамидально упорядоченное дерево
template <class Item>
class PQ
{
private:
    Item *pq;
    int N;
    Item nullitem{};
public:
    PQ(int maxN)
    { pq = new Item[maxN+1]; N = 0; }
    int empty() const{ return N == 0; }
    void insertFirst(Item item){ pq[0] = item; }//резерв для служебной метки
    //lgN сравнений, O(N) ~ lgN, т.к. любой путь между корнем и нижнем уровнем содержит <= lgN узлов
    void insert(Item item)
    { pq[++N] = item; fixUp(pq, N);/*восстановление с самого низа дерева*/ }
    //2lgN сравнений, O(N) ~ lgN, т.к. любой путь между корнем и нижнем уровнем содержит <= lgN узлов
    Item getMax()
    {
        //перед извлечением max место max занимает последний элемент
        exch(pq[1], pq[N]);
        //перемещение последнего элемента вниз, начиная с корня до предпоследнего элемента вкл.
        fixDown(pq, 1, N-1);
        //извлечение последнего (max) элемента
        return pq[N--];
    }
    Item getItem(int index)
    {
        if(index >=0 && index < N)
            return pq[index];
        return nullitem;
    }
};

#endif // PQ_H
