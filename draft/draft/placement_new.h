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
    auto* pd = new (pool) Derived();
    Base* pb = pd;
    pd->~Derived();
    pb->foo();
}

}

#endif // PLACEMENT_NEW_H
