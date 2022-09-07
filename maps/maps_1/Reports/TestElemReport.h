#ifndef TESTELEMREPORT_H
#define TESTELEMREPORT_H

#include <QString>
#include <QFont>

#include <iostream>
#include <iomanip>
#include <memory>

#include "Lot/TestElem.h"
#include "TestElemData.h"
using namespace std;

class TestElemReport
{
public:
    TestElemReport(const int slotNum, const int testNum, const shared_ptr<TestElem> spTestElem);

    void setTestElemData(TestElemData &testElemData);

    friend ostream& operator << (ostream& os, const TestElemReport& te);
    //friend string& operator += (string& s, const TestElemReport& te);
    friend QString& operator + (QString& s, const TestElemReport& te);

private:
    int m_slotNum;
    int m_testNum;
    shared_ptr<TestElem> m_spTestElem;
    string m_stdTestName;
    string m_stdParamName;
    string m_stdUnitName;

    int m_diesNum;
    int m_diesNumUnmasked;
    int m_diesNumMasked;
    int m_diesNumFit;
    int m_diesNumUnfit;
    double m_diesFitPercent;
    double m_diesUnfitPercent;

    double m_criteriumDn;
    double m_criteriumUp;
    double m_avg;
    double m_std;
    double m_min;
    double m_max;
};

#endif // TESTELEMREPORT_H
