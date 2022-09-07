#include "SystemDataBase.h"

//=================================================================================================
//NAMESPACE:
//=================================================================================================
shared_ptr<Lot> SystemDataBase::spLot{};
unique_ptr<QTableView> SystemDataBase::upView{};
unique_ptr<ConfigWin> SystemDataBase::upConfigWin{};
unique_ptr<SavingWin> SystemDataBase::upSavingWin{};
//прерывает запись в базу данных; посредник между главным окном и окном Progress в системе БД
Breaker* SystemDataBase::pBreaker{};
//размеры главного окна
int SystemDataBase::MainWinHeight{};
int SystemDataBase::MainWinWidth{};
//стандартные названия SQL-таблиц без указания слота пластины
QString SystemDataBase::LotDataSqlTable = "LOT_DATA";
QString SystemDataBase::WaferParamsSqlTable = "PARAMS_SLOT_";
QString SystemDataBase::WaferValuesSqlTable = "VALUES_SLOT_";
//-------------------------------------------------------------------------------------------------
//создание соединения с базой данных
bool SystemDataBase::createConnection(const QString& lotName)
{
    QSqlDatabase db{};
    if(!lotName.isEmpty())
    {
        db = QSqlDatabase::addDatabase("QSQLITE");
        //db = QSqlDatabase::addDatabase("QMYSQL");
        qDebug() <<  "DB valid is: " << db.isValid();
        qDebug() <<  "Driver name: " << db.driverName();

        QString dbFileName = lotName + ".db";
        db.setDatabaseName(dbFileName);
        db.setUserName("user");
        db.setHostName("localhost");
        db.setPassword("password");
    }
    else {qDebug() << "Database has no name"; return false;}
    if(!db.open())
    {
        qDebug() << "Cannot open database:" << db.lastError();
        return false;
    }
    return true;
}
//закрытие соединения с базой данных
void SystemDataBase::closeDataBase()
{
    QSqlDatabase db = QSqlDatabase::database();
    db.close();
    qDebug() << "database is closed";
    //    QString connectionName = db.connectionName();
    //    QSqlDatabase::removeDatabase(connectionName);
}
//-------------------------------------------------------------------------------------------------
//создание базы данных партии
void SystemDataBase::createLotDatabase(const QString& lotName)
{
    QTime time;
    time.start();
    if(!createConnection(lotName)) return;

    size_t waferCount = getWaferCount();
    if(waferCount == 0){closeDataBase(); return;}

    createLotTable();
    //---------------------------------------------------------------------------------
    Progress progress(pBreaker, 2 * waferCount);
    progress.setModal(false);
    progress.setMaximumSize(300, 100);
    progress.setWindowTitle("Сохранение партии ...");
    QObject::connect(&progress, Progress::closed, pBreaker, Breaker::slotBreakCalc);
    progress.show();
    //---------------------------------------------------------------------------------
    size_t stepLot = 0;
    //---------------------------------------------------------------------------------
    qDebug() << "Before loop: " << time.elapsed() / 1000 << " sec" << endl;
    //---------------------------------------------------------------------------------
    for(size_t slotIndex = 0; slotIndex < waferCount; ++slotIndex)
    {
        QTime time;
        time.start();
        qApp->processEvents();
        auto spWafer = getWafer(slotIndex);
        size_t slotNum = spWafer->getSlotNum();
        insertInLotTable(slotIndex, slotNum);

        if(pBreaker != nullptr)
            if(pBreaker->isBreakCalc()){closeDataBase(); break;}

        createWaferParamsTable(spWafer);
        progress.setStep(++stepLot);

        if(pBreaker != nullptr)
            if(pBreaker->isBreakCalc()){closeDataBase(); break;}

        createWaferValuesTable(spWafer);
        progress.setStep(++stepLot);

        qDebug() << "Wafer " + QString::number(slotNum) << " record time: "
                 << time.elapsed() / 1000 << " sec" << endl;
    }
    //---------------------------------------------------------------------------------
    closeDataBase();
    qDebug() << "Lot record time: " << time.elapsed() / 1000 << " sec" << endl;
}
//создание таблиц одного слота в базе данных партии
void SystemDataBase::createOneWaferTables(const QString& lotName, const int slotSelected)
{
    if(!createConnection(lotName)) return;

    size_t waferCount = getWaferCount();
    if(waferCount == 0){closeDataBase(); return;}

    createLotTable();
    for(size_t slotIdx = 0; slotIdx < waferCount; ++slotIdx)
    {
        qApp->processEvents();
        auto spWafer = getWafer(slotIdx);
        size_t slotNum = spWafer->getSlotNum();
        insertInLotTable(slotIdx, slotNum);
    }
    //---------------------------------------------------------------------------------------------
    size_t slotIndex = spLot->getSlotIndex(slotSelected);
    auto spWafer = getWafer(slotIndex);

    if(pBreaker != nullptr)
        if(pBreaker->isBreakCalc()){closeDataBase(); return;}
    createWaferParamsTable(spWafer);

    if(pBreaker != nullptr)
        if(pBreaker->isBreakCalc()){closeDataBase(); return;}
    createWaferValuesTable(spWafer);
    //---------------------------------------------------------------------------------------------
    closeDataBase();
}
//обновление базы данных партии
void SystemDataBase::updateLotDataBase(const QString& lotName)
{
    if(!createConnection(lotName)) return;

    size_t waferCount = getWaferCount();
    if(waferCount == 0){closeDataBase(); return;}
    //---------------------------------------------------------------------------------
    Progress progress(pBreaker, 2 * waferCount);
    progress.setModal(false);
    progress.setMaximumSize(300, 100);
    progress.setWindowTitle("Обновление партии ...");
    QObject::connect(&progress, Progress::closed, pBreaker, Breaker::slotBreakCalc);
    progress.show();
    //---------------------------------------------------------------------------------
    size_t stepLot = 0;
    //---------------------------------------------------------------------------------
    for(size_t slotIndex = 0; slotIndex < waferCount; ++slotIndex)
    {
        qApp->processEvents();
        auto spWafer = getWafer(slotIndex);
        size_t slotNum = spWafer->getSlotNum();
        updateLotTable(slotIndex, slotNum);

        if(pBreaker->isBreakCalc()){closeDataBase(); break;}

        updateWaferParamsTable(spWafer);
        progress.setStep(++stepLot);

        if(pBreaker->isBreakCalc()){closeDataBase(); break;}

        //updateWaferValuesTable(spWafer);
        progress.setStep(++stepLot);
    }
    closeDataBase();
}
//-------------------------------------------------------------------------------------------------
//удаление таблицы
void SystemDataBase::dropTable(QSqlQuery& query, const QString& tableName)
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
void SystemDataBase::createLotTable()
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
void SystemDataBase::insertInLotTable(const size_t slotIndex, const size_t slotNum)
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
void SystemDataBase::createWaferParamsTable(const shared_ptr<Wafer>& spWafer)
{
    size_t testElemCount = spWafer->getTestElemCount();
    //---------------------------------------------------------------------------------============
    Progress progress(pBreaker, testElemCount + 2);
    progress.setModal(false);
    progress.setStopButtonVisible();
    progress.setMaximumSize(300, 100);
    size_t slotNum = spWafer->getSlotNum();
    progress.setWindowTitle("слот " + QString::number(slotNum) + " (параметры) ...");
    progress.move(MainWinWidth/2 - progress.width()*1.45,
                  MainWinHeight/2 + progress.height()*1.9);
    QObject::connect(&progress, Progress::closed, pBreaker, Breaker::slotBreakCalc);
    progress.show();
    //---------------------------------------------------------------------------------------------
    size_t stepTest = 0;
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
        closeDataBase(); return;
    }
    //---------------------------------------------------------------------------------------------
    progress.setStep(++stepTest);//1
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
        qApp->processEvents();
        if(pBreaker->isBreakCalc()){closeDataBase(); break;}
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

        progress.setStep(++stepTest);
    }
    query.addBindValue(listTestIndex);
    query.addBindValue(listDieCount);
    query.addBindValue(listTestName);
    query.addBindValue(listParamName);
    query.addBindValue(listAlgName);
    query.addBindValue(listLow);
    query.addBindValue(listHigh);
    query.addBindValue(listUnit);
    query.addBindValue(listPrefix);

    if(!query.execBatch())
    {
        qDebug() << "Unable to make insert in Wafer Table";
        closeDataBase(); return;
    }
    progress.setStep(++stepTest);
}
//создание таблицы значений и вставка данных в нее
void SystemDataBase::createWaferValuesTable(const shared_ptr<Wafer>& spWafer)
{  
    size_t slotNum{};
    if(spWafer == nullptr) return;
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
        else{closeDataBase(); return;}
    }
    //---------------------------------------------------------------------------------------------
    //СОЗДАНИЕ ТАБЛИЦ
    QSqlQuery query;
    QString WaferValuesTable = WaferValuesSqlTable + QString::number(slotNum,10);
    //---------------------------------------------------------------------------------------------
    //удаление таблицы, если она существует
    dropTable(query, WaferValuesTable);
    //---------------------------------------------------------------------------------------------
    //1
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
        closeDataBase(); return;
    }
    //---------------------------------------------------------------------------------------------
    //ВСТАВКА ДАННЫХ В ТАБЛИЦЫ - вариант 3
    auto spTestElem = spWafer->getTestElem(int(0));
    if(spTestElem == nullptr) return;
    //---------------------------------------------------------------------------------------------
    size_t dieCount = spTestElem->getDieCount();
    size_t testCount = spWafer->getTestElemCount();
    testCount += (dieCount + 3);
    //---------------------------------------------------------------------------------------------
    Progress progress(pBreaker, testCount);
    progress.setModal(false);
    progress.setStopButtonVisible();
    progress.setMaximumSize(300, 100);
    progress.setWindowTitle("слот " + QString::number(slotNum) + " (значения) ...");
    QObject::connect(&progress, Progress::closed, pBreaker, Breaker::slotBreakCalc);
    progress.move(MainWinWidth/2 - progress.width()*1.45,
                  MainWinHeight/2 + progress.height()*1.9);
    progress.show();
    //---------------------------------------------------------------------------------------------
    size_t stepTest = 0;
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
            qApp->processEvents();
            if(pBreaker->isBreakCalc()){closeDataBase(); break;}

            listDieNums << ++dieNum;
            listDieX << spDie->getX();
            listDieY << spDie->getY();
            listDummies << ++dummy;
            progress.setStep(++stepTest);
        }
    query.addBindValue(listDieNums);
    query.addBindValue(listDieX);
    query.addBindValue(listDieY);
    //---------------------------------------------------------------------------------------------
    progress.setStep(++stepTest);//1
    //---------------------------------------------------------------------------------------------
    QVector<QVariantList> vec_of_listDieValuesMasks;
    for(size_t testIndex = 0; testIndex < testElemCount; ++testIndex)
    {
        qApp->processEvents();
        if(pBreaker->isBreakCalc()){closeDataBase(); break;}

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

        progress.setStep(++stepTest);
    }
    //---------------------------------------------------------------------------------------------
    query.addBindValue(listDummies);
    progress.setStep(++stepTest);//2

    bool ok = query.execBatch();
    if(!ok){
        qDebug() << "Unable to make insert values in WaferValuesTable";
        closeDataBase(); return;
    }
    progress.setStep(++stepTest);//3
    //---------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------
