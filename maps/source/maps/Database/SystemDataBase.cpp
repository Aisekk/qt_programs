#include "SystemDataBase.h"

//=================================================================================================
//NAMESPACE:
//=================================================================================================
shared_ptr<Lot> DataBase::spLot{};
unique_ptr<QTableView> DataBase::upView{};
unique_ptr<ConfigWin> DataBase::upConfigWin{};
unique_ptr<SavingWin> DataBase::upSavingWin{};
//прерывает запись в базу данных; посредник между главным окном и окном Progress в системе БД
Breaker* DataBase::pBreaker{};
//размеры главного окна
int DataBase::MainWinHeight{};
int DataBase::MainWinWidth{};
//стандартные названия SQL-таблиц без указания слота пластины
QString DataBase::LotDataSqlTable = "LOT_DATA";
QString DataBase::WaferParamsSqlTable = "PARAMS_SLOT_";
QString DataBase::WaferValuesSqlTable = "VALUES_SLOT_";
//многопоточностьы
mutex DataBase::Mutex{};
size_t DataBase::sharedStepLot{};
//-------------------------------------------------------------------------------------------------
//создание соединения с базой данных
bool DataBase::createConnection(const QString& lotName)
{
    QSqlDatabase db{};
    if(!lotName.isEmpty())
    {
        db = QSqlDatabase::addDatabase("QSQLITE");
        qDebug() <<  "DB valid is: " << db.isValid();
        qDebug() <<  "Driver name: " << db.driverName();

        QString dbFileName = lotName + ".db";
        db.setDatabaseName(dbFileName);
        db.setUserName("user");
        db.setHostName("localhost");
        db.setPassword("password");
    }
    else { qDebug() << "Database has no name"; return false; }
    if(!db.open())
    {
        qDebug() << "Cannot open database:" << db.lastError();
        return false;
    }
    return true;
}
//закрытие соединения с базой данных
void DataBase::closeDataBase()
{
    QSqlDatabase db = QSqlDatabase::database();
    db.close();
    qDebug() << "database is closed";
}
//-------------------------------------------------------------------------------------------------
//создание базы данных партии
void DataBase::createLotDatabase(const QString& lotName)
{
    QTime time; time.start();
    if(!createConnection(lotName)) return;

    size_t waferCount = getWaferCount();
    if(waferCount == 0){ closeDataBase(); return; }

    createLotTable();
    //---------------------------------------------------------------------------------------------
    size_t countStepIncInParamFunc = 4; size_t countStepIncInValuesFunc = 4;
    size_t Limit = 1 + waferCount + waferCount*(countStepIncInParamFunc + countStepIncInValuesFunc);
    Progress progress(nullptr, Limit);
    progress.setModal(true);
    //progress.setStopButtonVisible();
    progress.setMaximumSize(300, 100);
    progress.setWindowTitle("Сохранение партии ...");
    progress.show();
    DataBase::sharedStepLot = 0;
    //---------------------------------------------------------------------------------
    qDebug() << "Before loop: " << time.elapsed() / 1000 << " sec" << endl;
    //---------------------------------------------------------------------------------
    for(size_t slotIndex = 0; slotIndex < waferCount; ++slotIndex)
    {
        auto spWafer = getWafer(slotIndex);
        size_t slotNum = spWafer->getSlotNum();
        insertInLotTable(slotIndex, slotNum);
        progress.setStep(++DataBase::sharedStepLot);
        qApp->processEvents();
    }
    //---------------------------------------------------------------------------------------------
    future<bool> fparams{};
    future<bool> fvalues{};
    try
    {
        fparams = async(launch::async, createParamsTable, waferCount);
        fvalues = async(launch::async, createValuesTable, waferCount);
        future_status sparams{};
        future_status svalues{};
        //ждем асинхронного выполнения задач
        sparams = fparams.wait_for(chrono::seconds(0));
        svalues = fvalues.wait_for(chrono::seconds(0));
        if(sparams == future_status::deferred || svalues == future_status::deferred)
        {
            throw std::runtime_error("Асинхронное выполнение потерпело неудачу. "
                                     "\nВыполнение будет продолжено в синхронном режиме. ");
        }

        while(true)
        {
            progress.setStep(DataBase::sharedStepLot);
            sparams = fparams.wait_for(chrono::seconds(0));
            svalues = fvalues.wait_for(chrono::seconds(0));
            if(sparams == future_status::ready && svalues == future_status::ready) break;
            qApp->processEvents();
        }
        bool paramsResult = false;
        bool valuesResult = false;
        paramsResult = fparams.get();
        valuesResult = fvalues.get();
        if(paramsResult && valuesResult == false)
            throw std::runtime_error("Данные не записаны или записаны не полностью");

        progress.setStep(Limit);
    }
    catch(const exception& e){
        QMessageBox::warning(nullptr, "Создание файла базы данных", QString(e.what()));
        progress.setStep(++DataBase::sharedStepLot);
        fparams.get();
        progress.setStep(Limit/2);
        qApp->processEvents();
        fvalues.get();
        progress.setStep(Limit);
        qApp->processEvents();
    }
    catch(...){
        QMessageBox::warning(nullptr, "Ошибка записи в базу данных", QString("unknown"));
    }
    //---------------------------------------------------------------------------------------------
    closeDataBase();
    qDebug() << "Lot record time: " << time.elapsed() / 1000 << " sec" << endl;
}
//-------------------------------------------------------------------------------------------------
//инкремент, вычисляющий процент выполнения партии в 2 потоках
void DataBase::StepLotIncrement()
{
    DataBase::Mutex.lock();
    DataBase::sharedStepLot++;
    DataBase::Mutex.unlock();
}
//параллельное создание, заполнение таблиц параметров, значений
bool DataBase::createParamsTable(size_t waferCount)
{
    bool tableCreated = false;
    for(size_t slotIndex = 0; slotIndex < waferCount; ++slotIndex)
    {
        auto spWafer = getWafer(slotIndex);
        tableCreated = createWaferParamsTable(spWafer);
        if(tableCreated == false) break;
    }
    return tableCreated;
}
bool DataBase::createValuesTable(size_t waferCount)
{
    bool tableCreated = false;
    for(size_t slotIndex = 0; slotIndex < waferCount; ++slotIndex)
    {
        auto spWafer = getWafer(slotIndex);
        tableCreated = createWaferValuesTable(spWafer);
        if(tableCreated == false) break;
    }
    return tableCreated;
}
//-------------------------------------------------------------------------------------------------
//создание таблиц одного слота в базе данных партии
void DataBase::createOneWaferTables(const QString& lotName, int slotSelected)
{
    if(!createConnection(lotName)) return;

    size_t waferCount = getWaferCount();
    if(waferCount == 0){ closeDataBase(); return; }

    createLotTable();
    for(size_t slotIdx = 0; slotIdx < waferCount; ++slotIdx)
    {
        auto spWafer = getWafer(slotIdx);
        size_t slotNum = spWafer->getSlotNum();
        insertInLotTable(slotIdx, slotNum);
        qApp->processEvents();
    }
    //---------------------------------------------------------------------------------------------
    size_t slotIndex = spLot->getSlotIndex(slotSelected);
    auto spWafer = getWafer(slotIndex);
    size_t slotNum = spWafer->getSlotNum();
    size_t countStepIncInParamFunc = 4; size_t countStepIncInValuesFunc = 4;
    size_t Limit = 1 + 1*(countStepIncInParamFunc + countStepIncInValuesFunc);
    //---------------------------------------------------------------------------------------------
    Progress progress(nullptr, Limit);
    progress.setModal(true);
    progress.setMaximumSize(300, 100);
    progress.setWindowTitle("Сохранение слота " + QString::number(slotNum) + " ...");
    progress.show();
    size_t sharedStepWafer = 0;
    //---------------------------------------------------------------------------------------------
    future<bool> fparams = async(launch::async, createWaferParamsTable, spWafer);
    future<bool> fvalues = async(launch::async, createWaferValuesTable, spWafer);

    future_status sparams{};
    future_status svalues{};

    while(true)
    {
        sharedStepWafer = DataBase::sharedStepLot;
        progress.setStep(sharedStepWafer);
        sparams = fparams.wait_for(chrono::milliseconds(500));
        svalues = fvalues.wait_for(chrono::milliseconds(500));
        if(sparams == future_status::ready && svalues == future_status::ready) break;
        qApp->processEvents();
    }

    fparams.get();
    fvalues.get();
    progress.setStep(Limit);
    //---------------------------------------------------------------------------------------------
    closeDataBase();
}
//-------------------------------------------------------------------------------------------------
//удаление таблицы
void DataBase::dropTable(QSqlQuery& query, const QString& tableName)
{
    QSqlDatabase db = QSqlDatabase::database();
    QStringList tables = db.tables();
    if(tables.contains(tableName))
    {
        QString dropCmd = "DROP TABLE " + tableName;
        if(!query.exec(dropCmd))
        {
            qDebug() << "Unable to drop a lot table";
            closeDataBase();
        }
    }
}
//-------------------------------------------------------------------------------------------------
//создание таблицы партии
void DataBase::createLotTable()
{
    QSqlQuery query;
    //---------------------------------------------------------------------------------------------
    //удаление таблицы, если она существует
    dropTable(query, LotDataSqlTable);
    //---------------------------------------------------------------------------------------------
    QString createCmd =
            "CREATE TABLE " +
            LotDataSqlTable + " ( "
                      "slotIndex      INTEGER PRIMARY KEY NOT NULL, "
                      "slotNum        INTEGER NOT NULL "
                      ");";
    if(!query.exec(createCmd))
    {
        qDebug() << "Unable to create a lot table";
        closeDataBase(); return;
    }
    //---------------------------------------------------------------------------------------------
}
//вставка данных в таблицу партии
void DataBase::insertInLotTable(size_t slotIndex, size_t slotNum)
{
    QSqlQuery query;
    QString attributes = " (slotIndex, slotNum)";
    QString values = "VALUES (:slotIndex, :slotNum)";
    //---------------------------------------------------------------------------------------------
    //добавляем данные в базу
    query.prepare("INSERT INTO " + LotDataSqlTable + attributes + values);
    query.bindValue(":slotIndex", slotIndex);
    query.bindValue(":slotNum", slotNum);

    if(!query.exec())
    {
        qDebug() << "Unable to make insert in Lot Table";
        closeDataBase(); return;
    }
}

