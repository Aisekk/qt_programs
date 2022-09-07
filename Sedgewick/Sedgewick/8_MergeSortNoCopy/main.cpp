#include <iostream>
#include "funcs.h"
using namespace std;
//Раздел 8.4, Глава 8. Слияние и сортировка слиянием
//сортировка слиянием без копирования (усовершенствованная)
//основана на абстрактном обменном слиянии
//неадаптивная, устойчивая
//O(N) ~ NlogN гарантированно

//стандартное неустойчивое слияние
template <class Item>
void mergeAB(Item c[], Item a[], int N, Item b[], int M)
{
    for(int i = 0, j = 0, k = 0; k < N+M; k++)
    {
        if(i == N) { c[k] = b[j++]; continue; }
        if(j == M) { c[k] = a[i++]; continue; }
        c[k] = (a[i] < b[j]) ? a[i++] : b[j++];
    }
}
//абстрактное обменное слияние
const int N = 20;
const int maxN = N;
template <class Item>
void mergesortABr(Item a[], Item b[], int l, int r)
{
    if(r-l <= 10){ insertion(a, l, r); return; }
    int m = (l+r)/2;
    mergesortABr(b, a, l, m);
    mergesortABr(b, a, m+1, r);
    mergeAB(a+l, b+l, m-l+1, b+m+1, r-m);
}
//нисходящая сортировка слиянием
template <class Item>
void mergesort(Item a[], int l, int r)
{
    static Item aux[maxN];
    for(int i = l; i <= r; i++) aux[i] = a[i];
    mergesortABr(a, aux, l, r);
}
int main()
{
    int i, sw = 1;
    int a[N];
    //random array
    if(sw) for(i = 0; i < N; i++) a[i] = 100*(1.0*rand()/RAND_MAX);
    //else { N = 0; while(cin >> a[N]) N++;}
    cout << "Random array: " << endl;
    for(i = 0; i < N; i++) cout << a[i] << " ";
    cout << endl;
    //merging sort:
    cout << "Merging sort no copy (improved) of array: " << endl;
    int l = 0, r = N-1;
    mergesort(a, l, r);
    for(i = 0; i < N; i++) cout << a[i] << " ";
    cout << endl;
    //---------------------------------------------------------------------------------------------
    system("pause");
    return 0;
}
