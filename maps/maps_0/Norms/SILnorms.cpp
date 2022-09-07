#include "SILnorms.h"

//Переопределенные методы
//----------------------------------------------------------------------------------------------------
//R <= 10
void SIL10norms::SIL09(const QString& TestName, double& CriteriumDown, double& CriteriumUp)
{
    if(TestName.contains(tRZnTiSi) && TestName.contains(w09)){
        CriteriumDown = 0.1; CriteriumUp = 10.0;}//резисторы tRZnTiSi09
    else if(TestName.contains(tRZpTiSi) && TestName.contains(w09)){
        CriteriumDown = 0.1; CriteriumUp = 10.0;}//резисторы tRZpTiSi09
    else if(TestName.contains(tRZnSiTiSi) && TestName.contains(w09)){
        CriteriumDown = 0.1; CriteriumUp = 10.0;}//резисторы tRZnSiTiSi09
    else if(TestName.contains(tRZpSiTiSi) && TestName.contains(w09)){
        CriteriumDown = 0.1; CriteriumUp = 10.0;}//резисторы tRZpSiTiSi09
    else if(TestName.contains(tRZSiTiSi) && TestName.contains(w09)){
        CriteriumDown = 0.1; CriteriumUp = 10.0;}//резисторы tRZSiTiSi09
}
void SIL10norms::SIL05(const QString& TestName, double& CriteriumDown, double& CriteriumUp)
{
    if(TestName.contains(tRZnTiSi) && TestName.contains(w05)){
        CriteriumDown = 0.1; CriteriumUp = 10.0;}//резисторы tRZnTiSi05
    else if(TestName.contains(tRZpTiSi) && TestName.contains(w05)){
        CriteriumDown = 0.1; CriteriumUp = 10.0;}//резисторы tRZpTiSi05
    else if(TestName.contains(tRZnSiTiSi) && TestName.contains(w05)){
        CriteriumDown = 0.1; CriteriumUp = 10.0;}//резисторы tRZnSiTiSi05
    else if(TestName.contains(tRZpSiTiSi) && TestName.contains(w05)){
        CriteriumDown = 0.1; CriteriumUp = 10.0;}//резисторы tRZpSiTiSi05
    else if(TestName.contains(tRZSiTiSi) && TestName.contains(w05)){
        CriteriumDown = 0.1; CriteriumUp = 10.0;}//резисторы tRZSiTiSi05
}
void SIL10norms::SIL035(const QString& TestName, double& CriteriumDown, double& CriteriumUp)
{
    if(TestName.contains(tRZnTiSi) && TestName.contains(w035)){
        CriteriumDown = 0.1; CriteriumUp = 10.0;}//резисторы tRZnTiSi035
    else if(TestName.contains(tRZpTiSi) && TestName.contains(w035)){
        CriteriumDown = 0.1; CriteriumUp = 10.0;}//резисторы tRZpTiSi035
    else if(TestName.contains(tRZnSiTiSi) && TestName.contains(w035)){
        CriteriumDown = 0.1; CriteriumUp = 10.0;}//резисторы tRZnSiTiSi035
    else if(TestName.contains(tRZpSiTiSi) && TestName.contains(w035)){
        CriteriumDown = 0.1; CriteriumUp = 10.0;}//резисторы tRZpSiTiSi035
    else if(TestName.contains(tRZSiTiSi) && TestName.contains(w035)){
        CriteriumDown = 0.1; CriteriumUp = 10.0;}//резисторы tRZSiTiSi035
}
void SIL10norms::KLV_M1Si(const QString& TestName, double& CriteriumDown, double& CriteriumUp)
{
    if(TestName.contains(KLV_nM1) || TestName.contains(KLVnM1)){
        CriteriumDown = 0.1; CriteriumUp = 10.0;}//кельвины KLV_nM1
    else if(TestName.contains(KLV_pM1) || TestName.contains(KLVpM1)){
        CriteriumDown = 0.1; CriteriumUp = 10.0;}//кельвины KLV_pM1
    else if(TestName.contains(KLV_nSiM1) || TestName.contains(KLVnSiM1)){
        CriteriumDown = 0.1; CriteriumUp = 10.0;}//кельвины KLV_nSiM1
    else if(TestName.contains(KLV_pSiM1) || TestName.contains(KLVpSiM1)){
        CriteriumDown = 0.1; CriteriumUp = 10.0;}//кельвины KLV_pSiM1
    else if(TestName.contains(KLV_SiM1) || TestName.contains(KLVSiM1)){
        CriteriumDown = 0.1; CriteriumUp = 10.0;}//кельвины KLV_SiM1
}
void SIL10norms::Z_M1Si(const QString& TestName, double& CriteriumDown, double& CriteriumUp)
{
    if(TestName.contains(dZnM1) || TestName.contains(dZ_nM1)){
        CriteriumDown = 0.1; CriteriumUp = 10.0;}//цепочки dZnM1
    else if(TestName.contains(dZpM1) || TestName.contains(dZ_pM1)){
        CriteriumDown = 0.1; CriteriumUp = 10.0;}//цепочки dZpM1
    else if(TestName.contains(dZnSiM1) || TestName.contains(dZ_nSiM1)){
        CriteriumDown = 0.1; CriteriumUp = 10.0;}//цепочки dZnSiM1
    else if(TestName.contains(dZpSiM1) || TestName.contains(dZ_pSiM1)){
        CriteriumDown = 0.1; CriteriumUp = 10.0;}//цепочки dZpSiM1
    else if(TestName.contains(dZSiM1) || TestName.contains(dZ_SiM1)){
        CriteriumDown = 0.1; CriteriumUp = 10.0;}//кельвины KLV_SiM1
}

