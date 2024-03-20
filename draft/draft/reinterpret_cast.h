#ifndef REINTERPRET_CAST_H
#define REINTERPRET_CAST_H

#include <iostream>

namespace Cast {

struct A {
    int a = 1;
};

struct B {
    int b = 2;
};

struct C : A, B {
    int c = 3;
};

void reinterpet_cast() {
    C c;
    std::cout << static_cast<B*>(&c)->b << std::endl;
    std::cout << reinterpret_cast<B*>(&c)->b << std::endl;
}

}

#endif // REINTERPRET_CAST_H
