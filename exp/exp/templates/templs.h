#ifndef TEMPLS_H
#define TEMPLS_H

// инстанцирование шаблона - подстановка в шаблон конкретных типов вместо обобщенных
// специализация шаблона - замещение обобщенного кода шаблона специализированным кодом шаблона для специальных (конктретных) типов
// частичная специализация шаблона - замещение обобщенного кода шаблона специализированным кодом шаблона путем конкретизации обобщенных типов шаблона (например, замена T на T*)

template <class T = int>
class Matrix
{
public:
    Matrix(T t = 1){ _a = t; }
    Matrix(const T& elem)
    {
        _elem = elem;
    }
    int get() const { return _a; }
private:
    T _elem;
    int _a = 0;
};

template <typename T> T sqr(T);

template <typename T> class X
{
  T x;
public:
  X(T x):x(x){}
  T get()const;
  void set(T);
};


#endif // TEMPLS_H
