#ifndef INITLIST_H
#define INITLIST_H

#include <QObject>
#include <QDebug>

namespace InitList {

class A : public QObject {
public:
    A(QObject *parent = nullptr) : QObject(parent) {}
    ~A() { qDebug() << "~A()";}
};

class B : public A { //QObject {
public:
    B(QObject *parent = nullptr)
        : _a(new A(this))
    {
    }
private:
    A *_a;
};

void out() {
    //B b;
    //B *b = new B;
    //delete b;
    A *b = new B;
    delete b;
}

}

#endif // INITLIST_H
