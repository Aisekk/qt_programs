#ifndef ALIGN_H
#define ALIGN_H

#include <iostream>

namespace Align {

struct A {
    double a = 1.0;
    char b = 'a';
    long long c = 1;
    int d = 2;
};

struct B {
    char a = 'a';
    short b = 1;
    int c = 2;
};

struct C {
    char a = 'a';
    short b = 1;
};

void testAlign() {
    std::cout << "alignof():" << std::endl;
    std::cout << alignof(A) << std::endl;
    std::cout << alignof(B) << std::endl;
    std::cout << alignof(C) << std::endl;
    std::cout << "sizeof():" << std::endl;
    std::cout << sizeof(A) << std::endl; //32
    std::cout << sizeof(B) << std::endl; // 8
    std::cout << sizeof(C) << std::endl; // 4
    std::cout << "sizeof(long) = " << sizeof(long) << std::endl;
}

}

#endif // ALIGN_H
