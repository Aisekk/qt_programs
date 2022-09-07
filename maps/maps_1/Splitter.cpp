#include "Splitter.h"

Splitter::Splitter(QWidget *pwgt) : QSplitter(pwgt){}

size_t Splitter::getLotNum() const
{
    return m_lotNum;
}
void Splitter::setLotNum(const size_t lotNum)
{
    m_lotNum = lotNum;
}
