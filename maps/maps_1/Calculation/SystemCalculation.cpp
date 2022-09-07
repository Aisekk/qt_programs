#include "SystemCalculation.h"

//-----------------------------------------------------------------------------------------
//вычислить статистические параметры для одного теста
void SystemCalculation::calcTestElemStatistics(TestElemData& testElemData)
{
    //testIndex = 0,1,2...
    //slotIndex = 0,1,2...
    //--------------------------------------------------------------------------------------
    size_t slotIndex = testElemData.getSlotIndex();
    size_t testIndex = testElemData.getTestIndex();
    shared_ptr<Lot> spLot = testElemData.getLot();
    //--------------------------------------------------------------------------------------
    shared_ptr<Wafer> spWafer;
    shared_ptr<TestElem> spTestElem;
    QString testName{};

    if(spLot)
        spWafer = spLot->getWafer(slotIndex);
    if(spWafer)
        spTestElem = spWafer->getTestElem(testIndex);
    if(spTestElem)
        testName = spTestElem->getTestName();
    else return;
    //--------------------------------------------------------------------------------------
    MapImage* pMapImage = testElemData.getMapImage();
    if(pMapImage == nullptr)    return;
    //--------------------------------------------------------------------------------------
    //установка в карту названия теста
    pMapImage->setTestName(testName);
    //--------------------------------------------------------------------------------------
    //установка в карту названия параметра
    QString paramName = spTestElem->getParamName();
    pMapImage->setParamName(paramName);
    //--------------------------------------------------------------------------------------
    //установка в карту названия параметра - напряжения пробоя обратного транзистора
    QString algNameVtRevers = spTestElem->getAlgName();
    if(algNameVtRevers.contains("revers") || algNameVtRevers.contains("Revers"))
        pMapImage->setParamName(paramName + "_revers");
    //--------------------------------------------------------------------------------------
    //установка единиц измерения с префиксом
    ValuePrefix valuePrefix{};
    valuePrefix = spTestElem->getTestValuesPrefix();
    QString unitName = testElemUnitName(testName, paramName, valuePrefix);
    pMapImage->setUnitName(unitName);
    spTestElem->setUnitName(unitName);
    //--------------------------------------------------------------------------------------
    CalcData data;
    //--------------------------------------------------------------------------------------
    //установка в карту интервалов нормы
    data.criteriumDn = testElemData.getCriterionDn();
    data.criteriumUp = testElemData.getCriterionUp();
    pMapImage->setNormsInterval(data.criteriumDn, data.criteriumUp);
    pMapImage->setNormsDeviations(data.criteriumDn, data.criteriumUp);
    spTestElem->setCriterionDn(data.criteriumDn);
    spTestElem->setCriterionUp(data.criteriumUp);
    //-------------------------------------------------------------------------------------------
    //установка типа карты
    MapType mapType = testElemData.getMapType();
    pMapImage->setMapType(mapType);
    //-------------------------------------------------------------------------------------------
    QVector<shared_ptr<Die>> vec_spDies = spTestElem->getDies();
    //-------------------------------------------------------------------------------------------
    //маскирование
    doMaskingTestElem(vec_spDies, testElemData, data);
    //--------------------------------------------------------------------------------------------
    //определение максимального значения одной из координат кристалла на пластине
    int MaxOfXY = MaximalCoordinate(vec_spDies);
    //установка в карту максимального значения одной из координат + 1
    if(MaxOfXY != 0)
    {
        pMapImage->setMaxOfMesuredDiesAlongRadius(MaxOfXY);
        pMapImage->setNumOfVoidDiesLayers(1);
        pMapImage->setMaxOfDiesAlongRadiusInFact(MaxOfXY + 1);
    }
    //---------------------------------------------------------------------------------------------
    //установка исходного коэффициента масштабирования кристаллов
    pMapImage->setNormalScaleFactorDieSize();
    //---------------------------------------------------------------------------------------------
    //измеренное количество всех кристаллов для выбранного теста
    data.diesNum = vec_spDies.size();
    //количество немаскированных кристаллов
    data.diesNumUnmasked = data.vecPairXY_Unmasked.size();
    //количество маскированных кристаллов (включается в количество бракованных):
    data.diesNumMasked = data.diesNum - data.diesNumUnmasked;
    //количество маскированных кристаллов (не включается в количество бракованных):
    //int diesNumMasked = 0;
    //-----------------------------------------------------------------------------------------
    Statistica stat;
    stat.diesNumFit = 0;
    stat.diesNumUnfit = 0;
    stat.diesFitPercent = 0.0;
    stat.diesUnfitPercent = 0.0;

    stat.avg = 0.0;
    stat.std = 0.0;
    stat.min = 1.0e+290;
    stat.max = -1.0e+290;
    //-----------------------------------------------------------------------------------------
    //вычисление статистики
    StatisticsCalc(data, stat);
    //----------------------------------------------------------------------------------------
    //сохранение статистики тестового элемента для отчета
    unique_ptr<TestElemStatistics> upTestElemStats(new TestElemStatistics);
    TestElemStatistics *pTestElemStats = upTestElemStats.get();
    if(pTestElemStats != nullptr)
    {
        pTestElemStats->setDiesNum(data.diesNum);
        pTestElemStats->setDiesNumUnmasked(data.diesNumUnmasked);
        pTestElemStats->setDiesNumMasked(data.diesNumMasked);
        pTestElemStats->setDiesNumFit(stat.diesNumFit);
        pTestElemStats->setDiesNumUnfit(stat.diesNumUnfit);
        pTestElemStats->setDiesFitPercent(stat.diesFitPercent);
        pTestElemStats->setDiesUnfitPercent(stat.diesUnfitPercent);

        pTestElemStats->setAvg(stat.avg);
        pTestElemStats->setStd(stat.std);
        pTestElemStats->setMin(stat.min);
        pTestElemStats->setMax(stat.max);
    }
    testElemData.moveStatistics(std::move(upTestElemStats));
    //----------------------------------------------------------------------------------------
    //установка статистики в карту
    int slotNum = spWafer->getSlotNum();
    pMapImage->setWaferSlot(slotNum);

    pMapImage->setDiesNumMeasured(data.diesNum);
    pMapImage->setDiesNumUnmasked(data.diesNumUnmasked);
    pMapImage->setDiesNumMasked(data.diesNumMasked);
    pMapImage->setDiesFit(stat.diesNumFit, stat.diesFitPercent);
    pMapImage->setDiesUnfit(stat.diesNumUnfit, stat.diesUnfitPercent);

    pMapImage->setAvg(stat.avg);
    pMapImage->setStd(stat.std);
    pMapImage->setMin(stat.min);
    pMapImage->setMax(stat.max);

    pMapImage->setFitDies(stat.vecPairXY_Fit);
    pMapImage->setUnfitDiesLower(stat.vecPairXY_UnfitLower);
    pMapImage->setUnfitDiesUpper(stat.vecPairXY_UnfitUpper);

    pMapImage->setUnmaskedDies(data.vecPairXY, data.vecValues);
    pMapImage->setMaskedDies(data.vecPairXY_Masked, data.vecValues_Masked, data.vecMaskType);
    //------------------------------------------------------------------------------------------
    pMapImage->update();
}
//end of calcTestElemStatistics
//---------------------------------------------------------------------------------------------------
//сделать маскирование одного тестового элемента
void SystemCalculation::doMaskingTestElem(QVector<shared_ptr<Die>> vec_spDies,
                                          TestElemData &testElemData, CalcData& data)
{
    int mask_state_X = coordReset;
    int mask_state_Y = coordReset;
    Mask maskState = Mask::no;

    unique_ptr<MaskData> upMaskData = testElemData.getTestElemMaskData();
    MaskData *pMaskData = upMaskData.get();
    if(pMaskData != nullptr)
    {
        mask_state_X = pMaskData->getMaskState_X();
        mask_state_Y = pMaskData->getMaskState_Y();
        maskState = pMaskData->getMaskState();
    }
    upMaskData = nullptr;

    int x = coordReset;
    int y = coordReset;
    int x_toMask = coordReset;
    int y_toMask = coordReset;
    double value = 0.0;

    for(shared_ptr<Die>& spDie : vec_spDies)
    {
        //----------------------------------------------------------------------
        //заполнение массивов, не участвующих в маскировании
        x = spDie->getX();
        y = spDie->getY();
        value = spDie->getValue();
        //double criterionDn = testElemData.getCriterionDn();
        //double criterionUp = testElemData.getCriterionUp();
        data.vecPairXY.push_back(qMakePair(x,y));
        data.vecValues.push_back(value);
        //----------------------------------------------------------------------
        //установка состояния маскирования в кристаллы
        if(mask_state_X != coordReset && mask_state_Y != coordReset)
        {
            x_toMask = mask_state_X;
            y_toMask = mask_state_Y;

            if(maskState == Mask::no && x_toMask == x && y_toMask == y)
            {
                spDie->setMaskState(Mask::red);
                spDie->setMaskButtonState(MaskButtonState::masked);
            }
            else if(maskState >= Mask::red && x_toMask == x && y_toMask == y)
            {
                spDie->setMaskState(Mask::no);
                spDie->setMaskButtonState(MaskButtonState::unmasked);
            }
        }
        //----------------------------------------------------------------------
        //заполнение массивов маскированными и немаскированными кристаллами:
        Mask mask_State = spDie->getMaskState();
        if(mask_State >= Mask::red)
        {
            data.vecPairXY_Masked.push_back(qMakePair(x,y));
            data.vecValues_Masked.push_back(value);
            data.vecMaskType.push_back(mask_State);
        }
        else if(mask_State == Mask::no)
        {
            data.vecPairXY_Unmasked.push_back(qMakePair(x,y));
            data.vecValues_Unmasked.push_back(value);
        }
        //----------------------------------------------------------------------
    }
}
//максимальное значение координаты
int SystemCalculation::MaximalCoordinate(const QVector<shared_ptr<Die>> vec_spDies)
{
    int xMax = 0, yMax = 0;
    if(!vec_spDies.isEmpty())
    {
        Die *pDie = nullptr;
        auto cit = vec_spDies.constBegin();
        for(;cit != vec_spDies.constEnd(); ++cit)
        {
            pDie = cit->get();
            int x = pDie->getX();
            int y = pDie->getY();

            int absx = abs(x);
            int absy = abs(y);

            if(absx > xMax)   xMax = absx;
            if(absy > yMax)   yMax = absy;
        }
    }

    return (xMax >= yMax)? xMax : yMax;
}

