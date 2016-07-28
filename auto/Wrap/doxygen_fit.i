
// File: index.xml

// File: classMinimizerLibrary_1_1AlgorithmInfo.xml
%feature("docstring") MinimizerLibrary::AlgorithmInfo "

Provides description of minimization algorithm.

C++ includes: MinimizerLibrary.h
";

%feature("docstring")  MinimizerLibrary::AlgorithmInfo::AlgorithmInfo "MinimizerLibrary::AlgorithmInfo::AlgorithmInfo()
";

%feature("docstring")  MinimizerLibrary::AlgorithmInfo::AlgorithmInfo "AlgorithmInfo::AlgorithmInfo(const std::string &algType, const std::string &algDescription)
";


// File: classAttLimits.xml
%feature("docstring") AttLimits "

Attributes and limits for a fit parameter. Currently, the only attribute is fixed/free.

C++ includes: AttLimits.h
";

%feature("docstring")  AttLimits::AttLimits "AttLimits::AttLimits()
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


// File: classMinimizerLibrary_1_1Catalogue.xml
%feature("docstring") MinimizerLibrary::Catalogue "";

%feature("docstring")  MinimizerLibrary::Catalogue::Catalogue "Catalogue::Catalogue()

Catalogue constructor fills in all information related to available minimizers/algorithms. 
";

%feature("docstring")  MinimizerLibrary::Catalogue::addMinimizer "void Catalogue::addMinimizer(const MinimizerInfo &minimizer)

Adds minimizer info to the catalogue. 
";

%feature("docstring")  MinimizerLibrary::Catalogue::algorithmTypes "std::list< std::string > Catalogue::algorithmTypes(const std::string &minimizerType)

Returns list of algorithm types for given minimizer type. 
";

%feature("docstring")  MinimizerLibrary::Catalogue::algorithmDescriptions "std::list< std::string > Catalogue::algorithmDescriptions(const std::string &minimizerType)

Returns list of algorithm descriptions for given minimizer type. 
";


// File: classExceptions_1_1ClassInitializationException.xml
%feature("docstring") Exceptions::ClassInitializationException "";

%feature("docstring")  Exceptions::ClassInitializationException::ClassInitializationException "Exceptions::ClassInitializationException::ClassInitializationException(const std::string &message)
";


// File: classExceptions_1_1DeadReferenceException.xml
%feature("docstring") Exceptions::DeadReferenceException "";

%feature("docstring")  Exceptions::DeadReferenceException::DeadReferenceException "Exceptions::DeadReferenceException::DeadReferenceException(const std::string &message)
";


// File: classExceptions_1_1DivisionByZeroException.xml
%feature("docstring") Exceptions::DivisionByZeroException "";

%feature("docstring")  Exceptions::DivisionByZeroException::DivisionByZeroException "Exceptions::DivisionByZeroException::DivisionByZeroException(const std::string &message)
";


// File: classExceptions_1_1DomainErrorException.xml
%feature("docstring") Exceptions::DomainErrorException "";

%feature("docstring")  Exceptions::DomainErrorException::DomainErrorException "Exceptions::DomainErrorException::DomainErrorException(const std::string &message)
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


// File: classFitParameter.xml
%feature("docstring") FitParameter "

Parameter with value, error and limits for fitting routines.

C++ includes: FitParameter.h
";

%feature("docstring")  FitParameter::FitParameter "FitParameter::FitParameter()
";

%feature("docstring")  FitParameter::FitParameter "FitParameter::FitParameter(const std::string &name, double value, double step=0.0, const AttLimits &limits=AttLimits::limitless(), double error=0.0)
";

%feature("docstring")  FitParameter::~FitParameter "virtual FitParameter::~FitParameter()
";

%feature("docstring")  FitParameter::setValue "virtual void FitParameter::setValue(double value)

Sets value of parameter. 
";

%feature("docstring")  FitParameter::getValue "virtual double FitParameter::getValue() const

Returns value of parameter. 
";

%feature("docstring")  FitParameter::setStep "virtual void FitParameter::setStep(double value)

Sets parameter step for minimizer. 
";

%feature("docstring")  FitParameter::getStep "virtual double FitParameter::getStep() const

Returns parameter step for minimizer. 
";

%feature("docstring")  FitParameter::setError "virtual void FitParameter::setError(double value)

Sets parameter error. 
";

%feature("docstring")  FitParameter::getError "virtual double FitParameter::getError() const

Returns parameter step for minimizer. 
";


// File: classFitParameterLinked.xml
%feature("docstring") FitParameterLinked "

Provide simultaneous access for several real parameters from parameter pool.

C++ includes: FitParameterLinked.h
";

%feature("docstring")  FitParameterLinked::FitParameterLinked "FitParameterLinked::FitParameterLinked()
";

%feature("docstring")  FitParameterLinked::FitParameterLinked "FitParameterLinked::FitParameterLinked(const std::string &name, double value, double step, const AttLimits &attlim=AttLimits::limitless(), double error=0.0)
";

%feature("docstring")  FitParameterLinked::FitParameterLinked "FitParameterLinked::FitParameterLinked(const FitParameterLinked &)=delete
";

%feature("docstring")  FitParameterLinked::~FitParameterLinked "FitParameterLinked::~FitParameterLinked()
";

%feature("docstring")  FitParameterLinked::setValue "void FitParameterLinked::setValue(double value)

