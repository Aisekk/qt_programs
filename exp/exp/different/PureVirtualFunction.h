#ifndef PUREVIRTUALFUNCTION_H
#define PUREVIRTUALFUNCTION_H
#include <iostream>

extern int global;
extern int sglobal;

class A
{
private:
    virtual void foo() = 0;
    void bar()
    {
        foo();
    }
public:
    A()
    {
        //foo();
        //bar();
    }
};

class B : public A
{
private:
    void foo() override
    {
        std::cout << "foo()" << std::endl;
        std::cout << "global = " << global << std::endl;
        std::cout << "sglobal = " << sglobal << std::endl;
    }
public:
    B()
    {
        foo();
    }
};

void PureVirtualFunctionCall()
{
    //A a;
    B b;
}

#endif // PUREVIRTUALFUNCTION_H
