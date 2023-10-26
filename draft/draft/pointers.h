#ifndef POINTERS_H
#define POINTERS_H

#include <QDebug>
#include <iostream>

namespace Pointers {

class A {
public:
    A (int n) : n1{n} {}
    int n1;
    int *n2 = &n1;
};

void test() {
    A *a = new A{5};
    //int *p = &a->n1;
    std::cout << a->n1 << std::endl;
    std::cout << a->n2 << std::endl;
    delete a;
}

}

#endif // POINTERS_H
