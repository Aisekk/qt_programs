#include <iostream>

using namespace std;

int main()
{
    enum flag{ f1 = 0x01, f2 = 0x02, f3 = 0x03, f4 = 0x04 };
    flag f = f2;

    cout << "size of enum: " << sizeof(f) << endl;
    cout << "size of flag: " << sizeof(flag) << endl;

    int n = 0;
    if(n | f2)
        cout << "bitwise (0 | 0x02): " << static_cast<int>(n | f2) << endl; // 2
    if(n | f1)
        cout << "bitwise (0 | 0x01): " << static_cast<int>(n | f1) << endl; // 1
    if(n | f4)
        cout << "bitwise (0 | 0x04): " << static_cast<int>(n | f4) << endl; // 4
    if(n | f3)
        cout << "bitwise (0 | 0x03): " << static_cast<int>(n | f3) << endl; // 3

    if(f1 | f2)
       cout << "bitwise (0x01 | 0x02): " << static_cast<int>(f1 | f2) << endl; // 3

    return 0;
}
