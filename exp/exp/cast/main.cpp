#include <iostream>
#include <typeinfo>
using namespace std;

struct Base{};
struct Derived : public Base { int m_n; };

// преобразование поперек иерархии
struct Base1
{
    virtual ~Base1(){} // полиморфность
};
struct Base2
{
    void f(){ cout << "Base2::f()" <<endl; }
};
struct Derived1 : public Base1, public Base2 {};
struct Derived2 : public Base2, public Base1 {};

void f(Base1 *pBase1)
{
    if(typeid(*pBase1) == typeid(Derived1))
        cout << "Derived1 pointer" << endl;
    else if(typeid(*pBase1) == typeid(Derived2))
        cout << "Derived2 pointer" << endl;
    //
    Base2 *pBase2 = dynamic_cast<Base2*>(pBase1);
    // ...
    if(pBase2)
        pBase2->f();
}


int main()
{
    // преобразование вниз по иерархии
    Base base;
    Derived derived;
    derived.m_n = 1;

    Base& rDerived = derived; // всегда безопасно
    //Derived& rD = rDerived; // ошибка компиляции
    Derived& rD1 = static_cast<Derived&>(rDerived); // здесь безопасно
    Derived& rD2 = static_cast<Derived&>(base); // опасно

    cout << rD1.m_n << endl; // "1"
    cout << rD2.m_n << endl; // неопределенное поведение


    Derived1 d1;
    Derived2 d2;
    f(&d1);
    f(&d2);

    return 0;
}
