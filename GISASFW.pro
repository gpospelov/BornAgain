TEMPLATE = subdirs

SUBDIRS += \
    Core \
    ThirdParty/gtest \
#    ThirdParty/fftw++ \
    App \
    UnitTests/TestCore

TestCore.depends = ThirdParty/gtest ThirdParty/fftw++

# means that compilation will be in the listed order
CONFIG += ordered
