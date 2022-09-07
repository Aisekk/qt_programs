#include "ConfigWin.h"

ConfigWin::ConfigWin(QWidget *pwgt, QMap<size_t, size_t> mapSlotIndexesNums) :
    QDialog(pwgt, Qt::WindowTitleHint | Qt::WindowCloseButtonHint | Qt::WindowMinMaxButtonsHint),
    m_mapSlotIndexNums(mapSlotIndexesNums)
{
    //для задания положения дочерних окон
    m_tableViewPos = 100; m_tableViewShift = 50;
    //---------------------------------------------------------------------------------------------
    setMaximumSize(500,500);
    m_pvbxMainLayout = new QVBoxLayout;
    m_pgrdLayout = new QGridLayout;

    size_t slotNum = 0;
    size_t slotIndex = 0;
    size_t n = mapSlotIndexesNums.size();
    size_t n_max = 25;

    size_t row = 1, col = 0;
    size_t limitOnColumnCount = 5;
    QString slot = "слот ", space = "";
    if(n == 1) { slot = "                         слот "; space = "                         ";}
    if(n > 0 && n <= n_max)
        for(size_t i = 1; i <= n; i++)
        {
            //-------------------------------------------------------------------------------------
            //создание динамической формы
            QPushButton *pSlotButton = new QPushButton;
            if(!mapSlotIndexesNums.isEmpty())
                slotNum = mapSlotIndexesNums.value(slotIndex);
            slotIndex++;
            pSlotButton->setObjectName(QString::number(slotNum,10));
            pSlotButton->setText(slot + QString::number(slotNum,10) + space);
            if(i > limitOnColumnCount)
            {
                row++;//переход на новую строку
                col = 0;//на нулевой столбец в новой строке
                limitOnColumnCount += 5;
            }
            col++;
            //-------------------------------------------------------------------------------------
            m_pgrdLayout->addWidget(pSlotButton, row, col);
            //-------------------------------------------------------------------------------------
            //соединения - до установки компоновки !!!
            if(pSlotButton != nullptr)
            {
                connect(pSlotButton, &QPushButton::clicked, this, slotWaferParamsTableWin);
                connect(pSlotButton, &QPushButton::pressed, this, slotWaferParamsTableWin);
                connect(pSlotButton, &QPushButton::clicked, this, slotWaferValuesTableWin);
                connect(pSlotButton, &QPushButton::pressed, this, slotWaferValuesTableWin);
                connect(pSlotButton, &QPushButton::clicked, this, slotLotTableWin);
                connect(pSlotButton, &QPushButton::pressed, this, slotLotTableWin);
            }
            //-------------------------------------------------------------------------------------
        }
    else
    {
        QLabel *pLabel = new QLabel("В файле нет данных");
        m_pgrdLayout->addWidget(pLabel, 1, 0, Qt::AlignJustify);
    }

    m_pvbxMainLayout->addLayout(m_pgrdLayout,0);
    setLayout(m_pvbxMainLayout);
}
//-------------------------------------------------------------------------------------------------
void ConfigWin::setDatabase(const QSqlDatabase& db)
{
    if(db.isOpen())  m_dataBase = db;
    qDebug() << "Database is open";
}
void ConfigWin::closeEvent(QCloseEvent*)
{
    if(m_dataBase.isOpen())
    {
        m_dataBase.close();
        qDebug() << "Database is closed";
    }
    clearAll_Model_and_View_SqlTables();
}
//-------------------------------------------------------------------------------------------------
QString ConfigWin::getLotName() const
{
    return m_lotName;
}
void ConfigWin::setLotName(const QString& lotName)
{
    m_lotName = lotName;
}
//-------------------------------------------------------------------------------------------------
//save wafer params
void ConfigWin::saveWaferSqlTableModel(const size_t slotNum,
                                       const shared_ptr<QSqlTableModel> spSqlTableModel)
{
    m_map_spSqlWaferTableModel.insert(slotNum, spSqlTableModel);
}
void ConfigWin::saveWaferTableView(const size_t slotNum,
                                   const shared_ptr<QTableView> spTableView)
{
    m_map_spWaferTableView.insert(slotNum, spTableView);
}
//save wafer values
void ConfigWin::saveWaferValuesSqlTableModel(const size_t slotNum,
                                             const shared_ptr<QSqlTableModel> spSqlTableModel)
{
    m_map_spSqlTestElemValuesTableModel.insert(slotNum, spSqlTableModel);
}
void ConfigWin::saveWaferValuesTableView(const size_t slotNum,
                                         const shared_ptr<QTableView> spTableView)
{
    m_map_spTestElemValuesTableView.insert(slotNum, spTableView);
}

