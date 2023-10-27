#ifndef SMART_PTRS_H
#define SMART_PTRS_H

#include <memory>
#include <iostream>

namespace SmartPtrs {

class A;
class B;

class A {
public:
    A(std::shared_ptr<B> sp = nullptr) : spb{sp} {}
    ~A() { std::cout << "~A(): spb.use_count() = " << spb.use_count() << std::endl; }
    void outUseCountB() { std::cout << "spb.use_count() = " << spb.use_count() << std::endl; }
    void setB(std::shared_ptr<B> sp) { spb = sp; }
    int getNum() const { return num; }
    void setNum(int n) { num = n; }
private:
    std::shared_ptr<B> spb;
    int num = 1;
};

class B {
public:
    B(std::shared_ptr<A> sp  = nullptr) : spa{sp} {}
    ~B() { std::cout << "~B(): spa.use_count() = " << spa.use_count() << std::endl; }
    void outUseCountA() { std::cout << "spa.use_count() = " << spa.use_count() << std::endl; }
    void setA(std::shared_ptr<A> sp) { spa = sp; }
    int getNum() const { return num; }
    void setNum(int n) { num = n; }
private:
    //std::weak_ptr<A> spa;
    std::shared_ptr<A> spa;
    int num = 2;
};

class C {
public:
    C(std::shared_ptr<A> spa = nullptr, std::shared_ptr<B> spb = nullptr) : spa{spa}, spb{spb} {}
    ~C() { std::cout << "~C(): spa.use_count() = " << spa.use_count() << "; spb.use_count() = " << spb.use_count() << std::endl; }
private:
    std::shared_ptr<A> spa;
    std::shared_ptr<B> spb;
};

void onStack() {
    std::cout << "on stack: " << std::endl;
    {
        A a(std::make_shared<B>());
    }
}

void test() {
    A *pa = nullptr;
    B *pb = nullptr;
    {
        auto spa = std::make_shared<A>();
        auto spb = std::make_shared<B>(spa);
        spa->setB(spb);
        pa = spa.get();
        pb = spb.get();
        std::cout << "spa.use_count() = " << spa.use_count() << "; spb.use_count() = " << spb.use_count() << std::endl;
        //C c{spa,spb};
    }
    pa->outUseCountB();
    pb->outUseCountA();
    std::cout << "delete pa;" << std::endl;
    delete pa;
    //delete pb;
    pa->outUseCountB();
    pb->outUseCountA();
//    std::cout << "pa->getNum() = " << pa->getNum() << "; pb->getNum() = " << pb->getNum() << std::endl;
//    pa->setNum(3);
//    pb->setNum(4);
//    std::cout << "pa->getNum() = " << pa->getNum() << "; pb->getNum() = " << pb->getNum() << std::endl;
    //onStack();
}

}

#endif // SMART_PTRS_H
