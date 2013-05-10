# -----------------------------------------------------------------------------
# qmake project file to compile GUI core
# -----------------------------------------------------------------------------

QT       += core gui webkit webkitwidgets designer designercomponents
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
TARGET = coregui
TEMPLATE = app
QMAKE_EXTENSION_SHLIB = so
#CONFIG  -= app_bundle
CONFIG += BORNAGAIN_ROOT BORNAGAIN_PYTHON


include($$PWD/Views/Components/widgetbox/widgetbox.pri)
include($$PWD/Views/Components/SampleEditor/SampleEditor.pri)

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

INCLUDEPATH += $$PWD/mainwindow $$PWD/utils $$PWD/Views $$PWD/Models

# visual style "Manhattan"
LIBS += $$PWD/../../lib/libManhattanStyle.so
INCLUDEPATH += $$PWD/../externals/qt-manhattan-style

## ROOT libraries integration
LIBS += $$PWD/../../lib/libQtRoot.so $$PWD/../../lib/libGQt.so
INCLUDEPATH += $$PWD/../externals/qt-root/inc

# ROOT libraries integration
#LIBS += $$PWD/../../lib/libQtRoot.so /Users/pospelov/nest/software/root/qtroot/qtroot/libGQt.dylib
#INCLUDEPATH += /Users/pospelov/nest/software/root/qtroot/qtroot/qt/inc

INCLUDEPATH += $$PWD/../../Core/Algorithms/inc \
    $$PWD/../../Core/Fitting/inc \
    $$PWD/../../Core/FormFactors/inc \
    $$PWD/../../Core/Geometry/inc \
    $$PWD/../../Core/Samples/inc \
    $$PWD/../../Core/Tools/inc

# -----------------------------------------------------------------------------
# generating package dependency flags
# -----------------------------------------------------------------------------
LIBS += $$PWD/../../lib/libBornAgainCore.so


## ROOT libraries
#MYROOT = $$(ROOTSYS)
#isEmpty(MYROOT) {
#  message("Warning, ROOTSYS environment variable doesn't exist, trying to guess location")
#  ROOT_CONFIG_FILE = root-config
#  ROOT_CONFIG_FILE_LOCATIONS = /opt/local /usr/local /usr
#  for(dir, ROOT_CONFIG_FILE_LOCATIONS): isEmpty(MYROOT): exists($${dir}/bin/$${ROOT_CONFIG_FILE}): MYROOT = $${dir}
#  isEmpty(MYROOT): error("Can't find" $${ROOT_CONFIG_FILE} "in" $${ROOT_CONFIG_FILE_LOCATIONS})
#  message("Probable ROOTSYS is" $${MYROOT})
#}
#!isEmpty(MYROOT) {
#  !exists($${MYROOT}/bin/root-config): error("No config file "$${MYROOT}/bin/root-config)
#  INCLUDEPATH += $$system($${MYROOT}/bin/root-config --incdir)
#  #LIBS += -L$$system($${MYROOT}/bin/root-config --libdir ) -lGui -lCore -lCint -lRIO -lHist -lGraf -lGraf3d -lGpad -lTree -lRint -lPostscript -lMatrix -lPhysics -lMathCore -lMathMore -lMinuit2 -lGeom -lEve -lRGL -lThread -lpthread -lm -ldl
#  #LIBS += -L$$system($${MYROOT}/bin/root-config --libdir ) -lGui -lCore -lCint -lRIO -lHist -lGraf -lGraf3d -lGpad -lTree -lRint -lPostscript -lMatrix -lPhysics -lMathCore -lMathMore -lMinuit2 -lGeom -lEve -lRGL -lThread -lpthread -lm -ldl
#  LIBS += $$system($${MYROOT}/bin/root-config --glibs )
#  MYROOTCINT = $${MYROOT}/bin/rootcint
#}

RESOURCES   += coregui.qrc

# python include and library flags:
pythonvers=$$system("python -c 'import sys; sys.stdout.write(sys.version[:3])'")
INCLUDEPATH += $$system("python -c 'import sys; sys.stdout.write(sys.prefix + \"/include/python\" + sys.version[:3])'")
LIBS += -L$$system("python -c 'import sys; sys.stdout.write(sys.prefix + \"/lib\" )'") -lboost_python -lpython$$pythonvers

lessThan(QT_MAJOR_VERSION, 5): LIBS += -lQtDesigner -lQtDesignerComponents -lQtXml


# -----------------------------------------------------------------------------
# general project settings
# -----------------------------------------------------------------------------
include($$PWD/../../shared.pri)
INCLUDEPATH -= /opt/local/include

FORMS += \
    form.ui
