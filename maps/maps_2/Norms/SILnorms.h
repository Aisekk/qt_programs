#ifndef SILNORMS
#define SILNORMS

#include "BasicNorms.h"

class SIL10norms : public BasicNorms
{
public:
    SIL10norms() : BasicNorms() {}
    void SIL09(const QString& TestName, double& CriteriumDown, double& CriteriumUp) override;
    void SIL05(const QString& TestName, double& CriteriumDown, double& CriteriumUp) override;
    void SIL035(const QString& TestName, double& CriteriumDown, double& CriteriumUp) override;
    void KLV_M1Si(const QString& TestName, double& CriteriumDown, double& CriteriumUp) override;
    void Z_M1Si(const QString& TestName, double& CriteriumDown, double& CriteriumUp) override;
};

class SIL15norms : public BasicNorms
{
public:
    SIL15norms() : BasicNorms() {}
    void SIL09(const QString& TestName, double& CriteriumDown, double& CriteriumUp) override;
    void SIL05(const QString& TestName, double& CriteriumDown, double& CriteriumUp) override;
    void SIL035(const QString& TestName, double& CriteriumDown, double& CriteriumUp) override;
    void KLV_M1Si(const QString& TestName, double& CriteriumDown, double& CriteriumUp) override;
    void Z_M1Si(const QString& TestName, double& CriteriumDown, double& CriteriumUp) override;
};

class SIL30norms : public BasicNorms
{
public:
    SIL30norms() : BasicNorms() {}
    void SIL09(const QString& TestName, double& CriteriumDown, double& CriteriumUp) override;
    void SIL05(const QString& TestName, double& CriteriumDown, double& CriteriumUp) override;
    void SIL035(const QString& TestName, double& CriteriumDown, double& CriteriumUp) override;
    void KLV_M1Si(const QString& TestName, double& CriteriumDown, double& CriteriumUp) override;
    void Z_M1Si(const QString& TestName, double& CriteriumDown, double& CriteriumUp) override;
};

class SIL100norms : public BasicNorms
{
public:
    SIL100norms() : BasicNorms() {}
    void SIL09(const QString& TestName, double& CriteriumDown, double& CriteriumUp) override;
    void SIL05(const QString& TestName, double& CriteriumDown, double& CriteriumUp) override;
    void SIL035(const QString& TestName, double& CriteriumDown, double& CriteriumUp) override;
    void KLV_M1Si(const QString& TestName, double& CriteriumDown, double& CriteriumUp) override;
    void Z_M1Si(const QString& TestName, double& CriteriumDown, double& CriteriumUp) override;
};

class SIL500norms : public BasicNorms
{
public:
    SIL500norms() : BasicNorms() {}
    //переопределенные
    void SIL09(const QString& TestName, double& CriteriumDown, double& CriteriumUp) override;
    void SIL05(const QString& TestName, double& CriteriumDown, double& CriteriumUp) override;
    void SIL035(const QString& TestName, double& CriteriumDown, double& CriteriumUp) override;
    void KLV_M1Si(const QString& TestName, double& CriteriumDown, double& CriteriumUp) override;
    void Z_M1Si(const QString& TestName, double& CriteriumDown, double& CriteriumUp) override;
};

class SIL1000norms : public BasicNorms
{
public:
    SIL1000norms() : BasicNorms() {}
    //переопределенные
    void SIL09(const QString& TestName, double& CriteriumDown, double& CriteriumUp) override;
    void SIL05(const QString& TestName, double& CriteriumDown, double& CriteriumUp) override;
    void SIL035(const QString& TestName, double& CriteriumDown, double& CriteriumUp) override;
    void KLV_M1Si(const QString& TestName, double& CriteriumDown, double& CriteriumUp) override;
    void Z_M1Si(const QString& TestName, double& CriteriumDown, double& CriteriumUp) override;
};

#endif // SILNORMS

