#include "SystemNorms.h"

//----------------------------------------------------------------------------------------
//найти норму тестового элемента
void SystemNorms::findTestElemNorm(const NormsID normsID,
                                   const QString& fullTestName, const ValuePrefix valuePrefix,
                                   double& criterionDn, double& criterionUp)
{
    unique_ptr<BasicNorms> upBase;

    switch (normsID)
    {
    case NormsID::Global:
    {
        SystemSettings::readSettings_GlobalNorm(criterionDn, criterionUp, valuePrefix);
        break;
    }
    case NormsID::Local:
    {
        SystemSettings::findTestElemNorm(fullTestName, criterionDn, criterionUp, valuePrefix);
        break;
    }
    case NormsID::Dynamic: break;
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
        pBase->setTestInterval(fullTestName, valuePrefix, criterionDn, criterionUp);
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

    if(spLot) spWafer = spLot->getWafer(slotIndex); else return;
    if(spWafer) spTestElem = spWafer->getTestElem(testIndex); else return;
    if(spTestElem)
    {
        testName = spTestElem->getTestName();
        paramName = spTestElem->getParamName();
        valuePrefix = spTestElem->getTestValuesPrefix();
    }
    else return;

    QString fullTestName = testName + paramName;

    double criterionDn = -1.0e+290; //0.0;
    double criterionUp = 1.0e+290; //0.0;
    //найти норму для расчета
    NormsID normsID = testElemData.getNormsID();
    findTestElemNorm(normsID, fullTestName, valuePrefix, criterionDn, criterionUp);
    if(normsID == NormsID::Dynamic) return;
    testElemData.setCriterionDn(criterionDn);
    testElemData.setCriterionUp(criterionUp);
}
//----------------------------------------------------------------------------------------
