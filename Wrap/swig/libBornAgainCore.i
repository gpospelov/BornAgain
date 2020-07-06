// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Wrap/swig/libBornAgainCore.i
//! @brief     SWIG interface file for libBornAgainCore
//!
//!            Configuration is done in Core/CMakeLists.txt
//!
//! @homepage  http://apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

%module(directors="1", moduleimport="import $module") "libBornAgainCore"

%feature("autodoc");

/**/
%include "stdint.i"
%include "std_complex.i"
%include "std_string.i"
%include "std_vector.i"
%include "std_map.i"
%include "std_shared_ptr.i"

// TODO CLARIFY WHY THIS IS INCLUDED
%include "../../auto/Wrap/doxygen_core.i"

// include the list of smart pointers (common between Core and Fit)
%include "shared_pointers.i"

%include "warnings.i"
%include "deprecated.i"
%include "ignores.i"
%include "renameCore.i"
%include "directors.i"

%template(vdouble1d_t) std::vector<double>;
%template(vdouble2d_t) std::vector<std::vector<double>>;
%template(vector_integer_t) std::vector<int>;
%template(vinteger2d_t) std::vector<std::vector<int>>;
%template(vector_longinteger_t) std::vector<unsigned long int>;
%template(vector_complex_t) std::vector< std::complex<double>>;
%template(vector_string_t) std::vector<std::string>;
%template(map_string_double_t) std::map<std::string, double>;
%template(pair_double_t) std::pair<double, double>;
%template(vector_pair_double_t) std::vector<std::pair<double, double>>;
%nodefaultctor ParameterPool;

#define SWIG_FILE_WITH_INIT

%{
#define SWIG_FILE_WITH_INIT
#define PY_ARRAY_UNIQUE_SYMBOL BORNAGAIN_PYTHONAPI_ARRAY
%}

%include "numpy.i"
%init %{
    import_array();
%}

#define GCC_DIAG_OFF(x)
#define GCC_DIAG_ON(x)

#ifndef BORNAGAIN_PYTHON
#define BORNAGAIN_PYTHON
#endif

%import "Wrap/WinDllMacros.h"

