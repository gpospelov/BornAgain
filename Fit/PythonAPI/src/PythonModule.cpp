#include "Python.h"
#include "Macros.h"
GCC_DIAG_OFF(unused-parameter);
GCC_DIAG_OFF(missing-field-initializers);
#include "boost/python.hpp"
#include "boost/python/suite/indexing/vector_indexing_suite.hpp"
GCC_DIAG_ON(unused-parameter);
GCC_DIAG_ON(missing-field-initializers);

#include "AttLimits.pypp.h" 
#include "ChiSquaredModule.pypp.h" 
#include "FitSuite.pypp.h" 
#include "FitSuiteParameters.pypp.h" 
#include "IChiSquaredModule.pypp.h" 
#include "IMinimizer.pypp.h" 
#include "IOutputDataNormalizer.pypp.h" 
#include "ISquaredFunction.pypp.h" 
#include "MinimizerFactory.pypp.h" 
#include "OutputDataNormalizer.pypp.h" 
#include "OutputDataSimpleNormalizer.pypp.h" 
#include "PythonInterface_enumerations.pypp.h" 
#include "PythonInterface_free_functions.pypp.h" 
#include "SquaredFunctionDefault.pypp.h" 
#include "SquaredFunctionWhichOnlyWorks.pypp.h" 
#include "SquaredFunctionWithGaussianError.pypp.h" 
#include "SquaredFunctionWithSystematicError.pypp.h" 

BOOST_PYTHON_MODULE(libBornAgainFit){

    register_enumerations();
    register_AttLimits_class();
    register_IChiSquaredModule_class();
    register_ChiSquaredModule_class();
    register_FitSuite_class();
    register_FitSuiteParameters_class();
    register_IMinimizer_class();
    register_IOutputDataNormalizer_class();
    register_ISquaredFunction_class();
    register_MinimizerFactory_class();
    register_OutputDataNormalizer_class();
    register_OutputDataSimpleNormalizer_class();
    register_SquaredFunctionDefault_class();
    register_SquaredFunctionWhichOnlyWorks_class();
    register_SquaredFunctionWithGaussianError_class();
    register_SquaredFunctionWithSystematicError_class();
    register_free_functions();
}
