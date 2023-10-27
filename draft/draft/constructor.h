#ifndef CONSTRUCTOR_H
#define CONSTRUCTOR_H

#include <iostream>

namespace Constructor {

class A{
public:
    A() { std::cout << "A()" << std::endl; }
};
class B: public virtual A {
public:
    B() { std::cout << "B()" << std::endl; }
};
class D: public virtual A{
public:
    D() { std::cout << "D()" << std::endl; }
};

class M {
public:
    M() { std::cout << "M()" << std::endl; }
};

class C: public D, public B {
public:
    C() { std::cout << "C()" << std::endl; }
    M m;
    static int p;
    int q{};
    double d{};
};

void test() {
    C c;
    std::cout << c.q << std::endl;
    std::cout << c.d << std::endl;
}

}

#endif // CONSTRUCTOR_H
