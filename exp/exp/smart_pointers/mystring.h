#ifndef MYSTRING_H
#define MYSTRING_H
#include <cstring>
#include <iostream>
using namespace std;

class String
{
    char* buffer;
public:
    String();
    String(const char* input);
    String(std::initializer_list<char> vals);
    virtual ~String();
    String(const String& copy);
    String& operator= (const String& copy);
    String(String &&movesrc);
    String& operator = (String&& movesrc);
    const char& operator[] (int Index) const;
    operator const char* ();
    String operator + (const String& addThis);

    int getLength() const;
    const char* getString() const;

    friend ostream &operator <<(ostream &os, const String& str);
};

#endif // MYSTRING_H
