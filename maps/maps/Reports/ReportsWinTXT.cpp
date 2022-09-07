#include "ReportsWinTXT.h"

ReportsWinTXT::ReportsWinTXT(QWidget *pwgt, shared_ptr<Lot> spLot) :
    QDialog(pwgt, Qt::WindowTitleHint | Qt::WindowCloseButtonHint | Qt::WindowMinMaxButtonsHint),
    m_spLot(spLot)
{
    setLot(spLot);
    setReportFormat(ReportFormat::TXT);
    //построение "динамической" формы для переменного количества пластин, переданного в конструктор
    setModal(true);
    setWindowTitle("Создать TXT-отчет(ы)");
    setFixedSize(QWidget::sizeHint());

    QString strGaps;  for(int i = 0; i < 15 ; ++i) strGaps.append(" ");
    m_pLabel = new QLabel(strGaps + "Сначала откройте файл" + strGaps);

    m_vecSlotNums = m_spLot->getSlotNums();
    m_waferCount = m_vecSlotNums.size();
    int N = m_waferCount;//=количество кнопок
    int N_limit = 50;
    int sq = sqrt(N), sq0 = sq;
    if(sq == 1){sq = 2; sq0 = 2;}

    m_pvbxMainLayout = new QVBoxLayout;
    m_pgrdLayout = new QGridLayout;

    QString lotName = m_spLot->getLotName();
    QLabel* plbl = new QLabel("по партии: \n" + lotName);
    m_pvbxMainLayout->addWidget(plbl,0,Qt::AlignLeft);

    int row = 1, col = 0;
    bool goto_newRow = true;
    int slotNum = 0;
    if(N <= N_limit && N > 0)
    {
        for(int i = 1; i <= N; i++)
        {
            QPushButton *pSlotButton = new QPushButton;
            slotNum = m_vecSlotNums[i-1];
            pSlotButton->setObjectName(QString::number(slotNum,10));
            pSlotButton->setText("Слот " + QString::number(slotNum,10));
            m_mapSlotButtons.insert(slotNum, pSlotButton);

            if(i > sq && goto_newRow == true)
            {
                row++;//переход на новую строку
                col = 0;//на нулевой столбец в новой строке
                goto_newRow = false;
                sq+=sq0;
            }
            goto_newRow = true;
            m_pgrdLayout->addWidget(pSlotButton, row, col);
            col++;
        }
    }
    else if(N > N_limit)
    {
        QString strMax = strGaps + "Количество пластин превышает "
                + QString::number(N_limit,10) + strGaps;
        QLabel* plbl = new QLabel(strMax);
        m_pgrdLayout->addWidget(plbl, 1, 0, Qt::AlignJustify);
    }


    if(N == 0)
        m_pgrdLayout->addWidget(m_pLabel, 1, 0, Qt::AlignJustify);
    else if(N <= N_limit && N > 0)
    {
        int buttonW = 115, buttonH = 40;

        QHBoxLayout *phbxLayout = new QHBoxLayout;

        //большая кнопка для всех слотов - несколько файлов
        m_pAllWafersReportsBtn = new QPushButton;
        m_pAllWafersReportsBtn->setMinimumSize(buttonW,buttonH);
        m_pAllWafersReportsBtn->setObjectName("AllWafersBtn1");
        m_pAllWafersReportsBtn->setText("Отчеты по\n всем слотам");
        phbxLayout->addWidget(m_pAllWafersReportsBtn);

        //большая кнопка для всех слотов - один файл
        m_pAllWafersOneReportBtn = new QPushButton;
        m_pAllWafersOneReportBtn->setEnabled(false);

        m_pAllWafersOneReportBtn->setMinimumSize(buttonW,buttonH);
        m_pAllWafersOneReportBtn->setObjectName("AllWafersBtn2");
        m_pAllWafersOneReportBtn->setText("Один отчет\n по всем слотам");
        phbxLayout->addWidget(m_pAllWafersOneReportBtn);
        m_pgrdLayout->addLayout(phbxLayout, ++row, 0, 1, sq0);
        //----------------------------------------------------------------------------------------
        //соединения - до установки компоновки !!!
        //соединение кнопки на форме со слотом, создающим отчеты по всем пластинам в партии
        connect(m_pAllWafersReportsBtn, QPushButton::clicked, this, slotEmitAllWafersAllReports);
        //соединение кнопки на форме со слотом, создающим один отчет по всем пластинам в партии
        connect(m_pAllWafersOneReportBtn, QPushButton::clicked, this, slotEmitAllWafersOneReport);
    }

    m_pvbxMainLayout->addLayout(m_pgrdLayout,0);
    setLayout(m_pvbxMainLayout);
    //-----------------------------------------------------------------------------------------
    //соединение каждой кнопки на форме со слотом, создающим отчет
    if(!m_mapSlotButtons.isEmpty())
    {
        QMap<size_t,QPushButton*>::const_iterator cit = m_mapSlotButtons.constBegin();
        while(cit != m_mapSlotButtons.constEnd())
        {
            QPushButton *pSlotButton = cit.value();
            if(pSlotButton != nullptr)
                connect(pSlotButton, QPushButton::clicked, this, ReportsWinTXT::slotEmitSlotNum);
            ++cit;
        }
    }
    //-----------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------
ReportsWinTXT::~ReportsWinTXT(){}
//----------------------------------------------------------------------------------------
ReportData ReportsWinTXT::getReportData() const
{
    return m_reportData;
}
//----------------------------------------------------------------------------------------
void ReportsWinTXT::setReportFormat(ReportFormat repFormat)
{
    m_reportData.setReportFormat(repFormat);
}
void ReportsWinTXT::setNormsID(NormsID id)
{
    m_reportData.setNormsID(id);
}
void ReportsWinTXT::setMapType(MapType mapType)
{
    m_reportData.setMapType(mapType);
}
void ReportsWinTXT::setMapImage(MapImage* pMapImage)
{
    m_reportData.setMapImage(pMapImage);
}
void ReportsWinTXT::setLot(shared_ptr<Lot> spLot)
{
    m_reportData.setLot(spLot);
}
//----------------------------------------------------------------------------------------
void ReportsWinTXT::slotEmitSlotNum()
{
    //вычисление адреса объекта, передавшего сигнал, а по нему - номера слота
    int slotNum{};
    QPushButton *pSelectedSlotButton = qobject_cast<QPushButton*>(sender());
    if(pSelectedSlotButton != nullptr)
        slotNum = (pSelectedSlotButton->objectName()).toInt();
    //-------------------------------------------------------------------------
    //на основании выбранного пользователем номера слота (нажатой кнопки):
    //отправка главному объекту номера слота, формата вывода в файл, UI-данных
    sendOneWaferReportSig(slotNum);
}

void ReportsWinTXT::sendOneWaferReportSig(int slotNum)
{
    ReportData reportData = getReportData();
    emit sigOneWaferReport(slotNum, reportData);
}
void ReportsWinTXT::sendAllWafersReportsSig()
{
    ReportData reportData = getReportData();
    emit sigAllWafersReports(reportData);
}

void ReportsWinTXT::slotEmitAllWafersAllReports()
{
    sendAllWafersReportsSig();
}
void ReportsWinTXT::slotEmitAllWafersOneReport()
{
    emit sigAllWafersOneReport();
}

