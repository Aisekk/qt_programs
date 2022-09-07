#include <iostream>
#include "st.h"
using namespace std;
//Раздел 12.4, Глава 12. Таблицы символов и деревья бинарного поиска
//интерполяционный поиск, упорядоченная таблица символов
//эффективен, если ключи распределены равномерно и для больших N
int main()
{
    int N, maxN = 10;
    ST<Key, Item> st(maxN);
    for(N = 0; N < maxN; N++)
    { Item v; v.init(N+1); st.insert(v); }
    //---------------------------------------------------------------------------------------------
    cout << "Symbol table for interpolation search: " << endl;
    cout << "K,V" << endl;
    st.show();
    cout << N << " keys" << endl;
    cout << st.count() << " distinct keys" << endl;
    //---------------------------------------------------------------------------------------------
    Key key = 8; Item found = st.search(key);
    cout << "Interpolation search item with key = " << key << ": "; found.showValue();
    //---------------------------------------------------------------------------------------------
    int k = 3; Item sel = st.select(k);
    cout << "Selected " << k << " item: "; sel.showValue();
    st.show();
    //---------------------------------------------------------------------------------------------
    system("pause");
    return 0;
}
