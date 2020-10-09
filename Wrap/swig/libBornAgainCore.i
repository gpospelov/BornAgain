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
%include "../../auto/Wrap/doxygenCore.i"

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
%template(pvacuum_double_t) std::pair<double, double>;
%template(vector_pvacuum_double_t) std::vector<std::pair<double, double>>;

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

%{
#include "BAVersion.h"
#include "Core/Correlations/FTDecay1D.h"
#include "Core/Correlations/FTDecay2D.h"
#include "Core/Correlations/FTDistributions1D.h"
#include "Core/Correlations/FTDistributions2D.h"
#include "Core/Correlations/ILayout.h"
#include "Core/Correlations/IPeakShape.h"
#include "Core/Aggregate/IInterferenceFunction.h"
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
#include "Core/Aggregate/ParticleLayout.h"
#include "Core/Beam/Beam.h"
#include "Core/Beam/FootprintGauss.h"
#include "Core/Beam/FootprintSquare.h"
#include "Core/Axis/Bin.h"
#include "Core/Axis/ConstKBinAxis.h"
#include "Core/Axis/CustomBinAxis.h"
#include "Core/Axis/FixedBinAxis.h"
#include "Core/Axis/VariableBinAxis.h"
#include "Core/Computation/ConstantBackground.h"
#include "Core/Computation/IBackground.h"
#include "Core/Computation/MultiLayerFuncs.h"
#include "Core/Computation/PoissonNoiseBackground.h"
#include "Core/Detector/DetectorMask.h"
#include "Core/Detector/IDetector2D.h"
#include "Core/Resolution/IDetectorResolution.h"
#include "Core/Resolution/IResolutionFunction2D.h"
#include "Core/Detector/IsGISAXSDetector.h"
#include "Core/Detector/RectangularDetector.h"
#include "Core/Resolution/ResolutionFunction2DGaussian.h"
#include "Core/Resolution/ScanResolution.h"
#include "Core/Detector/SphericalDetector.h"
#include "Core/Fitting/FitObjective.h"
#include "Core/Fitting/IObserver.h"
#include "Core/Fitting/IterationInfo.h"
#include "Core/Fitting/PyFittingCallbacks.h"
#include "Core/HardParticle/FormFactorAnisoPyramid.h"
#include "Core/HardParticle/FormFactorBar.h"
#include "Core/HardParticle/FormFactorBox.h"
#include "Core/HardParticle/FormFactorCantellatedCube.h"
#include "Core/HardParticle/FormFactorCone.h"
#include "Core/HardParticle/FormFactorCone6.h"
#include "Core/HardParticle/FormFactorCosineRipple.h"
#include "Core/HardParticle/FormFactorCuboctahedron.h"
#include "Core/HardParticle/FormFactorCylinder.h"
#include "Core/HardParticle/FormFactorDodecahedron.h"
#include "Core/HardParticle/FormFactorDot.h"
#include "Core/HardParticle/FormFactorEllipsoidalCylinder.h"
#include "Core/HardParticle/FormFactorFullSphere.h"
#include "Core/HardParticle/FormFactorFullSpheroid.h"
#include "Core/HardParticle/FormFactorHemiEllipsoid.h"
#include "Core/HardParticle/FormFactorHollowSphere.h"
#include "Core/HardParticle/FormFactorIcosahedron.h"
#include "Core/HardParticle/FormFactorLongBoxGauss.h"
#include "Core/HardParticle/FormFactorLongBoxLorentz.h"
#include "Core/HardParticle/IFormFactorPolyhedron.h"
#include "Core/HardParticle/IFormFactorPrism.h"
#include "Core/HardParticle/FormFactorPrism3.h"
#include "Core/HardParticle/FormFactorPrism6.h"
#include "Core/HardParticle/FormFactorPyramid.h"
#include "Core/HardParticle/FormFactorSawtoothRipple.h"
#include "Core/HardParticle/FormFactorTetrahedron.h"
#include "Core/HardParticle/FormFactorTruncatedCube.h"
#include "Core/HardParticle/FormFactorTruncatedSphere.h"
#include "Core/HardParticle/FormFactorTruncatedSpheroid.h"
#include "Core/InputOutput/IntensityDataIOFactory.h"
#include "Core/Scan/AngularSpecScan.h"
#include "Core/Instrument/ChiSquaredModule.h"
#include "Core/Instrument/IChiSquaredModule.h"
#include "Core/Instrument/Instrument.h"
#include "Core/Instrument/PyArrayImportUtils.h"
#include "Core/Scan/QSpecScan.h"
#include "Core/Instrument/SimulationResult.h"
#include "Core/Instrument/SpectrumUtils.h"
#include "Core/Instrument/VarianceFunctions.h"
#include "Core/Histo/Histogram1D.h"
#include "Core/Histo/Histogram2D.h"
#include "Core/Histo/IHistogram.h"
#include "Core/Intensity/IIntensityFunction.h"
#include "Core/Intensity/IIntensityFunction.h"
#include "Core/Instrument/IntensityDataFunctions.h"
#include "Core/Data/OutputData.h"
#include "Core/Lattice/ILatticeOrientation.h"
#include "Core/Lattice/ISelectionRule.h"
#include "Core/Lattice/Lattice.h"
#include "Core/Lattice/Lattice2D.h"
#include "Core/Lattice/LatticeUtils.h"
#include "Core/Mask/Ellipse.h"
#include "Core/Mask/IShape2D.h"
#include "Core/Mask/Line.h"
#include "Core/Mask/Polygon.h"
#include "Core/Mask/Rectangle.h"
#include "Core/Material/MaterialFactoryFuncs.h"
#include "Core/Material/WavevectorInfo.h"
#include "Core/SampleBuilderEngine/ISampleBuilder.h"
#include "Core/Multilayer/Layer.h"
#include "Core/Multilayer/LayerInterface.h"
#include "Core/Multilayer/LayerRoughness.h"
#include "Core/Multilayer/MultiLayer.h"
#include "Core/Parametrization/Distributions.h"
#include "Core/Parametrization/ParameterDistribution.h"
#include "Core/Parametrization/ParameterSample.h"
#include "Core/Parametrization/RangedDistributions.h"
#include "Core/RT/SimulationOptions.h"
#include "Base/Utils/ThreadInfo.h"
#include "Core/Particle/Crystal.h"
#include "Core/Particle/FormFactorCrystal.h"
#include "Core/Particle/FormFactorWeighted.h"
#include "Core/Particle/IAbstractParticle.h"
#include "Core/Particle/IClusteredParticles.h"
#include "Core/Particle/IParticle.h"
#include "Core/Particle/MesoCrystal.h"
#include "Core/Particle/Particle.h"
#include "Core/Particle/ParticleComposition.h"
#include "Core/Particle/ParticleCoreShell.h"
#include "Core/Particle/ParticleDistribution.h"
#include "Core/Particle/SlicedParticle.h"
#include "Core/Scattering/IFormFactorDecorator.h"
#include "Core/Scattering/ISample.h"
#include "Core/Scattering/Rotations.h"
#include "Core/Simulation/DepthProbeSimulation.h"
#include "Core/Simulation/GISASSimulation.h"
#include "Core/Simulation/OffSpecSimulation.h"
#include "Core/Simulation/Simulation.h"
#include "Core/Simulation/Simulation2D.h"
#include "Core/Simulation/SpecularSimulation.h"
#include "Core/SoftParticle/FormFactorGauss.h"
#include "Core/SoftParticle/FormFactorSphereGaussianRadius.h"
#include "Core/SoftParticle/FormFactorSphereLogNormalRadius.h"
#include "Core/StandardSamples/SampleBuilderFactory.h"
#include "Core/Simulation/SimulationFactory.h"
#include "Fit/Kernel/FitOptions.h"
%}

