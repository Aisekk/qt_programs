#include <iostream>

using namespace std;

struct C1
{
    void f()
    { cout << "not virtual C1::f()\n"; }
    virtual void g()
    { cout << "virtual C1::g()\n"; }
};
struct C2 : public C1
{
    void f()
    { cout << "not virtual C2::f()\n"; }
    void g()
    { cout << "virtual C2::g()\n"; }
};

void call_f(C1 &rC)
{
    rC.f();
    rC.g();
}

int main()
{
    C1 c1;
    C2 c2;
    call_f(c1);
    call_f(c2);

    cout << "\n";
    c1.f();
    c2.f();

    return 0;
}
