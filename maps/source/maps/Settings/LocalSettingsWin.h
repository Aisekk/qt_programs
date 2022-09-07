#pragma once

#include <QDialog>
#include <QLineEdit>
#include <QLabel>
#include <QGridLayout>
#include <QTabWidget>
#include <QPushButton>
#include <QValidator>
#include <QSettings>
#include <QMessageBox>
//-------------------------------------------------------------------------------------------------
#include <memory>
//-------------------------------------------------------------------------------------------------
#include "Validator.h"
//-------------------------------------------------------------------------------------------------
using namespace std;

class LocalSettingsWin : public QDialog
{
    Q_OBJECT
public:
    LocalSettingsWin(QWidget *pwgt = nullptr);
    ~LocalSettingsWin();
    //---------------------------------------------------------------------------------------------
    void setSettings(shared_ptr<QSettings> spSettings);

    void createLineEdits();
    void createLabels();
    void setValidators();
    void addSeparatingLine(int &i, int j, QGridLayout* pgrdLayout);

    void addAll_R_SIL(int &i, int j, QGridLayout *pgrdLayout);
    void addTests_KLV_SIL(int &i, int j, QGridLayout *pgrdLayout);
    void addTests_Z_SIL(int &i, int j, QGridLayout* pgrdLayout);
    void addTests_RzSIL09(int &i, int j, QGridLayout* pgrdLayout);
    void addTests_RzSIL05(int &i, int j, QGridLayout *pgrdLayout);
    void addTests_RzSIL035(int &i, int j, QGridLayout *pgrdLayout);
    void addTests_RzSIL06(int &i, int j, QGridLayout *pgrdLayout);

    void addTests_KLV_MM(int &i, int j, QGridLayout *pgrdLayout);
    void addTests_Z_MM(int &i, int j, QGridLayout *pgrdLayout);
    void addTests_Meanders(int &i, int j, QGridLayout *pgrdLayout);

    void addTests_VDP(int &i, int j, QGridLayout *pgrdLayout);

    void addTests_An(int &i, int j, QGridLayout *pgrdLayout);
    void addTests_Ap(int &i, int j, QGridLayout *pgrdLayout);
    void addTests_Rn(int &i, int j, QGridLayout *pgrdLayout);
    void addTests_Rp(int &i, int j, QGridLayout *pgrdLayout);
    void addTests_Hn(int &i, int j, QGridLayout *pgrdLayout);
    void addTests_Hp(int &i, int j, QGridLayout *pgrdLayout);

    void addTests_pNpN(int &i, int j, QGridLayout* pgrdLayout);
    void addTests_Diod(int &i, int j, QGridLayout* pgrdLayout);
    void addTests_Capacity(int &i, int j, QGridLayout* pgrdLayout);

    //соединения полей
    void R_Dn_SIL_connections() const;
    void R_Up_SIL_connections() const;
    void KLVsDn_SIL_connections() const;
    void KLVsUp_SIL_connections() const;
    void ZsDn_SIL_connections() const;
    void ZsUp_SIL_connections() const;
    void Rz09Dn_SIL_connections() const;
    void Rz09Up_SIL_connections() const;
    void Rz05Dn_SIL_connections() const;
    void Rz05Up_SIL_connections() const;
    void Rz035Dn_SIL_connections() const;
    void Rz035Up_SIL_connections() const;
    void Rz06Dn_SIL_connections() const;
    void Rz06Up_SIL_connections() const;

    void Me_connections() const;
    void VDP_connections() const;
    void Tr_connections() const;

    //значения по умолчанию в полях
    void setDefaultMeaningsInLines();

    //настройки
    void writeSettings(bool &inputError);
    //---------------------------------------------------------------------------------------------
public slots:
    void slotCmdApplyEnabled();
    void slotApply();
    //---------------------------------------------------------------------------------------------
    //установка значений в поля SIL
    void slotSetRSIL_Dn(const QString& strCriteriumDn);
    void slotSetRSIL_Up(const QString& strCriteriumUp);

    void slotSetKLVsSIL_Dn(const QString& strCriteriumDn);
    void slotSetKLVsSIL_Up(const QString& strCriteriumUp);
    void slotSetZsSIL_Dn(const QString& strCriteriumDn);
    void slotSetZsSIL_Up(const QString& strCriteriumUp);
    void slotSetRz09SIL_Dn(const QString& strCriteriumDn);
    void slotSetRz09SIL_Up(const QString& strCriteriumUp);
    void slotSetRz05SIL_Dn(const QString& strCriteriumDn);
    void slotSetRz05SIL_Up(const QString& strCriteriumUp);
    void slotSetRz035SIL_Dn(const QString& strCriteriumDn);
    void slotSetRz035SIL_Up(const QString& strCriteriumUp);
    void slotSetRz06SIL_Dn(const QString& strCriteriumDn);
    void slotSetRz06SIL_Up(const QString& strCriteriumUp);
    //---------------------------------------------------------------------------------------------
    //установка значений в поля KLV_MeMe
    void slotSetKLV_M1M2_Dn(const QString& strCriteriumDn);
    void slotSetKLV_M2M3_Dn(const QString& strCriteriumDn);
    void slotSetKLV_M3M4_Dn(const QString& strCriteriumDn);
    void slotSetKLV_M1M4_Dn(const QString& strCriteriumDn);

