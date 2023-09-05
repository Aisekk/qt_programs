#ifndef PURE_VIRTUAL_FUNC_CALL_H
#define PURE_VIRTUAL_FUNC_CALL_H
#include <iostream>

namespace PureCall {

class Base {
public:
    Base() {
        std::cout << "Base()" << std::endl;
        g();
    }
    void g() { f(); }
    virtual void f() = 0; // { std::cout << "Base::f()" << std::endl; } //= 0;
};

class Derived : public Base
{
public:
    Derived() : Base(){}
    void f() override {
        std::cout << "Derived::f()" << std::endl;
    }
};

void pureVirtCall() {
    Derived d;
    //d.f();
}

}

#endif // PURE_VIRTUAL_FUNC_CALL_H
