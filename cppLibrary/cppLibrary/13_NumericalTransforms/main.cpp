#include <iostream>
#include <string>
#include <limits>
#include <exception>
using namespace std;

int main()
{
    try{
        //преобразование в числовой тип
        cout << stoi(" 77") << endl;
        cout << stod(" 77.7") << endl;
        cout << stoi("-0x77") << endl;

        //используем индексы необработанных символов
        size_t idx;
        cout << stoi(" 42 is the truth", &idx) << endl;
        cout << "idx of first unprocessed char: " << idx << endl;

        //используем основания 16 и 8
        cout << stoi(" 42", nullptr, 16) << endl;
        cout << stol("789", &idx, 8) << endl;
        cout << "idx of first unprocessed char: " << idx << endl;

        //преобразуем числовое значение в строку
        long long ll = numeric_limits<long long>::max();
        string s = to_string(ll);
        cout << s <<endl;

        //пытаемся выполнить обратное преобразование
        cout << stoi(s) << endl;// генерируется out_of_range
    }
    catch(const exception& e){ cout << e.what() << endl; }

    return 0;
}