    void slotSetKLV_M1M2_Up(const QString& strCriteriumUp);
    void slotSetKLV_M2M3_Up(const QString& strCriteriumUp);
    void slotSetKLV_M3M4_Up(const QString& strCriteriumUp);
    void slotSetKLV_M1M4_Up(const QString& strCriteriumUp);

    //установка значений в поля Z_MeMe
    void slotSetZ_M1M2_Dn(const QString& strCriteriumDn);
    void slotSetZ_M2M3_Dn(const QString& strCriteriumDn);
    void slotSetZ_M3M4_Dn(const QString& strCriteriumDn);
    void slotSetZ_M1M4_Dn(const QString& strCriteriumDn);

    void slotSetZ_M1M2_Up(const QString& strCriteriumUp);
    void slotSetZ_M2M3_Up(const QString& strCriteriumUp);
    void slotSetZ_M3M4_Up(const QString& strCriteriumUp);
    void slotSetZ_M1M4_Up(const QString& strCriteriumUp);

    //установка значений в поля Mean
    void slotSetMean1_05_Dn(const QString& strCriteriumDn);
    void slotSetMean1_09_Dn(const QString& strCriteriumDn);
    void slotSetMean2_06_Dn(const QString& strCriteriumDn);
    void slotSetMean2_09_Dn(const QString& strCriteriumDn);
    void slotSetMean3_06_Dn(const QString& strCriteriumDn);
    void slotSetMean3_09_Dn(const QString& strCriteriumDn);
    void slotSetMean4_06_Dn(const QString& strCriteriumDn);
    void slotSetMean4_09_Dn(const QString& strCriteriumDn);

    void slotSetMean1_05_Up(const QString& strCriteriumUp);
    void slotSetMean1_09_Up(const QString& strCriteriumUp);
    void slotSetMean2_06_Up(const QString& strCriteriumUp);
    void slotSetMean2_09_Up(const QString& strCriteriumUp);
    void slotSetMean3_06_Up(const QString& strCriteriumUp);
    void slotSetMean3_09_Up(const QString& strCriteriumUp);
    void slotSetMean4_06_Up(const QString& strCriteriumUp);
    void slotSetMean4_09_Up(const QString& strCriteriumUp);
    //---------------------------------------------------------------------------------------------
    //установка значений в поля VDP
    void slotSetVDPnWell_Dn(const QString& strCriteriumDn);
    void slotSetVDPpWell_Dn(const QString& strCriteriumDn);
    void slotSetVDPn_Dn(const QString& strCriteriumDn);
    void slotSetVDPp_Dn(const QString& strCriteriumDn);
    void slotSetVDPnSi_Dn(const QString& strCriteriumDn);
    void slotSetVDPpSi_Dn(const QString& strCriteriumDn);

    void slotSetVDPnWell_Up(const QString& strCriteriumUp);
    void slotSetVDPpWell_Up(const QString& strCriteriumUp);
    void slotSetVDPn_Up(const QString& strCriteriumUp);
    void slotSetVDPp_Up(const QString& strCriteriumUp);
    void slotSetVDPnSi_Up(const QString& strCriteriumUp);
    void slotSetVDPpSi_Up(const QString& strCriteriumUp);

    //---------------------------------------------------------------------------------------------
    //установка значений в поля Tr
    //An
    void slotSetAn_Vt_Dn(const QString& strCriteriumDn);
    void slotSetAn_VtRevers_Dn(const QString& strCriteriumDn);
    void slotSetAn_Be_Dn(const QString& strCriteriumDn);
    void slotSetAn_Vbr_Dn(const QString& strCriteriumDn);
    void slotSetAn_Gleak_Dn(const QString& strCriteriumDn);
    void slotSetAn_DSleak_Dn(const QString& strCriteriumDn);
    void slotSetAn_DSw_leak_Dn(const QString& strCriteriumDn);
    void slotSetAn_DScurrent_Dn(const QString& strCriteriumDn);
    void slotSetAn_DSw_driver_Dn(const QString& strCriteriumDn);

    void slotSetAn_Vt_Up(const QString& strCriteriumUp);
    void slotSetAn_VtRevers_Up(const QString& strCriteriumUp);
    void slotSetAn_Be_Up(const QString& strCriteriumUp);
    void slotSetAn_Vbr_Up(const QString& strCriteriumUp);
    void slotSetAn_Gleak_Up(const QString& strCriteriumUp);
    void slotSetAn_DSleak_Up(const QString& strCriteriumUp);
    void slotSetAn_DSw_leak_Up(const QString& strCriteriumUp);
    void slotSetAn_DScurrent_Up(const QString& strCriteriumUp);
    void slotSetAn_DSw_driver_Up(const QString& strCriteriumUp);

    //Ap
    void slotSetAp_Vt_Dn(const QString& strCriteriumDn);
    void slotSetAp_VtRevers_Dn(const QString& strCriteriumDn);
    void slotSetAp_Be_Dn(const QString& strCriteriumDn);
    void slotSetAp_Vbr_Dn(const QString& strCriteriumDn);
    void slotSetAp_Gleak_Dn(const QString& strCriteriumDn);
    void slotSetAp_DSleak_Dn(const QString& strCriteriumDn);
    void slotSetAp_DSw_leak_Dn(const QString& strCriteriumDn);
    void slotSetAp_DScurrent_Dn(const QString& strCriteriumDn);
    void slotSetAp_DSw_driver_Dn(const QString& strCriteriumDn);

