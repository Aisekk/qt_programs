#ifndef TESTELEM_H
#define TESTELEM_H

#include <QVector>

#include <vector>
#include <memory>
using namespace std;

#include <QDebug>
#include "Die.h"
#include "Types.h"

class TestElem
{
public:
    TestElem();
    TestElem(const size_t testIndex, const QString& testName, const QString& paramName,
             const QString& algName, ValuePrefix testValuesPrefix);

    size_t getSlotIndex() const;
    size_t getTestIndex() const;
    size_t getDieCount() const;
    NormsID getNormsID() const;
    double getCriterionDn() const;
    double getCriterionUp() const;
    ValuePrefix getTestValuesPrefix() const;
    QString getTestName() const;
    QString getParamName() const;
    QString getAlgName() const;
    QString getUnitName() const;
    QVector<shared_ptr<Die>> &getDies();

    void setSlotIndex(const size_t slotIndex);
    void setNormsID(const NormsID id);
    void setCriterionDn(const double &dn);
    void setCriterionUp(const double &up);
    void setTestValuesPrefix(const ValuePrefix valuePrefix);
    void setTestName(const QString& testName);
    void setUnitName(const QString& unitName);

    void addDie(shared_ptr<Die> &spDie);
    void deleteDies();

private:
    size_t m_slotIndex{};
    size_t m_testIndex{};
    NormsID m_NormsID;
    double m_criterionDn{};
    double m_criterionUp{};
    QString m_testName{};
    QString m_paramName{};
    QString m_algName{};
    QString m_unitName{};
    ValuePrefix m_testValuePrefix{};
    QVector<shared_ptr<Die>> m_vec_spDies;
};

#endif // TESTELEM_H
