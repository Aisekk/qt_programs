#include "Breaker.h"

Breaker::Breaker(QWidget *pwgt) : QWidget(pwgt), m_breakCalc(false){}

bool Breaker::isBreakCalc() const
{
    return m_breakCalc;
}
void Breaker::slotBreakCalc()
{
    m_breakCalc = true;
}
