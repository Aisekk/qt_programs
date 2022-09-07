#include <iostream>
#include <cstdlib>
using namespace std;

class A
{
public:
    A(){ cout << "A()" << endl; }
    virtual ~A(){ cout << "~A()" << endl; }
};
class B : public A
{
public:
    B(){ cout << "B()" << endl; }
    ~B(){ cout << "~B()" << endl; }
};
void stack()
{
    cout << "stack: " << endl;
    B b;
}
void free_store()
{
    cout << "free store: " << endl;
    A *pA = new B;
    // утечка памяти, если деструктор не виртуальный:
    // удаление через указатель на базовый класс => удаляется часть памяти под класс А
    // - для вызова деструктора компилятор использует раннее (статическое) связывание
    delete pA;
    // если деструктор виртуальный, то позднее (динамическое) связывание:
    // из таблицы виртуальных функций определяется адрес деструктора производного класса,
    // который после своей работы вызывает деструктор базового класса
}
//-------------------------------------------------------------------------------------------------
// виртуальные функции в деструкторах
class Cat
{
public:
    virtual ~Cat()
    {
        /* виртуальный вызов из деструктора невозможен, т.к. невозможно обращение
         * к той части объекта, которая уже разрушена, поэтому - раннее связывание */
        sayGoodbye();
    }
    void askForFood() const
    {
        speak(); eat();
    }
    virtual void speak() const { cout << "Meow! "; }
    virtual void eat() const { cout << "*champing*" << endl; }
    virtual void sayGoodbye() const { cout << "Meow-meow!" << endl; }
};
class CheshireCat : public Cat
{
public:
    virtual void speak() const { cout << "WTF?! Where\'s my milk? =) "; }
    virtual void sayGoodbye() const { cout << "Bye-bue! (:" << endl; }
};
void virt_funs_in_destructor()
{
    Cat *cats[] = { new Cat, new CheshireCat };
    cout << "Ordinary Cat: "; cats[0]->askForFood();
    cout << "Cheshire Cat: "; cats[1]->askForFood();

    delete cats[0]; delete cats[1];
}

//-------------------------------------------------------------------------------------------------
int main()
{
    stack();
    cout << endl;

    free_store();
    cout << endl;

    virt_funs_in_destructor();

    return 0;
}