%{
#include "Core/Instrument/AngularSpecScan.h"
#include "BAVersion.h"
#include "Core/Vector/BasicVector3D.h"
#include "Core/Beam/Beam.h"
#include "Core/Binning/Bin.h"
#include "Core/Instrument/ChiSquaredModule.h"
#include "Core/Basics/Complex.h"
#include "Core/Computation/ConstantBackground.h"
#include "Core/Binning/ConstKBinAxis.h"
#include "Core/Particle/Crystal.h"
#include "Core/Binning/CustomBinAxis.h"
#include "Core/Simulation/DepthProbeSimulation.h"
#include "Core/Instrument/DetectorMask.h"
#include "Core/Parametrization/Distributions.h"
#include "Core/Mask/Ellipse.h"
#include "Core/Aggregate/FTDecayFunctions.h"
#include "Core/Aggregate/FTDistributions1D.h"
#include "Core/Aggregate/FTDistributions2D.h"
#include "Fit/Kernel/FitOptions.h"
#include "Core/Fitting/PyFittingCallbacks.h"
#include "Core/Fitting/FitObjective.h"
#include "Core/Binning/FixedBinAxis.h"
#include "Core/Beam/FootprintFactorGaussian.h"
#include "Core/Beam/FootprintFactorSquare.h"
#include "Core/HardParticle/FormFactorAnisoPyramid.h"
#include "Core/HardParticle/FormFactorBar.h"
#include "Core/HardParticle/FormFactorBox.h"
#include "Core/HardParticle/FormFactorCantellatedCube.h"
#include "Core/HardParticle/FormFactorCone.h"
#include "Core/HardParticle/FormFactorCone6.h"
#include "Core/Particle/FormFactorCrystal.h"
#include "Core/HardParticle/FormFactorCuboctahedron.h"
#include "Core/HardParticle/FormFactorCylinder.h"
#include "Core/SoftParticle/FormFactorDebyeBueche.h"
#include "Core/HardParticle/FormFactorDodecahedron.h"
#include "Core/HardParticle/FormFactorDot.h"
#include "Core/HardParticle/FormFactorEllipsoidalCylinder.h"
#include "Core/HardParticle/FormFactorFullSphere.h"
#include "Core/HardParticle/FormFactorFullSpheroid.h"
#include "Core/SoftParticle/FormFactorGauss.h"
#include "Core/HardParticle/FormFactorHemiEllipsoid.h"
#include "Core/HardParticle/FormFactorIcosahedron.h"
#include "Core/HardParticle/FormFactorLongBoxGauss.h"
#include "Core/HardParticle/FormFactorLongBoxLorentz.h"
#include "Core/SoftParticle/FormFactorLorentz.h"
#include "Core/SoftParticle/FormFactorOrnsteinZernike.h"
#include "Core/HardParticle/FormFactorPolyhedron.h"
#include "Core/HardParticle/FormFactorPolyhedron.h"
#include "Core/HardParticle/FormFactorPrism3.h"
#include "Core/HardParticle/FormFactorPrism6.h"
#include "Core/HardParticle/FormFactorPyramid.h"
#include "Core/HardParticle/FormFactorRipple1.h"
#include "Core/HardParticle/FormFactorRipple2.h"
#include "Core/SoftParticle/FormFactorSphereGaussianRadius.h"
#include "Core/SoftParticle/FormFactorSphereLogNormalRadius.h"
#include "Core/SoftParticle/FormFactorSphereUniformRadius.h"
#include "Core/HardParticle/FormFactorTetrahedron.h"
#include "Core/HardParticle/FormFactorTruncatedCube.h"
#include "Core/HardParticle/FormFactorTruncatedSphere.h"
#include "Core/HardParticle/FormFactorTruncatedSpheroid.h"
#include "Core/Particle/FormFactorWeighted.h"
#include "Core/Simulation/GISASSimulation.h"
#include "Core/Instrument/Histogram1D.h"
#include "Core/Instrument/Histogram2D.h"
#include "Core/Particle/IAbstractParticle.h"
#include "Core/Computation/IBackground.h"
#include "Core/Basics/ICloneable.h"
#include "Core/Particle/IClusteredParticles.h"
#include "Core/Instrument/IDetector2D.h"
#include "Core/Instrument/IDetectorResolution.h"
#include "Core/DecoratedFormFactor/IFormFactorDecorator.h"
#include "Core/Instrument/IHistogram.h"
#include "Core/Instrument/IIntensityFunction.h"
#include "Core/Aggregate/IInterferenceFunction.h"
#include "Core/Aggregate/ILayout.h"
#include "Core/Basics/INamed.h"
#include "Core/Parametrization/INode.h"
#include "Core/Fitting/IObserver.h"
#include "Core/Parametrization/IParameterized.h"
#include "Core/Particle/IParticle.h"
#include "Core/Aggregate/IPeakShape.h"
#include "Core/Instrument/IResolutionFunction2D.h"
#include "Core/Scattering/ISample.h"
#include "Core/Multilayer/IMultiLayerBuilder.h"
#include "Core/Parametrization/INodeVisitor.h"
#include "Core/Lattice/ISelectionRule.h"
#include "Core/Mask/IShape2D.h"
#include "Core/Basics/ISingleton.h"
#include "Core/Instrument/Instrument.h"
#include "Core/Instrument/IntensityDataFunctions.h"
#include "Core/InputOutput/IntensityDataIOFactory.h"
#include "Core/Aggregate/InterferenceFunction1DLattice.h"
#include "Core/Aggregate/InterferenceFunction2DLattice.h"
#include "Core/Aggregate/InterferenceFunction2DParaCrystal.h"
#include "Core/Aggregate/InterferenceFunction2DSuperLattice.h"
#include "Core/Aggregate/InterferenceFunction3DLattice.h"
#include "Core/Aggregate/InterferenceFunctionFinite2DLattice.h"
#include "Core/Aggregate/InterferenceFunctionFinite3DLattice.h"
#include "Core/Aggregate/InterferenceFunctionHardDisk.h"
#include "Core/Aggregate/InterferenceFunctionNone.h"
#include "Core/Aggregate/InterferenceFunctionRadialParaCrystal.h"
#include "Core/Aggregate/InterferenceFunctionTwin.h"
#include "Core/Instrument/IsGISAXSDetector.h"
#include "Core/Lattice/ILatticeOrientation.h"
#include "Core/Lattice/Lattice.h"
#include "Core/Lattice/LatticeUtils.h"
#include "Core/Lattice/Lattice1DParameters.h"
#include "Core/Lattice/Lattice2D.h"
#include "Core/Multilayer/Layer.h"
#include "Core/Multilayer/LayerInterface.h"
#include "Core/Multilayer/LayerRoughness.h"
#include "Core/Mask/Line.h"
#include "Core/Material/MaterialFactoryFuncs.h"
#include "Core/Tools/MathFunctions.h"
#include "Core/Particle/MesoCrystal.h"
#include "Core/Multilayer/MultiLayer.h"
#include "Core/Multilayer/MultiLayerFuncs.h"
#include "Core/Simulation/OffSpecSimulation.h"
#include "Core/Instrument/OutputData.h"
#include "Core/Parametrization/ParameterDistribution.h"
#include "Core/Parametrization/ParameterPool.h"
#include "Core/Parametrization/ParameterSample.h"
#include "Core/Particle/Particle.h"
#include "Core/Particle/ParticleComposition.h"
#include "Core/Particle/ParticleCoreShell.h"
#include "Core/Particle/ParticleDistribution.h"
#include "Core/Aggregate/ParticleLayout.h"
#include "Core/Computation/PoissonNoiseBackground.h"
#include "Core/Mask/Polygon.h"
#include "Core/Instrument/PyArrayImportUtils.h"
#include "Core/Instrument/QSpecScan.h"
#include "Core/Parametrization/RangedDistributions.h"
#include "Core/Parametrization/RealParameter.h"
#include "Core/Mask/Rectangle.h"
#include "Core/Instrument/RectangularDetector.h"
#include "Core/Instrument/ResolutionFunction2DGaussian.h"
#include "Core/HardParticle/Ripples.h"
#include "Core/Scattering/Rotations.h"
#include "Core/StandardSamples/SampleBuilderFactory.h"
#include "Core/Instrument/ScanResolution.h"
#include "Core/Simulation/Simulation.h"
#include "Core/Simulation/Simulation2D.h"
#include "Core/StandardSamples/SimulationFactory.h"
#include "Core/Parametrization/SimulationOptions.h"
#include "Core/Instrument/SimulationResult.h"
#include "Core/Particle/SlicedParticle.h"
#include "Core/Simulation/SpecularSimulation.h"
#include "Core/Instrument/SphericalDetector.h"
#include "Core/Parametrization/ThreadInfo.h"
#include "Core/Parametrization/Units.h"
#include "Core/Binning/VariableBinAxis.h"
#include "Core/Vector/Vectors3D.h"
#include "Core/Vector/WavevectorInfo.h"
#include "Core/Instrument/IChiSquaredModule.h"
#include "Core/Instrument/IIntensityFunction.h"
#include "Core/Instrument/IIntensityNormalizer.h"
#include "Core/Instrument/VarianceFunctions.h"
#include "Core/Fitting/IterationInfo.h"
#include "Core/Tools/SpectrumUtils.h"
%}

