#include <iostream>
#include <cstring>
using namespace std;

class Fraction
{
    int m_nNom, m_nDen;
public:
    Fraction(int nNom = 0, int nDen = 1) : m_nNom(nNom), m_nDen(nDen) {}
    operator double () const
    {
        return ((1.0*m_nNom)/m_nDen);
    }
};

struct B;
struct A
{
    A(){}
    // конструктор преобразования
    A(const B &) // B -> A
    { cout << "A::A(const B &)" << endl; }
};
struct B
{
    // оператор преобразования
    operator A() // B -> A
    { cout << "B::operator A()" << endl; return A(); }
};

class String
{
    char *m_pszStr;
public:
    String(const char *pcszStr)
        : m_pszStr((char*) std::calloc(1 + std::strlen(pcszStr), sizeof(char)))
    {
        std::strcpy(m_pszStr, pcszStr);
    }
    operator const char* () const
    { return m_pszStr; }
};

int main()
{
    Fraction f1 = 4; // int -> Fraction
    double d = f1; // Fraction -> double

    cout << "f1 == " << f1 << endl;
    cout << "d == " << d << endl;

    B b;
    A a1(b);
    A a2;
    a2 = b;

    return 0;
}
