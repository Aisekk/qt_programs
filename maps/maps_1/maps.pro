#-------------------------------------------------
#
# Project created by QtCreator 2018-12-18T08:34:55
#
#-------------------------------------------------

QT      += core gui
QT      += widgets printsupport
QT      += sql
QT      += sql widgets
#LIBS += libmysql.dll
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = maps
TEMPLATE = app
#CONFIG += console

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        MainWindow.cpp \
    HelpWin.cpp \
    Lot/Lot.cpp \
    Lot/LotGroup.cpp \
    Lot/TestElem.cpp \
    Lot/Wafer.cpp \
    Lot/Die.cpp \
    MapImage.cpp \
    Progress.cpp \
    TreeView.cpp \
    TabWidget.cpp \
    Splitter.cpp \
    Norms/BasicNorms.cpp \
    Norms/BigNorms.cpp \
    Norms/FauNorms035.cpp \
    Norms/IntervalWin.cpp \
    Norms/Norms06.cpp \
    Norms/SILnorms.cpp \
    Norms/SystemNorms.cpp \
    Norms/UserNorms.cpp \
    Reports/ReportData.cpp \
    Reports/ReportsWinPDF.cpp \
    Reports/ReportsWinTXT.cpp \
    Reports/SystemReports.cpp \
    Reports/TestElemData.cpp \
    Reports/TestElemReport.cpp \
    Reports/TestElemStatistics.cpp \
    Parser/Parser_4082.cpp \
    Parser/ParserResMap.cpp \
    Parser/TestInfo.cpp \
    Settings/GlobalSettingsWin.cpp \
    Settings/LocalSettingsWin.cpp \
    Settings/SystemSettings.cpp \
    Masking/MaskData.cpp \
    Masking/MaskWin.cpp \
    Masking/MaskWindow.cpp \
    Calculation/SystemCalculation.cpp \
    Database/SystemDataBase.cpp \
    Database/Breaker.cpp \
    Database/ConfigWin.cpp \
    Database/SavingWin.cpp

HEADERS += \
        MainWindow.h \
    HelpWin.h \
    MapImage.h \
    Progress.h \
    TreeView.h \
    Validator.h \
    TabWidget.h \
    Splitter.h \
    Lot/Die.h \
    Lot/Lot.h \
    Lot/LotGroup.h \
    Lot/TestElem.h \
    Lot/Wafer.h \
    Norms/BasicNorms.h \
    Norms/BigNorms.h \
    Norms/FauNorms035.h \
    Norms/IntervalWin.h \
    Norms/Norms06.h \
    Norms/SILnorms.h \
    Norms/SystemNorms.h \
    Norms/UserNorms.h \
    Norms/ZshNorms035.h \
    Reports/ReportData.h \
    Reports/ReportsWinPDF.h \
    Reports/ReportsWinTXT.h \
    Reports/SystemReports.h \
    Reports/TestElemData.h \
    Reports/TestElemReport.h \
    Reports/TestElemStatistics.h \
    Parser/Parser_4082.h \
    Parser/ParserResMap.h \
    Parser/TestInfo.h \
    Settings/GlobalSettingsWin.h \
    Settings/LocalSettingsWin.h \
    Settings/SystemSettings.h \
    Masking/MaskData.h \
    Masking/MaskWin.h \
    Masking/MaskWindow.h \
    Calculation/SystemCalculation.h \
    Database/SystemDataBase.h \
    Database/Breaker.h \
    Database/ConfigWin.h \
    Database/SavingWin.h \
    Types.h


RC_ICONS = gnome-statistics.ico
RESOURCES += \
    resource.qrc
