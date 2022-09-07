#include <iostream>
#include <string>
#include <exception>
#include <memory>
#include <vector>
//#include <boost/scoped_ptr.hpp>
using namespace std;

class Y
{
  int m_n; public: Y(int n = 0) : m_n(n){}
};
class Data1
{
    int m_n;
public:
    Data1(int n = 0) : m_n(n) {}
    int data() const { return m_n; }
};
class Derived1 : public Data1
{
public:
    Derived1(int n = 0) : Data1(n) {}
};
class Derived2 : public Data1
{
public:
    Derived2(int n = 0) : Data1(n) {}
};

class Data2 { double m_n; public: Data2(double n = 0.0) : m_n(n){} };

// определение boost::scoped_ptr
template <class T> class scoped_pointer
{
    T *px;
public:
    explicit scoped_pointer(T *p = nullptr) : px(p){}
    ~scoped_pointer()
    {
        delete px; px = nullptr;
        cout << "scoped_pointer destroyed" << endl;
    }
    T &operator * () const { return *px; }
    T *operator -> () const { return px; }
    T *get() const { return px; }
    operator bool () const { return px != nullptr; }
    bool operator !() const { return px == nullptr; }
    void release()
    {
        delete px; px = nullptr;
        cout << "scoped_pointer released" << endl;
    }
};

class Data3
{
    int m_n;
    Y *m_pY;
    Data2 *m_pData2;
public:
    Data3(int n = 0)
        : m_n(n), m_pY(nullptr), m_pData2(nullptr) {}

