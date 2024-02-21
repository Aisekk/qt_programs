#ifndef CONSTRUCTORS_GEN_H
#define CONSTRUCTORS_GEN_H

#include <utility>

namespace ConstructorsGen {

class A {

};

void test_auto_gen() {
    A a, a1, a2, a3;
    A a_copy = a;
    a1 = a;
    a2 = std::move(a3);
}

}

#endif // CONSTRUCTORS_GEN_H