//save lot data
void ConfigWin::saveLotDataSqlTableModel(const size_t slotNum,
                                         const shared_ptr<QSqlTableModel> spSqlTableModel)
{
    m_map_spSqlLotDataTableModel.insert(slotNum, spSqlTableModel);
}
void ConfigWin::saveLotDataTableView(const size_t slotNum,
                                     const shared_ptr<QTableView> spTableView)
{
    m_map_spLotDataTableView.insert(slotNum, spTableView);
}
//-------------------------------------------------------------------------------------------------
void ConfigWin::clearAll_Model_and_View_SqlTables()
{
    //delete wafer params
    m_map_spSqlWaferTableModel.clear();
    m_map_spWaferTableView.clear();
    //delete wafer values
    m_map_spSqlTestElemValuesTableModel.clear();
    m_map_spTestElemValuesTableView.clear();
    //delete lot data
    m_map_spSqlLotDataTableModel.clear();
    m_map_spLotDataTableView.clear();
}
//-------------------------------------------------------------------------------------------------
//slots
//-------------------------------------------------------------------------------------------------
void ConfigWin::slotWaferParamsTableWin()
{
    if(!m_dataBase.isOpen()){
        qDebug() << "Database is not open when a Wafer TableWin creating; exiting"; return;}

    size_t slotNum{};
    QPushButton *pSlotButton = qobject_cast<QPushButton*>(sender());
    if(pSlotButton != nullptr)
        slotNum = (pSlotButton->objectName()).toInt();
    if(slotNum > 0)
    {
        QString WaferParamsTable =
                SystemDataBase::WaferParamsSqlTable  + QString::number(slotNum,10);
        //-----------------------------------------------------------------------------------------
        //создать модель
        shared_ptr<QSqlTableModel> spSqlTableModel = make_shared<QSqlTableModel>();
        if(spSqlTableModel)
        {
            spSqlTableModel->setTable(WaferParamsTable);
            spSqlTableModel->select();
        }
        //сохранить модель
        saveWaferSqlTableModel(slotNum, spSqlTableModel);
        //-----------------------------------------------------------------------------------------
        QString lotName = getLotName();
        //-----------------------------------------------------------------------------------------
        //создать таблицу и установить в нее модель
        shared_ptr<QTableView> spTableView = make_shared<QTableView>();
        if(spTableView && spSqlTableModel)
        {
            QSqlTableModel *pModel = spSqlTableModel.get();
            if(pModel != nullptr)
                spTableView->setModel(pModel);
            spTableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
            spTableView->resize(450, 450);
            QString waferTitle = lotName + ":  слот " + QString::number(slotNum,10) +
                    " (параметры)";
            spTableView->setWindowTitle(waferTitle);
            int shift = m_tableViewPos;
            spTableView->move(shift, shift);
            spTableView->show();
        }
        //сохранить таблицу
        saveWaferTableView(slotNum, spTableView);
        //-----------------------------------------------------------------------------------------
    }
    else
        qDebug() << "slotNum is uncorrect when a Wafer TableWin creating";

}
void ConfigWin::slotWaferValuesTableWin()
{
    if(!m_dataBase.isOpen()){
        qDebug() << "Database is not open when a TestElem Values TableWin creating; exiting"; return;}

    size_t slotNum{};
    QPushButton *pSlotButton = qobject_cast<QPushButton*>(sender());
    if(pSlotButton != nullptr)
        slotNum = (pSlotButton->objectName()).toInt();
    if(slotNum > 0)
    {
        QString WaferValuesTable =
                SystemDataBase::WaferValuesSqlTable + QString::number(slotNum,10);
        //-----------------------------------------------------------------------------------------
        //создать модель
        shared_ptr<QSqlTableModel> spSqlTableModel = make_shared<QSqlTableModel>();
        if(spSqlTableModel)
        {
            spSqlTableModel->setTable(WaferValuesTable);
            spSqlTableModel->select();
        }
        //сохранить модель
        saveWaferValuesSqlTableModel(slotNum, spSqlTableModel);
        //-----------------------------------------------------------------------------------------
        QString lotName = getLotName();
        //-----------------------------------------------------------------------------------------
        //создать таблицу и установить в нее модель
        shared_ptr<QTableView> spTableView = make_shared<QTableView>();
        if(spTableView && spSqlTableModel)
        {
            QSqlTableModel *pModel = spSqlTableModel.get();
            if(pModel != nullptr)
                spTableView->setModel(pModel);
            spTableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
            spTableView->resize(450, 450);
            QString testElemsTitle = lotName + ":  слот " + QString::number(slotNum,10) +
                    " (значения)";
            spTableView->setWindowTitle(testElemsTitle);
            int shift = m_tableViewPos + m_tableViewShift;
            spTableView->move(shift, shift);
            spTableView->show();
        }
        //сохранить таблицу
        saveWaferValuesTableView(slotNum, spTableView);
        //-----------------------------------------------------------------------------------------
    }
    else
        qDebug() << "slotNum is uncorrect when a Wafer Values Table Win creating";
}
void ConfigWin::slotLotTableWin()
{
    if(!m_dataBase.isOpen()){
        qDebug() << "Database is not open when a Lot Table Win creating; exiting"; return;}

    size_t slotNum{};
    QPushButton *pSlotButton = qobject_cast<QPushButton*>(sender());
    if(pSlotButton != nullptr)
        slotNum = (pSlotButton->objectName()).toInt();
    if(slotNum > 0)
    {
        QString LotDataTable = SystemDataBase::LotDataSqlTable;// + QString::number(slotNum,10);
        //-----------------------------------------------------------------------------------------
        //создать модель
        shared_ptr<QSqlTableModel> spSqlTableModel = make_shared<QSqlTableModel>();
        if(spSqlTableModel)
        {
            spSqlTableModel->setTable(LotDataTable);
            spSqlTableModel->select();
        }
        //сохранить модель
        saveLotDataSqlTableModel(slotNum, spSqlTableModel);
        //-----------------------------------------------------------------------------------------
        QString lotName = getLotName();
        //-----------------------------------------------------------------------------------------
        //создать таблицу и установить в нее модель
        shared_ptr<QTableView> spTableView = make_shared<QTableView>();
        if(spTableView && spSqlTableModel)
        {
            QSqlTableModel *pModel = spSqlTableModel.get();
            if(pModel != nullptr)
                spTableView->setModel(pModel);
            spTableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
            spTableView->resize(450, 450);
            QString lotDataTitle = lotName + ":  данные партии ";// + QString::number(slotNum,10);
            spTableView->setWindowTitle(lotDataTitle);
            int shift = m_tableViewPos + 2 * m_tableViewShift;
            spTableView->move(shift, shift);
            spTableView->show();
        }
        //сохранить таблицу
        saveLotDataTableView(slotNum, spTableView);
        //-----------------------------------------------------------------------------------------
    }
    else
        qDebug() << "slotNum is uncorrect when a Lot Data Table Win creating";
}
//-------------------------------------------------------------------------------------------------
