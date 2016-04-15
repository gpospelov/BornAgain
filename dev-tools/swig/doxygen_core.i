
// File: index.xml

// File: classAngularPixelMap.xml
%feature("docstring") AngularPixelMap "";

%feature("docstring")  AngularPixelMap::AngularPixelMap "AngularPixelMap::AngularPixelMap(Bin1D alpha_bin, Bin1D phi_bin)
";

%feature("docstring")  AngularPixelMap::~AngularPixelMap "virtual AngularPixelMap::~AngularPixelMap()
";

%feature("docstring")  AngularPixelMap::clone "AngularPixelMap * AngularPixelMap::clone() const 
";

%feature("docstring")  AngularPixelMap::createZeroSizeMap "AngularPixelMap * AngularPixelMap::createZeroSizeMap(double x, double y) const 
";

%feature("docstring")  AngularPixelMap::getK "kvector_t AngularPixelMap::getK(double x, double y, double wavelength) const 
";

%feature("docstring")  AngularPixelMap::getIntegrationFactor "double AngularPixelMap::getIntegrationFactor(double x, double y) const 
";

%feature("docstring")  AngularPixelMap::getSolidAngle "double AngularPixelMap::getSolidAngle() const 
";


// File: classAttLimits.xml
%feature("docstring") AttLimits "

Limits for fit parameters.

C++ includes: AttLimits.h
";

%feature("docstring")  AttLimits::AttLimits "AttLimits::AttLimits()
";

%feature("docstring")  AttLimits::~AttLimits "AttLimits::~AttLimits()
";

%feature("docstring")  AttLimits::hasLowerLimit "bool AttLimits::hasLowerLimit() const

if has lower limit 
";

%feature("docstring")  AttLimits::getLowerLimit "double AttLimits::getLowerLimit() const

Returns lower limit. 
";

%feature("docstring")  AttLimits::setLowerLimit "void AttLimits::setLowerLimit(double value)

Sets lower limit. 
";

%feature("docstring")  AttLimits::removeLowerLimit "void AttLimits::removeLowerLimit()

remove lower limit 
";

%feature("docstring")  AttLimits::hasUpperLimit "bool AttLimits::hasUpperLimit() const

if has upper limit 
";

%feature("docstring")  AttLimits::getUpperLimit "double AttLimits::getUpperLimit() const

Returns upper limit. 
";

%feature("docstring")  AttLimits::setUpperLimit "void AttLimits::setUpperLimit(double value)

Sets upper limit. 
";

%feature("docstring")  AttLimits::removeUpperLimit "void AttLimits::removeUpperLimit()

remove upper limit 
";

%feature("docstring")  AttLimits::hasLowerAndUpperLimits "bool AttLimits::hasLowerAndUpperLimits() const

if has lower and upper limit 
";

%feature("docstring")  AttLimits::setFixed "void AttLimits::setFixed(bool is_fixed)

Sets object fixed. 
";

%feature("docstring")  AttLimits::isFixed "bool AttLimits::isFixed() const

if object is fixed at some value 
";

%feature("docstring")  AttLimits::setLimits "void AttLimits::setLimits(double xmin, double xmax)

Sets lower and upper limits. 
";

%feature("docstring")  AttLimits::removeLimits "void AttLimits::removeLimits()

remove limits 
";

%feature("docstring")  AttLimits::isInRange "bool AttLimits::isInRange(double value) const

returns true if proposed value is in limits range 
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

%feature("docstring")  Basic2DParaCrystalBuilder::init_from "void Basic2DParaCrystalBuilder::init_from(const IComponentService *service)
";

%feature("docstring")  Basic2DParaCrystalBuilder::buildSample "ISample * Basic2DParaCrystalBuilder::buildSample() const 
";


// File: classGeometry_1_1BasicVector3D.xml
%feature("docstring") Geometry::BasicVector3D "

Three-dimensional vector template, for use with integer, double, or complex components.

C++ includes: BasicVector3D.h
";

%feature("docstring")  Geometry::BasicVector3D::BasicVector3D "Geometry::BasicVector3D< T >::BasicVector3D()

Default constructor. 
";

%feature("docstring")  Geometry::BasicVector3D::BasicVector3D "Geometry::BasicVector3D< T >::BasicVector3D(const T x1, const T y1, const T z1)

Constructor from cartesian components. 
";

%feature("docstring")  Geometry::BasicVector3D::x "T Geometry::BasicVector3D< T >::x() const

Returns x-component in cartesian coordinate system. 
";

%feature("docstring")  Geometry::BasicVector3D::y "T Geometry::BasicVector3D< T >::y() const

Returns y-component in cartesian coordinate system. 
";

%feature("docstring")  Geometry::BasicVector3D::z "T Geometry::BasicVector3D< T >::z() const

Returns z-component in cartesian coordinate system. 
";

%feature("docstring")  Geometry::BasicVector3D::setX "void Geometry::BasicVector3D< T >::setX(const T &a)

Sets x-component in cartesian coordinate system. 
";

%feature("docstring")  Geometry::BasicVector3D::setY "void Geometry::BasicVector3D< T >::setY(const T &a)

Sets y-component in cartesian coordinate system. 
";

%feature("docstring")  Geometry::BasicVector3D::setZ "void Geometry::BasicVector3D< T >::setZ(const T &a)

Sets z-component in cartesian coordinate system. 
";

%feature("docstring")  Geometry::BasicVector3D::setXYZ "void Geometry::BasicVector3D< T >::setXYZ(const T &x1, const T &y1, const T &z1)

Sets components in cartesian coordinate system. 
";

%feature("docstring")  Geometry::BasicVector3D::conj "BasicVector3D<T> Geometry::BasicVector3D< T >::conj() const

Returns complex conjugate vector. 
";

%feature("docstring")  Geometry::BasicVector3D::mag2 "double Geometry::BasicVector3D< T >::mag2() const

Returns squared magnitude squared of the vector. 
";

%feature("docstring")  Geometry::BasicVector3D::mag "double Geometry::BasicVector3D< T >::mag() const

Returns magnitude of the vector. 
";

%feature("docstring")  Geometry::BasicVector3D::magxy2 "double Geometry::BasicVector3D< T >::magxy2() const

Returns squared distance from z axis. 
";

%feature("docstring")  Geometry::BasicVector3D::magxy "double Geometry::BasicVector3D< T >::magxy() const

Returns distance from z axis. 
";

%feature("docstring")  Geometry::BasicVector3D::phi "double Geometry::BasicVector3D< T >::phi() const

Returns azimuth angle. 
";

%feature("docstring")  Geometry::BasicVector3D::theta "double Geometry::BasicVector3D< T >::theta() const

Returns polar angle. 
";

%feature("docstring")  Geometry::BasicVector3D::cosTheta "double Geometry::BasicVector3D< T >::cosTheta() const

Returns cosine of polar angle. 
";

%feature("docstring")  Geometry::BasicVector3D::sin2Theta "double Geometry::BasicVector3D< T >::sin2Theta() const

Returns squared sine of polar angle. 
";

%feature("docstring")  Geometry::BasicVector3D::unit "BasicVector3D<T> Geometry::BasicVector3D< T >::unit() const

Returns unit vector in direction of this. Throws for null vector. 
";

%feature("docstring")  Geometry::BasicVector3D::complex "BasicVector3D<std::complex<double> > Geometry::BasicVector3D< T >::complex() const

Returns this, trivially converted to complex type. 
";

%feature("docstring")  Geometry::BasicVector3D::dot "auto Geometry::BasicVector3D< T >::dot(const BasicVector3D< U > &v) const -> decltype(this->x()*v.x())

Returns dot product of vectors (antilinear in the first [=self] argument). 
";

%feature("docstring")  Geometry::BasicVector3D::cross "auto Geometry::BasicVector3D< T >::cross(const BasicVector3D< U > &v) const -> BasicVector3D< decltype(this->x()*v.x())>

Returns cross product of vectors (linear in both arguments). 
";

%feature("docstring")  Geometry::BasicVector3D::angle "double Geometry::BasicVector3D< T >::angle(const BasicVector3D< T > &v) const

Returns angle with respect to another vector. 
";

%feature("docstring")  Geometry::BasicVector3D::project "BasicVector3D<T> Geometry::BasicVector3D< T >::project(const BasicVector3D< T > &v) const

Returns projection of this onto other vector: (this*v)*v/|v|^2. 
";

%feature("docstring")  Geometry::BasicVector3D::rotatedX "BasicVector3D<T> Geometry::BasicVector3D< T >::rotatedX(double a) const

Returns result of rotation around x-axis. 
";

%feature("docstring")  Geometry::BasicVector3D::rotatedY "BasicVector3D<T> Geometry::BasicVector3D< T >::rotatedY(double a) const

Returns result of rotation around y-axis. 
";

%feature("docstring")  Geometry::BasicVector3D::rotatedZ "BasicVector3D<T> Geometry::BasicVector3D< T >::rotatedZ(double a) const

Returns result of rotation around z-axis. 
";

%feature("docstring")  Geometry::BasicVector3D::rotated "BasicVector3D<T> Geometry::BasicVector3D< T >::rotated(double a, const BasicVector3D< T > &v) const

Returns result of rotation around the axis specified by another vector. 
";

%feature("docstring")  Geometry::BasicVector3D::conj "BasicVector3D< double > Geometry::BasicVector3D< double >::conj() const

Returns complex conjugate vector. 
";

%feature("docstring")  Geometry::BasicVector3D::conj "BasicVector3D< complex_t > Geometry::BasicVector3D< complex_t >::conj() const

Returns complex conjugate vector. 
";

%feature("docstring")  Geometry::BasicVector3D::phi "double Geometry::BasicVector3D< double >::phi() const

Returns azimuth angle. 
";

%feature("docstring")  Geometry::BasicVector3D::theta "double Geometry::BasicVector3D< double >::theta() const

Returns polar angle. 
";

%feature("docstring")  Geometry::BasicVector3D::cosTheta "double Geometry::BasicVector3D< double >::cosTheta() const

Returns cosine of polar angle. 
";

%feature("docstring")  Geometry::BasicVector3D::sin2Theta "double Geometry::BasicVector3D< double >::sin2Theta() const

Returns squared sine of polar angle. 
";

%feature("docstring")  Geometry::BasicVector3D::complex "BasicVector3D< std::complex< double > > Geometry::BasicVector3D< double >::complex() const

Returns this, trivially converted to complex type. 
";

%feature("docstring")  Geometry::BasicVector3D::dot "complex_t Geometry::BasicVector3D< complex_t >::dot(const BasicVector3D< complex_t > &v) const

Returns dot product of complex vectors (antilinear in the first [=self] argument). 
";

%feature("docstring")  Geometry::BasicVector3D::dot "complex_t Geometry::BasicVector3D< complex_t >::dot(const BasicVector3D< double > &v) const

Returns mixed dot product of complex and double vectors (antilinear in the complex argument). 
";

%feature("docstring")  Geometry::BasicVector3D::dot "complex_t Geometry::BasicVector3D< double >::dot(const BasicVector3D< complex_t > &v) const

Returns mixed dot product of double and complex vectors (linear in the complex argument). 
";

%feature("docstring")  Geometry::BasicVector3D::dot "double Geometry::BasicVector3D< double >::dot(const BasicVector3D< double > &v) const

Returns dot product of double-typed vectors. 
";

%feature("docstring")  Geometry::BasicVector3D::cross "BasicVector3D< double > Geometry::BasicVector3D< double >::cross(const BasicVector3D< double > &v) const

Returns cross product of double-typed vectors. 
";

%feature("docstring")  Geometry::BasicVector3D::cross "BasicVector3D< complex_t > Geometry::BasicVector3D< double >::cross(const BasicVector3D< complex_t > &v) const

Returns mixed cross product of double and complex vectors. 
";

%feature("docstring")  Geometry::BasicVector3D::angle "double Geometry::BasicVector3D< double >::angle(const BasicVector3D< double > &v) const

Returns angle with respect to another vector. 
";

%feature("docstring")  Geometry::BasicVector3D::dot "BA_CORE_API_ std::complex< double > Geometry::BasicVector3D< std::complex< double > >::dot(const BasicVector3D< std::complex< double > > &v) const
";

%feature("docstring")  Geometry::BasicVector3D::dot "BA_CORE_API_ double Geometry::BasicVector3D< double >::dot(const BasicVector3D< double > &v) const
";

%feature("docstring")  Geometry::BasicVector3D::cross "BA_CORE_API_ BasicVector3D< double > Geometry::BasicVector3D< double >::cross(const BasicVector3D< double > &v) const
";

%feature("docstring")  Geometry::BasicVector3D::phi "BA_CORE_API_ double Geometry::BasicVector3D< double >::phi() const
";

%feature("docstring")  Geometry::BasicVector3D::theta "BA_CORE_API_ double Geometry::BasicVector3D< double >::theta() const
";

%feature("docstring")  Geometry::BasicVector3D::complex "BA_CORE_API_ BasicVector3D< std::complex< double > > Geometry::BasicVector3D< double >::complex() const
";


// File: classBeam.xml
%feature("docstring") Beam "

Ideal collimated beam defined by wavelength, direction and intensity.

C++ includes: Beam.h
";

%feature("docstring")  Beam::Beam "Beam::Beam()
";

%feature("docstring")  Beam::Beam "Beam::Beam(const Beam &other)
";

%feature("docstring")  Beam::~Beam "virtual Beam::~Beam()
";

%feature("docstring")  Beam::getCentralK "kvector_t Beam::getCentralK() const

Get the value of the wavevector. 
";

%feature("docstring")  Beam::setCentralK "void Beam::setCentralK(double wavelength, double alpha_i, double phi_i)

Sets the value of the incoming wavevector in terms of wavelength and incoming angles 
";

%feature("docstring")  Beam::getIntensity "double Beam::getIntensity() const

Gets the beam intensity in neutrons/sec. 
";

%feature("docstring")  Beam::setIntensity "void Beam::setIntensity(double intensity)

Sets the beam intensity in neutrons/sec. 
";

%feature("docstring")  Beam::setPolarization "void Beam::setPolarization(const kvector_t &bloch_vector)

Sets the polarization density matrix according to the given Bloch vector. 
";

%feature("docstring")  Beam::getPolarization "Eigen::Matrix2cd Beam::getPolarization() const

Gets the polarization density matrix (in spin basis along z-axis) 
";

%feature("docstring")  Beam::getWavelength "double Beam::getWavelength() const 
";

%feature("docstring")  Beam::getAlpha "double Beam::getAlpha() const 
";

%feature("docstring")  Beam::getPhi "double Beam::getPhi() const 
";


// File: structBin1D.xml
%feature("docstring") Bin1D "

One dimensional bin with left and right bounds.

C++ includes: Bin.h
";

%feature("docstring")  Bin1D::Bin1D "Bin1D::Bin1D()
";

%feature("docstring")  Bin1D::Bin1D "Bin1D::Bin1D(double lower, double upper)
";

%feature("docstring")  Bin1D::getMidPoint "double Bin1D::getMidPoint() const 
";

%feature("docstring")  Bin1D::getBinSize "double Bin1D::getBinSize() const 
";


// File: structBin1DCVector.xml
%feature("docstring") Bin1DCVector "

An one-dimensional range of cvector_t's.

C++ includes: Bin.h
";

%feature("docstring")  Bin1DCVector::Bin1DCVector "Bin1DCVector::Bin1DCVector()
";

%feature("docstring")  Bin1DCVector::Bin1DCVector "Bin1DCVector::Bin1DCVector(const cvector_t &lower, const cvector_t &upper)
";

%feature("docstring")  Bin1DCVector::Bin1DCVector "Bin1DCVector::Bin1DCVector(double wavelength, const Bin1D &alpha_bin, const Bin1D &phi_bin)

creation on  Bin1DCVector from alpha and phi bins 
";

%feature("docstring")  Bin1DCVector::getMidPoint "cvector_t Bin1DCVector::getMidPoint() const 
";

%feature("docstring")  Bin1DCVector::getDelta "cvector_t Bin1DCVector::getDelta() const 
";


// File: structBin1DKVector.xml
%feature("docstring") Bin1DKVector "

An one-dimensional range of kvector_t's.

C++ includes: Bin.h
";

%feature("docstring")  Bin1DKVector::Bin1DKVector "Bin1DKVector::Bin1DKVector()
";

%feature("docstring")  Bin1DKVector::Bin1DKVector "Bin1DKVector::Bin1DKVector(const kvector_t &lower, const kvector_t &upper)
";

%feature("docstring")  Bin1DKVector::Bin1DKVector "Bin1DKVector::Bin1DKVector(double wavelength, const Bin1D &alpha_bin, const Bin1D &phi_bin)

creation on  Bin1DKVector from alpha and phi bins 
";

%feature("docstring")  Bin1DKVector::getMidPoint "kvector_t Bin1DKVector::getMidPoint() const 
";

%feature("docstring")  Bin1DKVector::getDelta "kvector_t Bin1DKVector::getDelta() const 
";


// File: classBoxCompositionBuilder.xml
%feature("docstring") BoxCompositionBuilder "

Parent class to test all kind of compositions made out of boxes. Reproduces Python functional test transform_BoxComposition.py.

C++ includes: BoxCompositionBuilder.h
";

%feature("docstring")  BoxCompositionBuilder::BoxCompositionBuilder "BoxCompositionBuilder::BoxCompositionBuilder()
";

%feature("docstring")  BoxCompositionBuilder::~BoxCompositionBuilder "BoxCompositionBuilder::~BoxCompositionBuilder()
";


// File: classBoxCompositionRotateXBuilder.xml
%feature("docstring") BoxCompositionRotateXBuilder "

Two boxes in particle composition rotated in X by 90 degrees.

C++ includes: BoxCompositionBuilder.h
";

%feature("docstring")  BoxCompositionRotateXBuilder::BoxCompositionRotateXBuilder "BoxCompositionRotateXBuilder::BoxCompositionRotateXBuilder()
";

%feature("docstring")  BoxCompositionRotateXBuilder::buildSample "ISample * BoxCompositionRotateXBuilder::buildSample() const 
";


// File: classBoxCompositionRotateYBuilder.xml
%feature("docstring") BoxCompositionRotateYBuilder "

Two boxes in particle composition rotated in Y by 90 degrees.

C++ includes: BoxCompositionBuilder.h
";

%feature("docstring")  BoxCompositionRotateYBuilder::BoxCompositionRotateYBuilder "BoxCompositionRotateYBuilder::BoxCompositionRotateYBuilder()
";

%feature("docstring")  BoxCompositionRotateYBuilder::buildSample "ISample * BoxCompositionRotateYBuilder::buildSample() const 
";


// File: classBoxCompositionRotateZandYBuilder.xml
%feature("docstring") BoxCompositionRotateZandYBuilder "

Two boxes in particle composition rotated in Z and Y by 90 degrees.

C++ includes: BoxCompositionBuilder.h
";

%feature("docstring")  BoxCompositionRotateZandYBuilder::BoxCompositionRotateZandYBuilder "BoxCompositionRotateZandYBuilder::BoxCompositionRotateZandYBuilder()
";

%feature("docstring")  BoxCompositionRotateZandYBuilder::buildSample "ISample * BoxCompositionRotateZandYBuilder::buildSample() const 
";


// File: classBoxCompositionRotateZBuilder.xml
%feature("docstring") BoxCompositionRotateZBuilder "

Two boxes in particle composition rotated in Z by 90 degrees.

C++ includes: BoxCompositionBuilder.h
";

%feature("docstring")  BoxCompositionRotateZBuilder::BoxCompositionRotateZBuilder "BoxCompositionRotateZBuilder::BoxCompositionRotateZBuilder()
";

%feature("docstring")  BoxCompositionRotateZBuilder::buildSample "ISample * BoxCompositionRotateZBuilder::buildSample() const 
";


// File: classBoxStackCompositionBuilder.xml
%feature("docstring") BoxStackCompositionBuilder "

Two different boxes are first rotated and then composed, composition is then rotated.

C++ includes: BoxCompositionBuilder.h
";

%feature("docstring")  BoxStackCompositionBuilder::BoxStackCompositionBuilder "BoxStackCompositionBuilder::BoxStackCompositionBuilder()
";

%feature("docstring")  BoxStackCompositionBuilder::buildSample "ISample * BoxStackCompositionBuilder::buildSample() const 
";


// File: structIntegratorMCMiser_1_1CallBackHolder.xml
%feature("docstring") IntegratorMCMiser::CallBackHolder "

structure holding the object and possible extra parameters

C++ includes: IntegratorMCMiser.h
";


// File: structIntegratorReal_1_1CallBackHolder.xml
%feature("docstring") IntegratorReal::CallBackHolder "

structure holding the object and possible extra parameters

C++ includes: IntegratorReal.h
";


// File: classCenteredSquareLatticeBuilder.xml
%feature("docstring") CenteredSquareLatticeBuilder "

Builds sample: 2D lattice with different disorder (IsGISAXS example #6)

C++ includes: TwoDimLatticeBuilder.h
";

%feature("docstring")  CenteredSquareLatticeBuilder::CenteredSquareLatticeBuilder "CenteredSquareLatticeBuilder::CenteredSquareLatticeBuilder()
";

%feature("docstring")  CenteredSquareLatticeBuilder::buildSample "ISample * CenteredSquareLatticeBuilder::buildSample() const 
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

%feature("docstring")  ChiSquaredModule::processFitElements "void ChiSquaredModule::processFitElements(std::vector< FitElement >::iterator first, std::vector< FitElement >::iterator last)

Updates mp_simulation_data and mp_weights, returns chi^2. 
";


// File: classExceptions_1_1ClassInitializationException.xml
%feature("docstring") Exceptions::ClassInitializationException "";

%feature("docstring")  Exceptions::ClassInitializationException::ClassInitializationException "Exceptions::ClassInitializationException::ClassInitializationException(const std::string &message)
";


// File: classConstKBinAxis.xml
%feature("docstring") ConstKBinAxis "

Axis with fixed bin size in sin(angle) space.

C++ includes: ConstKBinAxis.h
";

%feature("docstring")  ConstKBinAxis::ConstKBinAxis "ConstKBinAxis::ConstKBinAxis(const std::string &name, size_t nbins, double start, double end)

ConstKBinAxis constructor.

Parameters:
-----------

name: 
Axis name

nbins: 
number of bins

start: 
low edge of first bin

end: 
upper edge of last bin 
";

%feature("docstring")  ConstKBinAxis::~ConstKBinAxis "virtual ConstKBinAxis::~ConstKBinAxis()
";

%feature("docstring")  ConstKBinAxis::clone "ConstKBinAxis * ConstKBinAxis::clone() const

clone function 
";

%feature("docstring")  ConstKBinAxis::createClippedAxis "ConstKBinAxis * ConstKBinAxis::createClippedAxis(double left, double right) const

Creates a new clipped axis. 
";


// File: classConvolutionDetectorResolution.xml
%feature("docstring") ConvolutionDetectorResolution "

Convolutes the intensity in 1 or 2 dimensions with a resolution function.

Limitation: this class assumes that the data points are evenly distributed on each axis

C++ includes: ConvolutionDetectorResolution.h
";

%feature("docstring")  ConvolutionDetectorResolution::ConvolutionDetectorResolution "ConvolutionDetectorResolution::ConvolutionDetectorResolution(cumulative_DF_1d res_function_1d)

Constructor taking a 1 dimensional resolution function as argument. 
";

%feature("docstring")  ConvolutionDetectorResolution::ConvolutionDetectorResolution "ConvolutionDetectorResolution::ConvolutionDetectorResolution(IResolutionFunction2D *p_res_function_2d)

Constructor taking a 2 dimensional resolution function as argument. 
";

%feature("docstring")  ConvolutionDetectorResolution::ConvolutionDetectorResolution "ConvolutionDetectorResolution::ConvolutionDetectorResolution(const IResolutionFunction2D &p_res_function_2d)
";

%feature("docstring")  ConvolutionDetectorResolution::~ConvolutionDetectorResolution "ConvolutionDetectorResolution::~ConvolutionDetectorResolution()
";

%feature("docstring")  ConvolutionDetectorResolution::applyDetectorResolution "void ConvolutionDetectorResolution::applyDetectorResolution(OutputData< double > *p_intensity_map) const

Convolve given intensities with the encapsulated resolution. 
";

%feature("docstring")  ConvolutionDetectorResolution::addParametersToExternalPool "std::string ConvolutionDetectorResolution::addParametersToExternalPool(std::string path, ParameterPool *external_pool, int copy_number=-1) const

Adds parameters from local pool to external pool and recursively call children. 
";

%feature("docstring")  ConvolutionDetectorResolution::clone "ConvolutionDetectorResolution * ConvolutionDetectorResolution::clone() const

clone object 
";

%feature("docstring")  ConvolutionDetectorResolution::getResolutionFunction2D "const IResolutionFunction2D * ConvolutionDetectorResolution::getResolutionFunction2D() const 
";


// File: classMathFunctions_1_1Convolve.xml
%feature("docstring") MathFunctions::Convolve "

Convolution of two real vectors (in 1D or 2D) using Fast Fourier Transform.

Usage: std::vector<double> signal, kernel, result;  Convolve cv; cv.fftconvolve(signal, kernel, result)

Given code rely on code from Jeremy Fix page http://jeremy.fix.free.fr/spip.php?article15 see also \"Efficient convolution using the Fast Fourier Transform, Application in C++\" by Jeremy Fix, May 30, 2011

C++ includes: Convolve.h
";

%feature("docstring")  MathFunctions::Convolve::Convolve "MathFunctions::Convolve::Convolve()
";

%feature("docstring")  MathFunctions::Convolve::~Convolve "MathFunctions::Convolve::~Convolve()
";

%feature("docstring")  MathFunctions::Convolve::fftconvolve "void MathFunctions::Convolve::fftconvolve(const double1d_t &source, const double1d_t &kernel, double1d_t &result)

convolution in 1D 
";

%feature("docstring")  MathFunctions::Convolve::fftconvolve "void MathFunctions::Convolve::fftconvolve(const double2d_t &source, const double2d_t &kernel, double2d_t &result)

convolution in 2D 
";

%feature("docstring")  MathFunctions::Convolve::init "void MathFunctions::Convolve::init(int h_src, int w_src, int h_kernel, int w_kernel)

prepare arrays for 2D convolution of given vectors 
";

%feature("docstring")  MathFunctions::Convolve::setMode "void MathFunctions::Convolve::setMode(EConvolutionMode mode)

Sets convolution mode. 
";


// File: classCoreFunctionalTest.xml
%feature("docstring") CoreFunctionalTest "

Core functional test compares results of the standard simulation with reference intensity data. Normally invoked by  FunctionalMultiTest.

C++ includes: CoreFunctionalTest.h
";

%feature("docstring")  CoreFunctionalTest::CoreFunctionalTest "CoreFunctionalTest::CoreFunctionalTest(const std::string &name, const std::string &description, GISASSimulation *simulation, OutputData< double > *reference, double threshold)
";

%feature("docstring")  CoreFunctionalTest::~CoreFunctionalTest "CoreFunctionalTest::~CoreFunctionalTest()
";

%feature("docstring")  CoreFunctionalTest::runTest "void CoreFunctionalTest::runTest()
";

%feature("docstring")  CoreFunctionalTest::analyseResults "int CoreFunctionalTest::analyseResults()
";

%feature("docstring")  CoreFunctionalTest::printResults "void CoreFunctionalTest::printResults(std::ostream &ostr) const 
";

%feature("docstring")  CoreFunctionalTest::setSimulationResultsFileName "void CoreFunctionalTest::setSimulationResultsFileName(const std::string &file_name)

Sets the name of the file to use to save the simulation results in the case of failed simulation. 
";


// File: classCoreFunctionalTestComponentService.xml
%feature("docstring") CoreFunctionalTestComponentService "

Contains all necessary information to compose core functional test.

C++ includes: CoreFunctionalTestComponentService.h
";

%feature("docstring")  CoreFunctionalTestComponentService::CoreFunctionalTestComponentService "CoreFunctionalTestComponentService::CoreFunctionalTestComponentService(const FunctionalTestInfo &info)
";

%feature("docstring")  CoreFunctionalTestComponentService::getFunctionalTest "IFunctionalTest * CoreFunctionalTestComponentService::getFunctionalTest() const 
";


// File: classCoreShellBoxRotateZandYBuilder.xml
%feature("docstring") CoreShellBoxRotateZandYBuilder "

Rotation and translation of core shell box particle in 3 layers system.

C++ includes: CoreShellParticleBuilder.h
";

%feature("docstring")  CoreShellBoxRotateZandYBuilder::CoreShellBoxRotateZandYBuilder "CoreShellBoxRotateZandYBuilder::CoreShellBoxRotateZandYBuilder()
";

%feature("docstring")  CoreShellBoxRotateZandYBuilder::buildSample "ISample * CoreShellBoxRotateZandYBuilder::buildSample() const 
";


// File: classCoreShellParticleBuilder.xml
%feature("docstring") CoreShellParticleBuilder "

Builds sample: Core Shell Nanoparticles (IsGISAXS example #11).

C++ includes: CoreShellParticleBuilder.h
";

%feature("docstring")  CoreShellParticleBuilder::CoreShellParticleBuilder "CoreShellParticleBuilder::CoreShellParticleBuilder()
";

%feature("docstring")  CoreShellParticleBuilder::buildSample "ISample * CoreShellParticleBuilder::buildSample() const 
";


// File: classCosineRippleBuilder.xml
%feature("docstring") CosineRippleBuilder "

Builds sample: cosine ripple within the 1D-paracrystal model.

C++ includes: RipplesBuilder.h
";

%feature("docstring")  CosineRippleBuilder::CosineRippleBuilder "CosineRippleBuilder::CosineRippleBuilder()
";

%feature("docstring")  CosineRippleBuilder::buildSample "ISample * CosineRippleBuilder::buildSample() const 
";


// File: classCrystal.xml
%feature("docstring") Crystal "

A crystal structure with a form factor as a basis.

C++ includes: Crystal.h
";

%feature("docstring")  Crystal::Crystal "Crystal::Crystal(const ParticleComposition &lattice_basis, const Lattice &lattice)
";

%feature("docstring")  Crystal::~Crystal "Crystal::~Crystal()
";

%feature("docstring")  Crystal::clone "Crystal * Crystal::clone() const

clone method to allow for polymorphic copying 
";

%feature("docstring")  Crystal::cloneInvertB "Crystal * Crystal::cloneInvertB() const

Returns a clone with inverted magnetic fields. 
";

%feature("docstring")  Crystal::accept "void Crystal::accept(ISampleVisitor *visitor) const

calls the  ISampleVisitor's visit method 
";

%feature("docstring")  Crystal::setAmbientMaterial "virtual void Crystal::setAmbientMaterial(const IMaterial &material)
";

%feature("docstring")  Crystal::getAmbientMaterial "virtual const IMaterial* Crystal::getAmbientMaterial() const 
";

%feature("docstring")  Crystal::createTotalFormFactor "IFormFactor * Crystal::createTotalFormFactor(const IFormFactor &meso_crystal_form_factor, const IRotation *p_rotation, kvector_t translation) const

create a total form factor for the mesocrystal with a specific shape and content

Parameters:
-----------

meso_crystal_form_factor: 
the form factor describing the shape of the mesocrystal

ambient_refractive_index: 
the refractive index of the ambient material The bulk content of the mesocrystal is encapsulated by the  IClusteredParticles object itself 
";

%feature("docstring")  Crystal::getTransformedLattice "Lattice Crystal::getTransformedLattice(const IRotation *p_rotation) const 
";

%feature("docstring")  Crystal::getLatticeBasis "const ParticleComposition* Crystal::getLatticeBasis() const 
";

%feature("docstring")  Crystal::setDWFactor "void Crystal::setDWFactor(double dw_factor)
";


// File: classCumulativeValue.xml
%feature("docstring") CumulativeValue "

The cumulative value with average and rms on-the-flight calculations.

C++ includes: CumulativeValue.h
";

%feature("docstring")  CumulativeValue::CumulativeValue "CumulativeValue::CumulativeValue()
";

%feature("docstring")  CumulativeValue::getNumberOfEntries "int CumulativeValue::getNumberOfEntries() const 
";

%feature("docstring")  CumulativeValue::getContent "double CumulativeValue::getContent() const 
";

%feature("docstring")  CumulativeValue::setContent "void CumulativeValue::setContent(double value)
";

%feature("docstring")  CumulativeValue::getAverage "double CumulativeValue::getAverage() const 
";

%feature("docstring")  CumulativeValue::getRMS "double CumulativeValue::getRMS() const 
";

%feature("docstring")  CumulativeValue::add "void CumulativeValue::add(double value, double weight=1.0)
";

%feature("docstring")  CumulativeValue::clear "void CumulativeValue::clear()
";


// File: classCustomBinAxis.xml
%feature("docstring") CustomBinAxis "

Axis with fixed bin size in sin(angle) space used for numerical comparison with IsGisaxs. The main feature of the axis is that it produces zero bin sizes.

C++ includes: CustomBinAxis.h
";

%feature("docstring")  CustomBinAxis::CustomBinAxis "CustomBinAxis::CustomBinAxis(const std::string &name, size_t nbins, double start, double end)

CustomBinAxis constructor.

Parameters:
-----------

name: 
Axis name

nbins: 
number of bins

start: 
center of first bin (IsGisaxs convention)

end: 
center of last bin (IsGisaxs convention) 
";

%feature("docstring")  CustomBinAxis::~CustomBinAxis "virtual CustomBinAxis::~CustomBinAxis()
";

%feature("docstring")  CustomBinAxis::clone "CustomBinAxis * CustomBinAxis::clone() const

clone function 
";

%feature("docstring")  CustomBinAxis::getBin "Bin1D CustomBinAxis::getBin(size_t index) const

retrieve a 1d bin for the given index 
";

%feature("docstring")  CustomBinAxis::getBinCenters "std::vector< double > CustomBinAxis::getBinCenters() const 
";

%feature("docstring")  CustomBinAxis::createClippedAxis "CustomBinAxis * CustomBinAxis::createClippedAxis(double left, double right) const

Creates a new clipped axis. 
";


// File: classCustomMorphologyBuilder.xml
%feature("docstring") CustomMorphologyBuilder "

Builds sample: mixture of different particles (IsGISAXS example #7)

C++ includes: CustomMorphologyBuilder.h
";

%feature("docstring")  CustomMorphologyBuilder::CustomMorphologyBuilder "CustomMorphologyBuilder::CustomMorphologyBuilder()
";

%feature("docstring")  CustomMorphologyBuilder::buildSample "ISample * CustomMorphologyBuilder::buildSample() const 
";


// File: classCylindersAndPrismsBuilder.xml
%feature("docstring") CylindersAndPrismsBuilder "

Builds sample: mixture of cylinders and prisms without interference (IsGISAXS example #1)

C++ includes: CylindersAndPrismsBuilder.h
";

%feature("docstring")  CylindersAndPrismsBuilder::CylindersAndPrismsBuilder "CylindersAndPrismsBuilder::CylindersAndPrismsBuilder()
";

%feature("docstring")  CylindersAndPrismsBuilder::buildSample "ISample * CylindersAndPrismsBuilder::buildSample() const 
";


// File: classCylindersInBABuilder.xml
%feature("docstring") CylindersInBABuilder "

Builds sample: cylinder formfactor in BA (IsGISAXS example #3, part II)

C++ includes: CylindersBuilder.h
";

%feature("docstring")  CylindersInBABuilder::CylindersInBABuilder "CylindersInBABuilder::CylindersInBABuilder()
";

%feature("docstring")  CylindersInBABuilder::buildSample "ISample * CylindersInBABuilder::buildSample() const 
";


// File: classCylindersInDWBABuilder.xml
%feature("docstring") CylindersInDWBABuilder "

Builds sample: cylinder formfactor in DWBA (IsGISAXS example #3, part I)

C++ includes: CylindersBuilder.h
";

%feature("docstring")  CylindersInDWBABuilder::CylindersInDWBABuilder "CylindersInDWBABuilder::CylindersInDWBABuilder()
";

%feature("docstring")  CylindersInDWBABuilder::buildSample "ISample * CylindersInDWBABuilder::buildSample() const 
";


// File: classCylindersInSSCABuilder.xml
%feature("docstring") CylindersInSSCABuilder "

Builds sample: size spacing correlation approximation (IsGISAXS example #15)

C++ includes: SizeDistributionModelsBuilder.h
";

%feature("docstring")  CylindersInSSCABuilder::CylindersInSSCABuilder "CylindersInSSCABuilder::CylindersInSSCABuilder()
";

%feature("docstring")  CylindersInSSCABuilder::buildSample "ISample * CylindersInSSCABuilder::buildSample() const 
";


// File: classCylindersWithSizeDistributionBuilder.xml
%feature("docstring") CylindersWithSizeDistributionBuilder "

Cylinders in BA with size distributions (IsGISAXS example #3, part II)

C++ includes: ParticleDistributionsBuilder.h
";

%feature("docstring")  CylindersWithSizeDistributionBuilder::CylindersWithSizeDistributionBuilder "CylindersWithSizeDistributionBuilder::CylindersWithSizeDistributionBuilder()
";

%feature("docstring")  CylindersWithSizeDistributionBuilder::buildSample "ISample * CylindersWithSizeDistributionBuilder::buildSample() const 
";


// File: classExceptions_1_1DeadReferenceException.xml
%feature("docstring") Exceptions::DeadReferenceException "";

%feature("docstring")  Exceptions::DeadReferenceException::DeadReferenceException "Exceptions::DeadReferenceException::DeadReferenceException(const std::string &message)
";


// File: classDecoratedLayerDWBASimulation.xml
%feature("docstring") DecoratedLayerDWBASimulation "

Calculates scattering cross sections in DWBA for a layer with particles in/on it.

C++ includes: DecoratedLayerDWBASimulation.h
";

%feature("docstring")  DecoratedLayerDWBASimulation::DecoratedLayerDWBASimulation "DecoratedLayerDWBASimulation::DecoratedLayerDWBASimulation(const Layer *p_layer, size_t layout_index=0)
";

%feature("docstring")  DecoratedLayerDWBASimulation::~DecoratedLayerDWBASimulation "DecoratedLayerDWBASimulation::~DecoratedLayerDWBASimulation()
";

%feature("docstring")  DecoratedLayerDWBASimulation::clone "DecoratedLayerDWBASimulation* DecoratedLayerDWBASimulation::clone() const 
";

%feature("docstring")  DecoratedLayerDWBASimulation::run "void DecoratedLayerDWBASimulation::run()
";


// File: classDecouplingApproximationStrategy.xml
%feature("docstring") DecouplingApproximationStrategy "

Strategy for implementing decoupling approximation.

C++ includes: DecouplingApproximationStrategy.h
";

%feature("docstring")  DecouplingApproximationStrategy::DecouplingApproximationStrategy "DecouplingApproximationStrategy::DecouplingApproximationStrategy(SimulationOptions sim_params)
";

%feature("docstring")  DecouplingApproximationStrategy::~DecouplingApproximationStrategy "virtual DecouplingApproximationStrategy::~DecouplingApproximationStrategy()
";

%feature("docstring")  DecouplingApproximationStrategy::init "void DecouplingApproximationStrategy::init(const SafePointerVector< FormFactorInfo > &form_factor_infos, const IInterferenceFunction &iff)

Initializes the object with form factors and interference functions. 
";


// File: classDetectorMask.xml
%feature("docstring") DetectorMask "

The container with all masks.

C++ includes: DetectorMask.h
";

%feature("docstring")  DetectorMask::DetectorMask "DetectorMask::DetectorMask()
";

%feature("docstring")  DetectorMask::DetectorMask "DetectorMask::DetectorMask(const DetectorMask &other)
";

%feature("docstring")  DetectorMask::addMask "void DetectorMask::addMask(const Geometry::IShape2D &shape, bool mask_value)

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

%feature("docstring")  DetectorMask::getMask "bool DetectorMask::getMask(size_t index) const 
";

%feature("docstring")  DetectorMask::getMaskData "const OutputData< bool > * DetectorMask::getMaskData() const 
";

%feature("docstring")  DetectorMask::removeMasks "void DetectorMask::removeMasks()

remove all masks and return object to initial state 
";

%feature("docstring")  DetectorMask::hasMasks "bool DetectorMask::hasMasks() const

returns true if has masks 
";

%feature("docstring")  DetectorMask::getNumberOfMaskedChannels "int DetectorMask::getNumberOfMaskedChannels() const 
";

%feature("docstring")  DetectorMask::getNumberOfMasks "size_t DetectorMask::getNumberOfMasks() const 
";

%feature("docstring")  DetectorMask::getMaskShape "const Geometry::IShape2D * DetectorMask::getMaskShape(size_t mask_index, bool &mask_value) const 
";


// File: classDistributionCosine.xml
%feature("docstring") DistributionCosine "

Cosine distribution.

C++ includes: Distributions.h
";

%feature("docstring")  DistributionCosine::DistributionCosine "DistributionCosine::DistributionCosine()
";

%feature("docstring")  DistributionCosine::DistributionCosine "DistributionCosine::DistributionCosine(double mean, double sigma)
";

%feature("docstring")  DistributionCosine::~DistributionCosine "virtual DistributionCosine::~DistributionCosine()
";

%feature("docstring")  DistributionCosine::clone "virtual DistributionCosine* DistributionCosine::clone() const

clone method 
";

%feature("docstring")  DistributionCosine::probabilityDensity "double DistributionCosine::probabilityDensity(double x) const

get the probability density for value x 
";

%feature("docstring")  DistributionCosine::getMean "virtual double DistributionCosine::getMean() const

get the mean of the distribution 
";

%feature("docstring")  DistributionCosine::getSigma "double DistributionCosine::getSigma() const

get the sigma parameter of the distribution 
";

%feature("docstring")  DistributionCosine::generateValueList "std::vector< double > DistributionCosine::generateValueList(size_t nbr_samples, double sigma_factor, const AttLimits &limits=AttLimits()) const

generate list of sample values 
";


// File: classDistributionGate.xml
%feature("docstring") DistributionGate "

uniform distribution function with half width hwhm

C++ includes: Distributions.h
";

%feature("docstring")  DistributionGate::DistributionGate "DistributionGate::DistributionGate()
";

%feature("docstring")  DistributionGate::DistributionGate "DistributionGate::DistributionGate(double min, double max)
";

%feature("docstring")  DistributionGate::~DistributionGate "virtual DistributionGate::~DistributionGate()
";

%feature("docstring")  DistributionGate::clone "virtual DistributionGate* DistributionGate::clone() const

clone method 
";

%feature("docstring")  DistributionGate::probabilityDensity "double DistributionGate::probabilityDensity(double x) const

get the probability density for value x 
";

%feature("docstring")  DistributionGate::getMean "virtual double DistributionGate::getMean() const

get the mean of the distribution 
";

%feature("docstring")  DistributionGate::getMin "double DistributionGate::getMin() const

get the minimum value of the distribution 
";

%feature("docstring")  DistributionGate::getMax "double DistributionGate::getMax() const

get the maximum value of the distribution 
";

%feature("docstring")  DistributionGate::generateValueList "std::vector< double > DistributionGate::generateValueList(size_t nbr_samples, double sigma_factor, const AttLimits &limits=AttLimits()) const

generate list of sample values 
";


// File: classDistributionGaussian.xml
%feature("docstring") DistributionGaussian "

Gaussian distribution with standard deviation std_dev.

C++ includes: Distributions.h
";

%feature("docstring")  DistributionGaussian::DistributionGaussian "DistributionGaussian::DistributionGaussian()
";

%feature("docstring")  DistributionGaussian::DistributionGaussian "DistributionGaussian::DistributionGaussian(double mean, double std_dev)
";

%feature("docstring")  DistributionGaussian::~DistributionGaussian "virtual DistributionGaussian::~DistributionGaussian()
";

%feature("docstring")  DistributionGaussian::clone "virtual DistributionGaussian* DistributionGaussian::clone() const

clone method 
";

%feature("docstring")  DistributionGaussian::probabilityDensity "double DistributionGaussian::probabilityDensity(double x) const

get the probability density for value x 
";

%feature("docstring")  DistributionGaussian::getMean "virtual double DistributionGaussian::getMean() const

get the mean of the distribution 
";

%feature("docstring")  DistributionGaussian::getStdDev "double DistributionGaussian::getStdDev() const

get the standard deviation 
";

%feature("docstring")  DistributionGaussian::generateValueList "std::vector< double > DistributionGaussian::generateValueList(size_t nbr_samples, double sigma_factor, const AttLimits &limits=AttLimits()) const

generate list of sample values 
";


// File: classDistributionHandler.xml
%feature("docstring") DistributionHandler "

Provides the functionality to average over parameter distributions with weights.

C++ includes: DistributionHandler.h
";

%feature("docstring")  DistributionHandler::DistributionHandler "DistributionHandler::DistributionHandler()
";

%feature("docstring")  DistributionHandler::~DistributionHandler "DistributionHandler::~DistributionHandler()
";

%feature("docstring")  DistributionHandler::addParameterDistribution "void DistributionHandler::addParameterDistribution(const std::string &param_name, const IDistribution1D &distribution, size_t nbr_samples, double sigma_factor=0.0, const AttLimits &limits=AttLimits())

add a sampled parameter distribution 
";

%feature("docstring")  DistributionHandler::addParameterDistribution "void DistributionHandler::addParameterDistribution(const ParameterDistribution &par_distr)
";

%feature("docstring")  DistributionHandler::getTotalNumberOfSamples "size_t DistributionHandler::getTotalNumberOfSamples() const

get the total number of parameter value combinations (product of the individual sizes of each parameter distribution 
";

%feature("docstring")  DistributionHandler::setParameterValues "double DistributionHandler::setParameterValues(ParameterPool *p_parameter_pool, size_t index)

set the parameter values of the simulation object to a specific combination of values, determined by the index (which must be smaller than the total number of combinations) and returns the weight associated with this combination of parameter values 
";

%feature("docstring")  DistributionHandler::getDistributions "const DistributionHandler::Distributions_t & DistributionHandler::getDistributions() const 
";


// File: classDistributionLogNormal.xml
%feature("docstring") DistributionLogNormal "

Log-normal distribution.

C++ includes: Distributions.h
";

%feature("docstring")  DistributionLogNormal::DistributionLogNormal "DistributionLogNormal::DistributionLogNormal(double scale_param)
";

%feature("docstring")  DistributionLogNormal::DistributionLogNormal "DistributionLogNormal::DistributionLogNormal(double median, double scale_param)
";

%feature("docstring")  DistributionLogNormal::~DistributionLogNormal "virtual DistributionLogNormal::~DistributionLogNormal()
";

%feature("docstring")  DistributionLogNormal::clone "virtual DistributionLogNormal* DistributionLogNormal::clone() const

clone method 
";

%feature("docstring")  DistributionLogNormal::probabilityDensity "double DistributionLogNormal::probabilityDensity(double x) const

get the probability density for value x 
";

%feature("docstring")  DistributionLogNormal::getMean "double DistributionLogNormal::getMean() const

get the mean of the distribution 
";

%feature("docstring")  DistributionLogNormal::getMedian "double DistributionLogNormal::getMedian() const

get the median of the distribution 
";

%feature("docstring")  DistributionLogNormal::getScalePar "double DistributionLogNormal::getScalePar() const

get the scale parameter of the distribution 
";

%feature("docstring")  DistributionLogNormal::generateValueList "std::vector< double > DistributionLogNormal::generateValueList(size_t nbr_samples, double sigma_factor, const AttLimits &limits=AttLimits()) const

generate list of sample values 
";


// File: classDistributionLorentz.xml
%feature("docstring") DistributionLorentz "

Lorentz distribution with half width hwhm.

C++ includes: Distributions.h
";

%feature("docstring")  DistributionLorentz::DistributionLorentz "DistributionLorentz::DistributionLorentz()
";

%feature("docstring")  DistributionLorentz::DistributionLorentz "DistributionLorentz::DistributionLorentz(double mean, double hwhm)
";

%feature("docstring")  DistributionLorentz::~DistributionLorentz "virtual DistributionLorentz::~DistributionLorentz()
";

%feature("docstring")  DistributionLorentz::clone "virtual DistributionLorentz* DistributionLorentz::clone() const

clone method 
";

%feature("docstring")  DistributionLorentz::probabilityDensity "double DistributionLorentz::probabilityDensity(double x) const

get the probability density for value x 
";

%feature("docstring")  DistributionLorentz::getMean "virtual double DistributionLorentz::getMean() const

get the mean of the distribution 
";

%feature("docstring")  DistributionLorentz::getHWHM "double DistributionLorentz::getHWHM() const

get the half width at half maximum 
";

%feature("docstring")  DistributionLorentz::generateValueList "std::vector< double > DistributionLorentz::generateValueList(size_t nbr_samples, double sigma_factor, const AttLimits &limits=AttLimits()) const

generate list of sample values 
";


// File: classExceptions_1_1DivisionByZeroException.xml
%feature("docstring") Exceptions::DivisionByZeroException "";

%feature("docstring")  Exceptions::DivisionByZeroException::DivisionByZeroException "Exceptions::DivisionByZeroException::DivisionByZeroException(const std::string &message)
";


// File: classExceptions_1_1DomainErrorException.xml
%feature("docstring") Exceptions::DomainErrorException "";

%feature("docstring")  Exceptions::DomainErrorException::DomainErrorException "Exceptions::DomainErrorException::DomainErrorException(const std::string &message)
";


// File: classDWBADiffuseReflection.xml
%feature("docstring") DWBADiffuseReflection "

Calculation of diffuse (aka off-specular) reflection from multilayers.

C++ includes: DWBADiffuseReflection.h
";

%feature("docstring")  DWBADiffuseReflection::DWBADiffuseReflection "DWBADiffuseReflection::DWBADiffuseReflection()
";

%feature("docstring")  DWBADiffuseReflection::execute "void DWBADiffuseReflection::execute(const MultiLayer &sample, const kvector_t &ki, const kvector_t &kf)
";

%feature("docstring")  DWBADiffuseReflection::setSample "void DWBADiffuseReflection::setSample(const MultiLayer &sample)
";

%feature("docstring")  DWBADiffuseReflection::getDiffuseAutocorr "double DWBADiffuseReflection::getDiffuseAutocorr() const 
";

%feature("docstring")  DWBADiffuseReflection::getDiffuseCrosscorr "double DWBADiffuseReflection::getDiffuseCrosscorr() const 
";

%feature("docstring")  DWBADiffuseReflection::setKvectors "void DWBADiffuseReflection::setKvectors(const kvector_t &ki, const kvector_t &kf)
";


// File: classDWBAProgressHandler.xml
%feature("docstring") DWBAProgressHandler "

Holds number of items processed by  DWBASimulation and informs  Simulation every n'th processed item.

C++ includes: ProgressHandlerDWBA.h
";


// File: classDWBASimulation.xml
%feature("docstring") DWBASimulation "

Base class for different simulations, using DWBA.

C++ includes: DWBASimulation.h
";

%feature("docstring")  DWBASimulation::DWBASimulation "DWBASimulation::DWBASimulation()
";

%feature("docstring")  DWBASimulation::~DWBASimulation "DWBASimulation::~DWBASimulation()
";

%feature("docstring")  DWBASimulation::init "void DWBASimulation::init(const Simulation &simulation, std::vector< SimulationElement >::iterator begin_it, std::vector< SimulationElement >::iterator end_it)

Initializes the simulation with the parameters from simulation. 
";

%feature("docstring")  DWBASimulation::getDWBAIntensity "const OutputData< double > & DWBASimulation::getDWBAIntensity() const

Returns output data containing calculated intensity. 
";

%feature("docstring")  DWBASimulation::clone "DWBASimulation * DWBASimulation::clone() const 
";


// File: classGeometry_1_1Ellipse.xml
%feature("docstring") Geometry::Ellipse "

Ellipse shape.

C++ includes: Ellipse.h
";

%feature("docstring")  Geometry::Ellipse::Ellipse "Geometry::Ellipse::Ellipse(double xcenter, double ycenter, double xradius, double yradius, double theta=0.0)

Ellipse constructor

Parameters:
-----------

xcenter: 
x-coordinate of  Ellipse's center

ycenter: 
y-coordinate of  Ellipse's center

xradius: 
Radius along x-axis

yradius: 
Radius along y-axis

theta: 
Angle of  Ellipse rotation in radians 
";

%feature("docstring")  Geometry::Ellipse::clone "Ellipse * Geometry::Ellipse::clone() const 
";

%feature("docstring")  Geometry::Ellipse::contains "bool Geometry::Ellipse::contains(double x, double y) const

Returns true if given point is inside or on border of ellipse. 
";

%feature("docstring")  Geometry::Ellipse::contains "bool Geometry::Ellipse::contains(const Bin1D &binx, const Bin1D &biny) const

Returns true if area defined by two bins is inside or on border of ellipse. More precisely, if mid point of two bins satisfy this condition. 
";

%feature("docstring")  Geometry::Ellipse::getCenterX "double Geometry::Ellipse::getCenterX() const 
";

%feature("docstring")  Geometry::Ellipse::getCenterY "double Geometry::Ellipse::getCenterY() const 
";

%feature("docstring")  Geometry::Ellipse::getRadiusX "double Geometry::Ellipse::getRadiusX() const 
";

%feature("docstring")  Geometry::Ellipse::getRadiusY "double Geometry::Ellipse::getRadiusY() const 
";

%feature("docstring")  Geometry::Ellipse::getTheta "double Geometry::Ellipse::getTheta() const 
";


// File: classExceptions_1_1ExistingClassRegistrationException.xml
%feature("docstring") Exceptions::ExistingClassRegistrationException "";

%feature("docstring")  Exceptions::ExistingClassRegistrationException::ExistingClassRegistrationException "Exceptions::ExistingClassRegistrationException::ExistingClassRegistrationException(const std::string &message)
";


// File: classExceptions_1_1FileIsBadException.xml
%feature("docstring") Exceptions::FileIsBadException "";

%feature("docstring")  Exceptions::FileIsBadException::FileIsBadException "Exceptions::FileIsBadException::FileIsBadException(const std::string &message)
";


// File: classExceptions_1_1FileNotIsOpenException.xml
%feature("docstring") Exceptions::FileNotIsOpenException "";

%feature("docstring")  Exceptions::FileNotIsOpenException::FileNotIsOpenException "Exceptions::FileNotIsOpenException::FileNotIsOpenException(const std::string &message)
";


// File: classUtils_1_1FileSystem.xml
%feature("docstring") Utils::FileSystem "

Class collecting utilities to work with file system.

C++ includes: FileSystem.h
";


// File: classFitElement.xml
%feature("docstring") FitElement "

Data stucture containing real data and simulation results for single detector cell. Used for chi2/residual calculations.

C++ includes: FitElement.h
";

%feature("docstring")  FitElement::FitElement "FitElement::FitElement()
";

%feature("docstring")  FitElement::FitElement "FitElement::FitElement(size_t index, double simul_value, double real_value, double weight=1.0)
";

%feature("docstring")  FitElement::FitElement "FitElement::FitElement(const FitElement &other)
";

%feature("docstring")  FitElement::getIndex "size_t FitElement::getIndex() const 
";

%feature("docstring")  FitElement::getSimulValue "double FitElement::getSimulValue() const 
";

%feature("docstring")  FitElement::getRealValue "double FitElement::getRealValue() const 
";

%feature("docstring")  FitElement::getWeight "double FitElement::getWeight() const 
";

%feature("docstring")  FitElement::getSquaredDifference "double FitElement::getSquaredDifference() const 
";

%feature("docstring")  FitElement::setSquaredDifference "void FitElement::setSquaredDifference(double value)
";

%feature("docstring")  FitElement::getResidual "double FitElement::getResidual() const 
";

%feature("docstring")  FitElement::setResidual "void FitElement::setResidual(double value)
";


// File: classFixedBinAxis.xml
%feature("docstring") FixedBinAxis "

Axis with fixed bin size.

C++ includes: FixedBinAxis.h
";

%feature("docstring")  FixedBinAxis::FixedBinAxis "FixedBinAxis::FixedBinAxis(const std::string &name, size_t nbins, double start, double end)

FixedBinAxis constructor.

Parameters:
-----------

name: 
Axis name

nbins: 
number of bins

start: 
low edge of first bin

end: 
upper edge of last bin 
";

%feature("docstring")  FixedBinAxis::~FixedBinAxis "virtual FixedBinAxis::~FixedBinAxis()
";

%feature("docstring")  FixedBinAxis::clone "FixedBinAxis * FixedBinAxis::clone() const

clone function 
";

%feature("docstring")  FixedBinAxis::getSize "size_t FixedBinAxis::getSize() const

retrieve the number of bins 
";

%feature("docstring")  FixedBinAxis::getBin "Bin1D FixedBinAxis::getBin(size_t index) const

retrieve a 1d bin for the given index 
";

%feature("docstring")  FixedBinAxis::getMin "double FixedBinAxis::getMin() const

Returns value of first point of axis. 
";

%feature("docstring")  FixedBinAxis::getMax "double FixedBinAxis::getMax() const

Returns value of last point of axis. 
";

%feature("docstring")  FixedBinAxis::getBinCenter "double FixedBinAxis::getBinCenter(size_t index) const 
";

%feature("docstring")  FixedBinAxis::findClosestIndex "size_t FixedBinAxis::findClosestIndex(double value) const

find bin index which is best match for given value 
";

%feature("docstring")  FixedBinAxis::getBinCenters "std::vector< double > FixedBinAxis::getBinCenters() const 
";

%feature("docstring")  FixedBinAxis::getBinBoundaries "std::vector< double > FixedBinAxis::getBinBoundaries() const 
";

%feature("docstring")  FixedBinAxis::createClippedAxis "FixedBinAxis * FixedBinAxis::createClippedAxis(double left, double right) const

Creates a new clipped axis. 
";


// File: classExceptions_1_1FormatErrorException.xml
%feature("docstring") Exceptions::FormatErrorException "";

%feature("docstring")  Exceptions::FormatErrorException::FormatErrorException "Exceptions::FormatErrorException::FormatErrorException(const std::string &message)
";


// File: classFormFactorAnisoPyramid.xml
%feature("docstring") FormFactorAnisoPyramid "

The formfactor of an anisotropic pyramid.

C++ includes: FormFactorAnisoPyramid.h
";

%feature("docstring")  FormFactorAnisoPyramid::FormFactorAnisoPyramid "FormFactorAnisoPyramid::FormFactorAnisoPyramid(double length, double width, double height, double alpha)

Anisotropic Pyramid constructor.

Parameters:
-----------

length: 
of Anisotropic Pyramid's base

width: 
of Anisotropic Pyramid's base

height: 
of Anisotropic Pyramid

alpha: 
angle in radians between base and facet 
";

%feature("docstring")  FormFactorAnisoPyramid::~FormFactorAnisoPyramid "virtual FormFactorAnisoPyramid::~FormFactorAnisoPyramid()
";

%feature("docstring")  FormFactorAnisoPyramid::clone "FormFactorAnisoPyramid * FormFactorAnisoPyramid::clone() const

Returns a clone of this  ISample object. 
";

%feature("docstring")  FormFactorAnisoPyramid::accept "void FormFactorAnisoPyramid::accept(ISampleVisitor *visitor) const

Calls the  ISampleVisitor's visit method. 
";

%feature("docstring")  FormFactorAnisoPyramid::getRadius "double FormFactorAnisoPyramid::getRadius() const

Returns the (approximate in some cases) radial size of the particle of this form factor's shape. This is used for SSCA calculations 
";

%feature("docstring")  FormFactorAnisoPyramid::getHeight "double FormFactorAnisoPyramid::getHeight() const 
";

%feature("docstring")  FormFactorAnisoPyramid::getLength "double FormFactorAnisoPyramid::getLength() const 
";

%feature("docstring")  FormFactorAnisoPyramid::getWidth "double FormFactorAnisoPyramid::getWidth() const 
";

%feature("docstring")  FormFactorAnisoPyramid::getAlpha "double FormFactorAnisoPyramid::getAlpha() const 
";

%feature("docstring")  FormFactorAnisoPyramid::evaluate_for_q "complex_t FormFactorAnisoPyramid::evaluate_for_q(const cvector_t &q) const

evaluate scattering amplitude for complex wavevector

Parameters:
-----------

q: 
wavevector transfer q=k_i-k_f 
";


// File: classFormFactorBox.xml
%feature("docstring") FormFactorBox "

The formfactor for a rectangular box.

The formfactor for a long rectangular box.

C++ includes: FormFactorBox.h
";

%feature("docstring")  FormFactorBox::FormFactorBox "FormFactorBox::FormFactorBox(double length, double width, double height)

Box constructor.

Parameters:
-----------

length: 
of Box's base

width: 
of Box's base

height: 
of Box 
";

%feature("docstring")  FormFactorBox::clone "FormFactorBox * FormFactorBox::clone() const

Returns a clone of this  ISample object. 
";

%feature("docstring")  FormFactorBox::accept "void FormFactorBox::accept(ISampleVisitor *visitor) const

Calls the  ISampleVisitor's visit method. 
";

%feature("docstring")  FormFactorBox::getLength "double FormFactorBox::getLength() const

Returns length of Box. 
";

%feature("docstring")  FormFactorBox::getHeight "double FormFactorBox::getHeight() const

Returns height of Box. 
";

%feature("docstring")  FormFactorBox::getRadius "double FormFactorBox::getRadius() const

Returns radius of Box. 
";

%feature("docstring")  FormFactorBox::getWidth "double FormFactorBox::getWidth() const

Returns width of Box. 
";

%feature("docstring")  FormFactorBox::evaluate_for_q "complex_t FormFactorBox::evaluate_for_q(const cvector_t &q) const

evaluate scattering amplitude for complex wavevector

Parameters:
-----------

q: 
wavevector transfer q=k_i-k_f 
";


// File: classFormFactorCone.xml
%feature("docstring") FormFactorCone "

The formfactor of a cone.

C++ includes: FormFactorCone.h
";

%feature("docstring")  FormFactorCone::FormFactorCone "FormFactorCone::FormFactorCone(double radius, double height, double alpha)

Cone constructor.

Parameters:
-----------

radius: 
of Cone's base

height: 
of Cone

angle: 
in radians between base and facet 
";

%feature("docstring")  FormFactorCone::~FormFactorCone "FormFactorCone::~FormFactorCone()
";

%feature("docstring")  FormFactorCone::clone "FormFactorCone * FormFactorCone::clone() const

Returns a clone of this  ISample object. 
";

%feature("docstring")  FormFactorCone::accept "void FormFactorCone::accept(ISampleVisitor *visitor) const

Calls the  ISampleVisitor's visit method. 
";

%feature("docstring")  FormFactorCone::getHeight "double FormFactorCone::getHeight() const 
";

%feature("docstring")  FormFactorCone::getRadius "double FormFactorCone::getRadius() const

Returns the (approximate in some cases) radial size of the particle of this form factor's shape. This is used for SSCA calculations 
";

%feature("docstring")  FormFactorCone::getAlpha "double FormFactorCone::getAlpha() const 
";

%feature("docstring")  FormFactorCone::evaluate_for_q "complex_t FormFactorCone::evaluate_for_q(const cvector_t &q) const

evaluate scattering amplitude for complex wavevector

Parameters:
-----------

q: 
wavevector transfer q=k_i-k_f 
";


// File: classFormFactorCone6.xml
%feature("docstring") FormFactorCone6 "

The formfactor of a cone6.

C++ includes: FormFactorCone6.h
";

%feature("docstring")  FormFactorCone6::FormFactorCone6 "FormFactorCone6::FormFactorCone6(double radius, double height, double alpha)

Cone6 constructor.

Parameters:
-----------

radius: 
of hexagonal base (different from R in IsGisaxs)

height: 
of Cone6

angle: 
in radians between base and facet 
";

%feature("docstring")  FormFactorCone6::clone "FormFactorCone6 * FormFactorCone6::clone() const

Returns a clone of this  ISample object. 
";

%feature("docstring")  FormFactorCone6::accept "void FormFactorCone6::accept(ISampleVisitor *visitor) const

Calls the  ISampleVisitor's visit method. 
";

%feature("docstring")  FormFactorCone6::getHeight "double FormFactorCone6::getHeight() const 
";

%feature("docstring")  FormFactorCone6::getRadius "double FormFactorCone6::getRadius() const final

Returns the (approximate in some cases) radial size of the particle of this form factor's shape. This is used for SSCA calculations 
";

%feature("docstring")  FormFactorCone6::getAlpha "double FormFactorCone6::getAlpha() const 
";


// File: classFormFactorCrystal.xml
%feature("docstring") FormFactorCrystal "

The formfactor for mesocrystals with a bulk crystal structure of particles.

C++ includes: FormFactorCrystal.h
";

%feature("docstring")  FormFactorCrystal::FormFactorCrystal "FormFactorCrystal::FormFactorCrystal(const Lattice &lattice, const IFormFactor &basis_form_factor, const IFormFactor &meso_form_factor)
";

%feature("docstring")  FormFactorCrystal::~FormFactorCrystal "FormFactorCrystal::~FormFactorCrystal()
";

%feature("docstring")  FormFactorCrystal::clone "FormFactorCrystal * FormFactorCrystal::clone() const

Returns a clone of this  ISample object. 
";

%feature("docstring")  FormFactorCrystal::accept "virtual void FormFactorCrystal::accept(ISampleVisitor *visitor) const

Calls the  ISampleVisitor's visit method. 
";

%feature("docstring")  FormFactorCrystal::getVolume "double FormFactorCrystal::getVolume() const

Returns the total volume of the particle of this form factor's shape. 
";

%feature("docstring")  FormFactorCrystal::getRadius "double FormFactorCrystal::getRadius() const

Returns the (approximate in some cases) radial size of the particle of this form factor's shape. This is used for SSCA calculations 
";

%feature("docstring")  FormFactorCrystal::evaluate "complex_t FormFactorCrystal::evaluate(const WavevectorInfo &wavevectors) const

Returns scattering amplitude for complex wavevector bin

Parameters:
-----------

k_i: 
incoming wavevector

k_f_bin: 
outgoing wavevector bin 
";

%feature("docstring")  FormFactorCrystal::evaluatePol "Eigen::Matrix2cd FormFactorCrystal::evaluatePol(const WavevectorInfo &wavevectors) const

Returns scattering amplitude for matrix interactions

Parameters:
-----------

k_i: 
incoming wavevector

k_f_bin: 
outgoing wavevector bin 
";

%feature("docstring")  FormFactorCrystal::evaluate_for_q "complex_t FormFactorCrystal::evaluate_for_q(const cvector_t &q) const

evaluate scattering amplitude for complex wavevector

Parameters:
-----------

q: 
wavevector transfer q=k_i-k_f 
";


// File: classFormFactorCuboctahedron.xml
%feature("docstring") FormFactorCuboctahedron "

The formfactor of a cuboctahedron.

C++ includes: FormFactorCuboctahedron.h
";

%feature("docstring")  FormFactorCuboctahedron::FormFactorCuboctahedron "FormFactorCuboctahedron::FormFactorCuboctahedron(double length, double height, double height_ratio, double alpha)

Cuboctahedron constructor.

Parameters:
-----------

length: 
of one side of Cuboctahedron's square base

height: 
of bottom of Cuboctahedron

height_ratio: 
: height top part/height bottom part

angle: 
in radians between base and facet 
";

%feature("docstring")  FormFactorCuboctahedron::~FormFactorCuboctahedron "virtual FormFactorCuboctahedron::~FormFactorCuboctahedron()
";

%feature("docstring")  FormFactorCuboctahedron::clone "FormFactorCuboctahedron * FormFactorCuboctahedron::clone() const final

Returns a clone of this  ISample object. 
";

%feature("docstring")  FormFactorCuboctahedron::accept "void FormFactorCuboctahedron::accept(ISampleVisitor *visitor) const final

Calls the  ISampleVisitor's visit method. 
";

%feature("docstring")  FormFactorCuboctahedron::getRadius "double FormFactorCuboctahedron::getRadius() const final

Returns the (approximate in some cases) radial size of the particle of this form factor's shape. This is used for SSCA calculations 
";

%feature("docstring")  FormFactorCuboctahedron::getHeight "double FormFactorCuboctahedron::getHeight() const 
";

%feature("docstring")  FormFactorCuboctahedron::getHeightRatio "double FormFactorCuboctahedron::getHeightRatio() const 
";

%feature("docstring")  FormFactorCuboctahedron::getLength "double FormFactorCuboctahedron::getLength() const 
";

%feature("docstring")  FormFactorCuboctahedron::getAlpha "double FormFactorCuboctahedron::getAlpha() const 
";


// File: classFormFactorCylinder.xml
%feature("docstring") FormFactorCylinder "

The formfactor of a cylinder.

C++ includes: FormFactorCylinder.h
";

%feature("docstring")  FormFactorCylinder::FormFactorCylinder "FormFactorCylinder::FormFactorCylinder(double radius, double height)

Cylinder constructor.

Parameters:
-----------

radius: 
of Cylinder's base

height: 
of Cylinder 
";

%feature("docstring")  FormFactorCylinder::~FormFactorCylinder "virtual FormFactorCylinder::~FormFactorCylinder()
";

%feature("docstring")  FormFactorCylinder::clone "FormFactorCylinder * FormFactorCylinder::clone() const

Returns a clone of this  ISample object. 
";

%feature("docstring")  FormFactorCylinder::accept "void FormFactorCylinder::accept(ISampleVisitor *visitor) const

Calls the  ISampleVisitor's visit method. 
";

%feature("docstring")  FormFactorCylinder::getHeight "double FormFactorCylinder::getHeight() const 
";

%feature("docstring")  FormFactorCylinder::getRadius "double FormFactorCylinder::getRadius() const

Returns the (approximate in some cases) radial size of the particle of this form factor's shape. This is used for SSCA calculations 
";

%feature("docstring")  FormFactorCylinder::evaluate_for_q "complex_t FormFactorCylinder::evaluate_for_q(const cvector_t &q) const

evaluate scattering amplitude for complex wavevector

Parameters:
-----------

q: 
wavevector transfer q=k_i-k_f 
";


// File: classFormFactorDecoratorDebyeWaller.xml
%feature("docstring") FormFactorDecoratorDebyeWaller "

Debye-Waller factors in radial and z directions.

C++ includes: FormFactorDecoratorDebyeWaller.h
";

%feature("docstring")  FormFactorDecoratorDebyeWaller::FormFactorDecoratorDebyeWaller "FormFactorDecoratorDebyeWaller::FormFactorDecoratorDebyeWaller(const IFormFactor &form_factor, double dw_factor)

Isotropic Debye-Waller factor. 
";

%feature("docstring")  FormFactorDecoratorDebyeWaller::FormFactorDecoratorDebyeWaller "FormFactorDecoratorDebyeWaller::FormFactorDecoratorDebyeWaller(const IFormFactor &form_factor, double dw_h_factor, double dw_r_factor)

Anisotropic Debye-Waller factor. 
";

%feature("docstring")  FormFactorDecoratorDebyeWaller::~FormFactorDecoratorDebyeWaller "virtual FormFactorDecoratorDebyeWaller::~FormFactorDecoratorDebyeWaller()
";

%feature("docstring")  FormFactorDecoratorDebyeWaller::clone "FormFactorDecoratorDebyeWaller * FormFactorDecoratorDebyeWaller::clone() const

Returns a clone of this  ISample object. 
";

%feature("docstring")  FormFactorDecoratorDebyeWaller::accept "virtual void FormFactorDecoratorDebyeWaller::accept(ISampleVisitor *visitor) const

Calls the  ISampleVisitor's visit method. 
";

%feature("docstring")  FormFactorDecoratorDebyeWaller::evaluate "complex_t FormFactorDecoratorDebyeWaller::evaluate(const WavevectorInfo &wavevectors) const

Returns scattering amplitude for complex wavevector bin

Parameters:
-----------

k_i: 
incoming wavevector

k_f_bin: 
outgoing wavevector bin 
";


// File: classFormFactorDecoratorFactor.xml
%feature("docstring") FormFactorDecoratorFactor "

Decorates a formfactor with a constant factor.

C++ includes: FormFactorDecoratorFactor.h
";

%feature("docstring")  FormFactorDecoratorFactor::FormFactorDecoratorFactor "FormFactorDecoratorFactor::FormFactorDecoratorFactor(const IFormFactor &form_factor, const complex_t &factor)
";

%feature("docstring")  FormFactorDecoratorFactor::~FormFactorDecoratorFactor "virtual FormFactorDecoratorFactor::~FormFactorDecoratorFactor()
";

%feature("docstring")  FormFactorDecoratorFactor::clone "FormFactorDecoratorFactor * FormFactorDecoratorFactor::clone() const

Returns a clone of this  ISample object. 
";

%feature("docstring")  FormFactorDecoratorFactor::accept "void FormFactorDecoratorFactor::accept(ISampleVisitor *visitor) const

Calls the  ISampleVisitor's visit method. 
";

%feature("docstring")  FormFactorDecoratorFactor::evaluate "complex_t FormFactorDecoratorFactor::evaluate(const WavevectorInfo &wavevectors) const

Evaluate the form factor for scalar calculations. 
";


// File: classFormFactorDecoratorMaterial.xml
%feature("docstring") FormFactorDecoratorMaterial "

Decorates a scalar formfactor with the correct factor for the material's refractive index and that of its surrounding material.

C++ includes: FormFactorDecoratorMaterial.h
";

%feature("docstring")  FormFactorDecoratorMaterial::FormFactorDecoratorMaterial "FormFactorDecoratorMaterial::FormFactorDecoratorMaterial(const IFormFactor &form_factor)
";

%feature("docstring")  FormFactorDecoratorMaterial::clone "FormFactorDecoratorMaterial * FormFactorDecoratorMaterial::clone() const

Returns a clone of this  ISample object. 
";

%feature("docstring")  FormFactorDecoratorMaterial::accept "virtual void FormFactorDecoratorMaterial::accept(ISampleVisitor *visitor) const

Calls the  ISampleVisitor's visit method. 
";

%feature("docstring")  FormFactorDecoratorMaterial::setMaterial "void FormFactorDecoratorMaterial::setMaterial(const IMaterial &material)

Sets the material of the scatterer. 
";

%feature("docstring")  FormFactorDecoratorMaterial::setAmbientMaterial "void FormFactorDecoratorMaterial::setAmbientMaterial(const IMaterial &material)

Sets the ambient material. 
";

%feature("docstring")  FormFactorDecoratorMaterial::getAmbientRefractiveIndex "complex_t FormFactorDecoratorMaterial::getAmbientRefractiveIndex() const

Retrieves the refractive index of the ambient material. 
";

%feature("docstring")  FormFactorDecoratorMaterial::evaluatePol "Eigen::Matrix2cd FormFactorDecoratorMaterial::evaluatePol(const WavevectorInfo &wavevectors) const

Returns scattering amplitude for matrix interactions. 
";


// File: classFormFactorDecoratorMultiPositionFactor.xml
%feature("docstring") FormFactorDecoratorMultiPositionFactor "

The formfactor for the same particle at different fixed positions.

C++ includes: FormFactorDecoratorMultiPositionFactor.h
";

%feature("docstring")  FormFactorDecoratorMultiPositionFactor::FormFactorDecoratorMultiPositionFactor "FormFactorDecoratorMultiPositionFactor::FormFactorDecoratorMultiPositionFactor(const IFormFactor &form_factor, std::vector< kvector_t > positions)
";

%feature("docstring")  FormFactorDecoratorMultiPositionFactor::clone "FormFactorDecoratorMultiPositionFactor * FormFactorDecoratorMultiPositionFactor::clone() const

Returns a clone of this  ISample object. 
";

%feature("docstring")  FormFactorDecoratorMultiPositionFactor::accept "void FormFactorDecoratorMultiPositionFactor::accept(ISampleVisitor *visitor) const

Calls the  ISampleVisitor's visit method. 
";

%feature("docstring")  FormFactorDecoratorMultiPositionFactor::getVolume "double FormFactorDecoratorMultiPositionFactor::getVolume() const

Returns the total volume of the particle of this form factor's shape. 
";

%feature("docstring")  FormFactorDecoratorMultiPositionFactor::getRadius "double FormFactorDecoratorMultiPositionFactor::getRadius() const

Returns the (approximate in some cases) radial size of the particle of this form factor's shape. This is used for SSCA calculations 
";

%feature("docstring")  FormFactorDecoratorMultiPositionFactor::evaluate "complex_t FormFactorDecoratorMultiPositionFactor::evaluate(const WavevectorInfo &wavevectors) const

Returns scattering amplitude for complex wavevector bin

Parameters:
-----------

k_i: 
incoming wavevector

k_f_bin: 
outgoing wavevector bin 
";

%feature("docstring")  FormFactorDecoratorMultiPositionFactor::evaluatePol "Eigen::Matrix2cd FormFactorDecoratorMultiPositionFactor::evaluatePol(const WavevectorInfo &wavevectors) const

Returns scattering amplitude for matrix interactions

Parameters:
-----------

k_i: 
incoming wavevector

k_f_bin: 
outgoing wavevector bin 
";


// File: classFormFactorDecoratorPositionFactor.xml
%feature("docstring") FormFactorDecoratorPositionFactor "

Decorates a formfactor with a position dependent phase factor.

C++ includes: FormFactorDecoratorPositionFactor.h
";

%feature("docstring")  FormFactorDecoratorPositionFactor::FormFactorDecoratorPositionFactor "FormFactorDecoratorPositionFactor::FormFactorDecoratorPositionFactor(const IFormFactor &form_factor, kvector_t position)
";

%feature("docstring")  FormFactorDecoratorPositionFactor::~FormFactorDecoratorPositionFactor "virtual FormFactorDecoratorPositionFactor::~FormFactorDecoratorPositionFactor()
";

%feature("docstring")  FormFactorDecoratorPositionFactor::clone "FormFactorDecoratorPositionFactor * FormFactorDecoratorPositionFactor::clone() const

Returns a clone of this  ISample object. 
";

%feature("docstring")  FormFactorDecoratorPositionFactor::accept "void FormFactorDecoratorPositionFactor::accept(ISampleVisitor *visitor) const

Calls the  ISampleVisitor's visit method. 
";

%feature("docstring")  FormFactorDecoratorPositionFactor::evaluate "complex_t FormFactorDecoratorPositionFactor::evaluate(const WavevectorInfo &wavevectors) const

Returns scattering amplitude for complex wavevector bin

Parameters:
-----------

k_i: 
incoming wavevector

k_f_bin: 
outgoing wavevector bin 
";

%feature("docstring")  FormFactorDecoratorPositionFactor::evaluatePol "Eigen::Matrix2cd FormFactorDecoratorPositionFactor::evaluatePol(const WavevectorInfo &wavevectors) const

Returns scattering amplitude for matrix interactions

Parameters:
-----------

k_i: 
incoming wavevector

k_f_bin: 
outgoing wavevector bin 
";


// File: classFormFactorDecoratorRotation.xml
%feature("docstring") FormFactorDecoratorRotation "

Equips a formfactor with a rotation.

C++ includes: FormFactorDecoratorRotation.h
";

%feature("docstring")  FormFactorDecoratorRotation::FormFactorDecoratorRotation "FormFactorDecoratorRotation::FormFactorDecoratorRotation(const IFormFactor &form_factor, const IRotation &transform)

Constructor, setting form factor and rotation. 
";

%feature("docstring")  FormFactorDecoratorRotation::clone "FormFactorDecoratorRotation * FormFactorDecoratorRotation::clone() const

Returns a clone of this  ISample object. 
";

%feature("docstring")  FormFactorDecoratorRotation::accept "void FormFactorDecoratorRotation::accept(ISampleVisitor *visitor) const

Calls the  ISampleVisitor's visit method. 
";

%feature("docstring")  FormFactorDecoratorRotation::evaluate "complex_t FormFactorDecoratorRotation::evaluate(const WavevectorInfo &wavevectors) const

Returns scattering amplitude for complex wavevector bin

Parameters:
-----------

k_i: 
incoming wavevector

k_f_bin: 
outgoing wavevector bin 
";


// File: classFormFactorDodecahedron.xml
%feature("docstring") FormFactorDodecahedron "

The formfactor of a regular dodecahedron.

C++ includes: FormFactorDodecahedron.h
";

%feature("docstring")  FormFactorDodecahedron::FormFactorDodecahedron "FormFactorDodecahedron::FormFactorDodecahedron(double edge)

Constructs a regular dodecahedron.

Parameters:
-----------

edge: 
length 
";

%feature("docstring")  FormFactorDodecahedron::clone "FormFactorDodecahedron * FormFactorDodecahedron::clone() const final

Returns a clone of this  ISample object. 
";

%feature("docstring")  FormFactorDodecahedron::accept "void FormFactorDodecahedron::accept(ISampleVisitor *visitor) const final

Calls the  ISampleVisitor's visit method. 
";

%feature("docstring")  FormFactorDodecahedron::getRadius "double FormFactorDodecahedron::getRadius() const final

Returns the (approximate in some cases) radial size of the particle of this form factor's shape. This is used for SSCA calculations 
";

%feature("docstring")  FormFactorDodecahedron::getEdge "double FormFactorDodecahedron::getEdge() const 
";


// File: classFormFactorDWBA.xml
%feature("docstring") FormFactorDWBA "

Evaluates a coherent sum of the four DWBA terms in a scalar formfactor.

C++ includes: FormFactorDWBA.h
";

%feature("docstring")  FormFactorDWBA::FormFactorDWBA "FormFactorDWBA::FormFactorDWBA(const IFormFactor &form_factor)
";

%feature("docstring")  FormFactorDWBA::~FormFactorDWBA "FormFactorDWBA::~FormFactorDWBA()
";

%feature("docstring")  FormFactorDWBA::clone "FormFactorDWBA * FormFactorDWBA::clone() const

Returns a clone of this  ISample object. 
";

%feature("docstring")  FormFactorDWBA::accept "virtual void FormFactorDWBA::accept(ISampleVisitor *visitor) const

Calls the  ISampleVisitor's visit method. 
";

%feature("docstring")  FormFactorDWBA::setSpecularInfo "void FormFactorDWBA::setSpecularInfo(const ILayerRTCoefficients *p_in_coeffs, const ILayerRTCoefficients *p_out_coeffs)

Sets reflection/transmission info for scalar DWBA simulation. 
";

%feature("docstring")  FormFactorDWBA::evaluate "complex_t FormFactorDWBA::evaluate(const WavevectorInfo &wavevectors) const

Returns scattering amplitude for complex wavevector bin

Parameters:
-----------

k_i: 
incoming wavevector

k_f_bin: 
outgoing wavevector bin 
";


// File: classFormFactorDWBAPol.xml
%feature("docstring") FormFactorDWBAPol "

Evaluates a coherent sum of the 16 matrix DWBA terms in a polarized formfactor.

C++ includes: FormFactorDWBAPol.h
";

%feature("docstring")  FormFactorDWBAPol::FormFactorDWBAPol "FormFactorDWBAPol::FormFactorDWBAPol(const IFormFactor &form_factor)
";

%feature("docstring")  FormFactorDWBAPol::~FormFactorDWBAPol "FormFactorDWBAPol::~FormFactorDWBAPol()
";

%feature("docstring")  FormFactorDWBAPol::clone "FormFactorDWBAPol * FormFactorDWBAPol::clone() const

Returns a clone of this  ISample object. 
";

%feature("docstring")  FormFactorDWBAPol::accept "virtual void FormFactorDWBAPol::accept(ISampleVisitor *visitor) const

calls the  ISampleVisitor's visit method 
";

%feature("docstring")  FormFactorDWBAPol::evaluate "complex_t FormFactorDWBAPol::evaluate(const WavevectorInfo &wavevectors) const

Throws exception. 
";

%feature("docstring")  FormFactorDWBAPol::evaluatePol "Eigen::Matrix2cd FormFactorDWBAPol::evaluatePol(const WavevectorInfo &wavevectors) const

Calculates and returns a polarized form factor calculation in DWBA. 
";

%feature("docstring")  FormFactorDWBAPol::getVolume "double FormFactorDWBAPol::getVolume() const

Returns the total volume of the particle of this form factor's shape. 
";

%feature("docstring")  FormFactorDWBAPol::getRadius "double FormFactorDWBAPol::getRadius() const

Returns the (approximate in some cases) radial size of the particle of this form factor's shape. This is used for SSCA calculations 
";

%feature("docstring")  FormFactorDWBAPol::setSpecularInfo "void FormFactorDWBAPol::setSpecularInfo(const ILayerRTCoefficients *p_in_coeffs, const ILayerRTCoefficients *p_out_coeffs)

Sets reflection/transmission info for scalar DWBA simulation. 
";


// File: classFormFactorEllipsoidalCylinder.xml
%feature("docstring") FormFactorEllipsoidalCylinder "

The formfactor of an ellipsoidal cylinder.

C++ includes: FormFactorEllipsoidalCylinder.h
";

%feature("docstring")  FormFactorEllipsoidalCylinder::FormFactorEllipsoidalCylinder "FormFactorEllipsoidalCylinder::FormFactorEllipsoidalCylinder(double radius_x, double radius_y, double height)

Ellipsoidal Cylinder constructor.

Parameters:
-----------

radius_x: 
half length of one horizontal main axes

radius_y: 
half length of the other horizontal main axes

height: 
of Ellipsoidal Cylinder 
";

%feature("docstring")  FormFactorEllipsoidalCylinder::clone "FormFactorEllipsoidalCylinder * FormFactorEllipsoidalCylinder::clone() const

Returns a clone of this  ISample object. 
";

%feature("docstring")  FormFactorEllipsoidalCylinder::accept "void FormFactorEllipsoidalCylinder::accept(ISampleVisitor *visitor) const

Calls the  ISampleVisitor's visit method. 
";

%feature("docstring")  FormFactorEllipsoidalCylinder::getRadius "double FormFactorEllipsoidalCylinder::getRadius() const

Returns the (approximate in some cases) radial size of the particle of this form factor's shape. This is used for SSCA calculations 
";

%feature("docstring")  FormFactorEllipsoidalCylinder::getRadiusX "double FormFactorEllipsoidalCylinder::getRadiusX() const 
";

%feature("docstring")  FormFactorEllipsoidalCylinder::getRadiusY "double FormFactorEllipsoidalCylinder::getRadiusY() const 
";

%feature("docstring")  FormFactorEllipsoidalCylinder::getHeight "double FormFactorEllipsoidalCylinder::getHeight() const 
";

%feature("docstring")  FormFactorEllipsoidalCylinder::evaluate_for_q "complex_t FormFactorEllipsoidalCylinder::evaluate_for_q(const cvector_t &q) const

evaluate scattering amplitude for complex wavevector

Parameters:
-----------

q: 
wavevector transfer q=k_i-k_f 
";


// File: classFormFactorFullSphere.xml
%feature("docstring") FormFactorFullSphere "

The formfactor of a sphere.

C++ includes: FormFactorFullSphere.h
";

%feature("docstring")  FormFactorFullSphere::FormFactorFullSphere "FormFactorFullSphere::FormFactorFullSphere(double radius)

Full Sphere constructor.

Parameters:
-----------

radius: 
of Sphere 
";

%feature("docstring")  FormFactorFullSphere::clone "FormFactorFullSphere * FormFactorFullSphere::clone() const

Returns a clone of this  ISample object. 
";

%feature("docstring")  FormFactorFullSphere::accept "void FormFactorFullSphere::accept(ISampleVisitor *visitor) const

Calls the  ISampleVisitor's visit method. 
";

%feature("docstring")  FormFactorFullSphere::getRadius "double FormFactorFullSphere::getRadius() const

Returns radius of sphere. 
";

%feature("docstring")  FormFactorFullSphere::evaluate_for_q "complex_t FormFactorFullSphere::evaluate_for_q(const cvector_t &q) const

evaluate scattering amplitude for complex wavevector

Parameters:
-----------

q: 
wavevector transfer q=k_i-k_f 
";


// File: classFormFactorFullSpheroid.xml
%feature("docstring") FormFactorFullSpheroid "

The formfactor of a full spheroid.

C++ includes: FormFactorFullSpheroid.h
";

%feature("docstring")  FormFactorFullSpheroid::FormFactorFullSpheroid "FormFactorFullSpheroid::FormFactorFullSpheroid(double radius, double height)

Full Spheroid constructor.

Parameters:
-----------

radius: 
of spheroid

height: 
of spheroid 
";

%feature("docstring")  FormFactorFullSpheroid::~FormFactorFullSpheroid "FormFactorFullSpheroid::~FormFactorFullSpheroid()
";

%feature("docstring")  FormFactorFullSpheroid::clone "FormFactorFullSpheroid * FormFactorFullSpheroid::clone() const

Returns a clone of this  ISample object. 
";

%feature("docstring")  FormFactorFullSpheroid::accept "void FormFactorFullSpheroid::accept(ISampleVisitor *visitor) const

Calls the  ISampleVisitor's visit method. 
";

%feature("docstring")  FormFactorFullSpheroid::getHeight "double FormFactorFullSpheroid::getHeight() const 
";

%feature("docstring")  FormFactorFullSpheroid::getRadius "double FormFactorFullSpheroid::getRadius() const

Returns the (approximate in some cases) radial size of the particle of this form factor's shape. This is used for SSCA calculations 
";

%feature("docstring")  FormFactorFullSpheroid::evaluate_for_q "complex_t FormFactorFullSpheroid::evaluate_for_q(const cvector_t &q) const

evaluate scattering amplitude for complex wavevector

Parameters:
-----------

q: 
wavevector transfer q=k_i-k_f 
";


// File: classFormFactorGauss.xml
%feature("docstring") FormFactorGauss "

The formfactor of a gaussian.

C++ includes: FormFactorGauss.h
";

%feature("docstring")  FormFactorGauss::FormFactorGauss "FormFactorGauss::FormFactorGauss(double volume)
";

%feature("docstring")  FormFactorGauss::FormFactorGauss "FormFactorGauss::FormFactorGauss(double width, double height)
";

%feature("docstring")  FormFactorGauss::~FormFactorGauss "virtual FormFactorGauss::~FormFactorGauss()
";

%feature("docstring")  FormFactorGauss::clone "FormFactorGauss * FormFactorGauss::clone() const

Returns a clone of this  ISample object. 
";

%feature("docstring")  FormFactorGauss::accept "void FormFactorGauss::accept(ISampleVisitor *visitor) const

Calls the  ISampleVisitor's visit method. 
";

%feature("docstring")  FormFactorGauss::evaluate_for_q "complex_t FormFactorGauss::evaluate_for_q(const cvector_t &q) const

evaluate scattering amplitude for complex wavevector

Parameters:
-----------

q: 
wavevector transfer q=k_i-k_f 
";

%feature("docstring")  FormFactorGauss::getHeight "double FormFactorGauss::getHeight() const

Returns height. 
";

%feature("docstring")  FormFactorGauss::getRadius "double FormFactorGauss::getRadius() const

Returns width. 
";


// File: classFormFactorHemiEllipsoid.xml
%feature("docstring") FormFactorHemiEllipsoid "

The formfactor of an hemi ellipsoid.

C++ includes: FormFactorHemiEllipsoid.h
";

%feature("docstring")  FormFactorHemiEllipsoid::FormFactorHemiEllipsoid "FormFactorHemiEllipsoid::FormFactorHemiEllipsoid(double radius_x, double radius_y, double height)

Hemi Ellipsoid constructor.

Parameters:
-----------

radius_x: 
half length of one horizontal main axes

radius_y: 
half length of the other horizontal main axes

height: 
of Hemi Ellipsoid 
";

%feature("docstring")  FormFactorHemiEllipsoid::~FormFactorHemiEllipsoid "FormFactorHemiEllipsoid::~FormFactorHemiEllipsoid()
";

%feature("docstring")  FormFactorHemiEllipsoid::clone "FormFactorHemiEllipsoid * FormFactorHemiEllipsoid::clone() const

Returns a clone of this  ISample object. 
";

%feature("docstring")  FormFactorHemiEllipsoid::accept "void FormFactorHemiEllipsoid::accept(ISampleVisitor *visitor) const

Calls the  ISampleVisitor's visit method. 
";

%feature("docstring")  FormFactorHemiEllipsoid::getRadius "double FormFactorHemiEllipsoid::getRadius() const

Returns the (approximate in some cases) radial size of the particle of this form factor's shape. This is used for SSCA calculations 
";

%feature("docstring")  FormFactorHemiEllipsoid::getHeight "double FormFactorHemiEllipsoid::getHeight() const 
";

%feature("docstring")  FormFactorHemiEllipsoid::getRadiusX "double FormFactorHemiEllipsoid::getRadiusX() const 
";

%feature("docstring")  FormFactorHemiEllipsoid::getRadiusY "double FormFactorHemiEllipsoid::getRadiusY() const 
";

%feature("docstring")  FormFactorHemiEllipsoid::evaluate_for_q "complex_t FormFactorHemiEllipsoid::evaluate_for_q(const cvector_t &q) const

evaluate scattering amplitude for complex wavevector

Parameters:
-----------

q: 
wavevector transfer q=k_i-k_f 
";


// File: classFormFactorIcosahedron.xml
%feature("docstring") FormFactorIcosahedron "

The formfactor of a regular icosahedron.

C++ includes: FormFactorIcosahedron.h
";

%feature("docstring")  FormFactorIcosahedron::FormFactorIcosahedron "FormFactorIcosahedron::FormFactorIcosahedron(double edge)

Constructs a regular icosahedron.

Parameters:
-----------

edge: 
length 
";

%feature("docstring")  FormFactorIcosahedron::clone "FormFactorIcosahedron * FormFactorIcosahedron::clone() const final

Returns a clone of this  ISample object. 
";

%feature("docstring")  FormFactorIcosahedron::accept "void FormFactorIcosahedron::accept(ISampleVisitor *visitor) const final

Calls the  ISampleVisitor's visit method. 
";

%feature("docstring")  FormFactorIcosahedron::getRadius "double FormFactorIcosahedron::getRadius() const final

Returns the (approximate in some cases) radial size of the particle of this form factor's shape. This is used for SSCA calculations 
";

%feature("docstring")  FormFactorIcosahedron::getEdge "double FormFactorIcosahedron::getEdge() const 
";


// File: classFormFactorInfo.xml
%feature("docstring") FormFactorInfo "

The FormFactorInfo holds information about particle position and abundance.

C++ includes: LayerStrategyBuilder.h
";

%feature("docstring")  FormFactorInfo::FormFactorInfo "FormFactorInfo::FormFactorInfo()
";

%feature("docstring")  FormFactorInfo::~FormFactorInfo "FormFactorInfo::~FormFactorInfo()
";

%feature("docstring")  FormFactorInfo::clone "FormFactorInfo * FormFactorInfo::clone() const 
";


// File: classFormFactorLongBoxGauss.xml
%feature("docstring") FormFactorLongBoxGauss "";

%feature("docstring")  FormFactorLongBoxGauss::FormFactorLongBoxGauss "FormFactorLongBoxGauss::FormFactorLongBoxGauss(double length, double width, double height)

Box constructor.

Parameters:
-----------

length: 
of Box's base

width: 
of Box's base

height: 
of Box 
";

%feature("docstring")  FormFactorLongBoxGauss::clone "FormFactorLongBoxGauss * FormFactorLongBoxGauss::clone() const

Returns a clone of this  ISample object. 
";

%feature("docstring")  FormFactorLongBoxGauss::accept "void FormFactorLongBoxGauss::accept(ISampleVisitor *visitor) const

Calls the  ISampleVisitor's visit method. 
";

%feature("docstring")  FormFactorLongBoxGauss::getLength "double FormFactorLongBoxGauss::getLength() const

Returns length of Box. 
";

%feature("docstring")  FormFactorLongBoxGauss::getHeight "double FormFactorLongBoxGauss::getHeight() const

Returns height of Box. 
";

%feature("docstring")  FormFactorLongBoxGauss::getRadius "double FormFactorLongBoxGauss::getRadius() const

Returns radius of Box. 
";

%feature("docstring")  FormFactorLongBoxGauss::getWidth "double FormFactorLongBoxGauss::getWidth() const

Returns width of Box. 
";

%feature("docstring")  FormFactorLongBoxGauss::evaluate_for_q "complex_t FormFactorLongBoxGauss::evaluate_for_q(const cvector_t &q) const

evaluate scattering amplitude for complex wavevector

Parameters:
-----------

q: 
wavevector transfer q=k_i-k_f 
";


// File: classFormFactorLongBoxLorentz.xml
%feature("docstring") FormFactorLongBoxLorentz "";

%feature("docstring")  FormFactorLongBoxLorentz::FormFactorLongBoxLorentz "FormFactorLongBoxLorentz::FormFactorLongBoxLorentz(double length, double width, double height)

Box constructor.

Parameters:
-----------

length: 
of Box's base

width: 
of Box's base

height: 
of Box 
";

%feature("docstring")  FormFactorLongBoxLorentz::clone "FormFactorLongBoxLorentz * FormFactorLongBoxLorentz::clone() const

Returns a clone of this  ISample object. 
";

%feature("docstring")  FormFactorLongBoxLorentz::accept "void FormFactorLongBoxLorentz::accept(ISampleVisitor *visitor) const

Calls the  ISampleVisitor's visit method. 
";

%feature("docstring")  FormFactorLongBoxLorentz::getLength "double FormFactorLongBoxLorentz::getLength() const

Returns length of Box. 
";

%feature("docstring")  FormFactorLongBoxLorentz::getHeight "double FormFactorLongBoxLorentz::getHeight() const

Returns height of Box. 
";

%feature("docstring")  FormFactorLongBoxLorentz::getRadius "double FormFactorLongBoxLorentz::getRadius() const

Returns radius of Box. 
";

%feature("docstring")  FormFactorLongBoxLorentz::getWidth "double FormFactorLongBoxLorentz::getWidth() const

Returns width of Box. 
";

%feature("docstring")  FormFactorLongBoxLorentz::evaluate_for_q "complex_t FormFactorLongBoxLorentz::evaluate_for_q(const cvector_t &q) const

evaluate scattering amplitude for complex wavevector

Parameters:
-----------

q: 
wavevector transfer q=k_i-k_f 
";


// File: classFormFactorLongRipple1Gauss.xml
%feature("docstring") FormFactorLongRipple1Gauss "

The formfactor for a cosine ripple.

C++ includes: FormFactorLongRipple1Gauss.h
";

%feature("docstring")  FormFactorLongRipple1Gauss::FormFactorLongRipple1Gauss "FormFactorLongRipple1Gauss::FormFactorLongRipple1Gauss(double length, double width, double height)

Ripple1 constructor.

Parameters:
-----------

length: 
of Ripple1

width: 
of cosine cross section

height: 
of cosine cross section 
";

%feature("docstring")  FormFactorLongRipple1Gauss::~FormFactorLongRipple1Gauss "FormFactorLongRipple1Gauss::~FormFactorLongRipple1Gauss()
";

%feature("docstring")  FormFactorLongRipple1Gauss::clone "FormFactorLongRipple1Gauss * FormFactorLongRipple1Gauss::clone() const

Returns a clone of this  ISample object. 
";

%feature("docstring")  FormFactorLongRipple1Gauss::accept "void FormFactorLongRipple1Gauss::accept(ISampleVisitor *visitor) const

Calls the  ISampleVisitor's visit method. 
";

%feature("docstring")  FormFactorLongRipple1Gauss::getRadius "double FormFactorLongRipple1Gauss::getRadius() const

Returns the (approximate in some cases) radial size of the particle of this form factor's shape. This is used for SSCA calculations 
";

%feature("docstring")  FormFactorLongRipple1Gauss::getHeight "double FormFactorLongRipple1Gauss::getHeight() const 
";

%feature("docstring")  FormFactorLongRipple1Gauss::getWidth "double FormFactorLongRipple1Gauss::getWidth() const 
";

%feature("docstring")  FormFactorLongRipple1Gauss::getLength "double FormFactorLongRipple1Gauss::getLength() const 
";

%feature("docstring")  FormFactorLongRipple1Gauss::evaluate_for_q "complex_t FormFactorLongRipple1Gauss::evaluate_for_q(const cvector_t &q) const

Complex formfactor. 
";


// File: classFormFactorLongRipple1Lorentz.xml
%feature("docstring") FormFactorLongRipple1Lorentz "

The formfactor for a cosine ripple.

C++ includes: FormFactorLongRipple1Lorentz.h
";

%feature("docstring")  FormFactorLongRipple1Lorentz::FormFactorLongRipple1Lorentz "FormFactorLongRipple1Lorentz::FormFactorLongRipple1Lorentz(double length, double width, double height)

FormFactorLongRipple1Lorentz constructor.

Parameters:
-----------

length: 
of Ripple1

width: 
of cosine cross section

height: 
of cosine cross section 
";

%feature("docstring")  FormFactorLongRipple1Lorentz::~FormFactorLongRipple1Lorentz "FormFactorLongRipple1Lorentz::~FormFactorLongRipple1Lorentz()
";

%feature("docstring")  FormFactorLongRipple1Lorentz::clone "FormFactorLongRipple1Lorentz * FormFactorLongRipple1Lorentz::clone() const

Returns a clone of this  ISample object. 
";

%feature("docstring")  FormFactorLongRipple1Lorentz::accept "void FormFactorLongRipple1Lorentz::accept(ISampleVisitor *visitor) const

Calls the  ISampleVisitor's visit method. 
";

%feature("docstring")  FormFactorLongRipple1Lorentz::getRadius "double FormFactorLongRipple1Lorentz::getRadius() const

Returns the (approximate in some cases) radial size of the particle of this form factor's shape. This is used for SSCA calculations 
";

%feature("docstring")  FormFactorLongRipple1Lorentz::getHeight "double FormFactorLongRipple1Lorentz::getHeight() const 
";

%feature("docstring")  FormFactorLongRipple1Lorentz::getWidth "double FormFactorLongRipple1Lorentz::getWidth() const 
";

%feature("docstring")  FormFactorLongRipple1Lorentz::getLength "double FormFactorLongRipple1Lorentz::getLength() const 
";

%feature("docstring")  FormFactorLongRipple1Lorentz::evaluate_for_q "complex_t FormFactorLongRipple1Lorentz::evaluate_for_q(const cvector_t &q) const

Complex formfactor. 
";


// File: classFormFactorLongRipple2Gauss.xml
%feature("docstring") FormFactorLongRipple2Gauss "

The formfactor for a triangular ripple.

C++ includes: FormFactorLongRipple2Gauss.h
";

%feature("docstring")  FormFactorLongRipple2Gauss::FormFactorLongRipple2Gauss "FormFactorLongRipple2Gauss::FormFactorLongRipple2Gauss(double length, double width, double height, double asymetry)

FormFactorLongRipple2Gauss constructor.

Parameters:
-----------

length: 
of Ripple2

width: 
of triangular cross section

height: 
of triangular cross section

asymmetry: 
length of triangular cross section 
";

%feature("docstring")  FormFactorLongRipple2Gauss::~FormFactorLongRipple2Gauss "virtual FormFactorLongRipple2Gauss::~FormFactorLongRipple2Gauss()
";

%feature("docstring")  FormFactorLongRipple2Gauss::clone "FormFactorLongRipple2Gauss * FormFactorLongRipple2Gauss::clone() const

Returns a clone of this  ISample object. 
";

%feature("docstring")  FormFactorLongRipple2Gauss::accept "void FormFactorLongRipple2Gauss::accept(ISampleVisitor *visitor) const

Calls the  ISampleVisitor's visit method. 
";

%feature("docstring")  FormFactorLongRipple2Gauss::getRadius "double FormFactorLongRipple2Gauss::getRadius() const

Returns the (approximate in some cases) radial size of the particle of this form factor's shape. This is used for SSCA calculations 
";

%feature("docstring")  FormFactorLongRipple2Gauss::getHeight "double FormFactorLongRipple2Gauss::getHeight() const 
";

%feature("docstring")  FormFactorLongRipple2Gauss::getWidth "double FormFactorLongRipple2Gauss::getWidth() const 
";

%feature("docstring")  FormFactorLongRipple2Gauss::getLength "double FormFactorLongRipple2Gauss::getLength() const 
";

%feature("docstring")  FormFactorLongRipple2Gauss::getAsymmetry "double FormFactorLongRipple2Gauss::getAsymmetry() const 
";

%feature("docstring")  FormFactorLongRipple2Gauss::evaluate_for_q "complex_t FormFactorLongRipple2Gauss::evaluate_for_q(const cvector_t &q) const

Complex formfactor. 
";


// File: classFormFactorLongRipple2Lorentz.xml
%feature("docstring") FormFactorLongRipple2Lorentz "

The formfactor for a triangular ripple.

C++ includes: FormFactorLongRipple2Lorentz.h
";

%feature("docstring")  FormFactorLongRipple2Lorentz::FormFactorLongRipple2Lorentz "FormFactorLongRipple2Lorentz::FormFactorLongRipple2Lorentz(double length, double width, double height, double asymetry)

FormFactorLongRipple2Lorentz constructor.

Parameters:
-----------

length: 
of Ripple2

width: 
of triangular cross section

height: 
of triangular cross section

asymmetry: 
length of triangular cross section 
";

%feature("docstring")  FormFactorLongRipple2Lorentz::~FormFactorLongRipple2Lorentz "virtual FormFactorLongRipple2Lorentz::~FormFactorLongRipple2Lorentz()
";

%feature("docstring")  FormFactorLongRipple2Lorentz::clone "FormFactorLongRipple2Lorentz * FormFactorLongRipple2Lorentz::clone() const

Returns a clone of this  ISample object. 
";

%feature("docstring")  FormFactorLongRipple2Lorentz::accept "void FormFactorLongRipple2Lorentz::accept(ISampleVisitor *visitor) const

Calls the  ISampleVisitor's visit method. 
";

%feature("docstring")  FormFactorLongRipple2Lorentz::getRadius "double FormFactorLongRipple2Lorentz::getRadius() const

Returns the (approximate in some cases) radial size of the particle of this form factor's shape. This is used for SSCA calculations 
";

%feature("docstring")  FormFactorLongRipple2Lorentz::getHeight "double FormFactorLongRipple2Lorentz::getHeight() const 
";

%feature("docstring")  FormFactorLongRipple2Lorentz::getWidth "double FormFactorLongRipple2Lorentz::getWidth() const 
";

%feature("docstring")  FormFactorLongRipple2Lorentz::getLength "double FormFactorLongRipple2Lorentz::getLength() const 
";

%feature("docstring")  FormFactorLongRipple2Lorentz::getAsymmetry "double FormFactorLongRipple2Lorentz::getAsymmetry() const 
";

%feature("docstring")  FormFactorLongRipple2Lorentz::evaluate_for_q "complex_t FormFactorLongRipple2Lorentz::evaluate_for_q(const cvector_t &q) const

Complex formfactor. 
";


// File: classFormFactorLorentz.xml
%feature("docstring") FormFactorLorentz "

The formfactor of a lorentzian.

C++ includes: FormFactorLorentz.h
";

%feature("docstring")  FormFactorLorentz::FormFactorLorentz "FormFactorLorentz::FormFactorLorentz(double volume)
";

%feature("docstring")  FormFactorLorentz::FormFactorLorentz "FormFactorLorentz::FormFactorLorentz(double width, double height)
";

%feature("docstring")  FormFactorLorentz::clone "FormFactorLorentz * FormFactorLorentz::clone() const

Returns a clone of this  ISample object. 
";

%feature("docstring")  FormFactorLorentz::accept "void FormFactorLorentz::accept(ISampleVisitor *visitor) const

Calls the  ISampleVisitor's visit method. 
";

%feature("docstring")  FormFactorLorentz::getRadius "double FormFactorLorentz::getRadius() const

Returns the (approximate in some cases) radial size of the particle of this form factor's shape. This is used for SSCA calculations 
";

%feature("docstring")  FormFactorLorentz::getHeight "double FormFactorLorentz::getHeight() const

Returns height of shape. 
";

%feature("docstring")  FormFactorLorentz::getWidth "double FormFactorLorentz::getWidth() const

Returns width of shape. 
";

%feature("docstring")  FormFactorLorentz::evaluate_for_q "complex_t FormFactorLorentz::evaluate_for_q(const cvector_t &q) const

evaluate scattering amplitude for complex wavevector

Parameters:
-----------

q: 
wavevector transfer q=k_i-k_f 
";


// File: classFormFactorPolygonalPrism.xml
%feature("docstring") FormFactorPolygonalPrism "

A prism with a polygonal base, for form factor computation.

C++ includes: FormFactorPolyhedron.h
";

%feature("docstring")  FormFactorPolygonalPrism::FormFactorPolygonalPrism "FormFactorPolygonalPrism::FormFactorPolygonalPrism(const PolyhedralFace &_base, const double _height)
";

%feature("docstring")  FormFactorPolygonalPrism::evaluate_for_q "complex_t FormFactorPolygonalPrism::evaluate_for_q(const cvector_t &q) const final

Returns the form factor F(q) of this polyhedron, respecting the offset z_origin. 
";

%feature("docstring")  FormFactorPolygonalPrism::getVolume "double FormFactorPolygonalPrism::getVolume() const

Returns the volume of this prism. 
";

%feature("docstring")  FormFactorPolygonalPrism::getHeight "double FormFactorPolygonalPrism::getHeight() const

Returns the height of this prism. 
";


// File: classFormFactorPolyhedron.xml
%feature("docstring") FormFactorPolyhedron "

A polyhedron, for form factor computation.

C++ includes: FormFactorPolyhedron.h
";

%feature("docstring")  FormFactorPolyhedron::FormFactorPolyhedron "FormFactorPolyhedron::FormFactorPolyhedron(const std::vector< PolyhedralFace > &_faces, const double _z_origin, const bool _sym_Ci=false)
";

%feature("docstring")  FormFactorPolyhedron::evaluate_for_q "complex_t FormFactorPolyhedron::evaluate_for_q(const cvector_t &q) const final

Returns the form factor F(q) of this polyhedron, respecting the offset z_origin. 
";

%feature("docstring")  FormFactorPolyhedron::getVolume "double FormFactorPolyhedron::getVolume() const

Returns the total volume of the particle of this form factor's shape. 
";

%feature("docstring")  FormFactorPolyhedron::assert_platonic "void FormFactorPolyhedron::assert_platonic() const

Assertions for Platonic solid. 
";


// File: classFormFactorPrism3.xml
%feature("docstring") FormFactorPrism3 "

The formfactor of a prism based on an equilateral triangle.

C++ includes: FormFactorPrism3.h
";

%feature("docstring")  FormFactorPrism3::FormFactorPrism3 "FormFactorPrism3::FormFactorPrism3(const double length, const double height)

Prism3 constructor.

Parameters:
-----------

length: 
of hexagonal base (different from R in IsGisaxs)

height: 
of Prism3 
";

%feature("docstring")  FormFactorPrism3::clone "FormFactorPrism3 * FormFactorPrism3::clone() const

Returns a clone of this  ISample object. 
";

%feature("docstring")  FormFactorPrism3::accept "void FormFactorPrism3::accept(ISampleVisitor *visitor) const

Calls the  ISampleVisitor's visit method. 
";

%feature("docstring")  FormFactorPrism3::getRadius "double FormFactorPrism3::getRadius() const

Returns the (approximate in some cases) radial size of the particle of this form factor's shape. This is used for SSCA calculations 
";

%feature("docstring")  FormFactorPrism3::getLength "double FormFactorPrism3::getLength() const 
";


// File: classFormFactorPrism6.xml
%feature("docstring") FormFactorPrism6 "

The formfactor of a prism based on a regular hexagonal.

C++ includes: FormFactorPrism6.h
";

%feature("docstring")  FormFactorPrism6::FormFactorPrism6 "FormFactorPrism6::FormFactorPrism6(const double radius, const double height)

Prism6 constructor.

Parameters:
-----------

radius: 
of hexagonal base (different from R in IsGisaxs)

height: 
of Prism6 
";

%feature("docstring")  FormFactorPrism6::clone "FormFactorPrism6 * FormFactorPrism6::clone() const

Returns a clone of this  ISample object. 
";

%feature("docstring")  FormFactorPrism6::accept "void FormFactorPrism6::accept(ISampleVisitor *visitor) const

Calls the  ISampleVisitor's visit method. 
";

%feature("docstring")  FormFactorPrism6::getRadius "double FormFactorPrism6::getRadius() const

Returns the (approximate in some cases) radial size of the particle of this form factor's shape. This is used for SSCA calculations 
";


// File: classFormFactorPyramid.xml
%feature("docstring") FormFactorPyramid "

The formfactor of a cone6.

C++ includes: FormFactorPyramid.h
";

%feature("docstring")  FormFactorPyramid::FormFactorPyramid "FormFactorPyramid::FormFactorPyramid(double length, double height, double alpha)

Pyramid constructor.

Parameters:
-----------

length: 
of one side of Pyramid's square base

height: 
of Pyramid

angle: 
in radians between base and facet 
";

%feature("docstring")  FormFactorPyramid::clone "FormFactorPyramid * FormFactorPyramid::clone() const final

Returns a clone of this  ISample object. 
";

%feature("docstring")  FormFactorPyramid::accept "void FormFactorPyramid::accept(ISampleVisitor *visitor) const final

Calls the  ISampleVisitor's visit method. 
";

%feature("docstring")  FormFactorPyramid::getRadius "double FormFactorPyramid::getRadius() const final

Returns the (approximate in some cases) radial size of the particle of this form factor's shape. This is used for SSCA calculations 
";

%feature("docstring")  FormFactorPyramid::getHeight "double FormFactorPyramid::getHeight() const 
";

%feature("docstring")  FormFactorPyramid::getLength "double FormFactorPyramid::getLength() const 
";

%feature("docstring")  FormFactorPyramid::getAlpha "double FormFactorPyramid::getAlpha() const 
";


// File: classFormFactorRipple1.xml
%feature("docstring") FormFactorRipple1 "

The formfactor for a cosine ripple.

C++ includes: FormFactorRipple1.h
";

%feature("docstring")  FormFactorRipple1::FormFactorRipple1 "FormFactorRipple1::FormFactorRipple1(double length, double width, double height)

Ripple1 constructor.

Parameters:
-----------

length: 
of Ripple1

width: 
of cosine cross section

height: 
of cosine cross section 
";

%feature("docstring")  FormFactorRipple1::~FormFactorRipple1 "FormFactorRipple1::~FormFactorRipple1()
";

%feature("docstring")  FormFactorRipple1::clone "FormFactorRipple1 * FormFactorRipple1::clone() const

Returns a clone of this  ISample object. 
";

%feature("docstring")  FormFactorRipple1::accept "void FormFactorRipple1::accept(ISampleVisitor *visitor) const

Calls the  ISampleVisitor's visit method. 
";

%feature("docstring")  FormFactorRipple1::getRadius "double FormFactorRipple1::getRadius() const

Returns the (approximate in some cases) radial size of the particle of this form factor's shape. This is used for SSCA calculations 
";

%feature("docstring")  FormFactorRipple1::getHeight "double FormFactorRipple1::getHeight() const 
";

%feature("docstring")  FormFactorRipple1::getWidth "double FormFactorRipple1::getWidth() const 
";

%feature("docstring")  FormFactorRipple1::getLength "double FormFactorRipple1::getLength() const 
";

%feature("docstring")  FormFactorRipple1::evaluate_for_q "complex_t FormFactorRipple1::evaluate_for_q(const cvector_t &q) const

Complex formfactor. 
";


// File: classFormFactorRipple2.xml
%feature("docstring") FormFactorRipple2 "

The formfactor for a triangular ripple.

C++ includes: FormFactorRipple2.h
";

%feature("docstring")  FormFactorRipple2::FormFactorRipple2 "FormFactorRipple2::FormFactorRipple2(double length, double width, double height, double asymetry)

Ripple2 constructor.

Parameters:
-----------

length: 
of Ripple2

width: 
of triangular cross section

height: 
of triangular cross section

asymmetry: 
length of triangular cross section 
";

%feature("docstring")  FormFactorRipple2::~FormFactorRipple2 "virtual FormFactorRipple2::~FormFactorRipple2()
";

%feature("docstring")  FormFactorRipple2::clone "FormFactorRipple2 * FormFactorRipple2::clone() const

Returns a clone of this  ISample object. 
";

%feature("docstring")  FormFactorRipple2::accept "void FormFactorRipple2::accept(ISampleVisitor *visitor) const

Calls the  ISampleVisitor's visit method. 
";

%feature("docstring")  FormFactorRipple2::getRadius "double FormFactorRipple2::getRadius() const

Returns the (approximate in some cases) radial size of the particle of this form factor's shape. This is used for SSCA calculations 
";

%feature("docstring")  FormFactorRipple2::getHeight "double FormFactorRipple2::getHeight() const 
";

%feature("docstring")  FormFactorRipple2::getWidth "double FormFactorRipple2::getWidth() const 
";

%feature("docstring")  FormFactorRipple2::getLength "double FormFactorRipple2::getLength() const 
";

%feature("docstring")  FormFactorRipple2::getAsymmetry "double FormFactorRipple2::getAsymmetry() const 
";

%feature("docstring")  FormFactorRipple2::evaluate_for_q "complex_t FormFactorRipple2::evaluate_for_q(const cvector_t &q) const

Complex formfactor. 
";


// File: classFormFactorSphereGaussianRadius.xml
%feature("docstring") FormFactorSphereGaussianRadius "

The formfactor of sphere with gaussian radius distribution.

C++ includes: FormFactorSphereGaussianRadius.h
";

%feature("docstring")  FormFactorSphereGaussianRadius::FormFactorSphereGaussianRadius "FormFactorSphereGaussianRadius::FormFactorSphereGaussianRadius(double mean, double sigma)
";

%feature("docstring")  FormFactorSphereGaussianRadius::clone "FormFactorSphereGaussianRadius * FormFactorSphereGaussianRadius::clone() const

Returns a clone of this  ISample object. 
";

%feature("docstring")  FormFactorSphereGaussianRadius::~FormFactorSphereGaussianRadius "FormFactorSphereGaussianRadius::~FormFactorSphereGaussianRadius()
";

%feature("docstring")  FormFactorSphereGaussianRadius::accept "void FormFactorSphereGaussianRadius::accept(ISampleVisitor *visitor) const

Calls the  ISampleVisitor's visit method. 
";

%feature("docstring")  FormFactorSphereGaussianRadius::getRadius "double FormFactorSphereGaussianRadius::getRadius() const

Returns the (approximate in some cases) radial size of the particle of this form factor's shape. This is used for SSCA calculations 
";

%feature("docstring")  FormFactorSphereGaussianRadius::evaluate_for_q "complex_t FormFactorSphereGaussianRadius::evaluate_for_q(const cvector_t &q) const

evaluate scattering amplitude for complex wavevector

Parameters:
-----------

q: 
wavevector transfer q=k_i-k_f 
";


// File: classFormFactorSphereLogNormalRadius.xml
%feature("docstring") FormFactorSphereLogNormalRadius "

The formfactor of sphere with log normal radius distribution.

C++ includes: FormFactorSphereLogNormalRadius.h
";

%feature("docstring")  FormFactorSphereLogNormalRadius::FormFactorSphereLogNormalRadius "FormFactorSphereLogNormalRadius::FormFactorSphereLogNormalRadius(double mean, double scale_param, size_t n_samples)
";

%feature("docstring")  FormFactorSphereLogNormalRadius::clone "FormFactorSphereLogNormalRadius * FormFactorSphereLogNormalRadius::clone() const

Returns a clone of this  ISample object. 
";

%feature("docstring")  FormFactorSphereLogNormalRadius::~FormFactorSphereLogNormalRadius "FormFactorSphereLogNormalRadius::~FormFactorSphereLogNormalRadius()
";

%feature("docstring")  FormFactorSphereLogNormalRadius::accept "void FormFactorSphereLogNormalRadius::accept(ISampleVisitor *visitor) const

Calls the  ISampleVisitor's visit method. 
";

%feature("docstring")  FormFactorSphereLogNormalRadius::getRadius "double FormFactorSphereLogNormalRadius::getRadius() const

Returns the (approximate in some cases) radial size of the particle of this form factor's shape. This is used for SSCA calculations 
";

%feature("docstring")  FormFactorSphereLogNormalRadius::evaluate_for_q "complex_t FormFactorSphereLogNormalRadius::evaluate_for_q(const cvector_t &q) const

evaluate scattering amplitude for complex wavevector

Parameters:
-----------

q: 
wavevector transfer q=k_i-k_f 
";


// File: classFormFactorSphereUniformRadius.xml
%feature("docstring") FormFactorSphereUniformRadius "

Integrated full sphere form factor over a uniform distribution of radii.

C++ includes: FormFactorSphereUniformRadius.h
";

%feature("docstring")  FormFactorSphereUniformRadius::FormFactorSphereUniformRadius "FormFactorSphereUniformRadius::FormFactorSphereUniformRadius(double mean, double full_width)
";

%feature("docstring")  FormFactorSphereUniformRadius::clone "FormFactorSphereUniformRadius * FormFactorSphereUniformRadius::clone() const

Returns a clone of this  ISample object. 
";

%feature("docstring")  FormFactorSphereUniformRadius::~FormFactorSphereUniformRadius "FormFactorSphereUniformRadius::~FormFactorSphereUniformRadius()
";

%feature("docstring")  FormFactorSphereUniformRadius::accept "void FormFactorSphereUniformRadius::accept(ISampleVisitor *visitor) const

Calls the  ISampleVisitor's visit method. 
";

%feature("docstring")  FormFactorSphereUniformRadius::getRadius "double FormFactorSphereUniformRadius::getRadius() const

Returns the (approximate in some cases) radial size of the particle of this form factor's shape. This is used for SSCA calculations 
";

%feature("docstring")  FormFactorSphereUniformRadius::evaluate_for_q "complex_t FormFactorSphereUniformRadius::evaluate_for_q(const cvector_t &q) const

evaluate scattering amplitude for complex wavevector

Parameters:
-----------

q: 
wavevector transfer q=k_i-k_f 
";


// File: classFormFactorTetrahedron.xml
%feature("docstring") FormFactorTetrahedron "

The formfactor of tetrahedron.

C++ includes: FormFactorTetrahedron.h
";

%feature("docstring")  FormFactorTetrahedron::FormFactorTetrahedron "FormFactorTetrahedron::FormFactorTetrahedron(double length, double height, double alpha)

Tetrahedron constructor.

Parameters:
-----------

length: 
of a side of Tetrahedron's base

height: 
of Tetrahedron

angle: 
in radians between base and facet 
";

%feature("docstring")  FormFactorTetrahedron::~FormFactorTetrahedron "FormFactorTetrahedron::~FormFactorTetrahedron()
";

%feature("docstring")  FormFactorTetrahedron::clone "FormFactorTetrahedron * FormFactorTetrahedron::clone() const

Returns a clone of this  ISample object. 
";

%feature("docstring")  FormFactorTetrahedron::accept "void FormFactorTetrahedron::accept(ISampleVisitor *visitor) const

Calls the  ISampleVisitor's visit method. 
";

%feature("docstring")  FormFactorTetrahedron::getRadius "double FormFactorTetrahedron::getRadius() const

Returns the (approximate in some cases) radial size of the particle of this form factor's shape. This is used for SSCA calculations 
";

%feature("docstring")  FormFactorTetrahedron::getHeight "double FormFactorTetrahedron::getHeight() const 
";

%feature("docstring")  FormFactorTetrahedron::getLength "double FormFactorTetrahedron::getLength() const 
";

%feature("docstring")  FormFactorTetrahedron::getAlpha "double FormFactorTetrahedron::getAlpha() const 
";


// File: classFormFactorTrivial.xml
%feature("docstring") FormFactorTrivial "";

%feature("docstring")  FormFactorTrivial::FormFactorTrivial "FormFactorTrivial::FormFactorTrivial()

Cylinder constructor.

Parameters:
-----------

radius: 
of Cylinder's base

height: 
of Cylinder 
";

%feature("docstring")  FormFactorTrivial::clone "FormFactorTrivial * FormFactorTrivial::clone() const

Returns a clone of this  ISample object. 
";

%feature("docstring")  FormFactorTrivial::accept "void FormFactorTrivial::accept(ISampleVisitor *visitor) const

Calls the  ISampleVisitor's visit method. 
";

%feature("docstring")  FormFactorTrivial::getRadius "double FormFactorTrivial::getRadius() const

Returns the (approximate in some cases) radial size of the particle of this form factor's shape. This is used for SSCA calculations 
";

%feature("docstring")  FormFactorTrivial::evaluate_for_q "complex_t FormFactorTrivial::evaluate_for_q(const cvector_t &q) const

evaluate scattering amplitude for complex wavevector

Parameters:
-----------

q: 
wavevector transfer q=k_i-k_f 
";


// File: classFormFactorTruncatedCube.xml
%feature("docstring") FormFactorTruncatedCube "

The formfactor of a truncated cube.

C++ includes: FormFactorTruncatedCube.h
";

%feature("docstring")  FormFactorTruncatedCube::FormFactorTruncatedCube "FormFactorTruncatedCube::FormFactorTruncatedCube(double length, double removed_length)

Truncated cube constructor.

Parameters:
-----------

side: 
length of the full cube

side: 
length of the trirectangular tetrahedron removed from each vertex of the cube 
";

%feature("docstring")  FormFactorTruncatedCube::clone "FormFactorTruncatedCube * FormFactorTruncatedCube::clone() const final

Returns a clone of this  ISample object. 
";

%feature("docstring")  FormFactorTruncatedCube::accept "void FormFactorTruncatedCube::accept(ISampleVisitor *visitor) const final

Calls the  ISampleVisitor's visit method. 
";

%feature("docstring")  FormFactorTruncatedCube::getRadius "double FormFactorTruncatedCube::getRadius() const final

Returns the (approximate in some cases) radial size of the particle of this form factor's shape. This is used for SSCA calculations 
";

%feature("docstring")  FormFactorTruncatedCube::getLength "double FormFactorTruncatedCube::getLength() const 
";

%feature("docstring")  FormFactorTruncatedCube::getRemovedLength "double FormFactorTruncatedCube::getRemovedLength() const 
";


// File: classFormFactorTruncatedSphere.xml
%feature("docstring") FormFactorTruncatedSphere "

The formfactor of a truncated Sphere.

C++ includes: FormFactorTruncatedSphere.h
";

%feature("docstring")  FormFactorTruncatedSphere::FormFactorTruncatedSphere "FormFactorTruncatedSphere::FormFactorTruncatedSphere(double radius, double height)

TruncatedSphere constructor.

Parameters:
-----------

radius: 
of Truncated Sphere

height: 
of Truncated Sphere 
";

%feature("docstring")  FormFactorTruncatedSphere::~FormFactorTruncatedSphere "FormFactorTruncatedSphere::~FormFactorTruncatedSphere()
";

%feature("docstring")  FormFactorTruncatedSphere::clone "FormFactorTruncatedSphere * FormFactorTruncatedSphere::clone() const

Returns a clone of this  ISample object. 
";

%feature("docstring")  FormFactorTruncatedSphere::accept "void FormFactorTruncatedSphere::accept(ISampleVisitor *visitor) const

Calls the  ISampleVisitor's visit method. 
";

%feature("docstring")  FormFactorTruncatedSphere::getRadius "double FormFactorTruncatedSphere::getRadius() const

Returns the (approximate in some cases) radial size of the particle of this form factor's shape. This is used for SSCA calculations 
";

%feature("docstring")  FormFactorTruncatedSphere::getHeight "double FormFactorTruncatedSphere::getHeight() const 
";


// File: classFormFactorTruncatedSpheroid.xml
%feature("docstring") FormFactorTruncatedSpheroid "

The formfactor of a truncated spheroid.

C++ includes: FormFactorTruncatedSpheroid.h
";

%feature("docstring")  FormFactorTruncatedSpheroid::FormFactorTruncatedSpheroid "FormFactorTruncatedSpheroid::FormFactorTruncatedSpheroid(double radius, double height, double height_flattening)

TruncatedSpheroid constructor.

Parameters:
-----------

radius: 
of Truncated Spheroid

height: 
of Truncated Spheroid

flattening: 
parameter in vertical direction (full height: 2 x flattening x radius) 
";

%feature("docstring")  FormFactorTruncatedSpheroid::~FormFactorTruncatedSpheroid "FormFactorTruncatedSpheroid::~FormFactorTruncatedSpheroid()
";

%feature("docstring")  FormFactorTruncatedSpheroid::clone "FormFactorTruncatedSpheroid * FormFactorTruncatedSpheroid::clone() const

Returns a clone of this  ISample object. 
";

%feature("docstring")  FormFactorTruncatedSpheroid::accept "void FormFactorTruncatedSpheroid::accept(ISampleVisitor *visitor) const

Calls the  ISampleVisitor's visit method. 
";

%feature("docstring")  FormFactorTruncatedSpheroid::getHeight "double FormFactorTruncatedSpheroid::getHeight() const 
";

%feature("docstring")  FormFactorTruncatedSpheroid::getHeightFlattening "double FormFactorTruncatedSpheroid::getHeightFlattening() const 
";

%feature("docstring")  FormFactorTruncatedSpheroid::getRadius "double FormFactorTruncatedSpheroid::getRadius() const

Returns the (approximate in some cases) radial size of the particle of this form factor's shape. This is used for SSCA calculations 
";

%feature("docstring")  FormFactorTruncatedSpheroid::evaluate_for_q "complex_t FormFactorTruncatedSpheroid::evaluate_for_q(const cvector_t &q) const

evaluate scattering amplitude for complex wavevector

Parameters:
-----------

q: 
wavevector transfer q=k_i-k_f 
";


// File: classFormFactorWeighted.xml
%feature("docstring") FormFactorWeighted "

Coherent sum of different form factors with different weights. Acts on scalar form factors.

C++ includes: FormFactorWeighted.h
";

%feature("docstring")  FormFactorWeighted::FormFactorWeighted "FormFactorWeighted::FormFactorWeighted()
";

%feature("docstring")  FormFactorWeighted::~FormFactorWeighted "FormFactorWeighted::~FormFactorWeighted()
";

%feature("docstring")  FormFactorWeighted::clone "FormFactorWeighted * FormFactorWeighted::clone() const

Returns a clone of this  ISample object. 
";

%feature("docstring")  FormFactorWeighted::accept "void FormFactorWeighted::accept(ISampleVisitor *visitor) const

Calls the  ISampleVisitor's visit method. 
";

%feature("docstring")  FormFactorWeighted::getRadius "double FormFactorWeighted::getRadius() const

Returns the (approximate in some cases) radial size of the particle of this form factor's shape. This is used for SSCA calculations 
";

%feature("docstring")  FormFactorWeighted::addFormFactor "void FormFactorWeighted::addFormFactor(const IFormFactor &form_factor, double weight=1.0)
";

%feature("docstring")  FormFactorWeighted::setAmbientMaterial "void FormFactorWeighted::setAmbientMaterial(const IMaterial &material)

Passes the refractive index of the ambient material in which this particle is embedded. 
";

%feature("docstring")  FormFactorWeighted::evaluate "complex_t FormFactorWeighted::evaluate(const WavevectorInfo &wavevectors) const

Returns scattering amplitude for complex wavevector bin

Parameters:
-----------

k_i: 
incoming wavevector

k_f_bin: 
outgoing wavevector bin 
";

%feature("docstring")  FormFactorWeighted::evaluatePol "Eigen::Matrix2cd FormFactorWeighted::evaluatePol(const WavevectorInfo &wavevectors) const

Calculates and returns a polarized form factor calculation in DWBA. 
";


// File: classFTDecayFunction1DCauchy.xml
%feature("docstring") FTDecayFunction1DCauchy "

1 dimensional Cauchy decay function in reciprocal space. Corresponds to exp(-|x|/omega) in real space

C++ includes: FTDecayFunctions.h
";

%feature("docstring")  FTDecayFunction1DCauchy::FTDecayFunction1DCauchy "FTDecayFunction1DCauchy::FTDecayFunction1DCauchy(double omega)
";

%feature("docstring")  FTDecayFunction1DCauchy::~FTDecayFunction1DCauchy "virtual FTDecayFunction1DCauchy::~FTDecayFunction1DCauchy()
";

%feature("docstring")  FTDecayFunction1DCauchy::clone "FTDecayFunction1DCauchy * FTDecayFunction1DCauchy::clone() const 
";

%feature("docstring")  FTDecayFunction1DCauchy::evaluate "double FTDecayFunction1DCauchy::evaluate(double q) const 
";


// File: classFTDecayFunction1DGauss.xml
%feature("docstring") FTDecayFunction1DGauss "

1 dimensional Gauss decay function in reciprocal space. Corresponds to exp[-x^2/(2*omega^2)] in real space

C++ includes: FTDecayFunctions.h
";

%feature("docstring")  FTDecayFunction1DGauss::FTDecayFunction1DGauss "FTDecayFunction1DGauss::FTDecayFunction1DGauss(double omega)
";

%feature("docstring")  FTDecayFunction1DGauss::~FTDecayFunction1DGauss "virtual FTDecayFunction1DGauss::~FTDecayFunction1DGauss()
";

%feature("docstring")  FTDecayFunction1DGauss::clone "FTDecayFunction1DGauss * FTDecayFunction1DGauss::clone() const 
";

%feature("docstring")  FTDecayFunction1DGauss::evaluate "double FTDecayFunction1DGauss::evaluate(double q) const 
";


// File: classFTDecayFunction1DTriangle.xml
%feature("docstring") FTDecayFunction1DTriangle "

1 dimensional triangle decay function in reciprocal space. Corresponds to 1-|x|/omega if |x|<omega (and 0 otherwise) in real space

C++ includes: FTDecayFunctions.h
";

%feature("docstring")  FTDecayFunction1DTriangle::FTDecayFunction1DTriangle "FTDecayFunction1DTriangle::FTDecayFunction1DTriangle(double omega)
";

%feature("docstring")  FTDecayFunction1DTriangle::~FTDecayFunction1DTriangle "virtual FTDecayFunction1DTriangle::~FTDecayFunction1DTriangle()
";

%feature("docstring")  FTDecayFunction1DTriangle::clone "FTDecayFunction1DTriangle * FTDecayFunction1DTriangle::clone() const 
";

%feature("docstring")  FTDecayFunction1DTriangle::evaluate "double FTDecayFunction1DTriangle::evaluate(double q) const 
";


// File: classFTDecayFunction1DVoigt.xml
%feature("docstring") FTDecayFunction1DVoigt "

1 dimensional Voigt decay function in reciprocal space. Corresponds to eta*Gauss + (1-eta)*Cauchy

C++ includes: FTDecayFunctions.h
";

%feature("docstring")  FTDecayFunction1DVoigt::FTDecayFunction1DVoigt "FTDecayFunction1DVoigt::FTDecayFunction1DVoigt(double omega, double eta)
";

%feature("docstring")  FTDecayFunction1DVoigt::~FTDecayFunction1DVoigt "virtual FTDecayFunction1DVoigt::~FTDecayFunction1DVoigt()
";

%feature("docstring")  FTDecayFunction1DVoigt::clone "FTDecayFunction1DVoigt * FTDecayFunction1DVoigt::clone() const 
";

%feature("docstring")  FTDecayFunction1DVoigt::evaluate "double FTDecayFunction1DVoigt::evaluate(double q) const 
";

%feature("docstring")  FTDecayFunction1DVoigt::getEta "virtual double FTDecayFunction1DVoigt::getEta() const 
";


// File: classFTDecayFunction2DCauchy.xml
%feature("docstring") FTDecayFunction2DCauchy "

2 dimensional Cauchy decay function in reciprocal space. Corresponds to exp(-r) in real space with  $r=\\\\sqrt{(\\\\frac{x}{\\\\omega_x})^2 + (\\\\frac{y}{\\\\omega_y})^2}$

C++ includes: FTDecayFunctions.h
";

%feature("docstring")  FTDecayFunction2DCauchy::FTDecayFunction2DCauchy "FTDecayFunction2DCauchy::FTDecayFunction2DCauchy(double decay_length_x, double decay_length_y)
";

%feature("docstring")  FTDecayFunction2DCauchy::~FTDecayFunction2DCauchy "virtual FTDecayFunction2DCauchy::~FTDecayFunction2DCauchy()
";

%feature("docstring")  FTDecayFunction2DCauchy::clone "FTDecayFunction2DCauchy * FTDecayFunction2DCauchy::clone() const 
";

%feature("docstring")  FTDecayFunction2DCauchy::evaluate "double FTDecayFunction2DCauchy::evaluate(double qx, double qy) const

evaluate Fourier transformed decay function for q in X,Y coordinates 
";


// File: classFTDecayFunction2DGauss.xml
%feature("docstring") FTDecayFunction2DGauss "

2 dimensional Gauss decay function in reciprocal space. Corresponds to exp(-r^2/2) in real space with  $r=\\\\sqrt{(\\\\frac{x}{\\\\omega_x})^2 + (\\\\frac{y}{\\\\omega_y})^2}$

C++ includes: FTDecayFunctions.h
";

%feature("docstring")  FTDecayFunction2DGauss::FTDecayFunction2DGauss "FTDecayFunction2DGauss::FTDecayFunction2DGauss(double decay_length_x, double decay_length_y)
";

%feature("docstring")  FTDecayFunction2DGauss::~FTDecayFunction2DGauss "virtual FTDecayFunction2DGauss::~FTDecayFunction2DGauss()
";

%feature("docstring")  FTDecayFunction2DGauss::clone "FTDecayFunction2DGauss * FTDecayFunction2DGauss::clone() const 
";

%feature("docstring")  FTDecayFunction2DGauss::evaluate "double FTDecayFunction2DGauss::evaluate(double qx, double qy) const

evaluate Fourier transformed decay function for q in X,Y coordinates 
";


// File: classFTDecayFunction2DVoigt.xml
%feature("docstring") FTDecayFunction2DVoigt "

2 dimensional Voigt decay function in reciprocal space. Corresponds to eta*Gauss + (1-eta)*Cauchy

C++ includes: FTDecayFunctions.h
";

%feature("docstring")  FTDecayFunction2DVoigt::FTDecayFunction2DVoigt "FTDecayFunction2DVoigt::FTDecayFunction2DVoigt(double decay_length_x, double decay_length_y, double eta)
";

%feature("docstring")  FTDecayFunction2DVoigt::~FTDecayFunction2DVoigt "virtual FTDecayFunction2DVoigt::~FTDecayFunction2DVoigt()
";

%feature("docstring")  FTDecayFunction2DVoigt::clone "FTDecayFunction2DVoigt * FTDecayFunction2DVoigt::clone() const 
";

%feature("docstring")  FTDecayFunction2DVoigt::evaluate "double FTDecayFunction2DVoigt::evaluate(double qx, double qy) const

evaluate Fourier transformed decay function for q in X,Y coordinates 
";

%feature("docstring")  FTDecayFunction2DVoigt::getEta "virtual double FTDecayFunction2DVoigt::getEta() const 
";


// File: classFTDistribution1DCauchy.xml
%feature("docstring") FTDistribution1DCauchy "

1 dimensional Cauchy distribution in Fourier space. Corresponds to a normalized exp(-|x|) in real space

C++ includes: FTDistributions.h
";

%feature("docstring")  FTDistribution1DCauchy::FTDistribution1DCauchy "FTDistribution1DCauchy::FTDistribution1DCauchy(double omega)
";

%feature("docstring")  FTDistribution1DCauchy::~FTDistribution1DCauchy "virtual FTDistribution1DCauchy::~FTDistribution1DCauchy()
";

%feature("docstring")  FTDistribution1DCauchy::clone "FTDistribution1DCauchy * FTDistribution1DCauchy::clone() const 
";

%feature("docstring")  FTDistribution1DCauchy::evaluate "double FTDistribution1DCauchy::evaluate(double q) const 
";


// File: classFTDistribution1DCosine.xml
%feature("docstring") FTDistribution1DCosine "

1 dimensional triangle distribution in Fourier space. Corresponds to a normalized 1+cos(pi*x/omega) if |x|<omega (and 0 otherwise) in real space

C++ includes: FTDistributions.h
";

%feature("docstring")  FTDistribution1DCosine::FTDistribution1DCosine "FTDistribution1DCosine::FTDistribution1DCosine(double omega)
";

%feature("docstring")  FTDistribution1DCosine::~FTDistribution1DCosine "virtual FTDistribution1DCosine::~FTDistribution1DCosine()
";

%feature("docstring")  FTDistribution1DCosine::clone "FTDistribution1DCosine * FTDistribution1DCosine::clone() const 
";

%feature("docstring")  FTDistribution1DCosine::evaluate "double FTDistribution1DCosine::evaluate(double q) const 
";


// File: classFTDistribution1DGate.xml
%feature("docstring") FTDistribution1DGate "

1 dimensional Gate distribution in Fourier space. Corresponds to a normalized constant if |x|<omega (and 0 otherwise) in real space

C++ includes: FTDistributions.h
";

%feature("docstring")  FTDistribution1DGate::FTDistribution1DGate "FTDistribution1DGate::FTDistribution1DGate(double omega)
";

%feature("docstring")  FTDistribution1DGate::~FTDistribution1DGate "virtual FTDistribution1DGate::~FTDistribution1DGate()
";

%feature("docstring")  FTDistribution1DGate::clone "FTDistribution1DGate * FTDistribution1DGate::clone() const 
";

%feature("docstring")  FTDistribution1DGate::evaluate "double FTDistribution1DGate::evaluate(double q) const 
";


// File: classFTDistribution1DGauss.xml
%feature("docstring") FTDistribution1DGauss "

1 dimensional Gauss distribution in Fourier space. Corresponds to a normalized exp(-x^2) in real space

C++ includes: FTDistributions.h
";

%feature("docstring")  FTDistribution1DGauss::FTDistribution1DGauss "FTDistribution1DGauss::FTDistribution1DGauss(double omega)
";

%feature("docstring")  FTDistribution1DGauss::~FTDistribution1DGauss "virtual FTDistribution1DGauss::~FTDistribution1DGauss()
";

%feature("docstring")  FTDistribution1DGauss::clone "FTDistribution1DGauss * FTDistribution1DGauss::clone() const 
";

%feature("docstring")  FTDistribution1DGauss::evaluate "double FTDistribution1DGauss::evaluate(double q) const 
";


// File: classFTDistribution1DTriangle.xml
%feature("docstring") FTDistribution1DTriangle "

1 dimensional triangle distribution in Fourier space. Corresponds to a normalized 1-|x|/omega if |x|<omega (and 0 otherwise) in real space

C++ includes: FTDistributions.h
";

%feature("docstring")  FTDistribution1DTriangle::FTDistribution1DTriangle "FTDistribution1DTriangle::FTDistribution1DTriangle(double omega)
";

%feature("docstring")  FTDistribution1DTriangle::~FTDistribution1DTriangle "virtual FTDistribution1DTriangle::~FTDistribution1DTriangle()
";

%feature("docstring")  FTDistribution1DTriangle::clone "FTDistribution1DTriangle * FTDistribution1DTriangle::clone() const 
";

%feature("docstring")  FTDistribution1DTriangle::evaluate "double FTDistribution1DTriangle::evaluate(double q) const 
";


// File: classFTDistribution1DVoigt.xml
%feature("docstring") FTDistribution1DVoigt "

1 dimensional Voigt distribution in Fourier space. Corresponds to eta*Gauss + (1-eta)*Cauchy

C++ includes: FTDistributions.h
";

%feature("docstring")  FTDistribution1DVoigt::FTDistribution1DVoigt "FTDistribution1DVoigt::FTDistribution1DVoigt(double omega, double eta)
";

%feature("docstring")  FTDistribution1DVoigt::~FTDistribution1DVoigt "virtual FTDistribution1DVoigt::~FTDistribution1DVoigt()
";

%feature("docstring")  FTDistribution1DVoigt::clone "FTDistribution1DVoigt * FTDistribution1DVoigt::clone() const 
";

%feature("docstring")  FTDistribution1DVoigt::evaluate "double FTDistribution1DVoigt::evaluate(double q) const 
";

%feature("docstring")  FTDistribution1DVoigt::getEta "virtual double FTDistribution1DVoigt::getEta() const 
";


// File: classFTDistribution2DCauchy.xml
%feature("docstring") FTDistribution2DCauchy "

2 dimensional Cauchy distribution in Fourier space. Corresponds to a normalized exp(-r) in real space with  $r=\\\\sqrt{(\\\\frac{x}{\\\\omega_x})^2 + (\\\\frac{y}{\\\\omega_y})^2}$

C++ includes: FTDistributions.h
";

%feature("docstring")  FTDistribution2DCauchy::FTDistribution2DCauchy "FTDistribution2DCauchy::FTDistribution2DCauchy(double coherence_length_x, double coherence_length_y)
";

%feature("docstring")  FTDistribution2DCauchy::~FTDistribution2DCauchy "virtual FTDistribution2DCauchy::~FTDistribution2DCauchy()
";

%feature("docstring")  FTDistribution2DCauchy::clone "FTDistribution2DCauchy * FTDistribution2DCauchy::clone() const 
";

%feature("docstring")  FTDistribution2DCauchy::evaluate "double FTDistribution2DCauchy::evaluate(double qx, double qy) const

evaluate Fourier transformed distribution for q in X,Y coordinates the original distribution (in real space) is assumed to be normalized: total integral is equal to 1 
";


// File: classFTDistribution2DCone.xml
%feature("docstring") FTDistribution2DCone "

2 dimensional cone distribution in Fourier space. Corresponds to 1-r if r<1 (and 0 otherwise) in real space with  $r=\\\\sqrt{(\\\\frac{x}{\\\\omega_x})^2 + (\\\\frac{y}{\\\\omega_y})^2}$

C++ includes: FTDistributions.h
";

%feature("docstring")  FTDistribution2DCone::FTDistribution2DCone "FTDistribution2DCone::FTDistribution2DCone(double coherence_length_x, double coherence_length_y)
";

%feature("docstring")  FTDistribution2DCone::~FTDistribution2DCone "virtual FTDistribution2DCone::~FTDistribution2DCone()
";

%feature("docstring")  FTDistribution2DCone::clone "FTDistribution2DCone * FTDistribution2DCone::clone() const 
";

%feature("docstring")  FTDistribution2DCone::evaluate "double FTDistribution2DCone::evaluate(double qx, double qy) const

evaluate Fourier transformed distribution for q in X,Y coordinates the original distribution (in real space) is assumed to be normalized: total integral is equal to 1 
";


// File: classFTDistribution2DGate.xml
%feature("docstring") FTDistribution2DGate "

2 dimensional gate distribution in Fourier space Corresponds to normalized constant if r<1 (and 0 otherwise) in real space. with  $r=\\\\sqrt{(\\\\frac{x}{\\\\omega_x})^2 + (\\\\frac{y}{\\\\omega_y})^2}$

C++ includes: FTDistributions.h
";

%feature("docstring")  FTDistribution2DGate::FTDistribution2DGate "FTDistribution2DGate::FTDistribution2DGate(double coherence_length_x, double coherence_length_y)
";

%feature("docstring")  FTDistribution2DGate::~FTDistribution2DGate "virtual FTDistribution2DGate::~FTDistribution2DGate()
";

%feature("docstring")  FTDistribution2DGate::clone "FTDistribution2DGate * FTDistribution2DGate::clone() const 
";

%feature("docstring")  FTDistribution2DGate::evaluate "double FTDistribution2DGate::evaluate(double qx, double qy) const

evaluate Fourier transformed distribution for q in X,Y coordinates the original distribution (in real space) is assumed to be normalized: total integral is equal to 1 
";


// File: classFTDistribution2DGauss.xml
%feature("docstring") FTDistribution2DGauss "

2 dimensional Gauss distribution in Fourier space. Corresponds to normalized exp(-r^2/2) in real space with  $r=\\\\sqrt{(\\\\frac{x}{\\\\omega_x})^2 + (\\\\frac{y}{\\\\omega_y})^2}$

C++ includes: FTDistributions.h
";

%feature("docstring")  FTDistribution2DGauss::FTDistribution2DGauss "FTDistribution2DGauss::FTDistribution2DGauss(double coherence_length_x, double coherence_length_y)
";

%feature("docstring")  FTDistribution2DGauss::~FTDistribution2DGauss "virtual FTDistribution2DGauss::~FTDistribution2DGauss()
";

%feature("docstring")  FTDistribution2DGauss::clone "FTDistribution2DGauss * FTDistribution2DGauss::clone() const 
";

%feature("docstring")  FTDistribution2DGauss::evaluate "double FTDistribution2DGauss::evaluate(double qx, double qy) const

evaluate Fourier transformed distribution for q in X,Y coordinates the original distribution (in real space) is assumed to be normalized: total integral is equal to 1 
";


// File: classFTDistribution2DVoigt.xml
%feature("docstring") FTDistribution2DVoigt "

2 dimensional Voigt distribution in Fourier space. Corresponds to eta*Gauss + (1-eta)*Cauchy

C++ includes: FTDistributions.h
";

%feature("docstring")  FTDistribution2DVoigt::FTDistribution2DVoigt "FTDistribution2DVoigt::FTDistribution2DVoigt(double coherence_length_x, double coherence_length_y, double eta)
";

%feature("docstring")  FTDistribution2DVoigt::~FTDistribution2DVoigt "virtual FTDistribution2DVoigt::~FTDistribution2DVoigt()
";

%feature("docstring")  FTDistribution2DVoigt::clone "FTDistribution2DVoigt * FTDistribution2DVoigt::clone() const 
";

%feature("docstring")  FTDistribution2DVoigt::evaluate "double FTDistribution2DVoigt::evaluate(double qx, double qy) const

evaluate Fourier transformed distribution for q in X,Y coordinates the original distribution (in real space) is assumed to be normalized: total integral is equal to 1 
";

%feature("docstring")  FTDistribution2DVoigt::getEta "virtual double FTDistribution2DVoigt::getEta() const 
";


// File: classFunctionalMultiTest.xml
%feature("docstring") FunctionalMultiTest "

Functional multi test constructs the collection of standard functional tests using component service, runs them one-by-one, and then reports results in a single table.

C++ includes: FunctionalMultiTest.h
";

%feature("docstring")  FunctionalMultiTest::FunctionalMultiTest "FunctionalMultiTest::FunctionalMultiTest(const std::string &name, FunctionalTestComponentService *service)
";

%feature("docstring")  FunctionalMultiTest::~FunctionalMultiTest "FunctionalMultiTest::~FunctionalMultiTest()
";

%feature("docstring")  FunctionalMultiTest::runTest "void FunctionalMultiTest::runTest()
";

%feature("docstring")  FunctionalMultiTest::analyseResults "int FunctionalMultiTest::analyseResults()
";

%feature("docstring")  FunctionalMultiTest::printResults "void FunctionalMultiTest::printResults(std::ostream &ostr) const 
";


// File: classFunctionalTestComponentService.xml
%feature("docstring") FunctionalTestComponentService "

Contains all necessary information to compose functional test.

C++ includes: FunctionalTestComponentService.h
";

%feature("docstring")  FunctionalTestComponentService::FunctionalTestComponentService "FunctionalTestComponentService::FunctionalTestComponentService(const FunctionalTestInfo &info)
";

%feature("docstring")  FunctionalTestComponentService::~FunctionalTestComponentService "FunctionalTestComponentService::~FunctionalTestComponentService()
";

%feature("docstring")  FunctionalTestComponentService::getFormFactor "IFormFactor * FunctionalTestComponentService::getFormFactor() const 
";

%feature("docstring")  FunctionalTestComponentService::getFTDistribution2D "IFTDistribution2D * FunctionalTestComponentService::getFTDistribution2D() const 
";

%feature("docstring")  FunctionalTestComponentService::getSimulation "GISASSimulation * FunctionalTestComponentService::getSimulation() const 
";

%feature("docstring")  FunctionalTestComponentService::getSampleBuilder "SampleBuilder_t FunctionalTestComponentService::getSampleBuilder() const 
";

%feature("docstring")  FunctionalTestComponentService::getReferenceData "OutputData< double > * FunctionalTestComponentService::getReferenceData() const 
";

%feature("docstring")  FunctionalTestComponentService::getFunctionalTest "IFunctionalTest * FunctionalTestComponentService::getFunctionalTest() const 
";

%feature("docstring")  FunctionalTestComponentService::getNumberOfComponents "size_t FunctionalTestComponentService::getNumberOfComponents() const 
";

%feature("docstring")  FunctionalTestComponentService::initComponent "void FunctionalTestComponentService::initComponent(size_t component_index)
";

%feature("docstring")  FunctionalTestComponentService::getCurrentComponentName "std::string FunctionalTestComponentService::getCurrentComponentName() const 
";

%feature("docstring")  FunctionalTestComponentService::getReferenceFileName "std::string FunctionalTestComponentService::getReferenceFileName() const 
";

%feature("docstring")  FunctionalTestComponentService::getTestInfo "FunctionalTestInfo FunctionalTestComponentService::getTestInfo() const 
";


// File: classFunctionalTestInfo.xml
%feature("docstring") FunctionalTestInfo "

Contains all necessary information to compose functional test.

C++ includes: FunctionalTestInfo.h
";

%feature("docstring")  FunctionalTestInfo::FunctionalTestInfo "FunctionalTestInfo::FunctionalTestInfo()
";

%feature("docstring")  FunctionalTestInfo::FunctionalTestInfo "FunctionalTestInfo::FunctionalTestInfo(const std::string &test_name, const std::string &test_description, const std::string &simulation_name, const std::string &sample_builder_name, const std::string &component_registry_name, double threshold)
";


// File: classFunctionalTestRegistry.xml
%feature("docstring") FunctionalTestRegistry "

The registry which holds information about available functional tests.

C++ includes: FunctionalTestRegistry.h
";

%feature("docstring")  FunctionalTestRegistry::FunctionalTestRegistry "FunctionalTestRegistry::FunctionalTestRegistry()
";

%feature("docstring")  FunctionalTestRegistry::add "void FunctionalTestRegistry::add(const std::string &test_name, const std::string &test_description, const std::string &simulation_name, const std::string &sample_builder_name, const std::string &component_registry_name, double threshold)
";

%feature("docstring")  FunctionalTestRegistry::getTestInfo "FunctionalTestInfo FunctionalTestRegistry::getTestInfo(const std::string &test_name)
";

%feature("docstring")  FunctionalTestRegistry::begin "iterator FunctionalTestRegistry::begin()
";

%feature("docstring")  FunctionalTestRegistry::end "iterator FunctionalTestRegistry::end()
";

%feature("docstring")  FunctionalTestRegistry::find "iterator FunctionalTestRegistry::find(const std::string &key)
";

%feature("docstring")  FunctionalTestRegistry::printCatalogue "void FunctionalTestRegistry::printCatalogue(std::ostream &ostr)
";

%feature("docstring")  FunctionalTestRegistry::isValidTest "bool FunctionalTestRegistry::isValidTest(const std::string &test_name)
";


// File: classGISASSimulation.xml
%feature("docstring") GISASSimulation "";

%feature("docstring")  GISASSimulation::GISASSimulation "GISASSimulation::GISASSimulation()
";

%feature("docstring")  GISASSimulation::GISASSimulation "GISASSimulation::GISASSimulation(const ISample &p_sample)
";

%feature("docstring")  GISASSimulation::GISASSimulation "GISASSimulation::GISASSimulation(SampleBuilder_t p_sample_builder)
";

%feature("docstring")  GISASSimulation::~GISASSimulation "virtual GISASSimulation::~GISASSimulation()
";

%feature("docstring")  GISASSimulation::clone "GISASSimulation * GISASSimulation::clone() const 
";

%feature("docstring")  GISASSimulation::prepareSimulation "void GISASSimulation::prepareSimulation()

Put into a clean state for running a simulation. 
";

%feature("docstring")  GISASSimulation::getNumberOfSimulationElements "int GISASSimulation::getNumberOfSimulationElements() const

Gets the number of elements this simulation needs to calculate. 
";

%feature("docstring")  GISASSimulation::getOutputData "const OutputData< double > * GISASSimulation::getOutputData() const

Returns detector intensity map (no detector resolution) 
";

%feature("docstring")  GISASSimulation::getDetectorIntensity "OutputData< double > * GISASSimulation::getDetectorIntensity(IDetector2D::EAxesUnits units_type=IDetector2D::DEFAULT) const

Returns clone of the detector intensity map with detector resolution applied. 
";

%feature("docstring")  GISASSimulation::getIntensityData "Histogram2D * GISASSimulation::getIntensityData(IDetector2D::EAxesUnits units_type=IDetector2D::DEFAULT) const

Returns clone of the detector intensity map with detector resolution applied in the form of 2D histogram. 
";

%feature("docstring")  GISASSimulation::setInstrument "void GISASSimulation::setInstrument(const Instrument &instrument)

Sets the instrument containing beam and detector information. 
";

%feature("docstring")  GISASSimulation::getInstrument "const Instrument & GISASSimulation::getInstrument() const

Returns the instrument containing beam and detector information. 
";

%feature("docstring")  GISASSimulation::getInstrument "Instrument & GISASSimulation::getInstrument()
";

%feature("docstring")  GISASSimulation::setBeamParameters "void GISASSimulation::setBeamParameters(double wavelength, double alpha_i, double phi_i)

Sets beam parameters from here (forwarded to  Instrument) 
";

%feature("docstring")  GISASSimulation::setBeamIntensity "void GISASSimulation::setBeamIntensity(double intensity)

Sets beam intensity from here (forwarded to  Instrument) 
";

%feature("docstring")  GISASSimulation::setBeamPolarization "void GISASSimulation::setBeamPolarization(const kvector_t &bloch_vector)

Sets the beam polarization according to the given Bloch vector. 
";

%feature("docstring")  GISASSimulation::setDetector "void GISASSimulation::setDetector(const IDetector2D &detector)

Sets the detector (axes can be overwritten later) 
";

%feature("docstring")  GISASSimulation::setDetectorParameters "void GISASSimulation::setDetectorParameters(const OutputData< double > &output_data)

Sets detector parameters using axes of output data. 
";

%feature("docstring")  GISASSimulation::setDetectorParameters "void GISASSimulation::setDetectorParameters(const IHistogram &hisotgram)
";

%feature("docstring")  GISASSimulation::setDetectorParameters "void GISASSimulation::setDetectorParameters(size_t n_phi, double phi_min, double phi_max, size_t n_alpha, double alpha_min, double alpha_max)

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

%feature("docstring")  GISASSimulation::setDetectorResolutionFunction "void GISASSimulation::setDetectorResolutionFunction(const IResolutionFunction2D &resolution_function)

Define resolution function for detector. 
";

%feature("docstring")  GISASSimulation::removeDetectorResolutionFunction "void GISASSimulation::removeDetectorResolutionFunction()

Removes detector resolution function. 
";

%feature("docstring")  GISASSimulation::setAnalyzerProperties "void GISASSimulation::setAnalyzerProperties(const kvector_t &direction, double efficiency, double total_transmission=1.0)

Sets the polarization analyzer characteristics of the detector. 
";

%feature("docstring")  GISASSimulation::removeMasks "void GISASSimulation::removeMasks()

removes all masks from the detector 
";

%feature("docstring")  GISASSimulation::addMask "void GISASSimulation::addMask(const Geometry::IShape2D &shape, bool mask_value=true)

Adds mask of given shape to the stack of detector masks. The mask value 'true' means that the channel will be excluded from the simulation. The mask which is added last has priority.

Parameters:
-----------

shape: 
The shape of mask (Rectangle, Polygon, Line, Ellipse)

mask_value: 
The value of mask 
";

%feature("docstring")  GISASSimulation::maskAll "void GISASSimulation::maskAll()

Put the mask for all detector channels (i.e. exclude whole detector from the analysis) 
";

%feature("docstring")  GISASSimulation::addParametersToExternalPool "std::string GISASSimulation::addParametersToExternalPool(std::string path, ParameterPool *external_pool, int copy_number=-1) const

Adds parameters from local pool to external pool and recursively calls its direct children. 
";


// File: classHexParaCrystalBuilder.xml
%feature("docstring") HexParaCrystalBuilder "

Builds sample: cylinders with 2DDL structure factor (IsGISAXS example #4)

C++ includes: ParaCrystalBuilder.h
";

%feature("docstring")  HexParaCrystalBuilder::HexParaCrystalBuilder "HexParaCrystalBuilder::HexParaCrystalBuilder()
";

%feature("docstring")  HexParaCrystalBuilder::buildSample "ISample * HexParaCrystalBuilder::buildSample() const 
";


// File: classHistogram1D.xml
%feature("docstring") Histogram1D "";

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

%feature("docstring")  Histogram1D::crop "Histogram1D * Histogram1D::crop(double xmin, double xmax)

Create new histogram by applying crop on axis. 
";


// File: classHistogram2D.xml
%feature("docstring") Histogram2D "";

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

Create new histogram by applying rectangular clip. 
";


// File: classHomogeneousMagneticMaterial.xml
%feature("docstring") HomogeneousMagneticMaterial "

An homogeneous material with magnetization.

C++ includes: HomogeneousMagneticMaterial.h
";

%feature("docstring")  HomogeneousMagneticMaterial::HomogeneousMagneticMaterial "HomogeneousMagneticMaterial::HomogeneousMagneticMaterial(const std::string &name, const complex_t &refractive_index, const kvector_t &magnetic_field)

Constructs a material with  name,  refractive_index and  magnetic_field
";

%feature("docstring")  HomogeneousMagneticMaterial::HomogeneousMagneticMaterial "HomogeneousMagneticMaterial::HomogeneousMagneticMaterial(const std::string &name, double refractive_index_delta, double refractive_index_beta, const kvector_t &magnetic_field)

Constructs a material with  name, refractive_index parameters and  magnetic_field
";

%feature("docstring")  HomogeneousMagneticMaterial::clone "HomogeneousMagneticMaterial * HomogeneousMagneticMaterial::clone() const

Clone. 
";

%feature("docstring")  HomogeneousMagneticMaterial::getMagneticField "kvector_t HomogeneousMagneticMaterial::getMagneticField() const

Get the magnetic field (in Tesla) 
";

%feature("docstring")  HomogeneousMagneticMaterial::setMagneticField "void HomogeneousMagneticMaterial::setMagneticField(const kvector_t &magnetic_field)

Set the magnetic field (in Tesla) 
";

%feature("docstring")  HomogeneousMagneticMaterial::isScalarMaterial "virtual bool HomogeneousMagneticMaterial::isScalarMaterial() const

Indicates that the material is not scalar. This means that different polarization states will be diffracted differently 
";

%feature("docstring")  HomogeneousMagneticMaterial::getScatteringMatrix "Eigen::Matrix2cd HomogeneousMagneticMaterial::getScatteringMatrix(double k_mag2) const

Get the scattering matrix (~potential V) from the material. This matrix appears in the full three-dimensional Schroedinger equation. 
";

%feature("docstring")  HomogeneousMagneticMaterial::createTransformedMaterial "const IMaterial * HomogeneousMagneticMaterial::createTransformedMaterial(const IRotation &rotation) const

Create a new material that is transformed with respect to this one. 
";


// File: classHomogeneousMaterial.xml
%feature("docstring") HomogeneousMaterial "

An homogeneous material with a refractive index.

C++ includes: HomogeneousMaterial.h
";

%feature("docstring")  HomogeneousMaterial::HomogeneousMaterial "HomogeneousMaterial::HomogeneousMaterial(const std::string &name, const complex_t &refractive_index)

Constructs a material with  name and  refractive_index. 
";

%feature("docstring")  HomogeneousMaterial::HomogeneousMaterial "HomogeneousMaterial::HomogeneousMaterial(const std::string &name, double refractive_index_delta, double refractive_index_beta)

Constructs a material with  name and refractive_index parameters delta and beta (n = 1 - delta + i*beta). 
";

%feature("docstring")  HomogeneousMaterial::~HomogeneousMaterial "virtual HomogeneousMaterial::~HomogeneousMaterial()
";

%feature("docstring")  HomogeneousMaterial::clone "HomogeneousMaterial * HomogeneousMaterial::clone() const

Clone. 
";

%feature("docstring")  HomogeneousMaterial::getRefractiveIndex "virtual complex_t HomogeneousMaterial::getRefractiveIndex() const

Return refractive index. 
";

%feature("docstring")  HomogeneousMaterial::setRefractiveIndex "void HomogeneousMaterial::setRefractiveIndex(const complex_t &refractive_index)

Set refractive index. 
";

%feature("docstring")  HomogeneousMaterial::getScatteringMatrix "Eigen::Matrix2cd HomogeneousMaterial::getScatteringMatrix(double k_mag2) const

Get the scattering matrix (~potential V) from the material. This matrix appears in the full three-dimensional Schroedinger equation. 
";

%feature("docstring")  HomogeneousMaterial::createTransformedMaterial "const IMaterial * HomogeneousMaterial::createTransformedMaterial(const IRotation &rotation) const

Create a new material that is transformed with respect to this one. 
";


// File: classGeometry_1_1HorizontalLine.xml
%feature("docstring") Geometry::HorizontalLine "

Horizontal infinite line.

C++ includes: Line.h
";

%feature("docstring")  Geometry::HorizontalLine::HorizontalLine "Geometry::HorizontalLine::HorizontalLine(double y)

Infinite vertical line constructor

Parameters:
-----------

y: 
The value at which it crosses y-axes 
";

%feature("docstring")  Geometry::HorizontalLine::clone "HorizontalLine * Geometry::HorizontalLine::clone() const 
";

%feature("docstring")  Geometry::HorizontalLine::contains "bool Geometry::HorizontalLine::contains(double x, double y) const

Returns true if given point is on this line segment. 
";

%feature("docstring")  Geometry::HorizontalLine::contains "bool Geometry::HorizontalLine::contains(const Bin1D &binx, const Bin1D &biny) const

Returns true if the line crosses the area defined by two given bins. 
";

%feature("docstring")  Geometry::HorizontalLine::getYpos "double Geometry::HorizontalLine::getYpos() const 
";


// File: classIAbstractParticle.xml
%feature("docstring") IAbstractParticle "

Interface for a generic particle.

C++ includes: IParticle.h
";

%feature("docstring")  IAbstractParticle::IAbstractParticle "IAbstractParticle::IAbstractParticle()
";

%feature("docstring")  IAbstractParticle::~IAbstractParticle "virtual IAbstractParticle::~IAbstractParticle()
";

%feature("docstring")  IAbstractParticle::clone "virtual IAbstractParticle* IAbstractParticle::clone() const =0

Returns a clone of this  ISample object. 
";

%feature("docstring")  IAbstractParticle::cloneInvertB "virtual IAbstractParticle* IAbstractParticle::cloneInvertB() const =0

Returns a clone with inverted magnetic fields. 
";

%feature("docstring")  IAbstractParticle::accept "void IAbstractParticle::accept(ISampleVisitor *visitor) const

calls the  ISampleVisitor's visit method 
";

%feature("docstring")  IAbstractParticle::setAmbientMaterial "void IAbstractParticle::setAmbientMaterial(const IMaterial &material)

Sets the refractive index of the ambient material (which influences its scattering power) 
";

%feature("docstring")  IAbstractParticle::getAbundance "double IAbstractParticle::getAbundance() const

Returns abundance. 
";

%feature("docstring")  IAbstractParticle::setAbundance "void IAbstractParticle::setAbundance(double abundance)

Sets abundance. 
";

%feature("docstring")  IAbstractParticle::getAmbientMaterial "virtual const IMaterial* IAbstractParticle::getAmbientMaterial() const =0

Returns particle's material. 
";


// File: classIAxis.xml
%feature("docstring") IAxis "

Interface for one-dimensional axes.

C++ includes: IAxis.h
";

%feature("docstring")  IAxis::IAxis "IAxis::IAxis(const std::string &name)

constructors 
";

%feature("docstring")  IAxis::clone "virtual IAxis* IAxis::clone() const =0

clone function 
";

%feature("docstring")  IAxis::createDoubleBinSize "IAxis * IAxis::createDoubleBinSize() const

Creates a new axis with half the number of bins. 
";

%feature("docstring")  IAxis::~IAxis "virtual IAxis::~IAxis()

destructor 
";

%feature("docstring")  IAxis::getSize "virtual size_t IAxis::getSize() const =0

retrieve the number of bins 
";

%feature("docstring")  IAxis::getName "std::string IAxis::getName() const

retrieve the label of the axis 
";

%feature("docstring")  IAxis::setName "void IAxis::setName(std::string name)

Sets the axis label. 
";

%feature("docstring")  IAxis::getBin "virtual Bin1D IAxis::getBin(size_t index) const =0

retrieve a 1d bin for the given index 
";

%feature("docstring")  IAxis::getMin "virtual double IAxis::getMin() const =0

Returns value of first point of axis. 
";

%feature("docstring")  IAxis::getMax "virtual double IAxis::getMax() const =0

Returns value of last point of axis. 
";

%feature("docstring")  IAxis::getBinCenter "virtual double IAxis::getBinCenter(size_t index) const =0
";

%feature("docstring")  IAxis::findClosestIndex "virtual size_t IAxis::findClosestIndex(double value) const =0

find bin index which is best match for given value 
";

%feature("docstring")  IAxis::getBinCenters "std::vector< double > IAxis::getBinCenters() const 
";

%feature("docstring")  IAxis::getBinBoundaries "std::vector< double > IAxis::getBinBoundaries() const 
";

%feature("docstring")  IAxis::createClippedAxis "IAxis * IAxis::createClippedAxis(double left, double right) const

Creates a new clipped axis. 
";

%feature("docstring")  IAxis::contains "bool IAxis::contains(double value) const

Returns true if axis contains given point. 
";


// File: classIChiSquaredModule.xml
%feature("docstring") IChiSquaredModule "

Interface for  ChiSquaredModule, ChiSquaredFrequency for chi2 calculations.

C++ includes: IChiSquaredModule.h
";

%feature("docstring")  IChiSquaredModule::IChiSquaredModule "IChiSquaredModule::IChiSquaredModule()
";

%feature("docstring")  IChiSquaredModule::~IChiSquaredModule "IChiSquaredModule::~IChiSquaredModule()
";

%feature("docstring")  IChiSquaredModule::clone "virtual IChiSquaredModule* IChiSquaredModule::clone() const =0

clone method 
";

%feature("docstring")  IChiSquaredModule::getSquaredFunction "const ISquaredFunction* IChiSquaredModule::getSquaredFunction() const

Returns squared function. 
";

%feature("docstring")  IChiSquaredModule::setChiSquaredFunction "void IChiSquaredModule::setChiSquaredFunction(ISquaredFunction *squared_function)

Sets squared function. 
";

%feature("docstring")  IChiSquaredModule::setChiSquaredFunction "void IChiSquaredModule::setChiSquaredFunction(const ISquaredFunction &squared_function)
";

%feature("docstring")  IChiSquaredModule::getIntensityNormalizer "virtual const IIntensityNormalizer* IChiSquaredModule::getIntensityNormalizer() const

Returns data normalizer. 
";

%feature("docstring")  IChiSquaredModule::getIntensityNormalizer "virtual IIntensityNormalizer* IChiSquaredModule::getIntensityNormalizer()

Returns data normalizer, non-const version needed to set internals. 
";

%feature("docstring")  IChiSquaredModule::setIntensityNormalizer "void IChiSquaredModule::setIntensityNormalizer(const IIntensityNormalizer &data_normalizer)

Sets data normalizer. 
";

%feature("docstring")  IChiSquaredModule::getIntensityFunction "virtual const IIntensityFunction* IChiSquaredModule::getIntensityFunction() const

Returns data rescaler. 
";

%feature("docstring")  IChiSquaredModule::setIntensityFunction "void IChiSquaredModule::setIntensityFunction(const IIntensityFunction &intensity_function)

Sets data rescaler. 
";

%feature("docstring")  IChiSquaredModule::processFitElements "virtual void IChiSquaredModule::processFitElements(std::vector< FitElement >::iterator, std::vector< FitElement >::iterator)
";


// File: classICloneable.xml
%feature("docstring") ICloneable "

Interface for objects that must not be copied, except by cloning.

This virtual base class disables the copy constructor and the operator= in all its child classes. Child classes should provide clone().

C++ includes: ICloneable.h
";

%feature("docstring")  ICloneable::ICloneable "ICloneable::ICloneable()
";

%feature("docstring")  ICloneable::~ICloneable "virtual ICloneable::~ICloneable()
";

%feature("docstring")  ICloneable::clone "virtual ICloneable* ICloneable::clone() const =0
";

%feature("docstring")  ICloneable::transferToCPP "virtual void ICloneable::transferToCPP()

Used for Python overriding of clone. 
";


// File: classICloneableRegistry.xml
%feature("docstring") ICloneableRegistry "

Templated registry for cloneable objects.

C++ includes: ICloneableRegistry.h
";

%feature("docstring")  ICloneableRegistry::createItem "AbstractProduct* ICloneableRegistry< IdentifierType, AbstractProduct >::createItem(const IdentifierType &key) const 
";

%feature("docstring")  ICloneableRegistry::begin "iterator ICloneableRegistry< IdentifierType, AbstractProduct >::begin()
";

%feature("docstring")  ICloneableRegistry::begin "const_iterator ICloneableRegistry< IdentifierType, AbstractProduct >::begin() const 
";

%feature("docstring")  ICloneableRegistry::end "iterator ICloneableRegistry< IdentifierType, AbstractProduct >::end()
";

%feature("docstring")  ICloneableRegistry::end "const_iterator ICloneableRegistry< IdentifierType, AbstractProduct >::end() const 
";


// File: classIClusteredParticles.xml
%feature("docstring") IClusteredParticles "

An ordered assembly of particles.

C++ includes: IClusteredParticles.h
";

%feature("docstring")  IClusteredParticles::IClusteredParticles "IClusteredParticles::IClusteredParticles()
";

%feature("docstring")  IClusteredParticles::~IClusteredParticles "virtual IClusteredParticles::~IClusteredParticles()
";

%feature("docstring")  IClusteredParticles::clone "virtual IClusteredParticles* IClusteredParticles::clone() const =0

clone method to allow for polymorphic copying 
";

%feature("docstring")  IClusteredParticles::cloneInvertB "virtual IClusteredParticles* IClusteredParticles::cloneInvertB() const =0

Returns a clone with inverted magnetic fields. 
";

%feature("docstring")  IClusteredParticles::accept "virtual void IClusteredParticles::accept(ISampleVisitor *visitor) const =0

calls the  ISampleVisitor's visit method 
";

%feature("docstring")  IClusteredParticles::setAmbientMaterial "virtual void IClusteredParticles::setAmbientMaterial(const IMaterial &material)=0
";

%feature("docstring")  IClusteredParticles::getAmbientMaterial "virtual const IMaterial* IClusteredParticles::getAmbientMaterial() const =0
";

%feature("docstring")  IClusteredParticles::createTotalFormFactor "virtual IFormFactor* IClusteredParticles::createTotalFormFactor(const IFormFactor &meso_crystal_form_factor, const IRotation *p_rotation, kvector_t translation) const

create a total form factor for the mesocrystal with a specific shape and content

Parameters:
-----------

meso_crystal_form_factor: 
the form factor describing the shape of the mesocrystal

ambient_refractive_index: 
the refractive index of the ambient material The bulk content of the mesocrystal is encapsulated by the  IClusteredParticles object itself 
";

%feature("docstring")  IClusteredParticles::applyRotation "virtual void IClusteredParticles::applyRotation(const IRotation &rotation)

Composes transformation with existing one. 
";


// File: classIComponentService.xml
%feature("docstring") IComponentService "

Interface to the class which provides client with objects he needs.

C++ includes: IComponentService.h
";

%feature("docstring")  IComponentService::getFormFactor "virtual IFormFactor* IComponentService::getFormFactor() const =0
";

%feature("docstring")  IComponentService::getFTDistribution2D "virtual IFTDistribution2D* IComponentService::getFTDistribution2D() const =0
";

%feature("docstring")  IComponentService::getSimulation "virtual GISASSimulation* IComponentService::getSimulation() const =0
";

%feature("docstring")  IComponentService::getSampleBuilder "virtual SampleBuilder_t IComponentService::getSampleBuilder() const =0
";

%feature("docstring")  IComponentService::getReferenceData "virtual OutputData<double>* IComponentService::getReferenceData() const =0
";

%feature("docstring")  IComponentService::getFunctionalTest "virtual IFunctionalTest* IComponentService::getFunctionalTest() const =0
";

%feature("docstring")  IComponentService::~IComponentService "virtual IComponentService::~IComponentService()
";


// File: classICompositeSample.xml
%feature("docstring") ICompositeSample "

Interface to describe the tree-like composition of samples.

C++ includes: ICompositeSample.h
";

%feature("docstring")  ICompositeSample::ICompositeSample "ICompositeSample::ICompositeSample()
";

%feature("docstring")  ICompositeSample::~ICompositeSample "virtual ICompositeSample::~ICompositeSample()
";

%feature("docstring")  ICompositeSample::clone "ICompositeSample* ICompositeSample::clone() const =0

Returns a clone of this  ISample object. 
";

%feature("docstring")  ICompositeSample::accept "void ICompositeSample::accept(ISampleVisitor *visitor) const

calls the  ISampleVisitor's visit method 
";

%feature("docstring")  ICompositeSample::registerChild "void ICompositeSample::registerChild(ISample *sample)

Registers child in the container. 
";

%feature("docstring")  ICompositeSample::deregisterChild "void ICompositeSample::deregisterChild(ISample *sample)

Removes registered child from the container.

remove registered child from the container 
";

%feature("docstring")  ICompositeSample::getChildren "std::vector< const ISample * > ICompositeSample::getChildren() const

Returns a vector of children (const). 
";

%feature("docstring")  ICompositeSample::size "size_t ICompositeSample::size() const

Returns number of children. 
";

%feature("docstring")  ICompositeSample::addParametersToExternalPool "std::string ICompositeSample::addParametersToExternalPool(std::string path, ParameterPool *external_pool, int copy_number=-1) const

Adds parameters from local pool to external pool and recursively calls its direct children. 
";


// File: classIDetector.xml
%feature("docstring") IDetector "

The detector interface.

C++ includes: IDetector2D.h
";


// File: classIDetector2D.xml
%feature("docstring") IDetector2D "";

%feature("docstring")  IDetector2D::IDetector2D "IDetector2D::IDetector2D()
";

%feature("docstring")  IDetector2D::IDetector2D "IDetector2D::IDetector2D(const IDetector2D &other)
";

%feature("docstring")  IDetector2D::clone "virtual IDetector2D* IDetector2D::clone() const =0
";

%feature("docstring")  IDetector2D::~IDetector2D "virtual IDetector2D::~IDetector2D()
";

%feature("docstring")  IDetector2D::init "void IDetector2D::init(const Beam &beam)

Inits detector with the beam settings. 
";

%feature("docstring")  IDetector2D::addAxis "void IDetector2D::addAxis(const IAxis &axis)
";

%feature("docstring")  IDetector2D::getAxis "const IAxis & IDetector2D::getAxis(size_t index) const 
";

%feature("docstring")  IDetector2D::getDimension "size_t IDetector2D::getDimension() const 
";

%feature("docstring")  IDetector2D::clear "void IDetector2D::clear()
";

%feature("docstring")  IDetector2D::matchDetectorAxes "void IDetector2D::matchDetectorAxes(const OutputData< double > &output_data)

Sets detector parameters using axes of output data. 
";

%feature("docstring")  IDetector2D::setDetectorParameters "void IDetector2D::setDetectorParameters(size_t n_x, double x_min, double x_max, size_t n_y, double y_min, double y_max)

Sets detector parameters using angle ranges. 
";

%feature("docstring")  IDetector2D::setDetectorAxes "void IDetector2D::setDetectorAxes(const IAxis &axis0, const IAxis &axis1)

Sets detector parameters using axes. 
";

%feature("docstring")  IDetector2D::setDetectorResolution "void IDetector2D::setDetectorResolution(IDetectorResolution *p_detector_resolution)

Sets the detector resolution. 
";

%feature("docstring")  IDetector2D::applyDetectorResolution "void IDetector2D::applyDetectorResolution(OutputData< double > *p_intensity_map) const

Applies the detector resolution to the given intensity maps. 
";

%feature("docstring")  IDetector2D::getDetectorResolutionFunction "const IDetectorResolution * IDetector2D::getDetectorResolutionFunction() const 
";

%feature("docstring")  IDetector2D::setAnalyzerProperties "void IDetector2D::setAnalyzerProperties(const kvector_t &direction, double efficiency, double total_transmission=1.0)

Sets the polarization analyzer characteristics of the detector. 
";

%feature("docstring")  IDetector2D::getAnalyzerOperator "Eigen::Matrix2cd IDetector2D::getAnalyzerOperator() const

Gets the polarization density matrix (in spin basis along z-axis) 
";

%feature("docstring")  IDetector2D::removeMasks "void IDetector2D::removeMasks()

removes all masks from the detector 
";

%feature("docstring")  IDetector2D::addMask "void IDetector2D::addMask(const Geometry::IShape2D &shape, bool mask_value=true)

Adds mask of given shape to the stack of detector masks. The mask value 'true' means that the channel will be excluded from the simulation. The mask which is added last has priority.

Parameters:
-----------

shape: 
The shape of mask (Rectangle, Polygon, Line, Ellipse)  The value of mask 
";

%feature("docstring")  IDetector2D::maskAll "void IDetector2D::maskAll()

Put the mask for all detector channels (i.e. exclude whole detector from the analysis) 
";

%feature("docstring")  IDetector2D::getDetectorMask "const DetectorMask * IDetector2D::getDetectorMask() const 
";

%feature("docstring")  IDetector2D::getNumberOfMaskedChannels "int IDetector2D::getNumberOfMaskedChannels() const 
";

%feature("docstring")  IDetector2D::isMasked "bool IDetector2D::isMasked(size_t index) const 
";

%feature("docstring")  IDetector2D::hasMasks "bool IDetector2D::hasMasks() const

return true if has masks 
";

%feature("docstring")  IDetector2D::createSimulationElements "std::vector< SimulationElement > IDetector2D::createSimulationElements(const Beam &beam)

Create a vector of  SimulationElement objects according to the detector and its mask. 
";

%feature("docstring")  IDetector2D::getSimulationElement "SimulationElement IDetector2D::getSimulationElement(size_t index, const Beam &beam) const

create single simulation element 
";

%feature("docstring")  IDetector2D::addParametersToExternalPool "std::string IDetector2D::addParametersToExternalPool(std::string path, ParameterPool *external_pool, int copy_number=-1) const

Adds parameters from local pool to external pool and recursively calls its direct children. 
";

%feature("docstring")  IDetector2D::createDetectorMap "OutputData< double > * IDetector2D::createDetectorMap(const Beam &beam, EAxesUnits units_type) const

Returns detector map in given axes units. 
";

%feature("docstring")  IDetector2D::getValidAxesUnits "std::vector< IDetector2D::EAxesUnits > IDetector2D::getValidAxesUnits() const

returns vector of valid axes units 
";

%feature("docstring")  IDetector2D::getDefaultAxesUnits "IDetector2D::EAxesUnits IDetector2D::getDefaultAxesUnits() const

return default axes units 
";


// File: classIDetectorResolution.xml
%feature("docstring") IDetectorResolution "

Interface for detector resolution algorithms.

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


// File: classIDistribution1D.xml
%feature("docstring") IDistribution1D "

Interface for 1 dimensional distributions.

C++ includes: Distributions.h
";

%feature("docstring")  IDistribution1D::IDistribution1D "IDistribution1D::IDistribution1D()
";

%feature("docstring")  IDistribution1D::~IDistribution1D "virtual IDistribution1D::~IDistribution1D()
";

%feature("docstring")  IDistribution1D::clone "virtual IDistribution1D* IDistribution1D::clone() const

clone method 
";

%feature("docstring")  IDistribution1D::probabilityDensity "virtual double IDistribution1D::probabilityDensity(double x) const =0

get the probability density for value x 
";

%feature("docstring")  IDistribution1D::getMean "virtual double IDistribution1D::getMean() const =0

get the mean of the distribution 
";

%feature("docstring")  IDistribution1D::generateSamples "std::vector< ParameterSample > IDistribution1D::generateSamples(size_t nbr_samples, double sigma_factor=0.0, const AttLimits &limits=AttLimits()) const

generate list of sampled values with their weight xmin, xmax for sample generations are deduced from sigma_factor and possible limits 
";

%feature("docstring")  IDistribution1D::generateSamples "std::vector< ParameterSample > IDistribution1D::generateSamples(size_t nbr_samples, double xmin, double xmax) const

generate list of sampled values with their weight within given xmin, xmax 
";

%feature("docstring")  IDistribution1D::generateValueList "virtual std::vector<double> IDistribution1D::generateValueList(size_t nbr_samples, double sigma_factor, const AttLimits &limits=AttLimits()) const =0

generate list of sample values

Parameters:
-----------

nbr_samples: 
number of values to generate

sigma_factor: 
parameter to derive min,max range for sample values

vector of generated values 
";

%feature("docstring")  IDistribution1D::generateValues "std::vector< double > IDistribution1D::generateValues(size_t nbr_samples, double xmin, double xmax) const

generate list of sample values

Parameters:
-----------

nbr_samples: 
number of values to generate

xmin: 
xmax: 
start and end value of the generated samples

vector of generated values 
";


// File: classIFactory.xml
%feature("docstring") IFactory "

Base class for all factories.

C++ includes: IFactory.h
";

%feature("docstring")  IFactory::IFactory "IFactory< IdentifierType, AbstractProduct >::IFactory()
";

%feature("docstring")  IFactory::createItem "AbstractProduct* IFactory< IdentifierType, AbstractProduct >::createItem(const IdentifierType &itemId)

Creates object by calling creation function corresponded to given identifier. 
";

%feature("docstring")  IFactory::registerItem "bool IFactory< IdentifierType, AbstractProduct >::registerItem(const IdentifierType &itemId, CreateItemCallback CreateFn)

Registers object's creation function. 
";

%feature("docstring")  IFactory::registerItem "bool IFactory< IdentifierType, AbstractProduct >::registerItem(const IdentifierType &itemId, CreateItemCallback CreateFn, const IdentifierType &itemDescription)

Registers object's creation function and store object description. 
";

%feature("docstring")  IFactory::~IFactory "IFactory< IdentifierType, AbstractProduct >::~IFactory()
";

%feature("docstring")  IFactory::clear "void IFactory< IdentifierType, AbstractProduct >::clear()

clear everything 
";

%feature("docstring")  IFactory::setOwnObjects "void IFactory< IdentifierType, AbstractProduct >::setOwnObjects(bool own_objects)

Sets flag to delete objects on descruction. 
";

%feature("docstring")  IFactory::getNumberOfRegistered "size_t IFactory< IdentifierType, AbstractProduct >::getNumberOfRegistered() const

Returns number of registered objects. 
";

%feature("docstring")  IFactory::begin "iterator IFactory< IdentifierType, AbstractProduct >::begin()
";

%feature("docstring")  IFactory::begin "const_iterator IFactory< IdentifierType, AbstractProduct >::begin() const 
";

%feature("docstring")  IFactory::end "iterator IFactory< IdentifierType, AbstractProduct >::end()
";

%feature("docstring")  IFactory::end "const_iterator IFactory< IdentifierType, AbstractProduct >::end() const 
";


// File: classIFormFactor.xml
%feature("docstring") IFormFactor "

The basic interface for form factors.

C++ includes: IFormFactor.h
";

%feature("docstring")  IFormFactor::IFormFactor "IFormFactor::IFormFactor()
";

%feature("docstring")  IFormFactor::~IFormFactor "virtual IFormFactor::~IFormFactor()
";

%feature("docstring")  IFormFactor::clone "virtual IFormFactor* IFormFactor::clone() const =0

Returns a clone of this  ISample object. 
";

%feature("docstring")  IFormFactor::setAmbientMaterial "virtual void IFormFactor::setAmbientMaterial(const IMaterial &)

Passes the refractive index of the ambient material in which this particle is embedded. 
";

%feature("docstring")  IFormFactor::evaluate "virtual complex_t IFormFactor::evaluate(const WavevectorInfo &wavevectors) const =0

Returns scattering amplitude for complex wavevector bin

Parameters:
-----------

k_i: 
incoming wavevector

k_f_bin: 
outgoing wavevector bin 
";

%feature("docstring")  IFormFactor::evaluatePol "Eigen::Matrix2cd IFormFactor::evaluatePol(const WavevectorInfo &wavevectors) const

Returns scattering amplitude for matrix interactions

Parameters:
-----------

k_i: 
incoming wavevector

k_f_bin: 
outgoing wavevector bin 
";

%feature("docstring")  IFormFactor::getVolume "double IFormFactor::getVolume() const

Returns the total volume of the particle of this form factor's shape. 
";

%feature("docstring")  IFormFactor::getRadius "virtual double IFormFactor::getRadius() const =0

Returns the (approximate in some cases) radial size of the particle of this form factor's shape. This is used for SSCA calculations 
";

%feature("docstring")  IFormFactor::setSpecularInfo "void IFormFactor::setSpecularInfo(const ILayerRTCoefficients *p_in_coeffs, const ILayerRTCoefficients *p_out_coeffs)

Sets reflection/transmission info. 
";


// File: classIFormFactorBorn.xml
%feature("docstring") IFormFactorBorn "

Pure virtual interface for Born form factors. Depends only on q=ki-kf.

C++ includes: IFormFactorBorn.h
";

%feature("docstring")  IFormFactorBorn::IFormFactorBorn "IFormFactorBorn::IFormFactorBorn()
";

%feature("docstring")  IFormFactorBorn::~IFormFactorBorn "virtual IFormFactorBorn::~IFormFactorBorn()
";

%feature("docstring")  IFormFactorBorn::clone "virtual IFormFactorBorn* IFormFactorBorn::clone() const =0

Returns a clone of this  ISample object. 
";

%feature("docstring")  IFormFactorBorn::accept "virtual void IFormFactorBorn::accept(ISampleVisitor *visitor) const

Calls the  ISampleVisitor's visit method. 
";

%feature("docstring")  IFormFactorBorn::evaluate "complex_t IFormFactorBorn::evaluate(const WavevectorInfo &wavevectors) const

Returns scattering amplitude for complex wavevector bin

Parameters:
-----------

k_i: 
incoming wavevector

k_f_bin: 
outgoing wavevector bin 
";

%feature("docstring")  IFormFactorBorn::evaluatePol "Eigen::Matrix2cd IFormFactorBorn::evaluatePol(const WavevectorInfo &wavevectors) const

Returns scattering amplitude for matrix interactions

Parameters:
-----------

k_i: 
incoming wavevector

k_f_bin: 
outgoing wavevector bin 
";

%feature("docstring")  IFormFactorBorn::evaluate_for_q "virtual complex_t IFormFactorBorn::evaluate_for_q(const cvector_t &q) const =0

evaluate scattering amplitude for complex wavevector

Parameters:
-----------

q: 
wavevector transfer q=k_i-k_f 
";


// File: classIFormFactorDecorator.xml
%feature("docstring") IFormFactorDecorator "

Encapsulates another formfactor and adds extra functionality (a scalar factor, a Debye-Waller factor, ...).

C++ includes: IFormFactorDecorator.h
";

%feature("docstring")  IFormFactorDecorator::IFormFactorDecorator "IFormFactorDecorator::IFormFactorDecorator(const IFormFactor &form_factor)
";

%feature("docstring")  IFormFactorDecorator::~IFormFactorDecorator "IFormFactorDecorator::~IFormFactorDecorator()
";

%feature("docstring")  IFormFactorDecorator::clone "virtual IFormFactorDecorator* IFormFactorDecorator::clone() const =0

Returns a clone of this  ISample object. 
";

%feature("docstring")  IFormFactorDecorator::accept "virtual void IFormFactorDecorator::accept(ISampleVisitor *visitor) const =0

Calls the  ISampleVisitor's visit method. 
";

%feature("docstring")  IFormFactorDecorator::setAmbientMaterial "void IFormFactorDecorator::setAmbientMaterial(const IMaterial &material)

Passes the refractive index of the ambient material in which this particle is embedded. 
";

%feature("docstring")  IFormFactorDecorator::getVolume "double IFormFactorDecorator::getVolume() const

Returns the total volume of the particle of this form factor's shape. 
";

%feature("docstring")  IFormFactorDecorator::getRadius "double IFormFactorDecorator::getRadius() const

Returns the (approximate in some cases) radial size of the particle of this form factor's shape. This is used for SSCA calculations 
";


// File: classIFTDecayFunction1D.xml
%feature("docstring") IFTDecayFunction1D "

Interface for 1 dimensional decay function in reciprocal space.

C++ includes: FTDecayFunctions.h
";

%feature("docstring")  IFTDecayFunction1D::IFTDecayFunction1D "IFTDecayFunction1D::IFTDecayFunction1D(double omega)
";

%feature("docstring")  IFTDecayFunction1D::~IFTDecayFunction1D "virtual IFTDecayFunction1D::~IFTDecayFunction1D()
";

%feature("docstring")  IFTDecayFunction1D::clone "virtual IFTDecayFunction1D* IFTDecayFunction1D::clone() const =0
";

%feature("docstring")  IFTDecayFunction1D::evaluate "virtual double IFTDecayFunction1D::evaluate(double q) const =0
";

%feature("docstring")  IFTDecayFunction1D::setOmega "void IFTDecayFunction1D::setOmega(double omega)
";

%feature("docstring")  IFTDecayFunction1D::getOmega "double IFTDecayFunction1D::getOmega() const 
";


// File: classIFTDecayFunction2D.xml
%feature("docstring") IFTDecayFunction2D "

Interface for 2 dimensional decay function in reciprocal space.

C++ includes: FTDecayFunctions.h
";

%feature("docstring")  IFTDecayFunction2D::IFTDecayFunction2D "IFTDecayFunction2D::IFTDecayFunction2D(double decay_length_x, double decay_length_y)
";

%feature("docstring")  IFTDecayFunction2D::~IFTDecayFunction2D "virtual IFTDecayFunction2D::~IFTDecayFunction2D()
";

%feature("docstring")  IFTDecayFunction2D::clone "virtual IFTDecayFunction2D* IFTDecayFunction2D::clone() const =0
";

%feature("docstring")  IFTDecayFunction2D::setGamma "void IFTDecayFunction2D::setGamma(double gamma)

set angle between first lattice vector and X-axis of distribution (both in direct space) 
";

%feature("docstring")  IFTDecayFunction2D::getGamma "double IFTDecayFunction2D::getGamma() const

get angle between first lattice vector and X-axis of distribution (both in direct space) 
";

%feature("docstring")  IFTDecayFunction2D::getDelta "double IFTDecayFunction2D::getDelta() const

get angle between X- and Y-axis of distribution (in direct space) 
";

%feature("docstring")  IFTDecayFunction2D::getDecayLengthX "double IFTDecayFunction2D::getDecayLengthX() const

get coherence length in X-direction 
";

%feature("docstring")  IFTDecayFunction2D::getDecayLengthY "double IFTDecayFunction2D::getDecayLengthY() const

get coherence length in Y-direction 
";

%feature("docstring")  IFTDecayFunction2D::evaluate "virtual double IFTDecayFunction2D::evaluate(double qx, double qy) const =0

evaluate Fourier transformed decay function for q in X,Y coordinates 
";

%feature("docstring")  IFTDecayFunction2D::transformToStarBasis "void IFTDecayFunction2D::transformToStarBasis(double qX, double qY, double alpha, double a, double b, double &qa, double &qb) const

transform back to a*, b* basis: 
";


// File: classIFTDistribution1D.xml
%feature("docstring") IFTDistribution1D "

Interface for 1 dimensional distributions in Fourier space.

C++ includes: FTDistributions.h
";

%feature("docstring")  IFTDistribution1D::IFTDistribution1D "IFTDistribution1D::IFTDistribution1D(double omega)
";

%feature("docstring")  IFTDistribution1D::~IFTDistribution1D "virtual IFTDistribution1D::~IFTDistribution1D()
";

%feature("docstring")  IFTDistribution1D::clone "virtual IFTDistribution1D* IFTDistribution1D::clone() const =0
";

%feature("docstring")  IFTDistribution1D::evaluate "virtual double IFTDistribution1D::evaluate(double q) const =0
";

%feature("docstring")  IFTDistribution1D::setOmega "void IFTDistribution1D::setOmega(double omega)
";

%feature("docstring")  IFTDistribution1D::getOmega "double IFTDistribution1D::getOmega() const 
";


// File: classIFTDistribution2D.xml
%feature("docstring") IFTDistribution2D "

Interface for 2 dimensional distributions in Fourier space.

C++ includes: FTDistributions.h
";

%feature("docstring")  IFTDistribution2D::IFTDistribution2D "IFTDistribution2D::IFTDistribution2D(double coherence_length_x, double coherence_length_y)
";

%feature("docstring")  IFTDistribution2D::~IFTDistribution2D "virtual IFTDistribution2D::~IFTDistribution2D()
";

%feature("docstring")  IFTDistribution2D::clone "virtual IFTDistribution2D* IFTDistribution2D::clone() const =0
";

%feature("docstring")  IFTDistribution2D::setGamma "void IFTDistribution2D::setGamma(double gamma)
";

%feature("docstring")  IFTDistribution2D::getGamma "double IFTDistribution2D::getGamma() const 
";

%feature("docstring")  IFTDistribution2D::getDelta "double IFTDistribution2D::getDelta() const 
";

%feature("docstring")  IFTDistribution2D::getCoherenceLengthX "double IFTDistribution2D::getCoherenceLengthX() const 
";

%feature("docstring")  IFTDistribution2D::getCoherenceLengthY "double IFTDistribution2D::getCoherenceLengthY() const 
";

%feature("docstring")  IFTDistribution2D::evaluate "virtual double IFTDistribution2D::evaluate(double qx, double qy) const =0

evaluate Fourier transformed distribution for q in X,Y coordinates the original distribution (in real space) is assumed to be normalized: total integral is equal to 1 
";


// File: classIFunctionalTest.xml
%feature("docstring") IFunctionalTest "

Basic class for all functional tests.

C++ includes: IFunctionalTest.h
";

%feature("docstring")  IFunctionalTest::IFunctionalTest "IFunctionalTest::IFunctionalTest()
";

%feature("docstring")  IFunctionalTest::IFunctionalTest "IFunctionalTest::IFunctionalTest(const std::string &name, const std::string &description)
";

%feature("docstring")  IFunctionalTest::~IFunctionalTest "virtual IFunctionalTest::~IFunctionalTest()
";

%feature("docstring")  IFunctionalTest::runTest "virtual void IFunctionalTest::runTest()=0
";

%feature("docstring")  IFunctionalTest::analyseResults "virtual int IFunctionalTest::analyseResults()=0
";

%feature("docstring")  IFunctionalTest::getName "std::string IFunctionalTest::getName() const 
";

%feature("docstring")  IFunctionalTest::setName "void IFunctionalTest::setName(const std::string &name)
";

%feature("docstring")  IFunctionalTest::getDescription "std::string IFunctionalTest::getDescription() const 
";

%feature("docstring")  IFunctionalTest::setDescription "void IFunctionalTest::setDescription(const std::string &description)
";

%feature("docstring")  IFunctionalTest::getTestResult "IFunctionalTest::ETestResult IFunctionalTest::getTestResult() const 
";

%feature("docstring")  IFunctionalTest::getTestResultString "std::string IFunctionalTest::getTestResultString() const 
";

%feature("docstring")  IFunctionalTest::getFormattedInfoString "std::string IFunctionalTest::getFormattedInfoString() const 
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

%feature("docstring")  IHistogram::getRank "size_t IHistogram::getRank() const

Returns number of histogram dimensions. 
";

%feature("docstring")  IHistogram::getTotalNumberOfBins "size_t IHistogram::getTotalNumberOfBins() const

Returns total number of histogram bins. For 2D histograms the result will be the product of bin numbers along X and Y axes. 
";

%feature("docstring")  IHistogram::getXaxis "const IAxis * IHistogram::getXaxis() const

returns x-axis 
";

%feature("docstring")  IHistogram::getYaxis "const IAxis * IHistogram::getYaxis() const

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

Returns global bin index for given axes indices. For 1D histogram the global bin index coinside with x-axis index.

Parameters:
-----------

binx: 
x-axis bin index

biny: 
y-axis bin index (for 2D histograms)

The global bin index 
";

%feature("docstring")  IHistogram::findGlobalBin "size_t IHistogram::findGlobalBin(double x, double y) const

Returns closest global bin index for given axes coordinates. For 1D.

Parameters:
-----------

x: 
Value on x-axis

y: 
Value on y-axis (for 2D histograms)

Closest global bin index 
";

%feature("docstring")  IHistogram::getXaxisIndex "int IHistogram::getXaxisIndex(size_t globalbin) const

Returns x-axis bin index for given globalbin. For 1D histograms returned value conicide with globalbin value. 
";

%feature("docstring")  IHistogram::getYaxisIndex "int IHistogram::getYaxisIndex(size_t globalbin) const

Returns y-axis bin index for given globalbin (for 2D histograms). 
";

%feature("docstring")  IHistogram::getXaxisValue "double IHistogram::getXaxisValue(size_t globalbin)

Returns the value on x-axis corresponding to the global bin index.

Parameters:
-----------

globalbin: 
The global bin index

The center of corresponding bin of the axis 
";

%feature("docstring")  IHistogram::getYaxisValue "double IHistogram::getYaxisValue(size_t globalbin)

Returns the value on y-axis corresponding to the global bin index (for 2D histograms).

Parameters:
-----------

globalbin: 
The global bin index

The center of corresponding bin of the axis 
";

%feature("docstring")  IHistogram::getBinContent "double IHistogram::getBinContent(size_t globalbin) const

Returns content (accumulated value) of the bin with given index.

Parameters:
-----------

globalbin: 
The global bin index

The value accumulated by the bin (integral) 
";

%feature("docstring")  IHistogram::getBinContent "double IHistogram::getBinContent(size_t binx, size_t biny) const

Returns content (accumulated value) of the bin with given indices (for 2D histograms).

Parameters:
-----------

binx: 
x-axis bin index

biny: 
y-axis bin index

The value accumulated by the bin (integral) 
";

%feature("docstring")  IHistogram::setBinContent "void IHistogram::setBinContent(size_t globalbin, double value)

Sets content of the bin corresponding to the globalbin number. 
";

%feature("docstring")  IHistogram::addBinContent "void IHistogram::addBinContent(size_t globalbin, double value)

Add the value to the bin. 
";

%feature("docstring")  IHistogram::getBinError "double IHistogram::getBinError(size_t globalbin) const

Returns error of the bin with given index. 
";

%feature("docstring")  IHistogram::getBinError "double IHistogram::getBinError(size_t binx, size_t biny) const

Returns error of the bin with given indices (for 2D histograms). 
";

%feature("docstring")  IHistogram::getBinAverage "double IHistogram::getBinAverage(size_t globalbin) const

Returns average value in the bin with given index. 
";

%feature("docstring")  IHistogram::getBinAverage "double IHistogram::getBinAverage(size_t binx, size_t biny) const

Returns average value of the bin with given indices (for 2D histograms). 
";

%feature("docstring")  IHistogram::getBinNumberOfEntries "int IHistogram::getBinNumberOfEntries(size_t globalbin) const

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

%feature("docstring")  IHistogram::reset "void IHistogram::reset()

Reset histogram content (axes remains) 
";

%feature("docstring")  IHistogram::createOutputData "OutputData< double > * IHistogram::createOutputData(DataType dataType=DataType::INTEGRAL) const

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

%feature("docstring")  IIntensityFunction::~IIntensityFunction "virtual IIntensityFunction::~IIntensityFunction()
";

%feature("docstring")  IIntensityFunction::clone "virtual IIntensityFunction* IIntensityFunction::clone() const =0
";

%feature("docstring")  IIntensityFunction::evaluate "virtual double IIntensityFunction::evaluate(double value) const =0
";


// File: classIIntensityNormalizer.xml
%feature("docstring") IIntensityNormalizer "

Interface to  OutputData normalizers.

C++ includes: IIntensityNormalizer.h
";

%feature("docstring")  IIntensityNormalizer::~IIntensityNormalizer "virtual IIntensityNormalizer::~IIntensityNormalizer()
";

%feature("docstring")  IIntensityNormalizer::clone "virtual IIntensityNormalizer* IIntensityNormalizer::clone() const =0
";

%feature("docstring")  IIntensityNormalizer::createNormalizedData "virtual OutputData<double>* IIntensityNormalizer::createNormalizedData(const OutputData< double > &data) const =0
";

%feature("docstring")  IIntensityNormalizer::apply "virtual void IIntensityNormalizer::apply(OutputData< double > &data) const =0
";

%feature("docstring")  IIntensityNormalizer::setMaximumIntensity "virtual void IIntensityNormalizer::setMaximumIntensity(double)=0
";


// File: classIInterferenceFunction.xml
%feature("docstring") IInterferenceFunction "

Interface to interference functions.

C++ includes: IInterferenceFunction.h
";

%feature("docstring")  IInterferenceFunction::~IInterferenceFunction "virtual IInterferenceFunction::~IInterferenceFunction()
";

%feature("docstring")  IInterferenceFunction::evaluate "virtual double IInterferenceFunction::evaluate(const kvector_t &q) const =0

Evaluates the interference function for a given wavevector transfer (only the real x and y components are relevant) 
";

%feature("docstring")  IInterferenceFunction::clone "virtual IInterferenceFunction* IInterferenceFunction::clone() const =0

Returns a clone of this  ISample object. 
";

%feature("docstring")  IInterferenceFunction::accept "virtual void IInterferenceFunction::accept(ISampleVisitor *visitor) const

Calls the  ISampleVisitor's visit method. 
";

%feature("docstring")  IInterferenceFunction::getKappa "virtual double IInterferenceFunction::getKappa() const

Retrieves the size-distance coupling constant (default 0.0) 
";

%feature("docstring")  IInterferenceFunction::getParticleDensity "virtual double IInterferenceFunction::getParticleDensity() const

If defined by this interference function's parameters, returns the particle density (per area). Otherwise, returns zero or a user-defined value 
";


// File: classIInterferenceFunctionStrategy.xml
%feature("docstring") IInterferenceFunctionStrategy "

Algorithm to apply one of interference function strategies (LMA, SCCA etc)

C++ includes: IInterferenceFunctionStrategy.h
";

%feature("docstring")  IInterferenceFunctionStrategy::IInterferenceFunctionStrategy "IInterferenceFunctionStrategy::IInterferenceFunctionStrategy(SimulationOptions sim_params)
";

%feature("docstring")  IInterferenceFunctionStrategy::~IInterferenceFunctionStrategy "IInterferenceFunctionStrategy::~IInterferenceFunctionStrategy()
";

%feature("docstring")  IInterferenceFunctionStrategy::init "void IInterferenceFunctionStrategy::init(const SafePointerVector< FormFactorInfo > &form_factor_infos, const IInterferenceFunction &iff)

Initializes the object with form factors and interference functions. 
";

%feature("docstring")  IInterferenceFunctionStrategy::setSpecularInfo "void IInterferenceFunctionStrategy::setSpecularInfo(const LayerSpecularInfo &specular_info)

Provides the R,T coefficients information. 
";

%feature("docstring")  IInterferenceFunctionStrategy::evaluate "double IInterferenceFunctionStrategy::evaluate(const SimulationElement &sim_element) const

Calculates the intensity for scalar particles/interactions. 
";

%feature("docstring")  IInterferenceFunctionStrategy::evaluatePol "double IInterferenceFunctionStrategy::evaluatePol(const SimulationElement &sim_element) const

Calculates the intensity in the presence of polarization of beam and detector. 
";


// File: classILayerRTCoefficients.xml
%feature("docstring") ILayerRTCoefficients "

Interface to access reflection/transmission coefficients.

C++ includes: ILayerRTCoefficients.h
";

%feature("docstring")  ILayerRTCoefficients::~ILayerRTCoefficients "virtual ILayerRTCoefficients::~ILayerRTCoefficients()
";

%feature("docstring")  ILayerRTCoefficients::clone "virtual ILayerRTCoefficients* ILayerRTCoefficients::clone() const =0
";

%feature("docstring")  ILayerRTCoefficients::T1plus "virtual Eigen::Vector2cd ILayerRTCoefficients::T1plus() const =0

The following functions return the transmitted and reflected amplitudes for different incoming beam polarizations and eigenmodes 
";

%feature("docstring")  ILayerRTCoefficients::R1plus "virtual Eigen::Vector2cd ILayerRTCoefficients::R1plus() const =0
";

%feature("docstring")  ILayerRTCoefficients::T2plus "virtual Eigen::Vector2cd ILayerRTCoefficients::T2plus() const =0
";

%feature("docstring")  ILayerRTCoefficients::R2plus "virtual Eigen::Vector2cd ILayerRTCoefficients::R2plus() const =0
";

%feature("docstring")  ILayerRTCoefficients::T1min "virtual Eigen::Vector2cd ILayerRTCoefficients::T1min() const =0
";

%feature("docstring")  ILayerRTCoefficients::R1min "virtual Eigen::Vector2cd ILayerRTCoefficients::R1min() const =0
";

%feature("docstring")  ILayerRTCoefficients::T2min "virtual Eigen::Vector2cd ILayerRTCoefficients::T2min() const =0
";

%feature("docstring")  ILayerRTCoefficients::R2min "virtual Eigen::Vector2cd ILayerRTCoefficients::R2min() const =0
";

%feature("docstring")  ILayerRTCoefficients::getKz "virtual Eigen::Vector2cd ILayerRTCoefficients::getKz() const =0

Returns z-part of the two wavevector eigenmodes. 
";

%feature("docstring")  ILayerRTCoefficients::getScalarT "virtual complex_t ILayerRTCoefficients::getScalarT() const

Scalar value getters; these throw errors by default as they should only be used when the derived object is really scalar 
";

%feature("docstring")  ILayerRTCoefficients::getScalarR "virtual complex_t ILayerRTCoefficients::getScalarR() const 
";

%feature("docstring")  ILayerRTCoefficients::getScalarKz "virtual complex_t ILayerRTCoefficients::getScalarKz() const 
";


// File: classILayout.xml
%feature("docstring") ILayout "

Interface to equip a sample component with various properties.

C++ includes: ILayout.h
";

%feature("docstring")  ILayout::ILayout "ILayout::ILayout()
";

%feature("docstring")  ILayout::~ILayout "virtual ILayout::~ILayout()
";

%feature("docstring")  ILayout::clone "virtual ILayout* ILayout::clone() const =0

Returns a clone of this  ISample object. 
";

%feature("docstring")  ILayout::accept "virtual void ILayout::accept(ISampleVisitor *visitor) const =0

calls the  ISampleVisitor's visit method 
";

%feature("docstring")  ILayout::cloneInvertB "virtual ILayout* ILayout::cloneInvertB() const =0

Returns a clone with inverted magnetic fields. 
";

%feature("docstring")  ILayout::getNumberOfParticles "virtual size_t ILayout::getNumberOfParticles() const =0

Returns number of particles. 
";

%feature("docstring")  ILayout::getParticle "virtual const IAbstractParticle* ILayout::getParticle(size_t index) const =0

Returns information about particle with index. 
";

%feature("docstring")  ILayout::getParticles "virtual SafePointerVector<const IParticle> ILayout::getParticles() const =0

Returns information on all particles (type and abundance) and generates new particles if an  IAbstractParticle denotes a collection 
";

%feature("docstring")  ILayout::getAbundanceOfParticle "virtual double ILayout::getAbundanceOfParticle(size_t index) const =0

Get abundance fraction of particle with index. 
";

%feature("docstring")  ILayout::getTotalAbundance "double ILayout::getTotalAbundance() const

Get total abundance of all particles. 
";

%feature("docstring")  ILayout::getInterferenceFunction "virtual const IInterferenceFunction* ILayout::getInterferenceFunction() const =0

Returns interference function. 
";

%feature("docstring")  ILayout::getTotalParticleSurfaceDensity "virtual double ILayout::getTotalParticleSurfaceDensity() const =0

Returns surface density of all particles. 
";

%feature("docstring")  ILayout::setTotalParticleSurfaceDensity "virtual void ILayout::setTotalParticleSurfaceDensity(double particle_density)=0

Sets surface density of all particles. 
";

%feature("docstring")  ILayout::getApproximation "ILayout::EInterferenceApproximation ILayout::getApproximation() const

Gets the used approximation for particles and interference functions. 
";

%feature("docstring")  ILayout::setApproximation "void ILayout::setApproximation(EInterferenceApproximation approximation)

Sets the used approximation for particles and interference functions. 
";


// File: classIMaterial.xml
%feature("docstring") IMaterial "

Interface to a named material.

C++ includes: IMaterial.h
";

%feature("docstring")  IMaterial::IMaterial "IMaterial::IMaterial(const std::string &name)

Constructor that sets  name. 
";

%feature("docstring")  IMaterial::~IMaterial "virtual IMaterial::~IMaterial()

Destructor. 
";

%feature("docstring")  IMaterial::clone "IMaterial * IMaterial::clone() const

Clone. 
";

%feature("docstring")  IMaterial::isScalarMaterial "virtual bool IMaterial::isScalarMaterial() const

Indicates whether the interaction with the material is scalar. This means that different polarization states will be diffracted equally 
";

%feature("docstring")  IMaterial::getRefractiveIndex "virtual complex_t IMaterial::getRefractiveIndex() const

Return refractive index. 
";

%feature("docstring")  IMaterial::getSpecularScatteringMatrix "Eigen::Matrix2cd IMaterial::getSpecularScatteringMatrix(const kvector_t &k) const

Get the effective scattering matrix from the refractive index and a given wavevector used for the specular calculation. This matrix appears in the one-dimensional Schroedinger equation in the z-direction 
";

%feature("docstring")  IMaterial::getScatteringMatrix "Eigen::Matrix2cd IMaterial::getScatteringMatrix(double k_mag2) const

Get the scattering matrix (~potential V) from the material. This matrix appears in the full three-dimensional Schroedinger equation. 
";

%feature("docstring")  IMaterial::createTransformedMaterial "const IMaterial * IMaterial::createTransformedMaterial(const IRotation &rotation) const

Create a new material that is transformed with respect to this one. 
";


// File: classINamed.xml
%feature("docstring") INamed "

Interface for named objects.

C++ includes: INamed.h
";

%feature("docstring")  INamed::INamed "INamed::INamed()

Default constructor, setting name=\"\". 
";

%feature("docstring")  INamed::INamed "INamed::INamed(std::string name)

Constructor that sets the  name. 
";

%feature("docstring")  INamed::~INamed "INamed::~INamed()

Destructor. 
";

%feature("docstring")  INamed::getName "std::string INamed::getName() const

Returns the name. 
";


// File: classGeometry_1_1InfinitePlane.xml
%feature("docstring") Geometry::InfinitePlane "

The infinite plane is used in masking to mask everythin once and forever.

C++ includes: InfinitePlane.h
";

%feature("docstring")  Geometry::InfinitePlane::InfinitePlane "Geometry::InfinitePlane::InfinitePlane()
";

%feature("docstring")  Geometry::InfinitePlane::clone "InfinitePlane * Geometry::InfinitePlane::clone() const 
";

%feature("docstring")  Geometry::InfinitePlane::contains "bool Geometry::InfinitePlane::contains(double x, double y) const

Returns true if given point is inside or on border of rectangle. 
";

%feature("docstring")  Geometry::InfinitePlane::contains "bool Geometry::InfinitePlane::contains(const Bin1D &binx, const Bin1D &biny) const

Returns true if mid point of two bins is inside rectangle. 
";


// File: classInstrument.xml
%feature("docstring") Instrument "

Assembles beam, detector and their relative positions wrt the sample.

C++ includes: Instrument.h
";

%feature("docstring")  Instrument::Instrument "Instrument::Instrument()
";

%feature("docstring")  Instrument::Instrument "Instrument::Instrument(const Instrument &other)
";

%feature("docstring")  Instrument::~Instrument "virtual Instrument::~Instrument()
";

%feature("docstring")  Instrument::getBeam "Beam Instrument::getBeam() const

Returns the beam data. 
";

%feature("docstring")  Instrument::setBeam "void Instrument::setBeam(const Beam &beam)

Sets the beam data. 
";

%feature("docstring")  Instrument::setBeamParameters "void Instrument::setBeamParameters(double wavelength, double alpha_i, double phi_i)

Sets the beam wavelength and incoming angles. 
";

%feature("docstring")  Instrument::setBeamIntensity "void Instrument::setBeamIntensity(double intensity)

Sets the beam's intensity. 
";

%feature("docstring")  Instrument::setBeamPolarization "void Instrument::setBeamPolarization(const kvector_t &bloch_vector)

Sets the beam's polarization according to the given Bloch vector. 
";

%feature("docstring")  Instrument::getBeamIntensity "double Instrument::getBeamIntensity() const

Returns the beam's intensity. 
";

%feature("docstring")  Instrument::getDetector "const IDetector2D * Instrument::getDetector() const

Returns the detector data. 
";

%feature("docstring")  Instrument::getDetector "IDetector2D * Instrument::getDetector()
";

%feature("docstring")  Instrument::getDetectorAxis "const IAxis & Instrument::getDetectorAxis(size_t index) const

Returns a detector axis. 
";

%feature("docstring")  Instrument::getDetectorDimension "size_t Instrument::getDetectorDimension() const

Returns the detector's dimension. 
";

%feature("docstring")  Instrument::setDetector "void Instrument::setDetector(const IDetector2D &detector)

Sets the detector (axes can be overwritten later) 
";

%feature("docstring")  Instrument::matchDetectorAxes "void Instrument::matchDetectorAxes(const OutputData< double > &output_data)

Sets detector parameters using axes of output data. 
";

%feature("docstring")  Instrument::setDetectorParameters "void Instrument::setDetectorParameters(size_t n_x, double x_min, double x_max, size_t n_y, double y_min, double y_max)

Sets detector parameters using angle ranges. 
";

%feature("docstring")  Instrument::setDetectorAxes "void Instrument::setDetectorAxes(const IAxis &axis0, const IAxis &axis1)

Sets detector parameters using axes. 
";

%feature("docstring")  Instrument::setDetectorResolutionFunction "void Instrument::setDetectorResolutionFunction(IResolutionFunction2D *p_resolution_function)

Sets detector resolution function. 
";

%feature("docstring")  Instrument::setDetectorResolutionFunction "void Instrument::setDetectorResolutionFunction(const IResolutionFunction2D &p_resolution_function)
";

%feature("docstring")  Instrument::setAnalyzerProperties "void Instrument::setAnalyzerProperties(const kvector_t &direction, double efficiency, double total_transmission=1.0)

Sets the polarization analyzer characteristics of the detector. 
";

%feature("docstring")  Instrument::applyDetectorResolution "void Instrument::applyDetectorResolution(OutputData< double > *p_intensity_map) const

apply the detector resolution to the given intensity map 
";

%feature("docstring")  Instrument::getDetectorIntensity "OutputData< double > * Instrument::getDetectorIntensity(const OutputData< double > &data, IDetector2D::EAxesUnits units_type=IDetector2D::DEFAULT) const

Returns clone of the intensity map with detector resolution applied, axes of map will be in requested units 
";

%feature("docstring")  Instrument::createSimulationElements "std::vector< SimulationElement > Instrument::createSimulationElements()

Create a vector of  SimulationElement objects according to the beam, detector and its mask. 
";

%feature("docstring")  Instrument::addParametersToExternalPool "std::string Instrument::addParametersToExternalPool(std::string path, ParameterPool *external_pool, int copy_number=-1) const

Adds parameters from local pool to external pool and recursively calls its direct children. 
";

%feature("docstring")  Instrument::initDetector "void Instrument::initDetector()

init detector with beam settings 
";


// File: classIntegratorComplex.xml
%feature("docstring") IntegratorComplex "

Template class to integrate complex class member functions.

Wraps an two integrators from the GNU Scientific Library. Since this class holds a persistent workspace, we need at least one instance per thread. Standard usage for integration inside a class T:
Create a handle to an integrator: 'auto integrator = make_integrator_complex(this, mem_function)'

Call: 'integrator.integrate(lmin, lmax)'

C++ includes: IntegratorComplex.h
";

%feature("docstring")  IntegratorComplex::IntegratorComplex "IntegratorComplex< T >::IntegratorComplex(const T *p_object, complex_integrand< T > p_member_function)

to integrate p_member_function, which must belong to p_object 
";

%feature("docstring")  IntegratorComplex::~IntegratorComplex "IntegratorComplex< T >::~IntegratorComplex()
";

%feature("docstring")  IntegratorComplex::integrate "complex_t IntegratorComplex< T >::integrate(double lmin, double lmax)

perform the actual integration over the range [lmin, lmax] 
";


// File: classIntegratorMCMiser.xml
%feature("docstring") IntegratorMCMiser "";

%feature("docstring")  IntegratorMCMiser::IntegratorMCMiser "IntegratorMCMiser< T >::IntegratorMCMiser(const T *p_object, miser_integrand< T > p_member_function, size_t dim)

to integrate p_member_function, which must belong to p_object 
";

%feature("docstring")  IntegratorMCMiser::~IntegratorMCMiser "IntegratorMCMiser< T >::~IntegratorMCMiser()
";

%feature("docstring")  IntegratorMCMiser::integrate "double IntegratorMCMiser< T >::integrate(double *min_array, double *max_array, void *params, size_t nbr_points)

perform the actual integration over the ranges [min_array, max_array] 
";


// File: classIntegratorReal.xml
%feature("docstring") IntegratorReal "

Template class to integrate class member functions.

Wraps an integrator from the GNU Scientific Library. Since this class holds a persistent workspace, we need at least one instance per thread. Standard usage for integration inside a class T:
Create a handle to an integrator: 'auto integrator = make_integrator_real(this, mem_function)'

Call: 'integrator.integrate(lmin, lmax)'

C++ includes: IntegratorReal.h
";

%feature("docstring")  IntegratorReal::IntegratorReal "IntegratorReal< T >::IntegratorReal(const T *p_object, real_integrand< T > p_member_function)

to integrate p_member_function, which must belong to p_object 
";

%feature("docstring")  IntegratorReal::~IntegratorReal "IntegratorReal< T >::~IntegratorReal()
";

%feature("docstring")  IntegratorReal::integrate "double IntegratorReal< T >::integrate(double lmin, double lmax)

perform the actual integration over the range [lmin, lmax] 
";


// File: classIntensityDataFunctions.xml
%feature("docstring") IntensityDataFunctions "

Class holding collection of static methods to work with intensity data.

C++ includes: IntensityDataFunctions.h
";


// File: classIntensityDataIOFactory.xml
%feature("docstring") IntensityDataIOFactory "

Provides users with possibility to read and write IntensityData from/to files in different format. Type of the file will be deduced from file name. *.txt - ASCII file with 2D array [nrow][ncol], layout as in numpy. *.int - BornAgain internal ASCII format. *.tif - 32-bits tiff file. If file name ends woth \"*.gz\" or \"*.bz2\" the file will be zipped on the fly using appropriate algorithm.

Usage:

C++ includes: IntensityDataIOFactory.h
";


// File: classIntensityFunctionLog.xml
%feature("docstring") IntensityFunctionLog "

Algorithm for applying log function to the measured intensity.

C++ includes: IIntensityFunction.h
";

%feature("docstring")  IntensityFunctionLog::~IntensityFunctionLog "virtual IntensityFunctionLog::~IntensityFunctionLog()
";

%feature("docstring")  IntensityFunctionLog::clone "virtual IntensityFunctionLog* IntensityFunctionLog::clone() const 
";

%feature("docstring")  IntensityFunctionLog::evaluate "virtual double IntensityFunctionLog::evaluate(double value) const 
";


// File: classIntensityFunctionSqrt.xml
%feature("docstring") IntensityFunctionSqrt "

Algorithm for applying sqrt function to the measured intensity.

C++ includes: IIntensityFunction.h
";

%feature("docstring")  IntensityFunctionSqrt::~IntensityFunctionSqrt "virtual IntensityFunctionSqrt::~IntensityFunctionSqrt()
";

%feature("docstring")  IntensityFunctionSqrt::clone "virtual IntensityFunctionSqrt* IntensityFunctionSqrt::clone() const 
";

%feature("docstring")  IntensityFunctionSqrt::evaluate "virtual double IntensityFunctionSqrt::evaluate(double value) const 
";


// File: classIntensityNormalizer.xml
%feature("docstring") IntensityNormalizer "

Standard  OutputData normalizer, with configurable max_intensity.

C++ includes: IIntensityNormalizer.h
";

%feature("docstring")  IntensityNormalizer::IntensityNormalizer "IntensityNormalizer::IntensityNormalizer(double scale=1.0, double shift=0.0)
";

%feature("docstring")  IntensityNormalizer::~IntensityNormalizer "virtual IntensityNormalizer::~IntensityNormalizer()
";

%feature("docstring")  IntensityNormalizer::clone "IntensityNormalizer * IntensityNormalizer::clone() const 
";

%feature("docstring")  IntensityNormalizer::createNormalizedData "OutputData< double > * IntensityNormalizer::createNormalizedData(const OutputData< double > &data) const 
";

%feature("docstring")  IntensityNormalizer::apply "void IntensityNormalizer::apply(OutputData< double > &data) const 
";

%feature("docstring")  IntensityNormalizer::setMaximumIntensity "virtual void IntensityNormalizer::setMaximumIntensity(double max_intensity)
";


// File: classIntensityScaleAndShiftNormalizer.xml
%feature("docstring") IntensityScaleAndShiftNormalizer "

Simplified  OutputData normalizer, with max_intensity=1.

C++ includes: IIntensityNormalizer.h
";

%feature("docstring")  IntensityScaleAndShiftNormalizer::IntensityScaleAndShiftNormalizer "IntensityScaleAndShiftNormalizer::IntensityScaleAndShiftNormalizer(double scale=1.0, double shift=0.0)
";

%feature("docstring")  IntensityScaleAndShiftNormalizer::~IntensityScaleAndShiftNormalizer "virtual IntensityScaleAndShiftNormalizer::~IntensityScaleAndShiftNormalizer()
";

%feature("docstring")  IntensityScaleAndShiftNormalizer::setMaximumIntensity "virtual void IntensityScaleAndShiftNormalizer::setMaximumIntensity(double max_intensity)
";

%feature("docstring")  IntensityScaleAndShiftNormalizer::clone "virtual IntensityScaleAndShiftNormalizer* IntensityScaleAndShiftNormalizer::clone() const 
";


// File: classInterferenceFunction1DLattice.xml
%feature("docstring") InterferenceFunction1DLattice "

Interference function of 1D lattice.

C++ includes: InterferenceFunction1DLattice.h
";

%feature("docstring")  InterferenceFunction1DLattice::InterferenceFunction1DLattice "InterferenceFunction1DLattice::InterferenceFunction1DLattice(double length, double xi)

constructor

Parameters:
-----------

lattice_params: 
 Lattice parameters

length: 
 Lattice length

xi: 
rotation of lattice with respect to x-axis 
";

%feature("docstring")  InterferenceFunction1DLattice::~InterferenceFunction1DLattice "InterferenceFunction1DLattice::~InterferenceFunction1DLattice()
";

%feature("docstring")  InterferenceFunction1DLattice::clone "InterferenceFunction1DLattice * InterferenceFunction1DLattice::clone() const

Returns a clone of this  ISample object. 
";

%feature("docstring")  InterferenceFunction1DLattice::accept "void InterferenceFunction1DLattice::accept(ISampleVisitor *visitor) const

Calls the  ISampleVisitor's visit method. 
";

%feature("docstring")  InterferenceFunction1DLattice::setDecayFunction "void InterferenceFunction1DLattice::setDecayFunction(const IFTDecayFunction1D &pdf)
";

%feature("docstring")  InterferenceFunction1DLattice::getLatticeParameters "Lattice1DParameters InterferenceFunction1DLattice::getLatticeParameters() const 
";

%feature("docstring")  InterferenceFunction1DLattice::getDecayFunction "const IFTDecayFunction1D * InterferenceFunction1DLattice::getDecayFunction() const 
";

%feature("docstring")  InterferenceFunction1DLattice::evaluate "double InterferenceFunction1DLattice::evaluate(const kvector_t &q) const

Evaluates the interference function for a given wavevector transfer (only the real x and y components are relevant) 
";


// File: classInterferenceFunction2DLattice.xml
%feature("docstring") InterferenceFunction2DLattice "

Interference function of 2D lattice.

C++ includes: InterferenceFunction2DLattice.h
";

%feature("docstring")  InterferenceFunction2DLattice::InterferenceFunction2DLattice "InterferenceFunction2DLattice::InterferenceFunction2DLattice(double length_1, double length_2, double angle, double xi=0.0)

contructor

Parameters:
-----------

length_1: 
 Lattice length 1

length_2: 
 Lattice length 2

angle: 
angle between lattice vectors

xi: 
rotation of lattice with respect to x-axis 
";

%feature("docstring")  InterferenceFunction2DLattice::~InterferenceFunction2DLattice "InterferenceFunction2DLattice::~InterferenceFunction2DLattice()
";

%feature("docstring")  InterferenceFunction2DLattice::clone "InterferenceFunction2DLattice * InterferenceFunction2DLattice::clone() const

Returns a clone of this  ISample object. 
";

%feature("docstring")  InterferenceFunction2DLattice::accept "void InterferenceFunction2DLattice::accept(ISampleVisitor *visitor) const

Calls the  ISampleVisitor's visit method. 
";

%feature("docstring")  InterferenceFunction2DLattice::setDecayFunction "void InterferenceFunction2DLattice::setDecayFunction(const IFTDecayFunction2D &pdf)
";

%feature("docstring")  InterferenceFunction2DLattice::getDecayFunction "const IFTDecayFunction2D * InterferenceFunction2DLattice::getDecayFunction() const 
";

%feature("docstring")  InterferenceFunction2DLattice::evaluate "double InterferenceFunction2DLattice::evaluate(const kvector_t &q) const

Evaluates the interference function for a given wavevector transfer (only the real x and y components are relevant) 
";

%feature("docstring")  InterferenceFunction2DLattice::getLatticeParameters "Lattice2DParameters InterferenceFunction2DLattice::getLatticeParameters() const 
";

%feature("docstring")  InterferenceFunction2DLattice::addParametersToExternalPool "std::string InterferenceFunction2DLattice::addParametersToExternalPool(std::string path, ParameterPool *external_pool, int copy_number=-1) const

Adds parameters from local pool to external pool and recursively calls its direct children. 
";

%feature("docstring")  InterferenceFunction2DLattice::getParticleDensity "double InterferenceFunction2DLattice::getParticleDensity() const

Returns the particle density associated with this 2d lattice. 
";


// File: classInterferenceFunction2DParaCrystal.xml
%feature("docstring") InterferenceFunction2DParaCrystal "

Interference function of 2D paracrystal.

C++ includes: InterferenceFunction2DParaCrystal.h
";

%feature("docstring")  InterferenceFunction2DParaCrystal::InterferenceFunction2DParaCrystal "InterferenceFunction2DParaCrystal::InterferenceFunction2DParaCrystal(double length_1, double length_2, double alpha_lattice, double xi=0.0, double damping_length=0.0)

constructor of 2D paracrystal interference function

Parameters:
-----------

length_1: 
Length of first lattice basis vector.

length_2: 
Length of second lattice basis vector.

alpha_lattice: 
Angle between the lattice basis vectors.

xi: 
Angle between first basis vector and the x-axis of incoming beam.

damping_length: 
Damping length for removing delta function singularity at q=0. 
";

%feature("docstring")  InterferenceFunction2DParaCrystal::~InterferenceFunction2DParaCrystal "InterferenceFunction2DParaCrystal::~InterferenceFunction2DParaCrystal()
";

%feature("docstring")  InterferenceFunction2DParaCrystal::clone "InterferenceFunction2DParaCrystal * InterferenceFunction2DParaCrystal::clone() const

Returns a clone of this  ISample object. 
";

%feature("docstring")  InterferenceFunction2DParaCrystal::accept "void InterferenceFunction2DParaCrystal::accept(ISampleVisitor *visitor) const

Calls the  ISampleVisitor's visit method. 
";

%feature("docstring")  InterferenceFunction2DParaCrystal::setDomainSizes "void InterferenceFunction2DParaCrystal::setDomainSizes(double size_1, double size_2)

Sets the sizes of coherence domains.

Parameters:
-----------

size_1: 
size in first lattice direction

size_2: 
size in second lattice direction 
";

%feature("docstring")  InterferenceFunction2DParaCrystal::setProbabilityDistributions "void InterferenceFunction2DParaCrystal::setProbabilityDistributions(const IFTDistribution2D &pdf_1, const IFTDistribution2D &pdf_2)

Sets the probability distributions (Fourier transformed) for the two lattice directions.

Parameters:
-----------

pdf_1: 
probability distribution in first lattice direction

pdf_2: 
probability distribution in second lattice direction 
";

%feature("docstring")  InterferenceFunction2DParaCrystal::setIntegrationOverXi "void InterferenceFunction2DParaCrystal::setIntegrationOverXi(bool integrate_xi)
";

%feature("docstring")  InterferenceFunction2DParaCrystal::evaluate "double InterferenceFunction2DParaCrystal::evaluate(const kvector_t &q) const

Evaluates the interference function for a given wavevector transfer (only the real x and y components are relevant) 
";

%feature("docstring")  InterferenceFunction2DParaCrystal::getDomainSizes "std::vector< double > InterferenceFunction2DParaCrystal::getDomainSizes() const 
";

%feature("docstring")  InterferenceFunction2DParaCrystal::getProbabilityDistributions "std::vector< const IFTDistribution2D * > InterferenceFunction2DParaCrystal::getProbabilityDistributions() const 
";

%feature("docstring")  InterferenceFunction2DParaCrystal::getIntegrationOverXi "bool InterferenceFunction2DParaCrystal::getIntegrationOverXi() const 
";

%feature("docstring")  InterferenceFunction2DParaCrystal::getDampingLength "double InterferenceFunction2DParaCrystal::getDampingLength() const 
";

%feature("docstring")  InterferenceFunction2DParaCrystal::getLatticeParameters "Lattice2DParameters InterferenceFunction2DParaCrystal::getLatticeParameters() const 
";

%feature("docstring")  InterferenceFunction2DParaCrystal::addParametersToExternalPool "std::string InterferenceFunction2DParaCrystal::addParametersToExternalPool(std::string path, ParameterPool *external_pool, int copy_number=-1) const

Adds parameters from local pool to external pool and recursively calls its direct children. 
";

%feature("docstring")  InterferenceFunction2DParaCrystal::getParticleDensity "double InterferenceFunction2DParaCrystal::getParticleDensity() const

Returns the particle density associated with this 2d paracrystal lattice. 
";


// File: classInterferenceFunctionNone.xml
%feature("docstring") InterferenceFunctionNone "

Default interference function (i.e. absence of any interference)

C++ includes: InterferenceFunctionNone.h
";

%feature("docstring")  InterferenceFunctionNone::InterferenceFunctionNone "InterferenceFunctionNone::InterferenceFunctionNone()
";

%feature("docstring")  InterferenceFunctionNone::clone "InterferenceFunctionNone * InterferenceFunctionNone::clone() const

Returns a clone of this  ISample object. 
";

%feature("docstring")  InterferenceFunctionNone::accept "void InterferenceFunctionNone::accept(ISampleVisitor *visitor) const

Calls the  ISampleVisitor's visit method. 
";

%feature("docstring")  InterferenceFunctionNone::evaluate "double InterferenceFunctionNone::evaluate(const kvector_t &q) const

Evaluates the interference function for a given wavevector transfer (only the real x and y components are relevant) 
";


// File: classInterferenceFunctionRadialParaCrystal.xml
%feature("docstring") InterferenceFunctionRadialParaCrystal "

Interference function of radial paracrystal.

C++ includes: InterferenceFunctionRadialParaCrystal.h
";

%feature("docstring")  InterferenceFunctionRadialParaCrystal::InterferenceFunctionRadialParaCrystal "InterferenceFunctionRadialParaCrystal::InterferenceFunctionRadialParaCrystal(double peak_distance, double damping_length=0.0)

constructor of radial paracrystal interference function

Parameters:
-----------

peak_distance: 
The distance to the first neighbor peak.

width: 
Width parameter in the pair correlation function.

m_corr_length: 
Correlation length of paracrystal. 
";

%feature("docstring")  InterferenceFunctionRadialParaCrystal::~InterferenceFunctionRadialParaCrystal "virtual InterferenceFunctionRadialParaCrystal::~InterferenceFunctionRadialParaCrystal()
";

%feature("docstring")  InterferenceFunctionRadialParaCrystal::clone "InterferenceFunctionRadialParaCrystal * InterferenceFunctionRadialParaCrystal::clone() const

Returns a clone of this  ISample object. 
";

%feature("docstring")  InterferenceFunctionRadialParaCrystal::accept "void InterferenceFunctionRadialParaCrystal::accept(ISampleVisitor *visitor) const

Calls the  ISampleVisitor's visit method. 
";

%feature("docstring")  InterferenceFunctionRadialParaCrystal::setDomainSize "void InterferenceFunctionRadialParaCrystal::setDomainSize(double size)

Sets size of coherence domain.

Parameters:
-----------

size: 
size in lattice direction 
";

%feature("docstring")  InterferenceFunctionRadialParaCrystal::getDomainSize "double InterferenceFunctionRadialParaCrystal::getDomainSize() const

Gets size of coherence domain.

Size in lattice direction 
";

%feature("docstring")  InterferenceFunctionRadialParaCrystal::setKappa "void InterferenceFunctionRadialParaCrystal::setKappa(double kappa)

Sets size-spacing coupling parameter.

Parameters:
-----------

kappa: 
size-spacing coupling parameter 
";

%feature("docstring")  InterferenceFunctionRadialParaCrystal::getKappa "double InterferenceFunctionRadialParaCrystal::getKappa() const

Gets size-spacing coupling parameter.

Size-spacing coupling parameter 
";

%feature("docstring")  InterferenceFunctionRadialParaCrystal::evaluate "double InterferenceFunctionRadialParaCrystal::evaluate(const kvector_t &q) const

Evaluates the interference function for a given wavevector transfer (only the real x and y components are relevant) 
";

%feature("docstring")  InterferenceFunctionRadialParaCrystal::FTPDF "complex_t InterferenceFunctionRadialParaCrystal::FTPDF(double qpar) const 
";

%feature("docstring")  InterferenceFunctionRadialParaCrystal::setProbabilityDistribution "void InterferenceFunctionRadialParaCrystal::setProbabilityDistribution(const IFTDistribution1D &pdf)

Sets the Fourier transformed probability distribution of the nearest particle 
";

%feature("docstring")  InterferenceFunctionRadialParaCrystal::getProbabilityDistribution "const IFTDistribution1D * InterferenceFunctionRadialParaCrystal::getProbabilityDistribution() const

Gets the Fourier transformed probability distribution of the nearest particle 
";

%feature("docstring")  InterferenceFunctionRadialParaCrystal::getPeakDistance "double InterferenceFunctionRadialParaCrystal::getPeakDistance() const 
";

%feature("docstring")  InterferenceFunctionRadialParaCrystal::getDampingLength "double InterferenceFunctionRadialParaCrystal::getDampingLength() const 
";


// File: classIObservable.xml
%feature("docstring") IObservable "

Observable interface from Observer pattern, for 1:n object dependencies.

C++ includes: IObserver.h
";

%feature("docstring")  IObservable::~IObservable "virtual IObservable::~IObservable()
";

%feature("docstring")  IObservable::attachObserver "void IObservable::attachObserver(observer_t obj)

attach observer to the list of observers 
";

%feature("docstring")  IObservable::notifyObservers "void IObservable::notifyObservers()

notify observers about change in status 
";


// File: classIObserver.xml
%feature("docstring") IObserver "

Observer interface from Observer pattern, for 1:n object dependencies.

C++ includes: IObserver.h
";

%feature("docstring")  IObserver::~IObserver "virtual IObserver::~IObserver()
";

%feature("docstring")  IObserver::notify "void IObserver::notify(IObservable *subject)

method which is used by observable subject to notify change in status 
";


// File: classIOutputDataReadStrategy.xml
%feature("docstring") IOutputDataReadStrategy "

Interface for reading strategy of  OutputData from file.

C++ includes: OutputDataReadStrategy.h
";

%feature("docstring")  IOutputDataReadStrategy::~IOutputDataReadStrategy "virtual IOutputDataReadStrategy::~IOutputDataReadStrategy()
";

%feature("docstring")  IOutputDataReadStrategy::readOutputData "virtual OutputData<double >* IOutputDataReadStrategy::readOutputData(std::istream &input_stream)=0
";


// File: classIOutputDataWriteStrategy.xml
%feature("docstring") IOutputDataWriteStrategy "

Strategy interface to write OututData in file.

C++ includes: OutputDataWriteStrategy.h
";

%feature("docstring")  IOutputDataWriteStrategy::IOutputDataWriteStrategy "IOutputDataWriteStrategy::IOutputDataWriteStrategy()
";

%feature("docstring")  IOutputDataWriteStrategy::~IOutputDataWriteStrategy "virtual IOutputDataWriteStrategy::~IOutputDataWriteStrategy()
";

%feature("docstring")  IOutputDataWriteStrategy::writeOutputData "virtual void IOutputDataWriteStrategy::writeOutputData(const OutputData< double > &data, std::ostream &output_stream)=0
";


// File: classIParameterized.xml
%feature("docstring") IParameterized "

Manage a local parameter pool, and a tree of child pools.

C++ includes: IParameterized.h
";

%feature("docstring")  IParameterized::IParameterized "IParameterized::IParameterized()
";

%feature("docstring")  IParameterized::IParameterized "IParameterized::IParameterized(const std::string &name)
";

%feature("docstring")  IParameterized::IParameterized "IParameterized::IParameterized(const IParameterized &other)
";

%feature("docstring")  IParameterized::~IParameterized "virtual IParameterized::~IParameterized()
";

%feature("docstring")  IParameterized::getParameterPool "const ParameterPool * IParameterized::getParameterPool() const

Returns pointer to the parameter pool. 
";

%feature("docstring")  IParameterized::createParameterTree "ParameterPool * IParameterized::createParameterTree() const

Creates new parameter pool, with all local parameters and those of its children. 
";

%feature("docstring")  IParameterized::printParameters "void IParameterized::printParameters() const 
";

%feature("docstring")  IParameterized::registerParameter "void IParameterized::registerParameter(const std::string &name, double *parpointer, const AttLimits &limits=AttLimits::limitless())

Register parameter address in the parameter pool. 
";

%feature("docstring")  IParameterized::setParameterValue "bool IParameterized::setParameterValue(const std::string &name, double value)

Sets the value of the parameter with the given name; returns true in the case of success. 
";

%feature("docstring")  IParameterized::clearParameterPool "void IParameterized::clearParameterPool()

Clears the parameter pool. 
";

%feature("docstring")  IParameterized::addParametersToExternalPool "std::string IParameterized::addParametersToExternalPool(std::string path, ParameterPool *external_pool, int copy_number=-1) const

Adds parameters from local pool to external pool and recursively calls its direct children. 
";


// File: classIParticle.xml
%feature("docstring") IParticle "

Interface for a real particle (one that has position/rotation and form factor)

C++ includes: IParticle.h
";

%feature("docstring")  IParticle::~IParticle "virtual IParticle::~IParticle()
";

%feature("docstring")  IParticle::clone "virtual IParticle* IParticle::clone() const =0

Returns a clone of this  ISample object. 
";

%feature("docstring")  IParticle::cloneInvertB "virtual IParticle* IParticle::cloneInvertB() const =0

Returns a clone with inverted magnetic fields. 
";

%feature("docstring")  IParticle::accept "void IParticle::accept(ISampleVisitor *visitor) const

calls the  ISampleVisitor's visit method 
";

%feature("docstring")  IParticle::createFormFactor "IFormFactor * IParticle::createFormFactor() const

Create a form factor for this particle. 
";

%feature("docstring")  IParticle::createTransformedFormFactor "virtual IFormFactor* IParticle::createTransformedFormFactor(const IRotation *p_rotation, kvector_t translation) const =0

Create a form factor for this particle with an extra scattering factor. 
";

%feature("docstring")  IParticle::getPosition "kvector_t IParticle::getPosition() const

Returns particle position. 
";

%feature("docstring")  IParticle::setPosition "void IParticle::setPosition(kvector_t position)

Sets particle position. 
";

%feature("docstring")  IParticle::setPosition "void IParticle::setPosition(double x, double y, double z)

Sets particle position. 
";

%feature("docstring")  IParticle::getRotation "const IRotation * IParticle::getRotation() const

Returns rotation object. 
";

%feature("docstring")  IParticle::setRotation "void IParticle::setRotation(const IRotation &rotation)

Sets transformation. 
";

%feature("docstring")  IParticle::applyRotation "void IParticle::applyRotation(const IRotation &rotation)

Applies transformation by composing it with the existing one. 
";

%feature("docstring")  IParticle::applyTranslation "void IParticle::applyTranslation(kvector_t displacement)

Applies extra translation by adding it to the current one. 
";


// File: classIPixelMap.xml
%feature("docstring") IPixelMap "

Interface for a function that maps [0,1]x[0,1] to the kvectors in a pixel.

C++ includes: IPixelMap.h
";

%feature("docstring")  IPixelMap::~IPixelMap "virtual IPixelMap::~IPixelMap()
";

%feature("docstring")  IPixelMap::clone "virtual IPixelMap* IPixelMap::clone() const =0
";

%feature("docstring")  IPixelMap::createZeroSizeMap "virtual IPixelMap* IPixelMap::createZeroSizeMap(double x, double y) const =0
";

%feature("docstring")  IPixelMap::getK "virtual kvector_t IPixelMap::getK(double x, double y, double wavelength) const =0
";

%feature("docstring")  IPixelMap::getIntegrationFactor "virtual double IPixelMap::getIntegrationFactor(double x, double y) const =0
";

%feature("docstring")  IPixelMap::getSolidAngle "virtual double IPixelMap::getSolidAngle() const =0
";


// File: classIPrecomputed.xml
%feature("docstring") IPrecomputed "

This singleton interface class gives access to the precomputed constants.

C++ includes: Precomputed.h
";


// File: classIResolutionFunction2D.xml
%feature("docstring") IResolutionFunction2D "

Interface providing two-dimensional resolution function.

C++ includes: IResolutionFunction2D.h
";

%feature("docstring")  IResolutionFunction2D::~IResolutionFunction2D "virtual IResolutionFunction2D::~IResolutionFunction2D()
";

%feature("docstring")  IResolutionFunction2D::evaluateCDF "virtual double IResolutionFunction2D::evaluateCDF(double x, double y) const =0
";

%feature("docstring")  IResolutionFunction2D::clone "virtual IResolutionFunction2D* IResolutionFunction2D::clone() const =0
";


// File: classIRotation.xml
%feature("docstring") IRotation "

An interface for classes representing a rotation.

C++ includes: Rotations.h
";

%feature("docstring")  IRotation::~IRotation "virtual IRotation::~IRotation()
";

%feature("docstring")  IRotation::clone "virtual IRotation* IRotation::clone() const =0

Returns a clone. 
";

%feature("docstring")  IRotation::cloneInvertB "virtual IRotation* IRotation::cloneInvertB() const =0

Returns a clone with inverted magnetic fields. 
";

%feature("docstring")  IRotation::createInverse "virtual IRotation* IRotation::createInverse() const =0

Returns a new  IRotation object that is the current object's inverse. 
";

%feature("docstring")  IRotation::accept "void IRotation::accept(ISampleVisitor *visitor) const

Calls the  ISampleVisitor's visit method. 
";

%feature("docstring")  IRotation::getTransform3D "virtual Geometry::Transform3D IRotation::getTransform3D() const =0

Returns transformation. 
";

%feature("docstring")  IRotation::isIdentity "bool IRotation::isIdentity() const

Returns true if roation matrix is identity matrix (no rotations) 
";


// File: classIRoughness.xml
%feature("docstring") IRoughness "

Interface to equip an interface with a roughness.

C++ includes: IRoughness.h
";

%feature("docstring")  IRoughness::IRoughness "IRoughness::IRoughness()
";

%feature("docstring")  IRoughness::~IRoughness "virtual IRoughness::~IRoughness()
";

%feature("docstring")  IRoughness::accept "virtual void IRoughness::accept(ISampleVisitor *visitor) const

Calls the  ISampleVisitor's visit method. 
";


// File: classISample.xml
%feature("docstring") ISample "

Interface for objects related to scattering.

C++ includes: ISample.h
";

%feature("docstring")  ISample::clone "virtual ISample* ISample::clone() const =0

Returns a clone of this  ISample object. 
";

%feature("docstring")  ISample::cloneInvertB "ISample * ISample::cloneInvertB() const

Returns a clone with inverted magnetic fields. 
";

%feature("docstring")  ISample::accept "virtual void ISample::accept(ISampleVisitor *p_visitor) const =0

Calls the  ISampleVisitor's visit method. 
";

%feature("docstring")  ISample::createDWBASimulation "DWBASimulation * ISample::createDWBASimulation() const

Returns an  ISimulation if DWBA is required. 
";

%feature("docstring")  ISample::printSampleTree "void ISample::printSampleTree()

Outputs the tree of parameters generated from this  ISample object and its descendants. 
";

%feature("docstring")  ISample::containsMagneticMaterial "bool ISample::containsMagneticMaterial() const

Indicates if this  ISample object contains a material with magnetic properties. 
";

%feature("docstring")  ISample::getChildren "std::vector< const ISample * > ISample::getChildren() const

Returns a vector of children (const). Default implementation returns empty vector. 
";

%feature("docstring")  ISample::size "size_t ISample::size() const

Returns number of children. Default implementation returns zero. 
";


// File: classISampleBuilder.xml
%feature("docstring") ISampleBuilder "

Interface to the class capable to build samples to simulate.

C++ includes: ISampleBuilder.h
";

%feature("docstring")  ISampleBuilder::ISampleBuilder "ISampleBuilder::ISampleBuilder()
";

%feature("docstring")  ISampleBuilder::~ISampleBuilder "virtual ISampleBuilder::~ISampleBuilder()
";

%feature("docstring")  ISampleBuilder::buildSample "virtual ISample* ISampleBuilder::buildSample() const 
";

%feature("docstring")  ISampleBuilder::init_from "virtual void ISampleBuilder::init_from(const IComponentService *)
";


// File: classISampleIteratorStrategy.xml
%feature("docstring") ISampleIteratorStrategy "";

%feature("docstring")  ISampleIteratorStrategy::~ISampleIteratorStrategy "virtual ISampleIteratorStrategy::~ISampleIteratorStrategy()
";

%feature("docstring")  ISampleIteratorStrategy::clone "virtual ISampleIteratorStrategy* ISampleIteratorStrategy::clone() const =0
";

%feature("docstring")  ISampleIteratorStrategy::first "virtual IteratorMemento ISampleIteratorStrategy::first(const ISample *p_root)=0
";

%feature("docstring")  ISampleIteratorStrategy::next "virtual void ISampleIteratorStrategy::next(IteratorMemento &iterator_stack) const =0
";

%feature("docstring")  ISampleIteratorStrategy::isDone "virtual bool ISampleIteratorStrategy::isDone(IteratorMemento &iterator_stack) const =0
";


// File: classISampleVisitor.xml
%feature("docstring") ISampleVisitor "

Visitor interface to visit  ISample objects.

From visitor pattern to achieve double dispatch

C++ includes: ISampleVisitor.h
";

%feature("docstring")  ISampleVisitor::ISampleVisitor "ISampleVisitor::ISampleVisitor()
";

%feature("docstring")  ISampleVisitor::~ISampleVisitor "virtual ISampleVisitor::~ISampleVisitor()
";

%feature("docstring")  ISampleVisitor::visit "void ISampleVisitor::visit(const ISample *)
";

%feature("docstring")  ISampleVisitor::visit "void ISampleVisitor::visit(const ICompositeSample *)
";

%feature("docstring")  ISampleVisitor::visit "void ISampleVisitor::visit(const IClusteredParticles *)
";

%feature("docstring")  ISampleVisitor::visit "void ISampleVisitor::visit(const Crystal *)
";

%feature("docstring")  ISampleVisitor::visit "void ISampleVisitor::visit(const ILayout *)
";

%feature("docstring")  ISampleVisitor::visit "void ISampleVisitor::visit(const ParticleLayout *)
";

%feature("docstring")  ISampleVisitor::visit "void ISampleVisitor::visit(const Layer *)
";

%feature("docstring")  ISampleVisitor::visit "void ISampleVisitor::visit(const LayerInterface *)
";

%feature("docstring")  ISampleVisitor::visit "void ISampleVisitor::visit(const MultiLayer *)
";

%feature("docstring")  ISampleVisitor::visit "void ISampleVisitor::visit(const IAbstractParticle *)
";

%feature("docstring")  ISampleVisitor::visit "void ISampleVisitor::visit(const IParticle *)
";

%feature("docstring")  ISampleVisitor::visit "void ISampleVisitor::visit(const Particle *)
";

%feature("docstring")  ISampleVisitor::visit "void ISampleVisitor::visit(const ParticleDistribution *)
";

%feature("docstring")  ISampleVisitor::visit "void ISampleVisitor::visit(const ParticleComposition *)
";

%feature("docstring")  ISampleVisitor::visit "void ISampleVisitor::visit(const MesoCrystal *)
";

%feature("docstring")  ISampleVisitor::visit "void ISampleVisitor::visit(const ParticleCoreShell *)
";

%feature("docstring")  ISampleVisitor::visit "void ISampleVisitor::visit(const IFormFactor *)
";

%feature("docstring")  ISampleVisitor::visit "void ISampleVisitor::visit(const IFormFactorBorn *)
";

%feature("docstring")  ISampleVisitor::visit "void ISampleVisitor::visit(const IFormFactorDecorator *)
";

%feature("docstring")  ISampleVisitor::visit "void ISampleVisitor::visit(const FormFactorAnisoPyramid *)
";

%feature("docstring")  ISampleVisitor::visit "void ISampleVisitor::visit(const FormFactorBox *)
";

%feature("docstring")  ISampleVisitor::visit "void ISampleVisitor::visit(const FormFactorCone *)
";

%feature("docstring")  ISampleVisitor::visit "void ISampleVisitor::visit(const FormFactorCone6 *)
";

%feature("docstring")  ISampleVisitor::visit "void ISampleVisitor::visit(const FormFactorCuboctahedron *)
";

%feature("docstring")  ISampleVisitor::visit "void ISampleVisitor::visit(const FormFactorCrystal *)
";

%feature("docstring")  ISampleVisitor::visit "void ISampleVisitor::visit(const FormFactorCylinder *)
";

%feature("docstring")  ISampleVisitor::visit "void ISampleVisitor::visit(const FormFactorDodecahedron *)
";

%feature("docstring")  ISampleVisitor::visit "void ISampleVisitor::visit(const FormFactorEllipsoidalCylinder *)
";

%feature("docstring")  ISampleVisitor::visit "void ISampleVisitor::visit(const FormFactorFullSphere *)
";

%feature("docstring")  ISampleVisitor::visit "void ISampleVisitor::visit(const FormFactorFullSpheroid *)
";

%feature("docstring")  ISampleVisitor::visit "void ISampleVisitor::visit(const FormFactorGauss *)
";

%feature("docstring")  ISampleVisitor::visit "void ISampleVisitor::visit(const FormFactorHemiEllipsoid *)
";

%feature("docstring")  ISampleVisitor::visit "void ISampleVisitor::visit(const FormFactorIcosahedron *)
";

%feature("docstring")  ISampleVisitor::visit "void ISampleVisitor::visit(const FormFactorLongBoxGauss *)
";

%feature("docstring")  ISampleVisitor::visit "void ISampleVisitor::visit(const FormFactorLongBoxLorentz *)
";

%feature("docstring")  ISampleVisitor::visit "void ISampleVisitor::visit(const FormFactorLorentz *)
";

%feature("docstring")  ISampleVisitor::visit "void ISampleVisitor::visit(const FormFactorPrism3 *)
";

%feature("docstring")  ISampleVisitor::visit "void ISampleVisitor::visit(const FormFactorPrism6 *)
";

%feature("docstring")  ISampleVisitor::visit "void ISampleVisitor::visit(const FormFactorPyramid *)
";

%feature("docstring")  ISampleVisitor::visit "void ISampleVisitor::visit(const FormFactorRipple1 *)
";

%feature("docstring")  ISampleVisitor::visit "void ISampleVisitor::visit(const FormFactorRipple2 *)
";

%feature("docstring")  ISampleVisitor::visit "void ISampleVisitor::visit(const FormFactorSphereGaussianRadius *)
";

%feature("docstring")  ISampleVisitor::visit "void ISampleVisitor::visit(const FormFactorSphereLogNormalRadius *)
";

%feature("docstring")  ISampleVisitor::visit "void ISampleVisitor::visit(const FormFactorTetrahedron *)
";

%feature("docstring")  ISampleVisitor::visit "void ISampleVisitor::visit(const FormFactorTrivial *)
";

%feature("docstring")  ISampleVisitor::visit "void ISampleVisitor::visit(const FormFactorTruncatedCube *)
";

%feature("docstring")  ISampleVisitor::visit "void ISampleVisitor::visit(const FormFactorTruncatedSphere *)
";

%feature("docstring")  ISampleVisitor::visit "void ISampleVisitor::visit(const FormFactorTruncatedSpheroid *)
";

%feature("docstring")  ISampleVisitor::visit "void ISampleVisitor::visit(const FormFactorDWBA *)
";

%feature("docstring")  ISampleVisitor::visit "void ISampleVisitor::visit(const FormFactorDWBAPol *)
";

%feature("docstring")  ISampleVisitor::visit "void ISampleVisitor::visit(const FormFactorWeighted *)
";

%feature("docstring")  ISampleVisitor::visit "void ISampleVisitor::visit(const FormFactorDecoratorDebyeWaller *)
";

%feature("docstring")  ISampleVisitor::visit "void ISampleVisitor::visit(const FormFactorDecoratorFactor *)
";

%feature("docstring")  ISampleVisitor::visit "void ISampleVisitor::visit(const FormFactorDecoratorMaterial *)
";

%feature("docstring")  ISampleVisitor::visit "void ISampleVisitor::visit(const FormFactorDecoratorMultiPositionFactor *)
";

%feature("docstring")  ISampleVisitor::visit "void ISampleVisitor::visit(const FormFactorDecoratorPositionFactor *)
";

%feature("docstring")  ISampleVisitor::visit "void ISampleVisitor::visit(const FormFactorDecoratorRotation *)
";

%feature("docstring")  ISampleVisitor::visit "void ISampleVisitor::visit(const IInterferenceFunction *)
";

%feature("docstring")  ISampleVisitor::visit "void ISampleVisitor::visit(const InterferenceFunction1DLattice *)
";

%feature("docstring")  ISampleVisitor::visit "void ISampleVisitor::visit(const InterferenceFunctionRadialParaCrystal *)
";

%feature("docstring")  ISampleVisitor::visit "void ISampleVisitor::visit(const InterferenceFunction2DLattice *)
";

%feature("docstring")  ISampleVisitor::visit "void ISampleVisitor::visit(const InterferenceFunction2DParaCrystal *)
";

%feature("docstring")  ISampleVisitor::visit "void ISampleVisitor::visit(const InterferenceFunctionNone *)
";

%feature("docstring")  ISampleVisitor::visit "void ISampleVisitor::visit(const IRoughness *)
";

%feature("docstring")  ISampleVisitor::visit "void ISampleVisitor::visit(const LayerRoughness *)
";

%feature("docstring")  ISampleVisitor::visit "void ISampleVisitor::visit(const IRotation *)
";

%feature("docstring")  ISampleVisitor::visit "void ISampleVisitor::visit(const RotationX *)
";

%feature("docstring")  ISampleVisitor::visit "void ISampleVisitor::visit(const RotationY *)
";

%feature("docstring")  ISampleVisitor::visit "void ISampleVisitor::visit(const RotationZ *)
";

%feature("docstring")  ISampleVisitor::visit "void ISampleVisitor::visit(const RotationEuler *)
";

%feature("docstring")  ISampleVisitor::visitEnter "bool ISampleVisitor::visitEnter(const ICompositeSample *)
";

%feature("docstring")  ISampleVisitor::visitLeave "bool ISampleVisitor::visitLeave(const ICompositeSample *)
";

%feature("docstring")  ISampleVisitor::getLevel "int ISampleVisitor::getLevel() const

return current level of the visitor in the composite hierarchy 
";

%feature("docstring")  ISampleVisitor::setLevel "void ISampleVisitor::setLevel(int level)

set current level of the visitor in the composite hierarchy 
";


// File: classISelectionRule.xml
%feature("docstring") ISelectionRule "

Pure virtual base class for selection rules.

C++ includes: ISelectionRule.h
";

%feature("docstring")  ISelectionRule::~ISelectionRule "virtual ISelectionRule::~ISelectionRule()
";

%feature("docstring")  ISelectionRule::clone "virtual ISelectionRule* ISelectionRule::clone() const =0
";

%feature("docstring")  ISelectionRule::coordinateSelected "virtual bool ISelectionRule::coordinateSelected(const IndexVector3D &coordinate) const =0
";


// File: classIsGISAXS08BBuilder.xml
%feature("docstring") IsGISAXS08BBuilder "

Builds sample: 2D paracrystal lattice with isotropic pdfs (IsGISAXS example #8)

it completely 
";

%feature("docstring")  IsGISAXS08BBuilder::IsGISAXS08BBuilder "IsGISAXS08BBuilder::IsGISAXS08BBuilder()
";

%feature("docstring")  IsGISAXS08BBuilder::buildSample "ISample * IsGISAXS08BBuilder::buildSample() const 
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

%feature("docstring")  IsGISAXSDetector::clone "IsGISAXSDetector * IsGISAXSDetector::clone() const 
";

%feature("docstring")  IsGISAXSDetector::~IsGISAXSDetector "virtual IsGISAXSDetector::~IsGISAXSDetector()
";


// File: classGeometry_1_1IShape2D.xml
%feature("docstring") Geometry::IShape2D "

Basic class for all shapes in 2D.

C++ includes: IShape2D.h
";

%feature("docstring")  Geometry::IShape2D::clone "virtual IShape2D* Geometry::IShape2D::clone() const =0
";

%feature("docstring")  Geometry::IShape2D::contains "virtual bool Geometry::IShape2D::contains(double x, double y) const =0

Returns true if point with given coordinates is inside or on border of the shape. 
";

%feature("docstring")  Geometry::IShape2D::contains "virtual bool Geometry::IShape2D::contains(const Bin1D &binx, const Bin1D &biny) const =0

Returns true if area defined by two bins is inside or on border of the shape. 
";


// File: classIShareable.xml
%feature("docstring") IShareable "

Dummy interface used to construct INamedShared and IParameterizedShared.

C++ includes: IShareable.h
";


// File: classISimulation.xml
%feature("docstring") ISimulation "

Interface class, encapsulating different simulations.

C++ includes: ISimulation.h
";

%feature("docstring")  ISimulation::ISimulation "ISimulation::ISimulation()
";

%feature("docstring")  ISimulation::~ISimulation "virtual ISimulation::~ISimulation()
";

%feature("docstring")  ISimulation::clone "ISimulation * ISimulation::clone() const 
";

%feature("docstring")  ISimulation::run "void ISimulation::run()
";

%feature("docstring")  ISimulation::isCompleted "bool ISimulation::isCompleted() const 
";

%feature("docstring")  ISimulation::getRunMessage "std::string ISimulation::getRunMessage() const 
";


// File: classISingleton.xml
%feature("docstring") ISingleton "

Singleton pattern.

C++ includes: ISingleton.h
";


// File: classISpecularInfoMap.xml
%feature("docstring") ISpecularInfoMap "

Interface class providing access to the reflection and transmittion coefficients.

C++ includes: ISpecularInfoMap.h
";

%feature("docstring")  ISpecularInfoMap::ISpecularInfoMap "ISpecularInfoMap::ISpecularInfoMap()
";

%feature("docstring")  ISpecularInfoMap::~ISpecularInfoMap "virtual ISpecularInfoMap::~ISpecularInfoMap()
";

%feature("docstring")  ISpecularInfoMap::clone "virtual ISpecularInfoMap* ISpecularInfoMap::clone() const =0
";

%feature("docstring")  ISpecularInfoMap::getOutCoefficients "virtual const ILayerRTCoefficients* ISpecularInfoMap::getOutCoefficients(double alpha_f, double phi_f, double wavelength) const =0

Retrieves the amplitude coefficients for the given angles. 
";

%feature("docstring")  ISpecularInfoMap::getInCoefficients "virtual const ILayerRTCoefficients* ISpecularInfoMap::getInCoefficients(double alpha_i, double phi_i, double wavelength) const =0

Retrieves the amplitude coefficients for the given angles. 
";


// File: classISquaredFunction.xml
%feature("docstring") ISquaredFunction "

Interface providing measures for deviation between two values.

Used By  ChiSquaredModule for chi2 calculations

C++ includes: ISquaredFunction.h
";

%feature("docstring")  ISquaredFunction::ISquaredFunction "ISquaredFunction::ISquaredFunction()
";

%feature("docstring")  ISquaredFunction::~ISquaredFunction "virtual ISquaredFunction::~ISquaredFunction()
";

%feature("docstring")  ISquaredFunction::clone "virtual ISquaredFunction* ISquaredFunction::clone() const =0
";

%feature("docstring")  ISquaredFunction::calculateSquaredDifference "virtual double ISquaredFunction::calculateSquaredDifference(double real_value, double simulated_value) const =0
";

%feature("docstring")  ISquaredFunction::calculateSquaredError "virtual double ISquaredFunction::calculateSquaredError(double real_value, double simulated_value=0.0) const =0
";


// File: classIteratorMemento.xml
%feature("docstring") IteratorMemento "

Holds all iterator states encountered for  SampleTreeIterator.

C++ includes: SampleTreeIterator.h
";

%feature("docstring")  IteratorMemento::IteratorMemento "IteratorMemento::IteratorMemento()
";

%feature("docstring")  IteratorMemento::~IteratorMemento "virtual IteratorMemento::~IteratorMemento()
";

%feature("docstring")  IteratorMemento::push_state "void IteratorMemento::push_state(const IteratorState &state)
";

%feature("docstring")  IteratorMemento::pop_state "void IteratorMemento::pop_state()
";

%feature("docstring")  IteratorMemento::get_state "IteratorState& IteratorMemento::get_state()
";

%feature("docstring")  IteratorMemento::empty "bool IteratorMemento::empty() const 
";

%feature("docstring")  IteratorMemento::reset "void IteratorMemento::reset()
";

%feature("docstring")  IteratorMemento::getCurrent "const ISample* IteratorMemento::getCurrent()
";

%feature("docstring")  IteratorMemento::next "void IteratorMemento::next()
";

%feature("docstring")  IteratorMemento::size "size_t IteratorMemento::size() const 
";


// File: classIteratorState.xml
%feature("docstring") IteratorState "

Holds state of iterator at single level for  SampleTreeIterator.

C++ includes: SampleTreeIterator.h
";

%feature("docstring")  IteratorState::IteratorState "IteratorState::IteratorState(const ISample *single_element)
";

%feature("docstring")  IteratorState::IteratorState "IteratorState::IteratorState(std::vector< const ISample * > samples)
";

%feature("docstring")  IteratorState::~IteratorState "virtual IteratorState::~IteratorState()
";

%feature("docstring")  IteratorState::getCurrent "const ISample* IteratorState::getCurrent() const 
";

%feature("docstring")  IteratorState::isEnd "bool IteratorState::isEnd() const 
";

%feature("docstring")  IteratorState::next "void IteratorState::next()
";


// File: classKVectorContainer.xml
%feature("docstring") KVectorContainer "

A vector of kvector_t's with optimized location/deallocation.

C++ includes: FastVector.h
";

%feature("docstring")  KVectorContainer::KVectorContainer "KVectorContainer::KVectorContainer(int buff_size=3)
";

%feature("docstring")  KVectorContainer::push_back "void KVectorContainer::push_back(const kvector_t &k)
";

%feature("docstring")  KVectorContainer::clear "void KVectorContainer::clear()
";

%feature("docstring")  KVectorContainer::size "size_t KVectorContainer::size()
";

%feature("docstring")  KVectorContainer::print "void KVectorContainer::print()
";

%feature("docstring")  KVectorContainer::begin "const_iterator KVectorContainer::begin() const 
";

%feature("docstring")  KVectorContainer::end "const_iterator KVectorContainer::end() const 
";


// File: classLargeCylindersInDWBABuilder.xml
%feature("docstring") LargeCylindersInDWBABuilder "

Builds sample with large cylinders for MC integration tests.

C++ includes: CylindersBuilder.h
";

%feature("docstring")  LargeCylindersInDWBABuilder::LargeCylindersInDWBABuilder "LargeCylindersInDWBABuilder::LargeCylindersInDWBABuilder()
";

%feature("docstring")  LargeCylindersInDWBABuilder::buildSample "ISample * LargeCylindersInDWBABuilder::buildSample() const 
";


// File: classLattice.xml
%feature("docstring") Lattice "

A lattice with three basis vectors.

C++ includes: Lattice.h
";

%feature("docstring")  Lattice::Lattice "Lattice::Lattice()
";

%feature("docstring")  Lattice::Lattice "Lattice::Lattice(const kvector_t &a1, const kvector_t &a2, const kvector_t &a3)
";

%feature("docstring")  Lattice::Lattice "Lattice::Lattice(const Lattice &lattice)
";

%feature("docstring")  Lattice::~Lattice "Lattice::~Lattice()
";

%feature("docstring")  Lattice::createTransformedLattice "Lattice Lattice::createTransformedLattice(const IRotation &rotation) const

Create transformed lattice. 
";

%feature("docstring")  Lattice::initialize "void Lattice::initialize() const

Initializes cached data. 
";

%feature("docstring")  Lattice::getBasisVectorA "kvector_t Lattice::getBasisVectorA() const

Returns basis vector a. 
";

%feature("docstring")  Lattice::getBasisVectorB "kvector_t Lattice::getBasisVectorB() const

Returns basis vector b. 
";

%feature("docstring")  Lattice::getBasisVectorC "kvector_t Lattice::getBasisVectorC() const

Returns basis vector c. 
";

%feature("docstring")  Lattice::getVolume "double Lattice::getVolume() const

Returns the volume of the unit cell. 
";

%feature("docstring")  Lattice::getReciprocalLatticeBasis "void Lattice::getReciprocalLatticeBasis(kvector_t &b1, kvector_t &b2, kvector_t &b3) const

Returns the reciprocal basis vectors. 
";

%feature("docstring")  Lattice::getNearestLatticeVectorCoordinates "IndexVector3D Lattice::getNearestLatticeVectorCoordinates(const kvector_t &vector_in) const

Returns the nearest lattice point from a given vector. 
";

%feature("docstring")  Lattice::getNearestReciprocalLatticeVectorCoordinates "IndexVector3D Lattice::getNearestReciprocalLatticeVectorCoordinates(const kvector_t &vector_in) const

Returns the nearest reciprocal lattice point from a given vector. 
";

%feature("docstring")  Lattice::computeReciprocalLatticeVectorsWithinRadius "void Lattice::computeReciprocalLatticeVectorsWithinRadius(const kvector_t &input_vector, double radius) const

Computes a list of reciprocal lattice vectors within a specified distance of a given vector. 
";

%feature("docstring")  Lattice::setSelectionRule "void Lattice::setSelectionRule(const ISelectionRule &p_selection_rule)

Sets a selection rule for the reciprocal vectors. 
";

%feature("docstring")  Lattice::getKVectorContainer "const KVectorContainer& Lattice::getKVectorContainer() const 
";


// File: classLattice1DBuilder.xml
%feature("docstring") Lattice1DBuilder "

Builds sample: cylinders with 1DDL structure factor.

C++ includes: LatticeBuilder.h
";

%feature("docstring")  Lattice1DBuilder::Lattice1DBuilder "Lattice1DBuilder::Lattice1DBuilder()
";

%feature("docstring")  Lattice1DBuilder::buildSample "ISample * Lattice1DBuilder::buildSample() const 
";


// File: classLattice1DParameters.xml
%feature("docstring") Lattice1DParameters "

Additional parameters for 1D lattice.

C++ includes: Lattice1DParameters.h
";

%feature("docstring")  Lattice1DParameters::Lattice1DParameters "Lattice1DParameters::Lattice1DParameters()
";


// File: classLattice2DParameters.xml
%feature("docstring") Lattice2DParameters "

Additional parameters for 2D lattice.

C++ includes: Lattice2DParameters.h
";

%feature("docstring")  Lattice2DParameters::Lattice2DParameters "Lattice2DParameters::Lattice2DParameters()
";


// File: classLayer.xml
%feature("docstring") Layer "

A layer with thickness and material.

C++ includes: Layer.h
";

%feature("docstring")  Layer::Layer "Layer::Layer()

Constructs empty layer. 
";

%feature("docstring")  Layer::Layer "Layer::Layer(const IMaterial &material, double thickness=0)

Constructs layer made of  material with  thickness in nanometers and decoration. 
";

%feature("docstring")  Layer::~Layer "Layer::~Layer()
";

%feature("docstring")  Layer::clone "Layer * Layer::clone() const

Returns a clone of this  ISample object. 
";

%feature("docstring")  Layer::cloneInvertB "Layer * Layer::cloneInvertB() const

Returns a clone with inverted magnetic fields. 
";

%feature("docstring")  Layer::accept "void Layer::accept(ISampleVisitor *visitor) const

Calls the  ISampleVisitor's visit method. 
";

%feature("docstring")  Layer::setThickness "void Layer::setThickness(double thickness)

Sets layer thickness in nanometers. 
";

%feature("docstring")  Layer::getThickness "double Layer::getThickness() const

Returns layer thickness in nanometers. 
";

%feature("docstring")  Layer::setMaterial "void Layer::setMaterial(const IMaterial &material)

Sets  material of the layer. 
";

%feature("docstring")  Layer::setMaterialAndThickness "void Layer::setMaterialAndThickness(const IMaterial &material, double thickness)

Sets  material and  thickness. 
";

%feature("docstring")  Layer::getMaterial "const IMaterial * Layer::getMaterial() const

Returns layer's material. 
";

%feature("docstring")  Layer::getRefractiveIndex "complex_t Layer::getRefractiveIndex() const

Returns refractive index of the layer's material. 
";

%feature("docstring")  Layer::getRefractiveIndex2 "complex_t Layer::getRefractiveIndex2() const

Returns squared refractive index of the layer's material. 
";

%feature("docstring")  Layer::addLayout "void Layer::addLayout(const ILayout &decoration)

sets particle layout 
";

%feature("docstring")  Layer::getNumberOfLayouts "size_t Layer::getNumberOfLayouts() const

gets number of layouts present 
";

%feature("docstring")  Layer::getLayout "const ILayout * Layer::getLayout(size_t i) const

returns particle decoration 
";

%feature("docstring")  Layer::hasDWBASimulation "bool Layer::hasDWBASimulation() const

Returns true if decoration is present. 
";

%feature("docstring")  Layer::createLayoutSimulation "LayerDWBASimulation * Layer::createLayoutSimulation(size_t layout_index) const

creates and returns a  LayerDWBASimulation for the given layout 
";

%feature("docstring")  Layer::getTotalParticleSurfaceDensity "double Layer::getTotalParticleSurfaceDensity(size_t layout_index) const 
";

%feature("docstring")  Layer::getTotalAbundance "double Layer::getTotalAbundance() const 
";

%feature("docstring")  Layer::setNumberOfLayers "void Layer::setNumberOfLayers(size_t n_layers)
";

%feature("docstring")  Layer::getNumberOfLayers "size_t Layer::getNumberOfLayers() const 
";


// File: classLayerDWBASimulation.xml
%feature("docstring") LayerDWBASimulation "

Base class for DWBA simulations in a layer.

C++ includes: LayerDWBASimulation.h
";

%feature("docstring")  LayerDWBASimulation::LayerDWBASimulation "LayerDWBASimulation::LayerDWBASimulation(const Layer *p_layer)
";

%feature("docstring")  LayerDWBASimulation::~LayerDWBASimulation "LayerDWBASimulation::~LayerDWBASimulation()
";

%feature("docstring")  LayerDWBASimulation::clone "LayerDWBASimulation* LayerDWBASimulation::clone() const 
";

%feature("docstring")  LayerDWBASimulation::setSpecularInfo "void LayerDWBASimulation::setSpecularInfo(const LayerSpecularInfo &specular_info)
";


// File: classLayerInterface.xml
%feature("docstring") LayerInterface "

Interface between two layers, possibly with roughness.

C++ includes: LayerInterface.h
";

%feature("docstring")  LayerInterface::~LayerInterface "LayerInterface::~LayerInterface()
";

%feature("docstring")  LayerInterface::clone "LayerInterface * LayerInterface::clone() const

Returns a clone of this  ISample object. 
";

%feature("docstring")  LayerInterface::accept "void LayerInterface::accept(ISampleVisitor *visitor) const

calls the  ISampleVisitor's visit method 
";

%feature("docstring")  LayerInterface::setLayerTop "void LayerInterface::setLayerTop(const Layer *p_layer_top)

Sets link to the layer above the interface. 
";

%feature("docstring")  LayerInterface::setLayerBottom "void LayerInterface::setLayerBottom(const Layer *p_layer_bottom)

Sets link to the layer below the interface. 
";

%feature("docstring")  LayerInterface::setLayersTopBottom "void LayerInterface::setLayersTopBottom(const Layer *p_layer_top, const Layer *p_layer_bottom)

Sets links to the layers above and below the interface. 
";

%feature("docstring")  LayerInterface::setRoughness "void LayerInterface::setRoughness(const LayerRoughness &roughness)

Sets roughness of the interface. 
";

%feature("docstring")  LayerInterface::getRoughness "const LayerRoughness * LayerInterface::getRoughness() const

Returns roughness of the interface. 
";

%feature("docstring")  LayerInterface::getLayerTop "const Layer * LayerInterface::getLayerTop() const

Returns top layer. 
";

%feature("docstring")  LayerInterface::getLayerBottom "const Layer * LayerInterface::getLayerBottom() const

Returns bottom layer. 
";


// File: classLayerRoughness.xml
%feature("docstring") LayerRoughness "

A Roughness of interface between two layers.

Based on the article D.K.G. de Boer, Physical review B, Volume 51, Number 8, 15 February 1995 \"X-ray reflection and transmission by rough surfaces\"

C++ includes: LayerRoughness.h
";

%feature("docstring")  LayerRoughness::LayerRoughness "LayerRoughness::LayerRoughness()
";

%feature("docstring")  LayerRoughness::LayerRoughness "LayerRoughness::LayerRoughness(double sigma, double hurstParameter, double latteralCorrLength)
";

%feature("docstring")  LayerRoughness::clone "LayerRoughness * LayerRoughness::clone() const

Returns a clone of this  ISample object. 
";

%feature("docstring")  LayerRoughness::accept "virtual void LayerRoughness::accept(ISampleVisitor *visitor) const

Calls the  ISampleVisitor's visit method. 
";

%feature("docstring")  LayerRoughness::getSpectralFun "double LayerRoughness::getSpectralFun(const kvector_t &kvec) const

Returns power spectral density of the surface roughness.

Power spectral density of the surface roughness is a result of two-dimensional Fourier transform of the correlation function of the roughness profile.

Based on the article D.K.G. de Boer, Physical review B, Volume 51, Number 8, 15 February 1995 \"X-ray reflection and transmission by rough surfaces\" 
";

%feature("docstring")  LayerRoughness::getCorrFun "double LayerRoughness::getCorrFun(const kvector_t &k) const

Correlation function of the roughness profile. 
";

%feature("docstring")  LayerRoughness::setSigma "void LayerRoughness::setSigma(double sigma)

Sets rms of roughness. 
";

%feature("docstring")  LayerRoughness::getSigma "double LayerRoughness::getSigma() const

Returns rms of roughness. 
";

%feature("docstring")  LayerRoughness::setHurstParameter "void LayerRoughness::setHurstParameter(double hurstParameter)

Sets hurst parameter. It describes how jagged the surface is. 
";

%feature("docstring")  LayerRoughness::getHurstParameter "double LayerRoughness::getHurstParameter() const

Returns hurst parameter. 
";

%feature("docstring")  LayerRoughness::setLatteralCorrLength "void LayerRoughness::setLatteralCorrLength(double latteralCorrLength)

Sets lateral correlation length. 
";

%feature("docstring")  LayerRoughness::getLatteralCorrLength "double LayerRoughness::getLatteralCorrLength() const

Returns latteral correlation length. 
";


// File: classLayerSpecularInfo.xml
%feature("docstring") LayerSpecularInfo "

Holds the amplitude information of the neutron wavefunction in a specific layer for different incoming (outgoing) angles of the neutron beam in the top layer (these amplitudes correspond to the specular part of the neutron wavefunction)

C++ includes: LayerSpecularInfo.h
";

%feature("docstring")  LayerSpecularInfo::LayerSpecularInfo "LayerSpecularInfo::LayerSpecularInfo()
";

%feature("docstring")  LayerSpecularInfo::~LayerSpecularInfo "virtual LayerSpecularInfo::~LayerSpecularInfo()
";

%feature("docstring")  LayerSpecularInfo::clone "LayerSpecularInfo * LayerSpecularInfo::clone() const 
";

%feature("docstring")  LayerSpecularInfo::addRTCoefficients "void LayerSpecularInfo::addRTCoefficients(ISpecularInfoMap *rt_coefficient_map)

Adds the amplitude coefficients for the (time-reversed) outgoing wavevector with the given angles 
";

%feature("docstring")  LayerSpecularInfo::getOutCoefficients "const ILayerRTCoefficients * LayerSpecularInfo::getOutCoefficients(double alpha_f, double phi_f, double wavelength) const

Retrieves the amplitude coefficients for the (time-reversed) outgoing wavevector with the given angles 
";

%feature("docstring")  LayerSpecularInfo::getInCoefficients "const ILayerRTCoefficients * LayerSpecularInfo::getInCoefficients(double alpha_i, double phi_i, double wavelength) const

Retrieves the amplitude coefficients for the incoming wavevector. 
";


// File: classLayerStrategyBuilder.xml
%feature("docstring") LayerStrategyBuilder "

Methods to generate a simulation strategy for decorated  Layer SimulationParameters.

C++ includes: LayerStrategyBuilder.h
";

%feature("docstring")  LayerStrategyBuilder::LayerStrategyBuilder "LayerStrategyBuilder::LayerStrategyBuilder(const Layer &decorated_layer, const Simulation &simulation, const SimulationOptions &sim_params, size_t layout_index)
";

%feature("docstring")  LayerStrategyBuilder::~LayerStrategyBuilder "LayerStrategyBuilder::~LayerStrategyBuilder()
";

%feature("docstring")  LayerStrategyBuilder::setRTInfo "void LayerStrategyBuilder::setRTInfo(const LayerSpecularInfo &specular_info)

Sets reflection/transmission map for DWBA calculation. 
";

%feature("docstring")  LayerStrategyBuilder::createStrategy "IInterferenceFunctionStrategy * LayerStrategyBuilder::createStrategy()

Creates a strategy object which is able to calculate the scattering for fixed k_f. 
";


// File: classLayersWithAbsorptionBuilder.xml
%feature("docstring") LayersWithAbsorptionBuilder "

The  LayersWithAbsorptionBuilder class generates a multilayer with 3 layers with absorption (refractive index has imaginary part). The middle layer is populated with particles. Requires  IComponentService which generates form factors, used for bulk form factors testing.

C++ includes: LayersWithAbsorptionBuilder.h
";

%feature("docstring")  LayersWithAbsorptionBuilder::LayersWithAbsorptionBuilder "LayersWithAbsorptionBuilder::LayersWithAbsorptionBuilder()
";

%feature("docstring")  LayersWithAbsorptionBuilder::~LayersWithAbsorptionBuilder "LayersWithAbsorptionBuilder::~LayersWithAbsorptionBuilder()
";

%feature("docstring")  LayersWithAbsorptionBuilder::init_from "void LayersWithAbsorptionBuilder::init_from(const IComponentService *service)
";

%feature("docstring")  LayersWithAbsorptionBuilder::buildSample "ISample * LayersWithAbsorptionBuilder::buildSample() const 
";


// File: classGeometry_1_1Line.xml
%feature("docstring") Geometry::Line "

The line segment.

C++ includes: Line.h
";

%feature("docstring")  Geometry::Line::Line "Geometry::Line::Line(double x1, double y1, double x2, double y2)

Line segment constructor. 
";

%feature("docstring")  Geometry::Line::clone "Line * Geometry::Line::clone() const 
";

%feature("docstring")  Geometry::Line::contains "bool Geometry::Line::contains(double x, double y) const

Returns true if given point is on this line segment. 
";

%feature("docstring")  Geometry::Line::contains "bool Geometry::Line::contains(const Bin1D &binx, const Bin1D &biny) const

Returns true if the line crosses the area defined by two given bins. 
";


// File: classLLData.xml
%feature("docstring") LLData "

Template class to store data of any type in multi-dimensional space (low-level)

C++ includes: LLData.h
";

%feature("docstring")  LLData::LLData "LLData< T >::LLData(size_t rank, const int *dimensions)
";

%feature("docstring")  LLData::LLData "LLData< T >::LLData(const LLData< T > &right)
";

%feature("docstring")  LLData::~LLData "LLData< T >::~LLData()
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


// File: classMSG_1_1Logger.xml
%feature("docstring") MSG::Logger "

Provides message service.

C++ includes: MessageService.h
";

%feature("docstring")  MSG::Logger::Logger "MSG::Logger::Logger(EMessageLevel level)
";

%feature("docstring")  MSG::Logger::~Logger "MSG::Logger::~Logger()
";

%feature("docstring")  MSG::Logger::NowTime "std::string MSG::Logger::NowTime()
";

%feature("docstring")  MSG::Logger::ToString "const std::string & MSG::Logger::ToString(EMessageLevel level)
";


// File: classExceptions_1_1LogicErrorException.xml
%feature("docstring") Exceptions::LogicErrorException "";

%feature("docstring")  Exceptions::LogicErrorException::LogicErrorException "Exceptions::LogicErrorException::LogicErrorException(const std::string &message)
";


// File: classMagneticCylindersBuilder.xml
%feature("docstring") MagneticCylindersBuilder "

Builds sample: cylinders with magnetic material and non-zero magnetic field.

C++ includes: MagneticParticlesBuilder.h
";

%feature("docstring")  MagneticCylindersBuilder::MagneticCylindersBuilder "MagneticCylindersBuilder::MagneticCylindersBuilder()
";

%feature("docstring")  MagneticCylindersBuilder::buildSample "ISample * MagneticCylindersBuilder::buildSample() const 
";


// File: classMagneticParticleZeroFieldBuilder.xml
%feature("docstring") MagneticParticleZeroFieldBuilder "

Builds sample: cylinders with magnetic material and zero magnetic field.

C++ includes: MagneticParticlesBuilder.h
";

%feature("docstring")  MagneticParticleZeroFieldBuilder::MagneticParticleZeroFieldBuilder "MagneticParticleZeroFieldBuilder::MagneticParticleZeroFieldBuilder()
";

%feature("docstring")  MagneticParticleZeroFieldBuilder::buildSample "ISample * MagneticParticleZeroFieldBuilder::buildSample() const 
";


// File: classMask.xml
%feature("docstring") Mask "

Base class for masking  OutputData elements.

C++ includes: Mask.h
";

%feature("docstring")  Mask::Mask "Mask::Mask(Mask *p_submask=0)
";

%feature("docstring")  Mask::~Mask "virtual Mask::~Mask()
";

%feature("docstring")  Mask::clone "Mask * Mask::clone() const 
";

%feature("docstring")  Mask::getFirstValidIndex "size_t Mask::getFirstValidIndex(size_t start_index)
";

%feature("docstring")  Mask::getNextIndex "size_t Mask::getNextIndex(size_t total_index)
";

%feature("docstring")  Mask::setMaxIndex "void Mask::setMaxIndex(size_t max_index)
";

%feature("docstring")  Mask::getOwnIndex "size_t Mask::getOwnIndex() const 
";

%feature("docstring")  Mask::getMaxIndex "size_t Mask::getMaxIndex() const 
";


// File: classMaskCoordinateEllipseFunction.xml
%feature("docstring") MaskCoordinateEllipseFunction "

Ellipse shaped mask for  OutputData.

C++ includes: MaskCoordinateFunction.h
";

%feature("docstring")  MaskCoordinateEllipseFunction::MaskCoordinateEllipseFunction "MaskCoordinateEllipseFunction::MaskCoordinateEllipseFunction(size_t rank, const int *center, const int *radii)
";

%feature("docstring")  MaskCoordinateEllipseFunction::clone "MaskCoordinateEllipseFunction * MaskCoordinateEllipseFunction::clone() const 
";

%feature("docstring")  MaskCoordinateEllipseFunction::~MaskCoordinateEllipseFunction "MaskCoordinateEllipseFunction::~MaskCoordinateEllipseFunction()
";


// File: classMaskCoordinateFunction.xml
%feature("docstring") MaskCoordinateFunction "

Base class for all kind of  OutputData's masks.

C++ includes: MaskCoordinateFunction.h
";

%feature("docstring")  MaskCoordinateFunction::MaskCoordinateFunction "MaskCoordinateFunction::MaskCoordinateFunction(size_t rank)
";

%feature("docstring")  MaskCoordinateFunction::clone "MaskCoordinateFunction * MaskCoordinateFunction::clone() const 
";

%feature("docstring")  MaskCoordinateFunction::~MaskCoordinateFunction "virtual MaskCoordinateFunction::~MaskCoordinateFunction()
";

%feature("docstring")  MaskCoordinateFunction::isMasked "bool MaskCoordinateFunction::isMasked(size_t rank, const int *coordinates) const 
";

%feature("docstring")  MaskCoordinateFunction::setInvertFlag "void MaskCoordinateFunction::setInvertFlag(bool invert)
";


// File: classMaskCoordinateRectangleFunction.xml
%feature("docstring") MaskCoordinateRectangleFunction "

Rectangular mask for  OutputData.

C++ includes: MaskCoordinateFunction.h
";

%feature("docstring")  MaskCoordinateRectangleFunction::MaskCoordinateRectangleFunction "MaskCoordinateRectangleFunction::MaskCoordinateRectangleFunction(size_t rank, const int *minima, const int *maxima)
";

%feature("docstring")  MaskCoordinateRectangleFunction::clone "MaskCoordinateRectangleFunction * MaskCoordinateRectangleFunction::clone() const 
";

%feature("docstring")  MaskCoordinateRectangleFunction::~MaskCoordinateRectangleFunction "MaskCoordinateRectangleFunction::~MaskCoordinateRectangleFunction()
";


// File: classMaskCoordinates.xml
%feature("docstring") MaskCoordinates "

Mask based on the coordinates.

C++ includes: Mask.h
";

%feature("docstring")  MaskCoordinates::MaskCoordinates "MaskCoordinates::MaskCoordinates(size_t rank, const int *dims, Mask *p_submask=0)
";

%feature("docstring")  MaskCoordinates::~MaskCoordinates "MaskCoordinates::~MaskCoordinates()
";

%feature("docstring")  MaskCoordinates::clone "MaskCoordinates * MaskCoordinates::clone() const 
";

%feature("docstring")  MaskCoordinates::setMaskCoordinateFunction "void MaskCoordinates::setMaskCoordinateFunction(MaskCoordinateFunction *p_mask_function)
";


// File: classMaskIndexModulus.xml
%feature("docstring") MaskIndexModulus "

Mask based on the index modulo a given number.

C++ includes: Mask.h
";

%feature("docstring")  MaskIndexModulus::MaskIndexModulus "MaskIndexModulus::MaskIndexModulus(size_t modulus, size_t remainder, Mask *p_submask=0)
";

%feature("docstring")  MaskIndexModulus::~MaskIndexModulus "virtual MaskIndexModulus::~MaskIndexModulus()
";

%feature("docstring")  MaskIndexModulus::clone "MaskIndexModulus * MaskIndexModulus::clone() const 
";


// File: classMatrixRTCoefficients.xml
%feature("docstring") MatrixRTCoefficients "

Specular reflection and transmission coefficients in a layer in case of 2x2 matrix interactions between the layers and the scattered particle.

C++ includes: MatrixRTCoefficients.h
";

%feature("docstring")  MatrixRTCoefficients::MatrixRTCoefficients "MatrixRTCoefficients::MatrixRTCoefficients()
";

%feature("docstring")  MatrixRTCoefficients::~MatrixRTCoefficients "virtual MatrixRTCoefficients::~MatrixRTCoefficients()
";

%feature("docstring")  MatrixRTCoefficients::clone "MatrixRTCoefficients * MatrixRTCoefficients::clone() const 
";

%feature("docstring")  MatrixRTCoefficients::T1plus "Eigen::Vector2cd MatrixRTCoefficients::T1plus() const

The following functions return the transmitted and reflected amplitudes for different incoming beam polarizations and eigenmodes 
";

%feature("docstring")  MatrixRTCoefficients::R1plus "Eigen::Vector2cd MatrixRTCoefficients::R1plus() const 
";

%feature("docstring")  MatrixRTCoefficients::T2plus "Eigen::Vector2cd MatrixRTCoefficients::T2plus() const 
";

%feature("docstring")  MatrixRTCoefficients::R2plus "Eigen::Vector2cd MatrixRTCoefficients::R2plus() const 
";

%feature("docstring")  MatrixRTCoefficients::T1min "Eigen::Vector2cd MatrixRTCoefficients::T1min() const 
";

%feature("docstring")  MatrixRTCoefficients::R1min "Eigen::Vector2cd MatrixRTCoefficients::R1min() const 
";

%feature("docstring")  MatrixRTCoefficients::T2min "Eigen::Vector2cd MatrixRTCoefficients::T2min() const 
";

%feature("docstring")  MatrixRTCoefficients::R2min "Eigen::Vector2cd MatrixRTCoefficients::R2min() const 
";

%feature("docstring")  MatrixRTCoefficients::getKz "Eigen::Vector2cd MatrixRTCoefficients::getKz() const

Returns z-part of the two wavevector eigenmodes. 
";


// File: classMatrixSpecularInfoMap.xml
%feature("docstring") MatrixSpecularInfoMap "

Implementation of  ISpecularInfoMap for matrix valued reflection/ transmission coefficients.

C++ includes: MatrixSpecularInfoMap.h
";

%feature("docstring")  MatrixSpecularInfoMap::MatrixSpecularInfoMap "MatrixSpecularInfoMap::MatrixSpecularInfoMap(const MultiLayer *multilayer, int layer)
";

%feature("docstring")  MatrixSpecularInfoMap::~MatrixSpecularInfoMap "virtual MatrixSpecularInfoMap::~MatrixSpecularInfoMap()
";

%feature("docstring")  MatrixSpecularInfoMap::clone "MatrixSpecularInfoMap * MatrixSpecularInfoMap::clone() const 
";

%feature("docstring")  MatrixSpecularInfoMap::getOutCoefficients "const MatrixRTCoefficients * MatrixSpecularInfoMap::getOutCoefficients(double alpha_f, double phi_f, double wavelength) const

Retrieves the amplitude coefficients for the given angles. 
";

%feature("docstring")  MatrixSpecularInfoMap::getInCoefficients "const MatrixRTCoefficients * MatrixSpecularInfoMap::getInCoefficients(double alpha_i, double phi_i, double wavelength) const

Retrieves the amplitude coefficients for the given angles. 
";


// File: classMCMiserIntegrator.xml
%feature("docstring") MCMiserIntegrator "

Template class to use Monte Carlo MISER integration of class member functions.

Wraps an integrator from GNU Scientific Library. Since this class holds a persistent workspace, we need at least one instance per thread. Standard usage for integration inside a class T:
Create a handle to an integrator: 'auto integrator = make_integrator_miser(this, mem_function, dimension)'

Call: 'integrator.integrate(lmin, lmax, data, nbr_points)'

C++ includes: IntegratorMCMiser.h
";


// File: classMesoCrystal.xml
%feature("docstring") MesoCrystal "

A particle with an internal structure of smaller particles.

C++ includes: MesoCrystal.h
";

%feature("docstring")  MesoCrystal::MesoCrystal "MesoCrystal::MesoCrystal(IClusteredParticles *p_particle_structure, IFormFactor *p_form_factor)
";

%feature("docstring")  MesoCrystal::MesoCrystal "MesoCrystal::MesoCrystal(const IClusteredParticles &particle_structure, IFormFactor &form_factor)
";

%feature("docstring")  MesoCrystal::~MesoCrystal "MesoCrystal::~MesoCrystal()
";

%feature("docstring")  MesoCrystal::clone "MesoCrystal * MesoCrystal::clone() const

Returns a clone of this  ISample object. 
";

%feature("docstring")  MesoCrystal::cloneInvertB "MesoCrystal * MesoCrystal::cloneInvertB() const

Returns a clone with inverted magnetic fields. 
";

%feature("docstring")  MesoCrystal::accept "void MesoCrystal::accept(ISampleVisitor *visitor) const

Calls the  ISampleVisitor's visit method. 
";

%feature("docstring")  MesoCrystal::setAmbientMaterial "void MesoCrystal::setAmbientMaterial(const IMaterial &material)

Sets the refractive index of the ambient material (which influences its scattering power) 
";

%feature("docstring")  MesoCrystal::getAmbientMaterial "const IMaterial * MesoCrystal::getAmbientMaterial() const

Returns particle's material. 
";

%feature("docstring")  MesoCrystal::createTransformedFormFactor "IFormFactor * MesoCrystal::createTransformedFormFactor(const IRotation *p_rotation, kvector_t translation) const

Create a form factor for this particle with an extra scattering factor. 
";

%feature("docstring")  MesoCrystal::getClusteredParticles "const IClusteredParticles * MesoCrystal::getClusteredParticles() const

get the internal structure, which is in principle unbounded in space (eg. an infinite crystal) 
";


// File: classMesoCrystalBuilder.xml
%feature("docstring") MesoCrystalBuilder "

Builds sample: mesocrystals of cylindrical shape composed by spherical nanoparticles.

C++ includes: MesoCrystalBuilder.h
";

%feature("docstring")  MesoCrystalBuilder::MesoCrystalBuilder "MesoCrystalBuilder::MesoCrystalBuilder()
";

%feature("docstring")  MesoCrystalBuilder::~MesoCrystalBuilder "virtual MesoCrystalBuilder::~MesoCrystalBuilder()
";

%feature("docstring")  MesoCrystalBuilder::buildSample "ISample * MesoCrystalBuilder::buildSample() const 
";


// File: classMultiLayer.xml
%feature("docstring") MultiLayer "

Stack of layers one below the other.

Example of system of 4 layers (3 interfaces):

ambience layer #0 z=getLayerBottomZ(0)=0.0 ------ interface #0 Fe, 20A layer #1 z=getLayerBottomZ(1)=-20.0 ------ interface #1 Cr, 40A layer #2 z=getLayerBottomZ(2)=-60.0 ------ interface #2 substrate layer #3 z=getLayerBottomZ(3)=-60.0

C++ includes: MultiLayer.h
";

%feature("docstring")  MultiLayer::MultiLayer "MultiLayer::MultiLayer()
";

%feature("docstring")  MultiLayer::~MultiLayer "MultiLayer::~MultiLayer()
";

%feature("docstring")  MultiLayer::accept "void MultiLayer::accept(ISampleVisitor *visitor) const

calls the  ISampleVisitor's visit method 
";

%feature("docstring")  MultiLayer::getNumberOfLayers "size_t MultiLayer::getNumberOfLayers() const

Returns number of layers in multilayer. 
";

%feature("docstring")  MultiLayer::getNumberOfInterfaces "size_t MultiLayer::getNumberOfInterfaces() const

Returns number of interfaces in multilayer. 
";

%feature("docstring")  MultiLayer::addLayer "void MultiLayer::addLayer(const Layer &p_child)

Adds object to multilayer, overrides from  ISample.

Adds layer with default (zero) roughness. 
";

%feature("docstring")  MultiLayer::addLayerWithTopRoughness "void MultiLayer::addLayerWithTopRoughness(const Layer &layer, const LayerRoughness &roughness)

Adds layer with top roughness. 
";

%feature("docstring")  MultiLayer::getLayer "const Layer * MultiLayer::getLayer(size_t i_layer) const

Returns layer with given index. 
";

%feature("docstring")  MultiLayer::getLayerInterface "const LayerInterface * MultiLayer::getLayerInterface(size_t i_interface) const

Returns layer with given index. 
";

%feature("docstring")  MultiLayer::getLayerBottomZ "double MultiLayer::getLayerBottomZ(size_t i_layer) const

Returns z-coordinate of the layer's bottom. 
";

%feature("docstring")  MultiLayer::getLayerThickness "double MultiLayer::getLayerThickness(size_t i_layer) const

Returns thickness of layer. 
";

%feature("docstring")  MultiLayer::getLayerTopInterface "const LayerInterface * MultiLayer::getLayerTopInterface(size_t i_layer) const

Returns top interface of layer.

Returns pointer to the top interface of the layer. nInterfaces = nLayers-1, first layer in multilayer doesn't have interface. 
";

%feature("docstring")  MultiLayer::getLayerBottomInterface "const LayerInterface * MultiLayer::getLayerBottomInterface(size_t i_layer) const

Returns bottom interface of layer.

Returns pointer to the bottom interface of the layer. 
";

%feature("docstring")  MultiLayer::clear "void MultiLayer::clear()

Destructs allocated objects. 
";

%feature("docstring")  MultiLayer::clone "MultiLayer * MultiLayer::clone() const

Returns alone of multilayer with clones of all layers and recreated interfaces between layers 
";

%feature("docstring")  MultiLayer::cloneInvertB "MultiLayer * MultiLayer::cloneInvertB() const

Returns a clone with inverted magnetic fields. 
";

%feature("docstring")  MultiLayer::setCrossCorrLength "void MultiLayer::setCrossCorrLength(double crossCorrLength)

Sets cross correlation length of roughnesses between interfaces. 
";

%feature("docstring")  MultiLayer::getCrossCorrLength "double MultiLayer::getCrossCorrLength() const

Returns cross correlation length of roughnesses between interfaces. 
";

%feature("docstring")  MultiLayer::getCrossCorrSpectralFun "double MultiLayer::getCrossCorrSpectralFun(const kvector_t &kvec, size_t j, size_t k) const

! correlation function of roughnesses between the interfaces

Fourier transform of the correlation function of roughnesses between the interfaces

Fourier transform of the correlation function of roughnesses between the interfaces j,k - indexes of layers in multilayer whose bottom interfaces we are considering 
";

%feature("docstring")  MultiLayer::setLayerThickness "void MultiLayer::setLayerThickness(size_t i_layer, double thickness)

Sets thickness of layer. 
";

%feature("docstring")  MultiLayer::createDWBASimulation "MultiLayerDWBASimulation * MultiLayer::createDWBASimulation() const

look for the presence of DWBA terms (e.g. included particles) and return  ISimulation if needed 
";

%feature("docstring")  MultiLayer::getIndexOfLayer "int MultiLayer::getIndexOfLayer(const Layer *layer) const

returns layer index 
";

%feature("docstring")  MultiLayer::requiresMatrixRTCoefficients "bool MultiLayer::requiresMatrixRTCoefficients() const

returns true if contains magnetic materials and matrix calculations are required 
";

%feature("docstring")  MultiLayer::zToLayerIndex "size_t MultiLayer::zToLayerIndex(double z_value)

returns layer index corresponding to given global z coordinate 
";


// File: classMultiLayerDWBASimulation.xml
%feature("docstring") MultiLayerDWBASimulation "

This is the class that will perform a DWBA calculation with the given sample and simulation parameters.

C++ includes: MultiLayerDWBASimulation.h
";

%feature("docstring")  MultiLayerDWBASimulation::MultiLayerDWBASimulation "MultiLayerDWBASimulation::MultiLayerDWBASimulation(const MultiLayer *p_multi_layer)
";

%feature("docstring")  MultiLayerDWBASimulation::~MultiLayerDWBASimulation "MultiLayerDWBASimulation::~MultiLayerDWBASimulation()
";

%feature("docstring")  MultiLayerDWBASimulation::clone "MultiLayerDWBASimulation* MultiLayerDWBASimulation::clone() const 
";

%feature("docstring")  MultiLayerDWBASimulation::init "void MultiLayerDWBASimulation::init(const Simulation &simulation, std::vector< SimulationElement >::iterator begin_it, std::vector< SimulationElement >::iterator end_it)

Initializes the simulation with the parameters from simulation. 
";

%feature("docstring")  MultiLayerDWBASimulation::run "void MultiLayerDWBASimulation::run()
";


// File: classMultiLayerRoughnessDWBASimulation.xml
%feature("docstring") MultiLayerRoughnessDWBASimulation "

Calculation of diffuse reflection from multilayer with rough interfaces.

C++ includes: MultiLayerRoughnessDWBASimulation.h
";

%feature("docstring")  MultiLayerRoughnessDWBASimulation::MultiLayerRoughnessDWBASimulation "MultiLayerRoughnessDWBASimulation::MultiLayerRoughnessDWBASimulation(const MultiLayer *p_multi_layer)
";

%feature("docstring")  MultiLayerRoughnessDWBASimulation::~MultiLayerRoughnessDWBASimulation "MultiLayerRoughnessDWBASimulation::~MultiLayerRoughnessDWBASimulation()
";

%feature("docstring")  MultiLayerRoughnessDWBASimulation::clone "MultiLayerRoughnessDWBASimulation* MultiLayerRoughnessDWBASimulation::clone() const 
";

%feature("docstring")  MultiLayerRoughnessDWBASimulation::run "void MultiLayerRoughnessDWBASimulation::run()
";

%feature("docstring")  MultiLayerRoughnessDWBASimulation::setSpecularInfo "void MultiLayerRoughnessDWBASimulation::setSpecularInfo(size_t i_layer, const LayerSpecularInfo &specular_info)

Sets magnetic reflection/transmission info for specific layer. 
";

%feature("docstring")  MultiLayerRoughnessDWBASimulation::evaluate "double MultiLayerRoughnessDWBASimulation::evaluate(const SimulationElement &sim_element)
";


// File: classMultiLayerWithRoughnessBuilder.xml
%feature("docstring") MultiLayerWithRoughnessBuilder "

Builds sample: layers with correlated roughness.

C++ includes: MultiLayerWithRoughnessBuilder.h
";

%feature("docstring")  MultiLayerWithRoughnessBuilder::MultiLayerWithRoughnessBuilder "MultiLayerWithRoughnessBuilder::MultiLayerWithRoughnessBuilder()
";

%feature("docstring")  MultiLayerWithRoughnessBuilder::buildSample "ISample * MultiLayerWithRoughnessBuilder::buildSample() const 
";


// File: classMultipleLayoutBuilder.xml
%feature("docstring") MultipleLayoutBuilder "

Builds sample: mixture of cylinders and prisms without interference using multiple particle layouts.

C++ includes: MultipleLayoutBuilder.h
";

%feature("docstring")  MultipleLayoutBuilder::MultipleLayoutBuilder "MultipleLayoutBuilder::MultipleLayoutBuilder()
";

%feature("docstring")  MultipleLayoutBuilder::buildSample "ISample * MultipleLayoutBuilder::buildSample() const 
";


// File: classExceptions_1_1NotImplementedException.xml
%feature("docstring") Exceptions::NotImplementedException "";

%feature("docstring")  Exceptions::NotImplementedException::NotImplementedException "Exceptions::NotImplementedException::NotImplementedException(const std::string &message)
";


// File: classExceptions_1_1NullPointerException.xml
%feature("docstring") Exceptions::NullPointerException "";

%feature("docstring")  Exceptions::NullPointerException::NullPointerException "Exceptions::NullPointerException::NullPointerException(const std::string &message)
";


// File: classOffSpecSimulation.xml
%feature("docstring") OffSpecSimulation "

Main class to run an off-specular simulation.

C++ includes: OffSpecSimulation.h
";

%feature("docstring")  OffSpecSimulation::OffSpecSimulation "OffSpecSimulation::OffSpecSimulation()
";

%feature("docstring")  OffSpecSimulation::OffSpecSimulation "OffSpecSimulation::OffSpecSimulation(const ISample &p_sample)
";

%feature("docstring")  OffSpecSimulation::OffSpecSimulation "OffSpecSimulation::OffSpecSimulation(SampleBuilder_t p_sample_builder)
";

%feature("docstring")  OffSpecSimulation::~OffSpecSimulation "virtual OffSpecSimulation::~OffSpecSimulation()
";

%feature("docstring")  OffSpecSimulation::clone "OffSpecSimulation * OffSpecSimulation::clone() const 
";

%feature("docstring")  OffSpecSimulation::prepareSimulation "void OffSpecSimulation::prepareSimulation()

Put into a clean state for running a simulation. 
";

%feature("docstring")  OffSpecSimulation::getNumberOfSimulationElements "int OffSpecSimulation::getNumberOfSimulationElements() const

Gets the number of elements this simulation needs to calculate. 
";

%feature("docstring")  OffSpecSimulation::getOutputData "const OutputData<double>* OffSpecSimulation::getOutputData() const

Returns detector intensity map. 
";

%feature("docstring")  OffSpecSimulation::getDetectorIntensity "OutputData< double > * OffSpecSimulation::getDetectorIntensity(IDetector2D::EAxesUnits units_type=IDetector2D::DEFAULT) const

Returns clone of the detector intensity map. 
";

%feature("docstring")  OffSpecSimulation::getIntensityData "Histogram2D * OffSpecSimulation::getIntensityData() const

Returns clone of the detector intensity map in the form of 2D histogram. 
";

%feature("docstring")  OffSpecSimulation::setInstrument "void OffSpecSimulation::setInstrument(const Instrument &instrument)

Sets the instrument containing beam and detector information. 
";

%feature("docstring")  OffSpecSimulation::getInstrument "const Instrument& OffSpecSimulation::getInstrument() const

Returns the instrument containing beam and detector information. 
";

%feature("docstring")  OffSpecSimulation::setBeamParameters "void OffSpecSimulation::setBeamParameters(double lambda, const IAxis &alpha_axis, double phi_i)

Sets beam parameters from here (forwarded to  Instrument) 
";

%feature("docstring")  OffSpecSimulation::setBeamIntensity "void OffSpecSimulation::setBeamIntensity(double intensity)

Sets beam intensity from here (forwarded to  Instrument) 
";

%feature("docstring")  OffSpecSimulation::setBeamPolarization "void OffSpecSimulation::setBeamPolarization(const kvector_t &bloch_vector)

Sets the beam polarization according to the given Bloch vector. 
";

%feature("docstring")  OffSpecSimulation::setDetectorParameters "void OffSpecSimulation::setDetectorParameters(const OutputData< double > &output_data)

Sets detector parameters using axes of output data. 
";

%feature("docstring")  OffSpecSimulation::setDetectorParameters "void OffSpecSimulation::setDetectorParameters(size_t n_x, double x_min, double x_max, size_t n_y, double y_min, double y_max)

Sets detector parameters using angle ranges. 
";

%feature("docstring")  OffSpecSimulation::setDetectorResolutionFunction "void OffSpecSimulation::setDetectorResolutionFunction(const IResolutionFunction2D &resolution_function)

Define resolution function for detector. 
";

%feature("docstring")  OffSpecSimulation::removeDetectorResolutionFunction "void OffSpecSimulation::removeDetectorResolutionFunction()

Removes detector resolution function. 
";

%feature("docstring")  OffSpecSimulation::setAnalyzerProperties "void OffSpecSimulation::setAnalyzerProperties(const kvector_t &direction, double efficiency, double total_transmission=1.0)

Sets the polarization analyzer characteristics of the detector. 
";

%feature("docstring")  OffSpecSimulation::addParametersToExternalPool "std::string OffSpecSimulation::addParametersToExternalPool(std::string path, ParameterPool *external_pool, int copy_number=-1) const

Adds parameters from local pool to external pool and recursively calls its direct children. 
";


// File: classOMPISimulation.xml
%feature("docstring") OMPISimulation "";

%feature("docstring")  OMPISimulation::runSimulation "void OMPISimulation::runSimulation(Simulation *simulation)
";


// File: classUtils_1_1OrderedMap.xml
%feature("docstring") Utils::OrderedMap "

Ordered map which saves the order of insertion.

C++ includes: Utils.h
";

%feature("docstring")  Utils::OrderedMap::OrderedMap "Utils::OrderedMap< Key, Object >::OrderedMap()
";

%feature("docstring")  Utils::OrderedMap::~OrderedMap "virtual Utils::OrderedMap< Key, Object >::~OrderedMap()
";

%feature("docstring")  Utils::OrderedMap::clear "void Utils::OrderedMap< Key, Object >::clear()
";

%feature("docstring")  Utils::OrderedMap::begin "const_iterator Utils::OrderedMap< Key, Object >::begin() const 
";

%feature("docstring")  Utils::OrderedMap::end "const_iterator Utils::OrderedMap< Key, Object >::end() const 
";

%feature("docstring")  Utils::OrderedMap::begin "iterator Utils::OrderedMap< Key, Object >::begin()
";

%feature("docstring")  Utils::OrderedMap::end "iterator Utils::OrderedMap< Key, Object >::end()
";

%feature("docstring")  Utils::OrderedMap::size "size_t Utils::OrderedMap< Key, Object >::size()
";

%feature("docstring")  Utils::OrderedMap::insert "void Utils::OrderedMap< Key, Object >::insert(const Key &key, const Object &object)
";

%feature("docstring")  Utils::OrderedMap::find "iterator Utils::OrderedMap< Key, Object >::find(const Key &key)
";

%feature("docstring")  Utils::OrderedMap::find "const_iterator Utils::OrderedMap< Key, Object >::find(const Key &key) const 
";

%feature("docstring")  Utils::OrderedMap::erase "size_t Utils::OrderedMap< Key, Object >::erase(const Key &key)
";

%feature("docstring")  Utils::OrderedMap::value "const Object& Utils::OrderedMap< Key, Object >::value(const Key &key)
";


// File: classExceptions_1_1OutOfBoundsException.xml
%feature("docstring") Exceptions::OutOfBoundsException "";

%feature("docstring")  Exceptions::OutOfBoundsException::OutOfBoundsException "Exceptions::OutOfBoundsException::OutOfBoundsException(const std::string &message)
";


// File: classOutputData.xml
%feature("docstring") OutputData "

Template class to store data of any type in multi-dimensional space.

C++ includes: OutputData.h
";

%feature("docstring")  OutputData::OutputData "OutputData< T >::OutputData()
";

%feature("docstring")  OutputData::~OutputData "OutputData< T >::~OutputData()
";

%feature("docstring")  OutputData::clone "OutputData< T > * OutputData< T >::clone() const 
";

%feature("docstring")  OutputData::copyFrom "void OutputData< T >::copyFrom(const OutputData< T > &x)
";

%feature("docstring")  OutputData::copyShapeFrom "void OutputData< T >::copyShapeFrom(const OutputData< U > &other)
";

%feature("docstring")  OutputData::addAxis "void OutputData< T >::addAxis(const IAxis &new_axis)
";

%feature("docstring")  OutputData::addAxis "void OutputData< T >::addAxis(const std::string &name, size_t size, double start, double end)
";

%feature("docstring")  OutputData::getAxis "const IAxis * OutputData< T >::getAxis(size_t serial_number) const

returns axis with given serial number 
";

%feature("docstring")  OutputData::getAxis "const IAxis * OutputData< T >::getAxis(const std::string &axis_name) const

returns axis with given name 
";

%feature("docstring")  OutputData::getAxisSerialNumber "size_t OutputData< T >::getAxisSerialNumber(const std::string &axis_name) const

returns serial number of axis with given name 
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

%feature("docstring")  OutputData::fillRawDataArray "void OutputData< T >::fillRawDataArray(T *destination) const

fill raw array with data 
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

%feature("docstring")  OutputData::getMask "Mask* OutputData< T >::getMask() const

Returns mask that will be used by iterators. 
";

%feature("docstring")  OutputData::setMask "void OutputData< T >::setMask(const Mask &mask)

Sets mask (or a stack of masks) 
";

%feature("docstring")  OutputData::addMask "void OutputData< T >::addMask(const Mask &mask)

Adds mask that will be used by iterators. 
";

%feature("docstring")  OutputData::removeAllMasks "void OutputData< T >::removeAllMasks()

Remove all masks. 
";

%feature("docstring")  OutputData::getAxesBinIndices "std::vector< int > OutputData< T >::getAxesBinIndices(size_t global_index) const

Returns vector of axes indices for given global index

Parameters:
-----------

global_index: 
The global index of this data structure.

Vector of bin indices for all axes defined 
";

%feature("docstring")  OutputData::getAxisBinIndex "int OutputData< T >::getAxisBinIndex(size_t global_index, size_t i_selected_axis) const

Returns axis bin index for given global index

Parameters:
-----------

global_index: 
The global index of this data structure.

i_selected_axis: 
Serial number of selected axis.

Corresponding bin index for selected axis 
";

%feature("docstring")  OutputData::getAxisBinIndex "int OutputData< T >::getAxisBinIndex(size_t global_index, const std::string &axis_name) const

Returns axis bin index for given global index

Parameters:
-----------

global_index: 
The global index of this data structure.

axis_name: 
The name of selected axis.

Corresponding bin index for selected axis 
";

%feature("docstring")  OutputData::toGlobalIndex "size_t OutputData< T >::toGlobalIndex(const std::vector< int > &axes_indices) const

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

Corresponding  Bin1D object 
";

%feature("docstring")  OutputData::getAxisBin "Bin1D OutputData< T >::getAxisBin(size_t global_index, const std::string &axis_name) const

Returns bin of selected axis for given global_index.

Parameters:
-----------

global_index: 
The global index of this data structure.

axis_name: 
The name of selected axis.

Corresponding  Bin1D object 
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

Adds <rank> axes with indicated sizes. 
";

%feature("docstring")  OutputData::setRawDataVector "void OutputData< T >::setRawDataVector(const std::vector< T > &data_vector)

Sets new values to raw data vector. 
";

%feature("docstring")  OutputData::setRawDataArray "void OutputData< T >::setRawDataArray(const T *source)

Sets new values to raw data array. 
";

%feature("docstring")  OutputData::hasSameDimensions "bool OutputData< T >::hasSameDimensions(const OutputData< U > &right) const

Returns true if object have same dimensions and number of axes bins.

Returns true if object have same dimensions. 
";

%feature("docstring")  OutputData::hasSameShape "bool OutputData< T >::hasSameShape(const OutputData< U > &right) const

Returns true if objects a) have same dimensions b) bin boundaries of axes coincide.

Returns true if object have same dimensions and shape of axis. 
";

%feature("docstring")  OutputData::isInitialized "bool OutputData< T >::isInitialized() const

returns data as Python numpy array

returns true if object is correctly initialized 
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

%feature("docstring")  OutputDataIterator::getMask "Mask* OutputDataIterator< TValue, TContainer >::getMask() const

Returns mask. 
";

%feature("docstring")  OutputDataIterator::setMask "void OutputDataIterator< TValue, TContainer >::setMask(const Mask &mask)

Sets mask (or a stack of masks) 
";

%feature("docstring")  OutputDataIterator::addMask "void OutputDataIterator< TValue, TContainer >::addMask(const Mask &mask)

Adds mask (also resets index to first available element) 
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


// File: classOutputDataWriteFactory.xml
%feature("docstring") OutputDataWriteFactory "

Creates writer appropariate for given type of files.

C++ includes: OutputDataWriteFactory.h
";


// File: classOutputDataWriteINTStrategy.xml
%feature("docstring") OutputDataWriteINTStrategy "

Strategy to write  OutputData to special BornAgain ASCII format.

C++ includes: OutputDataWriteStrategy.h
";

%feature("docstring")  OutputDataWriteINTStrategy::writeOutputData "void OutputDataWriteINTStrategy::writeOutputData(const OutputData< double > &data, std::ostream &output_stream)
";


// File: classOutputDataWriteNumpyTXTStrategy.xml
%feature("docstring") OutputDataWriteNumpyTXTStrategy "

Strategy to write  OutputData to simple ASCII file with the layout as in numpy.savetxt.

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

write output data to file 
";

%feature("docstring")  OutputDataWriter::setStrategy "void OutputDataWriter::setStrategy(IOutputDataWriteStrategy *write_strategy)

Sets concrete writing strategy. 
";


// File: classParameterDistribution.xml
%feature("docstring") ParameterDistribution "";

%feature("docstring")  ParameterDistribution::ParameterDistribution "ParameterDistribution::ParameterDistribution(const std::string &par_name, const IDistribution1D &distribution, size_t nbr_samples, double sigma_factor=0.0, const AttLimits &limits=AttLimits())
";

%feature("docstring")  ParameterDistribution::ParameterDistribution "ParameterDistribution::ParameterDistribution(const std::string &par_name, const IDistribution1D &distribution, size_t nbr_samples, double xmin, double xmax)
";

%feature("docstring")  ParameterDistribution::ParameterDistribution "ParameterDistribution::ParameterDistribution(const ParameterDistribution &other)
";

%feature("docstring")  ParameterDistribution::~ParameterDistribution "ParameterDistribution::~ParameterDistribution()
";

%feature("docstring")  ParameterDistribution::linkParameter "ParameterDistribution & ParameterDistribution::linkParameter(std::string par_name)
";

%feature("docstring")  ParameterDistribution::getMainParameterName "std::string ParameterDistribution::getMainParameterName() const

get the main parameter's name 
";

%feature("docstring")  ParameterDistribution::getNbrSamples "size_t ParameterDistribution::getNbrSamples() const

get number of samples for this distribution 
";

%feature("docstring")  ParameterDistribution::getSigmaFactor "double ParameterDistribution::getSigmaFactor() const

get the sigma factor 
";

%feature("docstring")  ParameterDistribution::getDistribution "const IDistribution1D * ParameterDistribution::getDistribution() const 
";

%feature("docstring")  ParameterDistribution::generateSamples "std::vector< ParameterSample > ParameterDistribution::generateSamples() const

generate list of sampled values with their weight 
";

%feature("docstring")  ParameterDistribution::getLinkedParameterNames "std::vector< std::string > ParameterDistribution::getLinkedParameterNames() const

get list of linked parameter names 
";

%feature("docstring")  ParameterDistribution::getLimits "AttLimits ParameterDistribution::getLimits() const 
";

%feature("docstring")  ParameterDistribution::getMinValue "double ParameterDistribution::getMinValue() const 
";

%feature("docstring")  ParameterDistribution::getMaxValue "double ParameterDistribution::getMaxValue() const 
";


// File: classParameterPattern.xml
%feature("docstring") ParameterPattern "

Helper class for constructing parameter patterns.

C++ includes: IParameterized.h
";

%feature("docstring")  ParameterPattern::ParameterPattern "ParameterPattern::ParameterPattern()
";

%feature("docstring")  ParameterPattern::ParameterPattern "ParameterPattern::ParameterPattern(std::string root_object)
";

%feature("docstring")  ParameterPattern::beginsWith "ParameterPattern & ParameterPattern::beginsWith(std::string start_type)
";

%feature("docstring")  ParameterPattern::add "ParameterPattern & ParameterPattern::add(std::string object_type)
";

%feature("docstring")  ParameterPattern::toStdString "std::string ParameterPattern::toStdString() const 
";


// File: classParameterPool.xml
%feature("docstring") ParameterPool "

Holds a map of pointers to parameters (which must have different names).

C++ includes: ParameterPool.h
";

%feature("docstring")  ParameterPool::ParameterPool "ParameterPool::ParameterPool()

Constructs an empty parameter pool. 
";

%feature("docstring")  ParameterPool::~ParameterPool "virtual ParameterPool::~ParameterPool()
";

%feature("docstring")  ParameterPool::clone "ParameterPool* ParameterPool::clone() const

Returns a literal clone. 
";

%feature("docstring")  ParameterPool::cloneWithPrefix "ParameterPool * ParameterPool::cloneWithPrefix(const std::string &prefix) const

Returns a clone with  prefix added to every parameter key. 
";

%feature("docstring")  ParameterPool::copyToExternalPool "void ParameterPool::copyToExternalPool(const std::string &prefix, ParameterPool *external_pool) const

Copies parameters to  external_pool, adding  prefix to every key.

Copy parameters of given pool to the external pool while adding prefix to local parameter keys 
";

%feature("docstring")  ParameterPool::clear "void ParameterPool::clear()

Deletes parameter map. 
";

%feature("docstring")  ParameterPool::size "size_t ParameterPool::size() const

Returns size of parameter container. 
";

%feature("docstring")  ParameterPool::registerParameter "void ParameterPool::registerParameter(const std::string &name, double *parpointer, const AttLimits &limits=AttLimits::limitless())

Registers a parameter with key  name and pointer-to-value  parpointer.

Registers parameter with given name. 
";

%feature("docstring")  ParameterPool::addParameter "bool ParameterPool::addParameter(const std::string &name, parameter_t par)

Adds parameter to the pool.

Low-level routine. 
";

%feature("docstring")  ParameterPool::getParameter "ParameterPool::parameter_t ParameterPool::getParameter(const std::string &name) const

Returns parameter named  name.

Returns parameter with given name. 
";

%feature("docstring")  ParameterPool::getMatchedParameters "std::vector< ParameterPool::parameter_t > ParameterPool::getMatchedParameters(const std::string &wildcards) const

Returns vector of parameters which fit pattern. 
";

%feature("docstring")  ParameterPool::setParameterValue "bool ParameterPool::setParameterValue(const std::string &name, double value)

Sets parameter value, return true in the case of success.

Sets parameter value. 
";

%feature("docstring")  ParameterPool::setMatchedParametersValue "int ParameterPool::setMatchedParametersValue(const std::string &wildcards, double value)

Sets parameter value, return number of changed parameters.

Sets parameter value. 
";

%feature("docstring")  ParameterPool::getParameterNames "std::vector< std::string > ParameterPool::getParameterNames() const

Returns all parameter names. 
";


// File: structParameterSample.xml
%feature("docstring") ParameterSample "

Represents a sampled parameter value with its weight.

C++ includes: ParameterSample.h
";


// File: classParticle.xml
%feature("docstring") Particle "

A particle with a form factor and refractive index.

C++ includes: Particle.h
";

%feature("docstring")  Particle::Particle "Particle::Particle()
";

%feature("docstring")  Particle::Particle "Particle::Particle(const IMaterial &p_material)
";

%feature("docstring")  Particle::Particle "Particle::Particle(const IMaterial &p_material, const IFormFactor &form_factor)
";

%feature("docstring")  Particle::Particle "Particle::Particle(const IMaterial &p_material, const IFormFactor &form_factor, const IRotation &rotation)
";

%feature("docstring")  Particle::clone "Particle * Particle::clone() const

Returns a clone of this  ISample object. 
";

%feature("docstring")  Particle::cloneInvertB "Particle * Particle::cloneInvertB() const

Returns a clone with inverted magnetic fields. 
";

%feature("docstring")  Particle::accept "void Particle::accept(ISampleVisitor *visitor) const

calls the  ISampleVisitor's visit method 
";

%feature("docstring")  Particle::setAmbientMaterial "void Particle::setAmbientMaterial(const IMaterial &material)

Sets the refractive index of the ambient material (which influences its scattering power) 
";

%feature("docstring")  Particle::getAmbientMaterial "const IMaterial * Particle::getAmbientMaterial() const

Returns particle's material. 
";

%feature("docstring")  Particle::createTransformedFormFactor "IFormFactor * Particle::createTransformedFormFactor(const IRotation *p_rotation, kvector_t translation) const

Create a form factor for this particle with an extra scattering factor. 
";

%feature("docstring")  Particle::setMaterial "void Particle::setMaterial(const IMaterial &material)

Sets  material. 
";

%feature("docstring")  Particle::getMaterial "const IMaterial * Particle::getMaterial() const

Returns particle's material. 
";

%feature("docstring")  Particle::getRefractiveIndex "complex_t Particle::getRefractiveIndex() const

Returns refractive index of the particle. 
";

%feature("docstring")  Particle::setFormFactor "void Particle::setFormFactor(const IFormFactor &form_factor)

Sets the form factor. 
";

%feature("docstring")  Particle::getFormFactor "const IFormFactor * Particle::getFormFactor() const

Returns the form factor. 
";


// File: classParticleComposition.xml
%feature("docstring") ParticleComposition "

A composition of particles at fixed positions.

C++ includes: ParticleComposition.h
";

%feature("docstring")  ParticleComposition::ParticleComposition "ParticleComposition::ParticleComposition()
";

%feature("docstring")  ParticleComposition::ParticleComposition "ParticleComposition::ParticleComposition(const IParticle &particle)
";

%feature("docstring")  ParticleComposition::ParticleComposition "ParticleComposition::ParticleComposition(const IParticle &particle, kvector_t position)
";

%feature("docstring")  ParticleComposition::ParticleComposition "ParticleComposition::ParticleComposition(const IParticle &particle, std::vector< kvector_t > positions)
";

%feature("docstring")  ParticleComposition::~ParticleComposition "ParticleComposition::~ParticleComposition()
";

%feature("docstring")  ParticleComposition::clone "ParticleComposition * ParticleComposition::clone() const

Returns a clone of this  ISample object. 
";

%feature("docstring")  ParticleComposition::cloneInvertB "ParticleComposition * ParticleComposition::cloneInvertB() const

Returns a clone with inverted magnetic fields. 
";

%feature("docstring")  ParticleComposition::accept "void ParticleComposition::accept(ISampleVisitor *visitor) const

Calls the  ISampleVisitor's visit method. 
";

%feature("docstring")  ParticleComposition::addParticle "void ParticleComposition::addParticle(const IParticle &particle)
";

%feature("docstring")  ParticleComposition::addParticle "void ParticleComposition::addParticle(const IParticle &particle, kvector_t position)
";

%feature("docstring")  ParticleComposition::addParticles "void ParticleComposition::addParticles(const IParticle &particle, std::vector< kvector_t > positions)
";

%feature("docstring")  ParticleComposition::setAmbientMaterial "void ParticleComposition::setAmbientMaterial(const IMaterial &material)

Sets the refractive index of the ambient material (which influences its scattering power) 
";

%feature("docstring")  ParticleComposition::getAmbientMaterial "const IMaterial * ParticleComposition::getAmbientMaterial() const

Returns particle's material. 
";

%feature("docstring")  ParticleComposition::createTransformedFormFactor "IFormFactor * ParticleComposition::createTransformedFormFactor(const IRotation *p_rotation, kvector_t translation) const

Create a form factor for this particle with an extra scattering factor. 
";

%feature("docstring")  ParticleComposition::getNbrParticles "size_t ParticleComposition::getNbrParticles() const

Returns number of different particles. 
";

%feature("docstring")  ParticleComposition::getParticle "const IParticle * ParticleComposition::getParticle(size_t index) const

Returns particle with given index. 
";

%feature("docstring")  ParticleComposition::getParticlePosition "kvector_t ParticleComposition::getParticlePosition(size_t index) const 
";


// File: classParticleCompositionBuilder.xml
%feature("docstring") ParticleCompositionBuilder "

Builds sample: two layers of spheres at hex lattice.

C++ includes: ParticleCompositionBuilder.h
";

%feature("docstring")  ParticleCompositionBuilder::ParticleCompositionBuilder "ParticleCompositionBuilder::ParticleCompositionBuilder()
";

%feature("docstring")  ParticleCompositionBuilder::buildSample "ISample * ParticleCompositionBuilder::buildSample() const 
";


// File: classParticleCoreShell.xml
%feature("docstring") ParticleCoreShell "

A particle with a core/shell geometry.

C++ includes: ParticleCoreShell.h
";

%feature("docstring")  ParticleCoreShell::ParticleCoreShell "ParticleCoreShell::ParticleCoreShell(const Particle &shell, const Particle &core, kvector_t relative_core_position=kvector_t(0.0, 0.0, 0.0))
";

%feature("docstring")  ParticleCoreShell::~ParticleCoreShell "ParticleCoreShell::~ParticleCoreShell()
";

%feature("docstring")  ParticleCoreShell::clone "ParticleCoreShell * ParticleCoreShell::clone() const

Returns a clone of this  ISample object. 
";

%feature("docstring")  ParticleCoreShell::cloneInvertB "ParticleCoreShell * ParticleCoreShell::cloneInvertB() const

Returns a clone with inverted magnetic fields. 
";

%feature("docstring")  ParticleCoreShell::accept "void ParticleCoreShell::accept(ISampleVisitor *visitor) const

Calls the  ISampleVisitor's visit method. 
";

%feature("docstring")  ParticleCoreShell::setAmbientMaterial "void ParticleCoreShell::setAmbientMaterial(const IMaterial &material)

Sets the refractive index of the ambient material (which influences its scattering power) 
";

%feature("docstring")  ParticleCoreShell::getAmbientMaterial "const IMaterial * ParticleCoreShell::getAmbientMaterial() const

Returns particle's material. 
";

%feature("docstring")  ParticleCoreShell::createTransformedFormFactor "IFormFactor * ParticleCoreShell::createTransformedFormFactor(const IRotation *p_rotation, kvector_t translation) const

Create a form factor for this particle with an extra scattering factor. 
";

%feature("docstring")  ParticleCoreShell::getCoreParticle "const Particle * ParticleCoreShell::getCoreParticle() const

Returns the core particle. 
";

%feature("docstring")  ParticleCoreShell::getShellParticle "const Particle * ParticleCoreShell::getShellParticle() const

Returns the shell particle. 
";


// File: classParticleDistribution.xml
%feature("docstring") ParticleDistribution "

A particle with a form factor and refractive index.

C++ includes: ParticleDistribution.h
";

%feature("docstring")  ParticleDistribution::ParticleDistribution "ParticleDistribution::ParticleDistribution(const IParticle &prototype, const ParameterDistribution &par_distr)
";

%feature("docstring")  ParticleDistribution::clone "ParticleDistribution * ParticleDistribution::clone() const

Returns a clone of this  ISample object. 
";

%feature("docstring")  ParticleDistribution::cloneInvertB "ParticleDistribution * ParticleDistribution::cloneInvertB() const

Returns a clone with inverted magnetic fields. 
";

%feature("docstring")  ParticleDistribution::accept "void ParticleDistribution::accept(ISampleVisitor *visitor) const

calls the  ISampleVisitor's visit method 
";

%feature("docstring")  ParticleDistribution::setAmbientMaterial "void ParticleDistribution::setAmbientMaterial(const IMaterial &material)

Sets the refractive index of the ambient material (which influences its scattering power) 
";

%feature("docstring")  ParticleDistribution::getAmbientMaterial "const IMaterial * ParticleDistribution::getAmbientMaterial() const

Returns particle's material. 
";

%feature("docstring")  ParticleDistribution::generateParticles "void ParticleDistribution::generateParticles(std::vector< const IParticle * > &particle_vector) const

Initializes list of new particles generated according to a distribution. 
";

%feature("docstring")  ParticleDistribution::getParameterDistribution "ParameterDistribution ParticleDistribution::getParameterDistribution() const

Returns the distributed parameter data. 
";

%feature("docstring")  ParticleDistribution::createDistributedParameterPool "ParameterPool * ParticleDistribution::createDistributedParameterPool() const

Returns the parameter pool that can be used for parameter distributions. 
";

%feature("docstring")  ParticleDistribution::getParticle "const IParticle * ParticleDistribution::getParticle() const

Returns particle. 
";


// File: classParticleInTheAirBuilder.xml
%feature("docstring") ParticleInTheAirBuilder "

The  ParticleInTheAirBuilder class generates a multilayer with single air layer populated with particles of certain types. Requires  IComponentService which generates form factors, used for bulk form factors testing.

C++ includes: ParticleInTheAirBuilder.h
";

%feature("docstring")  ParticleInTheAirBuilder::ParticleInTheAirBuilder "ParticleInTheAirBuilder::ParticleInTheAirBuilder()
";

%feature("docstring")  ParticleInTheAirBuilder::~ParticleInTheAirBuilder "ParticleInTheAirBuilder::~ParticleInTheAirBuilder()
";

%feature("docstring")  ParticleInTheAirBuilder::init_from "void ParticleInTheAirBuilder::init_from(const IComponentService *service)
";

%feature("docstring")  ParticleInTheAirBuilder::buildSample "ISample * ParticleInTheAirBuilder::buildSample() const 
";


// File: classParticleLayout.xml
%feature("docstring") ParticleLayout "

Decorator class that adds particles to  ISample objects.

C++ includes: ParticleLayout.h
";

%feature("docstring")  ParticleLayout::ParticleLayout "ParticleLayout::ParticleLayout()
";

%feature("docstring")  ParticleLayout::ParticleLayout "ParticleLayout::ParticleLayout(const IAbstractParticle &particle)
";

%feature("docstring")  ParticleLayout::ParticleLayout "ParticleLayout::ParticleLayout(const IAbstractParticle &particle, double abundance)
";

%feature("docstring")  ParticleLayout::~ParticleLayout "ParticleLayout::~ParticleLayout()
";

%feature("docstring")  ParticleLayout::clone "ParticleLayout * ParticleLayout::clone() const

Returns a clone of this  ISample object. 
";

%feature("docstring")  ParticleLayout::cloneInvertB "ParticleLayout * ParticleLayout::cloneInvertB() const

Returns a clone with inverted magnetic fields. 
";

%feature("docstring")  ParticleLayout::accept "void ParticleLayout::accept(ISampleVisitor *visitor) const

calls the  ISampleVisitor's visit method 
";

%feature("docstring")  ParticleLayout::addParticle "void ParticleLayout::addParticle(const IAbstractParticle &particle)

Adds generic particle to the layout. 
";

%feature("docstring")  ParticleLayout::addParticle "void ParticleLayout::addParticle(const IAbstractParticle &particle, double abundance)

Adds generic particle to the layout with only abundance defined.

Parameters:
-----------

abundance: 
 Particle abundance 
";

%feature("docstring")  ParticleLayout::addParticle "void ParticleLayout::addParticle(const IParticle &particle, double abundance, const kvector_t &position)

Adds particle to the layout with abundance and position defined.

Parameters:
-----------

abundance: 
 Particle abundance

position: 
 Particle position 
";

%feature("docstring")  ParticleLayout::addParticle "void ParticleLayout::addParticle(const IParticle &particle, double abundance, const kvector_t &position, const IRotation &rotation)

Adds particle to the layout with abundance, position and the rotation defined.

Parameters:
-----------

abundance: 
 Particle abundance

position: 
 Particle position

rotation: 
 Particle rotation 
";

%feature("docstring")  ParticleLayout::getNumberOfParticles "size_t ParticleLayout::getNumberOfParticles() const

Returns number of particles. 
";

%feature("docstring")  ParticleLayout::getParticle "const IAbstractParticle * ParticleLayout::getParticle(size_t index) const

get information about particle with index

Returns particle info. 
";

%feature("docstring")  ParticleLayout::getParticles "SafePointerVector< const IParticle > ParticleLayout::getParticles() const

Returns information on all particles (type and abundance) and generates new particles if an  IAbstractParticle denotes a collection 
";

%feature("docstring")  ParticleLayout::getAbundanceOfParticle "double ParticleLayout::getAbundanceOfParticle(size_t index) const

Get abundance fraction of particle with index. 
";

%feature("docstring")  ParticleLayout::getInterferenceFunction "const IInterferenceFunction * ParticleLayout::getInterferenceFunction() const

Returns interference functions. 
";

%feature("docstring")  ParticleLayout::addInterferenceFunction "void ParticleLayout::addInterferenceFunction(const IInterferenceFunction &interference_function)

Sets interference function.

Adds interference functions. 
";

%feature("docstring")  ParticleLayout::getTotalParticleSurfaceDensity "double ParticleLayout::getTotalParticleSurfaceDensity() const

Returns surface density of all particles. 
";

%feature("docstring")  ParticleLayout::setTotalParticleSurfaceDensity "void ParticleLayout::setTotalParticleSurfaceDensity(double particle_density)

Sets surface density of all particles. 
";


// File: classGeometry_1_1Polygon.xml
%feature("docstring") Geometry::Polygon "

The polygon in 2D space.

C++ includes: Polygon.h
";

%feature("docstring")  Geometry::Polygon::Polygon "Geometry::Polygon::Polygon(std::vector< double > x, std::vector< double > y)

Polygon defined by two arrays with x and y coordinates of points. Sizes of arrays should coincide. If polygon is unclosed (the last point doesn't repeat the first one), it will be closed automatically.

Parameters:
-----------

x: 
Vector of x-coordinates of polygon points.

x: 
Vector of y-coordinates of polygon points. 
";

%feature("docstring")  Geometry::Polygon::Polygon "Geometry::Polygon::Polygon(std::vector< std::vector< double > > points)

Polygon defined by two dimensional array with (x,y) coordinates of polygon points. The size of second dimension should be 2. If polygon is unclosed (the last point doesn't repeat the first one), it will be closed automatically.

Parameters:
-----------

points: 
Two dimensional vector of (x,y) coordinates of polygon points. 
";

%feature("docstring")  Geometry::Polygon::~Polygon "Geometry::Polygon::~Polygon()
";

%feature("docstring")  Geometry::Polygon::clone "Polygon * Geometry::Polygon::clone() const 
";

%feature("docstring")  Geometry::Polygon::contains "bool Geometry::Polygon::contains(double x, double y) const

Returns true if given point is inside or on border of polygon. 
";

%feature("docstring")  Geometry::Polygon::contains "bool Geometry::Polygon::contains(const Bin1D &binx, const Bin1D &biny) const

Returns true if area defined by two bins is inside or on border of polygon. More precisely, if mid point of two bins satisfy this condition. 
";

%feature("docstring")  Geometry::Polygon::getArea "double Geometry::Polygon::getArea() const 
";

%feature("docstring")  Geometry::Polygon::getPoints "void Geometry::Polygon::getPoints(std::vector< double > &xpos, std::vector< double > &ypos) const 
";


// File: classGeometry_1_1PolygonPrivate.xml
%feature("docstring") Geometry::PolygonPrivate "

The private data for polygons to hide boost dependency from the header. 
";

%feature("docstring")  Geometry::PolygonPrivate::init_from "void Geometry::PolygonPrivate::init_from(const std::vector< double > &x, const std::vector< double > &y)
";

%feature("docstring")  Geometry::PolygonPrivate::get_points "void Geometry::PolygonPrivate::get_points(std::vector< double > &xpos, std::vector< double > &ypos)
";


// File: classPolyhedralEdge.xml
%feature("docstring") PolyhedralEdge "

One edge of a polygon, for form factor computation.

C++ includes: FormFactorPolyhedron.h
";

%feature("docstring")  PolyhedralEdge::PolyhedralEdge "PolyhedralEdge::PolyhedralEdge(const kvector_t _Vlow, const kvector_t _Vhig)
";

%feature("docstring")  PolyhedralEdge::contrib "complex_t PolyhedralEdge::contrib(int m, cvector_t prevec, cvector_t qpa) const

Returns the contribution of this edge to the form factor. 
";


// File: classPolyhedralFace.xml
%feature("docstring") PolyhedralFace "

A polygon, for form factor computation.

C++ includes: FormFactorPolyhedron.h
";

%feature("docstring")  PolyhedralFace::PolyhedralFace "PolyhedralFace::PolyhedralFace(const std::vector< kvector_t > &_V=std::vector< kvector_t >(), bool _sym_S2=false)

Sets internal variables for given vertex chain. 
";

%feature("docstring")  PolyhedralFace::getArea "double PolyhedralFace::getArea() const

Returns area of this polygon. 
";

%feature("docstring")  PolyhedralFace::getPyramidalVolume "double PolyhedralFace::getPyramidalVolume() const

Returns volume of pyramid spanned by the origin and this polygon. 
";

%feature("docstring")  PolyhedralFace::ff_n "complex_t PolyhedralFace::ff_n(int m, const cvector_t q) const

Returns contribution qn*f_n [of order q^(n+1)] from this face to the polyhedral form factor. 
";

%feature("docstring")  PolyhedralFace::ff "complex_t PolyhedralFace::ff(const cvector_t q, const bool sym_Ci) const

Returns the contribution of this face to the polyhedral form factor. 
";

%feature("docstring")  PolyhedralFace::ff_2D "complex_t PolyhedralFace::ff_2D(const cvector_t qpa) const

Returns the two-dimensional form factor of this face, for use in a prism. 
";

%feature("docstring")  PolyhedralFace::assert_Ci "void PolyhedralFace::assert_Ci(const PolyhedralFace &other) const

Throws if deviation from inversion symmetry is detected. Does not check vertices. 
";


// File: classPrecomputed.xml
%feature("docstring") Precomputed "

This class contains precomputed constants.

So far, the only contents is factorial, used in the polyhedral form factor.

C++ includes: Precomputed.h
";

%feature("docstring")  Precomputed::Precomputed "Precomputed::Precomputed()

Precompute things upon class instantiation. 
";


// File: classProgramOptions.xml
%feature("docstring") ProgramOptions "

Handles command line and config file program options.

The definition of program options are done separately from CoreOptionsDescription, AppOptionsDescription modules and then added to given class using  add() method

C++ includes: ProgramOptions.h
";

%feature("docstring")  ProgramOptions::ProgramOptions "ProgramOptions::ProgramOptions()
";

%feature("docstring")  ProgramOptions::add "ProgramOptions& ProgramOptions::add(bpo::options_description opt)

Adds options to the global options list (object is passed by value, so no dependency from object life) 
";

%feature("docstring")  ProgramOptions::addPositional "ProgramOptions& ProgramOptions::addPositional(std::string option_name, int num_occurencies)

Adds positional options. 
";

%feature("docstring")  ProgramOptions::find "bool ProgramOptions::find(std::string name) const

Returns true if option with given name has been set. 
";

%feature("docstring")  ProgramOptions::isConsistent "bool ProgramOptions::isConsistent() const

Returns true if options are consistent (no conflicting options, no help request, config file is parsed) 
";

%feature("docstring")  ProgramOptions::parseCommandLine "void ProgramOptions::parseCommandLine(int argc, char **argv)

Parses command line arguments.

parse command line arguments 
";

%feature("docstring")  ProgramOptions::parseConfigFile "void ProgramOptions::parseConfigFile()

Parses config file for arguments.

parse config file for arguments 
";

%feature("docstring")  ProgramOptions::getVariables "bpo::variables_map& ProgramOptions::getVariables()

Returns reference to the variables container. 
";

%feature("docstring")  ProgramOptions::getOptions "bpo::options_description& ProgramOptions::getOptions()

Returns reference to the options description. 
";

%feature("docstring")  ProgramOptions::getPositionalOptions "bpo::positional_options_description& ProgramOptions::getPositionalOptions()

Returns reference to the positional options description. 
";


// File: classProgressHandler.xml
%feature("docstring") ProgressHandler "

Provides the functionality to calculate the progress of running simulation and report it to GUI.

Thread safe to be used from  DWBASimulation

C++ includes: ProgressHandler.h
";

%feature("docstring")  ProgressHandler::ProgressHandler "ProgressHandler::ProgressHandler()
";

%feature("docstring")  ProgressHandler::setCallback "void ProgressHandler::setCallback(ProgressHandler::Callback_t callback)
";

%feature("docstring")  ProgressHandler::update "bool ProgressHandler::update(int n)

Collects number of items processed by different  DWBASimulation's. Calculates general progress and inform GUI if progress has changed. Return flag is obtained from GUI and transferred to  DWBASimulation to ask them to stop calculations. 
";

%feature("docstring")  ProgressHandler::setNmaxItems "void ProgressHandler::setNmaxItems(long max)
";

%feature("docstring")  ProgressHandler::getProgress "long ProgressHandler::getProgress() const 
";

%feature("docstring")  ProgressHandler::getNitems "long ProgressHandler::getNitems() const 
";

%feature("docstring")  ProgressHandler::init "void ProgressHandler::init(Simulation *simulation, int param_combinations=1)

Initialize  ProgressHandler, estimates number of items to be calculated by  DWBASimulation's. 
";

%feature("docstring")  ProgressHandler::reset "void ProgressHandler::reset()
";


// File: classProgressHandlerDWBA.xml
%feature("docstring") ProgressHandlerDWBA "";

%feature("docstring")  ProgressHandlerDWBA::ProgressHandlerDWBA "ProgressHandlerDWBA::ProgressHandlerDWBA()
";

%feature("docstring")  ProgressHandlerDWBA::setCallback "void ProgressHandlerDWBA::setCallback(ProgressHandler::Callback_t callback)
";

%feature("docstring")  ProgressHandlerDWBA::getCallback "ProgressHandler::Callback_t ProgressHandlerDWBA::getCallback() const 
";

%feature("docstring")  ProgressHandlerDWBA::update "bool ProgressHandlerDWBA::update()

Method increments number of items processed. Every n'th processed item the  Simulation is informed via thread safe callback. Return flag false is used to inform DWBSimulation to interrupt calculations. 
";

%feature("docstring")  ProgressHandlerDWBA::finished "bool ProgressHandlerDWBA::finished()

finalize report to the simulation 
";


// File: classPyGenVisitor.xml
%feature("docstring") PyGenVisitor "";

%feature("docstring")  PyGenVisitor::PyGenVisitor "PyGenVisitor::PyGenVisitor()
";

%feature("docstring")  PyGenVisitor::~PyGenVisitor "PyGenVisitor::~PyGenVisitor()
";

%feature("docstring")  PyGenVisitor::writePyScript "std::string PyGenVisitor::writePyScript(const GISASSimulation *simulation)
";

%feature("docstring")  PyGenVisitor::visit "void PyGenVisitor::visit(const FormFactorAnisoPyramid *sample)
";

%feature("docstring")  PyGenVisitor::visit "void PyGenVisitor::visit(const FormFactorBox *sample)
";

%feature("docstring")  PyGenVisitor::visit "void PyGenVisitor::visit(const FormFactorCone *sample)
";

%feature("docstring")  PyGenVisitor::visit "void PyGenVisitor::visit(const FormFactorCone6 *sample)
";

%feature("docstring")  PyGenVisitor::visit "void PyGenVisitor::visit(const FormFactorCuboctahedron *sample)
";

%feature("docstring")  PyGenVisitor::visit "void PyGenVisitor::visit(const FormFactorCylinder *sample)
";

%feature("docstring")  PyGenVisitor::visit "void PyGenVisitor::visit(const FormFactorDodecahedron *sample)
";

%feature("docstring")  PyGenVisitor::visit "void PyGenVisitor::visit(const FormFactorEllipsoidalCylinder *sample)
";

%feature("docstring")  PyGenVisitor::visit "void PyGenVisitor::visit(const FormFactorFullSphere *sample)
";

%feature("docstring")  PyGenVisitor::visit "void PyGenVisitor::visit(const FormFactorFullSpheroid *sample)
";

%feature("docstring")  PyGenVisitor::visit "void PyGenVisitor::visit(const FormFactorGauss *sample)
";

%feature("docstring")  PyGenVisitor::visit "void PyGenVisitor::visit(const FormFactorHemiEllipsoid *sample)
";

%feature("docstring")  PyGenVisitor::visit "void PyGenVisitor::visit(const FormFactorIcosahedron *sample)
";

%feature("docstring")  PyGenVisitor::visit "void PyGenVisitor::visit(const FormFactorLorentz *sample)
";

%feature("docstring")  PyGenVisitor::visit "void PyGenVisitor::visit(const FormFactorPrism3 *sample)
";

%feature("docstring")  PyGenVisitor::visit "void PyGenVisitor::visit(const FormFactorPrism6 *sample)
";

%feature("docstring")  PyGenVisitor::visit "void PyGenVisitor::visit(const FormFactorPyramid *sample)
";

%feature("docstring")  PyGenVisitor::visit "void PyGenVisitor::visit(const FormFactorRipple1 *sample)
";

%feature("docstring")  PyGenVisitor::visit "void PyGenVisitor::visit(const FormFactorRipple2 *sample)
";

%feature("docstring")  PyGenVisitor::visit "void PyGenVisitor::visit(const FormFactorTetrahedron *sample)
";

%feature("docstring")  PyGenVisitor::visit "void PyGenVisitor::visit(const FormFactorTruncatedCube *sample)
";

%feature("docstring")  PyGenVisitor::visit "void PyGenVisitor::visit(const FormFactorTruncatedSphere *sample)
";

%feature("docstring")  PyGenVisitor::visit "void PyGenVisitor::visit(const FormFactorTruncatedSpheroid *sample)
";

%feature("docstring")  PyGenVisitor::visit "void PyGenVisitor::visit(const InterferenceFunctionNone *sample)
";

%feature("docstring")  PyGenVisitor::visit "void PyGenVisitor::visit(const InterferenceFunction1DLattice *sample)
";

%feature("docstring")  PyGenVisitor::visit "void PyGenVisitor::visit(const InterferenceFunctionRadialParaCrystal *sample)
";

%feature("docstring")  PyGenVisitor::visit "void PyGenVisitor::visit(const InterferenceFunction2DLattice *sample)
";

%feature("docstring")  PyGenVisitor::visit "void PyGenVisitor::visit(const InterferenceFunction2DParaCrystal *sample)
";

%feature("docstring")  PyGenVisitor::visit "void PyGenVisitor::visit(const Layer *sample)
";

%feature("docstring")  PyGenVisitor::visit "virtual void PyGenVisitor::visit(const LayerInterface *sample)
";

%feature("docstring")  PyGenVisitor::visit "void PyGenVisitor::visit(const LayerRoughness *sample)
";

%feature("docstring")  PyGenVisitor::visit "void PyGenVisitor::visit(const MultiLayer *sample)
";

%feature("docstring")  PyGenVisitor::visit "void PyGenVisitor::visit(const ParticleComposition *sample)
";

%feature("docstring")  PyGenVisitor::visit "void PyGenVisitor::visit(const MesoCrystal *sample)
";

%feature("docstring")  PyGenVisitor::visit "void PyGenVisitor::visit(const Particle *sample)
";

%feature("docstring")  PyGenVisitor::visit "void PyGenVisitor::visit(const ParticleDistribution *sample)
";

%feature("docstring")  PyGenVisitor::visit "void PyGenVisitor::visit(const ParticleCoreShell *sample)
";

%feature("docstring")  PyGenVisitor::visit "void PyGenVisitor::visit(const ParticleLayout *sample)
";

%feature("docstring")  PyGenVisitor::visit "void PyGenVisitor::visit(const RotationX *sample)
";

%feature("docstring")  PyGenVisitor::visit "void PyGenVisitor::visit(const RotationY *sample)
";

%feature("docstring")  PyGenVisitor::visit "void PyGenVisitor::visit(const RotationZ *sample)
";

%feature("docstring")  PyGenVisitor::visit "void PyGenVisitor::visit(const RotationEuler *sample)
";

%feature("docstring")  PyGenVisitor::definePreamble "std::string PyGenVisitor::definePreamble() const 
";

%feature("docstring")  PyGenVisitor::defineGetSimulation "std::string PyGenVisitor::defineGetSimulation(const GISASSimulation *simulation) const 
";

%feature("docstring")  PyGenVisitor::defineGetSample "std::string PyGenVisitor::defineGetSample() const 
";

%feature("docstring")  PyGenVisitor::defineMaterials "std::string PyGenVisitor::defineMaterials() const 
";


// File: classPyScriptFunctionalTest.xml
%feature("docstring") PyScriptFunctionalTest "

GUI functional test compares results of the reference simulation with the one obtained through domain->GUI->domain convertion. Normally invoked by  FunctionalMultiTest.

C++ includes: PyScriptFunctionalTest.h
";

%feature("docstring")  PyScriptFunctionalTest::PyScriptFunctionalTest "PyScriptFunctionalTest::PyScriptFunctionalTest(const std::string &name, const std::string &description, GISASSimulation *reference_simulation, double threshold)
";

%feature("docstring")  PyScriptFunctionalTest::~PyScriptFunctionalTest "PyScriptFunctionalTest::~PyScriptFunctionalTest()
";

%feature("docstring")  PyScriptFunctionalTest::runTest "void PyScriptFunctionalTest::runTest()
";

%feature("docstring")  PyScriptFunctionalTest::analyseResults "int PyScriptFunctionalTest::analyseResults()
";

%feature("docstring")  PyScriptFunctionalTest::getOutputData "const OutputData<double>* PyScriptFunctionalTest::getOutputData() const 
";

%feature("docstring")  PyScriptFunctionalTest::getDifference "double PyScriptFunctionalTest::getDifference() const 
";

%feature("docstring")  PyScriptFunctionalTest::printResults "void PyScriptFunctionalTest::printResults(std::ostream &ostr) const 
";

%feature("docstring")  PyScriptFunctionalTest::setPyScriptFileName "void PyScriptFunctionalTest::setPyScriptFileName(const std::string &file_name)
";


// File: classPyScriptFunctionalTestComponentService.xml
%feature("docstring") PyScriptFunctionalTestComponentService "

Contains all necessary information to compose pyscript functional test.

C++ includes: PyScriptFunctionalTestComponentService.h
";

%feature("docstring")  PyScriptFunctionalTestComponentService::PyScriptFunctionalTestComponentService "PyScriptFunctionalTestComponentService::PyScriptFunctionalTestComponentService(const FunctionalTestInfo &info)
";

%feature("docstring")  PyScriptFunctionalTestComponentService::getFunctionalTest "IFunctionalTest * PyScriptFunctionalTestComponentService::getFunctionalTest() const 
";


// File: classRadialParaCrystalBuilder.xml
%feature("docstring") RadialParaCrystalBuilder "

Builds sample: cylinders with 1DDL structure factor (IsGISAXS example #4)

C++ includes: ParaCrystalBuilder.h
";

%feature("docstring")  RadialParaCrystalBuilder::RadialParaCrystalBuilder "RadialParaCrystalBuilder::RadialParaCrystalBuilder()
";

%feature("docstring")  RadialParaCrystalBuilder::buildSample "ISample * RadialParaCrystalBuilder::buildSample() const 
";


// File: classRealParameterWrapper.xml
%feature("docstring") RealParameterWrapper "

Wrapper to real parameter for remote access to its value and callback abilities.

C++ includes: RealParameterWrapper.h
";

%feature("docstring")  RealParameterWrapper::RealParameterWrapper "RealParameterWrapper::RealParameterWrapper(double *par, const AttLimits &limits=AttLimits::limitless())
";

%feature("docstring")  RealParameterWrapper::RealParameterWrapper "RealParameterWrapper::RealParameterWrapper(const RealParameterWrapper &other)
";

%feature("docstring")  RealParameterWrapper::~RealParameterWrapper "RealParameterWrapper::~RealParameterWrapper()
";

%feature("docstring")  RealParameterWrapper::setValue "bool RealParameterWrapper::setValue(double value)

Sets value of wrapped parameter and emmit signal. 
";

%feature("docstring")  RealParameterWrapper::getValue "double RealParameterWrapper::getValue() const

Returns value of wrapped parameter. 
";

%feature("docstring")  RealParameterWrapper::isNull "bool RealParameterWrapper::isNull() const

Returns true if wrapped parameter was not initialized with proper real value. 
";

%feature("docstring")  RealParameterWrapper::checkNull "void RealParameterWrapper::checkNull() const

throw exception if parameter was not initialized with proper value 
";

%feature("docstring")  RealParameterWrapper::getAttLimits "AttLimits RealParameterWrapper::getAttLimits() const 
";


// File: classGeometry_1_1Rectangle.xml
%feature("docstring") Geometry::Rectangle "

The rectangle shape having its axis aligned to the coordinate system (non-rotated so far).

C++ includes: Rectangle.h
";

%feature("docstring")  Geometry::Rectangle::Rectangle "Geometry::Rectangle::Rectangle(double xlow, double ylow, double xup, double yup)

Rectangle constructor with lower left and upper right coordinates

Parameters:
-----------

xlow: 
x-coordinate of lower left corner

ylow: 
y-coordinate of lower left corner

xup: 
x-coordinate of upper right corner

yup: 
y-coordinate of upper right corner 
";

%feature("docstring")  Geometry::Rectangle::clone "Rectangle * Geometry::Rectangle::clone() const 
";

%feature("docstring")  Geometry::Rectangle::contains "bool Geometry::Rectangle::contains(double x, double y) const

Returns true if given point is inside or on border of rectangle. 
";

%feature("docstring")  Geometry::Rectangle::contains "bool Geometry::Rectangle::contains(const Bin1D &binx, const Bin1D &biny) const

Returns true if mid point of two bins is inside rectangle. 
";

%feature("docstring")  Geometry::Rectangle::getArea "double Geometry::Rectangle::getArea() const 
";

%feature("docstring")  Geometry::Rectangle::getXlow "double Geometry::Rectangle::getXlow() const 
";

%feature("docstring")  Geometry::Rectangle::getYlow "double Geometry::Rectangle::getYlow() const 
";

%feature("docstring")  Geometry::Rectangle::getXup "double Geometry::Rectangle::getXup() const 
";

%feature("docstring")  Geometry::Rectangle::getYup "double Geometry::Rectangle::getYup() const 
";


// File: classRectangularDetector.xml
%feature("docstring") RectangularDetector "

A rectangular plane detector with axes and resolution function.

C++ includes: RectangularDetector.h
";

%feature("docstring")  RectangularDetector::RectangularDetector "RectangularDetector::RectangularDetector(int nxbins, double width, int nybins, double height)

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

%feature("docstring")  RectangularDetector::clone "RectangularDetector * RectangularDetector::clone() const 
";

%feature("docstring")  RectangularDetector::~RectangularDetector "virtual RectangularDetector::~RectangularDetector()
";

%feature("docstring")  RectangularDetector::init "void RectangularDetector::init(const Beam &beam)

Inits detector with the beam settings. 
";

%feature("docstring")  RectangularDetector::setPosition "void RectangularDetector::setPosition(const kvector_t &normal_to_detector, double u0, double v0, const kvector_t &direction=kvector_t(0.0,-1.0, 0.0))
";

%feature("docstring")  RectangularDetector::setPerpendicularToSampleX "void RectangularDetector::setPerpendicularToSampleX(double distance, double u0, double v0)
";

%feature("docstring")  RectangularDetector::setPerpendicularToDirectBeam "void RectangularDetector::setPerpendicularToDirectBeam(double distance, double u0, double v0)
";

%feature("docstring")  RectangularDetector::setPerpendicularToReflectedBeam "void RectangularDetector::setPerpendicularToReflectedBeam(double distance, double u0=0.0, double v0=0.0)
";

%feature("docstring")  RectangularDetector::setDirectBeamPosition "void RectangularDetector::setDirectBeamPosition(double u0, double v0)
";

%feature("docstring")  RectangularDetector::addParametersToExternalPool "std::string RectangularDetector::addParametersToExternalPool(std::string path, ParameterPool *external_pool, int copy_number=-1) const

Adds parameters from local pool to external pool and recursively calls its direct children. 
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

%feature("docstring")  RectangularDetector::createDetectorMap "OutputData< double > * RectangularDetector::createDetectorMap(const Beam &beam, EAxesUnits units_type) const

Returns detector map in given axes units. 
";

%feature("docstring")  RectangularDetector::getValidAxesUnits "std::vector< IDetector2D::EAxesUnits > RectangularDetector::getValidAxesUnits() const

returns vector of valid axes units 
";

%feature("docstring")  RectangularDetector::getDefaultAxesUnits "IDetector2D::EAxesUnits RectangularDetector::getDefaultAxesUnits() const

return default axes units 
";


// File: classRectParaCrystalBuilder.xml
%feature("docstring") RectParaCrystalBuilder "

Builds sample: 2D paracrystal lattice (IsGISAXS example #8)

C++ includes: ParaCrystalBuilder.h
";

%feature("docstring")  RectParaCrystalBuilder::RectParaCrystalBuilder "RectParaCrystalBuilder::RectParaCrystalBuilder()
";

%feature("docstring")  RectParaCrystalBuilder::buildSample "ISample * RectParaCrystalBuilder::buildSample() const 
";


// File: classRectPixelMap.xml
%feature("docstring") RectPixelMap "";

%feature("docstring")  RectPixelMap::RectPixelMap "RectPixelMap::RectPixelMap(kvector_t corner_pos, kvector_t width, kvector_t height)
";

%feature("docstring")  RectPixelMap::~RectPixelMap "virtual RectPixelMap::~RectPixelMap()
";

%feature("docstring")  RectPixelMap::clone "RectPixelMap * RectPixelMap::clone() const 
";

%feature("docstring")  RectPixelMap::createZeroSizeMap "RectPixelMap * RectPixelMap::createZeroSizeMap(double x, double y) const 
";

%feature("docstring")  RectPixelMap::getK "kvector_t RectPixelMap::getK(double x, double y, double wavelength) const 
";

%feature("docstring")  RectPixelMap::getIntegrationFactor "double RectPixelMap::getIntegrationFactor(double x, double y) const 
";

%feature("docstring")  RectPixelMap::getSolidAngle "double RectPixelMap::getSolidAngle() const 
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

%feature("docstring")  ResolutionFunction2DGaussian::clone "ResolutionFunction2DGaussian * ResolutionFunction2DGaussian::clone() const 
";

%feature("docstring")  ResolutionFunction2DGaussian::getSigmaX "double ResolutionFunction2DGaussian::getSigmaX() const 
";

%feature("docstring")  ResolutionFunction2DGaussian::getSigmaY "double ResolutionFunction2DGaussian::getSigmaY() const 
";


// File: classRotatedPyramidsBuilder.xml
%feature("docstring") RotatedPyramidsBuilder "

Builds sample: Pyramids, rotated pyramids on top of substrate (IsGISAXS example #9)

C++ includes: RotatedPyramidsBuilder.h
";

%feature("docstring")  RotatedPyramidsBuilder::RotatedPyramidsBuilder "RotatedPyramidsBuilder::RotatedPyramidsBuilder()
";

%feature("docstring")  RotatedPyramidsBuilder::buildSample "ISample * RotatedPyramidsBuilder::buildSample() const 
";


// File: classRotatedSquareLatticeBuilder.xml
%feature("docstring") RotatedSquareLatticeBuilder "

Builds sample: 2D lattice with different disorder (IsGISAXS example #6)

C++ includes: TwoDimLatticeBuilder.h
";

%feature("docstring")  RotatedSquareLatticeBuilder::RotatedSquareLatticeBuilder "RotatedSquareLatticeBuilder::RotatedSquareLatticeBuilder()
";

%feature("docstring")  RotatedSquareLatticeBuilder::buildSample "ISample * RotatedSquareLatticeBuilder::buildSample() const 
";


// File: classRotationEuler.xml
%feature("docstring") RotationEuler "";

%feature("docstring")  RotationEuler::RotationEuler "RotationEuler::RotationEuler(double alpha, double beta, double gamma)
";

%feature("docstring")  RotationEuler::clone "RotationEuler * RotationEuler::clone() const

Returns a clone. 
";

%feature("docstring")  RotationEuler::cloneInvertB "RotationEuler * RotationEuler::cloneInvertB() const

Returns a clone with inverted magnetic fields. 
";

%feature("docstring")  RotationEuler::createInverse "IRotation * RotationEuler::createInverse() const

Returns a new  IRotation object that is the current object's inverse. 
";

%feature("docstring")  RotationEuler::getAlpha "double RotationEuler::getAlpha() const 
";

%feature("docstring")  RotationEuler::getBeta "double RotationEuler::getBeta() const 
";

%feature("docstring")  RotationEuler::getGamma "double RotationEuler::getGamma() const 
";

%feature("docstring")  RotationEuler::accept "void RotationEuler::accept(ISampleVisitor *visitor) const

Calls the  ISampleVisitor's visit method. 
";

%feature("docstring")  RotationEuler::getTransform3D "Geometry::Transform3D RotationEuler::getTransform3D() const

Returns transformation. 
";


// File: classRotationX.xml
%feature("docstring") RotationX "";

%feature("docstring")  RotationX::RotationX "RotationX::RotationX(double angle)
";

%feature("docstring")  RotationX::clone "RotationX * RotationX::clone() const

Returns a clone. 
";

%feature("docstring")  RotationX::cloneInvertB "RotationX * RotationX::cloneInvertB() const

Returns a clone with inverted magnetic fields. 
";

%feature("docstring")  RotationX::createInverse "RotationX * RotationX::createInverse() const

Returns a new  IRotation object that is the current object's inverse. 
";

%feature("docstring")  RotationX::getAngle "double RotationX::getAngle() const 
";

%feature("docstring")  RotationX::accept "void RotationX::accept(ISampleVisitor *visitor) const

Calls the  ISampleVisitor's visit method. 
";

%feature("docstring")  RotationX::getTransform3D "Geometry::Transform3D RotationX::getTransform3D() const

Returns transformation. 
";


// File: classRotationY.xml
%feature("docstring") RotationY "";

%feature("docstring")  RotationY::RotationY "RotationY::RotationY(double angle)
";

%feature("docstring")  RotationY::clone "RotationY * RotationY::clone() const

Returns a clone. 
";

%feature("docstring")  RotationY::cloneInvertB "RotationY * RotationY::cloneInvertB() const

Returns a clone with inverted magnetic fields. 
";

%feature("docstring")  RotationY::createInverse "RotationY * RotationY::createInverse() const

Returns a new  IRotation object that is the current object's inverse. 
";

%feature("docstring")  RotationY::getAngle "double RotationY::getAngle() const 
";

%feature("docstring")  RotationY::accept "void RotationY::accept(ISampleVisitor *visitor) const

Calls the  ISampleVisitor's visit method. 
";

%feature("docstring")  RotationY::getTransform3D "Geometry::Transform3D RotationY::getTransform3D() const

Returns transformation. 
";


// File: classRotationZ.xml
%feature("docstring") RotationZ "";

%feature("docstring")  RotationZ::RotationZ "RotationZ::RotationZ(double angle=0.0)
";

%feature("docstring")  RotationZ::clone "RotationZ * RotationZ::clone() const

Returns a clone. 
";

%feature("docstring")  RotationZ::cloneInvertB "RotationZ * RotationZ::cloneInvertB() const

Returns a clone with inverted magnetic fields. 
";

%feature("docstring")  RotationZ::createInverse "RotationZ * RotationZ::createInverse() const

Returns a new  IRotation object that is the current object's inverse. 
";

%feature("docstring")  RotationZ::getAngle "double RotationZ::getAngle() const 
";

%feature("docstring")  RotationZ::accept "void RotationZ::accept(ISampleVisitor *visitor) const

Calls the  ISampleVisitor's visit method. 
";

%feature("docstring")  RotationZ::getTransform3D "Geometry::Transform3D RotationZ::getTransform3D() const

Returns transformation. 
";


// File: classExceptions_1_1RuntimeErrorException.xml
%feature("docstring") Exceptions::RuntimeErrorException "";

%feature("docstring")  Exceptions::RuntimeErrorException::RuntimeErrorException "Exceptions::RuntimeErrorException::RuntimeErrorException(const std::string &message)
";


// File: classSafePointerVector.xml
%feature("docstring") SafePointerVector "

Safe handling of vectors of pointers that are owned by the vector.

The objects pointed to must support the ICLoneable interface.

C++ includes: SafePointerVector.h
";

%feature("docstring")  SafePointerVector::SafePointerVector "SafePointerVector< T >::SafePointerVector()
";

%feature("docstring")  SafePointerVector::SafePointerVector "SafePointerVector< T >::SafePointerVector(const SafePointerVector &other)
";

%feature("docstring")  SafePointerVector::~SafePointerVector "SafePointerVector< T >::~SafePointerVector()
";

%feature("docstring")  SafePointerVector::size "size_t SafePointerVector< T >::size() const 
";

%feature("docstring")  SafePointerVector::empty "bool SafePointerVector< T >::empty() const 
";

%feature("docstring")  SafePointerVector::push_back "void SafePointerVector< T >::push_back(T *pointer)
";

%feature("docstring")  SafePointerVector::begin "iterator SafePointerVector< T >::begin()
";

%feature("docstring")  SafePointerVector::begin "const_iterator SafePointerVector< T >::begin() const 
";

%feature("docstring")  SafePointerVector::end "iterator SafePointerVector< T >::end()
";

%feature("docstring")  SafePointerVector::end "const_iterator SafePointerVector< T >::end() const 
";

%feature("docstring")  SafePointerVector::getSTLVector "std::vector< const T * > SafePointerVector< T >::getSTLVector() const 
";

%feature("docstring")  SafePointerVector::deleteElement "bool SafePointerVector< T >::deleteElement(T *pointer)
";

%feature("docstring")  SafePointerVector::back "T* SafePointerVector< T >::back()
";

%feature("docstring")  SafePointerVector::back "const T* SafePointerVector< T >::back() const 
";

%feature("docstring")  SafePointerVector::clear "void SafePointerVector< T >::clear()
";


// File: classSampleBuilderFactory.xml
%feature("docstring") SampleBuilderFactory "

Factory to create standard pre-defined samples.

C++ includes: SampleBuilderFactory.h
";

%feature("docstring")  SampleBuilderFactory::SampleBuilderFactory "SampleBuilderFactory::SampleBuilderFactory()
";

%feature("docstring")  SampleBuilderFactory::createSample "ISample * SampleBuilderFactory::createSample(const std::string &name)
";

%feature("docstring")  SampleBuilderFactory::createBuilder "SampleBuilder_t SampleBuilderFactory::createBuilder(const std::string &name)
";


// File: classSampleIteratorPostorderStrategy.xml
%feature("docstring") SampleIteratorPostorderStrategy "";

%feature("docstring")  SampleIteratorPostorderStrategy::SampleIteratorPostorderStrategy "SampleIteratorPostorderStrategy::SampleIteratorPostorderStrategy()
";

%feature("docstring")  SampleIteratorPostorderStrategy::clone "SampleIteratorPostorderStrategy * SampleIteratorPostorderStrategy::clone() const 
";

%feature("docstring")  SampleIteratorPostorderStrategy::~SampleIteratorPostorderStrategy "SampleIteratorPostorderStrategy::~SampleIteratorPostorderStrategy()
";

%feature("docstring")  SampleIteratorPostorderStrategy::first "IteratorMemento SampleIteratorPostorderStrategy::first(const ISample *p_root)
";

%feature("docstring")  SampleIteratorPostorderStrategy::next "void SampleIteratorPostorderStrategy::next(IteratorMemento &iterator_stack) const 
";

%feature("docstring")  SampleIteratorPostorderStrategy::isDone "bool SampleIteratorPostorderStrategy::isDone(IteratorMemento &iterator_stack) const 
";


// File: classSampleIteratorPreorderStrategy.xml
%feature("docstring") SampleIteratorPreorderStrategy "";

%feature("docstring")  SampleIteratorPreorderStrategy::SampleIteratorPreorderStrategy "SampleIteratorPreorderStrategy::SampleIteratorPreorderStrategy()
";

%feature("docstring")  SampleIteratorPreorderStrategy::clone "SampleIteratorPreorderStrategy * SampleIteratorPreorderStrategy::clone() const 
";

%feature("docstring")  SampleIteratorPreorderStrategy::~SampleIteratorPreorderStrategy "SampleIteratorPreorderStrategy::~SampleIteratorPreorderStrategy()
";

%feature("docstring")  SampleIteratorPreorderStrategy::first "IteratorMemento SampleIteratorPreorderStrategy::first(const ISample *p_root)
";

%feature("docstring")  SampleIteratorPreorderStrategy::next "void SampleIteratorPreorderStrategy::next(IteratorMemento &iterator_stack) const 
";

%feature("docstring")  SampleIteratorPreorderStrategy::isDone "bool SampleIteratorPreorderStrategy::isDone(IteratorMemento &iterator_stack) const 
";


// File: classSampleLabelHandler.xml
%feature("docstring") SampleLabelHandler "

The hadler which construct labels for sample variables during python script generation.

C++ includes: SampleLabelHandler.h
";

%feature("docstring")  SampleLabelHandler::SampleLabelHandler "SampleLabelHandler::SampleLabelHandler()
";

%feature("docstring")  SampleLabelHandler::getFormFactorMap "SampleLabelHandler::formfactors_t * SampleLabelHandler::getFormFactorMap()
";

%feature("docstring")  SampleLabelHandler::getInterferenceFunctionMap "SampleLabelHandler::interferences_t * SampleLabelHandler::getInterferenceFunctionMap()
";

%feature("docstring")  SampleLabelHandler::getLayerMap "SampleLabelHandler::layers_t * SampleLabelHandler::getLayerMap()
";

%feature("docstring")  SampleLabelHandler::getLayerRoughnessMap "SampleLabelHandler::roughnesses_t * SampleLabelHandler::getLayerRoughnessMap()
";

%feature("docstring")  SampleLabelHandler::getMaterialMap "SampleLabelHandler::materials_t * SampleLabelHandler::getMaterialMap()
";

%feature("docstring")  SampleLabelHandler::getMultiLayerMap "SampleLabelHandler::multilayers_t * SampleLabelHandler::getMultiLayerMap()
";

%feature("docstring")  SampleLabelHandler::getParticleMap "SampleLabelHandler::particles_t * SampleLabelHandler::getParticleMap()
";

%feature("docstring")  SampleLabelHandler::getParticleCoreShellMap "SampleLabelHandler::particlescoreshell_t * SampleLabelHandler::getParticleCoreShellMap()
";

%feature("docstring")  SampleLabelHandler::getParticleDistributionsMap "SampleLabelHandler::particledistributions_t * SampleLabelHandler::getParticleDistributionsMap()
";

%feature("docstring")  SampleLabelHandler::getParticleLayoutMap "SampleLabelHandler::layouts_t * SampleLabelHandler::getParticleLayoutMap()
";

%feature("docstring")  SampleLabelHandler::getParticleCompositionMap "SampleLabelHandler::particlecompositions_t * SampleLabelHandler::getParticleCompositionMap()
";

%feature("docstring")  SampleLabelHandler::getRotationsMap "SampleLabelHandler::rotations_t * SampleLabelHandler::getRotationsMap()
";

%feature("docstring")  SampleLabelHandler::getLabel "std::string SampleLabelHandler::getLabel(const IFormFactor *sample)
";

%feature("docstring")  SampleLabelHandler::getLabel "std::string SampleLabelHandler::getLabel(const IInterferenceFunction *sample)
";

%feature("docstring")  SampleLabelHandler::getLabel "std::string SampleLabelHandler::getLabel(const IMaterial *sample)
";

%feature("docstring")  SampleLabelHandler::getLabel "std::string SampleLabelHandler::getLabel(const Layer *sample)
";

%feature("docstring")  SampleLabelHandler::getLabel "std::string SampleLabelHandler::getLabel(const LayerRoughness *sample)
";

%feature("docstring")  SampleLabelHandler::getLabel "std::string SampleLabelHandler::getLabel(const MultiLayer *sample)
";

%feature("docstring")  SampleLabelHandler::getLabel "std::string SampleLabelHandler::getLabel(const IAbstractParticle *sample)
";

%feature("docstring")  SampleLabelHandler::getLabel "std::string SampleLabelHandler::getLabel(const ParticleCoreShell *sample)
";

%feature("docstring")  SampleLabelHandler::getLabel "std::string SampleLabelHandler::getLabel(const ParticleDistribution *sample)
";

%feature("docstring")  SampleLabelHandler::getLabel "std::string SampleLabelHandler::getLabel(const ILayout *sample)
";

%feature("docstring")  SampleLabelHandler::getLabel "std::string SampleLabelHandler::getLabel(const ParticleComposition *sample)
";

%feature("docstring")  SampleLabelHandler::getLabel "std::string SampleLabelHandler::getLabel(const IRotation *sample)
";

%feature("docstring")  SampleLabelHandler::insertMaterial "void SampleLabelHandler::insertMaterial(const IMaterial *sample)
";

%feature("docstring")  SampleLabelHandler::setLabel "void SampleLabelHandler::setLabel(const IFormFactor *sample)
";

%feature("docstring")  SampleLabelHandler::setLabel "void SampleLabelHandler::setLabel(const IInterferenceFunction *sample)
";

%feature("docstring")  SampleLabelHandler::setLabel "void SampleLabelHandler::setLabel(const ILayout *sample)
";

%feature("docstring")  SampleLabelHandler::setLabel "void SampleLabelHandler::setLabel(const Layer *sample)
";

%feature("docstring")  SampleLabelHandler::setLabel "void SampleLabelHandler::setLabel(const LayerRoughness *sample)
";

%feature("docstring")  SampleLabelHandler::setLabel "void SampleLabelHandler::setLabel(const MultiLayer *sample)
";

%feature("docstring")  SampleLabelHandler::setLabel "void SampleLabelHandler::setLabel(const Particle *sample)
";

%feature("docstring")  SampleLabelHandler::setLabel "void SampleLabelHandler::setLabel(const ParticleCoreShell *sample)
";

%feature("docstring")  SampleLabelHandler::setLabel "void SampleLabelHandler::setLabel(const ParticleDistribution *sample)
";

%feature("docstring")  SampleLabelHandler::setLabel "void SampleLabelHandler::setLabel(const ParticleComposition *sample)
";

%feature("docstring")  SampleLabelHandler::setLabel "void SampleLabelHandler::setLabel(const IRotation *sample)
";


// File: classSampleMaterialVisitor.xml
%feature("docstring") SampleMaterialVisitor "

SampleMaterialVisitor retrieves a list of the used materials in a sample.

C++ includes: SampleMaterialVisitor.h
";

%feature("docstring")  SampleMaterialVisitor::SampleMaterialVisitor "SampleMaterialVisitor::SampleMaterialVisitor()
";

%feature("docstring")  SampleMaterialVisitor::~SampleMaterialVisitor "virtual SampleMaterialVisitor::~SampleMaterialVisitor()
";

%feature("docstring")  SampleMaterialVisitor::visit "void SampleMaterialVisitor::visit(const ISample *sample)
";

%feature("docstring")  SampleMaterialVisitor::visit "void SampleMaterialVisitor::visit(const ICompositeSample *sample)
";

%feature("docstring")  SampleMaterialVisitor::visit "void SampleMaterialVisitor::visit(const IClusteredParticles *sample)
";

%feature("docstring")  SampleMaterialVisitor::visit "void SampleMaterialVisitor::visit(const Crystal *sample)
";

%feature("docstring")  SampleMaterialVisitor::visit "void SampleMaterialVisitor::visit(const ILayout *sample)
";

%feature("docstring")  SampleMaterialVisitor::visit "void SampleMaterialVisitor::visit(const ParticleLayout *sample)
";

%feature("docstring")  SampleMaterialVisitor::visit "void SampleMaterialVisitor::visit(const Layer *sample)
";

%feature("docstring")  SampleMaterialVisitor::visit "void SampleMaterialVisitor::visit(const LayerInterface *sample)
";

%feature("docstring")  SampleMaterialVisitor::visit "void SampleMaterialVisitor::visit(const MultiLayer *sample)
";

%feature("docstring")  SampleMaterialVisitor::visit "void SampleMaterialVisitor::visit(const Particle *sample)
";

%feature("docstring")  SampleMaterialVisitor::visit "void SampleMaterialVisitor::visit(const ParticleDistribution *sample)
";

%feature("docstring")  SampleMaterialVisitor::visit "void SampleMaterialVisitor::visit(const ParticleComposition *sample)
";

%feature("docstring")  SampleMaterialVisitor::visit "void SampleMaterialVisitor::visit(const MesoCrystal *sample)
";

%feature("docstring")  SampleMaterialVisitor::visit "void SampleMaterialVisitor::visit(const ParticleCoreShell *sample)
";

%feature("docstring")  SampleMaterialVisitor::visit "void SampleMaterialVisitor::visit(const IFormFactor *sample)
";

%feature("docstring")  SampleMaterialVisitor::visit "void SampleMaterialVisitor::visit(const FormFactorDWBAPol *sample)
";

%feature("docstring")  SampleMaterialVisitor::visit "void SampleMaterialVisitor::visit(const FormFactorWeighted *sample)
";

%feature("docstring")  SampleMaterialVisitor::visit "void SampleMaterialVisitor::visit(const IFormFactorBorn *sample)
";

%feature("docstring")  SampleMaterialVisitor::visit "void SampleMaterialVisitor::visit(const FormFactorAnisoPyramid *sample)
";

%feature("docstring")  SampleMaterialVisitor::visit "void SampleMaterialVisitor::visit(const FormFactorBox *sample)
";

%feature("docstring")  SampleMaterialVisitor::visit "void SampleMaterialVisitor::visit(const FormFactorCone *sample)
";

%feature("docstring")  SampleMaterialVisitor::visit "void SampleMaterialVisitor::visit(const FormFactorCone6 *sample)
";

%feature("docstring")  SampleMaterialVisitor::visit "void SampleMaterialVisitor::visit(const FormFactorCrystal *sample)
";

%feature("docstring")  SampleMaterialVisitor::visit "void SampleMaterialVisitor::visit(const FormFactorCuboctahedron *sample)
";

%feature("docstring")  SampleMaterialVisitor::visit "void SampleMaterialVisitor::visit(const FormFactorCylinder *sample)
";

%feature("docstring")  SampleMaterialVisitor::visit "void SampleMaterialVisitor::visit(const FormFactorDodecahedron *sample)
";

%feature("docstring")  SampleMaterialVisitor::visit "void SampleMaterialVisitor::visit(const FormFactorEllipsoidalCylinder *sample)
";

%feature("docstring")  SampleMaterialVisitor::visit "void SampleMaterialVisitor::visit(const FormFactorFullSphere *sample)
";

%feature("docstring")  SampleMaterialVisitor::visit "void SampleMaterialVisitor::visit(const FormFactorFullSpheroid *sample)
";

%feature("docstring")  SampleMaterialVisitor::visit "void SampleMaterialVisitor::visit(const FormFactorGauss *sample)
";

%feature("docstring")  SampleMaterialVisitor::visit "void SampleMaterialVisitor::visit(const FormFactorHemiEllipsoid *sample)
";

%feature("docstring")  SampleMaterialVisitor::visit "void SampleMaterialVisitor::visit(const FormFactorIcosahedron *sample)
";

%feature("docstring")  SampleMaterialVisitor::visit "void SampleMaterialVisitor::visit(const FormFactorLongBoxGauss *sample)
";

%feature("docstring")  SampleMaterialVisitor::visit "void SampleMaterialVisitor::visit(const FormFactorLongBoxLorentz *sample)
";

%feature("docstring")  SampleMaterialVisitor::visit "void SampleMaterialVisitor::visit(const FormFactorLorentz *sample)
";

%feature("docstring")  SampleMaterialVisitor::visit "void SampleMaterialVisitor::visit(const FormFactorPrism3 *sample)
";

%feature("docstring")  SampleMaterialVisitor::visit "void SampleMaterialVisitor::visit(const FormFactorPrism6 *sample)
";

%feature("docstring")  SampleMaterialVisitor::visit "void SampleMaterialVisitor::visit(const FormFactorPyramid *sample)
";

%feature("docstring")  SampleMaterialVisitor::visit "void SampleMaterialVisitor::visit(const FormFactorRipple1 *sample)
";

%feature("docstring")  SampleMaterialVisitor::visit "void SampleMaterialVisitor::visit(const FormFactorRipple2 *sample)
";

%feature("docstring")  SampleMaterialVisitor::visit "void SampleMaterialVisitor::visit(const FormFactorSphereGaussianRadius *sample)
";

%feature("docstring")  SampleMaterialVisitor::visit "void SampleMaterialVisitor::visit(const FormFactorSphereLogNormalRadius *sample)
";

%feature("docstring")  SampleMaterialVisitor::visit "void SampleMaterialVisitor::visit(const FormFactorTetrahedron *sample)
";

%feature("docstring")  SampleMaterialVisitor::visit "void SampleMaterialVisitor::visit(const FormFactorTrivial *sample)
";

%feature("docstring")  SampleMaterialVisitor::visit "void SampleMaterialVisitor::visit(const FormFactorTruncatedCube *sample)
";

%feature("docstring")  SampleMaterialVisitor::visit "void SampleMaterialVisitor::visit(const FormFactorTruncatedSphere *sample)
";

%feature("docstring")  SampleMaterialVisitor::visit "void SampleMaterialVisitor::visit(const FormFactorTruncatedSpheroid *sample)
";

%feature("docstring")  SampleMaterialVisitor::visit "void SampleMaterialVisitor::visit(const IFormFactorDecorator *sample)
";

%feature("docstring")  SampleMaterialVisitor::visit "void SampleMaterialVisitor::visit(const FormFactorDWBA *sample)
";

%feature("docstring")  SampleMaterialVisitor::visit "void SampleMaterialVisitor::visit(const FormFactorDecoratorDebyeWaller *sample)
";

%feature("docstring")  SampleMaterialVisitor::visit "void SampleMaterialVisitor::visit(const FormFactorDecoratorFactor *sample)
";

%feature("docstring")  SampleMaterialVisitor::visit "void SampleMaterialVisitor::visit(const FormFactorDecoratorMaterial *sample)
";

%feature("docstring")  SampleMaterialVisitor::visit "void SampleMaterialVisitor::visit(const FormFactorDecoratorMultiPositionFactor *sample)
";

%feature("docstring")  SampleMaterialVisitor::visit "void SampleMaterialVisitor::visit(const FormFactorDecoratorPositionFactor *sample)
";

%feature("docstring")  SampleMaterialVisitor::visit "void SampleMaterialVisitor::visit(const FormFactorDecoratorRotation *sample)
";

%feature("docstring")  SampleMaterialVisitor::visit "void SampleMaterialVisitor::visit(const IInterferenceFunction *sample)
";

%feature("docstring")  SampleMaterialVisitor::visit "void SampleMaterialVisitor::visit(const InterferenceFunction1DLattice *sample)
";

%feature("docstring")  SampleMaterialVisitor::visit "void SampleMaterialVisitor::visit(const InterferenceFunctionRadialParaCrystal *sample)
";

%feature("docstring")  SampleMaterialVisitor::visit "void SampleMaterialVisitor::visit(const InterferenceFunction2DLattice *sample)
";

%feature("docstring")  SampleMaterialVisitor::visit "void SampleMaterialVisitor::visit(const InterferenceFunction2DParaCrystal *sample)
";

%feature("docstring")  SampleMaterialVisitor::visit "void SampleMaterialVisitor::visit(const InterferenceFunctionNone *sample)
";

%feature("docstring")  SampleMaterialVisitor::visit "void SampleMaterialVisitor::visit(const IRoughness *sample)
";

%feature("docstring")  SampleMaterialVisitor::visit "void SampleMaterialVisitor::visit(const LayerRoughness *sample)
";

%feature("docstring")  SampleMaterialVisitor::visit "void SampleMaterialVisitor::visit(const RotationX *)
";

%feature("docstring")  SampleMaterialVisitor::visit "void SampleMaterialVisitor::visit(const RotationY *)
";

%feature("docstring")  SampleMaterialVisitor::visit "void SampleMaterialVisitor::visit(const RotationZ *)
";

%feature("docstring")  SampleMaterialVisitor::visit "void SampleMaterialVisitor::visit(const RotationEuler *)
";

%feature("docstring")  SampleMaterialVisitor::getMaterials "std::vector<const IMaterial *> SampleMaterialVisitor::getMaterials() const

return vector of material presented in the sample 
";

%feature("docstring")  SampleMaterialVisitor::containsMagneticMaterial "bool SampleMaterialVisitor::containsMagneticMaterial() const

return true if contains magnetic materials 
";

%feature("docstring")  SampleMaterialVisitor::clear "void SampleMaterialVisitor::clear()

clear state of the visitor 
";


// File: classSamplePrintVisitor.xml
%feature("docstring") SamplePrintVisitor "

To help composite sample to print tree-like structure on the screen.

C++ includes: SamplePrintVisitor.h
";

%feature("docstring")  SamplePrintVisitor::SamplePrintVisitor "SamplePrintVisitor::SamplePrintVisitor()
";

%feature("docstring")  SamplePrintVisitor::visit "void SamplePrintVisitor::visit(const ISample *sample)
";

%feature("docstring")  SamplePrintVisitor::visit "void SamplePrintVisitor::visit(const ICompositeSample *sample)
";

%feature("docstring")  SamplePrintVisitor::visit "void SamplePrintVisitor::visit(const IClusteredParticles *sample)
";

%feature("docstring")  SamplePrintVisitor::visit "void SamplePrintVisitor::visit(const Crystal *sample)
";

%feature("docstring")  SamplePrintVisitor::visit "void SamplePrintVisitor::visit(const ILayout *sample)
";

%feature("docstring")  SamplePrintVisitor::visit "void SamplePrintVisitor::visit(const ParticleLayout *sample)
";

%feature("docstring")  SamplePrintVisitor::visit "void SamplePrintVisitor::visit(const Layer *sample)
";

%feature("docstring")  SamplePrintVisitor::visit "void SamplePrintVisitor::visit(const LayerInterface *sample)
";

%feature("docstring")  SamplePrintVisitor::visit "void SamplePrintVisitor::visit(const MultiLayer *sample)
";

%feature("docstring")  SamplePrintVisitor::visit "void SamplePrintVisitor::visit(const Particle *sample)
";

%feature("docstring")  SamplePrintVisitor::visit "void SamplePrintVisitor::visit(const ParticleDistribution *sample)
";

%feature("docstring")  SamplePrintVisitor::visit "void SamplePrintVisitor::visit(const ParticleComposition *sample)
";

%feature("docstring")  SamplePrintVisitor::visit "void SamplePrintVisitor::visit(const MesoCrystal *sample)
";

%feature("docstring")  SamplePrintVisitor::visit "void SamplePrintVisitor::visit(const ParticleCoreShell *sample)
";

%feature("docstring")  SamplePrintVisitor::visit "void SamplePrintVisitor::visit(const IFormFactor *sample)
";

%feature("docstring")  SamplePrintVisitor::visit "void SamplePrintVisitor::visit(const FormFactorDWBAPol *sample)
";

%feature("docstring")  SamplePrintVisitor::visit "void SamplePrintVisitor::visit(const FormFactorWeighted *sample)
";

%feature("docstring")  SamplePrintVisitor::visit "void SamplePrintVisitor::visit(const IFormFactorBorn *sample)
";

%feature("docstring")  SamplePrintVisitor::visit "void SamplePrintVisitor::visit(const FormFactorAnisoPyramid *sample)
";

%feature("docstring")  SamplePrintVisitor::visit "void SamplePrintVisitor::visit(const FormFactorBox *sample)
";

%feature("docstring")  SamplePrintVisitor::visit "void SamplePrintVisitor::visit(const FormFactorCone *sample)
";

%feature("docstring")  SamplePrintVisitor::visit "void SamplePrintVisitor::visit(const FormFactorCone6 *sample)
";

%feature("docstring")  SamplePrintVisitor::visit "void SamplePrintVisitor::visit(const FormFactorCrystal *sample)
";

%feature("docstring")  SamplePrintVisitor::visit "void SamplePrintVisitor::visit(const FormFactorCuboctahedron *sample)
";

%feature("docstring")  SamplePrintVisitor::visit "void SamplePrintVisitor::visit(const FormFactorCylinder *sample)
";

%feature("docstring")  SamplePrintVisitor::visit "void SamplePrintVisitor::visit(const FormFactorDodecahedron *sample)
";

%feature("docstring")  SamplePrintVisitor::visit "void SamplePrintVisitor::visit(const FormFactorEllipsoidalCylinder *sample)
";

%feature("docstring")  SamplePrintVisitor::visit "void SamplePrintVisitor::visit(const FormFactorFullSphere *sample)
";

%feature("docstring")  SamplePrintVisitor::visit "void SamplePrintVisitor::visit(const FormFactorFullSpheroid *sample)
";

%feature("docstring")  SamplePrintVisitor::visit "void SamplePrintVisitor::visit(const FormFactorGauss *sample)
";

%feature("docstring")  SamplePrintVisitor::visit "void SamplePrintVisitor::visit(const FormFactorHemiEllipsoid *sample)
";

%feature("docstring")  SamplePrintVisitor::visit "void SamplePrintVisitor::visit(const FormFactorIcosahedron *sample)
";

%feature("docstring")  SamplePrintVisitor::visit "void SamplePrintVisitor::visit(const FormFactorLongBoxGauss *sample)
";

%feature("docstring")  SamplePrintVisitor::visit "void SamplePrintVisitor::visit(const FormFactorLongBoxLorentz *sample)
";

%feature("docstring")  SamplePrintVisitor::visit "void SamplePrintVisitor::visit(const FormFactorLorentz *sample)
";

%feature("docstring")  SamplePrintVisitor::visit "void SamplePrintVisitor::visit(const FormFactorPrism3 *sample)
";

%feature("docstring")  SamplePrintVisitor::visit "void SamplePrintVisitor::visit(const FormFactorPrism6 *sample)
";

%feature("docstring")  SamplePrintVisitor::visit "void SamplePrintVisitor::visit(const FormFactorPyramid *sample)
";

%feature("docstring")  SamplePrintVisitor::visit "void SamplePrintVisitor::visit(const FormFactorRipple1 *sample)
";

%feature("docstring")  SamplePrintVisitor::visit "void SamplePrintVisitor::visit(const FormFactorRipple2 *sample)
";

%feature("docstring")  SamplePrintVisitor::visit "void SamplePrintVisitor::visit(const FormFactorSphereGaussianRadius *sample)
";

%feature("docstring")  SamplePrintVisitor::visit "void SamplePrintVisitor::visit(const FormFactorSphereLogNormalRadius *sample)
";

%feature("docstring")  SamplePrintVisitor::visit "void SamplePrintVisitor::visit(const FormFactorTetrahedron *sample)
";

%feature("docstring")  SamplePrintVisitor::visit "void SamplePrintVisitor::visit(const FormFactorTrivial *sample)
";

%feature("docstring")  SamplePrintVisitor::visit "void SamplePrintVisitor::visit(const FormFactorTruncatedCube *sample)
";

%feature("docstring")  SamplePrintVisitor::visit "void SamplePrintVisitor::visit(const FormFactorTruncatedSphere *sample)
";

%feature("docstring")  SamplePrintVisitor::visit "void SamplePrintVisitor::visit(const FormFactorTruncatedSpheroid *sample)
";

%feature("docstring")  SamplePrintVisitor::visit "void SamplePrintVisitor::visit(const IFormFactorDecorator *sample)
";

%feature("docstring")  SamplePrintVisitor::visit "void SamplePrintVisitor::visit(const FormFactorDWBA *sample)
";

%feature("docstring")  SamplePrintVisitor::visit "void SamplePrintVisitor::visit(const FormFactorDecoratorDebyeWaller *sample)
";

%feature("docstring")  SamplePrintVisitor::visit "void SamplePrintVisitor::visit(const FormFactorDecoratorFactor *sample)
";

%feature("docstring")  SamplePrintVisitor::visit "void SamplePrintVisitor::visit(const FormFactorDecoratorMaterial *sample)
";

%feature("docstring")  SamplePrintVisitor::visit "void SamplePrintVisitor::visit(const FormFactorDecoratorMultiPositionFactor *sample)
";

%feature("docstring")  SamplePrintVisitor::visit "void SamplePrintVisitor::visit(const FormFactorDecoratorPositionFactor *sample)
";

%feature("docstring")  SamplePrintVisitor::visit "void SamplePrintVisitor::visit(const FormFactorDecoratorRotation *sample)
";

%feature("docstring")  SamplePrintVisitor::visit "void SamplePrintVisitor::visit(const IInterferenceFunction *sample)
";

%feature("docstring")  SamplePrintVisitor::visit "void SamplePrintVisitor::visit(const InterferenceFunction1DLattice *sample)
";

%feature("docstring")  SamplePrintVisitor::visit "void SamplePrintVisitor::visit(const InterferenceFunctionRadialParaCrystal *sample)
";

%feature("docstring")  SamplePrintVisitor::visit "void SamplePrintVisitor::visit(const InterferenceFunction2DLattice *sample)
";

%feature("docstring")  SamplePrintVisitor::visit "void SamplePrintVisitor::visit(const InterferenceFunction2DParaCrystal *sample)
";

%feature("docstring")  SamplePrintVisitor::visit "void SamplePrintVisitor::visit(const InterferenceFunctionNone *sample)
";

%feature("docstring")  SamplePrintVisitor::visit "void SamplePrintVisitor::visit(const IRoughness *sample)
";

%feature("docstring")  SamplePrintVisitor::visit "void SamplePrintVisitor::visit(const LayerRoughness *sample)
";

%feature("docstring")  SamplePrintVisitor::visit "void SamplePrintVisitor::visit(const RotationX *sample)
";

%feature("docstring")  SamplePrintVisitor::visit "void SamplePrintVisitor::visit(const RotationY *sample)
";

%feature("docstring")  SamplePrintVisitor::visit "void SamplePrintVisitor::visit(const RotationZ *sample)
";

%feature("docstring")  SamplePrintVisitor::visit "void SamplePrintVisitor::visit(const RotationEuler *sample)
";


// File: classSampleTreeIterator.xml
%feature("docstring") SampleTreeIterator "

Iterator through  ISample tree of objects inside  ISample object.

Usage example: SampleTreeIterator<Strategy> it(&sample); it.first(); while( !it.is_done() ) {  ISample *p_sample = it.get_current(); it.next(); }

C++ includes: SampleTreeIterator.h
";

%feature("docstring")  SampleTreeIterator::SampleTreeIterator "SampleTreeIterator< Strategy >::SampleTreeIterator(const ISample *root)
";

%feature("docstring")  SampleTreeIterator::~SampleTreeIterator "virtual SampleTreeIterator< Strategy >::~SampleTreeIterator()
";

%feature("docstring")  SampleTreeIterator::first "void SampleTreeIterator< Strategy >::first()
";

%feature("docstring")  SampleTreeIterator::next "void SampleTreeIterator< Strategy >::next()
";

%feature("docstring")  SampleTreeIterator::getCurrent "const ISample * SampleTreeIterator< Strategy >::getCurrent()
";

%feature("docstring")  SampleTreeIterator::isDone "bool SampleTreeIterator< Strategy >::isDone() const 
";

%feature("docstring")  SampleTreeIterator::getLevel "size_t SampleTreeIterator< Strategy >::getLevel() const 
";


// File: classScalarRTCoefficients.xml
%feature("docstring") ScalarRTCoefficients "

Specular reflection and transmission coefficients in a layer in case of scalar interactions between the layers and the scattered particle.

C++ includes: ScalarRTCoefficients.h
";

%feature("docstring")  ScalarRTCoefficients::ScalarRTCoefficients "ScalarRTCoefficients::ScalarRTCoefficients()
";

%feature("docstring")  ScalarRTCoefficients::~ScalarRTCoefficients "virtual ScalarRTCoefficients::~ScalarRTCoefficients()
";

%feature("docstring")  ScalarRTCoefficients::clone "ScalarRTCoefficients * ScalarRTCoefficients::clone() const 
";

%feature("docstring")  ScalarRTCoefficients::T1plus "Eigen::Vector2cd ScalarRTCoefficients::T1plus() const

The following functions return the transmitted and reflected amplitudes for different incoming beam polarizations and eigenmodes 
";

%feature("docstring")  ScalarRTCoefficients::R1plus "Eigen::Vector2cd ScalarRTCoefficients::R1plus() const 
";

%feature("docstring")  ScalarRTCoefficients::T2plus "Eigen::Vector2cd ScalarRTCoefficients::T2plus() const 
";

%feature("docstring")  ScalarRTCoefficients::R2plus "Eigen::Vector2cd ScalarRTCoefficients::R2plus() const 
";

%feature("docstring")  ScalarRTCoefficients::T1min "Eigen::Vector2cd ScalarRTCoefficients::T1min() const 
";

%feature("docstring")  ScalarRTCoefficients::R1min "Eigen::Vector2cd ScalarRTCoefficients::R1min() const 
";

%feature("docstring")  ScalarRTCoefficients::T2min "Eigen::Vector2cd ScalarRTCoefficients::T2min() const 
";

%feature("docstring")  ScalarRTCoefficients::R2min "Eigen::Vector2cd ScalarRTCoefficients::R2min() const 
";

%feature("docstring")  ScalarRTCoefficients::getKz "Eigen::Vector2cd ScalarRTCoefficients::getKz() const

Returns z-part of the two wavevector eigenmodes. 
";

%feature("docstring")  ScalarRTCoefficients::getScalarT "complex_t ScalarRTCoefficients::getScalarT() const

Scalar value getters; these throw errors by default as they should only be used when the derived object is really scalar 
";

%feature("docstring")  ScalarRTCoefficients::getScalarR "complex_t ScalarRTCoefficients::getScalarR() const 
";

%feature("docstring")  ScalarRTCoefficients::getScalarKz "virtual complex_t ScalarRTCoefficients::getScalarKz() const 
";


// File: classScalarSpecularInfoMap.xml
%feature("docstring") ScalarSpecularInfoMap "

Implementation of  ISpecularInfoMap for scalar valued reflection/ transmission coefficients.

C++ includes: ScalarSpecularInfoMap.h
";

%feature("docstring")  ScalarSpecularInfoMap::ScalarSpecularInfoMap "ScalarSpecularInfoMap::ScalarSpecularInfoMap(const MultiLayer *multilayer, int layer)
";

%feature("docstring")  ScalarSpecularInfoMap::~ScalarSpecularInfoMap "virtual ScalarSpecularInfoMap::~ScalarSpecularInfoMap()
";

%feature("docstring")  ScalarSpecularInfoMap::clone "ScalarSpecularInfoMap * ScalarSpecularInfoMap::clone() const 
";

%feature("docstring")  ScalarSpecularInfoMap::getOutCoefficients "const ScalarRTCoefficients * ScalarSpecularInfoMap::getOutCoefficients(double alpha_f, double phi_f, double wavelength) const

Retrieves the amplitude coefficients for the given angles.

Todo
Can we avoid the code duplication in the two following functions ? 
";

%feature("docstring")  ScalarSpecularInfoMap::getInCoefficients "const ScalarRTCoefficients * ScalarSpecularInfoMap::getInCoefficients(double alpha_i, double phi_i, double wavelength) const

Retrieves the amplitude coefficients for the given angles. 
";


// File: classExceptions_1_1SelfReferenceException.xml
%feature("docstring") Exceptions::SelfReferenceException "";

%feature("docstring")  Exceptions::SelfReferenceException::SelfReferenceException "Exceptions::SelfReferenceException::SelfReferenceException(const std::string &message)
";


// File: classSimpleSelectionRule.xml
%feature("docstring") SimpleSelectionRule "

Selection rule (v*q)modulus!=0, defined by vector v(a,b,c) and modulus.

C++ includes: ISelectionRule.h
";

%feature("docstring")  SimpleSelectionRule::SimpleSelectionRule "SimpleSelectionRule::SimpleSelectionRule(int a, int b, int c, int modulus)
";

%feature("docstring")  SimpleSelectionRule::~SimpleSelectionRule "virtual SimpleSelectionRule::~SimpleSelectionRule()
";

%feature("docstring")  SimpleSelectionRule::clone "SimpleSelectionRule * SimpleSelectionRule::clone() const 
";

%feature("docstring")  SimpleSelectionRule::coordinateSelected "bool SimpleSelectionRule::coordinateSelected(const IndexVector3D &coordinate) const 
";


// File: classSimulation.xml
%feature("docstring") Simulation "

Main class to run the simulation.

C++ includes: GISASSimulation.h
";

%feature("docstring")  Simulation::Simulation "Simulation::Simulation()
";

%feature("docstring")  Simulation::Simulation "Simulation::Simulation(const ISample &p_sample)
";

%feature("docstring")  Simulation::Simulation "Simulation::Simulation(SampleBuilder_t p_sample_builder)
";

%feature("docstring")  Simulation::~Simulation "virtual Simulation::~Simulation()
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

%feature("docstring")  Simulation::runOMPISimulation "void Simulation::runOMPISimulation()

Run an OpenMPI simulation. 
";

%feature("docstring")  Simulation::setSample "void Simulation::setSample(const ISample &sample)

Sets the sample to be tested.

The  ISample object will not be owned by the  Simulation object. 
";

%feature("docstring")  Simulation::getSample "ISample* Simulation::getSample() const

Returns the sample. 
";

%feature("docstring")  Simulation::setSampleBuilder "void Simulation::setSampleBuilder(SampleBuilder_t sample_builder)

Sets the sample builder. 
";

%feature("docstring")  Simulation::getSampleBuilder "SampleBuilder_t Simulation::getSampleBuilder() const

return sample builder 
";

%feature("docstring")  Simulation::getNumberOfSimulationElements "virtual int Simulation::getNumberOfSimulationElements() const =0

Gets the number of elements this simulation needs to calculate. 
";

%feature("docstring")  Simulation::getDetectorIntensity "virtual OutputData<double>* Simulation::getDetectorIntensity(IDetector2D::EAxesUnits units_type=IDetector2D::DEFAULT) const =0

Clone simulated intensity map. 
";

%feature("docstring")  Simulation::addParametersToExternalPool "std::string Simulation::addParametersToExternalPool(std::string path, ParameterPool *external_pool, int copy_number=-1) const

Adds parameters from local to external pool, and call recursion over direct children. 
";

%feature("docstring")  Simulation::addParameterDistribution "void Simulation::addParameterDistribution(const std::string &param_name, const IDistribution1D &distribution, size_t nbr_samples, double sigma_factor=0.0, const AttLimits &limits=AttLimits())

add a sampled parameter distribution 
";

%feature("docstring")  Simulation::addParameterDistribution "void Simulation::addParameterDistribution(const ParameterDistribution &par_distr)

add a sampled parameter distribution 
";

%feature("docstring")  Simulation::getDistributionHandler "const DistributionHandler & Simulation::getDistributionHandler() const 
";

%feature("docstring")  Simulation::setProgressHandler "void Simulation::setProgressHandler(ProgressHandler_t progress)

sets progress handler (used by GUI) 
";

%feature("docstring")  Simulation::initProgressHandlerDWBA "void Simulation::initProgressHandlerDWBA(ProgressHandlerDWBA *dwba_progress)

initializes DWBA progress handler 
";

%feature("docstring")  Simulation::setOptions "void Simulation::setOptions(const SimulationOptions &options)
";

%feature("docstring")  Simulation::getOptions "const SimulationOptions & Simulation::getOptions() const 
";

%feature("docstring")  Simulation::getOptions "SimulationOptions & Simulation::getOptions()
";


// File: classSimulationElement.xml
%feature("docstring") SimulationElement "

Data stucture containing both input and output of a single detector cell.

C++ includes: SimulationElement.h
";

%feature("docstring")  SimulationElement::SimulationElement "SimulationElement::SimulationElement(double wavelength, double alpha_i, double phi_i, const IPixelMap *pixelmap)
";

%feature("docstring")  SimulationElement::SimulationElement "SimulationElement::SimulationElement(const SimulationElement &other)
";

%feature("docstring")  SimulationElement::SimulationElement "SimulationElement::SimulationElement(const SimulationElement &other, double x, double y)

Construct  SimulationElement from other element and restrict k_f to specific value in the original detector pixel 
";

%feature("docstring")  SimulationElement::~SimulationElement "SimulationElement::~SimulationElement()
";

%feature("docstring")  SimulationElement::setPolarization "void SimulationElement::setPolarization(const Eigen::Matrix2cd &polarization)

Sets the polarization density matrix (in spin basis along z-axis) 
";

%feature("docstring")  SimulationElement::getPolarization "Eigen::Matrix2cd SimulationElement::getPolarization() const

Gets the polarization density matrix (in spin basis along z-axis) 
";

%feature("docstring")  SimulationElement::setAnalyzerOperator "void SimulationElement::setAnalyzerOperator(const Eigen::Matrix2cd &polarization_operator)

Sets the polarization analyzer operator (in spin basis along z-axis) 
";

%feature("docstring")  SimulationElement::getAnalyzerOperator "Eigen::Matrix2cd SimulationElement::getAnalyzerOperator() const

Gets the polarization analyzer operator (in spin basis along z-axis) 
";

%feature("docstring")  SimulationElement::getWavelength "double SimulationElement::getWavelength() const 
";

%feature("docstring")  SimulationElement::getAlphaI "double SimulationElement::getAlphaI() const 
";

%feature("docstring")  SimulationElement::getPhiI "double SimulationElement::getPhiI() const 
";

%feature("docstring")  SimulationElement::getAlphaMean "double SimulationElement::getAlphaMean() const 
";

%feature("docstring")  SimulationElement::getPhiMean "double SimulationElement::getPhiMean() const 
";

%feature("docstring")  SimulationElement::setIntensity "void SimulationElement::setIntensity(double intensity)
";

%feature("docstring")  SimulationElement::addIntensity "void SimulationElement::addIntensity(double intensity)
";

%feature("docstring")  SimulationElement::getIntensity "double SimulationElement::getIntensity() const 
";

%feature("docstring")  SimulationElement::getKI "kvector_t SimulationElement::getKI() const 
";

%feature("docstring")  SimulationElement::getMeanKF "kvector_t SimulationElement::getMeanKF() const 
";

%feature("docstring")  SimulationElement::getMeanQ "kvector_t SimulationElement::getMeanQ() const 
";

%feature("docstring")  SimulationElement::getQ "kvector_t SimulationElement::getQ(double x, double y) const 
";

%feature("docstring")  SimulationElement::getK "kvector_t SimulationElement::getK(double x, double y) const 
";

%feature("docstring")  SimulationElement::getIntegrationFactor "double SimulationElement::getIntegrationFactor(double x, double y) const 
";

%feature("docstring")  SimulationElement::getSolidAngle "double SimulationElement::getSolidAngle() const 
";

%feature("docstring")  SimulationElement::getAlpha "double SimulationElement::getAlpha(double x, double y) const

get alpha for given detector pixel coordinates 
";

%feature("docstring")  SimulationElement::getPhi "double SimulationElement::getPhi(double x, double y) const

get phi for given detector pixel coordinates 
";


// File: classSimulationOptions.xml
%feature("docstring") SimulationOptions "

Collect the different options for simulation  SimulationOptions.

C++ includes: SimulationOptions.h
";

%feature("docstring")  SimulationOptions::SimulationOptions "SimulationOptions::SimulationOptions()
";

%feature("docstring")  SimulationOptions::isIntegrate "bool SimulationOptions::isIntegrate() const 
";

%feature("docstring")  SimulationOptions::getMcPoints "size_t SimulationOptions::getMcPoints() const 
";

%feature("docstring")  SimulationOptions::setMonteCarloIntegration "void SimulationOptions::setMonteCarloIntegration(bool flag=true, size_t mc_points=50)

Enables/disables MonetCarlo integration.

Parameters:
-----------

flag: 
If true, MonteCarlo integration will be used, otherwise analytical calculations

mc_points: 
Number of points for MonteCarlo integrator 
";

%feature("docstring")  SimulationOptions::setNumberOfThreads "void SimulationOptions::setNumberOfThreads(int nthreads)

Sets number of threads to use during the simulation (0 - take the default value from the hardware) 
";

%feature("docstring")  SimulationOptions::getNumberOfThreads "int SimulationOptions::getNumberOfThreads() const 
";

%feature("docstring")  SimulationOptions::setNumberOfBatches "void SimulationOptions::setNumberOfBatches(int nbatches)

Sets number of batches to split. 
";

%feature("docstring")  SimulationOptions::getNumberOfBatches "int SimulationOptions::getNumberOfBatches() const 
";

%feature("docstring")  SimulationOptions::getCurrentBatch "int SimulationOptions::getCurrentBatch() const 
";

%feature("docstring")  SimulationOptions::setThreadInfo "void SimulationOptions::setThreadInfo(const ThreadInfo &thread_info)

Sets the batch and thread information to be used. 
";

%feature("docstring")  SimulationOptions::getHardwareConcurrency "int SimulationOptions::getHardwareConcurrency() const 
";


// File: classSimulationRegistry.xml
%feature("docstring") SimulationRegistry "

Registry to create standard pre-defined simulations. Used in functional tests, performance measurements, etc.

C++ includes: SimulationRegistry.h
";

%feature("docstring")  SimulationRegistry::SimulationRegistry "SimulationRegistry::SimulationRegistry()
";

%feature("docstring")  SimulationRegistry::createSimulation "GISASSimulation * SimulationRegistry::createSimulation(const std::string &name)
";


// File: classSizeDistributionDAModelBuilder.xml
%feature("docstring") SizeDistributionDAModelBuilder "

Creates the sample demonstrating size distribution model in decoupling approximation. Equivalent of Examples/python/simulation/ex03_InterferenceFunctions/ApproximationDA.py.

C++ includes: SizeDistributionModelsBuilder.h
";

%feature("docstring")  SizeDistributionDAModelBuilder::SizeDistributionDAModelBuilder "SizeDistributionDAModelBuilder::SizeDistributionDAModelBuilder()
";

%feature("docstring")  SizeDistributionDAModelBuilder::buildSample "ISample * SizeDistributionDAModelBuilder::buildSample() const 
";


// File: classSizeDistributionLMAModelBuilder.xml
%feature("docstring") SizeDistributionLMAModelBuilder "

Creates the sample demonstrating size distribution model in local monodisperse approximation. Equivalent of Examples/python/simulation/ex03_InterferenceFunctions/ApproximationLMA.py.

C++ includes: SizeDistributionModelsBuilder.h
";

%feature("docstring")  SizeDistributionLMAModelBuilder::SizeDistributionLMAModelBuilder "SizeDistributionLMAModelBuilder::SizeDistributionLMAModelBuilder()
";

%feature("docstring")  SizeDistributionLMAModelBuilder::buildSample "ISample * SizeDistributionLMAModelBuilder::buildSample() const 
";


// File: classSizeDistributionSSCAModelBuilder.xml
%feature("docstring") SizeDistributionSSCAModelBuilder "

Creates the sample demonstrating size distribution model in size space coupling approximation. Equivalent of Examples/python/simulation/ex03_InterferenceFunctions/ApproximationSSCA.py.

C++ includes: SizeDistributionModelsBuilder.h
";

%feature("docstring")  SizeDistributionSSCAModelBuilder::SizeDistributionSSCAModelBuilder "SizeDistributionSSCAModelBuilder::SizeDistributionSSCAModelBuilder()
";

%feature("docstring")  SizeDistributionSSCAModelBuilder::buildSample "ISample * SizeDistributionSSCAModelBuilder::buildSample() const 
";


// File: classSizeSpacingCorrelationApproximationStrategy.xml
%feature("docstring") SizeSpacingCorrelationApproximationStrategy "

Strategy which implements size spacing correlation approximation.

C++ includes: SizeSpacingCorrelationApproximationStrategy.h
";

%feature("docstring")  SizeSpacingCorrelationApproximationStrategy::SizeSpacingCorrelationApproximationStrategy "SizeSpacingCorrelationApproximationStrategy::SizeSpacingCorrelationApproximationStrategy(SimulationOptions sim_params, double kappa)
";

%feature("docstring")  SizeSpacingCorrelationApproximationStrategy::~SizeSpacingCorrelationApproximationStrategy "virtual SizeSpacingCorrelationApproximationStrategy::~SizeSpacingCorrelationApproximationStrategy()
";

%feature("docstring")  SizeSpacingCorrelationApproximationStrategy::init "void SizeSpacingCorrelationApproximationStrategy::init(const SafePointerVector< FormFactorInfo > &form_factor_infos, const IInterferenceFunction &iff)

Initializes the object with form factors and interference functions. 
";


// File: classSpecularMagnetic.xml
%feature("docstring") SpecularMagnetic "

Implements the matrix formalism for the calculation of wave amplitudes of the coherent wave solution in a multilayer with magnetization.

C++ includes: SpecularMagnetic.h
";


// File: classSpecularMatrix.xml
%feature("docstring") SpecularMatrix "

Implements method 'execute' to compute refraction angles and transmission/reflection coefficients for coherent wave propagation in a multilayer.

C++ includes: SpecularMatrix.h
";


// File: classSpecularSimulation.xml
%feature("docstring") SpecularSimulation "

Main class to run a specular simulation.

C++ includes: SpecularSimulation.h
";

%feature("docstring")  SpecularSimulation::SpecularSimulation "SpecularSimulation::SpecularSimulation()
";

%feature("docstring")  SpecularSimulation::SpecularSimulation "SpecularSimulation::SpecularSimulation(const ISample &sample)
";

%feature("docstring")  SpecularSimulation::SpecularSimulation "SpecularSimulation::SpecularSimulation(SampleBuilder_t sample_builder)
";

%feature("docstring")  SpecularSimulation::~SpecularSimulation "SpecularSimulation::~SpecularSimulation()
";

%feature("docstring")  SpecularSimulation::clone "SpecularSimulation * SpecularSimulation::clone() const 
";

%feature("docstring")  SpecularSimulation::runSimulation "void SpecularSimulation::runSimulation()

Run a simulation with the current parameter settings. 
";

%feature("docstring")  SpecularSimulation::setSample "void SpecularSimulation::setSample(const ISample &sample)

Sets the sample to be tested. 
";

%feature("docstring")  SpecularSimulation::getSample "ISample * SpecularSimulation::getSample() const

Returns the sample. 
";

%feature("docstring")  SpecularSimulation::setSampleBuilder "void SpecularSimulation::setSampleBuilder(SampleBuilder_t sample_builder)

Sets the sample builder. 
";

%feature("docstring")  SpecularSimulation::getSampleBuilder "SampleBuilder_t SpecularSimulation::getSampleBuilder() const

return sample builder 
";

%feature("docstring")  SpecularSimulation::setBeamParameters "void SpecularSimulation::setBeamParameters(double lambda, const IAxis &alpha_axis)

Sets beam parameters with alpha_i of the beam defined in the range. 
";

%feature("docstring")  SpecularSimulation::setBeamParameters "void SpecularSimulation::setBeamParameters(double lambda, int nbins, double alpha_i_min, double alpha_i_max)
";

%feature("docstring")  SpecularSimulation::setEvanescentWaveAxis "void SpecularSimulation::setEvanescentWaveAxis(const IAxis &z_axis)

set axis for evanescent wave axis 
";

%feature("docstring")  SpecularSimulation::setEvanescentWaveAxis "void SpecularSimulation::setEvanescentWaveAxis(int nbins, double z_min, double z_max)
";

%feature("docstring")  SpecularSimulation::getAlphaAxis "const IAxis * SpecularSimulation::getAlphaAxis() const

returns alpha_i axis 
";

%feature("docstring")  SpecularSimulation::getScalarR "std::vector< complex_t > SpecularSimulation::getScalarR(size_t i_layer) const

returns vector containing reflection coefficients for all alpha_i angles for given layer index 
";

%feature("docstring")  SpecularSimulation::getScalarT "std::vector< complex_t > SpecularSimulation::getScalarT(size_t i_layer) const

returns vector containing transmission coefficients for all alpha_i angles for given layer index 
";

%feature("docstring")  SpecularSimulation::getScalarKz "std::vector< complex_t > SpecularSimulation::getScalarKz(size_t i_layer) const

returns vector containing Kz coefficients for all alpha_i angles for given layer index 
";

%feature("docstring")  SpecularSimulation::getLayerRTCoefficients "SpecularSimulation::LayerRTCoefficients_t SpecularSimulation::getLayerRTCoefficients(size_t i_alpha, size_t i_layer) const 
";

%feature("docstring")  SpecularSimulation::prepareSimulation "void SpecularSimulation::prepareSimulation()

Put into a clean state for running a simulation. 
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

%feature("docstring")  SphericalDetector::clone "SphericalDetector * SphericalDetector::clone() const 
";

%feature("docstring")  SphericalDetector::~SphericalDetector "virtual SphericalDetector::~SphericalDetector()
";

%feature("docstring")  SphericalDetector::addParametersToExternalPool "std::string SphericalDetector::addParametersToExternalPool(std::string path, ParameterPool *external_pool, int copy_number=-1) const

Adds parameters from local pool to external pool and recursively calls its direct children. 
";

%feature("docstring")  SphericalDetector::createDetectorMap "OutputData< double > * SphericalDetector::createDetectorMap(const Beam &beam, EAxesUnits units_type) const

Returns detector map in given axes units. 
";

%feature("docstring")  SphericalDetector::getValidAxesUnits "std::vector< IDetector2D::EAxesUnits > SphericalDetector::getValidAxesUnits() const

returns vector of valid axes units 
";

%feature("docstring")  SphericalDetector::getDefaultAxesUnits "IDetector2D::EAxesUnits SphericalDetector::getDefaultAxesUnits() const

return default axes units 
";


// File: classSquaredFunctionDefault.xml
%feature("docstring") SquaredFunctionDefault "

Squared difference between two values.

value = (a-b)*(a-b)/norm, where norm = max(b, 1.0) a - simulated values, b - real_values

C++ includes: ISquaredFunction.h
";

%feature("docstring")  SquaredFunctionDefault::SquaredFunctionDefault "SquaredFunctionDefault::SquaredFunctionDefault()
";

%feature("docstring")  SquaredFunctionDefault::~SquaredFunctionDefault "virtual SquaredFunctionDefault::~SquaredFunctionDefault()
";

%feature("docstring")  SquaredFunctionDefault::clone "virtual SquaredFunctionDefault* SquaredFunctionDefault::clone() const 
";

%feature("docstring")  SquaredFunctionDefault::calculateSquaredDifference "virtual double SquaredFunctionDefault::calculateSquaredDifference(double real_value, double simulated_value) const 
";

%feature("docstring")  SquaredFunctionDefault::calculateSquaredError "virtual double SquaredFunctionDefault::calculateSquaredError(double real_value, double simulated_value=0) const 
";


// File: classSquaredFunctionGaussianError.xml
%feature("docstring") SquaredFunctionGaussianError "

Squared difference between two values with gaussian error.

value = (a-b)*(a-b)/norm, where norm = sigma*sigma, sigma - is set by user

C++ includes: ISquaredFunction.h
";

%feature("docstring")  SquaredFunctionGaussianError::SquaredFunctionGaussianError "SquaredFunctionGaussianError::SquaredFunctionGaussianError(double sigma=0.01)
";

%feature("docstring")  SquaredFunctionGaussianError::~SquaredFunctionGaussianError "virtual SquaredFunctionGaussianError::~SquaredFunctionGaussianError()
";

%feature("docstring")  SquaredFunctionGaussianError::clone "virtual SquaredFunctionGaussianError* SquaredFunctionGaussianError::clone() const 
";

%feature("docstring")  SquaredFunctionGaussianError::calculateSquaredDifference "virtual double SquaredFunctionGaussianError::calculateSquaredDifference(double real_value, double simulated_value) const 
";

%feature("docstring")  SquaredFunctionGaussianError::calculateSquaredError "virtual double SquaredFunctionGaussianError::calculateSquaredError(double, double) const 
";


// File: classSquaredFunctionMeanSquaredError.xml
%feature("docstring") SquaredFunctionMeanSquaredError "

Squared difference between two values normalized by mean squared error.

value = (a-b)*(a-b)/norm, where norm = sqrt(sigma1*sigma1 + sigma2*sigma2), sigma1=max(a, 1.0), sigma2=max(b,1.0)

C++ includes: ISquaredFunction.h
";

%feature("docstring")  SquaredFunctionMeanSquaredError::SquaredFunctionMeanSquaredError "SquaredFunctionMeanSquaredError::SquaredFunctionMeanSquaredError()
";

%feature("docstring")  SquaredFunctionMeanSquaredError::~SquaredFunctionMeanSquaredError "virtual SquaredFunctionMeanSquaredError::~SquaredFunctionMeanSquaredError()
";

%feature("docstring")  SquaredFunctionMeanSquaredError::clone "virtual SquaredFunctionMeanSquaredError* SquaredFunctionMeanSquaredError::clone() const 
";

%feature("docstring")  SquaredFunctionMeanSquaredError::calculateSquaredDifference "virtual double SquaredFunctionMeanSquaredError::calculateSquaredDifference(double real_value, double simulated_value) const 
";

%feature("docstring")  SquaredFunctionMeanSquaredError::calculateSquaredError "virtual double SquaredFunctionMeanSquaredError::calculateSquaredError(double real_value, double simulated_value) const 
";


// File: classSquaredFunctionSimError.xml
%feature("docstring") SquaredFunctionSimError "

Squared difference between two values.

value = (a-b)*(a-b)/norm, where norm = max(a, 1.0) a - simulated values, b - real_values

C++ includes: ISquaredFunction.h
";

%feature("docstring")  SquaredFunctionSimError::SquaredFunctionSimError "SquaredFunctionSimError::SquaredFunctionSimError()
";

%feature("docstring")  SquaredFunctionSimError::~SquaredFunctionSimError "virtual SquaredFunctionSimError::~SquaredFunctionSimError()
";

%feature("docstring")  SquaredFunctionSimError::clone "virtual SquaredFunctionSimError* SquaredFunctionSimError::clone() const 
";

%feature("docstring")  SquaredFunctionSimError::calculateSquaredDifference "virtual double SquaredFunctionSimError::calculateSquaredDifference(double real_value, double simulated_value) const 
";

%feature("docstring")  SquaredFunctionSimError::calculateSquaredError "virtual double SquaredFunctionSimError::calculateSquaredError(double real_value, double simulated_value) const 
";


// File: classSquaredFunctionSystematicError.xml
%feature("docstring") SquaredFunctionSystematicError "

Squared difference between two values normalized by systematic error.

value = (a-b)*(a-b)/norm, where norm = max(error, 1.0), error = b + (epsilon*b)**2

C++ includes: ISquaredFunction.h
";

%feature("docstring")  SquaredFunctionSystematicError::SquaredFunctionSystematicError "SquaredFunctionSystematicError::SquaredFunctionSystematicError(double epsilon=0.08)
";

%feature("docstring")  SquaredFunctionSystematicError::~SquaredFunctionSystematicError "virtual SquaredFunctionSystematicError::~SquaredFunctionSystematicError()
";

%feature("docstring")  SquaredFunctionSystematicError::clone "virtual SquaredFunctionSystematicError* SquaredFunctionSystematicError::clone() const 
";

%feature("docstring")  SquaredFunctionSystematicError::calculateSquaredDifference "virtual double SquaredFunctionSystematicError::calculateSquaredDifference(double real_value, double simulated_value) const 
";

%feature("docstring")  SquaredFunctionSystematicError::calculateSquaredError "virtual double SquaredFunctionSystematicError::calculateSquaredError(double real_value, double simulated_value) const 
";


// File: classSquareLatticeBuilder.xml
%feature("docstring") SquareLatticeBuilder "

Builds sample: 2D lattice with different disorder (IsGISAXS example #6)

C++ includes: TwoDimLatticeBuilder.h
";

%feature("docstring")  SquareLatticeBuilder::SquareLatticeBuilder "SquareLatticeBuilder::SquareLatticeBuilder()
";

%feature("docstring")  SquareLatticeBuilder::buildSample "ISample * SquareLatticeBuilder::buildSample() const 
";


// File: classUtils_1_1String.xml
%feature("docstring") Utils::String "

Collection of utilities for std::string.

C++ includes: Utils.h
";


// File: classUtils_1_1StringUsageMap.xml
%feature("docstring") Utils::StringUsageMap "

Control how often a string is used.

C++ includes: Utils.h
";

%feature("docstring")  Utils::StringUsageMap::StringUsageMap "Utils::StringUsageMap::StringUsageMap()
";

%feature("docstring")  Utils::StringUsageMap::~StringUsageMap "Utils::StringUsageMap::~StringUsageMap()
";

%feature("docstring")  Utils::StringUsageMap::add "void Utils::StringUsageMap::add(std::string name)

Adds string to the map to count number of times it was used. 
";

%feature("docstring")  Utils::StringUsageMap::begin "iterator_t Utils::StringUsageMap::begin()

access to the map of strings 
";

%feature("docstring")  Utils::StringUsageMap::end "iterator_t Utils::StringUsageMap::end()
";

%feature("docstring")  Utils::StringUsageMap::get_current "std::string Utils::StringUsageMap::get_current() const

Returns current string. 
";


// File: classUtils_1_1System.xml
%feature("docstring") Utils::System "";


// File: classTestFormFactorsRegistry.xml
%feature("docstring") TestFormFactorsRegistry "

Registry with predifined form factors for functional tests purpose.

C++ includes: TestComponentsRegistry.h
";

%feature("docstring")  TestFormFactorsRegistry::TestFormFactorsRegistry "TestFormFactorsRegistry::TestFormFactorsRegistry()
";


// File: classTestFTDistribution2DRegistry.xml
%feature("docstring") TestFTDistribution2DRegistry "

Registry with predifined fourier transformed distributions for functional tests purpose.

C++ includes: TestComponentsRegistry.h
";

%feature("docstring")  TestFTDistribution2DRegistry::TestFTDistribution2DRegistry "TestFTDistribution2DRegistry::TestFTDistribution2DRegistry()
";


// File: structThreadInfo.xml
%feature("docstring") ThreadInfo "

Information to run simulation with dedicated number of threads.

C++ includes: ThreadInfo.h
";

%feature("docstring")  ThreadInfo::ThreadInfo "ThreadInfo::ThreadInfo()
";


// File: classTRange.xml
%feature("docstring") TRange "

An interval [lowerBound..upperBound[.

C++ includes: TRange.h
";

%feature("docstring")  TRange::TRange "TRange< T >::TRange(T lowerBound, T upperBound)
";

%feature("docstring")  TRange::~TRange "virtual TRange< T >::~TRange()
";

%feature("docstring")  TRange::getLowerBound "T TRange< T >::getLowerBound() const 
";

%feature("docstring")  TRange::getUpperBound "T TRange< T >::getUpperBound() const 
";

%feature("docstring")  TRange::getDifference "T TRange< T >::getDifference() const 
";

%feature("docstring")  TRange::inRange "bool TRange< T >::inRange(T value) const 
";


// File: classGeometry_1_1Transform3D.xml
%feature("docstring") Geometry::Transform3D "

Vector transformations in three dimensions.

C++ includes: Transform3D.h
";

%feature("docstring")  Geometry::Transform3D::Transform3D "Geometry::Transform3D::Transform3D()

Constructs unit transformation. 
";

%feature("docstring")  Geometry::Transform3D::Transform3D "Geometry::Transform3D::Transform3D(const Transform3D &other)

Copy constructor. 
";

%feature("docstring")  Geometry::Transform3D::~Transform3D "Geometry::Transform3D::~Transform3D()

Destructor. 
";

%feature("docstring")  Geometry::Transform3D::clone "Geometry::Transform3D * Geometry::Transform3D::clone() const

Clones the transformation. 
";

%feature("docstring")  Geometry::Transform3D::calculateEulerAngles "void Geometry::Transform3D::calculateEulerAngles(double *p_alpha, double *p_beta, double *p_gamma) const

Calculates the Euler angles corresponding to the rotation. 
";

%feature("docstring")  Geometry::Transform3D::getInverse "Geometry::Transform3D Geometry::Transform3D::getInverse() const

Returns the inverse transformation. 
";

%feature("docstring")  Geometry::Transform3D::transformed "Geometry::BasicVector3D< double > Geometry::Transform3D::transformed(const BasicVector3D< double > &v) const

Return transformed vector  v. 
";

%feature("docstring")  Geometry::Transform3D::transformed "Geometry::BasicVector3D< complex_t > Geometry::Transform3D::transformed(const BasicVector3D< complex_t > &v) const

Return transformed vector  v. 
";

%feature("docstring")  Geometry::Transform3D::transformedInverse "Geometry::BasicVector3D< double > Geometry::Transform3D::transformedInverse(const BasicVector3D< double > &v) const

Return transformed vector  v. 
";

%feature("docstring")  Geometry::Transform3D::transformedInverse "Geometry::BasicVector3D< complex_t > Geometry::Transform3D::transformedInverse(const BasicVector3D< complex_t > &v) const

Return transformed vector  v. 
";

%feature("docstring")  Geometry::Transform3D::getRotationType "Geometry::Transform3D::ERotationType Geometry::Transform3D::getRotationType() const

Retrieve the rotation type (general, around x, y or z-axis) 
";

%feature("docstring")  Geometry::Transform3D::isIdentity "bool Geometry::Transform3D::isIdentity() const

Determine if the transformation is trivial (identity) 
";

%feature("docstring")  Geometry::Transform3D::print "void Geometry::Transform3D::print(std::ostream &ostr) const 
";


// File: classTransformBoxBuilder.xml
%feature("docstring") TransformBoxBuilder "

Rotated box in 3 layers system.

C++ includes: TransformationsBuilder.h
";

%feature("docstring")  TransformBoxBuilder::TransformBoxBuilder "TransformBoxBuilder::TransformBoxBuilder()
";

%feature("docstring")  TransformBoxBuilder::buildSample "ISample * TransformBoxBuilder::buildSample() const 
";


// File: classTriangularRippleBuilder.xml
%feature("docstring") TriangularRippleBuilder "

Builds sample: triangular ripple within the 1D-paracrystal model (from PRB 85, 235415, 2012)

C++ includes: RipplesBuilder.h
";

%feature("docstring")  TriangularRippleBuilder::TriangularRippleBuilder "TriangularRippleBuilder::TriangularRippleBuilder()
";

%feature("docstring")  TriangularRippleBuilder::buildSample "ISample * TriangularRippleBuilder::buildSample() const 
";


// File: classTSampledRange.xml
%feature("docstring") TSampledRange "

An interval [lowerBound..upperBound[, and a number of samples.

C++ includes: TRange.h
";

%feature("docstring")  TSampledRange::TSampledRange "TSampledRange< T >::TSampledRange(size_t n_samples, T lowerBound, T upperBound)
";

%feature("docstring")  TSampledRange::getNSamples "size_t TSampledRange< T >::getNSamples() const 
";


// File: classTwoTypesCylindersDistributionBuilder.xml
%feature("docstring") TwoTypesCylindersDistributionBuilder "

Builds sample: mixture cylinder particles with different size distribution (IsGISAXS example #2)

C++ includes: ParticleDistributionsBuilder.h
";

%feature("docstring")  TwoTypesCylindersDistributionBuilder::TwoTypesCylindersDistributionBuilder "TwoTypesCylindersDistributionBuilder::TwoTypesCylindersDistributionBuilder()
";

%feature("docstring")  TwoTypesCylindersDistributionBuilder::buildSample "ISample * TwoTypesCylindersDistributionBuilder::buildSample() const 
";


// File: classExceptions_1_1UnknownClassRegistrationException.xml
%feature("docstring") Exceptions::UnknownClassRegistrationException "";

%feature("docstring")  Exceptions::UnknownClassRegistrationException::UnknownClassRegistrationException "Exceptions::UnknownClassRegistrationException::UnknownClassRegistrationException(const std::string &message)
";


// File: classUtils_1_1UnorderedMap.xml
%feature("docstring") Utils::UnorderedMap "

Unordered map (wrap boost::unordered_map).

C++ includes: Utils.h
";

%feature("docstring")  Utils::UnorderedMap::UnorderedMap "Utils::UnorderedMap< Key, Object >::UnorderedMap()
";

%feature("docstring")  Utils::UnorderedMap::~UnorderedMap "virtual Utils::UnorderedMap< Key, Object >::~UnorderedMap()
";

%feature("docstring")  Utils::UnorderedMap::clear "void Utils::UnorderedMap< Key, Object >::clear()
";

%feature("docstring")  Utils::UnorderedMap::begin "const_iterator Utils::UnorderedMap< Key, Object >::begin() const 
";

%feature("docstring")  Utils::UnorderedMap::end "const_iterator Utils::UnorderedMap< Key, Object >::end() const 
";

%feature("docstring")  Utils::UnorderedMap::find "const Object& Utils::UnorderedMap< Key, Object >::find(const Key &key) const 
";

%feature("docstring")  Utils::UnorderedMap::size "size_t Utils::UnorderedMap< Key, Object >::size()
";


// File: classVariableBinAxis.xml
%feature("docstring") VariableBinAxis "

Axis with variable bin size.

C++ includes: VariableBinAxis.h
";

%feature("docstring")  VariableBinAxis::VariableBinAxis "VariableBinAxis::VariableBinAxis(const std::string &name, size_t nbins, const std::vector< double > &bin_boundaries)

VariableBinAxis constructor.

Parameters:
-----------

name: 
Axis name

nbins: 
number of bins

bin_boundaries: 
Array of size nbins+1 containing low-edges for each bin and upper edge of last bin. 
";

%feature("docstring")  VariableBinAxis::~VariableBinAxis "virtual VariableBinAxis::~VariableBinAxis()
";

%feature("docstring")  VariableBinAxis::clone "VariableBinAxis * VariableBinAxis::clone() const

clone function 
";

%feature("docstring")  VariableBinAxis::getSize "size_t VariableBinAxis::getSize() const

retrieve the number of bins 
";

%feature("docstring")  VariableBinAxis::getBin "Bin1D VariableBinAxis::getBin(size_t index) const

retrieve a 1d bin for the given index 
";

%feature("docstring")  VariableBinAxis::getMin "double VariableBinAxis::getMin() const

Returns value of first point of axis. 
";

%feature("docstring")  VariableBinAxis::getMax "double VariableBinAxis::getMax() const

Returns value of last point of axis. 
";

%feature("docstring")  VariableBinAxis::getBinCenter "double VariableBinAxis::getBinCenter(size_t index) const 
";

%feature("docstring")  VariableBinAxis::findClosestIndex "size_t VariableBinAxis::findClosestIndex(double value) const

find bin index which is best match for given value 
";

%feature("docstring")  VariableBinAxis::getBinCenters "std::vector< double > VariableBinAxis::getBinCenters() const 
";

%feature("docstring")  VariableBinAxis::getBinBoundaries "std::vector< double > VariableBinAxis::getBinBoundaries() const 
";

%feature("docstring")  VariableBinAxis::createClippedAxis "VariableBinAxis * VariableBinAxis::createClippedAxis(double left, double right) const

Creates a new clipped axis. 
";


// File: classGeometry_1_1VerticalLine.xml
%feature("docstring") Geometry::VerticalLine "

Vertical infinite line.

C++ includes: Line.h
";

%feature("docstring")  Geometry::VerticalLine::VerticalLine "Geometry::VerticalLine::VerticalLine(double x)

Infinite vertical line constructor

Parameters:
-----------

x: 
The value at which it crosses x-axes 
";

%feature("docstring")  Geometry::VerticalLine::clone "VerticalLine * Geometry::VerticalLine::clone() const 
";

%feature("docstring")  Geometry::VerticalLine::contains "bool Geometry::VerticalLine::contains(double x, double y) const

Returns true if given point is on this line segment (y is unused) 
";

%feature("docstring")  Geometry::VerticalLine::contains "bool Geometry::VerticalLine::contains(const Bin1D &binx, const Bin1D &biny) const

Returns true if the line crosses the area defined by two given bins. 
";

%feature("docstring")  Geometry::VerticalLine::getXpos "double Geometry::VerticalLine::getXpos() const 
";


// File: classWavevectorInfo.xml
%feature("docstring") WavevectorInfo "

Holds all wavevector information relevant for calculating form factors.

C++ includes: WavevectorInfo.h
";

%feature("docstring")  WavevectorInfo::WavevectorInfo "WavevectorInfo::WavevectorInfo()
";

%feature("docstring")  WavevectorInfo::WavevectorInfo "WavevectorInfo::WavevectorInfo(cvector_t ki, cvector_t kf, double wavelength)
";

%feature("docstring")  WavevectorInfo::getKi "cvector_t WavevectorInfo::getKi() const 
";

%feature("docstring")  WavevectorInfo::getKf "cvector_t WavevectorInfo::getKf() const 
";

%feature("docstring")  WavevectorInfo::getQ "cvector_t WavevectorInfo::getQ() const 
";

%feature("docstring")  WavevectorInfo::getWavelength "double WavevectorInfo::getWavelength() const 
";


// File: classMathFunctions_1_1Convolve_1_1Workspace.xml


// File: namespace_0D300.xml


// File: namespace_0D314.xml


// File: namespace_0D320.xml


// File: namespace_0D344.xml


// File: namespace_0D358.xml


// File: namespace_0D95.xml


// File: namespaceboost_1_1geometry.xml


// File: namespaceBornAgain.xml
%feature("docstring")  BornAgain::GetMajorVersionNumber "int BornAgain::GetMajorVersionNumber()
";

%feature("docstring")  BornAgain::GetMinorVersionNumber "int BornAgain::GetMinorVersionNumber()
";

%feature("docstring")  BornAgain::GetPatchVersionNumber "int BornAgain::GetPatchVersionNumber()
";

%feature("docstring")  BornAgain::GetName "std::string BornAgain::GetName()
";

%feature("docstring")  BornAgain::GetVersionNumber "std::string BornAgain::GetVersionNumber()
";


// File: namespaceExceptions.xml
%feature("docstring")  Exceptions::LogExceptionMessage "void Exceptions::LogExceptionMessage(const std::string &message)
";


// File: namespaceFormFactorTools.xml
%feature("docstring")  FormFactorTools::createDWBAScalarFormFactor "IFormFactor * FormFactorTools::createDWBAScalarFormFactor(const IFormFactor &form_factor)

Decorates the given formfactor with a scalar dwba formfactor and returns this form factor 
";

%feature("docstring")  FormFactorTools::createDWBAMatrixFormFactor "IFormFactor * FormFactorTools::createDWBAMatrixFormFactor(const IFormFactor &form_factor)

Decorates the given formfactor with a matrix dwba formfactor and returns this form factor 
";


// File: namespaceGeometry.xml
%feature("docstring")  Geometry::toComplexVector "BA_CORE_API_ BasicVector3D< std::complex< double > > Geometry::toComplexVector(const BasicVector3D< double > &real_vector)

Todo
Replace by member function complex() 
";

%feature("docstring")  Geometry::vecOfLambdaAlphaPhi "BA_CORE_API_ BasicVector3D< double > Geometry::vecOfLambdaAlphaPhi(const double _lambda, const double _alpha, const double _phi)

Creates a vector<double> as a wavevector with given wavelength and angles. Specifically needed for grazing-incidence scattering. 
";


// File: namespaceMaterials.xml
%feature("docstring")  Materials::createInvertedMaterial "IMaterial * Materials::createInvertedMaterial(const IMaterial *material)
";


// File: namespaceMathFunctions.xml
%feature("docstring")  MathFunctions::Bessel_J0_PowSer "complex_t MathFunctions::Bessel_J0_PowSer(const complex_t z)

Computes complex Bessel function J0(z), using power series and asymptotic expansion.

Computes the complex Bessel function J0(z), using standard power series and asymptotic expansion.

Forked from unoptimized code at http://www.crbond.com/math.htm, who refers to \"Computation of Special Functions\", Zhang and Jin, John Wiley and Sons, 1996. 
";

%feature("docstring")  MathFunctions::Bessel_J1_PowSer "complex_t MathFunctions::Bessel_J1_PowSer(const complex_t z)

Computes complex Bessel function J0(z), using power series and asymptotic expansion.

Computes the complex Bessel function J1(z), using standard power series and asymptotic expansion.

Forked from same source as for Bessel_J0_PowSer 
";

%feature("docstring")  MathFunctions::StandardNormal "double MathFunctions::StandardNormal(double x)
";

%feature("docstring")  MathFunctions::Gaussian "double MathFunctions::Gaussian(double x, double average, double std_dev)
";

%feature("docstring")  MathFunctions::IntegratedGaussian "double MathFunctions::IntegratedGaussian(double x, double average, double std_dev)
";

%feature("docstring")  MathFunctions::Si "double MathFunctions::Si(double x)

Sine integral function:  $Si(x)\\\\equiv\\\\int_0^x du \\\\sin(u)/u$. 
";

%feature("docstring")  MathFunctions::sinc "double MathFunctions::sinc(double x)

sinc function:  $sinc(x)\\\\equiv\\\\sin(x)/x$
";

%feature("docstring")  MathFunctions::sinc "complex_t MathFunctions::sinc(const complex_t z)

Complex sinc function:  $sinc(x)\\\\equiv\\\\sin(x)/x$. 
";

%feature("docstring")  MathFunctions::tanhc "complex_t MathFunctions::tanhc(const complex_t z)

Complex tanhc function:  $tanhc(x)\\\\equiv\\\\tanh(x)/x$. 
";

%feature("docstring")  MathFunctions::Laue "complex_t MathFunctions::Laue(const complex_t z, size_t N)
";

%feature("docstring")  MathFunctions::Bessel_J0 "double MathFunctions::Bessel_J0(double x)

Bessel function of the first kind and order 0. 
";

%feature("docstring")  MathFunctions::Bessel_J1 "double MathFunctions::Bessel_J1(double x)

Bessel function of the first kind and order 1. 
";

%feature("docstring")  MathFunctions::Bessel_J1c "double MathFunctions::Bessel_J1c(double x)

Bessel function Bessel_J1(x)/x. 
";

%feature("docstring")  MathFunctions::Bessel_J0 "complex_t MathFunctions::Bessel_J0(const complex_t z)

Complex Bessel function of the first kind and order 0. 
";

%feature("docstring")  MathFunctions::Bessel_J1 "complex_t MathFunctions::Bessel_J1(const complex_t z)

Complex Bessel function of the first kind and order 1. 
";

%feature("docstring")  MathFunctions::Bessel_J1c "complex_t MathFunctions::Bessel_J1c(const complex_t z)

Complex Bessel function Bessel_J1(x)/x. 
";

%feature("docstring")  MathFunctions::FastFourierTransform "std::vector< complex_t > MathFunctions::FastFourierTransform(const std::vector< complex_t > &data, EFFTDirection tcase)

simple (and unoptimized) wrapper function for the discrete fast Fourier transformation library (fftw3) 
";

%feature("docstring")  MathFunctions::FastFourierTransform "std::vector< complex_t > MathFunctions::FastFourierTransform(const std::vector< double > &data, EFFTDirection tcase)

simple (and unoptimized) wrapper function for the discrete fast Fourier transformation library (fftw3); transforms real to complex 
";

%feature("docstring")  MathFunctions::ConvolveFFT "std::vector< complex_t > MathFunctions::ConvolveFFT(const std::vector< double > &signal, const std::vector< double > &resfunc)

convolution of two real vectors of equal size 
";

%feature("docstring")  MathFunctions::GenerateUniformRandom "double MathFunctions::GenerateUniformRandom()
";

%feature("docstring")  MathFunctions::GenerateStandardNormalRandom "double MathFunctions::GenerateStandardNormalRandom()
";

%feature("docstring")  MathFunctions::GenerateNormalRandom "double MathFunctions::GenerateNormalRandom(double average, double std_dev)
";

%feature("docstring")  MathFunctions::isnan "BA_CORE_API_ bool MathFunctions::isnan(double x)
";

%feature("docstring")  MathFunctions::isinf "BA_CORE_API_ bool MathFunctions::isinf(double x)
";


// File: namespaceMSG.xml
%feature("docstring")  MSG::SetLevel "BA_CORE_API_ void MSG::SetLevel(EMessageLevel level)
";

%feature("docstring")  MSG::SetLevel "BA_CORE_API_ void MSG::SetLevel(const std::string &levelname)
";


// File: namespaceNumeric.xml
%feature("docstring")  Numeric::areAlmostEqual "bool BA_CORE_API_ Numeric::areAlmostEqual(double a, double b, double tolerance_factor)

compare two doubles 
";

%feature("docstring")  Numeric::get_relative_difference "double BA_CORE_API_ Numeric::get_relative_difference(double a, double b)

calculates safe relative difference |(a-b)/b| 
";


// File: namespaceOutputDataFunctions.xml
%feature("docstring")  OutputDataFunctions::doubleBinSize "OutputData< double > * OutputDataFunctions::doubleBinSize(const OutputData< double > &source)

double the bin size for each dimension

double the bin size for each dimension. 
";

%feature("docstring")  OutputDataFunctions::FourierTransform "void OutputDataFunctions::FourierTransform(const OutputData< double > &source, OutputData< complex_t > *p_destination)

unnormalized Fourier transformation for real data

Fourier transformation of output data. 
";

%feature("docstring")  OutputDataFunctions::FourierTransformR "void OutputDataFunctions::FourierTransformR(const OutputData< complex_t > &source, OutputData< double > *p_destination)

unnormalized reverse Fourier transformation for real data

Fourier back transform. 
";

%feature("docstring")  OutputDataFunctions::getRealPart "OutputData< double > * OutputDataFunctions::getRealPart(const OutputData< complex_t > &source)

reduces the data to the element-wise real, imaginary or modulus part 
";

%feature("docstring")  OutputDataFunctions::getImagPart "OutputData< double > * OutputDataFunctions::getImagPart(const OutputData< complex_t > &source)
";

%feature("docstring")  OutputDataFunctions::getModulusPart "OutputData< double > * OutputDataFunctions::getModulusPart(const OutputData< complex_t > &source)
";

%feature("docstring")  OutputDataFunctions::getComponentData "OutputData< double > * OutputDataFunctions::getComponentData(const OutputData< Eigen::Matrix2d > &source, int row, int column)

Selects an element-wise component of the matrix-valued  OutputData structure and returns a new double-valued one 
";

%feature("docstring")  OutputDataFunctions::createFromComponents "OutputData< Eigen::Matrix2d > * OutputDataFunctions::createFromComponents(const OutputData< double > &component_00, const OutputData< double > &component_01, const OutputData< double > &component_10, const OutputData< double > &component_11)

Assembles a matrix-valued OuputData structure from its component maps 
";

%feature("docstring")  OutputDataFunctions::sliceAccrossOneAxis "OutputData< double > * OutputDataFunctions::sliceAccrossOneAxis(const OutputData< double > &data, const std::string &fixed_axis_name, double fixed_axis_value)

Slice data, having one bin on selected axis fixed. Resulting output data will have one axis less (without axis 'fixed_axis_name') 
";

%feature("docstring")  OutputDataFunctions::selectRangeOnOneAxis "OutputData< double > * OutputDataFunctions::selectRangeOnOneAxis(const OutputData< double > &data, const std::string &selected_axis_name, double axis_value1, double axis_value2)

Select range on one of the axis.

Select range on one of the axis. Resulting output data will have same number of axes

Resulting output data will have same number of axes 
";

%feature("docstring")  OutputDataFunctions::applyFunction "void OutputDataFunctions::applyFunction(OutputData< double > &data, const IIntensityFunction *func)

apply intensity function to values stored in output data 
";


// File: namespaceOutputDataIOHelper.xml
%feature("docstring")  OutputDataIOHelper::isCompressed "bool OutputDataIOHelper::isCompressed(const std::string &name)

Returns true if name contains *.gz extension. 
";

%feature("docstring")  OutputDataIOHelper::isGZipped "bool OutputDataIOHelper::isGZipped(const std::string &name)

Returns true if name contains *.gz extension.

Does name contain *.gz extension? 
";

%feature("docstring")  OutputDataIOHelper::isBZipped "bool OutputDataIOHelper::isBZipped(const std::string &name)

Returns true if name contains *.bz2 extension. 
";

%feature("docstring")  OutputDataIOHelper::GetFileMainExtension "std::string OutputDataIOHelper::GetFileMainExtension(const std::string &name)

Returns file extension after stripping '.gz' if any.

Returns file main extension (without .gz). 
";

%feature("docstring")  OutputDataIOHelper::isBinaryFile "bool OutputDataIOHelper::isBinaryFile(const std::string &file_name)

returns true if file name corresponds to a binary file 
";

%feature("docstring")  OutputDataIOHelper::isIntFile "bool OutputDataIOHelper::isIntFile(const std::string &file_name)

returns true if file name corresponds to BornAgain native format (compressed or not) 
";

%feature("docstring")  OutputDataIOHelper::isTxtFile "bool OutputDataIOHelper::isTxtFile(const std::string &file_name)

returns true if file name corresponds to simple numpy-style ASCII file 
";

%feature("docstring")  OutputDataIOHelper::isTiffFile "bool OutputDataIOHelper::isTiffFile(const std::string &file_name)

returns true if file name corresponds to tiff file (can be also compressed) 
";

%feature("docstring")  OutputDataIOHelper::isSimilarToFixedBinAxisType "bool OutputDataIOHelper::isSimilarToFixedBinAxisType(const std::string &line)

Returns true if string representation of the axis contains one of  FixedBinAxis,  ConstKBinAxis or  CustomBinAxis to parse it later in similar way. 
";

%feature("docstring")  OutputDataIOHelper::isVariableBinAxisType "bool OutputDataIOHelper::isVariableBinAxisType(const std::string &line)
";

%feature("docstring")  OutputDataIOHelper::createAxis "IAxis * OutputDataIOHelper::createAxis(std::istream &input_stream)

Creates axis of certain type from input stream. 
";

%feature("docstring")  OutputDataIOHelper::createFixedBinAxis "IAxis * OutputDataIOHelper::createFixedBinAxis(std::string line)

Create one of  FixedBinAxis from string representation  FixedBinAxis(\"axis0\", 10, -1, 1)  ConstKBinAxis(\"axis0\", 10, -1, 1)  CustomBinAxis(\"axis0\", 10, -1, 1) 
";

%feature("docstring")  OutputDataIOHelper::createVariableBinAxis "IAxis * OutputDataIOHelper::createVariableBinAxis(std::string line)

Create  VariableBinAxis from string representation  VariableBinAxis(\"axis0\", 4, [-1, -0.5, 0.5, 1, 2]) 
";

%feature("docstring")  OutputDataIOHelper::fillOutputData "void OutputDataIOHelper::fillOutputData(OutputData< double > *data, std::istream &input_stream)

Fills output data raw buffer from input stream. 
";

%feature("docstring")  OutputDataIOHelper::readLineOfDoubles "void OutputDataIOHelper::readLineOfDoubles(std::vector< double > &buffer, std::istringstream &iss)
";


// File: namespacePyGenTools.xml
%feature("docstring")  PyGenTools::genPyScript "std::string PyGenTools::genPyScript(GISASSimulation *simulation)
";

%feature("docstring")  PyGenTools::printBool "std::string PyGenTools::printBool(double value)
";

%feature("docstring")  PyGenTools::printDouble "std::string PyGenTools::printDouble(double input)
";

%feature("docstring")  PyGenTools::printNm "std::string PyGenTools::printNm(double input)
";

%feature("docstring")  PyGenTools::printScientificDouble "std::string PyGenTools::printScientificDouble(double input)
";

%feature("docstring")  PyGenTools::printDegrees "std::string PyGenTools::printDegrees(double input)
";

%feature("docstring")  PyGenTools::isSquare "bool PyGenTools::isSquare(double length1, double length2, double angle)
";

%feature("docstring")  PyGenTools::isHexagonal "bool PyGenTools::isHexagonal(double length1, double length2, double angle)
";

%feature("docstring")  PyGenTools::testPyScript "bool PyGenTools::testPyScript(GISASSimulation *simulation)
";

%feature("docstring")  PyGenTools::getRepresentation "std::string PyGenTools::getRepresentation(const IDistribution1D *distribution)
";

%feature("docstring")  PyGenTools::getRepresentation "std::string PyGenTools::getRepresentation(const std::string &indent, const Geometry::IShape2D *ishape, bool mask_value)
";

%feature("docstring")  PyGenTools::printKvector "std::string PyGenTools::printKvector(const kvector_t &value)
";

%feature("docstring")  PyGenTools::isDefaultDirection "bool PyGenTools::isDefaultDirection(const kvector_t &direction)

returns true if it is (0, -1, 0) vector 
";


// File: namespaceStandardSimulations.xml
%feature("docstring")  StandardSimulations::PolarizedDWBAMagCylinders2 "GISASSimulation * StandardSimulations::PolarizedDWBAMagCylinders2()
";

%feature("docstring")  StandardSimulations::BasicGISAS "GISASSimulation * StandardSimulations::BasicGISAS()

Basic GISAS simulation with the detector phi[0,2], theta[0,2]. 
";

%feature("docstring")  StandardSimulations::BasicGISAS00 "GISASSimulation * StandardSimulations::BasicGISAS00()

Basic GISAS for polarization studies. 
";

%feature("docstring")  StandardSimulations::MiniGISAS "GISASSimulation * StandardSimulations::MiniGISAS()

GISAS simulation with small detector and phi[-2,2], theta[0,2]. 
";

%feature("docstring")  StandardSimulations::MiniGISAS_v2 "GISASSimulation * StandardSimulations::MiniGISAS_v2()

GISAS simulation with small detector and phi[-1,1], theta[0,1]. 
";

%feature("docstring")  StandardSimulations::MiniGISASBeamDivergence "GISASSimulation * StandardSimulations::MiniGISASBeamDivergence()
";

%feature("docstring")  StandardSimulations::MiniGISASDetectorResolution "GISASSimulation * StandardSimulations::MiniGISASDetectorResolution()
";

%feature("docstring")  StandardSimulations::GISASWithMasks "GISASSimulation * StandardSimulations::GISASWithMasks()
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
";

%feature("docstring")  StandardSimulations::RectDetectorPerpToSample "GISASSimulation * StandardSimulations::RectDetectorPerpToSample()
";

%feature("docstring")  StandardSimulations::RectDetectorPerpToDirectBeam "GISASSimulation * StandardSimulations::RectDetectorPerpToDirectBeam()
";

%feature("docstring")  StandardSimulations::RectDetectorPerpToReflectedBeam "GISASSimulation * StandardSimulations::RectDetectorPerpToReflectedBeam()
";

%feature("docstring")  StandardSimulations::RectDetectorPerpToReflectedBeamDpos "GISASSimulation * StandardSimulations::RectDetectorPerpToReflectedBeamDpos()
";

%feature("docstring")  StandardSimulations::MiniGISASMonteCarlo "GISASSimulation * StandardSimulations::MiniGISASMonteCarlo()
";


// File: namespaceUnits.xml
%feature("docstring")  Units::rad2deg "double Units::rad2deg(double angle)
";

%feature("docstring")  Units::deg2rad "double Units::deg2rad(double angle)
";


// File: namespaceUtils.xml
%feature("docstring")  Utils::AdjustStringLength "std::string Utils::AdjustStringLength(std::string name, int length)
";

%feature("docstring")  Utils::EnableFloatingPointExceptions "void Utils::EnableFloatingPointExceptions()

enables exception throw in the case of NaN, Inf 
";


// File: Beam_8cpp.xml


// File: Beam_8h.xml


// File: ChiSquaredModule_8cpp.xml


// File: ChiSquaredModule_8h.xml


// File: ConvolutionDetectorResolution_8cpp.xml


// File: ConvolutionDetectorResolution_8h.xml


// File: DecoratedLayerDWBASimulation_8cpp.xml


// File: DecoratedLayerDWBASimulation_8h.xml


// File: DecouplingApproximationStrategy_8cpp.xml


// File: DecouplingApproximationStrategy_8h.xml


// File: DetectorMask_8cpp.xml


// File: DetectorMask_8h.xml


// File: DistributionHandler_8cpp.xml


// File: DistributionHandler_8h.xml


// File: Distributions_8cpp.xml


// File: Distributions_8h.xml


// File: DWBADiffuseReflection_8cpp.xml


// File: DWBADiffuseReflection_8h.xml


// File: DWBASimulation_8cpp.xml


// File: DWBASimulation_8h.xml


// File: FitElement_8cpp.xml


// File: FitElement_8h.xml


// File: FTDecayFunctions_8cpp.xml


// File: FTDecayFunctions_8h.xml


// File: FTDistributions_8cpp.xml


// File: FTDistributions_8h.xml


// File: GISASSimulation_8cpp.xml


// File: GISASSimulation_8h.xml


// File: IChiSquaredModule_8cpp.xml


// File: IChiSquaredModule_8h.xml


// File: IDetector2D_8cpp.xml


// File: IDetector2D_8h.xml


// File: IDetectorResolution_8cpp.xml


// File: IDetectorResolution_8h.xml


// File: IIntensityFunction_8h.xml


// File: IIntensityNormalizer_8cpp.xml


// File: IIntensityNormalizer_8h.xml


// File: IInterferenceFunctionStrategy_8cpp.xml


// File: IInterferenceFunctionStrategy_8h.xml


// File: ILayerRTCoefficients_8h.xml


// File: Instrument_8cpp.xml


// File: Instrument_8h.xml


// File: InterferenceFunctionStrategies_8h.xml


// File: IPixelMap_8h.xml


// File: IResolutionFunction2D_8h.xml


// File: ISampleBuilder_8h.xml


// File: IsGISAXSDetector_8cpp.xml


// File: IsGISAXSDetector_8h.xml


// File: ISimulation_8h.xml


// File: ISpecularInfoMap_8h.xml


// File: ISquaredFunction_8h.xml


// File: LayerDWBASimulation_8cpp.xml


// File: LayerDWBASimulation_8h.xml


// File: LayerSpecularInfo_8cpp.xml


// File: LayerSpecularInfo_8h.xml


// File: LayerStrategyBuilder_8cpp.xml


// File: LayerStrategyBuilder_8h.xml


// File: Mask_8cpp.xml


// File: Mask_8h.xml


// File: MaskCoordinateFunction_8cpp.xml


// File: MaskCoordinateFunction_8h.xml


// File: MatrixRTCoefficients_8cpp.xml


// File: MatrixRTCoefficients_8h.xml


// File: MatrixSpecularInfoMap_8cpp.xml


// File: MatrixSpecularInfoMap_8h.xml


// File: MultiLayerDWBASimulation_8cpp.xml


// File: MultiLayerDWBASimulation_8h.xml


// File: MultiLayerRoughnessDWBASimulation_8cpp.xml


// File: MultiLayerRoughnessDWBASimulation_8h.xml


// File: OffSpecSimulation_8cpp.xml


// File: OffSpecSimulation_8h.xml


// File: OMPISimulation_8cpp.xml


// File: OMPISimulation_8h.xml


// File: ParameterSample_8h.xml


// File: ProgressHandler_8cpp.xml


// File: ProgressHandler_8h.xml


// File: ProgressHandlerDWBA_8cpp.xml


// File: ProgressHandlerDWBA_8h.xml


// File: RectangularDetector_8cpp.xml


// File: RectangularDetector_8h.xml


// File: ResolutionFunction2DGaussian_8cpp.xml


// File: ResolutionFunction2DGaussian_8h.xml


// File: ScalarRTCoefficients_8h.xml


// File: ScalarSpecularInfoMap_8cpp.xml


// File: ScalarSpecularInfoMap_8h.xml


// File: Simulation_8cpp.xml


// File: Simulation_8h.xml


// File: SimulationElement_8cpp.xml
%feature("docstring")  AddElementsWithWeight "void AddElementsWithWeight(std::vector< SimulationElement >::const_iterator first, std::vector< SimulationElement >::const_iterator last, std::vector< SimulationElement >::iterator result, double weight)

Add element vector to element vector with weight. 
";

%feature("docstring")  setAllElementIntensities "void setAllElementIntensities(std::vector< SimulationElement >::iterator first, std::vector< SimulationElement >::iterator last, double intensity)

Set all element intensities to given value. 
";


// File: SimulationElement_8h.xml
%feature("docstring")  AddElementsWithWeight "void AddElementsWithWeight(std::vector< SimulationElement >::const_iterator first, std::vector< SimulationElement >::const_iterator last, std::vector< SimulationElement >::iterator result, double weight)

Add element vector to element vector with weight. 
";

%feature("docstring")  setAllElementIntensities "void setAllElementIntensities(std::vector< SimulationElement >::iterator first, std::vector< SimulationElement >::iterator last, double intensity)

Set all element intensities to given value. 
";


// File: SimulationOptions_8cpp.xml


// File: SimulationOptions_8h.xml


// File: SizeSpacingCorrelationApproximationStrategy_8cpp.xml


// File: SizeSpacingCorrelationApproximationStrategy_8h.xml


// File: SpecularMagnetic_8cpp.xml


// File: SpecularMagnetic_8h.xml


// File: SpecularMatrix_8cpp.xml


// File: SpecularMatrix_8h.xml


// File: SpecularSimulation_8cpp.xml


// File: SpecularSimulation_8h.xml


// File: SphericalDetector_8cpp.xml


// File: SphericalDetector_8h.xml


// File: ThreadInfo_8h.xml


// File: FormFactorAnisoPyramid_8cpp.xml


// File: FormFactorAnisoPyramid_8h.xml


// File: FormFactorBox_8cpp.xml


// File: FormFactorBox_8h.xml


// File: FormFactorCone_8cpp.xml


// File: FormFactorCone_8h.xml


// File: FormFactorCone6_8cpp.xml


// File: FormFactorCone6_8h.xml


// File: FormFactorCrystal_8cpp.xml


// File: FormFactorCrystal_8h.xml


// File: FormFactorCuboctahedron_8cpp.xml


// File: FormFactorCuboctahedron_8h.xml


// File: FormFactorCylinder_8cpp.xml


// File: FormFactorCylinder_8h.xml


// File: FormFactorDecoratorDebyeWaller_8cpp.xml


// File: FormFactorDecoratorDebyeWaller_8h.xml


// File: FormFactorDecoratorFactor_8h.xml


// File: FormFactorDecoratorMaterial_8cpp.xml


// File: FormFactorDecoratorMaterial_8h.xml


// File: FormFactorDecoratorMultiPositionFactor_8cpp.xml


// File: FormFactorDecoratorMultiPositionFactor_8h.xml


// File: FormFactorDecoratorPositionFactor_8h.xml


// File: FormFactorDecoratorRotation_8cpp.xml


// File: FormFactorDecoratorRotation_8h.xml


// File: FormFactorDodecahedron_8cpp.xml


// File: FormFactorDodecahedron_8h.xml


// File: FormFactorDWBA_8cpp.xml


// File: FormFactorDWBA_8h.xml


// File: FormFactorDWBAPol_8cpp.xml


// File: FormFactorDWBAPol_8h.xml


// File: FormFactorEllipsoidalCylinder_8cpp.xml


// File: FormFactorEllipsoidalCylinder_8h.xml


// File: FormFactorFullSphere_8cpp.xml


// File: FormFactorFullSphere_8h.xml


// File: FormFactorFullSpheroid_8cpp.xml


// File: FormFactorFullSpheroid_8h.xml


// File: FormFactorGauss_8cpp.xml


// File: FormFactorGauss_8h.xml


// File: FormFactorHemiEllipsoid_8cpp.xml


// File: FormFactorHemiEllipsoid_8h.xml


// File: FormFactorIcosahedron_8cpp.xml


// File: FormFactorIcosahedron_8h.xml


// File: FormFactorLongBoxGauss_8cpp.xml


// File: FormFactorLongBoxGauss_8h.xml


// File: FormFactorLongBoxLorentz_8cpp.xml


// File: FormFactorLongBoxLorentz_8h.xml


// File: FormFactorLongRipple1Gauss_8cpp.xml


// File: FormFactorLongRipple1Gauss_8h.xml


// File: FormFactorLongRipple1Lorentz_8cpp.xml


// File: FormFactorLongRipple1Lorentz_8h.xml


// File: FormFactorLongRipple2Gauss_8cpp.xml


// File: FormFactorLongRipple2Gauss_8h.xml


// File: FormFactorLongRipple2Lorentz_8cpp.xml


// File: FormFactorLongRipple2Lorentz_8h.xml


// File: FormFactorLorentz_8cpp.xml


// File: FormFactorLorentz_8h.xml


// File: FormFactorPolyhedron_8cpp.xml
%feature("docstring")  I "static complex_t I(0., 1.)
";

%feature("docstring")  eps "static double eps(2e-16)
";


// File: FormFactorPolyhedron_8h.xml


// File: FormFactorPrism3_8cpp.xml


// File: FormFactorPrism3_8h.xml


// File: FormFactorPrism6_8cpp.xml


// File: FormFactorPrism6_8h.xml


// File: FormFactorPyramid_8cpp.xml


// File: FormFactorPyramid_8h.xml


// File: FormFactorRipple1_8cpp.xml


// File: FormFactorRipple1_8h.xml


// File: FormFactorRipple2_8cpp.xml


// File: FormFactorRipple2_8h.xml


// File: FormFactors_8h.xml


// File: FormFactorSphereGaussianRadius_8cpp.xml


// File: FormFactorSphereGaussianRadius_8h.xml


// File: FormFactorSphereLogNormalRadius_8cpp.xml


// File: FormFactorSphereLogNormalRadius_8h.xml


// File: FormFactorSphereUniformRadius_8cpp.xml


// File: FormFactorSphereUniformRadius_8h.xml


// File: FormFactorTetrahedron_8cpp.xml


// File: FormFactorTetrahedron_8h.xml


// File: FormFactorTools_8cpp.xml


// File: FormFactorTools_8h.xml


// File: FormFactorTrivial_8cpp.xml


// File: FormFactorTrivial_8h.xml


// File: FormFactorTruncatedCube_8cpp.xml


// File: FormFactorTruncatedCube_8h.xml


// File: FormFactorTruncatedSphere_8cpp.xml


// File: FormFactorTruncatedSphere_8h.xml


// File: FormFactorTruncatedSpheroid_8cpp.xml


// File: FormFactorTruncatedSpheroid_8h.xml


// File: FormFactorWeighted_8cpp.xml


// File: FormFactorWeighted_8h.xml


// File: IFormFactor_8h.xml


// File: IFormFactorBorn_8cpp.xml


// File: IFormFactorBorn_8h.xml


// File: IFormFactorDecorator_8h.xml


// File: WavevectorInfo_8h.xml


// File: BasicVector3D_8cpp.xml


// File: BasicVector3D_8h.xml


// File: Ellipse_8cpp.xml


// File: Ellipse_8h.xml


// File: InfinitePlane_8cpp.xml


// File: InfinitePlane_8h.xml


// File: IShape2D_8h.xml


// File: Line_8cpp.xml


// File: Line_8h.xml


// File: Polygon_8cpp.xml


// File: Polygon_8h.xml


// File: Rectangle_8cpp.xml


// File: Rectangle_8h.xml


// File: Transform3D_8cpp.xml


// File: Transform3D_8h.xml


// File: Vectors3D_8h.xml


// File: boost__streams_8h.xml


// File: IntensityDataIOFactory_8cpp.xml


// File: IntensityDataIOFactory_8h.xml


// File: OutputDataIOHelper_8cpp.xml


// File: OutputDataIOHelper_8h.xml


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
%feature("docstring")  IgnoreDenormalized "double IgnoreDenormalized(double value)
";

%feature("docstring")  WriteOutputDataDoubles "void WriteOutputDataDoubles(const OutputData< double > &data, std::ostream &output_stream, size_t n_columns)
";


// File: OutputDataWriteStrategy_8h.xml


// File: TiffHandler_8cpp.xml


// File: TiffHandler_8h.xml


// File: BAVersion_8h.xml


// File: Crystal_8cpp.xml


// File: Crystal_8h.xml


// File: HomogeneousMagneticMaterial_8cpp.xml


// File: HomogeneousMagneticMaterial_8h.xml


// File: HomogeneousMaterial_8h.xml


// File: IClusteredParticles_8h.xml


// File: ICompositeSample_8cpp.xml


// File: ICompositeSample_8h.xml


// File: IInterferenceFunction_8h.xml


// File: ILayout_8h.xml


// File: IMaterial_8cpp.xml


// File: IMaterial_8h.xml


// File: InterferenceFunction1DLattice_8cpp.xml


// File: InterferenceFunction1DLattice_8h.xml


// File: InterferenceFunction2DLattice_8cpp.xml


// File: InterferenceFunction2DLattice_8h.xml


// File: InterferenceFunction2DParaCrystal_8cpp.xml


// File: InterferenceFunction2DParaCrystal_8h.xml


// File: InterferenceFunctionNone_8cpp.xml


// File: InterferenceFunctionNone_8h.xml


// File: InterferenceFunctionRadialParaCrystal_8cpp.xml


// File: InterferenceFunctionRadialParaCrystal_8h.xml


// File: InterferenceFunctions_8h.xml


// File: IParticle_8cpp.xml


// File: IParticle_8h.xml


// File: IRoughness_8h.xml


// File: ISample_8cpp.xml


// File: ISample_8h.xml


// File: ISampleIteratorStrategy_8cpp.xml


// File: ISampleIteratorStrategy_8h.xml


// File: ISampleVisitor_8cpp.xml
%feature("docstring")  VisitSampleTreePreorder "void VisitSampleTreePreorder(const ISample &sample, ISampleVisitor &visitor)
";

%feature("docstring")  VisitSampleTreePostorder "void VisitSampleTreePostorder(const ISample &sample, ISampleVisitor &visitor)
";


// File: ISampleVisitor_8h.xml
%feature("docstring")  VisitSampleTreePreorder "BA_CORE_API_ void VisitSampleTreePreorder(const ISample &sample, ISampleVisitor &visitor)
";

%feature("docstring")  VisitSampleTreePostorder "BA_CORE_API_ void VisitSampleTreePostorder(const ISample &sample, ISampleVisitor &visitor)
";


// File: ISelectionRule_8h.xml


// File: Lattice_8cpp.xml


// File: Lattice_8h.xml


// File: Lattice1DParameters_8h.xml


// File: Lattice2DParameters_8h.xml
%feature("docstring")  getUnitCellArea "double getUnitCellArea(const Lattice2DParameters &lattice_params)
";


// File: Layer_8cpp.xml


// File: Layer_8h.xml


// File: LayerInterface_8cpp.xml


// File: LayerInterface_8h.xml


// File: LayerRoughness_8cpp.xml


// File: LayerRoughness_8h.xml


// File: Materials_8cpp.xml


// File: Materials_8h.xml


// File: MesoCrystal_8cpp.xml


// File: MesoCrystal_8h.xml


// File: MultiLayer_8cpp.xml


// File: MultiLayer_8h.xml


// File: Particle_8cpp.xml


// File: Particle_8h.xml


// File: ParticleComposition_8cpp.xml


// File: ParticleComposition_8h.xml


// File: ParticleCoreShell_8cpp.xml


// File: ParticleCoreShell_8h.xml


// File: ParticleDistribution_8cpp.xml


// File: ParticleDistribution_8h.xml


// File: ParticleLayout_8cpp.xml


// File: ParticleLayout_8h.xml


// File: Rotations_8cpp.xml
%feature("docstring")  CreateProduct "IRotation* CreateProduct(const IRotation &left, const IRotation &right)
";


// File: Rotations_8h.xml
%feature("docstring")  CreateProduct "BA_CORE_API_ IRotation* CreateProduct(const IRotation &left, const IRotation &right)
";


// File: Samples_8h.xml


// File: SampleTreeIterator_8cpp.xml


// File: SampleTreeIterator_8h.xml


// File: BoxCompositionBuilder_8cpp.xml


// File: BoxCompositionBuilder_8h.xml


// File: core__functional__tests_8cpp.xml
%feature("docstring")  CORE_FUNCTIONAL_TEST "int CORE_FUNCTIONAL_TEST(const std::string &test_name)

run core functional tests with given name

Runs a functional test and returns error code. Note the analogy with PYSCRIPT_FUNCTIONAL_TEST and GUI_FUNCTIONAL_TEST. 
";


// File: core__functional__tests_8h.xml
%feature("docstring")  CORE_FUNCTIONAL_TEST "BA_CORE_API_ int CORE_FUNCTIONAL_TEST(const std::string &test_name)

run core functional tests with given name

Runs a functional test and returns error code. Note the analogy with PYSCRIPT_FUNCTIONAL_TEST and GUI_FUNCTIONAL_TEST. 
";


// File: CoreFunctionalTest_8cpp.xml


// File: CoreFunctionalTest_8h.xml


// File: CoreFunctionalTestComponentService_8cpp.xml


// File: CoreFunctionalTestComponentService_8h.xml


// File: CoreShellParticleBuilder_8cpp.xml


// File: CoreShellParticleBuilder_8h.xml


// File: CustomMorphologyBuilder_8cpp.xml


// File: CustomMorphologyBuilder_8h.xml


// File: CylindersAndPrismsBuilder_8cpp.xml


// File: CylindersAndPrismsBuilder_8h.xml


// File: CylindersBuilder_8cpp.xml


// File: CylindersBuilder_8h.xml


// File: FunctionalMultiTest_8cpp.xml


// File: FunctionalMultiTest_8h.xml


// File: FunctionalTestComponentService_8cpp.xml


// File: FunctionalTestComponentService_8h.xml


// File: FunctionalTestInfo_8cpp.xml


// File: FunctionalTestInfo_8h.xml


// File: FunctionalTestRegistry_8cpp.xml


// File: FunctionalTestRegistry_8h.xml


// File: IFunctionalTest_8cpp.xml


// File: IFunctionalTest_8h.xml


// File: LatticeBuilder_8cpp.xml


// File: LatticeBuilder_8h.xml


// File: LayersWithAbsorptionBuilder_8cpp.xml


// File: LayersWithAbsorptionBuilder_8h.xml


// File: MagneticParticlesBuilder_8cpp.xml


// File: MagneticParticlesBuilder_8h.xml


// File: MesoCrystalBuilder_8cpp.xml


// File: MesoCrystalBuilder_8h.xml


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


// File: ParticleInTheAirBuilder_8cpp.xml


// File: ParticleInTheAirBuilder_8h.xml


// File: pyscript__functional__tests_8cpp.xml
%feature("docstring")  PYSCRIPT_FUNCTIONAL_TEST "int PYSCRIPT_FUNCTIONAL_TEST(const std::string &test_name)

run pyscript functional tests with given name

Runs a functional test and returns error code. Note the analogy with CORE_FUNCTIONAL_TEST. 
";


// File: pyscript__functional__tests_8h.xml
%feature("docstring")  PYSCRIPT_FUNCTIONAL_TEST "BA_CORE_API_ int PYSCRIPT_FUNCTIONAL_TEST(const std::string &test_name)

run pyscript functional tests with given name

Runs a functional test and returns error code. Note the analogy with CORE_FUNCTIONAL_TEST. 
";


// File: PyScriptFunctionalTest_8cpp.xml


// File: PyScriptFunctionalTest_8h.xml


// File: PyScriptFunctionalTestComponentService_8cpp.xml


// File: PyScriptFunctionalTestComponentService_8h.xml


// File: RipplesBuilder_8cpp.xml


// File: RipplesBuilder_8h.xml


// File: RotatedPyramidsBuilder_8cpp.xml


// File: RotatedPyramidsBuilder_8h.xml


// File: SampleBuilderFactory_8cpp.xml


// File: SampleBuilderFactory_8h.xml


// File: SimulationRegistry_8cpp.xml


// File: SimulationRegistry_8h.xml


// File: SizeDistributionModelsBuilder_8cpp.xml


// File: SizeDistributionModelsBuilder_8h.xml


// File: StandardSimulations_8cpp.xml


// File: StandardSimulations_8h.xml


// File: TestComponentsRegistry_8cpp.xml


// File: TestComponentsRegistry_8h.xml


// File: TransformationsBuilder_8cpp.xml


// File: TransformationsBuilder_8h.xml


// File: TwoDimLatticeBuilder_8cpp.xml


// File: TwoDimLatticeBuilder_8h.xml


// File: AttLimits_8h.xml


// File: Bin_8h.xml


// File: BornAgainNamespace_8h.xml


// File: ConstKBinAxis_8cpp.xml


// File: ConstKBinAxis_8h.xml


// File: Convolve_8cpp.xml


// File: Convolve_8h.xml


// File: CoreOptionsDescription_8cpp.xml
%feature("docstring")  AddCoreOptions "void AddCoreOptions(ProgramOptions *p_options)

Adds command line and config file options. 
";


// File: CoreOptionsDescription_8h.xml
%feature("docstring")  AddCoreOptions "void BA_CORE_API_ AddCoreOptions(ProgramOptions *p_options)

Adds command line and config file options. 
";


// File: CumulativeValue_8h.xml


// File: CustomBinAxis_8cpp.xml


// File: CustomBinAxis_8h.xml


// File: EigenCore_8h.xml


// File: Exceptions_8cpp.xml


// File: Exceptions_8h.xml


// File: FastVector_8h.xml


// File: FileSystem_8cpp.xml


// File: FileSystem_8h.xml


// File: FixedBinAxis_8cpp.xml


// File: FixedBinAxis_8h.xml


// File: fp__exception__glibc__extension_8h.xml
%feature("docstring")  fegetexcept "int fegetexcept(void)

License: Public Domain 
David N. Williams 
";

%feature("docstring")  feenableexcept "int feenableexcept(unsigned int excepts)
";

%feature("docstring")  fedisableexcept "int fedisableexcept(unsigned int excepts)
";

%feature("docstring")  fhdl "void fhdl(int sig, siginfo_t *sip, ucontext_t *scp)
";


// File: Histogram1D_8cpp.xml


// File: Histogram1D_8h.xml


// File: Histogram2D_8cpp.xml


// File: Histogram2D_8h.xml


// File: IAxis_8h.xml
%feature("docstring")  HaveSameNameAndShape "bool HaveSameNameAndShape(const IAxis &left, const IAxis &right)

global helper function for comparison of axes 
";


// File: ICloneable_8h.xml


// File: ICloneableRegistry_8h.xml


// File: IComponentService_8h.xml


// File: IFactory_8cpp.xml


// File: IFactory_8h.xml
%feature("docstring")  IFactoryCreateFunction "Base* IFactoryCreateFunction()

creation function 
";


// File: IHistogram_8cpp.xml


// File: IHistogram_8h.xml


// File: INamed_8cpp.xml


// File: INamed_8h.xml


// File: IntegratorComplex_8h.xml
%feature("docstring")  make_integrator_complex "P_integrator_complex<T> make_integrator_complex(const T *object, complex_integrand< T > mem_function)
";


// File: IntegratorMCMiser_8h.xml
%feature("docstring")  make_integrator_miser "P_integrator_miser<T> make_integrator_miser(const T *object, miser_integrand< T > mem_function, size_t dim)
";


// File: IntegratorReal_8h.xml
%feature("docstring")  make_integrator_real "P_integrator_real<T> make_integrator_real(const T *object, real_integrand< T > mem_function)
";


// File: IntensityDataFunctions_8cpp.xml


// File: IntensityDataFunctions_8h.xml


// File: IObserver_8cpp.xml


// File: IObserver_8h.xml


// File: IParameterized_8cpp.xml


// File: IParameterized_8h.xml


// File: IShareable_8h.xml


// File: ISingleton_8h.xml


// File: LLData_8cpp.xml


// File: LLData_8h.xml
%feature("docstring")  HaveSameDimensions "bool HaveSameDimensions(const LLData< T > &left, const LLData< T > &right)
";


// File: Macros_8h.xml


// File: MathFunctions_8cpp.xml


// File: MathFunctions_8h.xml


// File: MessageService_8cpp.xml


// File: MessageService_8h.xml


// File: Numeric_8cpp.xml


// File: Numeric_8h.xml


// File: OutputData_8cpp.xml


// File: OutputData_8h.xml


// File: OutputDataFunctions_8cpp.xml
%feature("docstring")  toFftw3Array "void toFftw3Array(complex_t *source, size_t length, fftw_complex *destination)
";

%feature("docstring")  fromFftw3Array "void fromFftw3Array(fftw_complex *source, size_t length, complex_t *destination)
";


// File: OutputDataFunctions_8h.xml


// File: OutputDataIterator_8h.xml


// File: ParameterDistribution_8cpp.xml


// File: ParameterDistribution_8h.xml


// File: ParameterPool_8cpp.xml


// File: ParameterPool_8h.xml


// File: Precomputed_8cpp.xml


// File: Precomputed_8h.xml


// File: ProgramOptions_8cpp.xml


// File: ProgramOptions_8h.xml
%feature("docstring")  GCC_DIAG_OFF "GCC_DIAG_OFF(unused-parameter)
";

%feature("docstring")  GCC_DIAG_ON "GCC_DIAG_ON(unused-parameter)
";


// File: PyGenTools_8cpp.xml


// File: PyGenTools_8h.xml


// File: PyGenVisitor_8cpp.xml


// File: PyGenVisitor_8h.xml


// File: RealParameterWrapper_8cpp.xml


// File: RealParameterWrapper_8h.xml


// File: SafePointerVector_8h.xml


// File: SampleLabelHandler_8cpp.xml


// File: SampleLabelHandler_8h.xml


// File: SampleMaterialVisitor_8cpp.xml


// File: SampleMaterialVisitor_8h.xml


// File: SamplePrintVisitor_8cpp.xml


// File: SamplePrintVisitor_8h.xml


// File: TRange_8h.xml


// File: Types_8h.xml


// File: Units_8h.xml


// File: Utils_8cpp.xml


// File: Utils_8h.xml


// File: VariableBinAxis_8cpp.xml


// File: VariableBinAxis_8h.xml


// File: w32pragma_8h.xml


// File: WinDllMacros_8h.xml


// File: todo.xml


// File: dir_71ac7d288b31ea5199cbab5049eb200a.xml


// File: dir_d0c8f8fb9032c27878972645c4679f14.xml


// File: dir_c83916cd1ff49c9e86c8a91c5655951d.xml


// File: dir_a9c786a61b4a710816d2413b8525d71a.xml


// File: dir_0dfb301c6da10da77ed3e615fec89a12.xml


// File: dir_e8bc32d0cf85ef86a42504cd31af1370.xml


// File: dir_5bdd7468584af37b90b299acfd1751f3.xml


// File: dir_44b1a8f39c14c02f6e3c2be419aa97b0.xml


// File: dir_1a0696269c107461a4ce8ff1a48cd2f2.xml

