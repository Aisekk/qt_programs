#include <iostream>
#include <cstring>
#include <iterator>
#include <algorithm>
#include <malloc.h>
using namespace std;

// 1. Перечислите все проблемы, которые вы видите в данном коде:
class Foo
{
public:
    Foo(int j)
    {
        cout << "Foo()" <<endl;
        i = new int[j];
        _mem = j;
    }
    virtual ~Foo()
    {
        cout << "~Foo()";
        if(i == nullptr)
            cout << "; i = null";
        cout << endl;
        delete[] i;
    }
    Foo(const Foo& other)
    {
        if(other.i && this != &other)
        {
            int length = _msize(other.i) / sizeof(int);
            i = new int[length];
            std::memcpy(i, other.i, length);
            _mem = other._mem;
        }
    }
    Foo& operator=(const Foo& other)
    {
        if(other.i && this != &other)
        {
            delete[] i;
            int length = _msize(other.i) / sizeof(int);
            i = new int[length];
            std::memcpy(i, other.i, length);
            _mem = other._mem;
        }
       return *this;
    }
    int mem() const { return _mem; }
private:
    int* i;
    int _mem = 0;
};

class Bar: public Foo
{
public:
    Bar(int j, int k) : Foo(k)
    {
        cout << "Bar()" <<endl;
        i = new char[j];
    }
    ~Bar()
    {
        cout << "~Bar()" << endl;
        delete[] i;
    }
    int func(){ return _val; }
private:
    char* i;
    int _val = 3;
};


int main()
{
    Foo* f = new Foo(100);
    Foo* b = new Bar(200, 101);
    //Bar* b1 = new Bar(300);

    cout << "f::mem: " << f->mem() << endl;//100
    cout << "b::mem: " << b->mem() << endl;//101
    *f = *b;
    cout << "f::mem: " << f->mem() << endl;//101
    cout << "b::mem: " << b->mem() << endl;//101

    auto fb = dynamic_cast<Bar*>(f);
    if(fb)
    {
        cout << "fb->func() = " << fb->func() << endl;
    }

    delete f;
    delete b;

    //int a[] = { -5, 10, 15 };
    //std::cout << std::size(a) << '\n';

    return 0;
}

//2. Есть класс CodeGenerator, который умеет генерить код на разных языках.
// Предложите рефакторинг с учетом, что количество языков будет расширяться

class CodeGenerator
{
public:
    enum Lang {JAVA, C_PLUS_PLUS, PHP};
    CodeGenerator(Lang language) { _language = language; }
    std::string generateCode()
    {
        std::string code;
        switch(_language) {
        case JAVA: break;       //return generated java code
        case C_PLUS_PLUS:
        {
            code += someCodeRelatedThing();
            code += someCodeRelatedThing();
            break;    //return generated C++ code
        }
        case PHP: break;        //return generated PHP code
        default:
            throw new std::logic_error("Bad language");
        }
        return code;
    }
    std::string someCodeRelatedThing() // used in generateCode()
    {
        std::string someCode;
        switch(_language) {
        case JAVA: break;        //return generated java-related stuff
        case C_PLUS_PLUS:
        {
            someCode = "class Cpp{};";
            break; //return generated C++-related stuff
        }
        case PHP: break;         //return generated PHP-related stuff
        default:
            throw new std::logic_error("Bad language");
        }
        return someCode;
    }

private:
    Lang _language;
};

