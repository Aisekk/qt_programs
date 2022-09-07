#include <iostream>
#include "Queue.h"
using namespace std;
//Раздел 8.7, Глава 8. Слияние и сортировка слиянием
//восходящая сортировка слиянием связанного списка
//неадаптивная, устойчивая
//использует дополнительную память - только ссылки в узлах списков
struct node
{
    int item; node *next;
    node(int x)
    { item = x; next = nullptr; }
};
typedef node* link;
link merge(link a, link b)
{
    node dummy(0); link head = &dummy, c = head;
    while((a != nullptr) && (b != nullptr))
        if(a->item < b->item)
        { c->next = a; c = a; a = a->next; }
        else
        { c->next = b; c = b; b = b->next; }
    c->next = (a == nullptr) ? b : a;
    return head->next;
}
link mergesort(link t)
{
    QUEUE<link> Q(0);
    if(t == nullptr || t->next == nullptr) return t;
    for(link u = nullptr; t != nullptr; t = u)
    { u = t->next; t->next = nullptr; Q.put(t); }
    t = Q.get();
    while(!Q.empty())
    { Q.put(t); t = merge(Q.get(), Q.get()); }
    return t;
}
int main()
{
    //создание рандомного списка
    node heada(0); link a = &heada, t = a;
    const int N = 15;
    for(int i = 0; i < N; i++) t = (t->next = new node(100*(1.0*rand()/RAND_MAX)));
    //вывод списка
    cout << "Random list: " << endl;
    for(t = a; t != nullptr; t = t->next) cout << " " << t->item;
    cout << endl;
    //восходящая сортировка слиянием связанного списка
    cout << "Bottom-up merging sort of list: " << endl;
    link b = mergesort(a);
    for(link t = b; t != nullptr; t = t->next)
        cout << " " << t->item;
    cout << endl;
    //---------------------------------------------------------------------------------------------
    system("pause");
    return 0;
}
