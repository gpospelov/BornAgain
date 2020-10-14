
// File: index.xml

// File: classAngularSpecScan.xml
%feature("docstring") AngularSpecScan "

Scan type with inclination angles as coordinate values and a unique wavelength. Features footprint correction.

C++ includes: AngularSpecScan.h
";

%feature("docstring")  AngularSpecScan::AngularSpecScan "AngularSpecScan::AngularSpecScan(double wl, std::vector< double > inc_angle)
";

%feature("docstring")  AngularSpecScan::AngularSpecScan "AngularSpecScan::AngularSpecScan(double wl, const IAxis &inc_angle)
";

%feature("docstring")  AngularSpecScan::AngularSpecScan "AngularSpecScan::AngularSpecScan(double wl, int nbins, double alpha_i_min, double alpha_i_max)

Sets angle-defined specular scan. The first parameter is always a wavelength in nm. Second parameter is either a numpy array of incident angles in radians or an IAxis object with angle values. Alternatively an axis can be defined in-place, then the second passed parameter is the number of bins, third - minimum on-axis angle value, fourth - maximum on-axis angle value. 
";

%feature("docstring")  AngularSpecScan::~AngularSpecScan "AngularSpecScan::~AngularSpecScan() override
";

%feature("docstring")  AngularSpecScan::clone "AngularSpecScan * AngularSpecScan::clone() const override
";

%feature("docstring")  AngularSpecScan::generateSimulationElements "std::vector< SpecularSimulationElement > AngularSpecScan::generateSimulationElements() const override

Generates simulation elements for specular simulations. 
";

%feature("docstring")  AngularSpecScan::coordinateAxis "virtual const IAxis* AngularSpecScan::coordinateAxis() const override

Returns coordinate axis assigned to the data holder. 
";

%feature("docstring")  AngularSpecScan::footprintFactor "virtual const IFootprintFactor* AngularSpecScan::footprintFactor() const override

Returns  IFootprintFactor object pointer. 
";

%feature("docstring")  AngularSpecScan::footprint "std::vector< double > AngularSpecScan::footprint(size_t i, size_t n_elements) const override

Returns footprint correction factor for a range of simulation elements of size  n_elements and starting from element with index  i. 
";

%feature("docstring")  AngularSpecScan::numberOfSimulationElements "size_t AngularSpecScan::numberOfSimulationElements() const override

Returns the number of simulation elements. 
";

%feature("docstring")  AngularSpecScan::createIntensities "std::vector< double > AngularSpecScan::createIntensities(const std::vector< SpecularSimulationElement > &sim_elements) const override

Returns intensity vector corresponding to convolution of given simulation elements. 
";

%feature("docstring")  AngularSpecScan::print "std::string AngularSpecScan::print() const override

Print scan definition in python format. 
";

%feature("docstring")  AngularSpecScan::wavelength "double AngularSpecScan::wavelength() const
";

%feature("docstring")  AngularSpecScan::wavelengthResolution "const ScanResolution* AngularSpecScan::wavelengthResolution() const
";

%feature("docstring")  AngularSpecScan::angleResolution "const ScanResolution* AngularSpecScan::angleResolution() const
";

%feature("docstring")  AngularSpecScan::setFootprintFactor "void AngularSpecScan::setFootprintFactor(const IFootprintFactor *f_factor)

Sets footprint correction factor. 
";

%feature("docstring")  AngularSpecScan::setWavelengthResolution "void AngularSpecScan::setWavelengthResolution(const ScanResolution &resolution)

Sets wavelength resolution values via  ScanResolution object. 
";

%feature("docstring")  AngularSpecScan::setRelativeWavelengthResolution "void AngularSpecScan::setRelativeWavelengthResolution(const RangedDistribution &distr, double rel_dev)
";

%feature("docstring")  AngularSpecScan::setRelativeWavelengthResolution "void AngularSpecScan::setRelativeWavelengthResolution(const RangedDistribution &distr, const std::vector< double > &rel_dev)

Sets wavelength resolution values via RangedDistribution and values of relative deviations (that is,  rel_dev equals standard deviation divided by the mean value).  rel_dev can be either single-valued or a numpy array. In the latter case the length of the array should coinside with the length of the inclination angle axis. 
";

%feature("docstring")  AngularSpecScan::setAbsoluteWavelengthResolution "void AngularSpecScan::setAbsoluteWavelengthResolution(const RangedDistribution &distr, double std_dev)
";

%feature("docstring")  AngularSpecScan::setAbsoluteWavelengthResolution "void AngularSpecScan::setAbsoluteWavelengthResolution(const RangedDistribution &distr, const std::vector< double > &std_dev)

Sets wavelength resolution values via RangedDistribution and values of standard deviations.  std_dev can be either single-valued or a numpy array. In the latter case the length of the array should coinside with the length of the inclination angle axis. 
";

%feature("docstring")  AngularSpecScan::setAngleResolution "void AngularSpecScan::setAngleResolution(const ScanResolution &resolution)

Sets angle resolution values via  ScanResolution object. 
";

%feature("docstring")  AngularSpecScan::setRelativeAngularResolution "void AngularSpecScan::setRelativeAngularResolution(const RangedDistribution &distr, double rel_dev)
";

%feature("docstring")  AngularSpecScan::setRelativeAngularResolution "void AngularSpecScan::setRelativeAngularResolution(const RangedDistribution &distr, const std::vector< double > &rel_dev)

Sets angular resolution values via RangedDistribution and values of relative deviations (that is,  rel_dev equals standard deviation divided by the mean value).  rel_dev can be either single-valued or a numpy array. In the latter case the length of the array should coinside with the length of the inclination angle axis. 
";

%feature("docstring")  AngularSpecScan::setAbsoluteAngularResolution "void AngularSpecScan::setAbsoluteAngularResolution(const RangedDistribution &distr, double std_dev)
";

%feature("docstring")  AngularSpecScan::setAbsoluteAngularResolution "void AngularSpecScan::setAbsoluteAngularResolution(const RangedDistribution &distr, const std::vector< double > &std_dev)

Sets angular resolution values via RangedDistribution and values of standard deviations.  std_dev can be either single-valued or a numpy array. In the latter case the length of the array should coinside with the length of the inclination angle axis. 
";


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


// File: classAxes.xml
%feature("docstring") Axes "

Wrapper for detector axes units, required for a better representation of detector axes units in python

C++ includes: IUnitConverter.h
";


// File: structUnitConverterSimple_1_1AxisData.xml


// File: structAxisInfo.xml
%feature("docstring") AxisInfo "

Information about an axis in specific units. Can be used for plotting.

C++ includes: SimulationResult.h
";


// File: structArrayUtils_1_1CreateDataImpl_1_1baseClass.xml


// File: structArrayUtils_1_1CreateDataImpl_1_1baseClass_3_01std_1_1vector_3_01T_00_01A_01_4_01_4.xml


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


// File: classBeam.xml
%feature("docstring") Beam "

Beam defined by wavelength, direction and intensity.

C++ includes: Beam.h
";

%feature("docstring")  Beam::Beam "Beam::Beam(double wavelength, double alpha, double phi, double intensity)
";

%feature("docstring")  Beam::Beam "Beam::Beam(const Beam &other)
";

%feature("docstring")  Beam::~Beam "Beam::~Beam()
";

%feature("docstring")  Beam::getCentralK "kvector_t Beam::getCentralK() const

Returns the wavevector. 
";

%feature("docstring")  Beam::setCentralK "void Beam::setCentralK(double wavelength, double alpha_i, double phi_i)

Sets the wavevector in terms of wavelength and incoming angles. 
";

%feature("docstring")  Beam::getIntensity "double Beam::getIntensity() const

Returns the beam intensity in neutrons/sec. 
";

%feature("docstring")  Beam::setIntensity "void Beam::setIntensity(double intensity)

Sets the beam intensity in neutrons/sec. 
";

%feature("docstring")  Beam::footprintFactor "const IFootprintFactor * Beam::footprintFactor() const

Returns footprint factor. 
";

%feature("docstring")  Beam::setFootprintFactor "void Beam::setFootprintFactor(const IFootprintFactor &shape_factor)

Sets footprint factor to the beam. 
";

%feature("docstring")  Beam::setWidthRatio "void Beam::setWidthRatio(double width_ratio)

Sets beam to sample width ratio in footprint factor. 
";

%feature("docstring")  Beam::setPolarization "void Beam::setPolarization(const kvector_t bloch_vector)

Sets the polarization density matrix according to the given Bloch vector. 
";

%feature("docstring")  Beam::getBlochVector "kvector_t Beam::getBlochVector() const
";

%feature("docstring")  Beam::getPolarization "Eigen::Matrix2cd Beam::getPolarization() const

Returns the polarization density matrix (in spin basis along z-axis) 
";

%feature("docstring")  Beam::getWavelength "double Beam::getWavelength() const
";

%feature("docstring")  Beam::getAlpha "double Beam::getAlpha() const
";

%feature("docstring")  Beam::getPhi "double Beam::getPhi() const
";

%feature("docstring")  Beam::accept "void Beam::accept(INodeVisitor *visitor) const override
";

%feature("docstring")  Beam::getChildren "std::vector< const INode * > Beam::getChildren() const override
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


// File: classChiSquaredModule.xml
%feature("docstring") ChiSquaredModule "

Calculation of chi2 between two data sets.

C++ includes: ChiSquaredModule.h
";

%feature("docstring")  ChiSquaredModule::ChiSquaredModule "ChiSquaredModule::ChiSquaredModule()
";

%feature("docstring")  ChiSquaredModule::ChiSquaredModule "ChiSquaredModule::ChiSquaredModule(const ChiSquaredModule &other)
";

%feature("docstring")  ChiSquaredModule::~ChiSquaredModule "virtual ChiSquaredModule::~ChiSquaredModule()
";

%feature("docstring")  ChiSquaredModule::clone "virtual ChiSquaredModule* ChiSquaredModule::clone() const

clone method 
";

%feature("docstring")  ChiSquaredModule::residual "double ChiSquaredModule::residual(double a, double b, double weight)
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


// File: classConvolutionDetectorResolution.xml
%feature("docstring") ConvolutionDetectorResolution "

Limitation: this class assumes that the data points are evenly distributed on each axis.

Convolutes the intensity in 1 or 2 dimensions with a resolution function.

C++ includes: ConvolutionDetectorResolution.h
";

%feature("docstring")  ConvolutionDetectorResolution::ConvolutionDetectorResolution "ConvolutionDetectorResolution::ConvolutionDetectorResolution(cumulative_DF_1d res_function_1d)

Constructor taking a 1 dimensional resolution function as argument. 
";

%feature("docstring")  ConvolutionDetectorResolution::ConvolutionDetectorResolution "ConvolutionDetectorResolution::ConvolutionDetectorResolution(const IResolutionFunction2D &p_res_function_2d)

Constructor taking a 2 dimensional resolution function as argument. 
";

%feature("docstring")  ConvolutionDetectorResolution::~ConvolutionDetectorResolution "ConvolutionDetectorResolution::~ConvolutionDetectorResolution()
";

%feature("docstring")  ConvolutionDetectorResolution::applyDetectorResolution "void ConvolutionDetectorResolution::applyDetectorResolution(OutputData< double > *p_intensity_map) const

Convolve given intensities with the encapsulated resolution. 
";

%feature("docstring")  ConvolutionDetectorResolution::clone "ConvolutionDetectorResolution * ConvolutionDetectorResolution::clone() const
";

%feature("docstring")  ConvolutionDetectorResolution::accept "void ConvolutionDetectorResolution::accept(INodeVisitor *visitor) const final
";

%feature("docstring")  ConvolutionDetectorResolution::getResolutionFunction2D "const IResolutionFunction2D * ConvolutionDetectorResolution::getResolutionFunction2D() const
";

%feature("docstring")  ConvolutionDetectorResolution::getChildren "std::vector< const INode * > ConvolutionDetectorResolution::getChildren() const
";


// File: classConvolve.xml
%feature("docstring") Convolve "

Convolution of two real vectors (in 1D or 2D) using Fast Fourier Transform.

Usage: std::vector<double> signal, kernel, result;  Convolve cv; cv.fftconvolve(signal, kernel, result)

Given code rely on code from Jeremy Fix page, http://jeremy.fix.free.fr/spip.php?article15, see also \"Efficient convolution using the Fast Fourier Transform, Application in C++\" by Jeremy Fix, May 30, 2011

C++ includes: Convolve.h
";

%feature("docstring")  Convolve::Convolve "Convolve::Convolve()
";

%feature("docstring")  Convolve::fftconvolve "void Convolve::fftconvolve(const double1d_t &source, const double1d_t &kernel, double1d_t &result)

convolution in 1D 
";

%feature("docstring")  Convolve::fftconvolve "void Convolve::fftconvolve(const double2d_t &source, const double2d_t &kernel, double2d_t &result)

convolution in 2D 
";

%feature("docstring")  Convolve::init "void Convolve::init(int h_src, int w_src, int h_kernel, int w_kernel)

prepare arrays for 2D convolution of given vectors 
";

%feature("docstring")  Convolve::setMode "void Convolve::setMode(EConvolutionMode mode)

Sets convolution mode. 
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


// File: classArrayUtils_1_1CreateDataImpl.xml
%feature("docstring") ArrayUtils::CreateDataImpl "";


// File: classCumulativeValue.xml
%feature("docstring") CumulativeValue "

The cumulative value with average and rms on-the-flight calculations.

C++ includes: CumulativeValue.h
";

%feature("docstring")  CumulativeValue::CumulativeValue "CumulativeValue::CumulativeValue()
";

%feature("docstring")  CumulativeValue::clear "void CumulativeValue::clear()
";

%feature("docstring")  CumulativeValue::setContent "void CumulativeValue::setContent(double value)
";

%feature("docstring")  CumulativeValue::add "void CumulativeValue::add(double value, double weight=1.0)
";

%feature("docstring")  CumulativeValue::getNumberOfEntries "int CumulativeValue::getNumberOfEntries() const
";

%feature("docstring")  CumulativeValue::getContent "double CumulativeValue::getContent() const
";

%feature("docstring")  CumulativeValue::getAverage "double CumulativeValue::getAverage() const
";

%feature("docstring")  CumulativeValue::getRMS "double CumulativeValue::getRMS() const
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


// File: classDepthProbeConverter.xml
%feature("docstring") DepthProbeConverter "

DepthProbeConverter class handles the unit translations for depth probe simulations Its default units are radians for x-axis and nm for y-axis

C++ includes: SimpleUnitConverters.h
";

%feature("docstring")  DepthProbeConverter::DepthProbeConverter "DepthProbeConverter::DepthProbeConverter(const Beam &beam, const IAxis &alpha_axis, const IAxis &z_axis)
";

%feature("docstring")  DepthProbeConverter::~DepthProbeConverter "DepthProbeConverter::~DepthProbeConverter() final
";

%feature("docstring")  DepthProbeConverter::clone "DepthProbeConverter * DepthProbeConverter::clone() const final
";

%feature("docstring")  DepthProbeConverter::availableUnits "std::vector< Axes::Units > DepthProbeConverter::availableUnits() const final

Returns the list of all available units. 
";

%feature("docstring")  DepthProbeConverter::defaultUnits "Axes::Units DepthProbeConverter::defaultUnits() const final
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


// File: classDetectionProperties.xml
%feature("docstring") DetectionProperties "

Detector properties (efficiency, transmission).

C++ includes: DetectionProperties.h
";

%feature("docstring")  DetectionProperties::DetectionProperties "DetectionProperties::DetectionProperties(kvector_t direction, double efficiency, double total_transmission)
";

%feature("docstring")  DetectionProperties::DetectionProperties "DetectionProperties::DetectionProperties()
";

%feature("docstring")  DetectionProperties::DetectionProperties "DetectionProperties::DetectionProperties(const DetectionProperties &other)
";

%feature("docstring")  DetectionProperties::~DetectionProperties "virtual DetectionProperties::~DetectionProperties()=default
";

%feature("docstring")  DetectionProperties::setAnalyzerProperties "void DetectionProperties::setAnalyzerProperties(const kvector_t direction, double efficiency, double total_transmission)

Sets the polarization analyzer characteristics of the detector. 
";

%feature("docstring")  DetectionProperties::analyzerOperator "Eigen::Matrix2cd DetectionProperties::analyzerOperator() const

Return the polarization density matrix (in spin basis along z-axis) 
";

