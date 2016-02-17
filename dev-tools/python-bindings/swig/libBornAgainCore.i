%module(directors="1") "libBornAgainCore"



#pragma SWIG nowarn=314 // print
#pragma SWIG nowarn=315 // nothing known about std::size_t // fixed by #ifndef in Types.h
#pragma SWIG nowarn=362 // operator=
 //#pragma SWIG nowarn=389 // operator[]
#pragma SWIG nowarn=473 // returning pointer in a director method (object ownership problem)
#pragma SWIG nowarn=503 // operator<<
 //#pragma SWIG nowarn=509 // overload ignored since reference=pointer


%feature("director");

 /*
%feature("director") IAbstractParticle;
%feature("director") IAxis;
%feature("director") ICloneable;
%feature("director") IClusteredParticles;
%feature("director") ICompositeSample;
%feature("director") IDetector2D;
%feature("director") ILayout;
%feature("director") IFormFactor;
%feature("director") IFormFactorBorn;
%feature("director") IFormFactorDecorator;
%feature("director") IHistogram;
%feature("director") IInterferenceFunction;
%feature("director") IntensityDataFunctions;
%feature("director") IntensityDataIOFactory;
%feature("director") IMaterial;
%feature("director") Instrument;
%feature("director") InterferenceFunction1DLattice;
%feature("director") InterferenceFunctionRadialParaCrystal;
%feature("director") InterferenceFunction2DLattice;
%feature("director") InterferenceFunction2DParaCrystal;
%feature("director") InterferenceFunctionNone;
%feature("director") IObserver;
%feature("director") IParameterized;
%feature("director") IParticle;
%feature("director") IResolutionFunction2D;
%feature("director") IRotation;
%feature("director") ISample;
%feature("director") ISampleBuilder;
%feature("director") ISelectionRule;
%feature("director") IsGISAXSDetector;
%feature("director") IShape2D;
%feature("director") ISingleton;
/**/
%include "std_complex.i"
%include "std_string.i"
%include "std_vector.i"

 //%include "boost_shared_ptr.i"
 %include <boost/shared_ptr.hpp>
 //%shared_ptr(ISampleBuilder)
 %template(SampleBuilder_t) boost::shared_ptr<ISampleBuilder>;

//%shared_ptr(IParameterized)
//%shared_ptr(INamed)

 //%shared_ptr(IShape2D)
