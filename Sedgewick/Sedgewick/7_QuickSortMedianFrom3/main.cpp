#include <iostream>
using namespace std;
//Раздел 7.5, Глава 7. Быстрая сортировка
template <class Item>
void exch(Item& A, Item& B){ Item t = A; A = B; B = t; }
template <class Item>
void compexch(Item& A, Item& B)
{ if(B < A) exch(A,B); }
template <class Item>
void insertion(Item a[], int l, int r)
{
    int i;
    for(i = r; i > l; i--) compexch(a[i-1], a[i]);
    for(i = l+2; i <= r; i++)
    {
        int j = i; Item v = a[i];
        while(v < a[j-1])
        { a[j] = a[j-1]; j--; }
        a[j] = v;
    }
}
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
//быстрая сортировка: метод разделения с вычислением медианы из трех элементов
//адаптивная, неустойчивая
//отсечение небольших подфайлов размером М+1 и меньше
static const int M = 10;
template <class Item>
void quicksort(Item a[], int l, int r)
{
    if(r-l <= M) return;
    exch(a[(l+r)/2], a[r-1]);
    compexch(a[l], a[r-1]);
    compexch(a[l], a[r]);
    compexch(a[r-1], a[r]);
    int i = partition(a,l+1,r-1);
    quicksort(a,l,i-1);
    quicksort(a,i+1,r);
}
template <class Item>
void hybridsort(Item a[], int l, int r)
{ quicksort(a,l,r); insertion(a,l,r); }

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
    cout << "Quick sort median of 3 and clipping subarrays <= M+1 elements (M=10): " << endl;
    hybridsort(a,0,N-1);
    for(i = 0; i < N; i++) cout << a[i] << " ";
    cout << endl;
    //---------------------------------------------------------------------------------------------
    system("pause");
    return 0;
}
