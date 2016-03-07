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
%include "doxygen.i"

#pragma SWIG nowarn=314 // print
 //#pragma SWIG nowarn=315 // nothing known about std::size_t // fixed by #ifndef in Types.h
#pragma SWIG nowarn=362 // operator=
 //#pragma SWIG nowarn=389 // operator[]
#pragma SWIG nowarn=473 // returning pointer in a director method (object ownership problem)
#pragma SWIG nowarn=503 // operator<<
 //#pragma SWIG nowarn=509 // overload ignored since reference=pointer



 // gives libBornAgainFit knowledge of the libBornAgainCore python module
 // %import "../../Core/PythonAPI/libBornAgainCore.i"

%include "std_complex.i"
%include "std_string.i"
%include "std_vector.i"
%include "std_shared_ptr.i"

 //%shared_ptr(ISampleBuilder)
 //%shared_ptr(IParametrized)
 //%shared_ptr(INamed)
 //%template(SampleBuilder_t) boost::shared_ptr<ISampleBuilder>;


%shared_ptr(ISampleBuilder)
%shared_ptr(IParameterizedShared)
%shared_ptr(INamedShared)
%shared_ptr(LayerRTCoefficients_t)
%shared_ptr(ProgressHandler_t)
%shared_ptr(IObserver)
%shared_ptr(IFitObserver)
 //%shared_ptr(FitSuite)


%feature("director");
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




// // fix SWIG warning 509, certain C++ overloads create ambiguities in Python
%ignore ParticleLayout::addInterferenceFunction(IInterferenceFunction *);
%ignore ParticleLayout::addInterferenceFunction(const IInterferenceFunction *);
%ignore MesoCrystal::MesoCrystal(IClusteredParticles*, IFormFactor*);
%ignore MesoCrystal::MesoCrystal(const IClusteredParticles*, const IFormFactor*);
%ignore Instrument::setDetectorResolutionFunction(IResolutionFunction2D*);
%ignore Instrument::setDetectorResolutionFunction(const IResolutionFunction2D*);

// taken from dev-tools/python-bindings/settings_fit.py
%ignore FitSuite::setOptions(const FitOptions&);
%ignore FitSuite::getOptions();


// fix smart pointer problem
//%ignore IFitObserver::notify(IObservable*);
//%ignore IFitObserver::update(FitSuite*);

// // problems with BasicVector3D.h
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



//! file containig additional exposers
#include "PythonFitExposer.h"



%}

%import(module="libBornAgainCore") "AttLimits.h"
%import(module="libBornAgainCore") "ICloneable.h"
%import(module="libBornAgainCore") "INamed.h"
%import(module="libBornAgainCore") "IParameterized.h"
%import(module="libBornAgainCore") "IObserver.h"




%include "IChiSquaredModule.h"
%include "IFitObserver.h"
%include "IFitStrategy.h"
%include "IIntensityFunction.h"
%include "IIntensityNormalizer.h"

%include "ISquaredFunction.h"

%include "IMinimizer.h"


%include "ChiSquaredModule.h"
%include "FitObject.h"
%include "FitOptions.h"
%include "FitParameter.h"

%include "FitSuite.h"
%include "FitSuiteObjects.h"
%include "FitSuiteParameters.h"




%include "MathFunctions.h"
%include "MinimizerFactory.h"
%include "MinimizerOptions.h"



 /*
%extend IFitObserver {
    void notify(std::shared_ptr<IObservable> subject)
    {
        ($self)->notify(subject.get());
    }
};
/**/

 // introduced because of FitCylindersAndPrisms example
%extend FitSuiteParameters {
    const FitParameter* __getitem__(std::string name) const
    {
        return (*($self))[name];
    }
    
    /* void __setitem__(std::string name, const FitParameter* val)
    {
        (*($self))[name] = *val_;
        }*/

    const FitParameter* __getitem__(size_t index) const
    {
        return (*($self))[index];
    }
    
    /*    void __setitem__(size_t index, const FitParameter* val)
    {
        (*($self))[index] = *val;
        }*/
 };
