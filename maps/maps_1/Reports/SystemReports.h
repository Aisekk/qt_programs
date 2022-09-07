#ifndef SYSTEMREPORTS_H
#define SYSTEMREPORTS_H

#include <QTextEdit>
#include <QPrinter>
#include <QCoreApplication>
#include <memory>

#include "Progress.h"
#include "ReportsWinTXT.h"
#include "ReportsWinPDF.h"
#include "TestElemData.h"
#include "TestElemReport.h"

#include "Calculation/SystemCalculation.h"
#include "Norms/SystemNorms.h"
class ReportsCalc;
//============================================================================================
namespace SystemReports
{
extern unique_ptr<ReportsWinTXT> upReportsWinTXT;
extern unique_ptr<ReportsWinPDF> upReportsWinPDF;
extern ReportsCalc reportsCalculator;
}
//============================================================================================
class ReportsCalc : public QObject
{
    Q_OBJECT
public:
    ReportsCalc();
    ~ReportsCalc();
public slots:
    void slotOneWaferReport(const int slotNum, const ReportData &reportData);
    void slotAllWafersReports(const ReportData &reportData);
private:
    void calcTestElemReport(TestElemData &testElemData, TestElemReport &testElemReport);
};

#endif // SREPORTS_H
//============================================================================================
