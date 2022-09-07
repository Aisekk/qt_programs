#include "MaskWin.h"

MaskWin::MaskWin(QWidget *pwgt, const QString& testName,
                           const int testIndex, const int slotNum) :
    MaskWindow(pwgt), m_testName(testName)
{
    if(testIndex < 0 || slotNum < 0)
    {
        setWindowTitle("Ошибка                  ");
        m_pcmdApply->setVisible(false);
    }
    else
    {
        int testNum = testIndex + 1;
        QString strTestNum = QString::number(testNum, 10);
        QString strSlotNum = QString::number(slotNum, 10);
        setWindowTitle("Маскирование теста " + m_testName +
                       ", номер " + strTestNum + " (слот " + strSlotNum + ")");
    }
}
//----------------------------------------------------------------------------
void MaskWin::sendSigMaskState()
{
    int x = 0;
    int y = 0;
    QStringList listXY{};
    QString strX{}, strY{}, strXY{};
    Mask state{};
    QHash<QString,Mask>::const_iterator cit = m_hashDies_XY_State.constBegin();
    for(;cit != m_hashDies_XY_State.constEnd(); ++cit)
    {
        listXY = (cit.key()).split("_");
        strX = listXY[0];  strY = listXY[1];
        x = strX.toInt();  y = strY.toInt();
        // !!! количество отправленных сигналов = количество элементов в перебираемом массиве
        strXY = cit.key();
        state = cit.value();

        emit sigMaskState(x, y, state);
    }

}
//----------------------------------------------------------------------------

