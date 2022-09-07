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

#include <QtWidgets>
#include <QtScript>
#include <QScriptEngineDebugger>

// ----------------------------------------------------------------------
int main(int argc, char** argv)
{
    QApplication app(argc, argv);

    QScriptEngine         scriptEngine;
    QScriptEngineDebugger scriptDebugger;

    scriptDebugger.attachTo(&scriptEngine);

    QAction* pact = 
        scriptDebugger.action(QScriptEngineDebugger::InterruptAction);
    pact->trigger();

    QString strCode = "var sum = 0;\n"
                      "for (var i = 1; i < 5; i++) {\n"
                      "    sum += i;\n"
                      "}";

    QScriptValue result = scriptEngine.evaluate(strCode);

    return app.exec();
}
