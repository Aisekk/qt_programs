#include <iostream>
#include "GCD.h"
using namespace std;
//Раздел 5.1, Глава 5. Рекурсия и деревья

int main()
{
    cout << "Compute GCD of numbers: " << endl;
    cout << "number 1: ";
    int a{};
    cin >> a;
    cout << "number 2: ";
    int b{};
    cin >> b;
    //---------------------------------------------------------------------------------------------
    //НОД
    //GCD(a,b) = GCD(b, a Mod b)
    int gcd = GCD(a,b);
    //---------------------------------------------------------------------------------------------
    cout << "GCD of numbers " << a << "," << b << " : " << gcd << endl;
    //---------------------------------------------------------------------------------------------
    //НОД рекурсивный
    int gcdR = GCDR(a,b);
    //---------------------------------------------------------------------------------------------
    cout << "GCD recursive of numbers " << a << "," << b << " : " << gcdR << endl;
    //---------------------------------------------------------------------------------------------
    system("pause");
    return 0;
}