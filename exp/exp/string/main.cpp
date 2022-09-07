#include <iostream>
#include "mystring.h"
using namespace std;

void out_use_inex(const String& s)
{
    for(int i = 0; i < (int)s.size(); ++i)
    {
        cout << s[i];
    }
}

int main()
{
    String stroka;
    stroka = String("strochka");

    out_use_inex(stroka);

    stroka = "telega";
    cout << "\n" << stroka << endl;

    return 0;
}