Sets given value for all bound parameters. 
";

%feature("docstring")  FitParameterLinked::addParameter "void FitParameterLinked::addParameter(RealParameter *par)

Adds real parameter to the collection. 
";

%feature("docstring")  FitParameterLinked::addMatchedParametersFromPool "void FitParameterLinked::addMatchedParametersFromPool(const ParameterPool *pool, const std::string &wildcard=std::string())

Adds parameters from pool which match given wildcard. 
";


// File: classFitSuiteParameters.xml
%feature("docstring") FitSuiteParameters "

Holds vector of parameters for FitSuite.

C++ includes: FitSuiteParameters.h
";

%feature("docstring")  FitSuiteParameters::FitSuiteParameters "FitSuiteParameters::FitSuiteParameters()
";

%feature("docstring")  FitSuiteParameters::~FitSuiteParameters "FitSuiteParameters::~FitSuiteParameters()
";

%feature("docstring")  FitSuiteParameters::clear "void FitSuiteParameters::clear()

Clears all defined parameters. 
";

%feature("docstring")  FitSuiteParameters::addParameter "void FitSuiteParameters::addParameter(const std::string &name, double value, double step, const AttLimits &attlim, double error=0.0)

Adds fit parameter. 
";

%feature("docstring")  FitSuiteParameters::getFitParameter "const FitParameter * FitSuiteParameters::getFitParameter(const std::string &name) const

Returns fit parameter with given name. 
";

%feature("docstring")  FitSuiteParameters::getFitParameter "FitParameter * FitSuiteParameters::getFitParameter(const std::string &name)
";

%feature("docstring")  FitSuiteParameters::setValues "void FitSuiteParameters::setValues(const double *pars_values)

Sets values for all defined parameters. 
";

%feature("docstring")  FitSuiteParameters::setValues "void FitSuiteParameters::setValues(const std::vector< double > &pars_values)
";

%feature("docstring")  FitSuiteParameters::getValues "std::vector< double > FitSuiteParameters::getValues() const

Returns values of all defined parameters. 
";

%feature("docstring")  FitSuiteParameters::setErrors "void FitSuiteParameters::setErrors(const std::vector< double > &pars_errors)

Sets errors to all parameters. 
";

%feature("docstring")  FitSuiteParameters::getErrors "std::vector< double > FitSuiteParameters::getErrors() const

Returns errors of all defined parameters. 
";

%feature("docstring")  FitSuiteParameters::size "size_t FitSuiteParameters::size() const

Returns number of parameters. 
";

%feature("docstring")  FitSuiteParameters::push_back "void FitSuiteParameters::push_back(FitParameter *par)

Adds given  FitParameter to container. 
";

%feature("docstring")  FitSuiteParameters::begin "iterator FitSuiteParameters::begin()

Returns begin of container. 
";

%feature("docstring")  FitSuiteParameters::begin "const_iterator FitSuiteParameters::begin() const 
";

%feature("docstring")  FitSuiteParameters::end "iterator FitSuiteParameters::end()

Returns end of container. 
";

%feature("docstring")  FitSuiteParameters::end "const_iterator FitSuiteParameters::end() const 
";

%feature("docstring")  FitSuiteParameters::link_to_pool "void FitSuiteParameters::link_to_pool(const ParameterPool *pool)

Links fit parameters with pool parameters.

linking fit parameters with pool parameters 
";

%feature("docstring")  FitSuiteParameters::getNfreeParameters "size_t FitSuiteParameters::getNfreeParameters() const

Returns number of free parameters. 
";

%feature("docstring")  FitSuiteParameters::valuesAreDifferent "bool FitSuiteParameters::valuesAreDifferent(const double *pars_valuers, double tolerance_factor=1.0) const

Returns true if parameters already have the given values. 
";

%feature("docstring")  FitSuiteParameters::printParameters "void FitSuiteParameters::printParameters() const

Print defined parameters. 
";

%feature("docstring")  FitSuiteParameters::fixAll "void FitSuiteParameters::fixAll()

Fix all parameters. 
";

%feature("docstring")  FitSuiteParameters::releaseAll "void FitSuiteParameters::releaseAll()

Release all parameters. 
";

%feature("docstring")  FitSuiteParameters::setParametersFixed "void FitSuiteParameters::setParametersFixed(const std::vector< std::string > &pars, bool is_fixed)

Set fixed flag for parameters from the list. 
";


// File: classExceptions_1_1FormatErrorException.xml
%feature("docstring") Exceptions::FormatErrorException "";

%feature("docstring")  Exceptions::FormatErrorException::FormatErrorException "Exceptions::FormatErrorException::FormatErrorException(const std::string &message)
";


// File: classIMinimizer.xml
%feature("docstring") IMinimizer "

Common interface for all kind minimizer's.

C++ includes: IMinimizer.h
";

%feature("docstring")  IMinimizer::IMinimizer "IMinimizer::IMinimizer()
";

%feature("docstring")  IMinimizer::~IMinimizer "virtual IMinimizer::~IMinimizer()
";

%feature("docstring")  IMinimizer::minimize "void IMinimizer::minimize()

run minimization 
";

%feature("docstring")  IMinimizer::setParameter "void IMinimizer::setParameter(size_t index, const FitParameter *par)

Sets internal minimizer parameter. 
";

