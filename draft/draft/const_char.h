#ifndef CONST_CHAR_H
#define CONST_CHAR_H

#include <iostream>

void constness() {
    int value1{5};
    int value2{6};
    int* value3=&value1;
    std::cout<<"&value3="<<value3<<'\n';
    std::cout<<"&value1="<<&value1<<'\n';
    value3=&value2;
    std::cout<<"&value3="<<value3<<'\n';
    std::cout << "\nconst char* (char const*) -----------\n";
    const char* a{"stroka1"};
    //a[0] = 'e';
    const char* a1{"stroka2"};
    a = a1;
    std::cout << "a = " << a << '\n';
    a = "abcd";
    std::cout << "&a=" << &a <<'\n';
    a = "efg";
    std::cout << "&a=" << &a << '\n';
    std::cout << a;
    std::cout << "\nchar* const -----------\n";
    char* const b = (char* const)"stroka";
    //b = a;
    //char* const b = "stroka";
    //b[0] = 'w';
    //b = "str";
    std::cout << b << '\n';
    std::cout << "\nconst char c[]-----------\n";
    const char c[7] = "stroka";
    //c[0] = 'z';
    std::cout << c << '\n';
    std::cout << typeid ("stro").name() << '\n';
}

#endif // CONST_CHAR_H
