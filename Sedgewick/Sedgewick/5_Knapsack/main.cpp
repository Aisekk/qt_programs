#include <iostream>
//#include "FibonacciR.h"
using namespace std;
//Раздел 5.3, Глава 5. Рекурсия и деревья
//Задача о ранце
typedef struct{ int size; int val; } Item;
struct a
{
    int size; int val;
    bool operator == (const a& compareTo)
    { return ( (size = compareTo.size) && (val = compareTo.val) ); }
    bool operator != (const a& compareTo)
    { return ! (this->operator ==(compareTo)); }
};
static const int N = 5;
static Item items[N] = { {3,4}, {4,5}, {7,10}, {8,11}, {9,13} };
int knap(int cap)
{
    int i, space, max, t;
    for(i = 0, max = 0; i < N; i++)
        if( (space = cap - items[i].size) >= 0)
            if( (t = knap(space) + items[i].val) > max)
                max = t;
    return max;
}
//динамическое программирование
static const int M = 1000; //максимальный размер ранца
static int maxKnown[M];
int unknown = 0;
static Item itemsKnown[M];
int knapD(int M)
{
    int i, space, max, maxi = 0, t;
    if(maxKnown[M] != unknown) return maxKnown[M];
    for(i = 0, max = 0; i < N; i++)
        if( (space = M - items[i].size) >= 0)
            if( (t = knapD(space) + items[i].val) > max)
            { max = t; maxi = i; }
    maxKnown[M] = max; itemsKnown[M] = items[maxi];
    return max;
}

int main()
{
    //массив элементов типа Item
    cout << "Items: sizes and values" << endl;
    for(int i = 0; i < N; i++)
        cout << "Item " << i << ": size = " << items[i].size << "; value = " << items[i].val << endl;
    cout << endl;
    //---------------------------------------------------------------------------------------------
    cout << "Enter size of knapsack: ";
    //размер ранца
    int cap{};
    cin >> cap;
    //максимальная суммарная стоимость предметов (рекурсия)
    int maxCost = knap(cap);// O(N) ~ exp(N)
    cout << "Max cost of items in knapsack (size = " << cap
         << ") (recursion): = "<< maxCost << endl;
    //cap = 17: maxCost = 24
    //---------------------------------------------------------------------------------------------
    //нисходящее динамическое программирование
    int maxCostD = knapD(cap);// O(N) ~ N
    cout << "Max cost of items in knapsack (size = " << cap
         << ") (top-down dynamic programming): = "<< maxCostD << endl;
    //---------------------------------------------------------------------------------------------
    system("pause");
    return 0;
}