%feature("docstring")  IMinimizer::setParameters "void IMinimizer::setParameters(const FitSuiteParameters &parameters)

Sets internal minimizer parameters using external parameter list. 
";

%feature("docstring")  IMinimizer::setChiSquaredFunction "void IMinimizer::setChiSquaredFunction(function_chi2_t fun_chi2, size_t nparameters)

Sets chi squared function to minimize. 
";

%feature("docstring")  IMinimizer::setGradientFunction "void IMinimizer::setGradientFunction(function_gradient_t fun_gradient, size_t nparameters, size_t ndatasize)

Sets gradient function to minimize. 
";

%feature("docstring")  IMinimizer::getNumberOfVariables "size_t IMinimizer::getNumberOfVariables() const

Returns number of variables to fit. 
";

%feature("docstring")  IMinimizer::getMinValue "double IMinimizer::getMinValue() const

Returns minimum function value. 
";

%feature("docstring")  IMinimizer::getValueOfVariableAtMinimum "double IMinimizer::getValueOfVariableAtMinimum(size_t index) const

Returns value of the parameter at the minimum. 
";

%feature("docstring")  IMinimizer::getValueOfVariablesAtMinimum "std::vector< double > IMinimizer::getValueOfVariablesAtMinimum() const

Returns values of parameters at the minimum. 
";

%feature("docstring")  IMinimizer::getErrorOfVariable "double IMinimizer::getErrorOfVariable(size_t index) const

Returns error of variable at minimum. 
";

%feature("docstring")  IMinimizer::getErrorOfVariables "std::vector< double > IMinimizer::getErrorOfVariables() const

Returns errors of variables at minimum. 
";

%feature("docstring")  IMinimizer::clear "void IMinimizer::clear()

clear resources (parameters) for consecutives minimizations 
";

%feature("docstring")  IMinimizer::printResults "void IMinimizer::printResults() const

Prints fit results. 
";

%feature("docstring")  IMinimizer::getNCalls "size_t IMinimizer::getNCalls() const

Returns number of calls of minimized function. 
";

%feature("docstring")  IMinimizer::getOptions "MinimizerOptions * IMinimizer::getOptions()

return minimizer options 
";

%feature("docstring")  IMinimizer::getOptions "const MinimizerOptions * IMinimizer::getOptions() const 
";

%feature("docstring")  IMinimizer::setOptions "void IMinimizer::setOptions(const MinimizerOptions &options)

set minimizer options 
";

%feature("docstring")  IMinimizer::setOptionString "void IMinimizer::setOptionString(const std::string &options)

set minimizer option string 
";

%feature("docstring")  IMinimizer::isGradientBasedAgorithm "bool IMinimizer::isGradientBasedAgorithm()

Returns true if type of algorithm is Levenberg-Marquardt or similar. 
";

%feature("docstring")  IMinimizer::getMinimizerName "std::string IMinimizer::getMinimizerName() const

return name of the minimizer 
";

%feature("docstring")  IMinimizer::getAlgorithmName "std::string IMinimizer::getAlgorithmName() const

return name of the minimization algorithm 
";


// File: classMinimizerLibrary_1_1InfoItem.xml
%feature("docstring") MinimizerLibrary::InfoItem "

Simple item to hold the name and the description.

C++ includes: MinimizerLibrary.h
";

%feature("docstring")  MinimizerLibrary::InfoItem::InfoItem "MinimizerLibrary::InfoItem::InfoItem()
";

%feature("docstring")  MinimizerLibrary::InfoItem::InfoItem "MinimizerLibrary::InfoItem::InfoItem(const std::string &itemType, const std::string &itemDescription)
";

%feature("docstring")  MinimizerLibrary::InfoItem::getType "std::string MinimizerLibrary::InfoItem::getType() const 
";

%feature("docstring")  MinimizerLibrary::InfoItem::getDescription "std::string MinimizerLibrary::InfoItem::getDescription() const 
";


// File: classMSG_1_1Logger.xml
%feature("docstring") MSG::Logger "

Provides message service.

C++ includes: Logger.h
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


// File: classMinimizerCatalogue.xml
%feature("docstring") MinimizerCatalogue "

Map of minimizer names holding list of defined algorithms for every minimizer. 
";

%feature("docstring")  MinimizerCatalogue::MinimizerCatalogue "MinimizerCatalogue::MinimizerCatalogue()
";

%feature("docstring")  MinimizerCatalogue::begin "const_iterator MinimizerCatalogue::begin() const 
";

%feature("docstring")  MinimizerCatalogue::end "const_iterator MinimizerCatalogue::end() const 
";

%feature("docstring")  MinimizerCatalogue::isValid "bool MinimizerCatalogue::isValid(const std::string &minimizer, const std::string &algorithm) const 
";


// File: classMinimizerFactory.xml
%feature("docstring") MinimizerFactory "

Factory to create minimizers.

C++ includes: MinimizerFactory.h
";


// File: classMinimizerLibrary_1_1MinimizerInfo.xml
%feature("docstring") MinimizerLibrary::MinimizerInfo "

Provides info about the minimizer, including list of defined minimization algorithms.

Holds all information about available minimization engines.

C++ includes: MinimizerLibrary.h
";

%feature("docstring")  MinimizerLibrary::MinimizerInfo::MinimizerInfo "MinimizerLibrary::MinimizerInfo::MinimizerInfo()
";

