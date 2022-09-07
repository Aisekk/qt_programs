#include "SystemReports.h"

//============================================================================================
unique_ptr<ReportsWinTXT> SystemReports::upReportsWinTXT{};
unique_ptr<ReportsWinPDF> SystemReports::upReportsWinPDF{};
ReportsCalc SystemReports::reportsCalculator{};
//============================================================================================
ReportsCalc::ReportsCalc(){}
ReportsCalc::~ReportsCalc(){}
//--------------------------------------------------------------------------------------------
//создание отчета тестового элемента
void ReportsCalc::calcTestElemReport(TestElemData& testElemData, TestElemReport &testElemReport)
{
    //расчет статистики:
    SystemCalculation::calcTestElemStatistics(testElemData);
    //передача статистики в отчет:
    testElemReport.setTestElemData(testElemData);
}

//отчет по одной пластине
void ReportsCalc::slotOneWaferReport(int slotNum, const ReportData& reportData)
{
    //для урезания файла и однократных записей
    static int staticTestIndex = 0;
    //--------------------------------------------------------------------------------
    shared_ptr<Lot> spLot = reportData.getLot();
    //извлечение данных партии
    int slotIndex = -1;
    //int lotNum = 0;
    int testCount = -1;
    QString lotName{};
    shared_ptr<Wafer> spWafer;
    if(spLot)
    {
        lotName = spLot->getLotName();
        slotIndex = spLot->getSlotIndex(slotNum);
        if(slotIndex != -1)
            spWafer = spLot->getWafer(slotIndex);
        if(spWafer != nullptr)
            testCount = spWafer->getTestElemCount();
    }
    //--------------------------------------------------------------------------------
    //извлечение UI-данных:
    ReportFormat reportFormat = reportData.getReportFormat();
    NormsID normsID = reportData.getNormsID();
    MapType mapType = reportData.getMapType();
    MapImage* pMapImage = reportData.getMapImage();
    //--------------------------------------------------------------------------------
    switch(reportFormat)
    {
    case ReportFormat::TXT:
    {
        string strSlotNum = (QString::number(slotNum,10)).toStdString();
        string filename;
        filename = "report_slot " + strSlotNum + ".txt";

        fstream outfile;
        if(staticTestIndex == 0)
        {
            //открытие файла для его урезания, однократных записи номера слота и названия партии
            outfile.open(filename.data(), ios::out | ios::trunc);
            string stdLotFileName = lotName.toStdString();
            outfile << endl << " " << stdLotFileName << ": " << endl;
            string line;  for(int i = 0; i < 40 ; ++i)  line.append("=");
            outfile << endl << line << " Слот " << strSlotNum << " " <<
                       line << endl << endl;
            outfile.close();
        }

        //запись в файл всех тестовых элементов в слоте
        outfile.open(filename.data(), ios::app | ios::out);
        for(int testIndex = 0; testIndex < testCount; ++testIndex)
        {
            shared_ptr<TestElem> spTestElem = spWafer->getTestElem(testIndex);
            if(spTestElem == nullptr)  return;
            TestElemReport testElemReport(slotNum, staticTestIndex, spTestElem);
            ++staticTestIndex;

            TestElemData testElemData{};
            testElemData.setLot(spLot);
            testElemData.setSlotIndex(slotIndex);
            testElemData.setTestIndex(testIndex);
            //добавление UI-данных
            testElemData.setNormsID(normsID);
            SystemNorms::setTestElemNorm(testElemData);
            testElemData.setMapType(mapType);
            testElemData.setMapImage(pMapImage);

            //создание объекта-отчета по тестовому элементу
            calcTestElemReport(testElemData, testElemReport);

            //запись в файл по одному тесту
            outfile << testElemReport << endl;

            if(testIndex == testCount - 1)
                staticTestIndex = 0;
        }

        outfile.close();

        break;
    }
    case ReportFormat::PDF:
    {
        QTextEdit *ptxt = new QTextEdit;
        QFont fontOut("Courier New", 8);
        fontOut.setWeight(QFont::Normal);
        ptxt->setFont(fontOut);

        QPrinter printer(QPrinter::HighResolution);
        printer.setOutputFormat(QPrinter::PdfFormat);
        QString strFileName = "отчет_слот " + QString::number(slotNum,10) + ".pdf";
        printer.setOutputFileName(strFileName);


        QString line;  for(int i = 0; i < 90 ; ++i)  line.append("-");
        QString strReport = "ОТЧЕТ по " + lotName +
                ":\n" + line +
                "\nСЛОТ " + QString::number(slotNum,10);

        for(int testIndex = 0; testIndex < testCount; ++testIndex)
        {
            shared_ptr<TestElem> spTestElem = spWafer->getTestElem(testIndex);
            if(spTestElem == nullptr)  return;
            TestElemReport testElemReport(slotNum, staticTestIndex, spTestElem);
            ++staticTestIndex;

            TestElemData testElemData{};
            testElemData.setLot(spLot);
            testElemData.setSlotIndex(slotIndex);
            testElemData.setTestIndex(testIndex);
            //добавление UI-данных
            testElemData.setNormsID(normsID);
            SystemNorms::setTestElemNorm(testElemData);
            testElemData.setMapType(mapType);
            testElemData.setMapImage(pMapImage);

            //создание объекта-отчета по тестовому элементу
            calcTestElemReport(testElemData, testElemReport);

            //конкатенация по одному тесту
            strReport = strReport + testElemReport;

            if(staticTestIndex % 4 == 0)
                strReport = strReport + "\n" + lotName +
                        ":\n" + line + "\nСЛОТ " + QString::number(slotNum,10);

            //зануление статической переменной на последнем тесте
            if(testIndex == testCount - 1)
                staticTestIndex = 0;
        }

        ptxt->setText(strReport);
        ptxt->document()->print(&printer);
        delete ptxt;
    }
    }
    //end of switch
}

//отчеты по всем пластинам в партии: одна пластина - один файл
void ReportsCalc::slotAllWafersReports(const ReportData& reportData)
{
    QVector<size_t> vecSlotNums;
    shared_ptr<Lot> spLot = reportData.getLot();
    if(spLot)
        vecSlotNums = spLot->getSlotNums();

    Progress progress(nullptr, vecSlotNums.size());
    progress.show();

    size_t step = 0;
    for(auto slotNum : vecSlotNums)
    {
        slotOneWaferReport(slotNum, reportData);
        progress.setStep(++step);
        qApp->processEvents();
    }
}

//============================================================================================
