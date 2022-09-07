#ifndef FAUNORMS035
#define FAUNORMS035

#include "BasicNorms.h"

class FauNorms035 : public BasicNorms
{
public:
    FauNorms035() : BasicNorms() {}
    void Tr_Vbr(const QString& TestName, double& CriteriumDown, double& CriteriumUp) override;
    void Tr_DSleak(const QString& TestName, double& CriteriumDown, double& CriteriumUp) override;
    void Tr_DSw_leak(const QString& TestName, double& CriteriumDown, double& CriteriumUp) override;
    void Tr_DScurrent(const QString& TestName, double& CriteriumDown, double& CriteriumUp) override;
    void Tr_DSw_driver(const QString& TestName, double& CriteriumDown, double& CriteriumUp) override;
};


#endif // FAUNORMS035