// ownership

%newobject ScanResolution::scanRelativeResolution;
%newobject ScanResolution::scanAbsoluteResolution;

%newobject SimulationResult::histogram2d(Axes::Units units_type = Axes::Units::DEFAULT) const;

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

%import(module="libBornAgainBase") "Base/Types/Complex.h"
%import(module="libBornAgainBase") "Base/Types/ICloneable.h"
%import(module="libBornAgainBase") "Base/Vector/BasicVector3D.h"
%import(module="libBornAgainBase") "Base/Vector/Vectors3D.h"
%include "fromBase.i"

%import(module="libBornAgainParam") "Param/Base/ParameterPool.h"
%import(module="libBornAgainParam") "Param/Base/IParameterized.h"
%import(module="libBornAgainParam") "Param/Node/INode.h"
%include "fromParam.i"

%template(swig_dummy_type_axisinfo_vector) std::vector<AxisInfo>;

%template(swig_dummy_type_inode_vector) std::vector<INode*>;
%template(swig_dummy_type_const_inode_vector) std::vector<const INode*>;

%template(vector_IFormFactorPtr_t) std::vector<IFormFactor*>;

%include "Fit/TestEngine/IFactory.h"
%template(SampleBuilderFactoryTemp) IFactory<std::string, ISampleBuilder>;
%template(SimulationFactoryTemp) IFactory<std::string, Simulation>;

