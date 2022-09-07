#include <iostream>
#include <stdlib.h>
using namespace std;
//Раздел 6.9, Глава 6. Элементарные методы сортировки

typedef int Item;
struct node
{
    Item item; node *next;
    node(int x, node* t)
    { item = x; next = t;}
};
typedef node* link;
link findmax(link h)
{
    link max = nullptr; Item maxItem = h->item;
    for(link t = h; t != nullptr; t = t->next)
        if(t->item > maxItem) { maxItem = t->item; max = t; }
    return max;
}
//cортировка выбором связного списка
link listselection(link h)
{
    //node dummy(0, nullptr); link head = &dummy,
    link out = nullptr;
    //head->next = h;
    link in = h;
    while(in->next != nullptr)
    {
        link max = findmax(h), t = max->next;
        max->next = t->next;
        t->next = out; out = t;
        in = in->next;
    }
    return out;
}

int main()
{
    //создание упорядоченного списка
    node heada(0, nullptr); link a = &heada, t = a;
    const int N = 10;
    for(int i = 0; i < N; i++) t = (t->next = new node(rand() % N, nullptr));
    //вывод списка
    cout << "Initial list: ";
    for(t = a; t != nullptr; t = t->next) cout << " " << t->item;
    cout << endl;
    //max element
    link max = findmax(a);
    cout << "Max element in list = " << max->item << endl;
    //sorted list
    cout << "After list selection sort: ";
    link b = listselection(a);
    for(t = b; t != nullptr; t = t->next)
        cout << " " << t->item;
    cout << endl;
    //---------------------------------------------------------------------------------------------
    system("pause");
    return 0;
}