//----------------------------------------------------------------------------------------------------
//R <= 15
void SIL15norms::SIL09(const QString& TestName, double& CriteriumDown, double& CriteriumUp)
{
    if(TestName.contains(tRZnTiSi) && TestName.contains(w09)){
        CriteriumDown = 0.1; CriteriumUp = 15.0;}//резисторы tRZnTiSi09
    else if(TestName.contains(tRZpTiSi) && TestName.contains(w09)){
        CriteriumDown = 0.1; CriteriumUp = 15.0;}//резисторы tRZpTiSi09
    else if(TestName.contains(tRZnSiTiSi) && TestName.contains(w09)){
        CriteriumDown = 0.1; CriteriumUp = 15.0;}//резисторы tRZnSiTiSi09
    else if(TestName.contains(tRZpSiTiSi) && TestName.contains(w09)){
        CriteriumDown = 0.1; CriteriumUp = 15.0;}//резисторы tRZpSiTiSi09
    else if(TestName.contains(tRZSiTiSi) && TestName.contains(w09)){
        CriteriumDown = 0.1; CriteriumUp = 15.0;}//резисторы tRZSiTiSi09
}
void SIL15norms::SIL05(const QString& TestName, double& CriteriumDown, double& CriteriumUp)
{
    if(TestName.contains(tRZnTiSi) && TestName.contains(w05)){
        CriteriumDown = 0.1; CriteriumUp = 15.0;}//резисторы tRZnTiSi05
    else if(TestName.contains(tRZpTiSi) && TestName.contains(w05)){
        CriteriumDown = 0.1; CriteriumUp = 15.0;}//резисторы tRZpTiSi05
    else if(TestName.contains(tRZnSiTiSi) && TestName.contains(w05)){
        CriteriumDown = 0.1; CriteriumUp = 15.0;}//резисторы tRZnSiTiSi05
    else if(TestName.contains(tRZpSiTiSi) && TestName.contains(w05)){
        CriteriumDown = 0.1; CriteriumUp = 15.0;}//резисторы tRZpSiTiSi05
    else if(TestName.contains(tRZSiTiSi) && TestName.contains(w05)){
        CriteriumDown = 0.1; CriteriumUp = 15.0;}//резисторы tRZSiTiSi05
}
void SIL15norms::SIL035(const QString& TestName, double& CriteriumDown, double& CriteriumUp)
{
    if(TestName.contains(tRZnTiSi) && TestName.contains(w035)){
        CriteriumDown = 0.1; CriteriumUp = 15.0;}//резисторы tRZnTiSi035
    else if(TestName.contains(tRZpTiSi) && TestName.contains(w035)){
        CriteriumDown = 0.1; CriteriumUp = 15.0;}//резисторы tRZpTiSi035
    else if(TestName.contains(tRZnSiTiSi) && TestName.contains(w035)){
        CriteriumDown = 0.1; CriteriumUp = 15.0;}//резисторы tRZnSiTiSi035
    else if(TestName.contains(tRZpSiTiSi) && TestName.contains(w035)){
        CriteriumDown = 0.1; CriteriumUp = 15.0;}//резисторы tRZpSiTiSi035
    else if(TestName.contains(tRZSiTiSi) && TestName.contains(w035)){
        CriteriumDown = 0.1; CriteriumUp = 15.0;}//резисторы tRZSiTiSi035
}
void SIL15norms::KLV_M1Si(const QString& TestName, double& CriteriumDown, double& CriteriumUp)
{
    if(TestName.contains(KLV_nM1) || TestName.contains(KLVnM1)){
        CriteriumDown = 0.1; CriteriumUp = 15.0;}//кельвины KLV_nM1
    else if(TestName.contains(KLV_pM1) || TestName.contains(KLVpM1)){
        CriteriumDown = 0.1; CriteriumUp = 15.0;}//кельвины KLV_pM1
    else if(TestName.contains(KLV_nSiM1) || TestName.contains(KLVnSiM1)){
        CriteriumDown = 0.1; CriteriumUp = 15.0;}//кельвины KLV_nSiM1
    else if(TestName.contains(KLV_pSiM1) || TestName.contains(KLVpSiM1)){
        CriteriumDown = 0.1; CriteriumUp = 15.0;}//кельвины KLV_pSiM1
    else if(TestName.contains(KLV_SiM1) || TestName.contains(KLVSiM1)){
        CriteriumDown = 0.1; CriteriumUp = 15.0;}//кельвины KLV_SiM1
}
void SIL15norms::Z_M1Si(const QString& TestName, double& CriteriumDown, double& CriteriumUp)
{
    if(TestName.contains(dZnM1) || TestName.contains(dZ_nM1)){
        CriteriumDown = 0.1; CriteriumUp = 15.0;}//цепочки dZnM1
    else if(TestName.contains(dZpM1) || TestName.contains(dZ_pM1)){
        CriteriumDown = 0.1; CriteriumUp = 15.0;}//цепочки dZpM1
    else if(TestName.contains(dZnSiM1) || TestName.contains(dZ_nSiM1)){
        CriteriumDown = 0.1; CriteriumUp = 15.0;}//цепочки dZnSiM1
    else if(TestName.contains(dZpSiM1) || TestName.contains(dZ_pSiM1)){
        CriteriumDown = 0.1; CriteriumUp = 15.0;}//цепочки dZpSiM1
    else if(TestName.contains(dZSiM1) || TestName.contains(dZ_SiM1)){
        CriteriumDown = 0.1; CriteriumUp = 15.0;}//кельвины KLV_SiM1
}

