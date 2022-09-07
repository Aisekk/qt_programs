#include <iostream>
using namespace std;

// выравнивание - поля в памяти выравниваются на позиции, кратные свом размерам
struct A // 24b
{
    long long a;
    char b;
    int c;
    char b2;
};
struct A_opt // 16b
{
    long long a;
    char b;
    char b2;
    int c;
};

int main()
{
    cout << "size of A:     " << sizeof(A) << endl;
    cout << "size of A_opt: " << sizeof(A_opt) << endl;

    A a;
    A_opt a_opt;
    cout << "size of a:     " << sizeof(a) << endl;
    cout << "size of a_opt: " << sizeof(a_opt) << endl;

    return 0;
}
