#ifndef SIZEOF_H
#define SIZEOF_H

#include <iostream>
#include <cstddef>

namespace SizeOf {

class A {
public:
    A(){}
    //char ch = 'a';
    int n = 2;
};

class B : public virtual A {
public:
    virtual void func1() {}
    short s = 2;
    int i = 1;
    std::byte b;
    //char b;
};

void test() {
    std::cout << "sizeof(B) = " << sizeof(B) << std::endl;
}

}

#endif // SIZEOF_H
