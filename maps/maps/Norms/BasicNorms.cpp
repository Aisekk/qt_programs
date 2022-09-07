#include "BasicNorms.h"

BasicNorms::BasicNorms()
{
    m_milli = 1.0e+3;
    m_micro = 1.0e+6;
    m_nano = 1.0e+9;
    m_pico = 1.0e+12;
    m_kilo = 1.0e-3;
    m_mega = 1.0e-6;
    m_giga = 1.0e-9;
    m_tera = 1.0e-12;
    //----------------------------------------------------
    //структуры контактирования
    pNpN.setPattern("p[0-9]p[0-9]");
    //----------------------------------------------------
    //Силицидированные резисторы
    tRZnTiSi = "tRZnTiSi";//на N-моноSi
    tRZpTiSi = "tRZpTiSi";//на P-моноSi
    tRZnSiTiSi = "tRZnSiTiSi";//на N-полиSi
    tRZpSiTiSi = "tRZpSiTiSi";//на P-полиSi
    tRZSiTiSi = "tRZSiTiSi";//на нелегированном полиSi

    w09 = "09"; w05 = "05"; w035 = "035"; w06 = "06";
//---------------------------------------------------------------------------------------
    //Меандры
    Meander = "Meander"; One = "1"; Two = "2"; Three = "3"; Four = "4";
    //Сопротивление резистора в слое Met1 шириной 0,5 мкм (tRM1_3)
    dMeander1 = "dMeander1";
    //Сопротивление резистора в слое Met3 шириной 0,6 мкм (tRM1_3)
    dMeander3 = "dMeander3";
    //Сопротивление резистора в слое Met1 шириной 0,9 мкм (tRM1_3_09)
    dMeander1_09 = "dMeander1_09";
    //Сопротивление резистора в слое Met3 шириной 0,9 мкм (tRM1_3_09)
    dMeander3_09 = "dMeander3_09";

    //Сопротивление резистора в слое Met2 шириной 0,6 мкм (tRM2_4)
    dMeander2 = "dMeander2";
    //Сопротивление резистора в слое Met4 шириной 0,6 мкм (tRM2_4)
    dMeander4 = "dMeander4";
    //Сопротивление резистора в слое Met2 шириной 0,9 мкм (tRM2_4_09)
    dMeander2_09 = "dMeander2_09";
    //Сопротивление резистора в слое Met4 шириной 0,9 мкм (tRM2_4_09)
    dMeander4_09 = "dMeander4_09";

    divisorMeander = 5000.0;
//---------------------------------------------------------------------------------------
    //Кельвины M1-Si
    KLV_nM1 = "KLV_nM1"; KLVnM1 = "KLVnM1";//на N-моноSi
    KLV_pM1 = "KLV_pM1"; KLVpM1 = "KLVpM1";//на P-моноSi
    KLV_nSiM1 = "KLV_nSiM1"; KLVnSiM1 = "KLVnSiM1";//на N-полиSi
    KLV_pSiM1 = "KLV_pSiM1"; KLVpSiM1 = "KLVpSiM1";//на P-полиSi
    KLV_SiM1 = "KLV_SiM1"; KLVSiM1 = "KLVSiM1";//на нелегированном полиSi

    //Цепочки контактов M1-Si
    dZnM1 = "dZnM1"; dZ_nM1 = "dZ_nM1";//на N-моноSi
    dZpM1 = "dZpM1"; dZ_pM1 = "dZ_pM1";//на P-моноSi
    dZnSiM1 = "dZnSiM1"; dZ_nSiM1 = "dZ_nSiM1";//на N-полиSi
    dZpSiM1 = "dZpSiM1"; dZ_pSiM1 = "dZ_pSiM1";//на P-полиSi
    dZSiM1 = "dZSiM1", dZ_SiM1 = "dZ_SiM1";//на нелегированном полиSi

    //Кельвины Mеталл-Mеталл
    KLV_M1_M2 = "KLV_M1_M2"; KLV_M1M2 = "KLV_M1M2";
    KLV_M2_M3 = "KLV_M2_M3"; KLV_M2M3 = "KLV_M2M3";
    KLV_M3_M4 = "KLV_M3_M4"; KLV_M3M4 = "KLV_M3M4";
    KLV_M1_M4 = "KLV_M1_M4"; KLV_M1M4 = "KLV_M1M4";

    //Цепочки контактов Mетал-Mеталл
    dZ_M1M2 = "dZ_M1M2"; dZM1M2 = "dZM1M2"; Z_M1M2 = "Z_M1M2"; ZM1M2 = "ZM1M2";
    dZ_M2M3 = "dZ_M2M3"; dZM2M3 = "dZM2M3"; Z_M2M3 = "Z_M2M3"; ZM2M3 = "ZM2M2";
    dZ_M3M4 = "dZ_M3M4"; dZM3M4 = "dZM3M4"; Z_M3M4 = "Z_M3M4"; ZM3M4 = "ZM3M4";
    dZ_M1M4 = "dZ_M1M4"; dZM1M4 = "dZM1M4"; Z_M1M4 = "Z_M1M4"; ZM1M4 = "ZM1M4";

    //Структуры Ван-дер-Пау
    VDP = "VDP";
    VDPnWell = "VDPnWell";
    VDPpWell = "VDPpWell";
    VDPn = "VDPn";
    VDPp = "VDPp";
    VDPnSi = "VDPnSi";
    VDPpSi = "VDPpSi";

    //Емкости
    CpSinWell = "CpSinWell"; CnSipWell = "CnSipWell";
    //Диоды
    Diod = "Diod"; diod = "diod";

    //Транзисторы
    An = "An"; Ap = "Ap"; Rn = "Rn"; Rp = "Rp"; Hn = "Hn"; Hp = "Hp";
    Vt = "Vt"; Vbr = "Vbr";
    revers = "revers";
    Be = "Be";
    leak = "leak"; w = "w";
    Gleak = "Gleak"; G = "G";
    DSleak = "DSleak"; DS = "DS";
    LEN = 3.5;//мкм
    DSw_leak = "DSw_leak";
    DScurrent = "DScurrent"; current = "current";
    DSw_driver = "DSw_driver"; driver = "driver";
}

