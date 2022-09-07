#ifndef BREAKER_H
#define BREAKER_H

#include <QWidget>

class Breaker : public QWidget
{
    Q_OBJECT
public:
    Breaker(QWidget *pwgt = nullptr);
    bool isBreakCalc() const;
private:
    bool m_breakCalc;
public slots:
    void slotBreakCalc();
};

#endif // BREAKER_H
