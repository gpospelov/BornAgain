%module(directors="1") "libBornAgainFit"



#pragma SWIG nowarn=314 // print
 //#pragma SWIG nowarn=315 // nothing known about std::size_t // fixed by #ifndef in Types.h
#pragma SWIG nowarn=362 // operator=
 //#pragma SWIG nowarn=389 // operator[]
#pragma SWIG nowarn=473 // returning pointer in a director method (object ownership problem)
#pragma SWIG nowarn=503 // operator<<
 //#pragma SWIG nowarn=509 // overload ignored since reference=pointer






%include "std_complex.i"
%include "std_string.i"
%include "std_vector.i"
%include "boost_shared_ptr.i"

 //%shared_ptr(ISampleBuilder)
 //%shared_ptr(IParametrized)
 //%shared_ptr(INamed)
 //%template(SampleBuilder_t) boost::shared_ptr<ISampleBuilder>;

// from PythonCoreExposer.h
%template(vdouble1d_t) std::vector<double>;
%template(vdouble2d_t) std::vector< std::vector<double> >;
%template(vector_integer_t) std::vector<int >;
%template(vector_longinteger_t) std::vector<unsigned long int >;
%template(vector_complex_t) std::vector< std::complex<double> >;
%template(vector_string_t) std::vector<std::string>;




// fix SWIG warning 509, certain C++ overloads create ambiguities in Python
%ignore ParticleLayout::addInterferenceFunction(IInterferenceFunction *);
%ignore ParticleLayout::addInterferenceFunction(const IInterferenceFunction *);
%ignore MesoCrystal::MesoCrystal(IClusteredParticles*, IFormFactor*);
%ignore MesoCrystal::MesoCrystal(const IClusteredParticles*, const IFormFactor*);
%ignore Instrument::setDetectorResolutionFunction(IResolutionFunction2D*);
%ignore Instrument::setDetectorResolutionFunction(const IResolutionFunction2D*);

// problems with BasicVector3D.h
namespace Geometry {

%ignore BasicVector3D<std::complex<double> >::angle(const BasicVector3D<std::complex<double> >&) const;
%ignore BasicVector3D<std::complex<double> >::perp2(const BasicVector3D<std::complex<double> >&) const;
%ignore BasicVector3D<std::complex<double> >::sin2Theta() const;
%ignore BasicVector3D<std::complex<double> >::cosTheta() const;
  %ignore BasicVector3D<std::complex<double> >::theta() const;
%ignore BasicVector3D<std::complex<double> >::phi() const;
  %ignore BasicVector3D<std::complex<double> >::rotated(double, const BasicVector3D<std::complex<double> >&) const;
%ignore BasicVector3D<std::complex<double> >::rotatedX(double) const;
%ignore BasicVector3D<std::complex<double> >::rotatedY(double) const;
%ignore BasicVector3D<std::complex<double> >::rotatedZ(double) const;

  %ignore BasicVector3D<std::complex<double> >::cross(const BasicVector3D<std::complex<double> >&) const;
  %ignore BasicVector3D<std::complex<double> >::perp(const BasicVector3D<std::complex<double> >&) const;

  %ignore BasicVector3D<double>::rotated(double, const BasicVector3D<double>&) const;
%ignore BasicVector3D<double>::rotatedX(double) const;
%ignore BasicVector3D<double>::rotatedY(double) const;
%ignore BasicVector3D<double>::rotatedZ(double) const;
}



// %template(vector_realparameter_t) std::vector<RealParameterWrapper>;   // SWIG issue: fails to build ATM
//        %template( std::vector<ParameterSample> vector_ParameterSample_t;




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
%import "ICloneable.h"
%import "AttLimits.h"


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

#include "INamed.h"
#include "IObserver.h"
#include "IChiSquaredModule.h"
#include "IMinimizer.h"
#include "ChiSquaredModule.h"
#include "FitSuite.h"
#include "FitParameter.h"
#include "FitSuiteParameters.h"
#include "FitSuiteObjects.h"
#include "MinimizerFactory.h"
#include "MathFunctions.h"
#include "MinimizerOptions.h"
#include "ISquaredFunction.h"
#include "IIntensityNormalizer.h"
#include "IFitStrategy.h"
#include "IIntensityFunction.h"
#include "FitStrategyAdjustParameters.h"
#include "FitStrategyAdjustMinimizer.h"
#include "IFitObserver.h"

//! file containig additional exposers
#include "PythonFitExposer.h"


%}

%include "INamed.h"

%import "IParameterized.h"

%include "IObserver.h"
%include "IChiSquaredModule.h"
%include "IMinimizer.h"
%include "ChiSquaredModule.h"
%include "FitSuite.h"
%include "FitParameter.h"
%include "FitSuiteParameters.h"
%include "FitSuiteObjects.h"
%include "MinimizerFactory.h"
%include "MathFunctions.h"
%include "MinimizerOptions.h"
%include "ISquaredFunction.h"
%include "IIntensityNormalizer.h"
%include "IFitStrategy.h"
%include "IIntensityFunction.h"
%include "FitStrategyAdjustParameters.h"
%include "FitStrategyAdjustMinimizer.h"
%include "IFitObserver.h"


