# -----------------------------------------------------------------------------
# qmake project file to compile libBornAgainFit
# -----------------------------------------------------------------------------
TARGET   = BornAgainFit
TEMPLATE = lib
CONFIG  += plugin # to remove versions from file name
QT      -= core gui
QMAKE_EXTENSION_SHLIB = so # making standard *.so extension
# CONFIG  += BORNAGAIN_PYTHON
CONFIG  += BORNAGAIN_ROOT

# -----------------------------------------------------------------------------
# source and headers
# -----------------------------------------------------------------------------
SOURCES += \
    Factory/src/MinimizerFactory.cpp \
    Factory/src/ROOTGSLNLSMinimizer.cpp \
    Factory/src/ROOTGSLSimAnMinimizer.cpp \
    Factory/src/ROOTMinimizer.cpp \
    Factory/src/ROOTMinimizerHelper.cpp \
    #Factory/src/FitSuiteObserverFactory.cpp \
    #Factory/src/FitSuitePrintObserver.cpp \
    #Factory/src/FitSuiteDrawObserver.cpp \
    #Factory/src/FitSuiteWriteTreeObserver.cpp

HEADERS += \
    Factory/inc/MinimizerFactory.h \
    Factory/inc/ROOTGSLNLSMinimizer.h \
    Factory/inc/ROOTGSLSimAnMinimizer.h \
    Factory/inc/ROOTMinimizer.h \
    Factory/inc/ROOTMinimizerFunction.h \
    Factory/inc/ROOTMinimizerHelper.h \
    #Factory/inc/FitSuiteObserverFactory.h \
    #Factory/inc/FitSuitePrintObserver.h \
    #Factory/inc/FitSuiteDrawObserver.h \
    #Factory/inc/FitSuiteWriteTreeObserver.h

INCLUDEPATH += $$PWD/Factory/inc
DEPENDPATH  += $$PWD/Factory/inc

contains(CONFIG, BORNAGAIN_PYTHON) {
   include($$PWD/python_module.pri)
}

# -----------------------------------------------------------------------------
# additional libraries
# -----------------------------------------------------------------------------
LIBS += $$PWD/../lib/libBornAgainCore.so

# -----------------------------------------------------------------------------
# Installing library into dedicated directory at the end of compilation
# -----------------------------------------------------------------------------
target.path = $$PWD/../lib
INSTALLS += target
QMAKE_DISTCLEAN += $$target.path/$(TARGET)
QMAKE_POST_LINK = (make install)

# -----------------------------------------------------------------------------
# common project settings
# -----------------------------------------------------------------------------
include($$PWD/../shared.pri)