%feature("docstring")  MinimizerLibrary::MinimizerInfo::MinimizerInfo "MinimizerInfo::MinimizerInfo(const std::string &minimizerType, const std::string &minimizerDescription)
";

%feature("docstring")  MinimizerLibrary::MinimizerInfo::addAlgorithm "void MinimizerInfo::addAlgorithm(const AlgorithmInfo &algorithm)
";

%feature("docstring")  MinimizerLibrary::MinimizerInfo::addAlgorithm "void MinimizerInfo::addAlgorithm(const std::string &algorithmName, const std::string &algorithmDescription)
";

%feature("docstring")  MinimizerLibrary::MinimizerInfo::algorithmTypes "std::list< std::string > MinimizerInfo::algorithmTypes() const

Return list of algorithm types. 
";

%feature("docstring")  MinimizerLibrary::MinimizerInfo::algorithmDescriptions "std::list< std::string > MinimizerInfo::algorithmDescriptions() const

Returns list of string with description of all available algorithms. 
";


// File: classMinimizerOptions.xml
%feature("docstring") MinimizerOptions "

The MinimizerOptions class contains options for minimization algorithms.

It allows to set values only if they have been already registered.

C++ includes: MinimizerOptions.h
";

%feature("docstring")  MinimizerOptions::MinimizerOptions "MinimizerOptions::MinimizerOptions()
";

%feature("docstring")  MinimizerOptions::~MinimizerOptions "MinimizerOptions::~MinimizerOptions()
";

%feature("docstring")  MinimizerOptions::getTolerance "double MinimizerOptions::getTolerance() const

return minimizer tolerance 
";

%feature("docstring")  MinimizerOptions::setTolerance "void MinimizerOptions::setTolerance(double tolerance)

set minimizer tolerance 
";

%feature("docstring")  MinimizerOptions::getPrecision "double MinimizerOptions::getPrecision() const

return minimizer precision 
";

%feature("docstring")  MinimizerOptions::setPrecision "void MinimizerOptions::setPrecision(double precision)

set minimizer precision 
";

%feature("docstring")  MinimizerOptions::getMaxIterations "int MinimizerOptions::getMaxIterations() const

return maximum number of allowed iterations 
";

%feature("docstring")  MinimizerOptions::setMaxIterations "void MinimizerOptions::setMaxIterations(int max_iterations)

set maximum number of allowed iterations 
";

%feature("docstring")  MinimizerOptions::getMaxFunctionCalls "int MinimizerOptions::getMaxFunctionCalls() const

return maximum number of allowed function calls 
";

%feature("docstring")  MinimizerOptions::setMaxFunctionCalls "void MinimizerOptions::setMaxFunctionCalls(int max_function_calls)

set maximum number of allowed function calls 
";

%feature("docstring")  MinimizerOptions::getPrintLevel "int MinimizerOptions::getPrintLevel() const

return internal print level of the minimizer 
";

%feature("docstring")  MinimizerOptions::setPrintLevel "void MinimizerOptions::setPrintLevel(int print_level)

set internal print level of the minimizer 
";

%feature("docstring")  MinimizerOptions::setValue "void MinimizerOptions::setValue(const std::string &name, double val)

set option value 
";

%feature("docstring")  MinimizerOptions::setValue "void MinimizerOptions::setValue(const std::string &name, int val)
";

%feature("docstring")  MinimizerOptions::setValue "void MinimizerOptions::setValue(const std::string &name, const std::string &val)
";

%feature("docstring")  MinimizerOptions::getValue "void MinimizerOptions::getValue(const std::string &name, int &val)
";

%feature("docstring")  MinimizerOptions::getValue "void MinimizerOptions::getValue(const std::string &name, double &val)
";

%feature("docstring")  MinimizerOptions::getValue "void MinimizerOptions::getValue(const std::string &name, std::string &val)
";

%feature("docstring")  MinimizerOptions::addValue "void MinimizerOptions::addValue(const std::string &name, double val)
";

%feature("docstring")  MinimizerOptions::addValue "void MinimizerOptions::addValue(const std::string &name, int val)
";

%feature("docstring")  MinimizerOptions::addValue "void MinimizerOptions::addValue(const std::string &name, const std::string &val)
";

%feature("docstring")  MinimizerOptions::getIntValue "int MinimizerOptions::getIntValue(const std::string &name)
";

%feature("docstring")  MinimizerOptions::getRealValue "double MinimizerOptions::getRealValue(const std::string &name)
";

%feature("docstring")  MinimizerOptions::getNamedValue "std::string MinimizerOptions::getNamedValue(const std::string &name)
";

%feature("docstring")  MinimizerOptions::print "void MinimizerOptions::print() const 
";


// File: classExceptions_1_1NotImplementedException.xml
%feature("docstring") Exceptions::NotImplementedException "";

%feature("docstring")  Exceptions::NotImplementedException::NotImplementedException "Exceptions::NotImplementedException::NotImplementedException(const std::string &message)
";


// File: classExceptions_1_1NullPointerException.xml
%feature("docstring") Exceptions::NullPointerException "";

%feature("docstring")  Exceptions::NullPointerException::NullPointerException "Exceptions::NullPointerException::NullPointerException(const std::string &message)
";


