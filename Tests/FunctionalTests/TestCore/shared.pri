CONFIG  += console
CONFIG  -= qt
CONFIG  -= app_bundle
QT      -= core gui

include($$PWD/../../../shared.pri)

#CORE = $$PWD/../../../Core
#CORE_HEADERS = $${CORE}/Algorithms/inc $${CORE}/FormFactors/inc $${CORE}/Geometry/inc $${CORE}/Samples/inc $${CORE}/Tools/inc
#INCLUDEPATH += $${CORE_HEADERS}
#DEPENDPATH += $${CORE_HEADERS}

###############################################################################
# generating package dependency flags
###############################################################################
MY_DEPENDENCY_LIB = ScattCore
MY_DEPENDENCY_DEST =$$PWD/../../..
SONAME = so
for(dep, MY_DEPENDENCY_LIB) {
    LIBS += $${MY_DEPENDENCY_DEST}/lib/lib$${dep}.$${SONAME}
    PRE_TARGETDEPS += $${MY_DEPENDENCY_DEST}/lib/lib$${dep}.$${SONAME}
}

QMAKE_CXXFLAGS_RELEASE += -DSTANDALONE
QMAKE_CXXFLAGS_DEBUG += -DSTANDALONE

