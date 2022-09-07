#ifndef SYSTEMDATABASE_H
#define SYSTEMDATABASE_H

#include <QtSql>
#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QTableView>
#include <QLayout>

#include <memory>
using namespace std;

#include "Lot/Lot.h"
#include "Progress.h"
#include "Breaker.h"
#include "ConfigWin.h"
#include "SavingWin.h"
class ConfigWin;
//=================================================================================================
namespace SystemDataBase
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
//-------------------------------------------------------------------------------------------------
//создание соединения с базой данных
bool createConnection(const QString& lotName);
//закрытие соединения с базой данный
void closeDataBase();
//-------------------------------------------------------------------------------------------------
//создание базы данных партии
void createLotDatabase(const QString& lotName);
//создание таблиц одного слота в базе данных партии
void createOneWaferTables(const QString& lotName, const int slotSelected);
//обновление базы данных партии
void updateLotDataBase(const QString& lotName);
//-------------------------------------------------------------------------------------------------
//удаление таблицы
void dropTable(QSqlQuery &query, const QString& tableName);
//-------------------------------------------------------------------------------------------------
//создание таблицы партии
void createLotTable();
//вставка данных в таблицу партии
void insertInLotTable(const size_t slotIndex, const size_t slotNum);
//создание таблицы параметров и вставка данных в нее
void createWaferParamsTable(const shared_ptr<Wafer> &spWafer);
//создание таблицы значений и вставка данных в нее
void createWaferValuesTable(const shared_ptr<Wafer> &spWafer);
//-------------------------------------------------------------------------------------------------
//обновление таблицы партии
void updateLotTable(const int slotIndex, const int slotNum);
//обновление таблицы параметров
void updateWaferParamsTable(const shared_ptr<Wafer> &spWafer);
//обновление таблицы значений
void updateWaferValuesTable(const shared_ptr<Wafer> &spWafer);
//-------------------------------------------------------------------------------------------------
QString getTestElemFullName(const shared_ptr<TestElem> &spTestElem);
//-------------------------------------------------------------------------------------------------
//создать окно кнопок-слотов для сохранения слота или всех слотов в базе
void createSavingWin(const shared_ptr<Lot>& spLot);
//создать окно кнопок-слотов с доступом к данным в базе
void createConfigWin(const QString& lotName);
//-------------------------------------------------------------------------------------------------
//выборка данных из базы для построения модели и дерева
void queryLotData(shared_ptr<Lot> &spLot);
void queryParamsTable(shared_ptr<Wafer>& spWafer,
                      size_t slotNum, size_t slotIndex);
void queryValuesTable(shared_ptr<TestElem> &spTestElem, const QString &dbTestName,
                      const size_t slotNum, const size_t testIndex,
                      const ValuePrefix valuePrefix);
//-------------------------------------------------------------------------------------------------
//методы доступа к партии
size_t getWaferCount();
QString getLotName();
shared_ptr<Wafer> getWafer(size_t slotIndex);
//-------------------------------------------------------------------------------------------------
}
//=================================================================================================

#endif // SYSTEMDATABASE_H