// ownership

%newobject ScanResolution::scanRelativeResolution;
%newobject ScanResolution::scanAbsoluteResolution;

%newobject SimulationResult::histogram2d(AxesUnits units_type = AxesUnits::DEFAULT) const;

%newobject IntensityDataIOFactory::readOutputData(const std::string& file_name);
%newobject IntensityDataIOFactory::readIntensityData(const std::string& file_name);

%newobject DetectorMask::createHistogram() const;

%newobject PyArrayImport::importArrayToOutputData;
%newobject IHistogram::createFrom(const std::string& filename);
%newobject IHistogram::createFrom(const std::vector<std::vector<double>>& data);

%newobject InterferenceFunction2DLattice::createSquare(double lattice_length, double xi);
%newobject InterferenceFunction2DLattice::createHexagonal(double lattice_length, double xi);
%newobject InterferenceFunction2DParaCrystal::createSquare(
        double lattice_length, double damping_length, double domain_size_1, double domain_size_2);
%newobject InterferenceFunction2DParaCrystal::createHexagonal(
        double lattice_length, double damping_length, double domain_size_1, double domain_size_2);
%newobject InterferenceFunction2DSuperLattice::createSquare(
        double lattice_length, double xi, unsigned size_1, unsigned size_2);
%newobject InterferenceFunction2DSuperLattice::createHexagonal(
        double lattice_length, double xi, unsigned size_1, unsigned size_2);
