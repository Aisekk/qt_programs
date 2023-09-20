#ifndef CONSTRUCTORS_H
#define CONSTRUCTORS_H

#include <iostream>
#include <cassert>

namespace Ctrs {

class A {
public:
    int p{};
};

void autoGen() {
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
    a4 = std::move(a2);
    assert(a4.p == 2);
    assert(a2.p == 2);
    std::cout << a4.p << std::endl;
    std::cout << a2.p << std::endl;
}

void out() {
   autoGen();

}

}
#endif // CONSTRUCTORS_H
