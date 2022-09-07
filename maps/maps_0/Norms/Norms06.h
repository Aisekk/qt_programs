#ifndef NORMS06
#define NORMS06

#include "BasicNorms.h"

class Norms06 : public BasicNorms
{
public:
    Norms06() : BasicNorms(){}
protected:
    double LEN = 0.6;//мкм
public:
    void Tr_Vt(const QString& TestName, double& CriteriumDown, double& CriteriumUp) override;
    void Tr_VtRevers(const QString& TestName, double& CriteriumDown, double& CriteriumUp) override;
    void Tr_Be(const QString& TestName, double& CriteriumDown, double& CriteriumUp) override;

    void Tr_DSleak(const QString& TestName, double& CriteriumDown, double& CriteriumUp) override;
    void Tr_DSw_leak(const QString& TestName, double& CriteriumDown, double& CriteriumUp) override;
    void Tr_DScurrent(const QString& TestName, double& CriteriumDown, double& CriteriumUp) override;
    void Tr_DSw_driver(const QString& TestName, double& CriteriumDown, double& CriteriumUp) override;
};

#endif //NORMS06