%newobject InterferenceFunctionFinite2DLattice::createSquare(
        double lattice_length, double xi, unsigned size_1, unsigned size_2);
%newobject InterferenceFunctionFinite2DLattice::createHexagonal(
        double lattice_length, double xi, unsigned size_1, unsigned size_2);

// The following goes verbatim from libBornAgainCore.i to libBornAgainCore_wrap.cxx.
// Note that the order matters, as base classes must be included before derived classes.

%import(module="libBornAgainFit") "Fit/Tools/AttLimits.h"
%import(module="libBornAgainFit") "Fit/Tools/Attributes.h"
%import(module="libBornAgainFit") "Fit/Tools/RealLimits.h"
%import(module="libBornAgainFit") "Fit/Kernel/Parameters.h"
%import(module="libBornAgainFit") "Fit/Kernel/Parameter.h"

%include "BAVersion.h"
%include "Core/Vector/BasicVector3D.h"
%include "Core/Basics/ICloneable.h"
%include "Core/Basics/INamed.h"
%include "Core/Parametrization/IParameterized.h"
%include "Core/Parametrization/INode.h"

// need to tell SWIG explicitly to instantiate these templates with given types
%template(swig_dummy_type_inode_vector) std::vector<INode*>;
%template(swig_dummy_type_const_inode_vector) std::vector<const INode*>;
%template(swig_dummy_type_axisinfo_vector) std::vector<AxisInfo>;

// SWIG does not automatically instantiate templates, so we declare these by hand
%template(kvector_t) BasicVector3D<double>;
%template(vector_kvector_t) std::vector<BasicVector3D<double>>;
%template(cvector_t) BasicVector3D<std::complex<double>>;
%template(vector_cvector_t) std::vector<BasicVector3D<std::complex<double>>>;

// SWIG workaround for using axes units the same way as they are used in cpp files
%rename(AxesUnits) AxesUnitsWrap;
%rename(RoughnessModel) RoughnessModelWrap;

%include "Core/Basics/Complex.h"
%include "Core/Parametrization/Units.h"
%include "Core/Vector/Vectors3D.h"
%include "Core/Vector/WavevectorInfo.h"

%include "Core/Beam/Beam.h"
%include "Core/Binning/Bin.h"

%include "Core/Binning/IAxis.h"
%include "Core/Binning/VariableBinAxis.h"
%include "Core/Binning/ConstKBinAxis.h"
%include "Core/Binning/CustomBinAxis.h"

%include "Core/Mask/IShape2D.h"
%include "Core/Scattering/ISample.h"
%include "Core/Instrument/IChiSquaredModule.h"
%include "Core/Fitting/IObserver.h"
%include "Core/Instrument/IIntensityFunction.h"
%include "Core/Instrument/IIntensityNormalizer.h"
%include "Core/Instrument/VarianceFunctions.h"
%include "Core/Instrument/ChiSquaredModule.h"
%include "Fit/Kernel/FitOptions.h"
%include "Core/Fitting/PyFittingCallbacks.h"

%include "Core/Fitting/FitObjective.h"
%template(addSimulationAndData) FitObjective::addSimulationAndData<std::vector<double>>;
%template(addSimulationAndData) FitObjective::addSimulationAndData<std::vector<std::vector<double>>>;

%include "Core/Tools/MathFunctions.h"
%include "Core/StandardSamples/IFactory.h"
%include "Core/Multilayer/IMultiLayerBuilder.h"
%include "Core/Parametrization/INodeVisitor.h"
%include "Core/Particle/IClusteredParticles.h"
%include "Core/Particle/Crystal.h"
%include "Core/Parametrization/Distributions.h"
%include "Core/Instrument/DetectorMask.h"
%include "Core/Mask/Ellipse.h"
%include "Core/Aggregate/FTDecayFunctions.h"
%include "Core/Aggregate/FTDistributions1D.h"
%include "Core/Aggregate/FTDistributions2D.h"
%include "Core/Binning/FixedBinAxis.h"
%include "Core/Scattering/IFormFactor.h"
%template(vector_IFormFactorPtr_t) std::vector<IFormFactor*>;
%include "Core/Scattering/IFormFactorBorn.h"
%include "Core/DecoratedFormFactor/IFormFactorDecorator.h"
%include "Core/HardParticle/FormFactorPolyhedron.h"
%include "Core/HardParticle/ProfileBar.h"
%include "Core/HardParticle/ProfileRipple1.h"
%include "Core/HardParticle/ProfileRipple2.h"
%include "Core/HardParticle/Ripples.h"

