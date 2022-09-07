#ifndef SYSTEMNORMS_H
#define SYSTEMNORMS_H

#include "Types.h"
#include "Lot/Lot.h"
#include "Reports/TestElemData.h"
#include "Settings/SystemSettings.h"
//norms
#include "BigNorms.h"
#include "FauNorms035.h"
#include "Norms06.h"
#include "SILnorms.h"
#include "UserNorms.h"
#include "ZshNorms035.h"

namespace SystemNorms
{
//найти норму тестового элемента
void findTestElemNorm(const NormsID normsID, const QString &fullTestName,
                      const ValuePrefix valuePrefix,
                      double &criteriumDn, double &criteriumUp);
//установить норму тестового элемента
void setTestElemNorm(TestElemData& testElemData);
}

#endif // SYSTEMNORMS_H
