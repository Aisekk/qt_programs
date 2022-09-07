#include <iostream>
#include "st.h"
using namespace std;
//Раздел 12.5, Глава 12. Таблицы символов и деревья бинарного поиска
//BST - cтандартное дерево бинарного поиска

int main()
{
    int N = 10;
    ST<Key, Item> BST;
    //построение дерева
    for(int i = 0; i < N; i++)
    { Item v; v.init(2*i+1); BST.insert(v); }
    //---------------------------------------------------------------------------------------------
    cout << "Binary search tree: " << endl;
    cout << "K,V" << endl;
    BST.show();
    cout << BST.count() << " keys" << endl;
    //---------------------------------------------------------------------------------------------
    Key key = 9; Item found = BST.search(key);
    cout << "Binary search item with key = " << key << ": "; found.showValue();
    //---------------------------------------------------------------------------------------------
    Item v; int key2 = 0; v.init(key2); BST.insert(v);
    cout << "After insertion element: key = " << key2 << ", item = "; v.showValue();
    cout << "K,V" << endl;
    BST.show();
    cout << BST.count() << " keys" << endl;
    //--------------------------------------------------------------------------------------------- 
    ST<Key, Item> BST2;
    //построение дерева нерекурсивными вставками
    for(int i = 0; i < N-5; i++){ Item v; v.init(i*i); BST2.insert(v); }
    //вставка дублированных ключей
    for(int i = 1; i < N-7; i++){ Item v; v.init(i*i); BST2.insert(v); }
    cout << "BST created by nonrecursive insertions: " << endl;
    BST2.show();
    cout << BST2.count() << " keys" << endl;
    //---------------------------------------------------------------------------------------------
    system("pause");
    return 0;
}
