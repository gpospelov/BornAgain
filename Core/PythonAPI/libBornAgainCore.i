// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      PythonAPI/libBornAgainCore.i
//! @brief     SWIG interface file for libBornAgainCore
//!
//! @homepage  http://apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

%module(directors="1") "libBornAgainCore"

%feature("autodoc");
%include "doxygen.i"

#pragma SWIG nowarn=314 // print
#pragma SWIG nowarn=315 // nothing known about std::size_t // fixed by #ifndef in Types.h
 //#pragma SWIG nowarn=362 // operator=
 //#pragma SWIG nowarn=389 // operator[]
#pragma SWIG nowarn=473 // returning pointer in a director method (object ownership problem)
#pragma SWIG nowarn=503 // operator<<
 //#pragma SWIG nowarn=509 // overload ignored since reference=pointer


 //%feature("director");

 // manually declare which classes can be derived in Python and passed back to C++
 // this can be used to reduce the bloat in the swig-generated code

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
%feature("director") INamed;
%feature("director") INamedShared;
%feature("director") Instrument;
%feature("director") InterferenceFunction1DLattice;
%feature("director") InterferenceFunctionRadialParaCrystal;
%feature("director") InterferenceFunction2DLattice;
%feature("director") InterferenceFunction2DParaCrystal;
%feature("director") InterferenceFunctionNone;
%feature("director") IObserver;
%feature("director") IParameterized;
%feature("director") IParameterizedShared;
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
%include "std_shared_ptr.i"

%shared_ptr(ISampleBuilder)
%shared_ptr(IParameterizedShared)
%shared_ptr(INamedShared)
%shared_ptr(LayerRTCoefficients_t)
%shared_ptr(ProgressHandler_t)
%shared_ptr(IObserver)


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


// need to fix SWIG error, PI2 multiply defined
%ignore Units::PI2;


// problems with BasicVector3D.h
namespace Geometry {

    %ignore BasicVector3D<std::complex<double> >::complex() const;
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


    %extend BasicVector3D<double> {
        BasicVector3D<double> __add__(const BasicVector3D<double>& rhs) const
        {
            return *($self)+rhs;
        }

        BasicVector3D<double> __mul__(double c) const
        {
            return *($self)*c;
        }

        BasicVector3D<double> __rmul__(double c) const
        {
            return *($self)*c;
        }
    };
}




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

%{

#include "AttLimits.h"
#include "BAVersion.h"
#include "BasicVector3D.h"
#include "Beam.h"
#include "Bin.h"
#include "ConstKBinAxis.h"
#include "Crystal.h"
#include "CustomBinAxis.h"
#include "Distributions.h"
#include "Ellipse.h"
#include "FTDecayFunctions.h"
#include "FTDistributions.h"
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
#include "FormFactorLongBoxGauss.h"
#include "FormFactorLongBoxLorentz.h"
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
#include "GISASSimulation.h"
#include "Histogram1D.h"
#include "Histogram2D.h"
#include "HomogeneousMagneticMaterial.h"
#include "HomogeneousMaterial.h"
#include "IAxis.h"
#include "ICloneable.h"
#include "IClusteredParticles.h"
#include "ICompositeSample.h"
#include "IDetector2D.h"
#include "IDetectorResolution.h"
#include "Distributions.h"   
#include "FTDecayFunctions.h"
#include "IFormFactor.h"
#include "IFormFactorBorn.h"
#include "IFormFactorDecorator.h"
#include "IHistogram.h"
#include "IInterferenceFunction.h"
#include "ILayout.h"
#include "IMaterial.h"
#include "IObserver.h"
#include "IParameterized.h"
#include "IParameterizedShared.h"
#include "IParticle.h"
#include "IResolutionFunction2D.h"
#include "Rotations.h"
#include "ISample.h"
#include "ISampleBuilder.h"
#include "ISampleVisitor.h"
#include "ISelectionRule.h"
#include "IShape2D.h"
#include "ISingleton.h"
#include "Instrument.h"
#include "IntensityDataFunctions.h"
#include "IntensityDataIOFactory.h"
#include "InterferenceFunction1DLattice.h"
#include "InterferenceFunctionRadialParaCrystal.h"
#include "InterferenceFunction2DLattice.h"
#include "InterferenceFunction2DParaCrystal.h"
#include "InterferenceFunctionNone.h"
#include "InterferenceFunction1DLattice.h"
#include "InterferenceFunctionRadialParaCrystal.h"
#include "InterferenceFunction2DLattice.h"
#include "InterferenceFunction2DParaCrystal.h"
#include "InterferenceFunctionNone.h"
#include "IsGISAXSDetector.h"
#include "Lattice.h"
#include "Lattice1DParameters.h"
#include "Lattice2DParameters.h"
#include "Layer.h"
#include "LayerInterface.h"
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
#include "RealParameterWrapper.h"
#include "Rectangle.h"
#include "RectangularDetector.h"
#include "ResolutionFunction2DGaussian.h"
#include "Rotations.h"
#include "ISelectionRule.h"
#include "Simulation.h"
#include "SimulationParameters.h"
#include "SpecularSimulation.h"
#include "SphericalDetector.h"
#include "ThreadInfo.h"
#include "Types.h"
#include "Vectors3D.h"
#include "Units.h"
#include "VariableBinAxis.h"
#include "WavevectorInfo.h"

%}



