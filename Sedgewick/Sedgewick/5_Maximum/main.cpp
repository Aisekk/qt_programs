#include <iostream>
using namespace std;
//Раздел 5.2, Глава 5. Рекурсия и деревья
//Поиск максимума рекурсивно и нерекурсивно

typedef int Item;
Item max(Item a[], int l, int r)
{
    if(l == r) return a[l];
    int m = (l+r)/2;
    Item u = max(a,l,m);
    Item v = max(a,m+1,r);
    if(u > v) return u; else return v;
}

int main()
{
    //---------------------------------------------------------------------------------------------
    const int N = 10;
    int a[N];
    for(int i = 0; i < N; i++)
        a[i] = rand() % N;
    cout << "Random array for MAXIMUM search: " << endl;
    for(int i = 0; i < N; i++)
        cout << " " << a[i];
    cout << endl;
    //---------------------------------------------------------------------------------------------
    //линейный поиск максимума
    int m = a[0];
    for(int i = 1; i < N ; i++)
        if(a[i] > m) m = a[i];
    cout << "Result of linear search: " << m << endl;
    //---------------------------------------------------------------------------------------------
    //рекурсивный поиск максимума
    const int l = 0, r = 9;
    Item maxR = max(a,l,r);
    cout << "Result of recursive search: " << maxR << endl;
    //---------------------------------------------------------------------------------------------
    system("pause");
    return 0;
}
