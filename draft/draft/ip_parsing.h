#ifndef IP_PARSING_H
#define IP_PARSING_H

#include <QStringList>
#include <algorithm>
#include <iostream>
#include <QDebug>

namespace IpParsing {

bool parseIPv4String(const QString &tcpIpAddress, quint32 &num) {
    auto ipNums = tcpIpAddress.split('.');
    if (4 != ipNums.size()) {
        return false;
    }
    QByteArray res;
    std::for_each(ipNums.cbegin(), ipNums.cend(), [&res](const QString &elem){
        if (!elem.isEmpty()) {
            bool ok{false};
            quint8 num = elem.toUInt(&ok);
            qDebug() << "elem";
            if (ok) {
                qDebug() << "elem appended";
                res.append(num);
            }
        }
    });
    qDebug() << "res: " << res;
    qDebug() << "res.toHex(): " << res.toHex();
    bool ok{false};
    num = res.toHex().toUInt(&ok, 16);
    qDebug() << "num: " << num;
    return ok;
}

void test() {
    QString address = "192.168.0.1";
    quint32 res{0};
    if (parseIPv4String(address, res)) {
        bool ok = bool{res == 3232235521};
        std::cout << address.toStdString() << " in quint32: " << res << " (= 3232235521); ok = " << ok << std::endl;
    }
    bool ok{false};
    QByteArray ba = "A";
    qDebug() << ba.toHex().toUInt(&ok, 16) << "; ok = " << ok;
}

}

#endif // IP_PARSING_H