    Data3(Y *pY, Data2 *pData2)
        : m_n(0), m_pY(pY), m_pData2(pData2) {}
};
class Data4
{
    Y *m_pY;
    const scoped_pointer<Data2> m_cspData2;
public:
    Data4(Y *pY, const scoped_pointer<Data2>& cspData2)
        : m_pY(pY), m_cspData2(cspData2){}
};
//-------------------------------------------------------------------------------------------------
// задача управления ресурсами
class X : public Y
{
private:
    std::string m_Name;
    Data1 *m_pData1;
    Data2 *m_pData2;
    Data3 *m_pData3;
    void clear();
    double func(int n);
public:
    X(const std::string& rcName, int n = 0);
    ~X();
    std::string& name();
};
X::~X()
{
    clear();
}
void X::clear()
{
    delete m_pData3;
    delete m_pData2;
    delete m_pData1;
}
double X::func(int n)
{
    throw std::bad_alloc();
    return (double)n;
}
std::string& X::name()
{
    return m_Name;
}
X::X(const std::string& rcName, int n)
    : m_Name(rcName),
      m_pData1(nullptr),
      m_pData2(nullptr),
      m_pData3(nullptr)
{
    try
    {
        m_pData1 = new Data1(n);
        m_pData2 = new Data2(func(n));
        m_pData3 = new Data3(this, m_pData2); // Data3(Y*,Data2*)
        //throw std::bad_alloc();
    }
    catch(...)
    {
        cout << "X::std::bad_alloc catched" << endl;
        clear();
        //throw;
    }
}
//-------------------------------------------------------------------------------------------------
// задача управления ресурсами: константные указатели и функциональный блок try в конструкторе
class Z : public Y
{
private:
    std::string m_Name;
    Data1 *const m_cpData1;
    Data2 *const m_cpData2;
    Data3 *const m_cpData3;
    void clear();
    double func(int n);
public:
    Z(const std::string& rcName, int n = 0);
    ~Z();
    std::string& name();
};
Z::~Z()
{
    clear();
}
void Z::clear()
{
    delete m_cpData3;
    delete m_cpData2;
    delete m_cpData1;
}
double Z::func(int n)
{
    throw std::bad_alloc();
    return (double)n;
}
std::string& Z::name()
{
    return m_Name;
}
Z::Z(const std::string& rcName, int n)
try
    : m_Name(rcName),
    m_cpData1(new Data1(n)),
    m_cpData2(new Data2(func(n))),
    m_cpData3(new Data3(this, m_cpData2))
{}
catch(...)
{
cout << "Z::std::bad_alloc catched" << endl;
clear();
//throw;
}
//-------------------------------------------------------------------------------------------------
// для boost::scoped_ptr:
void f(Data1& rData1)
{
    cout << "data: " << rData1.data() <<endl;
}
void g(Data1 *pData1)
{
    cout << "*  : " << pData1 <<endl;
}
// определение boost::scoped_arr
template <class T> class scoped_arr
{
    T *px;
public:
    explicit scoped_arr(T *p = nullptr) : px(p){}
    ~scoped_arr(){ delete[] px; }
    T &operator [] (std::ptrdiff_t i) const { return px[i]; }
    T *get() const { return px; }
    operator bool () const { return px != nullptr; }
    bool operator !() const { return px == nullptr; }
    void release(){ delete[] px; px = nullptr; }
};
void scoped_pointer_use()
{
    // использование scoped_pointer
    cout << endl << "scoped pointers use: " << endl;
    scoped_pointer<Data1> ptr(new Data1(2));
    f(*ptr);
    cout << "-> : " << ptr->data() << endl;
    g(ptr.get());
    if(ptr){ cout << "ptr not nullptr" << endl; }
    ptr.release();
    if(!ptr){ cout << "ptr is nullptr" << endl; }
    // использование scoped_arr
    scoped_arr<char> ptr2(new char[100]);
    ptr2[10] = 'A';
    cout << "elem: " << ptr2[10] << endl;
}
//-------------------------------------------------------------------------------------------------
// решение задачи управления ресурсами с помощью интеллектуального указателя
class R : public Y
{
private:
    std::string m_Name;
    const scoped_pointer<Data1> m_cPData1;
    const scoped_pointer<Data2> m_cPData2;
    const scoped_pointer<Data4> m_cPData4;
    double func(int n);
public:
    R(const std::string& rcName, int n = 0);
    ~R();
    std::string& name();
};
R::~R()
{
    cout << "obj R destroyed" << endl;
}
double R::func(int n)
{
    //throw std::bad_alloc();
    return (double)n;
}
std::string& R::name()
{
    return m_Name;
}
R::R(const std::string& rcName, int n)
    : m_Name(rcName),
    m_cPData1(new Data1(n)),
    m_cPData2(new Data2(func(n))),
    m_cPData4(new Data4(this, m_cPData2))
{
    cout << "obj R constructed" << endl;
}
void resource_management_with_scoped_pointers()
{
    cout << endl << "resource management with scoped pointers: " << endl;
    try
    {
        R r("objR");
    }
    catch(...)
    {
        cout << "R::std::bad_alloc catched" << endl;
    }
}
//-------------------------------------------------------------------------------------------------
// копирование интеллектуальных указателей
void scoped_pointers_copying()
{
    cout << endl << "scoped pointers copying: " << endl;
    scoped_pointer<Data1> sp_data1(new Data1(4));
    scoped_pointer<Data1> sp_data2(new Data1(5));
    cout << "initial data: " << sp_data1->data() << ' ' << sp_data2->data() << endl;

    sp_data1 = sp_data2; // ?
    cout << "copying operator: " << sp_data1->data() << ' ' << sp_data2->data() << endl;

    scoped_pointer<Data1> sp_data3(sp_data2); // ?
    cout << "copying constructor: " << sp_data2->data() << ' ' << sp_data3->data() << endl;
}
//-------------------------------------------------------------------------------------------------
// определение std::auto_ptr C++98
template <class T> class auto_pointer
{
private:
    T *px;
public:
    explicit auto_pointer(T *p = nullptr) : px(p)
    {
        //cout << "auto_pointer constructed" << endl;
    }
    ~auto_pointer()
    {
        delete px; px = nullptr;
        //cout << "auto_pointer destroyed" << endl;
    }
    T &operator * () const { return *px; }
    T *operator -> () const { return px; }
    T *get() const { return px; }
    operator bool () const { return px != nullptr; }
    bool operator !() const { return px == nullptr; }

    T* release() throw()
    {
        T *pTmp = px;
        px = nullptr;
        return pTmp;
    }
    void reset(T *py)
    {
        px = py;
        //delete py;
        py = nullptr;
    }

    auto_pointer(auto_pointer& rPtr) throw()
        : px(rPtr.release()) {}
    template<typename T1> auto_pointer(auto_pointer<T1>& rPtr) throw()
        : px(rPtr.release()) {}
    auto_pointer &operator = (auto_pointer& rPtr) throw()
    {
        reset(rPtr.release());
        return *this;
    }
};
void use_homemade_auto_pointer_Cpp98()
{
    cout << endl << "use homemade auto_ptr C++98: " << endl;
    auto_pointer<Data1> ap1(new Data1(7));
    auto_pointer<Data1> ap2(new Data1(8));
    cout << "initial data: " << ap1->data() << ' ' << ap2->data() << endl;
    ap1 = ap2;
    cout << "copying operator: ";
    if(ap1) cout << ap1->data() << ' ';
    if(ap2) cout << ap2->data() << ' ';
    cout << endl;
}
//-------------------------------------------------------------------------------------------------
// использование std::auto_ptr C++98
typedef Data1 Base;
void f_ap(std::auto_ptr<Base> ap)
{
    cout << "auto_ptr after copying - data: " << ap->data() << endl;
}
void use_auto_ptr_Cpp98()
{
    cout << endl << "use auto_ptr C++98: " << endl;
    auto_ptr<Data1> ap1(new Data1(7));
    auto_ptr<Data1> ap2(new Data1(8));
    cout << "initial data: " << ap1->data() << ' ' << ap2->data() << endl;
    ap1 = ap2;
    cout << "copying operator: ";
    if(ap1.get() != NULL) cout << ap1->data() << ' ';
    if(ap2.get() != NULL) cout << ap2->data() << ' ';
    cout << endl;


    auto_ptr<Base> pb(new Derived1(7));
    auto_ptr<Derived2> pd(new Derived2(6));
    pb = pd; // auto_ptr<Derived2> --> auto_ptr<Base>
             // Derived2* --> Base*
    cout << "copying operator from derived to base: ";
    if(pb.get() != NULL) cout << pb->data() << ' ';
    if(pd.get() != NULL) cout << pd->data() << ' ';
    cout << endl;

    auto_ptr<Base> pb1(new Derived1(5));
    f_ap(pb1);
    const auto_ptr<Base> cpb(new Derived1);
    //f_ap(cpb); // ошибка компиляции
}
// использование std::auto_ptr C++98 с контейнерами
void use_auto_ptr_with_containers()
{
    typedef std::vector<std::auto_ptr<Base>> BaseVector;
    BaseVector v;
    std::auto_ptr<Base> ap_base(new Base);
    //v.push_back(ap_base); // ошибка компиляции, т.к. нет vector(T )
}
//-------------------------------------------------------------------------------------------------
// использование std::unique_ptr C++98 с контейнерами
void use_unique_ptr_with_containers()
{
    typedef std::vector<std::unique_ptr<Base>> BaseVector;
    BaseVector v;
    std::unique_ptr<Base> up_base(new Base);
    v.push_back(std::move(up_base)); // нет ошибки компиляции, т.к. vector(T&& )
}
//-------------------------------------------------------------------------------------------------
int main()
{
    X x("objX");
    try
    {
        Z z("objZ");
        cout << z.name() << endl;
    }
    //catch(const std::bad_alloc&) //
    catch(...)
    {
        cout << "Z::std::bad_alloc catched second" << endl;
    }
    //cout << x.name() << endl;

    // использование scoped_pointer
    scoped_pointer_use();
    // решение задачи управления ресурсами с помощью scoped_pointer
    resource_management_with_scoped_pointers();
    // копирование интеллектуальных указателей
    scoped_pointers_copying();
    // использование самодельного auto_ptr C++98
    use_homemade_auto_pointer_Cpp98();
    // использование auto_ptr C++98
    use_auto_ptr_Cpp98();
    // использование std::auto_ptr C++98 с контейнерами
    use_auto_ptr_with_containers();
    // использование std::unique_ptr C++98 с контейнерами
    use_unique_ptr_with_containers();

    return 0;
}
