#ifndef CONSTRUCTION_SEQ_H
#define CONSTRUCTION_SEQ_H

#include <iostream>

namespace ConstructionSeq {

class A {
public:
    A(){ std::cout << "A(): a = " << a << std::endl; a = 1; }
    A(const A& other) { std::cout << "A(const A& other)" << std::endl; a = other.a; }
    A& operator=(const A& other) { std::cout << "A& operator=(const A& other)" << std::endl; a = other.a; return *this; }
    ~A(){ std::cout << "~A()" << std::endl; }
private:
    int a;
};

class B {
public:
    B(){ std::cout << "B(): b = " << b << std::endl; b = 1; }
    B(const B& other) { std::cout << "B(const B& other)" << std::endl; b = other.b; }
    B& operator=(const B& other) { std::cout << "B& operator=(const B& other)" << std::endl; b = other.b; return *this; }
    ~B(){ std::cout << "~B()" << std::endl; }
private:
    int b;
};

class C : public A {
public:
    C(){ std::cout << "C(): c = " << c << std::endl; c = 1; }
    C(const C& other) { std::cout << "C(const C& other)" << std::endl; c = other.c; }
    C& operator=(const C& other) { std::cout << "C& operator=(const C& other)" << std::endl; c = other.c; return *this; }
    ~C(){ std::cout << "~C()" << std::endl; }
private:
    int c;
    B b;
};


void test() {
    C c; // A(), B(), C(), ~C(), ~B(), ~A()
}

}

#endif // CONSTRUCTION_SEQ_H