//создание таблицы параметров и вставка данных в нее
bool DataBase::createWaferParamsTable(shared_ptr<Wafer> spWafer)
{
    size_t testElemCount = spWafer->getTestElemCount();
    size_t slotNum = spWafer->getSlotNum();
    //---------------------------------------------------------------------------------------------
    QSqlQuery query;
    QString WaferParamsTable = WaferParamsSqlTable + QString::number(slotNum,10);
    //---------------------------------------------------------------------------------------------
    //удаление таблицы, если она существует
    dropTable(query, WaferParamsTable);
    //---------------------------------------------------------------------------------------------
    QString createCmd =
            "CREATE TABLE " +
            WaferParamsTable + " ( "
                               "testIndex      INTEGER PRIMARY KEY NOT NULL, "
                               "dieCount       INTEGER NOT NULL, "
                               "testName       VARCHAR(25), "
                               "paramName      VARCHAR(25), "
                               "algName        VARCHAR(25), "
                               "low            FLOAT(3), "
                               "high           FLOAT(3), "
                               "unit           VARCHAR(10), "
                               "prefix         INTEGER NOT NULL"
                               ");";

    if(!query.exec(createCmd))
    {
        qDebug() << "Unable to create a wafer data table";
        closeDataBase(); return false;
    }
    //---------------------------------------------------------------------------------------------
    StepLotIncrement();//1
    //---------------------------------------------------------------------------------------------
    shared_ptr<TestElem> spTestElem{};
    //---------------------------------------------------------------------------------------------
    //добавляем данные в базу - пакетная загрузка
    QVariantList listTestIndex;
    QVariantList listDieCount;
    QVariantList listTestName;
    QVariantList listParamName;
    QVariantList listAlgName;
    QVariantList listLow;
    QVariantList listHigh;
    QVariantList listUnit;
    QVariantList listPrefix;
    QString toInsert = "INSERT INTO " + WaferParamsTable +
            " (testIndex, dieCount, testName, paramName, algName, low, high, unit, prefix)"
            " VALUES(?,?,?,?,?,?,?,?,?)";
    query.prepare(toInsert);

    for(size_t testIndex = 0; testIndex < testElemCount; ++testIndex)
    {
        spTestElem = spWafer->getTestElem(testIndex);
        listTestIndex << testIndex;
        listDieCount << spTestElem->getDieCount();
        listTestName << spTestElem->getTestName();
        listParamName << spTestElem->getParamName();
        listAlgName << spTestElem->getAlgName();
        listLow << spTestElem->getCriterionDn();
        listHigh << spTestElem->getCriterionUp();
        listUnit << spTestElem->getUnitName();
        listPrefix << static_cast<int>(spTestElem->getTestValuesPrefix());
        //-----------------------------------------------------------------------------------------
        //StepLotIncrement();//2
        //-----------------------------------------------------------------------------------------
    }
    //-----------------------------------------------------------------------------------------
    StepLotIncrement();//2
    //-----------------------------------------------------------------------------------------
    query.addBindValue(listTestIndex);
    query.addBindValue(listDieCount);
    query.addBindValue(listTestName);
    query.addBindValue(listParamName);
    query.addBindValue(listAlgName);
    query.addBindValue(listLow);
    query.addBindValue(listHigh);
    query.addBindValue(listUnit);
    query.addBindValue(listPrefix);
    //---------------------------------------------------------------------------------------------
    StepLotIncrement();//3
    //---------------------------------------------------------------------------------------------
    bool tableCreated = false;
    tableCreated = query.execBatch();
    if(!tableCreated)
    {
        qDebug() << "Unable to make insert in Wafer Table";
        closeDataBase(); return false;
    }
    //---------------------------------------------------------------------------------------------
    StepLotIncrement();//4
    //---------------------------------------------------------------------------------------------
    return tableCreated;
}
//создание таблицы значений и вставка данных в нее
bool DataBase::createWaferValuesTable(shared_ptr<Wafer> spWafer)
{  
    size_t slotNum{};
    if(spWafer == nullptr) return false;
    //---------------------------------------------------------------------------------------------
    slotNum = spWafer->getSlotNum();
    QString testElemNames_DDL_Values{};
    QString testElemNames_DDL_MaskStates{};
    QString testElemNames_DDL{};
    QString testElemNamesMasks_toInsert{};
    QString what{};
    size_t testElemCount = spWafer->getTestElemCount();
    for(size_t testIndex = 0; testIndex < testElemCount; ++testIndex)
    {
        auto spTestElem = spWafer->getTestElem(testIndex);
        if(spTestElem)
        {
            QString testName = spTestElem->getTestName();
            QString paramName = spTestElem->getParamName();
            QString dbTestName = testName + "_" + paramName + "_" + QString::number(testIndex);
            QString testElemMask = dbTestName + "m";
            //для вставки в таблицу
            testElemNamesMasks_toInsert += (dbTestName + ", " + testElemMask + ", ");
            what += "?,?,";
            //для создания таблиц
            testElemNames_DDL_Values = (dbTestName + "  FLOAT(3), ");
            testElemNames_DDL_MaskStates = (testElemMask + "  INTEGER, ");
            testElemNames_DDL +=
                    (testElemNames_DDL_Values + testElemNames_DDL_MaskStates);
        }
        else{ closeDataBase(); return false; }
    }
    //---------------------------------------------------------------------------------------------
    StepLotIncrement();//1
    //---------------------------------------------------------------------------------------------
    //СОЗДАНИЕ ТАБЛИЦ
    QSqlQuery query;
    QString WaferValuesTable = WaferValuesSqlTable + QString::number(slotNum,10);
    //---------------------------------------------------------------------------------------------
    //удаление таблицы, если она существует
    dropTable(query, WaferValuesTable);
    //---------------------------------------------------------------------------------------------
    QString createValuesTableCmd =
            "CREATE TABLE " +
            WaferValuesTable +
            " ( "
            "dieNum     INTEGER PRIMARY KEY NOT NULL, "
            "X          INTEGER NOT NULL, "
            "Y          INTEGER NOT NULL, "
            + testElemNames_DDL +
            "dummy      INTEGER"
            ");";
    if(!query.exec(createValuesTableCmd))
    {
        qDebug() << "Unable to create a Test Elem Values Table";
        closeDataBase(); return false;
    }
    //---------------------------------------------------------------------------------------------
    //ВСТАВКА ДАННЫХ В ТАБЛИЦЫ - вариант 3
    auto spTestElem = spWafer->getTestElem(int(0));
    if(spTestElem == nullptr) return false;
    //---------------------------------------------------------------------------------------------
    size_t dieCount = spTestElem->getDieCount();
    size_t testCount = spWafer->getTestElemCount();
    testCount += (dieCount + 3);
    //---------------------------------------------------------------------------------------------
    QVariantList listDieNums;
    QVariantList listDieX;
    QVariantList listDieY;
    QVariantList listDummies;
    QString toInsert = "INSERT INTO " + WaferValuesTable +
            " (dieNum, X, Y, " + testElemNamesMasks_toInsert
            + " dummy) VALUES (?,?,?," + what + "?) ";
    query.prepare(toInsert);
    int dummy = 0;
    size_t dieNum = 0;

    auto vec_spDies = spTestElem->getDies();
    if(!vec_spDies.isEmpty())
        for(shared_ptr<Die>& spDie : vec_spDies)
        {
            listDieNums << ++dieNum;
            listDieX << spDie->getX();
            listDieY << spDie->getY();
            listDummies << ++dummy;
        }
    query.addBindValue(listDieNums);
    query.addBindValue(listDieX);
    query.addBindValue(listDieY);
    //---------------------------------------------------------------------------------------------
    StepLotIncrement();//2
    //---------------------------------------------------------------------------------------------
    QVector<QVariantList> vec_of_listDieValuesMasks;
    for(size_t testIndex = 0; testIndex < testElemCount; ++testIndex)
    {
        QVariantList listDieValues;
        QVariantList listDieMaskStates;
        auto spTestElem = spWafer->getTestElem(testIndex);
        auto vec_spDies = spTestElem->getDies();
        if(!vec_spDies.isEmpty())
            for(auto& spDie : vec_spDies)
            {
                listDieValues << spDie->getValue();
                listDieMaskStates << static_cast<int>(spDie->getMaskState());
            }

        vec_of_listDieValuesMasks.push_back(listDieValues);
        query.addBindValue(vec_of_listDieValuesMasks.last());

        vec_of_listDieValuesMasks.push_back(listDieMaskStates);
        query.addBindValue(vec_of_listDieValuesMasks.last());
        //-----------------------------------------------------------------------------------------
        //StepLotIncrement();//3
        //-----------------------------------------------------------------------------------------
    }
    //---------------------------------------------------------------------------------------------
    query.addBindValue(listDummies);
    //-----------------------------------------------------------------------------------------
    StepLotIncrement();//3
    //-----------------------------------------------------------------------------------------
    bool tableCreated = false;
    tableCreated = query.execBatch();
    if(!tableCreated){
        qDebug() << "Unable to make insert values in WaferValuesTable";
        closeDataBase(); return false;
    }
    //---------------------------------------------------------------------------------------------
    StepLotIncrement();//4
    //---------------------------------------------------------------------------------------------
    return tableCreated;
}
//-------------------------------------------------------------------------------------------------
QString DataBase::getTestElemFullName(shared_ptr<TestElem> spTestElem)
{
    QString testElemFullName{};
    if(spTestElem)
    {
        QString testName = spTestElem->getTestName();
        QString paramName = spTestElem->getParamName();
        testElemFullName = testName + "_" + paramName;
    }
    return testElemFullName;
    //---------------------------------------------------------------------------------------------
}
//---------------------------------------------------------------------------------------------
//создать окно кнопок-слотов для сохранения слота или всех слотов в базе
void DataBase::createSavingWin(shared_ptr<Lot> spLot)
{
    QString lotName = spLot->getLotName();
    if(!createConnection(lotName)) return;
    QSqlDatabase db = QSqlDatabase::database();
    //---------------------------------------------------------------------------------------------
    size_t slotIndex = 0;
    QMap<size_t,size_t> mapSlotIndexNums;
    QVector<size_t> vecSlotNums = spLot->getSlotNums();
    for(size_t& slotNum : vecSlotNums)
    {
        mapSlotIndexNums.insert(slotIndex, slotNum);
        ++slotIndex;
    }
    //---------------------------------------------------------------------------------------------
    //создать окно кнопок-слотов
    upSavingWin.reset(new SavingWin(nullptr, mapSlotIndexNums));
    SavingWin *pSavingWin{};
    if(upSavingWin)
        pSavingWin = upSavingWin.get();
    if(pSavingWin != nullptr)
    {
        pSavingWin->setLotName(lotName);
        pSavingWin->setWindowTitle("Сохранить " + lotName);
        pSavingWin->setDataBase(db);
        pSavingWin->show();
    }
    else db.close();
    //---------------------------------------------------------------------------------------------
}
//создание окна кнопок-слотов с данными из базы
void DataBase::createConfigWin(QString &lotName)
{
    if(!createConnection(lotName)) return;

    QSqlDatabase db = QSqlDatabase::database();
    QStringList tables = db.tables();
    QString lotTableName{};
    //---------------------------------------------------------------------------------------------
    if(!tables.isEmpty())
        lotTableName = LotDataSqlTable;
    //---------------------------------------------------------------------------------------------
    QSqlQuery query;
    if(!db.isOpen()){qDebug() << "Database is not open; exiting"; return;}
    if(!query.exec("SELECT slotIndex, slotNum FROM " + lotTableName + ";"))
    {
        qDebug() << "Unable to execute SELECT slotIndex, slotNum; exiting";
        closeDataBase(); return;
    }
    //считываем данные из таблицы партии
    QSqlRecord rec = query.record();
    size_t slotIndex{};
    size_t slotNum{};
    QMap<size_t,size_t> mapSlotIndexesNums;
    while(query.next())
    {
        slotIndex = query.value(rec.indexOf("slotIndex")).toInt();
        slotNum = query.value(rec.indexOf("slotNum")).toInt();
        mapSlotIndexesNums.insert(slotIndex, slotNum);
    }
    //---------------------------------------------------------------------------------------------
    //создать окно базы данных (окно кнопок-слотов на основе данных из файла БД)
    upConfigWin.reset(new ConfigWin(nullptr, mapSlotIndexesNums));
    ConfigWin *pConfigWin{};
    if(upConfigWin)
        pConfigWin = upConfigWin.get();
    if(pConfigWin != nullptr)
    {
        pConfigWin->setLotName(lotName);
        pConfigWin->setWindowTitle(lotName);
        pConfigWin->setDatabase(db);
        pConfigWin->show();
    }
    else db.close();
    //---------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------
//импорт базы данных:
//выборка данных из базы для построения модели и дерева
void DataBase::queryLotData(shared_ptr<Lot>& spLot)
{
    QString lotName = spLot->getLotName();
    if(!createConnection(lotName)) return;
    QSqlDatabase db = QSqlDatabase::database();
    if(!db.isOpen()){qDebug() << "Database " + lotName + " is not open; exiting"; return;}
    //---------------------------------------------------------------------------------------------
    //1 - запросы из общей таблицы (с индексами и номерами слотов)
    QSqlQuery query("SELECT * FROM " + LotDataSqlTable);
    if(!query.exec())
    {
        qDebug() << "Unable to select from lot data table";
        closeDataBase(); return;
    }
    //считываем данные из общей таблицы
    QSqlRecord recLot = query.record();
    while(query.next())
    {
        size_t slotIndex = query.value(recLot.indexOf("slotIndex")).toInt();
        size_t slotNum = query.value(recLot.indexOf("slotNum")).toInt();
        shared_ptr<Wafer> spWafer = make_shared<Wafer>(slotIndex, slotNum);
        //2 - запросы из таблицы параметров
        queryParamsTable(spWafer, slotNum, slotIndex);
        spLot->addWafer(spWafer, slotNum, slotIndex);
    }
    //---------------------------------------------------------------------------------------------
}
void DataBase::queryParamsTable(shared_ptr<Wafer>& spWafer,
                                size_t slotNum, size_t slotIndex)
{
    QString selectParams = "SELECT * FROM " + WaferParamsSqlTable + QString::number(slotNum,10);
    QSqlQuery query;
    query.prepare(selectParams);
    if(!query.exec())
    {
        qDebug() << "Unable to select from wafer parameters table";
        closeDataBase(); return;
    }
    //считываем данные из таблицы параметров
    QSqlRecord recParams = query.record();
    while(query.next())
    {
        size_t testIndex = query.value(recParams.indexOf("testIndex")).toInt();
        //size_t dieCount = query.value(recParams.indexOf("dieCount")).toInt();
        QString testName = query.value(recParams.indexOf("testName")).toString();
        QString paramName = query.value(recParams.indexOf("paramName")).toString();
        QString algName = query.value(recParams.indexOf("algName")).toString();
        double low = query.value(recParams.indexOf("low")).toDouble();
        double high = query.value(recParams.indexOf("high")).toDouble();
        QString unit = query.value(recParams.indexOf("unit")).toString();
        int prefix = query.value(recParams.indexOf("prefix")).toInt();
        ValuePrefix valuePrefix = static_cast<ValuePrefix>(prefix);

        shared_ptr<TestElem> spTestElem =
                make_shared<TestElem>(testIndex, testName, paramName, algName, valuePrefix);
        spTestElem->setSlotIndex(slotIndex);
        spTestElem->setCriterionDn(low);
        spTestElem->setCriterionUp(high);
        spTestElem->setUnitName(unit);
        //3 - запросы из таблицы значений
        QString dbTestName = testName + "_" + paramName + "_" + QString::number(testIndex);
        queryValuesTable(spTestElem, dbTestName, slotNum, testIndex, valuePrefix);

        spWafer->addTestElem(spTestElem, testIndex);
    }
}
void DataBase::queryValuesTable(shared_ptr<TestElem>& spTestElem, const QString& dbTestName,
                                size_t slotNum, size_t testIndex, ValuePrefix valuePrefix)
{
    QString dbTestNameMask = dbTestName + "m";
    QString selectValues = "SELECT dieNum, X, Y, " + dbTestName + ", " +
            dbTestNameMask + " FROM " +
            WaferValuesSqlTable + QString::number(slotNum,10);

    QSqlQuery query;
    query.prepare(selectValues);
    if(!query.exec())
    {
        qDebug() << "Unable to select from wafer values table";
        closeDataBase(); return;
    }
    size_t slotIndex = spTestElem->getSlotIndex();
    //считываем данные из таблицы значений
    QSqlRecord recValues = query.record();
    while(query.next())
    {
        int X = query.value(recValues.indexOf("X")).toInt();
        int Y = query.value(recValues.indexOf("Y")).toInt();
        double Value = query.value(recValues.indexOf(dbTestName)).toDouble();
        int state = query.value(recValues.indexOf(dbTestNameMask)).toInt();
        Mask maskState = static_cast<Mask>(state);
        bool buttonState = static_cast<bool>(state);
        MaskButtonState maskButtonState = static_cast<MaskButtonState>(buttonState);

        shared_ptr<Die> spDie =
                make_shared<Die>(X, Y, Value, testIndex, slotIndex, maskState, maskButtonState);

        switch (valuePrefix)
        {
        case ValuePrefix::norm: break;
        case ValuePrefix::milli:
        { spDie->setNormalValue(1.0e-3); spDie->changeValueTo(ValuePrefix::milli); break; }
        case ValuePrefix::micro:
        { spDie->setNormalValue(1.0e-6); spDie->changeValueTo(ValuePrefix::micro); break; }
        case ValuePrefix::nano:
        { spDie->setNormalValue(1.0e-9); spDie->changeValueTo(ValuePrefix::nano); break; }
        case ValuePrefix::pico:
        { spDie->setNormalValue(1.0e-12); spDie->changeValueTo(ValuePrefix::pico); break; }
        case ValuePrefix::kilo:
        { spDie->setNormalValue(1.0e+3); spDie->changeValueTo(ValuePrefix::kilo); break; }
        case ValuePrefix::mega:
        { spDie->setNormalValue(1.0e+6); spDie->changeValueTo(ValuePrefix::mega); break; }
        case ValuePrefix::giga:
        { spDie->setNormalValue(1.0e+9); spDie->changeValueTo(ValuePrefix::giga); break; }
        case ValuePrefix::tera:
        { spDie->setNormalValue(1.0e+12); spDie->changeValueTo(ValuePrefix::tera); break; }
        default: break;
        }
        spTestElem->addDie(spDie);
    }
}
//-------------------------------------------------------------------------------------------------
//методы доступа к данным партии
size_t DataBase::getWaferCount()
{
    if(spLot) return spLot->getWaferCount();
    else return 0;
}
QString DataBase::getLotName()
{
    QString lotName{};
    if(spLot) lotName = spLot->getLotName();
    return lotName;
}
shared_ptr<Wafer> DataBase::getWafer(size_t slotIndex)
{
    if(spLot) return spLot->getWafer(slotIndex);
    else return nullptr;
}
//=================================================================================================
