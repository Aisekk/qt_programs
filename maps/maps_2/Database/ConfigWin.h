#ifndef CONFIGWIN_H
#define CONFIGWIN_H

#include <memory>
using namespace std;

#include <QDialog>
#include <QPushButton>
#include <QLabel>
#include <QDebug>
#include <QSqlDatabase>
#include <QSqlTableModel>
#include <QTableView>
#include <QGridLayout>
#include <QVBoxLayout>
#include "SystemDataBase.h"
#include <QMap>

class ConfigWin : public QDialog
{
    Q_OBJECT
public:
    ConfigWin(QWidget *pwgt = nullptr, QMap<size_t,size_t> mapSlotIndexNums = {});
    void setDatabase(const QSqlDatabase& db);
    void setLotName(const QString& lotName);
    QString getLotName() const;
protected:
    void closeEvent(QCloseEvent*) override;
private:
    //---------------------------------------------------------------------------------------------
    void saveWaferSqlTableModel(const size_t slotNum,
                                const shared_ptr<QSqlTableModel> spSqlTableModel);
    void saveWaferTableView(const size_t slotNum, const shared_ptr<QTableView> spTableView);

    void saveWaferValuesSqlTableModel(const size_t slotNum,
                                      const shared_ptr<QSqlTableModel> spSqlTableModel);
    void saveWaferValuesTableView(const size_t slotNum, const shared_ptr<QTableView> spTableView);

    void saveLotDataSqlTableModel(const size_t slotNum,
                                  const shared_ptr<QSqlTableModel> spSqlTableModel);
    void saveLotDataTableView(const size_t slotNum, const shared_ptr<QTableView> spTableView);
    //---------------------------------------------------------------------------------------------
    void clearAll_Model_and_View_SqlTables();
    //---------------------------------------------------------------------------------------------
    QString m_lotName{};
    QSqlDatabase m_dataBase{};
    //---------------------------------------------------------------------------------------------
    QMap<size_t, size_t> m_mapSlotIndexNums;
    //wafer params
    QMap<size_t, shared_ptr<QSqlTableModel>> m_map_spSqlWaferTableModel;
    QMap<size_t, shared_ptr<QTableView>> m_map_spWaferTableView;
    //wafer values
    QMap<size_t, shared_ptr<QSqlTableModel>> m_map_spSqlTestElemValuesTableModel;
    QMap<size_t, shared_ptr<QTableView>> m_map_spTestElemValuesTableView;
    //lot data
    QMap<size_t, shared_ptr<QSqlTableModel>> m_map_spSqlLotDataTableModel;
    QMap<size_t, shared_ptr<QTableView>> m_map_spLotDataTableView;
    //---------------------------------------------------------------------------------------------
    int m_tableViewPos{};
    int m_tableViewShift{};
    QGridLayout *m_pgrdLayout{};
    QVBoxLayout *m_pvbxMainLayout{};
private slots:
    void slotWaferParamsTableWin();
    void slotWaferValuesTableWin();
    void slotLotTableWin();
};

#endif // CONFIGWIN_H
