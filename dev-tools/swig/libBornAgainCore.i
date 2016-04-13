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

 //%feature("director");
%feature("autodoc");







/**/
%include "stdint.i"
%include "std_complex.i"
%include "std_string.i"
%include "std_vector.i"
%include "std_shared_ptr.i"


%include "doxygen_core.i"

%include "warnings.i"
%include "ignores.i"
%include "extends.i"
%include "directors.i"

 // include the list of smart pointers (common between Core and Fit)
%include "shared_pointers.i"


// from PythonCoreExposer.h
%template(vdouble1d_t) std::vector<double>;
%template(vdouble2d_t) std::vector< std::vector<double> >;
%template(vector_integer_t) std::vector<int >;
%template(vector_longinteger_t) std::vector<unsigned long int >;
%template(vector_complex_t) std::vector< std::complex<double> >;
%template(vector_string_t) std::vector<std::string>;




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
#include "FormFactorLongRipple1Gauss.h"
#include "FormFactorLongRipple1Lorentz.h"
#include "FormFactorLongRipple2Gauss.h"
#include "FormFactorLongRipple2Lorentz.h"
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
#include "SimulationOptions.h"
#include "SpecularSimulation.h"
#include "SphericalDetector.h"
#include "ThreadInfo.h"
#include "Types.h"
#include "Vectors3D.h"
#include "Units.h"
#include "VariableBinAxis.h"
#include "WavevectorInfo.h"

#include "SampleBuilderFactory.h"
#include "SimulationRegistry.h"

%}




// import headers to be exported to Python interace.
// Note that the order of inclusion matters, as base classes must be imported before derived classes

%include "AttLimits.h"
%include "ICloneable.h"

%include "INamed.h"


//typedef INamedTemplate<void> INamed;
//typedef INamedTemplate<int> INamedShared;

 //%include "INamedShared.h"

%include "IParameterized.h"



//typedef IParameterized<void> IParamet

 //%include "IParameterizedShared.h"

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
%include "FormFactorLongRipple1Gauss.h"
%include "FormFactorLongRipple1Lorentz.h"
%include "FormFactorLongRipple2Gauss.h"
%include "FormFactorLongRipple2Lorentz.h"
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
%include "SimulationOptions.h"
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


%include "SampleBuilderFactory.h"
%include "SimulationRegistry.h"