%feature("docstring")  DetectionProperties::analyzerDirection "kvector_t DetectionProperties::analyzerDirection() const

Retrieve the analyzer characteristics. 
";

%feature("docstring")  DetectionProperties::analyzerEfficiency "double DetectionProperties::analyzerEfficiency() const

will always return positive value 
";

%feature("docstring")  DetectionProperties::analyzerTotalTransmission "double DetectionProperties::analyzerTotalTransmission() const
";

%feature("docstring")  DetectionProperties::accept "void DetectionProperties::accept(INodeVisitor *visitor) const final
";


// File: classDetectorContext.xml
%feature("docstring") DetectorContext "

Holds precalculated information for faster SimulationElement generation.

C++ includes: DetectorContext.h
";

%feature("docstring")  DetectorContext::DetectorContext "DetectorContext::DetectorContext(const IDetector2D *detector)
";

%feature("docstring")  DetectorContext::DetectorContext "DetectorContext::DetectorContext(const DetectorContext &other)=delete
";

%feature("docstring")  DetectorContext::numberOfSimulationElements "size_t DetectorContext::numberOfSimulationElements() const
";

%feature("docstring")  DetectorContext::createPixel "std::unique_ptr< IPixel > DetectorContext::createPixel(size_t element_index) const

Creates pixel for given element index. Element index is sequetial index in a vector of SimulationElements. Corresponds to sequence of detector bins inside ROI and outside of masked areas. 
";

%feature("docstring")  DetectorContext::detectorIndex "size_t DetectorContext::detectorIndex(size_t element_index) const
";


// File: classDetectorMask.xml
%feature("docstring") DetectorMask "

Collection of detector masks.

C++ includes: DetectorMask.h
";

%feature("docstring")  DetectorMask::DetectorMask "DetectorMask::DetectorMask()
";

%feature("docstring")  DetectorMask::DetectorMask "DetectorMask::DetectorMask(const DetectorMask &other)
";

%feature("docstring")  DetectorMask::addMask "void DetectorMask::addMask(const IShape2D &shape, bool mask_value)

Add mask to the stack of detector masks. The value \"true\" means that the area will be excluded from the analysis.

Parameters:
-----------

shape: 
The shape of mask.

mask_value: 
The value of mask 
";

%feature("docstring")  DetectorMask::initMaskData "void DetectorMask::initMaskData(const IDetector2D &detector)

Init the map of masks for the given detector plane. 
";

%feature("docstring")  DetectorMask::initMaskData "void DetectorMask::initMaskData(const OutputData< double > &data)
";

%feature("docstring")  DetectorMask::isMasked "bool DetectorMask::isMasked(size_t index) const
";

%feature("docstring")  DetectorMask::getMaskData "const OutputData<bool>* DetectorMask::getMaskData() const
";

%feature("docstring")  DetectorMask::createHistogram "Histogram2D * DetectorMask::createHistogram() const
";

%feature("docstring")  DetectorMask::removeMasks "void DetectorMask::removeMasks()

remove all masks and return object to initial state 
";

%feature("docstring")  DetectorMask::hasMasks "bool DetectorMask::hasMasks() const

returns true if has masks 
";

%feature("docstring")  DetectorMask::numberOfMaskedChannels "int DetectorMask::numberOfMaskedChannels() const
";

%feature("docstring")  DetectorMask::numberOfMasks "size_t DetectorMask::numberOfMasks() const
";

%feature("docstring")  DetectorMask::getMaskShape "const IShape2D * DetectorMask::getMaskShape(size_t mask_index, bool &mask_value) const
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

Returns simulation result in the form of  SimulationResult. 
";

%feature("docstring")  FitObjective::experimentalData "SimulationResult FitObjective::experimentalData(size_t i_item=0) const

Returns experimental data in the form of  SimulationResult. 
";

%feature("docstring")  FitObjective::uncertaintyData "SimulationResult FitObjective::uncertaintyData(size_t i_item=0) const

Returns experimental data uncertainties in the form of  SimulationResult. 
";

%feature("docstring")  FitObjective::relativeDifference "SimulationResult FitObjective::relativeDifference(size_t i_item=0) const

Returns relative difference between simulation and experimental data in the form of  SimulationResult. 
";

%feature("docstring")  FitObjective::absoluteDifference "SimulationResult FitObjective::absoluteDifference(size_t i_item=0) const

Returns absolute value of difference between simulation and experimental data in the form of  SimulationResult. 
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


// File: classFootprintGauss.xml
%feature("docstring") FootprintGauss "

Calculates footprint coefficient for a gaussian beam  Beam width is interpreted as the full width on the level of  \\\\[ \\\\exp{-1/2} \\\\] from the peak intensity.

C++ includes: FootprintGauss.h
";

%feature("docstring")  FootprintGauss::FootprintGauss "FootprintGauss::FootprintGauss(const std::vector< double > P)
";

%feature("docstring")  FootprintGauss::FootprintGauss "FootprintGauss::FootprintGauss(double width_ratio)
";

%feature("docstring")  FootprintGauss::accept "void FootprintGauss::accept(INodeVisitor *visitor) const override
";

%feature("docstring")  FootprintGauss::clone "FootprintGauss * FootprintGauss::clone() const override
";

%feature("docstring")  FootprintGauss::calculate "double FootprintGauss::calculate(double alpha) const override

Calculate footprint correction coefficient from the beam incident angle  alpha. 
";

%feature("docstring")  FootprintGauss::print "std::string FootprintGauss::print() const override

Print python-formatted footprint definition. 
";


// File: classFootprintSquare.xml
%feature("docstring") FootprintSquare "

Calculates footprint coefficient for a square beam

C++ includes: FootprintSquare.h
";

%feature("docstring")  FootprintSquare::FootprintSquare "FootprintSquare::FootprintSquare(const std::vector< double > P)
";

%feature("docstring")  FootprintSquare::FootprintSquare "FootprintSquare::FootprintSquare(double width_ratio)
";

%feature("docstring")  FootprintSquare::accept "void FootprintSquare::accept(INodeVisitor *visitor) const override
";

%feature("docstring")  FootprintSquare::clone "FootprintSquare * FootprintSquare::clone() const override
";

%feature("docstring")  FootprintSquare::calculate "double FootprintSquare::calculate(double alpha) const override

Calculate footprint correction coefficient from the beam incident angle  alpha. 
";

%feature("docstring")  FootprintSquare::print "std::string FootprintSquare::print() const override

Print python-formatted footprint definition. 
";


// File: classFormFactorComponents.xml
%feature("docstring") FormFactorComponents "

Predefined form factors for functional tests.

C++ includes: SampleComponents.h
";

%feature("docstring")  FormFactorComponents::FormFactorComponents "FormFactorComponents::FormFactorComponents()
";


// File: classFourierTransform.xml
%feature("docstring") FourierTransform "

Fourier transform of vectors (in 1D or 2D) using Fast Fourier Transform (fftw package).

Usage: std::vector<double> signal, result;  FourierTransform ft; ft.fft(signal, result)

Given code rely on code from Jeremy Fix page, http://jeremy.fix.free.fr/spip.php?article15, see also \"Efficient convolution using the Fast Fourier Transform, Application in C++\" by Jeremy Fix, May 30, 2011

C++ includes: FourierTransform.h
";

%feature("docstring")  FourierTransform::FourierTransform "FourierTransform::FourierTransform()
";

%feature("docstring")  FourierTransform::fft "void FourierTransform::fft(const double1d_t &source, double1d_t &result)

FT in 1D. 
";

%feature("docstring")  FourierTransform::fftshift "void FourierTransform::fftshift(double1d_t &result)

Shift low frequency to the center of 1D FT array. 
";

%feature("docstring")  FourierTransform::fft "void FourierTransform::fft(const double2d_t &source, double2d_t &result)

FT in 2D. 
";

%feature("docstring")  FourierTransform::fftshift "void FourierTransform::fftshift(double2d_t &result)

Shift low frequency to the center of 2D FT array. 
";

%feature("docstring")  FourierTransform::init "void FourierTransform::init(int h_src, int w_src)

prepare arrays for 2D Fourier Transformation (FT) of the given vector 
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

Sets beam parameters from here (forwarded to  Instrument) 
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


// File: classHistogram1D.xml
%feature("docstring") Histogram1D "

One dimensional histogram.

C++ includes: Histogram1D.h
";

%feature("docstring")  Histogram1D::Histogram1D "Histogram1D::Histogram1D(int nbinsx, double xlow, double xup)

Constructor for fix bin size histograms.

Parameters:
-----------

nbinsx: 
number of bins

xlow: 
low edge of the first bin

xup: 
upper edge of the last bin 
";

%feature("docstring")  Histogram1D::Histogram1D "Histogram1D::Histogram1D(int nbinsx, const std::vector< double > &xbins)

Constructor for variable bin size histograms.

Parameters:
-----------

nbinsx: 
number of bins

xbins: 
Array of size nbins+1 containing low-edges for each bin and upper edge of last bin. 
";

%feature("docstring")  Histogram1D::Histogram1D "Histogram1D::Histogram1D(const IAxis &axis)

Constructor for 1D histogram with custom axis. 
";

%feature("docstring")  Histogram1D::Histogram1D "Histogram1D::Histogram1D(const OutputData< double > &data)

Constructor for 1D histograms from basic  OutputData object. 
";

%feature("docstring")  Histogram1D::clone "Histogram1D * Histogram1D::clone() const

Returns clone of other histogram. 
";

%feature("docstring")  Histogram1D::getRank "size_t Histogram1D::getRank() const

Returns the number of histogram dimensions. 
";

%feature("docstring")  Histogram1D::fill "int Histogram1D::fill(double x, double weight=1.0)

Increment bin with abscissa x with a weight. 
";

%feature("docstring")  Histogram1D::getBinCenters "std::vector< double > Histogram1D::getBinCenters() const

returns vector of histogram bin centers 
";

%feature("docstring")  Histogram1D::getBinValues "std::vector< double > Histogram1D::getBinValues() const

returns vector of bin content (the value accumulated by bins) 
";

%feature("docstring")  Histogram1D::getBinErrors "std::vector< double > Histogram1D::getBinErrors() const

returns vector of bin errors 
";

%feature("docstring")  Histogram1D::getBinCentersNumpy "PyObject * Histogram1D::getBinCentersNumpy() const
";

%feature("docstring")  Histogram1D::getBinValuesNumpy "PyObject * Histogram1D::getBinValuesNumpy() const
";

%feature("docstring")  Histogram1D::getBinErrorsNumpy "PyObject * Histogram1D::getBinErrorsNumpy() const
";

%feature("docstring")  Histogram1D::crop "Histogram1D * Histogram1D::crop(double xmin, double xmax)

Creates new histogram by applying crop on axis. 
";


// File: classHistogram2D.xml
%feature("docstring") Histogram2D "

Two dimensional histogram.

C++ includes: Histogram2D.h
";

%feature("docstring")  Histogram2D::Histogram2D "Histogram2D::Histogram2D(int nbinsx, double xlow, double xup, int nbinsy, double ylow, double yup)

Constructor for fix bin size histograms.

Parameters:
-----------

nbinsx: 
number of bins on X-axis

xlow: 
low edge of the first bin of X-axis

xup: 
upper edge of the last bin of X-axis

nbinsy: 
number of bins on Y axis

ylow: 
low edge of the first bin of Y-axis

yup: 
upper edge of the last bin of Y-axis 
";

%feature("docstring")  Histogram2D::Histogram2D "Histogram2D::Histogram2D(int nbinsx, const std::vector< double > &xbins, int nbinsy, const std::vector< double > &ybins)

Constructor for variable bin size histograms.

Parameters:
-----------

nbinsx: 
number of bins on X-axis

xbins: 
Array of size nbins+1 containing low-edges for each bin and upper edge of last bin.

nbinsy: 
number of bins on Y-axis

ybins: 
Array of size nbins+1 containing low-edges for each bin and upper edge of last bin. 
";

%feature("docstring")  Histogram2D::Histogram2D "Histogram2D::Histogram2D(const IAxis &axis_x, const IAxis &axis_y)

Constructor for 2D histogram with custom axes. 
";

%feature("docstring")  Histogram2D::Histogram2D "Histogram2D::Histogram2D(const OutputData< double > &data)

Constructor for 2D histograms from basic  OutputData object. 
";

%feature("docstring")  Histogram2D::Histogram2D "Histogram2D::Histogram2D(std::vector< std::vector< double >> data)

Constructor for 2D histograms from numpy array (thanks to swig) 
";

%feature("docstring")  Histogram2D::clone "Histogram2D * Histogram2D::clone() const

Returns clone of other histogram. 
";

%feature("docstring")  Histogram2D::getRank "size_t Histogram2D::getRank() const

Returns the number of histogram dimensions. 
";

%feature("docstring")  Histogram2D::fill "int Histogram2D::fill(double x, double y, double weight=1.0)

Increment bin with abscissa x and ordinate y with a weight. 
";

%feature("docstring")  Histogram2D::projectionX "Histogram1D * Histogram2D::projectionX()

Project a 2D histogram into 1D histogram along X. The projection is made from all bins along y-axis. 
";

%feature("docstring")  Histogram2D::projectionX "Histogram1D * Histogram2D::projectionX(double yvalue)

Project a 2D histogram into 1D histogram along X. The projection is made from the y-bin closest to given ordinate yvalue.

Parameters:
-----------

yvalue: 
the value on y-axis at which projection is taken 
";

%feature("docstring")  Histogram2D::projectionX "Histogram1D * Histogram2D::projectionX(double ylow, double yup)

Project a 2D histogram into 1D histogram along X. The projection is made from all y-bins corresponding to ordinate between ylow and yup.

Parameters:
-----------

ylow: 
lower edje on y-axis

yup: 
upper edje on y-axis 
";

%feature("docstring")  Histogram2D::projectionY "Histogram1D * Histogram2D::projectionY()

Project a 2D histogram into 1D histogram along Y. The projection is made from all bins along x-axis. 
";

%feature("docstring")  Histogram2D::projectionY "Histogram1D * Histogram2D::projectionY(double xvalue)

Project a 2D histogram into 1D histogram along Y. The projection is made from the x-bin closest to given abscissa xvalue.

Parameters:
-----------

xvalue: 
the value on x-axis at which projection is taken 
";

%feature("docstring")  Histogram2D::projectionY "Histogram1D * Histogram2D::projectionY(double xlow, double xup)

Project a 2D histogram into 1D histogram along Y. The projection is made from all x-bins corresponding to abscissa between xlow and xup.

Parameters:
-----------

xlow: 
lower edje on x-axis

xup: 
upper edje on x-axis 
";

%feature("docstring")  Histogram2D::crop "Histogram2D * Histogram2D::crop(double xmin, double ymin, double xmax, double ymax)

Creates new histogram by applying rectangular clip. 
";

%feature("docstring")  Histogram2D::setContent "void Histogram2D::setContent(const std::vector< std::vector< double >> &data)

Sets the values in histograms channels from numpy array,. 
";

%feature("docstring")  Histogram2D::addContent "void Histogram2D::addContent(const std::vector< std::vector< double >> &data)

Add to values in histograms channels from numpy array,. 
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


// File: classIChiSquaredModule.xml
%feature("docstring") IChiSquaredModule "

Interface residual calculations.

C++ includes: IChiSquaredModule.h
";

%feature("docstring")  IChiSquaredModule::IChiSquaredModule "IChiSquaredModule::IChiSquaredModule()
";

%feature("docstring")  IChiSquaredModule::~IChiSquaredModule "IChiSquaredModule::~IChiSquaredModule()
";

%feature("docstring")  IChiSquaredModule::clone "virtual IChiSquaredModule* IChiSquaredModule::clone() const =0

clone method 
";

%feature("docstring")  IChiSquaredModule::varianceFunction "const IVarianceFunction * IChiSquaredModule::varianceFunction() const

Returns squared function. 
";

%feature("docstring")  IChiSquaredModule::setVarianceFunction "void IChiSquaredModule::setVarianceFunction(const IVarianceFunction &variance_function)

Sets squared function. 
";

%feature("docstring")  IChiSquaredModule::getIntensityFunction "const IIntensityFunction * IChiSquaredModule::getIntensityFunction() const

Returns data rescaler. 
";

%feature("docstring")  IChiSquaredModule::setIntensityFunction "void IChiSquaredModule::setIntensityFunction(const IIntensityFunction &intensity_function)

Sets data rescaler. 
";