%include "Core/HardParticle/FormFactorAnisoPyramid.h"
%include "Core/HardParticle/FormFactorBox.h"
%include "Core/HardParticle/FormFactorCantellatedCube.h"
%include "Core/HardParticle/FormFactorCone.h"
%include "Core/HardParticle/FormFactorCone6.h"
%include "Core/Particle/FormFactorCrystal.h"
%include "Core/HardParticle/FormFactorCuboctahedron.h"
%include "Core/HardParticle/FormFactorCylinder.h"
%include "Core/SoftParticle/FormFactorDebyeBueche.h"
%include "Core/HardParticle/FormFactorDodecahedron.h"
%include "Core/HardParticle/FormFactorDot.h"
%include "Core/HardParticle/FormFactorEllipsoidalCylinder.h"
%include "Core/HardParticle/FormFactorFullSphere.h"
%include "Core/HardParticle/FormFactorFullSpheroid.h"
%include "Core/SoftParticle/FormFactorGauss.h"
%include "Core/HardParticle/FormFactorHemiEllipsoid.h"
%include "Core/HardParticle/FormFactorIcosahedron.h"
%include "Core/HardParticle/FormFactorLongBoxGauss.h"
%include "Core/HardParticle/FormFactorLongBoxLorentz.h"
%include "Core/SoftParticle/FormFactorLorentz.h"
%include "Core/SoftParticle/FormFactorOrnsteinZernike.h"
%include "Core/HardParticle/FormFactorPolyhedron.h"
%include "Core/HardParticle/FormFactorPrism3.h"
%include "Core/HardParticle/FormFactorPrism6.h"
%include "Core/HardParticle/FormFactorPyramid.h"
%include "Core/HardParticle/FormFactorRipple1.h"
%include "Core/HardParticle/FormFactorRipple2.h"
%include "Core/SoftParticle/FormFactorSphereGaussianRadius.h"
%include "Core/SoftParticle/FormFactorSphereLogNormalRadius.h"
%include "Core/SoftParticle/FormFactorSphereUniformRadius.h"
%include "Core/HardParticle/FormFactorTetrahedron.h"
%include "Core/HardParticle/FormFactorTruncatedCube.h"
%include "Core/HardParticle/FormFactorTruncatedSphere.h"
%include "Core/HardParticle/FormFactorTruncatedSpheroid.h"
%include "Core/Particle/FormFactorWeighted.h"

%include "Core/Beam/IFootprintFactor.h"
%include "Core/Beam/FootprintFactorGaussian.h"
%include "Core/Beam/FootprintFactorSquare.h"

