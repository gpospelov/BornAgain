TEMPLATE = subdirs
CONFIG += ordered

SUBDIRS += \
    Core \
    ThirdParty/gtest \
    UnitTests/TestCore

TestCore.depends = ThirdParty/gtest