%feature("docstring")  IChiSquaredModule::residual "virtual double IChiSquaredModule::residual(double a, double b, double weight)=0
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


// File: classIDetector.xml
%feature("docstring") IDetector "

Abstract detector interface.

C++ includes: IDetector.h
";

%feature("docstring")  IDetector::IDetector "IDetector::IDetector()
";

%feature("docstring")  IDetector::clone "IDetector* IDetector::clone() const override=0
";

%feature("docstring")  IDetector::~IDetector "IDetector::~IDetector()
";

%feature("docstring")  IDetector::init "virtual void IDetector::init(const Beam &)

Inits detector with the beam settings. 
";

%feature("docstring")  IDetector::addAxis "void IDetector::addAxis(const IAxis &axis)
";

%feature("docstring")  IDetector::getAxis "const IAxis & IDetector::getAxis(size_t index) const
";

%feature("docstring")  IDetector::dimension "size_t IDetector::dimension() const

Returns actual dimensionality of the detector (number of defined axes) 
";

%feature("docstring")  IDetector::axisBinIndex "size_t IDetector::axisBinIndex(size_t index, size_t selected_axis) const

Calculate axis index for given global index. 
";

%feature("docstring")  IDetector::totalSize "size_t IDetector::totalSize() const

Returns total number of pixels. 
";

%feature("docstring")  IDetector::detectorMask "virtual const DetectorMask* IDetector::detectorMask() const =0

Returns detector masks container. 
";

%feature("docstring")  IDetector::setAnalyzerProperties "void IDetector::setAnalyzerProperties(const kvector_t direction, double efficiency, double total_transmission)

Sets the polarization analyzer characteristics of the detector. 
";

%feature("docstring")  IDetector::setDetectorResolution "void IDetector::setDetectorResolution(const IDetectorResolution &p_detector_resolution)

Sets the detector resolution. 
";

%feature("docstring")  IDetector::setResolutionFunction "void IDetector::setResolutionFunction(const IResolutionFunction2D &resFunc)
";

%feature("docstring")  IDetector::applyDetectorResolution "void IDetector::applyDetectorResolution(OutputData< double > *p_intensity_map) const

Applies the detector resolution to the given intensity maps. 
";

%feature("docstring")  IDetector::removeDetectorResolution "void IDetector::removeDetectorResolution()

Removes detector resolution function. 
";

%feature("docstring")  IDetector::detectorResolution "const IDetectorResolution * IDetector::detectorResolution() const

Returns a pointer to detector resolution object. 
";

%feature("docstring")  IDetector::createDetectorMap "std::unique_ptr< OutputData< double > > IDetector::createDetectorMap() const

Returns empty detector map in given axes units. 
";

%feature("docstring")  IDetector::regionOfInterest "virtual const RegionOfInterest* IDetector::regionOfInterest() const =0

Returns region of interest if exists. 
";

%feature("docstring")  IDetector::resetRegionOfInterest "virtual void IDetector::resetRegionOfInterest()=0

Resets region of interest making whole detector plane available for the simulation. 
";

%feature("docstring")  IDetector::detectionProperties "const DetectionProperties& IDetector::detectionProperties() const

Returns detection properties. 
";

%feature("docstring")  IDetector::createDetectorIntensity "OutputData< double > * IDetector::createDetectorIntensity(const std::vector< SimulationElement > &elements) const

Returns new intensity map with detector resolution applied. Map will be cropped to ROI if ROI is present. 
";

%feature("docstring")  IDetector::defaultAxesUnits "virtual Axes::Units IDetector::defaultAxesUnits() const

Return default axes units. 
";

%feature("docstring")  IDetector::numberOfSimulationElements "size_t IDetector::numberOfSimulationElements() const

Returns number of simulation elements. 
";

%feature("docstring")  IDetector::getChildren "std::vector< const INode * > IDetector::getChildren() const override
";

%feature("docstring")  IDetector::iterate "void IDetector::iterate(std::function< void(const_iterator)> func, bool visit_masks=false) const
";


// File: classIDetector2D.xml
%feature("docstring") IDetector2D "

Abstract 2D detector interface.

C++ includes: IDetector2D.h
";

%feature("docstring")  IDetector2D::IDetector2D "IDetector2D::IDetector2D()
";

%feature("docstring")  IDetector2D::clone "IDetector2D* IDetector2D::clone() const override=0
";

%feature("docstring")  IDetector2D::~IDetector2D "IDetector2D::~IDetector2D()
";

%feature("docstring")  IDetector2D::setDetectorParameters "void IDetector2D::setDetectorParameters(size_t n_x, double x_min, double x_max, size_t n_y, double y_min, double y_max)

Sets detector parameters using angle ranges. 
";

%feature("docstring")  IDetector2D::removeMasks "void IDetector2D::removeMasks()

Removes all masks from the detector. 
";

%feature("docstring")  IDetector2D::detectorMask "const DetectorMask * IDetector2D::detectorMask() const override

Returns detector masks container. 
";

%feature("docstring")  IDetector2D::addMask "void IDetector2D::addMask(const IShape2D &shape, bool mask_value=true)

Adds mask of given shape to the stack of detector masks. The mask value 'true' means that the channel will be excluded from the simulation. The mask which is added last has priority.

Parameters:
-----------

shape: 
The shape of mask (Rectangle, Polygon, Line, Ellipse)

mask_value: 
The value of mask 
";

%feature("docstring")  IDetector2D::maskAll "void IDetector2D::maskAll()

Put the mask for all detector channels (i.e. exclude whole detector from the analysis) 
";

%feature("docstring")  IDetector2D::regionOfInterest "const RegionOfInterest * IDetector2D::regionOfInterest() const override

Returns region of interest if exists. 
";

%feature("docstring")  IDetector2D::setRegionOfInterest "void IDetector2D::setRegionOfInterest(double xlow, double ylow, double xup, double yup)

Sets rectangular region of interest with lower left and upper right corners defined. 
";

%feature("docstring")  IDetector2D::resetRegionOfInterest "void IDetector2D::resetRegionOfInterest() override

Resets region of interest making whole detector plane available for the simulation. 
";

%feature("docstring")  IDetector2D::active_indices "std::vector< size_t > IDetector2D::active_indices() const

Returns vector of unmasked detector indices. 
";

%feature("docstring")  IDetector2D::createPixel "virtual IPixel* IDetector2D::createPixel(size_t index) const =0

Creates an IPixel for the given  OutputData object and index. 
";

%feature("docstring")  IDetector2D::indexOfSpecular "virtual size_t IDetector2D::indexOfSpecular(const Beam &beam) const =0

Returns index of pixel that contains the specular wavevector. If no pixel contains this specular wavevector, the number of pixels is returned. This corresponds to an overflow index. 
";

%feature("docstring")  IDetector2D::createContext "std::unique_ptr< DetectorContext > IDetector2D::createContext() const
";


// File: classIDetectorResolution.xml
%feature("docstring") IDetectorResolution "

Interface for detector resolution algorithms

C++ includes: IDetectorResolution.h
";

%feature("docstring")  IDetectorResolution::~IDetectorResolution "virtual IDetectorResolution::~IDetectorResolution()
";

%feature("docstring")  IDetectorResolution::applyDetectorResolution "virtual void IDetectorResolution::applyDetectorResolution(OutputData< double > *p_intensity_map) const =0

Apply the resolution function to the intensity data. 
";

%feature("docstring")  IDetectorResolution::applyDetectorResolutionPol "void IDetectorResolution::applyDetectorResolutionPol(OutputData< Eigen::Matrix2d > *p_matrix_intensity) const

Applies the detector resolution to the matrix-valued intensity data. 
";

%feature("docstring")  IDetectorResolution::clone "virtual IDetectorResolution* IDetectorResolution::clone() const =0
";


// File: classIFootprintFactor.xml
%feature("docstring") IFootprintFactor "

Abstract base for classes that calculate the beam footprint factor

C++ includes: IFootprintFactor.h
";

%feature("docstring")  IFootprintFactor::IFootprintFactor "IFootprintFactor::IFootprintFactor(const NodeMeta &meta, const std::vector< double > &PValues)
";

%feature("docstring")  IFootprintFactor::IFootprintFactor "IFootprintFactor::IFootprintFactor()=delete
";

%feature("docstring")  IFootprintFactor::~IFootprintFactor "IFootprintFactor::~IFootprintFactor()
";

%feature("docstring")  IFootprintFactor::clone "virtual IFootprintFactor* IFootprintFactor::clone() const =0
";

%feature("docstring")  IFootprintFactor::setWidthRatio "void IFootprintFactor::setWidthRatio(double width_ratio)
";

%feature("docstring")  IFootprintFactor::widthRatio "double IFootprintFactor::widthRatio() const
";

%feature("docstring")  IFootprintFactor::calculate "virtual double IFootprintFactor::calculate(double alpha) const =0

Calculate footprint correction coefficient from the beam incident angle  alpha. 
";

%feature("docstring")  IFootprintFactor::print "virtual std::string IFootprintFactor::print() const =0

Print python-formatted footprint definition. 
";


// File: classIHistogram.xml
%feature("docstring") IHistogram "

Base class for 1D and 2D histograms holding values of double type.

C++ includes: IHistogram.h
";

%feature("docstring")  IHistogram::IHistogram "IHistogram::IHistogram()
";

%feature("docstring")  IHistogram::IHistogram "IHistogram::IHistogram(const IHistogram &other)
";

%feature("docstring")  IHistogram::~IHistogram "virtual IHistogram::~IHistogram()
";

%feature("docstring")  IHistogram::IHistogram "IHistogram::IHistogram(const IAxis &axis_x)
";

%feature("docstring")  IHistogram::IHistogram "IHistogram::IHistogram(const IAxis &axis_x, const IAxis &axis_y)
";

%feature("docstring")  IHistogram::clone "virtual IHistogram* IHistogram::clone() const =0
";

%feature("docstring")  IHistogram::getRank "virtual size_t IHistogram::getRank() const =0

Returns number of histogram dimensions. 
";

%feature("docstring")  IHistogram::getTotalNumberOfBins "size_t IHistogram::getTotalNumberOfBins() const

Returns total number of histogram bins. For 2D histograms the result will be the product of bin numbers along X and Y axes. 
";

%feature("docstring")  IHistogram::getXaxis "const IAxis & IHistogram::getXaxis() const

returns x-axis 
";

%feature("docstring")  IHistogram::getYaxis "const IAxis & IHistogram::getYaxis() const

returns y-axis for 2D histograms 
";

%feature("docstring")  IHistogram::getXmin "double IHistogram::getXmin() const

Returns x-axis min (lower edge of first bin). 
";

%feature("docstring")  IHistogram::getXmax "double IHistogram::getXmax() const

Returns x-axis max (upper edge of last bin). 
";

%feature("docstring")  IHistogram::getNbinsX "size_t IHistogram::getNbinsX() const

Returns number of bins on x-axis. 
";

%feature("docstring")  IHistogram::getYmin "double IHistogram::getYmin() const

Returns y-axis min (lower edge of first bin) for 2D histograms. 
";

%feature("docstring")  IHistogram::getYmax "double IHistogram::getYmax() const

Returns y-axis max (upper edge of last bin) for 2D histograms. 
";

%feature("docstring")  IHistogram::getNbinsY "size_t IHistogram::getNbinsY() const

Returns number of bins on y-axis. 
";

%feature("docstring")  IHistogram::getGlobalBin "size_t IHistogram::getGlobalBin(size_t binx, size_t biny=0) const

Returns global bin index for given axes indices. For 1D, just returns binx. 
";

%feature("docstring")  IHistogram::findGlobalBin "size_t IHistogram::findGlobalBin(double x, double y) const

Returns closest global bin index for given axes coordinates. 
";

%feature("docstring")  IHistogram::getXaxisIndex "size_t IHistogram::getXaxisIndex(size_t i) const

Returns x-axis index for global bin index i. 
";

%feature("docstring")  IHistogram::getYaxisIndex "size_t IHistogram::getYaxisIndex(size_t i) const

Returns y-axis index for global bin index i. 
";

%feature("docstring")  IHistogram::getXaxisValue "double IHistogram::getXaxisValue(size_t i)

Returns the center of bin i of the x axis. 
";

%feature("docstring")  IHistogram::getYaxisValue "double IHistogram::getYaxisValue(size_t i)

Returns the center of bin i of the y axis. 
";

%feature("docstring")  IHistogram::getBinContent "double IHistogram::getBinContent(size_t i) const

Returns content (accumulated value) of bin i. 
";

%feature("docstring")  IHistogram::getData "const OutputData<CumulativeValue>& IHistogram::getData() const
";

%feature("docstring")  IHistogram::getData "OutputData<CumulativeValue>& IHistogram::getData()
";

%feature("docstring")  IHistogram::getBinContent "double IHistogram::getBinContent(size_t binx, size_t biny) const

Returns content (accumulated value) of the 2D histogram bin. 
";

%feature("docstring")  IHistogram::setBinContent "void IHistogram::setBinContent(size_t i, double value)

Sets content of the bin corresponding to the globalbin number. 
";

%feature("docstring")  IHistogram::addBinContent "void IHistogram::addBinContent(size_t i, double value)

Add the value to the bin. 
";

%feature("docstring")  IHistogram::getBinError "double IHistogram::getBinError(size_t i) const

Returns error of the bin with given index. 
";

%feature("docstring")  IHistogram::getBinError "double IHistogram::getBinError(size_t binx, size_t biny) const

Returns error of the bin with given indices (for 2D histograms). 
";

%feature("docstring")  IHistogram::getBinAverage "double IHistogram::getBinAverage(size_t i) const

Returns average value in the bin with given index. 
";

%feature("docstring")  IHistogram::getBinAverage "double IHistogram::getBinAverage(size_t binx, size_t biny) const

Returns average value of the bin with given indices (for 2D histograms). 
";

%feature("docstring")  IHistogram::getBinNumberOfEntries "int IHistogram::getBinNumberOfEntries(size_t i) const

Returns number of entries in the bin with given index. 
";

%feature("docstring")  IHistogram::getBinNumberOfEntries "int IHistogram::getBinNumberOfEntries(size_t binx, size_t biny) const

Returns number of entries in the bin with given indices (for 2D histograms). 
";

%feature("docstring")  IHistogram::getMaximum "double IHistogram::getMaximum() const

Returns histogram maximum value (maximum of  getBinContent() over all bins) 
";

%feature("docstring")  IHistogram::getMaximumBinIndex "size_t IHistogram::getMaximumBinIndex() const

Returns globalbin index with maximum content. 
";

%feature("docstring")  IHistogram::getMinimum "double IHistogram::getMinimum() const

Returns histogram minimum value (minimum of  getBinContent() over all bins) 
";

%feature("docstring")  IHistogram::getMinimumBinIndex "size_t IHistogram::getMinimumBinIndex() const

Returns globalbin index with minimum content. 
";

%feature("docstring")  IHistogram::scale "void IHistogram::scale(double value)

Multiply this histogram (every bin content value) by a constant. 
";

%feature("docstring")  IHistogram::integral "double IHistogram::integral() const

Returns integral of bins content (computed as a sum of all bin content). 
";

%feature("docstring")  IHistogram::array "PyObject * IHistogram::array(DataType dataType=DataType::INTEGRAL) const

Returns numpy array with bin content (accumulated values). 
";

%feature("docstring")  IHistogram::getArray "PyObject * IHistogram::getArray(DataType dataType=DataType::INTEGRAL) const

Deprecated
Use  array() instead. 
";

%feature("docstring")  IHistogram::reset "void IHistogram::reset()

Reset histogram content (axes remains) 
";

%feature("docstring")  IHistogram::createOutputData "OutputData< double > * IHistogram::createOutputData(DataType dataType=DataType::INTEGRAL) const

creates new  OutputData with histogram's shape and values corresponding to DataType

creates new  OutputData with histogram's shape and put there values corresponding to DataType 
";

%feature("docstring")  IHistogram::hasSameShape "bool IHistogram::hasSameShape(const IHistogram &other) const

Returns true if objects a) have same dimensions b) bin boundaries of axes coincide. 
";

%feature("docstring")  IHistogram::hasSameDimensions "bool IHistogram::hasSameDimensions(const IHistogram &other) const

Returns true if object have same rank and number of axes bins. 
";

%feature("docstring")  IHistogram::relativeDifferenceHistogram "IHistogram * IHistogram::relativeDifferenceHistogram(const IHistogram &rhs)

