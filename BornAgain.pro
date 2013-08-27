TEMPLATE = subdirs

include($$PWD/shared.pri)

SUBDIRS += Core
SUBDIRS += ThirdParty/gtest
SUBDIRS += Tests/UnitTests/TestCore
TestCore.depends = ThirdParty/gtest

SUBDIRS += Tests/FunctionalTests/TestCore

#isEmpty(ROOT_FRAMEWORK) {
#    message("No ROOT installation found. Additional library libRootMinimizers.so will be compiled.")
    SUBDIRS += ThirdParty/RootMinimizers
#}

#SUBDIRS += ThirdParty/RootMathMore

SUBDIRS += Fit
SUBDIRS += Tests/FunctionalTests/TestFit

#!isEmpty(ROOT_FRAMEWORK) {
#    SUBDIRS += App
#}


# compilation in lister order
CONFIG += ordered

