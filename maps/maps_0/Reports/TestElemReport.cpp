#include "TestElemReport.h"

TestElemReport::TestElemReport(int slotNum, int testNum, shared_ptr<TestElem> spTestElem)
    : m_slotNum(slotNum), m_testNum(testNum), m_spTestElem(spTestElem)
{
    QString testName = m_spTestElem->getTestName();
    QString paramName = m_spTestElem->getParamName();
    QString unitName = m_spTestElem->getUnitName();
    m_stdTestName = testName.toStdString();
    m_stdParamName = paramName.toStdString();
    m_stdUnitName = unitName.toStdString();
}
//-----------------------------------------------------------------------------------
void TestElemReport::setTestElemData(TestElemData& testElemData)
{
    unique_ptr<TestElemStatistics> upTestElemStats =
            std::move(testElemData.getTestElemStatistics());
    TestElemStatistics *pTestElemStats{};
    if(upTestElemStats) pTestElemStats = upTestElemStats.get();

    m_criterionDn = testElemData.getCriterionDn();
    m_criterionUp = testElemData.getCriterionUp();

    m_diesNum = pTestElemStats->getDiesNum();
    m_diesNumUnmasked = pTestElemStats->getDiesNumUnmasked();
    m_diesNumMasked = pTestElemStats->getDiesNumMasked();
    m_diesNumFit = pTestElemStats->getDiesNumFit();
    m_diesNumUnfit = pTestElemStats->getDiesNumUnfit();
    m_diesFitPercent = pTestElemStats->getDiesFitPercent();
    m_diesUnfitPercent = pTestElemStats->getDiesUnfitPercent();

    m_avg = pTestElemStats->getAvg();
    m_std = pTestElemStats->getStd();
    m_min = pTestElemStats->getMin();
    m_max = pTestElemStats->getMax();
}
//-----------------------------------------------------------------------------------
ostream& operator << (ostream& os, const TestElemReport& te)
{
    int p = 2;
    string line;  for(int i = 0; i < 43 ; ++i)  line.append("-");

    os << line << te.m_testNum << line << endl;
    os << " Тест:             " << te.m_stdTestName << endl;
    os << " Параметр:         " << te.m_stdParamName << endl;
    os << " Ед. измерения:    " << te.m_stdUnitName << endl;
    os << endl;

    os << " Кристаллов:       " << endl;
    os << " измеренных:       " << te.m_diesNum << endl;
    os << " немаскированных:  " << te.m_diesNumUnmasked << endl;
    os << " маскированных:    " << te.m_diesNumMasked << endl;
    os << fixed << setprecision(p);
    os << " годных:           " << setw(3) << te.m_diesNumFit
       << setw(2) << "(" << te.m_diesFitPercent << "%)" << endl;
    os << " брак:             " << setw(3) << te.m_diesNumUnfit
       << setw(2) << "(" << te.m_diesUnfitPercent << "%)" << endl;
    os << endl;

    double restrictUp = 1000.0, restrictDn = 0.01;

    if(fabs(te.m_criterionDn) >= restrictUp || fabs(te.m_criterionUp) >= restrictUp
            || fabs(te.m_criterionDn) < restrictDn || fabs(te.m_criterionUp) < restrictDn)
        os << scientific << setprecision(p);
    else
        os << fixed << setprecision(p);

    os << " Интервал:         " << "[" << te.m_criterionDn << ";" << te.m_criterionUp << "]" << endl;


    if( (fabs(te.m_avg) >= restrictUp || fabs(te.m_avg) < restrictDn)
            && fabs(te.m_avg) != 0 )
        os << scientific << setprecision(p);
    else
        os << fixed << setprecision(p);
    os << " среднее:          " << te.m_avg << endl;

    if( (fabs(te.m_std) >= restrictUp || fabs(te.m_std) < restrictDn)
            && fabs(te.m_std) != 0)
        os << scientific << setprecision(p);
    else
        os << fixed << setprecision(p);
    os << " сигма,%:          " << te.m_std << endl;

    if( (fabs(te.m_min) >= restrictUp || fabs(te.m_min) < restrictDn)
            && fabs(te.m_min) != 0)
        os << scientific << setprecision(p);
    else
        os << fixed << setprecision(p);
    os << " минимум:          " << te.m_min << endl;

    if( (fabs(te.m_max) >= restrictUp || fabs(te.m_max) < restrictDn)
            && fabs(te.m_max) != 0)
        os << scientific << setprecision(p);
    else
        os << fixed << setprecision(p);
    os << " максимум:         " << te.m_max;// << endl;

    return os;
}

