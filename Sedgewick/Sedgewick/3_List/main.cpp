#include <iostream>
#include "list.h"
using namespace std;
//Разделы 3.4, 3.5, 5.1, Глава 3. Элементарные структуры данных
//Обработка списка

int main()
{
    //решение задачи Иосифа
    cout << "Joseph task solution with List: " << endl;
    //---------------------------------------------------------------------------------------------
    int i{}, N{};
    cout << "Enter size of circular list: ";
    cin >> N;
    //---------------------------------------------------------------------------------------------
    cout << "Enter number of node to delete (must be < " << N << "): ";
    int M{};
    cin >> M;
    //---------------------------------------------------------------------------------------------
    link t, x;
    construct(N);
    for(i = 2, x = newNode(1); i <= N; i++)
    { t = newNode(i); insert(x,t); x = t; }
    //int size = count(first());
    //cout << "Size of created circular list = " << size << endl;
    while(x != next(x))
    {
        for(i = 1; i < M; i++) x = next(x);
        deleteNode(remove(x));
    }
    cout << "Item of remained node: " << item(x) << endl;
    //N=9, M=5: Item of remained node = 8
    //---------------------------------------------------------------------------------------------
    system("pause");
    return 0;
}