// File: classExceptions_1_1OutOfBoundsException.xml
%feature("docstring") Exceptions::OutOfBoundsException "";

%feature("docstring")  Exceptions::OutOfBoundsException::OutOfBoundsException "Exceptions::OutOfBoundsException::OutOfBoundsException(const std::string &message)
";


// File: classParameterPool.xml
%feature("docstring") ParameterPool "

Holds a map of pointers to parameters (which must have different names).

C++ includes: ParameterPool.h
";

%feature("docstring")  ParameterPool::ParameterPool "ParameterPool::ParameterPool(const std::string &name, std::function< void()> onChange)

Constructs an empty parameter pool. 
";

%feature("docstring")  ParameterPool::ParameterPool "ParameterPool::ParameterPool(const ParameterPool &)=delete
";

%feature("docstring")  ParameterPool::~ParameterPool "ParameterPool::~ParameterPool()
";

%feature("docstring")  ParameterPool::clone "ParameterPool * ParameterPool::clone() const

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

%feature("docstring")  ParameterPool::getName "std::string ParameterPool::getName() const 
";

%feature("docstring")  ParameterPool::size "size_t ParameterPool::size() const

Returns number of parameters in the pool. 
";

%feature("docstring")  ParameterPool::registerParameter "void ParameterPool::registerParameter(const std::string &name, double *parpointer)

Registers a parameter with key  name and pointer-to-value  parpointer.

Registers parameter with given name. 
";

%feature("docstring")  ParameterPool::registerParameter "void ParameterPool::registerParameter(const std::string &name, double *parpointer, const AttLimits &limits)

Registers a parameter with key  name and pointer-to-value  parpointer.

Registers parameter with given name. 
";

%feature("docstring")  ParameterPool::getParameter "RealParameter * ParameterPool::getParameter(const std::string &name)

Returns parameter named  name.

Returns parameter with given name. 
";

%feature("docstring")  ParameterPool::getParameter "const RealParameter * ParameterPool::getParameter(const std::string &name) const

Returns parameter named  name.

Returns parameter with given name. 
";

%feature("docstring")  ParameterPool::getMatchedParameters "std::vector< RealParameter * > ParameterPool::getMatchedParameters(const std::string &wildcards) const

Returns vector of parameters which fit pattern. 
";

%feature("docstring")  ParameterPool::setParameterValue "void ParameterPool::setParameterValue(const std::string &name, double value)

Sets parameter value. 
";

%feature("docstring")  ParameterPool::setMatchedParametersValue "int ParameterPool::setMatchedParametersValue(const std::string &wildcards, double value)

Sets parameter value, return number of changed parameters.

Sets parameter value. 
";

%feature("docstring")  ParameterPool::getParameterNames "std::vector< std::string > ParameterPool::getParameterNames() const

Returns all parameter names. 
";


// File: classRealParameter.xml
%feature("docstring") RealParameter "

Wrapper to real parameter for remote access to its value and callback abilities

C++ includes: RealParameter.h
";

%feature("docstring")  RealParameter::RealParameter "RealParameter::RealParameter(const std::string &name, ParameterPool *parent, volatile double *par, const AttLimits &limits=AttLimits::limitless())
";

%feature("docstring")  RealParameter::RealParameter "RealParameter::RealParameter(const RealParameter &other)
";

%feature("docstring")  RealParameter::RealParameter "RealParameter::RealParameter(const std::string &name, const RealParameter &other)

This constructor takes copies 'other' except for the name. 
";

%feature("docstring")  RealParameter::getName "std::string RealParameter::getName() const 
";

%feature("docstring")  RealParameter::setValue "void RealParameter::setValue(double value)

Sets value of wrapped parameter and emit signal. 
";

%feature("docstring")  RealParameter::getValue "double RealParameter::getValue() const

Returns value of wrapped parameter. 
";

%feature("docstring")  RealParameter::isNull "bool RealParameter::isNull() const

Returns true if wrapped parameter was not initialized with proper real value. 
";

%feature("docstring")  RealParameter::checkNull "void RealParameter::checkNull() const

throw exception if parameter was not initialized with proper value 
";

%feature("docstring")  RealParameter::getAttLimits "AttLimits RealParameter::getAttLimits() const 
";


// File: classROOTGeneticMinimizer.xml
%feature("docstring") ROOTGeneticMinimizer "

Wrapper for ROOT Genetic minimizer.

C++ includes: ROOTGeneticMinimizer.h
";

%feature("docstring")  ROOTGeneticMinimizer::ROOTGeneticMinimizer "ROOTGeneticMinimizer::ROOTGeneticMinimizer(const std::string &minimizer_name, const std::string &algo_type)
";

%feature("docstring")  ROOTGeneticMinimizer::~ROOTGeneticMinimizer "virtual ROOTGeneticMinimizer::~ROOTGeneticMinimizer()
";

%feature("docstring")  ROOTGeneticMinimizer::setParameter "void ROOTGeneticMinimizer::setParameter(size_t index, const FitParameter *par)

Sets internal minimizer parameter. 
";


// File: classROOTLMAMinimizer.xml
%feature("docstring") ROOTLMAMinimizer "

Wrapper for Levenberg Marquard GSL minimizer.

C++ includes: ROOTLMAMinimizer.h
";

