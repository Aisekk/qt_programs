#ifndef MYSTRING_H
#define MYSTRING_H

#include <cstdlib>
#include <cstring>

class String
{
private:
    char* _str = nullptr;
public:
    String(const char* str);
    String(const String& other);
    String& operator = (const String& other);
    String(String&& other);
    String& operator = (String&& other);
    ~String();
    operator const char *() const;
};

#endif // MYSTRING_H
