#include <iostream>
using namespace std;
//Раздел 8.7, Глава 8. Слияние и сортировка слиянием
//слияние связанных списков
//неадаптивное, устойчивое
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
int main()
{
    //создание упорядоченного списка 1
    node heada(0); link a = &heada, t = a;
    const int N = 10;
    for(int i = 0; i < N; i++) t = (t->next = new node(2*i+1));
    //вывод списка
    cout << "Ordered List A: " << endl;
    for(t = a; t != nullptr; t = t->next) cout << " " << t->item;
    cout << endl;
    //создание упорядоченного списка 2
    node headb(0); link b = &headb, t2 = b;
    const int M = 8;
    for(int i = 0; i < M; i++) t2 = (t2->next = new node(2*i+2));
    //вывод списка
    cout << "Ordered List B: " << endl;
    for(t2 = b; t2 != nullptr; t2 = t2->next) cout << " " << t2->item;
    cout << endl;
    //слияние связанных списков
    cout << "Merging of lists A and B: " << endl;
    link c = merge(a, b);
    for(link t = c; t != nullptr; t = t->next)
        cout << " " << t->item;
    cout << endl;
    //---------------------------------------------------------------------------------------------
    system("pause");
    return 0;
}