returns histogram representing relative difference of two histograms. 
";

%feature("docstring")  IHistogram::save "void IHistogram::save(const std::string &filename)

Saves histogram in file Following formats are available: *.txt, *.tif, *.int (*.txt.gz, *.tif.gz, *.int.gz) 
";

%feature("docstring")  IHistogram::load "void IHistogram::load(const std::string &filename)

Loads histogram from file, the shape of array in file should match Following formats are available: *.txt, *.tif, *.int (*.txt.gz, *.tif.gz, *.int.gz) Only bin content will be loaded, histogram axes remain the same. 
";


// File: classIIntensityFunction.xml
%feature("docstring") IIntensityFunction "

Interface for applying arbitrary function to the measured intensity.

C++ includes: IIntensityFunction.h
";

%feature("docstring")  IIntensityFunction::~IIntensityFunction "IIntensityFunction::~IIntensityFunction()
";

%feature("docstring")  IIntensityFunction::clone "virtual IIntensityFunction* IIntensityFunction::clone() const =0
";

%feature("docstring")  IIntensityFunction::evaluate "virtual double IIntensityFunction::evaluate(double value) const =0
";


// File: classIMetricWrapper.xml
%feature("docstring") IMetricWrapper "";

%feature("docstring")  IMetricWrapper::~IMetricWrapper "IMetricWrapper::~IMetricWrapper()
";

%feature("docstring")  IMetricWrapper::compute "virtual double IMetricWrapper::compute(const std::vector< SimDataPair > &fit_objects, size_t n_pars) const =0
";


// File: classInstrument.xml
%feature("docstring") Instrument "

Assembles beam, detector and their relative positions with respect to the sample.

C++ includes: Instrument.h
";

%feature("docstring")  Instrument::Instrument "Instrument::Instrument()
";

%feature("docstring")  Instrument::Instrument "Instrument::Instrument(const Instrument &other)
";

%feature("docstring")  Instrument::~Instrument "Instrument::~Instrument()
";

%feature("docstring")  Instrument::accept "void Instrument::accept(INodeVisitor *visitor) const final
";

%feature("docstring")  Instrument::getBeam "Beam& Instrument::getBeam()
";

%feature("docstring")  Instrument::getBeam "const Beam& Instrument::getBeam() const
";

%feature("docstring")  Instrument::setBeam "void Instrument::setBeam(const Beam &beam)
";

%feature("docstring")  Instrument::setBeamParameters "void Instrument::setBeamParameters(double wavelength, double alpha_i, double phi_i)

Sets the beam wavelength and incoming angles. 
";

%feature("docstring")  Instrument::setBeamIntensity "void Instrument::setBeamIntensity(double intensity)
";

%feature("docstring")  Instrument::setBeamPolarization "void Instrument::setBeamPolarization(const kvector_t bloch_vector)

Sets the beam's polarization according to the given Bloch vector. 
";

%feature("docstring")  Instrument::getBeamIntensity "double Instrument::getBeamIntensity() const
";

%feature("docstring")  Instrument::getDetector "const IDetector * Instrument::getDetector() const
";

%feature("docstring")  Instrument::detector "IDetector & Instrument::detector()
";

%feature("docstring")  Instrument::detector "const IDetector & Instrument::detector() const
";

%feature("docstring")  Instrument::detector2D "IDetector2D & Instrument::detector2D()
";

%feature("docstring")  Instrument::detector2D "const IDetector2D & Instrument::detector2D() const
";

%feature("docstring")  Instrument::getDetectorMask "const DetectorMask * Instrument::getDetectorMask() const
";

%feature("docstring")  Instrument::getDetectorAxis "const IAxis & Instrument::getDetectorAxis(size_t index) const
";

%feature("docstring")  Instrument::getDetectorDimension "size_t Instrument::getDetectorDimension() const
";

%feature("docstring")  Instrument::setDetector "void Instrument::setDetector(const IDetector &detector)

Sets the detector (axes can be overwritten later) 
";

%feature("docstring")  Instrument::setDetectorResolutionFunction "void Instrument::setDetectorResolutionFunction(const IResolutionFunction2D &p_resolution_function)

Sets detector resolution function. 
";

%feature("docstring")  Instrument::removeDetectorResolution "void Instrument::removeDetectorResolution()

Removes detector resolution function. 
";

%feature("docstring")  Instrument::setAnalyzerProperties "void Instrument::setAnalyzerProperties(const kvector_t direction, double efficiency, double total_transmission)

Sets the polarization analyzer characteristics of the detector. 
";

%feature("docstring")  Instrument::applyDetectorResolution "void Instrument::applyDetectorResolution(OutputData< double > *p_intensity_map) const

apply the detector resolution to the given intensity map 
";

%feature("docstring")  Instrument::initDetector "void Instrument::initDetector()

init detector with beam settings 
";

%feature("docstring")  Instrument::getChildren "std::vector< const INode * > Instrument::getChildren() const
";


// File: classIntensityDataIOFactory.xml
%feature("docstring") IntensityDataIOFactory "

Provides users with possibility to read and write IntensityData from/to files in different format. Type of the file will be deduced from file name. *.txt - ASCII file with 2D array [nrow][ncol], layout as in numpy. *.int - BornAgain internal ASCII format. *.tif - 32-bits tiff file. If file name ends woth \"*.gz\" or \"*.bz2\" the file will be zipped on the fly using appropriate algorithm. Usage:

C++ includes: IntensityDataIOFactory.h
";


// File: classIntensityFunctionLog.xml
%feature("docstring") IntensityFunctionLog "

Algorithm for applying log function to the measured intensity.

C++ includes: IIntensityFunction.h
";

%feature("docstring")  IntensityFunctionLog::clone "IntensityFunctionLog * IntensityFunctionLog::clone() const
";

%feature("docstring")  IntensityFunctionLog::evaluate "double IntensityFunctionLog::evaluate(double value) const
";


// File: classIntensityFunctionSqrt.xml
%feature("docstring") IntensityFunctionSqrt "

Algorithm for applying sqrt function to the measured intensity.

C++ includes: IIntensityFunction.h
";

%feature("docstring")  IntensityFunctionSqrt::clone "IntensityFunctionSqrt * IntensityFunctionSqrt::clone() const
";

%feature("docstring")  IntensityFunctionSqrt::evaluate "double IntensityFunctionSqrt::evaluate(double value) const
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


// File: classIOutputDataReadStrategy.xml
%feature("docstring") IOutputDataReadStrategy "

Interface for reading strategy of  OutputData from file.

C++ includes: OutputDataReadStrategy.h
";

%feature("docstring")  IOutputDataReadStrategy::~IOutputDataReadStrategy "virtual IOutputDataReadStrategy::~IOutputDataReadStrategy()
";

%feature("docstring")  IOutputDataReadStrategy::readOutputData "virtual OutputData<double>* IOutputDataReadStrategy::readOutputData(std::istream &input_stream)=0
";


// File: classIOutputDataWriteStrategy.xml
%feature("docstring") IOutputDataWriteStrategy "

Strategy interface to write OututData in file

C++ includes: OutputDataWriteStrategy.h
";

%feature("docstring")  IOutputDataWriteStrategy::IOutputDataWriteStrategy "IOutputDataWriteStrategy::IOutputDataWriteStrategy()
";

%feature("docstring")  IOutputDataWriteStrategy::~IOutputDataWriteStrategy "virtual IOutputDataWriteStrategy::~IOutputDataWriteStrategy()
";

%feature("docstring")  IOutputDataWriteStrategy::writeOutputData "virtual void IOutputDataWriteStrategy::writeOutputData(const OutputData< double > &data, std::ostream &output_stream)=0
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


// File: classIResolutionFunction2D.xml
%feature("docstring") IResolutionFunction2D "

Interface providing two-dimensional resolution function.

C++ includes: IResolutionFunction2D.h
";

%feature("docstring")  IResolutionFunction2D::IResolutionFunction2D "IResolutionFunction2D::IResolutionFunction2D()=default
";

%feature("docstring")  IResolutionFunction2D::IResolutionFunction2D "IResolutionFunction2D::IResolutionFunction2D(const NodeMeta &meta, const std::vector< double > &PValues)
";

%feature("docstring")  IResolutionFunction2D::~IResolutionFunction2D "virtual IResolutionFunction2D::~IResolutionFunction2D()
";

%feature("docstring")  IResolutionFunction2D::evaluateCDF "virtual double IResolutionFunction2D::evaluateCDF(double x, double y) const =0
";

%feature("docstring")  IResolutionFunction2D::clone "virtual IResolutionFunction2D* IResolutionFunction2D::clone() const =0
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


// File: classIsGISAXSDetector.xml
%feature("docstring") IsGISAXSDetector "

A spherical detector used for validation with IsGISAXS results.

C++ includes: IsGISAXSDetector.h
";

%feature("docstring")  IsGISAXSDetector::IsGISAXSDetector "IsGISAXSDetector::IsGISAXSDetector()
";

%feature("docstring")  IsGISAXSDetector::IsGISAXSDetector "IsGISAXSDetector::IsGISAXSDetector(size_t n_phi, double phi_min, double phi_max, size_t n_alpha, double alpha_min, double alpha_max)
";

%feature("docstring")  IsGISAXSDetector::IsGISAXSDetector "IsGISAXSDetector::IsGISAXSDetector(const IsGISAXSDetector &other)
";

%feature("docstring")  IsGISAXSDetector::clone "IsGISAXSDetector * IsGISAXSDetector::clone() const override
";

%feature("docstring")  IsGISAXSDetector::accept "void IsGISAXSDetector::accept(INodeVisitor *visitor) const final
";


// File: classISpecularScan.xml
%feature("docstring") ISpecularScan "

Base abstract class for all types of specular scans.

C++ includes: ISpecularScan.h
";

%feature("docstring")  ISpecularScan::ISpecularScan "ISpecularScan::ISpecularScan(SPECULAR_DATA_TYPE data_type)
";

%feature("docstring")  ISpecularScan::~ISpecularScan "ISpecularScan::~ISpecularScan() override
";

%feature("docstring")  ISpecularScan::clone "ISpecularScan* ISpecularScan::clone() const override=0
";

%feature("docstring")  ISpecularScan::generateSimulationElements "virtual std::vector<SpecularSimulationElement> ISpecularScan::generateSimulationElements() const =0

Generates simulation elements for specular simulations. 
";

%feature("docstring")  ISpecularScan::coordinateAxis "virtual const IAxis* ISpecularScan::coordinateAxis() const =0

Returns coordinate axis assigned to the data holder. 
";

%feature("docstring")  ISpecularScan::footprintFactor "virtual const IFootprintFactor* ISpecularScan::footprintFactor() const =0

Returns  IFootprintFactor object pointer. 
";

%feature("docstring")  ISpecularScan::footprint "virtual std::vector<double> ISpecularScan::footprint(size_t i, size_t n_elements) const =0

Returns footprint correction factor for a range of simulation elements of size  n_elements and starting from element with index  i. 
";

%feature("docstring")  ISpecularScan::numberOfSimulationElements "virtual size_t ISpecularScan::numberOfSimulationElements() const =0

Returns the number of simulation elements. 
";

%feature("docstring")  ISpecularScan::createIntensities "virtual std::vector<double> ISpecularScan::createIntensities(const std::vector< SpecularSimulationElement > &sim_elements) const =0

Returns intensity vector corresponding to convolution of given simulation elements. 
";

%feature("docstring")  ISpecularScan::print "virtual std::string ISpecularScan::print() const =0

Print scan definition in python format. 
";

%feature("docstring")  ISpecularScan::dataType "SPECULAR_DATA_TYPE ISpecularScan::dataType() const
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


// File: classIUnitConverter.xml
%feature("docstring") IUnitConverter "

Interface to provide axis translations to different units for simulation output

C++ includes: IUnitConverter.h
";

%feature("docstring")  IUnitConverter::~IUnitConverter "IUnitConverter::~IUnitConverter()
";

%feature("docstring")  IUnitConverter::clone "virtual IUnitConverter* IUnitConverter::clone() const =0
";

%feature("docstring")  IUnitConverter::dimension "virtual size_t IUnitConverter::dimension() const =0
";

%feature("docstring")  IUnitConverter::calculateMin "virtual double IUnitConverter::calculateMin(size_t i_axis, Axes::Units units_type) const =0
";

%feature("docstring")  IUnitConverter::calculateMax "virtual double IUnitConverter::calculateMax(size_t i_axis, Axes::Units units_type) const =0
";

%feature("docstring")  IUnitConverter::axisSize "virtual size_t IUnitConverter::axisSize(size_t i_axis) const =0
";

%feature("docstring")  IUnitConverter::axisName "std::string IUnitConverter::axisName(size_t i_axis, Axes::Units units_type=Axes::Units::DEFAULT) const
";

%feature("docstring")  IUnitConverter::availableUnits "virtual std::vector<Axes::Units> IUnitConverter::availableUnits() const =0
";

%feature("docstring")  IUnitConverter::defaultUnits "virtual Axes::Units IUnitConverter::defaultUnits() const =0
";

%feature("docstring")  IUnitConverter::substituteDefaultUnits "Axes::Units IUnitConverter::substituteDefaultUnits(Axes::Units units) const
";

%feature("docstring")  IUnitConverter::createConvertedAxis "virtual std::unique_ptr<IAxis> IUnitConverter::createConvertedAxis(size_t i_axis, Axes::Units units) const =0
";

%feature("docstring")  IUnitConverter::createConvertedData "std::unique_ptr< OutputData< double > > IUnitConverter::createConvertedData(const OutputData< double > &data, Axes::Units units) const

Creates  OutputData array in converter units. 
";


// File: classIVarianceFunction.xml
%feature("docstring") IVarianceFunction "

Variance function interface.

C++ includes: VarianceFunctions.h
";

%feature("docstring")  IVarianceFunction::IVarianceFunction "IVarianceFunction::IVarianceFunction()
";

%feature("docstring")  IVarianceFunction::~IVarianceFunction "IVarianceFunction::~IVarianceFunction()
";

%feature("docstring")  IVarianceFunction::clone "virtual IVarianceFunction* IVarianceFunction::clone() const =0
";

%feature("docstring")  IVarianceFunction::variance "virtual double IVarianceFunction::variance(double real_value, double simulated_value) const =0
";

%feature("docstring")  IVarianceFunction::IVarianceFunction "IVarianceFunction::IVarianceFunction(const IVarianceFunction &)=delete
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


// File: classLLData.xml
%feature("docstring") LLData "

Template class to store data of any type in multi-dimensional space (low-level).

C++ includes: LLData.h
";

%feature("docstring")  LLData::LLData "LLData< T >::LLData(size_t rank, const int *dimensions)
";

%feature("docstring")  LLData::LLData "LLData< T >::LLData(const LLData< T > &right)
";

%feature("docstring")  LLData::~LLData "LLData< T >::~LLData()
";

%feature("docstring")  LLData::meanValues "LLData<double> LLData< T >::meanValues() const
";

%feature("docstring")  LLData::atCoordinate "T & LLData< T >::atCoordinate(int *coordinate)
";

%feature("docstring")  LLData::atCoordinate "const T & LLData< T >::atCoordinate(int *coordinate) const
";

%feature("docstring")  LLData::setAll "void LLData< T >::setAll(const T &value)
";

%feature("docstring")  LLData::scaleAll "void LLData< T >::scaleAll(const T &factor)
";

%feature("docstring")  LLData::getTotalSize "size_t LLData< T >::getTotalSize() const
";

%feature("docstring")  LLData::getRank "size_t LLData< T >::getRank() const
";

%feature("docstring")  LLData::getDimensions "const int* LLData< T >::getDimensions() const
";

%feature("docstring")  LLData::getTotalSum "T LLData< T >::getTotalSum() const
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


// File: structArrayUtils_1_1CreateDataImpl_1_1nDim.xml


// File: structArrayUtils_1_1CreateDataImpl_1_1nDim_3_01std_1_1vector_3_01T_00_01A_01_4_01_4.xml


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

Sets beam parameters from here (forwarded to  Instrument) 
";

%feature("docstring")  OffSpecSimulation::beamAxis "const IAxis * OffSpecSimulation::beamAxis() const

Returns axis of the beam. 
";

%feature("docstring")  OffSpecSimulation::createUnitConverter "std::unique_ptr< IUnitConverter > OffSpecSimulation::createUnitConverter() const
";

