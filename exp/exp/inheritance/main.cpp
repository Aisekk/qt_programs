#include <iostream>
#include <vector>
#include <string>
#include <type_traits>
#include <assert.h>
using namespace std;

class Base
{
protected:
    int m_base_foo;
public:
    Base() : m_base_foo{} {}
    virtual ~Base(){}

    int BaseFoo(){ return ++m_base_foo; }
    void func1(){ cout << "base func1: " << endl; }
    void func1(bool b){ cout << "base func1(bool): " << b << endl; }
};
class Derived : public Base
{
    int *m_pint;
public:
    using Base::func1;//first way

    Derived() : Base(), m_pint{} { m_pint = new int(); *m_pint = 999; }
    virtual ~Derived(){ delete m_pint; }

    int DerivedFoo(){ return ++m_base_foo; }
    void func1(){ cout << "derived func1: " << endl; }
    int func2(){ return 2; }
    int get_int() const{ return *m_pint; }
};
class BigData
{
    std::vector<bool> vec;
    ~BigData() {}
public:
    BigData() : vec(10,1) {}
    static void destroy(BigData* pobj){ delete pobj; cout << "destroyed BigData" << endl; }
    void collOut(){ for(auto e : vec) cout << ' ' << e; cout << endl; }
};
class Singleton
{
    Singleton(){}
    Singleton(const Singleton&){}// = delete;
    Singleton& operator=(const Singleton&){}// = delete;
    string name;
public:
    static Singleton& GetObject()
    {
        static Singleton onlyObj;
        return onlyObj;
    }
    string getName(){ return name; }
    void setName(const string& _name){ name = std::move(_name); }
};

int main()
{
    Base bas; Derived der;
    //---------------------------------------------------------------------------------------------
    cout << "BaseFoo: " << der.BaseFoo() << endl;
    cout << "DerivedFoo: " << der.DerivedFoo() << endl;
    cout << endl;
    //---------------------------------------------------------------------------------------------
    bas.func1(); bas.func1(true);
    der.func1(); der.func1(true);
    //der.func1(); der.Base::func1(true);//second way
    cout << endl;
    //---------------------------------------------------------------------------------------------
    cout << "static_cast<>(): " << endl;
    Base *pBase = new Base();
    Derived *pDerived = static_cast<Derived*>(pBase);
    Derived& derived = *pDerived;
    cout << "pBase after downcast to pDerived: " << pDerived->DerivedFoo() << endl;
    cout << "pBase after downcast to pDerived: " << pDerived->func2() << endl;
    cout << "after &derived = *pDerived: " << derived.func2() << endl;

    int num{};
    try{ num = 10; /* pDerived->get_int(); */ }
    catch(const exception& e){ cout << "EXCEPTION: " << e.what() << "(runtime error)" << endl; }
    catch(...){ cout << "EXCEPTION: unknown " << endl; }

    cout << "pBase after downcast to pDerived: " << num << endl;//runtime error
    cout << endl;
    //---------------------------------------------------------------------------------------------
    cout << "dynamic_cast<>(): " << endl;
    Derived *pDerived2 = dynamic_cast<Derived*>(pBase);
    if(pDerived2)
        cout << "pBase downcast to pDerived2 successful: " << pDerived2->get_int() << endl;
    else cout << "pBase downcast to pDerived2 failed: " << endl;

    Base& refBase = bas;
    Derived& refDerived2 = derived;
    try{ refDerived2 = dynamic_cast<Derived&>(refBase); }
    catch(const exception& e){ cout << "EXCEPTION: " << e.what() << " (runtime error) " << endl; }
    catch(...){ cout << "EXCEPTION: unknown " << endl; }

//    if(is_reference<decltype(refDerived2)>::value)
//        cout << "refBase downcast to refDerived2 successful: " << refDerived2.get_int() << endl;
//    else cout << "refBase downcast to refDerived2 failed: " << endl;
    //---------------------------------------------------------------------------------------------
    cout << "assert macros: " << endl;
    Base *pbase{};
    assert(pbase == nullptr);
    //---------------------------------------------------------------------------------------------
    cout << endl << "big data: " << endl;
    //BigData bd;//запрещено создание в стеке
    BigData *bd = new BigData();
    bd->collOut();
    BigData::destroy(bd);
    //---------------------------------------------------------------------------------------------
    cout << endl << "singleton: " << endl;
    Singleton& onlyObj = Singleton::GetObject();
    onlyObj.setName("Single");
    cout << "Name: " << onlyObj.getName() << endl;
    //---------------------------------------------------------------------------------------------

    //---------------------------------------------------------------------------------------------
    system("pause");
    return 0;
}
