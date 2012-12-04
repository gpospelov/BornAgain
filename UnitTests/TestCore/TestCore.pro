###############################################################################
# qmake project file to compile and run unit test of ScattCore library
###############################################################################
TEMPLATE = app
CONFIG  -= qt app_bundle
CONFIG  += console build_all
QT      -= core gui

# including common project properties
include($$PWD/../../shared.pri)

SOURCES += main.cpp

HEADERS += \
	AxisDoubleTest.h \
    BeamTest.h \
    DetectorTest.h \
    ExperimentTest.h \
    MaskTest.h \
    OutputDataTest.h \
    OutputDataIteratorTest.h \
    GISASExperimentTest.h

OBJECTS_DIR = obj

INCLUDEPATH += ../../Core/Algorithms/inc ../../Core/FormFactors/inc ../../Core/Geometry/inc ../../Core/Samples/inc ../../Core/Tools/inc ../../ThirdParty/gtest/gtest-1.6.0/include
DEPENDPATH += ../../Core/Algorithms/inc ../../Core/FormFactors/inc ../../Core/Geometry/inc ../../Core/Samples/inc ../../Core/Tools/inc ../../ThirdParty/gtest/gtest-1.6.0/include
DEPENDPATH += $$PWD/.

LIBS = -L/opt/local/lib -lfftw3

CONFIG(JCNS) {
  #LIBS -= -lfftw3
  #LIBS += -Bstatic -lfftw3 -Bdynamic # request for static (with fPIC option)
  # "-lfftw3f" - with fPIC option, "-lfftw3" - without fPIC option
  LIBS = -L/usr/users/jcns/pospelov/software/lib -lfftw3
}

###############################################################################
# generating package dependency flags
###############################################################################
MY_DEPENDENCY_LIB = gtest ScattCore
MY_DEPENDENCY_DEST =$$PWD/../..
SONAME = so
# INCLUDEPATH += $${MY_DEPENDENCY_DEST}/inc
for(dep, MY_DEPENDENCY_LIB) {
    LIBS += $${MY_DEPENDENCY_DEST}/lib/lib$${dep}.$${SONAME}
    PRE_TARGETDEPS += $${MY_DEPENDENCY_DEST}/lib/lib$${dep}.$${SONAME}
#    INCLUDEPATH += $${MY_DEPENDENCY_DEST}/inc/$${dep}
}


# some hack that might be required for linux... under investigation
#LIBS += -lpthread
#LDFLAGS = -L/lib64
#QMAKE_CXXFLAGS += -pthread

###############################################################################
# attempt to compile project dependencies not from the top
###############################################################################
#PRE_TARGETDEPS += $$PWD/../../ThirdParty/gtest/libgtest.a
#makelibs.target = $$PWD/../../ThirdParty/gtest/libgtest.a
#makelibs.commands = (cd $$PWD/../../ThirdParty/gtest; qmake; make)
#makelibs.depends = FORCE
#QMAKE_EXTRA_TARGETS += makelibs


###############################################################################
# runs automatically tests right after linking
###############################################################################
QMAKE_POST_LINK = ./$(TARGET)
