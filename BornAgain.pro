TEMPLATE = subdirs

include($$PWD/shared.pri)

SUBDIRS += Core
SUBDIRS += ThirdParty/gtest
SUBDIRS += Tests/UnitTests/TestCore
SUBDIRS += Tests/FunctionalTests/TestCore
SUBDIRS += ThirdParty/RootMinimizers
SUBDIRS += Fit
SUBDIRS += Tests/FunctionalTests/TestFit

!isEmpty(ROOT_FRAMEWORK): SUBDIRS += App

# compilation in lister order
CONFIG += ordered