BasicNorms::~BasicNorms() {}
//------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------
void BasicNorms::setTestInterval(const QString& testName, ValuePrefix valuePrefix,
                                 double& criteriumDn, double& criteriumUp)
{
//------------------------------------------------------------------------------------
    //структуры контактирования
    Contacting(testName, criteriumDn, criteriumUp);
//------------------------------------------------------------------------------------
    SIL09(testName, criteriumDn, criteriumUp);
    SIL05(testName, criteriumDn, criteriumUp);
    SIL035(testName, criteriumDn, criteriumUp);
    SIL06(testName, criteriumDn, criteriumUp);
    Meanders(testName, criteriumDn, criteriumUp);
    KLV_M1Si(testName, criteriumDn, criteriumUp);
    Z_M1Si(testName, criteriumDn, criteriumUp);
    KLV_MeMe(testName, criteriumDn, criteriumUp);
    Z_MeMe(testName, criteriumDn, criteriumUp);
    VDPs(testName, criteriumDn, criteriumUp);
    Capacity(testName, criteriumDn, criteriumUp);
    Diods(testName, criteriumDn, criteriumUp);
    //транзисторы
    Tr_Vt(testName, criteriumDn, criteriumUp);
    //пороговые напряжения обратного транзистора
    Tr_VtRevers(testName, criteriumDn, criteriumUp);
    //крутизна
    Tr_Be(testName, criteriumDn, criteriumUp);
    //напряжение пробоя сток-исток
    Tr_Vbr(testName, criteriumDn, criteriumUp);
    //ток утечки затвор абсолютный
    Tr_Gleak(testName, criteriumDn, criteriumUp);
    //ток утечки сток-исток абсолютный
    Tr_DSleak(testName, criteriumDn, criteriumUp);
    //ток утечки сток-исток приведенный
    Tr_DSw_leak(testName, criteriumDn, criteriumUp);
    //ток насыщения абсолютный
    Tr_DScurrent(testName, criteriumDn, criteriumUp);
    //ток насыщения приведенный
    Tr_DSw_driver(testName, criteriumDn, criteriumUp);
    //------------------------------------------------------------------------------
    setPrefix(valuePrefix, criteriumDn, criteriumUp);
    //------------------------------------------------------------------------------
}
//end of setTestInterval
//------------------------------------------------------------------------------------------
//установить префикс
void BasicNorms::setPrefix(ValuePrefix valuePrefix, double& criterionDn, double& criterionUp)
{
    switch(valuePrefix)
    {
    case ValuePrefix::norm:         break;
    case ValuePrefix::milli:        { criterionDn *= m_milli;  criterionUp *= m_milli;  break;   }
    case ValuePrefix::micro:        { criterionDn *= m_micro;  criterionUp *= m_micro;  break;   }
    case ValuePrefix::nano:         { criterionDn *= m_nano;   criterionUp *= m_nano;   break;   }
    case ValuePrefix::pico:         { criterionDn *= m_pico;   criterionUp *= m_pico;   break;   }
    case ValuePrefix::kilo:         { criterionDn *= m_kilo;   criterionUp *= m_kilo;   break;   }
    case ValuePrefix::mega:         { criterionDn *= m_mega;   criterionUp *= m_mega;   break;   }
    case ValuePrefix::giga:         { criterionDn *= m_giga;   criterionUp *= m_giga;   break;   }
    case ValuePrefix::tera:         { criterionDn *= m_tera;   criterionUp *= m_tera;   break;   }
    }
}

