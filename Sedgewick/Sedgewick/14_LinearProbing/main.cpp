#include "st.h"
//Раздел 14.3. Линейное опробование (зондирование). Глава 14. Хеширование.
//Метод хеширования с открытой адресацией
int main()
{
    //---------------------------------------------------------------------------------------------
    //целочисленные ключи
    int N = 10; int a = 2;
    ST<Key, Item> hashT(N, hashM);
    cout << "K\tV\tHash" << endl;
    for(int i = 0; i < N; i++)
    { int key = i; Item v; v.init(key); /*v.init(rand() % 10);*/ hashT.insert(v); }
    //---------------------------------------------------------------------------------------------
    cout << "Hash table - linear probing (integer keys): " << endl;
    hashT.show(); cout << hashT.count() << " keys" << endl;
    //---------------------------------------------------------------------------------------------
    Key key = 7; Item found = hashT.search(key);
    cout << "Linear search item with key = " << key << ": "; found.showValue();
    cout << endl << endl;
    //---------------------------------------------------------------------------------------------
    Item v2; int key2 = 14; v2.init(key2); hashT.insert(v2);
    cout << "After insertion element: key = " << key2 << ", item = "; v2.showValue();
    cout << ", hash = " << hashM(key2, a*N) << endl;
    hashT.show(); cout << hashT.count() << " keys" << endl << endl;
    //---------------------------------------------------------------------------------------------
    Key key3 = 56; Item found2 = hashT.search(key3);
    cout << "Linear search item with key = " << key3 << ": "; found2.showValue();
    cout << endl;
    //---------------------------------------------------------------------------------------------
    Item v4; int key4 = 20; v4.init(key4); hashT.insert(v4);
    cout << "After insertion element: key = " << key4 << ", item = "; v4.showValue();
    cout << ", hash = " << hashM(key4, a*N) << endl;
    hashT.show(); cout << hashT.count() << " keys" << endl << endl;
    //---------------------------------------------------------------------------------------------
    Item v5; int key5 = 4; v5.init(key5); hashT.remove(v5);
    cout << "After remove element: key = " << key5 << ", item = "; v5.showValue();
    cout << ", hash = " << hashM(key5, a*N) << endl;
    hashT.show(); cout << hashT.count() << " keys" << endl << endl;
    //---------------------------------------------------------------------------------------------
    Item v6; int key6 = 113; v6.init(key6); hashT.insert(v6);
    cout << "After insertion element: key = " << key6 << ", item = "; v6.showValue();
    cout << ", hash = " << hashM(key6, a*N) << endl;
    hashT.show(); cout << hashT.count() << " keys" << endl << endl;
    //---------------------------------------------------------------------------------------------
    system("pause");
    return 0;
}
