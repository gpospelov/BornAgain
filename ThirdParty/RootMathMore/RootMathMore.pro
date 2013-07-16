TARGET   = RootMathMore
TEMPLATE = lib
QT      -= core gui
macx|unix {
  QMAKE_EXTENSION_SHLIB = so # making standard *.so extension
  CONFIG  += plugin # to remove versions from file name
}
CONFIG  += BORNAGAIN_ROOT

include(../../shared.pri)

SOURCES += \
    src/GSLMinimizer.cxx \
    src/GSLMinimizer1D.cxx \
    src/MultiNumGradFunction.cxx \
    src/GSLSimAnnealing.cxx \
    src/GSLRndmEngines.cxx \
    src/Derivator.cxx \
    src/GSLDerivator.cxx

HEADERS += \
    inc/GSLMinimizer.h \
    inc/GSLMinimizer1D.h \
    inc/GSLSimAnnealing.h \
    inc/GSLMultiFitFunctionWrapper.h \
    inc/GSLMultiFitFunctionAdapter.h \
    inc/GSLMultiFit.h \
    inc/GSLMultiMinimizer.h \
    inc/GSLMultiMinFunctionWrapper.h \
    inc/GSLMultiMinFunctionAdapter.h \
    inc/GSLFunctionWrapper.h \
    inc/MultiNumGradFunction.h \
    inc/GSLRngWrapper.h \
    inc/GSLRndmEngines.h \
    inc/Derivator.h \
    inc/GSLDerivator.h

INCLUDEPATH += inc

# -----------------------------------------------------------------------------
# Installing library into dedicated directory at the end of compilation
# -----------------------------------------------------------------------------
target.path = $$PWD/../../lib
INSTALLS += target
QMAKE_DISTCLEAN += $$target.path/$(TARGET)
isEmpty(MAKEFILE): MAKEFILE="Makefile"
QMAKE_POST_LINK = $$MAKE_COMMAND -f $${MAKEFILE} install