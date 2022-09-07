#include "SystemSettings.h"
using namespace SystemSettings;

//==============================================================================================
shared_ptr<QSettings> SystemSettings::spSettings{nullptr};
shared_ptr<LocalSettingsWin> SystemSettings::spLocalSettingsWin{nullptr};
shared_ptr<GlobalSettingsWin> SystemSettings::spGlobalSettingsWin{nullptr};
Settings SystemSettings::settings{};
//----------------------------------------------------------------------------------------------
void SystemSettings::initSettings()
{
    spSettings = make_shared<QSettings>();
    spLocalSettingsWin = make_shared<LocalSettingsWin>();
    spGlobalSettingsWin = make_shared<GlobalSettingsWin>();
    spLocalSettingsWin->setSettings(spSettings);
    spGlobalSettingsWin->setSettings(spSettings);
}
//----------------------------------------------------------------------------------------------
//чтение из реестра глобальных норм и их установка в текстовые поля (при загрузке программы)
void SystemSettings::readSettings_GlobalNorm(double& criterionDn, double& criterionUp,
                                             ValuePrefix valuePrefix)
{
    GlobalSettingsWin *pGlobalSettingsWin = spGlobalSettingsWin.get();
    QSettings *pSettings = spSettings.get();

    pSettings->beginGroup("/Settings");
    pSettings->beginGroup("/GlobalLimits");

    QString strDn = pSettings->value("/Dn_Limit","-1.000000e+290").toString();
    pGlobalSettingsWin->setDnLimit(strDn);
    criterionDn = Validator::valueToDouble(strDn);

    QString strUp = pSettings->value("/Up_Limit","1.000000e+290").toString();
    pGlobalSettingsWin->setUpLimit(strUp);
    criterionUp = Validator::valueToDouble(strUp);

    pSettings->endGroup();
    pSettings->endGroup();

    double milli = 1.0e+3, micro = 1.0e+6, nano = 1.0e+9, pico = 1.0e+12;
    double kilo = 1.0e-3, mega = 1.0e-6, giga = 1.0e-9, tera = 1.0e-12;

    switch(valuePrefix)
    {
    case ValuePrefix::norm:         break;
    case ValuePrefix::milli:        {  criterionDn *= milli;    criterionUp *= milli;  break;   }
    case ValuePrefix::micro:        {  criterionDn *= micro;    criterionUp *= micro;  break;   }
    case ValuePrefix::nano:         {  criterionDn *= nano;     criterionUp *= nano;   break;   }
    case ValuePrefix::pico:         {  criterionDn *= pico;     criterionUp *= pico;   break;   }
    case ValuePrefix::kilo:         {  criterionDn *= kilo;     criterionUp *= kilo;   break;   }
    case ValuePrefix::mega:         {  criterionDn *= mega;     criterionUp *= mega;   break;   }
    case ValuePrefix::giga:         {  criterionDn *= giga;     criterionUp *= giga;   break;   }
    case ValuePrefix::tera:         {  criterionDn *= tera;     criterionUp *= tera;   break;   }
    }
}

