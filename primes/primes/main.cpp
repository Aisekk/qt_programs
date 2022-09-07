#include <QCoreApplication>
#include "prime.h"
#include <iostream>
using namespace std;

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);
    //---------------------------------------------------------------------------------------------
    Loop();
    cout << endl;
    Eratosfen();
    cout << endl;
    Atkin();
    cout << endl;
    Loop();
    cout << endl;
    //---------------------------------------------------------------------------------------------
    //system("pause");
    return app.exec();
}
