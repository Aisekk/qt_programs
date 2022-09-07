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
link reverse(link x)
{
    link t, y = x, r = nullptr;
    while(y != nullptr)
    { t = y->next; y->next = r; r = y; y = t;}
    return r;
}
int main()
{
    //создание упорядоченного списка
    node heada(0, nullptr); link a = &heada, t = a;
    const int N = 10;
    for(int i = 0; i < N; i++)
        t = (t->next = new node(i, nullptr));
    //вывод списка
    cout << "Ordered List: " << endl;
    for(t = a; t != nullptr; t = t->next)
        cout << " " << t->item;
    cout << endl;
    //обращение списка
    cout << "Reversed List: " << endl;
    link b = reverse(a);
    for(t = b; t != nullptr; t = t->next)
        cout << " " << t->item;
    cout << endl;
    //---------------------------------------------------------------------------------------------
    system("pause");
    return 0;
}
