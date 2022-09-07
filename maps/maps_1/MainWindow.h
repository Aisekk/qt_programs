#pragma once

//Qt headers
//----------------------------------------------------------------------------
#include <QCoreApplication>
#include <QMainWindow>
#include <QAction>
#include <QMdiArea>
#include <QStandardItemModel>
//#include <QPrinter>
#include <QToolBar>
#include <QStatusBar>
#include <QMenu>
#include <QMenuBar>
#include <QDebug>
#include <QEvent>
//---------------------------------------------------------------------------
//C++ library headers
#include <iostream>
#include <memory>
using namespace std;
//----------------------------------------------------------------------------
//custom headers
//----------------------------------------------------------------------------
//SUBSYSTEMS:
//Calculation
#include "Calculation/SystemCalculation.h"
//Database
#include "Database/SystemDataBase.h"
//Lot
#include "Lot/LotGroup.h"
//Masking
#include "Masking/MaskWin.h"
//Norms (Intervals)
#include "Norms/SystemNorms.h"
#include "Norms/IntervalWin.h"
//Parser
#include "Parser/Parser_4082.h"
#include "Parser/ParserResMap.h"
//Reports
#include "Reports/SystemReports.h"
//Settings
#include "Settings/SystemSettings.h"
//MainWindow
#include "HelpWin.h"
#include "MapImage.h"
#include "Progress.h"
#include "Splitter.h"
#include "TabWidget.h"
#include "TreeView.h"
//miscellany
#include "Validator.h"
#include "Types.h"
//-------------------------------------------------------------------------------------------------
extern QString g_MainWinTitle;
extern QString g_strVersion, g_strYears;
//-------------------------------------------------------------------------------------------------
namespace Ui
{
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget* pwgt = nullptr);
    MainWindow(const MainWindow&) = delete;
    MainWindow& operator=(MainWindow&) = delete;

    ~MainWindow();
public slots:
    void slotStatisticsRecalc(const int X, const int Y, const Mask maskState);
    //================================================================================================
protected:
    void closeEvent(QCloseEvent *pe) override;
private:
    //--------------------------------------------------------------------------------------------
    //функции, вызываемые в конструкторе:
    void initThis();
    void createActions();
    void createReportsActions();
    void createToolBarActions();
    void createDiesScalingActions();
    void createNormsActions();
    void createMapActions();
    void createMenus();
    void addingActionsToMenus();
    void addingMenusToMenuBar();
    void createPrefixUnitActions();
    void createChilds();
    void createToolBars();
    void createGlobalSettingsWinConnections() const;
    //--------------------------------------------------------------------------------------------
    //загрузка файла:
    //установка данных партии в модель
    void setLotDataInModel();
    //вызываются при загрузке файла
    void setMDIareaVisible();
    void removeTextAfterDot(QString& lotName);
    void createTreeViewConnections(const TreeView *pTreeView) const;
    //изменение номера партии
    size_t lotNumIncrement();
    //изменение количества партий
    size_t lotCountIncrement();
    size_t lotCountDecrement();
    //---------------------------------------------------------------------------------------------
    //создание вкладки партии
    void addLotTab(const size_t lotNum, const QString &lotName);
    //методы доступа к объектам партии
    size_t getCurrentLotNum() const;
    shared_ptr<Lot> getCurrentLot() const;
    QString getLotName() const;
    shared_ptr<TestElem> getCurrentTestElem() const;
    //методы доступа к объектам интерфейса
    int getCurrentTabIndex() const;
    Splitter *getCurrentSplitter() const;
    QStandardItemModel* getCurrentLotModel() const;
    MapImage* getCurrentMapImage() const;
    TreeView* getCurrentTreeView() const;
    //интервалы
    NormsID getNormsID() const;
    //тип карты
    MapType getMapType() const;
    //---------------------------------------------------------------------------------------------
    //добавить партию в память
    void addLotToGroup(shared_ptr<Lot> spLot);
    //удалить партию из памяти
    void deleteLotFromGroup(size_t lotNum);
    //--------------------------------------------------------------------------------------------
    //маскирование кристаллов
    void createLocalMaskWinConnections(const MapImage *pMapImage) const;
    //--------------------------------------------------------------------------------------------
    //единицы измерения
    QString testElemUnitName(const QString &testName, const QString &paramName,
                             const ValuePrefix valuePrefix);
    //--------------------------------------------------------------------------------------------
    //проверка остановки объединения бракованных кристаллов
    bool savingUnfitDiesStopped() const;
    //--------------------------------------------------------------------------------------------
    //Ui::MainWindow *ui;
    struct Impl;
    unique_ptr<Impl> m_upImpl;
    //--------------------------------------------------------------------------------------------
    //количество загруженных партий
    int m_lotCount{};
    //для остановки сохранения бракованнных кристаллов
    bool m_savingUnfitDiesStopped{};
    //---------------------------------------------------------------------------------------------
    //объекты, включенные в объектную иерархию:
    //---------------------------------------------------------------------------------------------
    //центральный виджет
    QMdiArea *m_pMDI;
    TabWidget *m_pTabWidget;
    QHBoxLayout *m_phbxLayout;
    //---------------------------------------------------------------------------------------------
    //меню
    QMenu *m_pmnuFile;
    QMenu *m_pmnuScaling;
    QMenu *m_pmnuNorms;
    QMenu *m_pmnuSettings;
    QMenu *m_pmnuMaps;
    QMenu *m_pmnuReports;
    QMenu* m_pmnuView;
    QMenu* m_pmnuHelp;
    //---------------------------------------------------------------------------------------------
    //действия:
    //открытие, сохранение файлов
    QAction *m_pactOpen;
    QAction *m_pactOpen_ResMap;
    QAction *m_pactSave;
    //действия с базами данных
    QAction *m_pactSaveChangesInDies;
    QAction *m_pactSaveLotAsDataBase;
    QAction *m_pactImportLotFromDataBase;
    QAction *m_pactOpenLotConfigFromDataBase;
    QAction *m_pactUpdateDataBase;
    //показать/скрыть панель, движение разделителя
    QAction *m_pactShowHideTree;
    QAction *m_pactLeftShiftStep;
    QAction *m_pactRightShiftStep;
    //масштабирование кристаллов
    QAction *m_pactNormalDieState;
    QAction *m_pactDieSizeScaleUp;
    QAction *m_pactDieSizeScaleDown;
    QAction *m_pactAddEdgeDies;
    QAction *m_pactRemoveEdgeDies;
    //заданные в программе нормы
    QActionGroup *m_pactGroupNorms;
    QAction *m_pactGlobalNorms;
    QAction *m_pactZshNorms035;
    QAction *m_pactFauNorms035;
    QAction *m_pactNorms06;
    QAction *m_pactBigNorms;
    QAction *m_pactSIL10norms;
    QAction *m_pactSIL15norms;
    QAction *m_pactSIL30norms;
    QAction *m_pactSIL100norms;
    QAction *m_pactSIL500norms;
    QAction *m_pactSIL1000norms;
    //настраиваемые нормы
    QAction *m_pactLocalNorms;
    QAction *m_pactLocalNormsWin;
    QAction *m_pactGlobalNormsWin;
    //типы карт
    QActionGroup *m_pactGroupMaps;
    QAction *m_pactStandardMap;
    QAction *m_pactCoordinatesMap;
    //префиксы единиц измерения
    QAction *m_pactNormal;
    QAction *m_pactMilli;
    QAction *m_pactMicro;
    QAction *m_pactNano;
    QAction *m_pactPico;
    QAction *m_pactKilo;
    QAction *m_pactMega;
    QAction *m_pactGiga;
    QAction *m_pactTera;
    //отчеты по партиям
    QAction *m_pactReportsTXT;
    QAction *m_pactReportsPDF;
    //панель инструментов
    QToolBar *m_pToolBar;
    //-------------------------------------------------------------------------------------
    //объекты, не включенные в объектную иерархию:
    //-------------------------------------------------------------------------------------
    //окно маскирования кристаллов
    unique_ptr<MaskWin> m_upMaskWin;
    //-------------------------------------------------------------------------------------
    //окно интервала
    unique_ptr<IntervalWin> m_upIntervalWin;
    //-------------------------------------------------------------------------------------
    //окно справки
    unique_ptr<HelpWin> m_upHelpWin;
    //-------------------------------------------------------------------------------------
    //объект группы партий в памяти
    shared_ptr<LotGroup> m_spLotGroup;
    //-------------------------------------------------------------------------------------
