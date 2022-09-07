#include <iostream>
using namespace std;
//Раздел 7.8, Глава 7. Быстрая сортировка
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
//выборка на основе метода разбиения в быстрой сортировке
//адаптивная, неустойчивая
//O(N) ~ N в среднем
template <class Item>
void selectR(Item a[], int l, int r, int k)
{
    if(r <= l) return;
    int i = partition(a, l, r);
    if(k < i) selectR(a, l, i-1, k);
    if(k > i) selectR(a, i+1, r, k);
}
template <class Item>
void select(Item a[], int l, int r, int k)
{
    while(r > l)
    {
        int i = partition(a, l, r);
        if(k <= i) r = i-1;
        if(k >= i) l = i+1;
    }
}
int main()
{
    int i, N = 15, sw = 1;
    int a[N], b[N];
    if(sw) for(i = 0; i < N; i++) { a[i] = 100*(1.0*rand()/RAND_MAX); b[i] = a[i]; }
    else { N = 0; while(cin >> a[N]) N++; }
    //random array
    cout << "Random array: " << endl;
    for(i = 0; i < N; i++) cout << a[i] << " ";
    cout << endl << endl;
    //sorted array
    int p = N/2;
    //---------------------------------------------------------------------------------------------
    cout << "Partition of array by value of median (recursion): " << endl;
    selectR(a, 0, N-1, p);
    for(i = 0; i < N; i++) cout << a[i] << " ";
    cout << endl;
    cout << "Median of partitioned array: " << a[p] << endl << endl;
    //---------------------------------------------------------------------------------------------
    cout << "Partition of array by value of median (non recursion): " << endl;
    select(b, 0, N-1, p);//O(N) ~ N в среднем
    for(i = 0; i < N; i++) cout << b[i] << " ";
    cout << endl;
    cout << "Median of partitioned array (non recursion): " << b[p] << endl;
    //медиана занимает окончательное место
    //---------------------------------------------------------------------------------------------
    system("pause");
    return 0;
}
