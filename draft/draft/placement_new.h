#ifndef PLACEMENT_NEW_H
#define PLACEMENT_NEW_H

#include <iostream>
using namespace std;

namespace PlacementNew {

char pool[256];

class Base
{
public:
    virtual void foo() = 0;
    virtual ~Base(){};
};

class Derived: public Base
{
public:
    virtual void foo() override { cout <<"Derived::foo()" << endl;}
};

void pureCall()
{
    cout << "sizeof(Base) = " << sizeof(Base) << endl;
    auto* pd = new (pool) Derived();
    Base* pb = pd;
    pd->~Derived();
    pb->foo();
}

void test() {
    int X = 10;

    cout << "Before placement new :" << endl;
    cout << "X : " << X << endl;
    cout << "&X : " << &X << endl;

    // Placement new changes the value of X to 100
    int *mem = new (&X) int(100);

    cout << "\nAfter placement new :" << endl;
    cout << "X : " << X << endl;
    cout << "mem : " << mem << endl;
    cout << "&X : " << &X << endl;
}

}

#endif // PLACEMENT_NEW_H
