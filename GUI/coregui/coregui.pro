# -----------------------------------------------------------------------------
# qmake project file to compile GUI core
# -----------------------------------------------------------------------------
QT       += core gui script webkit webkitwidgets designer designercomponents
#QT       += core gui script webkit webkitwidgets
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
TARGET = coregui
TEMPLATE = app

#CONFIG  -= app_bundle
#CONFIG += BORNAGAIN_ROOT BORNAGAIN_PYTHON

include($$PWD/../../shared.pri)

include($$PWD/Views/Components/widgetbox/widgetbox.pri)
include($$PWD/Views/Components/SampleDesigner/SampleDesigner.pri)
include($$PWD/qttools/qtpropertybrowser/qtpropertybrowser.pri)

SOURCES += \
    mainwindow/main.cpp \
    mainwindow/mainwindow.cpp \
    mainwindow/taskselectorwidget.cpp \
    utils/ba_fancytabbar.cpp \
    utils/ba_stylehelper.cpp \
    utils/rootcanvas.cpp \
    Models/SimulationDataModel.cpp \
    Views/InstrumentView.cpp \
    Views/FitView.cpp \
    Views/SampleView.cpp \
    Views/SampleViewComponents.cpp \
    Views/SimulationView.cpp \
    Views/WelcomeView.cpp \
    Models/JobModel.cpp \
    Models/PythonScriptSampleBuilder.cpp \
    Views/JobView.cpp \
    Views/PyScriptView.cpp \
    utils/PyScriptSyntaxHighlighter.cpp

HEADERS  += \
    mainwindow/mainwindow.h \
    mainwindow/taskselectorwidget.h \
    utils/ba_fancytabbar.h \
    utils/ba_stylehelper.h \
    utils/rootcanvas.h \
    Models/SimulationDataModel.h \
    Models/SelectionListModel.h \
    Views/FitView.h \
    Views/InstrumentView.h \
    Views/SampleView.h \
    Views/SampleViewComponents.h \
    Views/SimulationView.h \
    Views/WelcomeView.h \
    Models/JobModel.h \
    Models/PythonScriptSampleBuilder.h \
    Views/JobView.h \
    Views/PyScriptView.h \
    utils/PyScriptSyntaxHighlighter.h

RESOURCES   += coregui.qrc

FORMS += \
    form.ui

myIncludes = $$PWD/mainwindow $$PWD/utils $$PWD/Views $$PWD/Models

# -----------------------------------------------------------------------------
# dependencies
# -----------------------------------------------------------------------------
DEPENDPATH  += $$myIncludes
INCLUDEPATH += $$myIncludes
INCLUDEPATH *= $$EIGEN_INCLUDE_DIR
INCLUDEPATH *= $$BOOST_INCLUDE_DIR
INCLUDEPATH += $$BornAgainCore_INCLUDE_DIR
INCLUDEPATH += $$ROOT_INCLUDE_DIR
INCLUDEPATH += $$PYTHON_INCLUDE_DIR
LIBS += $$BOOST_LIBRARY $$BornAgainCore_LIBRARY $$ROOT_LIBRARY $$PYTHON_LIBRARY

LIBS += $$PWD/../../lib/libManhattanStyle.so
INCLUDEPATH += $$PWD/../externals/qt-manhattan-style
LIBS += $$PWD/../../lib/libQtRoot.so $$PWD/../../lib/libGQt.so
INCLUDEPATH += $$PWD/../externals/qt-root/inc

lessThan(QT_MAJOR_VERSION, 5): LIBS += -lQtDesigner -lQtDesignerComponents -lQtXml
