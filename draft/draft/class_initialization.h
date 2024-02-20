#ifndef CLASS_INITIALIZATION_H
#define CLASS_INITIALIZATION_H

#include <string>
#include <iostream>
#include <cstring>

namespace ClassFieldsInit {

struct Coords {
    Coords(int x, int y) : x{x}, y{y} {
        std::cout << "Coords(): x = " << x << "; y = " << y << std::endl;
    }
    Coords(const Coords& other) {
        std::cout << "Coords(const Coords&) " << std::endl;
        x = other.x;
        y = other.y;
    }
    ~Coords() {
        std::cout << "~Coords()" << std::endl;
    }
    int x = 0;
    int y = 0;
};

class String {
public:
    String(const char* s = nullptr) {
        std::cout << "String(): " << s << std::endl;
        if (s != nullptr) {
            str = new char[std::strlen(s) + 1];
            strcpy(str, s);
            str[std::strlen(s)] = '\0';
        } else
            str = nullptr;
    }
    String(const String& other) {
        std::cout << "String(const String&): " << other.str << std::endl;
        if (str != other.str) {
            str = new char[std::strlen(other.str) + 1];
            strcpy(str, other.str);
            str[std::strlen(other.str)] = '\0';
        }
    }
    String& operator=(const String& other) {
        std::cout << "String& operator=(const String&): " << other.str << std::endl;
        if (str != other.str) {
            if (str != nullptr)
                delete [] str;
            str = new char[std::strlen(other.str) + 1];
            strcpy(str, other.str);
            str[std::strlen(other.str)] = '\0';
        }
        return *this;
    }
    ~String() {
        std::cout << "~String(): " << str << std::endl;
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

class A
{
public:
    A(int n, const Coords& coords, const String& s);
    ~A();
private:
    int _num = 0;
    Coords _coords;
    String _stroka;
    String _stroka2;
};

void test_init();

}

#endif // CLASS_INITIALIZATION_H