//----------------------------------------------------------------------------------------------------
//R <= 30
void SIL30norms::SIL09(const QString& TestName, double& CriteriumDown, double& CriteriumUp)
{
    if(TestName.contains(tRZnTiSi) && TestName.contains(w09)){
        CriteriumDown = 0.1; CriteriumUp = 30.0;}//резисторы tRZnTiSi09
    else if(TestName.contains(tRZpTiSi) && TestName.contains(w09)){
        CriteriumDown = 0.1; CriteriumUp = 30.0;}//резисторы tRZpTiSi09
    else if(TestName.contains(tRZnSiTiSi) && TestName.contains(w09)){
        CriteriumDown = 0.1; CriteriumUp = 30.0;}//резисторы tRZnSiTiSi09
    else if(TestName.contains(tRZpSiTiSi) && TestName.contains(w09)){
        CriteriumDown = 0.1; CriteriumUp = 30.0;}//резисторы tRZpSiTiSi09
    else if(TestName.contains(tRZSiTiSi) && TestName.contains(w09)){
        CriteriumDown = 0.1; CriteriumUp = 30.0;}//резисторы tRZSiTiSi09
}
void SIL30norms::SIL05(const QString& TestName, double& CriteriumDown, double& CriteriumUp)
{
    if(TestName.contains(tRZnTiSi) && TestName.contains(w05)){
        CriteriumDown = 0.1; CriteriumUp = 30.0;}//резисторы tRZnTiSi05
    else if(TestName.contains(tRZpTiSi) && TestName.contains(w05)){
        CriteriumDown = 0.1; CriteriumUp = 30.0;}//резисторы tRZpTiSi05
    else if(TestName.contains(tRZnSiTiSi) && TestName.contains(w05)){
        CriteriumDown = 0.1; CriteriumUp = 30.0;}//резисторы tRZnSiTiSi05
    else if(TestName.contains(tRZpSiTiSi) && TestName.contains(w05)){
        CriteriumDown = 0.1; CriteriumUp = 30.0;}//резисторы tRZpSiTiSi05
    else if(TestName.contains(tRZSiTiSi) && TestName.contains(w05)){
        CriteriumDown = 0.1; CriteriumUp = 30.0;}//резисторы tRZSiTiSi05
}
void SIL30norms::SIL035(const QString& TestName, double& CriteriumDown, double& CriteriumUp)
{
    if(TestName.contains(tRZnTiSi) && TestName.contains(w035)){
        CriteriumDown = 0.1; CriteriumUp = 30.0;}//резисторы tRZnTiSi035
    else if(TestName.contains(tRZpTiSi) && TestName.contains(w035)){
        CriteriumDown = 0.1; CriteriumUp = 30.0;}//резисторы tRZpTiSi035
    else if(TestName.contains(tRZnSiTiSi) && TestName.contains(w035)){
        CriteriumDown = 0.1; CriteriumUp = 30.0;}//резисторы tRZnSiTiSi035
    else if(TestName.contains(tRZpSiTiSi) && TestName.contains(w035)){
        CriteriumDown = 0.1; CriteriumUp = 30.0;}//резисторы tRZpSiTiSi035
    else if(TestName.contains(tRZSiTiSi) && TestName.contains(w035)){
        CriteriumDown = 0.1; CriteriumUp = 30.0;}//резисторы tRZSiTiSi035
}
void SIL30norms::KLV_M1Si(const QString& TestName, double& CriteriumDown, double& CriteriumUp)
{
    if(TestName.contains(KLV_nM1) || TestName.contains(KLVnM1)){
        CriteriumDown = 0.1; CriteriumUp = 30.0;}//кельвины KLV_nM1
    else if(TestName.contains(KLV_pM1) || TestName.contains(KLVpM1)){
        CriteriumDown = 0.1; CriteriumUp = 30.0;}//кельвины KLV_pM1
    else if(TestName.contains(KLV_nSiM1) || TestName.contains(KLVnSiM1)){
        CriteriumDown = 0.1; CriteriumUp = 30.0;}//кельвины KLV_nSiM1
    else if(TestName.contains(KLV_pSiM1) || TestName.contains(KLVpSiM1)){
        CriteriumDown = 0.1; CriteriumUp = 30.0;}//кельвины KLV_pSiM1
    else if(TestName.contains(KLV_SiM1) || TestName.contains(KLVSiM1)){
        CriteriumDown = 0.1; CriteriumUp = 30.0;}//кельвины KLV_SiM1
}
void SIL30norms::Z_M1Si(const QString& TestName, double& CriteriumDown, double& CriteriumUp)
{
    if(TestName.contains(dZnM1) || TestName.contains(dZ_nM1)){
        CriteriumDown = 0.1; CriteriumUp = 30.0;}//цепочки dZnM1
    else if(TestName.contains(dZpM1) || TestName.contains(dZ_pM1)){
        CriteriumDown = 0.1; CriteriumUp = 30.0;}//цепочки dZpM1
    else if(TestName.contains(dZnSiM1) || TestName.contains(dZ_nSiM1)){
        CriteriumDown = 0.1; CriteriumUp = 30.0;}//цепочки dZnSiM1
    else if(TestName.contains(dZpSiM1) || TestName.contains(dZ_pSiM1)){
        CriteriumDown = 0.1; CriteriumUp = 30.0;}//цепочки dZpSiM1
    else if(TestName.contains(dZSiM1) || TestName.contains(dZ_SiM1)){
        CriteriumDown = 0.1; CriteriumUp = 30.0;}//кельвины KLV_SiM1
}

