
// File: index.xml

// File: classAsymRippleBuilder.xml
%feature("docstring") AsymRippleBuilder "";

%feature("docstring")  AsymRippleBuilder::buildSample "MultiLayer * AsymRippleBuilder::buildSample() const
";


// File: classAveragedSlicedCylindersBuilder.xml
%feature("docstring") AveragedSlicedCylindersBuilder "

Provides exactly the same sample as  SLDSlicedCylindersBuilder, but with cylinders represented as homogeneous layers. SLD-based materials used. Assumed wavelength is 1.54 Angstrom.

C++ includes: SlicedCylindersBuilder.h
";

%feature("docstring")  AveragedSlicedCylindersBuilder::buildSample "MultiLayer * AveragedSlicedCylindersBuilder::buildSample() const
";


// File: classBasic2DLatticeBuilder.xml
%feature("docstring") Basic2DLatticeBuilder "

Builds sample: 2D lattice with arbitrary angle and different lattice length_1 and length_2.

C++ includes: TwoDimLatticeBuilder.h
";

%feature("docstring")  Basic2DLatticeBuilder::Basic2DLatticeBuilder "Basic2DLatticeBuilder::Basic2DLatticeBuilder()
";

%feature("docstring")  Basic2DLatticeBuilder::buildSample "MultiLayer * Basic2DLatticeBuilder::buildSample() const
";


// File: classBasic2DParaCrystalBuilder.xml
%feature("docstring") Basic2DParaCrystalBuilder "