//обновление таблицы партии
void SystemDataBase::updateLotTable(const int slotIndex, const int slotNum)
{
    QSqlQuery query;
    //---------------------------------------------------------------------------------------------
    //обновить таблицу, если она существует
    QSqlDatabase db = QSqlDatabase::database();
    QStringList tables = db.tables();
    if(tables.contains(LotDataSqlTable))
    {
        QString updateCmd = "UPDATE " + LotDataSqlTable + " SET "
                                              "slotIndex = " + QString::number(slotIndex) +
                                              ", slotNum = " + QString::number(slotNum) +
                " WHERE slotIndex = " + QString::number(slotIndex);
        if(!query.exec(updateCmd))
        {
            qDebug() << "Unable to update a lot table";
            closeDataBase(); return;
        }
    }
    //---------------------------------------------------------------------------------------------
}
//обновление таблицы параметров
void SystemDataBase::updateWaferParamsTable(const shared_ptr<Wafer>& spWafer)
{
    size_t testElemCount = spWafer->getTestElemCount();
    //---------------------------------------------------------------------------------============
    Progress progress(pBreaker, testElemCount + 1);
    progress.setModal(false);
    progress.setStopButtonVisible();
    progress.setMaximumSize(300, 100);
    size_t slotNum = spWafer->getSlotNum();
    progress.setWindowTitle("слот " + QString::number(slotNum) + " (параметры) ...");
    progress.move(MainWinWidth/2 - progress.width()*1.45,
                  MainWinHeight/2 + progress.height()*1.9);
    QObject::connect(&progress, Progress::closed, pBreaker, Breaker::slotBreakCalc);
    progress.show();
    //---------------------------------------------------------------------------------------------
    size_t stepTest = 0;
    //---------------------------------------------------------------------------------------------
    QSqlQuery query;
    QString WaferParamsTable = WaferParamsSqlTable + QString::number(slotNum,10);
    //---------------------------------------------------------------------------------------------
    //обновить таблицу, если она существует
    QSqlDatabase db = QSqlDatabase::database();
    QStringList tables = db.tables();
    if(!tables.contains(WaferParamsTable)) return;
    //---------------------------------------------------------------------------------------------
    progress.setStep(++stepTest);//1
    //---------------------------------------------------------------------------------------------
    shared_ptr<TestElem> spTestElem{};
    //---------------------------------------------------------------------------------------------
//    QString attributes = "("
//                         "testIndex, dieCount, testName, paramName, "
//                         "algName, low, high, unit, prefix"
//                         ")";
//    QString values = "VALUES ("
//                     ":testIndex, :dieCount, :testName, :paramName, "
//                     ":algName, :low, :high, :unit, :prefix"
//                     ")";
    //---------------------------------------------------------------------------------------------
    for(size_t testIndex = 0; testIndex < testElemCount; ++testIndex)
    {
        qApp->processEvents();
        if(pBreaker->isBreakCalc()){closeDataBase(); break;}
        spTestElem = spWafer->getTestElem(testIndex);

        size_t dieCount = spTestElem->getDieCount();
//        QString testName = spTestElem->getTestName();
//        QString paramName = spTestElem->getParamName();
//        QString algName = spTestElem->getAlgName();
        QString low = QString::number(spTestElem->getCriterionDn());
        QString high = QString::number(spTestElem->getCriterionUp());
//        QString unitName = spTestElem->getUnitName();
        int prefix = static_cast<int>(spTestElem->getTestValuesPrefix());

        QString updateCmd = "UPDATE " + WaferParamsTable + " SET " +
                //"testIndex = " + QString::number(testIndex)
                + " dieCount = " + QString::number(dieCount)
                //+ ", testName = " + testName
                //+ ", paramName = " + paramName
                //+ ", algName = " + algName
                + ", low = " + low
                + ", high = " + high
                //+ ", unit = " + unitName
                + ", prefix = " + QString::number(prefix)
                + " WHERE testIndex = " + QString::number(testIndex);

//        query.prepare("UPDATE " + WaferParamsTable + " " + attributes + " " + values +
//                      " WHERE testIndex = " + QString::number(testIndex) );
//        query.bindValue(":testIndex", testIndex);
//        query.bindValue(":dieCount", spTestElem->getDieCount());
//        query.bindValue(":testName", spTestElem->getTestName());
//        query.bindValue(":paramName", spTestElem->getParamName());
//        query.bindValue(":algName", spTestElem->getAlgName());
//        query.bindValue(":low", spTestElem->getCriterionDn());
//        query.bindValue(":high", spTestElem->getCriterionUp());
//        query.bindValue(":unit", spTestElem->getUnitName());
//        int prefix = static_cast<int>(spTestElem->getTestValuesPrefix());
//        query.bindValue(":prefix", prefix);

        if(!query.exec(updateCmd))
        {
            qDebug() << "Unable to update Wafer Params Table";
            closeDataBase(); break;
        }
        progress.setStep(++stepTest);
    }
    //---------------------------------------------------------------------------------------------
    //progress.setStep(++stepTest);
}
//обновление таблицы значений
void SystemDataBase::updateWaferValuesTable(const shared_ptr<Wafer>& spWafer)
{
    size_t slotNum{};
    if(spWafer == nullptr) return;
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
        else{closeDataBase(); return;}
    }
    //---------------------------------------------------------------------------------------------
    //СОЗДАНИЕ ТАБЛИЦ
    QSqlQuery query;
    QString WaferValuesTable = WaferValuesSqlTable + QString::number(slotNum,10);
    //---------------------------------------------------------------------------------------------
    //удаление таблицы, если она существует
    dropTable(query, WaferValuesTable);
    //---------------------------------------------------------------------------------------------
    //1
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
        closeDataBase(); return;
    }
    //---------------------------------------------------------------------------------------------
    //ВСТАВКА ДАННЫХ В ТАБЛИЦЫ - вариант 3
    auto spTestElem = spWafer->getTestElem(int(0));
    if(spTestElem == nullptr) return;
    //---------------------------------------------------------------------------------------------
    size_t dieCount = spTestElem->getDieCount();
    size_t testCount = spWafer->getTestElemCount();
    testCount += (dieCount + 3);
    //---------------------------------------------------------------------------------------------
    Progress progress(pBreaker, testCount);
    progress.setModal(false);
    progress.setStopButtonVisible();
    progress.setMaximumSize(300, 100);
    progress.setWindowTitle("слот " + QString::number(slotNum) + " (значения) ...");
    QObject::connect(&progress, Progress::closed, pBreaker, Breaker::slotBreakCalc);
    progress.move(MainWinWidth/2 - progress.width()*1.45,
                  MainWinHeight/2 + progress.height()*1.9);
    progress.show();
    //---------------------------------------------------------------------------------------------
    size_t stepTest = 0;
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
            qApp->processEvents();
            if(pBreaker->isBreakCalc()){closeDataBase(); break;}

            listDieNums << ++dieNum;
            listDieX << spDie->getX();
            listDieY << spDie->getY();
            listDummies << ++dummy;
            progress.setStep(++stepTest);
        }
    query.addBindValue(listDieNums);
    query.addBindValue(listDieX);
    query.addBindValue(listDieY);
    //---------------------------------------------------------------------------------------------
    progress.setStep(++stepTest);//1
    //---------------------------------------------------------------------------------------------
    QVector<QVariantList> vec_of_listDieValuesMasks;
    for(size_t testIndex = 0; testIndex < testElemCount; ++testIndex)
    {
        qApp->processEvents();
        if(pBreaker->isBreakCalc()){closeDataBase(); break;}

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

        progress.setStep(++stepTest);
    }
    //---------------------------------------------------------------------------------------------
    query.addBindValue(listDummies);
    progress.setStep(++stepTest);//2

    bool ok = query.execBatch();
    if(!ok){
        qDebug() << "Unable to make insert values in WaferValuesTable";
        closeDataBase(); return;
    }
    progress.setStep(++stepTest);//3
    //---------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------
