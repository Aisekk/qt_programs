#include <iostream>
#include <stdlib.h>
using namespace std;
//Раздел 6.4, Глава 6. Элементарные методы сортировки
template <class Item>
void exch(Item& A, Item& B)
{ Item t = A; A = B; B = t; }
template <class Item>
void compexch(Item& A, Item& B)
{ if(B < A) exch(A,B); }
//пузырьковая cортировка
//неадаптивная, устойчивая
//неадаптивная, т.к. используется compexch
template <class Item>
void bubble(Item a[], int l, int r)
{
    for(int i = l; i < r; i++)
        for(int j = r; j > i; j--)
            compexch(a[j-1], a[j]);
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
    cout << "After bubble sort: ";
    bubble(a,0,N-1);
    for(i = 0; i < N; i++) cout << a[i] << " ";
    cout << endl;
    //---------------------------------------------------------------------------------------------
    system("pause");
    return 0;
}
