#include <iostream>
#include "st.h"
using namespace std;
//Раздел 12.3, Глава 12. Таблицы символов и деревья бинарного поиска
//линейный поиск, неупорядоченная таблица символов с использованием связанного списка
int main()
{
    int N, maxN = 10;
    ST<Key, Item> st;
    for(N = 0; N < maxN; N++)
    { Item v; v.init(maxN-N); st.insert(v); }
    //---------------------------------------------------------------------------------------------
    cout << "Symbol table - unordered list: " << endl;
    cout << "K,V" << endl;
    st.show();
    cout << N << " keys" << endl;
    cout << st.count() << " distinct keys" << endl;
    //---------------------------------------------------------------------------------------------
    Key key = 6; Item found = st.search(key);
    cout << "Search item with key = " << key << ": "; found.showValue();
    //---------------------------------------------------------------------------------------------
    system("pause");
    return 0;
}
