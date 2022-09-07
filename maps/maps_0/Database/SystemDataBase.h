#ifndef SYSTEMDATABASE_H
#define SYSTEMDATABASE_H

#include <QtSql>
#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QTableView>
#include <QLayout>
#include <QMessageBox>

#include <memory>
#include <thread>
#include <future>
#include <exception>
using namespace std;

#include "LotGroup/Lot.h"
#include "Progress.h"
#include "Breaker.h"
#include "ConfigWin.h"
#include "SavingWin.h"
class ConfigWin;
class DataBaseCloser;
//=================================================================================================
namespace DataBase
{
extern shared_ptr<Lot> spLot;
extern unique_ptr<QTableView> upView;
extern unique_ptr<ConfigWin> upConfigWin;
extern unique_ptr<SavingWin> upSavingWin;
//прерывает запись в базу данных; посредник между главным окном и окном Progress в системе БД
extern Breaker *pBreaker;
//размеры главного окна
extern int MainWinHeight;
extern int MainWinWidth;
//стандартные названия SQL-таблиц без указания слота пластины
extern QString LotDataSqlTable;
extern QString WaferParamsSqlTable;
extern QString WaferValuesSqlTable;
//многопоточность
extern mutex Mutex;
extern size_t sharedStepLot;
//-------------------------------------------------------------------------------------------------
//создание соединения с базой данных
bool createConnection(const QString& lotName);
//закрытие соединения с базой данный
void closeDataBase();
//-------------------------------------------------------------------------------------------------
//создание базы данных партии
void createLotDatabase(const QString& lotName);
//создание таблиц одного слота в базе данных партии
void createOneWaferTables(const QString& lotName, int slotSelected);
//-------------------------------------------------------------------------------------------------
//удаление таблицы
void dropTable(QSqlQuery &query, const QString& tableName);
//-------------------------------------------------------------------------------------------------
//создание таблицы партии
void createLotTable();
//вставка данных в таблицу партии
void insertInLotTable(size_t slotIndex, size_t slotNum);
//создание таблицы параметров и вставка данных в нее
bool createWaferParamsTable(shared_ptr<Wafer> spWafer);
//создание таблицы значений и вставка данных в нее
bool createWaferValuesTable(shared_ptr<Wafer> spWafer);
//-------------------------------------------------------------------------------------------------
//инкремент, вычисляющий процент выполнения партии в потоках
void StepLotIncrement();
//инкремент, вычисляющий процент выполнения пластины в потоках
void StepWaferIncrement();
//параллельное создание, заполнение таблиц параметров, значений
bool createParamsTable(size_t waferCount);
bool createValuesTable(size_t waferCount);
//-------------------------------------------------------------------------------------------------
QString getTestElemFullName(shared_ptr<TestElem> spTestElem);
//-------------------------------------------------------------------------------------------------
//создать окно кнопок-слотов для сохранения слота или всех слотов в базе
void createSavingWin(shared_ptr<Lot> spLot);
//создать окно кнопок-слотов с доступом к данным в базе
void createConfigWin(QString& lotName);
//-------------------------------------------------------------------------------------------------
//выборка данных из базы для построения модели и дерева
void queryLotData(shared_ptr<Lot> &spLot);
void queryParamsTable(shared_ptr<Wafer>& spWafer,
                      size_t slotNum, size_t slotIndex);
void queryValuesTable(shared_ptr<TestElem> &spTestElem, const QString &dbTestName,
                      size_t slotNum, size_t testIndex, ValuePrefix valuePrefix);
//-------------------------------------------------------------------------------------------------
//методы доступа к партии
size_t getWaferCount();
QString getLotName();
shared_ptr<Wafer> getWafer(size_t slotIndex);
}
//=================================================================================================

#endif // SYSTEMDATABASE_H
