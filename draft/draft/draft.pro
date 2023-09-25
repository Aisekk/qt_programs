QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    file1.cpp \
    file2.cpp \
    main.cpp \
    mainwindow.cpp \
    object.cpp \
    operators.cpp \
    unions.cpp

HEADERS += \
    abstract_class.h \
    arrays.h \
    auto.h \
    const_char.h \
    constructors.h \
    delete_this.h \
    extern.h \
    file1.h \
    file2.h \
    foo.h \
    hash_heap.h \
    header.h \
    init.h \
    initlist.h \
    mainwindow.h \
    object.h \
    operators.h \
    placement_new.h \
    print.h \
    pure_virtual_func_call.h \
    reverse.h \
    romb_problem.h \
    sort.h \
    static_obj.h \
    static_obj_include.h \
    unions.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
