// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      PythonAPI/libBornAgainFit.i
//! @brief     SWIG interface file for libBornAgainFit
//!
//! @homepage  http://apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

%module(directors="1") "libBornAgainFit"

%feature("autodoc");

//%feature("director");

 // gives libBornAgainFit knowledge of the libBornAgainCore python module
 // %import "../../Core/PythonAPI/libBornAgainCore.i"

%include "std_complex.i"
%include "std_string.i"
%include "std_vector.i"
%include "std_shared_ptr.i"

 // import list of shared pointers (common between Core and Fit)
%include "shared_pointers.i"

%include "doxygen_fit.i"
%include "warnings.i"
%include "ignores.i"



%include "directors.i"

 //%shared_ptr(ISampleBuilder)
 //%shared_ptr(IParametrized)
 //%shared_ptr(INamed)
 //%template(SampleBuilder_t) boost::shared_ptr<ISampleBuilder>;



 //%shared_ptr(FitSuite)



/*
%feature("director") IObserver;
%feature("director") IObservable;
%feature("director") IFitObserver;
%feature("director") IFitSuite;
/**/

// // from PythonCoreExposer.h
%template(vdouble1d_t) std::vector<double>;
%template(vdouble2d_t) std::vector< std::vector<double> >;
%template(vector_integer_t) std::vector<int >;
%template(vector_longinteger_t) std::vector<unsigned long int >;
%template(vector_complex_t) std::vector< std::complex<double> >;
%template(vector_string_t) std::vector<std::string>;








// fix smart pointer problem
//%ignore IFitObserver::notify(IObservable*);
//%ignore IFitObserver::update(FitSuite*);




#define SWIG_FILE_WITH_INIT

%{
#define SWIG_FILE_WITH_INIT
#define PY_ARRAY_UNIQUE_SYMBOL BORNAGAIN_PYTHONAPI_ARRAY
%}

%include "numpy.i"
%init %{
import_array();
%} 

#define GCCXML_SKIP_THIS 1
#define GCC_DIAG_OFF(x)  
#define GCC_DIAG_ON(x) 



#ifndef BORNAGAIN_PYTHON
#define BORNAGAIN_PYTHON
#endif





%import "WinDllMacros.h"




 //%import "INamed.h"
 //%import "IParameterized.h"
 //%import "ISample.h"
 //%import "IMaterial.h"
 //%import "IAxis.h"
 //%import "VariableBinAxis.h"
 //%import "ICompositeSample.h"
 //%import "IClusteredParticles.h"
 //%import "IShape2D.h"

 //%import "IFormFactor.h"
 //%import "IFormFactorDecorator.h"
 //%import "IFormFactorBorn.h"
 //%import "IDetector2D.h"
 //%import "RealParameterWrapper.h"
 //%import "IParticle.h"
 //%import "ParameterDistribution.h"
 //%import "SafePointerVector.h"

 //%import "Simulation.h"
 //%import "IHistogram.h"

 //%import "IPixelMap.h"
 //%import "SphericalDetector.h"


 //%import "IRoughness.h"

%{


#include "ChiSquaredModule.h"
#include "FitObject.h"
#include "FitOptions.h"
#include "FitParameter.h"
#include "FitSuite.h"
#include "FitSuiteObjects.h"
#include "FitSuiteParameters.h"
#include "IChiSquaredModule.h"
#include "IFitObserver.h"
#include "IFitStrategy.h"
#include "IIntensityFunction.h"
#include "IIntensityNormalizer.h"
#include "IMinimizer.h"
#include "INamed.h"
#include "IObserver.h"
#include "ISquaredFunction.h"
#include "MathFunctions.h"
#include "MinimizerFactory.h"
#include "MinimizerOptions.h"
#include "FitStrategyAdjustMinimizer.h"



//! file containig additional exposers
#include "PythonFitExposer.h"



%}

%import(module="libBornAgainCore") "AttLimits.h"
%import(module="libBornAgainCore") "ICloneable.h"
%import(module="libBornAgainCore") "INamed.h"
%import(module="libBornAgainCore") "IParameterized.h"
%import(module="libBornAgainCore") "IObserver.h"


%include "IMinimizer.h"

%include "IChiSquaredModule.h"
%include "IFitObserver.h"
%include "IFitStrategy.h"
%include "IIntensityFunction.h"
%include "IIntensityNormalizer.h"

%include "ISquaredFunction.h"


%include "ChiSquaredModule.h"
%include "FitObject.h"
%include "FitOptions.h"
%include "FitParameter.h"

%include "FitSuite.h"
%include "FitSuiteObjects.h"
%include "FitSuiteParameters.h"

%include "MathFunctions.h"

%include "MinimizerOptions.h"
%include "MinimizerFactory.h"


%include "FitStrategyAdjustMinimizer.h"

 // extends included at end because swig needs to know something about the extended classes beforehand
%include "extends.i"
