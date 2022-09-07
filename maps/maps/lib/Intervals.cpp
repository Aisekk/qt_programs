#include "Intervals.h"

Intervals::Intervals()
{
    init();
}
void Intervals::init()
{
    m_mapTestElemIntervals.insert("An_UGST", {0.55, 0.70});
}
QPair<double,double> Intervals::interval(const QString& testName)
{
    //return m_mapTestElemIntervals.value(testName);
}