// need this to play nicely with ctypes
%ignore IParameterizedShared::registerParameter(const std::string &, double*, const AttLimits&);
%ignore IParameterizedShared::registerParameter(const std::string &, double*);
%ignore ISampleBuilder::registerParameter(const std::string &, double*, const AttLimits&);
%ignore ISampleBuilder::registerParameter(const std::string &, double*);
//%ignore ISampleBuilder::addParametersToExternalPool(std::string, ParameterPool*, int) const;
//%ignore ISampleBuilder::addParametersToExternalPool(std::string, ParameterPool*) const;



// import headers to be exported to Python interace.
// Note that the order of inclusion matters, as base classes must be imported before derived classes

%include "AttLimits.h"
%include "ICloneable.h"

%include "INamed.h"
%include "INamedShared.h"

%include "IParameterized.h"
%include "IParameterizedShared.h"

%include "BAVersion.h"
%include "BasicVector3D.h"

// SWIG does not automatically instantiate templates, so we declare these by hand
%template(kvector_t) Geometry::BasicVector3D<double >;
%template(vector_kvector_t) std::vector< Geometry::BasicVector3D<double> >;
%template(cvector_t) Geometry::BasicVector3D<std::complex<double> >;
%template(vector_cvector_t) std::vector< Geometry::BasicVector3D<std::complex<double> > >;

%include "Types.h"
%include "Units.h"
%include "Vectors3D.h"
%include "WavevectorInfo.h"

%include "Beam.h"
%include "Bin.h"

%include "IAxis.h"
%include "VariableBinAxis.h"
%include "ConstKBinAxis.h"
%include "CustomBinAxis.h"

%include "IShape2D.h"
%include "ISample.h"

// need to tell SWIG explicitly to instantiate these templates with given types
%template(swig_dummy_type_isample_vector) std::vector<ISample*>;
%template(swig_dummy_type_const_isample_vector) std::vector<const ISample*>;

%include "ISampleBuilder.h"
%include "ISampleVisitor.h"
%include "ICompositeSample.h"
%include "IClusteredParticles.h"
%include "Crystal.h"

%include "Distributions.h"
%include "Ellipse.h"
%include "FTDecayFunctions.h"
%include "FTDistributions.h"
%include "FixedBinAxis.h"

%include "IFormFactor.h"
%template(vector_IFormFactorPtr_t) std::vector<IFormFactor *>;

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
%include "FormFactorLongBoxGauss.h"
%include "FormFactorLongBoxLorentz.h"
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

%include "Simulation.h"
%include "SimulationParameters.h"
%include "GISASSimulation.h"

%include "IHistogram.h"
%include "Histogram1D.h"
%include "Histogram2D.h"

%include "IMaterial.h"
%include "HomogeneousMaterial.h"
%include "HomogeneousMagneticMaterial.h"