%feature("docstring")  OffSpecSimulation::intensityMapSize "size_t OffSpecSimulation::intensityMapSize() const override

Returns the total number of the intensity values in the simulation result. 
";


// File: classOffSpecularConverter.xml
%feature("docstring") OffSpecularConverter "

IUnitConverter class that handles the unit translations for off-specular simulations with a spherical detector Its default units are radians for both axes

C++ includes: SimpleUnitConverters.h
";

%feature("docstring")  OffSpecularConverter::OffSpecularConverter "OffSpecularConverter::OffSpecularConverter(const IDetector2D &detector, const Beam &beam, const IAxis &alpha_axis)
";

%feature("docstring")  OffSpecularConverter::~OffSpecularConverter "OffSpecularConverter::~OffSpecularConverter() final
";

%feature("docstring")  OffSpecularConverter::clone "OffSpecularConverter * OffSpecularConverter::clone() const final
";

%feature("docstring")  OffSpecularConverter::defaultUnits "Axes::Units OffSpecularConverter::defaultUnits() const final
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
%feature("docstring") OutputData "

Template class to store data of any type in multi-dimensional space.

C++ includes: OutputData.h
";

%feature("docstring")  OutputData::OutputData "OutputData< T >::OutputData()
";

%feature("docstring")  OutputData::OutputData "OutputData< T >::OutputData(const OutputData &)=delete
";

%feature("docstring")  OutputData::~OutputData "OutputData< T >::~OutputData()
";

%feature("docstring")  OutputData::clone "OutputData< T > * OutputData< T >::clone() const
";

%feature("docstring")  OutputData::copyFrom "void OutputData< T >::copyFrom(const OutputData< T > &x)
";

%feature("docstring")  OutputData::copyShapeFrom "void OutputData< T >::copyShapeFrom(const OutputData< U > &other)
";

%feature("docstring")  OutputData::meanValues "OutputData< double > * OutputData< T >::meanValues() const
";

%feature("docstring")  OutputData::addAxis "void OutputData< T >::addAxis(const IAxis &new_axis)
";

%feature("docstring")  OutputData::addAxis "void OutputData< T >::addAxis(const std::string &name, size_t size, double start, double end)
";

%feature("docstring")  OutputData::getAxis "const IAxis & OutputData< T >::getAxis(size_t serial_number) const

returns axis with given serial number 
";

%feature("docstring")  OutputData::getAxis "const IAxis & OutputData< T >::getAxis(const std::string &axis_name) const

returns axis with given name 
";

%feature("docstring")  OutputData::getRank "size_t OutputData< T >::getRank() const

Returns number of dimensions. 
";

%feature("docstring")  OutputData::getAllocatedSize "size_t OutputData< T >::getAllocatedSize() const

Returns total size of data buffer (product of bin number in every dimension). 
";

%feature("docstring")  OutputData::getAllSizes "std::vector< size_t > OutputData< T >::getAllSizes() const

Returns all sizes of its axes. 
";

%feature("docstring")  OutputData::getRawDataVector "std::vector< T > OutputData< T >::getRawDataVector() const

Returns copy of raw data vector. 
";

%feature("docstring")  OutputData::totalSum "T OutputData< T >::totalSum() const

Returns sum of all values in the data structure. 
";

%feature("docstring")  OutputData::begin "OutputData< T >::iterator OutputData< T >::begin()

Returns read/write iterator that points to the first element. 
";

%feature("docstring")  OutputData::begin "OutputData< T >::const_iterator OutputData< T >::begin() const

Returns read-only iterator that points to the first element. 
";

%feature("docstring")  OutputData::end "iterator OutputData< T >::end()

Returns read/write iterator that points to the one past last element. 
";

%feature("docstring")  OutputData::end "const_iterator OutputData< T >::end() const

Returns read-only iterator that points to the one past last element. 
";

%feature("docstring")  OutputData::getAxesBinIndices "std::vector< int > OutputData< T >::getAxesBinIndices(size_t global_index) const

Returns vector of axes indices for given global index

Parameters:
-----------

global_index: 
The global index of this data structure.

Vector of bin indices for all axes defined 
";

%feature("docstring")  OutputData::getAxisBinIndex "size_t OutputData< T >::getAxisBinIndex(size_t global_index, size_t i_selected_axis) const

Returns axis bin index for given global index

Parameters:
-----------

global_index: 
The global index of this data structure.

i_selected_axis: 
Serial number of selected axis.

Corresponding bin index for selected axis 
";

%feature("docstring")  OutputData::getAxisBinIndex "size_t OutputData< T >::getAxisBinIndex(size_t global_index, const std::string &axis_name) const

Returns axis bin index for given global index

Parameters:
-----------

global_index: 
The global index of this data structure.

axis_name: 
The name of selected axis.

Corresponding bin index for selected axis 
";

%feature("docstring")  OutputData::toGlobalIndex "size_t OutputData< T >::toGlobalIndex(const std::vector< unsigned > &axes_indices) const

Returns global index for specified indices of axes

Parameters:
-----------

axes_indices: 
Vector of axes indices for all specified axes in this dataset

Corresponding global index 
";

%feature("docstring")  OutputData::findGlobalIndex "size_t OutputData< T >::findGlobalIndex(const std::vector< double > &coordinates) const

Returns global index for specified axes values

Parameters:
-----------

coordinates: 
Vector of axes coordinates for all specified axes in this dataset

Closest global index 
";

%feature("docstring")  OutputData::getAxisValue "double OutputData< T >::getAxisValue(size_t global_index, size_t i_selected_axis) const

Returns the value of selected axis for given global_index.

Parameters:
-----------

global_index: 
The global index of this data structure.

i_selected_axis: 
Serial number of selected axis.

corresponding bin center of selected axis 
";

%feature("docstring")  OutputData::getAxisValue "double OutputData< T >::getAxisValue(size_t global_index, const std::string &axis_name) const

Returns the value of selected axis for given global_index.

Parameters:
-----------

global_index: 
The global index of this data structure.

axis_name: 
The name of selected axis.

corresponding bin center of selected axis 
";

%feature("docstring")  OutputData::getAxesValues "std::vector< double > OutputData< T >::getAxesValues(size_t global_index) const

Returns values on all defined axes for given globalbin number

Parameters:
-----------

global_index: 
The global index of this data structure.

Vector of corresponding bin centers 
";

%feature("docstring")  OutputData::getAxisBin "Bin1D OutputData< T >::getAxisBin(size_t global_index, size_t i_selected_axis) const

Returns bin of selected axis for given global_index.

Parameters:
-----------

global_index: 
The global index of this data structure.

i_selected_axis: 
Serial number of selected axis.

Corresponding Bin1D object 
";

%feature("docstring")  OutputData::getAxisBin "Bin1D OutputData< T >::getAxisBin(size_t global_index, const std::string &axis_name) const

Returns bin of selected axis for given global_index.

Parameters:
-----------

global_index: 
The global index of this data structure.

axis_name: 
The name of selected axis.

Corresponding Bin1D object 
";

%feature("docstring")  OutputData::clear "void OutputData< T >::clear()

Sets object into initial state (no dimensions, data) 
";

%feature("docstring")  OutputData::setAllTo "void OutputData< T >::setAllTo(const T &value)

Sets content of output data to specific value. 
";

%feature("docstring")  OutputData::scaleAll "void OutputData< T >::scaleAll(const T &factor)

multiply every item of this output data by value 
";

%feature("docstring")  OutputData::setAxisSizes "void OutputData< T >::setAxisSizes(size_t rank, int *n_dims)

Adds 'rank' axes with indicated sizes. 
";

%feature("docstring")  OutputData::setRawDataVector "void OutputData< T >::setRawDataVector(const std::vector< T > &data_vector)

Sets new values to raw data vector. 
";

%feature("docstring")  OutputData::setRawDataArray "void OutputData< T >::setRawDataArray(const T *source)

Sets new values to raw data array. 
";

%feature("docstring")  OutputData::getValue "double OutputData< T >::getValue(size_t index) const

Returns value or summed value, depending on T. 
";

%feature("docstring")  OutputData::hasSameDimensions "bool OutputData< T >::hasSameDimensions(const OutputData< U > &right) const

Returns true if object have same dimensions and number of axes bins.

Returns true if object have same dimensions. 
";

%feature("docstring")  OutputData::hasSameShape "bool OutputData< T >::hasSameShape(const OutputData< U > &right) const

Returns true if objects a) have same dimensions b) bin boundaries of axes coincide.

Returns true if object have same dimensions and shape of axis. 
";

%feature("docstring")  OutputData::getArray "PyObject* OutputData< T >::getArray() const

returns data as Python numpy array 
";

%feature("docstring")  OutputData::isInitialized "bool OutputData< T >::isInitialized() const

returns true if object is correctly initialized 
";

%feature("docstring")  OutputData::allocate "void OutputData< T >::allocate()

memory allocation for current dimensions configuration 
";


// File: classOutputDataIterator.xml
%feature("docstring") OutputDataIterator "

Iterator for underlying  OutputData container.

C++ includes: OutputDataIterator.h
";

%feature("docstring")  OutputDataIterator::OutputDataIterator "OutputDataIterator< TValue, TContainer >::OutputDataIterator()

Empty constructor to comply with stl forward iterators. 
";

%feature("docstring")  OutputDataIterator::OutputDataIterator "OutputDataIterator< TValue, TContainer >::OutputDataIterator(TContainer *p_output_data, size_t start_at_index=0)

constructor 
";

%feature("docstring")  OutputDataIterator::OutputDataIterator "OutputDataIterator< TValue, TContainer >::OutputDataIterator(const OutputDataIterator< TValue2, TContainer2 > &other)

templated copy construction 
";

%feature("docstring")  OutputDataIterator::OutputDataIterator "OutputDataIterator< TValue, TContainer >::OutputDataIterator(const OutputDataIterator< TValue, TContainer > &other)

non-templated copy construction 
";

%feature("docstring")  OutputDataIterator::~OutputDataIterator "OutputDataIterator< TValue, TContainer >::~OutputDataIterator()
";

%feature("docstring")  OutputDataIterator::getIndex "size_t OutputDataIterator< TValue, TContainer >::getIndex() const

Returns current index. 
";

%feature("docstring")  OutputDataIterator::getContainer "TContainer* OutputDataIterator< TValue, TContainer >::getContainer() const

Returns container pointer. 
";

%feature("docstring")  OutputDataIterator::swap "void OutputDataIterator< TValue, TContainer >::swap(OutputDataIterator< TValue, TContainer > &other)

Swaps iterators. 
";


// File: classOutputDataReader.xml
%feature("docstring") OutputDataReader "

Reads  OutputData from file using different reading strategies.

C++ includes: OutputDataReader.h
";

%feature("docstring")  OutputDataReader::OutputDataReader "OutputDataReader::OutputDataReader(const std::string &file_name)
";

%feature("docstring")  OutputDataReader::getOutputData "OutputData< double > * OutputDataReader::getOutputData()

read output data from file (file name was set already from OutputDataIOFactory) 
";

%feature("docstring")  OutputDataReader::setStrategy "void OutputDataReader::setStrategy(IOutputDataReadStrategy *read_strategy)

Sets concrete reading strategy. 
";


// File: classOutputDataReadFactory.xml
%feature("docstring") OutputDataReadFactory "

Creates reader appropariate for given type of files.

C++ includes: OutputDataReadFactory.h
";


// File: classOutputDataReadINTStrategy.xml
%feature("docstring") OutputDataReadINTStrategy "

Strategy to read BornAgain native IntensityData from ASCII file.

C++ includes: OutputDataReadStrategy.h
";

%feature("docstring")  OutputDataReadINTStrategy::readOutputData "OutputData< double > * OutputDataReadINTStrategy::readOutputData(std::istream &input_stream)
";


// File: classOutputDataReadNumpyTXTStrategy.xml
%feature("docstring") OutputDataReadNumpyTXTStrategy "

Strategy to read  OutputData from simple ASCII file with the layout as in numpy.savetxt.

C++ includes: OutputDataReadStrategy.h
";

%feature("docstring")  OutputDataReadNumpyTXTStrategy::readOutputData "OutputData< double > * OutputDataReadNumpyTXTStrategy::readOutputData(std::istream &input_stream)
";


// File: classOutputDataReadReflectometryStrategy.xml
%feature("docstring") OutputDataReadReflectometryStrategy "

Strategy to read Reflectometry data from ASCII file.

C++ includes: OutputDataReadStrategy.h
";

%feature("docstring")  OutputDataReadReflectometryStrategy::readOutputData "OutputData< double > * OutputDataReadReflectometryStrategy::readOutputData(std::istream &input_stream)
";


// File: classOutputDataWriteFactory.xml
%feature("docstring") OutputDataWriteFactory "

Creates writer appropariate for given type of files.

C++ includes: OutputDataWriteFactory.h
";


// File: classOutputDataWriteINTStrategy.xml
%feature("docstring") OutputDataWriteINTStrategy "

Strategy to write  OutputData to special BornAgain ASCII format

C++ includes: OutputDataWriteStrategy.h
";

%feature("docstring")  OutputDataWriteINTStrategy::writeOutputData "void OutputDataWriteINTStrategy::writeOutputData(const OutputData< double > &data, std::ostream &output_stream)
";


// File: classOutputDataWriteNumpyTXTStrategy.xml
%feature("docstring") OutputDataWriteNumpyTXTStrategy "

Strategy to write  OutputData to simple ASCII file with the layout as in numpy.savetxt

C++ includes: OutputDataWriteStrategy.h
";

%feature("docstring")  OutputDataWriteNumpyTXTStrategy::writeOutputData "void OutputDataWriteNumpyTXTStrategy::writeOutputData(const OutputData< double > &data, std::ostream &output_stream)
";


// File: classOutputDataWriter.xml
%feature("docstring") OutputDataWriter "

Write  OutputData to file using different witing strategies.

C++ includes: OutputDataWriter.h
";

%feature("docstring")  OutputDataWriter::OutputDataWriter "OutputDataWriter::OutputDataWriter(const std::string &file_name)
";

%feature("docstring")  OutputDataWriter::writeOutputData "void OutputDataWriter::writeOutputData(const OutputData< double > &data)

Writes output data to file. 
";

%feature("docstring")  OutputDataWriter::setStrategy "void OutputDataWriter::setStrategy(IOutputDataWriteStrategy *write_strategy)

Sets concrete writing strategy. 
";


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


// File: classQSpecScan.xml
%feature("docstring") QSpecScan "

Scan type with z-components of scattering vector as coordinate values. Wavelength and incident angles are not accessible separately.

C++ includes: QSpecScan.h
";

%feature("docstring")  QSpecScan::QSpecScan "QSpecScan::QSpecScan(std::vector< double > qs_nm)

Accepts qz-value vector (in inverse nm) 
";

%feature("docstring")  QSpecScan::QSpecScan "QSpecScan::QSpecScan(const IAxis &qs_nm)
";

%feature("docstring")  QSpecScan::QSpecScan "QSpecScan::QSpecScan(int nbins, double qz_min, double qz_max)

Sets q-defined specular scan. Accepts either numpy array of q-values sorted in ascending order or an IAxis object with q-values. Alternatively an axis can be defined in-place, then the first passed parameter is the number of bins, second - minimum on-axis q-value, third - maximum on-axis q_value. 
";

%feature("docstring")  QSpecScan::~QSpecScan "QSpecScan::~QSpecScan() override
";

%feature("docstring")  QSpecScan::clone "QSpecScan * QSpecScan::clone() const override
";

%feature("docstring")  QSpecScan::generateSimulationElements "std::vector< SpecularSimulationElement > QSpecScan::generateSimulationElements() const override

Generates simulation elements for specular simulations. 
";

%feature("docstring")  QSpecScan::coordinateAxis "virtual const IAxis* QSpecScan::coordinateAxis() const override

Returns coordinate axis assigned to the data holder. 
";

%feature("docstring")  QSpecScan::footprintFactor "virtual const IFootprintFactor* QSpecScan::footprintFactor() const override

Returns  IFootprintFactor object pointer. 
";

%feature("docstring")  QSpecScan::footprint "std::vector< double > QSpecScan::footprint(size_t i, size_t n_elements) const override

Returns footprint correction factor for a range of simulation elements of size  n_elements and starting from element with index  i. 
";

%feature("docstring")  QSpecScan::numberOfSimulationElements "size_t QSpecScan::numberOfSimulationElements() const override

Returns the number of simulation elements. 
";

