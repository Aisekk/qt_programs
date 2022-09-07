#include "st.h"
//Раздел 14.4. Динамические хеш-таблицы. Глава 14. Хеширование.
//Линейное опробование с расширением путем удвоения
void insertElem_and_showTable(Key key, ST<Key,Item>& hashTable)
{
    Item v; v.init(key); hashTable.insert(v);
    cout << "After insertion element: key = " << key << ", item = "; v.showValue();
    cout << ", hash = " << hashM(key, hashTable.size()) << endl;
    hashTable.show(); cout << hashTable.count() << " keys" << endl << endl;
}
void removeElem_and_showTable(Key key, ST<Key,Item>& hashTable)
{
    Item v; v.init(key); hashTable.remove(v);
    cout << "After remove element: key = " << key << ", item = "; v.showValue();
    cout << ", hash = " << hashM(key, hashTable.size()) << endl;
    hashTable.show(); cout << hashTable.count() << " keys" << endl << endl;
}
void searchAndShowElem(Key key, ST<Key,Item>& hashTable)
{
    Item found = hashTable.search(key);
    cout << "Linear search item with key = " << key << ": "; found.showValue();
    cout << endl << endl;
}

int main()
{
    //---------------------------------------------------------------------------------------------
    //целочисленные ключи
    ST<Key, Item> hashT(hashM);
    //---------------------------------------------------------------------------------------------
    cout << "Dynamic hash table based on linear probing (integer keys): " << endl;
    hashT.show(); cout << hashT.count() << " keys" << endl << endl;
    //---------------------------------------------------------------------------------------------
    insertElem_and_showTable(14, hashT);
    insertElem_and_showTable(20, hashT);
    //---------------------------------------------------------------------------------------------
    int N = 4;
    cout << "After insertion elements: ";
    for(int i = 1; i < N; i++)
    {
        int key = i; Item v; v.init(key); /* v.init(rand() % 10); */ hashT.insert(v);
        cout << "(" << key << ";"; v.showValue(); cout << "), ";
    }
    cout << endl;
    hashT.show(); cout << hashT.count() << " keys" << endl << endl;
    //---------------------------------------------------------------------------------------------
    searchAndShowElem(2, hashT);
    searchAndShowElem(56, hashT);
    //---------------------------------------------------------------------------------------------
    removeElem_and_showTable(1, hashT);
    //---------------------------------------------------------------------------------------------
    insertElem_and_showTable(5, hashT);
    insertElem_and_showTable(4, hashT);
    //---------------------------------------------------------------------------------------------
    cout << "After remove elements: ";
    for(int i = 2; i < 6; i++)
    {
        int key = i; Item v; v.init(key); /* v.init(rand() % 10); */ hashT.remove(v);
        cout << "(" << key << ";"; v.showValue(); cout << "), ";
    }
    cout << endl;
    hashT.show(); cout << hashT.count() << " keys" << endl << endl;
    //---------------------------------------------------------------------------------------------
    removeElem_and_showTable(20, hashT);
    //---------------------------------------------------------------------------------------------
    system("pause");
    return 0;
}