%feature("docstring")  ROOTLMAMinimizer::ROOTLMAMinimizer "ROOTLMAMinimizer::ROOTLMAMinimizer(const std::string &minimizer_name, const std::string &algo_type)
";

%feature("docstring")  ROOTLMAMinimizer::~ROOTLMAMinimizer "virtual ROOTLMAMinimizer::~ROOTLMAMinimizer()
";

%feature("docstring")  ROOTLMAMinimizer::isGradientBasedAgorithm "virtual bool ROOTLMAMinimizer::isGradientBasedAgorithm()

Returns true if type of algorithm is Levenberg-Marquardt or similar. 
";


// File: classROOTMinimizer.xml
%feature("docstring") ROOTMinimizer "

Wrapper for ROOT minimizers to interface with FitSuite.

C++ includes: ROOTMinimizer.h
";

%feature("docstring")  ROOTMinimizer::ROOTMinimizer "ROOTMinimizer::ROOTMinimizer(const std::string &minimizer_name, const std::string &algo_type=std::string())
";

%feature("docstring")  ROOTMinimizer::~ROOTMinimizer "ROOTMinimizer::~ROOTMinimizer()
";

%feature("docstring")  ROOTMinimizer::minimize "void ROOTMinimizer::minimize()

run minimization 
";

%feature("docstring")  ROOTMinimizer::setParameter "void ROOTMinimizer::setParameter(size_t index, const FitParameter *par)

Sets internal minimizer parameter. 
";

%feature("docstring")  ROOTMinimizer::setParameters "void ROOTMinimizer::setParameters(const FitSuiteParameters &parameters)

Sets internal minimizer parameters using external parameter list. 
";

%feature("docstring")  ROOTMinimizer::setChiSquaredFunction "void ROOTMinimizer::setChiSquaredFunction(function_chi2_t fun_chi2, size_t nparameters)

Sets chi squared function to minimize. 
";

%feature("docstring")  ROOTMinimizer::setGradientFunction "void ROOTMinimizer::setGradientFunction(function_gradient_t fun_gradient, size_t nparameters, size_t ndatasize)

Sets gradient function to minimize. 
";

%feature("docstring")  ROOTMinimizer::getNumberOfVariables "size_t ROOTMinimizer::getNumberOfVariables() const

Returns number of variables to fit. 
";

%feature("docstring")  ROOTMinimizer::getMinValue "double ROOTMinimizer::getMinValue() const

Returns minimum function value. 
";

%feature("docstring")  ROOTMinimizer::getValueOfVariableAtMinimum "double ROOTMinimizer::getValueOfVariableAtMinimum(size_t i) const

Returns value of the parameter at the minimum. 
";

%feature("docstring")  ROOTMinimizer::getValueOfVariablesAtMinimum "std::vector< double > ROOTMinimizer::getValueOfVariablesAtMinimum() const

Returns values of parameters at the minimum. 
";

%feature("docstring")  ROOTMinimizer::getErrorOfVariable "double ROOTMinimizer::getErrorOfVariable(size_t i) const

Returns error of variable at minimum. 
";

%feature("docstring")  ROOTMinimizer::getErrorOfVariables "std::vector< double > ROOTMinimizer::getErrorOfVariables() const

Returns errors of variables at minimum. 
";

%feature("docstring")  ROOTMinimizer::printResults "void ROOTMinimizer::printResults() const

Prints fit results. 
";

%feature("docstring")  ROOTMinimizer::clear "void ROOTMinimizer::clear()

clear resources (parameters) for consecutives minimizations 
";

%feature("docstring")  ROOTMinimizer::getNCalls "size_t ROOTMinimizer::getNCalls() const

Returns number of calls of minimized function. 
";

%feature("docstring")  ROOTMinimizer::getOptions "MinimizerOptions * ROOTMinimizer::getOptions()

return minimizer options 
";

%feature("docstring")  ROOTMinimizer::getOptions "const MinimizerOptions * ROOTMinimizer::getOptions() const 
";

%feature("docstring")  ROOTMinimizer::setOptions "void ROOTMinimizer::setOptions(const MinimizerOptions &options)

set minimizer options 
";

%feature("docstring")  ROOTMinimizer::getROOTMinimizer "BA_ROOT::Math::Minimizer * ROOTMinimizer::getROOTMinimizer()

Returns created minimizer. 
";

%feature("docstring")  ROOTMinimizer::getROOTMinimizer "const BA_ROOT::Math::Minimizer * ROOTMinimizer::getROOTMinimizer() const 
";

%feature("docstring")  ROOTMinimizer::isGradientBasedAgorithm "virtual bool ROOTMinimizer::isGradientBasedAgorithm()

Returns true if type of algorithm is Levenberg-Marquardt or similar. 
";

%feature("docstring")  ROOTMinimizer::getMinimizerName "std::string ROOTMinimizer::getMinimizerName() const

return name of the minimizer 
";

%feature("docstring")  ROOTMinimizer::getAlgorithmName "std::string ROOTMinimizer::getAlgorithmName() const

return name of the minimization algorithm 
";


// File: classROOTMinimizerChiSquaredFunction.xml
%feature("docstring") ROOTMinimizerChiSquaredFunction "

minimizer chi2 function

C++ includes: ROOTMinimizerFunction.h
";

