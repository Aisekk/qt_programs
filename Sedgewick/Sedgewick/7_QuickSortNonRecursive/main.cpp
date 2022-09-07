#include <iostream>
#include "Stack.h"
using namespace std;
//Раздел 7.3, Глава 7. Быстрая сортировка
template <class Item>
void exch(Item& A, Item& B){ Item t = A; A = B; B = t; }
//разделение
template <class Item>
int partition(Item a[], int l, int r)
{
    int i = l-1, j = r; Item v = a[r];
    for(;;)
    {
        while(a[++i] < v) ;
        while(v < a[--j]) if(j == l) break;
        if(i >= j) break;
        exch(a[i], a[j]);
    }
    exch(a[i], a[r]);
    return i;
}
//вставка в стек двух элементов
inline void push2(Stack<int>& s, int A, int B){ s.push(B); s.push(A); }
//быстрая сортировка нерекурсивная (с помощью стека: занесение в стек индексов массива)
template <class Item>
void quicksort(Item a[], int l, int r)
{
    Stack<int> s(50);
    push2(s,l,r);
    while(!s.empty())
    {
        l = s.pop(); r = s.pop();
        if(r <= l) continue;
        int i = partition(a,l,r);
        if(i-l > r-i)
        { push2(s,l,i-1); push2(s,i+1,r); }
        else
        { push2(s,i+1,r); push2(s,l,i-1); }
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
    cout << "Quick sort non recursive: ";
    quicksort(a,0,N-1);
    for(i = 0; i < N; i++) cout << a[i] << " ";
    cout << endl;
    //---------------------------------------------------------------------------------------------
    system("pause");
    return 0;
}
