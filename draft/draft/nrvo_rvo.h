#ifndef NRVO_RVO_H
#define NRVO_RVO_H

#include <iostream>
#include <string>

namespace RVO {

struct A {
    A(){ std::cout << "A()" << std::endl; }
    A(const A& other) { std::cout << "A(const A& other)" << std::endl; }
    A& operator=(const A& other) { std::cout << "A& operator=(const A& other)" << std::endl; return *this; }
    ~A(){ std::cout << "~A()" << std::endl; }
};
A nrvo() {
    A a;
    return a;
}
A rvo(){ return A(); }

struct S {
  constexpr S() {}
};

constexpr S rvo_() { return S(); }
constexpr S nrvo_() {
  S s;
  return s;
}

S global_rvo = rvo_();
S global_nrvo = nrvo_();

void test_NRVO_RVO() {
    std::cout << "Test NRVO" << std::endl;
    A a = nrvo();
    std::cout << "Test RVO" << std::endl;
    A a1 = rvo();
}

}

#endif // NRVO_RVO_H
