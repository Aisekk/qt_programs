#ifndef FILE1_H
#define FILE1_H

//#include "header.h"
#include <QDebug>

//namespace {
//const double Imax = 100.0;
//}
static const double I = 100.0;

void function1();
static void foo() { qInfo() << "file1: foo()"; }

#endif // FILE1_H
