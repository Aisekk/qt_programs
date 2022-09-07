#include <iostream>
using namespace std;

class Base
{
    int mem;
public:
    Base() : mem(0)
    {
        cout << "Base obj created: " << endl;
        cout << "its virtual func call: "; vfunc();
    }
    virtual ~Base(){ cout << "Base obj destroyed " << endl; }
    void func(){ cout << "it is Base func " << endl; }
    virtual void vfunc(){ cout << "it is Base vfunc " << endl; }
    virtual void vfunc2(){ cout << "it is Base vfunc2 " << endl; }
};
class Derived : public Base
{
public:
    Derived() : Base()
    {
        cout << "Derived obj created: " << endl;
        cout << "its virtual func call: "; vfunc();
    }
    ~Derived(){ cout << "Derived obj destroyed " << endl; }
    void func(){ cout << "it is Derived func " << endl; }
    virtual void vfunc(){ cout << "it is Derived vfunc " << endl; }
    virtual void vfunc2(){ cout << "it is Derived vfunc2 " << endl; }
};


int main()
{
    Base b;
    cout << "Base: " << endl;
    cout << "non virtual func: "; b.func();
    cout << "virtual vfunc: "; b.vfunc();
    cout << "virtual vfunc2: "; b.vfunc2();
    cout << "sizeof Base obj: " << sizeof(b) << endl;
    cout << endl;

    Derived d;
    cout << "Derived: " << endl;
    cout << "non virtual func: "; d.func();
    cout << "virtual vfunc: "; d.vfunc();
    cout << "virtual vfunc2: "; d.vfunc2();
    cout << "sizeof Derived obj: " << sizeof(d) << endl;
    cout << endl;

    cout << endl << "Polymorfism: " << endl;
    Base* pBase = new Derived;
    cout << "pBase = new Derived obj: " << endl;
    cout << "non virtual func: "; pBase->func();
    cout << "virtual vfunc: "; pBase->vfunc();
    cout << "virtual vfunc2: "; pBase->vfunc2();
    cout << "sizeof pBase = new Derived obj: " << sizeof(*pBase) << endl;
    cout << endl;
    delete pBase;

    system("pause");
    return 0;
}
