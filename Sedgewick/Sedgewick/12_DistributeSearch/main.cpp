#include <iostream>
#include "st.h"
using namespace std;
//Раздел 12.2, Глава 12. Таблицы символов и деревья бинарного поиска
//распределяющий поиск, непорядоченная таблица символов
int main()
{
    int N, maxN = 10;
    ST<Key, Item> st;
    for(N = 0; N < maxN; N++)
    { Item v; v.init(N); st.insert(v); }
    //---------------------------------------------------------------------------------------------
    cout << "Symbol table example: " << endl;
    cout << "K,V" << endl;
    st.show();
    cout << N << " keys" << endl;
    cout << st.count() << " distinct keys" << endl;
    //---------------------------------------------------------------------------------------------
    Key key = 5; Item found = st.search(key);
    cout << "Search item with key = " << key << ": "; found.showValue();
    //---------------------------------------------------------------------------------------------
    Item v; v.init(3); Key keyR = v.key(); st.remove(v);
    cout << "Remove item with key " << keyR << ": " << endl;
    st.show();
    //---------------------------------------------------------------------------------------------
    int k = 3; Item sel = st.select(k);
    cout << "Selected " << k << " item: "; sel.showValue();
    st.show();
    //---------------------------------------------------------------------------------------------
    system("pause");
    return 0;
}