/*
%shared_ptr(Geometry::IShape2D)
%shared_ptr(Crystal)
%shared_ptr(DistributionCosine)
%shared_ptr(DistributionGate)
%shared_ptr(DistributionGaussian)
%shared_ptr(DistributionLogNormal)
%shared_ptr(DistributionLorentz)
%shared_ptr(Geometry::Ellipse)
%shared_ptr(FTDistribution1DCauchy)
%shared_ptr(FTDistribution1DCosine)
%shared_ptr(FTDistribution1DGauss)
%shared_ptr(FTDistribution1DGate)
%shared_ptr(FTDistribution1DTriangle)
%shared_ptr(FTDistribution1DVoigt)
%shared_ptr(FTDistribution2DCauchy)
%shared_ptr(FTDistribution2DCone)
%shared_ptr(FTDistribution2DCosine)
%shared_ptr(FTDistribution2DGauss)
%shared_ptr(FTDistribution2DGate)
%shared_ptr(FTDistribution2DTriangle)
%shared_ptr(FTDistribution2DVoigt)
%shared_ptr(IFTDecayFunction1D)
%shared_ptr(FTDecayFunction1DCauchy)
%shared_ptr(FTDecayFunction1DGauss)
%shared_ptr(FTDecayFunction1DVoigt)
%shared_ptr(FTDecayFunction1DTriangle)
%shared_ptr(IFTDecayFunction2D)
%shared_ptr(FTDecayFunction2DCauchy)
%shared_ptr(FTDecayFunction2DGauss)
%shared_ptr(FTDecayFunction2DVoigt)
%shared_ptr(FormFactorAnisoPyramid)
%shared_ptr(FormFactorBox)
%shared_ptr(FormFactorCone)
%shared_ptr(FormFactorCone6)
%shared_ptr(FormFactorCrystal)
%shared_ptr(FormFactorCuboctahedron)
%shared_ptr(FormFactorCylinder)
%shared_ptr(FormFactorDecoratorDebyeWaller)
%shared_ptr(FormFactorEllipsoidalCylinder)
%shared_ptr(FormFactorFullSphere)
%shared_ptr(FormFactorFullSpheroid)
%shared_ptr(FormFactorGauss)
%shared_ptr(FormFactorHemiEllipsoid)
%shared_ptr(FormFactorLorentz)
%shared_ptr(FormFactorPrism3)
%shared_ptr(FormFactorPrism6)
%shared_ptr(FormFactorPyramid)
%shared_ptr(FormFactorRipple1)
%shared_ptr(FormFactorRipple2)
%shared_ptr(FormFactorSphereGaussianRadius)
%shared_ptr(FormFactorSphereLogNormalRadius)
%shared_ptr(FormFactorSphereUniformRadius)
%shared_ptr(FormFactorTetrahedron)
%shared_ptr(FormFactorTrivial)
%shared_ptr(FormFactorTruncatedCube)
%shared_ptr(FormFactorTruncatedSphere)
%shared_ptr(FormFactorTruncatedSpheroid)
%shared_ptr(FormFactorWeighted)
%shared_ptr(GISASSimulation)
%shared_ptr(HomogeneousMagneticMaterial)
%shared_ptr(HomogeneousMaterial)
%shared_ptr(Geometry::HorizontalLine)
%shared_ptr(IAbstractParticle)
%shared_ptr(ICloneable)
%shared_ptr(IClusteredParticles)
%shared_ptr(ICompositeSample)
%shared_ptr(IDetector2D)
%shared_ptr(IDistribution1D)
%shared_ptr(IFTDistribution1D)
%shared_ptr(IFTDistribution2D)
%shared_ptr(IFormFactor)
%shared_ptr(IFormFactorBorn)
%shared_ptr(IFormFactorDecorator)
%shared_ptr(IInterferenceFunction)
%shared_ptr(ILayout)
%shared_ptr(IMaterial)
%shared_ptr(INamed)
%shared_ptr(IParameterized)
%shared_ptr(IParticle)
%shared_ptr(IResolutionFunction2D)
%shared_ptr(IRotation)
%shared_ptr(IRoughness)
%shared_ptr(ISample)
%shared_ptr(Instrument)
%shared_ptr(InterferenceFunction1DLattice)
%shared_ptr(InterferenceFunctionRadialParaCrystal)
%shared_ptr(InterferenceFunction2DLattice)
%shared_ptr(InterferenceFunction2DParaCrystal)
%shared_ptr(InterferenceFunctionNone)
%shared_ptr(IsGISAXSDetector)
%shared_ptr(Layer)
%shared_ptr(LayerRoughness)
%shared_ptr(Geometry::Line)
%shared_ptr(MesoCrystal)
%shared_ptr(MultiLayer)
%shared_ptr(OffSpecSimulation)
%shared_ptr(ParameterDistribution)
%shared_ptr(ParameterPool)
%shared_ptr(Particle)
%shared_ptr(ParticleComposition)
%shared_ptr(ParticleCoreShell)
%shared_ptr(ParticleDistribution)
%shared_ptr(ParticleLayout)
%shared_ptr(Geometry::Polygon)
%shared_ptr(Geometry::Rectangle)
%shared_ptr(RectangularDetector)
%shared_ptr(ResolutionFunction2DGaussian)
%shared_ptr(RotationEuler)
%shared_ptr(RotationX)
%shared_ptr(RotationY)
%shared_ptr(RotationZ)
%shared_ptr(Simulation)
%shared_ptr(SpecularSimulation)
%shared_ptr(SphericalDetector)
%shared_ptr(Geometry::VerticalLine)
 /* */

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


// maybe this works..
%ignore Units::PI2;


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

  %ignore BasicVector3D<std::complex<double> >::mag() const;
  %ignore BasicVector3D<std::complex<double> >::mag2() const;
    %ignore BasicVector3D<std::complex<double> >::unit() const;

  %ignore BasicVector3D<double>::normalize() const;
  %ignore BasicVector3D<std::complex<double> >::normalize() const;
}