//чтение из реестра локальных норм и их установка в текстовые поля (при загрузке программы)
void SystemSettings::readSettings_LocalNorms()
{
    LocalSettingsWin *pLocalSettingsWin = spLocalSettingsWin.get();
    QSettings *pSettings = spSettings.get();

    pSettings->beginGroup("/Settings");
    //---------------------------------------------------------------------------------------------
    pSettings->beginGroup("/R_SIL");
    QString strR_SIL_Dn = pSettings->value("/R_SIL_Dn","0.1").toString();
    pLocalSettingsWin->slotSetRSIL_Dn(strR_SIL_Dn);

    QString strR_SIL_Up = pSettings->value("/R_SIL_Up","10.0").toString();
    pLocalSettingsWin->slotSetRSIL_Up(strR_SIL_Up);
    pSettings->endGroup();
    //---------------------------------------------------------------------------------------------
    pSettings->beginGroup("/KLVs_SIL");
    QString strKLVnM1_Dn = pSettings->value("/KLVnM1_Dn","0.1").toString();
    QString strKLVpM1_Dn = pSettings->value("/KLVpM1_Dn","0.1").toString();
    QString strKLVnSiM1_Dn = pSettings->value("/KLVnSiM1_Dn","0.1").toString();
    QString strKLVpSiM1_Dn = pSettings->value("/KLVpSiM1_Dn","0.1").toString();
    QString strKLVSiM1_Dn = pSettings->value("/KLVSiM1_Dn","0.1").toString();
    pLocalSettingsWin->slotSetKLVsSIL_Dn(strKLVnM1_Dn);
    pLocalSettingsWin->slotSetKLVsSIL_Dn(strKLVpM1_Dn);
    pLocalSettingsWin->slotSetKLVsSIL_Dn(strKLVnSiM1_Dn);
    pLocalSettingsWin->slotSetKLVsSIL_Dn(strKLVpSiM1_Dn);
    pLocalSettingsWin->slotSetKLVsSIL_Dn(strKLVSiM1_Dn);

    QString strKLVnM1_Up = pSettings->value("/KLVnM1_Up","10.0").toString();
    QString strKLVpM1_Up = pSettings->value("/KLVpM1_Up","10.0").toString();
    QString strKLVnSiM1_Up = pSettings->value("/KLVnSiM1_Up","10.0").toString();
    QString strKLVpSiM1_Up = pSettings->value("/KLVpSiM1_Up","10.0").toString();
    QString strKLVSiM1_Up = pSettings->value("/KLVSiM1_Up","10.0").toString();
    pLocalSettingsWin->slotSetKLVsSIL_Up(strKLVnM1_Up);
    pLocalSettingsWin->slotSetKLVsSIL_Up(strKLVpM1_Up);
    pLocalSettingsWin->slotSetKLVsSIL_Up(strKLVnSiM1_Up);
    pLocalSettingsWin->slotSetKLVsSIL_Up(strKLVpSiM1_Up);
    pLocalSettingsWin->slotSetKLVsSIL_Up(strKLVSiM1_Up);
    pSettings->endGroup();
    //---------------------------------------------------------------------------------------------
    pSettings->beginGroup("/Zs_SIL");
    QString strZnM1_Dn = pSettings->value("/ZnM1_Dn","0.1").toString();
    QString strZpM1_Dn = pSettings->value("/ZpM1_Dn","0.1").toString();
    QString strZnSiM1_Dn = pSettings->value("/ZnSiM1_Dn","0.1").toString();
    QString strZpSiM1_Dn = pSettings->value("/ZpSiM1_Dn","0.1").toString();
    QString strZSiM1_Dn = pSettings->value("/ZSiM1_Dn","0.1").toString();
    pLocalSettingsWin->slotSetZsSIL_Dn(strZnM1_Dn);
    pLocalSettingsWin->slotSetZsSIL_Dn(strZpM1_Dn);
    pLocalSettingsWin->slotSetZsSIL_Dn(strZnSiM1_Dn);
    pLocalSettingsWin->slotSetZsSIL_Dn(strZpSiM1_Dn);
    pLocalSettingsWin->slotSetZsSIL_Dn(strZSiM1_Dn);

    QString strZnM1_Up = pSettings->value("/ZnM1_Up","10.0").toString();
    QString strZpM1_Up = pSettings->value("/ZpM1_Up","10.0").toString();
    QString strZnSiM1_Up = pSettings->value("/ZnSiM1_Up","10.0").toString();
    QString strZpSiM1_Up = pSettings->value("/ZpSiM1_Up","10.0").toString();
    QString strZSiM1_Up = pSettings->value("/ZSiM1_Up","10.0").toString();
    pLocalSettingsWin->slotSetZsSIL_Up(strZnM1_Up);
    pLocalSettingsWin->slotSetZsSIL_Up(strZpM1_Up);
    pLocalSettingsWin->slotSetZsSIL_Up(strZnSiM1_Up);
    pLocalSettingsWin->slotSetZsSIL_Up(strZpSiM1_Up);
    pLocalSettingsWin->slotSetZsSIL_Up(strZSiM1_Up);
    pSettings->endGroup();
    //---------------------------------------------------------------------------------------------
    pSettings->beginGroup("/RZ09_SIL");
    QString strRZnTiSi09_Dn = pSettings->value("/RZnTiSi09_Dn","0.1").toString();
    QString strRZpTiSi09_Dn = pSettings->value("/RZpTiSi09_Dn","0.1").toString();
    QString strRZnSiTiSi09_Dn = pSettings->value("/RZnSiTiSi09_Dn","0.1").toString();
    QString strRZpSiTiSi09_Dn = pSettings->value("/RZpTiSi09_Dn","0.1").toString();
    QString strRZSiTiSi09_Dn = pSettings->value("/RZSiTiSi09_Dn","0.1").toString();
    pLocalSettingsWin->slotSetRz09SIL_Dn(strRZnTiSi09_Dn);
    pLocalSettingsWin->slotSetRz09SIL_Dn(strRZpTiSi09_Dn);
    pLocalSettingsWin->slotSetRz09SIL_Dn(strRZnSiTiSi09_Dn);
    pLocalSettingsWin->slotSetRz09SIL_Dn(strRZpSiTiSi09_Dn);
    pLocalSettingsWin->slotSetRz09SIL_Dn(strRZSiTiSi09_Dn);

    QString strRZnTiSi09_Up = pSettings->value("/RZnTiSi09_Up","10.0").toString();
    QString strRZpTiSi09_Up = pSettings->value("/RZpTiSi09_Up","10.0").toString();
    QString strRZnSiTiSi09_Up = pSettings->value("/RZnSiTiSi09_Up","10.0").toString();
    QString strRZpSiTiSi09_Up = pSettings->value("/RZpTiSi09_Up","10.0").toString();
    QString strRZSiTiSi09_Up = pSettings->value("/RZSiTiSi09_Up","10.0").toString();
    pLocalSettingsWin->slotSetRz09SIL_Up(strRZnTiSi09_Up);
    pLocalSettingsWin->slotSetRz09SIL_Up(strRZpTiSi09_Up);
    pLocalSettingsWin->slotSetRz09SIL_Up(strRZnSiTiSi09_Up);
    pLocalSettingsWin->slotSetRz09SIL_Up(strRZpSiTiSi09_Up);
    pLocalSettingsWin->slotSetRz09SIL_Up(strRZSiTiSi09_Up);
    pSettings->endGroup();

    pSettings->beginGroup("/RZ05_SIL");
    QString strRZnTiSi05_Dn = pSettings->value("/RZnTiSi05_Dn","0.1").toString();
    QString strRZpTiSi05_Dn = pSettings->value("/RZpTiSi05_Dn","0.1").toString();
    QString strRZnSiTiSi05_Dn = pSettings->value("/RZnSiTiSi05_Dn","0.1").toString();
    QString strRZpSiTiSi05_Dn = pSettings->value("/RZpTiSi05_Dn","0.1").toString();
    QString strRZSiTiSi05_Dn = pSettings->value("/RZSiTiSi05_Dn","0.1").toString();
    pLocalSettingsWin->slotSetRz05SIL_Dn(strRZnTiSi05_Dn);
    pLocalSettingsWin->slotSetRz05SIL_Dn(strRZpTiSi05_Dn);
    pLocalSettingsWin->slotSetRz05SIL_Dn(strRZnSiTiSi05_Dn);
    pLocalSettingsWin->slotSetRz05SIL_Dn(strRZpSiTiSi05_Dn);
    pLocalSettingsWin->slotSetRz05SIL_Dn(strRZSiTiSi05_Dn);

    QString strRZnTiSi05_Up = pSettings->value("/RZnTiSi05_Up","10.0").toString();
    QString strRZpTiSi05_Up = pSettings->value("/RZpTiSi05_Up","10.0").toString();
    QString strRZnSiTiSi05_Up = pSettings->value("/RZnSiTiSi05_Up","10.0").toString();
    QString strRZpSiTiSi05_Up = pSettings->value("/RZpTiSi05_Up","10.0").toString();
    QString strRZSiTiSi05_Up = pSettings->value("/RZSiTiSi05_Up","10.0").toString();
    pLocalSettingsWin->slotSetRz05SIL_Up(strRZnTiSi05_Up);
    pLocalSettingsWin->slotSetRz05SIL_Up(strRZpTiSi05_Up);
    pLocalSettingsWin->slotSetRz05SIL_Up(strRZnSiTiSi05_Up);
    pLocalSettingsWin->slotSetRz05SIL_Up(strRZpSiTiSi05_Up);
    pLocalSettingsWin->slotSetRz05SIL_Up(strRZSiTiSi05_Up);
    pSettings->endGroup();

    pSettings->beginGroup("/RZ035_SIL");
    QString strRZnTiSi035_Dn = pSettings->value("/RZnTiSi035_Dn","0.1").toString();
    QString strRZpTiSi035_Dn = pSettings->value("/RZpTiSi035_Dn","0.1").toString();
    QString strRZnSiTiSi035_Dn = pSettings->value("/RZnSiTiSi035_Dn","0.1").toString();
    QString strRZpSiTiSi035_Dn = pSettings->value("/RZpTiSi035_Dn","0.1").toString();
    QString strRZSiTiSi035_Dn = pSettings->value("/RZSiTiSi035_Dn","0.1").toString();
    pLocalSettingsWin->slotSetRz035SIL_Dn(strRZnTiSi035_Dn);
    pLocalSettingsWin->slotSetRz035SIL_Dn(strRZpTiSi035_Dn);
    pLocalSettingsWin->slotSetRz035SIL_Dn(strRZnSiTiSi035_Dn);
    pLocalSettingsWin->slotSetRz035SIL_Dn(strRZpSiTiSi035_Dn);
    pLocalSettingsWin->slotSetRz035SIL_Dn(strRZSiTiSi035_Dn);

    QString strRZnTiSi035_Up = pSettings->value("/RZnTiSi035_Up","10.0").toString();
    QString strRZpTiSi035_Up = pSettings->value("/RZpTiSi035_Up","10.0").toString();
    QString strRZnSiTiSi035_Up = pSettings->value("/RZnSiTiSi035_Up","10.0").toString();
    QString strRZpSiTiSi035_Up = pSettings->value("/RZpTiSi035_Up","10.0").toString();
    QString strRZSiTiSi035_Up = pSettings->value("/RZSiTiSi035_Up","10.0").toString();
    pLocalSettingsWin->slotSetRz035SIL_Up(strRZnTiSi035_Up);
    pLocalSettingsWin->slotSetRz035SIL_Up(strRZpTiSi035_Up);
    pLocalSettingsWin->slotSetRz035SIL_Up(strRZnSiTiSi035_Up);
    pLocalSettingsWin->slotSetRz035SIL_Up(strRZpSiTiSi035_Up);
    pLocalSettingsWin->slotSetRz035SIL_Up(strRZSiTiSi035_Up);
    pSettings->endGroup();

    pSettings->beginGroup("/RZ06_SIL");
    QString strRZnTiSi06_Dn = pSettings->value("/RZnTiSi06_Dn","0.1").toString();
    QString strRZpTiSi06_Dn = pSettings->value("/RZpTiSi06_Dn","0.1").toString();
    QString strRZnSiTiSi06_Dn = pSettings->value("/RZnSiTiSi06_Dn","0.1").toString();
    QString strRZpSiTiSi06_Dn = pSettings->value("/RZpTiSi06_Dn","0.1").toString();
    QString strRZSiTiSi06_Dn = pSettings->value("/RZSiTiSi06_Dn","0.1").toString();
    pLocalSettingsWin->slotSetRz06SIL_Dn(strRZnTiSi06_Dn);
    pLocalSettingsWin->slotSetRz06SIL_Dn(strRZpTiSi06_Dn);
    pLocalSettingsWin->slotSetRz06SIL_Dn(strRZnSiTiSi06_Dn);
    pLocalSettingsWin->slotSetRz06SIL_Dn(strRZpSiTiSi06_Dn);
    pLocalSettingsWin->slotSetRz06SIL_Dn(strRZSiTiSi06_Dn);

    QString strRZnTiSi06_Up = pSettings->value("/RZnTiSi06_Up","10.0").toString();
    QString strRZpTiSi06_Up = pSettings->value("/RZpTiSi06_Up","10.0").toString();
    QString strRZnSiTiSi06_Up = pSettings->value("/RZnSiTiSi06_Up","10.0").toString();
    QString strRZpSiTiSi06_Up = pSettings->value("/RZpTiSi06_Up","10.0").toString();
    QString strRZSiTiSi06_Up = pSettings->value("/RZSiTiSi06_Up","10.0").toString();
    pLocalSettingsWin->slotSetRz06SIL_Up(strRZnTiSi06_Up);
    pLocalSettingsWin->slotSetRz06SIL_Up(strRZpTiSi06_Up);
    pLocalSettingsWin->slotSetRz06SIL_Up(strRZnSiTiSi06_Up);
    pLocalSettingsWin->slotSetRz06SIL_Up(strRZpSiTiSi06_Up);
    pLocalSettingsWin->slotSetRz06SIL_Up(strRZSiTiSi06_Up);
    pSettings->endGroup();
    //---------------------------------------------------------------------------------------------
    pSettings->beginGroup("/KLV_MeMe");
    QString strKLV_M1M2_Dn = pSettings->value("/KLV_M1M2_Dn","0.1").toString();
    QString strKLV_M2M3_Dn = pSettings->value("/KLV_M2M3_Dn","0.1").toString();
    QString strKLV_M3M4_Dn = pSettings->value("/KLV_M3M4_Dn","0.1").toString();
    QString strKLV_M1M4_Dn = pSettings->value("/KLV_M1M4_Dn","0.1").toString();
    pLocalSettingsWin->slotSetKLV_M1M2_Dn(strKLV_M1M2_Dn);
    pLocalSettingsWin->slotSetKLV_M2M3_Dn(strKLV_M2M3_Dn);
    pLocalSettingsWin->slotSetKLV_M3M4_Dn(strKLV_M3M4_Dn);
    pLocalSettingsWin->slotSetKLV_M1M4_Dn(strKLV_M1M4_Dn);

    QString strKLV_M1M2_Up = pSettings->value("/KLV_M1M2_Up","2.5").toString();
    QString strKLV_M2M3_Up = pSettings->value("/KLV_M2M3_Up","2.5").toString();
    QString strKLV_M3M4_Up = pSettings->value("/KLV_M3M4_Up","2.5").toString();
    QString strKLV_M1M4_Up = pSettings->value("/KLV_M1M4_Up","7.5").toString();
    pLocalSettingsWin->slotSetKLV_M1M2_Up(strKLV_M1M2_Up);
    pLocalSettingsWin->slotSetKLV_M2M3_Up(strKLV_M2M3_Up);
    pLocalSettingsWin->slotSetKLV_M3M4_Up(strKLV_M3M4_Up);
    pLocalSettingsWin->slotSetKLV_M1M4_Up(strKLV_M1M4_Up);
    pSettings->endGroup();
    //---------------------------------------------------------------------------------------------
    pSettings->beginGroup("/Z_MeMe");
    QString strZ_M1M2_Dn = pSettings->value("/Z_M1M2_Dn","0.1").toString();
    QString strZ_M2M3_Dn = pSettings->value("/Z_M2M3_Dn","0.1").toString();
    QString strZ_M3M4_Dn = pSettings->value("/Z_M3M4_Dn","0.1").toString();
    QString strZ_M1M4_Dn = pSettings->value("/Z_M1M4_Dn","0.1").toString();
    pLocalSettingsWin->slotSetZ_M1M2_Dn(strZ_M1M2_Dn);
    pLocalSettingsWin->slotSetZ_M2M3_Dn(strZ_M2M3_Dn);
    pLocalSettingsWin->slotSetZ_M3M4_Dn(strZ_M3M4_Dn);
    pLocalSettingsWin->slotSetZ_M1M4_Dn(strZ_M1M4_Dn);

    QString strZ_M1M2_Up = pSettings->value("/Z_M1M2_Up","2.5").toString();
    QString strZ_M2M3_Up = pSettings->value("/Z_M2M3_Up","2.5").toString();
    QString strZ_M3M4_Up = pSettings->value("/Z_M3M4_Up","2.5").toString();
    QString strZ_M1M4_Up = pSettings->value("/Z_M1M4_Up","7.5").toString();
    pLocalSettingsWin->slotSetZ_M1M2_Up(strZ_M1M2_Up);
    pLocalSettingsWin->slotSetZ_M2M3_Up(strZ_M2M3_Up);
    pLocalSettingsWin->slotSetZ_M3M4_Up(strZ_M3M4_Up);
    pLocalSettingsWin->slotSetZ_M1M4_Up(strZ_M1M4_Up);
    pSettings->endGroup();
    //---------------------------------------------------------------------------------------------
    pSettings->beginGroup("/Mean");
    QString strMean1_05_Dn = pSettings->value("/Mean1_05_Dn","0.01").toString();
    QString strMean1_09_Dn = pSettings->value("/Mean1_09_Dn","0.01").toString();
    QString strMean2_06_Dn = pSettings->value("/Mean2_06_Dn","0.01").toString();
    QString strMean2_09_Dn = pSettings->value("/Mean2_09_Dn","0.01").toString();
    QString strMean3_06_Dn = pSettings->value("/Mean3_06_Dn","0.01").toString();
    QString strMean3_09_Dn = pSettings->value("/Mean3_09_Dn","0.01").toString();
    QString strMean4_06_Dn = pSettings->value("/Mean4_06_Dn","0.01").toString();
    QString strMean4_09_Dn = pSettings->value("/Mean4_09_Dn","0.01").toString();
    pLocalSettingsWin->slotSetMean1_05_Dn(strMean1_05_Dn);
    pLocalSettingsWin->slotSetMean1_09_Dn(strMean1_09_Dn);
    pLocalSettingsWin->slotSetMean2_06_Dn(strMean2_06_Dn);
    pLocalSettingsWin->slotSetMean2_06_Dn(strMean2_09_Dn);
    pLocalSettingsWin->slotSetMean3_06_Dn(strMean3_06_Dn);
    pLocalSettingsWin->slotSetMean3_06_Dn(strMean3_09_Dn);
    pLocalSettingsWin->slotSetMean4_06_Dn(strMean4_06_Dn);
    pLocalSettingsWin->slotSetMean4_06_Dn(strMean4_09_Dn);

    QString strMean1_05_Up = pSettings->value("/Mean1_05_Up","0.1").toString();
    QString strMean1_09_Up = pSettings->value("/Mean1_09_Up","0.1").toString();
    QString strMean2_06_Up = pSettings->value("/Mean2_06_Up","0.1").toString();
    QString strMean2_09_Up = pSettings->value("/Mean2_09_Up","0.1").toString();
    QString strMean3_06_Up = pSettings->value("/Mean3_06_Up","0.1").toString();
    QString strMean3_09_Up = pSettings->value("/Mean3_09_Up","0.1").toString();
    QString strMean4_06_Up = pSettings->value("/Mean4_06_Up","0.1").toString();
    QString strMean4_09_Up = pSettings->value("/Mean4_09_Up","0.1").toString();
    pLocalSettingsWin->slotSetMean1_05_Up(strMean1_05_Up);
    pLocalSettingsWin->slotSetMean1_09_Up(strMean1_09_Up);
    pLocalSettingsWin->slotSetMean2_06_Up(strMean2_06_Up);
    pLocalSettingsWin->slotSetMean2_09_Up(strMean2_09_Up);
    pLocalSettingsWin->slotSetMean3_06_Up(strMean3_06_Up);
    pLocalSettingsWin->slotSetMean3_09_Up(strMean3_09_Up);
    pLocalSettingsWin->slotSetMean4_06_Up(strMean4_06_Up);
    pLocalSettingsWin->slotSetMean4_09_Up(strMean4_09_Up);
    pSettings->endGroup();
    //---------------------------------------------------------------------------------------------
    pSettings->beginGroup("/VDP");
    QString strVDPnWell_Dn = pSettings->value("/VDPnWell_Dn","0.1").toString();
    QString strVDPpWell_Dn = pSettings->value("/VDPpWell_Dn","0.1").toString();
    QString strVDPn_Dn = pSettings->value("/VDPn_Dn","0.1").toString();
    QString strVDPp_Dn = pSettings->value("/VDPp_Dn","0.1").toString();
    QString strVDPnSi_Dn = pSettings->value("/VDPnSi_Dn","0.1").toString();
    QString strVDPpSi_Dn = pSettings->value("/VDPpSi_Dn","0.1").toString();
    pLocalSettingsWin->slotSetVDPnWell_Dn(strVDPnWell_Dn);
    pLocalSettingsWin->slotSetVDPpWell_Dn(strVDPpWell_Dn);
    pLocalSettingsWin->slotSetVDPn_Dn(strVDPn_Dn);
    pLocalSettingsWin->slotSetVDPp_Dn(strVDPp_Dn);
    pLocalSettingsWin->slotSetVDPnSi_Dn(strVDPnSi_Dn);
    pLocalSettingsWin->slotSetVDPpSi_Dn(strVDPpSi_Dn);

    QString strVDPnWell_Up = pSettings->value("/VDPnWell_Up","4000.0").toString();
    QString strVDPpWell_Up = pSettings->value("/VDPpWell_Up","5600.0").toString();
    QString strVDPn_Up = pSettings->value("/VDPn_Up","50.0").toString();
    QString strVDPp_Up = pSettings->value("/VDPp_Up","100.0").toString();
    QString strVDPnSi_Up = pSettings->value("/VDPnSi_Up","300.0").toString();
    QString strVDPpSi_Up = pSettings->value("/VDPpSi_Up","200.0").toString();
    pLocalSettingsWin->slotSetVDPnWell_Up(strVDPnWell_Up);
    pLocalSettingsWin->slotSetVDPpWell_Up(strVDPpWell_Up);
    pLocalSettingsWin->slotSetVDPn_Up(strVDPn_Up);
    pLocalSettingsWin->slotSetVDPp_Up(strVDPp_Up);
    pLocalSettingsWin->slotSetVDPnSi_Up(strVDPnSi_Up);
    pLocalSettingsWin->slotSetVDPpSi_Up(strVDPpSi_Up);
    pSettings->endGroup();
    //---------------------------------------------------------------------------------------------
    pSettings->beginGroup("/TrAn");
    QString strAn_Vt_Dn = pSettings->value("/An_Vt_Dn","0.55").toString();
    QString strAn_VtRevers_Dn = pSettings->value("/An_VtRevers_Dn","0.1").toString();
    QString strAn_Be_Dn = pSettings->value("/An_Be_Dn","2.2e-4").toString();
    QString strAn_Vbr_Dn = pSettings->value("/An_Vbr_Dn","8.0").toString();
    QString strAn_Gleak_Dn = pSettings->value("/An_Gleak_Dn","0.0").toString();
    QString strAn_DSleak_Dn = pSettings->value("/An_DSleak_Dn","0.0").toString();
    QString strAn_DSw_leak_Dn = pSettings->value("/An_DSw_leak_Dn","0.0").toString();
    QString strAn_DScurrent_Dn = pSettings->value("/An_DScurrent_Dn","4.2e-4").toString();
    QString strAn_DSw_driver_Dn = pSettings->value("/An_DSw_driver_Dn","4.2e-4").toString();
    pLocalSettingsWin->slotSetAn_Vt_Dn(strAn_Vt_Dn);
    pLocalSettingsWin->slotSetAn_VtRevers_Dn(strAn_VtRevers_Dn);
    pLocalSettingsWin->slotSetAn_Be_Dn(strAn_Be_Dn);
    pLocalSettingsWin->slotSetAn_Vbr_Dn(strAn_Vbr_Dn);
    pLocalSettingsWin->slotSetAn_Gleak_Dn(strAn_Gleak_Dn);
    pLocalSettingsWin->slotSetAn_DSleak_Dn(strAn_DSleak_Dn);
    pLocalSettingsWin->slotSetAn_DSw_leak_Dn(strAn_DSw_leak_Dn);
    pLocalSettingsWin->slotSetAn_DScurrent_Dn(strAn_DScurrent_Dn);
    pLocalSettingsWin->slotSetAn_DSw_driver_Dn(strAn_DSw_driver_Dn);

    QString strAn_Vt_Up = pSettings->value("/An_Vt_Up","0.70").toString();
    QString strAn_VtRevers_Up = pSettings->value("/An_VtRevers_Up","30.0").toString();
    QString strAn_Be_Up = pSettings->value("/An_Be_Up","2.6e-4").toString();
    QString strAn_Vbr_Up = pSettings->value("/An_Vbr_Up","30.0").toString();
    QString strAn_Gleak_Up = pSettings->value("/An_Gleak_Up","1.0e-12.0").toString();
    QString strAn_DSleak_Up = pSettings->value("/An_DSleak_Up","6.0e-12").toString();
    QString strAn_DSw_leak_Up = pSettings->value("/An_DSw_leak_Up","6.0e-12").toString();
    QString strAn_DScurrent_Up = pSettings->value("/An_DScurrent_Up","5.2e-4").toString();
    QString strAn_DSw_driver_Up = pSettings->value("/An_DSw_driver_Up","5.2e-4").toString();
    pLocalSettingsWin->slotSetAn_Vt_Up(strAn_Vt_Up);
    pLocalSettingsWin->slotSetAn_VtRevers_Up(strAn_VtRevers_Up);
    pLocalSettingsWin->slotSetAn_Be_Up(strAn_Be_Up);
    pLocalSettingsWin->slotSetAn_Vbr_Up(strAn_Vbr_Up);
    pLocalSettingsWin->slotSetAn_Gleak_Up(strAn_Gleak_Up);
    pLocalSettingsWin->slotSetAn_DSleak_Up(strAn_DSleak_Up);
    pLocalSettingsWin->slotSetAn_DSw_leak_Up(strAn_DSw_leak_Up);
    pLocalSettingsWin->slotSetAn_DScurrent_Up(strAn_DScurrent_Up);
    pLocalSettingsWin->slotSetAn_DSw_driver_Up(strAn_DSw_driver_Up);
    pSettings->endGroup();
    //---------------------------------------------------------------------------------------------
    pSettings->beginGroup("/TrAp");
    QString strAp_Vt_Dn = pSettings->value("/Ap_Vt_Dn","-0.50").toString();
    QString strAp_VtRevers_Dn = pSettings->value("/Ap_VtRevers_Dn","-30.0").toString();
    QString strAp_Be_Dn = pSettings->value("/Ap_Be_Dn","4.58e-5").toString();
    QString strAp_Vbr_Dn = pSettings->value("/Ap_Vbr_Dn","-30.0").toString();
    QString strAp_Gleak_Dn = pSettings->value("/Ap_Gleak_Dn","-1.0e-12").toString();
    QString strAp_DSleak_Dn = pSettings->value("/Ap_DSleak_Dn","-10.0e-12").toString();
    QString strAp_DSw_leak_Dn = pSettings->value("/Ap_DSw_leak_Dn","-10.0e-12").toString();
    QString strAp_DScurrent_Dn = pSettings->value("/Ap_DScurrent_Dn","-3.3e-4").toString();
    QString strAp_DSw_driver_Dn = pSettings->value("/Ap_DSw_driver_Dn","-3.3e-4").toString();
    pLocalSettingsWin->slotSetAp_Vt_Dn(strAp_Vt_Dn);
    pLocalSettingsWin->slotSetAp_VtRevers_Dn(strAp_VtRevers_Dn);
    pLocalSettingsWin->slotSetAp_Be_Dn(strAp_Be_Dn);
    pLocalSettingsWin->slotSetAp_Vbr_Dn(strAp_Vbr_Dn);
    pLocalSettingsWin->slotSetAp_Gleak_Dn(strAp_Gleak_Dn);
    pLocalSettingsWin->slotSetAp_DSleak_Dn(strAp_DSleak_Dn);
    pLocalSettingsWin->slotSetAp_DSw_leak_Dn(strAp_DSw_leak_Dn);
    pLocalSettingsWin->slotSetAp_DScurrent_Dn(strAp_DScurrent_Dn);
    pLocalSettingsWin->slotSetAp_DSw_driver_Dn(strAp_DSw_driver_Dn);

    QString strAp_Vt_Up = pSettings->value("/Ap_Vt_Up","-0.70").toString();
    QString strAp_VtRevers_Up = pSettings->value("/Ap_VtRevers_Up","-0.1").toString();
    QString strAp_Be_Up = pSettings->value("/Ap_Be_Up","6.21e-5").toString();
    QString strAp_Vbr_Up = pSettings->value("/Ap_Vbr_Up","-8.0").toString();
    QString strAp_Gleak_Up = pSettings->value("/Ap_Gleak_Up","0.0").toString();
    QString strAp_DSleak_Up = pSettings->value("/Ap_DSleak_Up","0.0").toString();
    QString strAp_DSw_leak_Up = pSettings->value("/Ap_DSw_leak_Up","0.0").toString();
    QString strAp_DScurrent_Up = pSettings->value("/Ap_DScurrent_Up","-2.3e-4").toString();
    QString strAp_DSw_driver_Up = pSettings->value("/Ap_DSw_driver_Up","-2.3e-4").toString();
    pLocalSettingsWin->slotSetAp_Vt_Up(strAp_Vt_Up);
    pLocalSettingsWin->slotSetAp_VtRevers_Up(strAp_VtRevers_Up);
    pLocalSettingsWin->slotSetAp_Be_Up(strAp_Be_Up);
    pLocalSettingsWin->slotSetAp_Vbr_Up(strAp_Vbr_Up);
    pLocalSettingsWin->slotSetAp_Gleak_Up(strAp_Gleak_Up);
    pLocalSettingsWin->slotSetAp_DSleak_Up(strAp_DSleak_Up);
    pLocalSettingsWin->slotSetAp_DSw_leak_Up(strAp_DSw_leak_Up);
    pLocalSettingsWin->slotSetAp_DScurrent_Up(strAp_DScurrent_Up);
    pLocalSettingsWin->slotSetAp_DSw_driver_Up(strAp_DSw_driver_Up);
    pSettings->endGroup();
    //---------------------------------------------------------------------------------------------
    pSettings->beginGroup("/TrRn");
    QString strRn_Vt_Dn = pSettings->value("/Rn_Vt_Dn","0.55").toString();
    QString strRn_VtRevers_Dn = pSettings->value("/Rn_VtRevers_Dn","0.1").toString();
    QString strRn_Be_Dn = pSettings->value("/Rn_Be_Dn","2.2e-4").toString();
    QString strRn_Vbr_Dn = pSettings->value("/Rn_Vbr_Dn","8.0").toString();
    QString strRn_Gleak_Dn = pSettings->value("/Rn_Gleak_Dn","0.0").toString();
    QString strRn_DSleak_Dn = pSettings->value("/Rn_DSleak_Dn","0.0").toString();
    QString strRn_DSw_leak_Dn = pSettings->value("/Rn_DSw_leak_Dn","0.0").toString();
    QString strRn_DScurrent_Dn = pSettings->value("/Rn_DScurrent_Dn","4.2e-4").toString();
    QString strRn_DSw_driver_Dn = pSettings->value("/Rn_DSw_driver_Dn","4.2e-4").toString();
    pLocalSettingsWin->slotSetRn_Vt_Dn(strRn_Vt_Dn);
    pLocalSettingsWin->slotSetRn_VtRevers_Dn(strRn_VtRevers_Dn);
    pLocalSettingsWin->slotSetRn_Be_Dn(strRn_Be_Dn);
    pLocalSettingsWin->slotSetRn_Vbr_Dn(strRn_Vbr_Dn);
    pLocalSettingsWin->slotSetRn_Gleak_Dn(strRn_Gleak_Dn);
    pLocalSettingsWin->slotSetRn_DSleak_Dn(strRn_DSleak_Dn);
    pLocalSettingsWin->slotSetRn_DSw_leak_Dn(strRn_DSw_leak_Dn);
    pLocalSettingsWin->slotSetRn_DScurrent_Dn(strRn_DScurrent_Dn);
    pLocalSettingsWin->slotSetRn_DSw_driver_Dn(strRn_DSw_driver_Dn);

    QString strRn_Vt_Up = pSettings->value("/Rn_Vt_Up","0.70").toString();
    QString strRn_VtRevers_Up = pSettings->value("/Rn_VtRevers_Up","30.0").toString();
    QString strRn_Be_Up = pSettings->value("/Rn_Be_Up","2.6e-4").toString();
    QString strRn_Vbr_Up = pSettings->value("/Rn_Vbr_Up","30.0").toString();
    QString strRn_Gleak_Up = pSettings->value("/Rn_Gleak_Up","1.0e-12.0").toString();
    QString strRn_DSleak_Up = pSettings->value("/Rn_DSleak_Up","6.0e-12").toString();
    QString strRn_DSw_leak_Up = pSettings->value("/Rn_DSw_leak_Up","6.0e-12").toString();
    QString strRn_DScurrent_Up = pSettings->value("/Rn_DScurrent_Up","5.2e-4").toString();
    QString strRn_DSw_driver_Up = pSettings->value("/Rn_DSw_driver_Up","5.2e-4").toString();
    pLocalSettingsWin->slotSetRn_Vt_Up(strRn_Vt_Up);
    pLocalSettingsWin->slotSetRn_VtRevers_Up(strRn_VtRevers_Up);
    pLocalSettingsWin->slotSetRn_Be_Up(strRn_Be_Up);
    pLocalSettingsWin->slotSetRn_Vbr_Up(strRn_Vbr_Up);
    pLocalSettingsWin->slotSetRn_Gleak_Up(strRn_Gleak_Up);
    pLocalSettingsWin->slotSetRn_DSleak_Up(strRn_DSleak_Up);
    pLocalSettingsWin->slotSetRn_DSw_leak_Up(strRn_DSw_leak_Up);
    pLocalSettingsWin->slotSetRn_DScurrent_Up(strRn_DScurrent_Up);
    pLocalSettingsWin->slotSetRn_DSw_driver_Up(strRn_DSw_driver_Up);
    pSettings->endGroup();
    //---------------------------------------------------------------------------------------------
    pSettings->beginGroup("/TrRp");
    QString strRp_Vt_Dn = pSettings->value("/Rp_Vt_Dn","-0.50").toString();
    QString strRp_VtRevers_Dn = pSettings->value("/Rp_VtRevers_Dn","-30.0").toString();
    QString strRp_Be_Dn = pSettings->value("/Rp_Be_Dn","4.58e-5").toString();
    QString strRp_Vbr_Dn = pSettings->value("/Rp_Vbr_Dn","-30.0").toString();
    QString strRp_Gleak_Dn = pSettings->value("/Rp_Gleak_Dn","-1.0e-12").toString();
    QString strRp_DSleak_Dn = pSettings->value("/Rp_DSleak_Dn","-10.0e-12").toString();
    QString strRp_DSw_leak_Dn = pSettings->value("/Rp_DSw_leak_Dn","-10.0e-12").toString();
    QString strRp_DScurrent_Dn = pSettings->value("/Rp_DScurrent_Dn","-3.3e-4").toString();
    QString strRp_DSw_driver_Dn = pSettings->value("/Rp_DSw_driver_Dn","-3.3e-4").toString();
    pLocalSettingsWin->slotSetRp_Vt_Dn(strRp_Vt_Dn);
    pLocalSettingsWin->slotSetRp_VtRevers_Dn(strRp_VtRevers_Dn);
    pLocalSettingsWin->slotSetRp_Be_Dn(strRp_Be_Dn);
    pLocalSettingsWin->slotSetRp_Vbr_Dn(strRp_Vbr_Dn);
    pLocalSettingsWin->slotSetRp_Gleak_Dn(strRp_Gleak_Dn);
    pLocalSettingsWin->slotSetRp_DSleak_Dn(strRp_DSleak_Dn);
    pLocalSettingsWin->slotSetRp_DSw_leak_Dn(strRp_DSw_leak_Dn);
    pLocalSettingsWin->slotSetRp_DScurrent_Dn(strRp_DScurrent_Dn);
    pLocalSettingsWin->slotSetRp_DSw_driver_Dn(strRp_DSw_driver_Dn);

    QString strRp_Vt_Up = pSettings->value("/Rp_Vt_Up","-0.70").toString();
    QString strRp_VtRevers_Up = pSettings->value("/Rp_VtRevers_Up","-0.1").toString();
    QString strRp_Be_Up = pSettings->value("/Rp_Be_Up","6.21e-5").toString();
    QString strRp_Vbr_Up = pSettings->value("/Rp_Vbr_Up","-8.0").toString();
    QString strRp_Gleak_Up = pSettings->value("/Rp_Gleak_Up","0.0").toString();
    QString strRp_DSleak_Up = pSettings->value("/Rp_DSleak_Up","0.0").toString();
    QString strRp_DSw_leak_Up = pSettings->value("/Rp_DSw_leak_Up","0.0").toString();
    QString strRp_DScurrent_Up = pSettings->value("/Rp_DScurrent_Up","-2.3e-4").toString();
    QString strRp_DSw_driver_Up = pSettings->value("/Rp_DSw_driver_Up","-2.3e-4").toString();
    pLocalSettingsWin->slotSetRp_Vt_Up(strRp_Vt_Up);
    pLocalSettingsWin->slotSetRp_VtRevers_Up(strRp_VtRevers_Up);
    pLocalSettingsWin->slotSetRp_Be_Up(strRp_Be_Up);
    pLocalSettingsWin->slotSetRp_Vbr_Up(strRp_Vbr_Up);
    pLocalSettingsWin->slotSetRp_Gleak_Up(strRp_Gleak_Up);
    pLocalSettingsWin->slotSetRp_DSleak_Up(strRp_DSleak_Up);
    pLocalSettingsWin->slotSetRp_DSw_leak_Up(strRp_DSw_leak_Up);
    pLocalSettingsWin->slotSetRp_DScurrent_Up(strRp_DScurrent_Up);
    pLocalSettingsWin->slotSetRp_DSw_driver_Up(strRp_DSw_driver_Up);
    pSettings->endGroup();
    //---------------------------------------------------------------------------------------------
    pSettings->beginGroup("/TrHn");
    QString strHn_Vt_Dn = pSettings->value("/Hn_Vt_Dn","0.55").toString();
    QString strHn_VtRevers_Dn = pSettings->value("/Hn_VtRevers_Dn","0.1").toString();
    QString strHn_Be_Dn = pSettings->value("/Hn_Be_Dn","2.2e-4").toString();
    QString strHn_Vbr_Dn = pSettings->value("/Hn_Vbr_Dn","8.0").toString();
    QString strHn_Gleak_Dn = pSettings->value("/Hn_Gleak_Dn","0.0").toString();
    QString strHn_DSleak_Dn = pSettings->value("/Hn_DSleak_Dn","0.0").toString();
    QString strHn_DSw_leak_Dn = pSettings->value("/Hn_DSw_leak_Dn","0.0").toString();
    QString strHn_DScurrent_Dn = pSettings->value("/Hn_DScurrent_Dn","4.2e-4").toString();
    QString strHn_DSw_driver_Dn = pSettings->value("/Hn_DSw_driver_Dn","4.2e-4").toString();
    pLocalSettingsWin->slotSetHn_Vt_Dn(strHn_Vt_Dn);
    pLocalSettingsWin->slotSetHn_VtRevers_Dn(strHn_VtRevers_Dn);
    pLocalSettingsWin->slotSetHn_Be_Dn(strHn_Be_Dn);
    pLocalSettingsWin->slotSetHn_Vbr_Dn(strHn_Vbr_Dn);
    pLocalSettingsWin->slotSetHn_Gleak_Dn(strHn_Gleak_Dn);
    pLocalSettingsWin->slotSetHn_DSleak_Dn(strHn_DSleak_Dn);
    pLocalSettingsWin->slotSetHn_DSw_leak_Dn(strHn_DSw_leak_Dn);
    pLocalSettingsWin->slotSetHn_DScurrent_Dn(strHn_DScurrent_Dn);
    pLocalSettingsWin->slotSetHn_DSw_driver_Dn(strHn_DSw_driver_Dn);

    QString strHn_Vt_Up = pSettings->value("/Hn_Vt_Up","0.70").toString();
    QString strHn_VtRevers_Up = pSettings->value("/Hn_VtRevers_Up","30.0").toString();
    QString strHn_Be_Up = pSettings->value("/Hn_Be_Up","2.6e-4").toString();
    QString strHn_Vbr_Up = pSettings->value("/Hn_Vbr_Up","30.0").toString();
    QString strHn_Gleak_Up = pSettings->value("/Hn_Gleak_Up","1.0e-12.0").toString();
    QString strHn_DSleak_Up = pSettings->value("/Hn_DSleak_Up","6.0e-12").toString();
    QString strHn_DSw_leak_Up = pSettings->value("/Hn_DSw_leak_Up","6.0e-12").toString();
    QString strHn_DScurrent_Up = pSettings->value("/Hn_DScurrent_Up","5.2e-4").toString();
    QString strHn_DSw_driver_Up = pSettings->value("/Hn_DSw_driver_Up","5.2e-4").toString();
    pLocalSettingsWin->slotSetHn_Vt_Up(strHn_Vt_Up);
    pLocalSettingsWin->slotSetHn_VtRevers_Up(strHn_VtRevers_Up);
    pLocalSettingsWin->slotSetHn_Be_Up(strHn_Be_Up);
    pLocalSettingsWin->slotSetHn_Vbr_Up(strHn_Vbr_Up);
    pLocalSettingsWin->slotSetHn_Gleak_Up(strHn_Gleak_Up);
    pLocalSettingsWin->slotSetHn_DSleak_Up(strHn_DSleak_Up);
    pLocalSettingsWin->slotSetHn_DSw_leak_Up(strHn_DSw_leak_Up);
    pLocalSettingsWin->slotSetHn_DScurrent_Up(strHn_DScurrent_Up);
    pLocalSettingsWin->slotSetHn_DSw_driver_Up(strHn_DSw_driver_Up);
    pSettings->endGroup();
    //---------------------------------------------------------------------------------------------
    pSettings->beginGroup("/TrHp");
    QString strHp_Vt_Dn = pSettings->value("/Hp_Vt_Dn","-0.50").toString();
    QString strHp_VtRevers_Dn = pSettings->value("/Hp_VtRevers_Dn","-30.0").toString();
    QString strHp_Be_Dn = pSettings->value("/Hp_Be_Dn","4.58e-5").toString();
    QString strHp_Vbr_Dn = pSettings->value("/Hp_Vbr_Dn","-30.0").toString();
    QString strHp_Gleak_Dn = pSettings->value("/Hp_Gleak_Dn","-1.0e-12").toString();
    QString strHp_DSleak_Dn = pSettings->value("/Hp_DSleak_Dn","-10.0e-12").toString();
    QString strHp_DSw_leak_Dn = pSettings->value("/Hp_DSw_leak_Dn","-10.0e-12").toString();
    QString strHp_DScurrent_Dn = pSettings->value("/Hp_DScurrent_Dn","-3.3e-4").toString();
    QString strHp_DSw_driver_Dn = pSettings->value("/Hp_DSw_driver_Dn","-3.3e-4").toString();
    pLocalSettingsWin->slotSetHp_Vt_Dn(strHp_Vt_Dn);
    pLocalSettingsWin->slotSetHp_VtRevers_Dn(strHp_VtRevers_Dn);
    pLocalSettingsWin->slotSetHp_Be_Dn(strHp_Be_Dn);
    pLocalSettingsWin->slotSetHp_Vbr_Dn(strHp_Vbr_Dn);
    pLocalSettingsWin->slotSetHp_Gleak_Dn(strHp_Gleak_Dn);
    pLocalSettingsWin->slotSetHp_DSleak_Dn(strHp_DSleak_Dn);
    pLocalSettingsWin->slotSetHp_DSw_leak_Dn(strHp_DSw_leak_Dn);
    pLocalSettingsWin->slotSetHp_DScurrent_Dn(strHp_DScurrent_Dn);
    pLocalSettingsWin->slotSetHp_DSw_driver_Dn(strHp_DSw_driver_Dn);

    QString strHp_Vt_Up = pSettings->value("/Hp_Vt_Up","-0.70").toString();
    QString strHp_VtRevers_Up = pSettings->value("/Hp_VtRevers_Up","-0.1").toString();
    QString strHp_Be_Up = pSettings->value("/Hp_Be_Up","6.21e-5").toString();
    QString strHp_Vbr_Up = pSettings->value("/Hp_Vbr_Up","-8.0").toString();
    QString strHp_Gleak_Up = pSettings->value("/Hp_Gleak_Up","0.0").toString();
    QString strHp_DSleak_Up = pSettings->value("/Hp_DSleak_Up","0.0").toString();
    QString strHp_DSw_leak_Up = pSettings->value("/Hp_DSw_leak_Up","0.0").toString();
    QString strHp_DScurrent_Up = pSettings->value("/Hp_DScurrent_Up","-2.3e-4").toString();
    QString strHp_DSw_driver_Up = pSettings->value("/Hp_DSw_driver_Up","-2.3e-4").toString();
    pLocalSettingsWin->slotSetHp_Vt_Up(strHp_Vt_Up);
    pLocalSettingsWin->slotSetHp_VtRevers_Up(strHp_VtRevers_Up);
    pLocalSettingsWin->slotSetHp_Be_Up(strHp_Be_Up);
    pLocalSettingsWin->slotSetHp_Vbr_Up(strHp_Vbr_Up);
    pLocalSettingsWin->slotSetHp_Gleak_Up(strHp_Gleak_Up);
    pLocalSettingsWin->slotSetHp_DSleak_Up(strHp_DSleak_Up);
    pLocalSettingsWin->slotSetHp_DSw_leak_Up(strHp_DSw_leak_Up);
    pLocalSettingsWin->slotSetHp_DScurrent_Up(strHp_DScurrent_Up);
    pLocalSettingsWin->slotSetHp_DSw_driver_Up(strHp_DSw_driver_Up);
    pSettings->endGroup();

    pSettings->endGroup();//end of /Settings Group

}

