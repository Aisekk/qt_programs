#ifndef CPP_MEMORY_H
#define CPP_MEMORY_H

#include <iostream>
#include <string>
#include <typeinfo>

namespace CppMemory {

void test() {
    char szData[] = "abc";
    szData[0] = 'A';
    std::cout << szData << std::endl;
    const char *pszData = "abc";
    //pszData[0] = 'A'; // compile error
    std::cout << pszData << std::endl;
}

template <class T>
class Number {
    T* num;
public:
    Number(T n) : num{new T{n}} {
        std::cout << "Number()" << std::endl;
    }
    ~Number() {
        delete num;
        std::cout << "~Number()" << std::endl;
    }

    T* get() const { return num; }
};

void test_number_template() {
    Number<int> n1(1);
    Number<double> n2(2.0);
    Number<long long> n3(100);

    std::cout << *n1.get() << std::endl;
    std::cout << *n2.get() << std::endl;
    std::cout << *n3.get() << std::endl;
}

}

#endif // CPP_MEMORY_H
