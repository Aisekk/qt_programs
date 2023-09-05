#ifndef ABSTRACT_CLASS_H
#define ABSTRACT_CLASS_H

#include <iostream>

namespace Abstract {

class CA { // Абстрактный класс
public:
    CA ( void ) { std::cout << "This object of the class "; }

    virtual void Abstr ( void ) = 0; // Чистая (пустая) виртуальная функция.
    void         fun   ( void ) { std::cout << "Реализация не будет наследоваться!"; }

    virtual ~CA () { std::cout << "." << std::endl; } //Вызывается в обр. порядке конструкторов
    //~CA () { std::cout << "." << std::endl; } //Вызывается в обр. порядке конструкторов
};

class CB : public CA {
public:
    CB ( void ) { std::cout << "CB;"; }

    void Abstr ( void ){ std::cout << " call function cb.Abstr();"; } //Подменяющая функция.
    void fun   ( void ){ std::cout << " call function cb.fun()"; }

    ~CB () { std::cout << "~CB()"; } // Неверно для абстр. кл. ~CB(){ ~CA(); }
};

class CC : public CA {
public:
    CC ( void ) { std::cout << "CC;"; }

    void Abstr ( void) { std::cout << " call function cc.Abstr();"; } //Подменяющая функция.
    void fun   ( void ) { std::cout << " call function cc.fun()"; }

    ~CC () { std::cout << "~CC()"; } // Неверно для абстр. кл. ~CC(){ ~CA(); }
};

void abstractOut () {
    std::cout << "Abstract class out:" << std::endl;
//    CB cb;
//    cb.Abstr(); cb.fun(); cb.~CB();

//    CC cc;
//    cc.Abstr(); cc.fun(); cc.~CC();

    CA *pcb = new CB;
    CA *pcc = new CC;
    delete pcb;
    delete pcc;
}

}


#endif // ABSTRACT_CLASS_H