//поиск в реестре нормы выбранного тестового элемента и ее установка в переменные
void SystemSettings::findTestElemNorm(const QString& testName,
                                      double& criterionDn, double& criterionUp,
                                      ValuePrefix valuePrefix)
{
    QString strDn{};
    QString strUp{};
    //--------------------------------------------------------------------------------------------------
    //кельвины M1-Si
    QString KLV_nM1 = "KLV_nM1", KLVnM1 = "KLVnM1";
    QString KLV_pM1 = "KLV_pM1", KLVpM1 = "KLVpM1";
    QString KLV_nSiM1 = "KLV_nSiM1", KLVnSiM1 = "KLVnSiM1";
    QString KLV_pSiM1 = "KLV_pSiM1", KLVpSiM1 = "KLVpSiM1";
    QString KLV_SiM1 = "KLV_SiM1", KLVSiM1 = "KLVSiM1";
    if(testName.contains(KLV_nM1) || testName.contains(KLVnM1))
        readTestElemNorms("/KLVs_SIL", "/KLVnM1", strDn, strUp);
    else if(testName.contains(KLV_pM1) || testName.contains(KLVpM1))
        readTestElemNorms("/KLVs_SIL", "/KLVpM1", strDn, strUp);
    else if(testName.contains(KLV_nSiM1) || testName.contains(KLVnSiM1))
        readTestElemNorms("/KLVs_SIL", "/KLVnSiM1", strDn, strUp);
    else if(testName.contains(KLV_pSiM1) || testName.contains(KLVpSiM1))
        readTestElemNorms("/KLVs_SIL", "/KLVpSiM1", strDn, strUp);
    else if(testName.contains(KLV_SiM1) || testName.contains(KLVSiM1))
        readTestElemNorms("/KLVs_SIL", "/KLVSiM1", strDn, strUp);
    //--------------------------------------------------------------------------------------------------
    //цепочки контактов M1-Si
    QString dZnM1 = "dZnM1",        dZ_nM1 = "dZ_nM1";
    QString dZpM1 = "dZpM1",        dZ_pM1 = "dZ_pM1";
    QString dZnSiM1 = "dZnSiM1",    dZ_nSiM1 = "dZ_nSiM1";
    QString dZpSiM1 = "dZpSiM1",    dZ_pSiM1 = "dZ_pSiM1";
    QString dZSiM1 = "dZSiM1",      dZ_SiM1 = "dZ_SiM1";

    if(testName.contains(dZnM1) || testName.contains(dZ_nM1))
        readTestElemNorms("/Zs_SIL", "/ZnM1", strDn, strUp);
    else if(testName.contains(dZpM1) || testName.contains(dZ_pM1))
        readTestElemNorms("/Zs_SIL", "/ZpM1", strDn, strUp);
    else if(testName.contains(dZnSiM1) || testName.contains(dZ_nSiM1))
        readTestElemNorms("/Zs_SIL", "/ZnSiM1", strDn, strUp);
    else if(testName.contains(dZpSiM1) || testName.contains(dZ_pSiM1))
        readTestElemNorms("/Zs_SIL", "/ZpSiM1", strDn, strUp);
    else if(testName.contains(dZSiM1) || testName.contains(dZ_SiM1))
        readTestElemNorms("/Zs_SIL", "/ZSiM1", strDn, strUp);
    //--------------------------------------------------------------------------------------------------
    //силицидированные резисторы
    QString RZnTiSi = "RZnTiSi";
    QString RZpTiSi = "RZpTiSi";
    QString RZnSiTiSi = "RZnSiTiSi";
    QString RZpSiTiSi = "RZpSiTiSi";
    QString RZSiTiSi = "RZSiTiSi";
    //--------------------------------------------------------------------------------------------------
    //силицидированные резисторы 09
    QString w09 = "09";

    if(testName.contains(RZnTiSi) && testName.contains(w09))
        readTestElemNorms("/RZ09_SIL", "/RZnTiSi09", strDn, strUp);
    else if(testName.contains(RZpTiSi) && testName.contains(w09))
        readTestElemNorms("/RZ09_SIL", "/RZpTiSi09", strDn, strUp);
    else if(testName.contains(RZnSiTiSi) && testName.contains(w09))
        readTestElemNorms("/RZ09_SIL", "/RZnSiTiSi09", strDn, strUp);
    else if(testName.contains(RZpSiTiSi) && testName.contains(w09))
        readTestElemNorms("/RZ09_SIL", "/RZpSiTiSi09", strDn, strUp);
    else if(testName.contains(RZSiTiSi) && testName.contains(w09))
        readTestElemNorms("/RZ09_SIL", "/RZSiTiSi09", strDn, strUp);
    //--------------------------------------------------------------------------------------------------
    //силицидированные резисторы 05
    QString w05 = "05";

    if(testName.contains(RZnTiSi) && testName.contains(w05))
        readTestElemNorms("/RZ05_SIL", "/RZnTiSi05", strDn, strUp);
    else if(testName.contains(RZpTiSi) && testName.contains(w05))
        readTestElemNorms("/RZ05_SIL", "/RZpTiSi05", strDn, strUp);
    else if(testName.contains(RZnSiTiSi) && testName.contains(w05))
        readTestElemNorms("/RZ05_SIL", "/RZnSiTiSi05", strDn, strUp);
    else if(testName.contains(RZpSiTiSi) && testName.contains(w05))
        readTestElemNorms("/RZ05_SIL", "/RZpSiTiSi05", strDn, strUp);
    else if(testName.contains(RZSiTiSi) && testName.contains(w05))
        readTestElemNorms("/RZ05_SIL", "/RZSiTiSi05", strDn, strUp);
    //--------------------------------------------------------------------------------------------------
    //силицидированные резисторы 035
    QString w035 = "035";

    if(testName.contains(RZnTiSi) && testName.contains(w035))
        readTestElemNorms("/RZ035_SIL", "/RZnTiSi035", strDn, strUp);
    else if(testName.contains(RZpTiSi) && testName.contains(w035))
        readTestElemNorms("/RZ035_SIL", "/RZpTiSi035", strDn, strUp);
    else if(testName.contains(RZnSiTiSi) && testName.contains(w035))
        readTestElemNorms("/RZ035_SIL", "/RZnSiTiSi035", strDn, strUp);
    else if(testName.contains(RZpSiTiSi) && testName.contains(w035))
        readTestElemNorms("/RZ035_SIL", "/RZpSiTiSi035", strDn, strUp);
    else if(testName.contains(RZSiTiSi) && testName.contains(w035))
        readTestElemNorms("/RZ035_SIL", "/RZSiTiSi035", strDn, strUp);
    //--------------------------------------------------------------------------------------------------
    //силицидированные резисторы 06
    QString w06 = "06";

    if(testName.contains(RZnTiSi) && testName.contains(w06))
        readTestElemNorms("/RZ06_SIL", "/RZnTiSi06", strDn, strUp);
    else if(testName.contains(RZpTiSi) && testName.contains(w06))
        readTestElemNorms("/RZ06_SIL", "/RZpTiSi06", strDn, strUp);
    else if(testName.contains(RZnSiTiSi) && testName.contains(w06))
        readTestElemNorms("/RZ06_SIL", "/RZnSiTiSi06", strDn, strUp);
    else if(testName.contains(RZpSiTiSi) && testName.contains(w06))
        readTestElemNorms("/RZ06_SIL", "/RZpSiTiSi06", strDn, strUp);
    else if(testName.contains(RZSiTiSi) && testName.contains(w06))
        readTestElemNorms("/RZ06_SIL", "/RZSiTiSi06", strDn, strUp);
    //--------------------------------------------------------------------------------------------------
    //структуры Ван-дер-Пау
    QString VDP = "VDP";
    QString VDPnWell = "VDPnWell";
    QString VDPpWell = "VDPpWell";
    QString VDPn = "VDPn";
    QString VDPp = "VDPp";
    QString VDPnSi = "VDPnSi";
    QString VDPpSi = "VDPpSi";

    if(testName.contains(VDPnWell) || (testName.contains(VDP) && testName.contains("n")
                                       && (testName.contains("Well") || testName.contains("well"))))
        readTestElemNorms("/VDP", "/VDPnWell", strDn, strUp);
    else if(testName.contains(VDPpWell) || (testName.contains(VDP) && testName.contains("p") &&
                                            (testName.contains("Well") || testName.contains("well"))))
        readTestElemNorms("/VDP", "/VDPpWell", strDn, strUp);
    else if(testName.contains(VDPn) || (testName.contains(VDP) && testName.contains("n")))
        readTestElemNorms("/VDP", "/VDPn", strDn, strUp);
    else if(testName.contains(VDPp) || (testName.contains(VDP) && testName.contains("p")))
        readTestElemNorms("/VDP", "/VDPp", strDn, strUp);
    else if(testName.contains(VDPnSi) || (testName.contains(VDP) && testName.contains("n")
                                          && testName.contains("Si")))
        readTestElemNorms("/VDP", "/VDPnSi", strDn, strUp);
    else if(testName.contains(VDPpSi) || (testName.contains(VDP) && testName.contains("p")
                                          && testName.contains("Si")))
        readTestElemNorms("/VDP", "/VDPpSi", strDn, strUp);
    //--------------------------------------------------------------------------------------------------
    //ТРАНЗИСТОРЫ
    QString An("An"), Ap("Ap"), Rn("Rn"), Rp("Rp"), Hn("Hn"), Hp("Hp");
    QString Vt("Vt");
    //пороговые напряжения
    if(testName.contains(An) && testName.contains(Vt))
        readTestElemNorms("/TrAn", "/An_Vt", strDn, strUp);
    else if(testName.contains(Ap) && testName.contains(Vt))
        readTestElemNorms("/TrAp", "/Ap_Vt", strDn, strUp);
    else if(testName.contains(Rn) && testName.contains(Vt))
        readTestElemNorms("/TrRn", "/Rn_Vt", strDn, strUp);
    else if(testName.contains(Rp) && testName.contains(Vt))
        readTestElemNorms("/TrRp", "/Rp_Vt", strDn, strUp);
    else if(testName.contains(Hn) && testName.contains(Vt))
        readTestElemNorms("/TrHn", "/Hn_Vt", strDn, strUp);
    else if(testName.contains(Hp) && testName.contains(Vt))
        readTestElemNorms("/TrHp", "/Hp_Vt", strDn, strUp);

    //напряжения пробоя
    QString Vbr("Vbr");
    if(testName.contains(An) && testName.contains(Vbr))
        readTestElemNorms("/TrAn", "/An_Vbr", strDn, strUp);
    else if(testName.contains(Ap) && testName.contains(Vbr))
        readTestElemNorms("/TrAp", "/Ap_Vbr", strDn, strUp);
    else if(testName.contains(Rn) && testName.contains(Vbr))
        readTestElemNorms("/TrRn", "/Rn_Vbr", strDn, strUp);
    else if(testName.contains(Rp) && testName.contains(Vbr))
        readTestElemNorms("/TrRp", "/Rp_Vbr", strDn, strUp);
    else if(testName.contains(Hn) && testName.contains(Vbr))
        readTestElemNorms("/TrHn", "/Hn_Vbr", strDn, strUp);
    else if(testName.contains(Hp) && testName.contains(Vbr))
        readTestElemNorms("/TrHp", "/Hp_Vbr", strDn, strUp);

    //пороговые напряжения обратного транзистора
    QString revers("revers");
    if(testName.contains(An) && testName.contains(Vt) && testName.contains(revers))
        readTestElemNorms("/TrAn", "/An_VtRevers", strDn, strUp);
    else if(testName.contains(Ap) && testName.contains(Vt) && testName.contains(revers))
        readTestElemNorms("/TrAp", "/Ap_VtRevers", strDn, strUp);
    else if(testName.contains(Rn) && testName.contains(Vt) && testName.contains(revers))
        readTestElemNorms("/TrRn", "/Rn_VtRevers", strDn, strUp);
    else if(testName.contains(Rp) && testName.contains(Vt) && testName.contains(revers))
        readTestElemNorms("/TrRp", "/Rp_VtRevers", strDn, strUp);
    else if(testName.contains(Hn) && testName.contains(Vt) && testName.contains(revers))
        readTestElemNorms("/TrHn", "/Hn_VtRevers", strDn, strUp);
    else if(testName.contains(Hp) && testName.contains(Vt) && testName.contains(revers))
        readTestElemNorms("/TrHp", "/Hp_VtRevers", strDn, strUp);

    //крутизна
    QString Be("Be");
    if(testName.contains(An) && testName.contains(Be))
        readTestElemNorms("/TrAn", "/An_Be", strDn, strUp);
    else if(testName.contains(Ap) && testName.contains(Be))
        readTestElemNorms("/TrAp", "/Ap_Be", strDn, strUp);
    else if(testName.contains(Rn) && testName.contains(Be))
        readTestElemNorms("/TrRn", "/Rn_Be", strDn, strUp);
    else if(testName.contains(Rp) && testName.contains(Be))
        readTestElemNorms("/TrRp", "/Rp_Be", strDn, strUp);
    else if(testName.contains(Hn) && testName.contains(Be))
        readTestElemNorms("/TrHn", "/Hn_Be", strDn, strUp);
    else if(testName.contains(Hp) && testName.contains(Be))
        readTestElemNorms("/TrHp", "/Hp_Be", strDn, strUp);

    //ток утечки затвор абсолютный
    QString leak("leak"), w("w");
    QString Gleak("Gleak"), G("G");
    if(testName.contains(An) &&
            (testName.contains(Gleak) ||
             (testName.contains(G) && testName.contains(leak) && !testName.contains(w))))
        readTestElemNorms("/TrAn", "/An_Gleak", strDn, strUp);
    else if(testName.contains(Ap) &&
            (testName.contains(Gleak) ||
             (testName.contains(G) && testName.contains(leak) && !testName.contains(w))))
        readTestElemNorms("/TrAp", "/Ap_Gleak", strDn, strUp);
    else if(testName.contains(Rn) &&
            (testName.contains(Gleak) ||
             (testName.contains(G) && testName.contains(leak) && !testName.contains(w))))
        readTestElemNorms("/TrRn", "/Rn_Gleak", strDn, strUp);
    else if(testName.contains(Rp) &&
            (testName.contains(Gleak) ||
             (testName.contains(G) && testName.contains(leak) && !testName.contains(w))))
        readTestElemNorms("/TrRp", "/Rp_Gleak", strDn, strUp);
    else if(testName.contains(Hn) &&
            (testName.contains(Gleak) ||
             (testName.contains(G) && testName.contains(leak) && !testName.contains(w))))
        readTestElemNorms("/TrHn", "/Hn_Gleak", strDn, strUp);
    else if(testName.contains(Hp) &&
            (testName.contains(Gleak) ||
             (testName.contains(G) && testName.contains(leak) && !testName.contains(w))))
        readTestElemNorms("/TrHp", "/Hp_Gleak", strDn, strUp);

    //ток утечки сток-исток абсолютный
    QString DSleak("DSleak"), DS("DS");
    if(testName.contains(An) &&
            (testName.contains(DSleak) ||
             (testName.contains(DS) && testName.contains(leak) && !testName.contains(w))))
        readTestElemNorms("/TrAn", "/An_DSleak", strDn, strUp);
    else if(testName.contains(Ap) &&
            (testName.contains(DSleak) ||
             (testName.contains(DS) && testName.contains(leak) && !testName.contains(w))))
        readTestElemNorms("/TrAp", "/Ap_DSleak", strDn, strUp);
    else if(testName.contains(Rn) &&
            (testName.contains(DSleak) ||
             (testName.contains(DS) && testName.contains(leak) && !testName.contains(w))))
        readTestElemNorms("/TrRn", "/Rn_DSleak", strDn, strUp);
    else if(testName.contains(Rp) &&
            (testName.contains(DSleak) ||
             (testName.contains(DS) && testName.contains(leak) && !testName.contains(w))))
        readTestElemNorms("/TrRp", "/Rp_DSleak", strDn, strUp);
    else if(testName.contains(Hn) &&
            (testName.contains(DSleak) ||
             (testName.contains(DS) && testName.contains(leak) && !testName.contains(w))))
        readTestElemNorms("/TrHn", "/Hn_DSleak", strDn, strUp);
    else if(testName.contains(Hp) &&
            (testName.contains(DSleak) ||
             (testName.contains(DS) && testName.contains(leak) && !testName.contains(w))))
        readTestElemNorms("/TrHp", "/Hp_DSleak", strDn, strUp);

    //ток утечки сток/исток приведенный
    QString DSw_leak("DSw_leak");
    if(testName.contains(An) &&
            (testName.contains(DSw_leak) ||
             (testName.contains(DS) && testName.contains(leak) && testName.contains(w))))
        readTestElemNorms("/TrAn", "/An_DSw_leak", strDn, strUp);
    else if(testName.contains(Ap) &&
            (testName.contains(DSw_leak) ||
             (testName.contains(DS) && testName.contains(leak) && testName.contains(w))))
        readTestElemNorms("/TrAp", "/Ap_DSw_leak", strDn, strUp);
    else if(testName.contains(Rn) &&
            (testName.contains(DSw_leak) ||
             (testName.contains(DS) && testName.contains(leak) && testName.contains(w))))
        readTestElemNorms("/TrRn", "/Rn_DSw_leak", strDn, strUp);
    else if(testName.contains(Rp) &&
            (testName.contains(DSw_leak) ||
             (testName.contains(DS) && testName.contains(leak) && testName.contains(w))))
        readTestElemNorms("/TrRp", "/Rp_DSw_leak", strDn, strUp);
    else if(testName.contains(Hn) &&
            (testName.contains(DSw_leak) ||
             (testName.contains(DS) && testName.contains(leak) && testName.contains(w))))
        readTestElemNorms("/TrHn", "/Hn_DSw_leak", strDn, strUp);
    else if(testName.contains(Hp) &&
            (testName.contains(DSw_leak) ||
             (testName.contains(DS) && testName.contains(leak) && testName.contains(w))))
        readTestElemNorms("/TrHp", "/Hp_DSw_leak", strDn, strUp);

    //ток насыщения абсолютный
    QString DScurrent("DScurrent"), current("current");
    if(testName.contains(An) &&
            (testName.contains(DScurrent) ||
             (testName.contains(DS) && testName.contains(current) && !testName.contains(w))))
        readTestElemNorms("/TrAn", "/An_DScurrent", strDn, strUp);
    else if(testName.contains(Ap) &&
            (testName.contains(DScurrent) ||
             (testName.contains(DS) && testName.contains(current) && !testName.contains(w))))
        readTestElemNorms("/TrAp", "/Ap_DScurrent", strDn, strUp);
    else if(testName.contains(Rn) &&
            (testName.contains(DScurrent) ||
             (testName.contains(DS) && testName.contains(current) && !testName.contains(w))))
        readTestElemNorms("/TrRn", "/Rn_DScurrent", strDn, strUp);
    else if(testName.contains(Rp) &&
            (testName.contains(DScurrent) ||
             (testName.contains(DS) && testName.contains(current) && !testName.contains(w))))
        readTestElemNorms("/TrRp", "/Rp_DScurrent", strDn, strUp);
    else if(testName.contains(Hn) &&
            (testName.contains(DScurrent) ||
             (testName.contains(DS) && testName.contains(current) && !testName.contains(w))))
        readTestElemNorms("/TrHn", "/Hn_DScurrent", strDn, strUp);
    else if(testName.contains(Hp) &&
            (testName.contains(DScurrent) ||
             (testName.contains(DS) && testName.contains(current) && !testName.contains(w))))
        readTestElemNorms("/TrHp", "/Hp_DScurrent", strDn, strUp);

    QString DSw_driver("DSw_driver"), driver("driver");
    if(testName.contains(An) &&
            (testName.contains(DSw_driver) ||
             (testName.contains(DS) && testName.contains(driver) && testName.contains(w))))
        readTestElemNorms("/TrAn", "/An_DSw_driver", strDn, strUp);
    else if(testName.contains(Ap) &&
            (testName.contains(DSw_driver) ||
             (testName.contains(DS) && testName.contains(driver) && testName.contains(w))))
        readTestElemNorms("/TrAp", "/Ap_DSw_driver", strDn, strUp);
    else if(testName.contains(Rn) &&
            (testName.contains(DSw_driver) ||
             (testName.contains(DS) && testName.contains(driver) && testName.contains(w))))
        readTestElemNorms("/TrRn", "/Rn_DSw_driver", strDn, strUp);
    else if(testName.contains(Rp) &&
            (testName.contains(DSw_driver) ||
             (testName.contains(DS) && testName.contains(driver) && testName.contains(w))))
        readTestElemNorms("/TrRp", "/Rp_DSw_driver", strDn, strUp);
    else if(testName.contains(Hn) &&
            (testName.contains(DSw_driver) ||
             (testName.contains(DS) && testName.contains(driver) && testName.contains(w))))
        readTestElemNorms("/TrHn", "/Hn_DSw_driver", strDn, strUp);
    else if(testName.contains(Hp) &&
            (testName.contains(DSw_driver) ||
             (testName.contains(DS) && testName.contains(driver) && !testName.contains(w))))
        readTestElemNorms("/TrHp", "/Hp_DSw_driver", strDn, strUp);
    //--------------------------------------------------------------------------------------------------

    criterionDn = Validator::valueToDouble(strDn);
    criterionUp = Validator::valueToDouble(strUp);

    double milli = 1.0e+3, micro = 1.0e+6, nano = 1.0e+9, pico = 1.0e+12;
    double kilo = 1.0e-3, mega = 1.0e-6, giga = 1.0e-9, tera = 1.0e-12;

    switch(valuePrefix)
    {
    case ValuePrefix::norm:         break;
    case ValuePrefix::milli:        {  criterionDn *= milli;    criterionUp *= milli;  break;   }
    case ValuePrefix::micro:        {  criterionDn *= micro;    criterionUp *= micro;  break;   }
    case ValuePrefix::nano:         {  criterionDn *= nano;     criterionUp *= nano;   break;   }
    case ValuePrefix::pico:         {  criterionDn *= pico;     criterionUp *= pico;   break;   }
    case ValuePrefix::kilo:         {  criterionDn *= kilo;     criterionUp *= kilo;   break;   }
    case ValuePrefix::mega:         {  criterionDn *= mega;     criterionUp *= mega;   break;   }
    case ValuePrefix::giga:         {  criterionDn *= giga;     criterionUp *= giga;   break;   }
    case ValuePrefix::tera:         {  criterionDn *= tera;     criterionUp *= tera;   break;   }
    }
    //--------------------------------------------------------------------------------------------------
}

