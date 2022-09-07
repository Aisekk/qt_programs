#ifndef INTERVALS_H
#define INTERVALS_H
#include "intervals_global.h"
#include <QString>
#include <QMap>

class INTERVALSSHARED_EXPORT Intervals
{

public:
    Intervals();
    QPair<double, double> interval(const QString& testName);
private:
    void init();
    QMap<QString, QPair<double,double>> m_mapTestElemIntervals;
};

#endif // INTERVALS_H
