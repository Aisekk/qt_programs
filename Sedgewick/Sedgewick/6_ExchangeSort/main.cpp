#include <iostream>
#include <stdlib.h>
using namespace std;
//Раздел 6.8, Глава 6. Элементарные методы сортировки

typedef int Index;
//обменная cортировка
//массив data[0],..., data[N-1] должен быть упорядочен на месте
//в соответствии с массивом индексов a[0],...,a[N-1]
//любой элемент, для которого a[i]==i, занимает свое окончательное место
template <class Item>
void insitu(Item data[], Index a[], int N)
{
    for(int i = 0; i < N; i++)
    {
        Item v = data[i];
        int j, k;
        for(k = i; a[k] != i; k = a[j], a[j] = j)
        { j = k; data[k] = data[a[k]]; }
        data[k] = v; a[k] = k;
    }
}
int main()
{
    int i, N = 10, sw = 1;
    int data[N];
    Index a[N];
    if(sw) for(i = 0; i < N; i++)
    {
        data[i] = 10*(1.0*rand()/RAND_MAX);
        a[i] = N-i-1;//индексы в обратном порядке
    }
    else { N = 0; while(cin >> data[N]) N++; }
    //random array
    cout << "Random array: ";
    for(i = 0; i < N; i++) cout << data[i] << " ";
    cout << endl;
    //sorted array
    cout << "After insitu sort: ";
    insitu(data,a,N);
    for(i = 0; i < N; i++) cout << data[i] << " ";
    cout << endl;
    //---------------------------------------------------------------------------------------------
    system("pause");
    return 0;
}
