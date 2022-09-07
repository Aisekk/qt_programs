#include "BigNorms.h"

//Члены-функции setTestIntervals
void BigNorms::SIL09(const QString& TestName, double& CriteriumDown, double& CriteriumUp)
{
    if(TestName.contains(tRZnTiSi) && TestName.contains(w09)){
        CriteriumDown = 0.1; CriteriumUp = 1000.0;}//резисторы tRZnTiSi09
    else if(TestName.contains(tRZpTiSi) && TestName.contains(w09)){
        CriteriumDown = 0.1; CriteriumUp = 1000.0;}//резисторы tRZpTiSi09
    else if(TestName.contains(tRZnSiTiSi) && TestName.contains(w09)){
        CriteriumDown = 0.1; CriteriumUp = 1000.0;}//резисторы tRZnSiTiSi09
    else if(TestName.contains(tRZpSiTiSi) && TestName.contains(w09)){
        CriteriumDown = 0.1; CriteriumUp = 1000.0;}//резисторы tRZpSiTiSi09
    else if(TestName.contains(tRZSiTiSi) && TestName.contains(w09)){
        CriteriumDown = 0.1; CriteriumUp = 1000.0;}//резисторы tRZSiTiSi09
}
void BigNorms::SIL05(const QString& TestName, double& CriteriumDown, double& CriteriumUp)
{
    if(TestName.contains(tRZnTiSi) && TestName.contains(w05)){
        CriteriumDown = 0.1; CriteriumUp = 1000.0;}//резисторы tRZnTiSi05
    else if(TestName.contains(tRZpTiSi) && TestName.contains(w05)){
        CriteriumDown = 0.1; CriteriumUp = 1000.0;}//резисторы tRZpTiSi05
    else if(TestName.contains(tRZnSiTiSi) && TestName.contains(w05)){
        CriteriumDown = 0.1; CriteriumUp = 1000.0;}//резисторы tRZnSiTiSi05
    else if(TestName.contains(tRZpSiTiSi) && TestName.contains(w05)){
        CriteriumDown = 0.1; CriteriumUp = 1000.0;}//резисторы tRZpSiTiSi05
    else if(TestName.contains(tRZSiTiSi) && TestName.contains(w05)){
        CriteriumDown = 0.1; CriteriumUp = 1000.0;}//резисторы tRZSiTiSi05
}
void BigNorms::SIL035(const QString& TestName, double& CriteriumDown, double& CriteriumUp)
{
    if(TestName.contains(tRZnTiSi) && TestName.contains(w035)){
        CriteriumDown = 0.1; CriteriumUp = 1000.0;}//резисторы tRZnTiSi035
    else if(TestName.contains(tRZpTiSi) && TestName.contains(w035)){
        CriteriumDown = 0.1; CriteriumUp = 1000.0;}//резисторы tRZpTiSi035
    else if(TestName.contains(tRZnSiTiSi) && TestName.contains(w035)){
        CriteriumDown = 0.1; CriteriumUp = 1000.0;}//резисторы tRZnSiTiSi035
    else if(TestName.contains(tRZpSiTiSi) && TestName.contains(w035)){
        CriteriumDown = 0.1; CriteriumUp = 1000.0;}//резисторы tRZpSiTiSi035
    else if(TestName.contains(tRZSiTiSi) && TestName.contains(w035)){
        CriteriumDown = 0.1; CriteriumUp = 1000.0;}//резисторы tRZSiTiSi035
}
void BigNorms::KLV_M1Si(const QString& TestName, double& CriteriumDown, double& CriteriumUp)
{
    if(TestName.contains(KLV_nM1) || TestName.contains(KLVnM1)){
        CriteriumDown = 0.1; CriteriumUp = 1000.0;}//кельвины KLV_nM1
    else if(TestName.contains(KLV_pM1) || TestName.contains(KLVpM1)){
        CriteriumDown = 0.1; CriteriumUp = 1000.0;}//кельвины KLV_pM1
    else if(TestName.contains(KLV_nSiM1) || TestName.contains(KLVnSiM1)){
        CriteriumDown = 0.1; CriteriumUp = 1000.0;}//кельвины KLV_nSiM1
    else if(TestName.contains(KLV_pSiM1) || TestName.contains(KLVpSiM1)){
        CriteriumDown = 0.1; CriteriumUp = 1000.0;}//кельвины KLV_pSiM1
    else if(TestName.contains(KLV_SiM1) || TestName.contains(KLVSiM1)){
        CriteriumDown = 0.1; CriteriumUp = 1000.0;}//кельвины KLV_SiM1
}
void BigNorms::Z_M1Si(const QString& TestName, double& CriteriumDown, double& CriteriumUp)
{
    if(TestName.contains(dZnM1) || TestName.contains(dZ_nM1)){
        CriteriumDown = 0.1; CriteriumUp = 1000.0;}//цепочки dZnM1
    else if(TestName.contains(dZpM1) || TestName.contains(dZ_pM1)){
        CriteriumDown = 0.1; CriteriumUp = 1000.0;}//цепочки dZpM1
    else if(TestName.contains(dZnSiM1) || TestName.contains(dZ_nSiM1)){
        CriteriumDown = 0.1; CriteriumUp = 1000.0;}//цепочки dZnSiM1
    else if(TestName.contains(dZpSiM1) || TestName.contains(dZ_pSiM1)){
        CriteriumDown = 0.1; CriteriumUp = 1000.0;}//цепочки dZpSiM1
    else if(TestName.contains(dZSiM1) || TestName.contains(dZ_SiM1)){
        CriteriumDown = 0.1; CriteriumUp = 1000.0;}//кельвины KLV_SiM1
}

