#ifndef INTERVALWIN_H
#define INTERVALWIN_H

#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QGridLayout>
#include <QDoubleValidator>
using namespace std;


class IntervalWin : public QDialog
{
    Q_OBJECT
public:
    IntervalWin(QWidget *pwgt = nullptr);
signals:
    void interval(const pair<double,double>&);
private slots:
    void slotApply();
private:
    double m_dn;
    double m_up;
    QLineEdit *m_ptxtDn;
    QLineEdit *m_ptxtUp;
};

#endif // INTERVALWIN_H