//----------------------------------------------------------------------------------------------------
//R <= 100
void SIL100norms::SIL09(const QString& TestName, double& CriteriumDown, double& CriteriumUp)
{
    if(TestName.contains(tRZnTiSi) && TestName.contains(w09)){
        CriteriumDown = 0.1; CriteriumUp = 100.0;}//резисторы tRZnTiSi09
    else if(TestName.contains(tRZpTiSi) && TestName.contains(w09)){
        CriteriumDown = 0.1; CriteriumUp = 100.0;}//резисторы tRZpTiSi09
    else if(TestName.contains(tRZnSiTiSi) && TestName.contains(w09)){
        CriteriumDown = 0.1; CriteriumUp = 100.0;}//резисторы tRZnSiTiSi09
    else if(TestName.contains(tRZpSiTiSi) && TestName.contains(w09)){
        CriteriumDown = 0.1; CriteriumUp = 100.0;}//резисторы tRZpSiTiSi09
    else if(TestName.contains(tRZSiTiSi) && TestName.contains(w09)){
        CriteriumDown = 0.1; CriteriumUp = 100.0;}//резисторы tRZSiTiSi09
}
void SIL100norms::SIL05(const QString& TestName, double& CriteriumDown, double& CriteriumUp)
{
    if(TestName.contains(tRZnTiSi) && TestName.contains(w05)){
        CriteriumDown = 0.1; CriteriumUp = 100.0;}//резисторы tRZnTiSi05
    else if(TestName.contains(tRZpTiSi) && TestName.contains(w05)){
        CriteriumDown = 0.1; CriteriumUp = 100.0;}//резисторы tRZpTiSi05
    else if(TestName.contains(tRZnSiTiSi) && TestName.contains(w05)){
        CriteriumDown = 0.1; CriteriumUp = 100.0;}//резисторы tRZnSiTiSi05
    else if(TestName.contains(tRZpSiTiSi) && TestName.contains(w05)){
        CriteriumDown = 0.1; CriteriumUp = 100.0;}//резисторы tRZpSiTiSi05
    else if(TestName.contains(tRZSiTiSi) && TestName.contains(w05)){
        CriteriumDown = 0.1; CriteriumUp = 100.0;}//резисторы tRZSiTiSi05
}
void SIL100norms::SIL035(const QString& TestName, double& CriteriumDown, double& CriteriumUp)
{
    if(TestName.contains(tRZnTiSi) && TestName.contains(w035)){
        CriteriumDown = 0.1; CriteriumUp = 100.0;}//резисторы tRZnTiSi035
    else if(TestName.contains(tRZpTiSi) && TestName.contains(w035)){
        CriteriumDown = 0.1; CriteriumUp = 100.0;}//резисторы tRZpTiSi035
    else if(TestName.contains(tRZnSiTiSi) && TestName.contains(w035)){
        CriteriumDown = 0.1; CriteriumUp = 100.0;}//резисторы tRZnSiTiSi035
    else if(TestName.contains(tRZpSiTiSi) && TestName.contains(w035)){
        CriteriumDown = 0.1; CriteriumUp = 100.0;}//резисторы tRZpSiTiSi035
    else if(TestName.contains(tRZSiTiSi) && TestName.contains(w035)){
        CriteriumDown = 0.1; CriteriumUp = 100.0;}//резисторы tRZSiTiSi035
}
void SIL100norms::KLV_M1Si(const QString& TestName, double& CriteriumDown, double& CriteriumUp)
{
    if(TestName.contains(KLV_nM1) || TestName.contains(KLVnM1)){
        CriteriumDown = 0.1; CriteriumUp = 100.0;}//кельвины KLV_nM1
    else if(TestName.contains(KLV_pM1) || TestName.contains(KLVpM1)){
        CriteriumDown = 0.1; CriteriumUp = 100.0;}//кельвины KLV_pM1
    else if(TestName.contains(KLV_nSiM1) || TestName.contains(KLVnSiM1)){
        CriteriumDown = 0.1; CriteriumUp = 100.0;}//кельвины KLV_nSiM1
    else if(TestName.contains(KLV_pSiM1) || TestName.contains(KLVpSiM1)){
        CriteriumDown = 0.1; CriteriumUp = 100.0;}//кельвины KLV_pSiM1
    else if(TestName.contains(KLV_SiM1) || TestName.contains(KLVSiM1)){
        CriteriumDown = 0.1; CriteriumUp = 100.0;}//кельвины KLV_SiM1
}
void SIL100norms::Z_M1Si(const QString& TestName, double& CriteriumDown, double& CriteriumUp)
{
    if(TestName.contains(dZnM1) || TestName.contains(dZ_nM1)){
        CriteriumDown = 0.1; CriteriumUp = 100.0;}//цепочки dZnM1
    else if(TestName.contains(dZpM1) || TestName.contains(dZ_pM1)){
        CriteriumDown = 0.1; CriteriumUp = 100.0;}//цепочки dZpM1
    else if(TestName.contains(dZnSiM1) || TestName.contains(dZ_nSiM1)){
        CriteriumDown = 0.1; CriteriumUp = 100.0;}//цепочки dZnSiM1
    else if(TestName.contains(dZpSiM1) || TestName.contains(dZ_pSiM1)){
        CriteriumDown = 0.1; CriteriumUp = 100.0;}//цепочки dZpSiM1
    else if(TestName.contains(dZSiM1) || TestName.contains(dZ_SiM1)){
        CriteriumDown = 0.1; CriteriumUp = 100.0;}//кельвины KLV_SiM1
}

