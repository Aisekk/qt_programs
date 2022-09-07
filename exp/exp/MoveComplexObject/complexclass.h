#ifndef COMPLEXCLASS_H
#define COMPLEXCLASS_H
#include <string>
#include <iostream>

class ComplexClass
{
public:
    ComplexClass(const char* str, int num, const std::string& stroka);
    ComplexClass(ComplexClass&& other);
    ComplexClass& operator=(ComplexClass&& other);
    void out() const;
private:
    char* _str;
    int _num;
    std::string _stroka;
};

#endif // COMPLEXCLASS_H
