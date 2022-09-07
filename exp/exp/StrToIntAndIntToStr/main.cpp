#include <iostream>
//#include "system.h"
#include "StrToInt_IntToStr.h"
using namespace std;

int main()
{
    int num;
    char s[40], *n;
    system("chcp 1251");
    system("cls");
    cout << "Введите число: ";
    cin.getline(s, 80);
    num = StrToInt(s);
    cout << "Вы ввели число " << num;
    num = num + 1;
    n = IntToStr(num);
    cout << endl << "увеличенное на 1 число равно " << n;
    cin.get();
    return 0;
}
