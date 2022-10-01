#include <iostream>
#include <cstring>
#include <iterator>
#include <algorithm>
#include <malloc.h>
#include "CodeGenerator.h"
#include "task3.h"
using namespace std;

int foo() { return 3; }

// 1. Перечислите все проблемы, которые вы видите в данном коде:
class Foo
{
public:
    Foo(int j)
    {
        cout << "Foo()" <<endl;
        i = new int[j];
        _mem = j;
    }
    virtual ~Foo()
    {
        cout << "~Foo()";
        if(i == nullptr)
            cout << "; i = null";
        cout << endl;
        delete[] i;
    }
    Foo(const Foo& other)
    {
        if(other.i && this != &other)
        {
            int length = _msize(other.i) / sizeof(int);
            i = new int[length];
            std::memcpy(i, other.i, length);
            _mem = other._mem;
        }
    }
    Foo& operator=(const Foo& other)
    {
        if(other.i && this != &other)
        {
            delete[] i;
            int length = _msize(other.i) / sizeof(int);
            i = new int[length];
            std::memcpy(i, other.i, length);
            _mem = other._mem;
        }
       return *this;
    }
    int mem() const { return _mem; }
private:
    int* i;
    int _mem = 0;
};

class Bar: public Foo
{
public:
    Bar(int j, int k) : Foo(k)
    {
        cout << "Bar()" <<endl;
        i = new char[j];
    }
    ~Bar()
    {
        cout << "~Bar()" << endl;
        delete[] i;
    }
    int func(){ return _val; }
private:
    char* i;
    int _val = 3;
};


int main()
{
    Foo* f = new Foo(100);
    Foo* b = new Bar(200, 101);
    //Bar* b1 = new Bar(300);

    cout << "f::mem: " << f->mem() << endl;//100
    cout << "b::mem: " << b->mem() << endl;//101
    *f = *b;
    cout << "f::mem: " << f->mem() << endl;//101
    cout << "b::mem: " << b->mem() << endl;//101

    auto fb = dynamic_cast<Bar*>(f);
    if(fb)
    {
        cout << "fb->func() = " << fb->func() << endl;
    }

    delete f;
    delete b;

    //int a[] = { -5, 10, 15 };
    //std::cout << std::size(a) << '\n';

    const int n = 3;
    //int array[foo()];
    int array[n];
    array[0] = 1;
    array[1] = 2;
    array[2] = 3;

    NewCodeGenerator cpp_generator(NewCodeGenerator::C_PLUS_PLUS);
    cout << "cpp generated code: " << cpp_generator.generateCode() << std::endl;

    NewCodeGenerator java_generator(NewCodeGenerator::JAVA);
    cout << "java generated code: " << java_generator.generateCode() << std::endl;

    return 0;
}


