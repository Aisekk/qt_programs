#ifndef REPORTSWINPDF_H
#define REPORTSWINPDF_H

#include "ReportsWinTXT.h"


class ReportsWinPDF : public ReportsWinTXT
{
    Q_OBJECT
public:
    ReportsWinPDF(QWidget *pwgt, shared_ptr<Lot> spLot);
    ~ReportsWinPDF();

    void sendOneWaferReportSig(int slotNum) override;
    void sendAllWafersReportsSig() override;
};

#endif // REPORTSWINPDF_H