//функции, вызываемые в setTestInterval
void BasicNorms::Contacting(const QString& testName, double& criteriumDn, double& criteriumUp)
{
    if(testName.contains(pNpN))
    { criteriumDn = 0.1; criteriumUp = 5.0; }
}

void BasicNorms::SIL09(const QString& testName, double& criteriumDn, double& criteriumUp)
{
    if(testName.contains(tRZnTiSi) && testName.contains(w09)){
        criteriumDn = 0.1; criteriumUp = 15.0;}//резисторы tRZnTiSi09
    else if(testName.contains(tRZpTiSi) && testName.contains(w09)){
        criteriumDn = 0.1; criteriumUp = 15.0;}//резисторы tRZpTiSi09
    else if(testName.contains(tRZnSiTiSi) && testName.contains(w09)){
        criteriumDn = 0.1; criteriumUp = 10.0;}//резисторы tRZnSiTiSi09
    else if(testName.contains(tRZpSiTiSi) && testName.contains(w09)){
        criteriumDn = 0.1; criteriumUp = 10.0;}//резисторы tRZpSiTiSi09
    else if(testName.contains(tRZSiTiSi) && testName.contains(w09)){
        criteriumDn = 0.1; criteriumUp = 10.0;}//резисторы tRZSiTiSi09
}
void BasicNorms::SIL05(const QString& testName, double& criteriumDn, double& criteriumUp)
{
    if(testName.contains(tRZnTiSi) && testName.contains(w05)){
        criteriumDn = 0.1; criteriumUp = 30.0;}//резисторы tRZnTiSi05
    else if(testName.contains(tRZpTiSi) && testName.contains(w05)){
        criteriumDn = 0.1; criteriumUp = 30.0;}//резисторы tRZpTiSi05
    else if(testName.contains(tRZnSiTiSi) && testName.contains(w05)){
        criteriumDn = 0.1; criteriumUp = 30.0;}//резисторы tRZnSiTiSi05
    else if(testName.contains(tRZpSiTiSi) && testName.contains(w05)){
        criteriumDn = 0.1; criteriumUp = 30.0;}//резисторы tRZpSiTiSi05
    else if(testName.contains(tRZSiTiSi) && testName.contains(w05)){
        criteriumDn = 0.1; criteriumUp = 30.0;}//резисторы tRZSiTiSi05
}
void BasicNorms::SIL035(const QString& testName, double& criteriumDn, double& criteriumUp)
{
    if(testName.contains(tRZnTiSi) && testName.contains(w035)){
        criteriumDn = 0.1; criteriumUp = 30.0;}//резисторы tRZnTiSi035
    else if(testName.contains(tRZpTiSi) && testName.contains(w035)){
        criteriumDn = 0.1; criteriumUp = 30.0;}//резисторы tRZpTiSi035
    else if(testName.contains(tRZnSiTiSi) && testName.contains(w035)){
        criteriumDn = 0.1; criteriumUp = 30.0;}//резисторы tRZnSiTiSi035
    else if(testName.contains(tRZpSiTiSi) && testName.contains(w035)){
        criteriumDn = 0.1; criteriumUp = 30.0;}//резисторы tRZpSiTiSi035
    else if(testName.contains(tRZSiTiSi) && testName.contains(w035)){
        criteriumDn = 0.1; criteriumUp = 30.0;}//резисторы tRZSiTiSi035
}
void BasicNorms::SIL06(const QString& testName, double& criteriumDn, double& criteriumUp)
{
    if(testName.contains(tRZnTiSi) && testName.contains(w06)){
        criteriumDn = 0.1; criteriumUp = 30.0;}//резисторы tRZnTiSi06
    else if(testName.contains(tRZpTiSi) && testName.contains(w06)){
        criteriumDn = 0.1; criteriumUp = 30.0;}//резисторы tRZpTiSi06
    else if(testName.contains(tRZnSiTiSi) && testName.contains(w06)){
        criteriumDn = 0.1; criteriumUp = 30.0;}//резисторы tRZnSiTiSi06
    else if(testName.contains(tRZpSiTiSi) && testName.contains(w06)){
        criteriumDn = 0.1; criteriumUp = 30.0;}//резисторы tRZpSiTiSi06
    else if(testName.contains(tRZSiTiSi) && testName.contains(w06)){
        criteriumDn = 0.1; criteriumUp = 30.0;}//резисторы tRZSiTiSi06
}
void BasicNorms::KLV_M1Si(const QString& testName, double& criteriumDn, double& criteriumUp)
{
    if(testName.contains(KLV_nM1) || testName.contains(KLVnM1)){
        criteriumDn = 0.1; criteriumUp = 15.0;}//кельвины KLV_nM1
    else if(testName.contains(KLV_pM1) || testName.contains(KLVpM1)){
        criteriumDn = 0.1; criteriumUp = 15.0;}//кельвины KLV_pM1
    else if(testName.contains(KLV_nSiM1) || testName.contains(KLVnSiM1)){
        criteriumDn = 0.1; criteriumUp = 15.0;}//кельвины KLV_nSiM1
    else if(testName.contains(KLV_pSiM1) || testName.contains(KLVpSiM1)){
        criteriumDn = 0.1; criteriumUp = 15.0;}//кельвины KLV_pSiM1
    else if(testName.contains(KLV_SiM1) || testName.contains(KLVSiM1)){
        criteriumDn = 0.1; criteriumUp = 15.0;}//кельвины KLV_SiM1
}
void BasicNorms::Z_M1Si(const QString& testName, double& criteriumDn, double& criteriumUp)
{
    if(testName.contains(dZnM1) || testName.contains(dZ_nM1)){
        criteriumDn = 0.1; criteriumUp = 15.0;}//цепочки dZnM1
    else if(testName.contains(dZpM1) || testName.contains(dZ_pM1)){
        criteriumDn = 0.1; criteriumUp = 15.0;}//цепочки dZpM1
    else if(testName.contains(dZnSiM1) || testName.contains(dZ_nSiM1)){
        criteriumDn = 0.1; criteriumUp = 15.0;}//цепочки dZnSiM1
    else if(testName.contains(dZpSiM1) || testName.contains(dZ_pSiM1)){
        criteriumDn = 0.1; criteriumUp = 15.0;}//цепочки dZpSiM1
    else if(testName.contains(dZSiM1) || testName.contains(dZ_SiM1)){
        criteriumDn = 0.1; criteriumUp = 15.0;}//кельвины KLV_SiM1
}