%include "IDetector2D.h"
%include "IDetectorResolution.h"
%include "Distributions.h"   
%include "FTDecayFunctions.h"

%include "IInterferenceFunction.h"
%include "ILayout.h"

%include "IObserver.h"

%include "IParticle.h"
%include "IResolutionFunction2D.h"
%include "Rotations.h"

%include "ISelectionRule.h"

%include "ISingleton.h"
%include "Instrument.h"
%include "IntensityDataFunctions.h"
%include "IntensityDataIOFactory.h"
%include "InterferenceFunction1DLattice.h"
%include "InterferenceFunctionRadialParaCrystal.h"
%include "InterferenceFunction2DLattice.h"
%include "InterferenceFunction2DParaCrystal.h"
%include "InterferenceFunctionNone.h"
%include "InterferenceFunction1DLattice.h"
%include "InterferenceFunctionRadialParaCrystal.h"
%include "InterferenceFunction2DLattice.h"
%include "InterferenceFunction2DParaCrystal.h"
%include "InterferenceFunctionNone.h"

%include "IPixelMap.h"
%include "SphericalDetector.h"
%include "IsGISAXSDetector.h"
%include "Lattice.h"
%include "Lattice1DParameters.h"
%include "Lattice2DParameters.h"
%include "Layer.h"

%include "IRoughness.h"
%include "LayerRoughness.h"
%include "Line.h"
%include "MathFunctions.h"
%include "MesoCrystal.h"
%include "MessageService.h"
%include "MultiLayer.h"
%include "OffSpecSimulation.h"

%include "OutputData.h"
%template(IntensityData) OutputData<double >;

%include "OutputDataFunctions.h"
%include "ParameterDistribution.h"
%include "ParameterPool.h"
%include "Particle.h"
%include "ParticleComposition.h"
%include "ParticleCoreShell.h"
%include "ParticleDistribution.h"
%include "ParticleLayout.h"
%include "Polygon.h"
%include "RealParameterWrapper.h"
%include "Rectangle.h"
%include "RectangularDetector.h"
%include "ResolutionFunction2DGaussian.h"
%include "Rotations.h"
%include "ISelectionRule.h"

%include "SpecularSimulation.h"

%include "ThreadInfo.h"



// ignored to avoid error (todo: check whether this is really necessary)
%ignore Crystal::getTransformedLattice(const IRotation *) const;


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



%extend IParameterizedShared {
    virtual void registerParameter(const std::string &name, long int parpointer, const AttLimits& limits = AttLimits::limitless())
    {
        return (*($self)).registerParameter(name, (double*)parpointer, limits);
    }

    /*virtual void registerParameter(const std::string &name, int parpointer, const AttLimits& limits = AttLimits::limitless())
      {
      return (*($self)).registerParameter(name, (double*)parpointer, limits);
      }*/

    /*virtual std::string addParametersToExternalPool(std::string path, boost::shared_ptr<ParameterPool> external_pool,
      int copy_number = -1) const
      {
      return ($self)->addParametersToExternalPool(path, external_pool.get(), copy_number);
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

/*

  %extend ICompositeSample {
  virtual void registerChild(boost::shared_ptr<ISample> sample)
  {
  ($self)->registerChild(sample.get());
  }
  
  virtual void deregisterChild(boost::shared_ptr<ISample> sample)
  {
  ($self)->deregisterChild(sample.get());
  }
  };

  %extend ISampleVisitor {
  virtual void visit(boost::shared_ptr<ISample> sample)
  {
  ($self)->visit(sample.get());
  }
  };
		       

  %extend ISampleIterator {
  virtual IteratorMemento first(boost::shared_ptr<ISample> p_root)
  {
  return ($self)->first(p_root.get());
  }
  };

  %extend SampleIteratorPreorderStrategy {
  virtual IteratorMemento first(boost::shared_ptr<ISample> p_root)
  {
  return ($self)->first(p_root.get());
  }
  };

  %extend SampleIteratorPostOrderStrategy {
  virtual IteratorMemento first(boost::shared_ptr<ISample> p_root)
  {
  return ($self)->first(p_root.get());
  }
  };
*/