%include "Core/Parametrization/ParameterSample.h"
%template(ParameterSampleVector) std::vector<ParameterSample>;

%include "Core/Data/OutputData.h"
%template(IntensityData) OutputData<double>;

%include "Core/Fitting/FitObjective.h"
%template(addSimulationAndData) FitObjective::addSimulationAndData<std::vector<double>>;
%template(addSimulationAndData) FitObjective::addSimulationAndData<std::vector<std::vector<double>>>;

%include "BAVersion.h"

%include "Core/Axis/Bin.h"
%include "Core/Axis/IAxis.h"
%include "Core/Axis/VariableBinAxis.h"
%include "Core/Axis/ConstKBinAxis.h"
%include "Core/Axis/CustomBinAxis.h"
%include "Core/Axis/FixedBinAxis.h"

%include "Core/Pixel/IPixel.h"

%include "Core/Mask/IShape2D.h"
%include "Core/Mask/Ellipse.h"
%include "Core/Mask/Line.h"
%include "Core/Mask/Polygon.h"
%include "Core/Mask/Rectangle.h"

%include "Core/Parametrization/Distributions.h"
%include "Core/Parametrization/Distributions.h"
%include "Core/Parametrization/ParameterDistribution.h"
%include "Core/Parametrization/RangedDistributions.h"
%include "Core/RT/SimulationOptions.h"
%include "Base/Utils/ThreadInfo.h"

%include "Core/Scattering/ISample.h"
%include "Core/Scattering/IFormFactor.h"
%include "Core/Scattering/IFormFactorBorn.h"
%include "Core/Scattering/IFormFactorDecorator.h"

%include "Core/Scattering/Rotations.h"

%include "Fit/Kernel/FitOptions.h"

%include "Core/Fitting/IObserver.h"
%include "Core/Fitting/IterationInfo.h"
%include "Core/Fitting/PyFittingCallbacks.h"

%include "Core/Particle/FormFactorCrystal.h"
%include "Core/Particle/FormFactorWeighted.h"
%include "Core/Particle/IAbstractParticle.h"
%include "Core/Particle/IClusteredParticles.h"
%include "Core/Particle/Crystal.h"
%include "Core/Particle/IParticle.h"
%include "Core/Particle/MesoCrystal.h"
%include "Core/Particle/Particle.h"
%include "Core/Particle/ParticleComposition.h"
%include "Core/Particle/ParticleCoreShell.h"
%include "Core/Particle/ParticleDistribution.h"

%include "Core/Correlations/FTDecay1D.h"
%include "Core/Correlations/FTDecay2D.h"
%include "Core/Correlations/FTDistributions1D.h"
%include "Core/Correlations/FTDistributions2D.h"
%include "Core/Correlations/FTDecay1D.h"
%include "Core/Correlations/FTDecay2D.h"
%include "Core/Correlations/ILayout.h"
%include "Core/Correlations/IPeakShape.h"

%include "Core/Aggregate/IInterferenceFunction.h"
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
%include "Core/Aggregate/ParticleLayout.h"

%include "Core/Beam/Beam.h"
%include "Core/Beam/IFootprintFactor.h"
%include "Core/Beam/FootprintGauss.h"
%include "Core/Beam/FootprintSquare.h"

%include "Core/SampleBuilderEngine/ISampleBuilder.h"
%include "Core/Multilayer/Layer.h"
%include "Core/Multilayer/LayerRoughness.h"
%include "Core/Multilayer/MultiLayer.h"

// SWIG workaround for using axes units the same way as they are used in cpp files
%rename(RoughnessModel) RoughnessModelWrap;
%include "Core/Multilayer/RoughnessModels.h"

%include "Core/HardParticle/IFormFactorPolyhedron.h"
%include "Core/HardParticle/IFormFactorPrism.h"
%include "Core/HardParticle/IProfileRipple.h"

