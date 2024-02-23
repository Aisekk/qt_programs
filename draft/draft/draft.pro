QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    bit_flags.cpp \
    class_initialization.cpp \
    file1.cpp \
    file2.cpp \
    main.cpp \
    mainwindow.cpp \
    object.cpp \
    operators.cpp \
    run_task_in_thread.cpp \
    static_word.cpp \
    static_word_2.cpp \
    unions.cpp

HEADERS += \
    abstract_class.h \
    arrays.h \
    auto.h \
    bit_flags.h \
    cast.h \
    class_initialization.h \
    constructor.h \
    constructors.h \
    constructors_gen.h \
    copy_algs.h \
    delete_this.h \
    directives.h \
    extern.h \
    file1.h \
    file2.h \
    foo.h \
    hash_heap.h \
    hash_table.h \
    header.h \
    init.h \
    initlist.h \
    ip_parsing.h \
    lambdas.h \
    literals.h \
    mainwindow.h \
    move.h \
    object.h \
    one_bool.h \
    operators.h \
    overflow.h \
    placement_new.h \
    pointers.h \
    print.h \
    pure_virtual_func_call.h \
    qt_object.h \
    reverse.h \
    romb_problem.h \
    run_task_in_thread.h \
    sets_tasks.h \
    sizeof.h \
    smart_ptrs.h \
    sort.h \
    static_obj.h \
    static_obj_include.h \
    static_word.h \
    static_word_2.h \
    stl_algs.h \
    stl_sorts.h \
    test_std_algs.h \
    unions.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
