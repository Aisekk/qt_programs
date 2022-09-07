#include "SystemNorms.h"

//----------------------------------------------------------------------------------------
//найти норму тестового элемента
void SystemNorms::findTestElemNorm(const NormsID normsID,
                                   const QString& fullTestName, const ValuePrefix valuePrefix,
                                   double& criteriumDn, double& criteriumUp)
{
    unique_ptr<BasicNorms> upBase;

    switch (normsID)
    {
    case NormsID::Global:
    {
        SystemSettings::readSettings_GlobalNorm(criteriumDn, criteriumUp, valuePrefix);
        break;
    }
    case NormsID::Local:
    {
        SystemSettings::findTestElemNorm(fullTestName, criteriumDn, criteriumUp, valuePrefix);
        break;
    }
    case NormsID::Zsh035:
    {
        upBase.reset(new ZshNorms035);
        break;
    }
    case NormsID::Fau035:
    {
        upBase.reset(new FauNorms035);
        break;
    }
    case NormsID::Norms06:
    {
        upBase.reset(new Norms06);
        break;
    }
    case NormsID::BigNorms:
    {
        upBase.reset(new BigNorms);
        break;
    }
    case NormsID::SIL10:
    {
        upBase.reset(new SIL10norms);
        break;
    }
    case NormsID::SIL15:
    {
        upBase.reset(new SIL15norms);
        break;
    }
    case NormsID::SIL30:
    {
        upBase.reset(new SIL30norms);
        break;
    }
    case NormsID::SIL100:
    {
        upBase.reset(new SIL100norms);
        break;
    }
    case NormsID::SIL500:
    {
        upBase.reset(new SIL500norms);
        break;
    }
    case NormsID::SIL1000:
    {
        upBase.reset(new SIL1000norms);
        break;
    }
    default:
        break;
    }

    BasicNorms *pBase = upBase.get();
    if(pBase != nullptr)
        pBase->setTestInterval(fullTestName, valuePrefix, criteriumDn, criteriumUp);
}
//установить норму тестового элемента
void SystemNorms::setTestElemNorm(TestElemData& testElemData)
{
    shared_ptr<Lot> spLot = testElemData.getLot();
    size_t slotIndex = testElemData.getSlotIndex();
    size_t testIndex = testElemData.getTestIndex();
    ValuePrefix valuePrefix{};

    shared_ptr<Wafer> spWafer{};
    shared_ptr<TestElem> spTestElem{};
    QString testName{};
    QString paramName{};

    if(spLot)
        spWafer = spLot->getWafer(slotIndex);
    if(spWafer)
        spTestElem = spWafer->getTestElem(testIndex);
    if(spTestElem)
    {
        testName = spTestElem->getTestName();
        paramName = spTestElem->getParamName();
        valuePrefix = spTestElem->getTestValuesPrefix();
    }

    QString fullTestName = testName + paramName;

    double criterionDn = 0.0;
    double criterionUp = 0.0;
    //найти норму для расчета
    NormsID normsID = testElemData.getNormsID();
    findTestElemNorm(normsID, fullTestName, valuePrefix, criterionDn, criterionUp);
    testElemData.setCriteriumDn(criterionDn);
    testElemData.setCriteriumUp(criterionUp);
}
//----------------------------------------------------------------------------------------
