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

%include "warnings.i"
%include "deprecation.i"
%include "ignoreBase.i"

// fix SWIG warning 509, certain C++ overloads create ambiguities in Python
%ignore ParticleLayout::setInterferenceFunction(IInterferenceFunction*);
%ignore ParticleLayout::setInterferenceFunction(const IInterferenceFunction*);
%ignore MesoCrystal::MesoCrystal(IClusteredParticles*, IFormFactor*);
%ignore MesoCrystal::MesoCrystal(const IClusteredParticles*, const IFormFactor*);
%ignore Instrument::setDetectorResolutionFunction(IResolutionFunction2D*);
%ignore Instrument::setDetectorResolutionFunction(const IResolutionFunction2D*);

%ignore ISampleBuilder::addParametersToExternalPool(const std::string&, ParameterPool*, int) const;
%ignore ISampleBuilder::addParametersToExternalPool(const std::string&, ParameterPool*) const;

// ignored to avoid error (todo: check whether this is really necessary)
%ignore Crystal::getTransformedLattice(const IRotation*) const;

// extra ignores for types and methods that shouldn't be visible in Python
%ignore DWBAComputation;
%ignore DecoratedLayerComputation;
%ignore FormFactorDWBA;
%ignore FormFactorDWBAPol;
%ignore ISampleVisitor::visit(const FormFactorDWBA*);
%ignore ISampleVisitor::visit(const FormFactorDWBAPol*);
%ignore ISpecularScan;
%ignore Lattice2D::ReciprocalBases;
%ignore Lattice2D::reciprocalBases();
%ignore RoughMultiLayerComputation;
%ignore SlicedFormFactorList;
%ignore SpecularComputation;

%rename(setSampleBuilderCpp) Simulation::setSampleBuilder;
%rename(setSampleBuilderCpp) SpecularSimulation::setSampleBuilder;
%rename(addSimulationAndData_cpp) FitObjective::addSimulationAndData;
%rename(evaluate_residuals_cpp) FitObjective::evaluate_residuals;
%rename(evaluate_cpp) FitObjective::evaluate;
%rename(finalize_cpp) FitObjective::finalize;
%rename(initPlot_cpp) FitObjective::initPlot;
%rename(uncertainties_cpp) FitObjective::uncertainties;
%rename(uncertaintyData_cpp) FitObjective::uncertaintyData;
%rename(containsUncertainties_cpp) FitObjective::containsUncertainties;
%rename(allPairsHaveUncertainties_cpp) FitObjective::allPairsHaveUncertainties;
%rename(MaterialProfile_cpp) MaterialProfile;

// force swig to use move ctor instead of copy ctor
%typemap(out) SlicedParticle %{
    $result = SWIG_NewPointerObj(new $1_ltype(std::move($1)), $&1_descriptor, SWIG_POINTER_OWN);
  %}

%shared_ptr(ISampleBuilder)

%feature("director") PyBuilderCallback;  // used in extendCore.i
%feature("director") PyObserverCallback; // used in extendCore.i

%feature("director") ISampleBuilder;     // used in mesocrystal1.py
%feature("director") ISample;            // needed by IFormFactor
%feature("director") IFormFactor;        // needed by IFormFactorBorn
%feature("director") IFormFactorBorn;    // used in CustomFormFactor.py
%feature("director") FitObjective;       // used in custom_objective_function.py

// Propagate python exceptions (from https://stackoverflow.com/questions/4811492)
%feature("director:except") {
    if( $error != NULL ) {
        PyObject *ptype, *pvalue, *ptraceback;
        PyErr_Fetch( &ptype, &pvalue, &ptraceback );
        PyErr_Restore( ptype, pvalue, ptraceback );
        PyErr_Print();
        Py_Exit(1);
    }
}

 // deprecations:
%rename(getArrayObsolete) IHistogram::getArray;
%extend IHistogram {
    %pythoncode %{
         @deprecated("Deprecated. Use array() instead.")
         def getArray(self):
             return self.getArrayObsolete()
    %}
 };

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
#include "Core/Histo/IntensityDataIOFactory.h"
#include "Core/Scan/AngularSpecScan.h"
#include "Core/Instrument/ChiSquaredModule.h"
#include "Core/Instrument/IChiSquaredModule.h"
#include "Core/Instrument/Instrument.h"
#include "Core/Instrument/PyArrayImportUtils.h"
#include "Core/Scan/QSpecScan.h"
#include "Core/Histo/SimulationResult.h"
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
#include "Core/RT/SimulationOptions.h"
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
%import(module="libBornAgainBase") "Base/Axis/IAxis.h"
%include "fromBase.i"

%import(module="libBornAgainParam") "Param/Base/ParameterPool.h"
%import(module="libBornAgainParam") "Param/Base/IParameterized.h"
%import(module="libBornAgainParam") "Param/Node/INode.h"
%import(module="libBornAgainParam") "Param/Distrib/ParameterDistribution.h"
%include "fromParam.i"

%template(swig_dummy_type_axisinfo_vector) std::vector<AxisInfo>;

%template(swig_dummy_type_inode_vector) std::vector<INode*>;
%template(swig_dummy_type_const_inode_vector) std::vector<const INode*>;

%template(vector_IFormFactorPtr_t) std::vector<IFormFactor*>;

%include "Fit/TestEngine/IFactory.h"
%template(SampleBuilderFactoryTemp) IFactory<std::string, ISampleBuilder>;
%template(SimulationFactoryTemp) IFactory<std::string, Simulation>;

%include "Core/Data/OutputData.h"
%template(IntensityData) OutputData<double>;

%include "Core/Fitting/FitObjective.h"
%template(addSimulationAndData) FitObjective::addSimulationAndData<std::vector<double>>;
%template(addSimulationAndData) FitObjective::addSimulationAndData<std::vector<std::vector<double>>>;

%include "BAVersion.h"

%include "Core/Mask/IShape2D.h"
%include "Core/Mask/Ellipse.h"
%include "Core/Mask/Line.h"
%include "Core/Mask/Polygon.h"
%include "Core/Mask/Rectangle.h"

%include "Core/RT/SimulationOptions.h"

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

%include "Core/Histo/IntensityDataIOFactory.h"

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
%include "Core/Histo/SimulationResult.h"
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
