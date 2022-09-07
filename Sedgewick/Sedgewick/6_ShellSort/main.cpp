#include <iostream>
#include <stdlib.h>
using namespace std;
//Раздел 6.5, Глава 6. Элементарные методы сортировки

//cортировка Шелла
//
//
template <class Item>
void shellsort(Item a[], int l, int r)
{
    int h;
    for(h = l; h <= (r-l)/9; h = 3*h+1) ; //O(N^3/2)
    for(; h > 0; h /= 3)
        for(int i = l+h; i <= r; i++)
        {
            int j = i; Item v = a[i];
            while(j >= l+h && v < a[j-h])
            { a[j] = a[j-h]; j -= h; }
            a[j] = v;
        }
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
    cout << "After Shell sort: ";
    shellsort(a,0,N-1);
    for(i = 0; i < N; i++) cout << a[i] << " ";
    cout << endl;
    //---------------------------------------------------------------------------------------------
    system("pause");
    return 0;
}