%feature("docstring")  QSpecScan::createIntensities "std::vector< double > QSpecScan::createIntensities(const std::vector< SpecularSimulationElement > &sim_elements) const override

Returns intensity vector corresponding to convolution of given simulation elements. 
";

%feature("docstring")  QSpecScan::print "std::string QSpecScan::print() const override

Print scan definition in python format. 
";

%feature("docstring")  QSpecScan::setQResolution "void QSpecScan::setQResolution(const ScanResolution &resolution)

Sets q resolution values via  ScanResolution object. 
";

%feature("docstring")  QSpecScan::setRelativeQResolution "void QSpecScan::setRelativeQResolution(const RangedDistribution &distr, double rel_dev)
";

%feature("docstring")  QSpecScan::setRelativeQResolution "void QSpecScan::setRelativeQResolution(const RangedDistribution &distr, const std::vector< double > &rel_dev)

Sets qz resolution values via RangedDistribution and values of relative deviations (that is,  rel_dev equals standard deviation divided by the mean value).  rel_dev can be either single-valued or a numpy array. In the latter case the length of the array should coinside with the length of the qz-axis. 
";

%feature("docstring")  QSpecScan::setAbsoluteQResolution "void QSpecScan::setAbsoluteQResolution(const RangedDistribution &distr, double std_dev)
";

%feature("docstring")  QSpecScan::setAbsoluteQResolution "void QSpecScan::setAbsoluteQResolution(const RangedDistribution &distr, const std::vector< double > &std_dev)

Sets qz resolution values via RangedDistribution and values of standard deviations.  std_dev can be either single-valued or a numpy array. In the latter case the length of the array should coinside with the length of the qz-axis. 
";


// File: classRadialParaCrystalBuilder.xml
%feature("docstring") RadialParaCrystalBuilder "

