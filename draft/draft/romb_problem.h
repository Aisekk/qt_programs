#ifndef ROMB_PROBLEM_H
#define ROMB_PROBLEM_H

#include <iostream>

namespace RombProblem {

class Base {
public:
    virtual void f() { std::cout << "Base::f()" << std::endl; }
    virtual ~Base() {}
};

class A : public virtual Base {
public:
    virtual void f() { std::cout << "A::f()" << std::endl; }
};

class B : public virtual Base {
public:
    //virtual void f() { std::cout << "B::f()" << std::endl; }
};

class C : public A, public B {
public:
    //virtual void f() { std::cout << "C::f()" << std::endl; }
};

class D : public C {
public:

};

void rombProblem() {
    C *c = new C;
    c->f();
    //c->A::f();
    D *d = new D;
    d->f();

    delete c;
    delete d;
}

}

#endif // ROMB_PROBLEM_H
