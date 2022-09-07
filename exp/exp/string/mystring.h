#ifndef MYSTRING_H
#define MYSTRING_H

#include <cstdlib>
#include <cstring>

class String
{
private:
    char* _str = nullptr;
public:
    String(const char* str = nullptr);
    String(const String& other);
    String& operator = (const String& other);
    String(String&& other);
    String& operator = (String&& other);
    ~String();
    size_t size() const;
    operator const char *() const;
    char& operator[](size_t i);
};

#endif // MYSTRING_H
