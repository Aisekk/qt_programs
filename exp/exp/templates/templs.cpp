#include "templs.h"

//template <class T>
//Matrix<T>::Matrix()
//{

//}

//template <class T>
//Matrix<T>::Matrix(const T& elem)
//{
//    _elem = elem;
//}

template <typename T> T sqr(T x)
{
    return x*x;
}

template <typename T> T X<T>::get() const
{
    return x;
}

template <typename T> void X<T>::set(T x)
{
    this->x=x;
}

template double sqr(double); // явное инстанцирование шаблона функции
template int sqr(int);       // для двух типов аргументов
template class X<int>;       // и класса для типа int
