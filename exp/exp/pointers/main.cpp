#include <iostream>
#include <memory>
#include <vector>
#include "copy_ptr.h"
using namespace std;
typedef std::vector<copy_ptr<Base>> BaseVector;

class Data
{
    int m_data;
public:
    Data(int d = 0) : m_data(d){}
    int value(){ return m_data; }
};
typedef std::auto_ptr<Data> DataPtr;

DataPtr f()
{
    DataPtr dp_ret(new Data(1));
    return dp_ret;
}

class X
{
    DataPtr m_ptrData;
};

void clone()
{
    Data d1(2);
    Data *d1_clone = new_clone<Data>(d1);
    cout << endl;
    cout << "d1 value: " << d1.value() << endl;
    cout << "d1 clone value: " << d1_clone->value() << endl;
    delete_clone(d1_clone);
    cout << "d1 value: " << d1.value() << endl;
    cout << "d1 clone value: " << d1_clone->value() << endl;
    cout << endl;
}

int main()
{
    DataPtr dp = f();
    cout << "value: " << dp.get()->value() << endl;

    X x1, x2;
    x2 = x1;
    clone();

    BaseVector v;
    //v.push_back(copy_ptr(new Derived1()));

    return 0;
}
