#include <iostream>
#include <stdlib.h>
using namespace std;
//Раздел 6.10, Глава 6. Элементарные методы сортировки

const int M = 1000;
const int maxN = 1000;
//метод распределяющего подсчета: O(N) ~ N при условии ...
void distcount(int a[], int l, int r)
{
    int i, j, cnt[M];
    static int b[maxN];
    for(j = 0; j < M; j++) cnt[j] = 0;
    for(j = l; j <= r; i++) cnt[a[i]+l]++;
    for(j = l; j < M; j++) cnt[j] += cnt[j-l];
    for(i = l; i <= r; i++) b[cnt[a[i]]++] = a[i];
    for(i = l; i <= r; i++) a[i] = b[i-l];
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
    cout << "After distcount sort: ";
    distcount(a,0,N-1);
    for(i = 0; i < N; i++) cout << a[i] << " ";
    cout << endl;
    //---------------------------------------------------------------------------------------------
    system("pause");
    return 0;
}
