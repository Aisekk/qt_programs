#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

int main()
{
    const string hello("Hello, how are you?");
    //инициализируем строку s всеми символами строки hello
    string s(hello.cbegin(),hello.cend());

    for(char c : s) cout << c;
    cout << endl;

    //изменяем порядок на обратный
    reverse(s.begin(), s.end());
    cout << "reverse:   " << s << endl;

    //сортируем
    sort(s.begin(), s.end());
    cout << "ordered:   " << s << endl;

    //удаляем соседние дубликаты
    // - unique() изменяет порядок и возвращает новый конец
    // - erase() уменьшает размер
    s.erase(unique(s.begin(), s.end()), s.end());
    cout << "no duplicates: " << s << endl;

    system("pause");
    return 0;
}
