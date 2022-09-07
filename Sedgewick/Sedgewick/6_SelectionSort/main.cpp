#include <iostream>
#include <stdlib.h>
using namespace std;
//Раздел 6.2, Глава 6. Элементарные методы сортировки
template <class Item>
void exch(Item& A, Item& B)
{ Item t = A; A = B; B = t; }

//cортировка выбором
//неадаптивная, устойчивая
//наименьшее число перемещений данных по сравнению с другими сортировками
template <class Item>
void selection(Item a[], int l, int r)
{
    for(int i = l; i < r; i++)
    {
        int min = i;
        for(int j = i+1; j <= r; j++)
            if(a[j] < a[min]) min = j;
        exch(a[i], a[min]);
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
    cout << "After selection sort: ";
    selection(a,0,N-1);
    for(i = 0; i < N; i++) cout << a[i] << " ";
    cout << endl;
    //---------------------------------------------------------------------------------------------
    system("pause");
    return 0;
}
