#include <iostream>
#include "pq.h"
using namespace std;
//Раздел 9.1, Глава 9. Очереди с приоритетами и пирамидальная сортировка
//Очередь с приоритетом с базовыми операциями
//реализация очереди с использованием массивов
//хранит элементы в неупорядоченном массиве

int main()
{
    int i, size = 100, N = 10;
    PQ<int> pq(size);
    //вставка рандомных элементов
    for(i = 0; i < N; i++) pq.insert(10*(1.0*rand()/RAND_MAX));
    cout << "Random priority queue: " << endl;
    for(i = 0; i < N; i++) cout << " " << pq.getItem(i);
    cout << endl;
    cout << "After remove max elements: " << endl;
    for(i = 0; i < N; i++) cout << " " << pq.getMax();
    cout << endl;
    //проверка наличия элементов
    cout << "Is PQ empty (= 1)?: " << pq.empty() << endl;
    //---------------------------------------------------------------------------------------------
    system("pause");
    return 0;
}
