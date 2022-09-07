#ifndef SYSTEMCALCULATION_H
#define SYSTEMCALCULATION_H

#include <memory>
using namespace std;

#include <QtMath>

#include "Types.h"
#include "Lot/Lot.h"
#include "Masking/MaskData.h"
#include "MapImage.h"
#include "Reports/TestElemData.h"

namespace SystemCalculation
{
const int coordReset = 1000;

struct CalcData
{
    double criteriumDn;
    double criteriumUp;
    int diesNum;
    int diesNumUnmasked;
    int diesNumMasked;
    vecPair vecPairXY;
    vecPair vecPairXY_Unmasked;
    vecPair vecPairXY_Masked;
    QVector<double> vecValues;
    QVector<double> vecValues_Unmasked;
    QVector<double> vecValues_Masked;
    QVector<Mask> vecMaskType;
};
struct Statistica
{
    int diesNumFit;
    int diesNumUnfit;
    double diesFitPercent;
    double diesUnfitPercent;
    double avg;
    double std;
    double min;
    double max;
    vecPair vecPairXY_Fit;
    vecPair vecPairXY_UnfitLower;
    vecPair vecPairXY_UnfitUpper;
};

//------------------------------------------------------------------------------------
//расчет статистики тестового элемента
void calcTestElemStatistics(TestElemData &testElemData);
//------------------------------------------------------------------------------------
//сделать маскирование
void doMaskingTestElem(QVector<shared_ptr<Die> > vec_spDies,
                       TestElemData &testElemData, CalcData& data);
//максимальное значение координаты
int MaximalCoordinate(const QVector<shared_ptr<Die> > vec_spDies);
//расчет статистики
void StatisticsCalc(const CalcData in, Statistica& out);
//--------------------------------------------------------------------------------------
//единицы измерения
QString testElemUnitName(const QString &testName, const QString &paramName,
                         const ValuePrefix valuePrefix);
//---------------------------------------------------------------------------------------
}

#endif // SYSTEMCALCULATION_H
