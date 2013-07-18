TEMPLATE = subdirs

include($$PWD/shared.pri)

SUBDIRS += Core ThirdParty/gtest

macx|unix {
  ROOT = $$system(root-config --prefix)
}
win32 {
#  ROOT = "C:/root"
}
isEmpty(ROOT) {
    message("No ROOT installation found. Fitting will not be available.")
}
!isEmpty(ROOT) SUBDIRS += ThirdParty/RootMathMore Fit App

SUBDIRS += Tests/UnitTests/TestCore
SUBDIRS += Tests/FunctionalTests/TestCore
SUBDIRS += Tests/FunctionalTests/TestFit


TestCore.depends = ThirdParty/gtest
TestCore.depends = ThirdParty/gtest

CONFIG += ordered # compilation in lister order

