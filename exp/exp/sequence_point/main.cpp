#include <iostream>
#include <array>
using namespace std;

// точка следования - место программы, в котором все побочные эффекты от предыдущих вычислений
// должны завершиться, а от последующих - еще не начаться

class X
{
public:
    X& f1(int i){ cout << " f1: " << i; }
    X& f2(int i){ cout << " f2: " << i; }
    X& f3(int i){ cout << " f3: " << i; }
};
int f(int p1, int p2)
{
    return p1 + p2;
}

int main()
{
    int i = 0;
    cout << (i += 1) << ' ' << (i += 1) << ' ' << (i += 1) << ' ' << endl;

    i = 0;
    cout.operator << (i += 1).operator << (i += 1).operator << (i += 1) << endl;

    i = 0;
    X x;
    x.f1(++i).f2(++i).f3(++i);
    cout << '\n';

    // между соседними точками следования скалярное значение должно меняться не более 1 раза,
    // причем предыдущее значение должно считываться только для определения сохраняемого значения

    // неопределенное поведение:
    std::array<int, 5> an = {9, 9, 9, 9, 9};
    i = 0;
    i = an[i++]; cout << i << ' ' << an[0] << endl;
    i = 0;
    i = ++i + 1; cout << i << ' ' << endl;

    int n = 0; i = 0;
    n = i ++ + ++i; cout << n << ' ' << i << endl;
    n = 0; i = 0;
    n = f(++i, ++i); cout << n << ' ' << i << endl;

    return 0;
}
