#ifndef SAVINGWIN_H
#define SAVINGWIN_H

#include <QDialog>
#include <QPushButton>
#include <QLabel>
#include <QDebug>
#include <QSqlDatabase>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QMap>

class SavingWin : public QDialog
{
    Q_OBJECT
public:
    SavingWin(QWidget *pwgt = nullptr, QMap<size_t,size_t> mapSlotIndexNums = {});

    QString getLotName() const;

    void setDataBase(const QSqlDatabase& db);
    void setLotName(const QString& lotName);
signals:
    void selectedSlot(const int slotNum);//-1 - all slots, 0 - no slot, 1... - slot num 1 selected
protected:
    void closeEvent(QCloseEvent*) override;
private:
    //---------------------------------------------------------------------------------------------
    QString m_lotName{};
    QSqlDatabase m_dataBase{};
    //---------------------------------------------------------------------------------------------
    QMap<size_t, size_t> m_mapSlotIndexNums;
    //---------------------------------------------------------------------------------------------
    QGridLayout *m_pgrdLayout{};
    QVBoxLayout *m_pvbxMainLayout{};
private slots:
    void slotSaveAllWafers();
    void slotSaveOneWafer();
};

#endif // SAVINGWIN_H
