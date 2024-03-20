#ifndef MOVE_SEMANTICS_H
#define MOVE_SEMANTICS_H

#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

namespace MoveSemantics {

void std_string_move() {
    std::vector<std::string> letters;

    letters.push_back("abc");
    std::string s{"def"};
    letters.push_back(std::move(s));

    std::cout << "std::vector letters holds: ";
    for (auto&& e : letters)
        std::cout << std::quoted(e) << ' ';

    std::cout << "\nMoved-from string s holds: " << std::quoted(s) << '\n';
}

class A {
public:
    A(int a_ = 0) : a{a_}{ std::cout << "A(): a = " << a << std::endl; }
    A(const A& other) { a = other.a; std::cout << "A(const A& other): a = " << a << std::endl; }
    A& operator=(const A& other) { a = other.a; std::cout << "A& operator=(const A& other): a = " << a << std::endl; return *this; }
    A(A&& other) noexcept { a = other.a; other.a = -1; std::cout << "A(A&& other): a = " << a << std::endl; }
    A& operator=(A&& other) noexcept { a = other.a; other.a = -1; std::cout << "A& operator=(A&& other): a = " << a << std::endl; return *this; }
    ~A(){ std::cout << "~A(): a = " << a << std::endl; }
    int a;
};

void print_addrs(const std::vector<A>& v) {
    for (const auto& e : v) {
        std::cout << &e.a << ' ';
    }
    std::cout << std::endl;
}

void print_vals(const std::vector<A>& v) {
    for (const auto& e : v) {
        std::cout << e.a << ' ';
    }
    std::cout << std::endl;
}

void move_std_vector() {
    std::vector<A> v{A(), A(1), A(2)};
    print_addrs(v); print_vals(v);
    //auto copy = v; print_addrs(copy);
    std::vector<A>&& moved = std::move(v); print_addrs(moved); print_vals(moved);
}

class B {
public:
    B(int b_ = 0) : b{new int{b_}}{ std::cout << "B(): b = " << b << std::endl; }
    B(const B& other) {
        b = new int{*other.b};
        std::cout << "B(const B& other): b = " << b << std::endl;
    }
    B& operator=(const B& other) {
        delete b;
        b = new int{*other.b};
        std::cout << "B& operator=(const B& other): b = " << b << std::endl;
        return *this;
    }
    B(B&& other) noexcept
    {
        b = other.b; other.b = nullptr;
        std::cout << "B(B&& other): b = " << b << std::endl;
    }
    B& operator=(B&& other) noexcept
    {
        b = other.b; other.b = nullptr;
        std::cout << "B& operator=(B&& other): b = " << b << std::endl;
        return *this;
    }
    ~B(){ std::cout << "~B(): b = " << b << std::endl; delete b; }
    int* b = nullptr;
};

void print_addrs(const std::vector<B>& v) {
    for (auto&& e : v) {
        std::cout << e.b << ' ';
    }
    std::cout << std::endl;
}

void print_addrs(std::vector<B>&& v) {
    for (auto&& e : v) {
        std::cout << e.b << ' ';
    }
    std::cout << std::endl;
}

void print_vals(const std::vector<B>& v) {
    for (const auto& e : v) {
        std::cout << *e.b << ' ';
    }
    std::cout << std::endl;
}


void move_std_vector_elems() {
    std::vector<B> v;
    v.reserve(10);
    B b, b1{1}, b2{2};
    v.push_back(std::move(b));
    v.push_back(std::move(b1));
    v.push_back(std::move(b2));
    print_addrs(v); print_vals(v);
    //auto copy = v; print_addrs(copy);
    std::vector<B>&& moved = std::move(v); print_addrs(moved); //print_vals(moved);
}

}

#endif // MOVE_SEMANTICS_H
