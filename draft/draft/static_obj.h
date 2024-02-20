#ifndef STATIC_OBJ_H
#define STATIC_OBJ_H

#include "object.h"
#include <iostream>

//static Object staticObject;

namespace Static {

class A {
public:
    A() {
        //std::cout << "Static A ctr" << std::endl;
    }
};

class C {
public:
    C(const int &v1, int id)
        : id(id)
        , ref(v1)
    {
        //this->id = id;
    }
    int x = 0;  // обычное поле
    inline static int sx = 0;  // статическое поле, проинициализированное прямо в классе
    static const int scx = 100;  // статическая константа
    static const double var;
    static A a;
    //const int id;
    const int id;
    const int &ref;
};

A C::a;
}

#endif // STATIC_OBJ_H