//вычисление статистики
void SystemCalculation::StatisticsCalc(const CalcData in, Statistica& out)
{
    out.diesNumFit = 0; out.diesNumUnfit = 0;
    //--------------------------------------------------------------------------------------
    //расчет среднего, минимум, максимум, сигма, годных чипов, двух типов негодных чипов
    for(int k = 0; k < in.diesNumUnmasked; ++k)
        if(in.vecValues_Unmasked[k] >= in.criteriumDn &&
                in.vecValues_Unmasked[k] <= in.criteriumUp)
        {
            ++out.diesNumFit;
            if( (in.criteriumDn >= 0 && in.criteriumUp >= 0) ||
                    (in.criteriumDn <= 0 && in.criteriumUp <= 0))
                out.avg += in.vecValues_Unmasked[k];
            else if(in.criteriumDn < 0 && in.criteriumUp > 0)
                out.avg += fabs(in.vecValues_Unmasked[k]);

            if(k == 0)   out.min = in.vecValues_Unmasked[0];
            if(k == 0)   out.max = in.vecValues_Unmasked[0];
            if(in.vecValues_Unmasked[k] < out.min)     out.min = in.vecValues_Unmasked[k];
            if(in.vecValues_Unmasked[k] > out.max)     out.max = in.vecValues_Unmasked[k];

            out.vecPairXY_Fit.push_back(in.vecPairXY_Unmasked[k]);
        }
        else if(in.vecValues_Unmasked[k] < in.criteriumDn)
            out.vecPairXY_UnfitLower.push_back(in.vecPairXY_Unmasked[k]);
        else if(in.vecValues_Unmasked[k] > in.criteriumUp)
            out.vecPairXY_UnfitUpper.push_back(in.vecPairXY_Unmasked[k]);
    //--------------------------------------------------------------------------------------
    //особые случаи для расчета среднего, минимум, максимум, сигма
    if(out.diesNumFit == 1)    out.min = out.max;
    //выход годных
    if(out.diesNumFit != 0)
    {
        //с учетом маскированных кристаллов:
        out.avg = out.avg / out.diesNumFit;

        out.diesNumUnfit = in.diesNumUnmasked - out.diesNumFit;
        out.diesNumUnfit = out.diesNumUnfit + in.diesNumMasked;
        int diesNum = out.diesNumFit + out.diesNumUnfit;
        out.diesUnfitPercent = ((double)out.diesNumUnfit)/((double)diesNum)*100.0;
        out.diesFitPercent = 100.0 - out.diesUnfitPercent;
    }
    if(out.diesNumFit == 0)
    {
        out.avg = 0.0;
        out.diesFitPercent = 0.0;
        out.avg = 0.0;
        out.std = 0.0;
        out.min = 0.0;
        out.max = 0.0;
        out.diesFitPercent = 0.0;
        out.diesNumUnfit = in.diesNumUnmasked - out.diesNumFit;
        out.diesUnfitPercent = ((double)out.diesNumUnfit)/((double)in.diesNumUnmasked)*100.0;
    }

    //---------------------------------------------------------------------------------------------
    //расчет среднеквадратичного отклонения (сигма) c учетом критерия
    if(out.diesNumFit != 0 && out.avg != 0.0)
    {
        for(int k = 0; k < in.vecValues_Unmasked.size(); ++k)
            if(in.vecValues_Unmasked[k] > in.criteriumDn && in.vecValues_Unmasked[k] < in.criteriumUp)
            {
                if( (in.criteriumDn >= 0 && in.criteriumUp >= 0) ||
                        (in.criteriumDn <= 0 && in.criteriumUp <= 0) )
                    out.std += qPow(out.avg - in.vecValues_Unmasked[k], 2);
                else if(in.criteriumDn < 0 && in.criteriumUp > 0)
                    out.std += qPow(out.avg - fabs(in.vecValues_Unmasked[k]), 2);
            }
    }
    out.std = out.std/(out.diesNumFit - 1);
    double AbsAvg = fabs(out.avg);
    if(AbsAvg)
        out.std = qSqrt(out.std)/AbsAvg*100.0;
    else
        out.std = 0.0;
    //-----------------------------------------------------------------------------------------------
    //особые случаи для расчета среднего, минимум, максимум, сигма
    if(out.diesNumFit == 1)    out.std = 0.0;

    if(out.diesNumFit == 0)
    {
        out.avg = 0.0; out.std = 0.0; out.min = 0.0; out.max = 0.0;
        out.diesFitPercent = 0.0; out.diesUnfitPercent = 0.0;
    }
    //--------------------------------------------------------------------------------------
}
//end of StatisticsCalculation
//---------------------------------------------------------------------------------------------------
//установка единицы измерения в карту
QString SystemCalculation::testElemUnitName(const QString& testName, const QString& paramName,
                                            const ValuePrefix valuePrefix)
{
    QString Unit = "";
    QString fullName = testName + paramName;

    switch(valuePrefix)
    {
    case ValuePrefix::norm:      break;
    case ValuePrefix::milli:     {    Unit += "м";     break;      }
    case ValuePrefix::micro:     {    Unit += "мк";    break;      }
    case ValuePrefix::nano:      {    Unit += "н";     break;      }
    case ValuePrefix::pico:      {    Unit += "п";     break;      }
    case ValuePrefix::kilo:      {    Unit += "к";     break;      }
    case ValuePrefix::mega:      {    Unit += "М";     break;      }
    case ValuePrefix::giga:      {    Unit += "Г";     break;      }
    case ValuePrefix::tera:      {    Unit += "Т";     break;      }
    default:                     break;
    }

    //сопротивление
    QRegExp pNpN("p[0-9]p[0-9]");
    QRegExp tRZ("tRZ"), KLV("KLV"), dM("dM"), VDP("VDP");
    QString Res = "Ом", R = "R";
    if(fullName.contains(pNpN) || fullName.contains(tRZ) || fullName.contains(KLV)
            || fullName.contains(dM) || fullName.contains(VDP) || paramName == R)
    {
        Unit += Res;
        return Unit;
    }
    QRegExp dZ("dZ"), Cont("Cont");
    QString ResPerCont = "Ом/конт";
    if(fullName.contains(dZ) || (fullName.contains("Z") && !fullName.contains(tRZ))
            || testName.contains(Cont))
    {
        Unit += ResPerCont;
        return Unit;
    }

    //напряжение
    QString Ap("Ap"), An("An"), Rp("Rp"), Rn("Rn"), Hp("Hp"), Hn("Hn");
    QString Vt("Vt"), Vbr("Vbr");
    QString Volt = "В";
    if( ( fullName.contains(Ap) || fullName.contains(An)
          || fullName.contains(Rp) || fullName.contains(Rn)
          || fullName.contains(Hp) || fullName.contains(Hn) )
            && (fullName.contains(Vt) || fullName.contains(Vbr)) )
    {
        Unit += Volt;
        return Unit;
    }

    //токи утечки затвор, сток-исток абсолютные
    QString leak("leak");
    QString Gleak("Gleak"), G("G");
    QString DSleak("DSleak"), DS("DS"), w("w");
    QString Amper = "А";
    if((fullName.contains(Ap) || (fullName.contains(An))
        || (fullName.contains(Rp)) || (fullName.contains(Rn))
        || (fullName.contains(Hp)) || (fullName.contains(Hn))) &&
            ( fullName.contains(Gleak) || fullName.contains(DSleak) ||
              (fullName.contains(G) && fullName.contains(leak) && !fullName.contains(w)) ||
              (fullName.contains(DS) && fullName.contains(leak) && !fullName.contains(w))) )
    {
        Unit += Amper;
        return Unit;
    }

    //ток утечки сток-исток приведенный
    QString DSw_leak("DSw_leak");// DSw("DSw");
    QString AmperPerMikron = "А/мкм";
    if((fullName.contains(Ap) || (fullName.contains(An))
        || (fullName.contains(Rp)) || (fullName.contains(Rn))
        || (fullName.contains(Hp)) || (fullName.contains(Hn)))
            && (fullName.contains(DSw_leak)
                || (fullName.contains(DS) && fullName.contains(leak) && fullName.contains(w))))
    {
        Unit += AmperPerMikron;
        return Unit;
    }

    //ток насыщения абсолютный
    QString DScurrent("DScurrent"), current("current");
    if(
            (fullName.contains(Ap) || (fullName.contains(An))
             || (fullName.contains(Rp)) || (fullName.contains(Rn))
             || (fullName.contains(Hp)) || (fullName.contains(Hn)))
            && (fullName.contains(DScurrent)
                || (fullName.contains(DS) && fullName.contains(current) && !fullName.contains(w))))
    {
        Unit += Amper;
        return Unit;
    }

    //ток насыщения приведенный
    QString DSw_driver("DSw_driver"), driver("driver");
    if(
            (fullName.contains(Ap) || (fullName.contains(An))
             || (fullName.contains(Rp)) || (fullName.contains(Rn))
             || (fullName.contains(Hp)) || (fullName.contains(Hn)))
            && (fullName.contains(DSw_driver)
                || (fullName.contains(DS) && fullName.contains(driver) && fullName.contains(w))))
    {
        Unit += AmperPerMikron;
        return Unit;
    }

    //ток насыщения приведенный
    QString Diod("Diod"), diod("diod");
    if(fullName.contains(Diod) || fullName.contains(diod))
    {
        Unit += Amper;
        return Unit;
    }

    //крутизна
    QString Be("Be"), be("be"), AdV2("А/В2");
    if(fullName.contains(Be) || fullName.contains(be))
    {
        Unit += AdV2;
        return Unit;
    }

    return Unit;
}
//---------------------------------------------------------------------------------------------------
