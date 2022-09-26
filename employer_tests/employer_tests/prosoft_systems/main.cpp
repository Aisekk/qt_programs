#include <iostream>

using namespace std;

class Foo
{
public:
    Foo(int j) { i = new int[j]; }
    virtual ~Foo() { delete[] i; }
private:
    int* i;
};

class Bar: public Foo
{
public:
    Bar(int j) : Foo(j) { _i = new char[j]; }
    ~Bar() { delete[] _i; }
private:
    char* _i;
};


void main()
{
    Foo* f = new Foo(100);
    Foo* b = new Bar(200);
    //Bar* b1 = new Bar(300);
    *f = *b; // *f имеет тип Foo и ему нельзя присваивать значение объекта типа Bar
    delete f;
    //delete b;

    //return 0;
}
