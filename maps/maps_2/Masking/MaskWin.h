#ifndef LOCALMASKWIN_H
#define LOCALMASKWIN_H

#include "MaskWindow.h"

class MaskWin : public MaskWindow
{
    Q_OBJECT
public:
    MaskWin(QWidget *pwgt = nullptr, const QString &testName = "",
            const int testIndex = -1, const int slotNum = -1);

signals:
    void sigMaskState(const int, const int, const Mask);

protected:
    void sendSigMaskState() override;

private:
    QString m_testName;
};

#endif // LOCALMASKWIN_H
