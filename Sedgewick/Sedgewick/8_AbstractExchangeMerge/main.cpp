#include <iostream>
using namespace std;
//Раздел 8.2, Глава 8. Слияние и сортировка слиянием
//абстрактное обменное слияние
//основано на создании битонического порядка элементов массива
//неадаптивное, устойчивое
//O(N) ~ N
const int maxN = 1000;
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
int main()
{
    int i, j, N = 10, M = 10, sw = 1;
    int a[N+M];
    //Two-part ordered array
    if(sw){ for(i = 0; i < N; i++) a[i] = 2*(i+1); for(j = i; j < N+M; j++) a[j] = 2*(j-N+1)-1; }
    else { N = 0; while(cin >> a[N]) N++;}
    cout << "Two-part ordered array: ";
    for(i = 0; i < N+M; i++) cout << a[i] << " ";
    cout << endl;
    //sorted array after merging:
    cout << "Abstract exchange merging of two-part ordered array: ";
    int l = 0, m = N-1, r = N+M-1;
    merge(a, l, m, r);
    for(i = 0; i < N+M; i++) cout << a[i] << " ";
    cout << endl;
    //---------------------------------------------------------------------------------------------
    system("pause");
    return 0;
}
