#include <iostream>
using namespace std;
//Раздел 8.5, Глава 8. Слияние и сортировка слиянием
//восходящая сортировка слиянием
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
inline int min(int A, int B){ return (A < B) ? A : B; }
//восходящая сортировка слиянием
template <class Item>
void mergesortBU(Item a[], int l, int r)
{
    for(int m = 1; m <= r-l; m = m+m)
        for(int i = l; i <= r-m; i += m+m)
            merge(a, i, i+m-1, min(i+m+m-1, r));
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
    cout << "Bottom-up merging sort: " << endl;
    int l = 0, r = N-1;
    mergesortBU(a, l, r);
    for(i = 0; i < N; i++) cout << a[i] << " ";
    cout << endl;
    //---------------------------------------------------------------------------------------------
    system("pause");
    return 0;
}
