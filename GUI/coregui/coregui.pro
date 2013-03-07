#-------------------------------------------------
#
# Project created by QtCreator 2013-02-11T18:32:10
#
#-------------------------------------------------

QT       += core gui webkit designer designercomponents

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets


TARGET = coregui
TEMPLATE = app

# making standard shared library extension
QMAKE_EXTENSION_SHLIB = so
#CONFIG  -= app_bundle
OBJECTS_DIR = .obj
MOC_DIR = .moc
RCC_DIR = .rcc

include($$PWD/Views/Components/widgetbox/widgetbox.pri)

SOURCES += \
    mainwindow/imode.cpp \
    mainwindow/main.cpp \
    mainwindow/mainwindow.cpp \
    mainwindow/welcomemode.cpp \
    Views/designercomponents.cpp \
    mainwindow/taskselectorwidget.cpp \
    utils/ba_fancytabbar.cpp \
    utils/ba_stylehelper.cpp \
    utils/rootcanvas.cpp \
    Models/SimulationDataModel.cpp \
    Views/InstrumentView.cpp \
    Views/FitView.cpp \
    Views/SampleView.cpp \
    Views/SimulationView.cpp \
    Views/WelcomeView.cpp \
    Views/sampleeditor.cpp \
    Views/sampleeditorstack.cpp \
    Models/JobModel.cpp \
    Models/PythonScriptSampleBuilder.cpp \
    Views/JobView.cpp

HEADERS  += \
    mainwindow/imode.h \
    mainwindow/mainwindow.h \
    mainwindow/welcomemode.h \
    Views/designercomponents.h \
    mainwindow/taskselectorwidget.h \
    utils/ba_fancytabbar.h \
    utils/ba_stylehelper.h \
    utils/rootcanvas.h \
    Models/SimulationDataModel.h \
    Models/SelectionListModel.h \
    Views/FitView.h \
    Views/InstrumentView.h \
    Views/SampleView.h \
    Views/SimulationView.h \
    Views/WelcomeView.h \
    Views/sampleeditor.h \
    Views/sampleeditorstack.h \
    Models/JobModel.h \
    Models/PythonScriptSampleBuilder.h \
    Views/JobView.h

INCLUDEPATH += $$PWD/mainwindow $$PWD/utils $$PWD/welcomemanager $$PWD/samplemanager $$PWD/experimentmanager $$PWD/simulationmanager $$PWD/fitmanager
INCLUDEPATH += $$PWD/mainwindow $$PWD/utils $$PWD/Views $$PWD/Models

# visual style "Manhattan"
LIBS += $$PWD/../../lib/libqt-manhattan-style.so
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
MY_DEPENDENCY_LIB = BornAgainCore
MY_DEPENDENCY_DEST =$$PWD/../..
SONAME = so
for(dep, MY_DEPENDENCY_LIB) {
    LIBS += $${MY_DEPENDENCY_DEST}/lib/lib$${dep}.$${SONAME}
#    PRE_TARGETDEPS += $${MY_DEPENDENCY_DEST}/lib/lib$${dep}.$${SONAME}
}

# qt-designer components
#INCLUDEPATH += $$QMAKE_INCDIR_QT/QtDesigner

# ROOT libraries
MYROOT = $$(ROOTSYS)
isEmpty(MYROOT) {
  message("Warning, ROOTSYS environment variable doesn't exist, trying to guess location")
  ROOT_CONFIG_FILE = root-config
  ROOT_CONFIG_FILE_LOCATIONS = /opt/local /usr/local /usr
  for(dir, ROOT_CONFIG_FILE_LOCATIONS): isEmpty(MYROOT): exists($${dir}/bin/$${ROOT_CONFIG_FILE}): MYROOT = $${dir}
  isEmpty(MYROOT): error("Can't find" $${ROOT_CONFIG_FILE} "in" $${ROOT_CONFIG_FILE_LOCATIONS})
  message("Probable ROOTSYS is" $${MYROOT})
}
!isEmpty(MYROOT) {
  !exists($${MYROOT}/bin/root-config): error("No config file "$${MYROOT}/bin/root-config)
  INCLUDEPATH += $$system($${MYROOT}/bin/root-config --incdir)
  #LIBS += -L$$system($${MYROOT}/bin/root-config --libdir ) -lGui -lCore -lCint -lRIO -lHist -lGraf -lGraf3d -lGpad -lTree -lRint -lPostscript -lMatrix -lPhysics -lMathCore -lMathMore -lMinuit2 -lGeom -lEve -lRGL -lThread -lpthread -lm -ldl
  #LIBS += -L$$system($${MYROOT}/bin/root-config --libdir ) -lGui -lCore -lCint -lRIO -lHist -lGraf -lGraf3d -lGpad -lTree -lRint -lPostscript -lMatrix -lPhysics -lMathCore -lMathMore -lMinuit2 -lGeom -lEve -lRGL -lThread -lpthread -lm -ldl
  LIBS += $$system($${MYROOT}/bin/root-config --glibs )
  MYROOTCINT = $${MYROOT}/bin/rootcint
}


#FORMS += \
#    testform.ui

RESOURCES   += coregui.qrc

# python include and library flags:
pythonvers=$$system("python -c 'import sys; sys.stdout.write(sys.version[:3])'")
INCLUDEPATH += $$system("python -c 'import sys; sys.stdout.write(sys.prefix + \"/include/python\" + sys.version[:3])'")
LIBS += -L$$system("python -c 'import sys; sys.stdout.write(sys.prefix + \"/lib\" )'") -lboost_python -lpython$$pythonvers

lessThan(QT_MAJOR_VERSION, 5): LIBS += -lQtDesigner -lQtDesignerComponents -lQtXml
#lessThan(QT_MAJOR_VERSION, 5): LIBS += -lQtDesigner -lQtDesignerComponents -lQtScript -lQtXml

