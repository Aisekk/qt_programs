#include <iostream>
using namespace std;
//Раздел 8.3, Глава 8. Слияние и сортировка слиянием
//сортировка слиянием
//основана на абстрактном обменном слиянии
//неадаптивная, устойчивая
//O(N) ~ NlogN гарантированно
//использует дополнительную память ~ N
const int N = 20;
const int maxN = N;
//абстрактное обменное слияние
template <class Item>
void merge(Item a[], int l, int m, int r)
{
    int i, j;
    static Item aux[maxN];
    for(i = m+1; i > l; i--) aux[i-1] = a[i-1];
    for(j = m; j < r; j++) aux[r+m-j] = a[j+1];
    for(int k = l; k <= r; k++)
        if(aux[j] < aux[i])
            a[k] = aux[j--]; else a[k] = aux[i++];
}
//нисходящая сортировка слиянием
template <class Item>
void mergesort(Item a[], int l, int r)
{
    if(r <= l) return;
    int m = (r+l)/2;
    mergesort(a, l, m);
    mergesort(a, m+1, r);
    merge(a, l, m, r);
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
    cout << "Top-down merging sort: " << endl;
    int l = 0, r = N-1;
    mergesort(a, l, r);
    for(i = 0; i < N; i++) cout << a[i] << " ";
    cout << endl;
    //---------------------------------------------------------------------------------------------
    system("pause");
    return 0;
}