// %template(vector_realparameter_t) std::vector<RealParameterWrapper>;   // SWIG issue: fails to build ATM
//        %template( std::vector<ParameterSample> vector_ParameterSample_t;




#define SWIG_FILE_WITH_INIT

%{
#include <boost/shared_ptr.hpp>
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
 //%import "ICloneable.h"
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
#include "AttLimits.h"
#include "BasicVector3D.h"
#include "BAVersion.h"
#include "Bin.h"
#include "ConstKBinAxis.h"
#include "Crystal.h"
#include "CustomBinAxis.h"
#include "Distributions.h"
#include "Ellipse.h"
#include "FixedBinAxis.h"
#include "FormFactorAnisoPyramid.h"
#include "FormFactorBox.h"
#include "FormFactorCone.h"
#include "FormFactorCone6.h"
#include "FormFactorCrystal.h"
#include "FormFactorCuboctahedron.h"
#include "FormFactorCylinder.h"
#include "FormFactorDecoratorDebyeWaller.h"
#include "FormFactorEllipsoidalCylinder.h"
#include "FormFactorFullSphere.h"
#include "FormFactorFullSpheroid.h"
#include "FormFactorGauss.h"
#include "FormFactorHemiEllipsoid.h"
#include "FormFactorLorentz.h"
#include "FormFactorPrism3.h"
#include "FormFactorPrism6.h"
#include "FormFactorPyramid.h"
#include "FormFactorRipple1.h"
#include "FormFactorRipple2.h"
#include "FormFactorSphereGaussianRadius.h"
#include "FormFactorSphereLogNormalRadius.h"
#include "FormFactorSphereUniformRadius.h"
#include "FormFactorTetrahedron.h"
#include "FormFactorTrivial.h"
#include "FormFactorTruncatedCube.h"
#include "FormFactorTruncatedSphere.h"
#include "FormFactorTruncatedSpheroid.h"
#include "FormFactorWeighted.h"
#include "FTDistributions.h"
#include "FTDecayFunctions.h"
#include "GISASSimulation.h"
#include "Histogram1D.h"
#include "Histogram2D.h"
#include "HomogeneousMaterial.h"
#include "HomogeneousMagneticMaterial.h"
#include "IAxis.h"
#include "ICloneable.h"
#include "IClusteredParticles.h"
#include "ICompositeSample.h"
#include "IDetector2D.h"
#include "ILayout.h"
#include "IFormFactor.h"
#include "IFormFactorBorn.h"
#include "IFormFactorDecorator.h"
#include "IHistogram.h"
#include "IInterferenceFunction.h"
#include "IntensityDataFunctions.h"
#include "IntensityDataIOFactory.h"
#include "IMaterial.h"
#include "Instrument.h"
#include "InterferenceFunction1DLattice.h"
#include "InterferenceFunctionRadialParaCrystal.h"
#include "InterferenceFunction2DLattice.h"
#include "InterferenceFunction2DParaCrystal.h"
#include "InterferenceFunctionNone.h"
#include "IObserver.h"
#include "IParameterized.h"
#include "IParticle.h"
#include "IResolutionFunction2D.h"
#include "ISample.h"
#include "ISampleBuilder.h"
#include "ISelectionRule.h"
#include "IsGISAXSDetector.h"
#include "IShape2D.h"
#include "ISingleton.h"
#include "Lattice.h"
#include "Lattice1DParameters.h"
#include "Lattice2DParameters.h"
#include "Layer.h"
#include "LayerRoughness.h"
#include "Line.h"
#include "MathFunctions.h"
#include "MesoCrystal.h"
#include "MessageService.h"
#include "MultiLayer.h"
#include "OffSpecSimulation.h"
#include "OutputData.h"
#include "OutputDataFunctions.h"
#include "ParameterDistribution.h"
#include "ParameterPool.h"
#include "Particle.h"
#include "ParticleComposition.h"
#include "ParticleCoreShell.h"
#include "ParticleDistribution.h"
#include "ParticleLayout.h"
#include "Polygon.h"
#include "Rectangle.h"
#include "RectangularDetector.h"
#include "RealParameterWrapper.h"
#include "ResolutionFunction2DGaussian.h"
#include "Rotations.h"
#include "SpecularSimulation.h"
#include "SphericalDetector.h"
#include "SimulationParameters.h"
#include "ThreadInfo.h"
#include "Types.h"
#include "Units.h"
#include "VariableBinAxis.h"

%}



