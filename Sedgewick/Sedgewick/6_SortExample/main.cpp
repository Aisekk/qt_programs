#include <iostream>
using namespace std;
//Раздел 6.1, Глава 6. Элементарные методы сортировки

template <class Item>
void exch(Item& A, Item& B){ Item t = A; A = B; B = t; }

template <typename Item>
void compexch(Item& A, Item& B){ if(B < A) exch(A,B); }

//сортировка вставками (простая неэффективная версия)
//неадаптивная, устойчивая
template <typename Item>
void sort(Item a[], int l, int r)
{
    for(int i = l+1; i <= r; i++)
        for(int j = i; j > l; j--)
            compexch(a[j-1], a[j]);
}

int main()
{
    int i, N = 10, sw = 1;
    int *a = new int[N];
    if(sw) for(i = 0; i < N; i++) a[i] = 1000*(1.0*rand()/RAND_MAX);
    else { N = 0; while(cin >> a[N]) N++; }
    //random array
    cout << "Random array: ";
    for(i = 0; i < N; i++) cout << a[i] << " ";
    cout << endl;
    //sorted array
    cout << "Sorted array by simple insertion sort: ";
    sort(a,0,N-1);
    for(i = 0; i < N; i++) cout << a[i] << " ";
    cout << endl;
    //---------------------------------------------------------------------------------------------
    system("pause");
    return 0;
}
