#include <iostream>
using namespace std;
//Раздел 7.1, Глава 7. Быстрая сортировка
template <class Item>
void exch(Item& A, Item& B){ Item t = A; A = B; B = t; }
//разделение
template <class Item>
int partition(Item a[], int l, int r)
{
    int i = l-1, j = r; Item v = a[r];
    for(;;)
    {
        while(a[++i] < v) ;
        while(v < a[--j]) if(j == l) break;
        if(i >= j) break;
        exch(a[i], a[j]);
    }
    exch(a[i], a[r]);
    return i;
}
//быстрая сортировка
//адаптивная, неустойчивая
//O(N) ~ NlogN в среднем; изменяется от N до N^2
template <class Item>
void quicksort(Item a[], int l, int r)
{
    if(r <= l) return;
    int i = partition(a, l, r);
    quicksort(a, l, i-1);
    quicksort(a, i+1, r);
}
int main()
{
    int i, N = 10, sw = 1;
    int a[N];
    if(sw) for(i = 0; i < N; i++) a[i] = 10*(1.0*rand()/RAND_MAX);
    else { N = 0; while(cin >> a[N]) N++; }
    //random array
    cout << "Random array: ";
    for(i = 0; i < N; i++) cout << a[i] << " ";
    cout << endl;
    //sorted array
    cout << "Quick sort: ";
    quicksort(a, 0, N-1);
    for(i = 0; i < N; i++) cout << a[i] << " ";
    cout << endl;
    //---------------------------------------------------------------------------------------------
    system("pause");
    return 0;
}