// need this to play nicely with ctypes
%ignore IParameterized::registerParameter(const std::string &, double*, const AttLimits&);
%ignore IParameterized::registerParameter(const std::string &, double*);
%ignore ISampleBuilder::registerParameter(const std::string &, double*, const AttLimits&);
%ignore ISampleBuilder::registerParameter(const std::string &, double*);
//%ignore ISampleBuilder::addParametersToExternalPool(std::string, ParameterPool*, int) const;
//%ignore ISampleBuilder::addParametersToExternalPool(std::string, ParameterPool*) const;


%include "AttLimits.h"
%include "BasicVector3D.h"
%include "BAVersion.h"
%include "Bin.h"
%include "IAxis.h"
%include "VariableBinAxis.h"
%include "ConstKBinAxis.h"
%include "ICloneable.h"
%include "INamed.h"
%include "IParameterized.h"
%include "ISample.h"
%include "ICompositeSample.h"
%include "IClusteredParticles.h"
%include "IShape2D.h"
%include "Crystal.h"
%include "CustomBinAxis.h"
%include "Distributions.h"
%include "Ellipse.h"
%include "FixedBinAxis.h"
%include "IFormFactor.h"
%include "IFormFactorBorn.h"
%include "IFormFactorDecorator.h"
%include "FormFactorAnisoPyramid.h"
%include "FormFactorBox.h"
%include "FormFactorCone.h"
%include "FormFactorCone6.h"
%include "FormFactorCrystal.h"
%include "FormFactorCuboctahedron.h"
%include "FormFactorCylinder.h"
%include "FormFactorDecoratorDebyeWaller.h"
%include "FormFactorEllipsoidalCylinder.h"
%include "FormFactorFullSphere.h"
%include "FormFactorFullSpheroid.h"
%include "FormFactorGauss.h"
%include "FormFactorHemiEllipsoid.h"
%include "FormFactorLorentz.h"
%include "FormFactorPrism3.h"
%include "FormFactorPrism6.h"
%include "FormFactorPyramid.h"
%include "FormFactorRipple1.h"
%include "FormFactorRipple2.h"
%include "FormFactorSphereGaussianRadius.h"
%include "FormFactorSphereLogNormalRadius.h"
%include "FormFactorSphereUniformRadius.h"
%include "FormFactorTetrahedron.h"
%include "FormFactorTrivial.h"
%include "FormFactorTruncatedCube.h"
%include "FormFactorTruncatedSphere.h"
%include "FormFactorTruncatedSpheroid.h"
%include "FormFactorWeighted.h"
%include "FTDistributions.h"
%include "FTDecayFunctions.h"
%include "IMaterial.h"
%include "Simulation.h"
%include "GISASSimulation.h"
%include "IHistogram.h"
%include "Histogram1D.h"
%include "Histogram2D.h"
%include "HomogeneousMaterial.h"
%include "HomogeneousMagneticMaterial.h"
%include "IAxis.h"
%include "ICloneable.h"
%include "IClusteredParticles.h"
%include "ICompositeSample.h"
%include "IDetector2D.h"
%include "ILayout.h"
%include "IHistogram.h"
%include "IInterferenceFunction.h"
%include "IntensityDataFunctions.h"
%include "IntensityDataIOFactory.h"
%include "IMaterial.h"
%include "Instrument.h"
%include "InterferenceFunction1DLattice.h"
%include "InterferenceFunctionRadialParaCrystal.h"
%include "InterferenceFunction2DLattice.h"
%include "InterferenceFunction2DParaCrystal.h"
%include "InterferenceFunctionNone.h"
%include "IObserver.h"
%include "IParameterized.h"
%include "IParticle.h"
%include "IResolutionFunction2D.h"
%include "ISample.h"



%include "ISampleBuilder.h"