%include "Core/Simulation/Simulation.h"
%include "Core/Simulation/Simulation2D.h"
%include "Core/Parametrization/SimulationOptions.h"
%include "Core/Simulation/GISASSimulation.h"
%include "Core/Instrument/IHistogram.h"
%include "Core/Instrument/Histogram1D.h"
%include "Core/Instrument/Histogram2D.h"
%include "Core/Instrument/SimulationResult.h"
%include "Core/Computation/IBackground.h"
%include "Core/Computation/ConstantBackground.h"
%include "Core/Instrument/IDetector.h"
%include "Core/Instrument/IDetector2D.h"
%include "Core/Instrument/IDetectorResolution.h"
%include "Core/Parametrization/Distributions.h"
%include "Core/Aggregate/FTDecayFunctions.h"
%include "Core/Aggregate/IInterferenceFunction.h"
%include "Core/Aggregate/ILayout.h"
%include "Core/Particle/IAbstractParticle.h"
%include "Core/Parametrization/IParameter.h" // needed?
%template(IParameterReal) IParameter<double>; // needed to avoid warning 401?
%include "Core/Particle/IParticle.h"
%include "Core/Aggregate/IPeakShape.h"
%include "Core/Instrument/IResolutionFunction2D.h"
%include "Core/Scattering/Rotations.h"
%include "Core/Lattice/ISelectionRule.h"
%include "Core/Basics/ISingleton.h"
%include "Core/Instrument/Instrument.h"
%include "Core/Instrument/IntensityDataFunctions.h"
%include "Core/InputOutput/IntensityDataIOFactory.h"
%include "Core/Aggregate/InterferenceFunction1DLattice.h"
%include "Core/Aggregate/InterferenceFunction2DLattice.h"
%include "Core/Aggregate/InterferenceFunction2DParaCrystal.h"
%include "Core/Aggregate/InterferenceFunction2DSuperLattice.h"
%include "Core/Aggregate/InterferenceFunction3DLattice.h"
%include "Core/Aggregate/InterferenceFunctionFinite2DLattice.h"
%include "Core/Aggregate/InterferenceFunctionFinite3DLattice.h"
%include "Core/Aggregate/InterferenceFunctionHardDisk.h"
%include "Core/Aggregate/InterferenceFunctionNone.h"
%include "Core/Aggregate/InterferenceFunctionRadialParaCrystal.h"
%include "Core/Aggregate/InterferenceFunctionTwin.h"
%include "Core/Binning/IPixel.h"
%include "Core/Instrument/SphericalDetector.h"
%include "Core/Instrument/IsGISAXSDetector.h"
%include "Core/Lattice/ILatticeOrientation.h"
%include "Core/Lattice/Lattice.h"
%include "Core/Lattice/LatticeUtils.h"
%include "Core/Lattice/Lattice1DParameters.h"
%include "Core/Lattice/Lattice2D.h"
%include "Core/Multilayer/Layer.h"
%include "Core/Multilayer/LayerRoughness.h"
%include "Core/Mask/Line.h"
%include "Core/Material/Material.h"
%include "Core/Material/MaterialFactoryFuncs.h"
%include "Core/Particle/MesoCrystal.h"
%include "Core/Multilayer/MultiLayer.h"
%include "Core/Multilayer/MultiLayerFuncs.h"
%include "Core/Simulation/OffSpecSimulation.h"
%include "Core/Instrument/IIntensityFunction.h"
%include "Core/Instrument/OutputData.h"
%template(IntensityData) OutputData<double>;
%include "Core/Parametrization/ParameterDistribution.h"
%include "Core/Parametrization/ParameterPool.h"
%include "Core/Parametrization/ParameterSample.h"
%template(ParameterSampleVector) std::vector<ParameterSample>;
%include "Core/Particle/Particle.h"
%include "Core/Particle/ParticleComposition.h"
%include "Core/Particle/ParticleCoreShell.h"
%include "Core/Particle/ParticleDistribution.h"
%include "Core/Aggregate/ParticleLayout.h"
%include "Core/Instrument/PyArrayImportUtils.h"
%include "Core/Computation/PoissonNoiseBackground.h"
%include "Core/Mask/Polygon.h"
%include "Core/Parametrization/RangedDistributions.h"
%include "Core/Parametrization/RealParameter.h"
%include "Core/Mask/Rectangle.h"
%include "Core/Instrument/RectangularDetector.h"
%include "Core/Instrument/ResolutionFunction2DGaussian.h"
%include "Core/Scattering/Rotations.h"
%include "Core/Multilayer/RoughnessModels.h"
%include "Core/Lattice/ISelectionRule.h"
%include "Core/Simulation/DepthProbeSimulation.h"
%include "Core/Simulation/SpecularSimulation.h"
%include "Core/Parametrization/ThreadInfo.h"
%template(SampleBuilderFactoryTemp) IFactory<std::string, IMultiLayerBuilder>;
%include "Core/StandardSamples/SampleBuilderFactory.h"
%template(SimulationFactoryTemp) IFactory<std::string, Simulation>;
%include "Core/StandardSamples/SimulationFactory.h"
%include "Core/Instrument/IUnitConverter.h"
%include "Core/Fitting/IterationInfo.h"
%include "Core/Tools/SpectrumUtils.h"

%include "Core/Instrument/ScanResolution.h"

%include "Core/Instrument/ISpecularScan.h"
%include "Core/Instrument/AngularSpecScan.h"
%include "Core/Instrument/QSpecScan.h"

%include "extendCore.i"
