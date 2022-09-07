#include <iostream>
#include "st.h"
using namespace std;
//Раздел 12.4, Глава 12. Таблицы символов и деревья бинарного поиска
//бинарный поиск, упорядоченная таблица символов
int main()
{
    int N, maxN = 10;
    ST<Key, Item> st(maxN);
    for(N = 0; N < maxN; N++)
    { Item v; v.init(N+1); st.insert(v); }
    //---------------------------------------------------------------------------------------------
    cout << "Symbol table for binary search: " << endl;
    cout << "K,V" << endl;
    st.show();
    cout << N << " keys" << endl;
    cout << st.count() << " distinct keys" << endl;
    //---------------------------------------------------------------------------------------------
    Key key = 8; Item found = st.search(key);
    cout << "Binary search item with key = " << key << ": "; found.showValue();
    //---------------------------------------------------------------------------------------------
    int k = 3; Item sel = st.select(k);
    cout << "Selected " << k << " item: "; sel.showValue();
    st.show();
    //---------------------------------------------------------------------------------------------
    system("pause");
    return 0;
}
