#include <iostream>
#include "f.h"
#include <vector>
#include <string>
#include <clocale>
#include <Windows.h>
using namespace std;

//void f();
//f(); - нельзя вызывать за предeлами main()
int x = 9;
void pointer_arithmetic();
void pointerConstness();
void rangeFor();
void For();
void refToPointer();
void callMethodThroughNullPtr();
void stdString();

int main()
{
    //setlocale(LC_CTYPE, "");

    //setlocale(LC_ALL, "Russian");
    //setlocale(LC_CTYPE, "Russian");
    //system("chcp 1251");

    //setlocale(LC_ALL, "PL_pl.UTF-8");
    //SetConsoleCP(CP_UTF8);
    //SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(1251);// установка кодовой страницы win-cp 1251 в поток ввода
    SetConsoleOutputCP(1251); // установка кодовой страницы win-cp 1251 в поток вывода

    cout << "Кириллица в консоли\n";

    //f();
    //cout << x << endl;
    //cout << 25u - 50 << endl;
    //pointer_arithmetic();
    //pointerConstness();
    //rangeFor();
    //refToPointer();
    //For();
    //callMethodThroughNullPtr();
    stdString();
    return 0;
}

void f()
{
   ::x = 8;
}

void pointer_arithmetic()
{
    int a[] = {1, 2, 3, 4, 5, 6};
    std::cout << (1 + 3)[a] - a[0] + (a + 1)[2] << endl; // a[4] - a[0] + a[3] = 5 - 1 + 4 = 8
}

void pointerConstness()
{
    {
        int a = 1;
        const int* p = &a;
        cout << "a = 1: " << *p << "; ";
        //*p = 2;
        a = 2;
        cout << "a = 2: " << *p << endl;
    }
    {
        int value = 100; //обычная переменная для взятия адреса
        int* const p = &value; //Указательная переменная зафиксировала сохранённый в себя адрес

        int y;
        //p = &y;  //Нельзя изменить указательную переменную
        //cout << "; " << *p << endl;
    }
    {
        int y = 200;
        int const *p = &y;

        //(*p) = 300; //Нельзя изменить косвенное значение "руками" указательной переменной
    }
    {
        int a = 100;
        const int* const p = &a;
        //int const* const p = &a;  //Запрет изменять и хранимый в указателе "p" адрес,
        //и значение в том адресе разыменованным указателем

        a++;       //напрямую значение можно менять
        //(*p)++;  //изменять разыменованным указателем нельзя
        //p++;     //переназначить адрес, хранимый в указательной переменной, нельзя
    }

}

void out(const std::vector<int*>& vec)
{
    for(auto p : vec)
        cout << p << " ";
    cout << endl;
}

void rangeFor()
{
    std::vector<int*> vec(10, nullptr);
    for(int*& p : vec)
        p = new int;

    out(vec);

    for(int*& p : vec)
    {
        delete p;
        p = nullptr;
    }

    out(vec);
}

void For()
{
    for(
        int i = 1;
        i < 2;
        ++i)
    {
        cout << i << " ";
    }
    cout << endl;
}

void refToPointer()
{
    int a = 1;
    int* ptr = &a;
    int*& ref_ptr = ptr;

    cout << "ptr = " << ptr << "; ref ptr: " << ref_ptr << endl;

}

void callMethodThroughNullPtr()
{
    class A
    {
    private:
        int i = 2;
    public:
        void f()
        {
            if(this != nullptr)
            {
                cout << "f(); this = " << this << endl;
            }
        }
        void g()
        {
            cout << "g()" << endl;
        }
        int get() { return 1; }
        int mem() { return i; }
        A(const A& a)
        {
            if(&a != nullptr)
                i = a.i;
        }
    };
    cout << "sizeof(A) = " << sizeof(A) << endl;
    A* a = nullptr;
    a->f();
    a->g();
    A a1(*a);
    cout << "*a = " << (*a).get() << endl;
    //cout << "*a = " << (*a).mem() << endl; // undefined behavior
    cout << "&a = " << &a << endl;
}

void stdString()
{
    //cout << "1" << endl;
    std::string en("stroka");
    std::cout << "строка en: " << en.data() << endl;
    try
    {
        std::wstring ru(L"строка");
        cout << "строка ру: " << ru.data() << endl;
    }
    catch (...)
    {
        cout << "except" << endl;
    }

    //cout << "строка en: " << en.data() << endl;
    //cout << "строка ру: " << a << endl;
    //cout << "строка ру: " << endl;
}
