TEMPLATE = subdirs

include($$PWD/shared.pri)

SUBDIRS += \
    Core \
    ThirdParty/gtest \
    App \
    Tests/UnitTests/TestCore

TestCore.depends = ThirdParty/gtest
TestCore.depends = ThirdParty/gtest

# means that compilation will be in the listed order
CONFIG += ordered


