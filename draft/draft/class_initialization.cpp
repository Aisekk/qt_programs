#include "class_initialization.h"

namespace ClassFieldsInit {

A::A(int n, const Coords &coords, const String &s)
    : _num{n}
    , _coords{coords}
    , _stroka{s}
    , _stroka2{"stroka 2"} {

    std::cout << "A()" << std::endl;
    _stroka2 = "stroka 3";
}

A::~A() {
    std::cout << "~A()" << std::endl;
}

void test_init() {
    Coords c(1,1);
    String s = "stroka 1";
    std::cout << "Start A: " << std::endl;
    A a{1, c, s};
    std::cout << "End A: " << std::endl;
}

}
