#include <iostream>
#include <string>
#include <algorithm>
#include <cctype>
#include <regex>
using namespace std;

int main()
{
    string s("The zip code of Braunschweig in Germany is 38100");
    cout << "original: " << s << endl;

    //переводим все символы в нижний регистр
    transform(s.cbegin(), s.cend(), //источник
              s.begin(), //получатель
              [](char c){ return tolower(c); }); //операция
    cout << "lowered: " << s << endl;

    //переводим все символы в верхний регистр
    transform(s.cbegin(), s.cend(), //источник
              s.begin(), //получатель
              [](char c){ return toupper(c); }); //операция
    cout << "uppered: " << s << endl;

    //выполняем поиск строки "Germany" без учета регистра
    string g("Germany");
    string::const_iterator pos;
    pos = search(s.cbegin(), s.cend(), //строка, в которой идет поиск
                 g.cbegin(), g.cend(), //искомая подстрока
                 [](char c1, char c2){ return toupper(c1) == toupper(c2); }//критерий сравнения
    );
    if(pos != s.end()){
        cout << "substring \"" << g << "\" found at index "
             << pos - s.begin() << endl;
    }

    system("pause");
    return 0;
}
