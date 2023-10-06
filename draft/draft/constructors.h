#ifndef CONSTRUCTORS_H
#define CONSTRUCTORS_H

#include <iostream>
#include <cassert>
#include <QDebug>

namespace Ctrs {

class A {
public:
    //A() = default;
    //~A() = default;
    A(){ std::cout << "A()" << std::endl; }
    ~A(){ std::cout << "~A()" << std::endl; }
    A(const A &other){ std::cout << "A(const A&)" << std::endl; p = other.p; }
    A& operator=(const A &other){ std::cout << "A& operator=(const A&)" << std::endl; p = other.p; return *this; }
    //A(A&&){ std::cout << "A(A&&)" << std::endl; }
    //A& operator=(A&&){ std::cout << "A& operator=(A&&)" << std::endl; }
    int p{};
};
std::ostream& operator<<(std::ostream &os, const A &a) {
    return os << a.p;
}

void autoCtrsGen() {
    A a;
    // copy ctr
    A a0 = a;
    assert(a0.p == 0);
    // copy opr
    A a1; a1.p = 1;
    A a2; a2.p = 2;
    a2 = a1;
    assert(a2.p == 1);
    // move ctr
    A a3 = std::move(a1);
    assert(a3.p == 1);
    assert(a1.p == 1);
    // move opr
    a2.p = 2;
    A a4;
    std::cout << "&a4 = " << &a4 << "; &a2 = " << &a2 << std::endl;
    a4 = std::move(a2);
    std::cout << "&a4 = " << &a4 << "; &a2 = " << &a2 << std::endl;
    assert(a4.p == 2);
    assert(a2.p == 2);
    assert(&a2 != &a4);
    std::cout << "a4 = " << a4 << "; a2 = " << a2 << std::endl;
}

void moveCancel() {
    A a;
    A a2 = std::move(a);
    A a3;
    a3 = std::move(a);
}

void out() {
   //autoCtrsGen();
    moveCancel();
}

}
#endif // CONSTRUCTORS_H
