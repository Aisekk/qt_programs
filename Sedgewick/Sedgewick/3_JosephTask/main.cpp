#include <iostream>
#include <stdlib.h>
using namespace std;
//Раздел 3.3, Глава 3. Элементарные структуры данных
//Задача Иосифа Флавия - пример циклического списка

struct node
{
    int item; node *next;
    node(int x, node* t)
    { item = x; next = t;}
};
typedef node* link;
int main()
{
    //---------------------------------------------------------------------------------------------
    int i{}, N{};
    cout << "Enter size of circular list: ";
    cin >> N;
    //cout << endl;
    //---------------------------------------------------------------------------------------------
    cout << "Enter number of node to delete (must be < " << N << "): ";
    int M{};
    cin >> M;
    //---------------------------------------------------------------------------------------------
    link t = new node(1,0); t->next = t;
    link x = t;
    for(i = 2; i <= N; i++)
        x = (x->next = new node(i,t));
    while(x != x->next)
    {
        for(i = 1; i < M; i++) x = x->next;
        x->next = x->next->next;
    }
    cout << "Item of remained node: " << x->item << endl;
    //N=9, M=5: Item of remained node = 8
    //---------------------------------------------------------------------------------------------
    system("pause");
    return 0;
}
