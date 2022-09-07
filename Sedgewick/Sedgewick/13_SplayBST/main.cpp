#include <iostream>
#include "st.h"
using namespace std;
//Раздел 13.2. Глава 13. Сбалансированные деревья
//Скошенное BST-дерево

int main()
{
    int N = 10;
    ST<Key, Item> BST;
    //построение BST-дерева вставками сводится к сортировке элементов
    for(int i = 0; i < N/2; i++){ Item v; v.init(N-2*i-1); BST.insert(v); }
    //---------------------------------------------------------------------------------------------
    cout << "Splay binary search tree: " << endl;
    cout << "K,V" << endl;
    BST.show(); cout << BST.count() << " keys" << endl;
    //---------------------------------------------------------------------------------------------
    cout << "Splay binary search tree balanced: " << endl;
    BST.balance(); cout << "K,V" << endl;
    BST.show(); cout << BST.count() << " keys" << endl;
    //---------------------------------------------------------------------------------------------
    Key key = 5; Item found = BST.search(key);
    cout << "Splay binary search item with key = " << key << ": "; found.showValue();
    //---------------------------------------------------------------------------------------------
    int k = 1; Item sel = BST.select(k);
    cout << "Selected " << k << " element: "; sel.showValue();
    //---------------------------------------------------------------------------------------------
    Item v2; int key2 = 6; v2.init(key2); BST.insert(v2);
    cout << "After insertion element: key = " << key2 << ", item = "; v2.showValue();
    //---------------------------------------------------------------------------------------------
    cout << "Splay binary search tree balanced: " << endl;
    BST.balance(); cout << "K,V" << endl;
    BST.show(); cout << BST.count() << " keys" << endl;
    //---------------------------------------------------------------------------------------------
    Item v3; int key3 = 4; v3.init(key3); BST.insert(v3);
    cout << "After insertion element: key = " << key3 << ", item = "; v3.showValue();
    Item v4; int key4 = 8; v4.init(key4); BST.insert(v4);
    cout << "After insertion element: key = " << key4 << ", item = "; v4.showValue();
    BST.show(); cout << BST.count() << " keys" << endl;
    //---------------------------------------------------------------------------------------------
    int k2 = 2; Item sel2 = BST.select(k2);
    cout << "Selected " << k2 << " element: "; sel2.showValue();
    //---------------------------------------------------------------------------------------------
    ST<Key, Item> BST2;
    for(int i = 0; i < 2; i++){ Item v; v.init(2*i); BST2.insert(v); }
    cout << "BST 2: " << endl;
    BST2.show(); cout << BST2.count() << " keys" << endl;
    cout << "Join of BST and BST2 above " << ": " << endl;
    BST.join(BST2); BST.show(); cout << BST.count() << " keys" << endl;
    //---------------------------------------------------------------------------------------------
    Item vr; int keyR = 6; vr.init(keyR); BST.remove(vr);
    cout << "After remove element: key = " << keyR << ", item = "; vr.showValue();
    BST.show(); cout << BST.count() << " keys" << endl;
    //---------------------------------------------------------------------------------------------
    Item v5; int key5 = 1; v5.init(key5); BST.insert(v5);
    cout << "After insertion element: key = " << key5 << ", item = "; v5.showValue();
    BST.show(); cout << BST.count() << " keys" << endl;
    //---------------------------------------------------------------------------------------------
    Item vr2; int keyR2 = 1; vr2.init(keyR2); BST.remove(vr2);
    cout << "After remove element: key = " << keyR2 << ", item = "; vr2.showValue();
    BST.show(); cout << BST.count() << " keys" << endl;
    //---------------------------------------------------------------------------------------------
    cout << "Splay binary search tree balanced: " << endl;
    BST.balance(); cout << "K,V" << endl;
    BST.show(); cout << BST.count() << " keys" << endl;
    //---------------------------------------------------------------------------------------------
    system("pause");
    return 0;
}
