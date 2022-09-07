#include "UserNorms.h"

UserNorms::UserNorms(){}

void UserNorms::UserDesignRules(const QString& TestName, double& CriteriumDown, double& CriteriumUp)
{
//-------------------------------------------------------------------------------------------------------------
    QRegExp pNpN("p[0-9]p[0-9]");
    //Структуры контактирования
    if(TestName.contains(pNpN)){
            CriteriumDown = 0.1; CriteriumUp = 5.0;}
//-------------------------------------------------------------------------------------------------------------
    //Силицидированные резисторы
    QString tRZnTiSi = "tRZnTiSi";//на N-моноSi
    QString tRZpTiSi = "tRZpTiSi";//на P-моноSi
    QString tRZnSiTiSi = "tRZnSiTiSi";//на N-полиSi
    QString tRZpSiTiSi = "tRZpSiTiSi";//на P-полиSi
    QString tRZSiTiSi = "tRZSiTiSi";//на нелегированном полиSi

    //Силицидированные резисторы 09
    QString w09 = "09";

    if(TestName.contains(tRZnTiSi) && TestName.contains(w09)){
        CriteriumDown = 0.1; CriteriumUp = 15.0;}//резисторы tRZnTiSi09
        //CriteriumDown = 1.5; CriteriumUp = 15.0;}//резисторы tRZnTiSi09
    else if(TestName.contains(tRZpTiSi) && TestName.contains(w09)){
        CriteriumDown = 0.1; CriteriumUp = 15.0;}//резисторы tRZpTiSi09
        //CriteriumDown = 1.5; CriteriumUp = 15.0;}//резисторы tRZpTiSi09
    else if(TestName.contains(tRZnSiTiSi) && TestName.contains(w09)){
        CriteriumDown = 0.1; CriteriumUp = 10.0;}//резисторы tRZnSiTiSi09
        //CriteriumDown = 2.0; CriteriumUp = 10.0;}//резисторы tRZnSiTiSi09
    else if(TestName.contains(tRZpSiTiSi) && TestName.contains(w09)){
        CriteriumDown = 0.1; CriteriumUp = 10.0;}//резисторы tRZpSiTiSi09
        //CriteriumDown = 2.0; CriteriumUp = 10.0;}//резисторы tRZpSiTiSi09
    else if(TestName.contains(tRZSiTiSi) && TestName.contains(w09)){
        CriteriumDown = 0.1; CriteriumUp = 10.0;}//резисторы tRZSiTiSi09
        //CriteriumDown = 2.0; CriteriumUp = 10.0;}//резисторы tRZSiTiSi09

    //Силицидированные резисторы 05
    QString w05 = "05";
    if(TestName.contains(tRZnTiSi) && TestName.contains(w05)){
        CriteriumDown = 0.1; CriteriumUp = 30.0;}//резисторы tRZnTiSi05
        //CriteriumDown = 1.5; CriteriumUp = 15.0;}//резисторы tRZnTiSi05
    else if(TestName.contains(tRZpTiSi) && TestName.contains(w05)){
        CriteriumDown = 0.1; CriteriumUp = 30.0;}//резисторы tRZpTiSi05
        //CriteriumDown = 1.5; CriteriumUp = 15.0;}//резисторы tRZpTiSi05
    else if(TestName.contains(tRZnSiTiSi) && TestName.contains(w05)){
        CriteriumDown = 0.1; CriteriumUp = 30.0;}//резисторы tRZnSiTiSi05
        //CriteriumDown = 2.0; CriteriumUp = 10.0;}//резисторы tRZnSiTiSi05
    else if(TestName.contains(tRZpSiTiSi) && TestName.contains(w05)){
        CriteriumDown = 0.1; CriteriumUp = 30.0;}//резисторы tRZpSiTiSi05
        //CriteriumDown = 2.0; CriteriumUp = 10.0;}//резисторы tRZpSiTiSi05
    else if(TestName.contains(tRZSiTiSi) && TestName.contains(w05)){
        CriteriumDown = 0.1; CriteriumUp = 30.0;}//резисторы tRZSiTiSi05
        //CriteriumDown = 2.0; CriteriumUp = 10.0;}//резисторы tRZSiTiSi05

    //Силицидированные резисторы 035
    QString w035 = "035";
    if(TestName.contains(tRZnTiSi) && TestName.contains(w035)){
        CriteriumDown = 0.1; CriteriumUp = 30.0;}//резисторы tRZnTiSi035
        //CriteriumDown = 2.0; CriteriumUp = 15.0;}//резисторы tRZnTiSi035
    else if(TestName.contains(tRZpTiSi) && TestName.contains(w035)){
        CriteriumDown = 0.1; CriteriumUp = 30.0;}//резисторы tRZpTiSi035
        //CriteriumDown = 2.0; CriteriumUp = 15.0;}//резисторы tRZpTiSi035
    else if(TestName.contains(tRZnSiTiSi) && TestName.contains(w035)){
        CriteriumDown = 0.1; CriteriumUp = 30.0;}//резисторы tRZnSiTiSi035
        //CriteriumDown = 2.0; CriteriumUp = 15.0;}//резисторы tRZnSiTiSi035
    else if(TestName.contains(tRZpSiTiSi) && TestName.contains(w035)){
        CriteriumDown = 0.1; CriteriumUp = 30.0;}//резисторы tRZpSiTiSi035
        //CriteriumDown = 2.0; CriteriumUp = 15.0;}//резисторы tRZpSiTiSi035
    else if(TestName.contains(tRZSiTiSi) && TestName.contains(w035)){
        CriteriumDown = 0.1; CriteriumUp = 30.0;}//резисторы tRZSiTiSi035
        //CriteriumDown = 2.0; CriteriumUp = 15.0;}//резисторы tRZSiTiSi035
//-------------------------------------------------------------------------------------------------------------
    QString Meander = "Meander", One = "1", Two = "2", Three = "3", Four = "4";
    //Сопротивление резистора в слое Met1 шириной 0,5 мкм (tRM1_3)
    QString dMeander1 = "dMeander1";
    //Сопротивление резистора в слое Met3 шириной 0,6 мкм (tRM1_3)
    QString dMeander3 = "dMeander3";
    //Сопротивление резистора в слое Met1 шириной 0,9 мкм (tRM1_3_09)
    QString dMeander1_09 = "dMeander1_09";
    //Сопротивление резистора в слое Met3 шириной 0,9 мкм (tRM1_3_09)
    QString dMeander3_09 = "dMeander3_09";

    //Сопротивление резистора в слое Met2 шириной 0,6 мкм (tRM2_4)
    QString dMeander2 = "dMeander2";
    //Сопротивление резистора в слое Met4 шириной 0,6 мкм (tRM2_4)
    QString dMeander4 = "dMeander4";
    //Сопротивление резистора в слое Met2 шириной 0,9 мкм (tRM2_4_09)
    QString dMeander2_09 = "dMeander2_09";
    //Сопротивление резистора в слое Met4 шириной 0,9 мкм (tRM2_4_09)
    QString dMeander4_09 = "dMeander4_09";

    double divisorMeander = 5000.0;

    if(TestName.contains(dMeander1) || (TestName.contains(Meander) && TestName.contains(One))){
        CriteriumDown = 200.0/divisorMeander; CriteriumUp = 450.0/divisorMeander;}//резисторы dMeander1
    else if(TestName.contains(dMeander3) || (TestName.contains(Meander) && TestName.contains(Three))){
        CriteriumDown = 200.0/divisorMeander; CriteriumUp = 450.0/divisorMeander;}//резисторы dMeander3
    else if(TestName.contains(dMeander1_09) ||
           (TestName.contains(Meander) && TestName.contains(One) && TestName.contains(w09))){
        CriteriumDown = 200.0/divisorMeander; CriteriumUp = 450.0/divisorMeander;}//резисторы dMeander1_09
    else if(TestName.contains(dMeander3_09) ||
           (TestName.contains(Meander) && TestName.contains(Three) && TestName.contains(w09))){
        CriteriumDown = 200.0/divisorMeander; CriteriumUp = 450.0/divisorMeander;}//резисторы dMeander3_09
    else if(TestName.contains(dMeander2) || (TestName.contains(Meander) && TestName.contains(Two))){
        CriteriumDown = 200.0/divisorMeander; CriteriumUp = 450.0/divisorMeander;}//резисторы dMeander2
    else if(TestName.contains(dMeander4) || (TestName.contains(Meander) && TestName.contains(Four))){
        CriteriumDown = 150.0/divisorMeander; CriteriumUp = 450.0/divisorMeander;}//резисторы dMeander4
    else if(TestName.contains(dMeander2_09) ||
           (TestName.contains(Meander) && TestName.contains(Two) && TestName.contains(w09))){
        CriteriumDown = 200.0/divisorMeander; CriteriumUp = 450.0/divisorMeander;}//резисторы dMeander2_09
    else if(TestName.contains(dMeander4_09) ||
           (TestName.contains(Meander) && TestName.contains(Four) && TestName.contains(w09))){
        CriteriumDown = 150.0/divisorMeander; CriteriumUp = 450.0/divisorMeander;}//резисторы dMeander4_09

//-------------------------------------------------------------------------------------------------------------
        //Кельвины M1-Si
        QString KLV_nM1 = "KLV_nM1", KLVnM1 = "KLVnM1";//на N-моноSi
        QString KLV_pM1 = "KLV_pM1", KLVpM1 = "KLVpM1";//на P-моноSi
        QString KLV_nSiM1 = "KLV_nSiM1", KLVnSiM1 = "KLVnSiM1";//на N-полиSi
        QString KLV_pSiM1 = "KLV_pSiM1", KLVpSiM1 = "KLVpSiM1";//на P-полиSi
        QString KLV_SiM1 = "KLV_SiM1", KLVSiM1 = "KLVSiM1";//на нелегированном полиSi

        if(TestName.contains(KLV_nM1) || TestName.contains(KLVnM1)){
            CriteriumDown = 0.1; CriteriumUp = 15.0;}//кельвины KLV_nM1
            //CriteriumDown = 2.0; CriteriumUp = 10.0;}//кельвины KLV_nM1
        else if(TestName.contains(KLV_pM1) || TestName.contains(KLVpM1)){
            CriteriumDown = 0.1; CriteriumUp = 15.0;}//кельвины KLV_pM1
            //CriteriumDown = 2.0; CriteriumUp = 10.0;}//кельвины KLV_pM1
        else if(TestName.contains(KLV_nSiM1) || TestName.contains(KLVnSiM1)){
            CriteriumDown = 0.1; CriteriumUp = 15.0;}//кельвины KLV_nSiM1
            //CriteriumDown = 2.0; CriteriumUp = 10.0;}//кельвины KLV_nSiM1
        else if(TestName.contains(KLV_pSiM1) || TestName.contains(KLVpSiM1)){
            CriteriumDown = 0.1; CriteriumUp = 15.0;}//кельвины KLV_pSiM1
            //CriteriumDown = 2.0; CriteriumUp = 10.0;}//кельвины KLV_pSiM1
        else if(TestName.contains(KLV_SiM1) || TestName.contains(KLVSiM1)){
            CriteriumDown = 0.1; CriteriumUp = 15.0;}//кельвины KLV_SiM1
            //CriteriumDown = 2.0; CriteriumUp = 10.0;}//кельвины KLV_SiM1
//-------------------------------------------------------------------------------------------------------------
        //Цепочки контактов M1-Si
        QString dZnM1 = "dZnM1", dZ_nM1 = "dZ_nM1";//на N-моноSi
        QString dZpM1 = "dZpM1", dZ_pM1 = "dZ_pM1";//на P-моноSi
        QString dZnSiM1 = "dZnSiM1", dZ_nSiM1 = "dZ_nSiM1";//на N-полиSi
        QString dZpSiM1 = "dZpSiM1", dZ_pSiM1 = "dZ_pSiM1";//на P-полиSi
        QString dZSiM1 = "dZSiM1", dZ_SiM1 = "dZ_SiM1";//на нелегированном полиSi

        if(TestName.contains(dZnM1) || TestName.contains(dZ_nM1)){
            CriteriumDown = 0.1; CriteriumUp = 15.0;}//цепочки dZnM1
            //CriteriumDown = 2.0; CriteriumUp = 10.0;}//цепочки dZnM1
        else if(TestName.contains(dZpM1) || TestName.contains(dZ_pM1)){
            CriteriumDown = 0.1; CriteriumUp = 15.0;}//цепочки dZpM1
            //CriteriumDown = 2.0; CriteriumUp = 10.0;}//цепочки dZpM1
        else if(TestName.contains(dZnSiM1) || TestName.contains(dZ_nSiM1)){
            CriteriumDown = 0.1; CriteriumUp = 15.0;}//цепочки dZnSiM1
            //CriteriumDown = 2.0; CriteriumUp = 10.0;}//цепочки dZnSiM1
        else if(TestName.contains(dZpSiM1) || TestName.contains(dZ_pSiM1)){
            CriteriumDown = 0.1; CriteriumUp = 15.0;}//цепочки dZpSiM1
            //CriteriumDown = 2.0; CriteriumUp = 10.0;}//цепочки dZpSiM1
        else if(TestName.contains(dZSiM1) || TestName.contains(dZ_SiM1)){
            CriteriumDown = 0.1; CriteriumUp = 15.0;}//кельвины KLV_SiM1
            //CriteriumDown = 2.0; CriteriumUp = 10.0;}//кельвины KLV_SiM1
//-------------------------------------------------------------------------------------------------------------
        //Кельвины Mеталл-Mеталл
        QString KLV_M1_M2 = "KLV_M1_M2", KLV_M1M2 = "KLV_M1M2";
        QString KLV_M2_M3 = "KLV_M2_M3", KLV_M2M3 = "KLV_M2M3";
        QString KLV_M3_M4 = "KLV_M3_M4", KLV_M3M4 = "KLV_M3M4";
        QString KLV_M1_M4 = "KLV_M1_M4", KLV_M1M4 = "KLV_M1M4";

        if(TestName.contains(KLV_M1_M2) || TestName.contains(KLV_M1M2)){
            CriteriumDown = 0.1; CriteriumUp = 2.5;}//кельвины M1_M2
            //CriteriumDown = 0.1; CriteriumUp = 1.5;}//кельвины M1_M2
        else if(TestName.contains(KLV_M2_M3) || TestName.contains(KLV_M2M3)){
            CriteriumDown = 0.1; CriteriumUp = 2.5;}//кельвины M2_M3
            //CriteriumDown = 0.1; CriteriumUp = 1.5;}//кельвины M2_M3
        else if(TestName.contains(KLV_M3_M4) || TestName.contains(KLV_M3M4)){
            CriteriumDown = 0.1; CriteriumUp = 2.5;}//кельвины M3_M4
            //CriteriumDown = 0.1; CriteriumUp = 1.5;}//кельвины M3_M4
        else if(TestName.contains(KLV_M1_M4) || TestName.contains(KLV_M1M4)){
            CriteriumDown = 0.1; CriteriumUp = 7.5;}//кельвины M1_M4
            //CriteriumDown = 0.1; CriteriumUp = 4.5;}//кельвины M1_M4
//-------------------------------------------------------------------------------------------------------------
        //Цепочки контактов Mетал-Mеталл
        QString dZ_M1M2 = "dZ_M1M2", dZM1M2 = "dZM1M2", Z_M1M2 = "Z_M1M2", ZM1M2 = "ZM1M2";
        QString dZ_M2M3 = "dZ_M2M3", dZM2M3 = "dZM2M3", Z_M2M3 = "Z_M2M3", ZM2M3 = "ZM2M2";
        QString dZ_M3M4 = "dZ_M3M4", dZM3M4 = "dZM3M4", Z_M3M4 = "Z_M3M4", ZM3M4 = "ZM3M4";
        QString dZ_M1M4 = "dZ_M1M4", dZM1M4 = "dZM1M4", Z_M1M4 = "Z_M1M4", ZM1M4 = "ZM1M4";

        if(TestName.contains(dZ_M1M2) || TestName.contains(dZM1M2)
                || TestName.contains(Z_M1M2) || TestName.contains(ZM1M2)){
                CriteriumDown = 0.1; CriteriumUp = 2.5;}//цепочки M1_M2
                //CriteriumDown = 0.1; CriteriumUp = 1.5;}//цепочки M1_M2
        else if(TestName.contains(dZ_M2M3) || TestName.contains(dZM2M3)
                || TestName.contains(Z_M2M3) || TestName.contains(ZM2M3)){
                CriteriumDown = 0.1; CriteriumUp = 2.5;}//цепочки M2_M3
                //CriteriumDown = 0.1; CriteriumUp = 1.5;}//цепочки M2_M3
        else if(TestName.contains(dZ_M3M4) || TestName.contains(dZM3M4)
                || TestName.contains(Z_M3M4) || TestName.contains(ZM3M4)){
                CriteriumDown = 0.1; CriteriumUp = 2.5;}//цепочки M3_M4
                //CriteriumDown = 0.1; CriteriumUp = 1.5;}//цепочки M3_M4
        else if(TestName.contains(dZ_M1M4) || TestName.contains(dZM1M4)
                || TestName.contains(Z_M1M4) || TestName.contains(ZM1M4)){
                CriteriumDown = 0.1; CriteriumUp = 7.5;}//цепочки M1_M4
                //CriteriumDown = 0.1; CriteriumUp = 4.5;}//цепочки M1_M4
//-------------------------------------------------------------------------------------------------------------
        //Структуры Ван-дер-Пау
        QString VDP = "VDP";
        QString VDPnWell = "VDPnWell";
        QString VDPpWell = "VDPpWell";
        QString VDPn = "VDPn";
        QString VDPp = "VDPp";
        QString VDPnSi = "VDPnSi";
        QString VDPpSi = "VDPpSi";

        if(TestName.contains(VDPnWell) || (TestName.contains(VDP) && TestName.contains("n")
           && (TestName.contains("Well") || TestName.contains("well")))){
                CriteriumDown = 0.1; CriteriumUp = 5600.0;}//структура VDPnWell
        else if(TestName.contains(VDPpWell) || (TestName.contains(VDP) && TestName.contains("p")
             && (TestName.contains("Well") || TestName.contains("well")))){
                CriteriumDown = 0.1; CriteriumUp = 4000.0;}//структура VDPpWell
        else if(TestName.contains(VDPn) || (TestName.contains(VDP) && TestName.contains("n"))){
                CriteriumDown = 0.1; CriteriumUp = 50.0;}//структура VDPn
        else if(TestName.contains(VDPp) || (TestName.contains(VDP) && TestName.contains("p"))){
                CriteriumDown = 0.1; CriteriumUp = 100.0;}//структура VDPp
        else if(TestName.contains(VDPnSi) || (TestName.contains(VDP) && TestName.contains("n")
                && TestName.contains("Si"))){
                CriteriumDown = 0.1; CriteriumUp = 300.0;}//структура VDPnSi
        else if(TestName.contains(VDPpSi) || (TestName.contains(VDP) && TestName.contains("p")
                && TestName.contains("Si"))){
                CriteriumDown = 0.1; CriteriumUp = 200.0;}//структура VDPpSi
//-------------------------------------------------------------------------------------------------------------
        //ЕМКОСТИ
        QString CpSinWell = "CpSinWell", CnSipWell = "CnSipWell";

        //Емкость между слоями P+Poly и nWell
        if(TestName.contains(CpSinWell) || (TestName.contains("Cp") && TestName.contains("Si")
           && (TestName.contains("n") || TestName.contains("N"))
           && (TestName.contains("Well") || TestName.contains("well")))){
           CriteriumDown = 4.6*(1e-15); CriteriumUp = 5.5*(1e-15);}//емкость CpSinWell
        //Емкость между слоями N+Poly и pWell
        else if(TestName.contains(CnSipWell) || (TestName.contains("Cn") && TestName.contains("Si")
           && (TestName.contains("p") || TestName.contains("P"))
           && (TestName.contains("Well") || TestName.contains("well")))){
           CriteriumDown = 4.6*(1e-15); CriteriumUp = 5.5*(1e-15);}//емкость CnSipWell

//-------------------------------------------------------------------------------------------------------------
        //ДИОДЫ
        QString Diod = "Diod", diod = "diod";

        //Диод на N-кармане
        if((TestName.contains(Diod) || TestName.contains(diod))
           && (TestName.contains("n") || TestName.contains("N")
           || TestName.contains("pn") || TestName.contains("PN"))){
           CriteriumDown = -2.0*(1e-12); CriteriumUp = 0.0;}// nDiod
        //Диод на N-кармане
        else if((TestName.contains(Diod) || TestName.contains(diod))
             && (TestName.contains("n") || TestName.contains("N")
             || TestName.contains("pn") || TestName.contains("PN"))
             && (TestName.contains("Well") || TestName.contains("well"))){
             CriteriumDown = -2.0*(1e-12); CriteriumUp = 0.0;}// nDiod
        //Диод на P-кармане
        else if((TestName.contains(Diod) || TestName.contains(diod))
             && (TestName.contains("p") || TestName.contains("P")
             || TestName.contains("np") || TestName.contains("NP"))){
             CriteriumDown = 0.0; CriteriumUp = 2.0*(1e-12);}// pDiod
        //Диод на P-кармане
        else if((TestName.contains(Diod) || TestName.contains(diod))
             && (TestName.contains("p") || TestName.contains("P")
             || TestName.contains("np") || TestName.contains("NP"))
             && (TestName.contains("Well") || TestName.contains("well"))){
             CriteriumDown = 0.0; CriteriumUp = 2.0*(1e-12);}// pDiod
//-------------------------------------------------------------------------------------------------------------
        //ТРАНЗИСТОРЫ
        QString An("An"), Ap("Ap"), Rn("Rn"), Rp("Rp"), Hn("Hn"), Hp("Hp");
        QString Vt("Vt"), Vbr("Vbr");
        //ПОРОГОВЫЕ НАПРЯЖЕНИЯ
        //TrAn
        if(TestName.contains(An) && TestName.contains(Vt))
        {
            CriteriumDown = 0.55; CriteriumUp = 0.70;
            //CriteriumDown = 0.60; CriteriumUp = 0.64;
        }
        //TrAp
        else if(TestName.contains(Ap) && TestName.contains(Vt))
        {
            CriteriumDown = -0.70; CriteriumUp = -0.50;
            //CriteriumDown = -0.520; CriteriumUp = -0.505;
        }
        //TrRn
        else if(TestName.contains(Rn) && TestName.contains(Vt))
        {
            CriteriumDown = 0.55; CriteriumUp = 0.70;
            //CriteriumDown = 0.60; CriteriumUp = 0.65;
        }
        //TrRp
        else if(TestName.contains(Rp) && TestName.contains(Vt))
        {
            CriteriumDown = -0.70; CriteriumUp = -0.50;
            //CriteriumDown = -0.525; CriteriumUp = -0.490;
        }
        //TrHp
        else if(TestName.contains(Hp) && TestName.contains(Vt))
        {
            CriteriumDown = -0.70; CriteriumUp = -0.50;
            //CriteriumDown = -0.53; CriteriumUp = -0.48;
        }
        //TrHn
        else if(TestName.contains(Hn) && TestName.contains(Vt))
        {
            CriteriumDown = 0.55; CriteriumUp = 0.70;
            //CriteriumDown = 0.59; CriteriumUp = 0.66;
        }
//-------------------------------------------------------------------------------------------------------------
        //ПОРОГОВЫЕ НАПРЯЖЕНИЯ ОБРАТНОГО ТРАНЗИСТОРА
        QString revers("revers");
        //TrAn
        if(TestName.contains(An) && TestName.contains(Vt) && TestName.contains(revers))
        {
            CriteriumDown = 0.55; CriteriumUp = 30.00;
            //CriteriumDown = 0.60; CriteriumUp = 0.64;
        }
        //TrAp
        else if(TestName.contains(Ap) && TestName.contains(Vt) && TestName.contains(revers))
        {
            CriteriumDown = -30.0; CriteriumUp = -0.50;
            //CriteriumDown = -0.520; CriteriumUp = -0.505;
        }
        //TrRn
        else if(TestName.contains(Rn) && TestName.contains(Vt) && TestName.contains(revers))
        {
            CriteriumDown = 0.55; CriteriumUp = 30.0;
            //CriteriumDown = 0.60; CriteriumUp = 0.65;
        }
        //TrRp
        else if(TestName.contains(Rp) && TestName.contains(Vt) && TestName.contains(revers))
        {
            CriteriumDown = -30.00; CriteriumUp = -0.50;
            //CriteriumDown = -0.525; CriteriumUp = -0.490;
        }
        //TrHn
        else if(TestName.contains(Hn) && TestName.contains(Vt) && TestName.contains(revers))
        {
            CriteriumDown = 0.55; CriteriumUp = 30.0;
            //CriteriumDown = 0.59; CriteriumUp = 0.66;
        }
        //TrHp
        else if(TestName.contains(Hp) && TestName.contains(Vt) && TestName.contains(revers))
        {
            CriteriumDown = -30.0; CriteriumUp = -0.50;
            //CriteriumDown = -0.53; CriteriumUp = -0.48;
        }
//-------------------------------------------------------------------------------------------------------------
        //КРУТИЗНА
        QString Be("Be");
        //An
        if(TestName.contains(An) && TestName.contains(Be))
        {
            CriteriumDown = 2.2*(1e-4); CriteriumUp = 2.6*(1e-4);
        }
        //Ap
        else if(TestName.contains(Ap) && TestName.contains(Be))
        {
            CriteriumDown = 4.58*(1e-5); CriteriumUp = 6.21*(1e-5);
        }
        //Rn
        if(TestName.contains(Rn) && TestName.contains(Be))
        {
            CriteriumDown = 2.2*(1e-4); CriteriumUp = 2.6*(1e-4);
        }
        //Rp
        else if(TestName.contains(Rp) && TestName.contains(Be))
        {
            CriteriumDown = 5.26*(1e-5); CriteriumUp = 6.87*(1e-5);
        }
        //Hn
        if(TestName.contains(Hn) && TestName.contains(Be))
        {
            CriteriumDown = 2.2*(1e-4); CriteriumUp = 2.6*(1e-4);
        }
        //Hp
        else if(TestName.contains(Hp) && TestName.contains(Be))
        {
            CriteriumDown = 5.15*(1e-5); CriteriumUp = 6.95*(1e-5);
        }
//-------------------------------------------------------------------------------------------------------------
        //НАПРЯЖЕНИЯ ПРОБОЯ СТОК-ИСТОК
        //TrAn
        if(TestName.contains(An) && TestName.contains(Vbr))
        {
            CriteriumDown = 8.0; CriteriumUp = 30.0;
            //CriteriumDown = 8.65; CriteriumUp = 8.80;
        }
        //TrAp
        else if(TestName.contains(Ap) && TestName.contains(Vbr))
        {
            CriteriumDown = -30.0; CriteriumUp = -8.0;
            //CriteriumDown = -8.13; CriteriumUp = -7.93;
        }
        //TrRn
        else if(TestName.contains(Rn) && TestName.contains(Vbr))
        {
            CriteriumDown = 8.0; CriteriumUp = 30.0;
            //CriteriumDown = 8.98; CriteriumUp = 9.10;
        }
        //TrRp
        else if(TestName.contains(Rp) && TestName.contains(Vbr))
        {
            CriteriumDown = -30.0; CriteriumUp = -8.0;
            //CriteriumDown = -9.20; CriteriumUp = -9.06;
        }
        //TrHn
        else if(TestName.contains(Hn) && TestName.contains(Vbr))
        {
            CriteriumDown = 8.0; CriteriumUp = 30.0;
            //CriteriumDown = 8.92; CriteriumUp = 9.20;
        }
        //TrHp
        else if(TestName.contains(Hp) && TestName.contains(Vbr))
        {
            CriteriumDown = -30.0; CriteriumUp = -8.0;
            //CriteriumDown = -9.25; CriteriumUp = -8.96;
        }
//-------------------------------------------------------------------------------------------------------------
        //ТОК УТЕЧКИ ЗАТВОР АБСОЛЮТНЫЙ
        QString leak("leak"), w("w");
        QString Gleak("Gleak"), G("G");
        //TrAn
        if(TestName.contains(An) &&
          (TestName.contains(Gleak) ||
          (TestName.contains(G) && TestName.contains(leak) && !TestName.contains(w))))
        {
            //CriteriumDown = -10.0*(1e-12); CriteriumUp = 10.0*(1e-12);
            //CriteriumDown = 0.0; CriteriumUp = 6.0*(1e-12);
            CriteriumDown = 0.0; CriteriumUp = 1e-12;
        }
        //TrAp
        else if(TestName.contains(Ap) &&
          (TestName.contains(Gleak) ||
          (TestName.contains(G) && TestName.contains(leak) && !TestName.contains(w))))
        {
            //CriteriumDown = -10.0*(1e-12); CriteriumUp = 10.0*(1e-12);
            //CriteriumDown = -10.0*(1e-12); CriteriumUp = 0.0;
            CriteriumDown = -1e-12; CriteriumUp = 0.0;
        }
        //TrRn
        else if(TestName.contains(Rn) &&
          (TestName.contains(Gleak) ||
          (TestName.contains(G) && TestName.contains(leak) && !TestName.contains(w))))
        {
            //CriteriumDown = -10.0*(1e-12); CriteriumUp = 10.0*(1e-12);
            //CriteriumDown = 0.0; CriteriumUp = 10.0*(1e-12);
            CriteriumDown = 0.0; CriteriumUp = 1e-12;
        }
        //TrRp
        else if(TestName.contains(Rp) &&
          (TestName.contains(Gleak) ||
          (TestName.contains(G) && TestName.contains(leak) && !TestName.contains(w))))
        {
            //CriteriumDown = -10.0*(1e-12); CriteriumUp = 10.0*(1e-12);
            //CriteriumDown = -10.0*(1e-12); CriteriumUp = 0.0;
            CriteriumDown = -1e-12; CriteriumUp = 0.0;
        }
        //TrHn
        else if(TestName.contains(Hn) &&
          (TestName.contains(Gleak) ||
          (TestName.contains(G) && TestName.contains(leak) && !TestName.contains(w))))
        {
            //CriteriumDown = -10.0*(1e-12); CriteriumUp = 10.0*(1e-12);
            //CriteriumDown = 0.0; CriteriumUp = 10.0*(1e-12);
            CriteriumDown = 0.0; CriteriumUp = 1e-12;
        }
        //TrHp
        else if(TestName.contains(Hp) &&
          (TestName.contains(Gleak) ||
          (TestName.contains(G) && TestName.contains(leak) && !TestName.contains(w))))
        {
            //CriteriumDown = -10.0*(1e-12); CriteriumUp = 10.0*(1e-12);
            //CriteriumDown = -10.0*(1e-12); CriteriumUp = 0.0;
            CriteriumDown = -1e-12; CriteriumUp = 0.0;
        }
//-------------------------------------------------------------------------------------------------------------
        //ТОК УТЕЧКИ СТОК-ИСТОК АБСОЛЮТНЫЙ
        QString DSleak("DSleak"), DS("DS");
        double LEN = 3.5;//мкм
        //TrAn
        if(TestName.contains(An) &&
          (TestName.contains(DSleak) ||
          (TestName.contains(DS) && TestName.contains(leak) && !TestName.contains(w))))
        {
            //CriteriumDown = -6.0*(1e-12)*LEN; CriteriumUp = 6.0*(1e-12)*LEN;
            //CriteriumDown = 0.0; CriteriumUp = 6.0*(1e-12)*LEN;
            CriteriumDown = 0.0;// 1.0*(1e-30)*LEN;
            CriteriumUp = 6.0*(1e-12)*LEN;
        }
        //TrAp
        else if(TestName.contains(Ap) &&
          (TestName.contains(DSleak) ||
          (TestName.contains(DS) && TestName.contains(leak) && !TestName.contains(w))))
        {
            //CriteriumDown = -10.0*(1e-12)*LEN; CriteriumUp = 10.0*(1e-12)*LEN;
            //CriteriumDown = -10.0*(1e-12)*LEN; CriteriumUp = 0.0;
            CriteriumDown = -10.0*(1e-12)*LEN;
            CriteriumUp = 0.0;// -1.0*(1e-30)*LEN;
        }
        //TrRn
        else if(TestName.contains(Rn) &&
          (TestName.contains(DSleak) ||
          (TestName.contains(DS) && TestName.contains(leak) && !TestName.contains(w))))
        {
            //CriteriumDown = -6.0*(1e-12)*LEN; CriteriumUp = 6.0*(1e-12)*LEN;
            //CriteriumDown = 0.0; CriteriumUp = 6.0*(1e-12)*LEN;
            CriteriumDown = 0.0; //1.0*(1e-30)*LEN;
            CriteriumUp = 10.0*(1e-12)*LEN;
        }
        //TrRp
        else if(TestName.contains(Rp) &&
          (TestName.contains(DSleak) ||
          (TestName.contains(DS) && TestName.contains(leak) && !TestName.contains(w))))
        {
            //CriteriumDown = -10.0*(1e-12)*LEN; CriteriumUp = 10.0*(1e-12)*LEN;
            //CriteriumDown = -10.0*(1e-12)*LEN; CriteriumUp = 0.0;
            CriteriumDown = -10.0*(1e-12)*LEN;
            CriteriumUp = 0.0;//-1.0*(1e-30)*LEN;
        }
        //TrHn
        else if(TestName.contains(Hn) &&
          (TestName.contains(DSleak) ||
          (TestName.contains(DS) && TestName.contains(leak) && !TestName.contains(w))))
        {
            //CriteriumDown = -6.0*(1e-12)*LEN; CriteriumUp = 6.0*(1e-12)*LEN;
            //CriteriumDown = 0.0; CriteriumUp = 6.0*(1e-12)*LEN;
            CriteriumDown = 0.0;// 1.0*(1e-30)*LEN;
            CriteriumUp = 10.0*(1e-12)*LEN;
        }
        //TrHp
        else if(TestName.contains(Hp) &&
          (TestName.contains(DSleak) ||
           (TestName.contains(DS) && TestName.contains(leak) && !TestName.contains(w))))
        {
            //CriteriumDown = -10.0*(1e-12)*LEN; CriteriumUp = 10.0*(1e-12)*LEN;
            //CriteriumDown = -10.0*(1e-12)*LEN; CriteriumUp = 0.0;
            CriteriumDown = -10.0*(1e-12)*LEN;
            CriteriumUp = 0.0;// -1.0*(1e-30)*LEN;
        }
//-------------------------------------------------------------------------------------------------------------
        //ТОК УТЕЧКИ СТОК-ИСТОК ПРИВЕДЕННЫЙ
        QString DSw_leak("DSw_leak");// DSw("DSw");
        //TrAn
        if(TestName.contains(An) &&
          (TestName.contains(DSw_leak) ||
          (TestName.contains(DS) && TestName.contains(leak) && TestName.contains(w))))
        {
            //CriteriumDown = -6.0*(1e-12); CriteriumUp = 6.0*(1e-12);
            //CriteriumDown = 0.0; CriteriumUp = 6.0*(1e-12);
            CriteriumDown = 0.0;// 1.0*(1e-30);
            CriteriumUp = 6.0*(1e-12);
        }
        //TrAp
        else if(TestName.contains(Ap) &&
          (TestName.contains(DSw_leak) ||
          (TestName.contains(DS) && TestName.contains(leak) && TestName.contains(w))))
        {
            //CriteriumDown = -10.0*(1e-12); CriteriumUp = 10.0*(1e-12);
            //CriteriumDown = -10.0*(1e-12); CriteriumUp = 0.0;
            CriteriumDown = -10.0*(1e-12);
            CriteriumUp = 0.0;// -1.0*(1e-30);
        }
        //TrRn
        else if(TestName.contains(Rn) &&
          (TestName.contains(DSw_leak) ||
          (TestName.contains(DS) && TestName.contains(leak) && TestName.contains(w))))
        {
            //CriteriumDown = -6.0*(1e-12); CriteriumUp = 6.0*(1e-12);
            //CriteriumDown = 0.0; CriteriumUp = 6.0*(1e-12);
            CriteriumDown = 0.0;// 1.0*(1e-30);
            CriteriumUp = 10.0*(1e-12);
        }
        //TrRp
        else if(TestName.contains(Rp) &&
          (TestName.contains(DSw_leak) ||
          (TestName.contains(DS) && TestName.contains(leak) && TestName.contains(w))))
        {
            //CriteriumDown = -10.0*(1e-12); CriteriumUp = 10.0*(1e-12);
            //CriteriumDown = -10.0*(1e-12); CriteriumUp = 0.0;
            CriteriumDown = -10.0*(1e-12);
            CriteriumUp = 0.0;// -1.0*(1e-30);
        }
        //TrHn
        else if(TestName.contains(Hn) &&
          (TestName.contains(DSw_leak) ||
          (TestName.contains(DS) && TestName.contains(leak) && TestName.contains(w))))
        {
            //CriteriumDown = -6.0*(1e-12); CriteriumUp = 6.0*(1e-12);
            //CriteriumDown = 0.0; CriteriumUp = 6.0*(1e-12);
            CriteriumDown = 0.0;// 1.0*(1e-30);
            CriteriumUp = 10.0*(1e-12);
        }
        //TrHp
        else if(TestName.contains(Hp) &&
          (TestName.contains(DSw_leak) ||
           (TestName.contains(DS) && TestName.contains(leak) && TestName.contains(w))))
        {
            //CriteriumDown = -10.0*(1e-12); CriteriumUp = 10.0*(1e-12);
            //CriteriumDown = -10.0*(1e-12); CriteriumUp = 0.0;
            CriteriumDown = -10.0*(1e-12);
            CriteriumUp = 0.0; // -1.0*(1e-30);
        }
//-------------------------------------------------------------------------------------------------------------
        //ТОК НАСЫЩЕНИЯ АБСОЛЮТНЫЙ
        QString DScurrent("DScurrent"), current("current");//
        //TrAn
        if(TestName.contains(An) &&
          (TestName.contains(DScurrent) ||
          (TestName.contains(DS) && TestName.contains(current) && !TestName.contains(w))))
        {
            CriteriumDown = 4.2*(1e-4)*LEN; CriteriumUp = 5.2*(1e-4)*LEN;
            //CriteriumDown = 4.8*(1e-4)*LEN; CriteriumUp = 5.13*(1e-4)*LEN;
        }
        //TrAp
        else if(TestName.contains(Ap) &&
          (TestName.contains(DScurrent) ||
          (TestName.contains(DS) && TestName.contains(current) && !TestName.contains(w))))
        {
            CriteriumDown = -3.3*(1e-4)*LEN; CriteriumUp = -2.3*(1e-4)*LEN;
            //CriteriumDown = -2.7*(1e-4)*LEN; CriteriumUp = -2.35*(1e-4)*LEN;
        }
        //TrRn
        else if(TestName.contains(Rn) &&
          (TestName.contains(DScurrent) ||
          (TestName.contains(DS) && TestName.contains(current) && !TestName.contains(w))))
        {
            CriteriumDown = 4.2*(1e-4)*LEN; CriteriumUp = 5.2*(1e-4)*LEN;
            //CriteriumDown = 5.3*(1e-4)*LEN; CriteriumUp = 5.6*(1e-4)*LEN;
        }
        //TrRp
        else if(TestName.contains(Rp) &&
          (TestName.contains(DScurrent) ||
          (TestName.contains(DS) && TestName.contains(current) && !TestName.contains(w))))
        {
            CriteriumDown = -3.3*(1e-4)*LEN; CriteriumUp = -2.3*(1e-4)*LEN;
            //CriteriumDown = -3.0*(1e-4)*LEN; CriteriumUp = -2.7*(1e-4)*LEN;
        }
        //TrHn
        else if(TestName.contains(Hn) &&
          (TestName.contains(DScurrent) ||
          (TestName.contains(DS) && TestName.contains(current) && !TestName.contains(w))))
        {
            CriteriumDown = 4.2*(1e-4)*LEN; CriteriumUp = 5.2*(1e-4)*LEN;
            //CriteriumDown = 5.3*(1e-4)*LEN; CriteriumUp = 5.6*(1e-4)*LEN;
        }
        //TrHp
        else if(TestName.contains(Hp) &&
          (TestName.contains(DScurrent) ||
          (TestName.contains(DS) && TestName.contains(current) && !TestName.contains(w))))
        {
            CriteriumDown = -3.3*(1e-4)*LEN; CriteriumUp = -2.3*(1e-4)*LEN;
            //CriteriumDown = -3.1*(1e-4)*LEN; CriteriumUp = -2.6*(1e-4)*LEN;
        }
//-------------------------------------------------------------------------------------------------------------
        //ТОК НАСЫЩЕНИЯ ПРИВЕДЕННЫЙ
        QString DSw_driver("DSw_driver"), driver("driver");
        //TrAn
        if(TestName.contains(An) &&
          (TestName.contains(DSw_driver) ||
          (TestName.contains(DS) && TestName.contains(driver) && TestName.contains(w))))
        {
            CriteriumDown = 4.2*(1e-4); CriteriumUp = 5.2*(1e-4);
            //CriteriumDown = 4.8*(1e-4); CriteriumUp = 5.13*(1e-4);
        }
        //TrAp
        else if(TestName.contains(Ap) &&
          (TestName.contains(DSw_driver) ||
          (TestName.contains(DS) && TestName.contains(driver) && TestName.contains(w))))
        {
            CriteriumDown = -3.3*(1e-4); CriteriumUp = -2.3*(1e-4);
            //CriteriumDown = -2.7*(1e-4); CriteriumUp = -2.35*(1e-4);
        }
        //TrRn
        else if(TestName.contains(Rn) &&
          (TestName.contains(DSw_driver) ||
          (TestName.contains(DS) && TestName.contains(driver) && TestName.contains(w))))
        {
            CriteriumDown = 4.2*(1e-4); CriteriumUp = 5.2*(1e-4);
            //CriteriumDown = 5.3*(1e-4); CriteriumUp = 5.6*(1e-4);
        }
        //TrRp
        else if(TestName.contains(Rp) &&
          (TestName.contains(DSw_driver) ||
          (TestName.contains(DS) && TestName.contains(driver) && TestName.contains(w))))
        {
            CriteriumDown = -3.3*(1e-4); CriteriumUp = -2.3*(1e-4);
            //CriteriumDown = -3.0*(1e-4); CriteriumUp = -2.7*(1e-4);
        }
        //TrHn
        else if(TestName.contains(Hn) &&
          (TestName.contains(DSw_driver) ||
          (TestName.contains(DS) && TestName.contains(driver) && TestName.contains(w))))
        {
            CriteriumDown = 4.2*(1e-4); CriteriumUp = 5.2*(1e-4);
            //CriteriumDown = 5.3*(1e-4); CriteriumUp = 5.6*(1e-4);
        }
        //TrHp
        else if(TestName.contains(Hp) &&
          (TestName.contains(DSw_driver) ||
          (TestName.contains(DS) && TestName.contains(driver) && TestName.contains(w))))
        {
            CriteriumDown = -3.3*(1e-4); CriteriumUp = -2.3*(1e-4);
            //CriteriumDown = -3.1*(1e-4); CriteriumUp = -2.6*(1e-4);
        }

//-------------------------------------------------------------------------------------------------------------
}//End of DesignRules035
