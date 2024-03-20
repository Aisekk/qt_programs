#ifndef WEAK_PTR_USE_H
#define WEAK_PTR_USE_H

#include <iostream>
#include <memory>
#include <thread>

namespace WeakPtrUse {

void dangling_ptr_problem() {
    // OLD, problem with dangling pointer
    // PROBLEM: ref will point to undefined data!

    int* ptr = new int(10);
    int* ref = ptr;
    delete ptr;

    // NEW
    // SOLUTION: check expired() or lock() to determine if pointer is valid

    // empty definition
    std::shared_ptr<int> sptr;

    // takes ownership of pointer
    sptr.reset(new int);
    *sptr = 10;

    // get pointer to data without taking ownership
    std::weak_ptr<int> weak1 = sptr;

    // deletes managed object, acquires new pointer
    sptr.reset(new int);
    *sptr = 5;

    // get pointer to new data without taking ownership
    std::weak_ptr<int> weak2 = sptr;

    // weak1 is expired!
    if(auto tmp = weak1.lock())
        std::cout << "weak1 value is " << *tmp << '\n';
    else
        std::cout << "weak1 is expired\n";

    // weak2 points to new data (5)
    if(auto tmp = weak2.lock())
        std::cout << "weak2 value is " << *tmp << '\n';
    else
        std::cout << "weak2 is expired\n";
}

class B;

class A {
public:
    //std::shared_ptr<B> bptr;
    std::weak_ptr<B> bptr;
    A() { std::cout << "A()" << std::endl; }
    ~A() { std::cout << "~A()" << std::endl; }
};

class B {
public:
    //std::shared_ptr<A> aptr;
    std::weak_ptr<A> aptr;
    B() { std::cout << "B()" << std::endl; }
    ~B() { std::cout << "~B()" << std::endl; }
};

void shared_ptr_mem_leak() {
    A* pa{};
    B* pb{};
    {
        std::shared_ptr<A> a = std::make_shared<A>();
        std::shared_ptr<B> b = std::make_shared<B>();
        a->bptr = b;
        b->aptr = a;
        std::cout << a.use_count() << std::endl;
        std::cout << b.use_count() << std::endl;
        pa = a.get();
        pb = b.get();
    }
    // put breakpoint here

    // if weak_ptr used
    std::cout << pa->bptr.use_count() << std::endl;
    std::cout << pb->aptr.use_count() << std::endl;
    std::cout << pa->bptr.expired() << std::endl;
    std::cout << pb->aptr.expired() << std::endl;

    // if shared_ptr used
    //std::cout << pa->bptr.use_count() << std::endl;
    //std::cout << pb->aptr.use_count() << std::endl;
    //delete pb;
}

std::shared_ptr<int> g_s = std::make_shared<int>(1);
void f1()
{
    std::shared_ptr<int> l_s1 = g_s; // read g_s
}
void f2()
{
    std::weak_ptr<int> wp = g_s;
    //while (wp.expired()) {
         std::cout << g_s.use_count() << std::endl;
    //}
}

void shared_ptr_no_thread_safe()
{
    std::thread th2(f2);

    std::shared_ptr<int> l_s2 = std::make_shared<int>(3);
    std::thread th1(f1);
    th1.detach();
    th2.detach();
    g_s = l_s2; // write g_s
}

}

#endif // WEAK_PTR_USE_H