QString SystemDataBase::getTestElemFullName(const shared_ptr<TestElem>& spTestElem)
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
void SystemDataBase::createSavingWin(const shared_ptr<Lot> &spLot)
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
void SystemDataBase::createConfigWin(const QString& lotName)
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
void SystemDataBase::queryLotData(shared_ptr<Lot>& spLot)
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
        spLot->addWafer(spWafer, slotNum, slotIndex, 0);
    }
    //---------------------------------------------------------------------------------------------
}
void SystemDataBase::queryParamsTable(shared_ptr<Wafer>& spWafer,
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
void SystemDataBase::queryValuesTable(shared_ptr<TestElem>& spTestElem,
                                      const QString& dbTestName,
                                      const size_t slotNum, const size_t testIndex,
                                      const ValuePrefix valuePrefix)
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
        case ValuePrefix::norm:         break;
        case ValuePrefix::milli:
        {spDie->setNormalValue(1.0e-3); spDie->changeValue_to_milli(); break;}
        case ValuePrefix::micro:
        {spDie->setNormalValue(1.0e-6); spDie->changeValue_to_micro(); break;}
        case ValuePrefix::nano:
        {spDie->setNormalValue(1.0e-9); spDie->changeValue_to_nano(); break;}
        case ValuePrefix::pico:
        {spDie->setNormalValue(1.0e-12); spDie->changeValue_to_pico(); break;}
        case ValuePrefix::kilo:
        {spDie->setNormalValue(1.0e+3); spDie->changeValue_to_kilo(); break;}
        case ValuePrefix::mega:
        {spDie->setNormalValue(1.0e+6); spDie->changeValue_to_mega(); break;}
        case ValuePrefix::giga:
        {spDie->setNormalValue(1.0e+9); spDie->changeValue_to_giga(); break;}
        case ValuePrefix::tera:
        {spDie->setNormalValue(1.0e+12); spDie->changeValue_to_tera(); break;}
        default: break;
        }

        spTestElem->addDie(spDie);
    }
}
//-------------------------------------------------------------------------------------------------
//методы доступа к данным партии
size_t SystemDataBase::getWaferCount()
{
    if(spLot)
        return spLot->getWaferCount();
    else return 0;
}
QString SystemDataBase::getLotName()
{
    QString lotName{};
    if(spLot)
        lotName = spLot->getLotName();
    return lotName;
}
shared_ptr<Wafer> SystemDataBase::getWafer(size_t slotIndex)
{
    if(spLot)
        return spLot->getWafer(slotIndex);
    else return nullptr;
}
//=================================================================================================
