#ifndef CPP_MEMORY_H
#define CPP_MEMORY_H

#include <iostream>
#include <string>
#include <typeinfo>

template <class T>
class Number {
    T* num;
public:
    Number(T n = T()) : num{new T{n}} {
        std::cout << "Number()" << std::endl;
    }
    ~Number() {
        delete num;
        std::cout << "~Number()" << std::endl;
    }

    T* get() const { return num; }
};

extern const Number<int> num_int;

namespace CppMemory {

void test();

void test_number_template();

void test_global_template();

}

#endif // CPP_MEMORY_H