void BigNorms::Meanders(const QString& TestName, double& CriteriumDown, double& CriteriumUp)
{
    if(TestName.contains(dMeander1) || (TestName.contains(Meander) && TestName.contains(One)))
    {
        CriteriumDown = 1.0/divisorMeander; CriteriumUp = 10000.0/divisorMeander;
    }//резисторы dMeander1
    else if(TestName.contains(dMeander3) || (TestName.contains(Meander) && TestName.contains(Three)))
    {
        CriteriumDown = 1.0/divisorMeander; CriteriumUp = 10000.0/divisorMeander;
    }//резисторы dMeander3
    else if(TestName.contains(dMeander1_09) ||
           (TestName.contains(Meander) && TestName.contains(One) && TestName.contains(w09)))
    {
        CriteriumDown = 1.0/divisorMeander; CriteriumUp = 10000.0/divisorMeander;
    }//резисторы dMeander1_09
    else if(TestName.contains(dMeander3_09) ||
           (TestName.contains(Meander) && TestName.contains(Three) && TestName.contains(w09)))
    {
        CriteriumDown = 1.0/divisorMeander; CriteriumUp = 10000.0/divisorMeander;
    }//резисторы dMeander3_09
    else if(TestName.contains(dMeander2) || (TestName.contains(Meander) && TestName.contains(Two)))
    {
        CriteriumDown = 1.0/divisorMeander; CriteriumUp = 10000.0/divisorMeander;
    }//резисторы dMeander2
    else if(TestName.contains(dMeander4) || (TestName.contains(Meander) && TestName.contains(Four)))
    {
        CriteriumDown = 1.0/divisorMeander; CriteriumUp = 10000.0/divisorMeander;
    }//резисторы dMeander4
    else if(TestName.contains(dMeander2_09) ||
           (TestName.contains(Meander) && TestName.contains(Two) && TestName.contains(w09)))
    {
        CriteriumDown = 1.0/divisorMeander; CriteriumUp = 10000.0/divisorMeander;
    }//резисторы dMeander2_09
    else if(TestName.contains(dMeander4_09) ||
           (TestName.contains(Meander) && TestName.contains(Four) && TestName.contains(w09)))
    {
        CriteriumDown = 1.0/divisorMeander; CriteriumUp = 10000.0/divisorMeander;
    }//резисторы dMeander4_09
}
void BigNorms::KLV_MeMe(const QString& TestName, double& CriteriumDown, double& CriteriumUp)
{
    if(TestName.contains(KLV_M1_M2) || TestName.contains(KLV_M1M2)){
        CriteriumDown = 0.1; CriteriumUp = 100.0;}//кельвины M1_M2
    else if(TestName.contains(KLV_M2_M3) || TestName.contains(KLV_M2M3)){
        CriteriumDown = 0.1; CriteriumUp = 100.0;}//кельвины M2_M3
    else if(TestName.contains(KLV_M3_M4) || TestName.contains(KLV_M3M4)){
        CriteriumDown = 0.1; CriteriumUp = 100.0;}//кельвины M3_M4
    else if(TestName.contains(KLV_M1_M4) || TestName.contains(KLV_M1M4)){
        CriteriumDown = 0.1; CriteriumUp = 100.0;}//кельвины M1_M4
}
void BigNorms::Z_MeMe(const QString& TestName, double& CriteriumDown, double& CriteriumUp)
{
    if(TestName.contains(dZ_M1M2) || TestName.contains(dZM1M2)
            || TestName.contains(Z_M1M2) || TestName.contains(ZM1M2)){
        CriteriumDown = 0.1; CriteriumUp = 100.0;}//цепочки M1_M2
    else if(TestName.contains(dZ_M2M3) || TestName.contains(dZM2M3)
            || TestName.contains(Z_M2M3) || TestName.contains(ZM2M3)){
        CriteriumDown = 0.1; CriteriumUp = 100.0;}//цепочки M2_M3
    else if(TestName.contains(dZ_M3M4) || TestName.contains(dZM3M4)
            || TestName.contains(Z_M3M4) || TestName.contains(ZM3M4)){
        CriteriumDown = 0.1; CriteriumUp = 100.0;}//цепочки M3_M4
    else if(TestName.contains(dZ_M1M4) || TestName.contains(dZM1M4)
            || TestName.contains(Z_M1M4) || TestName.contains(ZM1M4)){
        CriteriumDown = 0.1; CriteriumUp = 100.0;}//цепочки M1_M4
}
void BigNorms::VDPs(const QString& TestName, double& CriteriumDown, double& CriteriumUp)
{
    if(TestName.contains(VDPnWell) || (TestName.contains(VDP) && TestName.contains("n")
                                       && (TestName.contains("Well") || TestName.contains("well"))))
    {
        CriteriumDown = 0.1; CriteriumUp = 1.0*1e5;
    }//структура VDPnWell
    else if(TestName.contains(VDPpWell) || (TestName.contains(VDP) && TestName.contains("p")
                                            && (TestName.contains("Well") || TestName.contains("well"))))
    {
        CriteriumDown = 0.1; CriteriumUp = 1.0*1e5;
    }//структура VDPpWell
    else if(TestName.contains(VDPn) || (TestName.contains(VDP) && TestName.contains("n")))
    {
        CriteriumDown = 0.1; CriteriumUp = 1.0*1e5;
    }//структура VDPn
    else if(TestName.contains(VDPp) || (TestName.contains(VDP) && TestName.contains("p")))
    {
        CriteriumDown = 0.1; CriteriumUp = 1.0*1e5;
    }//структура VDPp
    else if(TestName.contains(VDPnSi) || (TestName.contains(VDP) && TestName.contains("n")
                                          && TestName.contains("Si")))
    {
        CriteriumDown = 0.1; CriteriumUp = 1.0*1e5;
    }//структура VDPnSi
    else if(TestName.contains(VDPpSi) || (TestName.contains(VDP) && TestName.contains("p")
                                          && TestName.contains("Si")))
    {
        CriteriumDown = 0.1; CriteriumUp = 1.0*1e5;
    }//структура VDPpSi
}
void BigNorms::Capacity(const QString& TestName, double& CriteriumDown, double& CriteriumUp)
{
    //Емкость между слоями P+Poly и nWell
    if(TestName.contains(CpSinWell) || (TestName.contains("Cp") && TestName.contains("Si")
                                        && (TestName.contains("n") || TestName.contains("N"))
                                        && (TestName.contains("Well") || TestName.contains("well"))))
    {
        CriteriumDown = 1.0*(1e-15); CriteriumUp = 10.0*(1e-15);
    }//емкость CpSinWell
    //Емкость между слоями N+Poly и pWell
    else if(TestName.contains(CnSipWell) || (TestName.contains("Cn") && TestName.contains("Si")
                                             && (TestName.contains("p") || TestName.contains("P"))
                                             && (TestName.contains("Well") || TestName.contains("well"))))
    {
        CriteriumDown = 1.0*(1e-15); CriteriumUp = 10.0*(1e-15);
    }//емкость CnSipWell
}
void BigNorms::Diods(const QString& TestName, double& CriteriumDown, double& CriteriumUp)
{
    //Диод на N-кармане
    if((TestName.contains(Diod) || TestName.contains(diod))
            && (TestName.contains("n") || TestName.contains("N")
                || TestName.contains("pn") || TestName.contains("PN"))){
        CriteriumDown = -10.0*(1e-12); CriteriumUp = 0.0;}// nDiod
    //Диод на N-кармане
    else if((TestName.contains(Diod) || TestName.contains(diod))
            && (TestName.contains("n") || TestName.contains("N")
                || TestName.contains("pn") || TestName.contains("PN"))
            && (TestName.contains("Well") || TestName.contains("well"))){
        CriteriumDown = -10.0*(1e-12); CriteriumUp = 0.0;}// nDiod
    //Диод на P-кармане
    else if((TestName.contains(Diod) || TestName.contains(diod))
            && (TestName.contains("p") || TestName.contains("P")
                || TestName.contains("np") || TestName.contains("NP"))){
        CriteriumDown = 0.0; CriteriumUp = 10.0*(1e-12);}// pDiod
    //Диод на P-кармане
    else if((TestName.contains(Diod) || TestName.contains(diod))
            && (TestName.contains("p") || TestName.contains("P")
                || TestName.contains("np") || TestName.contains("NP"))
            && (TestName.contains("Well") || TestName.contains("well"))){
        CriteriumDown = 0.0; CriteriumUp = 10.0*(1e-12);}// pDiod
}

