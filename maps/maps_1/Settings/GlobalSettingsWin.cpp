#include "GlobalSettingsWin.h"

GlobalSettingsWin::GlobalSettingsWin(QWidget *pwgt/*=0*/) : QWidget(pwgt)
{
    m_TypeLimit = 1.000000e+308;
    m_NormalLimit = 1.000000e+290;
    m_strNormalLimit_Dn = QString::number(-m_NormalLimit,'e');
    m_strNormallLimit_Up = QString::number(m_NormalLimit,'e');

    setWindowTitle("Глобальный интервал");
    setFixedSize(QWidget::sizeHint());
    //setMinimumSize(250,140); setMaximumSize(250,170);
    m_plbl_Dn_Limit = new QLabel;
    m_plbl_Up_Limit = new QLabel;
    m_ptxt_Dn_Limit = new QLineEdit;
    m_ptxt_Up_Limit = new QLineEdit;
    m_pvbxLayout = new QVBoxLayout;
    m_phbxLayout_Dn = new QHBoxLayout;
    m_phbxLayout_Up = new QHBoxLayout;
    m_phbxLayout_Buttons = new QHBoxLayout;

    m_plbl_Dn_Limit->setText("Нижний предел:  ");
    m_plbl_Up_Limit->setText("Верхний предел: ");

    m_pdblValidator_Dn_Limit = new QDoubleValidator(m_ptxt_Dn_Limit);
    m_pdblValidator_Up_Limit = new QDoubleValidator(m_ptxt_Up_Limit);
    m_pdblValidator_Dn_Limit->setRange(-m_TypeLimit, m_TypeLimit, 6);
    m_pdblValidator_Up_Limit->setRange(-m_TypeLimit, m_TypeLimit, 6);
    m_ptxt_Dn_Limit->setValidator(m_pdblValidator_Dn_Limit);
    m_ptxt_Up_Limit->setValidator(m_pdblValidator_Up_Limit);

    QPushButton *pcmdOk = new QPushButton("&Ok");
    QPushButton *pcmdCancel = new QPushButton("&Отмена");
    m_pcmdApply = new QPushButton("&Применить");
    m_pcmdApply->setEnabled(false);
    m_pcmdMachineLimits = new QPushButton("&Числовые пределы");


    connect(pcmdOk, QPushButton::clicked, this, GlobalSettingsWin::slot_Apply_and_HideWin);
    //connect(pcmdOk, &QPushButton::clicked, this, &GlobalSettingsWin::slotApply);
    connect(m_pcmdApply, QPushButton::clicked, this, GlobalSettingsWin::slotApply);
    connect(pcmdCancel, QPushButton::clicked, this, GlobalSettingsWin::slotHideWin);
    connect(m_pcmdMachineLimits, QPushButton::clicked, this, GlobalSettingsWin::slotMachineLimits);
    connect(m_pcmdMachineLimits, QPushButton::toggled, this, GlobalSettingsWin::slotMachineLimits);

    connect(m_ptxt_Dn_Limit, &QLineEdit::textChanged, this, &GlobalSettingsWin::slotCmdApplyEnabled);
    connect(m_ptxt_Up_Limit, &QLineEdit::textChanged, this, &GlobalSettingsWin::slotCmdApplyEnabled);

    m_phbxLayout_Dn->addWidget(m_plbl_Dn_Limit);
    m_phbxLayout_Dn->addWidget(m_ptxt_Dn_Limit);
    m_phbxLayout_Up->addWidget(m_plbl_Up_Limit);
    m_phbxLayout_Up->addWidget(m_ptxt_Up_Limit);
    //Ok, Apply, Cancel, DefaultMeanings
    //m_phbxLayout_Buttons->addStretch(1);
    m_phbxLayout_Buttons->addWidget(pcmdOk);
    m_phbxLayout_Buttons->addWidget(m_pcmdApply);
    m_phbxLayout_Buttons->addWidget(pcmdCancel);

    m_pvbxLayout->addLayout(m_phbxLayout_Dn);
    m_pvbxLayout->addLayout(m_phbxLayout_Up);
    m_pvbxLayout->addLayout(m_phbxLayout_Buttons);
    m_pvbxLayout->setMargin(15);
    m_pvbxLayout->addWidget(m_pcmdMachineLimits);
    setLayout(m_pvbxLayout);


}
//-------------------------------------------------------------------------------------------------------
GlobalSettingsWin::~GlobalSettingsWin(){}
//-------------------------------------------------------------------------------------------------------
//установка объекта настроек
void GlobalSettingsWin::setSettings(shared_ptr<QSettings> spSettings)
{
    m_spSettings = spSettings;
}
//-------------------------------------------------------------------------------------------------------
//запись настроек
void GlobalSettingsWin::writeSettings(bool& error)
{
    m_spSettings->beginGroup("/Settings");
//-----------------------------------------------------------------------------
    m_spSettings->beginGroup("/GlobalLimits");

    QString keyDn = "/Dn_Limit";
    Validator::validateValue(m_ptxt_Dn_Limit, m_pdblValidator_Dn_Limit, m_spSettings, keyDn, error);
    QString keyUp = "/Up_Limit";
    Validator::validateValue(m_ptxt_Up_Limit, m_pdblValidator_Up_Limit, m_spSettings, keyUp, error);

    m_spSettings->endGroup();
//-----------------------------------------------------------------------------
    m_spSettings->endGroup();
}
//-------------------------------------------------------------------------------------------------------
//слоты
void GlobalSettingsWin::slotApply()
{
    bool error = false;
    writeSettings(error);
    m_pcmdApply->setEnabled(false);
    emit recalc();
}
void GlobalSettingsWin::slot_Apply_and_HideWin()
{
    bool error = false;
    writeSettings(error);
    m_pcmdApply->setEnabled(false);
    emit recalc();

    if(error == false)
        this->hide();
}
void GlobalSettingsWin::slotCmdApplyEnabled()
{
    m_pcmdApply->setEnabled(true);
}
void GlobalSettingsWin::slotMachineLimits()
{
    m_ptxt_Dn_Limit->setText(m_strNormalLimit_Dn);
    m_ptxt_Up_Limit->setText(m_strNormallLimit_Up);
}
void GlobalSettingsWin::slotHideWin()
{
    hide();
}

//-------------------------------------------------------------------------------------------------------
void GlobalSettingsWin::setDnLimit(const QString& Dn)
{
    m_ptxt_Dn_Limit->setText(Dn);
}
void GlobalSettingsWin::setUpLimit(const QString& Up)
{
    m_ptxt_Up_Limit->setText(Up);
}
