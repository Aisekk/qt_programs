#include <iostream>

using namespace std;

struct A
{
    int m_n1, m_n2;
    // инициализация не в порядке списка
    A() : m_n2(1), m_n1(m_n2+1) // m_n1 == ???
    {
        //
    }
};

// случаи, требующие явной инициализации:
// если поле константное или ссылка, необходима явная инциализация
// (или конструктор по умолчанию для данного типа)
struct B
{
    const int m_cn = 1;
    int m_n = 2;
    int& m_rn = m_n;
    const A m_cA;
    // ошибка: m_cn и m_rn не проинициализированы
    // для типа A необходим конструктор по умолчанию
    B(){}
};

int main()
{
    A a;
    cout << "a.m_n1 == " << a.m_n1 << endl;
    cout << "a.m_n2 == " << a.m_n2 << endl;

    B b;
    cout << "b.m_cn == " << b.m_cn << endl;
    cout << "b.m_rn == " << b.m_rn << endl;

    return 0;
}