%feature("docstring")  ROOTMinimizerChiSquaredFunction::ROOTMinimizerChiSquaredFunction "ROOTMinimizerChiSquaredFunction::ROOTMinimizerChiSquaredFunction(IMinimizer::function_chi2_t fcn, int ndims)
";

%feature("docstring")  ROOTMinimizerChiSquaredFunction::~ROOTMinimizerChiSquaredFunction "virtual ROOTMinimizerChiSquaredFunction::~ROOTMinimizerChiSquaredFunction()
";


// File: classROOTMinimizerGradientFunction.xml
%feature("docstring") ROOTMinimizerGradientFunction "

Minimizer function with access to single data element residuals. Required by Fumili, Fumili2 and GSLMultiMin minimizers.

C++ includes: ROOTMinimizerFunction.h
";

%feature("docstring")  ROOTMinimizerGradientFunction::ROOTMinimizerGradientFunction "ROOTMinimizerGradientFunction::ROOTMinimizerGradientFunction(IMinimizer::function_gradient_t fun_gradient, size_t npars, size_t ndatasize)
";

%feature("docstring")  ROOTMinimizerGradientFunction::~ROOTMinimizerGradientFunction "virtual ROOTMinimizerGradientFunction::~ROOTMinimizerGradientFunction()
";

%feature("docstring")  ROOTMinimizerGradientFunction::Type "Type_t ROOTMinimizerGradientFunction::Type() const 
";

%feature("docstring")  ROOTMinimizerGradientFunction::Clone "BA_ROOT::Math::IMultiGenFunction* ROOTMinimizerGradientFunction::Clone() const 
";

%feature("docstring")  ROOTMinimizerGradientFunction::DataElement "double ROOTMinimizerGradientFunction::DataElement(const double *pars, unsigned int i_data, double *gradient=0) const

evaluation of single data element residual 
";


// File: classROOTMinimizerHelper.xml
%feature("docstring") ROOTMinimizerHelper "

Handles options and printing for  ROOTMinimizer Required by Fumili, Fumili2 and GSLMultiMin minimizers.

C++ includes: ROOTMinimizerHelper.h
";

%feature("docstring")  ROOTMinimizerHelper::ROOTMinimizerHelper "ROOTMinimizerHelper::ROOTMinimizerHelper()
";


// File: classROOTMinuit2Minimizer.xml
%feature("docstring") ROOTMinuit2Minimizer "

Wrapper for ROOT Minuit2 minimizer.

C++ includes: ROOTMinuit2Minimizer.h
";

%feature("docstring")  ROOTMinuit2Minimizer::ROOTMinuit2Minimizer "ROOTMinuit2Minimizer::ROOTMinuit2Minimizer(const std::string &minimizer_name, const std::string &algo_type)
";

%feature("docstring")  ROOTMinuit2Minimizer::~ROOTMinuit2Minimizer "virtual ROOTMinuit2Minimizer::~ROOTMinuit2Minimizer()
";

%feature("docstring")  ROOTMinuit2Minimizer::isGradientBasedAgorithm "bool ROOTMinuit2Minimizer::isGradientBasedAgorithm()

Returns true if type of algorithm is Levenberg-Marquardt or similar. 
";


// File: classROOTMultiMinMinimizer.xml
%feature("docstring") ROOTMultiMinMinimizer "

Wrapper for GSL gradiend descent minimizer family.

C++ includes: ROOTMultiMinMinimizer.h
";

%feature("docstring")  ROOTMultiMinMinimizer::ROOTMultiMinMinimizer "ROOTMultiMinMinimizer::ROOTMultiMinMinimizer(const std::string &minimizer_name, const std::string &algo_type)
";

%feature("docstring")  ROOTMultiMinMinimizer::~ROOTMultiMinMinimizer "virtual ROOTMultiMinMinimizer::~ROOTMultiMinMinimizer()
";


// File: classROOTSimAnMinimizer.xml
%feature("docstring") ROOTSimAnMinimizer "

Wrapper for ROOT GSL simmulated annealing minimizer.

C++ includes: ROOTSimAnMinimizer.h
";

%feature("docstring")  ROOTSimAnMinimizer::ROOTSimAnMinimizer "ROOTSimAnMinimizer::ROOTSimAnMinimizer(const std::string &minimizer_name, const std::string &algo_type)
";

%feature("docstring")  ROOTSimAnMinimizer::~ROOTSimAnMinimizer "virtual ROOTSimAnMinimizer::~ROOTSimAnMinimizer()
";


// File: classExceptions_1_1RuntimeErrorException.xml
%feature("docstring") Exceptions::RuntimeErrorException "";

%feature("docstring")  Exceptions::RuntimeErrorException::RuntimeErrorException "Exceptions::RuntimeErrorException::RuntimeErrorException(const std::string &message)
";


// File: classExceptions_1_1SelfReferenceException.xml
%feature("docstring") Exceptions::SelfReferenceException "";

%feature("docstring")  Exceptions::SelfReferenceException::SelfReferenceException "Exceptions::SelfReferenceException::SelfReferenceException(const std::string &message)
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


// File: classTrivialMinimizer.xml
%feature("docstring") TrivialMinimizer "

Minimizer which calls minimization function once to test whole chain.

C++ includes: TrivialMinimizer.h
";

%feature("docstring")  TrivialMinimizer::TrivialMinimizer "TrivialMinimizer::TrivialMinimizer()
";

