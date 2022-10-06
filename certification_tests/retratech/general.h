#ifndef GENERAL_H
#define GENERAL_H

#include <string>
#include <iostream>

void Switch()
{
    //std::string var;
    int var = 0, var1 = 1;
    //bool var = false;
    switch (var)
    {
    case 1:
        break;
    }
}

const int N = 50;

void Mistakes()
{
    bool bFirst = true;
    while(1)
    {
        int N = 1;
        if(bFirst)
        {
            N = 0; bFirst = 0;
        }
        if(N > ::N) break;
        N++;
    }
}

int func(const char* str)
{
    std::cout << str << std::endl;
    return 0;
}

void PointerToFunc()
{
    int(*f)(const char* str) = nullptr;
    f = func;
    f("stroka");
    auto g = (void*)f;
    //g("stroka 2");
}

void ThrowDouble()
{
    try{
        throw 8.;
    }
    catch(int){ std::cout << "int" << std::endl; }
    catch(float){ std::cout << "float" << std::endl; }
    catch(double){ std::cout << "double" << std::endl; }
}

void PrivateInheritance()
{
    struct First
    {
        First(){ std::cout << "First()"; }
        virtual ~First(){ std::cout << "~First()"; }
    };

    struct Second : First
    {
        Second(){ std::cout << "Second()"; }
        virtual ~Second(){ std::cout << "~Second()"; }
    };

    First* first = new Second;
    delete first;
}

void TypeId()
{
    class Zero{};

    class One : public Zero{};
    class Two : public Zero{};

    One* pO = new One;
    Two* pT = new Two;

    std::cout << (typeid(pO) == typeid (pT)) << std::endl;
}

void A_bit_shift_B()
{
    int A = 64;
    int B = 3;
    int C = A >> B;
    std::cout << C << std::endl;
}

namespace A
{
    struct X{};
    struct Y{};
    void f(int);
    void g(X);
}

namespace B
{
    void f(int i){}
    void g(A::X){}
    void h(A::Y){}
    void main();
}

void B::main()
{
    f(100);
    A::X x;
    A::g(x);
    A::Y y;
    h(y);
}


#endif // GENERAL_H
