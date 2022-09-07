#ifndef STATICFUNCINHEADER_H
#define STATICFUNCINHEADER_H
#include <iostream>

/* Мы не можем определить функцию в заголовочном файле не сделав ее inline или static,
 * потому что при повторном включении этого заголовочного файла мы получим такую же ошибку,
 * как и при использовании двух функций с одинаковым именем в разных cpp-файлах. */

static int svar = 5;
//int var1 = 1;

inline void func()
{
    std::cout << "func" << std::endl;
}

static void staticFunc()
{
    std::cout << "static func" << std::endl;
}

#endif // STATICFUNCINHEADER_H