%feature("docstring")  TrivialMinimizer::~TrivialMinimizer "virtual TrivialMinimizer::~TrivialMinimizer()
";

%feature("docstring")  TrivialMinimizer::minimize "void TrivialMinimizer::minimize()

run minimization 
";

%feature("docstring")  TrivialMinimizer::setParameters "void TrivialMinimizer::setParameters(const FitSuiteParameters &parameters)

Sets internal minimizer parameters using external parameter list. 
";

%feature("docstring")  TrivialMinimizer::setChiSquaredFunction "virtual void TrivialMinimizer::setChiSquaredFunction(function_chi2_t fun_chi2, size_t)

Sets chi squared function to minimize. 
";

%feature("docstring")  TrivialMinimizer::setGradientFunction "virtual void TrivialMinimizer::setGradientFunction(function_gradient_t, size_t, size_t)

Sets gradient function to minimize. 
";

%feature("docstring")  TrivialMinimizer::getNumberOfVariables "virtual size_t TrivialMinimizer::getNumberOfVariables() const

Returns number of variables to fit. 
";

%feature("docstring")  TrivialMinimizer::getValueOfVariableAtMinimum "double TrivialMinimizer::getValueOfVariableAtMinimum(size_t index) const

Returns pointer to the parameters values at the minimum. 
";

%feature("docstring")  TrivialMinimizer::getValueOfVariablesAtMinimum "std::vector< double > TrivialMinimizer::getValueOfVariablesAtMinimum() const

Returns value of the parameter at the minimum. 
";

%feature("docstring")  TrivialMinimizer::printResults "void TrivialMinimizer::printResults() const

Prints fit results. 
";


// File: classExceptions_1_1UnknownClassRegistrationException.xml
%feature("docstring") Exceptions::UnknownClassRegistrationException "";

%feature("docstring")  Exceptions::UnknownClassRegistrationException::UnknownClassRegistrationException "Exceptions::UnknownClassRegistrationException::UnknownClassRegistrationException(const std::string &message)
";


// File: namespaceAlgorithmNames.xml


// File: namespaceBA__ROOT.xml


// File: namespaceBA__ROOT_1_1Math.xml


// File: namespaceExceptions.xml
%feature("docstring")  Exceptions::LogExceptionMessage "void Exceptions::LogExceptionMessage(const std::string &message)
";


// File: namespaceMinimizerLibrary.xml


// File: namespaceMinimizerNames.xml


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


// File: namespaceUtils.xml
%feature("docstring")  Utils::AdjustStringLength "std::string Utils::AdjustStringLength(const std::string &name, int length)
";

%feature("docstring")  Utils::EnableFloatingPointExceptions "void Utils::EnableFloatingPointExceptions()

enables exception throw in the case of NaN, Inf 
";


// File: AlgorithmNames_8h.xml


// File: IMinimizer_8cpp.xml


// File: IMinimizer_8h.xml


// File: MinimizerFactory_8cpp.xml


// File: MinimizerFactory_8h.xml


// File: MinimizerLibrary_8cpp.xml


// File: MinimizerLibrary_8h.xml


// File: MinimizerOptions_8cpp.xml


// File: MinimizerOptions_8h.xml


// File: TrivialMinimizer_8cpp.xml


// File: TrivialMinimizer_8h.xml


// File: AttLimits_8cpp.xml


// File: AttLimits_8h.xml


// File: FitParameter_8cpp.xml


// File: FitParameter_8h.xml


// File: FitParameterLinked_8cpp.xml


// File: FitParameterLinked_8h.xml


// File: FitSuiteParameters_8cpp.xml


// File: FitSuiteParameters_8h.xml


// File: ParameterPool_8cpp.xml


// File: ParameterPool_8h.xml


// File: RealParameter_8cpp.xml


// File: RealParameter_8h.xml


// File: ROOTGeneticMinimizer_8cpp.xml


// File: ROOTGeneticMinimizer_8h.xml


// File: ROOTLMAMinimizer_8cpp.xml


// File: ROOTLMAMinimizer_8h.xml


// File: ROOTMinimizer_8cpp.xml


// File: ROOTMinimizer_8h.xml


// File: ROOTMinimizerFunction_8h.xml


// File: ROOTMinimizerHelper_8cpp.xml


// File: ROOTMinimizerHelper_8h.xml


// File: ROOTMinuit2Minimizer_8cpp.xml


// File: ROOTMinuit2Minimizer_8h.xml


// File: ROOTMultiMinMinimizer_8cpp.xml


// File: ROOTMultiMinMinimizer_8h.xml


// File: ROOTSimAnMinimizer_8cpp.xml


// File: ROOTSimAnMinimizer_8h.xml


// File: Exceptions_8cpp.xml


// File: Exceptions_8h.xml


// File: Logger_8cpp.xml


// File: Logger_8h.xml


// File: Numeric_8cpp.xml


// File: Numeric_8h.xml


// File: Utils_8cpp.xml


// File: Utils_8h.xml


// File: dir_892d84e8d1420bf45a9053cf0eede900.xml


// File: dir_7c95011753c2f8fb6f2a9c22c1fbdc50.xml


// File: dir_17bde39ef6b5d64be6f6883a061c9058.xml


// File: dir_3d2dd2c6a4dddd0587ea5f12e3139107.xml


// File: dir_c742711e288b52ad835463ef3a11378f.xml