%include "Core/HardParticle/FormFactorAnisoPyramid.h"
%include "Core/HardParticle/FormFactorBox.h"
%include "Core/HardParticle/FormFactorCantellatedCube.h"
%include "Core/HardParticle/FormFactorCone.h"
%include "Core/HardParticle/FormFactorCone6.h"
%include "Core/HardParticle/FormFactorCosineRipple.h"
%include "Core/HardParticle/FormFactorCuboctahedron.h"
%include "Core/HardParticle/FormFactorCylinder.h"
%include "Core/HardParticle/FormFactorDodecahedron.h"
%include "Core/HardParticle/FormFactorDot.h"
%include "Core/HardParticle/FormFactorEllipsoidalCylinder.h"
%include "Core/HardParticle/FormFactorFullSphere.h"
%include "Core/HardParticle/FormFactorFullSpheroid.h"
%include "Core/HardParticle/FormFactorHemiEllipsoid.h"
%include "Core/HardParticle/FormFactorHollowSphere.h"
%include "Core/HardParticle/FormFactorIcosahedron.h"
%include "Core/HardParticle/FormFactorLongBoxGauss.h"
%include "Core/HardParticle/FormFactorLongBoxLorentz.h"
%include "Core/HardParticle/FormFactorPrism3.h"
%include "Core/HardParticle/FormFactorPrism6.h"
%include "Core/HardParticle/FormFactorPyramid.h"
%include "Core/HardParticle/FormFactorSawtoothRipple.h"
%include "Core/HardParticle/FormFactorTetrahedron.h"
%include "Core/HardParticle/FormFactorTruncatedCube.h"
%include "Core/HardParticle/FormFactorTruncatedSphere.h"
%include "Core/HardParticle/FormFactorTruncatedSpheroid.h"

%include "Core/SoftParticle/FormFactorGauss.h"
%include "Core/SoftParticle/FormFactorSphereGaussianRadius.h"
%include "Core/SoftParticle/FormFactorSphereLogNormalRadius.h"

%include "Core/Simulation/Simulation.h"
%include "Core/Simulation/Simulation2D.h"
%include "Core/Simulation/GISASSimulation.h"
%include "Core/Simulation/DepthProbeSimulation.h"
%include "Core/Simulation/SpecularSimulation.h"
%include "Core/Simulation/OffSpecSimulation.h"

%include "Core/Computation/IBackground.h"
%include "Core/Computation/ConstantBackground.h"
%include "Core/Computation/PoissonNoiseBackground.h"
%include "Core/Computation/MultiLayerFuncs.h"

%include "Core/InputOutput/IntensityDataIOFactory.h"

%include "Core/Detector/IDetector.h"
%include "Core/Detector/IDetector2D.h"
%include "Core/Detector/SphericalDetector.h"
%include "Core/Detector/DetectorMask.h"
%include "Core/Detector/IsGISAXSDetector.h"
%include "Core/Detector/RectangularDetector.h"

%include "Core/Resolution/IDetectorResolution.h"
%include "Core/Resolution/IResolutionFunction2D.h"
%include "Core/Resolution/ResolutionFunction2DGaussian.h"
%include "Core/Resolution/ScanResolution.h"

%include "Core/Histo/IHistogram.h"
%include "Core/Intensity/IIntensityFunction.h"
%include "Core/Unit/IUnitConverter.h"

%include "Core/Histo/Histogram1D.h"
%include "Core/Histo/Histogram2D.h"
%include "Core/Instrument/IntensityDataFunctions.h"

%include "Core/Instrument/IChiSquaredModule.h"
%include "Core/Scan/ISpecularScan.h"

%include "Core/Scan/AngularSpecScan.h"
%include "Core/Instrument/ChiSquaredModule.h"
%include "Core/Instrument/Instrument.h"
%include "Core/Instrument/PyArrayImportUtils.h"
%include "Core/Scan/QSpecScan.h"
%include "Core/Instrument/SimulationResult.h"
%include "Core/Instrument/SpectrumUtils.h"
%include "Core/Instrument/VarianceFunctions.h"

%include "Core/Lattice/ILatticeOrientation.h"
%include "Core/Lattice/ISelectionRule.h"
%include "Core/Lattice/Lattice.h"
%include "Core/Lattice/Lattice2D.h"
%include "Core/Lattice/LatticeUtils.h"

%include "Core/Material/Material.h"
%include "Core/Material/MaterialFactoryFuncs.h"
%include "Core/Material/WavevectorInfo.h"

%include "Core/StandardSamples/SampleBuilderFactory.h"
%include "Core/Simulation/SimulationFactory.h"

%include "extendCore.i"

 // deprecations:
%rename(getArrayObsolete) IHistogram::getArray;
%extend IHistogram {
    %pythoncode %{
         @deprecated("Deprecated. Use array() instead.")
         def getArray(self):
             return self.getArrayObsolete()
    %}
 };
