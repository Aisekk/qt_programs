#-------------------------------------------------
#
# Project created by QtCreator 2019-10-18T15:08:47
#
#-------------------------------------------------

QT       += core gui
QT += multimedia
QT += multimedia multimediawidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = video
TEMPLATE = app

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
    VideoWidget.cpp \
    PopUpWidget.cpp \
    VideoSurface.cpp \
    Filter.cpp \
    VideoProducer.cpp

HEADERS += \
        MainWindow.h \
    VideoWidget.h \
    PopUpWidget.h \
    VideoSurface.h \
    Filter.h \
    VideoProducer.h

RESOURCES += \
    resource.qrc