void BasicNorms::Meanders(const QString& testName, double& criteriumDn, double& criteriumUp)
{
    if(testName.contains(dMeander1) || (testName.contains(Meander) && testName.contains(One)))
    {
        criteriumDn = 200.0/divisorMeander; criteriumUp = 450.0/divisorMeander;
    }//резисторы dMeander1
    else if(testName.contains(dMeander3) || (testName.contains(Meander) && testName.contains(Three)))
    {
        criteriumDn = 200.0/divisorMeander; criteriumUp = 450.0/divisorMeander;
    }//резисторы dMeander3
    else if(testName.contains(dMeander1_09) ||
           (testName.contains(Meander) && testName.contains(One) && testName.contains(w09)))
    {
        criteriumDn = 200.0/divisorMeander; criteriumUp = 450.0/divisorMeander;
    }//резисторы dMeander1_09
    else if(testName.contains(dMeander3_09) ||
           (testName.contains(Meander) && testName.contains(Three) && testName.contains(w09)))
    {
        criteriumDn = 200.0/divisorMeander; criteriumUp = 450.0/divisorMeander;
    }//резисторы dMeander3_09
    else if(testName.contains(dMeander2) || (testName.contains(Meander) && testName.contains(Two)))
    {
        criteriumDn = 200.0/divisorMeander; criteriumUp = 450.0/divisorMeander;
    }//резисторы dMeander2
    else if(testName.contains(dMeander4) || (testName.contains(Meander) && testName.contains(Four)))
    {
        criteriumDn = 150.0/divisorMeander; criteriumUp = 450.0/divisorMeander;
    }//резисторы dMeander4
    else if(testName.contains(dMeander2_09) ||
           (testName.contains(Meander) && testName.contains(Two) && testName.contains(w09)))
    {
        criteriumDn = 200.0/divisorMeander; criteriumUp = 450.0/divisorMeander;
    }//резисторы dMeander2_09
    else if(testName.contains(dMeander4_09) ||
           (testName.contains(Meander) && testName.contains(Four) && testName.contains(w09)))
    {
        criteriumDn = 150.0/divisorMeander; criteriumUp = 450.0/divisorMeander;
    }//резисторы dMeander4_09
}
void BasicNorms::KLV_MeMe(const QString& testName, double& criteriumDn, double& criteriumUp)
{
    if(testName.contains(KLV_M1_M2) || testName.contains(KLV_M1M2)){
        criteriumDn = 0.1; criteriumUp = 2.5;}//кельвины M1_M2
    else if(testName.contains(KLV_M2_M3) || testName.contains(KLV_M2M3)){
        criteriumDn = 0.1; criteriumUp = 2.5;}//кельвины M2_M3
    else if(testName.contains(KLV_M3_M4) || testName.contains(KLV_M3M4)){
        criteriumDn = 0.1; criteriumUp = 2.5;}//кельвины M3_M4
    else if(testName.contains(KLV_M1_M4) || testName.contains(KLV_M1M4)){
        criteriumDn = 0.1; criteriumUp = 7.5;}//кельвины M1_M4
}
void BasicNorms::Z_MeMe(const QString& testName, double& criteriumDn, double& criteriumUp)
{
    if(testName.contains(dZ_M1M2) || testName.contains(dZM1M2)
            || testName.contains(Z_M1M2) || testName.contains(ZM1M2))
    {
        criteriumDn = 0.1; criteriumUp = 2.5;
    }//цепочки M1_M2
    else if(testName.contains(dZ_M2M3) || testName.contains(dZM2M3)
            || testName.contains(Z_M2M3) || testName.contains(ZM2M3))
    {
        criteriumDn = 0.1; criteriumUp = 2.5;
    }//цепочки M2_M3
    else if(testName.contains(dZ_M3M4) || testName.contains(dZM3M4)
            || testName.contains(Z_M3M4) || testName.contains(ZM3M4))
    {
        criteriumDn = 0.1; criteriumUp = 2.5;
    }//цепочки M3_M4
    else if(testName.contains(dZ_M1M4) || testName.contains(dZM1M4)
            || testName.contains(Z_M1M4) || testName.contains(ZM1M4))
    {
        criteriumDn = 0.1; criteriumUp = 7.5;
    }//цепочки M1_M4
}
void BasicNorms::VDPs(const QString& testName, double& criteriumDn, double& criteriumUp)
{
    if(testName.contains(VDPnWell) || (testName.contains(VDP) && testName.contains("n")
                                       && (testName.contains("Well") || testName.contains("well"))))
    {
        criteriumDn = 0.1; criteriumUp = 5600.0;
    }//структура VDPnWell
    else if(testName.contains(VDPpWell) || (testName.contains(VDP) && testName.contains("p")
                                            && (testName.contains("Well") || testName.contains("well"))))
    {
        criteriumDn = 0.1; criteriumUp = 4000.0;
    }//структура VDPpWell
    else if(testName.contains(VDPn) || (testName.contains(VDP) && testName.contains("n")))
    {
        criteriumDn = 0.1; criteriumUp = 50.0;
    }//структура VDPn
    else if(testName.contains(VDPp) || (testName.contains(VDP) && testName.contains("p")))
    {
        criteriumDn = 0.1; criteriumUp = 100.0;
    }//структура VDPp
    else if(testName.contains(VDPnSi) || (testName.contains(VDP) && testName.contains("n")
                                          && testName.contains("Si")))
    {
        criteriumDn = 0.1; criteriumUp = 300.0;
    }//структура VDPnSi
    else if(testName.contains(VDPpSi) || (testName.contains(VDP) && testName.contains("p")
                                          && testName.contains("Si")))
    {
        criteriumDn = 0.1; criteriumUp = 200.0;
    }//структура VDPpSi
}
void BasicNorms::Capacity(const QString& testName, double& criteriumDn, double& criteriumUp)
{
    //емкость между слоями P+Poly и nWell
    if(testName.contains(CpSinWell) || (testName.contains("Cp") && testName.contains("Si")
                                        && (testName.contains("n") || testName.contains("N"))
                                        && (testName.contains("Well") || testName.contains("well"))))
    {
        criteriumDn = 4.6*(1e-15); criteriumUp = 5.5*(1e-15);
    }//емкость CpSinWell
    //емкость между слоями N+Poly и pWell
    else if(testName.contains(CnSipWell) || (testName.contains("Cn") && testName.contains("Si")
                                             && (testName.contains("p") || testName.contains("P"))
                                             && (testName.contains("Well") || testName.contains("well"))))
    {
        criteriumDn = 4.6*(1e-15); criteriumUp = 5.5*(1e-15);
    }//емкость CnSipWell
}
void BasicNorms::Diods(const QString& testName, double& criteriumDn, double& criteriumUp)
{
    //диод на N-кармане
    if((testName.contains(Diod) || testName.contains(diod))
            && (testName.contains("n") || testName.contains("N")
                || testName.contains("pn") || testName.contains("PN")))
    {
        criteriumDn = -2.0*(1e-12); criteriumUp = 0.0;
    }// nDiod
    //диод на N-кармане
    else if((testName.contains(Diod) || testName.contains(diod))
            && (testName.contains("n") || testName.contains("N")
                || testName.contains("pn") || testName.contains("PN"))
            && (testName.contains("Well") || testName.contains("well")))
    {
        criteriumDn = -2.0*(1e-12); criteriumUp = 0.0;
    }// nDiod
    //диод на P-кармане
    else if((testName.contains(Diod) || testName.contains(diod))
            && (testName.contains("p") || testName.contains("P")
                || testName.contains("np") || testName.contains("NP")))
    {
        criteriumDn = 0.0; criteriumUp = 2.0*(1e-12);
    }// pDiod
    //диод на P-кармане
    else if((testName.contains(Diod) || testName.contains(diod))
            && (testName.contains("p") || testName.contains("P")
                || testName.contains("np") || testName.contains("NP"))
            && (testName.contains("Well") || testName.contains("well")))
    {
        criteriumDn = 0.0; criteriumUp = 2.0*(1e-12);
    }// pDiod
}