QString& operator + (QString& qs, const TestElemReport& te)
{
    QString line;  for(int i = 0; i < 90 ; ++i)  line.append("-");
    qs += "\n" + line + "\n";
    qs += "\n";
    //----------------------------------------------------------------------------------
    qs += "Номер:               " + QString::number(te.m_testNum, 10) + "\n";
    qs += "Тест:                " + QString::fromStdString(te.m_stdTestName) + "\n";
    qs += "Параметр:            " + QString::fromStdString(te.m_stdParamName) + "\n";
    qs += "Ед. измерения:       " + QString::fromStdString(te.m_stdUnitName) + "\n";
    qs += "\n";
    //----------------------------------------------------------------------------------
    qs += "Кристаллов:\n";
    qs += "измеренных:          " + QString::number(te.m_diesNum, 10) + "\n";
    qs += "немаскированных:     " + QString::number(te.m_diesNumUnmasked, 10) + "\n";
    qs += "маскированных:       " + QString::number(te.m_diesNumMasked, 10) + "\n";
    qs += "годных:              " + QString::number(te.m_diesNumFit, 10) +
            " (" + QString::number(te.m_diesFitPercent, 'f', 2) + "%)" + "\n";
    qs += "брак:                " + QString::number(te.m_diesNumUnfit, 10) +
            " (" + QString::number(te.m_diesUnfitPercent, 'f', 2) + "%)" + "\n";
    qs += "\n";
    //----------------------------------------------------------------------------------
    double MAX = 1000.0, MIN = 0.01;
    qs += "Интервал:            [";
    if(fabs(te.m_criterionDn) >= MAX || fabs(te.m_criterionDn) < MIN
            || fabs(te.m_criterionUp) >= MAX || fabs(te.m_criterionUp) < MIN)
        qs += QString::number(te.m_criterionDn,'e',2) + ";" + QString::number(te.m_criterionUp,'e',2);
    else
        qs += QString::number(te.m_criterionDn,'f',2) + ";" + QString::number(te.m_criterionUp,'f',2);
    qs += "]\n";

    qs += "среднее:             ";
    if( (fabs(te.m_avg) >= MAX || fabs(te.m_avg) < MIN)
            && fabs(te.m_avg) != 0)
        qs += QString::number(te.m_avg, 'e', 2) + "\n";
    else
        qs += QString::number(te.m_avg, 'f', 2) + "\n";

    qs += "сигма,%:             ";
    if( (fabs(te.m_std) >= MAX || fabs(te.m_std) < MIN)
            && fabs(te.m_std) != 0)
        qs += QString::number(te.m_std, 'e', 2) + "\n";
    else
        qs += QString::number(te.m_std, 'f', 2) + "\n";

    qs += "минимум:             ";
    if( (fabs(te.m_min) >= MAX || fabs(te.m_min) < MIN)
            && fabs(te.m_min) != 0)
        qs += QString::number(te.m_min, 'e', 2) + "\n";
    else
        qs += QString::number(te.m_min, 'f', 2) + "\n";

    qs += "максимум:            ";
    if( (fabs(te.m_max) >= MAX || fabs(te.m_max) < MIN)
            && fabs(te.m_max) != 0)
        qs += QString::number(te.m_max, 'e', 2);
    else
        qs += QString::number(te.m_max, 'f', 2);

    qs += "\n";
    //----------------------------------------------------------------------------------
    return qs;
}
//-----------------------------------------------------------------------------------
