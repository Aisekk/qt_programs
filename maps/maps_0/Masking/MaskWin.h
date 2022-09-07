#ifndef LOCALMASKWIN_H
#define LOCALMASKWIN_H

#include "MaskWindow.h"

class MaskWin : public MaskWindow
{
    Q_OBJECT
public:
    MaskWin(QWidget *pwgt = nullptr, const QString &testName = "",
            int testIndex = -1, int slotNum = -1);

signals:
    void sigMaskState(int, int, Mask);

protected:
    void sendSigMaskState() override;

private:
    QString m_testName;
};

#endif // LOCALMASKWIN_H
