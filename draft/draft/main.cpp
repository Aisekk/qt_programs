#include "mainwindow.h"

#include <QApplication>
#include <QtGlobal>
#include <QList>
#include <list>
#include <QDebug>

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

void compareStlQt() {
    QList<int> qlist;
    std::list<int> stdlist;
    qInfo() << "sizeof (qlist) = " << sizeof (qlist) << "; sizeof (stdlist) = " << sizeof (stdlist);
}

int main(int argc, char *argv[])
{
    //QApplication a(argc, argv);
    //MainWindow w;
    //w.show();

    //get_7E_Address();

    //qInfo() << "CRC: " << calcCRC();
    //compareStlQt();
    qInfo() << "sizeof(unsigned int) = " << sizeof(unsigned int);

    return 0;// a.exec();
}