private slots:
    void slotFileLoad_4082();
    void slotFileLoad_ResMap();
    void slotSave();
    void slotTreeState();
    void slotTreeToLeft();
    void slotTreeToRight();
    void slotAddDiesToEdge();
    void slotRemoveDiesFromEdge();
    void slotDiesSizesScaleUp();
    void slotDiesSizesScaleDn();
    void slotNormalDiesScaleFactor();
    //закрытие вкладки и удаление данных партии
    void slotCloseTab(int tabIndex);
    //настроить интервал тестового элемента
    void slotTestElemIntervalWin();
    //расчет статистики
    void slotCalcTestElem(const QModelIndex &testModelIndex);
    void slotCalcTestElemByMasking(TestElemData& testElemData);
    void slotCalcTestElemByNorms();
    //строка состояния - показать выбранную норму
    void slotShowGlobalNorms();
    void slotShowZashita();
    void slotShowFaundri();
    void slotShowNorms06();
    void slotShowLeakage();
    void slotShowBigNorms();
    void slotShowSIL10();
    void slotShowSIL15();
    void slotShowSIL30();
    void slotShowSIL100();
    void slotShowSIL500();
    void slotShowSIL1000();
    void slotShowLocalNorms();
    //тип карты
    void slotStandardMap();
    void slotCoordinatesMap();
    //префиксы единиц измерения
    void slotNormalValues();
    void slotMilliValues();
    void slotMicroValues();
    void slotNanoValues();
    void slotPicoValues();
    void slotKiloValues();
    void slotMegaValues();
    void slotGigaValues();
    void slotTeraValues();
    //маскирование кристаллов
    void slotMaskWin(MaskButtonType maskBtnType);
    void slotChangeMaskStateAllDies(Mask maskState);
    void slotSaveChangesInDies();
    void slotStopSaving(bool stopped);
    //отчеты по партиям
    void slotCreateReportsWinTXT();
    void slotCreateReportsWinPDF();
    //базы данных
    void slotShowSavingWin();
    void slotSaveLotAsDatabase(const int selectedSlot);
    void slotImportDatabase();
    void slotOpenDatabaseConfig();
    void slotUpdateDatabase();
    //справка
    void slotHelpWin();
    //о программе
    void slotAbout();
};
