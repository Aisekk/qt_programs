#include <iostream>

using namespace std;

struct X
{
    static void* operator new(std::size_t nSize, char ch);//{ return new X; }
    static void operator delete(void *p, char ch);//{ delete p; }
    static void operator delete(void *p);//{ delete p; }
};
void f()
{
    //X *pX = new('!') X;
    //delete pX;//('!');
}
void Array()
{
    typedef char Str[100];
    char* szName = new Str;
    //
    cout << sizeof(Str) << endl;
    unsigned char ch = 0;
    for(unsigned char c = 0; c < 20; ++c)
    {
        ch += c;
        szName[c] = ch;
    }
    cout << szName << endl;
    cout << szName[5] << endl;
    //
    delete[] szName;
}
// выделение памяти без исключения
void alloc_no_throw()
{
    char *pchData = new(std::nothrow) char[1000000000];
    if(pchData != nullptr)
    {
        cout << "allocated with no throw: 0x" << pchData << endl;
        delete[] pchData;
    }
}

int main()
{
    //f();

    Array();
    alloc_no_throw();

    return 0;
}