void BasicNorms::Tr_Vt(const QString& testName, double& criteriumDn, double& criteriumUp)
{
    //An
    if(testName.contains(An) && testName.contains(Vt))
    {
        criteriumDn = 0.55; criteriumUp = 0.70;
    }
    //Ap
    else if(testName.contains(Ap) && testName.contains(Vt))
    {
        criteriumDn = -0.70; criteriumUp = -0.50;
    }
    //Rn
    else if(testName.contains(Rn) && testName.contains(Vt))
    {
        criteriumDn = 0.55; criteriumUp = 0.70;
    }
    //Rp
    else if(testName.contains(Rp) && testName.contains(Vt))
    {
        criteriumDn = -0.70; criteriumUp = -0.50;
    }
    //Hn
    else if(testName.contains(Hn) && testName.contains(Vt))
    {
        criteriumDn = 0.55; criteriumUp = 0.70;
    }
    //Hp
    else if(testName.contains(Hp) && testName.contains(Vt))
    {
        criteriumDn = -0.70; criteriumUp = -0.50;
    }
}
void BasicNorms::Tr_VtRevers(const QString& testName, double& criteriumDn, double& criteriumUp)
{
    //An
    if(testName.contains(An) && testName.contains(Vt) && testName.contains(revers))
    {
        criteriumDn = 0.55; criteriumUp = 30.00;
    }
    //Ap
    else if(testName.contains(Ap) && testName.contains(Vt) && testName.contains(revers))
    {
        criteriumDn = -30.0; criteriumUp = -0.50;
    }
    //Rn
    else if(testName.contains(Rn) && testName.contains(Vt) && testName.contains(revers))
    {
        criteriumDn = 0.55; criteriumUp = 30.0;
    }
    //Rp
    else if(testName.contains(Rp) && testName.contains(Vt) && testName.contains(revers))
    {
        criteriumDn = -30.00; criteriumUp = -0.50;
    }
    //Hn
    else if(testName.contains(Hn) && testName.contains(Vt) && testName.contains(revers))
    {
        criteriumDn = 0.55; criteriumUp = 30.0;
    }
    //Hp
    else if(testName.contains(Hp) && testName.contains(Vt) && testName.contains(revers))
    {
        criteriumDn = -30.0; criteriumUp = -0.50;
    }
}
void BasicNorms::Tr_Be(const QString& testName, double& criteriumDn, double& criteriumUp)
{
    //An
    if(testName.contains(An) && testName.contains(Be))
    {
        criteriumDn = 2.2*(1e-4); criteriumUp = 2.6*(1e-4);
    }
    //Ap
    else if(testName.contains(Ap) && testName.contains(Be))
    {
        criteriumDn = 4.58*(1e-5); criteriumUp = 6.21*(1e-5);
    }
    //Rn
    if(testName.contains(Rn) && testName.contains(Be))
    {
        criteriumDn = 2.2*(1e-4); criteriumUp = 2.6*(1e-4);
    }
    //Rp
    else if(testName.contains(Rp) && testName.contains(Be))
    {
        criteriumDn = 5.26*(1e-5); criteriumUp = 6.87*(1e-5);
    }
    //Hn
    if(testName.contains(Hn) && testName.contains(Be))
    {
        criteriumDn = 2.2*(1e-4); criteriumUp = 2.6*(1e-4);
    }
    //Hp
    else if(testName.contains(Hp) && testName.contains(Be))
    {
        criteriumDn = 5.15*(1e-5); criteriumUp = 6.95*(1e-5);
    }
}
void BasicNorms::Tr_Vbr(const QString& testName, double& criteriumDn, double& criteriumUp)
{
    //An
    if(testName.contains(An) && testName.contains(Vbr))
    {
        criteriumDn = 8.0; criteriumUp = 30.0;
    }
    //Ap
    else if(testName.contains(Ap) && testName.contains(Vbr))
    {
        criteriumDn = -30.0; criteriumUp = -8.0;
    }
    //Rn
    else if(testName.contains(Rn) && testName.contains(Vbr))
    {
        criteriumDn = 8.0; criteriumUp = 30.0;
    }
    //Rp
    else if(testName.contains(Rp) && testName.contains(Vbr))
    {
        criteriumDn = -30.0; criteriumUp = -8.0;
    }
    //Hn
    else if(testName.contains(Hn) && testName.contains(Vbr))
    {
        criteriumDn = 8.0; criteriumUp = 30.0;
    }
    //Hp
    else if(testName.contains(Hp) && testName.contains(Vbr))
    {
        criteriumDn = -30.0; criteriumUp = -8.0;
    }
}
void BasicNorms::Tr_Gleak(const QString& testName, double& criteriumDn, double& criteriumUp)
{
    //An
    if(testName.contains(An) &&
            (testName.contains(Gleak) ||
             (testName.contains(G) && testName.contains(leak) && !testName.contains(w))))
    {
        criteriumDn = 0.0; criteriumUp = 1e-12;
    }
    //Ap
    else if(testName.contains(Ap) &&
            (testName.contains(Gleak) ||
             (testName.contains(G) && testName.contains(leak) && !testName.contains(w))))
    {
        criteriumDn = -1e-12; criteriumUp = 0.0;
    }
    //Rn
    else if(testName.contains(Rn) &&
            (testName.contains(Gleak) ||
             (testName.contains(G) && testName.contains(leak) && !testName.contains(w))))
    {
        criteriumDn = 0.0; criteriumUp = 1e-12;
    }
    //Rp
    else if(testName.contains(Rp) &&
            (testName.contains(Gleak) ||
             (testName.contains(G) && testName.contains(leak) && !testName.contains(w))))
    {
        criteriumDn = -1e-12; criteriumUp = 0.0;
    }
    //Hn
    else if(testName.contains(Hn) &&
            (testName.contains(Gleak) ||
             (testName.contains(G) && testName.contains(leak) && !testName.contains(w))))
    {
        criteriumDn = 0.0; criteriumUp = 1e-12;
    }
    //Hp
    else if(testName.contains(Hp) &&
            (testName.contains(Gleak) ||
             (testName.contains(G) && testName.contains(leak) && !testName.contains(w))))
    {
        criteriumDn = -1e-12; criteriumUp = 0.0;
    }
}
void BasicNorms::Tr_DSleak(const QString& testName, double& criteriumDn, double& criteriumUp)
{
    //An
    if(testName.contains(An) &&
            (testName.contains(DSleak) ||
             (testName.contains(DS) && testName.contains(leak) && !testName.contains(w))))
    {
        criteriumDn = 0.0;
        criteriumUp = 6.0*(1e-12)*LEN;
    }
    //Ap
    else if(testName.contains(Ap) &&
            (testName.contains(DSleak) ||
             (testName.contains(DS) && testName.contains(leak) && !testName.contains(w))))
    {
        criteriumDn = -10.0*(1e-12)*LEN;
        criteriumUp = 0.0;
    }
    //Rn
    else if(testName.contains(Rn) &&
            (testName.contains(DSleak) ||
             (testName.contains(DS) && testName.contains(leak) && !testName.contains(w))))
    {
        criteriumDn = 0.0;
        criteriumUp = 10.0*(1e-12)*LEN;
    }
    //Rp
    else if(testName.contains(Rp) &&
            (testName.contains(DSleak) ||
             (testName.contains(DS) && testName.contains(leak) && !testName.contains(w))))
    {
        criteriumDn = -10.0*(1e-12)*LEN;
        criteriumUp = 0.0;
    }
    //Hn
    else if(testName.contains(Hn) &&
            (testName.contains(DSleak) ||
             (testName.contains(DS) && testName.contains(leak) && !testName.contains(w))))
    {
        criteriumDn = 0.0;
        criteriumUp = 10.0*(1e-12)*LEN;
    }
    //Hp
    else if(testName.contains(Hp) &&
            (testName.contains(DSleak) ||
             (testName.contains(DS) && testName.contains(leak) && !testName.contains(w))))
    {
        criteriumDn = -10.0*(1e-12)*LEN;
        criteriumUp = 0.0;
    }
}
void BasicNorms::Tr_DSw_leak(const QString& testName, double& criteriumDn, double& criteriumUp)
{
    //An
    if(testName.contains(An) &&
            (testName.contains(DSw_leak) ||
             (testName.contains(DS) && testName.contains(leak) && testName.contains(w))))
    {
        criteriumDn = 0.0;
        criteriumUp = 6.0*(1e-12);
    }
    //Ap
    else if(testName.contains(Ap) &&
            (testName.contains(DSw_leak) ||
             (testName.contains(DS) && testName.contains(leak) && testName.contains(w))))
    {
        criteriumDn = -10.0*(1e-12);
        criteriumUp = 0.0;
    }
    //Rn
    else if(testName.contains(Rn) &&
            (testName.contains(DSw_leak) ||
             (testName.contains(DS) && testName.contains(leak) && testName.contains(w))))
    {
        criteriumDn = 0.0;
        criteriumUp = 10.0*(1e-12);
    }
    //Rp
    else if(testName.contains(Rp) &&
            (testName.contains(DSw_leak) ||
             (testName.contains(DS) && testName.contains(leak) && testName.contains(w))))
    {
        criteriumDn = -10.0*(1e-12);
        criteriumUp = 0.0;
    }
    //Hn
    else if(testName.contains(Hn) &&
            (testName.contains(DSw_leak) ||
             (testName.contains(DS) && testName.contains(leak) && testName.contains(w))))
    {
        criteriumDn = 0.0;
        criteriumUp = 10.0*(1e-12);
    }
    //Hp
    else if(testName.contains(Hp) &&
            (testName.contains(DSw_leak) ||
             (testName.contains(DS) && testName.contains(leak) && testName.contains(w))))
    {
        criteriumDn = -10.0*(1e-12);
        criteriumUp = 0.0;
    }
}
void BasicNorms::Tr_DScurrent(const QString& testName, double& criteriumDn, double& criteriumUp)
{
    //An
    if(testName.contains(An) &&
            (testName.contains(DScurrent) ||
             (testName.contains(DS) && testName.contains(current) && !testName.contains(w))))
    {
        criteriumDn = 4.2*(1e-4)*LEN; criteriumUp = 5.2*(1e-4)*LEN;
    }
    //Ap
    else if(testName.contains(Ap) &&
            (testName.contains(DScurrent) ||
             (testName.contains(DS) && testName.contains(current) && !testName.contains(w))))
    {
        criteriumDn = -3.3*(1e-4)*LEN; criteriumUp = -2.3*(1e-4)*LEN;
    }
    //Rn
    else if(testName.contains(Rn) &&
            (testName.contains(DScurrent) ||
             (testName.contains(DS) && testName.contains(current) && !testName.contains(w))))
    {
        criteriumDn = 4.2*(1e-4)*LEN; criteriumUp = 5.2*(1e-4)*LEN;
    }
    //Rp
    else if(testName.contains(Rp) &&
            (testName.contains(DScurrent) ||
             (testName.contains(DS) && testName.contains(current) && !testName.contains(w))))
    {
        criteriumDn = -3.3*(1e-4)*LEN; criteriumUp = -2.3*(1e-4)*LEN;
    }
    //Hn
    else if(testName.contains(Hn) &&
            (testName.contains(DScurrent) ||
             (testName.contains(DS) && testName.contains(current) && !testName.contains(w))))
    {
        criteriumDn = 4.2*(1e-4)*LEN; criteriumUp = 5.2*(1e-4)*LEN;
    }
    //Hp
    else if(testName.contains(Hp) &&
            (testName.contains(DScurrent) ||
             (testName.contains(DS) && testName.contains(current) && !testName.contains(w))))
    {
        criteriumDn = -3.3*(1e-4)*LEN; criteriumUp = -2.3*(1e-4)*LEN;
    }
}
void BasicNorms::Tr_DSw_driver(const QString& testName, double& criteriumDn, double& criteriumUp)
{
    //An
    if(testName.contains(An) &&
            (testName.contains(DSw_driver) ||
             (testName.contains(DS) && testName.contains(driver) && testName.contains(w))))
    {
        criteriumDn = 4.2*(1e-4); criteriumUp = 5.2*(1e-4);
    }
    //Ap
    else if(testName.contains(Ap) &&
            (testName.contains(DSw_driver) ||
             (testName.contains(DS) && testName.contains(driver) && testName.contains(w))))
    {
        criteriumDn = -3.3*(1e-4); criteriumUp = -2.3*(1e-4);
    }
    //Rn
    else if(testName.contains(Rn) &&
            (testName.contains(DSw_driver) ||
             (testName.contains(DS) && testName.contains(driver) && testName.contains(w))))
    {
        criteriumDn = 4.2*(1e-4); criteriumUp = 5.2*(1e-4);
    }
    //Rp
    else if(testName.contains(Rp) &&
            (testName.contains(DSw_driver) ||
             (testName.contains(DS) && testName.contains(driver) && testName.contains(w))))
    {
        criteriumDn = -3.3*(1e-4); criteriumUp = -2.3*(1e-4);
    }
    //Hn
    else if(testName.contains(Hn) &&
            (testName.contains(DSw_driver) ||
             (testName.contains(DS) && testName.contains(driver) && testName.contains(w))))
    {
        criteriumDn = 4.2*(1e-4); criteriumUp = 5.2*(1e-4);
    }
    //Hp
    else if(testName.contains(Hp) &&
            (testName.contains(DSw_driver) ||
             (testName.contains(DS) && testName.contains(driver) && testName.contains(w))))
    {
        criteriumDn = -3.3*(1e-4); criteriumUp = -2.3*(1e-4);
    }
}
//---------------------------------------------------------------------------------------
