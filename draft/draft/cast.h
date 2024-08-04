#ifndef CAST_H
#define CAST_H

#include <iostream>
#include <vector>
#include <Qt>
#include <QDebug>

namespace Cast {

void boolCasting() {
    bool b = false;
    quint8 a1 = static_cast<quint8>(b);
    b = 230;//true;
    quint8 a2 = static_cast<quint8>(b);
    qDebug() << a1 << ' ' << a2;
    //std::cout << a1 << ' ' << a2 << std::endl;
}

class A {
public:
    int a = 1;
    virtual ~A() = default;
};

class B {
public:
    int b = 2;
    virtual ~B() = default;
};

class C : public A, public B {
public:
    int c = 3;
};

void test_cpp_cast() {
    C c;
    std::cout << "&c                   = " << &c << std::endl; // &c = &a
    //    std::cout << "&c + 4               = " << &c + 4 << std::endl; //
    //    std::cout << "&c + 8               = " << &c + 8 << std::endl; //
    //    std::cout << "&c + 12              = " << &c + 12 << std::endl; //
    // for cast up we need not virtual fun in base class
    std::cout << "dynamic_cast<A*>(&c) = " << dynamic_cast<A*>(&c) << std::endl; // &a
    std::cout << "dynamic_cast<B*>(&c) = " << dynamic_cast<B*>(&c) << std::endl; // &b
    std::cout << "static_cast<A*>(&c) = " << static_cast<A*>(&c) << std::endl; // &a
    std::cout << "static_cast<B*>(&c) = " << static_cast<B*>(&c) << std::endl; // &b

    //    std::cout << "dynamic_cast<A*>(&c)->a = " << dynamic_cast<A*>(&c)->a << std::endl; // 1
    //    std::cout << "dynamic_cast<B*>(&c)->b = " <<  dynamic_cast<B*>(&c)->b << std::endl; // 2
    //    std::cout << "static_cast<A*>(&c)->a = " <<  static_cast<A*>(&c)->a << std::endl; // 1
    //    std::cout << "static_cast<B*>(&c)->b = " <<  static_cast<B*>(&c)->b << std::endl; // 2

    A a;
    B b;
    B* pb = dynamic_cast<B*>(&c);
    // for cast down we need virtual fun in base class
    std::cout << "dynamic_cast<C*>(&a) = " << dynamic_cast<C*>(&a) << std::endl; // &a
    std::cout << "dynamic_cast<C*>(&b) = " << dynamic_cast<C*>(&b) << std::endl; // &b
    std::cout << "dynamic_cast<C*>(pb) = " << dynamic_cast<C*>(pb) << std::endl; // &c


    // compile error
    //    std::cout << "dynamic_cast<B*>(&a) = " << dynamic_cast<B*>(&a) << std::endl; // &a
    //    std::cout << "dynamic_cast<A*>(&b) = " <<  dynamic_cast<A*>(&b) << std::endl; // &b
    //    std::cout << "static_cast<B*>(&a) = " <<  static_cast<B*>(&a) << std::endl; // &a
    //    std::cout << "static_cast<A*>(&b) = " <<  static_cast<A*>(&b) << std::endl; // &b

    A a1 = static_cast<A>(c);
    B b1 = static_cast<B>(c);
    std::cout << "A a1 = static_cast<A>(c); &a1 = " << &a1 << std::endl; //
    std::cout << "B b1 = static_cast<B>(c); &b1 = " << &b1 << std::endl; //
    std::cout << "A a1 = static_cast<A>(c); a1.a = " << a1.a << std::endl; // 1
    std::cout << "B b1 = static_cast<B>(c); b1.b = " << b1.b << std::endl; // 2
}

void test_static_cast() {
    struct B
    {
        int m = 42;
        const char* hello() const
        {
            return "Hello world, this is B!\n";
        }
    };

    struct D : B
    {
        const char* hello() const
        {
            return "Hello world, this is D!\n";
        }
    };

    enum class E { ONE = 1, TWO, THREE };
    enum EU { ONE = 1, TWO, THREE };


    // 1. static downcast
    D d;
    B& br = d; // upcast via implicit conversion
    std::cout << "1) " << br.hello();
    D& another_d = static_cast<D&>(br); // downcast
    std::cout << "1) " << another_d.hello();

    // 2. lvalue to xvalue
    std::vector<int> v0{1,2,3};
    std::vector<int> v2 = static_cast<std::vector<int>&&>(v0);
    std::cout << "2) after move, v0.size() = " << v0.size() << '\n';

    // 3. initializing conversion
    int n = static_cast<int>(3.14);
    std::cout << "3) n = " << n << '\n';
    std::vector<int> v = static_cast<std::vector<int>>(10);
    std::cout << "3) v.size() = " << v.size() << '\n';

    // 4. discarded-value expression
    static_cast<void>(v2.size());

    // 5. inverse of implicit conversion
    void* nv = &n;
    int* ni = static_cast<int*>(nv);
    std::cout << "5) *ni = " << *ni << '\n';

    // 6. array-to-pointer followed by upcast
    D a[10];
    [[maybe_unused]]
            B* dp = static_cast<B*>(a);

    // 7. scoped enum to int
    E e = E::TWO;
    int two = static_cast<int>(e);
    std::cout << "7) " << two << '\n';

    // 8. int to enum, enum to another enum
    E e2 = static_cast<E>(two);
    [[maybe_unused]]
            EU eu = static_cast<EU>(e2);

    // 9. pointer to member upcast
    int D::*pm = &D::m;
    std::cout << "9) " << br.*static_cast<int B::*>(pm) << '\n';

    // 10. void* to any type
    void* voidp = &e;
    [[maybe_unused]]
            std::vector<int>* p = static_cast<std::vector<int>*>(voidp);
}

void test_dynamic_cast() {
    struct V
    {
        virtual void f() {} // must be polymorphic to use runtime-checked dynamic_cast
    };

    struct A : virtual V {};

    struct B : virtual V
    {
        B(V* v, A* a)
        {
            // casts during construction (see the call in the constructor of D below)
            auto b1 = dynamic_cast<B*>(v); // well-defined: v of type V*, V base of B, results in B*
            auto b2 = dynamic_cast<B*>(a); // undefined behavior: a has type A*, A not a base of B
            std::cout << "b1 = " << b1 << std::endl;
            std::cout << "b2 = " << b2 << std::endl; // == 0, since object B not created in D()
        }
    };

    struct D : A, B
    {
        D() : B(static_cast<A*>(this), this) {}
    };

    struct Base
    {
        virtual ~Base() {}
    };

    struct Derived : Base
    {
        virtual void name() {}
    };


    D d; // the most derived object
    A& a = d; // upcast, dynamic_cast may be used, but unnecessary

    std::cout << "&d = " << &d << std::endl;
    std::cout << "&a = " << &a << std::endl;

    [[maybe_unused]]
            D& new_d = dynamic_cast<D&>(a); // downcast
    [[maybe_unused]]
            B& new_b = dynamic_cast<B&>(a); // sidecast

    std::cout << "D& new_d = " << &new_d << std::endl;
    std::cout << "B& new_b = " << &new_b << std::endl;


    Base* b1 = new Base;
    if (Derived* d = dynamic_cast<Derived*>(b1); d != nullptr)
    {
        std::cout << "downcast from b1 to d successful\n";
        d->name(); // safe to call
    }

    Base* b2 = new Derived;
    if (Derived* d = dynamic_cast<Derived*>(b2); d != nullptr)
    {
        std::cout << "downcast from b2 to d successful\n";
        d->name(); // safe to call
    }

    delete b1;
    delete b2;
}

}


#endif // CAST_H
