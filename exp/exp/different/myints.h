#ifndef MYINTS_H
#define MYINTS_H

#include <cstdlib>
#include <cstring>

class Ints
{
private:
    int* _ints = nullptr;
public:
    Ints(const int* str);
    Ints(const Ints& other);
    Ints& operator = (const Ints& other);
    ~Ints();
    operator const int *() const;
};

#endif // MYINTS_H