void BigNorms::Tr_Vt(const QString& TestName, double& CriteriumDown, double& CriteriumUp)
{
    //An
    if(TestName.contains(An) && TestName.contains(Vt))
    {
        CriteriumDown = 0.1; CriteriumUp = 10.0;
    }
    //Ap
    else if(TestName.contains(Ap) && TestName.contains(Vt))
    {
        CriteriumDown = -10.0; CriteriumUp = -0.1;
    }
    //Rn
    else if(TestName.contains(Rn) && TestName.contains(Vt))
    {
        CriteriumDown = 0.1; CriteriumUp = 10.0;
    }
    //Rp
    else if(TestName.contains(Rp) && TestName.contains(Vt))
    {
        CriteriumDown = -10.0; CriteriumUp = -1.0;
    }
    //Hn
    else if(TestName.contains(Hn) && TestName.contains(Vt))
    {
        CriteriumDown = 0.1; CriteriumUp = 10.0;
    }
    //Hp
    else if(TestName.contains(Hp) && TestName.contains(Vt))
    {
        CriteriumDown = -10.0; CriteriumUp = -0.1;
    }
}
void BigNorms::Tr_VtRevers(const QString& TestName, double& CriteriumDown, double& CriteriumUp)
{
    //An
    if(TestName.contains(An) && TestName.contains(Vt) && TestName.contains(revers))
    {
        CriteriumDown = 0.1; CriteriumUp = 30.00;
    }
    //Ap
    else if(TestName.contains(Ap) && TestName.contains(Vt) && TestName.contains(revers))
    {
        CriteriumDown = -30.0; CriteriumUp = -0.1;
    }
    //Rn
    else if(TestName.contains(Rn) && TestName.contains(Vt) && TestName.contains(revers))
    {
        CriteriumDown = 0.1; CriteriumUp = 30.0;
    }
    //Rp
    else if(TestName.contains(Rp) && TestName.contains(Vt) && TestName.contains(revers))
    {
        CriteriumDown = -30.00; CriteriumUp = -0.1;
    }
    //Hn
    else if(TestName.contains(Hn) && TestName.contains(Vt) && TestName.contains(revers))
    {
        CriteriumDown = 0.1; CriteriumUp = 30.0;
    }
    //Hp
    else if(TestName.contains(Hp) && TestName.contains(Vt) && TestName.contains(revers))
    {
        CriteriumDown = -30.0; CriteriumUp = -0.1;
    }
}
void BigNorms::Tr_Be(const QString& TestName, double& CriteriumDown, double& CriteriumUp)
{
    //An
    if(TestName.contains(An) && TestName.contains(Be))
    {
        CriteriumDown = 1.0*(1e-4); CriteriumUp = 10.0*(1e-4);
    }
    //Ap
    else if(TestName.contains(Ap) && TestName.contains(Be))
    {
        CriteriumDown = 1.0*(1e-5); CriteriumUp = 10.0*(1e-5);
    }
    //Rn
    if(TestName.contains(Rn) && TestName.contains(Be))
    {
        CriteriumDown = 1.0*(1e-4); CriteriumUp = 10.0*(1e-4);
    }
    //Rp
    else if(TestName.contains(Rp) && TestName.contains(Be))
    {
        CriteriumDown = 1.0*(1e-5); CriteriumUp = 10.0*(1e-5);
    }
    //Hn
    if(TestName.contains(Hn) && TestName.contains(Be))
    {
        CriteriumDown = 1.0*(1e-4); CriteriumUp = 10.0*(1e-4);
    }
    //Hp
    else if(TestName.contains(Hp) && TestName.contains(Be))
    {
        CriteriumDown = 1.0*(1e-5); CriteriumUp = 10.0*(1e-5);
    }
}
void BigNorms::Tr_Vbr(const QString& TestName, double& CriteriumDown, double& CriteriumUp)
{
    //An
    if(TestName.contains(An) && TestName.contains(Vbr))
    {
        CriteriumDown = 8.0; CriteriumUp = 30.0;
    }
    //Ap
    else if(TestName.contains(Ap) && TestName.contains(Vbr))
    {
        CriteriumDown = -30.0; CriteriumUp = -8.0;
    }
    //Rn
    else if(TestName.contains(Rn) && TestName.contains(Vbr))
    {
        CriteriumDown = 8.0; CriteriumUp = 30.0;
    }
    //Rp
    else if(TestName.contains(Rp) && TestName.contains(Vbr))
    {
        CriteriumDown = -30.0; CriteriumUp = -8.0;
    }
    //Hn
    else if(TestName.contains(Hn) && TestName.contains(Vbr))
    {
        CriteriumDown = 8.0; CriteriumUp = 30.0;
    }
    //Hp
    else if(TestName.contains(Hp) && TestName.contains(Vbr))
    {
        CriteriumDown = -30.0; CriteriumUp = -8.0;
    }
}
void BigNorms::Tr_Gleak(const QString& TestName, double& CriteriumDown, double& CriteriumUp)
{
    //An
    if(TestName.contains(An) &&
            (TestName.contains(Gleak) ||
             (TestName.contains(G) && TestName.contains(leak) && !TestName.contains(w))))
    {
        CriteriumDown = 0.0; CriteriumUp = 1e-12;
    }
    //Ap
    else if(TestName.contains(Ap) &&
            (TestName.contains(Gleak) ||
             (TestName.contains(G) && TestName.contains(leak) && !TestName.contains(w))))
    {
        CriteriumDown = -1e-12; CriteriumUp = 0.0;
    }
    //Rn
    else if(TestName.contains(Rn) &&
            (TestName.contains(Gleak) ||
             (TestName.contains(G) && TestName.contains(leak) && !TestName.contains(w))))
    {
        CriteriumDown = 0.0; CriteriumUp = 1e-12;
    }
    //Rp
    else if(TestName.contains(Rp) &&
            (TestName.contains(Gleak) ||
             (TestName.contains(G) && TestName.contains(leak) && !TestName.contains(w))))
    {
        CriteriumDown = -1e-12; CriteriumUp = 0.0;
    }
    //Hn
    else if(TestName.contains(Hn) &&
            (TestName.contains(Gleak) ||
             (TestName.contains(G) && TestName.contains(leak) && !TestName.contains(w))))
    {
        CriteriumDown = 0.0; CriteriumUp = 1e-12;
    }
    //Hp
    else if(TestName.contains(Hp) &&
            (TestName.contains(Gleak) ||
             (TestName.contains(G) && TestName.contains(leak) && !TestName.contains(w))))
    {
        CriteriumDown = -1e-12; CriteriumUp = 0.0;
    }
}
void BigNorms::Tr_DSleak(const QString& TestName, double& CriteriumDown, double& CriteriumUp)
{
    //An
    if(TestName.contains(An) &&
            (TestName.contains(DSleak) ||
             (TestName.contains(DS) && TestName.contains(leak) && !TestName.contains(w))))
    {
        CriteriumDown = 0.0;// 1.0*(1e-30)*LEN;
        CriteriumUp = 6.0*(1e-12)*LEN;
    }
    //Ap
    else if(TestName.contains(Ap) &&
            (TestName.contains(DSleak) ||
             (TestName.contains(DS) && TestName.contains(leak) && !TestName.contains(w))))
    {
        CriteriumDown = -10.0*(1e-12)*LEN;
        CriteriumUp = 0.0;// -1.0*(1e-30)*LEN;
    }
    //Rn
    else if(TestName.contains(Rn) &&
            (TestName.contains(DSleak) ||
             (TestName.contains(DS) && TestName.contains(leak) && !TestName.contains(w))))
    {
        CriteriumDown = 0.0; //1.0*(1e-30)*LEN;
        CriteriumUp = 10.0*(1e-12)*LEN;
    }
    //Rp
    else if(TestName.contains(Rp) &&
            (TestName.contains(DSleak) ||
             (TestName.contains(DS) && TestName.contains(leak) && !TestName.contains(w))))
    {
        CriteriumDown = -10.0*(1e-12)*LEN;
        CriteriumUp = 0.0;//-1.0*(1e-30)*LEN;
    }
    //Hn
    else if(TestName.contains(Hn) &&
            (TestName.contains(DSleak) ||
             (TestName.contains(DS) && TestName.contains(leak) && !TestName.contains(w))))
    {
        CriteriumDown = 0.0;// 1.0*(1e-30)*LEN;
        CriteriumUp = 10.0*(1e-12)*LEN;
    }
    //Hp
    else if(TestName.contains(Hp) &&
            (TestName.contains(DSleak) ||
             (TestName.contains(DS) && TestName.contains(leak) && !TestName.contains(w))))
    {
        CriteriumDown = -10.0*(1e-12)*LEN;
        CriteriumUp = 0.0;// -1.0*(1e-30)*LEN;
    }
}
void BigNorms::Tr_DSw_leak(const QString& TestName, double& CriteriumDown, double& CriteriumUp)
{
    //An
    if(TestName.contains(An) &&
            (TestName.contains(DSw_leak) ||
             (TestName.contains(DS) && TestName.contains(leak) && TestName.contains(w))))
    {
        CriteriumDown = 0.0;// 1.0*(1e-30);
        CriteriumUp = 6.0*(1e-12);
    }
    //Ap
    else if(TestName.contains(Ap) &&
            (TestName.contains(DSw_leak) ||
             (TestName.contains(DS) && TestName.contains(leak) && TestName.contains(w))))
    {
        CriteriumDown = -10.0*(1e-12);
        CriteriumUp = 0.0;// -1.0*(1e-30);
    }
    //Rn
    else if(TestName.contains(Rn) &&
            (TestName.contains(DSw_leak) ||
             (TestName.contains(DS) && TestName.contains(leak) && TestName.contains(w))))
    {
        CriteriumDown = 0.0;// 1.0*(1e-30);
        CriteriumUp = 10.0*(1e-12);
    }
    //Rp
    else if(TestName.contains(Rp) &&
            (TestName.contains(DSw_leak) ||
             (TestName.contains(DS) && TestName.contains(leak) && TestName.contains(w))))
    {
        CriteriumDown = -10.0*(1e-12);
        CriteriumUp = 0.0;// -1.0*(1e-30);
    }
    //Hn
    else if(TestName.contains(Hn) &&
            (TestName.contains(DSw_leak) ||
             (TestName.contains(DS) && TestName.contains(leak) && TestName.contains(w))))
    {
        CriteriumDown = 0.0;// 1.0*(1e-30);
        CriteriumUp = 10.0*(1e-12);
    }
    //Hp
    else if(TestName.contains(Hp) &&
            (TestName.contains(DSw_leak) ||
             (TestName.contains(DS) && TestName.contains(leak) && TestName.contains(w))))
    {
        CriteriumDown = -10.0*(1e-12);
        CriteriumUp = 0.0; // -1.0*(1e-30);
    }
}
void BigNorms::Tr_DScurrent(const QString& TestName, double& CriteriumDown, double& CriteriumUp)
{
    //An
    if(TestName.contains(An) &&
            (TestName.contains(DScurrent) ||
             (TestName.contains(DS) && TestName.contains(current) && !TestName.contains(w))))
    {
        CriteriumDown = 4.2*(1e-4)*LEN; CriteriumUp = 5.2*(1e-4)*LEN;
    }
    //Ap
    else if(TestName.contains(Ap) &&
            (TestName.contains(DScurrent) ||
             (TestName.contains(DS) && TestName.contains(current) && !TestName.contains(w))))
    {
        CriteriumDown = -3.3*(1e-4)*LEN; CriteriumUp = -2.3*(1e-4)*LEN;
    }
    //Rn
    else if(TestName.contains(Rn) &&
            (TestName.contains(DScurrent) ||
             (TestName.contains(DS) && TestName.contains(current) && !TestName.contains(w))))
    {
        CriteriumDown = 4.2*(1e-4)*LEN; CriteriumUp = 5.2*(1e-4)*LEN;

    }
    //Rp
    else if(TestName.contains(Rp) &&
            (TestName.contains(DScurrent) ||
             (TestName.contains(DS) && TestName.contains(current) && !TestName.contains(w))))
    {
        CriteriumDown = -3.3*(1e-4)*LEN; CriteriumUp = -2.3*(1e-4)*LEN;
    }
    //Hn
    else if(TestName.contains(Hn) &&
            (TestName.contains(DScurrent) ||
             (TestName.contains(DS) && TestName.contains(current) && !TestName.contains(w))))
    {
        CriteriumDown = 4.2*(1e-4)*LEN; CriteriumUp = 5.2*(1e-4)*LEN;
    }
    //Hp
    else if(TestName.contains(Hp) &&
            (TestName.contains(DScurrent) ||
             (TestName.contains(DS) && TestName.contains(current) && !TestName.contains(w))))
    {
        CriteriumDown = -3.3*(1e-4)*LEN; CriteriumUp = -2.3*(1e-4)*LEN;
    }
}
void BigNorms::Tr_DSw_driver(const QString& TestName, double& CriteriumDown, double& CriteriumUp)
{
    //An
    if(TestName.contains(An) &&
            (TestName.contains(DSw_driver) ||
             (TestName.contains(DS) && TestName.contains(driver) && TestName.contains(w))))
    {
        CriteriumDown = 4.2*(1e-4); CriteriumUp = 5.2*(1e-4);
    }
    //Ap
    else if(TestName.contains(Ap) &&
            (TestName.contains(DSw_driver) ||
             (TestName.contains(DS) && TestName.contains(driver) && TestName.contains(w))))
    {
        CriteriumDown = -3.3*(1e-4); CriteriumUp = -2.3*(1e-4);
    }
    //Rn
    else if(TestName.contains(Rn) &&
            (TestName.contains(DSw_driver) ||
             (TestName.contains(DS) && TestName.contains(driver) && TestName.contains(w))))
    {
        CriteriumDown = 4.2*(1e-4); CriteriumUp = 5.2*(1e-4);
    }
    //Rp
    else if(TestName.contains(Rp) &&
            (TestName.contains(DSw_driver) ||
             (TestName.contains(DS) && TestName.contains(driver) && TestName.contains(w))))
    {
        CriteriumDown = -3.3*(1e-4); CriteriumUp = -2.3*(1e-4);
    }
    //Hn
    else if(TestName.contains(Hn) &&
            (TestName.contains(DSw_driver) ||
             (TestName.contains(DS) && TestName.contains(driver) && TestName.contains(w))))
    {
        CriteriumDown = 4.2*(1e-4); CriteriumUp = 5.2*(1e-4);
    }
    //Hp
    else if(TestName.contains(Hp) &&
            (TestName.contains(DSw_driver) ||
             (TestName.contains(DS) && TestName.contains(driver) && TestName.contains(w))))
    {
        CriteriumDown = -3.3*(1e-4); CriteriumUp = -2.3*(1e-4);
    }
}
