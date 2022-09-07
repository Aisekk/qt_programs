#include <iostream>
#include <vector>
#include <algorithm>
#include <new>
using namespace std;

void autoData_constData()
{
    // автоматические данные
    char szData[] = "abc";
    cout << szData << ' ';
    szData[0] = 'A';
    cout << szData << endl;

    // константные данные
    char *pszData = "abc";
    cout << pszData << ' ';
    //pszData[0] = 'A';
    cout << pszData << endl;
}
class Data
{
    int m_num;
public:
    Data(int num = 0) : m_num(num) {}
};
void heap_freestore()
{
    // сравнение кучи и свободной памяти
    // куча - размещение объекта
    Data *pData = reinterpret_cast<Data*>(std::malloc(sizeof(Data)));
    // куча - размещение массива объектов
    Data *pArray = reinterpret_cast<Data*>(std::calloc(9, sizeof(Data)));
    // удаление объекта
    std::free(pData);
    // удаление массива объектов
    std::free(pArray);

    // свободная память - размещение объекта
    Data *pData_2 = new Data;
    // свободная память - размещение массива объектов
    Data *pArray_2 = new Data[9];
    // свободная память - удаление объекта
    delete pData_2;
    // свободная память - удаление массива объектов
    delete [] pArray_2;
}
//-------------------------------------------------------------------------------------------------
// удаление полиморфных объектов
class Screen{};
class Shape
{
public:
    Shape(){ cout << " shape created " << endl; }
    virtual ~Shape(){ cout << " shape deleted " << endl; }
    virtual void draw(Screen& ) = 0;
    void destroy(){ delete this; cout << " shape destroyed " << endl; }
};
class Rectangle : public Shape
{
public:
    virtual void draw(Screen& ){}
};
typedef std::vector<Shape*> Shapes;
void deleteShape(Shape *pShape)
{
    delete pShape;
}
void deleteShapes(Shapes& rShapes)
{
    std::for_each(rShapes.begin(), rShapes.end(), deleteShape);
}
void destroyShapes(Shapes& rShapes)
{
    std::for_each(rShapes.begin(), rShapes.end(), std::mem_fun(&Shape::destroy));
}
//-------------------------------------------------------------------------------------------------
// стратегия владения объекта классом
class Owner
{
public:
    Owner();
    Owner(const Owner& );
    ~Owner();
    Owner& operator = (const Owner&);
private:
    Data *m_pData;
    void deleteData();
};
Owner::Owner() : m_pData(nullptr){ cout << " owner created " << endl; }
Owner::~Owner(){ deleteData(); cout << " owner deleted " << endl; }
void Owner::deleteData()
{
    delete m_pData;
    m_pData = nullptr;
}
//-------------------------------------------------------------------------------------------------
// функции выделения/освобождения памяти с размещением
void *operator new(std::size_t nSize, char ch)
{
    cout << "place " + ch << endl;
    return std::malloc(nSize);
}
void operator delete(void *pvData, char ch)
{
    cout << "delete place " + ch << endl;
    std::free(pvData);
}
void operator delete(void *pvData)
{
    //cout << "not place " << endl;
    std::free(pvData);
}
void placement()
{
    cout << "placement new(): " << endl;
    Data *pData = new('a') Data;
    delete pData;//('!');
}
//-------------------------------------------------------------------------------------------------
// пример использования delete[] - удаление массива
void deleteArray()
{
    //typedef char Str[100];
    char *szName = new char[100];
    //Str szName = new Str; // то же, что и "new char[100]"
    szName[0] = 'a';
    cout << endl << "delete array: " << szName << endl;
    delete [] szName;
}
//-------------------------------------------------------------------------------------------------
// пример вызова метода освобождения памяти
struct Base
{
    virtual ~Base(){}
    void operator delete(void*, size_t){ cout << "operator delete in base class" << endl; }
};
struct Derived : public Base
{
    void operator delete(void*){ cout << "operator delete in derived class" << endl; }
};
void delete_method()
{
    //cout << endl;
    Base *pBase = new Derived;
    delete pBase; // Derived::operator delete()
}
//-------------------------------------------------------------------------------------------------
// выделение памяти без исключения
void memory_allocation_without_exception()
{
    //char *pchData = new char[100000000000];
    char *pchData = new(std::nothrow) char[100000000000];
    if(pchData != nullptr)
    {
        cout << "memory allocation successful" << endl;
        delete [] pchData;
    }
}
//-------------------------------------------------------------------------------------------------
// размещение объекта в уже выделенной памяти
void object_placement_in_alloc_mem()
{
    char *pchData = reinterpret_cast<char*>(std::malloc(10000));
    Shape *pShape = new(pchData) Rectangle;
    pShape->~Shape();
    std::free(pchData);
    cout << endl;
}
// размещение/освобождение объекта в шаблоне
template <class T> T *new_alloc()
{
    const int SOME_BIG_SIZE = 1E5;
    char *pchData = reinterpret_cast<char*>(std::malloc(SOME_BIG_SIZE));
    return new(pchData) T();
}
template <class T> void delete_alloc(T *pT)
{
    pT->~T(); // при T == int ?
    std::free(pT);
}
void object_placement_in_alloc_mem_in_template()
{
    Shape *pShape = new_alloc<Rectangle>();
    int *pn = new_alloc<int>();
    // ...
    *pn = 5;
    cout << "int in template: " << *pn << endl;

    delete_alloc(pn);
    delete_alloc(pShape);
    cout << endl;
}
//-------------------------------------------------------------------------------------------------
int main()
{
    autoData_constData();
    heap_freestore();

    Shapes shapes;
    // удаление полиморфных объектов
    for(int i = 0; i < 3; ++i)
        shapes.push_back(new Rectangle);
    deleteShapes(shapes);

    // стратегия владения объекта классом
    //cout << endl;
    //Owner owner;

    // проблема полиморфных объектов
    cout << endl;
    Shapes s;
    for(int i = 0; i < 3; ++i)
        s.push_back(new Rectangle);
    Rectangle r;
    s.push_back(&r); // !
    deleteShapes(s); // !

    cout << endl;
    Shapes s2;
    for(int i = 0; i < 3; ++i)
        s2.push_back(new Rectangle);
    //Rectangle r;
    //s2.push_back(&r); // !
    destroyShapes(s2); // !
    cout << endl;

    placement();
    deleteArray();
    delete_method();
    memory_allocation_without_exception();
    object_placement_in_alloc_mem();
    object_placement_in_alloc_mem_in_template();

    cout << "at exit from main(): ";
    return 0;
}
