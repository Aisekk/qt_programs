#include <iostream>
using namespace std;
//Раздел 3.4, Глава 3. Элементарные структуры данных
//Обращение списка
struct node
{
    int item; node *next;
    node(int x, node* t)
    { item = x; next = t;}
};
typedef node* link;
int main()
{
    //создание рандомизированного списка
    node heada(0, nullptr); link a = &heada, t = a;
    const int N = 10;
    for(int i = 0; i < N; i++)
        t = (t->next = new node(rand() % N, nullptr));
    //вывод рандомизированного списка
    cout << "Random List: " << endl;
    for(t = a; t != nullptr; t = t->next)
        cout << " " << t->item;
    cout << endl;
    //создание отсортированного списка
    node headb(0, nullptr); link u, x, b = &headb;
    for(t = a->next; t != nullptr; t = u)
    {
        u = t->next;
        for(x = b; x->next != nullptr; x = x->next)
            if(x->next->item > t->item) break;
        t->next = x->next; x->next = t;
    }
    //вывод отсортированного списка
    cout << "Sorted List by insertion: " << endl;
    for(t = b; t != nullptr; t = t->next)
        cout << " " << t->item;
    cout << endl;
    //---------------------------------------------------------------------------------------------
    system("pause");
    return 0;
}
