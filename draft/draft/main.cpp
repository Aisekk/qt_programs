#include "mainwindow.h"
#include "header.h"
#include "file1.h"
//#include "file2.h"

#include <QApplication>
#include <QtGlobal>
#include <QList>
#include <QLinkedList>
#include <list>
#include <QDebug>

extern int a;
class Stroka;
Stroka stroka();

extern int f(int x);
int f(int x) { return x + 1; }
//int f(int x) { return x + 2; }

class E {
public:
    int getZero() { return zero; }
protected:
    int zero = 0;
};
class A : public E {
public:
    Stroka stroka() const;
    int getZero2() { zero = 1; return zero; }
    std::string str;
    static int x;
    const static int y = 0;
};
int A::x = 0;

void get_7E_Address() {
    quint16 addr(0x3F00);
    QString strAddr = QString::number(addr, 16).toUpper();
    qInfo() << strAddr + " = " << strAddr;
    auto addr_1 = (addr << 1);
    qInfo() << strAddr + " << 1 = " << QString::number(addr_1, 16).toUpper();
    auto res = addr_1 | 1;
    qInfo() << "(" + strAddr + " << 1) | 1 = " << QString::number(res, 16).toUpper();
}

QString calcCRC() {
    // Frame = 7E A0 4D 02 25 81 10 7E 4C 7E
    QByteArray data;
    data.append(0xA0);
    data.append(0x4D);
    data.append(0x02);
    data.append(0x25);
    data.append(0x81);
    data.append(0x10);
    quint16 crc = qChecksum(data.data(), data.size());

    QString strCRC = QString::number(crc, 16).toUpper();
    return strCRC;
}

void compareStlQtContainers() {
    QList<int> qlist;
    QLinkedList<int> qlinkedlist;
    std::list<int> stdlist;
    qInfo() << "sizeof (qlist) = " << sizeof (qlist) << "; sizeof (qlinkedlist) = " << sizeof (qlinkedlist)
            << "; sizeof (stdlist) = " << sizeof (stdlist);
}

void divideByZero() {
    //int n = 0;
    //int m = 5 / n; qInfo() << "m = " << m;
    double p = std::numeric_limits<double>::epsilon() / 2; // 0.0;
    double q = 5.0 / p; qInfo() << "q = " << q;
    double r = 1.0 * q; qInfo() << "r = " << r;
    double s = 1.0 / q; qInfo() << "s = " << s;
}

int main(int argc, char *argv[])
{
    //QApplication a(argc, argv);
    //MainWindow w;
    //w.show();

    //get_7E_Address();

    //qInfo() << "CRC: " << calcCRC();
    //compareStlQtContainers();
    //qInfo() << "sizeof(unsigned int) = " << sizeof(unsigned int);

    //A a;
    //a.x = 5;
    //qInfo() << a.getZero();

    //function1();
    //function2();
    //qInfo() << variable;

    //foo();
    divideByZero();

    return 0;// a.exec();
}
