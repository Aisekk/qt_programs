#ifndef CAST_H
#define CAST_H

#include <iostream>
#include <Qt>
#include <QDebug>

namespace Cast {

void boolCasting() {
    bool b = false;
    quint8 a1 = static_cast<quint8>(b);
    b = 230;//true;
    quint8 a2 = static_cast<quint8>(b);
    qDebug() << a1 << ' ' << a2;
    //std::cout << a1 << ' ' << a2 << std::endl;
}

}


#endif // CAST_H
