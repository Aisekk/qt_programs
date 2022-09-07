#include <iostream>
#include <stdlib.h>
using namespace std;
//Раздел 6.3, Глава 6. Элементарные методы сортировки
template <class Item>
void exch(Item& A, Item& B){ Item t = A; A = B; B = t; }
template <class Item>
void compexch(Item& A, Item& B){ if(B < A) exch(A,B); }
//cортировка вставками усовершенствованная (примерно в 2 раза быстрее простой версии)
//адаптивная, устойчивая
//время выполнения зависит главным образом от исходного порядка лючей
//1. помещает наименьший элемент массива в первую позицию (м.б. использован как сигнальный ключ)
//2. во внутреннем цикле лишь одна операция присваивания
//3. прекращается выполнение внутреннего цикла, когда вставляемый элемент находится в требуемой позиции
template <class Item>
void insertion(Item a[], int l, int r)
{
    int i;
    for(i = r; i > l; i--) compexch(a[i-1], a[i]);
    for(i = l+2; i <= r; i++)
    {
        int j = i; Item v = a[i];
        while(v < a[j-1])
        { a[j] = a[j-1]; j--; }
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
    cout << "After improved insertion sort: ";
    insertion(a,0,N-1);
    for(i = 0; i < N; i++) cout << a[i] << " ";
    cout << endl;
    //---------------------------------------------------------------------------------------------
    system("pause");
    return 0;
}
