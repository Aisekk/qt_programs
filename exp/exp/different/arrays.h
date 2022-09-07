#ifndef ARRAYS_H
#define ARRAYS_H
#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <cctype>
#include <iomanip>
#include <string>
#include <functional>
#include <exception>
#include <stdexcept>
#include <memory>
#include "mystring.h"

int global = 1;
static int sglobal = 2;

void outputStroki(const char** strs, int N)
{
    for(int i = 0; i < N; ++i)
        std::cout << strs[i] << std::endl;
}

void useOutputStroki()
{
    const char* lampa = "lampa";
    const char* okno = "okno";
    const char* chelovek = "chelovek";
    constexpr int N = 3;
    const char* stroki[N]; //{ lampa, okno, chelovek };
    stroki[0] = lampa;
    stroki[1] = okno;
    stroki[2] = chelovek;
    outputStroki(stroki, N);
}

void transformMap()
{
    std::vector<int> ints;
    std::vector<std::string> stroki;
    std::map<int, std::string> map = { {0,"null"}, {1,"first"}, {2,"second"} };
    std::transform(map.cbegin(), map.cend(), std::back_inserter(ints), [](const std::map<int, std::string>::value_type& val) { return val.first; });
    std::transform(map.cbegin(), map.cend(), std::back_inserter(stroki), [](const std::map<int, std::string>::value_type& val) { return val.second; });

    std::for_each(ints.cbegin(), ints.cend(), [](const int& val){ std::cout << val << " " << std::endl; });
    std::for_each(stroki.cbegin(), stroki.cend(), [](const std::string& val){ std::cout << val << " " << std::endl; });
}

void transformStroka()
{
    std::string s{"hello"};
    std::transform(s.cbegin(), s.cend(),
                   s.begin(), // write to the same location
                   [](unsigned char c) { return std::toupper(c); });
    std::cout << "s = " << s << '\n';

    // achieving the same with std::for_each (see Notes above)
    std::string g{"hello"};
    std::for_each(g.begin(), g.end(), [](char& c) { // modify in-place
        c = std::toupper(static_cast<unsigned char>(c));
    });
    std::cout << "g = " << g << '\n';

    std::vector<std::size_t> ordinals;
    std::transform(s.cbegin(), s.cend(), std::back_inserter(ordinals),
                   [](unsigned char c) { return c; });

    std::cout << "ordinals: ";
    for (auto ord : ordinals) {
        std::cout << ord << ' ';
    }

    std::transform(ordinals.cbegin(), ordinals.cend(), ordinals.cbegin(),
                   ordinals.begin(), std::plus<std::size_t>{});

    std::cout << "\nordinals: ";
    for (auto ord : ordinals) {
        std::cout << ord << ' ';
    }
}

// whether foo is declared noexcept depends on if the expression
// T() will throw any exceptions
template<class T>
void foo() noexcept(noexcept(T())) {}

void bar() noexcept(true) {}
void baz() noexcept { throw 42; } // noexcept is the same as noexcept(true)

void useNoexcept()
{
    foo<int>(); // noexcept(noexcept(int())) => noexcept(true), so this is fine

    bar(); // fine
    baz(); // compiles, but at runtime this calls std::terminate
}

void divisionByZero()
{
    int a =3;
    int b = 0;
    int c = - 1;
    try
    {
        // деление на ноль - это неопределенное поведение
        if(b == 0)
            throw std::runtime_error("Division by zero");
        c = a / b;
    }
    catch (const std::exception& e)
    {
        std::cout << e.what() << std::endl;
        //std::cout << "divide by zero !" << std::endl;
    }
    std::cout << "c = " << c << std::endl;
}

namespace Exp
{
class A
{
public:
    int i = 1;
};
class B : public A
{
public:
    int j = 2;
};

void func(A a)
{
    std::cout << "a.i = " << a.i << std::endl;
    //std::cout << "b.j = " << b.j << std::endl;
}
void passDerivedClassByValueToFuncTakeBaseClass()
{
    B b;
    b.i = 3;
    func(b);
}
}

void output()
{
    String a("stroka");
    std::cout << a << std::endl;
    String b(a);
    std::cout << b << std::endl;
    String c("telega");
    c = b;
    std::cout << c << std::endl;
}

void Std_strcopy_Test()
{
    const char* src = "Take the test.";
    //  src[0] = 'M'; // can't modify string literal
    //auto dst = std::make_unique<char[]>(std::strlen(src)+1); // +1 for the null terminator
    std::unique_ptr<char[]> dst(new char[std::strlen(src)+1]);
    std::strcpy(dst.get(), src);
    dst[0] = 'M';
    std::cout << src << '\n' << dst.get() << '\n';
}

#endif // ARRAYS_H