//----------------------------------------------------------------------------------------------------
//R <= 500
void SIL500norms::SIL09(const QString& TestName, double& CriteriumDown, double& CriteriumUp)
{
    if(TestName.contains(tRZnTiSi) && TestName.contains(w09)){
        CriteriumDown = 0.1; CriteriumUp = 500.0;}//резисторы tRZnTiSi09
    else if(TestName.contains(tRZpTiSi) && TestName.contains(w09)){
        CriteriumDown = 0.1; CriteriumUp = 500.0;}//резисторы tRZpTiSi09
    else if(TestName.contains(tRZnSiTiSi) && TestName.contains(w09)){
        CriteriumDown = 0.1; CriteriumUp = 500.0;}//резисторы tRZnSiTiSi09
    else if(TestName.contains(tRZpSiTiSi) && TestName.contains(w09)){
        CriteriumDown = 0.1; CriteriumUp = 500.0;}//резисторы tRZpSiTiSi09
    else if(TestName.contains(tRZSiTiSi) && TestName.contains(w09)){
        CriteriumDown = 0.1; CriteriumUp = 500.0;}//резисторы tRZSiTiSi09
}
void SIL500norms::SIL05(const QString& TestName, double& CriteriumDown, double& CriteriumUp)
{
    if(TestName.contains(tRZnTiSi) && TestName.contains(w05)){
        CriteriumDown = 0.1; CriteriumUp = 500.0;}//резисторы tRZnTiSi05
    else if(TestName.contains(tRZpTiSi) && TestName.contains(w05)){
        CriteriumDown = 0.1; CriteriumUp = 500.0;}//резисторы tRZpTiSi05
    else if(TestName.contains(tRZnSiTiSi) && TestName.contains(w05)){
        CriteriumDown = 0.1; CriteriumUp = 500.0;}//резисторы tRZnSiTiSi05
    else if(TestName.contains(tRZpSiTiSi) && TestName.contains(w05)){
        CriteriumDown = 0.1; CriteriumUp = 500.0;}//резисторы tRZpSiTiSi05
    else if(TestName.contains(tRZSiTiSi) && TestName.contains(w05)){
        CriteriumDown = 0.1; CriteriumUp = 500.0;}//резисторы tRZSiTiSi05
}
void SIL500norms::SIL035(const QString& TestName, double& CriteriumDown, double& CriteriumUp)
{
    if(TestName.contains(tRZnTiSi) && TestName.contains(w035)){
        CriteriumDown = 0.1; CriteriumUp = 500.0;}//резисторы tRZnTiSi035
    else if(TestName.contains(tRZpTiSi) && TestName.contains(w035)){
        CriteriumDown = 0.1; CriteriumUp = 500.0;}//резисторы tRZpTiSi035
    else if(TestName.contains(tRZnSiTiSi) && TestName.contains(w035)){
        CriteriumDown = 0.1; CriteriumUp = 500.0;}//резисторы tRZnSiTiSi035
    else if(TestName.contains(tRZpSiTiSi) && TestName.contains(w035)){
        CriteriumDown = 0.1; CriteriumUp = 500.0;}//резисторы tRZpSiTiSi035
    else if(TestName.contains(tRZSiTiSi) && TestName.contains(w035)){
        CriteriumDown = 0.1; CriteriumUp = 500.0;}//резисторы tRZSiTiSi035
}
void SIL500norms::KLV_M1Si(const QString& TestName, double& CriteriumDown, double& CriteriumUp)
{
    if(TestName.contains(KLV_nM1) || TestName.contains(KLVnM1)){
        CriteriumDown = 0.1; CriteriumUp = 500.0;}//кельвины KLV_nM1
    else if(TestName.contains(KLV_pM1) || TestName.contains(KLVpM1)){
        CriteriumDown = 0.1; CriteriumUp = 500.0;}//кельвины KLV_pM1
    else if(TestName.contains(KLV_nSiM1) || TestName.contains(KLVnSiM1)){
        CriteriumDown = 0.1; CriteriumUp = 500.0;}//кельвины KLV_nSiM1
    else if(TestName.contains(KLV_pSiM1) || TestName.contains(KLVpSiM1)){
        CriteriumDown = 0.1; CriteriumUp = 500.0;}//кельвины KLV_pSiM1
    else if(TestName.contains(KLV_SiM1) || TestName.contains(KLVSiM1)){
        CriteriumDown = 0.1; CriteriumUp = 500.0;}//кельвины KLV_SiM1
}
void SIL500norms::Z_M1Si(const QString& TestName, double& CriteriumDown, double& CriteriumUp)
{
    if(TestName.contains(dZnM1) || TestName.contains(dZ_nM1)){
        CriteriumDown = 0.1; CriteriumUp = 500.0;}//цепочки dZnM1
    else if(TestName.contains(dZpM1) || TestName.contains(dZ_pM1)){
        CriteriumDown = 0.1; CriteriumUp = 500.0;}//цепочки dZpM1
    else if(TestName.contains(dZnSiM1) || TestName.contains(dZ_nSiM1)){
        CriteriumDown = 0.1; CriteriumUp = 500.0;}//цепочки dZnSiM1
    else if(TestName.contains(dZpSiM1) || TestName.contains(dZ_pSiM1)){
        CriteriumDown = 0.1; CriteriumUp = 500.0;}//цепочки dZpSiM1
    else if(TestName.contains(dZSiM1) || TestName.contains(dZ_SiM1)){
        CriteriumDown = 0.1; CriteriumUp = 500.0;}//кельвины KLV_SiM1
}

//----------------------------------------------------------------------------------------------------
//R <= 1000
void SIL1000norms::SIL09(const QString& TestName, double& CriteriumDown, double& CriteriumUp)
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
void SIL1000norms::SIL05(const QString& TestName, double& CriteriumDown, double& CriteriumUp)
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
void SIL1000norms::SIL035(const QString& TestName, double& CriteriumDown, double& CriteriumUp)
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
void SIL1000norms::KLV_M1Si(const QString& TestName, double& CriteriumDown, double& CriteriumUp)
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
void SIL1000norms::Z_M1Si(const QString& TestName, double& CriteriumDown, double& CriteriumUp)
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




