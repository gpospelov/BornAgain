TEMPLATE = subdirs

SUBDIRS += \
    Core \
    ThirdParty/gtest \
    UnitTests/TestCore

TestCore.depends = ThirdParty/gtest

# means that compilation will be in the listed order
CONFIG += ordered
