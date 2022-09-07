#ifndef BIGNORMS
#define BIGNORMS

#include "BasicNorms.h"

class BigNorms : public BasicNorms
{
public:
    BigNorms() : BasicNorms(){}
    //Члены-функции setTestIntervals
    void SIL09(const QString& TestName, double& CriteriumDown, double& CriteriumUp) override;
    void SIL05(const QString& TestName, double& CriteriumDown, double& CriteriumUp) override;
    void SIL035(const QString& TestName, double& CriteriumDown, double& CriteriumUp) override;
    void KLV_M1Si(const QString& TestName, double& CriteriumDown, double& CriteriumUp) override;
    void Z_M1Si(const QString& TestName, double& CriteriumDown, double& CriteriumUp) override;
    void Meanders(const QString& TestName, double& CriteriumDown, double& CriteriumUp) override;
    void KLV_MeMe(const QString& TestName, double& CriteriumDown, double& CriteriumUp) override;
    void Z_MeMe(const QString& TestName, double& CriteriumDown, double& CriteriumUp) override;
    void VDPs(const QString& TestName, double& CriteriumDown, double& CriteriumUp) override;
    void Capacity(const QString& TestName, double& CriteriumDown, double& CriteriumUp) override;
    void Diods(const QString& TestName, double& CriteriumDown, double& CriteriumUp) override;

    void Tr_Vt(const QString& TestName, double& CriteriumDown, double& CriteriumUp) override;
    void Tr_VtRevers(const QString& TestName, double& CriteriumDown, double& CriteriumUp) override;
    void Tr_Be(const QString& TestName, double& CriteriumDown, double& CriteriumUp) override;
    void Tr_Vbr(const QString& TestName, double& CriteriumDown, double& CriteriumUp) override;
    void Tr_Gleak(const QString& TestName, double& CriteriumDown, double& CriteriumUp) override;
    void Tr_DSleak(const QString& TestName, double& CriteriumDown, double& CriteriumUp) override;
    void Tr_DSw_leak(const QString& TestName, double& CriteriumDown, double& CriteriumUp) override;
    void Tr_DScurrent(const QString& TestName, double& CriteriumDown, double& CriteriumUp) override;
    void Tr_DSw_driver(const QString& TestName, double& CriteriumDown, double& CriteriumUp) override;
};

#endif // BIGNORMS

