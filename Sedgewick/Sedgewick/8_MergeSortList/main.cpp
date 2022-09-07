#include <iostream>
using namespace std;
//Раздел 8.7, Глава 8. Слияние и сортировка слиянием
//нисходящая сортировка слиянием связанного списка
//неадаптивная, устойчивая
//использует дополнительную память - только ссылки в узлах списков
struct node
{
    int item; node *next;
    node(int x)
    { item = x; next = nullptr;}
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
link mergesort(link c)
{
    if(c == nullptr || c->next == nullptr) return c;
    link a = c, b = c->next;
    while((b != nullptr) && (b->next != nullptr))
    { c = c->next; b = b->next->next; }
    b = c->next; c->next = nullptr;
    return merge(mergesort(a), mergesort(b));
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
    //нисходящая сортировка слиянием связанного списка
    cout << "Top-down merging sort of list: " << endl;
    link b = mergesort(a);
    for(link t = b; t != nullptr; t = t->next)
        cout << " " << t->item;
    cout << endl;
    //---------------------------------------------------------------------------------------------
    system("pause");
    return 0;
}
