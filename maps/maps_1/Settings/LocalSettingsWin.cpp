#include "LocalSettingsWin.h"

LocalSettingsWin::LocalSettingsWin(QWidget *pwgt/*=0*/) :
    QDialog(pwgt, Qt::WindowTitleHint | Qt::WindowCloseButtonHint | Qt::WindowMinMaxButtonsHint)
{
    setModal(true);
    setWindowTitle("Настройки: локальные интервалы пользователя");
    setMinimumSize(QSize(850, 500));
    setMaximumSize(QSize(950, 700));

    QFont LabelFont("New Courier", 10);
    setFont(LabelFont);
    //создание текстовых полей
    createLineEdits();
    //создание надписей тестов
    createLabels();

    //setAttribute(Qt::WA_DeleteOnClose);
    QPushButton* pcmdOk = new QPushButton("&Ok");
    QPushButton* pcmdCancel = new QPushButton("&Отмена");
    m_pcmdApply = new QPushButton("&Применить");

    connect(pcmdOk, SIGNAL(clicked()), this, SLOT(accept()));
    connect(pcmdOk, SIGNAL(clicked()), this, SLOT(slotApply()));
    connect(m_pcmdApply, SIGNAL(clicked()), SLOT(slotApply()));
    connect(pcmdCancel, SIGNAL(clicked()), SLOT(reject()));

    //создание компоновок с надписями и полями
    m_pgrdLayoutResistorsSIL = new QGridLayout;
    m_pgrdLayoutResistorsSIL->setMargin(10);
    m_pgrdLayoutResistorsSIL->setSpacing(5);
    m_pgrdLayoutResistorsMe = new QGridLayout;
    m_pgrdLayoutResistorsMe->setMargin(10);
    m_pgrdLayoutResistorsMe->setSpacing(5);
    m_pgrdLayoutVanderPau = new QGridLayout;
    m_pgrdLayoutVanderPau->setMargin(10);
    m_pgrdLayoutVanderPau->setSpacing(5);
    m_pgrdLayoutTransistors = new QGridLayout;
    m_pgrdLayoutTransistors->setMargin(10);
    m_pgrdLayoutTransistors->setSpacing(5);
    m_pgrdLayoutOther = new QGridLayout;
    m_pgrdLayoutOther->setMargin(10);
    m_pgrdLayoutOther->setSpacing(5);

//-------------------------------------------------------------------------------------
    //Заполнение компоновки виджетами
    //Силицидные Кельвины, цепочки, резисторы
    int i = 0, j = 0;//i передается в методы add по ссылке
    addSeparatingLine(i,j, m_pgrdLayoutResistorsSIL);
    addSeparatingLine(i,j, m_pgrdLayoutResistorsSIL);
    addAll_R_SIL(i,j, m_pgrdLayoutResistorsSIL);
    addSeparatingLine(i,j, m_pgrdLayoutResistorsSIL);
    addSeparatingLine(i,j, m_pgrdLayoutResistorsSIL);
    addSeparatingLine(i,j, m_pgrdLayoutResistorsSIL);

    addTests_KLV_SIL(i,j, m_pgrdLayoutResistorsSIL);  addSeparatingLine(i,j, m_pgrdLayoutResistorsSIL);
    addTests_Z_SIL(i,j, m_pgrdLayoutResistorsSIL);
    i = 0; j = 4;
    addTests_RzSIL09(i,j, m_pgrdLayoutResistorsSIL);  addSeparatingLine(i,j, m_pgrdLayoutResistorsSIL);
    addTests_RzSIL05(i,j, m_pgrdLayoutResistorsSIL);  addSeparatingLine(i,j, m_pgrdLayoutResistorsSIL);
    addTests_RzSIL035(i,j, m_pgrdLayoutResistorsSIL); addSeparatingLine(i,j, m_pgrdLayoutResistorsSIL);
    addTests_RzSIL06(i,j, m_pgrdLayoutResistorsSIL);
    //Межметальные Кельвины, цепочки, меандры
    i = 0; j = 0;
    addTests_KLV_MM(i,j, m_pgrdLayoutResistorsMe); addSeparatingLine(i,j, m_pgrdLayoutResistorsMe);
    addTests_Z_MM(i,j, m_pgrdLayoutResistorsMe);
    i = 0; j = 4;
    addTests_Meanders(i,j, m_pgrdLayoutResistorsMe);
    //Ван дер Пау
    i = 0; j = 0;
    addTests_VDP(i,j, m_pgrdLayoutVanderPau);
    i = 0; j = 4; for(; j < 9; ++j) addSeparatingLine(i,j, m_pgrdLayoutVanderPau);
    //Транзисторы
    i = 0; j = 0;
    addTests_An(i, j, m_pgrdLayoutTransistors); addSeparatingLine(i,j, m_pgrdLayoutTransistors);
    addTests_Ap(i, j, m_pgrdLayoutTransistors);
    i = 0; j = 4;
    addTests_Rn(i, j, m_pgrdLayoutTransistors); addSeparatingLine(i,j, m_pgrdLayoutTransistors);
    addTests_Rp(i, j, m_pgrdLayoutTransistors);
    i = 0; j = 8;
    addTests_Hn(i, j, m_pgrdLayoutTransistors); addSeparatingLine(i,j, m_pgrdLayoutTransistors);
    addTests_Hp(i, j, m_pgrdLayoutTransistors);
    //Разное
    i = 0; j = 0;
    addTests_pNpN(i,j, m_pgrdLayoutOther); addSeparatingLine(i,j, m_pgrdLayoutOther);
    addTests_Diod(i,j, m_pgrdLayoutOther); addSeparatingLine(i,j, m_pgrdLayoutOther);
    addTests_Capacity(i,j, m_pgrdLayoutOther);
    j = 0; for(; j < 5; ++j){addSeparatingLine(i,j, m_pgrdLayoutOther);}
    i = 0; j = 4; for(; j < 9; ++j){addSeparatingLine(i,j, m_pgrdLayoutOther);}
//-------------------------------------------------------------------------------------

    //создание вкладок
    m_pTab = new QTabWidget;
    QString strResistorsSIL = "Резисторы SIL";
    QString strResistorsMe = "Резисторы Me";
    QString strVanderPau = "Ван дер Пау";
    QString strTransistors = "Транзисторы";
    QString strOther = "Разное";
    QWidget* pPageResistorsSIL = new QWidget;
    QWidget* pPageResistorsMe = new QWidget;
    QWidget* pPageVanderPau = new QWidget;
    QWidget* pPageTransistors = new QWidget;
    QWidget* pPageOther = new QWidget;
    pPageResistorsSIL->setLayout(m_pgrdLayoutResistorsSIL);
    pPageResistorsMe->setLayout(m_pgrdLayoutResistorsMe);
    pPageVanderPau->setLayout(m_pgrdLayoutVanderPau);
    pPageTransistors->setLayout(m_pgrdLayoutTransistors);
    pPageOther->setLayout(m_pgrdLayoutOther);
    m_pTab->addTab(pPageResistorsSIL, strResistorsSIL);
    m_pTab->addTab(pPageResistorsMe, strResistorsMe);
    m_pTab->addTab(pPageVanderPau, strVanderPau);
    m_pTab->addTab(pPageTransistors, strTransistors);
    m_pTab->addTab(pPageOther, strOther);

    //создание главной компоновки со вкладками
    m_pgrdMainLayout = new QGridLayout;
    m_pgrdMainLayout->setMargin(5);
    m_pgrdMainLayout->setSpacing(5);
    m_pgrdMainLayout->addWidget(m_pTab, 0, 0, 1, 8);
    //Ok, Apply, Cancel
    m_pgrdMainLayout->addWidget(pcmdOk, 1, 5);
    m_pcmdApply->setEnabled(false);
    m_pgrdMainLayout->addWidget(m_pcmdApply, 1, 6);
    m_pgrdMainLayout->addWidget(pcmdCancel, 1, 7);
    setLayout(m_pgrdMainLayout);

    //установка валидаторов
    setValidators();
    //установка значений по умолчанию в поля
    //setDefaultMeaningsInLines();

//-------------------------------------------------------------------------------------
    //Соединения полей
    R_Dn_SIL_connections();
    R_Up_SIL_connections();
    KLVsDn_SIL_connections();
    KLVsUp_SIL_connections();
    ZsDn_SIL_connections();
    ZsUp_SIL_connections();
    Rz09Dn_SIL_connections();
    Rz09Up_SIL_connections();
    Rz05Dn_SIL_connections();
    Rz05Up_SIL_connections();
    Rz035Dn_SIL_connections();
    Rz035Up_SIL_connections();
    Rz06Dn_SIL_connections();
    Rz06Up_SIL_connections();
    Me_connections();
    VDP_connections();
    Tr_connections();
//-------------------------------------------------------------------------------------
    //Обработка ошибок
    m_TypeLimit = 1.0e+308;
    m_strInputErrorType = "Ошибка ввода значения";
    m_strInputErrorContent = " Разделитель десятичной дроби - точка; "
                             "\n диапазон ввода [-1.0e+308; 1.0e+308]";
}
//-------------------------------------------------------------------------------------------------------
LocalSettingsWin::~LocalSettingsWin(){}
//-------------------------------------------------------------------------------------------------------
//установка объекта настроек
void LocalSettingsWin::setSettings(shared_ptr<QSettings> spSettings)
{
    m_spSettings = spSettings;
}
//-------------------------------------------------------------------------------------------------------
//функции конструктора: заполнение окна виджетами
void LocalSettingsWin::createLineEdits()
{   
    //сопротивление всех силицидных структур
    m_ptxtSIL_R_Dn = new QLineEdit;
    m_ptxtSIL_R_Up = new QLineEdit;
    //---------------------------------------------------------------------------------------------
    //силицидные Кельвины
    m_ptxtSIL_KLVnM1_Dn = new QLineEdit;
    m_ptxtSIL_KLVnM1_Up = new QLineEdit;
    m_ptxtSIL_KLVpM1_Dn = new QLineEdit;
    m_ptxtSIL_KLVpM1_Up = new QLineEdit;
    m_ptxtSIL_KLVnSiM1_Dn = new QLineEdit;
    m_ptxtSIL_KLVnSiM1_Up = new QLineEdit;
    m_ptxtSIL_KLVpSiM1_Dn = new QLineEdit;
    m_ptxtSIL_KLVpSiM1_Up = new QLineEdit;
    m_ptxtSIL_KLVSiM1_Dn = new QLineEdit;
    m_ptxtSIL_KLVSiM1_Up = new QLineEdit;
    //силицидные цепочки
    m_ptxtSIL_ZnM1_Dn = new QLineEdit;
    m_ptxtSIL_ZnM1_Up = new QLineEdit;
    m_ptxtSIL_ZpM1_Dn = new QLineEdit;
    m_ptxtSIL_ZpM1_Up = new QLineEdit;
    m_ptxtSIL_ZnSiM1_Dn = new QLineEdit;
    m_ptxtSIL_ZnSiM1_Up = new QLineEdit;
    m_ptxtSIL_ZpSiM1_Dn = new QLineEdit;
    m_ptxtSIL_ZpSiM1_Up = new QLineEdit;
    m_ptxtSIL_ZSiM1_Dn = new QLineEdit;
    m_ptxtSIL_ZSiM1_Up = new QLineEdit;
    //силицидные резисторы 09
    m_ptxtRZnTiSi09_Dn = new QLineEdit;
    m_ptxtRZnTiSi09_Up = new QLineEdit;
    m_ptxtRZpTiSi09_Dn = new QLineEdit;
    m_ptxtRZpTiSi09_Up = new QLineEdit;
    m_ptxtRZnSiTiSi09_Dn = new QLineEdit;
    m_ptxtRZnSiTiSi09_Up = new QLineEdit;
    m_ptxtRZpSiTiSi09_Dn = new QLineEdit;
    m_ptxtRZpSiTiSi09_Up = new QLineEdit;
    m_ptxtRZSiTiSi09_Dn = new QLineEdit;
    m_ptxtRZSiTiSi09_Up = new QLineEdit;
    //силицидные резисторы 05
    m_ptxtRZnTiSi05_Dn = new QLineEdit;
    m_ptxtRZnTiSi05_Up = new QLineEdit;
    m_ptxtRZpTiSi05_Dn = new QLineEdit;
    m_ptxtRZpTiSi05_Up = new QLineEdit;
    m_ptxtRZnSiTiSi05_Dn = new QLineEdit;
    m_ptxtRZnSiTiSi05_Up = new QLineEdit;
    m_ptxtRZpSiTiSi05_Dn = new QLineEdit;
    m_ptxtRZpSiTiSi05_Up = new QLineEdit;
    m_ptxtRZSiTiSi05_Dn = new QLineEdit;
    m_ptxtRZSiTiSi05_Up = new QLineEdit;
    //силицидные резисторы 035
    m_ptxtRZnTiSi035_Dn = new QLineEdit;
    m_ptxtRZnTiSi035_Up = new QLineEdit;
    m_ptxtRZpTiSi035_Dn = new QLineEdit;
    m_ptxtRZpTiSi035_Up = new QLineEdit;
    m_ptxtRZnSiTiSi035_Dn = new QLineEdit;
    m_ptxtRZnSiTiSi035_Up = new QLineEdit;
    m_ptxtRZpSiTiSi035_Dn = new QLineEdit;
    m_ptxtRZpSiTiSi035_Up = new QLineEdit;
    m_ptxtRZSiTiSi035_Dn = new QLineEdit;
    m_ptxtRZSiTiSi035_Up = new QLineEdit;
    //силицидные резисторы 06
    m_ptxtRZnTiSi06_Dn = new QLineEdit;
    m_ptxtRZnTiSi06_Up = new QLineEdit;
    m_ptxtRZpTiSi06_Dn = new QLineEdit;
    m_ptxtRZpTiSi06_Up = new QLineEdit;
    m_ptxtRZnSiTiSi06_Dn = new QLineEdit;
    m_ptxtRZnSiTiSi06_Up = new QLineEdit;
    m_ptxtRZpSiTiSi06_Dn = new QLineEdit;
    m_ptxtRZpSiTiSi06_Up = new QLineEdit;
    m_ptxtRZSiTiSi06_Dn = new QLineEdit;
    m_ptxtRZSiTiSi06_Up = new QLineEdit;
    //---------------------------------------------------------------------------------------------
    //межметальные Кельвины
    m_ptxtKLV_M1M2_Dn = new QLineEdit;
    m_ptxtKLV_M1M2_Up = new QLineEdit;
    m_ptxtKLV_M2M3_Dn = new QLineEdit;
    m_ptxtKLV_M2M3_Up = new QLineEdit;
    m_ptxtKLV_M3M4_Dn = new QLineEdit;
    m_ptxtKLV_M3M4_Up = new QLineEdit;
    m_ptxtKLV_M1M4_Dn = new QLineEdit;
    m_ptxtKLV_M1M4_Up = new QLineEdit;
    //межметальные цепочки
    m_ptxtZ_M1M2_Dn = new QLineEdit;
    m_ptxtZ_M1M2_Up = new QLineEdit;
    m_ptxtZ_M2M3_Dn = new QLineEdit;
    m_ptxtZ_M2M3_Up = new QLineEdit;
    m_ptxtZ_M3M4_Dn = new QLineEdit;
    m_ptxtZ_M3M4_Up = new QLineEdit;
    m_ptxtZ_M1M4_Dn = new QLineEdit;
    m_ptxtZ_M1M4_Up = new QLineEdit;
    //меандры
    m_ptxtMean1_05_Dn = new QLineEdit;
    m_ptxtMean1_05_Up = new QLineEdit;
    m_ptxtMean1_09_Dn = new QLineEdit;
    m_ptxtMean1_09_Up = new QLineEdit;
    m_ptxtMean2_06_Dn = new QLineEdit;
    m_ptxtMean2_06_Up = new QLineEdit;
    m_ptxtMean2_09_Dn = new QLineEdit;
    m_ptxtMean2_09_Up = new QLineEdit;
    m_ptxtMean3_06_Dn = new QLineEdit;
    m_ptxtMean3_06_Up = new QLineEdit;
    m_ptxtMean3_09_Dn = new QLineEdit;
    m_ptxtMean3_09_Up = new QLineEdit;
    m_ptxtMean4_06_Dn = new QLineEdit;
    m_ptxtMean4_06_Up = new QLineEdit;
    m_ptxtMean4_09_Dn = new QLineEdit;
    m_ptxtMean4_09_Up = new QLineEdit;
    //---------------------------------------------------------------------------------------------
    //Ван дер пау
    m_ptxtVDPnWell_Dn = new QLineEdit;
    m_ptxtVDPnWell_Up = new QLineEdit;
    m_ptxtVDPpWell_Dn = new QLineEdit;
    m_ptxtVDPpWell_Up = new QLineEdit;
    m_ptxtVDPn_Dn = new QLineEdit;
    m_ptxtVDPn_Up = new QLineEdit;
    m_ptxtVDPp_Dn = new QLineEdit;
    m_ptxtVDPp_Up = new QLineEdit;
    m_ptxtVDPnSi_Dn = new QLineEdit;
    m_ptxtVDPnSi_Up = new QLineEdit;
    m_ptxtVDPpSi_Dn = new QLineEdit;
    m_ptxtVDPpSi_Up = new QLineEdit;
    //---------------------------------------------------------------------------------------------
    //транзисторы
    //An
    m_ptxtAn_Vt_Dn = new QLineEdit;
    m_ptxtAn_Vt_Up = new QLineEdit;
    m_ptxtAn_VtRevers_Dn = new QLineEdit;
    m_ptxtAn_VtRevers_Up = new QLineEdit;
    m_ptxtAn_Be_Dn = new QLineEdit;
    m_ptxtAn_Be_Up = new QLineEdit;
    m_ptxtAn_Vbr_Dn = new QLineEdit;
    m_ptxtAn_Vbr_Up = new QLineEdit;
    m_ptxtAn_Gleak_Dn = new QLineEdit;
    m_ptxtAn_Gleak_Up = new QLineEdit;
    m_ptxtAn_DSleak_Dn = new QLineEdit;
    m_ptxtAn_DSleak_Up = new QLineEdit;
    m_ptxtAn_DSw_leak_Dn = new QLineEdit;
    m_ptxtAn_DSw_leak_Up = new QLineEdit;
    m_ptxtAn_DScurrent_Dn = new QLineEdit;
    m_ptxtAn_DScurrent_Up = new QLineEdit;
    m_ptxtAn_DSw_driver_Dn = new QLineEdit;
    m_ptxtAn_DSw_driver_Up = new QLineEdit;
    //Ap
    m_ptxtAp_Vt_Dn = new QLineEdit;
    m_ptxtAp_Vt_Up = new QLineEdit;
    m_ptxtAp_VtRevers_Dn = new QLineEdit;
    m_ptxtAp_VtRevers_Up = new QLineEdit;
    m_ptxtAp_Be_Dn = new QLineEdit;
    m_ptxtAp_Be_Up = new QLineEdit;
    m_ptxtAp_Vbr_Dn = new QLineEdit;
    m_ptxtAp_Vbr_Up = new QLineEdit;
    m_ptxtAp_Gleak_Dn = new QLineEdit;
    m_ptxtAp_Gleak_Up = new QLineEdit;
    m_ptxtAp_DSleak_Dn = new QLineEdit;
    m_ptxtAp_DSleak_Up = new QLineEdit;
    m_ptxtAp_DSw_leak_Dn = new QLineEdit;
    m_ptxtAp_DSw_leak_Up = new QLineEdit;
    m_ptxtAp_DScurrent_Dn = new QLineEdit;
    m_ptxtAp_DScurrent_Up = new QLineEdit;
    m_ptxtAp_DSw_driver_Dn = new QLineEdit;
    m_ptxtAp_DSw_driver_Up = new QLineEdit;
    //Rn
    m_ptxtRn_Vt_Dn = new QLineEdit;
    m_ptxtRn_Vt_Up = new QLineEdit;
    m_ptxtRn_VtRevers_Dn = new QLineEdit;
    m_ptxtRn_VtRevers_Up = new QLineEdit;
    m_ptxtRn_Be_Dn = new QLineEdit;
    m_ptxtRn_Be_Up = new QLineEdit;
    m_ptxtRn_Vbr_Dn = new QLineEdit;
    m_ptxtRn_Vbr_Up = new QLineEdit;
    m_ptxtRn_Gleak_Dn = new QLineEdit;
    m_ptxtRn_Gleak_Up = new QLineEdit;
    m_ptxtRn_DSleak_Dn = new QLineEdit;
    m_ptxtRn_DSleak_Up = new QLineEdit;
    m_ptxtRn_DSw_leak_Dn = new QLineEdit;
    m_ptxtRn_DSw_leak_Up = new QLineEdit;
    m_ptxtRn_DScurrent_Dn = new QLineEdit;
    m_ptxtRn_DScurrent_Up = new QLineEdit;
    m_ptxtRn_DSw_driver_Dn = new QLineEdit;
    m_ptxtRn_DSw_driver_Up = new QLineEdit;
    //Rp
    m_ptxtRp_Vt_Dn = new QLineEdit;
    m_ptxtRp_Vt_Up = new QLineEdit;
    m_ptxtRp_VtRevers_Dn = new QLineEdit;
    m_ptxtRp_VtRevers_Up = new QLineEdit;
    m_ptxtRp_Be_Dn = new QLineEdit;
    m_ptxtRp_Be_Up = new QLineEdit;
    m_ptxtRp_Vbr_Dn = new QLineEdit;
    m_ptxtRp_Vbr_Up = new QLineEdit;
    m_ptxtRp_Gleak_Dn = new QLineEdit;
    m_ptxtRp_Gleak_Up = new QLineEdit;
    m_ptxtRp_DSleak_Dn = new QLineEdit;
    m_ptxtRp_DSleak_Up = new QLineEdit;
    m_ptxtRp_DSw_leak_Dn = new QLineEdit;
    m_ptxtRp_DSw_leak_Up = new QLineEdit;
    m_ptxtRp_DScurrent_Dn = new QLineEdit;
    m_ptxtRp_DScurrent_Up = new QLineEdit;
    m_ptxtRp_DSw_driver_Dn = new QLineEdit;
    m_ptxtRp_DSw_driver_Up = new QLineEdit;
    //Hn
    m_ptxtHn_Vt_Dn = new QLineEdit;
    m_ptxtHn_Vt_Up = new QLineEdit;
    m_ptxtHn_VtRevers_Dn = new QLineEdit;
    m_ptxtHn_VtRevers_Up = new QLineEdit;
    m_ptxtHn_Be_Dn = new QLineEdit;
    m_ptxtHn_Be_Up = new QLineEdit;
    m_ptxtHn_Vbr_Dn = new QLineEdit;
    m_ptxtHn_Vbr_Up = new QLineEdit;
    m_ptxtHn_Gleak_Dn = new QLineEdit;
    m_ptxtHn_Gleak_Up = new QLineEdit;
    m_ptxtHn_DSleak_Dn = new QLineEdit;
    m_ptxtHn_DSleak_Up = new QLineEdit;
    m_ptxtHn_DSw_leak_Dn = new QLineEdit;
    m_ptxtHn_DSw_leak_Up = new QLineEdit;
    m_ptxtHn_DScurrent_Dn = new QLineEdit;
    m_ptxtHn_DScurrent_Up = new QLineEdit;
    m_ptxtHn_DSw_driver_Dn = new QLineEdit;
    m_ptxtHn_DSw_driver_Up = new QLineEdit;
    //Hp
    m_ptxtHp_Vt_Dn = new QLineEdit;
    m_ptxtHp_Vt_Up = new QLineEdit;
    m_ptxtHp_VtRevers_Dn = new QLineEdit;
    m_ptxtHp_VtRevers_Up = new QLineEdit;
    m_ptxtHp_Be_Dn = new QLineEdit;
    m_ptxtHp_Be_Up = new QLineEdit;
    m_ptxtHp_Vbr_Dn = new QLineEdit;
    m_ptxtHp_Vbr_Up = new QLineEdit;
    m_ptxtHp_Gleak_Dn = new QLineEdit;
    m_ptxtHp_Gleak_Up = new QLineEdit;
    m_ptxtHp_DSleak_Dn = new QLineEdit;
    m_ptxtHp_DSleak_Up = new QLineEdit;
    m_ptxtHp_DSw_leak_Dn = new QLineEdit;
    m_ptxtHp_DSw_leak_Up = new QLineEdit;
    m_ptxtHp_DScurrent_Dn = new QLineEdit;
    m_ptxtHp_DScurrent_Up = new QLineEdit;
    m_ptxtHp_DSw_driver_Dn = new QLineEdit;
    m_ptxtHp_DSw_driver_Up = new QLineEdit;
    //---------------------------------------------------------------------------------------------
    //структуры контактирования
    m_ptxtpNpN_Dn = new QLineEdit;
    m_ptxtpNpN_Up = new QLineEdit;
    //диоды
    m_ptxtDiodn_pWell_Dn = new QLineEdit;
    m_ptxtDiodn_pWell_Up = new QLineEdit;
    m_ptxtDiodp_nWell_Dn = new QLineEdit;
    m_ptxtDiodp_nWell_Up = new QLineEdit;
    //емкости
    m_ptxtCM1M2_Dn = new QLineEdit;
    m_ptxtCM1M2_Up = new QLineEdit;
    m_ptxtCM2M3_Dn = new QLineEdit;
    m_ptxtCM2M3_Up = new QLineEdit;
    m_ptxtCM3M4_Dn = new QLineEdit;
    m_ptxtCM3M4_Up = new QLineEdit;
    m_ptxtCpSinWell_Dn = new QLineEdit;
    m_ptxtCpSinWell_Up = new QLineEdit;
    m_ptxtCnSipWell_Dn = new QLineEdit;
    m_ptxtCnSipWell_Up = new QLineEdit;
}
//-------------------------------------------------------------------------------------------------
void LocalSettingsWin::setValidators()
{
    //---------------------------------------------------------------------------------------------
    //сопротивление всех силицидных структур
    m_pdblValidator_R_Dn = new QDoubleValidator(m_ptxtSIL_R_Dn);
    m_pdblValidator_R_Up = new QDoubleValidator(m_ptxtSIL_R_Up);
    m_ptxtSIL_R_Dn->setValidator(m_pdblValidator_R_Dn);
    m_ptxtSIL_R_Up->setValidator(m_pdblValidator_R_Up);
    //---------------------------------------------------------------------------------------------
    //силицидные Кельвины
    m_pdblValidator_KLVnM1_Dn = new QDoubleValidator(m_ptxtSIL_KLVnM1_Dn);
    m_pdblValidator_KLVnM1_Up = new QDoubleValidator(m_ptxtSIL_KLVnM1_Up);

    QDoubleValidator* pdblValidator_KLVpM1_Dn = new QDoubleValidator(m_ptxtSIL_KLVpM1_Dn);
    QDoubleValidator* pdblValidator_KLVpM1_Up = new QDoubleValidator(m_ptxtSIL_KLVpM1_Up);
    QDoubleValidator* pdblValidator_KLVnSiM1_Dn = new QDoubleValidator(m_ptxtSIL_KLVnSiM1_Dn);
    QDoubleValidator* pdblValidator_KLVnSiM1_Up = new QDoubleValidator(m_ptxtSIL_KLVnSiM1_Up);
    QDoubleValidator* pdblValidator_KLVpSiM1_Dn = new QDoubleValidator(m_ptxtSIL_KLVpSiM1_Dn);
    QDoubleValidator* pdblValidator_KLVpSiM1_Up = new QDoubleValidator(m_ptxtSIL_KLVpSiM1_Up);
    QDoubleValidator* pdblValidator_KLVSiM1_Dn = new QDoubleValidator(m_ptxtSIL_KLVSiM1_Dn);
    QDoubleValidator* pdblValidator_KLVSiM1_Up = new QDoubleValidator(m_ptxtSIL_KLVSiM1_Up);
    m_ptxtSIL_KLVnM1_Dn->setValidator(m_pdblValidator_KLVnM1_Dn);
    m_ptxtSIL_KLVnM1_Up->setValidator(m_pdblValidator_KLVnM1_Up);
    m_ptxtSIL_KLVpM1_Dn->setValidator(pdblValidator_KLVpM1_Dn);
    m_ptxtSIL_KLVpM1_Up->setValidator(pdblValidator_KLVpM1_Up);
    m_ptxtSIL_KLVnSiM1_Dn->setValidator(pdblValidator_KLVnSiM1_Dn);
    m_ptxtSIL_KLVnSiM1_Up->setValidator(pdblValidator_KLVnSiM1_Up);
    m_ptxtSIL_KLVpSiM1_Dn->setValidator(pdblValidator_KLVpSiM1_Dn);
    m_ptxtSIL_KLVpSiM1_Up->setValidator(pdblValidator_KLVpSiM1_Up);
    m_ptxtSIL_KLVSiM1_Dn->setValidator(pdblValidator_KLVSiM1_Dn);
    m_ptxtSIL_KLVSiM1_Up->setValidator(pdblValidator_KLVSiM1_Up);
    //---------------------------------------------------------------------------------------------
    //силицидные цепочки
    QDoubleValidator* pdblValidator_ZnM1_Dn = new QDoubleValidator(m_ptxtSIL_ZnM1_Dn);
    QDoubleValidator* pdblValidator_ZnM1_Up = new QDoubleValidator(m_ptxtSIL_ZnM1_Up);
    QDoubleValidator* pdblValidator_ZpM1_Dn = new QDoubleValidator(m_ptxtSIL_ZpM1_Dn);
    QDoubleValidator* pdblValidator_ZpM1_Up = new QDoubleValidator(m_ptxtSIL_ZpM1_Up);
    QDoubleValidator* pdblValidator_ZnSiM1_Dn = new QDoubleValidator(m_ptxtSIL_ZnSiM1_Dn);
    QDoubleValidator* pdblValidator_ZnSiM1_Up = new QDoubleValidator(m_ptxtSIL_ZnSiM1_Up);
    QDoubleValidator* pdblValidator_ZpSiM1_Dn = new QDoubleValidator(m_ptxtSIL_ZpSiM1_Dn);
    QDoubleValidator* pdblValidator_ZpSiM1_Up = new QDoubleValidator(m_ptxtSIL_ZpSiM1_Up);
    QDoubleValidator* pdblValidator_ZSiM1_Dn = new QDoubleValidator(m_ptxtSIL_ZSiM1_Dn);
    QDoubleValidator* pdblValidator_ZSiM1_Up = new QDoubleValidator(m_ptxtSIL_ZSiM1_Up);
    m_ptxtSIL_ZnM1_Dn->setValidator(pdblValidator_ZnM1_Dn);
    m_ptxtSIL_ZnM1_Up->setValidator(pdblValidator_ZnM1_Up);
    m_ptxtSIL_ZpM1_Dn->setValidator(pdblValidator_ZpM1_Dn);
    m_ptxtSIL_ZpM1_Up->setValidator(pdblValidator_ZpM1_Up);
    m_ptxtSIL_ZnSiM1_Dn->setValidator(pdblValidator_ZnSiM1_Dn);
    m_ptxtSIL_ZnSiM1_Up->setValidator(pdblValidator_ZnSiM1_Up);
    m_ptxtSIL_ZpSiM1_Dn->setValidator(pdblValidator_ZpSiM1_Dn);
    m_ptxtSIL_ZpSiM1_Up->setValidator(pdblValidator_ZpSiM1_Up);
    m_ptxtSIL_ZSiM1_Dn->setValidator(pdblValidator_ZSiM1_Dn);
    m_ptxtSIL_ZSiM1_Up->setValidator(pdblValidator_ZSiM1_Up);
    //---------------------------------------------------------------------------------------------
    //силицидные резисторы 09
    QDoubleValidator* pdblValidator_RZnTiSi09_Dn = new QDoubleValidator(m_ptxtRZnTiSi09_Dn);
    QDoubleValidator* pdblValidator_RZnTiSi09_Up = new QDoubleValidator(m_ptxtRZnTiSi09_Up);
    QDoubleValidator* pdblValidator_RZpTiSi09_Dn = new QDoubleValidator(m_ptxtRZpTiSi09_Dn);
    QDoubleValidator* pdblValidator_RZpTiSi09_Up = new QDoubleValidator(m_ptxtRZpTiSi09_Up);
    QDoubleValidator* pdblValidator_RZnSiTiSi09_Dn = new QDoubleValidator(m_ptxtRZnSiTiSi09_Dn);
    QDoubleValidator* pdblValidator_RZnSiTiSi09_Up = new QDoubleValidator(m_ptxtRZnSiTiSi09_Up);
    QDoubleValidator* pdblValidator_RZpSiTiSi09_Dn = new QDoubleValidator(m_ptxtRZpTiSi09_Dn);
    QDoubleValidator* pdblValidator_RZpSiTiSi09_Up = new QDoubleValidator(m_ptxtRZpTiSi09_Up);
    QDoubleValidator* pdblValidator_RZSiTiSi09_Dn = new QDoubleValidator(m_ptxtRZSiTiSi09_Dn);
    QDoubleValidator* pdblValidator_RZSiTiSi09_Up = new QDoubleValidator(m_ptxtRZSiTiSi09_Up);
    m_ptxtRZnTiSi09_Dn->setValidator(pdblValidator_RZnTiSi09_Dn);
    m_ptxtRZnTiSi09_Up->setValidator(pdblValidator_RZnTiSi09_Up);
    m_ptxtRZpTiSi09_Dn->setValidator(pdblValidator_RZpTiSi09_Dn);
    m_ptxtRZpTiSi09_Up->setValidator(pdblValidator_RZpTiSi09_Up);
    m_ptxtRZnSiTiSi09_Dn->setValidator(pdblValidator_RZnSiTiSi09_Dn);
    m_ptxtRZnSiTiSi09_Up->setValidator(pdblValidator_RZnSiTiSi09_Up);
    m_ptxtRZpTiSi09_Dn->setValidator(pdblValidator_RZpSiTiSi09_Dn);
    m_ptxtRZpTiSi09_Up->setValidator(pdblValidator_RZpSiTiSi09_Up);
    m_ptxtRZSiTiSi09_Dn->setValidator(pdblValidator_RZSiTiSi09_Dn);
    m_ptxtRZSiTiSi09_Up->setValidator(pdblValidator_RZSiTiSi09_Up);
    //---------------------------------------------------------------------------------------------
    //силицидные резисторы 05
    QDoubleValidator* pdblValidator_RZnTiSi05_Dn = new QDoubleValidator(m_ptxtRZnTiSi05_Dn);
    QDoubleValidator* pdblValidator_RZnTiSi05_Up = new QDoubleValidator(m_ptxtRZnTiSi05_Up);
    QDoubleValidator* pdblValidator_RZpTiSi05_Dn = new QDoubleValidator(m_ptxtRZpTiSi05_Dn);
    QDoubleValidator* pdblValidator_RZpTiSi05_Up = new QDoubleValidator(m_ptxtRZpTiSi05_Up);
    QDoubleValidator* pdblValidator_RZnSiTiSi05_Dn = new QDoubleValidator(m_ptxtRZnSiTiSi05_Dn);
    QDoubleValidator* pdblValidator_RZnSiTiSi05_Up = new QDoubleValidator(m_ptxtRZnSiTiSi05_Up);
    QDoubleValidator* pdblValidator_RZpSiTiSi05_Dn = new QDoubleValidator(m_ptxtRZpTiSi05_Dn);
    QDoubleValidator* pdblValidator_RZpSiTiSi05_Up = new QDoubleValidator(m_ptxtRZpTiSi05_Up);
    QDoubleValidator* pdblValidator_RZSiTiSi05_Dn = new QDoubleValidator(m_ptxtRZSiTiSi05_Dn);
    QDoubleValidator* pdblValidator_RZSiTiSi05_Up = new QDoubleValidator(m_ptxtRZSiTiSi05_Up);
    m_ptxtRZnTiSi05_Dn->setValidator(pdblValidator_RZnTiSi05_Dn);
    m_ptxtRZnTiSi05_Up->setValidator(pdblValidator_RZnTiSi05_Up);
    m_ptxtRZpTiSi05_Dn->setValidator(pdblValidator_RZpTiSi05_Dn);
    m_ptxtRZpTiSi05_Up->setValidator(pdblValidator_RZpTiSi05_Up);
    m_ptxtRZnSiTiSi05_Dn->setValidator(pdblValidator_RZnSiTiSi05_Dn);
    m_ptxtRZnSiTiSi05_Up->setValidator(pdblValidator_RZnSiTiSi05_Up);
    m_ptxtRZpTiSi05_Dn->setValidator(pdblValidator_RZpSiTiSi05_Dn);
    m_ptxtRZpTiSi05_Up->setValidator(pdblValidator_RZpSiTiSi05_Up);
    m_ptxtRZSiTiSi05_Dn->setValidator(pdblValidator_RZSiTiSi05_Dn);
    m_ptxtRZSiTiSi05_Up->setValidator(pdblValidator_RZSiTiSi05_Up);
    //---------------------------------------------------------------------------------------------
    //силицидные резисторы 035
    QDoubleValidator* pdblValidator_RZnTiSi035_Dn = new QDoubleValidator(m_ptxtRZnTiSi035_Dn);
    QDoubleValidator* pdblValidator_RZnTiSi035_Up = new QDoubleValidator(m_ptxtRZnTiSi035_Up);
    QDoubleValidator* pdblValidator_RZpTiSi035_Dn = new QDoubleValidator(m_ptxtRZpTiSi035_Dn);
    QDoubleValidator* pdblValidator_RZpTiSi035_Up = new QDoubleValidator(m_ptxtRZpTiSi035_Up);
    QDoubleValidator* pdblValidator_RZnSiTiSi035_Dn = new QDoubleValidator(m_ptxtRZnSiTiSi035_Dn);
    QDoubleValidator* pdblValidator_RZnSiTiSi035_Up = new QDoubleValidator(m_ptxtRZnSiTiSi035_Up);
    QDoubleValidator* pdblValidator_RZpSiTiSi035_Dn = new QDoubleValidator(m_ptxtRZpTiSi035_Dn);
    QDoubleValidator* pdblValidator_RZpSiTiSi035_Up = new QDoubleValidator(m_ptxtRZpTiSi035_Up);
    QDoubleValidator* pdblValidator_RZSiTiSi035_Dn = new QDoubleValidator(m_ptxtRZSiTiSi035_Dn);
    QDoubleValidator* pdblValidator_RZSiTiSi035_Up = new QDoubleValidator(m_ptxtRZSiTiSi035_Up);
    m_ptxtRZnTiSi035_Dn->setValidator(pdblValidator_RZnTiSi035_Dn);
    m_ptxtRZnTiSi035_Up->setValidator(pdblValidator_RZnTiSi035_Up);
    m_ptxtRZpTiSi035_Dn->setValidator(pdblValidator_RZpTiSi035_Dn);
    m_ptxtRZpTiSi035_Up->setValidator(pdblValidator_RZpTiSi035_Up);
    m_ptxtRZnSiTiSi035_Dn->setValidator(pdblValidator_RZnSiTiSi035_Dn);
    m_ptxtRZnSiTiSi035_Up->setValidator(pdblValidator_RZnSiTiSi035_Up);
    m_ptxtRZpTiSi035_Dn->setValidator(pdblValidator_RZpSiTiSi035_Dn);
    m_ptxtRZpTiSi035_Up->setValidator(pdblValidator_RZpSiTiSi035_Up);
    m_ptxtRZSiTiSi035_Dn->setValidator(pdblValidator_RZSiTiSi035_Dn);
    m_ptxtRZSiTiSi035_Up->setValidator(pdblValidator_RZSiTiSi035_Up);
    //---------------------------------------------------------------------------------------------
    //силицидные резисторы 06
    QDoubleValidator* pdblValidator_RZnTiSi06_Dn = new QDoubleValidator(m_ptxtRZnTiSi06_Dn);
    QDoubleValidator* pdblValidator_RZnTiSi06_Up = new QDoubleValidator(m_ptxtRZnTiSi06_Up);
    QDoubleValidator* pdblValidator_RZpTiSi06_Dn = new QDoubleValidator(m_ptxtRZpTiSi06_Dn);
    QDoubleValidator* pdblValidator_RZpTiSi06_Up = new QDoubleValidator(m_ptxtRZpTiSi06_Up);
    QDoubleValidator* pdblValidator_RZnSiTiSi06_Dn = new QDoubleValidator(m_ptxtRZnSiTiSi06_Dn);
    QDoubleValidator* pdblValidator_RZnSiTiSi06_Up = new QDoubleValidator(m_ptxtRZnSiTiSi06_Up);
    QDoubleValidator* pdblValidator_RZpSiTiSi06_Dn = new QDoubleValidator(m_ptxtRZpTiSi06_Dn);
    QDoubleValidator* pdblValidator_RZpSiTiSi06_Up = new QDoubleValidator(m_ptxtRZpTiSi06_Up);
    QDoubleValidator* pdblValidator_RZSiTiSi06_Dn = new QDoubleValidator(m_ptxtRZSiTiSi06_Dn);
    QDoubleValidator* pdblValidator_RZSiTiSi06_Up = new QDoubleValidator(m_ptxtRZSiTiSi06_Up);
    m_ptxtRZnTiSi06_Dn->setValidator(pdblValidator_RZnTiSi06_Dn);
    m_ptxtRZnTiSi06_Up->setValidator(pdblValidator_RZnTiSi06_Up);
    m_ptxtRZpTiSi06_Dn->setValidator(pdblValidator_RZpTiSi06_Dn);
    m_ptxtRZpTiSi06_Up->setValidator(pdblValidator_RZpTiSi06_Up);
    m_ptxtRZnSiTiSi06_Dn->setValidator(pdblValidator_RZnSiTiSi06_Dn);
    m_ptxtRZnSiTiSi06_Up->setValidator(pdblValidator_RZnSiTiSi06_Up);
    m_ptxtRZpTiSi06_Dn->setValidator(pdblValidator_RZpSiTiSi06_Dn);
    m_ptxtRZpTiSi06_Up->setValidator(pdblValidator_RZpSiTiSi06_Up);
    m_ptxtRZSiTiSi06_Dn->setValidator(pdblValidator_RZSiTiSi06_Dn);
    m_ptxtRZSiTiSi06_Up->setValidator(pdblValidator_RZSiTiSi06_Up);
    //---------------------------------------------------------------------------------------------
    //Ван дер пау
    QDoubleValidator* pdblValidator_VDPnWell_Dn = new QDoubleValidator(m_ptxtVDPnWell_Dn);
    QDoubleValidator* pdblValidator_VDPnWell_Up = new QDoubleValidator(m_ptxtVDPnWell_Up);
    QDoubleValidator* pdblValidator_VDPpWell_Dn = new QDoubleValidator(m_ptxtVDPpWell_Dn);
    QDoubleValidator* pdblValidator_VDPpWell_Up = new QDoubleValidator(m_ptxtVDPpWell_Up);
    QDoubleValidator* pdblValidator_VDPn_Dn = new QDoubleValidator(m_ptxtVDPn_Dn);
    QDoubleValidator* pdblValidator_VDPn_Up = new QDoubleValidator(m_ptxtVDPn_Up);
    QDoubleValidator* pdblValidator_VDPp_Dn = new QDoubleValidator(m_ptxtVDPp_Dn);
    QDoubleValidator* pdblValidator_VDPp_Up = new QDoubleValidator(m_ptxtVDPp_Up);
    QDoubleValidator* pdblValidator_VDPnSi_Dn = new QDoubleValidator(m_ptxtVDPnSi_Dn);
    QDoubleValidator* pdblValidator_VDPnSi_Up = new QDoubleValidator(m_ptxtVDPnSi_Up);
    QDoubleValidator* pdblValidator_VDPpSi_Dn = new QDoubleValidator(m_ptxtVDPpSi_Dn);
    QDoubleValidator* pdblValidator_VDPpSi_Up = new QDoubleValidator(m_ptxtVDPpSi_Up);
    m_ptxtVDPnWell_Dn->setValidator(pdblValidator_VDPnWell_Dn);
    m_ptxtVDPnWell_Up->setValidator(pdblValidator_VDPnWell_Up);
    m_ptxtVDPpWell_Dn->setValidator(pdblValidator_VDPpWell_Dn);
    m_ptxtVDPpWell_Up->setValidator(pdblValidator_VDPpWell_Up);
    m_ptxtVDPn_Dn->setValidator(pdblValidator_VDPn_Dn);
    m_ptxtVDPn_Up->setValidator(pdblValidator_VDPn_Up);
    m_ptxtVDPp_Dn->setValidator(pdblValidator_VDPp_Dn);
    m_ptxtVDPp_Up->setValidator(pdblValidator_VDPp_Up);
    m_ptxtVDPnSi_Dn->setValidator(pdblValidator_VDPnSi_Dn);
    m_ptxtVDPnSi_Up->setValidator(pdblValidator_VDPnSi_Up);
    m_ptxtVDPpSi_Dn->setValidator(pdblValidator_VDPpSi_Dn);
    m_ptxtVDPpSi_Up->setValidator(pdblValidator_VDPpSi_Up);
    //---------------------------------------------------------------------------------------------
    //An
    QDoubleValidator* pdblValidator_An_Vt_Dn = new QDoubleValidator(m_ptxtAn_Vt_Dn);
    QDoubleValidator* pdblValidator_An_VtRevers_Dn = new QDoubleValidator(m_ptxtAn_VtRevers_Dn);
    QDoubleValidator* pdblValidator_An_Be_Dn = new QDoubleValidator(m_ptxtAn_Be_Dn);
    QDoubleValidator* pdblValidator_An_Vbr_Dn = new QDoubleValidator(m_ptxtAn_Vbr_Dn);
    QDoubleValidator* pdblValidator_An_Gleak_Dn = new QDoubleValidator(m_ptxtAn_Gleak_Dn);
    QDoubleValidator* pdblValidator_An_DSleak_Dn = new QDoubleValidator(m_ptxtAn_DSleak_Dn);
    QDoubleValidator* pdblValidator_An_DSw_leak_Dn = new QDoubleValidator(m_ptxtAn_DSw_leak_Dn);
    QDoubleValidator* pdblValidator_An_DScurrent_Dn = new QDoubleValidator(m_ptxtAn_DScurrent_Dn);
    QDoubleValidator* pdblValidator_An_DSw_driver_Dn = new QDoubleValidator(m_ptxtAn_DSw_driver_Dn);
    m_ptxtAn_Vt_Dn->setValidator(pdblValidator_An_Vt_Dn);
    m_ptxtAn_VtRevers_Dn->setValidator(pdblValidator_An_VtRevers_Dn);
    m_ptxtAn_Be_Dn->setValidator(pdblValidator_An_Be_Dn);
    m_ptxtAn_Vbr_Dn->setValidator(pdblValidator_An_Vbr_Dn);
    m_ptxtAn_Gleak_Dn->setValidator(pdblValidator_An_Gleak_Dn);
    m_ptxtAn_DSleak_Dn->setValidator(pdblValidator_An_DSleak_Dn);
    m_ptxtAn_DSw_leak_Dn->setValidator(pdblValidator_An_DSw_leak_Dn);
    m_ptxtAn_DScurrent_Dn->setValidator(pdblValidator_An_DScurrent_Dn);
    m_ptxtAn_DSw_driver_Dn->setValidator(pdblValidator_An_DSw_driver_Dn);

    QDoubleValidator* pdblValidator_An_Vt_Up = new QDoubleValidator(m_ptxtAn_Vt_Up);
    QDoubleValidator* pdblValidator_An_VtRevers_Up = new QDoubleValidator(m_ptxtAn_VtRevers_Up);
    QDoubleValidator* pdblValidator_An_Be_Up = new QDoubleValidator(m_ptxtAn_Be_Up);
    QDoubleValidator* pdblValidator_An_Vbr_Up = new QDoubleValidator(m_ptxtAn_Vbr_Up);
    QDoubleValidator* pdblValidator_An_Gleak_Up = new QDoubleValidator(m_ptxtAn_Gleak_Up);
    QDoubleValidator* pdblValidator_An_DSleak_Up = new QDoubleValidator(m_ptxtAn_DSleak_Up);
    QDoubleValidator* pdblValidator_An_DSw_leak_Up = new QDoubleValidator(m_ptxtAn_DSw_leak_Up);
    QDoubleValidator* pdblValidator_An_DScurrent_Up = new QDoubleValidator(m_ptxtAn_DScurrent_Up);
    QDoubleValidator* pdblValidator_An_DSw_driver_Up = new QDoubleValidator(m_ptxtAn_DSw_driver_Up);
    m_ptxtAn_Vt_Up->setValidator(pdblValidator_An_Vt_Up);
    m_ptxtAn_VtRevers_Up->setValidator(pdblValidator_An_VtRevers_Up);
    m_ptxtAn_Be_Up->setValidator(pdblValidator_An_Be_Up);
    m_ptxtAn_Vbr_Up->setValidator(pdblValidator_An_Vbr_Up);
    m_ptxtAn_Gleak_Up->setValidator(pdblValidator_An_Gleak_Up);
    m_ptxtAn_DSleak_Up->setValidator(pdblValidator_An_DSleak_Up);
    m_ptxtAn_DSw_leak_Up->setValidator(pdblValidator_An_DSw_leak_Up);
    m_ptxtAn_DScurrent_Up->setValidator(pdblValidator_An_DScurrent_Up);
    m_ptxtAn_DSw_driver_Up->setValidator(pdblValidator_An_DSw_driver_Up);
    //---------------------------------------------------------------------------------------------
    //Ap
    QDoubleValidator* pdblValidator_Ap_Vt_Dn = new QDoubleValidator(m_ptxtAp_Vt_Dn);
    QDoubleValidator* pdblValidator_Ap_VtRevers_Dn = new QDoubleValidator(m_ptxtAp_VtRevers_Dn);
    QDoubleValidator* pdblValidator_Ap_Be_Dn = new QDoubleValidator(m_ptxtAp_Be_Dn);
    QDoubleValidator* pdblValidator_Ap_Vbr_Dn = new QDoubleValidator(m_ptxtAp_Vbr_Dn);
    QDoubleValidator* pdblValidator_Ap_Gleak_Dn = new QDoubleValidator(m_ptxtAp_Gleak_Dn);
    QDoubleValidator* pdblValidator_Ap_DSleak_Dn = new QDoubleValidator(m_ptxtAp_DSleak_Dn);
    QDoubleValidator* pdblValidator_Ap_DSw_leak_Dn = new QDoubleValidator(m_ptxtAp_DSw_leak_Dn);
    QDoubleValidator* pdblValidator_Ap_DScurrent_Dn = new QDoubleValidator(m_ptxtAp_DScurrent_Dn);
    QDoubleValidator* pdblValidator_Ap_DSw_driver_Dn = new QDoubleValidator(m_ptxtAp_DSw_driver_Dn);
    m_ptxtAp_Vt_Dn->setValidator(pdblValidator_Ap_Vt_Dn);
    m_ptxtAp_VtRevers_Dn->setValidator(pdblValidator_Ap_VtRevers_Dn);
    m_ptxtAp_Be_Dn->setValidator(pdblValidator_Ap_Be_Dn);
    m_ptxtAp_Vbr_Dn->setValidator(pdblValidator_Ap_Vbr_Dn);
    m_ptxtAp_Gleak_Dn->setValidator(pdblValidator_Ap_Gleak_Dn);
    m_ptxtAp_DSleak_Dn->setValidator(pdblValidator_Ap_DSleak_Dn);
    m_ptxtAp_DSw_leak_Dn->setValidator(pdblValidator_Ap_DSw_leak_Dn);
    m_ptxtAp_DScurrent_Dn->setValidator(pdblValidator_Ap_DScurrent_Dn);
    m_ptxtAp_DSw_driver_Dn->setValidator(pdblValidator_Ap_DSw_driver_Dn);

    QDoubleValidator* pdblValidator_Ap_Vt_Up = new QDoubleValidator(m_ptxtAp_Vt_Up);
    QDoubleValidator* pdblValidator_Ap_VtRevers_Up = new QDoubleValidator(m_ptxtAp_VtRevers_Up);
    QDoubleValidator* pdblValidator_Ap_Be_Up = new QDoubleValidator(m_ptxtAp_Be_Up);
    QDoubleValidator* pdblValidator_Ap_Vbr_Up = new QDoubleValidator(m_ptxtAp_Vbr_Up);
    QDoubleValidator* pdblValidator_Ap_Gleak_Up = new QDoubleValidator(m_ptxtAp_Gleak_Up);
    QDoubleValidator* pdblValidator_Ap_DSleak_Up = new QDoubleValidator(m_ptxtAp_DSleak_Up);
    QDoubleValidator* pdblValidator_Ap_DSw_leak_Up = new QDoubleValidator(m_ptxtAp_DSw_leak_Up);
    QDoubleValidator* pdblValidator_Ap_DScurrent_Up = new QDoubleValidator(m_ptxtAp_DScurrent_Up);
    QDoubleValidator* pdblValidator_Ap_DSw_driver_Up = new QDoubleValidator(m_ptxtAp_DSw_driver_Up);
    m_ptxtAp_Vt_Up->setValidator(pdblValidator_Ap_Vt_Up);
    m_ptxtAp_VtRevers_Up->setValidator(pdblValidator_Ap_VtRevers_Up);
    m_ptxtAp_Be_Up->setValidator(pdblValidator_Ap_Be_Up);
    m_ptxtAp_Vbr_Up->setValidator(pdblValidator_Ap_Vbr_Up);
    m_ptxtAp_Gleak_Up->setValidator(pdblValidator_Ap_Gleak_Up);
    m_ptxtAp_DSleak_Up->setValidator(pdblValidator_Ap_DSleak_Up);
    m_ptxtAp_DSw_leak_Up->setValidator(pdblValidator_Ap_DSw_leak_Up);
    m_ptxtAp_DScurrent_Up->setValidator(pdblValidator_Ap_DScurrent_Up);
    m_ptxtAp_DSw_driver_Up->setValidator(pdblValidator_Ap_DSw_driver_Up);
    //---------------------------------------------------------------------------------------------
    //Rn
    QDoubleValidator* pdblValidator_Rn_Vt_Dn = new QDoubleValidator(m_ptxtRn_Vt_Dn);
    QDoubleValidator* pdblValidator_Rn_VtRevers_Dn = new QDoubleValidator(m_ptxtRn_VtRevers_Dn);
    QDoubleValidator* pdblValidator_Rn_Be_Dn = new QDoubleValidator(m_ptxtRn_Be_Dn);
    QDoubleValidator* pdblValidator_Rn_Vbr_Dn = new QDoubleValidator(m_ptxtRn_Vbr_Dn);
    QDoubleValidator* pdblValidator_Rn_Gleak_Dn = new QDoubleValidator(m_ptxtRn_Gleak_Dn);
    QDoubleValidator* pdblValidator_Rn_DSleak_Dn = new QDoubleValidator(m_ptxtRn_DSleak_Dn);
    QDoubleValidator* pdblValidator_Rn_DSw_leak_Dn = new QDoubleValidator(m_ptxtRn_DSw_leak_Dn);
    QDoubleValidator* pdblValidator_Rn_DScurrent_Dn = new QDoubleValidator(m_ptxtRn_DScurrent_Dn);
    QDoubleValidator* pdblValidator_Rn_DSw_driver_Dn = new QDoubleValidator(m_ptxtRn_DSw_driver_Dn);
    m_ptxtRn_Vt_Dn->setValidator(pdblValidator_Rn_Vt_Dn);
    m_ptxtRn_VtRevers_Dn->setValidator(pdblValidator_Rn_VtRevers_Dn);
    m_ptxtRn_Be_Dn->setValidator(pdblValidator_Rn_Be_Dn);
    m_ptxtRn_Vbr_Dn->setValidator(pdblValidator_Rn_Vbr_Dn);
    m_ptxtRn_Gleak_Dn->setValidator(pdblValidator_Rn_Gleak_Dn);
    m_ptxtRn_DSleak_Dn->setValidator(pdblValidator_Rn_DSleak_Dn);
    m_ptxtRn_DSw_leak_Dn->setValidator(pdblValidator_Rn_DSw_leak_Dn);
    m_ptxtRn_DScurrent_Dn->setValidator(pdblValidator_Rn_DScurrent_Dn);
    m_ptxtRn_DSw_driver_Dn->setValidator(pdblValidator_Rn_DSw_driver_Dn);

    QDoubleValidator* pdblValidator_Rn_Vt_Up = new QDoubleValidator(m_ptxtRn_Vt_Up);
    QDoubleValidator* pdblValidator_Rn_VtRevers_Up = new QDoubleValidator(m_ptxtRn_VtRevers_Up);
    QDoubleValidator* pdblValidator_Rn_Be_Up = new QDoubleValidator(m_ptxtRn_Be_Up);
    QDoubleValidator* pdblValidator_Rn_Vbr_Up = new QDoubleValidator(m_ptxtRn_Vbr_Up);
    QDoubleValidator* pdblValidator_Rn_Gleak_Up = new QDoubleValidator(m_ptxtRn_Gleak_Up);
    QDoubleValidator* pdblValidator_Rn_DSleak_Up = new QDoubleValidator(m_ptxtRn_DSleak_Up);
    QDoubleValidator* pdblValidator_Rn_DSw_leak_Up = new QDoubleValidator(m_ptxtRn_DSw_leak_Up);
    QDoubleValidator* pdblValidator_Rn_DScurrent_Up = new QDoubleValidator(m_ptxtRn_DScurrent_Up);
    QDoubleValidator* pdblValidator_Rn_DSw_driver_Up = new QDoubleValidator(m_ptxtRn_DSw_driver_Up);
    m_ptxtRn_Vt_Up->setValidator(pdblValidator_Rn_Vt_Up);
    m_ptxtRn_VtRevers_Up->setValidator(pdblValidator_Rn_VtRevers_Up);
    m_ptxtRn_Be_Up->setValidator(pdblValidator_Rn_Be_Up);
    m_ptxtRn_Vbr_Up->setValidator(pdblValidator_Rn_Vbr_Up);
    m_ptxtRn_Gleak_Up->setValidator(pdblValidator_Rn_Gleak_Up);
    m_ptxtRn_DSleak_Up->setValidator(pdblValidator_Rn_DSleak_Up);
    m_ptxtRn_DSw_leak_Up->setValidator(pdblValidator_Rn_DSw_leak_Up);
    m_ptxtRn_DScurrent_Up->setValidator(pdblValidator_Rn_DScurrent_Up);
    m_ptxtRn_DSw_driver_Up->setValidator(pdblValidator_Rn_DSw_driver_Up);
    //---------------------------------------------------------------------------------------------
    //Rp
    QDoubleValidator* pdblValidator_Rp_Vt_Dn = new QDoubleValidator(m_ptxtRp_Vt_Dn);
    QDoubleValidator* pdblValidator_Rp_VtRevers_Dn = new QDoubleValidator(m_ptxtRp_VtRevers_Dn);
    QDoubleValidator* pdblValidator_Rp_Be_Dn = new QDoubleValidator(m_ptxtRp_Be_Dn);
    QDoubleValidator* pdblValidator_Rp_Vbr_Dn = new QDoubleValidator(m_ptxtRp_Vbr_Dn);
    QDoubleValidator* pdblValidator_Rp_Gleak_Dn = new QDoubleValidator(m_ptxtRp_Gleak_Dn);
    QDoubleValidator* pdblValidator_Rp_DSleak_Dn = new QDoubleValidator(m_ptxtRp_DSleak_Dn);
    QDoubleValidator* pdblValidator_Rp_DSw_leak_Dn = new QDoubleValidator(m_ptxtRp_DSw_leak_Dn);
    QDoubleValidator* pdblValidator_Rp_DScurrent_Dn = new QDoubleValidator(m_ptxtRp_DScurrent_Dn);
    QDoubleValidator* pdblValidator_Rp_DSw_driver_Dn = new QDoubleValidator(m_ptxtRp_DSw_driver_Dn);
    m_ptxtRp_Vt_Dn->setValidator(pdblValidator_Rp_Vt_Dn);
    m_ptxtRp_VtRevers_Dn->setValidator(pdblValidator_Rp_VtRevers_Dn);
    m_ptxtRp_Be_Dn->setValidator(pdblValidator_Rp_Be_Dn);
    m_ptxtRp_Vbr_Dn->setValidator(pdblValidator_Rp_Vbr_Dn);
    m_ptxtRp_Gleak_Dn->setValidator(pdblValidator_Rp_Gleak_Dn);
    m_ptxtRp_DSleak_Dn->setValidator(pdblValidator_Rp_DSleak_Dn);
    m_ptxtRp_DSw_leak_Dn->setValidator(pdblValidator_Rp_DSw_leak_Dn);
    m_ptxtRp_DScurrent_Dn->setValidator(pdblValidator_Rp_DScurrent_Dn);
    m_ptxtRp_DSw_driver_Dn->setValidator(pdblValidator_Rp_DSw_driver_Dn);

    QDoubleValidator* pdblValidator_Rp_Vt_Up = new QDoubleValidator(m_ptxtRp_Vt_Up);
    QDoubleValidator* pdblValidator_Rp_VtRevers_Up = new QDoubleValidator(m_ptxtRp_VtRevers_Up);
    QDoubleValidator* pdblValidator_Rp_Be_Up = new QDoubleValidator(m_ptxtRp_Be_Up);
    QDoubleValidator* pdblValidator_Rp_Vbr_Up = new QDoubleValidator(m_ptxtRp_Vbr_Up);
    QDoubleValidator* pdblValidator_Rp_Gleak_Up = new QDoubleValidator(m_ptxtRp_Gleak_Up);
    QDoubleValidator* pdblValidator_Rp_DSleak_Up = new QDoubleValidator(m_ptxtRp_DSleak_Up);
    QDoubleValidator* pdblValidator_Rp_DSw_leak_Up = new QDoubleValidator(m_ptxtRp_DSw_leak_Up);
    QDoubleValidator* pdblValidator_Rp_DScurrent_Up = new QDoubleValidator(m_ptxtRp_DScurrent_Up);
    QDoubleValidator* pdblValidator_Rp_DSw_driver_Up = new QDoubleValidator(m_ptxtRp_DSw_driver_Up);
    m_ptxtRp_Vt_Up->setValidator(pdblValidator_Rp_Vt_Up);
    m_ptxtRp_VtRevers_Up->setValidator(pdblValidator_Rp_VtRevers_Up);
    m_ptxtRp_Be_Up->setValidator(pdblValidator_Rp_Be_Up);
    m_ptxtRp_Vbr_Up->setValidator(pdblValidator_Rp_Vbr_Up);
    m_ptxtRp_Gleak_Up->setValidator(pdblValidator_Rp_Gleak_Up);
    m_ptxtRp_DSleak_Up->setValidator(pdblValidator_Rp_DSleak_Up);
    m_ptxtRp_DSw_leak_Up->setValidator(pdblValidator_Rp_DSw_leak_Up);
    m_ptxtRp_DScurrent_Up->setValidator(pdblValidator_Rp_DScurrent_Up);
    m_ptxtRp_DSw_driver_Up->setValidator(pdblValidator_Rp_DSw_driver_Up);
    //---------------------------------------------------------------------------------------------
    //Hn
    QDoubleValidator* pdblValidator_Hn_Vt_Dn = new QDoubleValidator(m_ptxtHn_Vt_Dn);
    QDoubleValidator* pdblValidator_Hn_VtRevers_Dn = new QDoubleValidator(m_ptxtHn_VtRevers_Dn);
    QDoubleValidator* pdblValidator_Hn_Be_Dn = new QDoubleValidator(m_ptxtHn_Be_Dn);
    QDoubleValidator* pdblValidator_Hn_Vbr_Dn = new QDoubleValidator(m_ptxtHn_Vbr_Dn);
    QDoubleValidator* pdblValidator_Hn_Gleak_Dn = new QDoubleValidator(m_ptxtHn_Gleak_Dn);
    QDoubleValidator* pdblValidator_Hn_DSleak_Dn = new QDoubleValidator(m_ptxtHn_DSleak_Dn);
    QDoubleValidator* pdblValidator_Hn_DSw_leak_Dn = new QDoubleValidator(m_ptxtHn_DSw_leak_Dn);
    QDoubleValidator* pdblValidator_Hn_DScurrent_Dn = new QDoubleValidator(m_ptxtHn_DScurrent_Dn);
    QDoubleValidator* pdblValidator_Hn_DSw_driver_Dn = new QDoubleValidator(m_ptxtHn_DSw_driver_Dn);
    m_ptxtHn_Vt_Dn->setValidator(pdblValidator_Hn_Vt_Dn);
    m_ptxtHn_VtRevers_Dn->setValidator(pdblValidator_Hn_VtRevers_Dn);
    m_ptxtHn_Be_Dn->setValidator(pdblValidator_Hn_Be_Dn);
    m_ptxtHn_Vbr_Dn->setValidator(pdblValidator_Hn_Vbr_Dn);
    m_ptxtHn_Gleak_Dn->setValidator(pdblValidator_Hn_Gleak_Dn);
    m_ptxtHn_DSleak_Dn->setValidator(pdblValidator_Hn_DSleak_Dn);
    m_ptxtHn_DSw_leak_Dn->setValidator(pdblValidator_Hn_DSw_leak_Dn);
    m_ptxtHn_DScurrent_Dn->setValidator(pdblValidator_Hn_DScurrent_Dn);
    m_ptxtHn_DSw_driver_Dn->setValidator(pdblValidator_Hn_DSw_driver_Dn);

    QDoubleValidator* pdblValidator_Hn_Vt_Up = new QDoubleValidator(m_ptxtHn_Vt_Up);
    QDoubleValidator* pdblValidator_Hn_VtRevers_Up = new QDoubleValidator(m_ptxtHn_VtRevers_Up);
    QDoubleValidator* pdblValidator_Hn_Be_Up = new QDoubleValidator(m_ptxtHn_Be_Up);
    QDoubleValidator* pdblValidator_Hn_Vbr_Up = new QDoubleValidator(m_ptxtHn_Vbr_Up);
    QDoubleValidator* pdblValidator_Hn_Gleak_Up = new QDoubleValidator(m_ptxtHn_Gleak_Up);
    QDoubleValidator* pdblValidator_Hn_DSleak_Up = new QDoubleValidator(m_ptxtHn_DSleak_Up);
    QDoubleValidator* pdblValidator_Hn_DSw_leak_Up = new QDoubleValidator(m_ptxtHn_DSw_leak_Up);
    QDoubleValidator* pdblValidator_Hn_DScurrent_Up = new QDoubleValidator(m_ptxtHn_DScurrent_Up);
    QDoubleValidator* pdblValidator_Hn_DSw_driver_Up = new QDoubleValidator(m_ptxtHn_DSw_driver_Up);
    m_ptxtHn_Vt_Up->setValidator(pdblValidator_Hn_Vt_Up);
    m_ptxtHn_VtRevers_Up->setValidator(pdblValidator_Hn_VtRevers_Up);
    m_ptxtHn_Be_Up->setValidator(pdblValidator_Hn_Be_Up);
    m_ptxtHn_Vbr_Up->setValidator(pdblValidator_Hn_Vbr_Up);
    m_ptxtHn_Gleak_Up->setValidator(pdblValidator_Hn_Gleak_Up);
    m_ptxtHn_DSleak_Up->setValidator(pdblValidator_Hn_DSleak_Up);
    m_ptxtHn_DSw_leak_Up->setValidator(pdblValidator_Hn_DSw_leak_Up);
    m_ptxtHn_DScurrent_Up->setValidator(pdblValidator_Hn_DScurrent_Up);
    m_ptxtHn_DSw_driver_Up->setValidator(pdblValidator_Hn_DSw_driver_Up);
    //---------------------------------------------------------------------------------------------
    //Hp
    QDoubleValidator* pdblValidator_Hp_Vt_Dn = new QDoubleValidator(m_ptxtHp_Vt_Dn);
    QDoubleValidator* pdblValidator_Hp_VtRevers_Dn = new QDoubleValidator(m_ptxtHp_VtRevers_Dn);
    QDoubleValidator* pdblValidator_Hp_Be_Dn = new QDoubleValidator(m_ptxtHp_Be_Dn);
    QDoubleValidator* pdblValidator_Hp_Vbr_Dn = new QDoubleValidator(m_ptxtHp_Vbr_Dn);
    QDoubleValidator* pdblValidator_Hp_Gleak_Dn = new QDoubleValidator(m_ptxtHp_Gleak_Dn);
    QDoubleValidator* pdblValidator_Hp_DSleak_Dn = new QDoubleValidator(m_ptxtHp_DSleak_Dn);
    QDoubleValidator* pdblValidator_Hp_DSw_leak_Dn = new QDoubleValidator(m_ptxtHp_DSw_leak_Dn);
    QDoubleValidator* pdblValidator_Hp_DScurrent_Dn = new QDoubleValidator(m_ptxtHp_DScurrent_Dn);
    QDoubleValidator* pdblValidator_Hp_DSw_driver_Dn = new QDoubleValidator(m_ptxtHp_DSw_driver_Dn);
    m_ptxtHp_Vt_Dn->setValidator(pdblValidator_Hp_Vt_Dn);
    m_ptxtHp_VtRevers_Dn->setValidator(pdblValidator_Hp_VtRevers_Dn);
    m_ptxtHp_Be_Dn->setValidator(pdblValidator_Hp_Be_Dn);
    m_ptxtHp_Vbr_Dn->setValidator(pdblValidator_Hp_Vbr_Dn);
    m_ptxtHp_Gleak_Dn->setValidator(pdblValidator_Hp_Gleak_Dn);
    m_ptxtHp_DSleak_Dn->setValidator(pdblValidator_Hp_DSleak_Dn);
    m_ptxtHp_DSw_leak_Dn->setValidator(pdblValidator_Hp_DSw_leak_Dn);
    m_ptxtHp_DScurrent_Dn->setValidator(pdblValidator_Hp_DScurrent_Dn);
    m_ptxtHp_DSw_driver_Dn->setValidator(pdblValidator_Hp_DSw_driver_Dn);

    QDoubleValidator* pdblValidator_Hp_Vt_Up = new QDoubleValidator(m_ptxtHp_Vt_Up);
    QDoubleValidator* pdblValidator_Hp_VtRevers_Up = new QDoubleValidator(m_ptxtHp_VtRevers_Up);
    QDoubleValidator* pdblValidator_Hp_Be_Up = new QDoubleValidator(m_ptxtHp_Be_Up);
    QDoubleValidator* pdblValidator_Hp_Vbr_Up = new QDoubleValidator(m_ptxtHp_Vbr_Up);
    QDoubleValidator* pdblValidator_Hp_Gleak_Up = new QDoubleValidator(m_ptxtHp_Gleak_Up);
    QDoubleValidator* pdblValidator_Hp_DSleak_Up = new QDoubleValidator(m_ptxtHp_DSleak_Up);
    QDoubleValidator* pdblValidator_Hp_DSw_leak_Up = new QDoubleValidator(m_ptxtHp_DSw_leak_Up);
    QDoubleValidator* pdblValidator_Hp_DScurrent_Up = new QDoubleValidator(m_ptxtHp_DScurrent_Up);
    QDoubleValidator* pdblValidator_Hp_DSw_driver_Up = new QDoubleValidator(m_ptxtHp_DSw_driver_Up);
    m_ptxtHp_Vt_Up->setValidator(pdblValidator_Hp_Vt_Up);
    m_ptxtHp_VtRevers_Up->setValidator(pdblValidator_Hp_VtRevers_Up);
    m_ptxtHp_Be_Up->setValidator(pdblValidator_Hp_Be_Up);
    m_ptxtHp_Vbr_Up->setValidator(pdblValidator_Hp_Vbr_Up);
    m_ptxtHp_Gleak_Up->setValidator(pdblValidator_Hp_Gleak_Up);
    m_ptxtHp_DSleak_Up->setValidator(pdblValidator_Hp_DSleak_Up);
    m_ptxtHp_DSw_leak_Up->setValidator(pdblValidator_Hp_DSw_leak_Up);
    m_ptxtHp_DScurrent_Up->setValidator(pdblValidator_Hp_DScurrent_Up);
    m_ptxtHp_DSw_driver_Up->setValidator(pdblValidator_Hp_DSw_driver_Up);
    //---------------------------------------------------------------------------------------------
    //pNpN
    QDoubleValidator* pdblValidator_pNpN_Dn = new QDoubleValidator(m_ptxtpNpN_Dn);
    m_ptxtpNpN_Dn->setValidator(pdblValidator_pNpN_Dn);

    QDoubleValidator* pdblValidator_pNpN_Up = new QDoubleValidator(m_ptxtpNpN_Up);
    m_ptxtpNpN_Up->setValidator(pdblValidator_pNpN_Up);
    //---------------------------------------------------------------------------------------------
    //диоды
    QDoubleValidator* pdblValidator_Diodn_pWell_Dn = new QDoubleValidator(m_ptxtDiodn_pWell_Dn);
    QDoubleValidator* pdblValidator_Diodp_nWell_Dn = new QDoubleValidator(m_ptxtDiodp_nWell_Dn);
    m_ptxtDiodn_pWell_Dn->setValidator(pdblValidator_Diodn_pWell_Dn);
    m_ptxtDiodp_nWell_Dn->setValidator(pdblValidator_Diodp_nWell_Dn);

    QDoubleValidator* pdblValidator_Diodn_pWell_Up = new QDoubleValidator(m_ptxtDiodn_pWell_Up);
    QDoubleValidator* pdblValidator_Diodp_nWell_Up = new QDoubleValidator(m_ptxtDiodp_nWell_Up);
    m_ptxtDiodn_pWell_Up->setValidator(pdblValidator_Diodn_pWell_Up);
    m_ptxtDiodp_nWell_Up->setValidator(pdblValidator_Diodp_nWell_Up);
    //---------------------------------------------------------------------------------------------
    //емкости
    QDoubleValidator* pdblValidator_CM1M2_Dn = new QDoubleValidator(m_ptxtCM1M2_Dn);
    QDoubleValidator* pdblValidator_CM2M3_Dn = new QDoubleValidator(m_ptxtCM2M3_Dn);
    QDoubleValidator* pdblValidator_CM3M4_Dn = new QDoubleValidator(m_ptxtCM3M4_Dn);
    m_ptxtCM1M2_Dn->setValidator(pdblValidator_CM1M2_Dn);
    m_ptxtCM2M3_Dn->setValidator(pdblValidator_CM2M3_Dn);
    m_ptxtCM3M4_Dn->setValidator(pdblValidator_CM3M4_Dn);

    QDoubleValidator* pdblValidator_CM1M2_Up = new QDoubleValidator(m_ptxtCM1M2_Up);
    QDoubleValidator* pdblValidator_CM2M3_Up = new QDoubleValidator(m_ptxtCM2M3_Up);
    QDoubleValidator* pdblValidator_CM3M4_Up = new QDoubleValidator(m_ptxtCM3M4_Up);
    m_ptxtCM1M2_Up->setValidator(pdblValidator_CM1M2_Up);
    m_ptxtCM2M3_Up->setValidator(pdblValidator_CM2M3_Up);
    m_ptxtCM3M4_Up->setValidator(pdblValidator_CM3M4_Up);

    QDoubleValidator* pdblValidator_CpSinWell_Dn = new QDoubleValidator(m_ptxtCpSinWell_Dn);
    QDoubleValidator* pdblValidator_CnSipWell_Dn = new QDoubleValidator(m_ptxtCnSipWell_Dn);
    m_ptxtCpSinWell_Dn->setValidator(pdblValidator_CpSinWell_Dn);
    m_ptxtCnSipWell_Dn->setValidator(pdblValidator_CnSipWell_Dn);

    QDoubleValidator* pdblValidator_CpSinWell_Up = new QDoubleValidator(m_ptxtCpSinWell_Up);
    QDoubleValidator* pdblValidator_CnSipWell_Up = new QDoubleValidator(m_ptxtCnSipWell_Up);
    m_ptxtCpSinWell_Up  ->setValidator(pdblValidator_CpSinWell_Up);
    m_ptxtCnSipWell_Up->setValidator(pdblValidator_CnSipWell_Up);
    //---------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------
void LocalSettingsWin::createLabels()
{
    //создание лейблов тестовых элементов
    //---------------------------------------------------------------------------------------------
    //сопротивление всех силицидных структур
    m_plblSIL_R = new QLabel("  R_SIL ");
    //---------------------------------------------------------------------------------------------
    //cилицидные Кельвины
    m_plblSIL_KLVnM1 = new QLabel("  KLVnM1 ");
    m_plblSIL_KLVpM1 = new QLabel("  KLVpM1 ");
    m_plblSIL_KLVnSiM1 = new QLabel("  KLVnSiM1 ");
    m_plblSIL_KLVpSiM1 = new QLabel("  KLVpSiM1 ");
    m_plblSIL_KLVSiM1 = new QLabel("  KLVSiM1 ");
    //cилицидные цепочки
    m_plblSIL_ZnM1 = new QLabel("  ZnM1 ");
    m_plblSIL_ZpM1 = new QLabel("  ZpM1 ");
    m_plblSIL_ZnSiM1 = new QLabel("  ZnSiM1 ");
    m_plblSIL_ZpSiM1 = new QLabel("  ZpSiM1 ");
    m_plblSIL_ZSiM1 = new QLabel("  ZSiM1 ");
    //силицидные резисторы 09
    m_plblRZnTiSi09 = new QLabel("   RZnTiSi09 ");
    m_plblRZpTiSi09 = new QLabel("   RZpTiSi09 ");
    m_plblRZnSiTiSi09 = new QLabel("   RZnSiTiSi09 ");
    m_plblRZpSiTiSi09 = new QLabel("   RZpSiTiSi09 ");
    m_plblRZSiTiSi09 = new QLabel("   RZSiTiSi09 ");
    //cилицидные резисторы 05
    m_plblRZnTiSi05 = new QLabel("   RZnTiSi05 ");
    m_plblRZpTiSi05 = new QLabel("   RZpTiSi05 ");
    m_plblRZnSiTiSi05 = new QLabel("   RZnSiTiSi05 ");
    m_plblRZpSiTiSi05 = new QLabel("   RZpSiTiSi05 ");
    m_plblRZSiTiSi05 = new QLabel("   RZSiTiSi05 ");
    //cилицидные резисторы 035
    m_plblRZnTiSi035 = new QLabel("   RZnTiSi035 ");
    m_plblRZpTiSi035 = new QLabel("   RZpTiSi035 ");
    m_plblRZnSiTiSi035 = new QLabel("   RZnSiTiSi035 ");
    m_plblRZpSiTiSi035 = new QLabel("   RZpSiTiSi035 ");
    m_plblRZSiTiSi035 = new QLabel("   RZSiTiSi035 ");
    //cилицидные резисторы 06
    m_plblRZnTiSi06 = new QLabel("   RZnTiSi06 ");
    m_plblRZpTiSi06 = new QLabel("   RZpTiSi06 ");
    m_plblRZnSiTiSi06 = new QLabel("   RZnSiTiSi06 ");
    m_plblRZpSiTiSi06 = new QLabel("   RZpSiTiSi06 ");
    m_plblRZSiTiSi06 = new QLabel("   RZSiTiSi06 ");
    //---------------------------------------------------------------------------------------------
    //межметальные Кельвины
    m_plblKLV_M1M2 = new QLabel("  KLV_M1M2 ");
    m_plblKLV_M2M3 = new QLabel("  KLV_M2M3 ");
    m_plblKLV_M3M4 = new QLabel("  KLV_M3M4 ");
    m_plblKLV_M1M4 = new QLabel("  KLV_M1M4 ");
    //межметальные цепочки
    m_plblZ_M1M2 = new QLabel("  Z_M1M2 ");
    m_plblZ_M2M3 = new QLabel("  Z_M2M3 ");
    m_plblZ_M3M4 = new QLabel("  Z_M3M4 ");
    m_plblZ_M1M4 = new QLabel("  Z_M1M4 ");
    //меандры
    m_plblMean1_05 = new QLabel("  Mean1_05 ");
    m_plblMean1_09 = new QLabel("  Mean1_09 ");
    m_plblMean2_06 = new QLabel("  Mean2_06 ");
    m_plblMean2_09 = new QLabel("  Mean2_09 ");
    m_plblMean3_06 = new QLabel("  Mean3_06 ");
    m_plblMean3_09 = new QLabel("  Mean3_09 ");
    m_plblMean4_06 = new QLabel("  Mean4_06 ");
    m_plblMean4_09 = new QLabel("  Mean4_09 ");
    //---------------------------------------------------------------------------------------------
    //Ван дер Пау
    m_plblVDPnWell = new QLabel("  VDPnWell ");
    m_plblVDPpWell = new QLabel("  VDPpWell ");
    m_plblVDPn = new QLabel("  VDPn ");
    m_plblVDPp = new QLabel("  VDPp ");
    m_plblVDPnSi = new QLabel("  VDPnSi ");
    m_plblVDPpSi = new QLabel("  VDPpSi ");
    //---------------------------------------------------------------------------------------------
    //Транзисторы
    //An
    m_plblAn_Vt = new QLabel("  An_Vt ");
    m_plblAn_VtRevers = new QLabel("  An_VtRevers ");
    m_plblAn_Be = new QLabel("  An_Be ");
    m_plblAn_Vbr = new QLabel("  An_Vbr ");
    m_plblAn_Gleak = new QLabel("  An_Gleak ");
    m_plblAn_DSleak = new QLabel("  An_DSleak ");
    m_plblAn_DSw_leak = new QLabel("  An_DSw_leak ");
    m_plblAn_DScurrent = new QLabel("  An_DScurrent ");
    m_plblAn_DSw_driver = new QLabel("  An_DSw_driver ");
    //Ap
    m_plblAp_Vt = new QLabel("  Ap_Vt ");
    m_plblAp_VtRevers = new QLabel("  Ap_VtRevers ");
    m_plblAp_Be = new QLabel("  Ap_Be ");
    m_plblAp_Vbr = new QLabel("  Ap_Vbr ");
    m_plblAp_Gleak = new QLabel("  Ap_Gleak ");
    m_plblAp_DSleak = new QLabel("  Ap_DSleak ");
    m_plblAp_DSw_leak = new QLabel("  Ap_DSw_leak ");
    m_plblAp_DScurrent = new QLabel("  Ap_DScurrent ");
    m_plblAp_DSw_driver = new QLabel("  Ap_DSw_driver ");
    //Rn
    m_plblRn_Vt = new QLabel("  Rn_Vt ");
    m_plblRn_VtRevers = new QLabel("  Rn_VtRevers ");
    m_plblRn_Be = new QLabel("  Rn_Be ");
    m_plblRn_Vbr = new QLabel("  Rn_Vbr ");
    m_plblRn_Gleak = new QLabel("  Rn_Gleak ");
    m_plblRn_DSleak = new QLabel("  Rn_DSleak ");
    m_plblRn_DSw_leak = new QLabel("  Rn_DSw_leak ");
    m_plblRn_DScurrent = new QLabel("  Rn_DScurrent ");
    m_plblRn_DSw_driver = new QLabel("  Rn_DSw_driver ");
    //Rp
    m_plblRp_Vt = new QLabel("  Rp_Vt ");
    m_plblRp_VtRevers = new QLabel("  Rp_VtRevers ");
    m_plblRp_Be = new QLabel("  Rp_Be ");
    m_plblRp_Vbr = new QLabel("  Rp_Vbr ");
    m_plblRp_Gleak = new QLabel("  Rp_Gleak ");
    m_plblRp_DSleak = new QLabel("  Rp_DSleak ");
    m_plblRp_DSw_leak = new QLabel("  Rp_DSw_leak ");
    m_plblRp_DScurrent = new QLabel("  Rp_DScurrent ");
    m_plblRp_DSw_driver = new QLabel("  Rp_DSw_driver ");
    //Hn
    m_plblHn_Vt = new QLabel("  Hn_Vt ");
    m_plblHn_VtRevers = new QLabel("  Hn_VtRevers ");
    m_plblHn_Be = new QLabel("  Hn_Be ");
    m_plblHn_Vbr = new QLabel("  Hn_Vbr ");
    m_plblHn_Gleak = new QLabel("  Hn_Gleak ");
    m_plblHn_DSleak = new QLabel("  Hn_DSleak ");
    m_plblHn_DSw_leak = new QLabel("  Hn_DSw_leak ");
    m_plblHn_DScurrent = new QLabel("  Hn_DScurrent ");
    m_plblHn_DSw_driver = new QLabel("  Hn_DSw_driver ");
    //Hp
    m_plblHp_Vt = new QLabel("  Hp_Vt ");
    m_plblHp_VtRevers = new QLabel("  Hp_VtRevers ");
    m_plblHp_Be = new QLabel("  Hp_Be ");
    m_plblHp_Vbr = new QLabel("  Hp_Vbr ");
    m_plblHp_Gleak = new QLabel("  Hp_Gleak ");
    m_plblHp_DSleak = new QLabel("  Hp_DSleak ");
    m_plblHp_DSw_leak = new QLabel("  Hp_DSw_leak ");
    m_plblHp_DScurrent = new QLabel("  Hp_DScurrent ");
    m_plblHp_DSw_driver = new QLabel("  Hp_DSw_driver ");
    //---------------------------------------------------------------------------------------------
    //структуры контактирования
    m_plblpNpN = new QLabel("  pNpN ");
    //диоды
    m_plblDiodn_pWell = new QLabel("  Diodn_pWell ");
    m_plblDiodp_nWell = new QLabel("  Diodp_nWell ");
    //емкости
    m_plblCM1M2 = new QLabel("  CM1M2 ");
    m_plblCM2M3 = new QLabel("  CM2M3 ");
    m_plblCM3M4 = new QLabel("  CM3M4 ");
    m_plblCpSinWell = new QLabel("  CpSinWell ");
    m_plblCnSipWell = new QLabel("  CnSipWell ");
}
//-------------------------------------------------------------------------------------------------------
void LocalSettingsWin::addSeparatingLine(int &i, int j, QGridLayout* pgrdLayout)
{
    //separating line
    ++i; //j = 0;
    QLabel* lblSeparatingLine = new QLabel("          ");
    pgrdLayout->addWidget(lblSeparatingLine, i, j);
}
//-------------------------------------------------------------------------------------------------------
QLabel* LocalSettingsWin::initLabelHyp()
{
    QLabel *plblHyp = new QLabel("-");
    return plblHyp;
}
//-------------------------------------------------------------------------------------------------------
//i = 0
void LocalSettingsWin::addAll_R_SIL(int &i, int j, QGridLayout *pgrdLayout)
{
    //int jInput = j;
    //All_R_SIL
    //++i;  
    pgrdLayout->addWidget(m_plblSIL_R, i, j++);
    pgrdLayout->addWidget(m_ptxtSIL_R_Dn, i, j++);
    pgrdLayout->addWidget(initLabelHyp(), i, j++);
    pgrdLayout->addWidget(m_ptxtSIL_R_Up, i, j++);
    //
}

void LocalSettingsWin::addTests_KLV_SIL(int &i, int j, QGridLayout *pgrdLayout)
{
    int jInput = j;
    //KLV_nM1 - на N-моно-Si
    ++i;
    pgrdLayout->addWidget(m_plblSIL_KLVnM1, i, j++);
    pgrdLayout->addWidget(m_ptxtSIL_KLVnM1_Dn, i, j++);
    pgrdLayout->addWidget(initLabelHyp(), i, j++);
    pgrdLayout->addWidget(m_ptxtSIL_KLVnM1_Up, i, j++);
    //KLV_pM1 - на P-моно-Si
    ++i; j = jInput;
    pgrdLayout->addWidget(m_plblSIL_KLVpM1, i, j++);
    pgrdLayout->addWidget(m_ptxtSIL_KLVpM1_Dn, i, j++);
    pgrdLayout->addWidget(initLabelHyp(), i, j++);
    pgrdLayout->addWidget(m_ptxtSIL_KLVpM1_Up, i, j++);
    //KLV_nSiM1 - на N-поли-Si
    ++i; j = jInput;
    pgrdLayout->addWidget(m_plblSIL_KLVnSiM1, i, j++);
    pgrdLayout->addWidget(m_ptxtSIL_KLVnSiM1_Dn, i, j++);
    pgrdLayout->addWidget(initLabelHyp(), i, j++);
    pgrdLayout->addWidget(m_ptxtSIL_KLVnSiM1_Up, i, j++);
    //KLV_pSiM1 - на P-поли-Si
    ++i; j = jInput;
    pgrdLayout->addWidget(m_plblSIL_KLVpSiM1, i, j++);
    pgrdLayout->addWidget(m_ptxtSIL_KLVpSiM1_Dn, i, j++);
    pgrdLayout->addWidget(initLabelHyp(), i, j++);
    pgrdLayout->addWidget(m_ptxtSIL_KLVpSiM1_Up, i, j++);
    //KLV_SiM1 - на поли-Si
    ++i; j = jInput;
    pgrdLayout->addWidget(m_plblSIL_KLVSiM1, i, j++);
    pgrdLayout->addWidget(m_ptxtSIL_KLVSiM1_Dn, i, j++);
    pgrdLayout->addWidget(initLabelHyp(), i, j++);
    pgrdLayout->addWidget(m_ptxtSIL_KLVSiM1_Up, i, j++);
}
//-------------------------------------------------------------------------------------------------------
void LocalSettingsWin::addTests_Z_SIL(int &i, int j, QGridLayout *pgrdLayout)
{
    int jInput = j;
    //Z_nM1 - на N-моно-Si
    ++i;
    pgrdLayout->addWidget(m_plblSIL_ZnM1, i, j++);
    pgrdLayout->addWidget(m_ptxtSIL_ZnM1_Dn, i, j++);
    pgrdLayout->addWidget(initLabelHyp(), i, j++);
    pgrdLayout->addWidget(m_ptxtSIL_ZnM1_Up, i, j++);
    //Z_pM1 - на P-моно-Si
    ++i; j = jInput;
    pgrdLayout->addWidget(m_plblSIL_ZpM1, i, j++);
    pgrdLayout->addWidget(m_ptxtSIL_ZpM1_Dn, i, j++);
    pgrdLayout->addWidget(initLabelHyp(), i, j++);
    pgrdLayout->addWidget(m_ptxtSIL_ZpM1_Up, i, j++);
    //Z_nSiM1 - на N-поли-Si
    ++i; j = jInput;
    pgrdLayout->addWidget(m_plblSIL_ZnSiM1, i, j++);
    pgrdLayout->addWidget(m_ptxtSIL_ZnSiM1_Dn, i, j++);
    pgrdLayout->addWidget(initLabelHyp(), i, j++);
    pgrdLayout->addWidget(m_ptxtSIL_ZnSiM1_Up, i, j++);
    //Z_pSiM1 - на P-поли-Si
    ++i; j = jInput;
    pgrdLayout->addWidget(m_plblSIL_ZpSiM1, i, j++);
    pgrdLayout->addWidget(m_ptxtSIL_ZpSiM1_Dn, i, j++);
    pgrdLayout->addWidget(initLabelHyp(), i, j++);
    pgrdLayout->addWidget(m_ptxtSIL_ZpSiM1_Up, i, j++);
    //Z_SiM1 - на поли-Si
    ++i; j = jInput;
    pgrdLayout->addWidget(m_plblSIL_ZSiM1, i, j++);
    pgrdLayout->addWidget(m_ptxtSIL_ZSiM1_Dn, i, j++);
    pgrdLayout->addWidget(initLabelHyp(), i, j++);
    pgrdLayout->addWidget(m_ptxtSIL_ZSiM1_Up, i, j++);
}
//-------------------------------------------------------------------------------------------------------
//i = 0
void LocalSettingsWin::addTests_RzSIL09(int &i, int j, QGridLayout *pgrdLayout)
{
    int jInput = j;
    //RZnTiSi09 - на N-моно-Si
    //++i;
    pgrdLayout->addWidget(m_plblRZnTiSi09, i, j++);
    pgrdLayout->addWidget(m_ptxtRZnTiSi09_Dn, i, j++);
    pgrdLayout->addWidget(initLabelHyp(), i, j++);
    pgrdLayout->addWidget(m_ptxtRZnTiSi09_Up, i, j++);
    //RZpTiSi09 - на P-моно-Si
    ++i; j = jInput;
    pgrdLayout->addWidget(m_plblRZpTiSi09, i, j++);
    pgrdLayout->addWidget(m_ptxtRZpTiSi09_Dn, i, j++);
    pgrdLayout->addWidget(initLabelHyp(), i, j++);
    pgrdLayout->addWidget(m_ptxtRZpTiSi09_Up, i, j++);
    //RZnSiTiSi09 - на N-поли-Si
    ++i; j = jInput;
    pgrdLayout->addWidget(m_plblRZnSiTiSi09, i, j++);
    pgrdLayout->addWidget(m_ptxtRZnSiTiSi09_Dn, i, j++);
    pgrdLayout->addWidget(initLabelHyp(), i, j++);
    pgrdLayout->addWidget(m_ptxtRZnSiTiSi09_Up, i, j++);
    //RZpSiTiSi09 - на P-поли-Si
    ++i; j = jInput;
    pgrdLayout->addWidget(m_plblRZpSiTiSi09, i, j++);
    pgrdLayout->addWidget(m_ptxtRZpSiTiSi09_Dn, i, j++);
    pgrdLayout->addWidget(initLabelHyp(), i, j++);
    pgrdLayout->addWidget(m_ptxtRZpSiTiSi09_Up, i, j++);
    //RZSiTiSi09 - на поли-Si
    ++i; j = jInput;
    pgrdLayout->addWidget(m_plblRZSiTiSi09, i, j++);
    pgrdLayout->addWidget(m_ptxtRZSiTiSi09_Dn, i, j++);
    pgrdLayout->addWidget(initLabelHyp(), i, j++);
    pgrdLayout->addWidget(m_ptxtRZSiTiSi09_Up, i, j++);
}
//-------------------------------------------------------------------------------------------------------
void LocalSettingsWin::addTests_RzSIL05(int &i, int j, QGridLayout *pgrdLayout)
{
    int jInput = j;
    //RZnTiSi05 - на N-моно-Si
    ++i;
    pgrdLayout->addWidget(m_plblRZnTiSi05, i, j++);
    pgrdLayout->addWidget(m_ptxtRZnTiSi05_Dn, i, j++);
    pgrdLayout->addWidget(initLabelHyp(), i, j++);
    pgrdLayout->addWidget(m_ptxtRZnTiSi05_Up, i, j++);
    //RZpTiSi05 - на P-моно-Si
    ++i; j = jInput;
    pgrdLayout->addWidget(m_plblRZpTiSi05, i, j++);
    pgrdLayout->addWidget(m_ptxtRZpTiSi05_Dn, i, j++);
    pgrdLayout->addWidget(initLabelHyp(), i, j++);
    pgrdLayout->addWidget(m_ptxtRZpTiSi05_Up, i, j++);
    //RZnSiTiSi05 - на N-поли-Si
    ++i; j = jInput;
    pgrdLayout->addWidget(m_plblRZnSiTiSi05, i, j++);
    pgrdLayout->addWidget(m_ptxtRZnSiTiSi05_Dn, i, j++);
    pgrdLayout->addWidget(initLabelHyp(), i, j++);
    pgrdLayout->addWidget(m_ptxtRZnSiTiSi05_Up, i, j++);
    //RZpSiTiSi05 - на P-поли-Si
    ++i; j = jInput;
    pgrdLayout->addWidget(m_plblRZpSiTiSi05, i, j++);
    pgrdLayout->addWidget(m_ptxtRZpSiTiSi05_Dn, i, j++);
    pgrdLayout->addWidget(initLabelHyp(), i, j++);
    pgrdLayout->addWidget(m_ptxtRZpSiTiSi05_Up, i, j++);
    //RZSiTiSi09 - на поли-Si
    ++i; j = jInput;
    pgrdLayout->addWidget(m_plblRZSiTiSi05, i, j++);
    pgrdLayout->addWidget(m_ptxtRZSiTiSi05_Dn, i, j++);
    pgrdLayout->addWidget(initLabelHyp(), i, j++);
    pgrdLayout->addWidget(m_ptxtRZSiTiSi05_Up, i, j++);

}
//-------------------------------------------------------------------------------------------------------
void LocalSettingsWin::addTests_RzSIL035(int &i, int j, QGridLayout *pgrdLayout)
{
    int jInput = j;
    //RZnTiSi035 - на N-моно-Si
    ++i;
    pgrdLayout->addWidget(m_plblRZnTiSi035, i, j++);
    pgrdLayout->addWidget(m_ptxtRZnTiSi035_Dn, i, j++);
    pgrdLayout->addWidget(initLabelHyp(), i, j++);
    pgrdLayout->addWidget(m_ptxtRZnTiSi035_Up, i, j++);
    //RZpTiSi035 - на P-моно-Si
    ++i; j = jInput;
    pgrdLayout->addWidget(m_plblRZpTiSi035, i, j++);
    pgrdLayout->addWidget(m_ptxtRZpTiSi035_Dn, i, j++);
    pgrdLayout->addWidget(initLabelHyp(), i, j++);
    pgrdLayout->addWidget(m_ptxtRZpTiSi035_Up, i, j++);
    //RZnSiTiSi035 - на N-поли-Si
    ++i; j = jInput;
    pgrdLayout->addWidget(m_plblRZnSiTiSi035, i, j++);
    pgrdLayout->addWidget(m_ptxtRZnSiTiSi035_Dn, i, j++);
    pgrdLayout->addWidget(initLabelHyp(), i, j++);
    pgrdLayout->addWidget(m_ptxtRZnSiTiSi035_Up, i, j++);
    //RZpSiTiSi035 - на P-поли-Si
    ++i; j = jInput;
    pgrdLayout->addWidget(m_plblRZpSiTiSi035, i, j++);
    pgrdLayout->addWidget(m_ptxtRZpSiTiSi035_Dn, i, j++);
    pgrdLayout->addWidget(initLabelHyp(), i, j++);
    pgrdLayout->addWidget(m_ptxtRZpSiTiSi035_Up, i, j++);
    //RZSiTiSi035 - на поли-Si
    ++i; j = jInput;
    pgrdLayout->addWidget(m_plblRZSiTiSi035, i, j++);
    pgrdLayout->addWidget(m_ptxtRZSiTiSi035_Dn, i, j++);
    pgrdLayout->addWidget(initLabelHyp(), i, j++);
    pgrdLayout->addWidget(m_ptxtRZSiTiSi035_Up, i, j++);
}
//-------------------------------------------------------------------------------------------------------
void LocalSettingsWin::addTests_RzSIL06(int &i, int j, QGridLayout *pgrdLayout)
{
    int jInput = j;
    //RZnTiSi06 - на N-моно-Si
    ++i;
    pgrdLayout->addWidget(m_plblRZnTiSi06, i, j++);
    pgrdLayout->addWidget(m_ptxtRZnTiSi06_Dn, i, j++);
    pgrdLayout->addWidget(initLabelHyp(), i, j++);
    pgrdLayout->addWidget(m_ptxtRZnTiSi06_Up, i, j++);
    //RZpTiSi06 - на P-моно-Si
    ++i; j = jInput;
    pgrdLayout->addWidget(m_plblRZpTiSi06, i, j++);
    pgrdLayout->addWidget(m_ptxtRZpTiSi06_Dn, i, j++);
    pgrdLayout->addWidget(initLabelHyp(), i, j++);
    pgrdLayout->addWidget(m_ptxtRZpTiSi06_Up, i, j++);
    //RZnSiTiSi06 - на N-поли-Si
    ++i; j = jInput;
    pgrdLayout->addWidget(m_plblRZnSiTiSi06, i, j++);
    pgrdLayout->addWidget(m_ptxtRZnSiTiSi06_Dn, i, j++);
    pgrdLayout->addWidget(initLabelHyp(), i, j++);
    pgrdLayout->addWidget(m_ptxtRZnSiTiSi06_Up, i, j++);
    //RZpSiTiSi05 - на P-поли-Si
    ++i; j = jInput;
    pgrdLayout->addWidget(m_plblRZpSiTiSi06, i, j++);
    pgrdLayout->addWidget(m_ptxtRZpSiTiSi06_Dn, i, j++);
    pgrdLayout->addWidget(initLabelHyp(), i, j++);
    pgrdLayout->addWidget(m_ptxtRZpSiTiSi06_Up, i, j++);
    //RZSiTiSi09 - на поли-Si
    ++i; j = jInput;
    pgrdLayout->addWidget(m_plblRZSiTiSi06, i, j++);
    pgrdLayout->addWidget(m_ptxtRZSiTiSi06_Dn, i, j++);
    pgrdLayout->addWidget(initLabelHyp(), i, j++);
    pgrdLayout->addWidget(m_ptxtRZSiTiSi06_Up, i, j++);
}
//-------------------------------------------------------------------------------------------------------
//i = 0
void LocalSettingsWin::addTests_KLV_MM(int &i, int j, QGridLayout *pgrdLayout)
{
    int jInput = j;
    //KLV_M1M2
    //++i;
    pgrdLayout->addWidget(m_plblKLV_M1M2, i, j++);
    pgrdLayout->addWidget(m_ptxtKLV_M1M2_Dn, i, j++);
    pgrdLayout->addWidget(initLabelHyp(), i, j++);
    pgrdLayout->addWidget(m_ptxtKLV_M1M2_Up, i, j++);
    //KLV_M2M3
    ++i; j = jInput;
    pgrdLayout->addWidget(m_plblKLV_M2M3, i, j++);
    pgrdLayout->addWidget(m_ptxtKLV_M2M3_Dn, i, j++);
    pgrdLayout->addWidget(initLabelHyp(), i, j++);
    pgrdLayout->addWidget(m_ptxtKLV_M2M3_Up, i, j++);
    //KLV_M3M4
    ++i; j = jInput;
    pgrdLayout->addWidget(m_plblKLV_M3M4, i, j++);
    pgrdLayout->addWidget(m_ptxtKLV_M3M4_Dn, i, j++);
    pgrdLayout->addWidget(initLabelHyp(), i, j++);
    pgrdLayout->addWidget(m_ptxtKLV_M3M4_Up, i, j++);
    //KLV_M1M4
    ++i; j = jInput;
    pgrdLayout->addWidget(m_plblKLV_M1M4, i, j++);
    pgrdLayout->addWidget(m_ptxtKLV_M1M4_Dn, i, j++);
    pgrdLayout->addWidget(initLabelHyp(), i, j++);
    pgrdLayout->addWidget(m_ptxtKLV_M1M4_Up, i, j++);
}
//-------------------------------------------------------------------------------------------------------
void LocalSettingsWin::addTests_Z_MM(int &i, int j, QGridLayout *pgrdLayout)
{
    int jInput = j;
    //Z_M1M2
    ++i;
    pgrdLayout->addWidget(m_plblZ_M1M2, i, j++);
    pgrdLayout->addWidget(m_ptxtZ_M1M2_Dn, i, j++);
    pgrdLayout->addWidget(initLabelHyp(), i, j++);
    pgrdLayout->addWidget(m_ptxtZ_M1M2_Up, i, j++);
    //Z_M2M3
    ++i; j = jInput;
    pgrdLayout->addWidget(m_plblZ_M2M3, i, j++);
    pgrdLayout->addWidget(m_ptxtZ_M2M3_Dn, i, j++);
    pgrdLayout->addWidget(initLabelHyp(), i, j++);
    pgrdLayout->addWidget(m_ptxtZ_M2M3_Up, i, j++);
    //Z_M3M4
    ++i; j = jInput;
    pgrdLayout->addWidget(m_plblZ_M3M4, i, j++);
    pgrdLayout->addWidget(m_ptxtZ_M3M4_Dn, i, j++);
    pgrdLayout->addWidget(initLabelHyp(), i, j++);
    pgrdLayout->addWidget(m_ptxtZ_M3M4_Up, i, j++);
    //Z_M1M4
    ++i; j = jInput;
    pgrdLayout->addWidget(m_plblZ_M1M4, i, j++);
    pgrdLayout->addWidget(m_ptxtZ_M1M4_Dn, i, j++);
    pgrdLayout->addWidget(initLabelHyp(), i, j++);
    pgrdLayout->addWidget(m_ptxtZ_M1M4_Up, i, j++);
}
//-------------------------------------------------------------------------------------------------------
//i = 0
void LocalSettingsWin::addTests_Meanders(int &i, int j, QGridLayout *pgrdLayout)
{
    int jInput = j;
    //Mean1_05
    //++i;
    pgrdLayout->addWidget(m_plblMean1_05, i, j++);
    pgrdLayout->addWidget(m_ptxtMean1_05_Dn, i, j++);
    pgrdLayout->addWidget(initLabelHyp(), i, j++);
    pgrdLayout->addWidget(m_ptxtMean1_05_Up, i, j++);
    //Mean1_09
    ++i; j = jInput;
    pgrdLayout->addWidget(m_plblMean1_09, i, j++);
    pgrdLayout->addWidget(m_ptxtMean1_09_Dn, i, j++);
    pgrdLayout->addWidget(initLabelHyp(), i, j++);
    pgrdLayout->addWidget(m_ptxtMean1_09_Up, i, j++);
    //Mean2_06
    ++i;
    ++i; j = jInput;
    pgrdLayout->addWidget(m_plblMean2_06, i, j++);
    pgrdLayout->addWidget(m_ptxtMean2_06_Dn, i, j++);
    pgrdLayout->addWidget(initLabelHyp(), i, j++);
    pgrdLayout->addWidget(m_ptxtMean2_06_Up, i, j++);
    //Mean2_09
    ++i; j = jInput;
    pgrdLayout->addWidget(m_plblMean2_09, i, j++);
    pgrdLayout->addWidget(m_ptxtMean2_09_Dn, i, j++);
    pgrdLayout->addWidget(initLabelHyp(), i, j++);
    pgrdLayout->addWidget(m_ptxtMean2_09_Up, i, j++);
    //Mean3_06
    ++i;
    ++i; j = jInput;
    pgrdLayout->addWidget(m_plblMean3_06, i, j++);
    pgrdLayout->addWidget(m_ptxtMean3_06_Dn, i, j++);
    pgrdLayout->addWidget(initLabelHyp(), i, j++);
    pgrdLayout->addWidget(m_ptxtMean3_06_Up, i, j++);
    //Mean3_09
    ++i; j = jInput;
    pgrdLayout->addWidget(m_plblMean3_09, i, j++);
    pgrdLayout->addWidget(m_ptxtMean3_09_Dn, i, j++);
    pgrdLayout->addWidget(initLabelHyp(), i, j++);
    pgrdLayout->addWidget(m_ptxtMean3_09_Up, i, j++);
    //Mean4_06
    ++i;
    ++i; j = jInput;
    pgrdLayout->addWidget(m_plblMean4_06, i, j++);
    pgrdLayout->addWidget(m_ptxtMean4_06_Dn, i, j++);
    pgrdLayout->addWidget(initLabelHyp(), i, j++);
    pgrdLayout->addWidget(m_ptxtMean4_06_Up, i, j++);
    //Mean4_09
    ++i; j = jInput;
    pgrdLayout->addWidget(m_plblMean4_09, i, j++);
    pgrdLayout->addWidget(m_ptxtMean4_09_Dn, i, j++);
    pgrdLayout->addWidget(initLabelHyp(), i, j++);
    pgrdLayout->addWidget(m_ptxtMean4_09_Up, i, j++);
}
//-------------------------------------------------------------------------------------------------------
//i = 0
void LocalSettingsWin::addTests_An(int &i, int j, QGridLayout *pgrdLayout)
{
    int jInput = j;
    //An_Vt
    //++i;
    pgrdLayout->addWidget(m_plblAn_Vt, i, j++);
    pgrdLayout->addWidget(m_ptxtAn_Vt_Dn, i, j++);
    pgrdLayout->addWidget(initLabelHyp(), i, j++);
    pgrdLayout->addWidget(m_ptxtAn_Vt_Up, i, j++);
    //An_VtRevers
    ++i; j = jInput;
    pgrdLayout->addWidget(m_plblAn_VtRevers, i, j++);
    pgrdLayout->addWidget(m_ptxtAn_VtRevers_Dn, i, j++);
    pgrdLayout->addWidget(initLabelHyp(), i, j++);
    pgrdLayout->addWidget(m_ptxtAn_VtRevers_Up, i, j++);
    //An_Be
    ++i; j = jInput;
    pgrdLayout->addWidget(m_plblAn_Be, i, j++);
    pgrdLayout->addWidget(m_ptxtAn_Be_Dn, i, j++);
    pgrdLayout->addWidget(initLabelHyp(), i, j++);
    pgrdLayout->addWidget(m_ptxtAn_Be_Up, i, j++);
    //An_Vbr
    ++i; j = jInput;
    pgrdLayout->addWidget(m_plblAn_Vbr, i, j++);
    pgrdLayout->addWidget(m_ptxtAn_Vbr_Dn, i, j++);
    pgrdLayout->addWidget(initLabelHyp(), i, j++);
    pgrdLayout->addWidget(m_ptxtAn_Vbr_Up, i, j++);
    //An_Gleak
    ++i; j = jInput;
    pgrdLayout->addWidget(m_plblAn_Gleak, i, j++);
    pgrdLayout->addWidget(m_ptxtAn_Gleak_Dn, i, j++);
    pgrdLayout->addWidget(initLabelHyp(), i, j++);
    pgrdLayout->addWidget(m_ptxtAn_Gleak_Up, i, j++);
    //An_DSleak
    ++i; j = jInput;
    pgrdLayout->addWidget(m_plblAn_DSleak, i, j++);
    pgrdLayout->addWidget(m_ptxtAn_DSleak_Dn, i, j++);
    pgrdLayout->addWidget(initLabelHyp(), i, j++);
    pgrdLayout->addWidget(m_ptxtAn_DSleak_Up, i, j++);
    //An_DSw_leak
    ++i; j = jInput;
    pgrdLayout->addWidget(m_plblAn_DSw_leak, i, j++);
    pgrdLayout->addWidget(m_ptxtAn_DSw_leak_Dn, i, j++);
    pgrdLayout->addWidget(initLabelHyp(), i, j++);
    pgrdLayout->addWidget(m_ptxtAn_DSw_leak_Up, i, j++);
    //An_DScurrent
    ++i; j = jInput;
    pgrdLayout->addWidget(m_plblAn_DScurrent, i, j++);
    pgrdLayout->addWidget(m_ptxtAn_DScurrent_Dn, i, j++);
    pgrdLayout->addWidget(initLabelHyp(), i, j++);
    pgrdLayout->addWidget(m_ptxtAn_DScurrent_Up, i, j++);
    //An_DSw_driver
    ++i; j = jInput;
    pgrdLayout->addWidget(m_plblAn_DSw_driver, i, j++);
    pgrdLayout->addWidget(m_ptxtAn_DSw_driver_Dn, i, j++);
    pgrdLayout->addWidget(initLabelHyp(), i, j++);
    pgrdLayout->addWidget(m_ptxtAn_DSw_driver_Up, i, j++);
}
void LocalSettingsWin::addTests_Ap(int &i, int j, QGridLayout *pgrdLayout)
{
    int jInput = j;
    //Ap_Vt
    ++i;
    pgrdLayout->addWidget(m_plblAp_Vt, i, j++);
    pgrdLayout->addWidget(m_ptxtAp_Vt_Dn, i, j++);
    pgrdLayout->addWidget(initLabelHyp(), i, j++);
    pgrdLayout->addWidget(m_ptxtAp_Vt_Up, i, j++);
    //Ap_VtRevers
    ++i; j = jInput;
    pgrdLayout->addWidget(m_plblAp_VtRevers, i, j++);
    pgrdLayout->addWidget(m_ptxtAp_VtRevers_Dn, i, j++);
    pgrdLayout->addWidget(initLabelHyp(), i, j++);
    pgrdLayout->addWidget(m_ptxtAp_VtRevers_Up, i, j++);
    //Ap_Be
    ++i; j = jInput;
    pgrdLayout->addWidget(m_plblAp_Be, i, j++);
    pgrdLayout->addWidget(m_ptxtAp_Be_Dn, i, j++);
    pgrdLayout->addWidget(initLabelHyp(), i, j++);
    pgrdLayout->addWidget(m_ptxtAp_Be_Up, i, j++);
    //Ap_Vbr
    ++i; j = jInput;
    pgrdLayout->addWidget(m_plblAp_Vbr, i, j++);
    pgrdLayout->addWidget(m_ptxtAp_Vbr_Dn, i, j++);
    pgrdLayout->addWidget(initLabelHyp(), i, j++);
    pgrdLayout->addWidget(m_ptxtAp_Vbr_Up, i, j++);
    //Ap_Gleak
    ++i; j = jInput;
    pgrdLayout->addWidget(m_plblAp_Gleak, i, j++);
    pgrdLayout->addWidget(m_ptxtAp_Gleak_Dn, i, j++);
    pgrdLayout->addWidget(initLabelHyp(), i, j++);
    pgrdLayout->addWidget(m_ptxtAp_Gleak_Up, i, j++);
    //Ap_DSleak
    ++i; j = jInput;
    pgrdLayout->addWidget(m_plblAp_DSleak, i, j++);
    pgrdLayout->addWidget(m_ptxtAp_DSleak_Dn, i, j++);
    pgrdLayout->addWidget(initLabelHyp(), i, j++);
    pgrdLayout->addWidget(m_ptxtAp_DSleak_Up, i, j++);
    //Ap_DSw_leak
    ++i; j = jInput;
    pgrdLayout->addWidget(m_plblAp_DSw_leak, i, j++);
    pgrdLayout->addWidget(m_ptxtAp_DSw_leak_Dn, i, j++);
    pgrdLayout->addWidget(initLabelHyp(), i, j++);
    pgrdLayout->addWidget(m_ptxtAp_DSw_leak_Up, i, j++);
    //Ap_DScurrent
    ++i; j = jInput;
    pgrdLayout->addWidget(m_plblAp_DScurrent, i, j++);
    pgrdLayout->addWidget(m_ptxtAp_DScurrent_Dn, i, j++);
    pgrdLayout->addWidget(initLabelHyp(), i, j++);
    pgrdLayout->addWidget(m_ptxtAp_DScurrent_Up, i, j++);
    //Ap_DSw_driver
    ++i; j = jInput;
    pgrdLayout->addWidget(m_plblAp_DSw_driver, i, j++);
    pgrdLayout->addWidget(m_ptxtAp_DSw_driver_Dn, i, j++);
    pgrdLayout->addWidget(initLabelHyp(), i, j++);
    pgrdLayout->addWidget(m_ptxtAp_DSw_driver_Up, i, j++);
}
//i = 0
void LocalSettingsWin::addTests_Rn(int &i, int j, QGridLayout *pgrdLayout)
{
    int jInput = j;
    //Rn_Vt
    //++i;
    pgrdLayout->addWidget(m_plblRn_Vt, i, j++);
    pgrdLayout->addWidget(m_ptxtRn_Vt_Dn, i, j++);
    pgrdLayout->addWidget(initLabelHyp(), i, j++);
    pgrdLayout->addWidget(m_ptxtRn_Vt_Up, i, j++);
    //Rn_VtRevers
    ++i; j = jInput;
    pgrdLayout->addWidget(m_plblRn_VtRevers, i, j++);
    pgrdLayout->addWidget(m_ptxtRn_VtRevers_Dn, i, j++);
    pgrdLayout->addWidget(initLabelHyp(), i, j++);
    pgrdLayout->addWidget(m_ptxtRn_VtRevers_Up, i, j++);
    //Rn_Be
    ++i; j = jInput;
    pgrdLayout->addWidget(m_plblRn_Be, i, j++);
    pgrdLayout->addWidget(m_ptxtRn_Be_Dn, i, j++);
    pgrdLayout->addWidget(initLabelHyp(), i, j++);
    pgrdLayout->addWidget(m_ptxtRn_Be_Up, i, j++);
    //Rn_Vbr
    ++i; j = jInput;
    pgrdLayout->addWidget(m_plblRn_Vbr, i, j++);
    pgrdLayout->addWidget(m_ptxtRn_Vbr_Dn, i, j++);
    pgrdLayout->addWidget(initLabelHyp(), i, j++);
    pgrdLayout->addWidget(m_ptxtRn_Vbr_Up, i, j++);
    //Rn_Gleak
    ++i; j = jInput;
    pgrdLayout->addWidget(m_plblRn_Gleak, i, j++);
    pgrdLayout->addWidget(m_ptxtRn_Gleak_Dn, i, j++);
    pgrdLayout->addWidget(initLabelHyp(), i, j++);
    pgrdLayout->addWidget(m_ptxtRn_Gleak_Up, i, j++);
    //Rn_DSleak
    ++i; j = jInput;
    pgrdLayout->addWidget(m_plblRn_DSleak, i, j++);
    pgrdLayout->addWidget(m_ptxtRn_DSleak_Dn, i, j++);
    pgrdLayout->addWidget(initLabelHyp(), i, j++);
    pgrdLayout->addWidget(m_ptxtRn_DSleak_Up, i, j++);
    //Rn_DSw_leak
    ++i; j = jInput;
    pgrdLayout->addWidget(m_plblRn_DSw_leak, i, j++);
    pgrdLayout->addWidget(m_ptxtRn_DSw_leak_Dn, i, j++);
    pgrdLayout->addWidget(initLabelHyp(), i, j++);
    pgrdLayout->addWidget(m_ptxtRn_DSw_leak_Up, i, j++);
    //Rn_DScurrent
    ++i; j = jInput;
    pgrdLayout->addWidget(m_plblRn_DScurrent, i, j++);
    pgrdLayout->addWidget(m_ptxtRn_DScurrent_Dn, i, j++);
    pgrdLayout->addWidget(initLabelHyp(), i, j++);
    pgrdLayout->addWidget(m_ptxtRn_DScurrent_Up, i, j++);
    //Rn_DSw_driver
    ++i; j = jInput;
    pgrdLayout->addWidget(m_plblRn_DSw_driver, i, j++);
    pgrdLayout->addWidget(m_ptxtRn_DSw_driver_Dn, i, j++);
    pgrdLayout->addWidget(initLabelHyp(), i, j++);
    pgrdLayout->addWidget(m_ptxtRn_DSw_driver_Up, i, j++);
}
void LocalSettingsWin::addTests_Rp(int &i, int j, QGridLayout *pgrdLayout)
{
    int jInput = j;
    //Rp_Vt
    ++i;
    pgrdLayout->addWidget(m_plblRp_Vt, i, j++);
    pgrdLayout->addWidget(m_ptxtRp_Vt_Dn, i, j++);
    pgrdLayout->addWidget(initLabelHyp(), i, j++);
    pgrdLayout->addWidget(m_ptxtRp_Vt_Up, i, j++);
    //Rp_VtRevers
    ++i; j = jInput;
    pgrdLayout->addWidget(m_plblRp_VtRevers, i, j++);
    pgrdLayout->addWidget(m_ptxtRp_VtRevers_Dn, i, j++);
    pgrdLayout->addWidget(initLabelHyp(), i, j++);
    pgrdLayout->addWidget(m_ptxtRp_VtRevers_Up, i, j++);
    //Rp_Be
    ++i; j = jInput;
    pgrdLayout->addWidget(m_plblRp_Be, i, j++);
    pgrdLayout->addWidget(m_ptxtRp_Be_Dn, i, j++);
    pgrdLayout->addWidget(initLabelHyp(), i, j++);
    pgrdLayout->addWidget(m_ptxtRp_Be_Up, i, j++);
    //Rp_Vbr
    ++i; j = jInput;
    pgrdLayout->addWidget(m_plblRp_Vbr, i, j++);
    pgrdLayout->addWidget(m_ptxtRp_Vbr_Dn, i, j++);
    pgrdLayout->addWidget(initLabelHyp(), i, j++);
    pgrdLayout->addWidget(m_ptxtRp_Vbr_Up, i, j++);
    //Rp_Gleak
    ++i; j = jInput;
    pgrdLayout->addWidget(m_plblRp_Gleak, i, j++);
    pgrdLayout->addWidget(m_ptxtRp_Gleak_Dn, i, j++);
    pgrdLayout->addWidget(initLabelHyp(), i, j++);
    pgrdLayout->addWidget(m_ptxtRp_Gleak_Up, i, j++);
    //Rp_DSleak
    ++i; j = jInput;
    pgrdLayout->addWidget(m_plblRp_DSleak, i, j++);
    pgrdLayout->addWidget(m_ptxtRp_DSleak_Dn, i, j++);
    pgrdLayout->addWidget(initLabelHyp(), i, j++);
    pgrdLayout->addWidget(m_ptxtRp_DSleak_Up, i, j++);
    //Rp_DSw_leak
    ++i; j = jInput;
    pgrdLayout->addWidget(m_plblRp_DSw_leak, i, j++);
    pgrdLayout->addWidget(m_ptxtRp_DSw_leak_Dn, i, j++);
    pgrdLayout->addWidget(initLabelHyp(), i, j++);
    pgrdLayout->addWidget(m_ptxtRp_DSw_leak_Up, i, j++);
    //Rp_DScurrent
    ++i; j = jInput;
    pgrdLayout->addWidget(m_plblRp_DScurrent, i, j++);
    pgrdLayout->addWidget(m_ptxtRp_DScurrent_Dn, i, j++);
    pgrdLayout->addWidget(initLabelHyp(), i, j++);
    pgrdLayout->addWidget(m_ptxtRp_DScurrent_Up, i, j++);
    //Rp_DSw_driver
    ++i; j = jInput;
    pgrdLayout->addWidget(m_plblRp_DSw_driver, i, j++);
    pgrdLayout->addWidget(m_ptxtRp_DSw_driver_Dn, i, j++);
    pgrdLayout->addWidget(initLabelHyp(), i, j++);
    pgrdLayout->addWidget(m_ptxtRp_DSw_driver_Up, i, j++);
}
//i = 0
void LocalSettingsWin::addTests_Hn(int &i, int j, QGridLayout *pgrdLayout)
{
    int jInput = j;
    //Hn_Vt
    //++i;
    pgrdLayout->addWidget(m_plblHn_Vt, i, j++);
    pgrdLayout->addWidget(m_ptxtHn_Vt_Dn, i, j++);
    pgrdLayout->addWidget(initLabelHyp(), i, j++);
    pgrdLayout->addWidget(m_ptxtHn_Vt_Up, i, j++);
    //Hn_VtRevers
    ++i; j = jInput;
    pgrdLayout->addWidget(m_plblHn_VtRevers, i, j++);
    pgrdLayout->addWidget(m_ptxtHn_VtRevers_Dn, i, j++);
    pgrdLayout->addWidget(initLabelHyp(), i, j++);
    pgrdLayout->addWidget(m_ptxtHn_VtRevers_Up, i, j++);
    //Hn_Be
    ++i; j = jInput;
    pgrdLayout->addWidget(m_plblHn_Be, i, j++);
    pgrdLayout->addWidget(m_ptxtHn_Be_Dn, i, j++);
    pgrdLayout->addWidget(initLabelHyp(), i, j++);
    pgrdLayout->addWidget(m_ptxtHn_Be_Up, i, j++);
    //Hn_Vbr
    ++i; j = jInput;
    pgrdLayout->addWidget(m_plblHn_Vbr, i, j++);
    pgrdLayout->addWidget(m_ptxtHn_Vbr_Dn, i, j++);
    pgrdLayout->addWidget(initLabelHyp(), i, j++);
    pgrdLayout->addWidget(m_ptxtHn_Vbr_Up, i, j++);
    //Hn_Gleak
    ++i; j = jInput;
    pgrdLayout->addWidget(m_plblHn_Gleak, i, j++);
    pgrdLayout->addWidget(m_ptxtHn_Gleak_Dn, i, j++);
    pgrdLayout->addWidget(initLabelHyp(), i, j++);
    pgrdLayout->addWidget(m_ptxtHn_Gleak_Up, i, j++);
    //Hn_DSleak
    ++i; j = jInput;
    pgrdLayout->addWidget(m_plblHn_DSleak, i, j++);
    pgrdLayout->addWidget(m_ptxtHn_DSleak_Dn, i, j++);
    pgrdLayout->addWidget(initLabelHyp(), i, j++);
    pgrdLayout->addWidget(m_ptxtHn_DSleak_Up, i, j++);
    //Hn_DSw_leak
    ++i; j = jInput;
    pgrdLayout->addWidget(m_plblHn_DSw_leak, i, j++);
    pgrdLayout->addWidget(m_ptxtHn_DSw_leak_Dn, i, j++);
    pgrdLayout->addWidget(initLabelHyp(), i, j++);
    pgrdLayout->addWidget(m_ptxtHn_DSw_leak_Up, i, j++);
    //Hn_DScurrent
    ++i; j = jInput;
    pgrdLayout->addWidget(m_plblHn_DScurrent, i, j++);
    pgrdLayout->addWidget(m_ptxtHn_DScurrent_Dn, i, j++);
    pgrdLayout->addWidget(initLabelHyp(), i, j++);
    pgrdLayout->addWidget(m_ptxtHn_DScurrent_Up, i, j++);
    //Hn_DSw_driver
    ++i; j = jInput;
    pgrdLayout->addWidget(m_plblHn_DSw_driver, i, j++);
    pgrdLayout->addWidget(m_ptxtHn_DSw_driver_Dn, i, j++);
    pgrdLayout->addWidget(initLabelHyp(), i, j++);
    pgrdLayout->addWidget(m_ptxtHn_DSw_driver_Up, i, j++);
}
void LocalSettingsWin::addTests_Hp(int &i, int j, QGridLayout *pgrdLayout)
{
    int jInput = j;
    //Hp_Vt
    ++i;
    pgrdLayout->addWidget(m_plblHp_Vt, i, j++);
    pgrdLayout->addWidget(m_ptxtHp_Vt_Dn, i, j++);
    pgrdLayout->addWidget(initLabelHyp(), i, j++);
    pgrdLayout->addWidget(m_ptxtHp_Vt_Up, i, j++);
    //Hp_VtRevers
    ++i; j = jInput;
    pgrdLayout->addWidget(m_plblHp_VtRevers, i, j++);
    pgrdLayout->addWidget(m_ptxtHp_VtRevers_Dn, i, j++);
    pgrdLayout->addWidget(initLabelHyp(), i, j++);
    pgrdLayout->addWidget(m_ptxtHp_VtRevers_Up, i, j++);
    //Hp_Be
    ++i; j = jInput;
    pgrdLayout->addWidget(m_plblHp_Be, i, j++);
    pgrdLayout->addWidget(m_ptxtHp_Be_Dn, i, j++);
    pgrdLayout->addWidget(initLabelHyp(), i, j++);
    pgrdLayout->addWidget(m_ptxtHp_Be_Up, i, j++);
    //Hp_Vbr
    ++i; j = jInput;
    pgrdLayout->addWidget(m_plblHp_Vbr, i, j++);
    pgrdLayout->addWidget(m_ptxtHp_Vbr_Dn, i, j++);
    pgrdLayout->addWidget(initLabelHyp(), i, j++);
    pgrdLayout->addWidget(m_ptxtHp_Vbr_Up, i, j++);
    //Hp_Gleak
    ++i; j = jInput;
    pgrdLayout->addWidget(m_plblHp_Gleak, i, j++);
    pgrdLayout->addWidget(m_ptxtHp_Gleak_Dn, i, j++);
    pgrdLayout->addWidget(initLabelHyp(), i, j++);
    pgrdLayout->addWidget(m_ptxtHp_Gleak_Up, i, j++);
    //Hp_DSleak
    ++i; j = jInput;
    pgrdLayout->addWidget(m_plblHp_DSleak, i, j++);
    pgrdLayout->addWidget(m_ptxtHp_DSleak_Dn, i, j++);
    pgrdLayout->addWidget(initLabelHyp(), i, j++);
    pgrdLayout->addWidget(m_ptxtHp_DSleak_Up, i, j++);
    //Hp_DSw_leak
    ++i; j = jInput;
    pgrdLayout->addWidget(m_plblHp_DSw_leak, i, j++);
    pgrdLayout->addWidget(m_ptxtHp_DSw_leak_Dn, i, j++);
    pgrdLayout->addWidget(initLabelHyp(), i, j++);
    pgrdLayout->addWidget(m_ptxtHp_DSw_leak_Up, i, j++);
    //Hp_DScurrent
    ++i; j = jInput;
    pgrdLayout->addWidget(m_plblHp_DScurrent, i, j++);
    pgrdLayout->addWidget(m_ptxtHp_DScurrent_Dn, i, j++);
    pgrdLayout->addWidget(initLabelHyp(), i, j++);
    pgrdLayout->addWidget(m_ptxtHp_DScurrent_Up, i, j++);
    //Hp_DSw_driver
    ++i; j = jInput;
    pgrdLayout->addWidget(m_plblHp_DSw_driver, i, j++);
    pgrdLayout->addWidget(m_ptxtHp_DSw_driver_Dn, i, j++);
    pgrdLayout->addWidget(initLabelHyp(), i, j++);
    pgrdLayout->addWidget(m_ptxtHp_DSw_driver_Up, i, j++);
}
//-------------------------------------------------------------------------------------------------------
//i = 0
void LocalSettingsWin::addTests_VDP(int &i, int j, QGridLayout *pgrdLayout)
{
    int jInput = j;
    //VDP_nWell
    //++i;
    pgrdLayout->addWidget(m_plblVDPnWell, i, j++);
    pgrdLayout->addWidget(m_ptxtVDPnWell_Dn, i, j++);
    pgrdLayout->addWidget(initLabelHyp(), i, j++);
    pgrdLayout->addWidget(m_ptxtVDPnWell_Up, i, j++);
    //VDP_pWell
    ++i; j = jInput;
    pgrdLayout->addWidget(m_plblVDPpWell, i, j++);
    pgrdLayout->addWidget(m_ptxtVDPpWell_Dn, i, j++);
    pgrdLayout->addWidget(initLabelHyp(), i, j++);
    pgrdLayout->addWidget(m_ptxtVDPpWell_Up, i, j++);
    //VDP_n
    ++i; j = jInput;
    pgrdLayout->addWidget(m_plblVDPn, i, j++);
    pgrdLayout->addWidget(m_ptxtVDPn_Dn, i, j++);
    pgrdLayout->addWidget(initLabelHyp(), i, j++);
    pgrdLayout->addWidget(m_ptxtVDPn_Up, i, j++);
    //VDP_p
    ++i; j = jInput;
    pgrdLayout->addWidget(m_plblVDPp, i, j++);
    pgrdLayout->addWidget(m_ptxtVDPp_Dn, i, j++);
    pgrdLayout->addWidget(initLabelHyp(), i, j++);
    pgrdLayout->addWidget(m_ptxtVDPp_Up, i, j++);
    //VDP_nSi
    ++i; j = jInput;
    pgrdLayout->addWidget(m_plblVDPnSi, i, j++);
    pgrdLayout->addWidget(m_ptxtVDPnSi_Dn, i, j++);
    pgrdLayout->addWidget(initLabelHyp(), i, j++);
    pgrdLayout->addWidget(m_ptxtVDPnSi_Up, i, j++);
    //VDP_pSi
    ++i; j = jInput;
    pgrdLayout->addWidget(m_plblVDPpSi, i, j++);
    pgrdLayout->addWidget(m_ptxtVDPpSi_Dn, i, j++);
    pgrdLayout->addWidget(initLabelHyp(), i, j++);
    pgrdLayout->addWidget(m_ptxtVDPpSi_Up, i, j++);
}
//-------------------------------------------------------------------------------------------------------
//i = 0
void LocalSettingsWin::addTests_pNpN(int& i, int j, QGridLayout *pgrdLayout)
{
    pgrdLayout->addWidget(m_plblpNpN, i, j++);
    pgrdLayout->addWidget(m_ptxtpNpN_Dn, i, j++);
    pgrdLayout->addWidget(initLabelHyp(), i, j++);
    pgrdLayout->addWidget(m_ptxtpNpN_Up, i, j++);
}
//-------------------------------------------------------------------------------------------------------
void LocalSettingsWin::addTests_Diod(int &i, int j, QGridLayout *pgrdLayout)
{
    int jInput = j;
    //Diodn_pWell
    ++i;
    pgrdLayout->addWidget(m_plblDiodn_pWell, i, j++);
    pgrdLayout->addWidget(m_ptxtDiodn_pWell_Dn, i, j++);
    pgrdLayout->addWidget(initLabelHyp(), i, j++);
    pgrdLayout->addWidget(m_ptxtDiodn_pWell_Up, i, j++);
    //Diodp_nWell
    ++i; j = jInput;
    pgrdLayout->addWidget(m_plblDiodp_nWell, i, j++);
    pgrdLayout->addWidget(m_ptxtDiodp_nWell_Dn, i, j++);
    pgrdLayout->addWidget(initLabelHyp(), i, j++);
    pgrdLayout->addWidget(m_ptxtDiodp_nWell_Up, i, j++);
}
//-------------------------------------------------------------------------------------------------------
void LocalSettingsWin::addTests_Capacity(int &i, int j, QGridLayout *pgrdLayout)
{
    int jInput = j;
    //CM1M2
    ++i;
    pgrdLayout->addWidget(m_plblCM1M2, i, j++);
    pgrdLayout->addWidget(m_ptxtCM1M2_Dn, i, j++);
    pgrdLayout->addWidget(initLabelHyp(), i, j++);
    pgrdLayout->addWidget(m_ptxtCM1M2_Up, i, j++);
    //CM2M3
    ++i; j = jInput;
    pgrdLayout->addWidget(m_plblCM2M3, i, j++);
    pgrdLayout->addWidget(m_ptxtCM2M3_Dn, i, j++);
    pgrdLayout->addWidget(initLabelHyp(), i, j++);
    pgrdLayout->addWidget(m_ptxtCM2M3_Up, i, j++);
    //CM3M4
    ++i; j = jInput;
    pgrdLayout->addWidget(m_plblCM3M4, i, j++);
    pgrdLayout->addWidget(m_ptxtCM3M4_Dn, i, j++);
    pgrdLayout->addWidget(initLabelHyp(), i, j++);
    pgrdLayout->addWidget(m_ptxtCM3M4_Up, i, j++);
    //CpSinWell
    ++i; j = jInput;
    pgrdLayout->addWidget(m_plblCpSinWell, i, j++);
    pgrdLayout->addWidget(m_ptxtCpSinWell_Dn, i, j++);
    pgrdLayout->addWidget(initLabelHyp(), i, j++);
    pgrdLayout->addWidget(m_ptxtCpSinWell_Up, i, j++);
    //CnSipWell
    ++i; j = jInput;
    pgrdLayout->addWidget(m_plblCnSipWell, i, j++);
    pgrdLayout->addWidget(m_ptxtCnSipWell_Dn, i, j++);
    pgrdLayout->addWidget(initLabelHyp(), i, j++);
    pgrdLayout->addWidget(m_ptxtCnSipWell_Up, i, j++);
}
//-------------------------------------------------------------------------------------------------------
void LocalSettingsWin::setDefaultMeaningsInLines()
{
    //установка значений по умолчанию в поля
//-----------------------------------------------------------------------------
    //SIL
    QString strRSIL_Dn = "0.1", strRSIL_Up = "10.0";
    QString strKLVsSIL_Dn = "0.1", strKLVsSIL_Up = "10.0";
    QString strZsSIL_Dn = "0.1", strZsSIL_Up = "10.0";
    QString strRz09SIL_Dn = "0.1", strRz09SIL_Up = "10.0";
    QString strRz05SIL_Dn = "0.1", strRz05SIL_Up = "10.0";
    QString strRz035SIL_Dn = "0.1", strRz035SIL_Up = "10.0";

    if((m_ptxtSIL_R_Dn->text()).isEmpty()) slotSetRSIL_Dn(strRSIL_Dn);
    if((m_ptxtSIL_R_Up->text()).isEmpty()) slotSetRSIL_Up(strRSIL_Up);

    if(m_ptxtSIL_KLVnM1_Dn->text() == "") slotSetKLVsSIL_Dn(strKLVsSIL_Dn);
    if(m_ptxtSIL_KLVnM1_Up->text() == "") slotSetKLVsSIL_Up(strKLVsSIL_Up);

    if(m_ptxtSIL_ZnM1_Dn->text() == "") slotSetZsSIL_Dn(strZsSIL_Dn);
    if(m_ptxtSIL_ZnM1_Up->text() == "") slotSetZsSIL_Up(strZsSIL_Up);

    if(m_ptxtRZnTiSi09_Dn->text() == "") slotSetRz09SIL_Dn(strRz09SIL_Dn);
    if(m_ptxtRZnTiSi09_Up->text() == "") slotSetRz09SIL_Up(strRz09SIL_Up);

    if(m_ptxtRZnTiSi05_Dn->text() == "") slotSetRz05SIL_Dn(strRz05SIL_Dn);
    if(m_ptxtRZnTiSi05_Up->text() == "") slotSetRz05SIL_Up(strRz05SIL_Up);

//    if(m_ptxtRZnTiSi035_Dn->text() == "") slotSetRz035SIL_Dn(strRz035SIL_Dn);
//    if(m_ptxtRZnTiSi035_Up->text() == "") slotSetRz035SIL_Up(strRz035SIL_Up);
//-------------------------------------------------------------------------------------
    //Ме
    QString strKLVsMiMj_Dn = "0.1", strKLVsMiMj_Up = "2.5";
    QString strKLVsM1M4_Dn = "0.1", strKLVsM1M4_Up = "7.5";
    QString strZsMiMj_Dn = "0.1", strZsMiMj_Up = "2.5";
    QString strZsM1M4_Dn = "0.1", strZsM1M4_Up = "7.5";

    if(m_ptxtKLV_M1M2_Dn->text() == "")
        slotSetKLVsMiMj_Dn(strKLVsMiMj_Dn);
    if(m_ptxtKLV_M1M2_Up->text() == "")
        slotSetKLVsMiMj_Up(strKLVsMiMj_Up);
    if(m_ptxtKLV_M1M4_Dn->text() == "")
        slotSetKLVsM1M4_Dn(strKLVsM1M4_Dn);
    if(m_ptxtKLV_M1M4_Up->text() == "")
        slotSetKLVsM1M4_Up(strKLVsM1M4_Up);

    if(m_ptxtZ_M1M2_Dn->text() == "")
        slotSetZsMiMj_Dn(strZsMiMj_Dn);
    if(m_ptxtZ_M1M2_Up->text() == "")
        slotSetZsMiMj_Up(strZsMiMj_Up);
    if(m_ptxtZ_M1M4_Dn->text() == "")
        slotSetZsM1M4_Dn(strZsM1M4_Dn);
    if(m_ptxtZ_M1M4_Up->text() == "")
        slotSetZsM1M4_Up(strZsM1M4_Up);

    double divisor = 5000.0;

    QString Meander1_05 = QString::number(200.0/divisor, 'g', 4);
    QString Meander1_09 = QString::number(450.0/divisor, 'g', 4);

    QString dMeander2_06 = QString::number(200.0/divisor, 'g', 4);
    QString dMeander2_09 = QString::number(450.0/divisor, 'g', 4);

    QString dMeander3_06 = "dMeander3_09";
    QString dMeander3_09 = "dMeander3_09";

    //QString dMeander3_06 = "dMeander3_09";
    //QString dMeander3_09 = "dMeander3_09";

//-------------------------------------------------------------------------------------------------
}
//=================================================================================================
//соединения полей
void LocalSettingsWin::R_Dn_SIL_connections() const
{
    //KLV_Dn
    connect(m_ptxtSIL_R_Dn, SIGNAL(textChanged(const QString&)),
            m_ptxtSIL_KLVnM1_Dn, SLOT(setText(const QString&)));
    connect(m_ptxtSIL_R_Dn, SIGNAL(textChanged(const QString&)),
            m_ptxtSIL_KLVpM1_Dn, SLOT(setText(const QString&)));
    connect(m_ptxtSIL_R_Dn, SIGNAL(textChanged(const QString&)),
            m_ptxtSIL_KLVnSiM1_Dn, SLOT(setText(const QString&)));
    connect(m_ptxtSIL_R_Dn, SIGNAL(textChanged(const QString&)),
            m_ptxtSIL_KLVpSiM1_Dn, SLOT(setText(const QString&)));
    connect(m_ptxtSIL_R_Dn, SIGNAL(textChanged(const QString&)),
            m_ptxtSIL_KLVSiM1_Dn, SLOT(setText(const QString&)));

    //Z_Dn
    connect(m_ptxtSIL_R_Dn, SIGNAL(textChanged(const QString&)),
            m_ptxtSIL_ZnM1_Dn, SLOT(setText(const QString&)));
    connect(m_ptxtSIL_R_Dn, SIGNAL(textChanged(const QString&)),
            m_ptxtSIL_ZpM1_Dn, SLOT(setText(const QString&)));
    connect(m_ptxtSIL_R_Dn, SIGNAL(textChanged(const QString&)),
            m_ptxtSIL_ZnSiM1_Dn, SLOT(setText(const QString&)));
    connect(m_ptxtSIL_R_Dn, SIGNAL(textChanged(const QString&)),
            m_ptxtSIL_ZpSiM1_Dn, SLOT(setText(const QString&)));
    connect(m_ptxtSIL_R_Dn, SIGNAL(textChanged(const QString&)),
            m_ptxtSIL_ZSiM1_Dn, SLOT(setText(const QString&)));

    //Rz09_Dn
    connect(m_ptxtSIL_R_Dn, SIGNAL(textChanged(const QString&)),
            m_ptxtRZnTiSi09_Dn, SLOT(setText(const QString&)));
    connect(m_ptxtSIL_R_Dn, SIGNAL(textChanged(const QString&)),
            m_ptxtRZpTiSi09_Dn, SLOT(setText(const QString&)));
    connect(m_ptxtSIL_R_Dn, SIGNAL(textChanged(const QString&)),
            m_ptxtRZnSiTiSi09_Dn, SLOT(setText(const QString&)));
    connect(m_ptxtSIL_R_Dn, SIGNAL(textChanged(const QString&)),
            m_ptxtRZpSiTiSi09_Dn, SLOT(setText(const QString&)));
    connect(m_ptxtSIL_R_Dn, SIGNAL(textChanged(const QString&)),
            m_ptxtRZSiTiSi09_Dn, SLOT(setText(const QString&)));

    //Rz05_Dn
    connect(m_ptxtSIL_R_Dn, SIGNAL(textChanged(const QString&)),
            m_ptxtRZnTiSi05_Dn, SLOT(setText(const QString&)));
    connect(m_ptxtSIL_R_Dn, SIGNAL(textChanged(const QString&)),
            m_ptxtRZpTiSi05_Dn, SLOT(setText(const QString&)));
    connect(m_ptxtSIL_R_Dn, SIGNAL(textChanged(const QString&)),
            m_ptxtRZnSiTiSi05_Dn, SLOT(setText(const QString&)));
    connect(m_ptxtSIL_R_Dn, SIGNAL(textChanged(const QString&)),
            m_ptxtRZpSiTiSi05_Dn, SLOT(setText(const QString&)));
    connect(m_ptxtSIL_R_Dn, SIGNAL(textChanged(const QString&)),
            m_ptxtRZSiTiSi05_Dn, SLOT(setText(const QString&)));

    //Rz035_Dn
    connect(m_ptxtSIL_R_Dn, SIGNAL(textChanged(const QString&)),
            m_ptxtRZnTiSi035_Dn, SLOT(setText(const QString&)));
    connect(m_ptxtSIL_R_Dn, SIGNAL(textChanged(const QString&)),
            m_ptxtRZpTiSi035_Dn, SLOT(setText(const QString&)));
    connect(m_ptxtSIL_R_Dn, SIGNAL(textChanged(const QString&)),
            m_ptxtRZnSiTiSi035_Dn, SLOT(setText(const QString&)));
    connect(m_ptxtSIL_R_Dn, SIGNAL(textChanged(const QString&)),
            m_ptxtRZpSiTiSi035_Dn, SLOT(setText(const QString&)));
    connect(m_ptxtSIL_R_Dn, SIGNAL(textChanged(const QString&)),
            m_ptxtRZSiTiSi035_Dn, SLOT(setText(const QString&)));

    //Rz06_Dn
    connect(m_ptxtSIL_R_Dn, SIGNAL(textChanged(const QString&)),
            m_ptxtRZnTiSi06_Dn, SLOT(setText(const QString&)));
    connect(m_ptxtSIL_R_Dn, SIGNAL(textChanged(const QString&)),
            m_ptxtRZpTiSi06_Dn, SLOT(setText(const QString&)));
    connect(m_ptxtSIL_R_Dn, SIGNAL(textChanged(const QString&)),
            m_ptxtRZnSiTiSi06_Dn, SLOT(setText(const QString&)));
    connect(m_ptxtSIL_R_Dn, SIGNAL(textChanged(const QString&)),
            m_ptxtRZpSiTiSi06_Dn, SLOT(setText(const QString&)));
    connect(m_ptxtSIL_R_Dn, SIGNAL(textChanged(const QString&)),
            m_ptxtRZSiTiSi06_Dn, SLOT(setText(const QString&)));
}
void LocalSettingsWin::R_Up_SIL_connections() const
{
    //KLV_Up
    connect(m_ptxtSIL_R_Up, SIGNAL(textChanged(const QString&)),
            m_ptxtSIL_KLVnM1_Up, SLOT(setText(const QString&)));
    connect(m_ptxtSIL_R_Up, SIGNAL(textChanged(const QString&)),
            m_ptxtSIL_KLVpM1_Up, SLOT(setText(const QString&)));
    connect(m_ptxtSIL_R_Up, SIGNAL(textChanged(const QString&)),
            m_ptxtSIL_KLVnSiM1_Up, SLOT(setText(const QString&)));
    connect(m_ptxtSIL_R_Up, SIGNAL(textChanged(const QString&)),
            m_ptxtSIL_KLVpSiM1_Up, SLOT(setText(const QString&)));
    connect(m_ptxtSIL_R_Up, SIGNAL(textChanged(const QString&)),
            m_ptxtSIL_KLVSiM1_Up, SLOT(setText(const QString&)));

    //Z_Up
    connect(m_ptxtSIL_R_Up, SIGNAL(textChanged(const QString&)),
            m_ptxtSIL_ZnM1_Up, SLOT(setText(const QString&)));
    connect(m_ptxtSIL_R_Up, SIGNAL(textChanged(const QString&)),
            m_ptxtSIL_ZpM1_Up, SLOT(setText(const QString&)));
    connect(m_ptxtSIL_R_Up, SIGNAL(textChanged(const QString&)),
            m_ptxtSIL_ZnSiM1_Up, SLOT(setText(const QString&)));
    connect(m_ptxtSIL_R_Up, SIGNAL(textChanged(const QString&)),
            m_ptxtSIL_ZpSiM1_Up, SLOT(setText(const QString&)));
    connect(m_ptxtSIL_R_Up, SIGNAL(textChanged(const QString&)),
            m_ptxtSIL_ZSiM1_Up, SLOT(setText(const QString&)));

    //Rz09_Up
    connect(m_ptxtSIL_R_Up, SIGNAL(textChanged(const QString&)),
            m_ptxtRZnTiSi09_Up, SLOT(setText(const QString&)));
    connect(m_ptxtSIL_R_Up, SIGNAL(textChanged(const QString&)),
            m_ptxtRZpTiSi09_Up, SLOT(setText(const QString&)));
    connect(m_ptxtSIL_R_Up, SIGNAL(textChanged(const QString&)),
            m_ptxtRZnSiTiSi09_Up, SLOT(setText(const QString&)));
    connect(m_ptxtSIL_R_Up, SIGNAL(textChanged(const QString&)),
            m_ptxtRZpSiTiSi09_Up, SLOT(setText(const QString&)));
    connect(m_ptxtSIL_R_Up, SIGNAL(textChanged(const QString&)),
            m_ptxtRZSiTiSi09_Up, SLOT(setText(const QString&)));

    //Rz05_Up
    connect(m_ptxtSIL_R_Up, SIGNAL(textChanged(const QString&)),
            m_ptxtRZnTiSi05_Up, SLOT(setText(const QString&)));
    connect(m_ptxtSIL_R_Up, SIGNAL(textChanged(const QString&)),
            m_ptxtRZpTiSi05_Up, SLOT(setText(const QString&)));
    connect(m_ptxtSIL_R_Up, SIGNAL(textChanged(const QString&)),
            m_ptxtRZnSiTiSi05_Up, SLOT(setText(const QString&)));
    connect(m_ptxtSIL_R_Up, SIGNAL(textChanged(const QString&)),
            m_ptxtRZpSiTiSi05_Up, SLOT(setText(const QString&)));
    connect(m_ptxtSIL_R_Up, SIGNAL(textChanged(const QString&)),
            m_ptxtRZSiTiSi05_Up, SLOT(setText(const QString&)));

    //Rz035_Up
    connect(m_ptxtSIL_R_Up, SIGNAL(textChanged(const QString&)),
            m_ptxtRZnTiSi035_Up, SLOT(setText(const QString&)));
    connect(m_ptxtSIL_R_Up, SIGNAL(textChanged(const QString&)),
            m_ptxtRZpTiSi035_Up, SLOT(setText(const QString&)));
    connect(m_ptxtSIL_R_Up, SIGNAL(textChanged(const QString&)),
            m_ptxtRZnSiTiSi035_Up, SLOT(setText(const QString&)));
    connect(m_ptxtSIL_R_Up, SIGNAL(textChanged(const QString&)),
            m_ptxtRZpSiTiSi035_Up, SLOT(setText(const QString&)));
    connect(m_ptxtSIL_R_Up, SIGNAL(textChanged(const QString&)),
            m_ptxtRZSiTiSi035_Up, SLOT(setText(const QString&)));

    //Rz06_Up
    connect(m_ptxtSIL_R_Up, SIGNAL(textChanged(const QString&)),
            m_ptxtRZnTiSi06_Up, SLOT(setText(const QString&)));
    connect(m_ptxtSIL_R_Up, SIGNAL(textChanged(const QString&)),
            m_ptxtRZpTiSi06_Up, SLOT(setText(const QString&)));
    connect(m_ptxtSIL_R_Up, SIGNAL(textChanged(const QString&)),
            m_ptxtRZnSiTiSi06_Up, SLOT(setText(const QString&)));
    connect(m_ptxtSIL_R_Up, SIGNAL(textChanged(const QString&)),
            m_ptxtRZpSiTiSi06_Up, SLOT(setText(const QString&)));
    connect(m_ptxtSIL_R_Up, SIGNAL(textChanged(const QString&)),
            m_ptxtRZSiTiSi06_Up, SLOT(setText(const QString&)));
}
void LocalSettingsWin::KLVsDn_SIL_connections() const
{
    //KLVnM1_Dn
    connect(m_ptxtSIL_KLVnM1_Dn, SIGNAL(textChanged(const QString&)),
            m_ptxtSIL_KLVpM1_Dn, SLOT(setText(const QString&)));
    connect(m_ptxtSIL_KLVnM1_Dn, SIGNAL(textChanged(const QString&)),
            m_ptxtSIL_KLVnSiM1_Dn, SLOT(setText(const QString&)));
    connect(m_ptxtSIL_KLVnM1_Dn, SIGNAL(textChanged(const QString&)),
            m_ptxtSIL_KLVpSiM1_Dn, SLOT(setText(const QString&)));
    connect(m_ptxtSIL_KLVnM1_Dn, SIGNAL(textChanged(const QString&)),
            m_ptxtSIL_KLVSiM1_Dn, SLOT(setText(const QString&)));
    //KLVpM1_Dn
    connect(m_ptxtSIL_KLVpM1_Dn, SIGNAL(textChanged(const QString&)),
            m_ptxtSIL_KLVnM1_Dn, SLOT(setText(const QString&)));
    connect(m_ptxtSIL_KLVpM1_Dn, SIGNAL(textChanged(const QString&)),
            m_ptxtSIL_KLVnSiM1_Dn, SLOT(setText(const QString&)));
    connect(m_ptxtSIL_KLVpM1_Dn, SIGNAL(textChanged(const QString&)),
            m_ptxtSIL_KLVpSiM1_Dn, SLOT(setText(const QString&)));
    connect(m_ptxtSIL_KLVpM1_Dn, SIGNAL(textChanged(const QString&)),
            m_ptxtSIL_KLVSiM1_Dn, SLOT(setText(const QString&)));
    //KLVnSiM1_Dn
    connect(m_ptxtSIL_KLVnSiM1_Dn, SIGNAL(textChanged(const QString&)),
            m_ptxtSIL_KLVnM1_Dn, SLOT(setText(const QString&)));
    connect(m_ptxtSIL_KLVnSiM1_Dn, SIGNAL(textChanged(const QString&)),
            m_ptxtSIL_KLVpM1_Dn, SLOT(setText(const QString&)));
    connect(m_ptxtSIL_KLVnSiM1_Dn, SIGNAL(textChanged(const QString&)),
            m_ptxtSIL_KLVpSiM1_Dn, SLOT(setText(const QString&)));
    connect(m_ptxtSIL_KLVnSiM1_Dn, SIGNAL(textChanged(const QString&)),
            m_ptxtSIL_KLVSiM1_Dn, SLOT(setText(const QString&)));
    //KLVpSiM1_Dn
    connect(m_ptxtSIL_KLVpSiM1_Dn, SIGNAL(textChanged(const QString&)),
            m_ptxtSIL_KLVnM1_Dn, SLOT(setText(const QString&)));
    connect(m_ptxtSIL_KLVpSiM1_Dn, SIGNAL(textChanged(const QString&)),
            m_ptxtSIL_KLVpM1_Dn, SLOT(setText(const QString&)));
    connect(m_ptxtSIL_KLVpSiM1_Dn, SIGNAL(textChanged(const QString&)),
            m_ptxtSIL_KLVnSiM1_Dn, SLOT(setText(const QString&)));
    connect(m_ptxtSIL_KLVpSiM1_Dn, SIGNAL(textChanged(const QString&)),
            m_ptxtSIL_KLVSiM1_Dn, SLOT(setText(const QString&)));
    //KLVSiM1_Dn
    connect(m_ptxtSIL_KLVSiM1_Dn, SIGNAL(textChanged(const QString&)),
            m_ptxtSIL_KLVnM1_Dn, SLOT(setText(const QString&)));
    connect(m_ptxtSIL_KLVSiM1_Dn, SIGNAL(textChanged(const QString&)),
            m_ptxtSIL_KLVpM1_Dn, SLOT(setText(const QString&)));
    connect(m_ptxtSIL_KLVSiM1_Dn, SIGNAL(textChanged(const QString&)),
            m_ptxtSIL_KLVnSiM1_Dn, SLOT(setText(const QString&)));
    connect(m_ptxtSIL_KLVSiM1_Dn, SIGNAL(textChanged(const QString&)),
            m_ptxtSIL_KLVpSiM1_Dn, SLOT(setText(const QString&)));

    connect(m_ptxtSIL_KLVnM1_Dn, SIGNAL(textChanged(const QString&)),
            this, SLOT(slotCmdApplyEnabled()));
}
void LocalSettingsWin::KLVsUp_SIL_connections() const
{
    //KLVnM1_Dn
    connect(m_ptxtSIL_KLVnM1_Up, SIGNAL(textChanged(const QString&)),
            m_ptxtSIL_KLVpM1_Up, SLOT(setText(const QString&)));
    connect(m_ptxtSIL_KLVnM1_Up, SIGNAL(textChanged(const QString&)),
            m_ptxtSIL_KLVnSiM1_Up, SLOT(setText(const QString&)));
    connect(m_ptxtSIL_KLVnM1_Up, SIGNAL(textChanged(const QString&)),
            m_ptxtSIL_KLVpSiM1_Up, SLOT(setText(const QString&)));
    connect(m_ptxtSIL_KLVnM1_Up, SIGNAL(textChanged(const QString&)),
            m_ptxtSIL_KLVSiM1_Up, SLOT(setText(const QString&)));
    //KLVpM1_Dn
    connect(m_ptxtSIL_KLVpM1_Up, SIGNAL(textChanged(const QString&)),
            m_ptxtSIL_KLVnM1_Up, SLOT(setText(const QString&)));
    connect(m_ptxtSIL_KLVpM1_Up, SIGNAL(textChanged(const QString&)),
            m_ptxtSIL_KLVnSiM1_Up, SLOT(setText(const QString&)));
    connect(m_ptxtSIL_KLVpM1_Up, SIGNAL(textChanged(const QString&)),
            m_ptxtSIL_KLVpSiM1_Up, SLOT(setText(const QString&)));
    connect(m_ptxtSIL_KLVpM1_Up, SIGNAL(textChanged(const QString&)),
            m_ptxtSIL_KLVSiM1_Up, SLOT(setText(const QString&)));
    //KLVnSiM1_Dn
    connect(m_ptxtSIL_KLVnSiM1_Up, SIGNAL(textChanged(const QString&)),
            m_ptxtSIL_KLVnM1_Up, SLOT(setText(const QString&)));
    connect(m_ptxtSIL_KLVnSiM1_Up, SIGNAL(textChanged(const QString&)),
            m_ptxtSIL_KLVpM1_Up, SLOT(setText(const QString&)));
    connect(m_ptxtSIL_KLVnSiM1_Up, SIGNAL(textChanged(const QString&)),
            m_ptxtSIL_KLVpSiM1_Up, SLOT(setText(const QString&)));
    connect(m_ptxtSIL_KLVnSiM1_Up, SIGNAL(textChanged(const QString&)),
            m_ptxtSIL_KLVSiM1_Up, SLOT(setText(const QString&)));
    //KLVpSiM1_Dn
    connect(m_ptxtSIL_KLVpSiM1_Up, SIGNAL(textChanged(const QString&)),
            m_ptxtSIL_KLVnM1_Up, SLOT(setText(const QString&)));
    connect(m_ptxtSIL_KLVpSiM1_Up, SIGNAL(textChanged(const QString&)),
            m_ptxtSIL_KLVpM1_Up, SLOT(setText(const QString&)));
    connect(m_ptxtSIL_KLVpSiM1_Up, SIGNAL(textChanged(const QString&)),
            m_ptxtSIL_KLVnSiM1_Up, SLOT(setText(const QString&)));
    connect(m_ptxtSIL_KLVpSiM1_Up, SIGNAL(textChanged(const QString&)),
            m_ptxtSIL_KLVSiM1_Up, SLOT(setText(const QString&)));
    //KLVSiM1_Dn
    connect(m_ptxtSIL_KLVSiM1_Up, SIGNAL(textChanged(const QString&)),
            m_ptxtSIL_KLVnM1_Up, SLOT(setText(const QString&)));
    connect(m_ptxtSIL_KLVSiM1_Up, SIGNAL(textChanged(const QString&)),
            m_ptxtSIL_KLVpM1_Up, SLOT(setText(const QString&)));
    connect(m_ptxtSIL_KLVSiM1_Up, SIGNAL(textChanged(const QString&)),
            m_ptxtSIL_KLVnSiM1_Up, SLOT(setText(const QString&)));
    connect(m_ptxtSIL_KLVSiM1_Up, SIGNAL(textChanged(const QString&)),
            m_ptxtSIL_KLVpSiM1_Up, SLOT(setText(const QString&)));

    connect(m_ptxtSIL_KLVnM1_Up, SIGNAL(textChanged(const QString&)),
            this, SLOT(slotCmdApplyEnabled()));
}
void LocalSettingsWin::ZsDn_SIL_connections() const
{
    //ZnM1_Dn
    connect(m_ptxtSIL_ZnM1_Dn, SIGNAL(textChanged(const QString&)),
            m_ptxtSIL_ZpM1_Dn, SLOT(setText(const QString&)));
    connect(m_ptxtSIL_ZnM1_Dn, SIGNAL(textChanged(const QString&)),
            m_ptxtSIL_ZnSiM1_Dn, SLOT(setText(const QString&)));
    connect(m_ptxtSIL_ZnM1_Dn, SIGNAL(textChanged(const QString&)),
            m_ptxtSIL_ZpSiM1_Dn, SLOT(setText(const QString&)));
    connect(m_ptxtSIL_ZnM1_Dn, SIGNAL(textChanged(const QString&)),
            m_ptxtSIL_ZSiM1_Dn, SLOT(setText(const QString&)));
    //ZpM1_Dn
    connect(m_ptxtSIL_ZpM1_Dn, SIGNAL(textChanged(const QString&)),
            m_ptxtSIL_ZnM1_Dn, SLOT(setText(const QString&)));
    connect(m_ptxtSIL_ZpM1_Dn, SIGNAL(textChanged(const QString&)),
            m_ptxtSIL_ZnSiM1_Dn, SLOT(setText(const QString&)));
    connect(m_ptxtSIL_ZpM1_Dn, SIGNAL(textChanged(const QString&)),
            m_ptxtSIL_ZpSiM1_Dn, SLOT(setText(const QString&)));
    connect(m_ptxtSIL_ZpM1_Dn, SIGNAL(textChanged(const QString&)),
            m_ptxtSIL_ZSiM1_Dn, SLOT(setText(const QString&)));
    //ZnSiM1_Dn
    connect(m_ptxtSIL_ZnSiM1_Dn, SIGNAL(textChanged(const QString&)),
            m_ptxtSIL_ZnM1_Dn, SLOT(setText(const QString&)));
    connect(m_ptxtSIL_ZnSiM1_Dn, SIGNAL(textChanged(const QString&)),
            m_ptxtSIL_ZpM1_Dn, SLOT(setText(const QString&)));
    connect(m_ptxtSIL_ZnSiM1_Dn, SIGNAL(textChanged(const QString&)),
            m_ptxtSIL_ZpSiM1_Dn, SLOT(setText(const QString&)));
    connect(m_ptxtSIL_ZnSiM1_Dn, SIGNAL(textChanged(const QString&)),
            m_ptxtSIL_ZSiM1_Dn, SLOT(setText(const QString&)));
    //ZpSiM1_Dn
    connect(m_ptxtSIL_ZpSiM1_Dn, SIGNAL(textChanged(const QString&)),
            m_ptxtSIL_ZnM1_Dn, SLOT(setText(const QString&)));
    connect(m_ptxtSIL_ZpSiM1_Dn, SIGNAL(textChanged(const QString&)),
            m_ptxtSIL_ZpM1_Dn, SLOT(setText(const QString&)));
    connect(m_ptxtSIL_ZpSiM1_Dn, SIGNAL(textChanged(const QString&)),
            m_ptxtSIL_ZnSiM1_Dn, SLOT(setText(const QString&)));
    connect(m_ptxtSIL_ZpSiM1_Dn, SIGNAL(textChanged(const QString&)),
            m_ptxtSIL_ZSiM1_Dn, SLOT(setText(const QString&)));
    //ZSiM1_Dn
    connect(m_ptxtSIL_ZSiM1_Dn, SIGNAL(textChanged(const QString&)),
            m_ptxtSIL_ZnM1_Dn, SLOT(setText(const QString&)));
    connect(m_ptxtSIL_ZSiM1_Dn, SIGNAL(textChanged(const QString&)),
            m_ptxtSIL_ZpM1_Dn, SLOT(setText(const QString&)));
    connect(m_ptxtSIL_ZSiM1_Dn, SIGNAL(textChanged(const QString&)),
            m_ptxtSIL_ZnSiM1_Dn, SLOT(setText(const QString&)));
    connect(m_ptxtSIL_ZSiM1_Dn, SIGNAL(textChanged(const QString&)),
            m_ptxtSIL_ZpSiM1_Dn, SLOT(setText(const QString&)));

    connect(m_ptxtSIL_ZnM1_Dn, SIGNAL(textChanged(const QString&)),
            this, SLOT(slotCmdApplyEnabled()));
}
void LocalSettingsWin::ZsUp_SIL_connections() const
{
    //ZnM1_Up
    connect(m_ptxtSIL_ZnM1_Up, SIGNAL(textChanged(const QString&)),
            m_ptxtSIL_ZpM1_Up, SLOT(setText(const QString&)));
    connect(m_ptxtSIL_ZnM1_Up, SIGNAL(textChanged(const QString&)),
            m_ptxtSIL_ZnSiM1_Up, SLOT(setText(const QString&)));
    connect(m_ptxtSIL_ZnM1_Up, SIGNAL(textChanged(const QString&)),
            m_ptxtSIL_ZpSiM1_Up, SLOT(setText(const QString&)));
    connect(m_ptxtSIL_ZnM1_Up, SIGNAL(textChanged(const QString&)),
            m_ptxtSIL_ZSiM1_Up, SLOT(setText(const QString&)));
    //ZpM1_Up
    connect(m_ptxtSIL_ZpM1_Up, SIGNAL(textChanged(const QString&)),
            m_ptxtSIL_ZnM1_Up, SLOT(setText(const QString&)));
    connect(m_ptxtSIL_ZpM1_Up, SIGNAL(textChanged(const QString&)),
            m_ptxtSIL_ZnSiM1_Up, SLOT(setText(const QString&)));
    connect(m_ptxtSIL_ZpM1_Up, SIGNAL(textChanged(const QString&)),
            m_ptxtSIL_ZpSiM1_Up, SLOT(setText(const QString&)));
    connect(m_ptxtSIL_ZpM1_Up, SIGNAL(textChanged(const QString&)),
            m_ptxtSIL_ZSiM1_Up, SLOT(setText(const QString&)));
    //ZnSiM1_Up
    connect(m_ptxtSIL_ZnSiM1_Up, SIGNAL(textChanged(const QString&)),
            m_ptxtSIL_ZnM1_Up, SLOT(setText(const QString&)));
    connect(m_ptxtSIL_ZnSiM1_Up, SIGNAL(textChanged(const QString&)),
            m_ptxtSIL_ZpM1_Up, SLOT(setText(const QString&)));
    connect(m_ptxtSIL_ZnSiM1_Up, SIGNAL(textChanged(const QString&)),
            m_ptxtSIL_ZpSiM1_Up, SLOT(setText(const QString&)));
    connect(m_ptxtSIL_ZnSiM1_Up, SIGNAL(textChanged(const QString&)),
            m_ptxtSIL_ZSiM1_Up, SLOT(setText(const QString&)));
    //ZpSiM1_Up
    connect(m_ptxtSIL_ZpSiM1_Up, SIGNAL(textChanged(const QString&)),
            m_ptxtSIL_ZnM1_Up, SLOT(setText(const QString&)));
    connect(m_ptxtSIL_ZpSiM1_Up, SIGNAL(textChanged(const QString&)),
            m_ptxtSIL_ZpM1_Up, SLOT(setText(const QString&)));
    connect(m_ptxtSIL_ZpSiM1_Up, SIGNAL(textChanged(const QString&)),
            m_ptxtSIL_ZnSiM1_Up, SLOT(setText(const QString&)));
    connect(m_ptxtSIL_ZpSiM1_Up, SIGNAL(textChanged(const QString&)),
            m_ptxtSIL_ZSiM1_Up, SLOT(setText(const QString&)));
    //ZSiM1_Up
    connect(m_ptxtSIL_ZSiM1_Up, SIGNAL(textChanged(const QString&)),
            m_ptxtSIL_ZnM1_Up, SLOT(setText(const QString&)));
    connect(m_ptxtSIL_ZSiM1_Up, SIGNAL(textChanged(const QString&)),
            m_ptxtSIL_ZpM1_Up, SLOT(setText(const QString&)));
    connect(m_ptxtSIL_ZSiM1_Up, SIGNAL(textChanged(const QString&)),
            m_ptxtSIL_ZnSiM1_Up, SLOT(setText(const QString&)));
    connect(m_ptxtSIL_ZSiM1_Up, SIGNAL(textChanged(const QString&)),
            m_ptxtSIL_ZpSiM1_Up, SLOT(setText(const QString&)));

    connect(m_ptxtSIL_ZnM1_Up, SIGNAL(textChanged(const QString&)),
            this, SLOT(slotCmdApplyEnabled()));
}
void LocalSettingsWin::Rz09Dn_SIL_connections() const
{
    //RZnTiSi09_Dn
    connect(m_ptxtRZnTiSi09_Dn, SIGNAL(textChanged(const QString&)),
            m_ptxtRZpTiSi09_Dn, SLOT(setText(const QString&)));
    connect(m_ptxtRZnTiSi09_Dn, SIGNAL(textChanged(const QString&)),
            m_ptxtRZnSiTiSi09_Dn, SLOT(setText(const QString&)));
    connect(m_ptxtRZnTiSi09_Dn, SIGNAL(textChanged(const QString&)),
            m_ptxtRZpTiSi09_Dn, SLOT(setText(const QString&)));
    connect(m_ptxtRZnTiSi09_Dn, SIGNAL(textChanged(const QString&)),
            m_ptxtRZSiTiSi09_Dn, SLOT(setText(const QString&)));

    //RZpTiSi09_Dn
    connect(m_ptxtRZpTiSi09_Dn, SIGNAL(textChanged(const QString&)),
            m_ptxtRZnTiSi09_Dn, SLOT(setText(const QString&)));
    connect(m_ptxtRZpTiSi09_Dn, SIGNAL(textChanged(const QString&)),
            m_ptxtRZnSiTiSi09_Dn, SLOT(setText(const QString&)));
    connect(m_ptxtRZpTiSi09_Dn, SIGNAL(textChanged(const QString&)),
            m_ptxtRZpTiSi09_Dn, SLOT(setText(const QString&)));
    connect(m_ptxtRZpTiSi09_Dn, SIGNAL(textChanged(const QString&)),
            m_ptxtRZSiTiSi09_Dn, SLOT(setText(const QString&)));

    //RZnSiTiSi09_Dn
    connect(m_ptxtRZnSiTiSi09_Dn, SIGNAL(textChanged(const QString&)),
            m_ptxtRZnTiSi09_Dn, SLOT(setText(const QString&)));
    connect(m_ptxtRZnSiTiSi09_Dn, SIGNAL(textChanged(const QString&)),
            m_ptxtRZpTiSi09_Dn, SLOT(setText(const QString&)));
    connect(m_ptxtRZnSiTiSi09_Dn, SIGNAL(textChanged(const QString&)),
            m_ptxtRZpSiTiSi09_Dn, SLOT(setText(const QString&)));
    connect(m_ptxtRZnSiTiSi09_Dn, SIGNAL(textChanged(const QString&)),
            m_ptxtRZSiTiSi09_Dn, SLOT(setText(const QString&)));

    //RZpSiTiSi09_Dn
    connect(m_ptxtRZpSiTiSi09_Dn, SIGNAL(textChanged(const QString&)),
            m_ptxtRZnTiSi09_Dn, SLOT(setText(const QString&)));
    connect(m_ptxtRZpSiTiSi09_Dn, SIGNAL(textChanged(const QString&)),
            m_ptxtRZpTiSi09_Dn, SLOT(setText(const QString&)));
    connect(m_ptxtRZpSiTiSi09_Dn, SIGNAL(textChanged(const QString&)),
            m_ptxtRZnSiTiSi09_Dn, SLOT(setText(const QString&)));
    connect(m_ptxtRZpSiTiSi09_Dn, SIGNAL(textChanged(const QString&)),
            m_ptxtRZSiTiSi09_Dn, SLOT(setText(const QString&)));

    //RZSiTiSi09_Dn
    connect(m_ptxtRZSiTiSi09_Dn, SIGNAL(textChanged(const QString&)),
            m_ptxtRZnTiSi09_Dn, SLOT(setText(const QString&)));
    connect(m_ptxtRZSiTiSi09_Dn, SIGNAL(textChanged(const QString&)),
            m_ptxtRZpTiSi09_Dn, SLOT(setText(const QString&)));
    connect(m_ptxtRZSiTiSi09_Dn, SIGNAL(textChanged(const QString&)),
            m_ptxtRZnSiTiSi09_Dn, SLOT(setText(const QString&)));
    connect(m_ptxtRZSiTiSi09_Dn, SIGNAL(textChanged(const QString&)),
            m_ptxtRZpSiTiSi09_Dn, SLOT(setText(const QString&)));

    connect(m_ptxtRZnTiSi09_Dn, SIGNAL(textChanged(const QString&)),
            this, SLOT(slotCmdApplyEnabled()));
}
void LocalSettingsWin::Rz09Up_SIL_connections() const
{
    //RZnTiSi09_Up
    connect(m_ptxtRZnTiSi09_Up, SIGNAL(textChanged(const QString&)),
            m_ptxtRZpTiSi09_Up, SLOT(setText(const QString&)));
    connect(m_ptxtRZnTiSi09_Up, SIGNAL(textChanged(const QString&)),
            m_ptxtRZnSiTiSi09_Up, SLOT(setText(const QString&)));
    connect(m_ptxtRZnTiSi09_Up, SIGNAL(textChanged(const QString&)),
            m_ptxtRZpTiSi09_Up, SLOT(setText(const QString&)));
    connect(m_ptxtRZnTiSi09_Up, SIGNAL(textChanged(const QString&)),
            m_ptxtRZSiTiSi09_Up, SLOT(setText(const QString&)));

    //RZpTiSi09_Up
    connect(m_ptxtRZpTiSi09_Up, SIGNAL(textChanged(const QString&)),
            m_ptxtRZnTiSi09_Up, SLOT(setText(const QString&)));
    connect(m_ptxtRZpTiSi09_Up, SIGNAL(textChanged(const QString&)),
            m_ptxtRZnSiTiSi09_Up, SLOT(setText(const QString&)));
    connect(m_ptxtRZpTiSi09_Up, SIGNAL(textChanged(const QString&)),
            m_ptxtRZpTiSi09_Up, SLOT(setText(const QString&)));
    connect(m_ptxtRZpTiSi09_Up, SIGNAL(textChanged(const QString&)),
            m_ptxtRZSiTiSi09_Up, SLOT(setText(const QString&)));

    //RZnSiTiSi09_Up
    connect(m_ptxtRZnSiTiSi09_Up, SIGNAL(textChanged(const QString&)),
            m_ptxtRZnTiSi09_Up, SLOT(setText(const QString&)));
    connect(m_ptxtRZnSiTiSi09_Up, SIGNAL(textChanged(const QString&)),
            m_ptxtRZpTiSi09_Up, SLOT(setText(const QString&)));
    connect(m_ptxtRZnSiTiSi09_Up, SIGNAL(textChanged(const QString&)),
            m_ptxtRZpSiTiSi09_Up, SLOT(setText(const QString&)));
    connect(m_ptxtRZnSiTiSi09_Up, SIGNAL(textChanged(const QString&)),
            m_ptxtRZSiTiSi09_Up, SLOT(setText(const QString&)));

    //RZpSiTiSi09_Up
    connect(m_ptxtRZpSiTiSi09_Up, SIGNAL(textChanged(const QString&)),
            m_ptxtRZnTiSi09_Up, SLOT(setText(const QString&)));
    connect(m_ptxtRZpSiTiSi09_Up, SIGNAL(textChanged(const QString&)),
            m_ptxtRZpTiSi09_Up, SLOT(setText(const QString&)));
    connect(m_ptxtRZpSiTiSi09_Up, SIGNAL(textChanged(const QString&)),
            m_ptxtRZnSiTiSi09_Up, SLOT(setText(const QString&)));
    connect(m_ptxtRZpSiTiSi09_Up, SIGNAL(textChanged(const QString&)),
            m_ptxtRZSiTiSi09_Up, SLOT(setText(const QString&)));

    //RZSiTiSi09_Up
    connect(m_ptxtRZSiTiSi09_Up, SIGNAL(textChanged(const QString&)),
            m_ptxtRZnTiSi09_Up, SLOT(setText(const QString&)));
    connect(m_ptxtRZSiTiSi09_Up, SIGNAL(textChanged(const QString&)),
            m_ptxtRZpTiSi09_Up, SLOT(setText(const QString&)));
    connect(m_ptxtRZSiTiSi09_Up, SIGNAL(textChanged(const QString&)),
            m_ptxtRZnSiTiSi09_Up, SLOT(setText(const QString&)));
    connect(m_ptxtRZSiTiSi09_Up, SIGNAL(textChanged(const QString&)),
            m_ptxtRZpSiTiSi09_Up, SLOT(setText(const QString&)));

    connect(m_ptxtRZnTiSi09_Up, SIGNAL(textChanged(const QString&)),
            this, SLOT(slotCmdApplyEnabled()));
}
void LocalSettingsWin::Rz05Dn_SIL_connections() const
{
    //RZnTiSi05_Dn
    connect(m_ptxtRZnTiSi05_Dn, SIGNAL(textChanged(const QString&)),
            m_ptxtRZpTiSi05_Dn, SLOT(setText(const QString&)));
    connect(m_ptxtRZnTiSi05_Dn, SIGNAL(textChanged(const QString&)),
            m_ptxtRZnSiTiSi05_Dn, SLOT(setText(const QString&)));
    connect(m_ptxtRZnTiSi05_Dn, SIGNAL(textChanged(const QString&)),
            m_ptxtRZpTiSi05_Dn, SLOT(setText(const QString&)));
    connect(m_ptxtRZnTiSi05_Dn, SIGNAL(textChanged(const QString&)),
            m_ptxtRZSiTiSi05_Dn, SLOT(setText(const QString&)));

    //RZpTiSi05_Dn
    connect(m_ptxtRZpTiSi05_Dn, SIGNAL(textChanged(const QString&)),
            m_ptxtRZnTiSi05_Dn, SLOT(setText(const QString&)));
    connect(m_ptxtRZpTiSi05_Dn, SIGNAL(textChanged(const QString&)),
            m_ptxtRZnSiTiSi05_Dn, SLOT(setText(const QString&)));
    connect(m_ptxtRZpTiSi05_Dn, SIGNAL(textChanged(const QString&)),
            m_ptxtRZpTiSi05_Dn, SLOT(setText(const QString&)));
    connect(m_ptxtRZpTiSi05_Dn, SIGNAL(textChanged(const QString&)),
            m_ptxtRZSiTiSi05_Dn, SLOT(setText(const QString&)));

    //RZnSiTiSi05_Dn
    connect(m_ptxtRZnSiTiSi05_Dn, SIGNAL(textChanged(const QString&)),
            m_ptxtRZnTiSi05_Dn, SLOT(setText(const QString&)));
    connect(m_ptxtRZnSiTiSi05_Dn, SIGNAL(textChanged(const QString&)),
            m_ptxtRZpTiSi05_Dn, SLOT(setText(const QString&)));
    connect(m_ptxtRZnSiTiSi05_Dn, SIGNAL(textChanged(const QString&)),
            m_ptxtRZpSiTiSi05_Dn, SLOT(setText(const QString&)));
    connect(m_ptxtRZnSiTiSi05_Dn, SIGNAL(textChanged(const QString&)),
            m_ptxtRZSiTiSi05_Dn, SLOT(setText(const QString&)));

    //RZpSiTiSi05_Dn
    connect(m_ptxtRZpSiTiSi05_Dn, SIGNAL(textChanged(const QString&)),
            m_ptxtRZnTiSi05_Dn, SLOT(setText(const QString&)));
    connect(m_ptxtRZpSiTiSi05_Dn, SIGNAL(textChanged(const QString&)),
            m_ptxtRZpTiSi05_Dn, SLOT(setText(const QString&)));
    connect(m_ptxtRZpSiTiSi05_Dn, SIGNAL(textChanged(const QString&)),
            m_ptxtRZnSiTiSi05_Dn, SLOT(setText(const QString&)));
    connect(m_ptxtRZpSiTiSi05_Dn, SIGNAL(textChanged(const QString&)),
            m_ptxtRZSiTiSi05_Dn, SLOT(setText(const QString&)));

    //RZSiTiSi05_Dn
    connect(m_ptxtRZSiTiSi05_Dn, SIGNAL(textChanged(const QString&)),
            m_ptxtRZnTiSi05_Dn, SLOT(setText(const QString&)));
    connect(m_ptxtRZSiTiSi05_Dn, SIGNAL(textChanged(const QString&)),
            m_ptxtRZpTiSi05_Dn, SLOT(setText(const QString&)));
    connect(m_ptxtRZSiTiSi05_Dn, SIGNAL(textChanged(const QString&)),
            m_ptxtRZnSiTiSi05_Dn, SLOT(setText(const QString&)));
    connect(m_ptxtRZSiTiSi05_Dn, SIGNAL(textChanged(const QString&)),
            m_ptxtRZpSiTiSi05_Dn, SLOT(setText(const QString&)));

    connect(m_ptxtRZnTiSi05_Dn, SIGNAL(textChanged(const QString&)),
            this, SLOT(slotCmdApplyEnabled()));
}
void LocalSettingsWin::Rz05Up_SIL_connections() const
{
    //RZnTiSi05_Up
    connect(m_ptxtRZnTiSi05_Up, SIGNAL(textChanged(const QString&)),
            m_ptxtRZpTiSi05_Up, SLOT(setText(const QString&)));
    connect(m_ptxtRZnTiSi05_Up, SIGNAL(textChanged(const QString&)),
            m_ptxtRZnSiTiSi05_Up, SLOT(setText(const QString&)));
    connect(m_ptxtRZnTiSi05_Up, SIGNAL(textChanged(const QString&)),
            m_ptxtRZpTiSi05_Up, SLOT(setText(const QString&)));
    connect(m_ptxtRZnTiSi05_Up, SIGNAL(textChanged(const QString&)),
            m_ptxtRZSiTiSi05_Up, SLOT(setText(const QString&)));

    //RZpTiSi05_Up
    connect(m_ptxtRZpTiSi05_Up, SIGNAL(textChanged(const QString&)),
            m_ptxtRZnTiSi05_Up, SLOT(setText(const QString&)));
    connect(m_ptxtRZpTiSi05_Up, SIGNAL(textChanged(const QString&)),
            m_ptxtRZnSiTiSi05_Up, SLOT(setText(const QString&)));
    connect(m_ptxtRZpTiSi05_Up, SIGNAL(textChanged(const QString&)),
            m_ptxtRZpTiSi05_Up, SLOT(setText(const QString&)));
    connect(m_ptxtRZpTiSi05_Up, SIGNAL(textChanged(const QString&)),
            m_ptxtRZSiTiSi05_Up, SLOT(setText(const QString&)));

    //RZnSiTiSi05_Up
    connect(m_ptxtRZnSiTiSi05_Up, SIGNAL(textChanged(const QString&)),
            m_ptxtRZnTiSi05_Up, SLOT(setText(const QString&)));
    connect(m_ptxtRZnSiTiSi05_Up, SIGNAL(textChanged(const QString&)),
            m_ptxtRZpTiSi05_Up, SLOT(setText(const QString&)));
    connect(m_ptxtRZnSiTiSi05_Up, SIGNAL(textChanged(const QString&)),
            m_ptxtRZpSiTiSi05_Up, SLOT(setText(const QString&)));
    connect(m_ptxtRZnSiTiSi05_Up, SIGNAL(textChanged(const QString&)),
            m_ptxtRZSiTiSi05_Up, SLOT(setText(const QString&)));

    //RZpSiTiSi05_Up
    connect(m_ptxtRZpSiTiSi05_Up, SIGNAL(textChanged(const QString&)),
            m_ptxtRZnTiSi05_Up, SLOT(setText(const QString&)));
    connect(m_ptxtRZpSiTiSi05_Up, SIGNAL(textChanged(const QString&)),
            m_ptxtRZpTiSi05_Up, SLOT(setText(const QString&)));
    connect(m_ptxtRZpSiTiSi05_Up, SIGNAL(textChanged(const QString&)),
            m_ptxtRZnSiTiSi05_Up, SLOT(setText(const QString&)));
    connect(m_ptxtRZpSiTiSi05_Up, SIGNAL(textChanged(const QString&)),
            m_ptxtRZSiTiSi05_Up, SLOT(setText(const QString&)));

    //RZSiTiSi05_Up
    connect(m_ptxtRZSiTiSi05_Up, SIGNAL(textChanged(const QString&)),
            m_ptxtRZnTiSi05_Up, SLOT(setText(const QString&)));
    connect(m_ptxtRZSiTiSi05_Up, SIGNAL(textChanged(const QString&)),
            m_ptxtRZpTiSi05_Up, SLOT(setText(const QString&)));
    connect(m_ptxtRZSiTiSi05_Up, SIGNAL(textChanged(const QString&)),
            m_ptxtRZnSiTiSi05_Up, SLOT(setText(const QString&)));
    connect(m_ptxtRZSiTiSi05_Up, SIGNAL(textChanged(const QString&)),
            m_ptxtRZpSiTiSi05_Up, SLOT(setText(const QString&)));

    connect(m_ptxtRZnTiSi05_Up, SIGNAL(textChanged(const QString&)),
            this, SLOT(slotCmdApplyEnabled()));
}
void LocalSettingsWin::Rz035Dn_SIL_connections() const
{
    //RZnTiSi035_Dn
    connect(m_ptxtRZnTiSi035_Dn, SIGNAL(textChanged(const QString&)),
            m_ptxtRZpTiSi035_Dn, SLOT(setText(const QString&)));
    connect(m_ptxtRZnTiSi035_Dn, SIGNAL(textChanged(const QString&)),
            m_ptxtRZnSiTiSi035_Dn, SLOT(setText(const QString&)));
    connect(m_ptxtRZnTiSi035_Dn, SIGNAL(textChanged(const QString&)),
            m_ptxtRZpTiSi035_Dn, SLOT(setText(const QString&)));
    connect(m_ptxtRZnTiSi035_Dn, SIGNAL(textChanged(const QString&)),
            m_ptxtRZSiTiSi035_Dn, SLOT(setText(const QString&)));

    //RZpTiSi035_Dn
    connect(m_ptxtRZpTiSi035_Dn, SIGNAL(textChanged(const QString&)),
            m_ptxtRZnTiSi035_Dn, SLOT(setText(const QString&)));
    connect(m_ptxtRZpTiSi035_Dn, SIGNAL(textChanged(const QString&)),
            m_ptxtRZnSiTiSi035_Dn, SLOT(setText(const QString&)));
    connect(m_ptxtRZpTiSi035_Dn, SIGNAL(textChanged(const QString&)),
            m_ptxtRZpTiSi035_Dn, SLOT(setText(const QString&)));
    connect(m_ptxtRZpTiSi035_Dn, SIGNAL(textChanged(const QString&)),
            m_ptxtRZSiTiSi035_Dn, SLOT(setText(const QString&)));

    //RZnSiTiSi035_Dn
    connect(m_ptxtRZnSiTiSi035_Dn, SIGNAL(textChanged(const QString&)),
            m_ptxtRZnTiSi035_Dn, SLOT(setText(const QString&)));
    connect(m_ptxtRZnSiTiSi035_Dn, SIGNAL(textChanged(const QString&)),
            m_ptxtRZpTiSi035_Dn, SLOT(setText(const QString&)));
    connect(m_ptxtRZnSiTiSi035_Dn, SIGNAL(textChanged(const QString&)),
            m_ptxtRZpSiTiSi035_Dn, SLOT(setText(const QString&)));
    connect(m_ptxtRZnSiTiSi035_Dn, SIGNAL(textChanged(const QString&)),
            m_ptxtRZSiTiSi035_Dn, SLOT(setText(const QString&)));

    //RZpSiTiSi035_Dn
    connect(m_ptxtRZpSiTiSi035_Dn, SIGNAL(textChanged(const QString&)),
            m_ptxtRZnTiSi035_Dn, SLOT(setText(const QString&)));
    connect(m_ptxtRZpSiTiSi035_Dn, SIGNAL(textChanged(const QString&)),
            m_ptxtRZpTiSi035_Dn, SLOT(setText(const QString&)));
    connect(m_ptxtRZpSiTiSi035_Dn, SIGNAL(textChanged(const QString&)),
            m_ptxtRZnSiTiSi035_Dn, SLOT(setText(const QString&)));
    connect(m_ptxtRZpSiTiSi035_Dn, SIGNAL(textChanged(const QString&)),
            m_ptxtRZSiTiSi035_Dn, SLOT(setText(const QString&)));

    //RZSiTiSi035_Dn
    connect(m_ptxtRZSiTiSi035_Dn, SIGNAL(textChanged(const QString&)),
            m_ptxtRZnTiSi035_Dn, SLOT(setText(const QString&)));
    connect(m_ptxtRZSiTiSi035_Dn, SIGNAL(textChanged(const QString&)),
            m_ptxtRZpTiSi035_Dn, SLOT(setText(const QString&)));
    connect(m_ptxtRZSiTiSi035_Dn, SIGNAL(textChanged(const QString&)),
            m_ptxtRZnSiTiSi035_Dn, SLOT(setText(const QString&)));
    connect(m_ptxtRZSiTiSi035_Dn, SIGNAL(textChanged(const QString&)),
            m_ptxtRZpSiTiSi035_Dn, SLOT(setText(const QString&)));

    connect(m_ptxtRZnTiSi035_Dn, SIGNAL(textChanged(const QString&)),
            this, SLOT(slotCmdApplyEnabled()));
}
void LocalSettingsWin::Rz035Up_SIL_connections() const
{
    //RZnTiSi035_Up
    connect(m_ptxtRZnTiSi035_Up, SIGNAL(textChanged(const QString&)),
            m_ptxtRZpTiSi035_Up, SLOT(setText(const QString&)));
    connect(m_ptxtRZnTiSi035_Up, SIGNAL(textChanged(const QString&)),
            m_ptxtRZnSiTiSi035_Up, SLOT(setText(const QString&)));
    connect(m_ptxtRZnTiSi035_Up, SIGNAL(textChanged(const QString&)),
            m_ptxtRZpTiSi035_Up, SLOT(setText(const QString&)));
    connect(m_ptxtRZnTiSi035_Up, SIGNAL(textChanged(const QString&)),
            m_ptxtRZSiTiSi035_Up, SLOT(setText(const QString&)));

    //RZpTiSi035_Up
    connect(m_ptxtRZpTiSi035_Up, SIGNAL(textChanged(const QString&)),
            m_ptxtRZnTiSi035_Up, SLOT(setText(const QString&)));
    connect(m_ptxtRZpTiSi035_Up, SIGNAL(textChanged(const QString&)),
            m_ptxtRZnSiTiSi035_Up, SLOT(setText(const QString&)));
    connect(m_ptxtRZpTiSi035_Up, SIGNAL(textChanged(const QString&)),
            m_ptxtRZpTiSi035_Up, SLOT(setText(const QString&)));
    connect(m_ptxtRZpTiSi035_Up, SIGNAL(textChanged(const QString&)),
            m_ptxtRZSiTiSi035_Up, SLOT(setText(const QString&)));

    //RZnSiTiSi035_Up
    connect(m_ptxtRZnSiTiSi035_Up, SIGNAL(textChanged(const QString&)),
            m_ptxtRZnTiSi035_Up, SLOT(setText(const QString&)));
    connect(m_ptxtRZnSiTiSi035_Up, SIGNAL(textChanged(const QString&)),
            m_ptxtRZpTiSi035_Up, SLOT(setText(const QString&)));
    connect(m_ptxtRZnSiTiSi035_Up, SIGNAL(textChanged(const QString&)),
            m_ptxtRZpSiTiSi035_Up, SLOT(setText(const QString&)));
    connect(m_ptxtRZnSiTiSi035_Up, SIGNAL(textChanged(const QString&)),
            m_ptxtRZSiTiSi035_Up, SLOT(setText(const QString&)));

    //RZpSiTiSi035_Up
    connect(m_ptxtRZpSiTiSi035_Up, SIGNAL(textChanged(const QString&)),
            m_ptxtRZnTiSi035_Up, SLOT(setText(const QString&)));
    connect(m_ptxtRZpSiTiSi035_Up, SIGNAL(textChanged(const QString&)),
            m_ptxtRZpTiSi035_Up, SLOT(setText(const QString&)));
    connect(m_ptxtRZpSiTiSi035_Up, SIGNAL(textChanged(const QString&)),
            m_ptxtRZnSiTiSi035_Up, SLOT(setText(const QString&)));
    connect(m_ptxtRZpSiTiSi035_Up, SIGNAL(textChanged(const QString&)),
            m_ptxtRZSiTiSi035_Up, SLOT(setText(const QString&)));

    //RZSiTiSi035_Up
    connect(m_ptxtRZSiTiSi035_Up, SIGNAL(textChanged(const QString&)),
            m_ptxtRZnTiSi035_Up, SLOT(setText(const QString&)));
    connect(m_ptxtRZSiTiSi035_Up, SIGNAL(textChanged(const QString&)),
            m_ptxtRZpTiSi035_Up, SLOT(setText(const QString&)));
    connect(m_ptxtRZSiTiSi035_Up, SIGNAL(textChanged(const QString&)),
            m_ptxtRZnSiTiSi035_Up, SLOT(setText(const QString&)));
    connect(m_ptxtRZSiTiSi035_Up, SIGNAL(textChanged(const QString&)),
            m_ptxtRZpSiTiSi035_Up, SLOT(setText(const QString&)));

    connect(m_ptxtRZnTiSi035_Up, SIGNAL(textChanged(const QString&)),
            this, SLOT(slotCmdApplyEnabled()));
}
void LocalSettingsWin::Rz06Dn_SIL_connections() const
{
    //RZnTiSi06_Dn
    connect(m_ptxtRZnTiSi06_Dn, SIGNAL(textChanged(const QString&)),
            m_ptxtRZpTiSi06_Dn, SLOT(setText(const QString&)));
    connect(m_ptxtRZnTiSi06_Dn, SIGNAL(textChanged(const QString&)),
            m_ptxtRZnSiTiSi06_Dn, SLOT(setText(const QString&)));
    connect(m_ptxtRZnTiSi06_Dn, SIGNAL(textChanged(const QString&)),
            m_ptxtRZpTiSi06_Dn, SLOT(setText(const QString&)));
    connect(m_ptxtRZnTiSi06_Dn, SIGNAL(textChanged(const QString&)),
            m_ptxtRZSiTiSi06_Dn, SLOT(setText(const QString&)));

    //RZpTiSi06_Dn
    connect(m_ptxtRZpTiSi06_Dn, SIGNAL(textChanged(const QString&)),
            m_ptxtRZnTiSi06_Dn, SLOT(setText(const QString&)));
    connect(m_ptxtRZpTiSi06_Dn, SIGNAL(textChanged(const QString&)),
            m_ptxtRZnSiTiSi06_Dn, SLOT(setText(const QString&)));
    connect(m_ptxtRZpTiSi06_Dn, SIGNAL(textChanged(const QString&)),
            m_ptxtRZpTiSi06_Dn, SLOT(setText(const QString&)));
    connect(m_ptxtRZpTiSi06_Dn, SIGNAL(textChanged(const QString&)),
            m_ptxtRZSiTiSi06_Dn, SLOT(setText(const QString&)));

    //RZnSiTiSi06_Dn
    connect(m_ptxtRZnSiTiSi06_Dn, SIGNAL(textChanged(const QString&)),
            m_ptxtRZnTiSi06_Dn, SLOT(setText(const QString&)));
    connect(m_ptxtRZnSiTiSi06_Dn, SIGNAL(textChanged(const QString&)),
            m_ptxtRZpTiSi06_Dn, SLOT(setText(const QString&)));
    connect(m_ptxtRZnSiTiSi06_Dn, SIGNAL(textChanged(const QString&)),
            m_ptxtRZpSiTiSi06_Dn, SLOT(setText(const QString&)));
    connect(m_ptxtRZnSiTiSi06_Dn, SIGNAL(textChanged(const QString&)),
            m_ptxtRZSiTiSi06_Dn, SLOT(setText(const QString&)));

    //RZpSiTiSi06_Dn
    connect(m_ptxtRZpSiTiSi06_Dn, SIGNAL(textChanged(const QString&)),
            m_ptxtRZnTiSi06_Dn, SLOT(setText(const QString&)));
    connect(m_ptxtRZpSiTiSi06_Dn, SIGNAL(textChanged(const QString&)),
            m_ptxtRZpTiSi06_Dn, SLOT(setText(const QString&)));
    connect(m_ptxtRZpSiTiSi06_Dn, SIGNAL(textChanged(const QString&)),
            m_ptxtRZnSiTiSi06_Dn, SLOT(setText(const QString&)));
    connect(m_ptxtRZpSiTiSi06_Dn, SIGNAL(textChanged(const QString&)),
            m_ptxtRZSiTiSi06_Dn, SLOT(setText(const QString&)));

    //RZSiTiSi06_Dn
    connect(m_ptxtRZSiTiSi06_Dn, SIGNAL(textChanged(const QString&)),
            m_ptxtRZnTiSi06_Dn, SLOT(setText(const QString&)));
    connect(m_ptxtRZSiTiSi06_Dn, SIGNAL(textChanged(const QString&)),
            m_ptxtRZpTiSi06_Dn, SLOT(setText(const QString&)));
    connect(m_ptxtRZSiTiSi06_Dn, SIGNAL(textChanged(const QString&)),
            m_ptxtRZnSiTiSi06_Dn, SLOT(setText(const QString&)));
    connect(m_ptxtRZSiTiSi06_Dn, SIGNAL(textChanged(const QString&)),
            m_ptxtRZpSiTiSi06_Dn, SLOT(setText(const QString&)));

    connect(m_ptxtRZnTiSi06_Dn, SIGNAL(textChanged(const QString&)),
            this, SLOT(slotCmdApplyEnabled()));
}
void LocalSettingsWin::Rz06Up_SIL_connections() const
{
    //RZnTiSi06_Up
    connect(m_ptxtRZnTiSi06_Up, SIGNAL(textChanged(const QString&)),
            m_ptxtRZpTiSi06_Up, SLOT(setText(const QString&)));
    connect(m_ptxtRZnTiSi06_Up, SIGNAL(textChanged(const QString&)),
            m_ptxtRZnSiTiSi06_Up, SLOT(setText(const QString&)));
    connect(m_ptxtRZnTiSi06_Up, SIGNAL(textChanged(const QString&)),
            m_ptxtRZpTiSi06_Up, SLOT(setText(const QString&)));
    connect(m_ptxtRZnTiSi06_Up, SIGNAL(textChanged(const QString&)),
            m_ptxtRZSiTiSi06_Up, SLOT(setText(const QString&)));

    //RZpTiSi06_Up
    connect(m_ptxtRZpTiSi06_Up, SIGNAL(textChanged(const QString&)),
            m_ptxtRZnTiSi06_Up, SLOT(setText(const QString&)));
    connect(m_ptxtRZpTiSi06_Up, SIGNAL(textChanged(const QString&)),
            m_ptxtRZnSiTiSi06_Up, SLOT(setText(const QString&)));
    connect(m_ptxtRZpTiSi06_Up, SIGNAL(textChanged(const QString&)),
            m_ptxtRZpTiSi06_Up, SLOT(setText(const QString&)));
    connect(m_ptxtRZpTiSi06_Up, SIGNAL(textChanged(const QString&)),
            m_ptxtRZSiTiSi06_Up, SLOT(setText(const QString&)));

    //RZnSiTiSi06_Up
    connect(m_ptxtRZnSiTiSi06_Up, SIGNAL(textChanged(const QString&)),
            m_ptxtRZnTiSi06_Up, SLOT(setText(const QString&)));
    connect(m_ptxtRZnSiTiSi06_Up, SIGNAL(textChanged(const QString&)),
            m_ptxtRZpTiSi06_Up, SLOT(setText(const QString&)));
    connect(m_ptxtRZnSiTiSi06_Up, SIGNAL(textChanged(const QString&)),
            m_ptxtRZpSiTiSi06_Up, SLOT(setText(const QString&)));
    connect(m_ptxtRZnSiTiSi06_Up, SIGNAL(textChanged(const QString&)),
            m_ptxtRZSiTiSi06_Up, SLOT(setText(const QString&)));

    //RZpSiTiSi06_Up
    connect(m_ptxtRZpSiTiSi06_Up, SIGNAL(textChanged(const QString&)),
            m_ptxtRZnTiSi06_Up, SLOT(setText(const QString&)));
    connect(m_ptxtRZpSiTiSi06_Up, SIGNAL(textChanged(const QString&)),
            m_ptxtRZpTiSi06_Up, SLOT(setText(const QString&)));
    connect(m_ptxtRZpSiTiSi06_Up, SIGNAL(textChanged(const QString&)),
            m_ptxtRZnSiTiSi06_Up, SLOT(setText(const QString&)));
    connect(m_ptxtRZpSiTiSi06_Up, SIGNAL(textChanged(const QString&)),
            m_ptxtRZSiTiSi06_Up, SLOT(setText(const QString&)));

    //RZSiTiSi06_Up
    connect(m_ptxtRZSiTiSi06_Up, SIGNAL(textChanged(const QString&)),
            m_ptxtRZnTiSi06_Up, SLOT(setText(const QString&)));
    connect(m_ptxtRZSiTiSi06_Up, SIGNAL(textChanged(const QString&)),
            m_ptxtRZpTiSi06_Up, SLOT(setText(const QString&)));
    connect(m_ptxtRZSiTiSi06_Up, SIGNAL(textChanged(const QString&)),
            m_ptxtRZnSiTiSi06_Up, SLOT(setText(const QString&)));
    connect(m_ptxtRZSiTiSi06_Up, SIGNAL(textChanged(const QString&)),
            m_ptxtRZpSiTiSi06_Up, SLOT(setText(const QString&)));

    connect(m_ptxtRZnTiSi06_Up, SIGNAL(textChanged(const QString&)),
            this, SLOT(slotCmdApplyEnabled()));
}
//-------------------------------------------------------------------------------------------------
void LocalSettingsWin::VDP_connections() const
{
    connect(m_ptxtVDPnWell_Dn, SIGNAL(textChanged(const QString&)),
            this, SLOT(slotCmdApplyEnabled()));
    connect(m_ptxtVDPpWell_Dn, SIGNAL(textChanged(const QString&)),
            this, SLOT(slotCmdApplyEnabled()));
    connect(m_ptxtVDPn_Dn, SIGNAL(textChanged(const QString&)),
            this, SLOT(slotCmdApplyEnabled()));
    connect(m_ptxtVDPp_Dn, SIGNAL(textChanged(const QString&)),
            this, SLOT(slotCmdApplyEnabled()));
    connect(m_ptxtVDPnSi_Dn, SIGNAL(textChanged(const QString&)),
            this, SLOT(slotCmdApplyEnabled()));
    connect(m_ptxtVDPpSi_Dn, SIGNAL(textChanged(const QString&)),
            this, SLOT(slotCmdApplyEnabled()));

    connect(m_ptxtVDPnWell_Up, SIGNAL(textChanged(const QString&)),
            this, SLOT(slotCmdApplyEnabled()));
    connect(m_ptxtVDPpWell_Up, SIGNAL(textChanged(const QString&)),
            this, SLOT(slotCmdApplyEnabled()));
    connect(m_ptxtVDPn_Up, SIGNAL(textChanged(const QString&)),
            this, SLOT(slotCmdApplyEnabled()));
    connect(m_ptxtVDPp_Up, SIGNAL(textChanged(const QString&)),
            this, SLOT(slotCmdApplyEnabled()));
    connect(m_ptxtVDPnSi_Up, SIGNAL(textChanged(const QString&)),
            this, SLOT(slotCmdApplyEnabled()));
    connect(m_ptxtVDPpSi_Up, SIGNAL(textChanged(const QString&)),
            this, SLOT(slotCmdApplyEnabled()));
}
//-------------------------------------------------------------------------------------------------
void LocalSettingsWin::Me_connections() const
{
    //межметальные Кельвины
    connect(m_ptxtKLV_M1M2_Dn, SIGNAL(textChanged(const QString&)),
            this, SLOT(slotCmdApplyEnabled()));
    connect(m_ptxtKLV_M1M2_Up, SIGNAL(textChanged(const QString&)),
            this, SLOT(slotCmdApplyEnabled()));
    connect(m_ptxtKLV_M2M3_Dn, SIGNAL(textChanged(const QString&)),
            this, SLOT(slotCmdApplyEnabled()));
    connect(m_ptxtKLV_M2M3_Up, SIGNAL(textChanged(const QString&)),
            this, SLOT(slotCmdApplyEnabled()));
    connect(m_ptxtKLV_M3M4_Dn, SIGNAL(textChanged(const QString&)),
            this, SLOT(slotCmdApplyEnabled()));
    connect(m_ptxtKLV_M3M4_Up, SIGNAL(textChanged(const QString&)),
            this, SLOT(slotCmdApplyEnabled()));
    connect(m_ptxtKLV_M1M4_Dn, SIGNAL(textChanged(const QString&)),
            this, SLOT(slotCmdApplyEnabled()));
    connect(m_ptxtKLV_M1M4_Up, SIGNAL(textChanged(const QString&)),
            this, SLOT(slotCmdApplyEnabled()));
    //межметальные цепочки
    connect(m_ptxtZ_M1M2_Dn, SIGNAL(textChanged(const QString&)),
            this, SLOT(slotCmdApplyEnabled()));
    connect(m_ptxtZ_M1M2_Up, SIGNAL(textChanged(const QString&)),
            this, SLOT(slotCmdApplyEnabled()));
    connect(m_ptxtZ_M2M3_Dn, SIGNAL(textChanged(const QString&)),
            this, SLOT(slotCmdApplyEnabled()));
    connect(m_ptxtZ_M2M3_Up, SIGNAL(textChanged(const QString&)),
            this, SLOT(slotCmdApplyEnabled()));
    connect(m_ptxtZ_M3M4_Dn, SIGNAL(textChanged(const QString&)),
            this, SLOT(slotCmdApplyEnabled()));
    connect(m_ptxtZ_M3M4_Up, SIGNAL(textChanged(const QString&)),
            this, SLOT(slotCmdApplyEnabled()));
    connect(m_ptxtZ_M1M4_Dn, SIGNAL(textChanged(const QString&)),
            this, SLOT(slotCmdApplyEnabled()));
    connect(m_ptxtZ_M1M4_Up, SIGNAL(textChanged(const QString&)),
            this, SLOT(slotCmdApplyEnabled()));
    //меандры
    connect(m_ptxtMean1_05_Dn, SIGNAL(textChanged(const QString&)),
            this, SLOT(slotCmdApplyEnabled()));
    connect(m_ptxtMean1_05_Up, SIGNAL(textChanged(const QString&)),
            this, SLOT(slotCmdApplyEnabled()));
    connect(m_ptxtMean1_09_Dn, SIGNAL(textChanged(const QString&)),
            this, SLOT(slotCmdApplyEnabled()));
    connect(m_ptxtMean1_09_Up, SIGNAL(textChanged(const QString&)),
            this, SLOT(slotCmdApplyEnabled()));

    connect(m_ptxtMean2_06_Dn, SIGNAL(textChanged(const QString&)),
            this, SLOT(slotCmdApplyEnabled()));
    connect(m_ptxtMean2_06_Up, SIGNAL(textChanged(const QString&)),
            this, SLOT(slotCmdApplyEnabled()));
    connect(m_ptxtMean2_09_Dn, SIGNAL(textChanged(const QString&)),
            this, SLOT(slotCmdApplyEnabled()));
    connect(m_ptxtMean2_09_Up, SIGNAL(textChanged(const QString&)),
            this, SLOT(slotCmdApplyEnabled()));

    connect(m_ptxtMean3_06_Dn, SIGNAL(textChanged(const QString&)),
            this, SLOT(slotCmdApplyEnabled()));
    connect(m_ptxtMean3_06_Up, SIGNAL(textChanged(const QString&)),
            this, SLOT(slotCmdApplyEnabled()));
    connect(m_ptxtMean3_09_Dn, SIGNAL(textChanged(const QString&)),
            this, SLOT(slotCmdApplyEnabled()));
    connect(m_ptxtMean3_09_Up, SIGNAL(textChanged(const QString&)),
            this, SLOT(slotCmdApplyEnabled()));

    connect(m_ptxtMean4_06_Dn, SIGNAL(textChanged(const QString&)),
            this, SLOT(slotCmdApplyEnabled()));
    connect(m_ptxtMean4_06_Up, SIGNAL(textChanged(const QString&)),
            this, SLOT(slotCmdApplyEnabled()));
    connect(m_ptxtMean4_09_Dn, SIGNAL(textChanged(const QString&)),
            this, SLOT(slotCmdApplyEnabled()));
    connect(m_ptxtMean4_09_Up, SIGNAL(textChanged(const QString&)),
            this, SLOT(slotCmdApplyEnabled()));
}
//-------------------------------------------------------------------------------------------------
void LocalSettingsWin::Tr_connections() const
{
    //An
    connect(m_ptxtAn_Vt_Dn, SIGNAL(textChanged(const QString&)),
            this, SLOT(slotCmdApplyEnabled()));
    connect(m_ptxtAn_VtRevers_Dn, SIGNAL(textChanged(const QString&)),
            this, SLOT(slotCmdApplyEnabled()));
    connect(m_ptxtAn_Be_Dn, SIGNAL(textChanged(const QString&)),
            this, SLOT(slotCmdApplyEnabled()));
    connect(m_ptxtAn_Vbr_Dn, SIGNAL(textChanged(const QString&)),
            this, SLOT(slotCmdApplyEnabled()));
    connect(m_ptxtAn_Gleak_Dn, SIGNAL(textChanged(const QString&)),
            this, SLOT(slotCmdApplyEnabled()));
    connect(m_ptxtAn_DSleak_Dn, SIGNAL(textChanged(const QString&)),
            this, SLOT(slotCmdApplyEnabled()));
    connect(m_ptxtAn_DSw_leak_Dn, SIGNAL(textChanged(const QString&)),
            this, SLOT(slotCmdApplyEnabled()));
    connect(m_ptxtAn_DScurrent_Dn, SIGNAL(textChanged(const QString&)),
            this, SLOT(slotCmdApplyEnabled()));
    connect(m_ptxtAn_DSw_driver_Dn, SIGNAL(textChanged(const QString&)),
            this, SLOT(slotCmdApplyEnabled()));

    connect(m_ptxtAn_Vt_Up, SIGNAL(textChanged(const QString&)),
            this, SLOT(slotCmdApplyEnabled()));
    connect(m_ptxtAn_VtRevers_Up, SIGNAL(textChanged(const QString&)),
            this, SLOT(slotCmdApplyEnabled()));
    connect(m_ptxtAn_Be_Up, SIGNAL(textChanged(const QString&)),
            this, SLOT(slotCmdApplyEnabled()));
    connect(m_ptxtAn_Vbr_Up, SIGNAL(textChanged(const QString&)),
            this, SLOT(slotCmdApplyEnabled()));
    connect(m_ptxtAn_Gleak_Up, SIGNAL(textChanged(const QString&)),
            this, SLOT(slotCmdApplyEnabled()));
    connect(m_ptxtAn_DSleak_Up, SIGNAL(textChanged(const QString&)),
            this, SLOT(slotCmdApplyEnabled()));
    connect(m_ptxtAn_DSw_leak_Up, SIGNAL(textChanged(const QString&)),
            this, SLOT(slotCmdApplyEnabled()));
    connect(m_ptxtAn_DScurrent_Up, SIGNAL(textChanged(const QString&)),
            this, SLOT(slotCmdApplyEnabled()));
    connect(m_ptxtAn_DSw_driver_Up, SIGNAL(textChanged(const QString&)),
            this, SLOT(slotCmdApplyEnabled()));

    //Ap
    connect(m_ptxtAp_Vt_Dn, SIGNAL(textChanged(const QString&)),
            this, SLOT(slotCmdApplyEnabled()));
    connect(m_ptxtAp_VtRevers_Dn, SIGNAL(textChanged(const QString&)),
            this, SLOT(slotCmdApplyEnabled()));
    connect(m_ptxtAp_Be_Dn, SIGNAL(textChanged(const QString&)),
            this, SLOT(slotCmdApplyEnabled()));
    connect(m_ptxtAp_Vbr_Dn, SIGNAL(textChanged(const QString&)),
            this, SLOT(slotCmdApplyEnabled()));
    connect(m_ptxtAp_Gleak_Dn, SIGNAL(textChanged(const QString&)),
            this, SLOT(slotCmdApplyEnabled()));
    connect(m_ptxtAp_DSleak_Dn, SIGNAL(textChanged(const QString&)),
            this, SLOT(slotCmdApplyEnabled()));
    connect(m_ptxtAp_DSw_leak_Dn, SIGNAL(textChanged(const QString&)),
            this, SLOT(slotCmdApplyEnabled()));
    connect(m_ptxtAp_DScurrent_Dn, SIGNAL(textChanged(const QString&)),
            this, SLOT(slotCmdApplyEnabled()));
    connect(m_ptxtAp_DSw_driver_Dn, SIGNAL(textChanged(const QString&)),
            this, SLOT(slotCmdApplyEnabled()));

    connect(m_ptxtAp_Vt_Up, SIGNAL(textChanged(const QString&)),
            this, SLOT(slotCmdApplyEnabled()));
    connect(m_ptxtAp_VtRevers_Up, SIGNAL(textChanged(const QString&)),
            this, SLOT(slotCmdApplyEnabled()));
    connect(m_ptxtAp_Be_Up, SIGNAL(textChanged(const QString&)),
            this, SLOT(slotCmdApplyEnabled()));
    connect(m_ptxtAp_Vbr_Up, SIGNAL(textChanged(const QString&)),
            this, SLOT(slotCmdApplyEnabled()));
    connect(m_ptxtAp_Gleak_Up, SIGNAL(textChanged(const QString&)),
            this, SLOT(slotCmdApplyEnabled()));
    connect(m_ptxtAp_DSleak_Up, SIGNAL(textChanged(const QString&)),
            this, SLOT(slotCmdApplyEnabled()));
    connect(m_ptxtAp_DSw_leak_Up, SIGNAL(textChanged(const QString&)),
            this, SLOT(slotCmdApplyEnabled()));
    connect(m_ptxtAp_DScurrent_Up, SIGNAL(textChanged(const QString&)),
            this, SLOT(slotCmdApplyEnabled()));
    connect(m_ptxtAp_DSw_driver_Up, SIGNAL(textChanged(const QString&)),
            this, SLOT(slotCmdApplyEnabled()));

    //Rn
    connect(m_ptxtRn_Vt_Dn, SIGNAL(textChanged(const QString&)),
            this, SLOT(slotCmdApplyEnabled()));
    connect(m_ptxtRn_VtRevers_Dn, SIGNAL(textChanged(const QString&)),
            this, SLOT(slotCmdApplyEnabled()));
    connect(m_ptxtRn_Be_Dn, SIGNAL(textChanged(const QString&)),
            this, SLOT(slotCmdApplyEnabled()));
    connect(m_ptxtRn_Vbr_Dn, SIGNAL(textChanged(const QString&)),
            this, SLOT(slotCmdApplyEnabled()));
    connect(m_ptxtRn_Gleak_Dn, SIGNAL(textChanged(const QString&)),
            this, SLOT(slotCmdApplyEnabled()));
    connect(m_ptxtRn_DSleak_Dn, SIGNAL(textChanged(const QString&)),
            this, SLOT(slotCmdApplyEnabled()));
    connect(m_ptxtRn_DSw_leak_Dn, SIGNAL(textChanged(const QString&)),
            this, SLOT(slotCmdApplyEnabled()));
    connect(m_ptxtRn_DScurrent_Dn, SIGNAL(textChanged(const QString&)),
            this, SLOT(slotCmdApplyEnabled()));
    connect(m_ptxtRn_DSw_driver_Dn, SIGNAL(textChanged(const QString&)),
            this, SLOT(slotCmdApplyEnabled()));

    connect(m_ptxtRn_Vt_Up, SIGNAL(textChanged(const QString&)),
            this, SLOT(slotCmdApplyEnabled()));
    connect(m_ptxtRn_VtRevers_Up, SIGNAL(textChanged(const QString&)),
            this, SLOT(slotCmdApplyEnabled()));
    connect(m_ptxtRn_Be_Up, SIGNAL(textChanged(const QString&)),
            this, SLOT(slotCmdApplyEnabled()));
    connect(m_ptxtRn_Vbr_Up, SIGNAL(textChanged(const QString&)),
            this, SLOT(slotCmdApplyEnabled()));
    connect(m_ptxtRn_Gleak_Up, SIGNAL(textChanged(const QString&)),
            this, SLOT(slotCmdApplyEnabled()));
    connect(m_ptxtRn_DSleak_Up, SIGNAL(textChanged(const QString&)),
            this, SLOT(slotCmdApplyEnabled()));
    connect(m_ptxtRn_DSw_leak_Up, SIGNAL(textChanged(const QString&)),
            this, SLOT(slotCmdApplyEnabled()));
    connect(m_ptxtRn_DScurrent_Up, SIGNAL(textChanged(const QString&)),
            this, SLOT(slotCmdApplyEnabled()));
    connect(m_ptxtRn_DSw_driver_Up, SIGNAL(textChanged(const QString&)),
            this, SLOT(slotCmdApplyEnabled()));

    //Rp
    connect(m_ptxtRp_Vt_Dn, SIGNAL(textChanged(const QString&)),
            this, SLOT(slotCmdApplyEnabled()));
    connect(m_ptxtRp_VtRevers_Dn, SIGNAL(textChanged(const QString&)),
            this, SLOT(slotCmdApplyEnabled()));
    connect(m_ptxtRp_Be_Dn, SIGNAL(textChanged(const QString&)),
            this, SLOT(slotCmdApplyEnabled()));
    connect(m_ptxtRp_Vbr_Dn, SIGNAL(textChanged(const QString&)),
            this, SLOT(slotCmdApplyEnabled()));
    connect(m_ptxtRp_Gleak_Dn, SIGNAL(textChanged(const QString&)),
            this, SLOT(slotCmdApplyEnabled()));
    connect(m_ptxtRp_DSleak_Dn, SIGNAL(textChanged(const QString&)),
            this, SLOT(slotCmdApplyEnabled()));
    connect(m_ptxtRp_DSw_leak_Dn, SIGNAL(textChanged(const QString&)),
            this, SLOT(slotCmdApplyEnabled()));
    connect(m_ptxtRp_DScurrent_Dn, SIGNAL(textChanged(const QString&)),
            this, SLOT(slotCmdApplyEnabled()));
    connect(m_ptxtRp_DSw_driver_Dn, SIGNAL(textChanged(const QString&)),
            this, SLOT(slotCmdApplyEnabled()));

    connect(m_ptxtRp_Vt_Up, SIGNAL(textChanged(const QString&)),
            this, SLOT(slotCmdApplyEnabled()));
    connect(m_ptxtRp_VtRevers_Up, SIGNAL(textChanged(const QString&)),
            this, SLOT(slotCmdApplyEnabled()));
    connect(m_ptxtRp_Be_Up, SIGNAL(textChanged(const QString&)),
            this, SLOT(slotCmdApplyEnabled()));
    connect(m_ptxtRp_Vbr_Up, SIGNAL(textChanged(const QString&)),
            this, SLOT(slotCmdApplyEnabled()));
    connect(m_ptxtRp_Gleak_Up, SIGNAL(textChanged(const QString&)),
            this, SLOT(slotCmdApplyEnabled()));
    connect(m_ptxtRp_DSleak_Up, SIGNAL(textChanged(const QString&)),
            this, SLOT(slotCmdApplyEnabled()));
    connect(m_ptxtRp_DSw_leak_Up, SIGNAL(textChanged(const QString&)),
            this, SLOT(slotCmdApplyEnabled()));
    connect(m_ptxtRp_DScurrent_Up, SIGNAL(textChanged(const QString&)),
            this, SLOT(slotCmdApplyEnabled()));
    connect(m_ptxtRp_DSw_driver_Up, SIGNAL(textChanged(const QString&)),
            this, SLOT(slotCmdApplyEnabled()));

    //Hn
    connect(m_ptxtHn_Vt_Dn, SIGNAL(textChanged(const QString&)),
            this, SLOT(slotCmdApplyEnabled()));
    connect(m_ptxtHn_VtRevers_Dn, SIGNAL(textChanged(const QString&)),
            this, SLOT(slotCmdApplyEnabled()));
    connect(m_ptxtHn_Be_Dn, SIGNAL(textChanged(const QString&)),
            this, SLOT(slotCmdApplyEnabled()));
    connect(m_ptxtHn_Vbr_Dn, SIGNAL(textChanged(const QString&)),
            this, SLOT(slotCmdApplyEnabled()));
    connect(m_ptxtHn_Gleak_Dn, SIGNAL(textChanged(const QString&)),
            this, SLOT(slotCmdApplyEnabled()));
    connect(m_ptxtHn_DSleak_Dn, SIGNAL(textChanged(const QString&)),
            this, SLOT(slotCmdApplyEnabled()));
    connect(m_ptxtHn_DSw_leak_Dn, SIGNAL(textChanged(const QString&)),
            this, SLOT(slotCmdApplyEnabled()));
    connect(m_ptxtHn_DScurrent_Dn, SIGNAL(textChanged(const QString&)),
            this, SLOT(slotCmdApplyEnabled()));
    connect(m_ptxtHn_DSw_driver_Dn, SIGNAL(textChanged(const QString&)),
            this, SLOT(slotCmdApplyEnabled()));

    connect(m_ptxtHn_Vt_Up, SIGNAL(textChanged(const QString&)),
            this, SLOT(slotCmdApplyEnabled()));
    connect(m_ptxtHn_VtRevers_Up, SIGNAL(textChanged(const QString&)),
            this, SLOT(slotCmdApplyEnabled()));
    connect(m_ptxtHn_Be_Up, SIGNAL(textChanged(const QString&)),
            this, SLOT(slotCmdApplyEnabled()));
    connect(m_ptxtHn_Vbr_Up, SIGNAL(textChanged(const QString&)),
            this, SLOT(slotCmdApplyEnabled()));
    connect(m_ptxtHn_Gleak_Up, SIGNAL(textChanged(const QString&)),
            this, SLOT(slotCmdApplyEnabled()));
    connect(m_ptxtHn_DSleak_Up, SIGNAL(textChanged(const QString&)),
            this, SLOT(slotCmdApplyEnabled()));
    connect(m_ptxtHn_DSw_leak_Up, SIGNAL(textChanged(const QString&)),
            this, SLOT(slotCmdApplyEnabled()));
    connect(m_ptxtHn_DScurrent_Up, SIGNAL(textChanged(const QString&)),
            this, SLOT(slotCmdApplyEnabled()));
    connect(m_ptxtHn_DSw_driver_Up, SIGNAL(textChanged(const QString&)),
            this, SLOT(slotCmdApplyEnabled()));

    //Hp
    connect(m_ptxtHp_Vt_Dn, SIGNAL(textChanged(const QString&)),
            this, SLOT(slotCmdApplyEnabled()));
    connect(m_ptxtHp_VtRevers_Dn, SIGNAL(textChanged(const QString&)),
            this, SLOT(slotCmdApplyEnabled()));
    connect(m_ptxtHp_Be_Dn, SIGNAL(textChanged(const QString&)),
            this, SLOT(slotCmdApplyEnabled()));
    connect(m_ptxtHp_Vbr_Dn, SIGNAL(textChanged(const QString&)),
            this, SLOT(slotCmdApplyEnabled()));
    connect(m_ptxtHp_Gleak_Dn, SIGNAL(textChanged(const QString&)),
            this, SLOT(slotCmdApplyEnabled()));
    connect(m_ptxtHp_DSleak_Dn, SIGNAL(textChanged(const QString&)),
            this, SLOT(slotCmdApplyEnabled()));
    connect(m_ptxtHp_DSw_leak_Dn, SIGNAL(textChanged(const QString&)),
            this, SLOT(slotCmdApplyEnabled()));
    connect(m_ptxtHp_DScurrent_Dn, SIGNAL(textChanged(const QString&)),
            this, SLOT(slotCmdApplyEnabled()));
    connect(m_ptxtHp_DSw_driver_Dn, SIGNAL(textChanged(const QString&)),
            this, SLOT(slotCmdApplyEnabled()));

    connect(m_ptxtHp_Vt_Up, SIGNAL(textChanged(const QString&)),
            this, SLOT(slotCmdApplyEnabled()));
    connect(m_ptxtHp_VtRevers_Up, SIGNAL(textChanged(const QString&)),
            this, SLOT(slotCmdApplyEnabled()));
    connect(m_ptxtHp_Be_Up, SIGNAL(textChanged(const QString&)),
            this, SLOT(slotCmdApplyEnabled()));
    connect(m_ptxtHp_Vbr_Up, SIGNAL(textChanged(const QString&)),
            this, SLOT(slotCmdApplyEnabled()));
    connect(m_ptxtHp_Gleak_Up, SIGNAL(textChanged(const QString&)),
            this, SLOT(slotCmdApplyEnabled()));
    connect(m_ptxtHp_DSleak_Up, SIGNAL(textChanged(const QString&)),
            this, SLOT(slotCmdApplyEnabled()));
    connect(m_ptxtHp_DSw_leak_Up, SIGNAL(textChanged(const QString&)),
            this, SLOT(slotCmdApplyEnabled()));
    connect(m_ptxtHp_DScurrent_Up, SIGNAL(textChanged(const QString&)),
            this, SLOT(slotCmdApplyEnabled()));
    connect(m_ptxtHp_DSw_driver_Up, SIGNAL(textChanged(const QString&)),
            this, SLOT(slotCmdApplyEnabled()));
}
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
//запись настроек
void LocalSettingsWin::writeSettings(bool& error)
{
    //запись настроек в реестр Win
    m_spSettings->beginGroup("/Settings");
    //-----------------------------------------------------------------------------
    //SIL
    m_spSettings->beginGroup("/R_SIL");

    QString key_RSIL_Dn = "/R_SIL_Dn";
    Validator::validateValue(m_ptxtSIL_R_Dn, m_pdblValidator_R_Dn, m_spSettings, key_RSIL_Dn, error);
    QString key_RSIL_Up = "/R_SIL_Up";
    Validator::validateValue(m_ptxtSIL_R_Up, m_pdblValidator_R_Up, m_spSettings, key_RSIL_Up, error);

    m_spSettings->endGroup();
    //-----------------------------------------------------------------------------
    m_spSettings->beginGroup("/KLVs_SIL");

    QString key_KLVnM1_Dn = "/KLVnM1_Dn";
    Validator::validateValue(m_ptxtSIL_KLVnM1_Dn, m_pdblValidator_KLVnM1_Dn, m_spSettings,
                             key_KLVnM1_Dn, error);
    QString key_KLVnM1_Up = "/KLVnM1_Up";
    Validator::validateValue(m_ptxtSIL_KLVnM1_Up, m_pdblValidator_KLVnM1_Up, m_spSettings,
                             key_KLVnM1_Up, error);


    m_spSettings->setValue("/KLVpM1_Dn",         m_ptxtSIL_KLVpM1_Dn->text());
    m_spSettings->setValue("/KLVnSiM1_Dn",       m_ptxtSIL_KLVnSiM1_Dn->text());
    m_spSettings->setValue("/KLVpSiM1_Dn",       m_ptxtSIL_KLVpSiM1_Dn->text());
    m_spSettings->setValue("/KLVSiM1_Dn",        m_ptxtSIL_KLVSiM1_Dn->text());

    m_spSettings->setValue("/KLVpM1_Up",         m_ptxtSIL_KLVpM1_Up->text());
    m_spSettings->setValue("/KLVnSiM1_Up",       m_ptxtSIL_KLVnSiM1_Up->text());
    m_spSettings->setValue("/KLVpSiM1_Up",       m_ptxtSIL_KLVpSiM1_Up->text());
    m_spSettings->setValue("/KLVSiM1_Up",        m_ptxtSIL_KLVSiM1_Up->text());
    m_spSettings->endGroup();

    m_spSettings->beginGroup("/Zs_SIL");
    m_spSettings->setValue("/ZnM1_Dn",           m_ptxtSIL_ZnM1_Dn->text());
    m_spSettings->setValue("/ZpM1_Dn",           m_ptxtSIL_ZpM1_Dn->text());
    m_spSettings->setValue("/ZnSiM1_Dn",         m_ptxtSIL_ZnSiM1_Dn->text());
    m_spSettings->setValue("/ZpSiM1_Dn",         m_ptxtSIL_ZpSiM1_Dn->text());
    m_spSettings->setValue("/ZSiM1_Dn",          m_ptxtSIL_ZSiM1_Dn->text());

    m_spSettings->setValue("/ZnM1_Up",           m_ptxtSIL_ZnM1_Up->text());
    m_spSettings->setValue("/ZpM1_Up",           m_ptxtSIL_ZpM1_Up->text());
    m_spSettings->setValue("/ZnSiM1_Up",         m_ptxtSIL_ZnSiM1_Up->text());
    m_spSettings->setValue("/ZpSiM1_Up",         m_ptxtSIL_ZpSiM1_Up->text());
    m_spSettings->setValue("/ZSiM1_Up",          m_ptxtSIL_ZSiM1_Up->text());
    m_spSettings->endGroup();

    m_spSettings->beginGroup("/RZ09_SIL");
    m_spSettings->setValue("/RZnTiSi09_Dn",      m_ptxtRZnTiSi09_Dn->text());
    m_spSettings->setValue("/RZpTiSi09_Dn",      m_ptxtRZpTiSi09_Dn->text());
    m_spSettings->setValue("/RZnSiTiSi09_Dn",    m_ptxtRZnSiTiSi09_Dn->text());
    m_spSettings->setValue("/RZpSiTiSi09_Dn",    m_ptxtRZpSiTiSi09_Dn->text());
    m_spSettings->setValue("/RZSiTiSi09_Dn",     m_ptxtRZSiTiSi09_Dn->text());

    m_spSettings->setValue("/RZnTiSi09_Up",      m_ptxtRZnTiSi09_Up->text());
    m_spSettings->setValue("/RZpTiSi09_Up",      m_ptxtRZpTiSi09_Up->text());
    m_spSettings->setValue("/RZnSiTiSi09_Up",    m_ptxtRZnSiTiSi09_Up->text());
    m_spSettings->setValue("/RZpSiTiSi09_Up",    m_ptxtRZpSiTiSi09_Up->text());
    m_spSettings->setValue("/RZSiTiSi09_Up",     m_ptxtRZSiTiSi09_Up->text());
    m_spSettings->endGroup();

    m_spSettings->beginGroup("/RZ05_SIL");
    m_spSettings->setValue("/RZnTiSi05_Dn",      m_ptxtRZnTiSi05_Dn->text());
    m_spSettings->setValue("/RZpTiSi05_Dn",      m_ptxtRZpTiSi05_Dn->text());
    m_spSettings->setValue("/RZnSiTiSi05_Dn",    m_ptxtRZnSiTiSi05_Dn->text());
    m_spSettings->setValue("/RZpSiTiSi05_Dn",    m_ptxtRZpSiTiSi05_Dn->text());
    m_spSettings->setValue("/RZSiTiSi05_Dn",     m_ptxtRZSiTiSi05_Dn->text());

    m_spSettings->setValue("/RZnTiSi05_Up",      m_ptxtRZnTiSi05_Up->text());
    m_spSettings->setValue("/RZpTiSi05_Up",      m_ptxtRZpTiSi05_Up->text());
    m_spSettings->setValue("/RZnSiTiSi05_Up",    m_ptxtRZnSiTiSi05_Up->text());
    m_spSettings->setValue("/RZpSiTiSi05_Up",    m_ptxtRZpSiTiSi05_Up->text());
    m_spSettings->setValue("/RZSiTiSi05_Up",     m_ptxtRZSiTiSi05_Up->text());
    m_spSettings->endGroup();

    m_spSettings->beginGroup("/RZ035_SIL");
    m_spSettings->setValue("/RZnTiSi035_Dn",     m_ptxtRZnTiSi035_Dn->text());
    m_spSettings->setValue("/RZpTiSi035_Dn",     m_ptxtRZpTiSi035_Dn->text());
    m_spSettings->setValue("/RZnSiTiSi035_Dn",   m_ptxtRZnSiTiSi035_Dn->text());
    m_spSettings->setValue("/RZpSiTiSi035_Dn",   m_ptxtRZpSiTiSi035_Dn->text());
    m_spSettings->setValue("/RZSiTiSi035_Dn",    m_ptxtRZSiTiSi035_Dn->text());

    m_spSettings->setValue("/RZnTiSi035_Up",     m_ptxtRZnTiSi035_Up->text());
    m_spSettings->setValue("/RZpTiSi035_Up",     m_ptxtRZpTiSi035_Up->text());
    m_spSettings->setValue("/RZnSiTiSi035_Up",   m_ptxtRZnSiTiSi035_Up->text());
    m_spSettings->setValue("/RZpSiTiSi035_Up",   m_ptxtRZpSiTiSi035_Up->text());
    m_spSettings->setValue("/RZSiTiSi035_Up",    m_ptxtRZSiTiSi035_Up->text());
    m_spSettings->endGroup();

    m_spSettings->beginGroup("/RZ06_SIL");
    m_spSettings->setValue("/RZnTiSi06_Dn",      m_ptxtRZnTiSi06_Dn->text());
    m_spSettings->setValue("/RZpTiSi06_Dn",      m_ptxtRZpTiSi06_Dn->text());
    m_spSettings->setValue("/RZnSiTiSi06_Dn",    m_ptxtRZnSiTiSi06_Dn->text());
    m_spSettings->setValue("/RZpSiTiSi06_Dn",    m_ptxtRZpSiTiSi06_Dn->text());
    m_spSettings->setValue("/RZSiTiSi06_Dn",     m_ptxtRZSiTiSi06_Dn->text());

    m_spSettings->setValue("/RZnTiSi06_Up",      m_ptxtRZnTiSi06_Up->text());
    m_spSettings->setValue("/RZpTiSi06_Up",      m_ptxtRZpTiSi06_Up->text());
    m_spSettings->setValue("/RZnSiTiSi06_Up",    m_ptxtRZnSiTiSi06_Up->text());
    m_spSettings->setValue("/RZpSiTiSi06_Up",    m_ptxtRZpSiTiSi06_Up->text());
    m_spSettings->setValue("/RZSiTiSi06_Up",     m_ptxtRZSiTiSi06_Up->text());
    m_spSettings->endGroup();
    //-----------------------------------------------------------------------------
    //межметальные Кельвины
    m_spSettings->beginGroup("/KLV_MeMe");
    m_spSettings->setValue("/KLV_M1M2_Dn",       m_ptxtKLV_M1M2_Dn->text());
    m_spSettings->setValue("/KLV_M2M3_Dn",       m_ptxtKLV_M2M3_Dn->text());
    m_spSettings->setValue("/KLV_M3M4_Dn",       m_ptxtKLV_M3M4_Dn->text());
    m_spSettings->setValue("/KLV_M1M4_Dn",       m_ptxtKLV_M1M4_Dn->text());

    m_spSettings->setValue("/KLV_M1M2_Up",       m_ptxtKLV_M1M2_Up->text());
    m_spSettings->setValue("/KLV_M2M3_Up",       m_ptxtKLV_M2M3_Up->text());
    m_spSettings->setValue("/KLV_M3M4_Up",       m_ptxtKLV_M3M4_Up->text());
    m_spSettings->setValue("/KLV_M1M4_Up",       m_ptxtKLV_M1M4_Up->text());
    m_spSettings->endGroup();

    //межметальные цепочки
    m_spSettings->beginGroup("/Z_MeMe");
    m_spSettings->setValue("/Z_M1M2_Dn",       m_ptxtZ_M1M2_Dn->text());
    m_spSettings->setValue("/Z_M2M3_Dn",       m_ptxtZ_M2M3_Dn->text());
    m_spSettings->setValue("/Z_M3M4_Dn",       m_ptxtZ_M3M4_Dn->text());
    m_spSettings->setValue("/Z_M1M4_Dn",       m_ptxtZ_M1M4_Dn->text());

    m_spSettings->setValue("/Z_M1M2_Up",       m_ptxtZ_M1M2_Up->text());
    m_spSettings->setValue("/Z_M2M3_Up",       m_ptxtZ_M2M3_Up->text());
    m_spSettings->setValue("/Z_M3M4_Up",       m_ptxtZ_M3M4_Up->text());
    m_spSettings->setValue("/Z_M1M4_Up",       m_ptxtZ_M1M4_Up->text());
    m_spSettings->endGroup();

    //меандры
    m_spSettings->beginGroup("/Mean");
    m_spSettings->setValue("/Mean1_05_Dn",     m_ptxtMean1_05_Dn->text());
    m_spSettings->setValue("/Mean1_09_Dn",     m_ptxtMean1_09_Dn->text());
    m_spSettings->setValue("/Mean2_06_Dn",     m_ptxtMean2_06_Dn->text());
    m_spSettings->setValue("/Mean2_09_Dn",     m_ptxtMean2_09_Dn->text());
    m_spSettings->setValue("/Mean3_06_Dn",     m_ptxtMean3_06_Dn->text());
    m_spSettings->setValue("/Mean3_09_Dn",     m_ptxtMean3_09_Dn->text());
    m_spSettings->setValue("/Mean4_06_Dn",     m_ptxtMean4_06_Dn->text());
    m_spSettings->setValue("/Mean4_09_Dn",     m_ptxtMean4_09_Dn->text());

    m_spSettings->setValue("/Mean1_05_Up",     m_ptxtMean1_05_Up->text());
    m_spSettings->setValue("/Mean1_09_Up",     m_ptxtMean1_09_Up->text());
    m_spSettings->setValue("/Mean2_06_Up",     m_ptxtMean2_06_Up->text());
    m_spSettings->setValue("/Mean2_09_Up",     m_ptxtMean2_09_Up->text());
    m_spSettings->setValue("/Mean3_06_Up",     m_ptxtMean3_06_Up->text());
    m_spSettings->setValue("/Mean3_09_Up",     m_ptxtMean3_09_Up->text());
    m_spSettings->setValue("/Mean4_06_Up",     m_ptxtMean4_06_Up->text());
    m_spSettings->setValue("/Mean4_09_Up",     m_ptxtMean4_09_Up->text());
    m_spSettings->endGroup();
    //-----------------------------------------------------------------------------
    //VDP
    m_spSettings->beginGroup("/VDP");
    m_spSettings->setValue("/VDPnWell_Dn",       m_ptxtVDPnWell_Dn->text());
    m_spSettings->setValue("/VDPpWell_Dn",       m_ptxtVDPpWell_Dn->text());
    m_spSettings->setValue("/VDPn_Dn",           m_ptxtVDPn_Dn->text());
    m_spSettings->setValue("/VDPp_Dn",           m_ptxtVDPp_Dn->text());
    m_spSettings->setValue("/VDPnSi_Dn",         m_ptxtVDPnSi_Dn->text());
    m_spSettings->setValue("/VDPpSi_Dn",         m_ptxtVDPpSi_Dn->text());

    m_spSettings->setValue("/VDPnWell_Up",       m_ptxtVDPnWell_Up->text());
    m_spSettings->setValue("/VDPpWell_Up",       m_ptxtVDPpWell_Up->text());
    m_spSettings->setValue("/VDPn_Up",           m_ptxtVDPn_Up->text());
    m_spSettings->setValue("/VDPp_Up",           m_ptxtVDPp_Up->text());
    m_spSettings->setValue("/VDPnSi_Up",         m_ptxtVDPnSi_Up->text());
    m_spSettings->setValue("/VDPpSi_Up",         m_ptxtVDPpSi_Up->text());
    m_spSettings->endGroup();
//-----------------------------------------------------------------------------
    //An
    m_spSettings->beginGroup("/TrAn");
    m_spSettings->setValue("/An_Vt_Dn",          m_ptxtAn_Vt_Dn->text());
    m_spSettings->setValue("/An_VtRevers_Dn",    m_ptxtAn_VtRevers_Dn->text());
    m_spSettings->setValue("/An_Be_Dn",          m_ptxtAn_Be_Dn->text());
    m_spSettings->setValue("/An_Vbr_Dn",         m_ptxtAn_Vbr_Dn->text());
    m_spSettings->setValue("/An_Gleak_Dn",       m_ptxtAn_Gleak_Dn->text());
    m_spSettings->setValue("/An_DSleak_Dn",      m_ptxtAn_DSleak_Dn->text());
    m_spSettings->setValue("/An_DSw_leak_Dn",    m_ptxtAn_DSw_leak_Dn->text());
    m_spSettings->setValue("/An_DScurrent_Dn",   m_ptxtAn_DScurrent_Dn->text());
    m_spSettings->setValue("/An_DSw_driver_Dn",  m_ptxtAn_DSw_driver_Dn->text());

    m_spSettings->setValue("/An_Vt_Up",          m_ptxtAn_Vt_Up->text());
    m_spSettings->setValue("/An_VtRevers_Up",    m_ptxtAn_VtRevers_Up->text());
    m_spSettings->setValue("/An_Be_Up",          m_ptxtAn_Be_Up->text());
    m_spSettings->setValue("/An_Vbr_Up",         m_ptxtAn_Vbr_Up->text());
    m_spSettings->setValue("/An_Gleak_Up",       m_ptxtAn_Gleak_Up->text());
    m_spSettings->setValue("/An_DSleak_Up",      m_ptxtAn_DSleak_Up->text());
    m_spSettings->setValue("/An_DSw_leak_Up",    m_ptxtAn_DSw_leak_Up->text());
    m_spSettings->setValue("/An_DScurrent_Up",   m_ptxtAn_DScurrent_Up->text());
    m_spSettings->setValue("/An_DSw_driver_Up",  m_ptxtAn_DSw_driver_Up->text());
    m_spSettings->endGroup();
//-----------------------------------------------------------------------------
    //Ap
    m_spSettings->beginGroup("/TrAp");
    m_spSettings->setValue("/Ap_Vt_Dn",          m_ptxtAp_Vt_Dn->text());
    m_spSettings->setValue("/Ap_VtRevers_Dn",    m_ptxtAp_VtRevers_Dn->text());
    m_spSettings->setValue("/Ap_Be_Dn",          m_ptxtAp_Be_Dn->text());
    m_spSettings->setValue("/Ap_Vbr_Dn",         m_ptxtAp_Vbr_Dn->text());
    m_spSettings->setValue("/Ap_Gleak_Dn",       m_ptxtAp_Gleak_Dn->text());
    m_spSettings->setValue("/Ap_DSleak_Dn",      m_ptxtAp_DSleak_Dn->text());
    m_spSettings->setValue("/Ap_DSw_leak_Dn",    m_ptxtAp_DSw_leak_Dn->text());
    m_spSettings->setValue("/Ap_DScurrent_Dn",   m_ptxtAp_DScurrent_Dn->text());
    m_spSettings->setValue("/Ap_DSw_driver_Dn",  m_ptxtAp_DSw_driver_Dn->text());

    m_spSettings->setValue("/Ap_Vt_Up",          m_ptxtAp_Vt_Up->text());
    m_spSettings->setValue("/Ap_VtRevers_Up",    m_ptxtAp_VtRevers_Up->text());
    m_spSettings->setValue("/Ap_Be_Up",          m_ptxtAp_Be_Up->text());
    m_spSettings->setValue("/Ap_Vbr_Up",         m_ptxtAp_Vbr_Up->text());
    m_spSettings->setValue("/Ap_Gleak_Up",       m_ptxtAp_Gleak_Up->text());
    m_spSettings->setValue("/Ap_DSleak_Up",      m_ptxtAp_DSleak_Up->text());
    m_spSettings->setValue("/Ap_DSw_leak_Up",    m_ptxtAp_DSw_leak_Up->text());
    m_spSettings->setValue("/Ap_DScurrent_Up",   m_ptxtAp_DScurrent_Up->text());
    m_spSettings->setValue("/Ap_DSw_driver_Up",  m_ptxtAp_DSw_driver_Up->text());
    m_spSettings->endGroup();
//-----------------------------------------------------------------------------
    //Rn
    m_spSettings->beginGroup("/TrRn");
    m_spSettings->setValue("/Rn_Vt_Dn",          m_ptxtRn_Vt_Dn->text());
    m_spSettings->setValue("/Rn_VtRevers_Dn",    m_ptxtRn_VtRevers_Dn->text());
    m_spSettings->setValue("/Rn_Be_Dn",          m_ptxtRn_Be_Dn->text());
    m_spSettings->setValue("/Rn_Vbr_Dn",         m_ptxtRn_Vbr_Dn->text());
    m_spSettings->setValue("/Rn_Gleak_Dn",       m_ptxtRn_Gleak_Dn->text());
    m_spSettings->setValue("/Rn_DSleak_Dn",      m_ptxtRn_DSleak_Dn->text());
    m_spSettings->setValue("/Rn_DSw_leak_Dn",    m_ptxtRn_DSw_leak_Dn->text());
    m_spSettings->setValue("/Rn_DScurrent_Dn",   m_ptxtRn_DScurrent_Dn->text());
    m_spSettings->setValue("/Rn_DSw_driver_Dn",  m_ptxtRn_DSw_driver_Dn->text());

    m_spSettings->setValue("/Rn_Vt_Up",          m_ptxtRn_Vt_Up->text());
    m_spSettings->setValue("/Rn_VtRevers_Up",    m_ptxtRn_VtRevers_Up->text());
    m_spSettings->setValue("/Rn_Be_Up",          m_ptxtRn_Be_Up->text());
    m_spSettings->setValue("/Rn_Vbr_Up",         m_ptxtRn_Vbr_Up->text());
    m_spSettings->setValue("/Rn_Gleak_Up",       m_ptxtRn_Gleak_Up->text());
    m_spSettings->setValue("/Rn_DSleak_Up",      m_ptxtRn_DSleak_Up->text());
    m_spSettings->setValue("/Rn_DSw_leak_Up",    m_ptxtRn_DSw_leak_Up->text());
    m_spSettings->setValue("/Rn_DScurrent_Up",   m_ptxtRn_DScurrent_Up->text());
    m_spSettings->setValue("/Rn_DSw_driver_Up",  m_ptxtRn_DSw_driver_Up->text());
    m_spSettings->endGroup();
//-----------------------------------------------------------------------------
    //Rp
    m_spSettings->beginGroup("/TrRp");
    m_spSettings->setValue("/Rp_Vt_Dn",          m_ptxtRp_Vt_Dn->text());
    m_spSettings->setValue("/Rp_VtRevers_Dn",    m_ptxtRp_VtRevers_Dn->text());
    m_spSettings->setValue("/Rp_Be_Dn",          m_ptxtRp_Be_Dn->text());
    m_spSettings->setValue("/Rp_Vbr_Dn",         m_ptxtRp_Vbr_Dn->text());
    m_spSettings->setValue("/Rp_Gleak_Dn",       m_ptxtRp_Gleak_Dn->text());
    m_spSettings->setValue("/Rp_DSleak_Dn",      m_ptxtRp_DSleak_Dn->text());
    m_spSettings->setValue("/Rp_DSw_leak_Dn",    m_ptxtRp_DSw_leak_Dn->text());
    m_spSettings->setValue("/Rp_DScurrent_Dn",   m_ptxtRp_DScurrent_Dn->text());
    m_spSettings->setValue("/Rp_DSw_driver_Dn",  m_ptxtRp_DSw_driver_Dn->text());

    m_spSettings->setValue("/Rp_Vt_Up",          m_ptxtRp_Vt_Up->text());
    m_spSettings->setValue("/Rp_VtRevers_Up",    m_ptxtRp_VtRevers_Up->text());
    m_spSettings->setValue("/Rp_Be_Up",          m_ptxtRp_Be_Up->text());
    m_spSettings->setValue("/Rp_Vbr_Up",         m_ptxtRp_Vbr_Up->text());
    m_spSettings->setValue("/Rp_Gleak_Up",       m_ptxtRp_Gleak_Up->text());
    m_spSettings->setValue("/Rp_DSleak_Up",      m_ptxtRp_DSleak_Up->text());
    m_spSettings->setValue("/Rp_DSw_leak_Up",    m_ptxtRp_DSw_leak_Up->text());
    m_spSettings->setValue("/Rp_DScurrent_Up",   m_ptxtRp_DScurrent_Up->text());
    m_spSettings->setValue("/Rp_DSw_driver_Up",  m_ptxtRp_DSw_driver_Up->text());
    m_spSettings->endGroup();
//-----------------------------------------------------------------------------
    //Hn
    m_spSettings->beginGroup("/TrHn");
    m_spSettings->setValue("/Hn_Vt_Dn",          m_ptxtHn_Vt_Dn->text());
    m_spSettings->setValue("/Hn_VtRevers_Dn",    m_ptxtHn_VtRevers_Dn->text());
    m_spSettings->setValue("/Hn_Be_Dn",          m_ptxtHn_Be_Dn->text());
    m_spSettings->setValue("/Hn_Vbr_Dn",         m_ptxtHn_Vbr_Dn->text());
    m_spSettings->setValue("/Hn_Gleak_Dn",       m_ptxtHn_Gleak_Dn->text());
    m_spSettings->setValue("/Hn_DSleak_Dn",      m_ptxtHn_DSleak_Dn->text());
    m_spSettings->setValue("/Hn_DSw_leak_Dn",    m_ptxtHn_DSw_leak_Dn->text());
    m_spSettings->setValue("/Hn_DScurrent_Dn",   m_ptxtHn_DScurrent_Dn->text());
    m_spSettings->setValue("/Hn_DSw_driver_Dn",  m_ptxtHn_DSw_driver_Dn->text());

    m_spSettings->setValue("/Hn_Vt_Up",          m_ptxtHn_Vt_Up->text());
    m_spSettings->setValue("/Hn_VtRevers_Up",    m_ptxtHn_VtRevers_Up->text());
    m_spSettings->setValue("/Hn_Be_Up",          m_ptxtHn_Be_Up->text());
    m_spSettings->setValue("/Hn_Vbr_Up",         m_ptxtHn_Vbr_Up->text());
    m_spSettings->setValue("/Hn_Gleak_Up",       m_ptxtHn_Gleak_Up->text());
    m_spSettings->setValue("/Hn_DSleak_Up",      m_ptxtHn_DSleak_Up->text());
    m_spSettings->setValue("/Hn_DSw_leak_Up",    m_ptxtHn_DSw_leak_Up->text());
    m_spSettings->setValue("/Hn_DScurrent_Up",   m_ptxtHn_DScurrent_Up->text());
    m_spSettings->setValue("/Hn_DSw_driver_Up",  m_ptxtHn_DSw_driver_Up->text());
    m_spSettings->endGroup();
//-----------------------------------------------------------------------------
    //Hp
    m_spSettings->beginGroup("/TrHp");
    m_spSettings->setValue("/Hp_Vt_Dn",          m_ptxtHp_Vt_Dn->text());
    m_spSettings->setValue("/Hp_VtRevers_Dn",    m_ptxtHp_VtRevers_Dn->text());
    m_spSettings->setValue("/Hp_Be_Dn",          m_ptxtHp_Be_Dn->text());
    m_spSettings->setValue("/Hp_Vbr_Dn",         m_ptxtHp_Vbr_Dn->text());
    m_spSettings->setValue("/Hp_Gleak_Dn",       m_ptxtHp_Gleak_Dn->text());
    m_spSettings->setValue("/Hp_DSleak_Dn",      m_ptxtHp_DSleak_Dn->text());
    m_spSettings->setValue("/Hp_DSw_leak_Dn",    m_ptxtHp_DSw_leak_Dn->text());
    m_spSettings->setValue("/Hp_DScurrent_Dn",   m_ptxtHp_DScurrent_Dn->text());
    m_spSettings->setValue("/Hp_DSw_driver_Dn",  m_ptxtHp_DSw_driver_Dn->text());

    m_spSettings->setValue("/Hp_Vt_Up",          m_ptxtHp_Vt_Up->text());
    m_spSettings->setValue("/Hp_VtRevers_Up",    m_ptxtHp_VtRevers_Up->text());
    m_spSettings->setValue("/Hp_Be_Up",          m_ptxtHp_Be_Up->text());
    m_spSettings->setValue("/Hp_Vbr_Up",         m_ptxtHp_Vbr_Up->text());
    m_spSettings->setValue("/Hp_Gleak_Up",       m_ptxtHp_Gleak_Up->text());
    m_spSettings->setValue("/Hp_DSleak_Up",      m_ptxtHp_DSleak_Up->text());
    m_spSettings->setValue("/Hp_DSw_leak_Up",    m_ptxtHp_DSw_leak_Up->text());
    m_spSettings->setValue("/Hp_DScurrent_Up",   m_ptxtHp_DScurrent_Up->text());
    m_spSettings->setValue("/Hp_DSw_driver_Up",  m_ptxtHp_DSw_driver_Up->text());
    m_spSettings->endGroup();
//-----------------------------------------------------------------------------
    m_spSettings->endGroup();//Settings
}
//-------------------------------------------------------------------------------------------------
//слоты:
//-------------------------------------------------------------------------------------------------
//установка значений в поля SIL
//на поликремнии резисторов 0,5 мкм нет
//на монокремнии резисторов 0,35 мкм нет
void LocalSettingsWin::slotSetRSIL_Dn(const QString& strCriteriumDn)
{    
    m_ptxtSIL_R_Dn->setText(strCriteriumDn);
}
void LocalSettingsWin::slotSetRSIL_Up(const QString &strCriteriumUp)
{
    m_ptxtSIL_R_Up->setText(strCriteriumUp);
}

void LocalSettingsWin::slotSetKLVsSIL_Dn(const QString &strCriteriumDn)
{
    //силицидные Кельвины
    m_ptxtSIL_KLVnM1_Dn->setText(strCriteriumDn);
    m_ptxtSIL_KLVpM1_Dn->setText(strCriteriumDn);
    m_ptxtSIL_KLVnSiM1_Dn->setText(strCriteriumDn);
    m_ptxtSIL_KLVpSiM1_Dn->setText(strCriteriumDn);
    m_ptxtSIL_KLVSiM1_Dn->setText(strCriteriumDn);
}
void LocalSettingsWin::slotSetKLVsSIL_Up(const QString &strCriteriumUp)
{
    //силицидные Кельвины
    m_ptxtSIL_KLVnM1_Up->setText(strCriteriumUp);
    m_ptxtSIL_KLVpM1_Up->setText(strCriteriumUp);
    m_ptxtSIL_KLVnSiM1_Up->setText(strCriteriumUp);
    m_ptxtSIL_KLVpSiM1_Up->setText(strCriteriumUp);
    m_ptxtSIL_KLVSiM1_Up->setText(strCriteriumUp);
}

void LocalSettingsWin::slotSetZsSIL_Dn(const QString &strCriteriumDn)
{
    //силицидные цепочки
    m_ptxtSIL_ZnM1_Dn->setText(strCriteriumDn);
    m_ptxtSIL_ZpM1_Dn->setText(strCriteriumDn);
    m_ptxtSIL_ZnSiM1_Dn->setText(strCriteriumDn);
    m_ptxtSIL_ZpSiM1_Dn->setText(strCriteriumDn);
    m_ptxtSIL_ZSiM1_Dn->setText(strCriteriumDn);
}
void LocalSettingsWin::slotSetZsSIL_Up(const QString &strCriteriumUp)
{
    //силицидные цепочки
    m_ptxtSIL_ZnM1_Up->setText(strCriteriumUp);
    m_ptxtSIL_ZpM1_Up->setText(strCriteriumUp);
    m_ptxtSIL_ZnSiM1_Up->setText(strCriteriumUp);
    m_ptxtSIL_ZpSiM1_Up->setText(strCriteriumUp);
    m_ptxtSIL_ZSiM1_Up->setText(strCriteriumUp);
}

void LocalSettingsWin::slotSetRz09SIL_Dn(const QString &strCriteriumDn)
{
    //силицидные резисторы 09
    m_ptxtRZnTiSi09_Dn->setText(strCriteriumDn);
    m_ptxtRZpTiSi09_Dn->setText(strCriteriumDn);
    m_ptxtRZnSiTiSi09_Dn->setText(strCriteriumDn);
    m_ptxtRZpSiTiSi09_Dn->setText(strCriteriumDn);
    m_ptxtRZSiTiSi09_Dn->setText(strCriteriumDn);
}
void LocalSettingsWin::slotSetRz09SIL_Up(const QString &strCriteriumUp)
{
    //силицидные резисторы 09
    m_ptxtRZnTiSi09_Up->setText(strCriteriumUp);
    m_ptxtRZpTiSi09_Up->setText(strCriteriumUp);
    m_ptxtRZnSiTiSi09_Up->setText(strCriteriumUp);
    m_ptxtRZpSiTiSi09_Up->setText(strCriteriumUp);
    m_ptxtRZSiTiSi09_Up->setText(strCriteriumUp);
}

void LocalSettingsWin::slotSetRz05SIL_Dn(const QString &strCriteriumDn)
{
    //силицидные резисторы 05
    m_ptxtRZnTiSi05_Dn->setText(strCriteriumDn);
    m_ptxtRZpTiSi05_Dn->setText(strCriteriumDn);
    m_ptxtRZnSiTiSi05_Dn->setText(strCriteriumDn);
    m_ptxtRZpSiTiSi05_Dn->setText(strCriteriumDn);
    m_ptxtRZSiTiSi05_Dn->setText(strCriteriumDn);
}
void LocalSettingsWin::slotSetRz05SIL_Up(const QString &strCriteriumUp)
{
    //силицидные резисторы 05
    m_ptxtRZnTiSi05_Up->setText(strCriteriumUp);
    m_ptxtRZpTiSi05_Up->setText(strCriteriumUp);
    m_ptxtRZnSiTiSi05_Up->setText(strCriteriumUp);
    m_ptxtRZpSiTiSi05_Up->setText(strCriteriumUp);
    m_ptxtRZSiTiSi05_Up->setText(strCriteriumUp);
}

void LocalSettingsWin::slotSetRz035SIL_Dn(const QString &strCriteriumDn)
{
    //силицидные резисторы 035
    m_ptxtRZnTiSi035_Dn->setText(strCriteriumDn);
    m_ptxtRZpTiSi035_Dn->setText(strCriteriumDn);
    m_ptxtRZnSiTiSi035_Dn->setText(strCriteriumDn);
    m_ptxtRZpSiTiSi035_Dn->setText(strCriteriumDn);
    m_ptxtRZSiTiSi035_Dn->setText(strCriteriumDn);
}
void LocalSettingsWin::slotSetRz035SIL_Up(const QString &strCriteriumUp)
{
    //силицидные резисторы 035
    m_ptxtRZnTiSi035_Up->setText(strCriteriumUp);
    m_ptxtRZpTiSi035_Up->setText(strCriteriumUp);
    m_ptxtRZnSiTiSi035_Up->setText(strCriteriumUp);
    m_ptxtRZpSiTiSi035_Up->setText(strCriteriumUp);
    m_ptxtRZSiTiSi035_Up->setText(strCriteriumUp);
}

void LocalSettingsWin::slotSetRz06SIL_Dn(const QString &strCriteriumDn)
{
    //силицидные резисторы 06
    m_ptxtRZnTiSi06_Dn->setText(strCriteriumDn);
    m_ptxtRZpTiSi06_Dn->setText(strCriteriumDn);
    m_ptxtRZnSiTiSi06_Dn->setText(strCriteriumDn);
    m_ptxtRZpSiTiSi06_Dn->setText(strCriteriumDn);
    m_ptxtRZSiTiSi06_Dn->setText(strCriteriumDn);
}
void LocalSettingsWin::slotSetRz06SIL_Up(const QString &strCriteriumUp)
{
    //силицидные резисторы 06
    m_ptxtRZnTiSi06_Up->setText(strCriteriumUp);
    m_ptxtRZpTiSi06_Up->setText(strCriteriumUp);
    m_ptxtRZnSiTiSi06_Up->setText(strCriteriumUp);
    m_ptxtRZpSiTiSi06_Up->setText(strCriteriumUp);
    m_ptxtRZSiTiSi06_Up->setText(strCriteriumUp);
}
//----------------------------------------------------------------------------------
//установка значений в поля KLV_MeMe
void LocalSettingsWin::slotSetKLV_M1M2_Dn(const QString& strCriteriumDn)
{
    m_ptxtKLV_M1M2_Dn->setText(strCriteriumDn);
}
void LocalSettingsWin::slotSetKLV_M2M3_Dn(const QString& strCriteriumDn)
{
    m_ptxtKLV_M2M3_Dn->setText(strCriteriumDn);
}
void LocalSettingsWin::slotSetKLV_M3M4_Dn(const QString& strCriteriumDn)
{
    m_ptxtKLV_M3M4_Dn->setText(strCriteriumDn);
}
void LocalSettingsWin::slotSetKLV_M1M4_Dn(const QString& strCriteriumDn)
{
    m_ptxtKLV_M1M4_Dn->setText(strCriteriumDn);
}

void LocalSettingsWin::slotSetKLV_M1M2_Up(const QString& strCriteriumUp)
{
    m_ptxtKLV_M1M2_Up->setText(strCriteriumUp);
}
void LocalSettingsWin::slotSetKLV_M2M3_Up(const QString& strCriteriumUp)
{
    m_ptxtKLV_M2M3_Up->setText(strCriteriumUp);
}
void LocalSettingsWin::slotSetKLV_M3M4_Up(const QString& strCriteriumUp)
{
    m_ptxtKLV_M3M4_Up->setText(strCriteriumUp);
}
void LocalSettingsWin::slotSetKLV_M1M4_Up(const QString& strCriteriumUp)
{
    m_ptxtKLV_M1M4_Up->setText(strCriteriumUp);
}
//----------------------------------------------------------------------------------
//установка значений в поля Z_MeMe
void LocalSettingsWin::slotSetZ_M1M2_Dn(const QString& strCriteriumDn)
{
    m_ptxtZ_M1M2_Dn->setText(strCriteriumDn);
}
void LocalSettingsWin::slotSetZ_M2M3_Dn(const QString& strCriteriumDn)
{
    m_ptxtZ_M2M3_Dn->setText(strCriteriumDn);
}
void LocalSettingsWin::slotSetZ_M3M4_Dn(const QString& strCriteriumDn)
{
    m_ptxtZ_M3M4_Dn->setText(strCriteriumDn);
}
void LocalSettingsWin::slotSetZ_M1M4_Dn(const QString& strCriteriumDn)
{
    m_ptxtZ_M1M4_Dn->setText(strCriteriumDn);
}

void LocalSettingsWin::slotSetZ_M1M2_Up(const QString& strCriteriumUp)
{
    m_ptxtZ_M1M2_Up->setText(strCriteriumUp);
}
void LocalSettingsWin::slotSetZ_M2M3_Up(const QString& strCriteriumUp)
{
    m_ptxtZ_M2M3_Up->setText(strCriteriumUp);
}
void LocalSettingsWin::slotSetZ_M3M4_Up(const QString& strCriteriumUp)
{
    m_ptxtZ_M3M4_Up->setText(strCriteriumUp);
}
void LocalSettingsWin::slotSetZ_M1M4_Up(const QString& strCriteriumUp)
{
    m_ptxtZ_M1M4_Up->setText(strCriteriumUp);
}
//----------------------------------------------------------------------------------
//установка значений в поля Mean
void LocalSettingsWin::slotSetMean1_05_Dn(const QString& strCriteriumDn)
{
    m_ptxtMean1_05_Dn->setText(strCriteriumDn);
}
void LocalSettingsWin::slotSetMean1_09_Dn(const QString& strCriteriumDn)
{
    m_ptxtMean1_09_Dn->setText(strCriteriumDn);
}
void LocalSettingsWin::slotSetMean2_06_Dn(const QString& strCriteriumDn)
{
    m_ptxtMean2_06_Dn->setText(strCriteriumDn);
}
void LocalSettingsWin::slotSetMean2_09_Dn(const QString& strCriteriumDn)
{
    m_ptxtMean2_09_Dn->setText(strCriteriumDn);
}
void LocalSettingsWin::slotSetMean3_06_Dn(const QString& strCriteriumDn)
{
    m_ptxtMean3_06_Dn->setText(strCriteriumDn);
}
void LocalSettingsWin::slotSetMean3_09_Dn(const QString& strCriteriumDn)
{
    m_ptxtMean3_09_Dn->setText(strCriteriumDn);
}
void LocalSettingsWin::slotSetMean4_06_Dn(const QString& strCriteriumDn)
{
    m_ptxtMean4_06_Dn->setText(strCriteriumDn);
}
void LocalSettingsWin::slotSetMean4_09_Dn(const QString& strCriteriumDn)
{
    m_ptxtMean4_09_Dn->setText(strCriteriumDn);
}

void LocalSettingsWin::slotSetMean1_05_Up(const QString& strCriteriumUp)
{
    m_ptxtMean1_05_Up->setText(strCriteriumUp);
}
void LocalSettingsWin::slotSetMean1_09_Up(const QString& strCriteriumUp)
{
    m_ptxtMean1_09_Up->setText(strCriteriumUp);
}
void LocalSettingsWin::slotSetMean2_06_Up(const QString& strCriteriumUp)
{
    m_ptxtMean2_06_Up->setText(strCriteriumUp);
}
void LocalSettingsWin::slotSetMean2_09_Up(const QString& strCriteriumUp)
{
    m_ptxtMean2_09_Up->setText(strCriteriumUp);
}
void LocalSettingsWin::slotSetMean3_06_Up(const QString& strCriteriumUp)
{
    m_ptxtMean3_06_Up->setText(strCriteriumUp);
}
void LocalSettingsWin::slotSetMean3_09_Up(const QString& strCriteriumUp)
{
    m_ptxtMean3_09_Up->setText(strCriteriumUp);
}
void LocalSettingsWin::slotSetMean4_06_Up(const QString& strCriteriumUp)
{
    m_ptxtMean4_06_Up->setText(strCriteriumUp);
}
void LocalSettingsWin::slotSetMean4_09_Up(const QString& strCriteriumUp)
{
    m_ptxtMean4_09_Up->setText(strCriteriumUp);
}
//----------------------------------------------------------------------------------
//установка значений в поля VDP
void LocalSettingsWin::slotSetVDPnWell_Dn(const QString &strCriteriumDn)
{
    m_ptxtVDPnWell_Dn->setText(strCriteriumDn);
}
void LocalSettingsWin::slotSetVDPnWell_Up(const QString &strCriteriumUp)
{
    m_ptxtVDPnWell_Up->setText(strCriteriumUp);
}
void LocalSettingsWin::slotSetVDPpWell_Dn(const QString &strCriteriumDn)
{
    m_ptxtVDPpWell_Dn->setText(strCriteriumDn);
}
void LocalSettingsWin::slotSetVDPpWell_Up(const QString &strCriteriumUp)
{
    m_ptxtVDPpWell_Up->setText(strCriteriumUp);
}

void LocalSettingsWin::slotSetVDPn_Dn(const QString &strCriteriumDn)
{
    m_ptxtVDPn_Dn->setText(strCriteriumDn);
}
void LocalSettingsWin::slotSetVDPn_Up(const QString &strCriteriumUp)
{
    m_ptxtVDPn_Up->setText(strCriteriumUp);
}
void LocalSettingsWin::slotSetVDPp_Dn(const QString &strCriteriumDn)
{
    m_ptxtVDPp_Dn->setText(strCriteriumDn);
}
void LocalSettingsWin::slotSetVDPp_Up(const QString &strCriteriumUp)
{
    m_ptxtVDPp_Up->setText(strCriteriumUp);
}

void LocalSettingsWin::slotSetVDPnSi_Dn(const QString &strCriteriumDn)
{
    m_ptxtVDPnSi_Dn->setText(strCriteriumDn);
}
void LocalSettingsWin::slotSetVDPnSi_Up(const QString &strCriteriumUp)
{
    m_ptxtVDPnSi_Up->setText(strCriteriumUp);
}
void LocalSettingsWin::slotSetVDPpSi_Dn(const QString &strCriteriumDn)
{
    m_ptxtVDPpSi_Dn->setText(strCriteriumDn);
}
void LocalSettingsWin::slotSetVDPpSi_Up(const QString &strCriteriumUp)
{
    m_ptxtVDPpSi_Up->setText(strCriteriumUp);
}
//----------------------------------------------------------------------------------
//установка значений в поля Tr
//An
void LocalSettingsWin::slotSetAn_Vt_Dn(const QString &strCriteriumDn)
{
    m_ptxtAn_Vt_Dn->setText(strCriteriumDn);
}
void LocalSettingsWin::slotSetAn_VtRevers_Dn(const QString &strCriteriumDn)
{
    m_ptxtAn_VtRevers_Dn->setText(strCriteriumDn);
}
void LocalSettingsWin::slotSetAn_Be_Dn(const QString &strCriteriumDn)
{
    m_ptxtAn_Be_Dn->setText(strCriteriumDn);
}
void LocalSettingsWin::slotSetAn_Vbr_Dn(const QString &strCriteriumDn)
{
    m_ptxtAn_Vbr_Dn->setText(strCriteriumDn);
}
void LocalSettingsWin::slotSetAn_Gleak_Dn(const QString &strCriteriumDn)
{
    m_ptxtAn_Gleak_Dn->setText(strCriteriumDn);
}
void LocalSettingsWin::slotSetAn_DSleak_Dn(const QString &strCriteriumDn)
{
    m_ptxtAn_DSleak_Dn->setText(strCriteriumDn);
}
void LocalSettingsWin::slotSetAn_DSw_leak_Dn(const QString &strCriteriumDn)
{
    m_ptxtAn_DSw_leak_Dn->setText(strCriteriumDn);
}
void LocalSettingsWin::slotSetAn_DScurrent_Dn(const QString &strCriteriumDn)
{
    m_ptxtAn_DScurrent_Dn->setText(strCriteriumDn);
}
void LocalSettingsWin::slotSetAn_DSw_driver_Dn(const QString &strCriteriumDn)
{
    m_ptxtAn_DSw_driver_Dn->setText(strCriteriumDn);
}

void LocalSettingsWin::slotSetAn_Vt_Up(const QString &strCriteriumUp)
{
    m_ptxtAn_Vt_Up->setText(strCriteriumUp);
}
void LocalSettingsWin::slotSetAn_VtRevers_Up(const QString &strCriteriumUp)
{
    m_ptxtAn_VtRevers_Up->setText(strCriteriumUp);
}
void LocalSettingsWin::slotSetAn_Be_Up(const QString &strCriteriumUp)
{
    m_ptxtAn_Be_Up->setText(strCriteriumUp);
}
void LocalSettingsWin::slotSetAn_Vbr_Up(const QString &strCriteriumUp)
{
    m_ptxtAn_Vbr_Up->setText(strCriteriumUp);
}
void LocalSettingsWin::slotSetAn_Gleak_Up(const QString &strCriteriumUp)
{
    m_ptxtAn_Gleak_Up->setText(strCriteriumUp);
}
void LocalSettingsWin::slotSetAn_DSleak_Up(const QString &strCriteriumUp)
{
    m_ptxtAn_DSleak_Up->setText(strCriteriumUp);
}
void LocalSettingsWin::slotSetAn_DSw_leak_Up(const QString &strCriteriumUp)
{
    m_ptxtAn_DSw_leak_Up->setText(strCriteriumUp);
}
void LocalSettingsWin::slotSetAn_DScurrent_Up(const QString &strCriteriumUp)
{
    m_ptxtAn_DScurrent_Up->setText(strCriteriumUp);
}
void LocalSettingsWin::slotSetAn_DSw_driver_Up(const QString &strCriteriumUp)
{
    m_ptxtAn_DSw_driver_Up->setText(strCriteriumUp);
}

//Ap
void LocalSettingsWin::slotSetAp_Vt_Dn(const QString &strCriteriumDn)
{
    m_ptxtAp_Vt_Dn->setText(strCriteriumDn);
}
void LocalSettingsWin::slotSetAp_VtRevers_Dn(const QString &strCriteriumDn)
{
    m_ptxtAp_VtRevers_Dn->setText(strCriteriumDn);
}
void LocalSettingsWin::slotSetAp_Be_Dn(const QString &strCriteriumDn)
{
    m_ptxtAp_Be_Dn->setText(strCriteriumDn);
}
void LocalSettingsWin::slotSetAp_Vbr_Dn(const QString &strCriteriumDn)
{
    m_ptxtAp_Vbr_Dn->setText(strCriteriumDn);
}
void LocalSettingsWin::slotSetAp_Gleak_Dn(const QString &strCriteriumDn)
{
    m_ptxtAp_Gleak_Dn->setText(strCriteriumDn);
}
void LocalSettingsWin::slotSetAp_DSleak_Dn(const QString &strCriteriumDn)
{
    m_ptxtAp_DSleak_Dn->setText(strCriteriumDn);
}
void LocalSettingsWin::slotSetAp_DSw_leak_Dn(const QString &strCriteriumDn)
{
    m_ptxtAp_DSw_leak_Dn->setText(strCriteriumDn);
}
void LocalSettingsWin::slotSetAp_DScurrent_Dn(const QString &strCriteriumDn)
{
    m_ptxtAp_DScurrent_Dn->setText(strCriteriumDn);
}
void LocalSettingsWin::slotSetAp_DSw_driver_Dn(const QString &strCriteriumDn)
{
    m_ptxtAp_DSw_driver_Dn->setText(strCriteriumDn);
}

void LocalSettingsWin::slotSetAp_Vt_Up(const QString &strCriteriumUp)
{
    m_ptxtAp_Vt_Up->setText(strCriteriumUp);
}
void LocalSettingsWin::slotSetAp_VtRevers_Up(const QString &strCriteriumUp)
{
    m_ptxtAp_VtRevers_Up->setText(strCriteriumUp);
}
void LocalSettingsWin::slotSetAp_Be_Up(const QString &strCriteriumUp)
{
    m_ptxtAp_Be_Up->setText(strCriteriumUp);
}
void LocalSettingsWin::slotSetAp_Vbr_Up(const QString &strCriteriumUp)
{
    m_ptxtAp_Vbr_Up->setText(strCriteriumUp);
}
void LocalSettingsWin::slotSetAp_Gleak_Up(const QString &strCriteriumUp)
{
    m_ptxtAp_Gleak_Up->setText(strCriteriumUp);
}
void LocalSettingsWin::slotSetAp_DSleak_Up(const QString &strCriteriumUp)
{
    m_ptxtAp_DSleak_Up->setText(strCriteriumUp);
}
void LocalSettingsWin::slotSetAp_DSw_leak_Up(const QString &strCriteriumUp)
{
    m_ptxtAp_DSw_leak_Up->setText(strCriteriumUp);
}
void LocalSettingsWin::slotSetAp_DScurrent_Up(const QString &strCriteriumUp)
{
    m_ptxtAp_DScurrent_Up->setText(strCriteriumUp);
}
void LocalSettingsWin::slotSetAp_DSw_driver_Up(const QString &strCriteriumUp)
{
    m_ptxtAp_DSw_driver_Up->setText(strCriteriumUp);
}

//Rn
void LocalSettingsWin::slotSetRn_Vt_Dn(const QString &strCriteriumDn)
{
    m_ptxtRn_Vt_Dn->setText(strCriteriumDn);
}
void LocalSettingsWin::slotSetRn_VtRevers_Dn(const QString &strCriteriumDn)
{
    m_ptxtRn_VtRevers_Dn->setText(strCriteriumDn);
}
void LocalSettingsWin::slotSetRn_Be_Dn(const QString &strCriteriumDn)
{
    m_ptxtRn_Be_Dn->setText(strCriteriumDn);
}
void LocalSettingsWin::slotSetRn_Vbr_Dn(const QString &strCriteriumDn)
{
    m_ptxtRn_Vbr_Dn->setText(strCriteriumDn);
}
void LocalSettingsWin::slotSetRn_Gleak_Dn(const QString &strCriteriumDn)
{
    m_ptxtRn_Gleak_Dn->setText(strCriteriumDn);
}
void LocalSettingsWin::slotSetRn_DSleak_Dn(const QString &strCriteriumDn)
{
    m_ptxtRn_DSleak_Dn->setText(strCriteriumDn);
}
void LocalSettingsWin::slotSetRn_DSw_leak_Dn(const QString &strCriteriumDn)
{
    m_ptxtRn_DSw_leak_Dn->setText(strCriteriumDn);
}
void LocalSettingsWin::slotSetRn_DScurrent_Dn(const QString &strCriteriumDn)
{
    m_ptxtRn_DScurrent_Dn->setText(strCriteriumDn);
}
void LocalSettingsWin::slotSetRn_DSw_driver_Dn(const QString &strCriteriumDn)
{
    m_ptxtRn_DSw_driver_Dn->setText(strCriteriumDn);
}

void LocalSettingsWin::slotSetRn_Vt_Up(const QString &strCriteriumUp)
{
    m_ptxtRn_Vt_Up->setText(strCriteriumUp);
}
void LocalSettingsWin::slotSetRn_VtRevers_Up(const QString &strCriteriumUp)
{
    m_ptxtRn_VtRevers_Up->setText(strCriteriumUp);
}
void LocalSettingsWin::slotSetRn_Be_Up(const QString &strCriteriumUp)
{
    m_ptxtRn_Be_Up->setText(strCriteriumUp);
}
void LocalSettingsWin::slotSetRn_Vbr_Up(const QString &strCriteriumUp)
{
    m_ptxtRn_Vbr_Up->setText(strCriteriumUp);
}
void LocalSettingsWin::slotSetRn_Gleak_Up(const QString &strCriteriumUp)
{
    m_ptxtRn_Gleak_Up->setText(strCriteriumUp);
}
void LocalSettingsWin::slotSetRn_DSleak_Up(const QString &strCriteriumUp)
{
    m_ptxtRn_DSleak_Up->setText(strCriteriumUp);
}
void LocalSettingsWin::slotSetRn_DSw_leak_Up(const QString &strCriteriumUp)
{
    m_ptxtRn_DSw_leak_Up->setText(strCriteriumUp);
}
void LocalSettingsWin::slotSetRn_DScurrent_Up(const QString &strCriteriumUp)
{
    m_ptxtRn_DScurrent_Up->setText(strCriteriumUp);
}
void LocalSettingsWin::slotSetRn_DSw_driver_Up(const QString &strCriteriumUp)
{
    m_ptxtRn_DSw_driver_Up->setText(strCriteriumUp);
}

//Rp
void LocalSettingsWin::slotSetRp_Vt_Dn(const QString& strCriteriumDn)
{
    m_ptxtRp_Vt_Dn->setText(strCriteriumDn);
}
void LocalSettingsWin::slotSetRp_VtRevers_Dn(const QString &strCriteriumDn)
{
    m_ptxtRp_VtRevers_Dn->setText(strCriteriumDn);
}
void LocalSettingsWin::slotSetRp_Be_Dn(const QString &strCriteriumDn)
{
    m_ptxtRp_Be_Dn->setText(strCriteriumDn);
}
void LocalSettingsWin::slotSetRp_Vbr_Dn(const QString &strCriteriumDn)
{
    m_ptxtRp_Vbr_Dn->setText(strCriteriumDn);
}
void LocalSettingsWin::slotSetRp_Gleak_Dn(const QString &strCriteriumDn)
{
    m_ptxtRp_Gleak_Dn->setText(strCriteriumDn);
}
void LocalSettingsWin::slotSetRp_DSleak_Dn(const QString &strCriteriumDn)
{
    m_ptxtRp_DSleak_Dn->setText(strCriteriumDn);
}
void LocalSettingsWin::slotSetRp_DSw_leak_Dn(const QString &strCriteriumDn)
{
    m_ptxtRp_DSw_leak_Dn->setText(strCriteriumDn);
}
void LocalSettingsWin::slotSetRp_DScurrent_Dn(const QString &strCriteriumDn)
{
    m_ptxtRp_DScurrent_Dn->setText(strCriteriumDn);
}
void LocalSettingsWin::slotSetRp_DSw_driver_Dn(const QString &strCriteriumDn)
{
    m_ptxtRp_DSw_driver_Dn->setText(strCriteriumDn);
}

void LocalSettingsWin::slotSetRp_Vt_Up(const QString &strCriteriumUp)
{
    m_ptxtRp_Vt_Up->setText(strCriteriumUp);
}
void LocalSettingsWin::slotSetRp_VtRevers_Up(const QString &strCriteriumUp)
{
    m_ptxtRp_VtRevers_Up->setText(strCriteriumUp);
}
void LocalSettingsWin::slotSetRp_Be_Up(const QString &strCriteriumUp)
{
    m_ptxtRp_Be_Up->setText(strCriteriumUp);
}
void LocalSettingsWin::slotSetRp_Vbr_Up(const QString &strCriteriumUp)
{
    m_ptxtRp_Vbr_Up->setText(strCriteriumUp);
}
void LocalSettingsWin::slotSetRp_Gleak_Up(const QString &strCriteriumUp)
{
    m_ptxtRp_Gleak_Up->setText(strCriteriumUp);
}
void LocalSettingsWin::slotSetRp_DSleak_Up(const QString &strCriteriumUp)
{
    m_ptxtRp_DSleak_Up->setText(strCriteriumUp);
}
void LocalSettingsWin::slotSetRp_DSw_leak_Up(const QString &strCriteriumUp)
{
    m_ptxtRp_DSw_leak_Up->setText(strCriteriumUp);
}
void LocalSettingsWin::slotSetRp_DScurrent_Up(const QString &strCriteriumUp)
{
    m_ptxtRp_DScurrent_Up->setText(strCriteriumUp);
}
void LocalSettingsWin::slotSetRp_DSw_driver_Up(const QString &strCriteriumUp)
{
    m_ptxtRp_DSw_driver_Up->setText(strCriteriumUp);
}

//Hn
void LocalSettingsWin::slotSetHn_Vt_Dn(const QString &strCriteriumDn)
{
    m_ptxtHn_Vt_Dn->setText(strCriteriumDn);
}
void LocalSettingsWin::slotSetHn_VtRevers_Dn(const QString &strCriteriumDn)
{
    m_ptxtHn_VtRevers_Dn->setText(strCriteriumDn);
}
void LocalSettingsWin::slotSetHn_Be_Dn(const QString &strCriteriumDn)
{
    m_ptxtHn_Be_Dn->setText(strCriteriumDn);
}
void LocalSettingsWin::slotSetHn_Vbr_Dn(const QString &strCriteriumDn)
{
    m_ptxtHn_Vbr_Dn->setText(strCriteriumDn);
}
void LocalSettingsWin::slotSetHn_Gleak_Dn(const QString &strCriteriumDn)
{
    m_ptxtHn_Gleak_Dn->setText(strCriteriumDn);
}
void LocalSettingsWin::slotSetHn_DSleak_Dn(const QString &strCriteriumDn)
{
    m_ptxtHn_DSleak_Dn->setText(strCriteriumDn);
}
void LocalSettingsWin::slotSetHn_DSw_leak_Dn(const QString &strCriteriumDn)
{
    m_ptxtHn_DSw_leak_Dn->setText(strCriteriumDn);
}
void LocalSettingsWin::slotSetHn_DScurrent_Dn(const QString &strCriteriumDn)
{
    m_ptxtHn_DScurrent_Dn->setText(strCriteriumDn);
}
void LocalSettingsWin::slotSetHn_DSw_driver_Dn(const QString &strCriteriumDn)
{
    m_ptxtHn_DSw_driver_Dn->setText(strCriteriumDn);
}

void LocalSettingsWin::slotSetHn_Vt_Up(const QString &strCriteriumUp)
{
    m_ptxtHn_Vt_Up->setText(strCriteriumUp);
}
void LocalSettingsWin::slotSetHn_VtRevers_Up(const QString &strCriteriumUp)
{
    m_ptxtHn_VtRevers_Up->setText(strCriteriumUp);
}
void LocalSettingsWin::slotSetHn_Be_Up(const QString &strCriteriumUp)
{
    m_ptxtHn_Be_Up->setText(strCriteriumUp);
}
void LocalSettingsWin::slotSetHn_Vbr_Up(const QString &strCriteriumUp)
{
    m_ptxtHn_Vbr_Up->setText(strCriteriumUp);
}
void LocalSettingsWin::slotSetHn_Gleak_Up(const QString &strCriteriumUp)
{
    m_ptxtHn_Gleak_Up->setText(strCriteriumUp);
}
void LocalSettingsWin::slotSetHn_DSleak_Up(const QString &strCriteriumUp)
{
    m_ptxtHn_DSleak_Up->setText(strCriteriumUp);
}
void LocalSettingsWin::slotSetHn_DSw_leak_Up(const QString &strCriteriumUp)
{
    m_ptxtHn_DSw_leak_Up->setText(strCriteriumUp);
}
void LocalSettingsWin::slotSetHn_DScurrent_Up(const QString &strCriteriumUp)
{
    m_ptxtHn_DScurrent_Up->setText(strCriteriumUp);
}
void LocalSettingsWin::slotSetHn_DSw_driver_Up(const QString &strCriteriumUp)
{
    m_ptxtHn_DSw_driver_Up->setText(strCriteriumUp);
}

//Hp
void LocalSettingsWin::slotSetHp_Vt_Dn(const QString &strCriteriumDn)
{
    m_ptxtHp_Vt_Dn->setText(strCriteriumDn);
}
void LocalSettingsWin::slotSetHp_VtRevers_Dn(const QString &strCriteriumDn)
{
    m_ptxtHp_VtRevers_Dn->setText(strCriteriumDn);
}
void LocalSettingsWin::slotSetHp_Be_Dn(const QString &strCriteriumDn)
{
    m_ptxtHp_Be_Dn->setText(strCriteriumDn);
}
void LocalSettingsWin::slotSetHp_Vbr_Dn(const QString &strCriteriumDn)
{
    m_ptxtHp_Vbr_Dn->setText(strCriteriumDn);
}
void LocalSettingsWin::slotSetHp_Gleak_Dn(const QString &strCriteriumDn)
{
    m_ptxtHp_Gleak_Dn->setText(strCriteriumDn);
}
void LocalSettingsWin::slotSetHp_DSleak_Dn(const QString &strCriteriumDn)
{
    m_ptxtHp_DSleak_Dn->setText(strCriteriumDn);
}
void LocalSettingsWin::slotSetHp_DSw_leak_Dn(const QString &strCriteriumDn)
{
    m_ptxtHp_DSw_leak_Dn->setText(strCriteriumDn);
}
void LocalSettingsWin::slotSetHp_DScurrent_Dn(const QString &strCriteriumDn)
{
    m_ptxtHp_DScurrent_Dn->setText(strCriteriumDn);
}
void LocalSettingsWin::slotSetHp_DSw_driver_Dn(const QString &strCriteriumDn)
{
    m_ptxtHp_DSw_driver_Dn->setText(strCriteriumDn);
}

void LocalSettingsWin::slotSetHp_Vt_Up(const QString &strCriteriumUp)
{
    m_ptxtHp_Vt_Up->setText(strCriteriumUp);
}
void LocalSettingsWin::slotSetHp_VtRevers_Up(const QString &strCriteriumUp)
{
    m_ptxtHp_VtRevers_Up->setText(strCriteriumUp);
}
void LocalSettingsWin::slotSetHp_Be_Up(const QString &strCriteriumUp)
{
    m_ptxtHp_Be_Up->setText(strCriteriumUp);
}
void LocalSettingsWin::slotSetHp_Vbr_Up(const QString &strCriteriumUp)
{
    m_ptxtHp_Vbr_Up->setText(strCriteriumUp);
}
void LocalSettingsWin::slotSetHp_Gleak_Up(const QString &strCriteriumUp)
{
    m_ptxtHp_Gleak_Up->setText(strCriteriumUp);
}
void LocalSettingsWin::slotSetHp_DSleak_Up(const QString &strCriteriumUp)
{
    m_ptxtHp_DSleak_Up->setText(strCriteriumUp);
}
void LocalSettingsWin::slotSetHp_DSw_leak_Up(const QString &strCriteriumUp)
{
    m_ptxtHp_DSw_leak_Up->setText(strCriteriumUp);
}
void LocalSettingsWin::slotSetHp_DScurrent_Up(const QString &strCriteriumUp)
{
    m_ptxtHp_DScurrent_Up->setText(strCriteriumUp);
}
void LocalSettingsWin::slotSetHp_DSw_driver_Up(const QString &strCriteriumUp)
{
    m_ptxtHp_DSw_driver_Up->setText(strCriteriumUp);
}


//----------------------------------------------------------------------------------
//установка значений в поля Me
void LocalSettingsWin::slotSetKLVsMiMj_Dn(const QString &strCriteriumDn)
{
    //межметальные кельвины
    m_ptxtKLV_M1M2_Dn->setText(strCriteriumDn);
    m_ptxtKLV_M2M3_Dn->setText(strCriteriumDn);
    m_ptxtKLV_M3M4_Dn->setText(strCriteriumDn);
}
void LocalSettingsWin::slotSetKLVsMiMj_Up(const QString &strCriteriumUp)
{
    //межметальные кельвины
    m_ptxtKLV_M1M2_Up->setText(strCriteriumUp);
    m_ptxtKLV_M2M3_Up->setText(strCriteriumUp);
    m_ptxtKLV_M3M4_Up->setText(strCriteriumUp);
}
void LocalSettingsWin::slotSetKLVsM1M4_Dn(const QString &strCriteriumDn)
{
    //межметальные кельвины
    m_ptxtKLV_M1M4_Dn->setText(strCriteriumDn);
}
void LocalSettingsWin::slotSetKLVsM1M4_Up(const QString &strCriteriumUp)
{
    //межметальные кельвины
    m_ptxtKLV_M1M4_Up->setText(strCriteriumUp);
}

void LocalSettingsWin::slotSetZsMiMj_Dn(const QString &strCriteriumDn)
{
    //межметальные кельвины
    m_ptxtZ_M1M2_Dn->setText(strCriteriumDn);
    m_ptxtZ_M2M3_Dn->setText(strCriteriumDn);
    m_ptxtZ_M3M4_Dn->setText(strCriteriumDn);
}
void LocalSettingsWin::slotSetZsMiMj_Up(const QString &strCriteriumUp)
{
    //межметальные кельвины
    m_ptxtZ_M1M2_Up->setText(strCriteriumUp);
    m_ptxtZ_M2M3_Up->setText(strCriteriumUp);
    m_ptxtZ_M3M4_Up->setText(strCriteriumUp);
}
void LocalSettingsWin::slotSetZsM1M4_Dn(const QString &strCriteriumDn)
{
    //межметальные кельвины
    m_ptxtZ_M1M4_Dn->setText(strCriteriumDn);
}
void LocalSettingsWin::slotSetZsM1M4_Up(const QString &strCriteriumUp)
{
    //межметальные кельвины
    m_ptxtZ_M1M4_Up->setText(strCriteriumUp);
}
//-------------------------------------------------------------------------------------------------------
void LocalSettingsWin::slotApply()
{
    bool inputError = false;
    writeSettings(inputError);
    m_pcmdApply->setEnabled(false);
}
void LocalSettingsWin::slotCmdApplyEnabled()
{
    m_pcmdApply->setEnabled(true);
}
//-------------------------------------------------------------------------------------------------------