//чтение из реестра нормы выбранного тестового элемента и ее установка в переменные
void SystemSettings::readTestElemNorms(const QString& groupName, const QString& testName,
                                       QString& Dn, QString& Up)
{
    spSettings->beginGroup("/Settings");
    spSettings->beginGroup(groupName);
    Dn = spSettings->value(testName + "_Dn",0).toString();
    Up = spSettings->value(testName + "_Up",0).toString();
    spSettings->endGroup();
    spSettings->endGroup();
}
//==============================================================================================
Settings::Settings(){}
Settings::~Settings(){}

void Settings::init(shared_ptr<QSettings> spSettings,
                    shared_ptr<LocalSettingsWin> spLocalSettingsWin,
                    shared_ptr<GlobalSettingsWin> spGlobalSettingsWin)
{
    m_spSettings = spSettings;
    m_spLocalSettingsWin = spLocalSettingsWin;
    m_spGlobalSettingsWin = spGlobalSettingsWin;
}
//----------------------------------------------------------------------------------------------
//слоты:
//показать окно настроек: локальные нормы пользователя
void Settings::slotLocalSettingsWin()
{
    if(m_spLocalSettingsWin)
        m_spLocalSettingsWin->show();
}
//показать окно настроек: глобальные нормы пользователя
void Settings::slotGlobalSettingsWin()
{
    if(m_spGlobalSettingsWin)
        m_spGlobalSettingsWin->show();
}
//==============================================================================================