    void slotSetAp_Vt_Up(const QString& strCriteriumUp);
    void slotSetAp_VtRevers_Up(const QString& strCriteriumUp);
    void slotSetAp_Be_Up(const QString& strCriteriumUp);
    void slotSetAp_Vbr_Up(const QString& strCriteriumUp);
    void slotSetAp_Gleak_Up(const QString& strCriteriumUp);
    void slotSetAp_DSleak_Up(const QString& strCriteriumUp);
    void slotSetAp_DSw_leak_Up(const QString& strCriteriumUp);
    void slotSetAp_DScurrent_Up(const QString& strCriteriumUp);
    void slotSetAp_DSw_driver_Up(const QString& strCriteriumUp);

    //Rn
    void slotSetRn_Vt_Dn(const QString& strCriteriumDn);
    void slotSetRn_VtRevers_Dn(const QString& strCriteriumDn);
    void slotSetRn_Be_Dn(const QString& strCriteriumDn);
    void slotSetRn_Vbr_Dn(const QString& strCriteriumDn);
    void slotSetRn_Gleak_Dn(const QString& strCriteriumDn);
    void slotSetRn_DSleak_Dn(const QString& strCriteriumDn);
    void slotSetRn_DSw_leak_Dn(const QString& strCriteriumDn);
    void slotSetRn_DScurrent_Dn(const QString& strCriteriumDn);
    void slotSetRn_DSw_driver_Dn(const QString& strCriteriumDn);

    void slotSetRn_Vt_Up(const QString& strCriteriumUp);
    void slotSetRn_VtRevers_Up(const QString& strCriteriumUp);
    void slotSetRn_Be_Up(const QString& strCriteriumUp);
    void slotSetRn_Vbr_Up(const QString& strCriteriumUp);
    void slotSetRn_Gleak_Up(const QString& strCriteriumUp);
    void slotSetRn_DSleak_Up(const QString& strCriteriumUp);
    void slotSetRn_DSw_leak_Up(const QString& strCriteriumUp);
    void slotSetRn_DScurrent_Up(const QString& strCriteriumUp);
    void slotSetRn_DSw_driver_Up(const QString& strCriteriumUp);

    //Rp
    void slotSetRp_Vt_Dn(const QString& strCriteriumDn);
    void slotSetRp_VtRevers_Dn(const QString& strCriteriumDn);
    void slotSetRp_Be_Dn(const QString& strCriteriumDn);
    void slotSetRp_Vbr_Dn(const QString& strCriteriumDn);
    void slotSetRp_Gleak_Dn(const QString& strCriteriumDn);
    void slotSetRp_DSleak_Dn(const QString& strCriteriumDn);
    void slotSetRp_DSw_leak_Dn(const QString& strCriteriumDn);
    void slotSetRp_DScurrent_Dn(const QString& strCriteriumDn);
    void slotSetRp_DSw_driver_Dn(const QString& strCriteriumDn);

    void slotSetRp_Vt_Up(const QString& strCriteriumUp);
    void slotSetRp_VtRevers_Up(const QString& strCriteriumUp);
    void slotSetRp_Be_Up(const QString& strCriteriumUp);
    void slotSetRp_Vbr_Up(const QString& strCriteriumUp);
    void slotSetRp_Gleak_Up(const QString& strCriteriumUp);
    void slotSetRp_DSleak_Up(const QString& strCriteriumUp);
    void slotSetRp_DSw_leak_Up(const QString& strCriteriumUp);
    void slotSetRp_DScurrent_Up(const QString& strCriteriumUp);
    void slotSetRp_DSw_driver_Up(const QString& strCriteriumUp);


    //Hn
    void slotSetHn_Vt_Dn(const QString& strCriteriumDn);
    void slotSetHn_VtRevers_Dn(const QString& strCriteriumDn);
    void slotSetHn_Be_Dn(const QString& strCriteriumDn);
    void slotSetHn_Vbr_Dn(const QString& strCriteriumDn);
    void slotSetHn_Gleak_Dn(const QString& strCriteriumDn);
    void slotSetHn_DSleak_Dn(const QString& strCriteriumDn);
    void slotSetHn_DSw_leak_Dn(const QString& strCriteriumDn);
    void slotSetHn_DScurrent_Dn(const QString& strCriteriumDn);
    void slotSetHn_DSw_driver_Dn(const QString& strCriteriumDn);

    void slotSetHn_Vt_Up(const QString& strCriteriumUp);
    void slotSetHn_VtRevers_Up(const QString& strCriteriumUp);
    void slotSetHn_Be_Up(const QString& strCriteriumUp);
    void slotSetHn_Vbr_Up(const QString& strCriteriumUp);
    void slotSetHn_Gleak_Up(const QString& strCriteriumUp);
    void slotSetHn_DSleak_Up(const QString& strCriteriumUp);
    void slotSetHn_DSw_leak_Up(const QString& strCriteriumUp);
    void slotSetHn_DScurrent_Up(const QString& strCriteriumUp);
    void slotSetHn_DSw_driver_Up(const QString& strCriteriumUp);

