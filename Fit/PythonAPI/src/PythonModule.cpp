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
#include "IChiSquaredModule.pypp.h" 
#include "IMinimizer.pypp.h" 
#include "MinimizerFactory.pypp.h" 
#include "ndimdata_t.pypp.h" 

BOOST_PYTHON_MODULE(libBornAgainFit){

    register_AttLimits_class();
    register_IChiSquaredModule_class();
    register_ChiSquaredModule_class();
    register_FitSuite_class();
    register_IMinimizer_class();
    register_MinimizerFactory_class();
    register_ndimdata_t_class();
}
