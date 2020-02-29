QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    BackgroundColorDelegate.cpp \
    DigitalClock.cpp \
    ExecutorDelegat.cpp \
    LoggingCategories.cpp \
    LoginDialog.cpp \
    MainTableView.cpp \
    MainWindow.cpp \
    MenuDelegat.cpp \
    NetworkManager.cpp \
    PlayButtonDelegat.cpp \
    SignupDialog.cpp \
    Task.cpp \
    TasksModel.cpp \
    TasksSortFilterProxyModel.cpp \
    TimeDelta.cpp \
    TimerClockDelegat.cpp \
    TitleDelegat.cpp \
    main.cpp

HEADERS += \
    BackgroundColorDelegate.h \
    DigitalClock.h \
    ExecutorDelegat.h \
    LoggingCategories.h \
    LoginDialog.h \
    MainTableView.h \
    MainWindow.h \
    MenuDelegat.h \
    NetworkManager.h \
    PlayButtonDelegat.h \
    SignupDialog.h \
    Task.h \
    TasksModel.h \
    TasksSortFilterProxyModel.h \
    TimeDelta.h \
    TimerClockDelegat.h \
    TitleDelegat.h \
    config.h

#FORMS += \
#    widget.ui

QT += network

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