    //Hp
    void slotSetHp_Vt_Dn(const QString& strCriteriumDn);
    void slotSetHp_VtRevers_Dn(const QString& strCriteriumDn);
    void slotSetHp_Be_Dn(const QString& strCriteriumDn);
    void slotSetHp_Vbr_Dn(const QString& strCriteriumDn);
    void slotSetHp_Gleak_Dn(const QString& strCriteriumDn);
    void slotSetHp_DSleak_Dn(const QString& strCriteriumDn);
    void slotSetHp_DSw_leak_Dn(const QString& strCriteriumDn);
    void slotSetHp_DScurrent_Dn(const QString& strCriteriumDn);
    void slotSetHp_DSw_driver_Dn(const QString& strCriteriumDn);

    void slotSetHp_Vt_Up(const QString& strCriteriumUp);
    void slotSetHp_VtRevers_Up(const QString& strCriteriumUp);
    void slotSetHp_Be_Up(const QString& strCriteriumUp);
    void slotSetHp_Vbr_Up(const QString& strCriteriumUp);
    void slotSetHp_Gleak_Up(const QString& strCriteriumUp);
    void slotSetHp_DSleak_Up(const QString& strCriteriumUp);
    void slotSetHp_DSw_leak_Up(const QString& strCriteriumUp);
    void slotSetHp_DScurrent_Up(const QString& strCriteriumUp);
    void slotSetHp_DSw_driver_Up(const QString& strCriteriumUp);
    //---------------------------------------------------------------------------------------------
    //Установка значений в поля Me
    void slotSetKLVsMiMj_Dn(const QString& strCriteriumDn);
    void slotSetKLVsMiMj_Up(const QString& strCriteriumUp);
    void slotSetKLVsM1M4_Dn(const QString& strCriteriumDn);
    void slotSetKLVsM1M4_Up(const QString& strCriteriumUp);
    void slotSetZsMiMj_Dn(const QString& strCriteriumDn);
    void slotSetZsMiMj_Up(const QString& strCriteriumUp);
    void slotSetZsM1M4_Dn(const QString& strCriteriumDn);
    void slotSetZsM1M4_Up(const QString& strCriteriumUp);


private:
    QLabel* initLabelHyp();
    //---------------------------------------------------------------------------------------------
    //объекты, включенные в объектную иерархию:
    //---------------------------------------------------------------------------------------------
    //создание компоновок и вкладок
    QGridLayout* m_pgrdLayoutResistorsSIL;
    QGridLayout* m_pgrdLayoutResistorsMe;
    QGridLayout* m_pgrdLayoutVanderPau;
    QGridLayout* m_pgrdLayoutTransistors;
    QGridLayout* m_pgrdLayoutOther;
    QGridLayout* m_pgrdMainLayout;
    QTabWidget* m_pTab;
    //---------------------------------------------------------------------------------------------
    //создание текстовых полей