Builds sample: basic two dimensional paracrystal with various probability distribution functions (PDF's). They are initialized via component service.

C++ includes: ParaCrystalBuilder.h
";

%feature("docstring")  Basic2DParaCrystalBuilder::Basic2DParaCrystalBuilder "Basic2DParaCrystalBuilder::Basic2DParaCrystalBuilder()
";

%feature("docstring")  Basic2DParaCrystalBuilder::~Basic2DParaCrystalBuilder "Basic2DParaCrystalBuilder::~Basic2DParaCrystalBuilder()
";

%feature("docstring")  Basic2DParaCrystalBuilder::buildSample "MultiLayer * Basic2DParaCrystalBuilder::buildSample() const
";

%feature("docstring")  Basic2DParaCrystalBuilder::createSampleByIndex "MultiLayer * Basic2DParaCrystalBuilder::createSampleByIndex(size_t index)
";


// File: classBoxCompositionRotateXBuilder.xml
%feature("docstring") BoxCompositionRotateXBuilder "

Two boxes in particle composition rotated in X by 90 degrees.

C++ includes: BoxCompositionBuilder.h
";

%feature("docstring")  BoxCompositionRotateXBuilder::buildSample "MultiLayer * BoxCompositionRotateXBuilder::buildSample() const
";


// File: classBoxCompositionRotateYBuilder.xml
%feature("docstring") BoxCompositionRotateYBuilder "

Two boxes in particle composition rotated in Y by 90 degrees.

C++ includes: BoxCompositionBuilder.h
";

%feature("docstring")  BoxCompositionRotateYBuilder::buildSample "MultiLayer * BoxCompositionRotateYBuilder::buildSample() const
";


// File: classBoxCompositionRotateZandYBuilder.xml
%feature("docstring") BoxCompositionRotateZandYBuilder "

Two boxes in particle composition rotated in Z and Y by 90 degrees.

C++ includes: BoxCompositionBuilder.h
";

%feature("docstring")  BoxCompositionRotateZandYBuilder::buildSample "MultiLayer * BoxCompositionRotateZandYBuilder::buildSample() const
";


// File: classBoxCompositionRotateZBuilder.xml
%feature("docstring") BoxCompositionRotateZBuilder "

Two boxes in particle composition rotated in Z by 90 degrees.

C++ includes: BoxCompositionBuilder.h
";

%feature("docstring")  BoxCompositionRotateZBuilder::buildSample "MultiLayer * BoxCompositionRotateZBuilder::buildSample() const
";


// File: classBoxesSquareLatticeBuilder.xml
%feature("docstring") BoxesSquareLatticeBuilder "

Builds sample: square boxes in a square lattice

C++ includes: BoxesSquareLatticeBuilder.h
";

%feature("docstring")  BoxesSquareLatticeBuilder::buildSample "MultiLayer * BoxesSquareLatticeBuilder::buildSample() const
";


// File: classBoxStackCompositionBuilder.xml
%feature("docstring") BoxStackCompositionBuilder "

Two different boxes are first rotated and then composed, composition is then rotated.

C++ includes: BoxCompositionBuilder.h
";

%feature("docstring")  BoxStackCompositionBuilder::buildSample "MultiLayer * BoxStackCompositionBuilder::buildSample() const
";


// File: classCenteredSquareLatticeBuilder.xml
%feature("docstring") CenteredSquareLatticeBuilder "

Builds sample: 2D lattice with different disorder (IsGISAXS example #6).

C++ includes: TwoDimLatticeBuilder.h
";

%feature("docstring")  CenteredSquareLatticeBuilder::buildSample "MultiLayer * CenteredSquareLatticeBuilder::buildSample() const
";


// File: classChi2Metric.xml
%feature("docstring") Chi2Metric "

Implementation of the standard  $ \\\\chi^2 $ metric derived from maximum likelihood with Gaussian uncertainties. With default L2 norm corresponds to the formula  \\\\[\\\\chi^2 = \\\\sum \\\\frac{(I - D)^2}{\\\\delta_D^2}\\\\]

C++ includes: ObjectiveMetric.h
";

%feature("docstring")  Chi2Metric::Chi2Metric "Chi2Metric::Chi2Metric()
";

%feature("docstring")  Chi2Metric::clone "Chi2Metric * Chi2Metric::clone() const override
";

%feature("docstring")  Chi2Metric::computeFromArrays "double Chi2Metric::computeFromArrays(std::vector< double > sim_data, std::vector< double > exp_data, std::vector< double > uncertainties, std::vector< double > weight_factors) const override

Computes metric value from data arrays. Negative values in exp_data are ignored as well as non-positive weight_factors and uncertainties. All arrays involved in the computation must be of the same size.

Parameters:
-----------

sim_data: 
array with simulated intensities.

exp_data: 
array with intensity values obtained from an experiment.

uncertainties: 
array with experimental data uncertainties.

weight_factors: 
user-defined weighting factors. Used linearly, no matter which norm is chosen. 
";

%feature("docstring")  Chi2Metric::computeFromArrays "double Chi2Metric::computeFromArrays(std::vector< double > sim_data, std::vector< double > exp_data, std::vector< double > weight_factors) const override

Computes metric value from data arrays. Negative values in exp_data are ignored as well as non-positive weight_factors. All arrays involved in the computation must be of the same size.

Parameters:
-----------

sim_data: 
array with simulated intensities.

exp_data: 
array with intensity values obtained from an experiment.

weight_factors: 
user-defined weighting factors. Used linearly, no matter which norm is chosen. 
";


// File: classChiModuleWrapper.xml
%feature("docstring") ChiModuleWrapper "

Metric wrapper for back-compaptibility with old scripts. 
";

%feature("docstring")  ChiModuleWrapper::ChiModuleWrapper "ChiModuleWrapper::ChiModuleWrapper(std::unique_ptr< IChiSquaredModule > module)
";

%feature("docstring")  ChiModuleWrapper::compute "double ChiModuleWrapper::compute(const std::vector< SimDataPair > &fit_objects, size_t n_pars) const override
";


// File: classComputationStatus.xml
%feature("docstring") ComputationStatus "

Completion status (flag and text) of a numeric computation.

C++ includes: ComputationStatus.h
";

%feature("docstring")  ComputationStatus::ComputationStatus "ComputationStatus::ComputationStatus()
";

%feature("docstring")  ComputationStatus::isCompleted "bool ComputationStatus::isCompleted() const
";

%feature("docstring")  ComputationStatus::errorMessage "std::string ComputationStatus::errorMessage() const
";

%feature("docstring")  ComputationStatus::setRunning "void ComputationStatus::setRunning()
";

%feature("docstring")  ComputationStatus::setCompleted "void ComputationStatus::setCompleted()
";

%feature("docstring")  ComputationStatus::setFailed "void ComputationStatus::setFailed()
";

%feature("docstring")  ComputationStatus::setErrorMessage "void ComputationStatus::setErrorMessage(const std::string &message)
";


// File: classConesWithLimitsDistributionBuilder.xml
%feature("docstring") ConesWithLimitsDistributionBuilder "

Cones with the distribution applied to the angle and RealLimits defined.

C++ includes: ParticleDistributionsBuilder.h
";

%feature("docstring")  ConesWithLimitsDistributionBuilder::ConesWithLimitsDistributionBuilder "ConesWithLimitsDistributionBuilder::ConesWithLimitsDistributionBuilder()
";

%feature("docstring")  ConesWithLimitsDistributionBuilder::buildSample "MultiLayer * ConesWithLimitsDistributionBuilder::buildSample() const
";


// File: classConstantBackground.xml
%feature("docstring") ConstantBackground "

Class representing a constant background signal

C++ includes: ConstantBackground.h
";

%feature("docstring")  ConstantBackground::ConstantBackground "ConstantBackground::ConstantBackground(const std::vector< double > P)
";

%feature("docstring")  ConstantBackground::ConstantBackground "ConstantBackground::ConstantBackground(double background_value)
";

%feature("docstring")  ConstantBackground::clone "ConstantBackground * ConstantBackground::clone() const override final
";

%feature("docstring")  ConstantBackground::backgroundValue "double ConstantBackground::backgroundValue() const
";

%feature("docstring")  ConstantBackground::accept "void ConstantBackground::accept(INodeVisitor *visitor) const override
";

%feature("docstring")  ConstantBackground::addBackGround "double ConstantBackground::addBackGround(double intensity) const override final
";


// File: classCoreShellBoxRotateZandYBuilder.xml
%feature("docstring") CoreShellBoxRotateZandYBuilder "

Rotation and translation of core shell box particle in 3 layers system.

C++ includes: CoreShellParticleBuilder.h
";

%feature("docstring")  CoreShellBoxRotateZandYBuilder::buildSample "MultiLayer * CoreShellBoxRotateZandYBuilder::buildSample() const
";


// File: classCoreShellParticleBuilder.xml
%feature("docstring") CoreShellParticleBuilder "

Builds sample: Core Shell Nanoparticles (IsGISAXS example #11).

C++ includes: CoreShellParticleBuilder.h
";

%feature("docstring")  CoreShellParticleBuilder::buildSample "MultiLayer * CoreShellParticleBuilder::buildSample() const
";


// File: classCosineRippleBuilder.xml
%feature("docstring") CosineRippleBuilder "

Builds sample: cosine ripple within the 1D-paracrystal model.

C++ includes: RipplesBuilder.h
";

%feature("docstring")  CosineRippleBuilder::buildSample "MultiLayer * CosineRippleBuilder::buildSample() const
";


// File: classCustomMorphologyBuilder.xml
%feature("docstring") CustomMorphologyBuilder "

Builds sample: mixture of different particles (IsGISAXS example #7).

C++ includes: CustomMorphologyBuilder.h
";

%feature("docstring")  CustomMorphologyBuilder::buildSample "MultiLayer * CustomMorphologyBuilder::buildSample() const
";


// File: classCylindersAndPrismsBuilder.xml
%feature("docstring") CylindersAndPrismsBuilder "

Builds sample: mixture of cylinders and prisms without interference (IsGISAXS example #1).

C++ includes: CylindersAndPrismsBuilder.h
";

%feature("docstring")  CylindersAndPrismsBuilder::buildSample "MultiLayer * CylindersAndPrismsBuilder::buildSample() const
";


// File: classCylindersInBABuilder.xml
%feature("docstring") CylindersInBABuilder "

Builds sample: cylinder form factor in BA (IsGISAXS example #3, part II).

C++ includes: CylindersBuilder.h
";

%feature("docstring")  CylindersInBABuilder::CylindersInBABuilder "CylindersInBABuilder::CylindersInBABuilder()
";

%feature("docstring")  CylindersInBABuilder::buildSample "MultiLayer * CylindersInBABuilder::buildSample() const
";


// File: classCylindersInDWBABuilder.xml
%feature("docstring") CylindersInDWBABuilder "

Builds sample: cylinder form factor in DWBA (IsGISAXS example #3, part I).

C++ includes: CylindersBuilder.h
";

%feature("docstring")  CylindersInDWBABuilder::CylindersInDWBABuilder "CylindersInDWBABuilder::CylindersInDWBABuilder()
";

%feature("docstring")  CylindersInDWBABuilder::buildSample "MultiLayer * CylindersInDWBABuilder::buildSample() const
";


// File: classCylindersInSSCABuilder.xml
%feature("docstring") CylindersInSSCABuilder "

Builds sample: size spacing correlation approximation (IsGISAXS example #15).

C++ includes: SizeDistributionModelsBuilder.h
";

%feature("docstring")  CylindersInSSCABuilder::buildSample "MultiLayer * CylindersInSSCABuilder::buildSample() const
";


// File: classCylindersWithSizeDistributionBuilder.xml
%feature("docstring") CylindersWithSizeDistributionBuilder "

Cylinders in BA with size distributions (IsGISAXS example #3, part II).

C++ includes: ParticleDistributionsBuilder.h
";

%feature("docstring")  CylindersWithSizeDistributionBuilder::buildSample "MultiLayer * CylindersWithSizeDistributionBuilder::buildSample() const
";


// File: classDelayedProgressCounter.xml
%feature("docstring") DelayedProgressCounter "

Counter for reporting progress (with delay interval) in a threaded computation.

C++ includes: DelayedProgressCounter.h
";

%feature("docstring")  DelayedProgressCounter::DelayedProgressCounter "DelayedProgressCounter::DelayedProgressCounter(ProgressHandler *p_progress, size_t interval)
";

%feature("docstring")  DelayedProgressCounter::~DelayedProgressCounter "DelayedProgressCounter::~DelayedProgressCounter()
";

%feature("docstring")  DelayedProgressCounter::stepProgress "void DelayedProgressCounter::stepProgress()

Increments inner counter; at regular intervals updates progress handler. 
";


// File: classDepthProbeComputation.xml
%feature("docstring") DepthProbeComputation "

Performs a single-threaded depth probe computation with given sample.

Controlled by the multi-threading machinery in Simulation::runSingleSimulation().

C++ includes: DepthProbeComputation.h
";

%feature("docstring")  DepthProbeComputation::DepthProbeComputation "DepthProbeComputation::DepthProbeComputation(const MultiLayer &multilayer, const SimulationOptions &options, ProgressHandler &progress, DepthProbeElementIter begin_it, DepthProbeElementIter end_it)
";

%feature("docstring")  DepthProbeComputation::~DepthProbeComputation "DepthProbeComputation::~DepthProbeComputation() override
";


// File: classDepthProbeComputationTerm.xml
%feature("docstring") DepthProbeComputationTerm "";

%feature("docstring")  DepthProbeComputationTerm::DepthProbeComputationTerm "DepthProbeComputationTerm::DepthProbeComputationTerm(const ProcessedSample *p_sample)
";

%feature("docstring")  DepthProbeComputationTerm::~DepthProbeComputationTerm "DepthProbeComputationTerm::~DepthProbeComputationTerm()
";

%feature("docstring")  DepthProbeComputationTerm::setProgressHandler "void DepthProbeComputationTerm::setProgressHandler(ProgressHandler *p_progress)
";

%feature("docstring")  DepthProbeComputationTerm::compute "void DepthProbeComputationTerm::compute(DepthProbeElement &elem) const
";


// File: classDepthProbeElement.xml
%feature("docstring") DepthProbeElement "";

%feature("docstring")  DepthProbeElement::DepthProbeElement "DepthProbeElement::DepthProbeElement(double wavelength, double alpha_i, const IAxis *z_positions)
";

%feature("docstring")  DepthProbeElement::DepthProbeElement "DepthProbeElement::DepthProbeElement(const DepthProbeElement &other)
";

%feature("docstring")  DepthProbeElement::DepthProbeElement "DepthProbeElement::DepthProbeElement(DepthProbeElement &&other) noexcept
";

%feature("docstring")  DepthProbeElement::~DepthProbeElement "DepthProbeElement::~DepthProbeElement()
";

%feature("docstring")  DepthProbeElement::getWavelength "double DepthProbeElement::getWavelength() const
";

%feature("docstring")  DepthProbeElement::getAlphaI "double DepthProbeElement::getAlphaI() const
";

%feature("docstring")  DepthProbeElement::getKi "kvector_t DepthProbeElement::getKi() const
";

%feature("docstring")  DepthProbeElement::setIntensities "void DepthProbeElement::setIntensities(T &&intensities)
";

%feature("docstring")  DepthProbeElement::getIntensities "const std::valarray<double>& DepthProbeElement::getIntensities() const
";

%feature("docstring")  DepthProbeElement::setZPositions "void DepthProbeElement::setZPositions(const IAxis *z_positions)
";

%feature("docstring")  DepthProbeElement::getZPositions "const IAxis* DepthProbeElement::getZPositions() const
";

%feature("docstring")  DepthProbeElement::size "size_t DepthProbeElement::size() const
";

%feature("docstring")  DepthProbeElement::setCalculationFlag "void DepthProbeElement::setCalculationFlag(bool calculation_flag)

Set calculation flag (if it's false, zero intensity is assigned to the element) 
";

%feature("docstring")  DepthProbeElement::isCalculated "bool DepthProbeElement::isCalculated() const
";


// File: classDepthProbeSimulation.xml
%feature("docstring") DepthProbeSimulation "";

%feature("docstring")  DepthProbeSimulation::DepthProbeSimulation "DepthProbeSimulation::DepthProbeSimulation()
";

%feature("docstring")  DepthProbeSimulation::~DepthProbeSimulation "DepthProbeSimulation::~DepthProbeSimulation() override
";

%feature("docstring")  DepthProbeSimulation::clone "DepthProbeSimulation * DepthProbeSimulation::clone() const override
";

%feature("docstring")  DepthProbeSimulation::accept "void DepthProbeSimulation::accept(INodeVisitor *visitor) const override final
";

%feature("docstring")  DepthProbeSimulation::result "SimulationResult DepthProbeSimulation::result() const override

Returns the results of the simulation in a format that supports unit conversion and export to numpy arrays 
";

%feature("docstring")  DepthProbeSimulation::setBeamParameters "void DepthProbeSimulation::setBeamParameters(double lambda, int nbins, double alpha_i_min, double alpha_i_max, const IFootprintFactor *beam_shape=nullptr)

Sets beam parameters with alpha_i of the beam defined in the range. 
";

%feature("docstring")  DepthProbeSimulation::setZSpan "void DepthProbeSimulation::setZSpan(size_t n_bins, double z_min, double z_max)

Set z positions for intensity calculations. Negative z's correspond to the area under sample surface. The more negative z is, the deeper layer corresponds to it. 
";

%feature("docstring")  DepthProbeSimulation::getAlphaAxis "const IAxis * DepthProbeSimulation::getAlphaAxis() const

Returns a pointer to incident angle axis. 
";

%feature("docstring")  DepthProbeSimulation::getZAxis "const IAxis * DepthProbeSimulation::getZAxis() const

Returns a pointer to z-position axis. 
";

%feature("docstring")  DepthProbeSimulation::intensityMapSize "size_t DepthProbeSimulation::intensityMapSize() const override

Returns the total number of the intensity values in the simulation result. 
";

%feature("docstring")  DepthProbeSimulation::createUnitConverter "std::unique_ptr< IUnitConverter > DepthProbeSimulation::createUnitConverter() const
";


// File: classDWBAComputation.xml
%feature("docstring") DWBAComputation "

Performs a single-threaded DWBA computation with given sample and simulation parameters.

Controlled by the multi-threading machinery in Simulation::runSingleSimulation().

C++ includes: DWBAComputation.h
";

%feature("docstring")  DWBAComputation::DWBAComputation "DWBAComputation::DWBAComputation(const MultiLayer &multilayer, const SimulationOptions &options, ProgressHandler &progress, std::vector< SimulationElement >::iterator begin_it, std::vector< SimulationElement >::iterator end_it)
";

%feature("docstring")  DWBAComputation::~DWBAComputation "DWBAComputation::~DWBAComputation() override
";


// File: classDWBASingleComputation.xml
%feature("docstring") DWBASingleComputation "

Class that handles all the computations involved in GISAS (particles, roughness,...) for a single detector bin.

Called by DWBASimulation on each detector bin.

C++ includes: DWBASingleComputation.h
";

%feature("docstring")  DWBASingleComputation::DWBASingleComputation "DWBASingleComputation::DWBASingleComputation()
";

%feature("docstring")  DWBASingleComputation::~DWBASingleComputation "DWBASingleComputation::~DWBASingleComputation()
";

%feature("docstring")  DWBASingleComputation::DWBASingleComputation "DWBASingleComputation::DWBASingleComputation(DWBASingleComputation &&other)
";

%feature("docstring")  DWBASingleComputation::setProgressHandler "void DWBASingleComputation::setProgressHandler(ProgressHandler *p_progress)
";

%feature("docstring")  DWBASingleComputation::addLayoutComputation "void DWBASingleComputation::addLayoutComputation(ParticleLayoutComputation *p_layout_comp)
";

%feature("docstring")  DWBASingleComputation::setRoughnessComputation "void DWBASingleComputation::setRoughnessComputation(RoughMultiLayerComputation *p_roughness_comp)
";

%feature("docstring")  DWBASingleComputation::setSpecularBinComputation "void DWBASingleComputation::setSpecularBinComputation(GISASSpecularComputation *p_spec_comp)
";

%feature("docstring")  DWBASingleComputation::compute "void DWBASingleComputation::compute(SimulationElement &elem) const
";

%feature("docstring")  DWBASingleComputation::regionMap "const std::map< size_t, std::vector< HomogeneousRegion > > & DWBASingleComputation::regionMap() const

Retrieves a map of regions for the calculation of averaged layers. 
";


// File: classFeNiBilayerBuilder.xml
%feature("docstring") FeNiBilayerBuilder "";

%feature("docstring")  FeNiBilayerBuilder::buildSample "MultiLayer * FeNiBilayerBuilder::buildSample() const
";


// File: classFeNiBilayerNCBuilder.xml
%feature("docstring") FeNiBilayerNCBuilder "";

%feature("docstring")  FeNiBilayerNCBuilder::buildSample "MultiLayer * FeNiBilayerNCBuilder::buildSample() const
";


// File: classFeNiBilayerSpinFlipBuilder.xml
%feature("docstring") FeNiBilayerSpinFlipBuilder "";

%feature("docstring")  FeNiBilayerSpinFlipBuilder::buildSample "MultiLayer * FeNiBilayerSpinFlipBuilder::buildSample() const
";


// File: classFeNiBilayerSpinFlipNCBuilder.xml
%feature("docstring") FeNiBilayerSpinFlipNCBuilder "";

%feature("docstring")  FeNiBilayerSpinFlipNCBuilder::buildSample "MultiLayer * FeNiBilayerSpinFlipNCBuilder::buildSample() const
";


// File: classFeNiBilayerSpinFlipTanhBuilder.xml
%feature("docstring") FeNiBilayerSpinFlipTanhBuilder "";

%feature("docstring")  FeNiBilayerSpinFlipTanhBuilder::buildSample "MultiLayer * FeNiBilayerSpinFlipTanhBuilder::buildSample() const
";


// File: classFeNiBilayerTanhBuilder.xml
%feature("docstring") FeNiBilayerTanhBuilder "";

%feature("docstring")  FeNiBilayerTanhBuilder::buildSample "MultiLayer * FeNiBilayerTanhBuilder::buildSample() const
";


// File: classFiniteSquareLatticeBuilder.xml
%feature("docstring") FiniteSquareLatticeBuilder "

Builds sample: 2D finite lattice with thermal disorder.

C++ includes: TwoDimLatticeBuilder.h
";

%feature("docstring")  FiniteSquareLatticeBuilder::buildSample "MultiLayer * FiniteSquareLatticeBuilder::buildSample() const
";


// File: classFitObjective.xml
%feature("docstring") FitObjective "

Holds vector of   SimDataPairs (experimental data and simulation results) for use in fitting.

C++ includes: FitObjective.h
";

%feature("docstring")  FitObjective::FitObjective "FitObjective::FitObjective()
";

%feature("docstring")  FitObjective::~FitObjective "FitObjective::~FitObjective()
";

%feature("docstring")  FitObjective::addSimulationAndData "void FitObjective::addSimulationAndData(simulation_builder_t builder, const OutputData< double > &data, std::unique_ptr< OutputData< double >> uncertainties, double weight=1.0)

Constructs simulation/data pair for later fit.

Parameters:
-----------

builder: 
simulation builder capable of producing simulations

data: 
experimental data array

uncertainties: 
data uncertainties array

weight: 
weight of dataset in metric calculations 
";

%feature("docstring")  FitObjective::addSimulationAndData "void FitObjective::addSimulationAndData(PyBuilderCallback &callback, const T &data, double weight=1.0)

Constructs simulation/data pair for later fit.

Parameters:
-----------

callback: 
simulation builder capable of producing simulations

data: 
experimental data array

weight: 
weight of dataset in metric calculations 
";

%feature("docstring")  FitObjective::addSimulationAndData "void FitObjective::addSimulationAndData(PyBuilderCallback &callback, const T &data, const T &uncertainties, double weight=1.0)

Constructs simulation/data pair for later fit.

Parameters:
-----------

callback: 
simulation builder capable of producing simulations

data: 
experimental data array

uncertainties: 
data uncertainties array

weight: 
weight of dataset in metric calculations 
";

%feature("docstring")  FitObjective::evaluate "double FitObjective::evaluate(const Fit::Parameters &params)
";

%feature("docstring")  FitObjective::evaluate_residuals "std::vector< double > FitObjective::evaluate_residuals(const Fit::Parameters &params)
";

%feature("docstring")  FitObjective::numberOfFitElements "size_t FitObjective::numberOfFitElements() const
";

%feature("docstring")  FitObjective::simulationResult "SimulationResult FitObjective::simulationResult(size_t i_item=0) const

Returns simulation result in the form of SimulationResult. 
";

%feature("docstring")  FitObjective::experimentalData "SimulationResult FitObjective::experimentalData(size_t i_item=0) const

Returns experimental data in the form of SimulationResult. 
";

%feature("docstring")  FitObjective::uncertaintyData "SimulationResult FitObjective::uncertaintyData(size_t i_item=0) const

Returns experimental data uncertainties in the form of SimulationResult. 
";

%feature("docstring")  FitObjective::relativeDifference "SimulationResult FitObjective::relativeDifference(size_t i_item=0) const

Returns relative difference between simulation and experimental data in the form of SimulationResult. 
";

%feature("docstring")  FitObjective::absoluteDifference "SimulationResult FitObjective::absoluteDifference(size_t i_item=0) const

Returns absolute value of difference between simulation and experimental data in the form of SimulationResult. 
";

%feature("docstring")  FitObjective::experimental_array "std::vector< double > FitObjective::experimental_array() const

Returns one dimensional array representing merged experimental data. The area outside of the region of interest is not included, masked data is nullified. 
";

%feature("docstring")  FitObjective::simulation_array "std::vector< double > FitObjective::simulation_array() const

Returns one dimensional array representing merged simulated intensities data. The area outside of the region of interest is not included, masked data is nullified. 
";

%feature("docstring")  FitObjective::uncertainties "std::vector< double > FitObjective::uncertainties() const

Returns one-dimensional array representing merged data uncertainties. The area outside of the region of interest is not included, masked data is nullified. 
";

%feature("docstring")  FitObjective::weights_array "std::vector< double > FitObjective::weights_array() const

Returns one-dimensional array representing merged user weights. The area outside of the region of interest is not included, masked data is nullified. 
";

%feature("docstring")  FitObjective::initPrint "void FitObjective::initPrint(int every_nth)

Initializes printing to standard output on every_nth fit iteration. 
";

%feature("docstring")  FitObjective::initPlot "void FitObjective::initPlot(int every_nth, PyObserverCallback &callback)

Initializes observer callback to be called on every_nth fit iteration. 
";

%feature("docstring")  FitObjective::iterationInfo "IterationInfo FitObjective::iterationInfo() const
";

%feature("docstring")  FitObjective::minimizerResult "Fit::MinimizerResult FitObjective::minimizerResult() const
";

%feature("docstring")  FitObjective::finalize "void FitObjective::finalize(const Fit::MinimizerResult &result)

Should be explicitely called on last iteration to notify all observers. 
";

%feature("docstring")  FitObjective::fitObjectCount "unsigned FitObjective::fitObjectCount() const
";

%feature("docstring")  FitObjective::run_simulations "void FitObjective::run_simulations(const Fit::Parameters &params)
";

%feature("docstring")  FitObjective::setChiSquaredModule "void FitObjective::setChiSquaredModule(const IChiSquaredModule &module)
";

%feature("docstring")  FitObjective::setObjectiveMetric "void FitObjective::setObjectiveMetric(const std::string &metric)
";

%feature("docstring")  FitObjective::setObjectiveMetric "void FitObjective::setObjectiveMetric(const std::string &metric, const std::string &norm)

Sets objective metric to the  FitObjective.

Parameters:
-----------

metric: 
metric name

norm: 
metric norm name (defaults to L2-norm) 
";

%feature("docstring")  FitObjective::containsUncertainties "bool FitObjective::containsUncertainties(size_t i_item) const

Returns true if the specified DataPair element contains uncertainties. 
";

%feature("docstring")  FitObjective::allPairsHaveUncertainties "bool FitObjective::allPairsHaveUncertainties() const

Returns true if all the data pairs in  FitObjective instance contain uncertainties. 
";

%feature("docstring")  FitObjective::dataPair "const SimDataPair & FitObjective::dataPair(size_t i_item=0) const

Returns a reference to i-th  SimDataPair. 
";

%feature("docstring")  FitObjective::initPlot "void FitObjective::initPlot(int every_nth, fit_observer_t observer)
";

%feature("docstring")  FitObjective::isCompleted "bool FitObjective::isCompleted() const
";

%feature("docstring")  FitObjective::interruptFitting "void FitObjective::interruptFitting()
";

%feature("docstring")  FitObjective::isInterrupted "bool FitObjective::isInterrupted() const
";

%feature("docstring")  FitObjective::isFirstIteration "bool FitObjective::isFirstIteration() const
";

%feature("docstring")  FitObjective::setObjectiveMetric "void FitObjective::setObjectiveMetric(std::unique_ptr< ObjectiveMetric > metric)
";


// File: classFitObserver.xml
%feature("docstring") FitObserver "

Contains collection of observers and call them at specified intervals. Each observer will be called at first iteration and every-nth iterations.

C++ includes: FitObserver.h
";

%feature("docstring")  FitObserver::FitObserver "FitObserver< T >::FitObserver()
";

%feature("docstring")  FitObserver::addObserver "void FitObserver< T >::addObserver(int every_nth, observer_t observer)

Adds observer to the list.

Parameters:
-----------

every_nth: 
An observer function will be called every_nth iterations.

observer: 
Observer function to be called. 
";

%feature("docstring")  FitObserver::notify "void FitObserver< T >::notify(const T &data)

Notifies all observers at their personally specified intervals.

Parameters:
-----------

data: 
The data which will be passed to the observer. 
";

%feature("docstring")  FitObserver::notify_all "void FitObserver< T >::notify_all(const T &data)
";


// File: classFitPrintService.xml
%feature("docstring") FitPrintService "

Prints fit statistics to standard output during minimizer iterations.

C++ includes: FitPrintService.h
";

%feature("docstring")  FitPrintService::FitPrintService "FitPrintService::FitPrintService()
";

%feature("docstring")  FitPrintService::print "void FitPrintService::print(const FitObjective &objective)
";


// File: classFitStatus.xml
%feature("docstring") FitStatus "

Contains status of the fitting (running, interupted etc) and all intermediate information which has to be collected during the fit. Owned by  FitObjective.

C++ includes: FitStatus.h
";

%feature("docstring")  FitStatus::FitStatus "FitStatus::FitStatus(const FitObjective *fit_objective)
";

%feature("docstring")  FitStatus::~FitStatus "FitStatus::~FitStatus()
";

%feature("docstring")  FitStatus::setInterrupted "void FitStatus::setInterrupted()
";

%feature("docstring")  FitStatus::isInterrupted "bool FitStatus::isInterrupted() const
";

%feature("docstring")  FitStatus::isCompleted "bool FitStatus::isCompleted() const
";

%feature("docstring")  FitStatus::update "void FitStatus::update(const Fit::Parameters &params, double chi2)
";

%feature("docstring")  FitStatus::initPrint "void FitStatus::initPrint(int every_nth)
";

%feature("docstring")  FitStatus::addObserver "void FitStatus::addObserver(int every_nth, fit_observer_t)
";

%feature("docstring")  FitStatus::iterationInfo "IterationInfo FitStatus::iterationInfo() const
";

%feature("docstring")  FitStatus::minimizerResult "Fit::MinimizerResult FitStatus::minimizerResult() const
";

%feature("docstring")  FitStatus::finalize "void FitStatus::finalize(const Fit::MinimizerResult &result)

Should be explicitely called on last iteration to notify all observers. 
";


// File: classFixedBuilder.xml
%feature("docstring") FixedBuilder "

A trivial sample builder class that builds a fixed sample.

C++ includes: FixedBuilder.h
";

%feature("docstring")  FixedBuilder::FixedBuilder "FixedBuilder::FixedBuilder()=delete
";

%feature("docstring")  FixedBuilder::FixedBuilder "FixedBuilder::FixedBuilder(const MultiLayer &)
";

%feature("docstring")  FixedBuilder::buildSample "MultiLayer * FixedBuilder::buildSample() const
";


// File: classFormFactorComponents.xml
%feature("docstring") FormFactorComponents "

Predefined form factors for functional tests.

C++ includes: SampleComponents.h
";

%feature("docstring")  FormFactorComponents::FormFactorComponents "FormFactorComponents::FormFactorComponents()
";


// File: classFTDistribution2DComponents.xml
%feature("docstring") FTDistribution2DComponents "

Predefined Fourier transformed distributions for functional tests.

C++ includes: SampleComponents.h
";

%feature("docstring")  FTDistribution2DComponents::FTDistribution2DComponents "FTDistribution2DComponents::FTDistribution2DComponents()
";


// File: classGISASSimulation.xml
%feature("docstring") GISASSimulation "

Main class to run a Grazing-Incidence Small-Angle Scattering simulation.

C++ includes: GISASSimulation.h
";

%feature("docstring")  GISASSimulation::GISASSimulation "GISASSimulation::GISASSimulation()
";

%feature("docstring")  GISASSimulation::~GISASSimulation "GISASSimulation::~GISASSimulation()
";

%feature("docstring")  GISASSimulation::clone "GISASSimulation* GISASSimulation::clone() const override
";

%feature("docstring")  GISASSimulation::accept "void GISASSimulation::accept(INodeVisitor *visitor) const override
";

%feature("docstring")  GISASSimulation::prepareSimulation "void GISASSimulation::prepareSimulation() override

Put into a clean state for running a simulation. 
";

%feature("docstring")  GISASSimulation::result "SimulationResult GISASSimulation::result() const override

Returns the results of the simulation in a format that supports unit conversion and export to numpy arrays 
";

%feature("docstring")  GISASSimulation::setBeamParameters "void GISASSimulation::setBeamParameters(double wavelength, double alpha_i, double phi_i)

Sets beam parameters from here (forwarded to Instrument) 
";

%feature("docstring")  GISASSimulation::intensityMapSize "size_t GISASSimulation::intensityMapSize() const override

Returns the total number of the intensity values in the simulation result. 
";


// File: classGISASSpecularComputation.xml
%feature("docstring") GISASSpecularComputation "

Computes the specular signal in the bin where q_parallel = 0. Used by  DWBAComputation.

C++ includes: GISASSpecularComputation.h
";

%feature("docstring")  GISASSpecularComputation::GISASSpecularComputation "GISASSpecularComputation::GISASSpecularComputation(const IFresnelMap *p_fresnel_map)
";

%feature("docstring")  GISASSpecularComputation::compute "void GISASSpecularComputation::compute(SimulationElement &elem) const
";


// File: classHardDiskBuilder.xml
%feature("docstring") HardDiskBuilder "

Builds sample: cylinders with hard disk Percus-Yevick interference.

C++ includes: PercusYevickBuilder.h
";

%feature("docstring")  HardDiskBuilder::buildSample "MultiLayer * HardDiskBuilder::buildSample() const
";


// File: classHexParaCrystalBuilder.xml
%feature("docstring") HexParaCrystalBuilder "

Builds sample: cylinders with 2DDL structure factor (IsGISAXS example #4).

C++ includes: ParaCrystalBuilder.h
";

%feature("docstring")  HexParaCrystalBuilder::buildSample "MultiLayer * HexParaCrystalBuilder::buildSample() const
";


// File: classHomogeneousMultilayerBuilder.xml
%feature("docstring") HomogeneousMultilayerBuilder "

Builds a sample with 10 interchanging homogeneous layers of Ti and Ni on silicone substrate. Ti is 70 angstroms thick, Ni is 30 angstroms thick. No absorption, no roughness, target wavelength is 1.54 angstroms.

C++ includes: HomogeneousMultilayerBuilder.h
";

%feature("docstring")  HomogeneousMultilayerBuilder::buildSample "MultiLayer * HomogeneousMultilayerBuilder::buildSample() const
";


// File: classIBackground.xml
%feature("docstring") IBackground "

Interface for a simulating the background signal

C++ includes: IBackground.h
";

%feature("docstring")  IBackground::IBackground "IBackground::IBackground(const NodeMeta &meta, const std::vector< double > &PValues)
";

%feature("docstring")  IBackground::~IBackground "IBackground::~IBackground()
";

%feature("docstring")  IBackground::clone "virtual IBackground* IBackground::clone() const =0
";

%feature("docstring")  IBackground::addBackGround "virtual double IBackground::addBackGround(double element) const =0
";


// File: classIComputation.xml
%feature("docstring") IComputation "

Interface for a single-threaded computation with given range of SimulationElements and  ProgressHandler.

Controlled by the multi-threading machinery in Simulation::runSingleSimulation().

C++ includes: IComputation.h
";

%feature("docstring")  IComputation::IComputation "IComputation::IComputation(const MultiLayer &sample, const SimulationOptions &options, ProgressHandler &progress)
";

%feature("docstring")  IComputation::~IComputation "IComputation::~IComputation()
";

%feature("docstring")  IComputation::run "void IComputation::run()
";

%feature("docstring")  IComputation::isCompleted "bool IComputation::isCompleted() const
";

%feature("docstring")  IComputation::errorMessage "std::string IComputation::errorMessage() const
";


// File: classIMetricWrapper.xml
%feature("docstring") IMetricWrapper "";

%feature("docstring")  IMetricWrapper::~IMetricWrapper "IMetricWrapper::~IMetricWrapper()
";

%feature("docstring")  IMetricWrapper::compute "virtual double IMetricWrapper::compute(const std::vector< SimDataPair > &fit_objects, size_t n_pars) const =0
";


// File: classIObservable.xml
%feature("docstring") IObservable "

Observable interface from Observer pattern

C++ includes: IObserver.h
";

%feature("docstring")  IObservable::~IObservable "IObservable::~IObservable()
";

%feature("docstring")  IObservable::attachObserver "void IObservable::attachObserver(observer_t obj)

attach observer to the list of observers 
";

%feature("docstring")  IObservable::notifyObservers "void IObservable::notifyObservers()

notify observers about change in status 
";


// File: classIObserver.xml
%feature("docstring") IObserver "

Observer interface from Observer pattern.

C++ includes: IObserver.h
";

%feature("docstring")  IObserver::~IObserver "IObserver::~IObserver()
";

%feature("docstring")  IObserver::notify "virtual void IObserver::notify(IObservable *subject)=0

method which is used by observable subject to notify change in status 
";


// File: classIRegistry.xml
%feature("docstring") IRegistry "

Templated object registry.

C++ includes: IRegistry.h
";

%feature("docstring")  IRegistry::getItem "const ValueType* IRegistry< ValueType >::getItem(const std::string &key) const
";

%feature("docstring")  IRegistry::keys "std::vector<std::string> IRegistry< ValueType >::keys() const
";

%feature("docstring")  IRegistry::size "size_t IRegistry< ValueType >::size() const
";


// File: classISampleBuilder.xml
%feature("docstring") ISampleBuilder "

Interface to the class capable to build samples to simulate.

C++ includes: ISampleBuilder.h
";

%feature("docstring")  ISampleBuilder::ISampleBuilder "ISampleBuilder::ISampleBuilder()
";

%feature("docstring")  ISampleBuilder::~ISampleBuilder "ISampleBuilder::~ISampleBuilder()
";

%feature("docstring")  ISampleBuilder::buildSample "virtual MultiLayer* ISampleBuilder::buildSample() const =0
";

%feature("docstring")  ISampleBuilder::createSampleByIndex "virtual MultiLayer* ISampleBuilder::createSampleByIndex(size_t)
";

%feature("docstring")  ISampleBuilder::size "virtual size_t ISampleBuilder::size()
";


// File: classIterationInfo.xml
%feature("docstring") IterationInfo "

Stores fit iteration info to track fit flow from various observers. Used in context of  FitObjective.

C++ includes: IterationInfo.h
";

%feature("docstring")  IterationInfo::IterationInfo "IterationInfo::IterationInfo()
";

%feature("docstring")  IterationInfo::update "void IterationInfo::update(const Fit::Parameters &params, double chi2)
";

%feature("docstring")  IterationInfo::iterationCount "unsigned IterationInfo::iterationCount() const

Returns current number of minimizer iterations. 
";

%feature("docstring")  IterationInfo::chi2 "double IterationInfo::chi2() const
";

%feature("docstring")  IterationInfo::parameters "Fit::Parameters IterationInfo::parameters() const
";

%feature("docstring")  IterationInfo::parameterMap "std::map< std::string, double > IterationInfo::parameterMap() const

Returns map of fit parameter names and its current values. 
";


// File: classLabelMap.xml
%feature("docstring") LabelMap "";


// File: classLargeCylindersInDWBABuilder.xml
%feature("docstring") LargeCylindersInDWBABuilder "

Builds sample with large cylinders for MC integration tests.

C++ includes: CylindersBuilder.h
";

%feature("docstring")  LargeCylindersInDWBABuilder::LargeCylindersInDWBABuilder "LargeCylindersInDWBABuilder::LargeCylindersInDWBABuilder()
";

%feature("docstring")  LargeCylindersInDWBABuilder::buildSample "MultiLayer * LargeCylindersInDWBABuilder::buildSample() const
";


// File: classLattice1DBuilder.xml
%feature("docstring") Lattice1DBuilder "

Builds sample: cylinders with 1DDL structure factor.

C++ includes: LatticeBuilder.h
";

%feature("docstring")  Lattice1DBuilder::buildSample "MultiLayer * Lattice1DBuilder::buildSample() const
";


// File: classLayersWithAbsorptionBuilder.xml
%feature("docstring") LayersWithAbsorptionBuilder "

The  LayersWithAbsorptionBuilder class generates a multilayer with 3 layers with absorption (refractive index has imaginary part).The middle layer is populated with particles. Requires IComponentService which generates form factors, used for bulk form factors testing.

C++ includes: LayersWithAbsorptionBuilder.h
";

%feature("docstring")  LayersWithAbsorptionBuilder::LayersWithAbsorptionBuilder "LayersWithAbsorptionBuilder::LayersWithAbsorptionBuilder()
";

%feature("docstring")  LayersWithAbsorptionBuilder::~LayersWithAbsorptionBuilder "LayersWithAbsorptionBuilder::~LayersWithAbsorptionBuilder()
";

%feature("docstring")  LayersWithAbsorptionBuilder::buildSample "MultiLayer * LayersWithAbsorptionBuilder::buildSample() const
";

%feature("docstring")  LayersWithAbsorptionBuilder::createSampleByIndex "MultiLayer * LayersWithAbsorptionBuilder::createSampleByIndex(size_t index)
";

%feature("docstring")  LayersWithAbsorptionBuilder::size "size_t LayersWithAbsorptionBuilder::size()
";


// File: classLayersWithAbsorptionBySLDBuilder.xml
%feature("docstring") LayersWithAbsorptionBySLDBuilder "

The  LayersWithAbsorptionBySLDBuilder class generates a multilayer with 3 layers with absorption (refractive index has imaginary part). //! The middle layer is populated with particles. MaterialBySLD is used to generate maaterials

C++ includes: LayersWithAbsorptionBySLDBuilder.h
";

%feature("docstring")  LayersWithAbsorptionBySLDBuilder::buildSample "MultiLayer * LayersWithAbsorptionBySLDBuilder::buildSample() const
";


// File: classLayoutStrategyBuilder.xml
%feature("docstring") LayoutStrategyBuilder "

Methods to generate a simulation strategy for a  ParticleLayoutComputation.

C++ includes: LayoutStrategyBuilder.h
";

%feature("docstring")  LayoutStrategyBuilder::LayoutStrategyBuilder "LayoutStrategyBuilder::LayoutStrategyBuilder(const ProcessedLayout *p_layout, const SimulationOptions &sim_params, bool polarized)
";

%feature("docstring")  LayoutStrategyBuilder::~LayoutStrategyBuilder "LayoutStrategyBuilder::~LayoutStrategyBuilder()
";

%feature("docstring")  LayoutStrategyBuilder::releaseStrategy "IInterferenceFunctionStrategy * LayoutStrategyBuilder::releaseStrategy()
";


// File: classLinkedBoxDistributionBuilder.xml
%feature("docstring") LinkedBoxDistributionBuilder "

Distribution of boxes with main parameter and two linked parameters.

C++ includes: ParticleDistributionsBuilder.h
";

%feature("docstring")  LinkedBoxDistributionBuilder::LinkedBoxDistributionBuilder "LinkedBoxDistributionBuilder::LinkedBoxDistributionBuilder()=default
";

%feature("docstring")  LinkedBoxDistributionBuilder::buildSample "MultiLayer * LinkedBoxDistributionBuilder::buildSample() const
";


// File: classLogMetric.xml
%feature("docstring") LogMetric "

Implementation of the standard  $ \\\\chi^2 $ metric with intensity  $I$ and experimental data  $D$ being replaced by  $ \\\\log_{10} I $ and  $\\\\log_{10} D$ accordingly. With default L2 norm corresponds to the formula  \\\\[\\\\chi^2 = \\\\sum \\\\frac{(\\\\log_{10} I - log_{10} D)^2 D^2 \\\\ln^2{10}}{\\\\delta_D^2}\\\\]

C++ includes: ObjectiveMetric.h
";

%feature("docstring")  LogMetric::LogMetric "LogMetric::LogMetric()
";

%feature("docstring")  LogMetric::clone "LogMetric * LogMetric::clone() const override
";

%feature("docstring")  LogMetric::computeFromArrays "double LogMetric::computeFromArrays(std::vector< double > sim_data, std::vector< double > exp_data, std::vector< double > uncertainties, std::vector< double > weight_factors) const override

Computes metric value from data arrays. Negative values in exp_data are ignored as well as non-positive weight_factors and uncertainties. All arrays involved in the computation must be of the same size.

Parameters:
-----------

sim_data: 
array with simulated intensities.

exp_data: 
array with intensity values obtained from an experiment.

uncertainties: 
array with experimental data uncertainties.

weight_factors: 
user-defined weighting factors. Used linearly, no matter which norm is chosen. 
";

%feature("docstring")  LogMetric::computeFromArrays "double LogMetric::computeFromArrays(std::vector< double > sim_data, std::vector< double > exp_data, std::vector< double > weight_factors) const override

Computes metric value from data arrays. Negative values in exp_data are ignored as well as non-positive weight_factors. All arrays involved in the computation must be of the same size.

Parameters:
-----------

sim_data: 
array with simulated intensities.

exp_data: 
array with intensity values obtained from an experiment.

weight_factors: 
user-defined weighting factors. Used linearly, no matter which norm is chosen. 
";


// File: classMagneticCylindersBuilder.xml
%feature("docstring") MagneticCylindersBuilder "

Builds sample: cylinders with magnetic material and non-zero magnetic field.

C++ includes: MagneticParticlesBuilder.h
";

%feature("docstring")  MagneticCylindersBuilder::buildSample "MultiLayer * MagneticCylindersBuilder::buildSample() const
";


// File: classMagneticLayerBuilder.xml
%feature("docstring") MagneticLayerBuilder "

Builds sample: magnetic spheres in a magnetized layer on a non-magnetized substrate.

C++ includes: MagneticLayersBuilder.h
";

%feature("docstring")  MagneticLayerBuilder::buildSample "MultiLayer * MagneticLayerBuilder::buildSample() const
";


// File: classMagneticParticleZeroFieldBuilder.xml
%feature("docstring") MagneticParticleZeroFieldBuilder "

Builds sample: cylinders with magnetic material and zero magnetic field.

C++ includes: MagneticParticlesBuilder.h
";

%feature("docstring")  MagneticParticleZeroFieldBuilder::buildSample "MultiLayer * MagneticParticleZeroFieldBuilder::buildSample() const
";


// File: classMagneticRotationBuilder.xml
%feature("docstring") MagneticRotationBuilder "

Builds sample: rotated magnetic spheres in substrate layer with a unit magnetic field.

C++ includes: MagneticLayersBuilder.h
";

%feature("docstring")  MagneticRotationBuilder::buildSample "MultiLayer * MagneticRotationBuilder::buildSample() const
";


// File: classMagneticSpheresBuilder.xml
%feature("docstring") MagneticSpheresBuilder "

Builds sample: spheres with magnetization inside substrate.

C++ includes: MagneticParticlesBuilder.h
";

%feature("docstring")  MagneticSpheresBuilder::buildSample "MultiLayer * MagneticSpheresBuilder::buildSample() const
";


// File: classMagneticSubstrateZeroFieldBuilder.xml
%feature("docstring") MagneticSubstrateZeroFieldBuilder "

Builds sample: spheres in substrate layer with a zero magnetic field.

C++ includes: MagneticLayersBuilder.h
";

%feature("docstring")  MagneticSubstrateZeroFieldBuilder::buildSample "MultiLayer * MagneticSubstrateZeroFieldBuilder::buildSample() const
";


// File: structPlainMultiLayerBySLDBuilder_1_1MaterialData.xml


// File: classMesoCrystalBuilder.xml
%feature("docstring") MesoCrystalBuilder "

Builds sample: cylindrical mesocrystal composed of spheres in a cubic lattice.

C++ includes: MesoCrystalBuilder.h
";

%feature("docstring")  MesoCrystalBuilder::buildSample "MultiLayer * MesoCrystalBuilder::buildSample() const
";


// File: classMPISimulation.xml
%feature("docstring") MPISimulation "";

%feature("docstring")  MPISimulation::runSimulation "void MPISimulation::runSimulation(Simulation *simulation)
";


// File: classMultiLayerWithNCRoughnessBuilder.xml
%feature("docstring") MultiLayerWithNCRoughnessBuilder "

Builds sample: layers with correlated roughness.

C++ includes: MultiLayerWithNCRoughnessBuilder.h
";

%feature("docstring")  MultiLayerWithNCRoughnessBuilder::buildSample "MultiLayer * MultiLayerWithNCRoughnessBuilder::buildSample() const override
";


// File: classMultiLayerWithRoughnessBuilder.xml
%feature("docstring") MultiLayerWithRoughnessBuilder "

Builds sample: layers with correlated roughness.

C++ includes: MultiLayerWithRoughnessBuilder.h
";

%feature("docstring")  MultiLayerWithRoughnessBuilder::buildSample "MultiLayer * MultiLayerWithRoughnessBuilder::buildSample() const
";


// File: classMultipleLayoutBuilder.xml
%feature("docstring") MultipleLayoutBuilder "

Builds sample: mixture of cylinders and prisms without interference, using multiple particle layouts

C++ includes: MultipleLayoutBuilder.h
";

%feature("docstring")  MultipleLayoutBuilder::buildSample "MultiLayer * MultipleLayoutBuilder::buildSample() const
";


// File: classObjectiveMetric.xml
%feature("docstring") ObjectiveMetric "

Base class for metric implementations.

C++ includes: ObjectiveMetric.h
";

%feature("docstring")  ObjectiveMetric::ObjectiveMetric "ObjectiveMetric::ObjectiveMetric(std::function< double(double)> norm)
";

%feature("docstring")  ObjectiveMetric::clone "ObjectiveMetric* ObjectiveMetric::clone() const override=0
";

%feature("docstring")  ObjectiveMetric::compute "double ObjectiveMetric::compute(const SimDataPair &data_pair, bool use_weights) const

Computes metric value from  SimDataPair object. Calls computeFromArrays internally.

Parameters:
-----------

data_pair: 
 SimDataPair object. Can optionally contain data uncertainties

use_weights: 
boolean, defines if data uncertainties should be taken into account 
";

%feature("docstring")  ObjectiveMetric::computeFromArrays "virtual double ObjectiveMetric::computeFromArrays(std::vector< double > sim_data, std::vector< double > exp_data, std::vector< double > uncertainties, std::vector< double > weight_factors) const =0

Computes metric value from data arrays. Negative values in exp_data are ignored as well as non-positive weight_factors and uncertainties. All arrays involved in the computation must be of the same size.

Parameters:
-----------

sim_data: 
array with simulated intensities.

exp_data: 
array with intensity values obtained from an experiment.

uncertainties: 
array with experimental data uncertainties.

weight_factors: 
user-defined weighting factors. Used linearly, no matter which norm is chosen. 
";

%feature("docstring")  ObjectiveMetric::computeFromArrays "virtual double ObjectiveMetric::computeFromArrays(std::vector< double > sim_data, std::vector< double > exp_data, std::vector< double > weight_factors) const =0

Computes metric value from data arrays. Negative values in exp_data are ignored as well as non-positive weight_factors. All arrays involved in the computation must be of the same size.

Parameters:
-----------

sim_data: 
array with simulated intensities.

exp_data: 
array with intensity values obtained from an experiment.

weight_factors: 
user-defined weighting factors. Used linearly, no matter which norm is chosen. 
";

%feature("docstring")  ObjectiveMetric::setNorm "void ObjectiveMetric::setNorm(std::function< double(double)> norm)
";

%feature("docstring")  ObjectiveMetric::norm "auto ObjectiveMetric::norm() const

Returns a copy of the normalization function used. 
";


// File: classObjectiveMetricWrapper.xml
%feature("docstring") ObjectiveMetricWrapper "";

%feature("docstring")  ObjectiveMetricWrapper::ObjectiveMetricWrapper "ObjectiveMetricWrapper::ObjectiveMetricWrapper(std::unique_ptr< ObjectiveMetric > module)
";

%feature("docstring")  ObjectiveMetricWrapper::compute "double ObjectiveMetricWrapper::compute(const std::vector< SimDataPair > &fit_objects, size_t n_pars) const override
";


// File: classFitObserver_1_1ObserverData.xml


// File: classOffSpecSimulation.xml
%feature("docstring") OffSpecSimulation "

Main class to run an off-specular simulation.

C++ includes: OffSpecSimulation.h
";

%feature("docstring")  OffSpecSimulation::OffSpecSimulation "OffSpecSimulation::OffSpecSimulation()
";

%feature("docstring")  OffSpecSimulation::~OffSpecSimulation "OffSpecSimulation::~OffSpecSimulation() final
";

%feature("docstring")  OffSpecSimulation::clone "OffSpecSimulation* OffSpecSimulation::clone() const override
";

%feature("docstring")  OffSpecSimulation::accept "void OffSpecSimulation::accept(INodeVisitor *visitor) const final
";

%feature("docstring")  OffSpecSimulation::prepareSimulation "void OffSpecSimulation::prepareSimulation() final

Put into a clean state for running a simulation. 
";

%feature("docstring")  OffSpecSimulation::result "SimulationResult OffSpecSimulation::result() const override

Returns the results of the simulation in a format that supports unit conversion and export to numpy arrays 
";

%feature("docstring")  OffSpecSimulation::setBeamParameters "void OffSpecSimulation::setBeamParameters(double wavelength, const IAxis &alpha_axis, double phi_i)

Sets beam parameters from here (forwarded to Instrument) 
";

%feature("docstring")  OffSpecSimulation::beamAxis "const IAxis * OffSpecSimulation::beamAxis() const

Returns axis of the beam. 
";

%feature("docstring")  OffSpecSimulation::createUnitConverter "std::unique_ptr< IUnitConverter > OffSpecSimulation::createUnitConverter() const
";

%feature("docstring")  OffSpecSimulation::intensityMapSize "size_t OffSpecSimulation::intensityMapSize() const override

Returns the total number of the intensity values in the simulation result. 
";


// File: classOrderedMap.xml
%feature("docstring") OrderedMap "

Ordered map which saves the order of insertion.

C++ includes: OrderedMap.h
";

%feature("docstring")  OrderedMap::OrderedMap "OrderedMap< Key, Object >::OrderedMap()
";

%feature("docstring")  OrderedMap::~OrderedMap "virtual OrderedMap< Key, Object >::~OrderedMap()
";

%feature("docstring")  OrderedMap::clear "void OrderedMap< Key, Object >::clear()
";

%feature("docstring")  OrderedMap::begin "const_iterator OrderedMap< Key, Object >::begin() const
";

%feature("docstring")  OrderedMap::end "const_iterator OrderedMap< Key, Object >::end() const
";

%feature("docstring")  OrderedMap::begin "iterator OrderedMap< Key, Object >::begin()
";

%feature("docstring")  OrderedMap::end "iterator OrderedMap< Key, Object >::end()
";

%feature("docstring")  OrderedMap::size "size_t OrderedMap< Key, Object >::size() const
";

%feature("docstring")  OrderedMap::empty "bool OrderedMap< Key, Object >::empty() const
";

%feature("docstring")  OrderedMap::insert "void OrderedMap< Key, Object >::insert(const Key &key, const Object &object)
";

%feature("docstring")  OrderedMap::find "iterator OrderedMap< Key, Object >::find(const Key &key)
";

%feature("docstring")  OrderedMap::find "const_iterator OrderedMap< Key, Object >::find(const Key &key) const
";

%feature("docstring")  OrderedMap::erase "size_t OrderedMap< Key, Object >::erase(const Key &key)
";

%feature("docstring")  OrderedMap::value "const Object& OrderedMap< Key, Object >::value(const Key &key) const
";


// File: classOutputData.xml
%feature("docstring") OutputData "";


// File: classParticleCompositionBuilder.xml
%feature("docstring") ParticleCompositionBuilder "

Builds sample: two layers of spheres at hex lattice.

C++ includes: ParticleCompositionBuilder.h
";

%feature("docstring")  ParticleCompositionBuilder::buildSample "MultiLayer * ParticleCompositionBuilder::buildSample() const
";


// File: classParticleInVacuumBuilder.xml
%feature("docstring") ParticleInVacuumBuilder "

The  ParticleInVacuumBuilder class generates a multilayer with single vacuum layer populated with particles of certain types. Requires IComponentService which generates form factors, used for bulk form factors testing.

C++ includes: ParticleInVacuumBuilder.h
";

%feature("docstring")  ParticleInVacuumBuilder::ParticleInVacuumBuilder "ParticleInVacuumBuilder::ParticleInVacuumBuilder()
";

%feature("docstring")  ParticleInVacuumBuilder::buildSample "MultiLayer * ParticleInVacuumBuilder::buildSample() const
";

%feature("docstring")  ParticleInVacuumBuilder::createSampleByIndex "MultiLayer * ParticleInVacuumBuilder::createSampleByIndex(size_t index)
";

%feature("docstring")  ParticleInVacuumBuilder::size "size_t ParticleInVacuumBuilder::size()
";


// File: classParticleLayoutComputation.xml
%feature("docstring") ParticleLayoutComputation "

Computes the scattering contribution from one particle layout. Used by  DWBAComputation.

C++ includes: ParticleLayoutComputation.h
";

%feature("docstring")  ParticleLayoutComputation::ParticleLayoutComputation "ParticleLayoutComputation::ParticleLayoutComputation(const ProcessedLayout *p_layout, const SimulationOptions &options, bool polarized)
";

%feature("docstring")  ParticleLayoutComputation::~ParticleLayoutComputation "ParticleLayoutComputation::~ParticleLayoutComputation()
";

%feature("docstring")  ParticleLayoutComputation::compute "void ParticleLayoutComputation::compute(SimulationElement &elem) const
";

%feature("docstring")  ParticleLayoutComputation::mergeRegionMap "void ParticleLayoutComputation::mergeRegionMap(std::map< size_t, std::vector< HomogeneousRegion >> &region_map) const

Merges its region map into the given one (notice non-const reference parameter) 
";


// File: classPlainMultiLayerBySLDBuilder.xml
%feature("docstring") PlainMultiLayerBySLDBuilder "

Builds a sample with 10 interchanging homogeneous layers of Ti and Ni on silicone substrate. Ti is 70 angstroms thick, Ni is 30 angstroms thick.

C++ includes: PlainMultiLayerBySLDBuilder.h
";

%feature("docstring")  PlainMultiLayerBySLDBuilder::PlainMultiLayerBySLDBuilder "PlainMultiLayerBySLDBuilder::PlainMultiLayerBySLDBuilder(int n_layers=10)
";

%feature("docstring")  PlainMultiLayerBySLDBuilder::buildSample "MultiLayer * PlainMultiLayerBySLDBuilder::buildSample() const override
";


// File: classPoissonLikeMetric.xml
%feature("docstring") PoissonLikeMetric "

Implementation of  $ \\\\chi^2 $ metric with standard deviation  $\\\\sigma = max(\\\\sqrt{I}, 1)$, where  $I$ is the simulated intensity. With default L2 norm corresponds to the formula  \\\\[\\\\chi^2 = \\\\sum \\\\frac{(I - D)^2}{max(I, 1)}\\\\] for unweighted experimental data. Falls to standard  Chi2Metric when data uncertainties are taken into account.

C++ includes: ObjectiveMetric.h
";

%feature("docstring")  PoissonLikeMetric::PoissonLikeMetric "PoissonLikeMetric::PoissonLikeMetric()
";

%feature("docstring")  PoissonLikeMetric::clone "PoissonLikeMetric * PoissonLikeMetric::clone() const override
";

%feature("docstring")  PoissonLikeMetric::computeFromArrays "double PoissonLikeMetric::computeFromArrays(std::vector< double > sim_data, std::vector< double > exp_data, std::vector< double > weight_factors) const override

Computes metric value from data arrays. Negative values in exp_data are ignored as well as non-positive weight_factors. All arrays involved in the computation must be of the same size.

Parameters:
-----------

sim_data: 
array with simulated intensities.

exp_data: 
array with intensity values obtained from an experiment.

weight_factors: 
user-defined weighting factors. Used linearly, no matter which norm is chosen. 
";


// File: classPoissonNoiseBackground.xml
%feature("docstring") PoissonNoiseBackground "

Class representing Poisson noise on top of the scattered intensity

C++ includes: PoissonNoiseBackground.h
";

%feature("docstring")  PoissonNoiseBackground::PoissonNoiseBackground "PoissonNoiseBackground::PoissonNoiseBackground()
";

%feature("docstring")  PoissonNoiseBackground::clone "PoissonNoiseBackground * PoissonNoiseBackground::clone() const override final
";

%feature("docstring")  PoissonNoiseBackground::accept "void PoissonNoiseBackground::accept(INodeVisitor *visitor) const override
";

%feature("docstring")  PoissonNoiseBackground::addBackGround "double PoissonNoiseBackground::addBackGround(double intensity) const override final
";


// File: classProcessedLayout.xml
%feature("docstring") ProcessedLayout "

Data structure that contains preprocessed data for a single layout.

If particles in the layout crossed the limits of the layer slices, these particles will be sliced themselves.

C++ includes: ProcessedLayout.h
";

%feature("docstring")  ProcessedLayout::ProcessedLayout "ProcessedLayout::ProcessedLayout(const ILayout &layout, const std::vector< Slice > &slices, double z_ref, const IFresnelMap *p_fresnel_map, bool polarized)
";

%feature("docstring")  ProcessedLayout::ProcessedLayout "ProcessedLayout::ProcessedLayout(ProcessedLayout &&other)
";

%feature("docstring")  ProcessedLayout::~ProcessedLayout "ProcessedLayout::~ProcessedLayout()
";

%feature("docstring")  ProcessedLayout::numberOfSlices "size_t ProcessedLayout::numberOfSlices() const
";

%feature("docstring")  ProcessedLayout::surfaceDensity "double ProcessedLayout::surfaceDensity() const
";

%feature("docstring")  ProcessedLayout::formFactorList "const std::vector< FormFactorCoherentSum > & ProcessedLayout::formFactorList() const
";

%feature("docstring")  ProcessedLayout::interferenceFunction "const IInterferenceFunction * ProcessedLayout::interferenceFunction() const
";

%feature("docstring")  ProcessedLayout::regionMap "std::map< size_t, std::vector< HomogeneousRegion > > ProcessedLayout::regionMap() const
";


// File: classProcessedSample.xml
%feature("docstring") ProcessedSample "

Data structure that contains all the necessary data for scattering calculations.

If the usage of average materials is requested, layers and particles are sliced into multiple slices and the average material is calculated for each slice.

C++ includes: ProcessedSample.h
";

%feature("docstring")  ProcessedSample::ProcessedSample "ProcessedSample::ProcessedSample(const MultiLayer &sample, const SimulationOptions &options)
";

%feature("docstring")  ProcessedSample::~ProcessedSample "ProcessedSample::~ProcessedSample()
";

%feature("docstring")  ProcessedSample::numberOfSlices "size_t ProcessedSample::numberOfSlices() const
";

%feature("docstring")  ProcessedSample::slices "const std::vector< Slice > & ProcessedSample::slices() const
";

%feature("docstring")  ProcessedSample::averageSlices "const std::vector< Slice > & ProcessedSample::averageSlices() const
";

%feature("docstring")  ProcessedSample::layouts "const std::vector< ProcessedLayout > & ProcessedSample::layouts() const
";

%feature("docstring")  ProcessedSample::fresnelMap "const IFresnelMap * ProcessedSample::fresnelMap() const
";

%feature("docstring")  ProcessedSample::crossCorrelationLength "double ProcessedSample::crossCorrelationLength() const
";

%feature("docstring")  ProcessedSample::externalField "kvector_t ProcessedSample::externalField() const
";

%feature("docstring")  ProcessedSample::bottomRoughness "const LayerRoughness * ProcessedSample::bottomRoughness(size_t i) const
";

%feature("docstring")  ProcessedSample::sliceTopZ "double ProcessedSample::sliceTopZ(size_t i) const
";

%feature("docstring")  ProcessedSample::sliceBottomZ "double ProcessedSample::sliceBottomZ(size_t i) const
";

%feature("docstring")  ProcessedSample::containsMagneticMaterial "bool ProcessedSample::containsMagneticMaterial() const
";

%feature("docstring")  ProcessedSample::hasRoughness "bool ProcessedSample::hasRoughness() const
";

%feature("docstring")  ProcessedSample::crossCorrSpectralFun "double ProcessedSample::crossCorrSpectralFun(const kvector_t kvec, size_t j, size_t k) const

Fourier transform of the correlation function of roughnesses between the interfaces 
";


// File: classProfileHelper.xml
%feature("docstring") ProfileHelper "

Object that can generate the material profile of a sample as a function of depth.

The generated profile contains the complex SLD for SLD materials and the parameters delta and beta for refractive index materials

C++ includes: ProfileHelper.h
";

%feature("docstring")  ProfileHelper::ProfileHelper "ProfileHelper::ProfileHelper(const ProcessedSample &sample)
";

%feature("docstring")  ProfileHelper::~ProfileHelper "ProfileHelper::~ProfileHelper()
";

%feature("docstring")  ProfileHelper::calculateProfile "std::vector< complex_t > ProfileHelper::calculateProfile(const std::vector< double > &z_values) const
";

%feature("docstring")  ProfileHelper::defaultLimits "std::pair< double, double > ProfileHelper::defaultLimits() const
";


// File: classProgressHandler.xml
%feature("docstring") ProgressHandler "

Maintains information about progress of a computation. Owner is the computation, which periodically calls the thread-safe function incrementDone(..). An application (GUI or script) may subscribe(..) to be informed about progress. It is then periodically called back by inform(..). The return value of inform(..) can be used to request termination of the computation.

C++ includes: ProgressHandler.h
";

%feature("docstring")  ProgressHandler::ProgressHandler "ProgressHandler::ProgressHandler()
";

%feature("docstring")  ProgressHandler::ProgressHandler "ProgressHandler::ProgressHandler(const ProgressHandler &other)
";

%feature("docstring")  ProgressHandler::subscribe "void ProgressHandler::subscribe(ProgressHandler::Callback_t callback)
";

%feature("docstring")  ProgressHandler::reset "void ProgressHandler::reset()
";

%feature("docstring")  ProgressHandler::setExpectedNTicks "void ProgressHandler::setExpectedNTicks(size_t n)
";

%feature("docstring")  ProgressHandler::incrementDone "void ProgressHandler::incrementDone(size_t ticks_done)

Increments number of completed computation steps (ticks). Performs callback (method m_inform) to inform the subscriber about the state of the computation and to obtain as return value a flag that indicates whether to continue the computation. 
";

%feature("docstring")  ProgressHandler::alive "bool ProgressHandler::alive()
";


// File: classPyBuilderCallback.xml
%feature("docstring") PyBuilderCallback "

Builds simulation object using a Python callable. Base class to wrap Python callable and pass it to C++. Used in swig interface file, intended to be overloaded from Python.

C++ includes: PyFittingCallbacks.h
";

%feature("docstring")  PyBuilderCallback::PyBuilderCallback "PyBuilderCallback::PyBuilderCallback()
";

%feature("docstring")  PyBuilderCallback::~PyBuilderCallback "PyBuilderCallback::~PyBuilderCallback()
";

%feature("docstring")  PyBuilderCallback::build_simulation "Simulation * PyBuilderCallback::build_simulation(Fit::Parameters)
";


// File: classPyObserverCallback.xml
%feature("docstring") PyObserverCallback "

Observer for  FitObjective based on Python callable. Base class to wrap Python callable and pass it to C++. Used in swig interface file, intended to be overloaded from Python.

C++ includes: PyFittingCallbacks.h
";

%feature("docstring")  PyObserverCallback::PyObserverCallback "PyObserverCallback::PyObserverCallback()
";

%feature("docstring")  PyObserverCallback::~PyObserverCallback "PyObserverCallback::~PyObserverCallback()
";

%feature("docstring")  PyObserverCallback::update "void PyObserverCallback::update(const FitObjective &)
";


// File: classRadialParaCrystalBuilder.xml
%feature("docstring") RadialParaCrystalBuilder "

Builds sample: cylinders with 1DDL structure factor (IsGISAXS example #4).

C++ includes: ParaCrystalBuilder.h
";

%feature("docstring")  RadialParaCrystalBuilder::buildSample "MultiLayer * RadialParaCrystalBuilder::buildSample() const
";


// File: classRectParaCrystalBuilder.xml
%feature("docstring") RectParaCrystalBuilder "

Builds sample: 2D paracrystal lattice (IsGISAXS example #8).

C++ includes: ParaCrystalBuilder.h
";

%feature("docstring")  RectParaCrystalBuilder::buildSample "MultiLayer * RectParaCrystalBuilder::buildSample() const
";


// File: classRelativeDifferenceMetric.xml
%feature("docstring") RelativeDifferenceMetric "

Implementation of relative difference metric. With default L2 norm and weighting off corresponds to the formula  \\\\[Result = \\\\sum \\\\frac{(I - D)^2}{(I + D)^2}\\\\] where  $I$ is the simulated intensity,  $D$ - experimental data. If weighting is on, falls back to the standard  $\\\\chi^2$ metric.

C++ includes: ObjectiveMetric.h
";

%feature("docstring")  RelativeDifferenceMetric::RelativeDifferenceMetric "RelativeDifferenceMetric::RelativeDifferenceMetric()
";

%feature("docstring")  RelativeDifferenceMetric::clone "RelativeDifferenceMetric * RelativeDifferenceMetric::clone() const override
";

%feature("docstring")  RelativeDifferenceMetric::computeFromArrays "double RelativeDifferenceMetric::computeFromArrays(std::vector< double > sim_data, std::vector< double > exp_data, std::vector< double > weight_factors) const override

Computes metric value from data arrays. Negative values in exp_data are ignored as well as non-positive weight_factors. All arrays involved in the computation must be of the same size.

Parameters:
-----------

sim_data: 
array with simulated intensities.

exp_data: 
array with intensity values obtained from an experiment.

weight_factors: 
user-defined weighting factors. Used linearly, no matter which norm is chosen. 
";


// File: classResonatorBuilder.xml
%feature("docstring") ResonatorBuilder "

Builds sample: multilayer with Ti/Pt layers sequence.

C++ includes: ResonatorBuilder.h
";

%feature("docstring")  ResonatorBuilder::ResonatorBuilder "ResonatorBuilder::ResonatorBuilder()
";

%feature("docstring")  ResonatorBuilder::buildSample "MultiLayer * ResonatorBuilder::buildSample() const
";


// File: classRotatedCylindersBuilder.xml
%feature("docstring") RotatedCylindersBuilder "

Builds sample: cylinder form factor in DWBA (IsGISAXS example #3, part I).

C++ includes: CylindersBuilder.h
";

%feature("docstring")  RotatedCylindersBuilder::RotatedCylindersBuilder "RotatedCylindersBuilder::RotatedCylindersBuilder()
";

%feature("docstring")  RotatedCylindersBuilder::buildSample "MultiLayer * RotatedCylindersBuilder::buildSample() const
";


// File: classRotatedPyramidsBuilder.xml
%feature("docstring") RotatedPyramidsBuilder "

Builds sample: Pyramids, rotated pyramids on top of substrate (IsGISAXS example #9)

C++ includes: RotatedPyramidsBuilder.h
";

%feature("docstring")  RotatedPyramidsBuilder::buildSample "MultiLayer * RotatedPyramidsBuilder::buildSample() const
";


// File: classRotatedPyramidsDistributionBuilder.xml
%feature("docstring") RotatedPyramidsDistributionBuilder "

Rotated Pyramids with the distribution applied to the rotation angle.

C++ includes: ParticleDistributionsBuilder.h
";

%feature("docstring")  RotatedPyramidsDistributionBuilder::RotatedPyramidsDistributionBuilder "RotatedPyramidsDistributionBuilder::RotatedPyramidsDistributionBuilder()
";

%feature("docstring")  RotatedPyramidsDistributionBuilder::buildSample "MultiLayer * RotatedPyramidsDistributionBuilder::buildSample() const
";


// File: classRotatedSquareLatticeBuilder.xml
%feature("docstring") RotatedSquareLatticeBuilder "

Builds sample: 2D lattice with different disorder (IsGISAXS example #6).

C++ includes: TwoDimLatticeBuilder.h
";

%feature("docstring")  RotatedSquareLatticeBuilder::buildSample "MultiLayer * RotatedSquareLatticeBuilder::buildSample() const
";


// File: classRoughMultiLayerComputation.xml
%feature("docstring") RoughMultiLayerComputation "

Computes the diffuse reflection from the rough interfaces of a multilayer. Used by  DWBAComputation.

C++ includes: RoughMultiLayerComputation.h
";

%feature("docstring")  RoughMultiLayerComputation::RoughMultiLayerComputation "RoughMultiLayerComputation::RoughMultiLayerComputation(const ProcessedSample *p_sample)
";

%feature("docstring")  RoughMultiLayerComputation::compute "void RoughMultiLayerComputation::compute(SimulationElement &elem) const
";


// File: classRQ4Metric.xml
%feature("docstring") RQ4Metric "

Implementation of relative difference metric. With default L2 norm and weighting off corresponds to the formula  \\\\[Result = \\\\sum (I \\\\cdot Q^4 - D \\\\cdot Q^4)^2\\\\] where  $Q$ is the scattering vector magnitude. If weighting is on, coincides with the metric provided by  Chi2Metric class.

C++ includes: ObjectiveMetric.h
";

%feature("docstring")  RQ4Metric::RQ4Metric "RQ4Metric::RQ4Metric()
";

%feature("docstring")  RQ4Metric::clone "RQ4Metric * RQ4Metric::clone() const override
";

%feature("docstring")  RQ4Metric::compute "double RQ4Metric::compute(const SimDataPair &data_pair, bool use_weights) const override

Computes metric value from  SimDataPair object. Calls computeFromArrays internally.

Parameters:
-----------

data_pair: 
 SimDataPair object. Can optionally contain data uncertainties

use_weights: 
boolean, defines if data uncertainties should be taken into account 
";


// File: classSampleBuilderFactory.xml
%feature("docstring") SampleBuilderFactory "

Factory to create standard pre-defined samples

C++ includes: SampleBuilderFactory.h
";

%feature("docstring")  SampleBuilderFactory::SampleBuilderFactory "SampleBuilderFactory::SampleBuilderFactory()
";

%feature("docstring")  SampleBuilderFactory::createSampleByName "MultiLayer * SampleBuilderFactory::createSampleByName(const std::string &name)

Retrieves a SampleBuilder from the registry, does the build, and returns the result. 
";


// File: classSampleBuilderNode.xml
%feature("docstring") SampleBuilderNode "

Wraps an  ISampleBuilder, and puts it in an INode tree. Used by  SampleProvider.

C++ includes: SampleBuilderNode.h
";

%feature("docstring")  SampleBuilderNode::SampleBuilderNode "SampleBuilderNode::SampleBuilderNode()
";

%feature("docstring")  SampleBuilderNode::SampleBuilderNode "SampleBuilderNode::SampleBuilderNode(const SampleBuilderNode &other)
";

%feature("docstring")  SampleBuilderNode::setSBN "void SampleBuilderNode::setSBN(const std::shared_ptr< ISampleBuilder > &sample_builder)

Sets sample builder and borrows its parameters. 
";

%feature("docstring")  SampleBuilderNode::reset "void SampleBuilderNode::reset()

Resets to initial state by removing builder and its borrowed parameters. 
";

%feature("docstring")  SampleBuilderNode::accept "void SampleBuilderNode::accept(INodeVisitor *visitor) const final
";

%feature("docstring")  SampleBuilderNode::createMultiLayer "std::unique_ptr< MultiLayer > SampleBuilderNode::createMultiLayer()

Creates a multilayer using sample builder. 
";

%feature("docstring")  SampleBuilderNode::builder "std::shared_ptr< ISampleBuilder > SampleBuilderNode::builder() const

Returns current sample builder. 
";


// File: classSampleLabelHandler.xml
%feature("docstring") SampleLabelHandler "

The handler which construct labels for sample variables during python script generation.

C++ includes: SampleLabelHandler.h
";

%feature("docstring")  SampleLabelHandler::SampleLabelHandler "SampleLabelHandler::SampleLabelHandler()
";

%feature("docstring")  SampleLabelHandler::crystalMap "crystals_t* SampleLabelHandler::crystalMap()
";

%feature("docstring")  SampleLabelHandler::formFactorMap "formfactors_t* SampleLabelHandler::formFactorMap()
";

%feature("docstring")  SampleLabelHandler::interferenceFunctionMap "interferences_t* SampleLabelHandler::interferenceFunctionMap()
";

%feature("docstring")  SampleLabelHandler::layerMap "layers_t* SampleLabelHandler::layerMap()
";

%feature("docstring")  SampleLabelHandler::particleLayoutMap "layouts_t* SampleLabelHandler::particleLayoutMap()
";

%feature("docstring")  SampleLabelHandler::materialMap "materials_t* SampleLabelHandler::materialMap()
";

%feature("docstring")  SampleLabelHandler::latticeMap "lattices_t* SampleLabelHandler::latticeMap()
";

%feature("docstring")  SampleLabelHandler::mesocrystalMap "mesocrystals_t* SampleLabelHandler::mesocrystalMap()
";

%feature("docstring")  SampleLabelHandler::multiLayerMap "multilayers_t* SampleLabelHandler::multiLayerMap()
";

%feature("docstring")  SampleLabelHandler::particleCompositionMap "particlecompositions_t* SampleLabelHandler::particleCompositionMap()
";

%feature("docstring")  SampleLabelHandler::particleDistributionsMap "particledistributions_t* SampleLabelHandler::particleDistributionsMap()
";

%feature("docstring")  SampleLabelHandler::particleMap "particles_t* SampleLabelHandler::particleMap()
";

%feature("docstring")  SampleLabelHandler::particleCoreShellMap "particlescoreshell_t* SampleLabelHandler::particleCoreShellMap()
";

%feature("docstring")  SampleLabelHandler::rotationsMap "rotations_t* SampleLabelHandler::rotationsMap()
";

%feature("docstring")  SampleLabelHandler::layerRoughnessMap "roughnesses_t* SampleLabelHandler::layerRoughnessMap()
";

%feature("docstring")  SampleLabelHandler::labelCrystal "std::string SampleLabelHandler::labelCrystal(const Crystal *sample)
";

%feature("docstring")  SampleLabelHandler::labelFormFactor "std::string SampleLabelHandler::labelFormFactor(const IFormFactor *sample)
";

%feature("docstring")  SampleLabelHandler::labelInterferenceFunction "std::string SampleLabelHandler::labelInterferenceFunction(const IInterferenceFunction *sample)
";

%feature("docstring")  SampleLabelHandler::labelLayer "std::string SampleLabelHandler::labelLayer(const Layer *sample)
";

%feature("docstring")  SampleLabelHandler::labelLayout "std::string SampleLabelHandler::labelLayout(const ILayout *sample)
";

%feature("docstring")  SampleLabelHandler::labelMaterial "std::string SampleLabelHandler::labelMaterial(const Material *sample)
";

%feature("docstring")  SampleLabelHandler::labelLattice "std::string SampleLabelHandler::labelLattice(const Lattice *sample)
";

%feature("docstring")  SampleLabelHandler::labelMultiLayer "std::string SampleLabelHandler::labelMultiLayer(const MultiLayer *sample)
";

%feature("docstring")  SampleLabelHandler::labelParticle "std::string SampleLabelHandler::labelParticle(const IAbstractParticle *sample)
";

%feature("docstring")  SampleLabelHandler::labelRotation "std::string SampleLabelHandler::labelRotation(const IRotation *sample)
";

%feature("docstring")  SampleLabelHandler::labelRoughness "std::string SampleLabelHandler::labelRoughness(const LayerRoughness *sample)
";

%feature("docstring")  SampleLabelHandler::insertCrystal "void SampleLabelHandler::insertCrystal(const Crystal *sample)
";

%feature("docstring")  SampleLabelHandler::insertFormFactor "void SampleLabelHandler::insertFormFactor(const IFormFactor *sample)
";

%feature("docstring")  SampleLabelHandler::insertInterferenceFunction "void SampleLabelHandler::insertInterferenceFunction(const IInterferenceFunction *sample)
";

%feature("docstring")  SampleLabelHandler::insertLayer "void SampleLabelHandler::insertLayer(const Layer *sample)
";

%feature("docstring")  SampleLabelHandler::insertLayout "void SampleLabelHandler::insertLayout(const ILayout *sample)
";

%feature("docstring")  SampleLabelHandler::insertMaterial "void SampleLabelHandler::insertMaterial(const Material *sample)
";

%feature("docstring")  SampleLabelHandler::insertLattice "void SampleLabelHandler::insertLattice(const Lattice *sample)
";

%feature("docstring")  SampleLabelHandler::insertMesoCrystal "void SampleLabelHandler::insertMesoCrystal(const MesoCrystal *sample)
";

%feature("docstring")  SampleLabelHandler::insertMultiLayer "void SampleLabelHandler::insertMultiLayer(const MultiLayer *sample)
";

%feature("docstring")  SampleLabelHandler::insertParticleComposition "void SampleLabelHandler::insertParticleComposition(const ParticleComposition *sample)
";

%feature("docstring")  SampleLabelHandler::insertParticleDistribution "void SampleLabelHandler::insertParticleDistribution(const ParticleDistribution *sample)
";

%feature("docstring")  SampleLabelHandler::insertParticle "void SampleLabelHandler::insertParticle(const Particle *sample)
";

%feature("docstring")  SampleLabelHandler::insertParticleCoreShell "void SampleLabelHandler::insertParticleCoreShell(const ParticleCoreShell *sample)
";

%feature("docstring")  SampleLabelHandler::insertRotation "void SampleLabelHandler::insertRotation(const IRotation *sample)
";

%feature("docstring")  SampleLabelHandler::insertRoughness "void SampleLabelHandler::insertRoughness(const LayerRoughness *sample)
";


// File: classSampleProvider.xml
%feature("docstring") SampleProvider "

Holds either a Sample, or a  SampleBuilderNode (which holds an  ISampleBuilder). Used in  Simulation, which holds a  SampleProvider member.

C++ includes: SampleProvider.h
";

%feature("docstring")  SampleProvider::SampleProvider "SampleProvider::SampleProvider()
";

%feature("docstring")  SampleProvider::SampleProvider "SampleProvider::SampleProvider(const SampleProvider &other)
";

%feature("docstring")  SampleProvider::~SampleProvider "SampleProvider::~SampleProvider()
";

%feature("docstring")  SampleProvider::setSample "void SampleProvider::setSample(const MultiLayer &multilayer)
";

%feature("docstring")  SampleProvider::setBuilder "void SampleProvider::setBuilder(const std::shared_ptr< ISampleBuilder > &sample_builder)
";

%feature("docstring")  SampleProvider::sample "const MultiLayer * SampleProvider::sample() const

Returns current sample. 
";

%feature("docstring")  SampleProvider::updateSample "void SampleProvider::updateSample()

Generates new sample if sample builder defined. 
";

%feature("docstring")  SampleProvider::getChildren "std::vector< const INode * > SampleProvider::getChildren() const override
";

%feature("docstring")  SampleProvider::accept "void SampleProvider::accept(INodeVisitor *visitor) const final
";

%feature("docstring")  SampleProvider::setParent "void SampleProvider::setParent(const INode *newParent) override
";


// File: classSampleToPython.xml
%feature("docstring") SampleToPython "

Generates Python code snippet from domain (C++) objects representing sample construction.

C++ includes: SampleToPython.h
";

%feature("docstring")  SampleToPython::SampleToPython "SampleToPython::SampleToPython()
";

%feature("docstring")  SampleToPython::~SampleToPython "SampleToPython::~SampleToPython()
";

%feature("docstring")  SampleToPython::generateSampleCode "std::string SampleToPython::generateSampleCode(const MultiLayer &multilayer)
";


// File: classSimDataPair.xml
%feature("docstring") SimDataPair "

Holds pair of simulation/experimental data to fit.

C++ includes: SimDataPair.h
";

%feature("docstring")  SimDataPair::SimDataPair "SimDataPair::SimDataPair(simulation_builder_t builder, const OutputData< double > &data, std::unique_ptr< OutputData< double >> uncertainties, double user_weight=1.0)
";

%feature("docstring")  SimDataPair::SimDataPair "SimDataPair::SimDataPair(simulation_builder_t builder, const OutputData< double > &data, std::unique_ptr< OutputData< double >> uncertainties, std::unique_ptr< OutputData< double >> user_weights)
";

%feature("docstring")  SimDataPair::SimDataPair "SimDataPair::SimDataPair(SimDataPair &&other)
";

%feature("docstring")  SimDataPair::~SimDataPair "SimDataPair::~SimDataPair()
";

%feature("docstring")  SimDataPair::runSimulation "void SimDataPair::runSimulation(const Fit::Parameters &params)
";

%feature("docstring")  SimDataPair::containsUncertainties "bool SimDataPair::containsUncertainties() const
";

%feature("docstring")  SimDataPair::numberOfFitElements "size_t SimDataPair::numberOfFitElements() const

Returns the number of elements in the fit area. 
";

%feature("docstring")  SimDataPair::simulationResult "SimulationResult SimDataPair::simulationResult() const

Returns the result of last computed simulation. 
";

%feature("docstring")  SimDataPair::experimentalData "SimulationResult SimDataPair::experimentalData() const

Returns the experimental data cut to the ROI area. 
";

%feature("docstring")  SimDataPair::uncertainties "SimulationResult SimDataPair::uncertainties() const

Returns the data uncertainties cut to the ROI area If no uncertainties present, returns zero-filled SimulationResult. 
";

%feature("docstring")  SimDataPair::userWeights "SimulationResult SimDataPair::userWeights() const

Returns the user uncertainties cut to the ROI area. 
";

%feature("docstring")  SimDataPair::relativeDifference "SimulationResult SimDataPair::relativeDifference() const

Returns relative difference between simulation and experimental data.

Returns the relative difference between simulated and experimental data cut to the ROI area 
";

%feature("docstring")  SimDataPair::absoluteDifference "SimulationResult SimDataPair::absoluteDifference() const

Returns the absolute difference between simulated and experimental data cut to the ROI area 
";

%feature("docstring")  SimDataPair::simulation_array "std::vector< double > SimDataPair::simulation_array() const

Returns the flattened simulated intensities cut to the ROI area. 
";

%feature("docstring")  SimDataPair::experimental_array "std::vector< double > SimDataPair::experimental_array() const

Returns the flattened experimental data cut to the ROI area. 
";

%feature("docstring")  SimDataPair::uncertainties_array "std::vector< double > SimDataPair::uncertainties_array() const

Returns the flattened experimental uncertainties cut to the ROI area. If no uncertainties are available, returns a zero-filled array sized to the ROI area. 
";

%feature("docstring")  SimDataPair::user_weights_array "std::vector< double > SimDataPair::user_weights_array() const

Returns a flat array of user weights cut to the ROI area. 
";


// File: classSimpleMagneticLayerBuilder.xml
%feature("docstring") SimpleMagneticLayerBuilder "

Builds sample: ambient and one magnetized layer on a non-magnetized substrate.

C++ includes: MagneticLayersBuilder.h
";

%feature("docstring")  SimpleMagneticLayerBuilder::buildSample "MultiLayer * SimpleMagneticLayerBuilder::buildSample() const
";


// File: classSimpleMagneticRotationBuilder.xml
%feature("docstring") SimpleMagneticRotationBuilder "

Builds sample: magnetic layer on a magnetic substrate with the fields rotated by 90°

C++ includes: MagneticLayersBuilder.h
";

%feature("docstring")  SimpleMagneticRotationBuilder::buildSample "MultiLayer * SimpleMagneticRotationBuilder::buildSample() const override
";

%feature("docstring")  SimpleMagneticRotationBuilder::createSampleByIndex "MultiLayer * SimpleMagneticRotationBuilder::createSampleByIndex(size_t index) override
";

%feature("docstring")  SimpleMagneticRotationBuilder::size "size_t SimpleMagneticRotationBuilder::size() override
";


// File: classSimulation.xml
%feature("docstring") Simulation "

Pure virtual base class of OffSpecularSimulation,  GISASSimulation and  SpecularSimulation. Holds the common infrastructure to run a simulation: multithreading, batch processing, weighting over parameter distributions, ...

C++ includes: Simulation.h
";

%feature("docstring")  Simulation::Simulation "Simulation::Simulation()
";

%feature("docstring")  Simulation::~Simulation "Simulation::~Simulation()
";

%feature("docstring")  Simulation::clone "virtual Simulation* Simulation::clone() const =0
";

%feature("docstring")  Simulation::prepareSimulation "void Simulation::prepareSimulation()

Put into a clean state for running a simulation. 
";

%feature("docstring")  Simulation::runSimulation "void Simulation::runSimulation()

Run a simulation, possibly averaged over parameter distributions.

Run simulation with possible averaging over parameter distributions. 
";

%feature("docstring")  Simulation::runMPISimulation "void Simulation::runMPISimulation()

Run a simulation in a MPI environment. 
";

%feature("docstring")  Simulation::setInstrument "void Simulation::setInstrument(const Instrument &instrument)
";

%feature("docstring")  Simulation::getInstrument "const Instrument& Simulation::getInstrument() const
";

%feature("docstring")  Simulation::getInstrument "Instrument& Simulation::getInstrument()
";

%feature("docstring")  Simulation::setBeamIntensity "void Simulation::setBeamIntensity(double intensity)
";

%feature("docstring")  Simulation::getBeamIntensity "double Simulation::getBeamIntensity() const
";

%feature("docstring")  Simulation::setBeamPolarization "void Simulation::setBeamPolarization(const kvector_t bloch_vector)

Sets the beam polarization according to the given Bloch vector. 
";

%feature("docstring")  Simulation::setDetectorResolutionFunction "void Simulation::setDetectorResolutionFunction(const IResolutionFunction2D &resolution_function)
";

%feature("docstring")  Simulation::removeDetectorResolutionFunction "void Simulation::removeDetectorResolutionFunction()
";

%feature("docstring")  Simulation::setAnalyzerProperties "void Simulation::setAnalyzerProperties(const kvector_t direction, double efficiency, double total_transmission)

Sets the polarization analyzer characteristics of the detector. 
";

%feature("docstring")  Simulation::setSample "void Simulation::setSample(const MultiLayer &sample)

The MultiLayer object will not be owned by the  Simulation object. 
";

%feature("docstring")  Simulation::sample "const MultiLayer * Simulation::sample() const
";

%feature("docstring")  Simulation::setSampleBuilder "void Simulation::setSampleBuilder(const std::shared_ptr< ISampleBuilder > &sample_builder)
";

%feature("docstring")  Simulation::setBackground "void Simulation::setBackground(const IBackground &bg)
";

%feature("docstring")  Simulation::background "const IBackground* Simulation::background() const
";

%feature("docstring")  Simulation::intensityMapSize "virtual size_t Simulation::intensityMapSize() const =0

Returns the total number of the intensity values in the simulation result. 
";

%feature("docstring")  Simulation::result "virtual SimulationResult Simulation::result() const =0

Returns the results of the simulation in a format that supports unit conversion and export to numpy arrays 
";

%feature("docstring")  Simulation::addParameterDistribution "void Simulation::addParameterDistribution(const std::string &param_name, const IDistribution1D &distribution, size_t nbr_samples, double sigma_factor=0.0, const RealLimits &limits=RealLimits())
";

%feature("docstring")  Simulation::addParameterDistribution "void Simulation::addParameterDistribution(const ParameterDistribution &par_distr)
";

%feature("docstring")  Simulation::getDistributionHandler "const DistributionHandler& Simulation::getDistributionHandler() const
";

%feature("docstring")  Simulation::setOptions "void Simulation::setOptions(const SimulationOptions &options)
";

%feature("docstring")  Simulation::getOptions "const SimulationOptions& Simulation::getOptions() const
";

%feature("docstring")  Simulation::getOptions "SimulationOptions& Simulation::getOptions()
";

%feature("docstring")  Simulation::subscribe "void Simulation::subscribe(ProgressHandler::Callback_t inform)
";

%feature("docstring")  Simulation::setTerminalProgressMonitor "void Simulation::setTerminalProgressMonitor()

Initializes a progress monitor that prints to stdout. 
";

%feature("docstring")  Simulation::getChildren "std::vector< const INode * > Simulation::getChildren() const
";

%feature("docstring")  Simulation::convertData "SimulationResult Simulation::convertData(const OutputData< double > &data, bool put_masked_areas_to_zero=true)

Convert user data to SimulationResult object for later drawing in various axes units. User data will be cropped to the ROI defined in the simulation, amplitudes in areas corresponding to the masked areas of the detector will be set to zero. 
";


// File: classSimulation2D.xml
%feature("docstring") Simulation2D "

Pure virtual base class of OffSpecularSimulation and  GISASSimulation. Holds the common implementations for simulations with a 2D detector

C++ includes: Simulation2D.h
";

%feature("docstring")  Simulation2D::Simulation2D "Simulation2D::Simulation2D()
";

%feature("docstring")  Simulation2D::~Simulation2D "Simulation2D::~Simulation2D() override
";

%feature("docstring")  Simulation2D::clone "Simulation2D* Simulation2D::clone() const override=0
";

%feature("docstring")  Simulation2D::prepareSimulation "void Simulation2D::prepareSimulation() override

Put into a clean state for running a simulation. 
";

%feature("docstring")  Simulation2D::setDetectorParameters "void Simulation2D::setDetectorParameters(size_t n_phi, double phi_min, double phi_max, size_t n_alpha, double alpha_min, double alpha_max)

Sets spherical detector parameters using angle ranges

Parameters:
-----------

n_phi: 
number of phi-axis bins

phi_min: 
low edge of first phi-bin

phi_max: 
upper edge of last phi-bin

n_alpha: 
number of alpha-axis bins

alpha_min: 
low edge of first alpha-bin

alpha_max: 
upper edge of last alpha-bin 
";

%feature("docstring")  Simulation2D::setDetector "void Simulation2D::setDetector(const IDetector2D &detector)

Sets the detector (axes can be overwritten later) 
";

%feature("docstring")  Simulation2D::removeMasks "void Simulation2D::removeMasks()

removes all masks from the detector 
";

%feature("docstring")  Simulation2D::addMask "void Simulation2D::addMask(const IShape2D &shape, bool mask_value=true)

Adds mask of given shape to the stack of detector masks. The mask value 'true' means that the channel will be excluded from the simulation. The mask which is added last has priority.

Parameters:
-----------

shape: 
The shape of mask (Rectangle, Polygon, Line, Ellipse)

mask_value: 
The value of mask 
";

%feature("docstring")  Simulation2D::maskAll "void Simulation2D::maskAll()

Put the mask for all detector channels (i.e. exclude whole detector from the analysis) 
";

%feature("docstring")  Simulation2D::setRegionOfInterest "void Simulation2D::setRegionOfInterest(double xlow, double ylow, double xup, double yup)

Sets rectangular region of interest with lower left and upper right corners defined. 
";


// File: classSimulationFactory.xml
%feature("docstring") SimulationFactory "

Registry to create standard pre-defined simulations. Used in functional tests, performance measurements, etc.

C++ includes: SimulationFactory.h
";

%feature("docstring")  SimulationFactory::SimulationFactory "SimulationFactory::SimulationFactory()
";


// File: classSimulationToPython.xml
%feature("docstring") SimulationToPython "

Write a Python script that allows to run the current simulation.

C++ includes: SimulationToPython.h
";

%feature("docstring")  SimulationToPython::generateSimulationCode "std::string SimulationToPython::generateSimulationCode(const Simulation &simulation, EMainType mainType)

Returns a Python script that sets up a simulation and runs it if invoked as main program. 
";


// File: classSizeDistributionDAModelBuilder.xml
%feature("docstring") SizeDistributionDAModelBuilder "

Creates the sample demonstrating size distribution model in decoupling approximation. Equivalent of Examples/python/simulation/ex03_InterferenceFunctions/ApproximationDA.py

C++ includes: SizeDistributionModelsBuilder.h
";

%feature("docstring")  SizeDistributionDAModelBuilder::buildSample "MultiLayer * SizeDistributionDAModelBuilder::buildSample() const
";


// File: classSizeDistributionLMAModelBuilder.xml
%feature("docstring") SizeDistributionLMAModelBuilder "

Creates the sample demonstrating size distribution model in local monodisperse approximation. Equivalent of Examples/python/simulation/ex03_InterferenceFunctions/ApproximationLMA.py

C++ includes: SizeDistributionModelsBuilder.h
";

%feature("docstring")  SizeDistributionLMAModelBuilder::buildSample "MultiLayer * SizeDistributionLMAModelBuilder::buildSample() const
";


// File: classSizeDistributionSSCAModelBuilder.xml
%feature("docstring") SizeDistributionSSCAModelBuilder "

Creates the sample demonstrating size distribution model in size space coupling approximation. Equivalent of Examples/python/simulation/ex03_InterferenceFunctions/ApproximationSSCA.py

C++ includes: SizeDistributionModelsBuilder.h
";

%feature("docstring")  SizeDistributionSSCAModelBuilder::buildSample "MultiLayer * SizeDistributionSSCAModelBuilder::buildSample() const
";


// File: classSLDSlicedCylindersBuilder.xml
%feature("docstring") SLDSlicedCylindersBuilder "

Provides exactly the same sample as  SlicedCylindersBuilder, but with sld-based materials. Assumed wavelength is 1.54 Angstrom.

C++ includes: SlicedCylindersBuilder.h
";

%feature("docstring")  SLDSlicedCylindersBuilder::buildSample "MultiLayer * SLDSlicedCylindersBuilder::buildSample() const
";


// File: classSlicedCompositionBuilder.xml
%feature("docstring") SlicedCompositionBuilder "

Builds sample: spherical composition made of top+bottom spherical cups

C++ includes: SlicedCompositionBuilder.h
";

%feature("docstring")  SlicedCompositionBuilder::buildSample "MultiLayer * SlicedCompositionBuilder::buildSample() const
";


// File: classSlicedCylindersBuilder.xml
%feature("docstring") SlicedCylindersBuilder "

Builds sample: cylinders on a silicon substrate

C++ includes: SlicedCylindersBuilder.h
";

%feature("docstring")  SlicedCylindersBuilder::buildSample "MultiLayer * SlicedCylindersBuilder::buildSample() const
";


// File: classSpecularComputation.xml
%feature("docstring") SpecularComputation "

Performs a single-threaded specular computation with given sample.

Controlled by the multi-threading machinery in Simulation::runSingleSimulation().

C++ includes: SpecularComputation.h
";

%feature("docstring")  SpecularComputation::SpecularComputation "SpecularComputation::SpecularComputation(const MultiLayer &multilayer, const SimulationOptions &options, ProgressHandler &progress, SpecularElementIter begin_it, SpecularElementIter end_it)
";

%feature("docstring")  SpecularComputation::~SpecularComputation "SpecularComputation::~SpecularComputation() override
";


// File: classSpecularComputationTerm.xml
%feature("docstring") SpecularComputationTerm "

Computes the specular scattering. Used by  SpecularComputation.

Inherited by  SpecularScalarTerm,  SpecularMatrixTerm

C++ includes: SpecularComputationTerm.h
";

%feature("docstring")  SpecularComputationTerm::SpecularComputationTerm "SpecularComputationTerm::SpecularComputationTerm(std::unique_ptr< ISpecularStrategy > strategy)
";

%feature("docstring")  SpecularComputationTerm::~SpecularComputationTerm "SpecularComputationTerm::~SpecularComputationTerm()
";

%feature("docstring")  SpecularComputationTerm::SpecularComputationTerm "SpecularComputationTerm::SpecularComputationTerm(const SpecularComputationTerm &other)=delete
";

%feature("docstring")  SpecularComputationTerm::setProgressHandler "void SpecularComputationTerm::setProgressHandler(ProgressHandler *p_progress)
";

%feature("docstring")  SpecularComputationTerm::compute "void SpecularComputationTerm::compute(SpecularSimulationElement &elem, const std::vector< Slice > &slices) const
";


// File: classSpecularMatrixTerm.xml
%feature("docstring") SpecularMatrixTerm "

Computes the specular scattering for a magnetic sample Used by  SpecularComputation.

C++ includes: SpecularComputationTerm.h
";

%feature("docstring")  SpecularMatrixTerm::SpecularMatrixTerm "SpecularMatrixTerm::SpecularMatrixTerm(std::unique_ptr< ISpecularStrategy > strategy)
";


// File: classSpecularScalarTerm.xml
%feature("docstring") SpecularScalarTerm "

Computes the specular scattering for a scalar sample Used by  SpecularComputation.

C++ includes: SpecularComputationTerm.h
";

%feature("docstring")  SpecularScalarTerm::SpecularScalarTerm "SpecularScalarTerm::SpecularScalarTerm(std::unique_ptr< ISpecularStrategy > strategy)
";


// File: classSpecularSimulation.xml
%feature("docstring") SpecularSimulation "

Main class to run a specular simulation.

C++ includes: SpecularSimulation.h
";

%feature("docstring")  SpecularSimulation::SpecularSimulation "SpecularSimulation::SpecularSimulation()
";

%feature("docstring")  SpecularSimulation::~SpecularSimulation "SpecularSimulation::~SpecularSimulation() override
";

%feature("docstring")  SpecularSimulation::clone "SpecularSimulation * SpecularSimulation::clone() const override
";

%feature("docstring")  SpecularSimulation::prepareSimulation "void SpecularSimulation::prepareSimulation() override

Put into a clean state for running a simulation. 
";

%feature("docstring")  SpecularSimulation::accept "void SpecularSimulation::accept(INodeVisitor *visitor) const override final
";

%feature("docstring")  SpecularSimulation::result "SimulationResult SpecularSimulation::result() const override

Returns the results of the simulation in a format that supports unit conversion and export to numpy arrays. If simulation was not run, returns an array of proper size filled with zeros. 
";

%feature("docstring")  SpecularSimulation::setScan "void SpecularSimulation::setScan(const ISpecularScan &scan)

Sets chosen specular scan to the simulation. 
";

%feature("docstring")  SpecularSimulation::coordinateAxis "const IAxis * SpecularSimulation::coordinateAxis() const

Returns a pointer to coordinate axis. 
";

%feature("docstring")  SpecularSimulation::footprintFactor "const IFootprintFactor * SpecularSimulation::footprintFactor() const

Returns a pointer to footprint factor holder. 
";

%feature("docstring")  SpecularSimulation::intensityMapSize "size_t SpecularSimulation::intensityMapSize() const override

Returns the total number of the intensity values in the simulation result. 
";

%feature("docstring")  SpecularSimulation::dataHandler "const ISpecularScan* SpecularSimulation::dataHandler() const

Returns internal data handler. 
";


// File: classSpecularStrategyBuilder.xml
%feature("docstring") SpecularStrategyBuilder "";


// File: classSpheresWithLimitsDistributionBuilder.xml
%feature("docstring") SpheresWithLimitsDistributionBuilder "

Spherical particles with the distribution applied to the radius and RealLimits defined.

C++ includes: ParticleDistributionsBuilder.h
";

%feature("docstring")  SpheresWithLimitsDistributionBuilder::SpheresWithLimitsDistributionBuilder "SpheresWithLimitsDistributionBuilder::SpheresWithLimitsDistributionBuilder()
";

%feature("docstring")  SpheresWithLimitsDistributionBuilder::buildSample "MultiLayer * SpheresWithLimitsDistributionBuilder::buildSample() const
";


// File: classSquareLatticeBuilder.xml
%feature("docstring") SquareLatticeBuilder "

Builds sample: 2D lattice with different disorder (IsGISAXS example #6).

C++ includes: TwoDimLatticeBuilder.h
";

%feature("docstring")  SquareLatticeBuilder::SquareLatticeBuilder "SquareLatticeBuilder::SquareLatticeBuilder()
";

%feature("docstring")  SquareLatticeBuilder::buildSample "MultiLayer * SquareLatticeBuilder::buildSample() const
";


// File: classSuperLatticeBuilder.xml
%feature("docstring") SuperLatticeBuilder "

Builds sample: 2D finite lattice of 2D finite lattices (superlattice).

C++ includes: TwoDimLatticeBuilder.h
";

%feature("docstring")  SuperLatticeBuilder::buildSample "MultiLayer * SuperLatticeBuilder::buildSample() const
";


// File: classThickAbsorptiveSampleBuilder.xml
%feature("docstring") ThickAbsorptiveSampleBuilder "";

%feature("docstring")  ThickAbsorptiveSampleBuilder::buildSample "MultiLayer * ThickAbsorptiveSampleBuilder::buildSample() const override
";


// File: classTransformBoxBuilder.xml
%feature("docstring") TransformBoxBuilder "

Rotated box in 3 layers system.

C++ includes: TransformationsBuilder.h
";

%feature("docstring")  TransformBoxBuilder::buildSample "MultiLayer * TransformBoxBuilder::buildSample() const
";


// File: classTriangularRippleBuilder.xml
%feature("docstring") TriangularRippleBuilder "

Builds sample: triangular ripple within the 1D-paracrystal model (from PRB 85, 235415, 2012).

C++ includes: RipplesBuilder.h
";

%feature("docstring")  TriangularRippleBuilder::TriangularRippleBuilder "TriangularRippleBuilder::TriangularRippleBuilder()
";

%feature("docstring")  TriangularRippleBuilder::buildSample "MultiLayer * TriangularRippleBuilder::buildSample() const
";


// File: classTwoLayerRoughnessBuilder.xml
%feature("docstring") TwoLayerRoughnessBuilder "

Builds sample: two layers with rough interface.

C++ includes: TwoLayerRoughnessBuilder.h
";

%feature("docstring")  TwoLayerRoughnessBuilder::buildSample "MultiLayer * TwoLayerRoughnessBuilder::buildSample() const
";


// File: classTwoTypesCylindersDistributionBuilder.xml
%feature("docstring") TwoTypesCylindersDistributionBuilder "

Builds mixture of cylinder particles with different size distribution (IsGISAXS example #2)

C++ includes: ParticleDistributionsBuilder.h
";

%feature("docstring")  TwoTypesCylindersDistributionBuilder::TwoTypesCylindersDistributionBuilder "TwoTypesCylindersDistributionBuilder::TwoTypesCylindersDistributionBuilder()
";

%feature("docstring")  TwoTypesCylindersDistributionBuilder::buildSample "MultiLayer * TwoTypesCylindersDistributionBuilder::buildSample() const
";


// File: namespace_0D100.xml


// File: namespace_0D102.xml


// File: namespace_0D106.xml


// File: namespace_0D118.xml


// File: namespace_0D124.xml


// File: namespace_0D128.xml


// File: namespace_0D146.xml


// File: namespace_0D165.xml


// File: namespace_0D29.xml


// File: namespace_0D31.xml


// File: namespace_0D33.xml


// File: namespace_0D37.xml


// File: namespace_0D45.xml


// File: namespace_0D53.xml


// File: namespace_0D58.xml


// File: namespace_0D67.xml


// File: namespace_0D69.xml


// File: namespace_0D73.xml


// File: namespace_0D80.xml


// File: namespace_0D86.xml


// File: namespace_0D94.xml


// File: namespaceExportToPython.xml
%feature("docstring")  ExportToPython::generateSampleCode "std::string ExportToPython::generateSampleCode(const MultiLayer &multilayer)
";

%feature("docstring")  ExportToPython::generateSimulationCode "std::string ExportToPython::generateSimulationCode(const Simulation &simulation)
";

%feature("docstring")  ExportToPython::generatePyExportTest "std::string ExportToPython::generatePyExportTest(const Simulation &simulation)
";


// File: namespaceFit.xml


// File: namespaceINodeUtils.xml
%feature("docstring")  INodeUtils::ChildNodesOfType "std::vector<const T*> INodeUtils::ChildNodesOfType(const INode &node)
";

%feature("docstring")  INodeUtils::OnlyChildOfType "const T* INodeUtils::OnlyChildOfType(const INode &node)
";

%feature("docstring")  INodeUtils::AllDescendantsOfType "std::vector<const T*> INodeUtils::AllDescendantsOfType(const INode &node)
";


// File: namespaceObjectiveMetricUtils.xml
%feature("docstring")  ObjectiveMetricUtils::l1Norm "const std::function< double(double)> ObjectiveMetricUtils::l1Norm()

Returns L1 normalization function. 
";

%feature("docstring")  ObjectiveMetricUtils::l2Norm "const std::function< double(double)> ObjectiveMetricUtils::l2Norm()

Returns L2 normalization function. 
";

%feature("docstring")  ObjectiveMetricUtils::createMetric "std::unique_ptr< ObjectiveMetric > ObjectiveMetricUtils::createMetric(const std::string &metric)

Creates the specified metric with the default norm. 
";

%feature("docstring")  ObjectiveMetricUtils::createMetric "std::unique_ptr< ObjectiveMetric > ObjectiveMetricUtils::createMetric(std::string metric, std::string norm)

Creates the metric with the specified norm. 
";

%feature("docstring")  ObjectiveMetricUtils::availableMetricOptions "std::string ObjectiveMetricUtils::availableMetricOptions()

Prints available metric options. 
";

%feature("docstring")  ObjectiveMetricUtils::normNames "std::vector< std::string > ObjectiveMetricUtils::normNames()

Returns the names of the norms used by  ObjectiveMetric. 
";

%feature("docstring")  ObjectiveMetricUtils::metricNames "std::vector< std::string > ObjectiveMetricUtils::metricNames()

Returns the names of the objective metrics used. 
";

%feature("docstring")  ObjectiveMetricUtils::defaultNormName "std::string ObjectiveMetricUtils::defaultNormName()

Returns default norm name. 
";

%feature("docstring")  ObjectiveMetricUtils::defaultMetricName "std::string ObjectiveMetricUtils::defaultMetricName()

Returns default metric name. 
";


// File: namespacerefMat.xml


// File: namespaceStandardSimulations.xml
%feature("docstring")  StandardSimulations::BasicGISAS "GISASSimulation * StandardSimulations::BasicGISAS()

Basic GISAS simulation with the detector phi[0,2], theta[0,2]. 
";

%feature("docstring")  StandardSimulations::BasicGISAS00 "GISASSimulation * StandardSimulations::BasicGISAS00()

Basic GISAS for polarization studies. 
";

%feature("docstring")  StandardSimulations::BasicPolarizedGISAS "GISASSimulation * StandardSimulations::BasicPolarizedGISAS()

Basic GISAS simulation for spin flip channel. 
";

%feature("docstring")  StandardSimulations::MiniGISAS "GISASSimulation * StandardSimulations::MiniGISAS()

GISAS simulation with small detector and phi[-2,2], theta[0,2]. 
";

%feature("docstring")  StandardSimulations::MiniGISAS_v2 "GISASSimulation * StandardSimulations::MiniGISAS_v2()

GISAS simulation with small detector and phi[-1,1], theta[0,1]. 
";

%feature("docstring")  StandardSimulations::MiniGISASBeamDivergence "GISASSimulation * StandardSimulations::MiniGISASBeamDivergence()

GISAS simulation with beam divergence applied. 
";

%feature("docstring")  StandardSimulations::MiniGISASDetectorResolution "GISASSimulation * StandardSimulations::MiniGISASDetectorResolution()

GISAS simulation with detector resolution. 
";

%feature("docstring")  StandardSimulations::MiniGISASSpecularPeak "GISASSimulation * StandardSimulations::MiniGISASSpecularPeak()

GISAS simulation with small detector and including specular peak. 
";

%feature("docstring")  StandardSimulations::GISASWithMasks "GISASSimulation * StandardSimulations::GISASWithMasks()

GISAS simulation with multiple masks on the detector plane. 
";

%feature("docstring")  StandardSimulations::MaxiGISAS "GISASSimulation * StandardSimulations::MaxiGISAS()

GISAS simulation with large detector to test performance. 
";

%feature("docstring")  StandardSimulations::MaxiGISAS00 "GISASSimulation * StandardSimulations::MaxiGISAS00()

Basic GISAS for polarization studies. 
";

%feature("docstring")  StandardSimulations::IsGISAXSSimulation1 "GISASSimulation * StandardSimulations::IsGISAXSSimulation1()

Typical IsGISAXS simulation with the detector phi[-1,1], theta[0,2]. 
";

%feature("docstring")  StandardSimulations::IsGISAXSSimulation2 "GISASSimulation * StandardSimulations::IsGISAXSSimulation2()

Typical IsGISAXS simulation with the detector phi[0,2], theta[0,2]. 
";

%feature("docstring")  StandardSimulations::RectDetectorGeneric "GISASSimulation * StandardSimulations::RectDetectorGeneric()

GISAS simulation with generic rectangular detector. 
";

%feature("docstring")  StandardSimulations::RectDetectorPerpToSample "GISASSimulation * StandardSimulations::RectDetectorPerpToSample()

GISAS simulation with the rectangular detector perpendicular to the sample. 
";

%feature("docstring")  StandardSimulations::RectDetectorPerpToDirectBeam "GISASSimulation * StandardSimulations::RectDetectorPerpToDirectBeam()

GISAS simulation with the rectangular detector perpendicular to the direct beam. 
";

%feature("docstring")  StandardSimulations::RectDetectorPerpToReflectedBeam "GISASSimulation * StandardSimulations::RectDetectorPerpToReflectedBeam()

GISAS simulation with the rectangular detector perpendicular to the reflected beam. 
";

%feature("docstring")  StandardSimulations::RectDetectorPerpToReflectedBeamDpos "GISASSimulation * StandardSimulations::RectDetectorPerpToReflectedBeamDpos()

GISAS simulation with the rectangular detector perpendicular to the reflected beam when the coordinates of direct beam are known. 
";

%feature("docstring")  StandardSimulations::MiniGISASMonteCarlo "GISASSimulation * StandardSimulations::MiniGISASMonteCarlo()

GISAS simulation with Monte-Carlo integration switched ON. 
";

%feature("docstring")  StandardSimulations::SphericalDetWithRoi "GISASSimulation * StandardSimulations::SphericalDetWithRoi()

GISAS simulation with spherical detector, region of interest and mask. 
";

%feature("docstring")  StandardSimulations::RectDetWithRoi "GISASSimulation * StandardSimulations::RectDetWithRoi()

GISAS simulation with rectangular detector, region of interest and mask. 
";

%feature("docstring")  StandardSimulations::ConstantBackgroundGISAS "GISASSimulation * StandardSimulations::ConstantBackgroundGISAS()
";

%feature("docstring")  StandardSimulations::MiniGISASFit "GISASSimulation * StandardSimulations::MiniGISASFit()

Simulation with fitting. Beam intensity set to provide reasonably large values in detector channels. 
";

%feature("docstring")  StandardSimulations::ExtraLongWavelengthGISAS "GISASSimulation * StandardSimulations::ExtraLongWavelengthGISAS()

GISAS simulation with an extra long wavelength. 
";

%feature("docstring")  StandardSimulations::MiniGISASPolarizationPP "GISASSimulation * StandardSimulations::MiniGISASPolarizationPP()
";

%feature("docstring")  StandardSimulations::MiniGISASPolarizationPM "GISASSimulation * StandardSimulations::MiniGISASPolarizationPM()
";

%feature("docstring")  StandardSimulations::MiniGISASPolarizationMP "GISASSimulation * StandardSimulations::MiniGISASPolarizationMP()
";

%feature("docstring")  StandardSimulations::MiniGISASPolarizationMM "GISASSimulation * StandardSimulations::MiniGISASPolarizationMM()
";

%feature("docstring")  StandardSimulations::BasicSpecular "SpecularSimulation * StandardSimulations::BasicSpecular()
";

%feature("docstring")  StandardSimulations::BasicSpecularQ "SpecularSimulation * StandardSimulations::BasicSpecularQ()
";

%feature("docstring")  StandardSimulations::SpecularWithGaussianBeam "SpecularSimulation * StandardSimulations::SpecularWithGaussianBeam()
";

%feature("docstring")  StandardSimulations::SpecularWithSquareBeam "SpecularSimulation * StandardSimulations::SpecularWithSquareBeam()
";

%feature("docstring")  StandardSimulations::SpecularDivergentBeam "SpecularSimulation * StandardSimulations::SpecularDivergentBeam()
";

%feature("docstring")  StandardSimulations::TOFRWithRelativeResolution "SpecularSimulation * StandardSimulations::TOFRWithRelativeResolution()
";

%feature("docstring")  StandardSimulations::TOFRWithPointwiseResolution "SpecularSimulation * StandardSimulations::TOFRWithPointwiseResolution()
";

%feature("docstring")  StandardSimulations::BasicSpecularPP "SpecularSimulation * StandardSimulations::BasicSpecularPP()
";

%feature("docstring")  StandardSimulations::BasicSpecularMM "SpecularSimulation * StandardSimulations::BasicSpecularMM()
";

%feature("docstring")  StandardSimulations::BasicSpecularPM "SpecularSimulation * StandardSimulations::BasicSpecularPM()
";

%feature("docstring")  StandardSimulations::BasicSpecularMP "SpecularSimulation * StandardSimulations::BasicSpecularMP()
";

%feature("docstring")  StandardSimulations::BasicSpecularQPP "SpecularSimulation * StandardSimulations::BasicSpecularQPP()
";

%feature("docstring")  StandardSimulations::BasicSpecularQMM "SpecularSimulation * StandardSimulations::BasicSpecularQMM()
";

%feature("docstring")  StandardSimulations::BasicSpecularQPM "SpecularSimulation * StandardSimulations::BasicSpecularQPM()
";

%feature("docstring")  StandardSimulations::BasicSpecularQMP "SpecularSimulation * StandardSimulations::BasicSpecularQMP()
";

%feature("docstring")  StandardSimulations::MiniOffSpec "OffSpecSimulation * StandardSimulations::MiniOffSpec()
";

%feature("docstring")  StandardSimulations::BasicDepthProbe "DepthProbeSimulation * StandardSimulations::BasicDepthProbe()
";


// File: namespaceUnitConverterUtils.xml
%feature("docstring")  UnitConverterUtils::createOutputData "std::unique_ptr< OutputData< double > > UnitConverterUtils::createOutputData(const IUnitConverter &converter, Axes::Units units)

Returns zero-valued output data array in specified units. 
";

%feature("docstring")  UnitConverterUtils::createConverterForGISAS "std::unique_ptr< IUnitConverter > UnitConverterUtils::createConverterForGISAS(const Instrument &instrument)

Helper factory function to use in  GISASSimulation. Depending on the type of detector, returns either RectangularConverter or SphericalConverter. 
";

%feature("docstring")  UnitConverterUtils::createConverter "std::unique_ptr< IUnitConverter > UnitConverterUtils::createConverter(const Simulation &simulation)
";


// File: ComputationStatus_8h.xml


// File: ConstantBackground_8cpp.xml


// File: ConstantBackground_8h.xml


// File: DelayedProgressCounter_8cpp.xml


// File: DelayedProgressCounter_8h.xml


// File: DepthProbeComputation_8cpp.xml


// File: DepthProbeComputation_8h.xml


// File: DepthProbeComputationTerm_8cpp.xml


// File: DepthProbeComputationTerm_8h.xml


// File: DepthProbeElement_8cpp.xml


// File: DepthProbeElement_8h.xml


// File: DWBAComputation_8cpp.xml


// File: DWBAComputation_8h.xml


// File: DWBASingleComputation_8cpp.xml


// File: DWBASingleComputation_8h.xml


// File: GISASSpecularComputation_8cpp.xml


// File: GISASSpecularComputation_8h.xml


// File: IBackground_8cpp.xml


// File: IBackground_8h.xml


// File: IComputation_8cpp.xml


// File: IComputation_8h.xml


// File: LayoutStrategyBuilder_8cpp.xml


// File: LayoutStrategyBuilder_8h.xml


// File: MultiLayerFuncs_8cpp.xml
%feature("docstring")  MaterialProfile "std::vector<complex_t> MaterialProfile(const MultiLayer &multilayer, int n_points, double z_min, double z_max)

Calculate average material profile for given multilayer 
";

%feature("docstring")  DefaultMaterialProfileLimits "std::pair<double, double> DefaultMaterialProfileLimits(const MultiLayer &multilayer)

Get default z limits for generating a material profile. 
";

%feature("docstring")  GenerateZValues "std::vector<double> GenerateZValues(int n_points, double z_min, double z_max)

Generate z values (equidistant) for use in MaterialProfile. 
";


// File: MultiLayerFuncs_8h.xml
%feature("docstring")  MaterialProfile "std::vector<complex_t> MaterialProfile(const MultiLayer &multilayer, int n_points, double z_min, double z_max)

Calculate average material profile for given multilayer 
";

%feature("docstring")  DefaultMaterialProfileLimits "std::pair<double, double> DefaultMaterialProfileLimits(const MultiLayer &multilayer)

Get default z limits for generating a material profile. 
";

%feature("docstring")  GenerateZValues "std::vector<double> GenerateZValues(int n_points, double z_min, double z_max)

Generate z values (equidistant) for use in MaterialProfile. 
";


// File: ParticleLayoutComputation_8cpp.xml


// File: ParticleLayoutComputation_8h.xml


// File: PoissonNoiseBackground_8cpp.xml


// File: PoissonNoiseBackground_8h.xml


// File: ProcessedLayout_8cpp.xml


// File: ProcessedLayout_8h.xml


// File: ProcessedSample_8cpp.xml


// File: ProcessedSample_8h.xml


// File: ProfileHelper_8cpp.xml


// File: ProfileHelper_8h.xml


// File: ProgressHandler_8cpp.xml


// File: ProgressHandler_8h.xml


// File: RoughMultiLayerComputation_8cpp.xml


// File: RoughMultiLayerComputation_8h.xml


// File: SpecularComputation_8cpp.xml


// File: SpecularComputation_8h.xml


// File: SpecularComputationTerm_8cpp.xml


// File: SpecularComputationTerm_8h.xml


// File: SpecularStrategyBuilder_8cpp.xml


// File: SpecularStrategyBuilder_8h.xml


// File: ExportToPython_8cpp.xml


// File: ExportToPython_8h.xml


// File: INodeUtils_8h.xml


// File: OrderedMap_8h.xml


// File: SampleLabelHandler_8cpp.xml


// File: SampleLabelHandler_8h.xml


// File: SampleToPython_8cpp.xml


// File: SampleToPython_8h.xml


// File: SimulationToPython_8cpp.xml


// File: SimulationToPython_8h.xml


// File: FitObjective_8cpp.xml


// File: FitObjective_8h.xml


// File: FitObserver_8h.xml


// File: FitPrintService_8cpp.xml


// File: FitPrintService_8h.xml


// File: FitStatus_8cpp.xml


// File: FitStatus_8h.xml


// File: FitTypes_8h.xml


// File: IObserver_8cpp.xml


// File: IObserver_8h.xml


// File: IterationInfo_8cpp.xml


// File: IterationInfo_8h.xml


// File: ObjectiveMetric_8cpp.xml


// File: ObjectiveMetric_8h.xml


// File: ObjectiveMetricUtils_8cpp.xml


// File: ObjectiveMetricUtils_8h.xml


// File: PyFittingCallbacks_8cpp.xml


// File: PyFittingCallbacks_8h.xml


// File: SimDataPair_8cpp.xml


// File: SimDataPair_8h.xml


// File: FixedBuilder_8cpp.xml


// File: FixedBuilder_8h.xml


// File: IRegistry_8h.xml


// File: ISampleBuilder_8cpp.xml


// File: ISampleBuilder_8h.xml


// File: SampleBuilderNode_8cpp.xml


// File: SampleBuilderNode_8h.xml


// File: SampleComponents_8cpp.xml


// File: SampleComponents_8h.xml


// File: SampleProvider_8cpp.xml


// File: SampleProvider_8h.xml


// File: DepthProbeSimulation_8cpp.xml


// File: DepthProbeSimulation_8h.xml


// File: GISASSimulation_8cpp.xml


// File: GISASSimulation_8h.xml


// File: MPISimulation_8cpp.xml


// File: MPISimulation_8h.xml


// File: OffSpecSimulation_8cpp.xml


// File: OffSpecSimulation_8h.xml


// File: Simulation_8cpp.xml


// File: Simulation_8h.xml


// File: Simulation2D_8cpp.xml


// File: Simulation2D_8h.xml


// File: SimulationFactory_8cpp.xml


// File: SimulationFactory_8h.xml


// File: SpecularSimulation_8cpp.xml


// File: SpecularSimulation_8h.xml


// File: StandardSimulations_8cpp.xml


// File: StandardSimulations_8h.xml


// File: UnitConverterUtils_8cpp.xml


// File: UnitConverterUtils_8h.xml


// File: BoxCompositionBuilder_8cpp.xml


// File: BoxCompositionBuilder_8h.xml


// File: BoxesSquareLatticeBuilder_8cpp.xml


// File: BoxesSquareLatticeBuilder_8h.xml


// File: CoreShellParticleBuilder_8cpp.xml


// File: CoreShellParticleBuilder_8h.xml


// File: CustomMorphologyBuilder_8cpp.xml


// File: CustomMorphologyBuilder_8h.xml


// File: CylindersAndPrismsBuilder_8cpp.xml


// File: CylindersAndPrismsBuilder_8h.xml


// File: CylindersBuilder_8cpp.xml


// File: CylindersBuilder_8h.xml


// File: FeNiBilayerBuilder_8cpp.xml


// File: FeNiBilayerBuilder_8h.xml


// File: HomogeneousMultilayerBuilder_8cpp.xml


// File: HomogeneousMultilayerBuilder_8h.xml


// File: LatticeBuilder_8cpp.xml


// File: LatticeBuilder_8h.xml


// File: LayersWithAbsorptionBuilder_8cpp.xml


// File: LayersWithAbsorptionBuilder_8h.xml


// File: LayersWithAbsorptionBySLDBuilder_8cpp.xml
%feature("docstring")  middle_layer_thickness "const double middle_layer_thickness(60.0 *Units::nanometer)
";


// File: LayersWithAbsorptionBySLDBuilder_8h.xml


// File: MagneticLayersBuilder_8cpp.xml


// File: MagneticLayersBuilder_8h.xml


// File: MagneticParticlesBuilder_8cpp.xml


// File: MagneticParticlesBuilder_8h.xml


// File: MesoCrystalBuilder_8cpp.xml


// File: MesoCrystalBuilder_8h.xml


// File: MultiLayerWithNCRoughnessBuilder_8cpp.xml


// File: MultiLayerWithNCRoughnessBuilder_8h.xml


// File: MultiLayerWithRoughnessBuilder_8cpp.xml


// File: MultiLayerWithRoughnessBuilder_8h.xml


// File: MultipleLayoutBuilder_8cpp.xml


// File: MultipleLayoutBuilder_8h.xml


// File: ParaCrystalBuilder_8cpp.xml


// File: ParaCrystalBuilder_8h.xml


// File: ParticleCompositionBuilder_8cpp.xml


// File: ParticleCompositionBuilder_8h.xml


// File: ParticleDistributionsBuilder_8cpp.xml


// File: ParticleDistributionsBuilder_8h.xml


// File: ParticleInVacuumBuilder_8cpp.xml


// File: ParticleInVacuumBuilder_8h.xml


// File: PercusYevickBuilder_8cpp.xml


// File: PercusYevickBuilder_8h.xml


// File: PlainMultiLayerBySLDBuilder_8cpp.xml


// File: PlainMultiLayerBySLDBuilder_8h.xml


// File: ReferenceMaterials_8h.xml


// File: ResonatorBuilder_8cpp.xml


// File: ResonatorBuilder_8h.xml


// File: RipplesBuilder_8cpp.xml


// File: RipplesBuilder_8h.xml


// File: RotatedPyramidsBuilder_8cpp.xml


// File: RotatedPyramidsBuilder_8h.xml


// File: SampleBuilderFactory_8cpp.xml


// File: SampleBuilderFactory_8h.xml


// File: SizeDistributionModelsBuilder_8cpp.xml


// File: SizeDistributionModelsBuilder_8h.xml


// File: SlicedCompositionBuilder_8cpp.xml


// File: SlicedCompositionBuilder_8h.xml


// File: SlicedCylindersBuilder_8cpp.xml


// File: SlicedCylindersBuilder_8h.xml


// File: ThickAbsorptiveSampleBuilder_8cpp.xml


// File: ThickAbsorptiveSampleBuilder_8h.xml


// File: TransformationsBuilder_8cpp.xml


// File: TransformationsBuilder_8h.xml


// File: TwoDimLatticeBuilder_8cpp.xml


// File: TwoDimLatticeBuilder_8h.xml


// File: TwoLayerRoughnessBuilder_8cpp.xml


// File: TwoLayerRoughnessBuilder_8h.xml


// File: dir_7de90f35ae2a2c7b4fa95823d333cc96.xml


// File: dir_c6310732a22f63c0c2fc5595561e68f1.xml


// File: dir_cca9b87b2505f372a6ce58947a507789.xml


// File: dir_4470199ae7eb44153ffe31d163ed0f28.xml


// File: dir_dfcc64e98e4f62108d0fa0099ad7f9c0.xml


// File: dir_d7a24665a95cfc15308ebd7b07b5ebd6.xml


// File: dir_5d2259b43612a5a0ff7512df653d7370.xml

