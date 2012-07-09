TEMPLATE = subdirs

SUBDIRS += \
    Core \
    ThirdParty/gtest \
    App \
    UnitTests/TestCore

TestCore.depends = ThirdParty/gtest

# means that compilation will be in the listed order
CONFIG += ordered

# special compiling mode for code profiling using gperftools
#CONFIG += GPERFTOOLS

