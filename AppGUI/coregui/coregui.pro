#-------------------------------------------------
#
# Project created by QtCreator 2013-02-11T18:32:10
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = coregui
TEMPLATE = app


# making standard shared library extension
QMAKE_EXTENSION_SHLIB = so
CONFIG  -= app_bundle
OBJECTS_DIR = obj
MOC_DIR = obj
UI_DIR  = obj
RCC_DIR = obj

SOURCES += \
    mainwindow/imode.cpp \
    mainwindow/main.cpp \
    mainwindow/mainwindow.cpp \
    mainwindow/welcomemode.cpp \
    experimentmanager/experimentmanager.cpp \
    fitmanager/fitmanager.cpp \
    samplemanager/samplemanager.cpp \
    simulationmanager/simulationmanager.cpp \
    welcomemanager/welcomemanager.cpp \
    samplemanager/designercomponents.cpp \
    mainwindow/taskselectorwidget.cpp \
    utils/ba_fancytabbar.cpp \
    utils/ba_stylehelper.cpp

HEADERS  += \
    mainwindow/imode.h \
    mainwindow/mainwindow.h \
    mainwindow/welcomemode.h \
    experimentmanager/experimentmanager.h \
    fitmanager/fitmanager.h \
    samplemanager/samplemanager.h \
    simulationmanager/simulationmanager.h \
    welcomemanager/welcomemanager.h \
    samplemanager/designercomponents.h \
    mainwindow/taskselectorwidget.h \
    utils/ba_fancytabbar.h \
    utils/ba_stylehelper.h

INCLUDEPATH += $$PWD/mainwindow $$PWD/utils $$PWD/welcomemanager $$PWD/samplemanager $$PWD/experimentmanager $$PWD/simulationmanager $$PWD/fitmanager
LIBS += $$PWD/../../lib/libqt-manhattan-style.so
INCLUDEPATH += $$PWD/../externals/qt-manhattan-style
