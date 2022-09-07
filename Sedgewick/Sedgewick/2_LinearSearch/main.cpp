#include <iostream>
#include <stdlib.h>
#include "LinearSearch.h"
using namespace std;
//Раздел 2.6, Глава 2. Принципы анализа алгоритмов

int main()
{
    //---------------------------------------------------------------------------------------------
    const int N = 10;
    int a[N];
    for(int i = 0; i < N; i++)
        a[i] = rand() % N;
    cout << "Array for linear search: " << endl;
    for(int i = 0; i < N; i++)
        cout << " " << a[i];
    cout << endl;
    //---------------------------------------------------------------------------------------------
    cout << "Enter number to find: ";
    int v{};
    cin >> v;
    int l = 0, r = N-1;
    int index = search(a,v,l,r);
    cout << endl;
    if(index != -1) cout << "Number found: " << a[index] << " (index = " << index << ")";
    else cout << "Number not found ";
    cout << endl;
    //---------------------------------------------------------------------------------------------
    system("pause");
    return 0;
}
