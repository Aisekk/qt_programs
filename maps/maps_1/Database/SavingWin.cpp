#include "SavingWin.h"

SavingWin::SavingWin(QWidget *pwgt, QMap<size_t, size_t> mapSlotIndexNums) :
    QDialog(pwgt, Qt::WindowTitleHint | Qt::WindowCloseButtonHint | Qt::WindowMinMaxButtonsHint),
    m_mapSlotIndexNums(mapSlotIndexNums)
{
    //-------------------------------------------------------------------------------------
    setWindowTitle("Сохранить слоты: ");
    setMaximumSize(500,500);
    m_pvbxMainLayout = new QVBoxLayout;
    m_pgrdLayout = new QGridLayout;

    size_t slotNum = 0;
    size_t slotIndex = 0;
    size_t n = mapSlotIndexNums.size();
    size_t n_max = 25;
    //---------------------------------------------------------------------------------------------
    //кнопка - сохранить все слоты
    QPushButton *pAllSlotsButton = new QPushButton;
    pAllSlotsButton->setText("   СОХРАНИТЬ ВСЕ СЛОТЫ   ");
    pAllSlotsButton->setMinimumHeight(35);
    connect(pAllSlotsButton, QPushButton::clicked, this, slotSaveAllWafers);
    connect(pAllSlotsButton, QPushButton::pressed, this, slotSaveAllWafers);
    m_pgrdLayout->addWidget(pAllSlotsButton, 0, 0, 1, 6, Qt::AlignHCenter);
    //---------------------------------------------------------------------------------------------
    QString slot = "слот ", space = "";
    if(n == 1) { slot = "     слот "; space = "     "; }
    //---------------------------------------------------------------------------------------------
    size_t row = 1, col = 0;
    size_t limitOnColumnCount = 5;
    if(n > 0 && n <= n_max)
        for(size_t i = 1; i <= n; i++)
        {
            //-------------------------------------------------------------------------------------
            //создание динамической формы
            QPushButton *pSlotButton = new QPushButton;
            if(!mapSlotIndexNums.isEmpty())
                slotNum = mapSlotIndexNums.value(slotIndex);
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
            //соединения - до установки компоновки !
            if(pSlotButton != nullptr)
            {
                connect(pSlotButton, QPushButton::clicked, this, slotSaveOneWafer);
                connect(pSlotButton, QPushButton::pressed, this, slotSaveOneWafer);
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
void SavingWin::setDataBase(const QSqlDatabase& db)
{
    if(db.isOpen())  m_dataBase = db;
    qDebug() << "Database is open";
}
void SavingWin::setLotName(const QString& lotName)
{
    m_lotName = lotName;
}
//-------------------------------------------------------------------------------------------------
void SavingWin::closeEvent(QCloseEvent*)
{
}
//-------------------------------------------------------------------------------------------------
QString SavingWin::getLotName() const
{
    return m_lotName;
}
//-------------------------------------------------------------------------------------------------
//slots
void SavingWin::slotSaveAllWafers()
{
    int noSlotSelected = -1;
    close();
    emit selectedSlot(noSlotSelected);
}
void SavingWin::slotSaveOneWafer()
{
    QPushButton *pSlotButton = qobject_cast<QPushButton*>(sender());
    int slotNum{};
    if(pSlotButton != nullptr)
        slotNum = (pSlotButton->objectName()).toInt();
    close();
    emit selectedSlot(slotNum);
}
//-------------------------------------------------------------------------------------------------
