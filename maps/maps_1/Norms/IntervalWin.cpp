#include "IntervalWin.h"

IntervalWin::IntervalWin(QWidget *pwgt) : QDialog(pwgt)
{
    setWindowTitle("Интервал: ");
    m_ptxtDn = new QLineEdit;
    m_ptxtUp = new QLineEdit;
    //---------------------------------------------------------------------------------------------
    QPushButton* pcmdOk = new QPushButton("&Ok");
    QPushButton* pcmdCancel = new QPushButton("&Отмена");
    //---------------------------------------------------------------------------------------------
    connect(pcmdOk, QPushButton::clicked, this, IntervalWin::accept);
    connect(pcmdOk, QPushButton::clicked, this, IntervalWin::slotApply);
    connect(pcmdCancel, QPushButton::clicked, this, IntervalWin::reject);

    connect(pcmdOk, QPushButton::pressed, this, IntervalWin::accept);
    connect(pcmdOk, QPushButton::pressed, this, IntervalWin::slotApply);
    connect(pcmdCancel, QPushButton::pressed, this, IntervalWin::reject);
    //---------------------------------------------------------------------------------------------
    QGridLayout *pgrdLayout = new QGridLayout;
    pgrdLayout->addWidget(m_ptxtDn, 0, 0);
    QLabel *pLabel = new QLabel(" - ");
    pgrdLayout->addWidget(pLabel, 0, 1);
    pgrdLayout->addWidget(m_ptxtUp, 0, 2);
    pgrdLayout->addWidget(pcmdOk, 1, 0, 1, 2);
    pgrdLayout->addWidget(pcmdCancel, 1, 2);

    setLayout(pgrdLayout);
}
//-------------------------------------------------------------------------------------------------
void IntervalWin::slotApply()
{
    double dn = (m_ptxtDn->text()).toDouble();
    double up = (m_ptxtUp->text()).toDouble();
    std::pair<double,double> Pair(dn,up);
    emit interval(Pair);
}
//-------------------------------------------------------------------------------------------------
