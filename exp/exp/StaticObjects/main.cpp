#include <iostream>
//#include "math.cpp"
#include "extend_math.cpp"
#include "StaticFuncInHeader.h"

using namespace std;
// 1. Статические переменные внутри функции: пропущено
// 2. Статические объекты класса

class Base
{
public:
    Base()
    {
        std::cout << "Constructor Base" << std::endl;
    }
    ~Base()
    {
        std::cout << "Destructor Base" << std::endl;
    }
};

void foo()
{
    static Base obj;
    //Base obj;
}

// 3. Статические члены класса

class A
{
public:
  A() { std::cout << "Constructor A" << std::endl; }
  ~A() { std::cout << "Destructor A" << std::endl; }
};

class B
{
public:
  B() { std::cout << "Constructor B" << count++ << std::endl; }
  ~B() { std::cout << "Destructor B" << --count << std::endl; }

private:
  static A a; // объявление
  static int count; // объявление
};

A B::a; // определение
int B::count = 1; // определение

// 4. Статические функции

int sum(int, int); // declaration
void outStaticVar();
//extern int var1;

int main()
{
    //foo();
    //std::cout << "End of foo()" << std::endl;
    //B b1, b2, b3;

    int result = sum(1, 2);
    std::cout << "sum = " << result << std::endl;

    func();
    staticFunc();
    outStaticVar();

    std::cout << "var1 = " << var1 << std::endl;

    return 0;
}

