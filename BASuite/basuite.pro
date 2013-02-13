#-------------------------------------------------
#
# Project created by QtCreator 2013-02-11T18:32:10
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = basuite
TEMPLATE = app

SOURCES += \
    appcore/fancytabwidget.cpp \
    appcore/imode.cpp \
    appcore/main.cpp \
    appcore/mainwindow.cpp \
    appcore/welcomemode.cpp \
    experimentmanager/experimentmanager.cpp \
    fitmanager/fitmanager.cpp \
    samplemanager/samplemanager.cpp \
    simulationmanager/simulationmanager.cpp \
#    utils/fancymainwindow.cpp \
    utils/fancytab.cpp \
    utils/fancytabbar.cpp \
#    utils/manhattanstyle.cpp \
#    utils/styleanimator.cpp \
#    utils/styledbar.cpp \
    utils/stylehelper.cpp \
    welcomemanager/welcomemanager.cpp

HEADERS  += \
    appcore/fancytabwidget.h \
    appcore/imode.h \
    appcore/mainwindow.h \
    appcore/welcomemode.h \
    experimentmanager/experimentmanager.h \
    fitmanager/fitmanager.h \
    samplemanager/samplemanager.h \
    simulationmanager/simulationmanager.h \
#    utils/fancymainwindow.h \
    utils/fancytab.h \
    utils/fancytabbar.h \
#    utils/manhattanstyle.h \
#    utils/styleanimator.h \
#    utils/styledbar.h \
    utils/stylehelper.h \
    welcomemanager/welcomemanager.h

INCLUDEPATH += $$PWD/utils $$PWD/appcore $$PWD/welcomemanager $$PWD/samplemanager $$PWD/experimentmanager $$PWD/simulationmanager $$PWD/fitmanager

#FORMS    += mainwindow.ui
