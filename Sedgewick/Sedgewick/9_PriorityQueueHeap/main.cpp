#include <iostream>
#include "pq.h"
using namespace std;
//Раздел 9.3, Глава 9. Очереди с приоритетами и пирамидальная сортировка
//Очередь с приоритетом на базе пирамидально упорядоченного дерева

//нисходящая сортировка с использованием очереди с приоритетом
//O(N) ~ NlgN; Q(N) ~ (lgN + ... + lg2 + lg1) < NlgN
//использует доп. память ~ N: копирует элементы массива в очередь
template <class Item>
void PQsort(Item a[], int l, int r)
{
    int k;
    PQ<Item> pq(r-l+1);
    for(k = l; k <= r; k++) pq.insert(a[k]);//доп. память ~ N
    for(k = r; k >= l; k--) a[k] = pq.getMax();
}
int main()
{
    int i, size = 100, N = 20;
    PQ<int> pq(size);
    pq.insertFirst(0);//вставка служебного значения
    //построение пирамидального дерева из рандомных элементов
    //O(N) ~ N в среднем (для рандомных элементов)
    //O(N) ~ NlgN - в худшем случае (когда каждый вставляемый элемент больше всех элементов в дереве)
    //общая стоимость построения = (lg1 + lg2 + ... + lgN) < NlgN
    for(i = 0; i < N; i++) pq.insert(100*(1.0*rand()/RAND_MAX));
    cout << "Heap-ordered priority queue: " << endl;
    for(i = 0; i < N; i++) cout << " " << pq.getItem(i);
    cout << endl;
    cout << "After remove max elements: " << endl;
    for(i = 0; i < N; i++) cout << " " << pq.getMax();
    cout << endl;
    //проверка наличия элементов
    cout << "Is PQ empty (= 1)?: " << pq.empty() << endl;
    //---------------------------------------------------------------------------------------------
    cout << endl; int a[N];//построение рандомного массива
    for(i = 0; i < N; i++) a[i] = 100*(1.0*rand()/RAND_MAX);
    cout << "Random array: " << endl;
    for(i = 0; i < N; i++) cout << " " << a[i]; cout << endl;
    PQsort(a, 0, N-1);
    cout << "Sorted array with heap-ordered priority queue: " << endl;
    for(i = 0; i < N; i++) cout << " " << a[i]; cout << endl;
    //---------------------------------------------------------------------------------------------
    system("pause");
    return 0;
}
