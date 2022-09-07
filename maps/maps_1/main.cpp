#include <QApplication>
#include "MainWindow.h"

QString g_MainWinTitle = "Карты и статистика";
QString g_strYears = "2017-2019";
QString g_strVersion = "0.1.0.1";
// ----------------------------------------------------------------------
int main(int argc, char** argv)
{
    QApplication app(argc, argv);

    MainWindow MainWin;
    MainWin.show();

    return app.exec();
}
