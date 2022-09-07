#include <iostream>
#include <bitset>
#include <algorithm>
using namespace std;

bitset<8> byteReverse1(bitset<8>& b)
{
    char j = 7;
    for(char i = 0; i < 4; i++, j--)
    {
        bool t = b[i];
        b[i] = b[j];
        b[j] = t;
    }
    return b;
}
bitset<8> byteReverse2(bitset<8>& b)
{
    bitset<8> a;
    for(char i = 0; i < 8; i++)
    {
        a[i] = b[7-i];
        b << 1;
    }
    return a;
}


int main()
{
    bitset<8> byte("10001101");
    cout << "Input byte: " << byte << endl;
    cout << "Reverse byte 1: " << byteReverse1(byte) << endl;
    cout << "Reverse byte 2: " << byteReverse2(byte) << endl;
    system("pause");
    return 0;
}