Builds sample: cylinders with 1DDL structure factor (IsGISAXS example #4).

C++ includes: ParaCrystalBuilder.h
";

%feature("docstring")  RadialParaCrystalBuilder::buildSample "MultiLayer * RadialParaCrystalBuilder::buildSample() const
";


// File: classRectangularConverter.xml
%feature("docstring") RectangularConverter "

IUnitConverter class that handles the unit translations for rectangular detectors Its default units are mm for both axes

C++ includes: SimpleUnitConverters.h
";

%feature("docstring")  RectangularConverter::RectangularConverter "RectangularConverter::RectangularConverter(const RectangularDetector &detector, const Beam &beam)
";

%feature("docstring")  RectangularConverter::~RectangularConverter "RectangularConverter::~RectangularConverter() final
";

%feature("docstring")  RectangularConverter::clone "RectangularConverter * RectangularConverter::clone() const final
";

%feature("docstring")  RectangularConverter::availableUnits "std::vector< Axes::Units > RectangularConverter::availableUnits() const final

Returns the list of all available units. 
";

%feature("docstring")  RectangularConverter::defaultUnits "Axes::Units RectangularConverter::defaultUnits() const final
";


// File: classRectangularDetector.xml
%feature("docstring") RectangularDetector "

A flat rectangular detector with axes and resolution function.

C++ includes: RectangularDetector.h
";

%feature("docstring")  RectangularDetector::RectangularDetector "RectangularDetector::RectangularDetector(size_t nxbins, double width, size_t nybins, double height)

Rectangular detector constructor

Parameters:
-----------

nxbins: 
Number of bins (pixels) in x-direction

width: 
Width of the detector in mm along x-direction

nybins: 
Number of bins (pixels) in y-direction

height: 
Height of the detector in mm along y-direction 
";

%feature("docstring")  RectangularDetector::RectangularDetector "RectangularDetector::RectangularDetector(const RectangularDetector &other)
";

%feature("docstring")  RectangularDetector::clone "RectangularDetector * RectangularDetector::clone() const override
";

%feature("docstring")  RectangularDetector::accept "void RectangularDetector::accept(INodeVisitor *visitor) const final
";

%feature("docstring")  RectangularDetector::~RectangularDetector "RectangularDetector::~RectangularDetector()
";

%feature("docstring")  RectangularDetector::init "void RectangularDetector::init(const Beam &beam) override

Inits detector with the beam settings. 
";

%feature("docstring")  RectangularDetector::setPosition "void RectangularDetector::setPosition(const kvector_t normal_to_detector, double u0, double v0, const kvector_t direction=kvector_t(0.0, -1.0, 0.0))
";

%feature("docstring")  RectangularDetector::setPerpendicularToSampleX "void RectangularDetector::setPerpendicularToSampleX(double distance, double u0, double v0)
";

%feature("docstring")  RectangularDetector::setPerpendicularToDirectBeam "void RectangularDetector::setPerpendicularToDirectBeam(double distance, double u0, double v0)
";

%feature("docstring")  RectangularDetector::setPerpendicularToReflectedBeam "void RectangularDetector::setPerpendicularToReflectedBeam(double distance, double u0=0.0, double v0=0.0)
";

%feature("docstring")  RectangularDetector::setDirectBeamPosition "void RectangularDetector::setDirectBeamPosition(double u0, double v0)
";

%feature("docstring")  RectangularDetector::getWidth "double RectangularDetector::getWidth() const
";

%feature("docstring")  RectangularDetector::getHeight "double RectangularDetector::getHeight() const
";

%feature("docstring")  RectangularDetector::getNbinsX "size_t RectangularDetector::getNbinsX() const
";

%feature("docstring")  RectangularDetector::getNbinsY "size_t RectangularDetector::getNbinsY() const
";

%feature("docstring")  RectangularDetector::getNormalVector "kvector_t RectangularDetector::getNormalVector() const
";

%feature("docstring")  RectangularDetector::getU0 "double RectangularDetector::getU0() const
";

%feature("docstring")  RectangularDetector::getV0 "double RectangularDetector::getV0() const
";

%feature("docstring")  RectangularDetector::getDirectionVector "kvector_t RectangularDetector::getDirectionVector() const
";

%feature("docstring")  RectangularDetector::getDistance "double RectangularDetector::getDistance() const
";

%feature("docstring")  RectangularDetector::getDirectBeamU0 "double RectangularDetector::getDirectBeamU0() const
";

%feature("docstring")  RectangularDetector::getDirectBeamV0 "double RectangularDetector::getDirectBeamV0() const
";

%feature("docstring")  RectangularDetector::getDetectorArrangment "RectangularDetector::EDetectorArrangement RectangularDetector::getDetectorArrangment() const
";

%feature("docstring")  RectangularDetector::defaultAxesUnits "Axes::Units RectangularDetector::defaultAxesUnits() const override

return default axes units 
";

%feature("docstring")  RectangularDetector::regionOfInterestPixel "RectangularPixel * RectangularDetector::regionOfInterestPixel() const
";


// File: classRectangularPixel.xml
%feature("docstring") RectangularPixel "

A pixel in a  RectangularDetector.

C++ includes: RectangularPixel.h
";

%feature("docstring")  RectangularPixel::RectangularPixel "RectangularPixel::RectangularPixel(kvector_t corner_pos, kvector_t width, kvector_t height)
";

%feature("docstring")  RectangularPixel::clone "RectangularPixel * RectangularPixel::clone() const override
";

%feature("docstring")  RectangularPixel::createZeroSizePixel "RectangularPixel * RectangularPixel::createZeroSizePixel(double x, double y) const override
";

%feature("docstring")  RectangularPixel::getK "kvector_t RectangularPixel::getK(double x, double y, double wavelength) const override
";

%feature("docstring")  RectangularPixel::getPosition "kvector_t RectangularPixel::getPosition(double x, double y) const
";

%feature("docstring")  RectangularPixel::getIntegrationFactor "double RectangularPixel::getIntegrationFactor(double x, double y) const override
";

%feature("docstring")  RectangularPixel::getSolidAngle "double RectangularPixel::getSolidAngle() const override
";


// File: classRectParaCrystalBuilder.xml
%feature("docstring") RectParaCrystalBuilder "

Builds sample: 2D paracrystal lattice (IsGISAXS example #8).

C++ includes: ParaCrystalBuilder.h
";

%feature("docstring")  RectParaCrystalBuilder::buildSample "MultiLayer * RectParaCrystalBuilder::buildSample() const
";


// File: classRegionOfInterest.xml
%feature("docstring") RegionOfInterest "

Defines rectangular area for the detector which will be simulated/fitted.

C++ includes: RegionOfInterest.h
";

%feature("docstring")  RegionOfInterest::RegionOfInterest "RegionOfInterest::RegionOfInterest(const IDetector2D &detector, double xlow, double ylow, double xup, double yup)
";

%feature("docstring")  RegionOfInterest::RegionOfInterest "RegionOfInterest::RegionOfInterest(const OutputData< double > &data, double xlow, double ylow, double xup, double yup)
";

%feature("docstring")  RegionOfInterest::clone "RegionOfInterest * RegionOfInterest::clone() const
";

%feature("docstring")  RegionOfInterest::~RegionOfInterest "RegionOfInterest::~RegionOfInterest()
";

%feature("docstring")  RegionOfInterest::getXlow "double RegionOfInterest::getXlow() const
";

%feature("docstring")  RegionOfInterest::getYlow "double RegionOfInterest::getYlow() const
";

%feature("docstring")  RegionOfInterest::getXup "double RegionOfInterest::getXup() const
";

%feature("docstring")  RegionOfInterest::getYup "double RegionOfInterest::getYup() const
";

%feature("docstring")  RegionOfInterest::detectorIndex "size_t RegionOfInterest::detectorIndex(size_t roiIndex) const

Converts roi index to the detector index. 
";

%feature("docstring")  RegionOfInterest::roiIndex "size_t RegionOfInterest::roiIndex(size_t detectorIndex) const

Converts global detector index to ROI index. 
";

%feature("docstring")  RegionOfInterest::roiSize "size_t RegionOfInterest::roiSize() const

Number of detector bins in ROI area. 
";

%feature("docstring")  RegionOfInterest::detectorSize "size_t RegionOfInterest::detectorSize() const

Number of detector bins. 
";

%feature("docstring")  RegionOfInterest::isInROI "bool RegionOfInterest::isInROI(size_t detectorIndex) const
";

%feature("docstring")  RegionOfInterest::clipAxisToRoi "std::unique_ptr< IAxis > RegionOfInterest::clipAxisToRoi(size_t axis_index, const IAxis &axis) const
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


// File: classResolutionFunction2DGaussian.xml
%feature("docstring") ResolutionFunction2DGaussian "

Simple gaussian two-dimensional resolution function.

C++ includes: ResolutionFunction2DGaussian.h
";

%feature("docstring")  ResolutionFunction2DGaussian::ResolutionFunction2DGaussian "ResolutionFunction2DGaussian::ResolutionFunction2DGaussian(double sigma_x, double sigma_y)
";

%feature("docstring")  ResolutionFunction2DGaussian::evaluateCDF "double ResolutionFunction2DGaussian::evaluateCDF(double x, double y) const
";

%feature("docstring")  ResolutionFunction2DGaussian::clone "ResolutionFunction2DGaussian* ResolutionFunction2DGaussian::clone() const
";

%feature("docstring")  ResolutionFunction2DGaussian::accept "void ResolutionFunction2DGaussian::accept(INodeVisitor *visitor) const final
";

%feature("docstring")  ResolutionFunction2DGaussian::getSigmaX "double ResolutionFunction2DGaussian::getSigmaX() const
";

%feature("docstring")  ResolutionFunction2DGaussian::getSigmaY "double ResolutionFunction2DGaussian::getSigmaY() const
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


// File: classScanResolution.xml
%feature("docstring") ScanResolution "

Container for reflectivity resolution data.

C++ includes: ScanResolution.h
";

%feature("docstring")  ScanResolution::~ScanResolution "ScanResolution::~ScanResolution() override
";

%feature("docstring")  ScanResolution::clone "ScanResolution* ScanResolution::clone() const override=0
";

%feature("docstring")  ScanResolution::distribution "const RangedDistribution* ScanResolution::distribution() const
";

%feature("docstring")  ScanResolution::nSamples "size_t ScanResolution::nSamples() const
";

%feature("docstring")  ScanResolution::generateSamples "virtual DistrOutput ScanResolution::generateSamples(double mean, size_t n_times) const =0
";

%feature("docstring")  ScanResolution::generateSamples "virtual DistrOutput ScanResolution::generateSamples(const std::vector< double > &mean) const =0
";

%feature("docstring")  ScanResolution::stdDevs "virtual std::vector<double> ScanResolution::stdDevs(double mean, size_t n_times) const =0
";

%feature("docstring")  ScanResolution::stdDevs "virtual std::vector<double> ScanResolution::stdDevs(const std::vector< double > &mean) const =0
";

%feature("docstring")  ScanResolution::empty "bool ScanResolution::empty() const
";

%feature("docstring")  ScanResolution::print "std::string ScanResolution::print() const

Prints object definition in python format. 
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

Returns the data uncertainties cut to the ROI area If no uncertainties present, returns zero-filled  SimulationResult. 
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

Convert user data to  SimulationResult object for later drawing in various axes units. User data will be cropped to the ROI defined in the simulation, amplitudes in areas corresponding to the masked areas of the detector will be set to zero. 
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


// File: classSimulationArea.xml
%feature("docstring") SimulationArea "

Holds iteration logic over active detector channels in the presence of masked areas and  RegionOfInterest defined.

C++ includes: SimulationArea.h
";

%feature("docstring")  SimulationArea::SimulationArea "SimulationArea::SimulationArea(const IDetector *detector)
";

%feature("docstring")  SimulationArea::~SimulationArea "virtual SimulationArea::~SimulationArea()
";

%feature("docstring")  SimulationArea::begin "SimulationAreaIterator SimulationArea::begin()
";

%feature("docstring")  SimulationArea::end "SimulationAreaIterator SimulationArea::end()
";

%feature("docstring")  SimulationArea::isMasked "bool SimulationArea::isMasked(size_t index) const

returns true if given iterator index correspond to masked detector channel 
";

%feature("docstring")  SimulationArea::totalSize "size_t SimulationArea::totalSize() const
";

%feature("docstring")  SimulationArea::roiIndex "size_t SimulationArea::roiIndex(size_t index) const

Return index in ROI map from iterator index. 
";

%feature("docstring")  SimulationArea::detectorIndex "size_t SimulationArea::detectorIndex(size_t index) const

Return detector index from iterator index. 
";


// File: classSimulationAreaIterator.xml
%feature("docstring") SimulationAreaIterator "

An iterator for  SimulationArea.

C++ includes: SimulationAreaIterator.h
";

%feature("docstring")  SimulationAreaIterator::SimulationAreaIterator "SimulationAreaIterator::SimulationAreaIterator(const SimulationArea *area, size_t start_at_index)
";

%feature("docstring")  SimulationAreaIterator::index "size_t SimulationAreaIterator::index() const
";

%feature("docstring")  SimulationAreaIterator::elementIndex "size_t SimulationAreaIterator::elementIndex() const
";

%feature("docstring")  SimulationAreaIterator::roiIndex "size_t SimulationAreaIterator::roiIndex() const
";

%feature("docstring")  SimulationAreaIterator::detectorIndex "size_t SimulationAreaIterator::detectorIndex() const
";


// File: classSimulationFactory.xml
%feature("docstring") SimulationFactory "

Registry to create standard pre-defined simulations. Used in functional tests, performance measurements, etc.

C++ includes: SimulationFactory.h
";

%feature("docstring")  SimulationFactory::SimulationFactory "SimulationFactory::SimulationFactory()
";


// File: classSimulationResult.xml
%feature("docstring") SimulationResult "

Wrapper around  OutputData<double> that also provides unit conversions.

C++ includes: SimulationResult.h
";

%feature("docstring")  SimulationResult::SimulationResult "SimulationResult::SimulationResult()=default
";

%feature("docstring")  SimulationResult::SimulationResult "SimulationResult::SimulationResult(const OutputData< double > &data, const IUnitConverter &unit_converter)
";

%feature("docstring")  SimulationResult::SimulationResult "SimulationResult::SimulationResult(const SimulationResult &other)
";

%feature("docstring")  SimulationResult::SimulationResult "SimulationResult::SimulationResult(SimulationResult &&other)
";

%feature("docstring")  SimulationResult::data "std::unique_ptr< OutputData< double > > SimulationResult::data(Axes::Units units=Axes::Units::DEFAULT) const
";

%feature("docstring")  SimulationResult::histogram2d "Histogram2D * SimulationResult::histogram2d(Axes::Units units=Axes::Units::DEFAULT) const
";

%feature("docstring")  SimulationResult::axisInfo "std::vector< AxisInfo > SimulationResult::axisInfo(Axes::Units units=Axes::Units::DEFAULT) const

Provide  AxisInfo for each axis and the given units. 
";

%feature("docstring")  SimulationResult::converter "const IUnitConverter & SimulationResult::converter() const

Returns underlying unit converter. 
";

%feature("docstring")  SimulationResult::size "size_t SimulationResult::size() const
";

%feature("docstring")  SimulationResult::empty "bool SimulationResult::empty() const
";

%feature("docstring")  SimulationResult::array "PyObject * SimulationResult::array(Axes::Units units=Axes::Units::DEFAULT) const

returns intensity data as Python numpy array 
";

%feature("docstring")  SimulationResult::axis "std::vector< double > SimulationResult::axis(Axes::Units units=Axes::Units::DEFAULT) const
";

%feature("docstring")  SimulationResult::axis "std::vector< double > SimulationResult::axis(size_t i_axis, Axes::Units units=Axes::Units::DEFAULT) const

Returns axis coordinates as a numpy array. With no parameters given returns coordinates of x-axis in default units. 
";


// File: classSimulationRoiArea.xml
%feature("docstring") SimulationRoiArea "

Holds iteration logic over active detector channels in the presence of ROI. On the contrary to  SimulationArea class, iterates also over masked areas.

C++ includes: SimulationArea.h
";

%feature("docstring")  SimulationRoiArea::SimulationRoiArea "SimulationRoiArea::SimulationRoiArea(const IDetector *detector)
";

%feature("docstring")  SimulationRoiArea::isMasked "bool SimulationRoiArea::isMasked(size_t) const

returns true if given iterator index correspond to masked detector channel 
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


// File: classSpecularDetector1D.xml
%feature("docstring") SpecularDetector1D "

1D detector for specular simulations. Use of this detector is deprecated.

C++ includes: SpecularDetector1D.h
";

%feature("docstring")  SpecularDetector1D::SpecularDetector1D "SpecularDetector1D::SpecularDetector1D(const IAxis &axis)
";

%feature("docstring")  SpecularDetector1D::~SpecularDetector1D "SpecularDetector1D::~SpecularDetector1D()
";

%feature("docstring")  SpecularDetector1D::clone "SpecularDetector1D * SpecularDetector1D::clone() const override
";

%feature("docstring")  SpecularDetector1D::accept "void SpecularDetector1D::accept(INodeVisitor *visitor) const override
";

%feature("docstring")  SpecularDetector1D::detectorMask "const DetectorMask* SpecularDetector1D::detectorMask() const override

Returns detector masks container. 
";

%feature("docstring")  SpecularDetector1D::regionOfInterest "const RegionOfInterest* SpecularDetector1D::regionOfInterest() const override

Returns region of interest if exists. 
";

%feature("docstring")  SpecularDetector1D::resetRegionOfInterest "void SpecularDetector1D::resetRegionOfInterest() override

Resets region of interest making whole detector plane available for the simulation. 
";

%feature("docstring")  SpecularDetector1D::defaultAxesUnits "Axes::Units SpecularDetector1D::defaultAxesUnits() const override

Return default axes units. 
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


// File: classSphericalConverter.xml
%feature("docstring") SphericalConverter "

IUnitConverter class that handles the unit translations for spherical detectors Its default units are radians for both axes

C++ includes: SimpleUnitConverters.h
";

%feature("docstring")  SphericalConverter::SphericalConverter "SphericalConverter::SphericalConverter(const SphericalDetector &detector, const Beam &beam)
";

%feature("docstring")  SphericalConverter::~SphericalConverter "SphericalConverter::~SphericalConverter() final
";

%feature("docstring")  SphericalConverter::clone "SphericalConverter * SphericalConverter::clone() const final
";

%feature("docstring")  SphericalConverter::availableUnits "std::vector< Axes::Units > SphericalConverter::availableUnits() const final

Returns the list of all available units. 
";

%feature("docstring")  SphericalConverter::defaultUnits "Axes::Units SphericalConverter::defaultUnits() const final
";


// File: classSphericalDetector.xml
%feature("docstring") SphericalDetector "

A spherical detector with axes and resolution function.

C++ includes: SphericalDetector.h
";

%feature("docstring")  SphericalDetector::SphericalDetector "SphericalDetector::SphericalDetector()
";

%feature("docstring")  SphericalDetector::SphericalDetector "SphericalDetector::SphericalDetector(size_t n_phi, double phi_min, double phi_max, size_t n_alpha, double alpha_min, double alpha_max)

Spherical detector constructor using angle ranges

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

%feature("docstring")  SphericalDetector::SphericalDetector "SphericalDetector::SphericalDetector(const SphericalDetector &other)
";

%feature("docstring")  SphericalDetector::clone "SphericalDetector * SphericalDetector::clone() const override
";

%feature("docstring")  SphericalDetector::accept "void SphericalDetector::accept(INodeVisitor *visitor) const override
";

%feature("docstring")  SphericalDetector::~SphericalDetector "SphericalDetector::~SphericalDetector() override
";

%feature("docstring")  SphericalDetector::defaultAxesUnits "Axes::Units SphericalDetector::defaultAxesUnits() const override

return default axes units 
";


// File: classSphericalPixel.xml
%feature("docstring") SphericalPixel "

A pixel in a  SphericalDetector.

C++ includes: SphericalPixel.h
";

%feature("docstring")  SphericalPixel::SphericalPixel "SphericalPixel::SphericalPixel(const Bin1D &alpha_bin, const Bin1D &phi_bin)
";

%feature("docstring")  SphericalPixel::clone "SphericalPixel * SphericalPixel::clone() const override
";

%feature("docstring")  SphericalPixel::createZeroSizePixel "SphericalPixel * SphericalPixel::createZeroSizePixel(double x, double y) const override
";

%feature("docstring")  SphericalPixel::getK "kvector_t SphericalPixel::getK(double x, double y, double wavelength) const override
";

%feature("docstring")  SphericalPixel::getIntegrationFactor "double SphericalPixel::getIntegrationFactor(double x, double y) const override
";

%feature("docstring")  SphericalPixel::getSolidAngle "double SphericalPixel::getSolidAngle() const override
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


// File: classUnitConverter1D.xml
%feature("docstring") UnitConverter1D "

Conversion of axis units for the case of 1D simulation result.

C++ includes: UnitConverter1D.h
";

%feature("docstring")  UnitConverter1D::~UnitConverter1D "UnitConverter1D::~UnitConverter1D() override=default
";

%feature("docstring")  UnitConverter1D::clone "UnitConverter1D* UnitConverter1D::clone() const override=0
";

%feature("docstring")  UnitConverter1D::dimension "size_t UnitConverter1D::dimension() const override

Returns dimensionality of converted canvas. 
";

%feature("docstring")  UnitConverter1D::calculateMin "double UnitConverter1D::calculateMin(size_t i_axis, Axes::Units units_type) const override

Calculates minimum on-axis value in given units. 
";

%feature("docstring")  UnitConverter1D::calculateMax "double UnitConverter1D::calculateMax(size_t i_axis, Axes::Units units_type) const override

Calculates maximum on-axis value in given units. 
";

%feature("docstring")  UnitConverter1D::createConvertedAxis "std::unique_ptr< IAxis > UnitConverter1D::createConvertedAxis(size_t i_axis, Axes::Units units) const override

Creates axis in converted units. 
";

%feature("docstring")  UnitConverter1D::createConvertedData "std::unique_ptr< OutputData< double > > UnitConverter1D::createConvertedData(const OutputData< double > &data, Axes::Units units) const override

Creates  OutputData array in converter units. 
";


// File: classUnitConverterConvSpec.xml
%feature("docstring") UnitConverterConvSpec "

Conversion of axis units for the case of conventional (angle-based) reflectometry.

C++ includes: UnitConverter1D.h
";

%feature("docstring")  UnitConverterConvSpec::UnitConverterConvSpec "UnitConverterConvSpec::UnitConverterConvSpec(const Beam &beam, const IAxis &axis, Axes::Units axis_units=Axes::Units::RADIANS)

Constructs the object for unit conversion. 
";

%feature("docstring")  UnitConverterConvSpec::UnitConverterConvSpec "UnitConverterConvSpec::UnitConverterConvSpec(const AngularSpecScan &handler)
";

%feature("docstring")  UnitConverterConvSpec::~UnitConverterConvSpec "UnitConverterConvSpec::~UnitConverterConvSpec() override
";

%feature("docstring")  UnitConverterConvSpec::clone "UnitConverterConvSpec * UnitConverterConvSpec::clone() const override
";

%feature("docstring")  UnitConverterConvSpec::axisSize "size_t UnitConverterConvSpec::axisSize(size_t i_axis) const override

Returns the size of underlying axis. 
";

%feature("docstring")  UnitConverterConvSpec::availableUnits "std::vector< Axes::Units > UnitConverterConvSpec::availableUnits() const override

Returns the list of all available units. 
";

%feature("docstring")  UnitConverterConvSpec::defaultUnits "Axes::Units UnitConverterConvSpec::defaultUnits() const override

Returns default units to convert to. 
";


// File: classUnitConverterQSpec.xml
%feature("docstring") UnitConverterQSpec "

Conversion of axis units for the case of q-defined reflectometry.

C++ includes: UnitConverter1D.h
";

%feature("docstring")  UnitConverterQSpec::UnitConverterQSpec "UnitConverterQSpec::UnitConverterQSpec(const QSpecScan &handler)
";

%feature("docstring")  UnitConverterQSpec::~UnitConverterQSpec "UnitConverterQSpec::~UnitConverterQSpec() override
";

%feature("docstring")  UnitConverterQSpec::clone "UnitConverterQSpec * UnitConverterQSpec::clone() const override
";

%feature("docstring")  UnitConverterQSpec::axisSize "size_t UnitConverterQSpec::axisSize(size_t i_axis) const override

Returns the size of underlying axis. 
";

%feature("docstring")  UnitConverterQSpec::availableUnits "std::vector< Axes::Units > UnitConverterQSpec::availableUnits() const override

Returns the list of all available units. 
";

%feature("docstring")  UnitConverterQSpec::defaultUnits "Axes::Units UnitConverterQSpec::defaultUnits() const override

Returns default units to convert to. 
";


// File: classUnitConverterSimple.xml
%feature("docstring") UnitConverterSimple "

Interface for objects that provide axis translations to different units for  IDetector objects

C++ includes: SimpleUnitConverters.h
";

%feature("docstring")  UnitConverterSimple::UnitConverterSimple "UnitConverterSimple::UnitConverterSimple(const Beam &beam)
";

%feature("docstring")  UnitConverterSimple::~UnitConverterSimple "UnitConverterSimple::~UnitConverterSimple() override=default
";

%feature("docstring")  UnitConverterSimple::dimension "size_t UnitConverterSimple::dimension() const final
";

%feature("docstring")  UnitConverterSimple::calculateMin "double UnitConverterSimple::calculateMin(size_t i_axis, Axes::Units units_type) const final
";

%feature("docstring")  UnitConverterSimple::calculateMax "double UnitConverterSimple::calculateMax(size_t i_axis, Axes::Units units_type) const final
";

%feature("docstring")  UnitConverterSimple::axisSize "size_t UnitConverterSimple::axisSize(size_t i_axis) const final
";

%feature("docstring")  UnitConverterSimple::availableUnits "std::vector< Axes::Units > UnitConverterSimple::availableUnits() const override

Returns the list of all available units. 
";

%feature("docstring")  UnitConverterSimple::createConvertedAxis "std::unique_ptr< IAxis > UnitConverterSimple::createConvertedAxis(size_t i_axis, Axes::Units units) const final
";


// File: classVarianceConstantFunction.xml
%feature("docstring") VarianceConstantFunction "

Returns 1.0 as variance value

C++ includes: VarianceFunctions.h
";

%feature("docstring")  VarianceConstantFunction::clone "VarianceConstantFunction * VarianceConstantFunction::clone() const override
";

%feature("docstring")  VarianceConstantFunction::variance "double VarianceConstantFunction::variance(double, double) const override
";


// File: classVarianceSimFunction.xml
%feature("docstring") VarianceSimFunction "

Returns max(sim, epsilon)

C++ includes: VarianceFunctions.h
";

%feature("docstring")  VarianceSimFunction::VarianceSimFunction "VarianceSimFunction::VarianceSimFunction(double epsilon=1.0)
";

%feature("docstring")  VarianceSimFunction::clone "VarianceSimFunction * VarianceSimFunction::clone() const override
";

%feature("docstring")  VarianceSimFunction::variance "double VarianceSimFunction::variance(double exp, double sim) const override
";


// File: classConvolve_1_1Workspace.xml


// File: classFourierTransform_1_1Workspace.xml


// File: namespace_0D100.xml


// File: namespace_0D105.xml


// File: namespace_0D114.xml


// File: namespace_0D116.xml


// File: namespace_0D120.xml


// File: namespace_0D133.xml


// File: namespace_0D135.xml


// File: namespace_0D139.xml


// File: namespace_0D145.xml


// File: namespace_0D180.xml


// File: namespace_0D187.xml


// File: namespace_0D193.xml


// File: namespace_0D197.xml


// File: namespace_0D199.xml


// File: namespace_0D207.xml


// File: namespace_0D213.xml


// File: namespace_0D215.xml


// File: namespace_0D219.xml


// File: namespace_0D231.xml


// File: namespace_0D237.xml


// File: namespace_0D241.xml


// File: namespace_0D259.xml


// File: namespace_0D278.xml


// File: namespace_0D292.xml


// File: namespace_0D37.xml


// File: namespace_0D39.xml


// File: namespace_0D41.xml


// File: namespace_0D45.xml


// File: namespace_0D80.xml


// File: namespace_0D92.xml


// File: namespaceArrayUtils.xml
%feature("docstring")  ArrayUtils::getShape "std::pair< size_t, size_t > ArrayUtils::getShape(const T &data)

Returns shape nrows, ncols of 2D array. 
";

%feature("docstring")  ArrayUtils::createData "CreateDataImpl::ReturnType<T> ArrayUtils::createData(const T &vec)

Creates  OutputData array from input vector. 
";

%feature("docstring")  ArrayUtils::createNumpyArray "PyObject * ArrayUtils::createNumpyArray(const std::vector< double > &data)
";

%feature("docstring")  ArrayUtils::createVector1D "decltype(auto) ArrayUtils::createVector1D(const T &data)

Creates 1D vector from  OutputData. 
";

%feature("docstring")  ArrayUtils::createVector2D "decltype(auto) ArrayUtils::createVector2D(const T &data)

Creates 2D vector from  OutputData. 
";


// File: namespaceAxisNames.xml
%feature("docstring")  AxisNames::InitSphericalAxis0 "std::map< Axes::Units, std::string > AxisNames::InitSphericalAxis0()
";

%feature("docstring")  AxisNames::InitSphericalAxis1 "std::map< Axes::Units, std::string > AxisNames::InitSphericalAxis1()
";

%feature("docstring")  AxisNames::InitRectangularAxis0 "std::map< Axes::Units, std::string > AxisNames::InitRectangularAxis0()
";

%feature("docstring")  AxisNames::InitRectangularAxis1 "std::map< Axes::Units, std::string > AxisNames::InitRectangularAxis1()
";

%feature("docstring")  AxisNames::InitOffSpecAxis0 "std::map< Axes::Units, std::string > AxisNames::InitOffSpecAxis0()
";

%feature("docstring")  AxisNames::InitOffSpecAxis1 "std::map< Axes::Units, std::string > AxisNames::InitOffSpecAxis1()
";

%feature("docstring")  AxisNames::InitSpecAxis "std::map< Axes::Units, std::string > AxisNames::InitSpecAxis()
";

%feature("docstring")  AxisNames::InitSpecAxisQ "std::map< Axes::Units, std::string > AxisNames::InitSpecAxisQ()
";

%feature("docstring")  AxisNames::InitSampleDepthAxis "std::map< Axes::Units, std::string > AxisNames::InitSampleDepthAxis()
";


// File: namespaceDataFormatUtils.xml
%feature("docstring")  DataFormatUtils::isCompressed "bool DataFormatUtils::isCompressed(const std::string &name)

Returns true if name contains *.gz extension. 
";

%feature("docstring")  DataFormatUtils::isGZipped "bool DataFormatUtils::isGZipped(const std::string &name)

Returns true if name contains *.gz extension.

Does name contain *.gz extension? 
";

%feature("docstring")  DataFormatUtils::isBZipped "bool DataFormatUtils::isBZipped(const std::string &name)

Returns true if name contains *.bz2 extension. 
";

%feature("docstring")  DataFormatUtils::GetFileMainExtension "std::string DataFormatUtils::GetFileMainExtension(const std::string &name)

Returns file extension after stripping '.gz' if any.

Returns file main extension (without .gz). 
";

%feature("docstring")  DataFormatUtils::isIntFile "bool DataFormatUtils::isIntFile(const std::string &file_name)

returns true if file name corresponds to BornAgain native format (compressed or not) 
";

%feature("docstring")  DataFormatUtils::isTiffFile "bool DataFormatUtils::isTiffFile(const std::string &file_name)

returns true if file name corresponds to tiff file (can be also compressed) 
";

%feature("docstring")  DataFormatUtils::createAxis "std::unique_ptr< IAxis > DataFormatUtils::createAxis(std::istream &input_stream)

Creates axis of certain type from input stream. 
";

%feature("docstring")  DataFormatUtils::fillOutputData "void DataFormatUtils::fillOutputData(OutputData< double > *data, std::istream &input_stream)

Fills output data raw buffer from input stream. 
";

%feature("docstring")  DataFormatUtils::parse_doubles "std::vector< double > DataFormatUtils::parse_doubles(const std::string &str)

Parse double values from string to vector of double. 
";

%feature("docstring")  DataFormatUtils::readLineOfDoubles "void DataFormatUtils::readLineOfDoubles(std::vector< double > &buffer, std::istringstream &iss)
";


// File: namespaceDetectorFunctions.xml
%feature("docstring")  DetectorFunctions::hasSameDimensions "bool DetectorFunctions::hasSameDimensions(const IDetector &detector, const OutputData< double > &data)

Returns true if the data has same axes size (nx,ny) with the detector. 
";

%feature("docstring")  DetectorFunctions::axesToString "std::string DetectorFunctions::axesToString(const IDetector &detector)

Returns string representation of axes dimension in the form \"(nx,ny)\". 
";

%feature("docstring")  DetectorFunctions::axesToString "std::string DetectorFunctions::axesToString(const OutputData< double > &data)

Returns string representation of axes dimension in the form \"(nx,ny)\". 
";


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


// File: namespaceIntensityDataFunctions.xml
%feature("docstring")  IntensityDataFunctions::RelativeDifference "double IntensityDataFunctions::RelativeDifference(const SimulationResult &dat, const SimulationResult &ref)

Returns sum of relative differences between each pair of elements: (a, b) -> 2*abs(a - b)/(a + b) ( and zero if a-b=0 )

Returns sum of relative differences between each pair of elements: (a, b) -> 2*abs(a - b)/(|a| + |b|) ( and zero if a=b=0 within epsilon ) 
";

%feature("docstring")  IntensityDataFunctions::getRelativeDifference "double IntensityDataFunctions::getRelativeDifference(const OutputData< double > &dat, const OutputData< double > &ref)

Returns relative difference between two data sets sum(dat[i] - ref[i])/ref[i]). 
";

%feature("docstring")  IntensityDataFunctions::checkRelativeDifference "bool IntensityDataFunctions::checkRelativeDifference(const OutputData< double > &dat, const OutputData< double > &ref, const double threshold)

Returns true is relative difference is below threshold; prints informative output. 
";

%feature("docstring")  IntensityDataFunctions::getRelativeDifference "double IntensityDataFunctions::getRelativeDifference(const IHistogram &dat, const IHistogram &ref)
";

%feature("docstring")  IntensityDataFunctions::coordinateToBinf "double IntensityDataFunctions::coordinateToBinf(double coordinate, const IAxis &axis)

Transforms coordinate on axis into the bin-fraction-coordinate. 
";

%feature("docstring")  IntensityDataFunctions::coordinateFromBinf "double IntensityDataFunctions::coordinateFromBinf(double value, const IAxis &axis)

Transforms bin-fraction-coordinate into axis coordinate. 
";

%feature("docstring")  IntensityDataFunctions::coordinateToBinf "void IntensityDataFunctions::coordinateToBinf(double &x, double &y, const OutputData< double > &data)

Transforms x,y coordinate from  OutputData axes coordinates to bin-fraction-coordinates. 
";

%feature("docstring")  IntensityDataFunctions::coordinateFromBinf "void IntensityDataFunctions::coordinateFromBinf(double &x, double &y, const OutputData< double > &data)

Transforms x,y coordinate from bin-fraction-coordinates to  OutputData's axes coordinates. 
";

%feature("docstring")  IntensityDataFunctions::create2DArrayfromOutputData "std::vector< std::vector< double > > IntensityDataFunctions::create2DArrayfromOutputData(const OutputData< double > &data)

Creates a vector of vectors of double (2D Array) from  OutputData. 
";

%feature("docstring")  IntensityDataFunctions::FT2DArray "std::vector< std::vector< double > > IntensityDataFunctions::FT2DArray(const std::vector< std::vector< double >> &signal)

Creates a Fourier Transform of a 2D Array (vector of vectors). 
";

%feature("docstring")  IntensityDataFunctions::createRelativeDifferenceData "std::unique_ptr< OutputData< double > > IntensityDataFunctions::createRelativeDifferenceData(const OutputData< double > &data, const OutputData< double > &reference)
";

%feature("docstring")  IntensityDataFunctions::createRearrangedDataSet "std::unique_ptr< OutputData< double > > IntensityDataFunctions::createRearrangedDataSet(const OutputData< double > &data, int n)

Returns new object with input data rotated by n*90 deg counterclockwise (n > 0) or clockwise (n < 0)  Axes are swapped if the data is effectively rotated by 90 or 270 degrees Applicable to 2D arrays only 
";

%feature("docstring")  IntensityDataFunctions::createClippedDataSet "std::unique_ptr< OutputData< double > > IntensityDataFunctions::createClippedDataSet(const OutputData< double > &origin, double x1, double y1, double x2, double y2)

Returns new IntensityData objects which axes clipped to represent the specified rectangle. 
";

%feature("docstring")  IntensityDataFunctions::createOutputDatafrom2DArray "std::unique_ptr< OutputData< double > > IntensityDataFunctions::createOutputDatafrom2DArray(const std::vector< std::vector< double >> &array_2d)

Creates  OutputData from a 2D Array. 
";

%feature("docstring")  IntensityDataFunctions::createFFT "std::unique_ptr< OutputData< double > > IntensityDataFunctions::createFFT(const OutputData< double > &data)

Creates Fourier Transform ( OutputData format) of intensity map ( OutputData format). 
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


// File: namespacePyArrayImport.xml
%feature("docstring")  PyArrayImport::importArrayToOutputData "OutputData< double > * PyArrayImport::importArrayToOutputData(const std::vector< double > &vec)

for importing 1D array of doubles from python into  OutputData
";

%feature("docstring")  PyArrayImport::importArrayToOutputData "OutputData< double > * PyArrayImport::importArrayToOutputData(const std::vector< std::vector< double >> &vec)

for importing 2D array of doubles from python into  OutputData
";


// File: namespacepyfmt2.xml
%feature("docstring")  pyfmt2::representShape2D "std::string pyfmt2::representShape2D(const std::string &indent, const IShape2D *ishape, bool mask_value, std::function< std::string(double)> printValueFunc)

Returns fixed Python code snippet that defines the function \"runSimulation\". 
";

%feature("docstring")  pyfmt2::valueTimesUnit "std::string pyfmt2::valueTimesUnit(const RealParameter *par)

Returns parameter value, followed by its unit multiplicator (like \"* nm\"). 
";

%feature("docstring")  pyfmt2::argumentList "std::string pyfmt2::argumentList(const IParameterized *ip)

Returns comma-separated list of parameter values, including unit multiplicator (like \"* nm\"). 
";

%feature("docstring")  pyfmt2::printDistribution "std::string pyfmt2::printDistribution(const IDistribution1D &par_distr, const std::string &units)

Prints distribution with constructor parameters in given units. ba.DistributionGaussian(2.0*deg, 0.02*deg) 
";

%feature("docstring")  pyfmt2::printParameterDistribution "std::string pyfmt2::printParameterDistribution(const ParameterDistribution &par_distr, const std::string &distVarName, const std::string &units)
";

%feature("docstring")  pyfmt2::printAxis "std::string pyfmt2::printAxis(const IAxis &axis, const std::string &units, size_t offset)

Prints python-script definition for given axis. offset is used for alignment and indentation in multiple-line definitions 
";


// File: namespacerefMat.xml


// File: namespaceSpectrumUtils.xml
%feature("docstring")  SpectrumUtils::FindPeaks "std::vector< std::pair< double, double > > SpectrumUtils::FindPeaks(const Histogram2D &hist, double sigma=2, const std::string &option={}, double threshold=0.05)
";


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

Simulation with fitting.  Beam intensity set to provide reasonably large values in detector channels. 
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

Helper factory function to use in  GISASSimulation. Depending on the type of detector, returns either  RectangularConverter or  SphericalConverter. 
";

%feature("docstring")  UnitConverterUtils::createConverter "std::unique_ptr< IUnitConverter > UnitConverterUtils::createConverter(const Simulation &simulation)
";


// File: Beam_8cpp.xml


// File: Beam_8h.xml


// File: FootprintGauss_8cpp.xml


// File: FootprintGauss_8h.xml


// File: FootprintSquare_8cpp.xml


// File: FootprintSquare_8h.xml


// File: IFootprintFactor_8cpp.xml


// File: IFootprintFactor_8h.xml


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


// File: CumulativeValue_8cpp.xml


// File: CumulativeValue_8h.xml


// File: LLData_8cpp.xml


// File: LLData_8h.xml
%feature("docstring")  HaveSameDimensions "bool HaveSameDimensions(const LLData< T > &left, const LLData< T > &right)
";


// File: OutputData_8cpp.xml


// File: OutputData_8h.xml


// File: OutputDataIterator_8h.xml
%feature("docstring")  swap "void swap(OutputDataIterator< TValue, TContainer > &left, OutputDataIterator< TValue, TContainer > &right)

make Swappable 
";


// File: DetectionProperties_8cpp.xml


// File: DetectionProperties_8h.xml


// File: DetectorContext_8cpp.xml


// File: DetectorContext_8h.xml


// File: DetectorFunctions_8cpp.xml


// File: DetectorFunctions_8h.xml


// File: DetectorMask_8cpp.xml


// File: DetectorMask_8h.xml


// File: IDetector_8cpp.xml


// File: IDetector_8h.xml


// File: IDetector2D_8cpp.xml


// File: IDetector2D_8h.xml


// File: IsGISAXSDetector_8cpp.xml


// File: IsGISAXSDetector_8h.xml


// File: RectangularDetector_8cpp.xml


// File: RectangularDetector_8h.xml


// File: RectangularPixel_8cpp.xml


// File: RectangularPixel_8h.xml


// File: RegionOfInterest_8cpp.xml


// File: RegionOfInterest_8h.xml


// File: SimpleUnitConverters_8cpp.xml


// File: SimpleUnitConverters_8h.xml


// File: SimulationArea_8cpp.xml


// File: SimulationArea_8h.xml


// File: SimulationAreaIterator_8cpp.xml


// File: SimulationAreaIterator_8h.xml


// File: SpecularDetector1D_8cpp.xml


// File: SpecularDetector1D_8h.xml


// File: SphericalDetector_8cpp.xml


// File: SphericalDetector_8h.xml


// File: SphericalPixel_8cpp.xml


// File: SphericalPixel_8h.xml


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


// File: Histogram1D_8cpp.xml


// File: Histogram1D_8h.xml


// File: Histogram2D_8cpp.xml


// File: Histogram2D_8h.xml


// File: IHistogram_8cpp.xml


// File: IHistogram_8h.xml


// File: IntensityDataIOFactory_8cpp.xml


// File: IntensityDataIOFactory_8h.xml


// File: SimulationResult_8cpp.xml


// File: SimulationResult_8h.xml


// File: boost__streams_8h.xml


// File: DataFormatUtils_8cpp.xml


// File: DataFormatUtils_8h.xml


// File: OutputDataReader_8cpp.xml


// File: OutputDataReader_8h.xml


// File: OutputDataReadFactory_8cpp.xml


// File: OutputDataReadFactory_8h.xml


// File: OutputDataReadStrategy_8cpp.xml


// File: OutputDataReadStrategy_8h.xml


// File: OutputDataWriteFactory_8cpp.xml


// File: OutputDataWriteFactory_8h.xml


// File: OutputDataWriter_8cpp.xml


// File: OutputDataWriter_8h.xml


// File: OutputDataWriteStrategy_8cpp.xml


// File: OutputDataWriteStrategy_8h.xml


// File: TiffHandler_8cpp.xml


// File: TiffHandler_8h.xml


// File: ChiSquaredModule_8cpp.xml


// File: ChiSquaredModule_8h.xml


// File: FourierTransform_8cpp.xml


// File: FourierTransform_8h.xml


// File: IChiSquaredModule_8cpp.xml


// File: IChiSquaredModule_8h.xml


// File: Instrument_8cpp.xml


// File: Instrument_8h.xml


// File: IntensityDataFunctions_8cpp.xml


// File: IntensityDataFunctions_8h.xml


// File: PyArrayImportUtils_8cpp.xml


// File: PyArrayImportUtils_8h.xml


// File: PyFmt2_8cpp.xml


// File: PyFmt2_8h.xml


// File: SpectrumUtils_8cpp.xml


// File: SpectrumUtils_8h.xml


// File: VarianceFunctions_8cpp.xml


// File: VarianceFunctions_8h.xml


// File: ArrayUtils_8cpp.xml


// File: ArrayUtils_8h.xml


// File: IIntensityFunction_8cpp.xml


// File: IIntensityFunction_8h.xml


// File: ConvolutionDetectorResolution_8cpp.xml


// File: ConvolutionDetectorResolution_8h.xml


// File: Convolve_8cpp.xml


// File: Convolve_8h.xml


// File: IDetectorResolution_8h.xml


// File: IResolutionFunction2D_8cpp.xml


// File: IResolutionFunction2D_8h.xml


// File: ResolutionFunction2DGaussian_8cpp.xml


// File: ResolutionFunction2DGaussian_8h.xml


// File: ScanResolution_8cpp.xml


// File: ScanResolution_8h.xml


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


// File: AngularSpecScan_8cpp.xml


// File: AngularSpecScan_8h.xml


// File: ISpecularScan_8cpp.xml


// File: ISpecularScan_8h.xml


// File: QSpecScan_8cpp.xml


// File: QSpecScan_8h.xml


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


// File: AxisNames_8cpp.xml


// File: AxisNames_8h.xml


// File: IUnitConverter_8cpp.xml


// File: IUnitConverter_8h.xml


// File: UnitConverter1D_8cpp.xml


// File: UnitConverter1D_8h.xml


// File: deprecated.xml


// File: dir_2afd61a498231c74441502b63b50f75c.xml


// File: dir_7de90f35ae2a2c7b4fa95823d333cc96.xml


// File: dir_c6310732a22f63c0c2fc5595561e68f1.xml


// File: dir_e8e4c52c5b1be567b4cbfc8c213ce785.xml


// File: dir_44f78a63fb6824b6161080fb024dfdfe.xml


// File: dir_cca9b87b2505f372a6ce58947a507789.xml


// File: dir_4470199ae7eb44153ffe31d163ed0f28.xml


// File: dir_0af69761ac55fbb3eaeece0bb92e99d9.xml


// File: dir_d7044b5fc4daccc5700de9f07da81a11.xml


// File: dir_602d2305564088eb1fd2ee9e74929d48.xml


// File: dir_d6d024cca01b851661c3fb5635dd2ee0.xml


// File: dir_790d5e8b445d9aec8c8895146706942a.xml


// File: dir_dfcc64e98e4f62108d0fa0099ad7f9c0.xml


// File: dir_6de83e740cfcd9d0abfe8dffab2832a5.xml


// File: dir_d7a24665a95cfc15308ebd7b07b5ebd6.xml


// File: dir_5d2259b43612a5a0ff7512df653d7370.xml


// File: dir_bac1ac4b8e69c9aa3a35df48fc2a6289.xml

