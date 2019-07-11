#-------------------------------------------------
#
# Project created by QtCreator 2019-03-13T11:39:18
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = StockMonitor
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
    addstock.cpp \
    basebutton.cpp \
    baseshadowdialog.cpp \
    capsulestock.cpp \
    main.cpp \
    mainmenu.cpp \
    mainwindow.cpp \
    menubutton.cpp \
    roundedbutton.cpp \
    stockinfo.cpp \
    stockitem.cpp \
    stockwidget.cpp \
    textbutton.cpp

HEADERS += \
    addstock.h \
    basebutton.h \
    baseshadowdialog.h \
    capsulestock.h \
    mainmenu.h \
    mainwindow.h \
    menubutton.h \
    roundedbutton.h \
    stockinfo.h \
    stockitem.h \
    stockwidget.h \
    textbutton.h

FORMS += \
    addstock.ui \
    mainmenu.ui \
    mainwindow.ui \
    stockitem.ui \
    stockwidget.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resource.qrc