    //сопротивление всех силицидных структур
    QLineEdit* m_ptxtSIL_R_Dn;
    QLineEdit* m_ptxtSIL_R_Up;
    //силицидные Кельвины
    QLineEdit* m_ptxtSIL_KLVnM1_Dn;
    QLineEdit* m_ptxtSIL_KLVnM1_Up;
    QLineEdit* m_ptxtSIL_KLVpM1_Dn;
    QLineEdit* m_ptxtSIL_KLVpM1_Up;
    QLineEdit* m_ptxtSIL_KLVnSiM1_Dn;
    QLineEdit* m_ptxtSIL_KLVnSiM1_Up;
    QLineEdit* m_ptxtSIL_KLVpSiM1_Dn;
    QLineEdit* m_ptxtSIL_KLVpSiM1_Up;
    QLineEdit* m_ptxtSIL_KLVSiM1_Dn;
    QLineEdit* m_ptxtSIL_KLVSiM1_Up;
    //силицидные цепочки
    QLineEdit* m_ptxtSIL_ZnM1_Dn;
    QLineEdit* m_ptxtSIL_ZnM1_Up;
    QLineEdit* m_ptxtSIL_ZpM1_Dn;
    QLineEdit* m_ptxtSIL_ZpM1_Up;
    QLineEdit* m_ptxtSIL_ZnSiM1_Dn;
    QLineEdit* m_ptxtSIL_ZnSiM1_Up;
    QLineEdit* m_ptxtSIL_ZpSiM1_Dn;
    QLineEdit* m_ptxtSIL_ZpSiM1_Up;
    QLineEdit* m_ptxtSIL_ZSiM1_Dn;
    QLineEdit* m_ptxtSIL_ZSiM1_Up;
    //силицидные резисторы 09
    QLineEdit* m_ptxtRZnTiSi09_Dn;
    QLineEdit* m_ptxtRZnTiSi09_Up;
    QLineEdit* m_ptxtRZpTiSi09_Dn;
    QLineEdit* m_ptxtRZpTiSi09_Up;
    QLineEdit* m_ptxtRZnSiTiSi09_Dn;
    QLineEdit* m_ptxtRZnSiTiSi09_Up;
    QLineEdit* m_ptxtRZpSiTiSi09_Dn;
    QLineEdit* m_ptxtRZpSiTiSi09_Up;
    QLineEdit* m_ptxtRZSiTiSi09_Dn;
    QLineEdit* m_ptxtRZSiTiSi09_Up;
    //силицидные резисторы 05
    QLineEdit* m_ptxtRZnTiSi05_Dn;
    QLineEdit* m_ptxtRZnTiSi05_Up;
    QLineEdit* m_ptxtRZpTiSi05_Dn;
    QLineEdit* m_ptxtRZpTiSi05_Up;
    //------------------------------
    QLineEdit* m_ptxtRZnSiTiSi05_Dn;
    QLineEdit* m_ptxtRZnSiTiSi05_Up;
    QLineEdit* m_ptxtRZpSiTiSi05_Dn;
    QLineEdit* m_ptxtRZpSiTiSi05_Up;
    QLineEdit* m_ptxtRZSiTiSi05_Dn;
    QLineEdit* m_ptxtRZSiTiSi05_Up;
    //силицидные резисторы 035
    QLineEdit* m_ptxtRZnTiSi035_Dn;
    QLineEdit* m_ptxtRZnTiSi035_Up;
    QLineEdit* m_ptxtRZpTiSi035_Dn;
    QLineEdit* m_ptxtRZpTiSi035_Up;
    //-------------------------------
    QLineEdit* m_ptxtRZnSiTiSi035_Dn;
    QLineEdit* m_ptxtRZnSiTiSi035_Up;
    QLineEdit* m_ptxtRZpSiTiSi035_Dn;
    QLineEdit* m_ptxtRZpSiTiSi035_Up;
    QLineEdit* m_ptxtRZSiTiSi035_Dn;
    QLineEdit* m_ptxtRZSiTiSi035_Up;
    //силицидные резисторы 06
    QLineEdit* m_ptxtRZnTiSi06_Dn;
    QLineEdit* m_ptxtRZnTiSi06_Up;
    QLineEdit* m_ptxtRZpTiSi06_Dn;
    QLineEdit* m_ptxtRZpTiSi06_Up;
    QLineEdit* m_ptxtRZnSiTiSi06_Dn;
    QLineEdit* m_ptxtRZnSiTiSi06_Up;
    QLineEdit* m_ptxtRZpSiTiSi06_Dn;
    QLineEdit* m_ptxtRZpSiTiSi06_Up;
    QLineEdit* m_ptxtRZSiTiSi06_Dn;
    QLineEdit* m_ptxtRZSiTiSi06_Up;
    //---------------------------------------------------------------------------------------------
    //межметальные Кельвины
    QLineEdit* m_ptxtKLV_M1M2_Dn;
    QLineEdit* m_ptxtKLV_M1M2_Up;
    QLineEdit* m_ptxtKLV_M2M3_Dn;
    QLineEdit* m_ptxtKLV_M2M3_Up;
    QLineEdit* m_ptxtKLV_M3M4_Dn;
    QLineEdit* m_ptxtKLV_M3M4_Up;
    QLineEdit* m_ptxtKLV_M1M4_Dn;
    QLineEdit* m_ptxtKLV_M1M4_Up;
    //межметальные цепочки
    QLineEdit* m_ptxtZ_M1M2_Dn;
    QLineEdit* m_ptxtZ_M1M2_Up;
    QLineEdit* m_ptxtZ_M2M3_Dn;
    QLineEdit* m_ptxtZ_M2M3_Up;
    QLineEdit* m_ptxtZ_M3M4_Dn;
    QLineEdit* m_ptxtZ_M3M4_Up;
    QLineEdit* m_ptxtZ_M1M4_Dn;
    QLineEdit* m_ptxtZ_M1M4_Up;
    //меандры
    QLineEdit* m_ptxtMean1_05_Dn;
    QLineEdit* m_ptxtMean1_05_Up;
    QLineEdit* m_ptxtMean1_09_Dn;
    QLineEdit* m_ptxtMean1_09_Up;
    QLineEdit* m_ptxtMean2_06_Dn;
    QLineEdit* m_ptxtMean2_06_Up;
    QLineEdit* m_ptxtMean2_09_Dn;
    QLineEdit* m_ptxtMean2_09_Up;
    QLineEdit* m_ptxtMean3_06_Dn;
    QLineEdit* m_ptxtMean3_06_Up;
    QLineEdit* m_ptxtMean3_09_Dn;
    QLineEdit* m_ptxtMean3_09_Up;
    QLineEdit* m_ptxtMean4_06_Dn;
    QLineEdit* m_ptxtMean4_06_Up;
    QLineEdit* m_ptxtMean4_09_Dn;
    QLineEdit* m_ptxtMean4_09_Up;
    //---------------------------------------------------------------------------------------------
    //Ван дер пау
    QLineEdit* m_ptxtVDPnWell_Dn;
    QLineEdit* m_ptxtVDPnWell_Up;
    QLineEdit* m_ptxtVDPpWell_Dn;
    QLineEdit* m_ptxtVDPpWell_Up;
    QLineEdit* m_ptxtVDPn_Dn;
    QLineEdit* m_ptxtVDPn_Up;
    QLineEdit* m_ptxtVDPp_Dn;
    QLineEdit* m_ptxtVDPp_Up;
    QLineEdit* m_ptxtVDPnSi_Dn;
    QLineEdit* m_ptxtVDPnSi_Up;
    QLineEdit* m_ptxtVDPpSi_Dn;
    QLineEdit* m_ptxtVDPpSi_Up;
    //---------------------------------------------------------------------------------------------
    //An
    QLineEdit* m_ptxtAn_Vt_Dn;
    QLineEdit* m_ptxtAn_Vt_Up;
    QLineEdit* m_ptxtAn_VtRevers_Dn;
    QLineEdit* m_ptxtAn_VtRevers_Up;
    QLineEdit* m_ptxtAn_Be_Dn;
    QLineEdit* m_ptxtAn_Be_Up;
    QLineEdit* m_ptxtAn_Vbr_Dn;
    QLineEdit* m_ptxtAn_Vbr_Up;
    QLineEdit* m_ptxtAn_Gleak_Dn;
    QLineEdit* m_ptxtAn_Gleak_Up;
    QLineEdit* m_ptxtAn_DSleak_Dn;
    QLineEdit* m_ptxtAn_DSleak_Up;
    QLineEdit* m_ptxtAn_DSw_leak_Dn;
    QLineEdit* m_ptxtAn_DSw_leak_Up;
    QLineEdit* m_ptxtAn_DScurrent_Dn;
    QLineEdit* m_ptxtAn_DScurrent_Up;
    QLineEdit* m_ptxtAn_DSw_driver_Dn;
    QLineEdit* m_ptxtAn_DSw_driver_Up;
    //Ap
    QLineEdit* m_ptxtAp_Vt_Dn;
    QLineEdit* m_ptxtAp_Vt_Up;
    QLineEdit* m_ptxtAp_VtRevers_Dn;
    QLineEdit* m_ptxtAp_VtRevers_Up;
    QLineEdit* m_ptxtAp_Be_Dn;
    QLineEdit* m_ptxtAp_Be_Up;
    QLineEdit* m_ptxtAp_Vbr_Dn;
    QLineEdit* m_ptxtAp_Vbr_Up;
    QLineEdit* m_ptxtAp_Gleak_Dn;
    QLineEdit* m_ptxtAp_Gleak_Up;
    QLineEdit* m_ptxtAp_DSleak_Dn;
    QLineEdit* m_ptxtAp_DSleak_Up;
    QLineEdit* m_ptxtAp_DSw_leak_Dn;
    QLineEdit* m_ptxtAp_DSw_leak_Up;
    QLineEdit* m_ptxtAp_DScurrent_Dn;
    QLineEdit* m_ptxtAp_DScurrent_Up;
    QLineEdit* m_ptxtAp_DSw_driver_Dn;
    QLineEdit* m_ptxtAp_DSw_driver_Up;
    //Rn
    QLineEdit* m_ptxtRn_Vt_Dn;
    QLineEdit* m_ptxtRn_Vt_Up;
    QLineEdit* m_ptxtRn_VtRevers_Dn;
    QLineEdit* m_ptxtRn_VtRevers_Up;
    QLineEdit* m_ptxtRn_Be_Dn;
    QLineEdit* m_ptxtRn_Be_Up;
    QLineEdit* m_ptxtRn_Vbr_Dn;
    QLineEdit* m_ptxtRn_Vbr_Up;
    QLineEdit* m_ptxtRn_Gleak_Dn;
    QLineEdit* m_ptxtRn_Gleak_Up;
    QLineEdit* m_ptxtRn_DSleak_Dn;
    QLineEdit* m_ptxtRn_DSleak_Up;
    QLineEdit* m_ptxtRn_DSw_leak_Dn;
    QLineEdit* m_ptxtRn_DSw_leak_Up;
    QLineEdit* m_ptxtRn_DScurrent_Dn;
    QLineEdit* m_ptxtRn_DScurrent_Up;
    QLineEdit* m_ptxtRn_DSw_driver_Dn;
    QLineEdit* m_ptxtRn_DSw_driver_Up;
    //Rp
    QLineEdit* m_ptxtRp_Vt_Dn;
    QLineEdit* m_ptxtRp_Vt_Up;
    QLineEdit* m_ptxtRp_VtRevers_Dn;
    QLineEdit* m_ptxtRp_VtRevers_Up;
    QLineEdit* m_ptxtRp_Be_Dn;
    QLineEdit* m_ptxtRp_Be_Up;
    QLineEdit* m_ptxtRp_Vbr_Dn;
    QLineEdit* m_ptxtRp_Vbr_Up;
    QLineEdit* m_ptxtRp_Gleak_Dn;
    QLineEdit* m_ptxtRp_Gleak_Up;
    QLineEdit* m_ptxtRp_DSleak_Dn;
    QLineEdit* m_ptxtRp_DSleak_Up;
    QLineEdit* m_ptxtRp_DSw_leak_Dn;
    QLineEdit* m_ptxtRp_DSw_leak_Up;
    QLineEdit* m_ptxtRp_DScurrent_Dn;
    QLineEdit* m_ptxtRp_DScurrent_Up;
    QLineEdit* m_ptxtRp_DSw_driver_Dn;
    QLineEdit* m_ptxtRp_DSw_driver_Up;
    //Hn
    QLineEdit* m_ptxtHn_Vt_Dn;
    QLineEdit* m_ptxtHn_Vt_Up;
    QLineEdit* m_ptxtHn_VtRevers_Dn;
    QLineEdit* m_ptxtHn_VtRevers_Up;
    QLineEdit* m_ptxtHn_Be_Dn;
    QLineEdit* m_ptxtHn_Be_Up;
    QLineEdit* m_ptxtHn_Vbr_Dn;
    QLineEdit* m_ptxtHn_Vbr_Up;
    QLineEdit* m_ptxtHn_Gleak_Dn;
    QLineEdit* m_ptxtHn_Gleak_Up;
    QLineEdit* m_ptxtHn_DSleak_Dn;
    QLineEdit* m_ptxtHn_DSleak_Up;
    QLineEdit* m_ptxtHn_DSw_leak_Dn;
    QLineEdit* m_ptxtHn_DSw_leak_Up;
    QLineEdit* m_ptxtHn_DScurrent_Dn;
    QLineEdit* m_ptxtHn_DScurrent_Up;
    QLineEdit* m_ptxtHn_DSw_driver_Dn;
    QLineEdit* m_ptxtHn_DSw_driver_Up;
    //Hp
    QLineEdit* m_ptxtHp_Vt_Dn;
    QLineEdit* m_ptxtHp_Vt_Up;
    QLineEdit* m_ptxtHp_VtRevers_Dn;
    QLineEdit* m_ptxtHp_VtRevers_Up;
    QLineEdit* m_ptxtHp_Be_Dn;
    QLineEdit* m_ptxtHp_Be_Up;
    QLineEdit* m_ptxtHp_Vbr_Dn;
    QLineEdit* m_ptxtHp_Vbr_Up;
    QLineEdit* m_ptxtHp_Gleak_Dn;
    QLineEdit* m_ptxtHp_Gleak_Up;
    QLineEdit* m_ptxtHp_DSleak_Dn;
    QLineEdit* m_ptxtHp_DSleak_Up;
    QLineEdit* m_ptxtHp_DSw_leak_Dn;
    QLineEdit* m_ptxtHp_DSw_leak_Up;
    QLineEdit* m_ptxtHp_DScurrent_Dn;
    QLineEdit* m_ptxtHp_DScurrent_Up;
    QLineEdit* m_ptxtHp_DSw_driver_Dn;
    QLineEdit* m_ptxtHp_DSw_driver_Up;
    //---------------------------------------------------------------------------------------------
    //структуры контактирования
    QLineEdit* m_ptxtpNpN_Dn;
    QLineEdit* m_ptxtpNpN_Up;
    //диоды
    QLineEdit* m_ptxtDiodn_pWell_Dn;
    QLineEdit* m_ptxtDiodn_pWell_Up;
    QLineEdit* m_ptxtDiodp_nWell_Dn;
    QLineEdit* m_ptxtDiodp_nWell_Up;
    //емкости
    QLineEdit* m_ptxtCM1M2_Dn;
    QLineEdit* m_ptxtCM1M2_Up;
    QLineEdit* m_ptxtCM2M3_Dn;
    QLineEdit* m_ptxtCM2M3_Up;
    QLineEdit* m_ptxtCM3M4_Dn;
    QLineEdit* m_ptxtCM3M4_Up;
    QLineEdit* m_ptxtCpSinWell_Dn;
    QLineEdit* m_ptxtCpSinWell_Up;
    QLineEdit* m_ptxtCnSipWell_Dn;
    QLineEdit* m_ptxtCnSipWell_Up;
    //-----------------------------------------------------------------------------------------
    //создание лейблов тестовых элементов
    //-----------------------------------------------------------------------------------------
    //сопротивление всех силицидных структур
    QLabel* m_plblSIL_R;
    //силицидные Кельвины
    QLabel* m_plblSIL_KLVnM1;
    QLabel* m_plblSIL_KLVpM1;
    QLabel* m_plblSIL_KLVnSiM1;
    QLabel* m_plblSIL_KLVpSiM1;
    QLabel* m_plblSIL_KLVSiM1;
    //силицидные цепочки
    QLabel* m_plblSIL_ZnM1;
    QLabel* m_plblSIL_ZpM1;
    QLabel* m_plblSIL_ZnSiM1;
    QLabel* m_plblSIL_ZpSiM1;
    QLabel* m_plblSIL_ZSiM1;
    //силицидные резисторы 09
    QLabel* m_plblRZnTiSi09;
    QLabel* m_plblRZpTiSi09;
    QLabel* m_plblRZnSiTiSi09;
    QLabel* m_plblRZpSiTiSi09;
    QLabel* m_plblRZSiTiSi09;
    //силицидные резисторы 05
    QLabel* m_plblRZnTiSi05;
    QLabel* m_plblRZpTiSi05;
    QLabel* m_plblRZnSiTiSi05;
    QLabel* m_plblRZpSiTiSi05;
    QLabel* m_plblRZSiTiSi05;
    //силицидные резисторы 035
    QLabel* m_plblRZnTiSi035;
    QLabel* m_plblRZpTiSi035;
    QLabel* m_plblRZnSiTiSi035;
    QLabel* m_plblRZpSiTiSi035;
    QLabel* m_plblRZSiTiSi035;
    //силицидные резисторы 06
    QLabel* m_plblRZnTiSi06;
    QLabel* m_plblRZpTiSi06;
    QLabel* m_plblRZnSiTiSi06;
    QLabel* m_plblRZpSiTiSi06;
    QLabel* m_plblRZSiTiSi06;
    //---------------------------------------------------------------------------------------------
    //межметальные Кельвины
    QLabel* m_plblKLV_M1M2;
    QLabel* m_plblKLV_M2M3;
    QLabel* m_plblKLV_M3M4;
    QLabel* m_plblKLV_M1M4;
    //межметальные цепочки
    QLabel* m_plblZ_M1M2;
    QLabel* m_plblZ_M2M3;
    QLabel* m_plblZ_M3M4;
    QLabel* m_plblZ_M1M4;
    //меандры
    QLabel* m_plblMean1_05;
    QLabel* m_plblMean1_09;
    QLabel* m_plblMean2_06;
    QLabel* m_plblMean2_09;
    QLabel* m_plblMean3_06;
    QLabel* m_plblMean3_09;
    QLabel* m_plblMean4_06;
    QLabel* m_plblMean4_09;
    //---------------------------------------------------------------------------------------------
    //Ван дер пау
    QLabel* m_plblVDPnWell;
    QLabel* m_plblVDPpWell;
    QLabel* m_plblVDPn;
    QLabel* m_plblVDPp;
    QLabel* m_plblVDPnSi;
    QLabel* m_plblVDPpSi;
    //---------------------------------------------------------------------------------------------
    //Транзисторы
    //An
    QLabel* m_plblAn_Vt;
    QLabel* m_plblAn_VtRevers;
    QLabel* m_plblAn_Be;
    QLabel* m_plblAn_Vbr;
    QLabel* m_plblAn_Gleak;
    QLabel* m_plblAn_DSleak;
    QLabel* m_plblAn_DSw_leak;
    QLabel* m_plblAn_DScurrent;
    QLabel* m_plblAn_DSw_driver;
    //Ap
    QLabel* m_plblAp_Vt;
    QLabel* m_plblAp_VtRevers;
    QLabel* m_plblAp_Be;
    QLabel* m_plblAp_Vbr;
    QLabel* m_plblAp_Gleak;
    QLabel* m_plblAp_DSleak;
    QLabel* m_plblAp_DSw_leak;
    QLabel* m_plblAp_DScurrent;
    QLabel* m_plblAp_DSw_driver;
    //Rn
    QLabel* m_plblRn_Vt;
    QLabel* m_plblRn_VtRevers;
    QLabel* m_plblRn_Be;
    QLabel* m_plblRn_Vbr;
    QLabel* m_plblRn_Gleak;
    QLabel* m_plblRn_DSleak;
    QLabel* m_plblRn_DSw_leak;
    QLabel* m_plblRn_DScurrent;
    QLabel* m_plblRn_DSw_driver;
    //Rp
    QLabel* m_plblRp_Vt;
    QLabel* m_plblRp_VtRevers;
    QLabel* m_plblRp_Be;
    QLabel* m_plblRp_Vbr;
    QLabel* m_plblRp_Gleak;
    QLabel* m_plblRp_DSleak;
    QLabel* m_plblRp_DSw_leak;
    QLabel* m_plblRp_DScurrent;
    QLabel* m_plblRp_DSw_driver;
    //Hn
    QLabel* m_plblHn_Vt;
    QLabel* m_plblHn_VtRevers;
    QLabel* m_plblHn_Be;
    QLabel* m_plblHn_Vbr;
    QLabel* m_plblHn_Gleak;
    QLabel* m_plblHn_DSleak;
    QLabel* m_plblHn_DSw_leak;
    QLabel* m_plblHn_DScurrent;
    QLabel* m_plblHn_DSw_driver;
    //Hp
    QLabel* m_plblHp_Vt;
    QLabel* m_plblHp_VtRevers;
    QLabel* m_plblHp_Be;
    QLabel* m_plblHp_Vbr;
    QLabel* m_plblHp_Gleak;
    QLabel* m_plblHp_DSleak;
    QLabel* m_plblHp_DSw_leak;
    QLabel* m_plblHp_DScurrent;
    QLabel* m_plblHp_DSw_driver;
    //---------------------------------------------------------------------------------------------
    //структуры контактирования
    QLabel* m_plblpNpN;
    //диоды
    QLabel* m_plblDiodn_pWell;
    QLabel* m_plblDiodp_nWell;
    //емкости
    QLabel* m_plblCM1M2;
    QLabel* m_plblCM2M3;
    QLabel* m_plblCM3M4;
    QLabel* m_plblCpSinWell;
    QLabel* m_plblCnSipWell;
    //---------------------------------------------------------------------------------------------
    //валидаторы
    QDoubleValidator* m_pdblValidator_R_Dn;
    QDoubleValidator* m_pdblValidator_R_Up;

    QDoubleValidator* m_pdblValidator_KLVnM1_Dn;
    QDoubleValidator* m_pdblValidator_KLVnM1_Up;
    //---------------------------------------------------------------------------------------------
    //кнопки
    QPushButton* m_pcmdApply;
    //---------------------------------------------------------------------------------------------
    //объекты, не включенные в объектную иерархию:
    //---------------------------------------------------------------------------------------------
    //настройки
    shared_ptr<QSettings> m_spSettings;
    //---------------------------------------------------------------------------------------------
    //обработка ошибок
    double m_TypeLimit;
    QString m_strInputErrorType;
    QString m_strInputErrorContent;
    //---------------------------------------------------------------------------------------------
};



