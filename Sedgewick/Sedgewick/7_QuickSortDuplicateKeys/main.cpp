#include <iostream>
using namespace std;
//Раздел 7.6, Глава 7. Быстрая сортировка
template <class Item>
void exch(Item& A, Item& B){ Item t = A; A = B; B = t; }
//быстрая сортировка: дублированные ключи
//адаптивная, неустойчивая
template <class Item>
void quicksort(Item a[], int l, int r)
{
    int k; Item v = a[r];
    if(r <= l) return;
    int i = l-1, j = r, p = l-1, q =r;
    for(;;)
    {
        while(a[++i] < v) ;
        while(v < a[--j]) if(j == l) break;
        if(i >= j) break;
        exch(a[i], a[j]);
        if(a[i] == v) { p++; exch(a[p], a[i]); }
        if(a[j] == v) { q--; exch(a[q], a[j]); }
    }
    exch(a[i], a[r]); j = i-1; i = i+1;
    for(k = l; k <= p; k++, j--) exch(a[k], a[j]);
    for(k = r-1; k >= q; k--, i++) exch(a[k], a[i]);
    quicksort(a,l,j);
    quicksort(a,i,r);
}

int main()
{
    int i, N = 20, sw = 1;
    int a[N];
    if(sw) for(i = 0; i < N; i++) a[i] = 10*(1.0*rand()/RAND_MAX);
    else { N = 0; while(cin >> a[N]) N++; }
    //random array
    cout << "Random array: " << endl;
    for(i = 0; i < N; i++) cout << a[i] << " ";
    cout << endl;
    //sorted array
    cout << "Quick sort - duplicate keys: " << endl;
    quicksort(a,0,N-1);
    for(i = 0; i < N; i++) cout << a[i] << " ";
    cout << endl;
    //---------------------------------------------------------------------------------------------
    system("pause");
    return 0;
}
