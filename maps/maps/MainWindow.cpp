#include "MainWindow.h"

//ГЛАВНАЯ СИСТЕМА: ИНТЕРФЕЙС ПОЛЬЗОВАТЕЛЯ
//===============================================================================================
//1. ИНТЕРФЕЙС ГЛАВНОГО ОКНА:
//===============================================================================================
MainWindow::MainWindow(QWidget* pwgt) : QMainWindow(pwgt)
{
    //---------------------------------------------------------------------------------------------
    setWindowTitle(g_MainWinTitle);
    setMinimumSize(QSize(700, 500));
    setWindowState(Qt::WindowMaximized);
    //---------------------------------------------------------------------------------------------
    //настройки
    QCoreApplication::setOrganizationName("ChekmarevAV");
    QCoreApplication::setApplicationName("MAPS");
    QLocale::setDefault(QLocale::German);

    SystemSettings::initSettings();
    SystemSettings::settings.init(SystemSettings::spSettings,
                                  SystemSettings::spLocalSettingsWin,
                                  SystemSettings::spGlobalSettingsWin);
    //чтение настроек локальных норм
    SystemSettings::readSettings_LocalNorms();
    //чтение настроек глобальных норм
    double input = 0.0;
    SystemSettings::readSettings_GlobalNorm(input, input, ValuePrefix::norm);
    //---------------------------------------------------------------------------------------------
    //инициализация объектов, не включенных в объектную иерархию
    initThis();
    //---------------------------------------------------------------------------------------------
    //создание действий
    createActions();
    createReportsActions();
    createToolBarActions();
    createDiesScalingActions();
    createNormsActions();
    createMapActions();
    createPrefixUnitActions();
    createMenus();
    addingActionsToMenus();
    addingMenusToMenuBar();
    createChilds();
    createGlobalSettingsWinConnections();
    createToolBars();
    //--------------------------------------------------------------------------------------
    statusBar()->showMessage("Готово", 3000);
    //--------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------
MainWindow::~MainWindow()
{
    //------------------------------------------------------------------
    qDebug() << "\nMainWin destructor:";

    qDebug() << "m_spLotGroup use_count: " << m_spLotGroup.use_count();
    //qDebug() << "m_spSettings use_count: " << m_spSettings.use_count();
}
//----------------------------------------------------------------------
void MainWindow::closeEvent(QCloseEvent* pe)
{
    QMessageBox::StandardButton interrupt = QMessageBox::No;
    //прерывание сохранения в базу данных
    if(DataBase::pBreaker != nullptr)
    {
        interrupt = QMessageBox::question(this, "???",
                                          " Прервать сохранение данных и выйти из программы?");

        switch(interrupt)
        {
        case QMessageBox::Yes:
        {
            DataBase::pBreaker->slotBreakCalc();
            pe->accept();
            break;
        }
        case QMessageBox::No:
        { pe->ignore(); break; }
        default: break;
        }
    }
    //-------------------------------------------------------------------
    qDebug() << "\nMainWin closeEvent(): ";
    qDebug() << "USE_COUNT of shared ptrs: ";
    qDebug() << "m_spLotGroup use_count: " << m_spLotGroup.use_count();
    //qDebug() << "m_spSettings use_count: " << m_spSettings.use_count();
    //-------------------------------------------------------------------
    //удаление объектов-партий c автоматическим удалением других объектов по цепочке
    qDebug() << "\nLotGroup destruction:";
    if(m_spLotGroup)
    {
        //m_spLots->deleteLots();
        m_spLotGroup = nullptr;
        qDebug() << "LotGroup deleted: " << m_spLotGroup.get();
    }
    //-------------------------------------------------------------------
    DataBase::upSavingWin = nullptr;
}
//-----------------------------------------------------------------------
//функции, вызываемые в конструкторе
void MainWindow::initThis()
{
    //создание динамических объектов, не включенных в объектную иерархию:
    //------------------------------------------------------------------------
    //объект партий
    m_spLotGroup = make_shared<LotGroup>();
    //------------------------------------------------------------------------
}
void MainWindow::createActions()
{
    //---------------------------------------------------------------------------------------------
    //открытие, сохранение файлов
    QIcon openIcon(":/fileopen.png");
    m_pactOpen = new QAction("Открыть файл 4082", nullptr);
    m_pactOpen->setText("&Открыть файл 4082 ...");
    m_pactOpen->setShortcut(QKeySequence("CTRL+O"));
    m_pactOpen->setToolTip("Открыть файл 4082");
    m_pactOpen->setIcon(openIcon);
    m_pactOpen->setIconVisibleInMenu(true);
    m_pactOpen->setVisible(true);
    QObject::connect(m_pactOpen, &QAction::triggered, this, slotFileLoad_4082);

    m_pactOpen_ResMap = new QAction("Открыть файл ResMap", nullptr);
    m_pactOpen_ResMap->setText("&Открыть файл ResMap ...");
    m_pactOpen_ResMap->setShortcut(QKeySequence("CTRL+R"));
    m_pactOpen_ResMap->setToolTip("Открыть файл ResMap");
    connect(m_pactOpen_ResMap, QAction::triggered, this, slotFileLoad_ResMap);

    m_pactSave = new QAction("Сохранить карту как изображение", nullptr);
    m_pactSave->setText("&Сохранить карту как изображение");
    m_pactSave->setShortcut(QKeySequence("CTRL+S"));
    m_pactSave->setToolTip("Сохранить карту как изображение");
    m_pactSave->setIcon(QPixmap(":/filesave.png"));
    connect(m_pactSave, QAction::triggered, this, slotSave);
    //---------------------------------------------------------------------------------------------
    m_pactInitDynIntervals = new QAction("Инициализировать динамические интервалы", nullptr);
    m_pactInitDynIntervals->setText("&Инициализировать динамические интервалы");
    m_pactInitDynIntervals->setToolTip("Инициализировать динамические интервалы "
                                       "значениями по умолчанию");
    m_pactInitDynIntervals->setIcon(QPixmap(":/init_default.png"));
    connect(m_pactInitDynIntervals, QAction::triggered, this, slotInitDynIntervalsByDefault);
    //---------------------------------------------------------------------------------------------
    m_pactCopyDynIntervals = new QAction("Копировать динамические интервалы и префиксы", nullptr);
    m_pactCopyDynIntervals->setText("&Копировать динамические интервалы и префиксы");
    m_pactCopyDynIntervals->setToolTip("Копировать динамические интервалы и префиксы "
                                       "из первого слота в остальные");
    m_pactCopyDynIntervals->setIcon(QPixmap(":/copy.png"));
    connect(m_pactCopyDynIntervals, QAction::triggered, this, slotCopyDynIntervalsAndPrefixes);
    //---------------------------------------------------------------------------------------------
    //действия с базами данных
    m_pactSaveChangesInDies = new QAction("Сохранить изменения в памяти", nullptr);
    m_pactSaveChangesInDies->setText("&Сохранить изменения в памяти");
    m_pactSaveChangesInDies->setToolTip("Сохранить изменения в памяти "
                                     "(перед сохранением партии как базы данных)");
    m_pactSaveChangesInDies->setIcon(QPixmap(":/save_changes.png"));
    connect(m_pactSaveChangesInDies, QAction::triggered, this, slotSaveChangesInDies);

    m_pactSaveLotAsDataBase = new QAction("Сохранить партию как базу данных", nullptr);
    m_pactSaveLotAsDataBase->setText("&Сохранить партию как базу данных");
    m_pactSaveLotAsDataBase->setToolTip("Сохранить партию как базу данных");
    m_pactSaveLotAsDataBase->setIcon(QPixmap(":/db_save.png"));
    connect(m_pactSaveLotAsDataBase, QAction::triggered, this, slotShowSavingWin);

    m_pactImportLotFromDataBase = new QAction("Импортировать партию из базы данных", nullptr);
    m_pactImportLotFromDataBase->setText("&Импортировать партию из базы данных ...");
    m_pactImportLotFromDataBase->setToolTip("Импортировать партию из базы данных");
    m_pactImportLotFromDataBase->setIcon(QPixmap(":/db_import.png"));
    connect(m_pactImportLotFromDataBase, QAction::triggered, this, slotImportDatabase);

    m_pactOpenLotConfigFromDataBase = new QAction("Открыть базу данных партии", nullptr);
    m_pactOpenLotConfigFromDataBase->setText("&Открыть базу данных партии ...");
    m_pactOpenLotConfigFromDataBase->setToolTip("Открыть базу данных партии");
    m_pactOpenLotConfigFromDataBase->setIcon(QPixmap(":/db_config.png"));
    connect(m_pactOpenLotConfigFromDataBase, QAction::triggered, this, slotOpenDatabaseConfig);
    //---------------------------------------------------------------------------------------------
}
void MainWindow::createReportsActions()
{
    m_pactReportsTXT = new QAction("Создать подробный TXT-отчет", nullptr);
    m_pactReportsTXT->setText("&Создать подробный TXT-отчет");
    m_pactReportsTXT->setToolTip("Создать подробный TXT-отчет");
    connect(m_pactReportsTXT, QAction::triggered, this, MainWindow::slotCreateReportsWinTXT);

    m_pactReportsPDF = new QAction("Создать подробный PDF-отчет", nullptr);
    m_pactReportsPDF->setText("&Создать подробный PDF-отчет");
    m_pactReportsPDF->setToolTip("Создать подробный PDF-отчет");
    connect(m_pactReportsPDF, QAction::triggered, this, MainWindow::slotCreateReportsWinPDF);
}
void MainWindow::createToolBarActions()
{
    //показать/скрыть панель, движение разделителя
    m_pactShowHideTree = new QAction("", 0);
    m_pactShowHideTree->setText("&Показать/скрыть панель");
    m_pactShowHideTree->setShortcut(QKeySequence(Qt::ControlModifier + Qt::Key_Space));
    m_pactShowHideTree->setIcon(QPixmap(":/list.png"));
    m_pactShowHideTree->setToolTip("Показать/скрыть панель");
    connect(m_pactShowHideTree, QAction::triggered, this, slotTreeState);

    m_pactLeftShiftStep = new QAction("", 0);
    m_pactLeftShiftStep->setText("&Разделитель влево");
    m_pactLeftShiftStep->setShortcut(QKeySequence(Qt::ControlModifier + Qt::Key_Left));
    m_pactLeftShiftStep->setIcon(QPixmap(":/arrow-left.png"));
    m_pactLeftShiftStep->setToolTip("Разделитель влево");
    connect(m_pactLeftShiftStep, QAction::triggered, this, slotTreeToLeft);

    m_pactRightShiftStep = new QAction("", 0);
    m_pactRightShiftStep->setText("&Разделитель вправо");
    m_pactRightShiftStep->setShortcut(QKeySequence(Qt::ControlModifier + Qt::Key_Right));
    m_pactRightShiftStep->setIcon(QPixmap(":/arrow-right.png"));
    m_pactRightShiftStep->setToolTip("Разделитель вправо");
    connect(m_pactRightShiftStep, QAction::triggered, this, slotTreeToRight);
}
void MainWindow::createDiesScalingActions()
{
    //масштабирование кристаллов
    m_pactAddEdgeDies = new QAction("Добавить кристаллы на кромке", nullptr);
    m_pactAddEdgeDies->setText("&Добавить кристаллы на кромке");
    m_pactAddEdgeDies->setShortcut(QKeySequence(Qt::ShiftModifier + Qt::Key_Equal));
    m_pactAddEdgeDies->setToolTip("Добавить кристаллы на кромке");
    connect(m_pactAddEdgeDies, SIGNAL(triggered()), SLOT(slotAddDiesToEdge()));

    m_pactRemoveEdgeDies = new QAction("Убрать кристаллы на кромке", nullptr);
    m_pactRemoveEdgeDies->setText("&Убрать кристаллы на кромке");
    m_pactRemoveEdgeDies->setShortcut(QKeySequence(Qt::ShiftModifier + Qt::Key_Minus));
    m_pactRemoveEdgeDies->setToolTip("Убрать кристаллы на кромке");
    connect(m_pactRemoveEdgeDies, SIGNAL(triggered()), SLOT(slotRemoveDiesFromEdge()));

    m_pactDieSizeScaleUp = new QAction("Увеличить размер кристалла", nullptr);
    m_pactDieSizeScaleUp->setShortcut(QKeySequence(Qt::ControlModifier + Qt::Key_Equal));
    m_pactDieSizeScaleUp->setIcon(QPixmap(":/plus.png"));
    m_pactDieSizeScaleUp->setToolTip("Увеличить размер кристалла");
    connect(m_pactDieSizeScaleUp, SIGNAL(triggered()), SLOT(slotDiesSizesScaleUp()));

    m_pactDieSizeScaleDown = new QAction("Уменьшить размер кристалла", nullptr);
    m_pactDieSizeScaleDown->setShortcut(QKeySequence(Qt::ControlModifier + Qt::Key_Minus));
    m_pactDieSizeScaleDown->setIcon(QPixmap(":/minus.png"));
    m_pactDieSizeScaleDown->setToolTip("Уменьшить размер кристалла");
    connect(m_pactDieSizeScaleDown, SIGNAL(triggered()), SLOT(slotDiesSizesScaleDn()));

    m_pactNormalDieState = new QAction("Вернуть в исходное состояние", nullptr);
    m_pactNormalDieState->setShortcut(QKeySequence(Qt::ControlModifier + Qt::Key_Backspace));
    m_pactNormalDieState->setIcon(QPixmap(":/home.png"));
    m_pactNormalDieState->setToolTip("Вернуть в исходное состояние размеры и количество кристаллов");
    connect(m_pactNormalDieState, SIGNAL(triggered()), SLOT(slotNormalDiesScaleFactor()));
}
void MainWindow::createNormsActions()
{
    //нормы
    m_pactZshNorms035 = new QAction("ZSH", nullptr);
    m_pactZshNorms035->setText("&ZSH");
    m_pactZshNorms035->setCheckable(true);
    m_pactZshNorms035->setShortcut(QKeySequence("CTRL+Z"));
    connect(m_pactZshNorms035, QAction::triggered, this, slotCalcTestElemByNorms);
    connect(m_pactZshNorms035, QAction::triggered, this, slotShowZSH);
    m_pactZshNorms035->setChecked(false);

    m_pactFauNorms035 = new QAction("FAU", nullptr);
    m_pactFauNorms035->setText("&FAU");
    m_pactFauNorms035->setCheckable(true);
    m_pactFauNorms035->setShortcut(QKeySequence("CTRL+F"));
    connect(m_pactFauNorms035, QAction::triggered, this, slotCalcTestElemByNorms);
    connect(m_pactFauNorms035, QAction::triggered, this, slotShowFAU);

    m_pactNorms06 = new QAction("0,6 мкм", nullptr);
    m_pactNorms06->setText("&0,6 мкм");
    m_pactNorms06->setCheckable(true);
    //m_pactNorms06->setShortcut(QKeySequence("CTRL+D"));
    connect(m_pactNorms06, QAction::triggered, this, slotCalcTestElemByNorms);
    connect(m_pactNorms06, QAction::triggered, this, slotShowNorms06);

    m_pactBigNorms = new QAction("Большие интервалы", nullptr);
    m_pactBigNorms->setText("&Большие интервалы");
    m_pactBigNorms->setCheckable(true);
    m_pactBigNorms->setShortcut(QKeySequence("CTRL+B"));
    connect(m_pactBigNorms, QAction::triggered, this, slotCalcTestElemByNorms);
    connect(m_pactBigNorms, QAction::triggered, this, slotShowBigNorms);

    m_pactSIL10norms = new QAction("SIL 10 Ом", nullptr);
    m_pactSIL10norms->setText("&SIL 0.1-10 Ом");
    m_pactSIL10norms->setCheckable(true);
    m_pactSIL10norms->setShortcut(QKeySequence("CTRL+1"));
    connect(m_pactSIL10norms, QAction::triggered, this, slotCalcTestElemByNorms);
    connect(m_pactSIL10norms, QAction::triggered, this, slotShowSIL10);

    m_pactSIL15norms = new QAction("SIL 15 Ом", nullptr);
    m_pactSIL15norms->setText("&SIL 0.1-15 Ом");
    m_pactSIL15norms->setCheckable(true);
    m_pactSIL15norms->setShortcut(QKeySequence("CTRL+2"));
    connect(m_pactSIL15norms, QAction::triggered, this, slotCalcTestElemByNorms);
    connect(m_pactSIL15norms, QAction::triggered, this, slotShowSIL15);

    m_pactSIL30norms = new QAction("SIL 30 Ом", nullptr);
    m_pactSIL30norms->setText("&SIL 0.1-30 Ом");
    m_pactSIL30norms->setCheckable(true);
    m_pactSIL30norms->setShortcut(QKeySequence("CTRL+3"));
    connect(m_pactSIL30norms, QAction::triggered, this, slotCalcTestElemByNorms);
    connect(m_pactSIL30norms, QAction::triggered, this, slotShowSIL30);

    m_pactSIL100norms = new QAction("SIL 100 Ом", nullptr);
    m_pactSIL100norms->setText("&SIL 0.1-100 Ом");
    m_pactSIL100norms->setCheckable(true);
    m_pactSIL100norms->setShortcut(QKeySequence("CTRL+4"));
    connect(m_pactSIL100norms, QAction::triggered, this, slotCalcTestElemByNorms);
    connect(m_pactSIL100norms, QAction::triggered, this, slotShowSIL100);

    m_pactSIL500norms = new QAction("SIL 500 Ом", nullptr);
    m_pactSIL500norms->setText("&SIL 0.1-500 Ом");
    m_pactSIL500norms->setCheckable(true);
    m_pactSIL500norms->setShortcut(QKeySequence("CTRL+5"));
    connect(m_pactSIL500norms, QAction::triggered, this, slotCalcTestElemByNorms);
    connect(m_pactSIL500norms, QAction::triggered, this, slotShowSIL500);

    m_pactSIL1000norms = new QAction("SIL 1000 Ом", nullptr);
    m_pactSIL1000norms->setText("&SIL 0.1-1000 Ом");
    m_pactSIL1000norms->setCheckable(true);
    m_pactSIL1000norms->setShortcut(QKeySequence("CTRL+6"));
    connect(m_pactSIL1000norms, QAction::triggered, this, slotCalcTestElemByNorms);
    connect(m_pactSIL1000norms, QAction::triggered, this, slotShowSIL1000);
    //---------------------------------------------------------------------------------------------
    //переключиться на локальные интервалы
    m_pactLocalNorms = new QAction("Локальные интервалы", nullptr);
    m_pactLocalNorms->setText("&Локальные интервалы");
    m_pactLocalNorms->setCheckable(true);
    m_pactLocalNorms->setShortcut(QKeySequence("CTRL+L"));
    connect(m_pactLocalNorms, QAction::triggered, this, slotCalcTestElemByNorms);
    connect(m_pactLocalNorms, QAction::triggered, this, slotShowLocalNorms);
    m_pactLocalNorms->setEnabled(true);

    //переключиться на глобальный интервал
    m_pactGlobalNorms = new QAction("Глобальный интервал", nullptr);
    m_pactGlobalNorms->setText("&Глобальный интервал");
    m_pactGlobalNorms->setCheckable(true);
    m_pactGlobalNorms->setShortcut(QKeySequence("CTRL+G"));
    connect(m_pactGlobalNorms, QAction::triggered, this, slotCalcTestElemByNorms);
    connect(m_pactGlobalNorms, QAction::triggered, this, slotShowGlobalNorms);
    //по умолчанию
    m_pactGlobalNorms->setChecked(true);

    //переключиться на динамический интервал
    m_pactDynamicInterval = new QAction("Динамический интервал", nullptr);
    m_pactDynamicInterval->setText("&Динамический интервал");
    m_pactDynamicInterval->setCheckable(true);
    m_pactDynamicInterval->setShortcut(QKeySequence("CTRL+D"));
    connect(m_pactDynamicInterval, QAction::triggered, this, slotCalcTestElemByNorms);
    connect(m_pactDynamicInterval, QAction::triggered, this, slotShowDynamicInterval);
    //---------------------------------------------------------------------------------------------
    //установить интервалы пользователя
    m_pactLocalNormsWin = new QAction("Локальные интервалы", nullptr);
    m_pactLocalNormsWin->setText("&Локальные интервалы");
    m_pactLocalNormsWin->setShortcut(QKeySequence("SHIFT+L"));
    connect(m_pactLocalNormsWin, QAction::triggered,
            &SystemSettings::settings, Settings::slotLocalSettingsWin);

    //установить глобальный интервал
    m_pactGlobalNormsWin = new QAction("Глобальный интервал", nullptr);
    m_pactGlobalNormsWin->setText("&Глобальный интервал");
    m_pactGlobalNormsWin->setShortcut(QKeySequence("SHIFT+G"));
    connect(m_pactGlobalNormsWin, QAction::triggered,
            &SystemSettings::settings, Settings::slotGlobalSettingsWin);
}
void MainWindow::createMapActions()
{
    //стандартная карта
    m_pactStandardMap = new QAction("Стандартная карта", nullptr);
    m_pactStandardMap->setText("&Стандартная карта");
    m_pactStandardMap->setCheckable(true);
    m_pactStandardMap->setChecked(true);
    m_pactStandardMap->setShortcut(QKeySequence(Qt::Key_Space));
    m_pactStandardMap->setToolTip("Стандартная карта");
    connect(m_pactStandardMap, QAction::triggered, this, slotStandardMap);

    //карта координат кристаллов
    m_pactCoordinatesMap = new QAction("Карта координат", nullptr);
    m_pactCoordinatesMap->setText("&Карта координат");
    m_pactCoordinatesMap->setCheckable(true);
    m_pactCoordinatesMap->setShortcut(QKeySequence(Qt::Key_Backspace));
    m_pactCoordinatesMap->setToolTip("Карта координат");
    connect(m_pactCoordinatesMap, QAction::triggered, this, slotCoordinatesMap);
}
void MainWindow::createPrefixUnitActions()
{
    //единицы измерения
    m_pactNormal = new QAction("исходное значение",this);
    m_pactNormal->setText("&исходное значение");
    m_pactNormal->setIconText("НОРМА");
    connect(m_pactNormal, QAction::triggered, this, slotNormalValues);

    m_pactMilli = new QAction("милли",this);
    m_pactMilli->setText("&милли");
    m_pactMilli->setIconText("МИЛЛИ");
    connect(m_pactMilli, QAction::triggered, this, slotMilliValues);

    m_pactMicro = new QAction("микро",this);
    m_pactMicro->setText("&микро");
    m_pactMicro->setIconText("МИКРО");
    connect(m_pactMicro, QAction::triggered, this, slotMicroValues);

    m_pactNano = new QAction("нано",this);
    m_pactNano->setText("&нано");
    m_pactNano->setIconText("НАНО");
    connect(m_pactNano, QAction::triggered, this, slotNanoValues);

    m_pactPico = new QAction("пико",this);
    m_pactPico->setText("&пико");
    m_pactPico->setIconText("ПИКО");
    connect(m_pactPico, QAction::triggered, this, slotPicoValues);

    m_pactKilo = new QAction("кило",this);
    m_pactKilo->setText("&кило");
    m_pactKilo->setIconText("КИЛО");
    connect(m_pactKilo, QAction::triggered, this, slotKiloValues);

    m_pactMega = new QAction("мега",this);
    m_pactMega->setText("&мега");
    m_pactMega->setIconText("МЕГА");
    connect(m_pactMega, QAction::triggered, this, slotMegaValues);

    m_pactGiga = new QAction("гига",this);
    m_pactGiga->setText("&гига");
    m_pactGiga->setIconText("ГИГА");
    connect(m_pactGiga, QAction::triggered, this, slotGigaValues);

    m_pactTera = new QAction("тера",this);
    m_pactTera->setText("&тера");
    m_pactTera->setIconText("ТЕРА");
    connect(m_pactTera, QAction::triggered, this, slotTeraValues);
}
void MainWindow::createChilds()
{
    //удаление динамических объектов, не вкл. в объектную иерархию, -- в деструкторе
    m_pTabWidget = new TabWidget;
    m_pTabWidget->setTabsClosable(true);
    m_pTabWidget->setAttribute(Qt::WA_DeleteOnClose);
    connect(m_pTabWidget, TabWidget::tabCloseRequested, this, slotCloseTab);

    //компоновка центрального виджета
    m_phbxLayout = new QHBoxLayout;
    m_phbxLayout->setMargin(1);
    m_phbxLayout->setSpacing(1);
    m_phbxLayout->addWidget(m_pTabWidget);

    //создание центрального виджета
    m_pMDI = new QMdiArea(this);
    m_pMDI->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    m_pMDI->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    m_pMDI->setLayout(m_phbxLayout);

    setCentralWidget(m_pMDI);
    m_pMDI->setVisible(false);
}
void MainWindow::createMenus()
{
    m_pmnuFile = new QMenu("&Файл");
    m_pmnuScaling = new QMenu("&Масштаб");
    m_pmnuNorms = new QMenu("&Выбрать интервалы");
    m_pmnuSettings = new QMenu("&Настройки");
    m_pmnuMaps = new QMenu("&Карта");
    m_pmnuReports = new QMenu("&Отчеты");
    m_pmnuView = new QMenu("&Вид");
    m_pmnuHelp = new QMenu("&Справка");
}
void MainWindow::addingActionsToMenus()
{  
    m_pmnuFile->addAction(m_pactOpen);
    //m_pmnuFile->addAction(m_pactOpen_ResMap);
    m_pmnuFile->addAction(m_pactSave);
    m_pmnuFile->addSeparator();
    m_pmnuFile->addAction(m_pactInitDynIntervals);
    m_pmnuFile->addAction(m_pactCopyDynIntervals);
    m_pmnuFile->addSeparator();
    m_pmnuFile->addAction(m_pactSaveChangesInDies);
    m_pmnuFile->addAction(m_pactSaveLotAsDataBase);
    m_pmnuFile->addAction(m_pactImportLotFromDataBase);
    m_pmnuFile->addAction(m_pactOpenLotConfigFromDataBase);
    m_pmnuFile->addSeparator();
    m_pmnuFile->addAction("&Выйти", qApp, SLOT(closeAllWindows()), QKeySequence("CTRL+Q"));
    //-------------------------------------------------------------------
    m_pmnuScaling->addAction(m_pactNormalDieState);
    m_pmnuScaling->addAction(m_pactDieSizeScaleUp);
    m_pmnuScaling->addAction(m_pactDieSizeScaleDown);
    m_pmnuScaling->addAction(m_pactAddEdgeDies);
    m_pmnuScaling->addAction(m_pactRemoveEdgeDies);
    //-------------------------------------------------------------------
    m_pactGroupNorms = new QActionGroup(this);;
    m_pactGroupNorms->addAction(m_pactZshNorms035);
    m_pactGroupNorms->addAction(m_pactFauNorms035);
    m_pactGroupNorms->addAction(m_pactNorms06);
    m_pactGroupNorms->addAction(m_pactBigNorms);
    m_pactGroupNorms->addAction(m_pactSIL10norms);
    m_pactGroupNorms->addAction(m_pactSIL15norms);
    m_pactGroupNorms->addAction(m_pactSIL30norms);
    m_pactGroupNorms->addAction(m_pactSIL100norms);
    m_pactGroupNorms->addAction(m_pactSIL500norms);
    m_pactGroupNorms->addAction(m_pactSIL1000norms);
    m_pactGroupNorms->addAction(m_pactLocalNorms);
    m_pactGroupNorms->addAction(m_pactGlobalNorms);
    m_pactGroupNorms->addAction(m_pactDynamicInterval);

    QList<QAction*> pactList;
    pactList.push_back(m_pactZshNorms035);
    pactList.push_back(m_pactFauNorms035);
    pactList.push_back(m_pactNorms06);
    pactList.push_back(m_pactBigNorms);
    pactList.push_back(m_pactSIL10norms);
    pactList.push_back(m_pactSIL15norms);
    pactList.push_back(m_pactSIL30norms);
    pactList.push_back(m_pactSIL100norms);
    pactList.push_back(m_pactSIL500norms);
    pactList.push_back(m_pactSIL1000norms);
    pactList.push_back(m_pactLocalNorms);
    pactList.push_back(m_pactGlobalNorms);
    pactList.push_back(m_pactDynamicInterval);
    m_pmnuNorms->addActions(pactList);
    //---------------------------------------------------------------
    m_pmnuSettings->addAction(m_pactLocalNormsWin);
    m_pmnuSettings->addAction(m_pactGlobalNormsWin);

    m_pactGroupMaps = new QActionGroup(this);;
    m_pactGroupMaps->addAction(m_pactStandardMap);
    m_pactGroupMaps->addAction(m_pactCoordinatesMap);
    QList<QAction*> pactListMaps;
    pactListMaps.push_back(m_pactStandardMap);
    pactListMaps.push_back(m_pactCoordinatesMap);
    m_pmnuMaps->addActions(pactListMaps);

    m_pmnuReports->addAction(m_pactReportsTXT);
    m_pmnuReports->addAction(m_pactReportsPDF);

    m_pmnuView->addAction(m_pactShowHideTree);
    m_pmnuView->addAction(m_pactLeftShiftStep);
    m_pmnuView->addAction(m_pactRightShiftStep);

    m_pmnuHelp->addAction("&Помощь", this, SLOT(slotHelpWin()), Qt::Key_F1);
    m_pmnuHelp->addAction("&О программе", this, SLOT(slotAbout()));
}
void MainWindow::addingMenusToMenuBar()
{
    menuBar()->addMenu(m_pmnuFile);
    menuBar()->addMenu(m_pmnuScaling);
    menuBar()->addMenu(m_pmnuNorms);
    menuBar()->addMenu(m_pmnuSettings);
    menuBar()->addMenu(m_pmnuMaps);
    menuBar()->addMenu(m_pmnuReports);
    menuBar()->addMenu(m_pmnuView);
    menuBar()->addMenu(m_pmnuHelp);
}
void MainWindow::createToolBars()
{
    //горизонтальная панель инструментов
    m_pToolBar = new QToolBar("Панель инструментов", this);
    m_pToolBar->addAction(m_pactOpen);
    m_pToolBar->addAction(m_pactSave);
    m_pToolBar->addSeparator();
    m_pToolBar->addAction(m_pactInitDynIntervals);
    m_pToolBar->addAction(m_pactCopyDynIntervals);
    m_pToolBar->addSeparator();
    m_pToolBar->addAction(m_pactSaveChangesInDies);
    m_pToolBar->addAction(m_pactSaveLotAsDataBase);
    m_pToolBar->addAction(m_pactImportLotFromDataBase);
    m_pToolBar->addAction(m_pactOpenLotConfigFromDataBase);
    m_pToolBar->addSeparator();
    m_pToolBar->addAction(m_pactShowHideTree);
    m_pToolBar->addAction(m_pactLeftShiftStep);
    m_pToolBar->addAction(m_pactRightShiftStep);
    m_pToolBar->addSeparator();
    m_pToolBar->addAction(m_pactNormalDieState);
    m_pToolBar->addAction(m_pactDieSizeScaleUp);
    m_pToolBar->addAction(m_pactDieSizeScaleDown);
    m_pToolBar->addSeparator();
    m_pToolBar->addAction(m_pactPico);
    m_pToolBar->addAction(m_pactNano);
    m_pToolBar->addAction(m_pactMicro);
    m_pToolBar->addAction(m_pactMilli);
    m_pToolBar->addAction(m_pactNormal);
    m_pToolBar->addAction(m_pactKilo);
    m_pToolBar->addAction(m_pactMega);
    m_pToolBar->addAction(m_pactGiga);
    m_pToolBar->addAction(m_pactTera);
    m_pToolBar->addSeparator();
    addToolBar(Qt::TopToolBarArea, m_pToolBar);
}
void MainWindow::createGlobalSettingsWinConnections() const
{
    //применение норм (пересчет) при нажатии кнопки Apply в окне объекта GlobalSettingsWin
    GlobalSettingsWin *pGlobalSettingsWin = SystemSettings::spGlobalSettingsWin.get();
    if(pGlobalSettingsWin)
        connect(pGlobalSettingsWin, GlobalSettingsWin::recalc, this, slotCalcTestElemByNorms);
}
//-----------------------------------------------------------------------
//сохранить карту
void MainWindow::slotSave()
{
    MapImage *pMapImage = getCurrentMapImage();
    if(pMapImage) pMapImage->slotSave();
}
//----------------------------------------------------------------------
//слоты для перемещения панели (дерева с тестами)
void MainWindow::slotTreeState()
{
    TreeView* pTreeView = getCurrentTreeView();
    if(pTreeView) pTreeView->toHide();
}
//----------------------------------------------------------------------
void MainWindow::slotTreeToLeft()
{
    TreeView* pTreeView = getCurrentTreeView();
    if(pTreeView) pTreeView->toLeft();
}
// ----------------------------------------------------------------------
void MainWindow::slotTreeToRight()
{
    TreeView* pTreeView = getCurrentTreeView();
    if(pTreeView) pTreeView->toRight();
}
//----------------------------------------------------------------------
//слоты для масштабирования кристаллов
void MainWindow::slotAddDiesToEdge()
{
    MapImage *pMapImage = getCurrentMapImage();
    int max_of_XY = 0;
    if(pMapImage)
        max_of_XY = pMapImage->getMaxOfDiesAlongRadius();

    if(max_of_XY != 0)
    {
        int Num_Of_VoidDiesLayers = pMapImage->getNumOfVoidDiesLayers();
        pMapImage->setNumOfVoidDiesLayers(++Num_Of_VoidDiesLayers);
        pMapImage->setMaxOfDiesAlongRadiusInFact(max_of_XY + Num_Of_VoidDiesLayers);
        pMapImage->update();
    }
}
//----------------------------------------------------------------------
void MainWindow::slotRemoveDiesFromEdge()
{
    MapImage *pMapImage = getCurrentMapImage();
    int max_of_XY = 0;
    if(pMapImage)
        max_of_XY = pMapImage->getMaxOfDiesAlongRadius();

    if(max_of_XY != 0)
    {
        int Num_Of_VoidDiesLayers = pMapImage->getNumOfVoidDiesLayers();
        pMapImage->setNumOfVoidDiesLayers(--Num_Of_VoidDiesLayers);
        pMapImage->setMaxOfDiesAlongRadiusInFact(max_of_XY + Num_Of_VoidDiesLayers);
        pMapImage->update();
    }
}
//----------------------------------------------------------------------
void MainWindow::slotDiesSizesScaleUp()
{
    MapImage *pMapImage = getCurrentMapImage();
    int max_of_XY = 0;
    if(pMapImage)
        max_of_XY = pMapImage->getMaxOfDiesAlongRadius();

    if(max_of_XY != 0)
        pMapImage->scaleUpDieSize();
}
//----------------------------------------------------------------------
void MainWindow::slotDiesSizesScaleDn()
{
    MapImage *pMapImage = getCurrentMapImage();
    int max_of_XY = 0;
    if(pMapImage)
        max_of_XY = pMapImage->getMaxOfDiesAlongRadius();

    if(max_of_XY != 0)
        pMapImage->scaleDownDieSize();
}
//----------------------------------------------------------------------
void MainWindow::slotNormalDiesScaleFactor()
{
    MapImage *pMapImage = getCurrentMapImage();
    int max_of_XY = 0;
    if(pMapImage)
        max_of_XY = pMapImage->getMaxOfDiesAlongRadius();

    if(max_of_XY != 0)
        pMapImage->setNormalScaleFactorDieSize();
}
//----------------------------------------------------------------------
//строка состояния
void MainWindow::slotShowGlobalNorms(){statusBar()->showMessage("Глобальный интервал",0);}
void MainWindow::slotShowLocalNorms(){statusBar()->showMessage("Локальные интервалы",0);}
void MainWindow::slotShowDynamicInterval(){statusBar()->showMessage("Динамический интервал",0);}
void MainWindow::slotShowZSH(){statusBar()->showMessage("Интервалы: ZSH",0);}
void MainWindow::slotShowFAU(){statusBar()->showMessage("Интервалы: FAU",0);}
void MainWindow::slotShowNorms06(){statusBar()->showMessage("Интервалы: 0,6 мкм",0);}
void MainWindow::slotShowLeakage(){statusBar()->showMessage("Интервалы: Токи утечки по модулю",0);}
void MainWindow::slotShowBigNorms(){statusBar()->showMessage("Большие интервалы",0);}
void MainWindow::slotShowSIL10(){statusBar()->showMessage("Интервалы: SIL 0.1-10 Ом",0);}
void MainWindow::slotShowSIL15(){statusBar()->showMessage("Интервалы: SIL 0.1-15 Ом",0);}
void MainWindow::slotShowSIL30(){statusBar()->showMessage("Интервалы: SIL 0.1-30 Ом",0);}
void MainWindow::slotShowSIL100(){statusBar()->showMessage("Интервалы: SIL 0.1-100 Ом",0);}
void MainWindow::slotShowSIL500(){statusBar()->showMessage("Интервалы: SIL 0.1-500 Ом",0);}
void MainWindow::slotShowSIL1000(){statusBar()->showMessage("Интервалы: SIL 0.1-1000 Ом",0);}
//-----------------------------------------------------------------------
//тип карты
void MainWindow::slotStandardMap()
{
    MapImage* pMapImage{};
    Splitter *pSpl{};
    pSpl = qobject_cast<Splitter*>(m_pTabWidget->currentWidget());
    if(pSpl)
    {
        pMapImage = pSpl->findChild<MapImage*>();
        if(pMapImage)
            pMapImage->setMapType(MapType::standard);
        else return;
    }
}
void MainWindow::slotCoordinatesMap()
{
    MapImage* pMapImage{};
    Splitter *pSpl{};
    pSpl = qobject_cast<Splitter*>(m_pTabWidget->currentWidget());
    if(pSpl)
    {
        pMapImage = pSpl->findChild<MapImage*>();
        if(pMapImage)
            pMapImage->setMapType(MapType::coordinates);
        else return;
    }
}
//-----------------------------------------------------------------------
//окно: помощь
void MainWindow::slotHelpWin()
{
    m_upHelpWin.reset(new HelpWin);
    HelpWin *pHelpWin = m_upHelpWin.get();
    pHelpWin->show();
}
//окно: о программе
void MainWindow::slotAbout()
{
    QMessageBox::about(this, "О программе ",
                       " Свободное ПО в пределах организации"
                       "\n Карты и статистика"
                       "\n Программа построения карт и вычисления статистики параметров микросхем"
                       "\n Версия " + g_strVersion + ", " + g_strYears +
                       "\n Автор: ");
}
//===============================================================================================
//
//
//
//===============================================================================================
//2. МЕТОДЫ ДОСТУПА:
//===============================================================================================
//методы доступа к объектам партии:
size_t MainWindow::getCurrentLotNum() const
{
    size_t lotNum{};
    TreeView* pTreeView = getCurrentTreeView();
    if(pTreeView)
    {
        lotNum = pTreeView->getLotNum();
        if(lotNum) return lotNum;
    }
    return 0;
}
shared_ptr<Lot> MainWindow::getCurrentLot() const
{
    size_t lotNum = getCurrentLotNum();
    shared_ptr<Lot> spLot = m_spLotGroup->getLot(lotNum);
    if(spLot)
        return spLot;
    return nullptr;
}
QString MainWindow::getLotName() const
{
    QString fileName{};
    shared_ptr<Lot> spLot = getCurrentLot();
    if(spLot)
        fileName = spLot->getLotName();
    return fileName;
}
shared_ptr<TestElem> MainWindow::getCurrentTestElem() const
{
    QPersistentModelIndex persTestModelIndex{};
    shared_ptr<Wafer> spWafer;
    shared_ptr<TestElem> spTestElem;
    size_t testIndex{};
    size_t slotIndex{};
    QModelIndex slotModelIndex{};

    shared_ptr<Lot> spLot = getCurrentLot();
    if(spLot)
    {
        persTestModelIndex = spLot->getTestModelIndex();
        if(persTestModelIndex.isValid())
        {
            testIndex = persTestModelIndex.row();
            slotModelIndex = persTestModelIndex.parent();
            slotIndex = slotModelIndex.row() - 1;
            if(slotModelIndex.isValid())
                spWafer = spLot->getWafer(slotIndex);
            else return nullptr;
        }
    }

    if(spWafer)
        spTestElem = spWafer->getTestElem(testIndex);
    if(spTestElem)
        return spTestElem;

    return nullptr;
}
//методы доступа к объектам интерфейса:
int MainWindow::getCurrentTabIndex() const
{
    int tabIndex = m_pTabWidget->currentIndex();
    return tabIndex;
}
Splitter* MainWindow::getCurrentSplitter() const
{
    Splitter *pSpl = nullptr;
    pSpl = qobject_cast<Splitter*>(m_pTabWidget->currentWidget());
    if(pSpl)
        return pSpl;
    return nullptr;
}
QStandardItemModel* MainWindow::getCurrentLotModel() const
{
    TreeView* pTreeView{};
    QStandardItemModel* pModel{};
    pTreeView = getCurrentTreeView();
    if(pTreeView)
    {
        pModel = qobject_cast<QStandardItemModel*>(pTreeView->model());
        if(pModel != nullptr)
            return pModel;
    }
    return nullptr;
}
MapImage* MainWindow::getCurrentMapImage() const
{
    Splitter *pSpl = getCurrentSplitter();
    if(pSpl)
    {
        MapImage* pMapImage = pSpl->findChild<MapImage*>();
        if(pMapImage != nullptr)
            return pMapImage;
    }
    return nullptr;
}
TreeView* MainWindow::getCurrentTreeView() const
{
    Splitter *pSpl = getCurrentSplitter();
    if(pSpl != nullptr)
    {
        TreeView* pTreeView = pSpl->findChild<TreeView*>();
        if(pTreeView != nullptr)
            return pTreeView;
    }
    return nullptr;
}
//другие методы
NormsID MainWindow::getNormsID() const
{
    TreeView *pTreeView = getCurrentTreeView();
    if(pTreeView) pTreeView->setIntervalEnabled(false);

    NormsID normsID = NormsID::Global;
    if(m_pactGlobalNorms->isChecked())              normsID = NormsID::Global;
    else if(m_pactLocalNorms->isChecked())          normsID = NormsID::Local;
    else if(m_pactDynamicInterval->isChecked())
    {
        normsID = NormsID::Dynamic;
        if(pTreeView) pTreeView->setIntervalEnabled(true);
    }
    else if(m_pactZshNorms035->isChecked())         normsID = NormsID::Zsh035;
    else if(m_pactFauNorms035->isChecked())         normsID = NormsID::Fau035;
    else if(m_pactNorms06->isChecked())             normsID = NormsID::Norms06;
    else if(m_pactBigNorms->isChecked())            normsID = NormsID::BigNorms;
    else if(m_pactSIL10norms->isChecked())          normsID = NormsID::SIL10;
    else if(m_pactSIL15norms->isChecked())          normsID = NormsID::SIL15;
    else if(m_pactSIL30norms->isChecked())          normsID = NormsID::SIL30;
    else if(m_pactSIL100norms->isChecked())         normsID = NormsID::SIL100;
    else if(m_pactSIL500norms->isChecked())         normsID = NormsID::SIL500;
    else if(m_pactSIL1000norms->isChecked())        normsID = NormsID::SIL1000;

    return normsID;
}
MapType MainWindow::getMapType() const
{
    MapType mapType{};
    if(m_pactStandardMap->isChecked())
        mapType = MapType::standard;
    else if(m_pactCoordinatesMap->isChecked())
        mapType = MapType::coordinates;
    return mapType;
}
//-----------------------------------------------------------------------------------------------
//добавить партию в группу партий (в память)
void MainWindow::addLotToGroup(shared_ptr<Lot> spLot)
{
    m_spLotGroup->addLot(spLot);
}
//удалить партию из группы партий (из памяти)
void MainWindow::deleteLotFromGroup(size_t lotNum)
{
    m_spLotGroup->deleteLot(lotNum);
}
//===============================================================================================
//
//
//
//===============================================================================================
//3. ОБРАБОТКА ДАННЫХ:
//===============================================================================================
void MainWindow::setLotDataInModel()
{
        shared_ptr<Lot> spLot = getCurrentLot();
        QString lotName = spLot->getLotName();
        int waferCount = spLot->getWaferCount();
        QStandardItemModel *pModel = getCurrentLotModel();
        if(pModel == nullptr){qDebug() << "pModel is nullptr"; return;}

        pModel->setRowCount(1);
        pModel->setColumnCount(1);
        //вставка слотов
        pModel->setRowCount(waferCount + 1);
        QModelIndex index00 = pModel->index(0,0);
        pModel->setData(index00, lotName);

        QString testName{}, paramName{}, algName{};
        shared_ptr<Wafer> spWafer;
        int slotIndex = 0;
        for(int topRow = 1; topRow <= waferCount; ++topRow)
        {
            spWafer = spLot->getWafer(slotIndex);
            slotIndex++;
            QModelIndex index = pModel->index(topRow,0);
            int slotNum = spWafer->getSlotNum();
            int testElemsCount_OneWafer = spWafer->getTestElemCount();

            pModel->setData(index,"Слот " + QString::number(slotNum)
                            + " (тестов: " + QString::number(testElemsCount_OneWafer) + ")");
            pModel->insertRows(0, testElemsCount_OneWafer, index);
            pModel->insertColumns(0, 1, index);

            for(int row = 0; row < testElemsCount_OneWafer; ++row)
            {
                //row = testIndex
                shared_ptr<TestElem> spTestElem = spWafer->getTestElem(row);
                testName = spTestElem->getTestName();
                paramName = spTestElem->getParamName();
                algName = spTestElem->getAlgName();

                QString sum_TestNames_ParamNames{};
                QString revers = "revers", Revers = "Revers";
                if(algName.contains(revers) || algName.contains(Revers))
                    sum_TestNames_ParamNames = testName + " (" + paramName
                            + "_" + revers + ")";
                else
                    sum_TestNames_ParamNames = testName + " (" + paramName + ")";

                pModel->setData(pModel->index(row,0,index), sum_TestNames_ParamNames);
            }
        }
}
//-----------------------------------------------------------------------------------------------
//загрузка файлов:
//-----------------------------------------------------------------------------------------------
//открыть/загрузить файл 4082
void MainWindow::slotFileLoad_4082()
{
    //------------------------------------------------------------------------------------------------------------
    //запись имени файла
    QString strFilter{};
    QString fileNameWithPath{};
    QString strFile = QFileDialog::
            getOpenFileName(this, fileNameWithPath,"",
                            "Файл 4082(*.AD5T);;Текстовый файл(*.txt)",
                            &strFilter);

    if(!strFile.isEmpty())
        if(strFilter.contains("AD5T") || strFilter.contains("txt"))
            fileNameWithPath = strFile;

    QString openingFileName = fileNameWithPath;
    QFileInfo FileInfo(fileNameWithPath);
    QString fileNameNoPath = FileInfo.completeBaseName();
    removeTextAfterDot(fileNameNoPath);
    QString lotName = fileNameNoPath;
    //---------------------------------------------------------------------------------
    //чтение файла
    QFile ReadFileAD5T(openingFileName);
    if(!ReadFileAD5T.open(QIODevice::ReadOnly | QIODevice::Text)) return;
    else setMDIareaVisible();
    //---------------------------------------------------------------------------------
    //парсинг
    size_t lotNum{};
    size_t lotCount = 0;
    shared_ptr<Lot> spLot;
    Reading reading_switch = Reading::on;
    switch(reading_switch)
    {
    case Reading::on:
    {
        //разбор данных файла в объекте парсера
        FileReader4082 fileReader;
        fileReader.fileReading(ReadFileAD5T);
        //инкремент порядкового номера партии
        lotNum = lotNumIncrement();
        //инкремент количества партий
        lotCount = lotCountIncrement();
        //создание объекта-партии
        spLot = fileReader.getLot();
        if(spLot == nullptr){ qDebug() << "spLot is nullptr"; return; }
        spLot->setLotNum(lotNum);
        spLot->setLotName(lotName);
        //добавление партии в группу
        addLotToGroup(spLot);
        break;
    }
    case Reading::off:{ break; }
    }
    //---------------------------------------------------------------------------------
    ReadFileAD5T.close();

    //создание вкладки партии и дабавление ее в центральный виджет
    addLotTab(lotNum, lotName);
    //запись данных партии в модель
    setLotDataInModel();
    //создание соединений с деревом
    TreeView *pTreeView = getCurrentTreeView();
    if(pTreeView)
        createTreeViewConnections(pTreeView);

    QString mainWinTitle = g_MainWinTitle + ": количество партий - " + QString::number(lotCount);
    setWindowTitle(mainWinTitle);
}
//-----------------------------------------------------------------------------------------------
//открыть/загрузить файл ResMap - НЕ ДОДЕЛАНО
void MainWindow::slotFileLoad_ResMap()
{
    //----------------------------------------------------------------------------------
    //запись имени файла
    QString strFilter{};
    QString fileNameWithPath{};
    QStringList strFiles = QFileDialog::
            getOpenFileNames(this, fileNameWithPath,
                             "",
                             "Файл ResMap(*.R**);;Текстовый файл(*.txt)", &strFilter);

    if (!strFiles.isEmpty())
        if(strFilter.contains("R") || strFilter.contains("txt"))
            fileNameWithPath = strFiles[0];

    //fileNameWithPath = "BMK_M1_165_F_KLV_Z_trA_RSiTi_VDP_1.ad5_su.AD5T";
    //fileNameWithPath = "1_3 values.txt";
    QFileInfo FileInfo(fileNameWithPath);
    QString fileNameNoPath = FileInfo.completeBaseName();
    QString titleName = "Первый файл ResMap: ";
    setWindowTitle(titleName + fileNameNoPath);
    //парсинг
    Reading parsing_switch = Reading::on;

    switch(parsing_switch)
    {
    case Reading::off:
    {
        break;
    }
    case Reading::on:
    {
        //разбор данных файла в объекте парсера
        QStringList::const_iterator cit = strFiles.constBegin();
        for(;cit != strFiles.constEnd(); ++cit)
        {
            //чтение файла
            QFile ReadFileResMap(*cit);
            if(!ReadFileResMap.open(QIODevice::ReadOnly | QIODevice::Text))
                return;

            FileReaderResMap parser;
            parser.fileReading(ReadFileResMap);
            ReadFileResMap.close();
        }

        break;
    }
    }

    //end of parsing_switch
    //----------------------------------------конец Parsing ------------------------------------

}
//-----------------------------------------------------------------------------------------------
//изменение номера партии
size_t MainWindow::lotNumIncrement()
{
    static size_t lotNum = 0;
    return ++lotNum;
}
//изменение количества партий
size_t MainWindow::lotCountIncrement()
{
    return ++m_lotCount;
}
size_t MainWindow::lotCountDecrement()
{
    return --m_lotCount;
}
//-------------------------------------------------------------------------------------------------
//удаление текста после точки из названия партии
void MainWindow::removeTextAfterDot(QString& lotName)
{
    char dot = '.';
    QStringList strList{};
    if(lotName.contains(dot))
    {
        strList = lotName.split(dot);
        lotName = strList[0];
    }
}
void MainWindow::setMDIareaVisible()
{
    m_pMDI->setVisible(true);
}
//-------------------------------------------------------------------------------------------------
//соединения объектов при обработке данных
void MainWindow::createTreeViewConnections(const TreeView* pTreeView) const
{
    //---------------------------------------------------------------------------------------------
    //соединение сигнала из дерева со слотом выбора карты
    //press left mouse
    connect(pTreeView, TreeView::clicked, this, slotCalcTestElem);
    //press Enter
    connect(pTreeView, TreeView::activated, this, slotCalcTestElem);
    //---------------------------------------------------------------------------------------------
    //вычисление при клике правой кнопкой мыши:
    connect(pTreeView, TreeView::contextMnuEvent, this, slotCalcTestElemByNorms);
    //вычисление после маскирования:
    connect(pTreeView, TreeView::maskTrigger, this, slotMaskWin);
    //---------------------------------------------------------------------------------------------
    //изменить состояние маскирования всех кристаллов
    //(маскировать все кристаллы или снять маску со всех кристаллов)
    connect(pTreeView, TreeView::maskState, this, slotChangeMaskStateAllDies);
    //---------------------------------------------------------------------------------------------
    //задать динамический интервал тестового элемента
    connect(pTreeView, TreeView::interval, this, slotTestElemDynIntervalWin);
}
//-------------------------------------------------------------------------------------------------
//настроить интервал тестового элемента
void MainWindow::slotTestElemDynIntervalWin()
{
    //---------------------------------------------------------------------------------------------
    //проверка на ошибки
    TreeView* pTreeView = qobject_cast<TreeView*>(sender());
    if(pTreeView == nullptr){ qDebug() << "pTreeView is nullptr"; return;}

    shared_ptr<Lot> spLot = getCurrentLot();
    size_t waferCount{};
    if(spLot) waferCount = spLot->getWaferCount(); else return;

    QStandardItemModel *pModel = getCurrentLotModel();
    if(pModel == nullptr){ qDebug() << "pModel is nullptr" ; return;}
    QModelIndex testModelIndex = pTreeView->currentIndex();

    bool error = false;
    for(size_t i = 0; i < waferCount + 1 ; ++i)
        if(testModelIndex == pModel->index(i,0) && error == false)
        {
            QMessageBox::warning(this, "Ошибка", "Выберите тестовый элемент");
            error = true;
        }
    if(error) return;
    //---------------------------------------------------------------------------------------------
    auto spTestElem = getCurrentTestElem();
    if(spTestElem == nullptr) return;
    QString testName = spTestElem->getTestName();
    m_upIntervalWin.reset(new IntervalWin(nullptr));
    IntervalWin *pIntervalWin = m_upIntervalWin.get();
    connect(pIntervalWin, IntervalWin::interval, this, slotCalcTestElemByDynInterval);
    pIntervalWin->setWindowTitle("Интервал " + testName + ": ");
    pIntervalWin->show();
}
//-------------------------------------------------------------------------------------------------
//инициализировать динамические интервалы значениями по умолчанию
void MainWindow::slotInitDynIntervalsByDefault()
{
    QLibrary lib("intervals");
    typedef QPair<double,double> (*LibFct)(const QString&);
    LibFct libfct = (LibFct)(lib.resolve("IntervalsObj"));
    if(libfct == nullptr) return;
    //---------------------------------------------------------------------------------------------
    auto spLot = getCurrentLot();
    if(spLot == nullptr) return;
    size_t waferCount = spLot->getWaferCount();
    //---------------------------------------------------------------------------------------------
    Progress progress(this, waferCount);
    progress.setModal(false);
    progress.setMaximumSize(300, 100);
    progress.setWindowTitle("Инициализация динамических интервалов ...");
    progress.show();
    size_t stepLot = 0;
    //---------------------------------------------------------------------------------------------
    QPair<double, double> twoValues{};
    for(size_t slotIndex = 0; slotIndex < waferCount; ++slotIndex)
    {
        auto spWafer = spLot->getWafer(slotIndex);
        if(spWafer == nullptr) break;
        size_t testElemCount = spWafer->getTestElemCount();
        for(size_t testIndex = 0; testIndex < testElemCount; ++testIndex)
        {
            //-------------------------------------------------------------------------------------
            auto spTestElem = spWafer->getTestElem(testIndex);
            if(spTestElem == nullptr) break;
            QString testName = spTestElem->getTestName();
            //извлечь данные из dll-функции
            twoValues = libfct(testName);
            //-------------------------------------------------------------------------------------
            //установить интервал тестового элемента
            double dn = twoValues.first;
            double up = twoValues.second;
            spTestElem->setCriterionDn(dn);
            spTestElem->setCriterionUp(up);
            TestElemData testElemData{};
            slotCalcTestElemByMasking(testElemData);
            //-------------------------------------------------------------------------------------
        }
        progress.setStep(++stepLot);
    }
}
//копировать динамические интервалы из первого слота в остальные слоты
void MainWindow::slotCopyDynIntervalsAndPrefixes()
{
    auto spLot = getCurrentLot();
    if(spLot == nullptr) return;
    size_t waferCount = spLot->getWaferCount();

    size_t slotIndex = 0;
    auto spFirstWafer = spLot->getWafer(slotIndex);
    if(spFirstWafer == nullptr) return;
    size_t testElemCountFirstWafer = spFirstWafer->getTestElemCount();
    //---------------------------------------------------------------------------------------------
    Progress progress(this, waferCount);
    progress.setModal(false);
    progress.setMaximumSize(300, 100);
    progress.setWindowTitle("Копирование интервалов, префиксов ...");
    progress.show();
    size_t stepLot = 0;
    //---------------------------------------------------------------------------------------------
    for(size_t slotIndex = 1; slotIndex < waferCount; ++slotIndex)
    {
        auto spWafer = spLot->getWafer(slotIndex);
        if(spWafer == nullptr) break;
        size_t testElemCount = spWafer->getTestElemCount();
        if(testElemCount != testElemCountFirstWafer) break;
        for(size_t testIndex = 0; testIndex < testElemCount; ++testIndex)
        {
            auto spTestElemFirstWafer = spFirstWafer->getTestElem(testIndex);
            if(spTestElemFirstWafer == nullptr) break;
            //-------------------------------------------------------------------------------------
            //установить префикс
            ValuePrefix prefix = spTestElemFirstWafer->getTestValuesPrefix();
            auto spTestElem = spWafer->getTestElem(testIndex);
            if(spTestElem == nullptr) break;
            spTestElem->setTestValuesPrefix(prefix);
            //пересчет тестового элемента с новым префиксом величин в кристаллах
            setPrefixIntoTestElemDies(spTestElem, prefix);
            //-------------------------------------------------------------------------------------
            //установить интервал тестового элемента
            double dn = spTestElemFirstWafer->getCriterionDn();
            double up = spTestElemFirstWafer->getCriterionUp();
            spTestElem->setCriterionDn(dn);
            spTestElem->setCriterionUp(up);
            //-------------------------------------------------------------------------------------
        }
        progress.setStep(++stepLot);
    }
}
//-------------------------------------------------------------------------------------------------
//расчет статистики:
//-------------------------------------------------------------------------------------------------
//вычислить тестовый элемент, выбранный пользователем
void MainWindow::slotCalcTestElem(const QModelIndex& testModelIndex)
{    
    QPersistentModelIndex persTestModelIndex = testModelIndex;
    auto spLot = getCurrentLot();
    if(spLot) spLot->setModelIndex(persTestModelIndex); else return;
    //------------------------------------------------------------------------------------
    int testIndex{};
    int slotIndex{};
    QModelIndex slotModelIndex{};
    if(testModelIndex.isValid())
    {
        testIndex = testModelIndex.row();
        slotModelIndex = testModelIndex.parent();
        slotIndex = slotModelIndex.row() - 1;
    }
    //------------------------------------------------------------------------------------  
    TestElemData testElemData{};
    testElemData.setLot(spLot);
    testElemData.setSlotIndex(slotIndex);
    testElemData.setTestIndex(testIndex);
    //------------------------------------------------------------------------------------
    NormsID normsID = getNormsID();
    auto spTestElem = getCurrentTestElem();
    if(spTestElem == nullptr) return;
    if(normsID == NormsID::Dynamic)
    {
        double dn = spTestElem->getCriterionDn();
        double up = spTestElem->getCriterionUp();
        testElemData.setCriterionDn(dn);
        testElemData.setCriterionUp(up);
    }
    testElemData.setNormsID(normsID);
    SystemNorms::setTestElemNorm(testElemData);
    //------------------------------------------------------------------------------------
    MapType mapType = getMapType();
    testElemData.setMapType(mapType);
    //------------------------------------------------------------------------------------
    MapImage* pMapImage = getCurrentMapImage();
    if(pMapImage == nullptr) return;
    testElemData.setMapImage(pMapImage);
    //------------------------------------------------------------------------------------
    if(slotModelIndex.isValid())
        SystemCalculation::calcTestElemStatistics(testElemData);
    else return;
}

//вычислить тестовый элемент с учетом маскирования, заданного пользователем
void MainWindow::slotCalcTestElemByMasking(TestElemData &testElemData)
{
    //------------------------------------------------------------------------------------
    QPersistentModelIndex persTestModelIndex{};
    auto spLot = getCurrentLot();
    if(spLot) persTestModelIndex = spLot->getTestModelIndex(); else return;
    //------------------------------------------------------------------------------------
    int testIndex{};
    int slotIndex{};
    QModelIndex slotModelIndex{};
    if(persTestModelIndex.isValid())
    {
        //индекс теста
        testIndex = persTestModelIndex.row();
        //индекс слота
        slotModelIndex = persTestModelIndex.parent();
        slotIndex = slotModelIndex.row() - 1;
    }
    else return;
    //------------------------------------------------------------------------------------
    testElemData.setLot(spLot);
    testElemData.setSlotIndex(slotIndex);
    testElemData.setTestIndex(testIndex);
    //------------------------------------------------------------------------------------
    NormsID normsID = getNormsID();
    auto spTestElem = getCurrentTestElem();
    if(spTestElem == nullptr) return;
    if(normsID == NormsID::Dynamic)
    {
        double dn = spTestElem->getCriterionDn();
        double up = spTestElem->getCriterionUp();
        testElemData.setCriterionDn(dn);
        testElemData.setCriterionUp(up);
    }
    testElemData.setNormsID(normsID);
    SystemNorms::setTestElemNorm(testElemData);
    //------------------------------------------------------------------------------------
    MapType mapType = getMapType();
    testElemData.setMapType(mapType);
    //------------------------------------------------------------------------------------
    MapImage* pMapImage = getCurrentMapImage();
    if(pMapImage == nullptr) return;
    testElemData.setMapImage(pMapImage);
    //------------------------------------------------------------------------------------
    if(slotModelIndex.isValid())
        SystemCalculation::calcTestElemStatistics(testElemData);
    else return;
}

//вычислить тестовый элемент по нормам, выбранным пользователем
void MainWindow::slotCalcTestElemByNorms()
{
    TestElemData testElemData{};
    slotCalcTestElemByMasking(testElemData);
}

//вычислить тестовый элемент по динамическому интервалу, выбранному пользователем
void MainWindow::slotCalcTestElemByDynInterval(const QPair<double,double>& twoValues)
{
    double dn = twoValues.first;
    double up = twoValues.second;
    auto spTestElem = getCurrentTestElem();
    spTestElem->setNormsID(NormsID::Dynamic);
    spTestElem->setCriterionDn(dn);
    spTestElem->setCriterionUp(up);

    TestElemData testElemData{};
    slotCalcTestElemByMasking(testElemData);
}
//-------------------------------------------------------------------------------------------------
//создание вкладки партии
void MainWindow::addLotTab(size_t lotNum, const QString& lotName)
{
    size_t mapWidthInPixel = 1024+512;
    size_t mapHeightInPixel = 1024+128;

    MapImage *pMapImage = new MapImage;
    pMapImage->setAttribute(Qt::WA_DeleteOnClose);
    pMapImage->resize(QSize(mapWidthInPixel, mapHeightInPixel));

    QStandardItemModel *pModel = new QStandardItemModel;

    TreeView *pTreeView = new TreeView;
    pTreeView->setAttribute(Qt::WA_DeleteOnClose);
    pTreeView->setLotNum(lotNum);
    pTreeView->setModel(pModel);
    pTreeView->setFont(QFont("New Courier", 10));
    size_t treeWidth = 210;
    pTreeView->setFixedWidth(treeWidth);
    pTreeView->setHeaderHidden(true);
    pTreeView->setVisible(true);
    pTreeView->setEditTriggers(QAbstractItemView::NoEditTriggers);

    Splitter *pSpl = new Splitter(nullptr);
    pSpl->setOrientation(Qt::Horizontal);
    pSpl->setAttribute(Qt::WA_DeleteOnClose);
    pSpl->setLotNum(lotNum);
    pSpl->addWidget(pTreeView);
    pSpl->addWidget(pMapImage);


    //добавление новой вкладки-партии в объект TabWidget
    if(pSpl != nullptr)
    {
        m_pTabWidget->addTab(pSpl, lotName);
        //установить текущую вкладку
        m_pTabWidget->setCurrentWidget(pSpl);
    }
}
//удаление вкладки партии
void MainWindow::slotCloseTab(int tabIndex)
{
    //закрытие вкладки
    Splitter *pspl = qobject_cast<Splitter*>(m_pTabWidget->widget(tabIndex));

    size_t lotNum{};
    if(pspl != nullptr)
    {
        lotNum = pspl->getLotNum();
        pspl->close();
    }

    size_t lotCount{};
    if(lotNum != 0)
    {
        deleteLotFromGroup(lotNum);
        lotCount = lotCountDecrement();
    }
    QString mainWinTitle = g_MainWinTitle + ": количество партий - " + QString::number(lotCount);
    setWindowTitle(mainWinTitle);
}
//=================================================================================================
//
//
//
//=================================================================================================
//4. ПРЕФИКСЫ ЕДИНИЦ ИЗМЕРЕНИЯ:
//=================================================================================================
//установка префикса в объекты-кристаллы
void MainWindow::setPrefixIntoTestElemDies(shared_ptr<TestElem> spTestElem, ValuePrefix prefix)
{
    QVector<shared_ptr<Die>> vec_spDies = spTestElem->getDies();
    if(!vec_spDies.isEmpty())
    {
        for(shared_ptr<Die> spDie : vec_spDies)
            spDie->changeValueTo(prefix);
        slotCalcTestElemByNorms();
    }
}
//установка префикса для единицы измерения
void MainWindow::slotNormalValues()
{
    ValuePrefix prefix = ValuePrefix::norm;
    shared_ptr<TestElem> spTestElem = getCurrentTestElem();
    if(spTestElem) spTestElem->setTestValuesPrefix(prefix); else return;
    setPrefixIntoTestElemDies(spTestElem, prefix);
}
void MainWindow::slotMilliValues()
{
    ValuePrefix prefix = ValuePrefix::milli;
    shared_ptr<TestElem> spTestElem = getCurrentTestElem();
    if(spTestElem) spTestElem->setTestValuesPrefix(prefix); else return;
    setPrefixIntoTestElemDies(spTestElem, prefix);
}
void MainWindow::slotMicroValues()
{
    ValuePrefix prefix = ValuePrefix::micro;
    shared_ptr<TestElem> spTestElem = getCurrentTestElem();
    if(spTestElem) spTestElem->setTestValuesPrefix(prefix); else return;
    setPrefixIntoTestElemDies(spTestElem, prefix);
}
void MainWindow::slotNanoValues()
{
    ValuePrefix prefix = ValuePrefix::nano;
    shared_ptr<TestElem> spTestElem = getCurrentTestElem();
    if(spTestElem) spTestElem->setTestValuesPrefix(prefix); else return;
    setPrefixIntoTestElemDies(spTestElem, prefix);
}
void MainWindow::slotPicoValues()
{
    ValuePrefix prefix = ValuePrefix::pico;
    shared_ptr<TestElem> spTestElem = getCurrentTestElem();
    if(spTestElem) spTestElem->setTestValuesPrefix(prefix); else return;
    setPrefixIntoTestElemDies(spTestElem, prefix);
}
void MainWindow::slotKiloValues()
{
    ValuePrefix prefix = ValuePrefix::kilo;
    shared_ptr<TestElem> spTestElem = getCurrentTestElem();
    if(spTestElem) spTestElem->setTestValuesPrefix(prefix); else return;
    setPrefixIntoTestElemDies(spTestElem, prefix);
}
void MainWindow::slotMegaValues()
{
    ValuePrefix prefix = ValuePrefix::mega;
    shared_ptr<TestElem> spTestElem = getCurrentTestElem();
    if(spTestElem) spTestElem->setTestValuesPrefix(prefix); else return;
    setPrefixIntoTestElemDies(spTestElem, prefix);
}
void MainWindow::slotGigaValues()
{
    ValuePrefix prefix = ValuePrefix::giga;
    shared_ptr<TestElem> spTestElem = getCurrentTestElem();
    if(spTestElem) spTestElem->setTestValuesPrefix(prefix); else return;
    setPrefixIntoTestElemDies(spTestElem, prefix);
}
void MainWindow::slotTeraValues()
{
    ValuePrefix prefix = ValuePrefix::tera;
    shared_ptr<TestElem> spTestElem = getCurrentTestElem();
    if(spTestElem) spTestElem->setTestValuesPrefix(prefix); else return;
    setPrefixIntoTestElemDies(spTestElem, prefix);
}
//=================================================================================================
//
//
//
//=================================================================================================
//5. МАСКИРОВАНИЕ КРИСТАЛЛОВ:
//=================================================================================================
void MainWindow::slotMaskWin(MaskButtonType maskBtnType)
{    
    TreeView* pTreeView = qobject_cast<TreeView*>(sender());
    if(pTreeView == nullptr){ qDebug() << "pTreeView is nullptr"; return;}

    shared_ptr<Lot> spLot = getCurrentLot();
    size_t waferCount{};
    if(spLot) waferCount = spLot->getWaferCount();

    QStandardItemModel *pModel = getCurrentLotModel();
    MapImage *pMapImage = getCurrentMapImage();
    if(pModel == nullptr){ qDebug() << "pModel is nullptr" ; return;}
    if(pMapImage == nullptr){ qDebug() << "pMapImage is nullptr" ; return;}

    //название тестового элемента
    QModelIndex testModelIndex = pTreeView->currentIndex();
    QVariant selectedTestName = pModel->data(testModelIndex);
    QString testName = selectedTestName.toString();
    //индексы тестового элемента, пластины и номер пластины
    int testIndex = testModelIndex.row();
    QModelIndex slotModelIndex = testModelIndex.parent();
    size_t slotIndex = slotModelIndex.row() - 1;
    shared_ptr<Wafer> spWafer = spLot->getWafer(slotIndex);
    size_t slotNum{};
    if(spWafer) slotNum = spWafer->getSlotNum();

    bool error = false;
    for(size_t i = 0; i < waferCount + 1 ; ++i)
        if(testModelIndex == pModel->index(i,0) && error == false)
        {
            QMessageBox::warning(this, "Ошибка", "Выберите тестовый элемент");
            error = true;
        }
    if(error) return;

    auto spTestElem = spWafer->getTestElem(testIndex);
    QVector<shared_ptr<Die>> vec_spDies;
    if(spTestElem)
        vec_spDies = spTestElem->getDies();

    if(!vec_spDies.isEmpty() && testModelIndex.isValid() && slotModelIndex.isValid() )
    {
        m_upMaskWin.reset(new MaskWin(nullptr, testName, testIndex, slotNum));
        createLocalMaskWinConnections(pMapImage);
        //передача массива всех исходных кристаллов в объект маскирования
        //и типа кнопки маскирования
        MaskWin *pMaskWin = m_upMaskWin.get();
        if(pMaskWin != nullptr)
            pMaskWin->setDieButtons(vec_spDies, maskBtnType);
        else return;

        //установка маскированных кристаллов на форму кнопок
        for(shared_ptr<Die> spDie : vec_spDies)
            if(spDie->maskButtonState() == MaskButtonState::masked)
            {
                int x = spDie->getX();
                int y = spDie->getY();
                pMaskWin->setDieButtonToMaskedState(x,y);
            }
        pMaskWin->show();
    }
}
void MainWindow::slotChangeMaskStateAllDies(Mask maskState)
{
    TreeView* pTreeView = qobject_cast<TreeView*>(sender());
    if(pTreeView == nullptr){ qDebug() << "pTreeView is nullptr"; return;}

    shared_ptr<Lot> spLot = getCurrentLot();
    size_t waferCount{};
    if(spLot) waferCount = spLot->getWaferCount();

    QStandardItemModel *pModel = getCurrentLotModel();
    MapImage *pMapImage = getCurrentMapImage();
    if(pModel == nullptr){ qDebug() << "pModel is nullptr" ; return;}
    if(pMapImage == nullptr){ qDebug() << "pMapImage is nullptr" ; return;}

    //название тестового элемента
    QModelIndex testModelIndex = pTreeView->currentIndex();
    QVariant selectedTestName = pModel->data(testModelIndex);
    QString testName = selectedTestName.toString();
    //индексы тестового элемента, пластины и номер пластины
    int testIndex = testModelIndex.row();
    QModelIndex slotModelIndex = testModelIndex.parent();
    size_t slotIndex = slotModelIndex.row() - 1;
    shared_ptr<Wafer> spWafer = spLot->getWafer(slotIndex);
    size_t slotNum{};
    if(spWafer) slotNum = spWafer->getSlotNum();

    bool error = false;
    for(size_t i = 0; i < waferCount + 1 ; ++i)
        if(testModelIndex == pModel->index(i,0) && error == false)
        {
            QMessageBox::warning(this, "Ошибка", "Выберите тестовый элемент");
            error = true;
        }
    if(error) return;

    auto spTestElem = spWafer->getTestElem(testIndex);
    QVector<shared_ptr<Die>> vec_spDies;
    if(spTestElem) vec_spDies = spTestElem->getDies();

    if(error == false && !vec_spDies.isEmpty()
            && testModelIndex.isValid() && slotModelIndex.isValid() )
    {
        m_upMaskWin.reset(new MaskWin(nullptr, testName, testIndex, slotNum));
        createLocalMaskWinConnections(pMapImage);
        //передача массива всех исходных кристаллов в объект маскирования
        //и типа кнопки маскирования
        MaskButtonType maskBtnType = MaskButtonType::value;
        MaskWin *pMaskWin = m_upMaskWin.get();
        if(pMaskWin != nullptr)
            pMaskWin->setDieButtons(vec_spDies, maskBtnType);
        else return;

        //маскирование или демаскирование всех кристаллов
        MaskButtonState maskButtonState{};
        switch (maskState){
        case Mask::no:{ maskButtonState = MaskButtonState::unmasked; break; }
        case Mask::red:{ maskButtonState = MaskButtonState::masked; break; }
        case Mask::blue:{ maskButtonState = MaskButtonState::masked; break; }
        case Mask::gray:{ maskButtonState = MaskButtonState::masked; break; }
        default: break; }
        if(maskButtonState == MaskButtonState::masked)
            for(shared_ptr<Die> spDie : vec_spDies)
            {
                int x = spDie->getX();
                int y = spDie->getY();
                spDie->setMaskState(maskState);
                spDie->setMaskButtonState(maskButtonState);
                pMaskWin->setDieButtonToMaskedState(x,y);
            }
        else
            for(shared_ptr<Die> spDie : vec_spDies)
            {
                int x = spDie->getX();
                int y = spDie->getY();
                spDie->setMaskState(maskState);
                spDie->setMaskButtonState(maskButtonState);
                pMaskWin->setDieButtonToUnmaskedState(x,y);
            }
        pMaskWin->slotApply();
        if(maskButtonState == MaskButtonState::unmasked)
            slotCalcTestElem(testModelIndex);
    }
}
//-------------------------------------------------------------------------------------------------
void MainWindow::createLocalMaskWinConnections(const MapImage *pMapImage) const
{
    MaskWin *pLocalMaskWin = m_upMaskWin.get();
    if(pLocalMaskWin != nullptr)
    {
        //передача координат и состояния маскирования в объект-карту для изменения цвета кристалла
        connect(pLocalMaskWin, MaskWin::sigMaskState, pMapImage, MapImage::slotDrawDieMasked);
        //передача координат и состояния маскирования в объект this для пересчета статистики
        connect(pLocalMaskWin, MaskWin::sigMaskState, this, slotStatisticsRecalc);
    }
}
//-------------------------------------------------------------------------------------------------
//слот для приема координат типа int,int, состояния кристалла типа bool и пересчета статистики
void MainWindow::slotStatisticsRecalc(int X, int Y, Mask maskState)
{
    unique_ptr<MaskData> upMaskData(new MaskData);
    MaskData *pMaskData = upMaskData.get();
    if(pMaskData != nullptr)
    {
        pMaskData->setX_of_MaskState(X);
        pMaskData->setY_of_MaskState(Y);
        pMaskData->setMaskState(maskState);
    }

    TestElemData testElemData{};
    testElemData.moveMaskData(std::move(upMaskData));
    slotCalcTestElemByMasking(testElemData);
}
//-------------------------------------------------------------------------------------------------
//
//
//
//===============================================================================================
//6. ОТЧЕТЫ ПО ПАРТИЯМ:
//===============================================================================================
//создать окно TXT-отчетов
void MainWindow::slotCreateReportsWinTXT()
{
    shared_ptr<Lot> spLot = getCurrentLot();
    if(spLot == nullptr) return;

    SystemReports::upReportsWinTXT.reset(new ReportsWinTXT(nullptr, spLot));
    ReportsWinTXT *pReportsWinTXT = SystemReports::upReportsWinTXT.get();
    //передать UI-данные
    NormsID normsID = getNormsID();
    MapType mapType = getMapType();
    MapImage* pMapImage = getCurrentMapImage();
    pReportsWinTXT->setNormsID(normsID);
    pReportsWinTXT->setMapType(mapType);
    pReportsWinTXT->setMapImage(pMapImage);

    //соединения окна отчетов с калькулятором отчетов
    connect(pReportsWinTXT, ReportsWinTXT::sigOneWaferReport,
            &SystemReports::reportsCalculator, ReportsCalc::slotOneWaferReport);
    connect(pReportsWinTXT, ReportsWinTXT::sigAllWafersReports,
            &SystemReports::reportsCalculator, ReportsCalc::slotAllWafersReports);

    pReportsWinTXT->show();
}
//создать окно PDF-отчетов
void MainWindow::slotCreateReportsWinPDF()
{
    shared_ptr<Lot> spLot = getCurrentLot();
    if(spLot == nullptr) return;

    SystemReports::upReportsWinPDF.reset(new ReportsWinPDF(nullptr, spLot));
    ReportsWinPDF *pReportsWinPDF = SystemReports::upReportsWinPDF.get();
    //передать UI-данные
    NormsID normsID = getNormsID();
    MapType mapType = getMapType();
    MapImage* pMapImage = getCurrentMapImage();
    pReportsWinPDF->setNormsID(normsID);
    pReportsWinPDF->setMapType(mapType);
    pReportsWinPDF->setMapImage(pMapImage);

    //соединения окна отчетов с калькулятором отчетов
    connect(pReportsWinPDF, ReportsWinPDF::sigOneWaferReport,
            &SystemReports::reportsCalculator, ReportsCalc::slotOneWaferReport);
    connect(pReportsWinPDF, ReportsWinPDF::sigAllWafersReports,
            &SystemReports::reportsCalculator, ReportsCalc::slotAllWafersReports);

    pReportsWinPDF->show();
}
//===============================================================================================
//
//
//
//===============================================================================================
//7. БАЗЫ ДАННЫХ:
//-------------------------------------------------------------------------------------------------
//сохранить данные в памяти (брак. кристаллы ...) перед сохранением в базу данных
void MainWindow::slotSaveChangesInDies()
{
    shared_ptr<Lot> spLot = getCurrentLot();
    size_t waferCount{};
    if(spLot) waferCount = spLot->getWaferCount(); else return;
    slotStopSaving(false);
    //---------------------------------------------------------------------------------------------
    NormsID extNormsID = getNormsID();
    //---------------------------------------------------------------------------------------------
    if(waferCount <= 0) return;
    for(size_t slotIndex = 0; slotIndex < waferCount; ++slotIndex)
    {
        auto spWafer = spLot->getWafer(slotIndex);
        size_t testElemCount = spWafer->getTestElemCount();

        Progress progress(this, testElemCount);
        progress.setModal(false);
        progress.setStopButtonVisible();
        progress.adjustSize();
        ssize_t slotNum = spWafer->getSlotNum();
        progress.setWindowTitle("Сохранение: слот " +
                                QString::number(slotNum,10) + " ...");
        connect(&progress, Progress::stopped, this, slotStopSaving);
        progress.show();
        size_t step = 0;
        if(savingUnfitDiesStopped()){ progress.close(); return; }

        if(spWafer == nullptr) return;
        for(size_t testIndex = 0; testIndex < testElemCount; ++testIndex)
        {
            if(savingUnfitDiesStopped()){ progress.close(); break; }
            auto spTestElem = spWafer->getTestElem(testIndex);
            if(spTestElem == nullptr) break;
            //---------------------------------------------------------
            TestElemData testElemData{};
            testElemData.setLot(spLot);
            testElemData.setSlotIndex(slotIndex);
            testElemData.setTestIndex(testIndex);
            //---------------------------------------------------------
            double criterionDn{};
            double criterionUp{};
            NormsID id = spTestElem->getNormsID();
            if(id == NormsID::Dynamic)
            {
                //извлечь интервал из памяти
                criterionDn = spTestElem->getCriterionDn();
                criterionUp = spTestElem->getCriterionUp();
            }
            else
            {
                if(extNormsID == NormsID::Dynamic)
                { progress.setStep(++step); continue; }
                testElemData.setNormsID(extNormsID);
                //вычислить интервал для тестового элемента
                SystemNorms::setTestElemNorm(testElemData);
                //установить интервал в тестовый элемент (в память)
                criterionDn = testElemData.getCriterionDn();
                criterionUp = testElemData.getCriterionUp();
                spTestElem->setCriterionDn(criterionDn);
                spTestElem->setCriterionUp(criterionUp);
            }
            QString testName = spTestElem->getTestName();
            QString paramName = spTestElem->getParamName();
            ValuePrefix prefix  = spTestElem->getTestValuesPrefix();
            QString testElemUnitName = SystemCalculation::
                    testElemUnitName(testName, paramName, prefix);
            spTestElem->setUnitName(testElemUnitName);

            auto vec_spDies = spTestElem->getDies();
            if(!vec_spDies.isEmpty())
                for(shared_ptr<Die>& spDie : vec_spDies)
                {
                    double value = spDie->getValue();
                    if(value < criterionDn || value > criterionUp)
                    {
                        spDie->setMaskState(Mask::red);
                        spDie->setMaskButtonState(MaskButtonState::masked);
                    }
                }
            progress.setStep(++step);
            qApp->processEvents();
        }
    }
}
void MainWindow::slotStopSaving(bool stopped)
{
    m_savingUnfitDiesStopped = stopped;
}
bool MainWindow::savingUnfitDiesStopped() const
{
    return m_savingUnfitDiesStopped;
}
//-------------------------------------------------------------------------------------------------
void MainWindow::slotShowSavingWin()
{
    QString lotName{};
    shared_ptr<Lot> spLot = getCurrentLot();
    if(spLot) lotName = spLot->getLotName(); else return;

    QString strFilter{};
    QString fileName = QFileDialog::
            getSaveFileName(this, "Сохранить партию как файл базы данных ...",
                            lotName, "Файл базы данных (*.db)", &strFilter);
    if(!fileName.isEmpty())
    {
        DataBase::spLot = spLot;
        DataBase::createSavingWin(spLot);
        SavingWin *pSavingWin{};
        if(DataBase::upSavingWin) pSavingWin = DataBase::upSavingWin.get();
        if(pSavingWin != nullptr)
            connect(pSavingWin, SavingWin::selectedSlot, this, slotSaveLotAsDatabase);
    }
}
void MainWindow::slotSaveLotAsDatabase(const int selectedSlot)
{
    DataBase::MainWinHeight = height();
    DataBase::MainWinWidth = width();

    QString lotName{};
    shared_ptr<Lot> spLot = getCurrentLot();
    if(spLot) lotName = spLot->getLotName(); else return;

    if(selectedSlot == -1) DataBase::createLotDatabase(lotName);
    else DataBase::createOneWaferTables(lotName, selectedSlot);
}

void MainWindow::slotImportDatabase()
{
    QString strFilter{};
    QString fullFileName = QFileDialog::
            getOpenFileName(this, "Импортировать базу данных партии...",
                            "", "Файл базы данных (*.db)", &strFilter);

    if(!fullFileName.isEmpty())
    {
        QFileInfo FileInfo(fullFileName);
        //вычисление имени файла БД без пути и расширения
        QString dbFileName_NoPathNoExtension = FileInfo.completeBaseName();
        QString lotName = dbFileName_NoPathNoExtension;// + ".db";
        size_t lotNum = lotNumIncrement();

        shared_ptr<Lot> spLot = make_shared<Lot>();
        spLot->setLotNum(lotNum);
        spLot->setLotName(lotName);
        DataBase::queryLotData(spLot);
        //добавление партии в группу
        addLotToGroup(spLot);
        //создание вкладки партии и дабавление ее в центральный виджет
        addLotTab(lotNum, lotName);
        //запись данных партии в модель
        setLotDataInModel();
        //создание соединений с деревом
        TreeView *pTreeView = getCurrentTreeView();
        if(pTreeView != nullptr)
            createTreeViewConnections(pTreeView);

        //инкремент количества партий
        size_t lotCount = lotCountIncrement();
        QString MainWinTitle = g_MainWinTitle + ": количество партий - " + QString::number(lotCount);
        setWindowTitle(MainWinTitle);
        setMDIareaVisible();
    }
}
void MainWindow::slotOpenDatabaseConfig()
{
    QString strFilter{};
    QString fullFileName = QFileDialog::
            getOpenFileName(this, "Открыть файл базы данных ...",
                            "", "Файл базы данных (*.db)", &strFilter);

    if(!fullFileName.isEmpty())
    {
        QFileInfo FileInfo(fullFileName);
        //вычисление имени файла БД без пути и расширения
        QString dbLotFileName_NoPathNoExt = FileInfo.completeBaseName();
        DataBase::createConfigWin(dbLotFileName_NoPathNoExt);
    }
}
//-------------------------------------------------------------------------------------------------
