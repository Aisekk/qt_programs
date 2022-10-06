#ifndef GENERAL_H
#define GENERAL_H

#include <string>
#include <iostream>
using namespace std;

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

void ThrowInt()
{
    try{
        throw 56;
    }
    //catch(...){ std::cout << "..." << std::endl; } // catch-all handler must come last
    catch(long){ std::cout << "long" << std::endl; }
    catch(int){ std::cout << "int" << std::endl; }
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
    void f(int){}
    void g(X){}
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
    B::g(x);
    A::Y y;
    h(y);
}

void VirtualPublic()
{
    class A
    {
    public:
        A(){ std::cout << "A()"; }
    };

    class B : virtual public A
    {
    public:
        B(){ std::cout << "B()"; }
    };

    class C : public B
    {
    public:
        C(){ std::cout << "C()"; }
    };

    C c;
}

void TypeDimensions()
{
    int i = 1;
    signed int signed_i = 1;
    unsigned int unsigned_i = 1;

    cout << "sizeof (int) = " << sizeof (int) << endl;
    cout << "sizeof (signed int) = " << sizeof (signed int) << endl;
    cout << "sizeof (unsigned int) = " << sizeof (unsigned int) << endl;

    cout << "sizeof (i) = " << sizeof (i) << endl;
    cout << "sizeof (signed_i) = " << sizeof (signed_i) << endl;
    cout << "sizeof (unsigned_i) = " << sizeof (unsigned_i) << endl;

    cout << "sizeof (char) = " << sizeof (char) << endl;
    cout << "sizeof (wchar_t) = " << sizeof (wchar_t) << endl;
    cout << "sizeof (long) = " << sizeof (long) << endl;

    cout << "sizeof (float) = " << sizeof (float) << endl;
    cout << "sizeof (double) = " << sizeof (double) << endl;
    cout << "sizeof (long double) = " << sizeof (long double) << endl;
}

void CallBaseClassMethod()
{
    class Bird
    {
    public:
        void fly() { cout << "fly" << endl; }
        virtual ~Bird() = default;
    };

    class Plane : Bird
    {
      public:
        using Bird::fly;
    };

    //Bird* bird = new Plane();
    Plane* superjet100 = new Plane();
    superjet100->fly();

    delete superjet100;
}

#endif // GENERAL_H
