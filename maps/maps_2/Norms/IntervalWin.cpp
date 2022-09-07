#include "IntervalWin.h"

IntervalWin::IntervalWin(QWidget *pwgt) :
  QDialog(pwgt, Qt::WindowTitleHint | Qt::WindowCloseButtonHint | Qt::WindowMinMaxButtonsHint)
{
    setWindowTitle("Динамический интервал: ");
    setMaximumSize(500,200);
    m_ptxtDn = new QLineEdit;
    m_ptxtUp = new QLineEdit;
    //---------------------------------------------------------------------------------------------
    double typeLimit = 1.0e+290;
    QDoubleValidator *pdblValidator_Dn = new QDoubleValidator(m_ptxtDn);
    pdblValidator_Dn->setRange(-typeLimit, typeLimit, 6);
    QDoubleValidator *pdblValidator_Up = new QDoubleValidator(m_ptxtUp);
    pdblValidator_Up->setRange(-typeLimit, typeLimit, 6);
    m_ptxtDn->setValidator(pdblValidator_Dn);
    m_ptxtUp->setValidator(pdblValidator_Up);
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
