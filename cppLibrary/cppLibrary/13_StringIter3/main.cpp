#include <iostream>
#include <string>
#include <algorithm>
#include <iterator>
#include <locale>
using namespace std;

int main()
{
    string input;
    //не игнорируем начальные пробельные символы
    cin.unsetf(ios::skipws);

    //читаем все символы, сжимая пропуски
    const locale& loc(cin.getloc()); //локальный контекст
    unique_copy(istream_iterator<char>(cin), //начало источника
                istream_iterator<char>(), //конец источника
                back_inserter(input), //получатель
                [=] (char c1, char c2)
    { return isspace(c1,loc) && isspace(c2,loc); }); //критерий для смежных дубликатов
    cout << input << endl;

    system("pause");
    return 0;
}
