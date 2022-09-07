#include "ReportsWinPDF.h"

ReportsWinPDF::ReportsWinPDF(QWidget *pwgt, const shared_ptr<Lot> spLot) : ReportsWinTXT(pwgt, spLot)
{
    setWindowTitle("Создать PDF-отчет(ы)");
    setReportFormat(ReportFormat::PDF);
}

ReportsWinPDF::~ReportsWinPDF() {}

void ReportsWinPDF::sendOneWaferReportSig(int slotNum)
{
    ReportData reportData = getReportData();
    emit sigOneWaferReport(slotNum, reportData);
}

void ReportsWinPDF::sendAllWafersReportsSig()
{
    ReportData reportData = getReportData();
    emit sigAllWafersReports(reportData);
}
