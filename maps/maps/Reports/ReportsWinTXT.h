#ifndef REPORTSWINTXT_H
#define REPORTSWINTXT_H

#include <QDialog>
#include <QGridLayout>
#include <QBoxLayout>
#include <QPushButton>
#include <QWidget>
#include <QLabel>
#include <QMap>
#include <QVector>
#include <QTextStream>
#include <QFile>
#include <QAction>
#include <QString>

#include <iostream>
#include <fstream>
#include <string>

#include "LotGroup/Lot.h"
#include "Types.h"
#include "MapImage.h"
#include "ReportData.h"
using namespace std;


class ReportsWinTXT : public QDialog
{
    Q_OBJECT
//--------------------------------------------------------------------------
public:
    ReportsWinTXT(QWidget *pwgt, shared_ptr<Lot> spLot);
    virtual ~ReportsWinTXT();

    ReportData getReportData() const;

    void setReportFormat(ReportFormat repFormat);
    void setNormsID(NormsID id);
    void setMapType(MapType mapType);
    void setMapImage(MapImage* mapImage);
    void setLot(shared_ptr<Lot> spLot);

signals:
    void sigOneWaferReport(int, ReportData&);
    void sigAllWafersReports(ReportData&);
    void sigAllWafersOneReport();
//--------------------------------------------------------------------------
protected:
    virtual void sendOneWaferReportSig(int slotNum);
    virtual void sendAllWafersReportsSig();
protected slots:
    void slotEmitAllWafersOneReport();
    void slotEmitSlotNum();
    void slotEmitAllWafersAllReports();
protected:
    size_t m_waferCount{};
    ReportData m_reportData{};
    QLabel *m_pLabel{};
    QVBoxLayout *m_pvbxMainLayout{};
    QGridLayout *m_pgrdLayout{};
    QPushButton *m_pAllWafersReportsBtn{};
    QPushButton *m_pAllWafersOneReportBtn{};
    shared_ptr<Lot> m_spLot;

    QVector<size_t> m_vecSlotNums;
    QMap<size_t,QPushButton*> m_mapSlotButtons;
};

#endif // REPORTSWINTXT_H