%include "ISelectionRule.h"
%include "IPixelMap.h"
%include "SphericalDetector.h"
%include "IsGISAXSDetector.h"
%include "IShape2D.h"
%include "ISingleton.h"
%include "Lattice.h"
%include "Lattice1DParameters.h"
%include "Lattice2DParameters.h"
%include "IRoughness.h"
%include "Layer.h"
%include "IRoughness.h"
%include "RealParameterWrapper.h"
%include "LayerRoughness.h"
%include "Line.h"
%include "MathFunctions.h"
%include "MesoCrystal.h"
%include "MessageService.h"
%include "MultiLayer.h"
%include "OffSpecSimulation.h"
%include "OutputData.h"
%include "OutputDataFunctions.h"
%include "ParameterDistribution.h"
%include "ParameterPool.h"
%include "Particle.h"



// from PythonCoreExposer.h
%template(kvector_t) Geometry::BasicVector3D<double >;
%template(vector_kvector_t) std::vector< Geometry::BasicVector3D<double> >;
%template(cvector_t) Geometry::BasicVector3D<std::complex<double> >;
%template(vector_cvector_t) std::vector< Geometry::BasicVector3D<std::complex<double> > >;
%template(vector_IFormFactorPtr_t) std::vector<IFormFactor *>;
%template(IntensityData) OutputData<double >;





%include "ParticleComposition.h"
%include "ParticleCoreShell.h"
%include "ParticleDistribution.h"
%include "ParticleLayout.h"
%include "Polygon.h"
%include "Rectangle.h"
%include "RectangularDetector.h"
%include "ResolutionFunction2DGaussian.h"
%include "Rotations.h"
%include "SpecularSimulation.h"
%include "SphericalDetector.h"
%include "SimulationParameters.h"
%include "ThreadInfo.h"
%include "Types.h"
%include "Units.h"
%include "VariableBinAxis.h"




 // why do we need this again?
%ignore Crystal::getTransformedLattice(const IRotation *) const;




// %template(complex_t) std::complex<double>;









%extend OutputData<double> {
  double __getitem__(unsigned int i) {
    return (*($self))[i];
  }
  
  double __setitem__(unsigned int i, double value) {
    (*($self))[i] = value;
    return (*($self))[i];
  }
};

%extend FixedBinAxis {
  double __getitem__(unsigned int i) {
    return (*($self))[i];
  }
  
  /*  double __setitem__(unsigned int i, double value) {
    (*($self))[i] = value;
    return (*($self))[i];
    }*/
};


%extend VariableBinAxis {
  double __getitem__(unsigned int i) {
    return (*($self))[i];
  }
  
  /*  double __setitem__(unsigned int i, double value) {
    (*($self))[i] = value;
    return (*($self))[i];
    } */
};


/*
%extend IAxis {
  double __getitem__(unsigned int i) {
    return (*($self))[i];
  }
  
  double __setitem__(unsigned int i, double value) {
    (*($self))[i] = value;
    return (*($self))[i];
  }
};
*/

//%ignore IAxis::operator==(const IAxis& rhs);

%extend IAxis {
  bool __ne__(const IAxis& rhs)
  {
    return !(*$self == rhs);
  }
};



%extend IParameterized {
  virtual void registerParameter(const std::string &name, long int parpointer, const AttLimits& limits = AttLimits::limitless())
  {
    return (*($self)).registerParameter(name, (double*)parpointer, limits);
  }

  /*virtual void registerParameter(const std::string &name, int parpointer, const AttLimits& limits = AttLimits::limitless())
  {
    return (*($self)).registerParameter(name, (double*)parpointer, limits);
    }*/
};

%extend ISampleBuilder {
  virtual void registerParameter(const std::string &name, long int parpointer, const AttLimits& limits = AttLimits::limitless())
  {
    return (*($self)).registerParameter(name, (double*)parpointer, limits);
  }

  /*virtual void registerParameter(const std::string &name, int parpointer, const AttLimits& limits = AttLimits::limitless())
  {
    return (*($self)).registerParameter(name, (double*)parpointer, limits);
    }*/
};

/* %extend ISampleBuilder {
  virtual std::string addParametersToExternalPool(
        std::string path,
        ParameterPool *external_pool,
        int copy_number=-1) const
  {
    return (*($self)).addParametersToExternalPool(path, external_pool, copy_number);
  }
};
*/




