#ifndef LITERALS_H
#define LITERALS_H

#include <iostream>
#include <cstring>

namespace Literals {

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

void text_literals() {
    char const* lit = "some literal";
    std::cout << "lit = " << lit << '\n';
    lit = "new literal";
    std::cout << "lit = " << lit << '\n';
    const char* lit2 = "2nd literal";
    lit2 = lit;
    std::cout << "lit2 = " << lit2 << '\n';
    const char c[] = "c literal";
    std::cout << "c = " << c << '\n';
    char a[] = "a literal";
    std::cout << "a = " << a << '\n';

    char array[] = "stroka";
    array[4] = 'q';
    std::cout << "array = " << array << '\n';
    char* const arr = array;
    //arr = "new stroka";
}

class A {
public:
    A(const char* lit) : _lit{lit} {}
    const char* get_lit() const {
        return _lit;
    }
    void set_lit(const char* lit) {
        _lit = lit;
    }
private:
    const char* _lit;
};

class String {
  public:
    String(const char* s = nullptr) {
        str = new char[std::strlen(s) + 1];
        strcpy(str, s);
        str[std::strlen(s)] = '\0';
    }
    ~String() {
        delete [] str;
    }
    char* get() const {
        return str;
    }
    std::iostream& operator<<(std::iostream& io) {
        io << str;
        return io;
    }
private:
    char* str;
};

void class_literals() {
    A a{"obj lit"};
    std::cout << a.get_lit() << std::endl;
    a.set_lit("new obj lit");
    std::cout << a.get_lit() << std::endl;

    String str{"stroka"};
    std::cout << str.get() << std::endl;
    char* s = str.get();
    s[4] = 'q';
    std::cout << str.get() << std::endl;
}

}




#endif // LITERALS_H
