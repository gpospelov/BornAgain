HEADERS +=  \ 
    PythonAPI/inc/PythonPlusplusFitHelper.h \ 
    PythonAPI/inc/AttLimits.pypp.h \
    PythonAPI/inc/ChiSquaredModule.pypp.h \
    PythonAPI/inc/FitSuite.pypp.h \
    PythonAPI/inc/IChiSquaredModule.pypp.h \
    PythonAPI/inc/IMinimizer.pypp.h \
    PythonAPI/inc/MinimizerFactory.pypp.h \
    PythonAPI/inc/ndimdata_t.pypp.h 

SOURCES +=  \ 
    PythonAPI/src/PythonModule.cpp \ 
    PythonAPI/src/AttLimits.pypp.cpp \
    PythonAPI/src/ChiSquaredModule.pypp.cpp \
    PythonAPI/src/FitSuite.pypp.cpp \
    PythonAPI/src/IChiSquaredModule.pypp.cpp \
    PythonAPI/src/IMinimizer.pypp.cpp \
    PythonAPI/src/MinimizerFactory.pypp.cpp \
    PythonAPI/src/ndimdata_t.pypp.cpp 

INCLUDEPATH += $$PWD/PythonAPI/inc 
DEPENDPATH  += $$PWD/PythonAPI/inc 

