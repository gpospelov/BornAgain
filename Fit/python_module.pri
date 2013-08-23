HEADERS +=  \ 
    PythonAPI/inc/PythonFitExposer.h \ 
    PythonAPI/inc/PythonFitList.h \ 
    PythonAPI/inc/AttLimits.pypp.h \
    PythonAPI/inc/ChiSquaredModule.pypp.h \
    PythonAPI/inc/FitSuite.pypp.h \
    PythonAPI/inc/FitSuiteParameters.pypp.h \
    PythonAPI/inc/IChiSquaredModule.pypp.h \
    PythonAPI/inc/IMinimizer.pypp.h \
    PythonAPI/inc/IOutputDataNormalizer.pypp.h \
    PythonAPI/inc/ISquaredFunction.pypp.h \
    PythonAPI/inc/MinimizerFactory.pypp.h \
    PythonAPI/inc/OutputDataNormalizer.pypp.h \
    PythonAPI/inc/OutputDataSimpleNormalizer.pypp.h \
    PythonAPI/inc/SquaredFunctionDefault.pypp.h \
    PythonAPI/inc/SquaredFunctionWhichOnlyWorks.pypp.h \
    PythonAPI/inc/SquaredFunctionWithGaussianError.pypp.h \
    PythonAPI/inc/SquaredFunctionWithSystematicError.pypp.h 

SOURCES +=  \ 
    PythonAPI/src/PythonModule.cpp \ 
    PythonAPI/src/AttLimits.pypp.cpp \
    PythonAPI/src/ChiSquaredModule.pypp.cpp \
    PythonAPI/src/FitSuite.pypp.cpp \
    PythonAPI/src/FitSuiteParameters.pypp.cpp \
    PythonAPI/src/IChiSquaredModule.pypp.cpp \
    PythonAPI/src/IMinimizer.pypp.cpp \
    PythonAPI/src/IOutputDataNormalizer.pypp.cpp \
    PythonAPI/src/ISquaredFunction.pypp.cpp \
    PythonAPI/src/MinimizerFactory.pypp.cpp \
    PythonAPI/src/OutputDataNormalizer.pypp.cpp \
    PythonAPI/src/OutputDataSimpleNormalizer.pypp.cpp \
    PythonAPI/src/SquaredFunctionDefault.pypp.cpp \
    PythonAPI/src/SquaredFunctionWhichOnlyWorks.pypp.cpp \
    PythonAPI/src/SquaredFunctionWithGaussianError.pypp.cpp \
    PythonAPI/src/SquaredFunctionWithSystematicError.pypp.cpp 

INCLUDEPATH += ./PythonAPI/inc 
DEPENDPATH  += ./PythonAPI/inc 
