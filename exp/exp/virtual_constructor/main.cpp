#include <iostream>
#include <vector>
using namespace std;

struct Base
{
    virtual Base* clone() const
    {
        return new Base(*this);
    }
    virtual ~Base(){}
};

struct Derived : Base
{
    virtual Derived* clone() const
    {
        return new Derived(*this);
    }
};

void createNCopies(const Base& rcBase, int nCopies, std::vector<Base*>& rV)
{
    for(int i = 0; i < nCopies; ++i)
        rV.push_back(rcBase.clone());
}

int main()
{
    Base b;
    Derived d;

    //Base *pBase = b.clone();
    //Derived *pDerived = d.clone();

    std::vector<Base*> vecpBase;
    createNCopies(b, 3, vecpBase);

    for(auto p : vecpBase)
        cout << p << endl;
    return 0;
}
