#include "st.h"
//Раздел 14.2. Цепочки переполнения (раздельное связывание). Глава 14. Хеширование.
void insertElem_and_showTable(Key key, ST<Key,Item>& hashTable)
{
    Item v; v.init(key); hashTable.insert(v);
    cout << "After insertion element: key = " << key << ", item = "; v.showValue();
    cout << ", hash = " << hashM(key, hashTable.size()) << endl;
    hashTable.show(); cout << hashTable.count() << " keys" << endl << endl;
}
void removeLastElems_and_showTable(ST<Key,Item>& hashTable, int numOfLastElems)
{
    Value* values = hashTable.removeLastElems(numOfLastElems);
    cout << "After remove " << numOfLastElems << " last items:";
    if(values != nullptr)
    { int i = 0; while(values[i] != -1){ cout << " " << values[i]; i++; } }
    cout << endl;
    hashTable.showCounts(); cout << hashTable.count() << " keys" << endl << endl;
}
void searchAndShowElem(Key key, ST<Key,Item>& hashTable)
{
    Item found = hashTable.search(key);
    cout << "Linear search item with key = " << key << ": "; found.showValue();
    cout << endl << endl;
}
void showTableWithCounts(ST<Key,Item>& hashTable)
{
    hashTable.showCounts(); cout << hashTable.count() << " keys" << endl << endl;
}

int main()
{
    //---------------------------------------------------------------------------------------------
    //целочисленные ключи
    int N = 10, M = 15;
    ST<Key, Item> hashT(M, hashM);
    cout << "K\tV\tHash" << endl;
    for(int key = 0; key < N; key++)
    {
        Item v; v.init(key);//v.init(rand() % 10);
        hashT.insert(v); v.show(); cout << "\t" << hashM(key, hashT.size()) << endl;
    }
    //---------------------------------------------------------------------------------------------
    cout << "Hash table - separate chaining (integer keys): " << endl;
    hashT.show(); cout << hashT.count() << " keys" << endl;
    //---------------------------------------------------------------------------------------------
    searchAndShowElem(7, hashT);
    //---------------------------------------------------------------------------------------------
    insertElem_and_showTable(14, hashT);
    insertElem_and_showTable(17, hashT);
    //---------------------------------------------------------------------------------------------
    searchAndShowElem(56, hashT);
    showTableWithCounts(hashT);
    //---------------------------------------------------------------------------------------------
    removeLastElems_and_showTable(hashT, 3);
    insertElem_and_showTable(13, hashT);
    //---------------------------------------------------------------------------------------------
    removeLastElems_and_showTable(hashT, 0);
    removeLastElems_and_showTable(hashT, 1);
    removeLastElems_and_showTable(hashT, 6);
    removeLastElems_and_showTable(hashT, 6);
    removeLastElems_and_showTable(hashT, 1);
    removeLastElems_and_showTable(hashT, 2);
    //---------------------------------------------------------------------------------------------
    cout << "K\tV\tHash" << endl;
    for(int i = 0; i < N; i++)
    {
        int key = 2*i + 1; Item v; v.init(key);
        hashT.insert(v); v.show(); cout << "\t" << hashM(key, hashT.size()) << endl;
    }
    hashT.show(); cout << hashT.count() << " keys" << endl;
    //---------------------------------------------------------------------------------------------
    system("pause");
    return 0;
}
