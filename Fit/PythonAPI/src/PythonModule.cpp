#include "Python.h"
#include "Macros.h"
GCC_DIAG_OFF(unused-parameter)
GCC_DIAG_OFF(missing-field-initializers)
#include "boost/python.hpp"
GCC_DIAG_ON(unused-parameter)
GCC_DIAG_ON(missing-field-initializers)
#include "FitOptions.pypp.h"
#include "FitSuiteObjects.pypp.h"
#include "IChiSquaredModule.pypp.h"
#include "FitStrategyDefault.pypp.h"
#include "IntensityFunctionLog.pypp.h"
#include "IntensityNormalizer.pypp.h"
#include "FitStrategyFixParameters.pypp.h"
#include "FitStrategyAdjustParameters.pypp.h"
#include "SquaredFunctionGaussianError.pypp.h"
#include "IFitStrategy.pypp.h"
#include "MinimizerFactory.pypp.h"
#include "FitSuite.pypp.h"
#include "IMinimizer.pypp.h"
#include "IntensityScaleAndShiftNormalizer.pypp.h"
#include "ISquaredFunction.pypp.h"
#include "SquaredFunctionSimError.pypp.h"
#include "FitStrategyAdjustMinimizer.pypp.h"
#include "FitParameter.pypp.h"
#include "IFitObserver.pypp.h"
#include "SquaredFunctionDefault.pypp.h"
#include "ChiSquaredModule.pypp.h"
#include "SquaredFunctionMeanSquaredError.pypp.h"
#include "IIntensityNormalizer.pypp.h"
#include "FitSuiteParameters.pypp.h"
#include "FitStrategyReleaseParameters.pypp.h"
#include "MinimizerOptions.pypp.h"
#include "IIntensityFunction.pypp.h"
#include "IntensityFunctionSqrt.pypp.h"
#include "FitObject.pypp.h"
#include "SquaredFunctionSystematicError.pypp.h"
#include "INamed.pypp.h"

BOOST_PYTHON_MODULE(libBornAgainFit){
    boost::python::docstring_options doc_options(true, true, false);

    register_IChiSquaredModule_class();
    register_ChiSquaredModule_class();
    register_INamed_class();
    register_IIntensityNormalizer_class();
    register_FitObject_class();
    register_FitOptions_class();
    register_FitParameter_class();
    register_IFitStrategy_class();
    register_FitStrategyAdjustMinimizer_class();
    register_FitStrategyAdjustParameters_class();
    register_FitStrategyDefault_class();
    register_FitStrategyFixParameters_class();
    register_FitStrategyReleaseParameters_class();
    register_FitSuite_class();
    register_FitSuiteObjects_class();
    register_FitSuiteParameters_class();
    register_IFitObserver_class();
    register_IIntensityFunction_class();
    register_IMinimizer_class();
    register_ISquaredFunction_class();
    register_IntensityFunctionLog_class();
    register_IntensityFunctionSqrt_class();
    register_IntensityNormalizer_class();
    register_IntensityScaleAndShiftNormalizer_class();
    register_MinimizerFactory_class();
    register_MinimizerOptions_class();
    register_SquaredFunctionDefault_class();
    register_SquaredFunctionGaussianError_class();
    register_SquaredFunctionMeanSquaredError_class();
    register_SquaredFunctionSimError_class();
    register_SquaredFunctionSystematicError_class();
}
