// ======================================================================
//  main.cpp
// ======================================================================
//                   This file is a part of the book 
//             "Qt 5.3 Professional programming with C++"
// ======================================================================
//  Copyright (c) 2014 by Max Schlee
//
//  Email : Max.Schlee@neonway.com
//  Blog  : http://www.maxschlee.com
//
//  Social Networks
//  ---------------
//  FaceBook : http://www.facebook.com/mschlee
//  Twitter  : http://twitter.com/Max_Schlee
//  2Look.me : http://2look.me/NW100003
//  Xing     : http://www.xing.com/profile/Max_Schlee
//  vk.com   : https://vk.com/max.schlee
// ======================================================================

#include <QApplication>
#include "SDIProgram.h"

// ----------------------------------------------------------------------
int main(int argc, char** argv) 
{
    QApplication app(argc, argv);
    SDIProgram   psdi;

    psdi.setWindowTitle("SDI Program");
    psdi.resize(300, 300);
    psdi.show();

    return app.exec();
}
