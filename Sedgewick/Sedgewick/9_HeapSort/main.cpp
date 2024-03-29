#include <iostream>
using namespace std;
//Раздел 9.4, Глава 9. Очереди с приоритетами и пирамидальная сортировка
template <class Item>
void exch(Item& A, Item& B){ Item t = A; A = B; B = t; }
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
//Пирамидальная сортировка - менее 2NlgN сравнений (2 этапа)
//O(N) ~ NlogN гарантированно, не зависит от входных данных (неадаптивный)
//1. построение пирамидального дерева (из массива) снизу вверх
//2. сортировка массива с сокращением размера дерева на один элемент
//Преимущества: 1 - гарантированное время выполнения ~ NlgN; 2 - отсутствие вспомогательной памяти
//Недостатки: неустойчивость
template <class Item>
void heapsort(Item a[], int l, int r)
{
    int k, N = r-l+1;
    Item *pq = a+l-1;
    //1. построение пирамидального дерева снизу вверх за время ~ N
    for(k = N/2; k >= l; k--) fixDown(pq, k, N);
    //2. сортировка массива за время ~ NlogN с сокращением размера дерева на 1 (--N):
    //помещение последнего элемента в корень, а макс. элемента в конец массива
    //с последующим восстановлением пирамидальной упорядоченности сверху вниз,
    //не затрагивая последний (max) элемент (--N), помещенный в окончательную позицию
    while(N > 1){ exch(pq[1], pq[N]); fixDown(pq, 1, --N); }
}
int main()
{
    int i, N = 10;
    int a[N];//построение рандомного массива
    for(i = 0; i < N; i++) a[i] = 100*(1.0*rand()/RAND_MAX);
    cout << "Random array: " << endl;
    for(i = 0; i < N; i++) cout << " " << a[i]; cout << endl;
    heapsort(a, 0, N-1);
    cout << "Heap-Sorted array: " << endl;
    for(i = 0; i < N; i++) cout << " " << a[i]; cout << endl;
    //---------------------------------------------------------------------------------------------
    system("pause");
    return 0;
}
