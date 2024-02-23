#include <cstdio>
#include <cstring>

#include "mainwindow.h"
#include "header.h"
#include "file1.h"
//#include "file2.h"
#include "literals.h"
#include "unions.h"
#include "static_obj.h"
#include "static_obj_include.h"
#include "operators.h"
#include "pure_virtual_func_call.h"
#include "placement_new.h"
#include "romb_problem.h"
#include "abstract_class.h"
#include "sort.h"
#include "print.h"
#include "arrays.h"
#include "delete_this.h"
#include "extern.h"
#include "reverse.h"
#include "auto.h"
#include "init.h"
#include "constructors.h"
#include "initlist.h"
#include "lambdas.h"
#include "cast.h"
#include "move.h"
#include "hash_heap.h"
#include "hash_table.h"
#include "pointers.h"
#include "align.h"
#include "stl_algs.h"
#include "smart_ptrs.h"
#include "constructor.h"
#include "sets_tasks.h"
#include "sizeof.h"
#include "overflow.h"
#include "test_std_algs.h"
#include "stl_sorts.h"
#include "one_bool.h"
#include "copy_algs.h"
#include "ip_parsing.h"
#include "static_word.h"
#include "static_word_2.h"
#include "bit_flags.h"
#include "class_initialization.h"
#include "directives.h"
#include "constructors_gen.h"

#include <QApplication>
#include <QtGlobal>
#include <QList>
#include <QLinkedList>
#include <list>
#include <QDebug>

int global = 10;
//static int static_var = 11;

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

void out_vec(const std::vector<const char*> &points) {
  for (const auto &s : points) {
    std::cout << s << ' ';
  }
  std::cout << std::endl;
}

int main(int argc, char *argv[])
{
    //ConstructorsGen::test_auto_gen();
    //Directives::test();
    //ClassFieldsInit::test_init();

    //Literals::class_literals();
    //Literals::text_literals();
    //Literals::constness();

    //BitFlags::test_bit_flags();
    //BitFlags::test_bit_flags_0x();

    //Static::C c(1,1);
    //fun_1();

    // test std algs
    //SetsTasks::test();
    //TestStdAlgs::test_for_each();
    //STL::test();

    //OneBool::test();
    //std::wstring s = L"рус";
    //std::wcout << s << std::endl;

    //CopyAlgs::test();
    //IpParsing::test();

    // sorts
    //StlSorts::test();
    //Sort::test();

    // algorithm tasks
    //Heap::topKFrequentOut();
    //HashTable::outHashTableParams();
    //HashTable::checkMyHashMap();

    //PlacementNew::test();
    //Overflow::overflow();
    //SizeOf::test();
    //Constructor::test();
    //SmartPtrs::test();
    //Align::testAlign();
    //Pointers::test();
    //Cast::boolCasting();
    //Lambdas::func();
    //InitList::out();
    //Ctrs::out();
    //Init::out();
    //Init::sumOut();
    //AutoTypeOut::autoOut();
    //Reverse::outReverseResults();
    //Extern::outGlobal();
    //std::cout << "I = " << I << std::endl;
    //DeleteThis::SomeResource *some = new DeleteThis::SomeResource ; some->Close();

    //Abstract::abstractOut();
    //RombProblem::rombProblem();
    //PlacementNew::pureCall();
    //PureCall::pureVirtCall();
    //B1 *a = new B1;
    //a->f();
    //A1 a1;

    //Terminate *t = nullptr;
    //t->out();
    //t->get(); termination

    //if_c17();
    //unary();
    //qInfo() << "staticObject.read() = " << staticObject.read();
    //outUnion_U1();
    //outUnion_U2();
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
    //divideByZero();

    return 0;// a.exec();
}
