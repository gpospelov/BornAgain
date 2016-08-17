
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


// File: classAttributes.xml
%feature("docstring") Attributes "

Attributes for a fit parameter. Currently, the only attribute is fixed/free.

C++ includes: Attributes.h
";

%feature("docstring")  Attributes::Attributes "Attributes::Attributes()
";

%feature("docstring")  Attributes::setFixed "void Attributes::setFixed(bool is_fixed)
";

%feature("docstring")  Attributes::isFixed "bool Attributes::isFixed() const 
";


// File: classBasicMinimizer.xml
%feature("docstring") BasicMinimizer "

The  BasicMinimizer class is a base for all minimizers.

C++ includes: BasicMinimizer.h
";

%feature("docstring")  BasicMinimizer::BasicMinimizer "BasicMinimizer::BasicMinimizer(const std::string &minimizerName, const std::string &algorithmName=std::string())
";

%feature("docstring")  BasicMinimizer::~BasicMinimizer "BasicMinimizer::~BasicMinimizer()
";

%feature("docstring")  BasicMinimizer::minimize "void BasicMinimizer::minimize()

run minimization 
";

%feature("docstring")  BasicMinimizer::getMinimizerName "std::string BasicMinimizer::getMinimizerName() const final

return name of the minimizer 
";

%feature("docstring")  BasicMinimizer::getAlgorithmName "std::string BasicMinimizer::getAlgorithmName() const final

return name of the minimization algorithm 
";

%feature("docstring")  BasicMinimizer::setAlgorithmName "void BasicMinimizer::setAlgorithmName(const std::string &algorithmName)
";

%feature("docstring")  BasicMinimizer::setParameter "void BasicMinimizer::setParameter(size_t index, const FitParameter *par)
";

%feature("docstring")  BasicMinimizer::setParameters "void BasicMinimizer::setParameters(const FitSuiteParameters &parameters)

Sets internal minimizer parameter.

Sets internal minimizer parameters using external parameter list 
";

%feature("docstring")  BasicMinimizer::setChiSquaredFunction "void BasicMinimizer::setChiSquaredFunction(function_chi2_t fun_chi2, size_t nparameters)

Sets chi squared function to minimize. 
";

%feature("docstring")  BasicMinimizer::setGradientFunction "void BasicMinimizer::setGradientFunction(function_gradient_t fun_gradient, size_t nparameters, size_t ndatasize)

Sets gradient function to minimize. 
";

%feature("docstring")  BasicMinimizer::getNumberOfVariables "size_t BasicMinimizer::getNumberOfVariables() const

Returns number of variables to fit. 
";

%feature("docstring")  BasicMinimizer::getValueOfVariablesAtMinimum "std::vector< double > BasicMinimizer::getValueOfVariablesAtMinimum() const

Returns minimum function value.

Returns values of parameters at the minimum 
";

%feature("docstring")  BasicMinimizer::getErrorOfVariables "std::vector< double > BasicMinimizer::getErrorOfVariables() const

Returns errors of variables at minimum. 
";

%feature("docstring")  BasicMinimizer::printResults "void BasicMinimizer::printResults() const

clear resources (parameters) for consecutives minimizations

Prints fit results 
";

%feature("docstring")  BasicMinimizer::toResultString "std::string BasicMinimizer::toResultString() const 
";

%feature("docstring")  BasicMinimizer::isGradientBasedAgorithm "virtual bool BasicMinimizer::isGradientBasedAgorithm()

Returns true if type of algorithm is Levenberg-Marquardt or similar. 
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


// File: classConfigurable.xml
%feature("docstring") Configurable "

A base class for storing (int,double,string) options.

C++ includes: Configurable.h
";

%feature("docstring")  Configurable::Configurable "Configurable::Configurable()
";

%feature("docstring")  Configurable::Configurable "Configurable::Configurable(const Configurable &other)

Returns true if option with such name already exists. 
";

%feature("docstring")  Configurable::addOption "Configurable::option_t Configurable::addOption(const std::string &optionName, T value, const std::string &description=std::string())
";

%feature("docstring")  Configurable::option "Configurable::option_t Configurable::option(const std::string &optionName)
";

%feature("docstring")  Configurable::option "const Configurable::option_t Configurable::option(const std::string &optionName) const 
";

%feature("docstring")  Configurable::optionValue "T Configurable::optionValue(const std::string &optionName) const 
";

%feature("docstring")  Configurable::setOptionValue "void Configurable::setOptionValue(const std::string &optionName, T value)

Sets the value of option. Option should hold same value type already. 
";

%feature("docstring")  Configurable::toOptionString "std::string Configurable::toOptionString(const std::string &delimeter=\";\") const

Returns string with all options using given delimeter. 
";


// File: classFitParameter.xml
%feature("docstring") FitParameter "

Fittable parameter with value, error, step, limits, and fixed flag.

C++ includes: FitParameter.h
";

%feature("docstring")  FitParameter::FitParameter "FitParameter::FitParameter()
";

%feature("docstring")  FitParameter::FitParameter "FitParameter::FitParameter(const std::string &name, double value, double step=0.0, const Limits &limits=Limits::limitless(), const Attributes &attr=Attributes::free(), double error=0.0)
";

%feature("docstring")  FitParameter::~FitParameter "virtual FitParameter::~FitParameter()
";

%feature("docstring")  FitParameter::getName "std::string FitParameter::getName() const 
";

%feature("docstring")  FitParameter::setValue "virtual void FitParameter::setValue(double value)
";

%feature("docstring")  FitParameter::getValue "double FitParameter::getValue() const 
";

%feature("docstring")  FitParameter::setStep "void FitParameter::setStep(double value)
";

%feature("docstring")  FitParameter::getStep "double FitParameter::getStep() const 
";

%feature("docstring")  FitParameter::setError "void FitParameter::setError(double value)
";

%feature("docstring")  FitParameter::getError "double FitParameter::getError() const 
";


// File: classFitSuiteParameters.xml
%feature("docstring") FitSuiteParameters "

Vector of parameters, for FitSuite

C++ includes: FitSuiteParameters.h
";

%feature("docstring")  FitSuiteParameters::FitSuiteParameters "FitSuiteParameters::FitSuiteParameters()
";

%feature("docstring")  FitSuiteParameters::~FitSuiteParameters "FitSuiteParameters::~FitSuiteParameters()
";

%feature("docstring")  FitSuiteParameters::clear "void FitSuiteParameters::clear()

Clears all defined parameters. 
";

%feature("docstring")  FitSuiteParameters::addFitParameter "void FitSuiteParameters::addFitParameter(FitParameter *par)

Adds fit parameter. 
";

%feature("docstring")  FitSuiteParameters::getFitParameters "std::vector<FitParameter*>& FitSuiteParameters::getFitParameters()

Returns all parameters. 
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

%feature("docstring")  FitSuiteParameters::begin "std::vector<FitParameter*>::iterator FitSuiteParameters::begin()

Returns begin of container. 
";

%feature("docstring")  FitSuiteParameters::begin "std::vector<FitParameter*>::const_iterator FitSuiteParameters::begin() const 
";

%feature("docstring")  FitSuiteParameters::end "std::vector<FitParameter*>::iterator FitSuiteParameters::end()

Returns end of container. 
";

%feature("docstring")  FitSuiteParameters::end "std::vector<FitParameter*>::const_iterator FitSuiteParameters::end() const 
";

%feature("docstring")  FitSuiteParameters::numberOfFreeFitParameters "size_t FitSuiteParameters::numberOfFreeFitParameters() const

Returns number of free parameters. 
";

%feature("docstring")  FitSuiteParameters::valuesAreDifferent "bool FitSuiteParameters::valuesAreDifferent(const double *pars_valuers, double tolerance_factor=1.0) const

Returns true if parameters already have the given values. 
";

%feature("docstring")  FitSuiteParameters::printFitParameters "void FitSuiteParameters::printFitParameters() const

Print defined parameters. 
";

%feature("docstring")  FitSuiteParameters::fixAll "void FitSuiteParameters::fixAll()

Fix all parameters. 
";

%feature("docstring")  FitSuiteParameters::releaseAll "void FitSuiteParameters::releaseAll()

Release all parameters. 
";

%feature("docstring")  FitSuiteParameters::setFixed "void FitSuiteParameters::setFixed(const std::vector< std::string > &pars, bool is_fixed)

Set fixed flag for parameters from the list. 
";


// File: classIMinimizer.xml
%feature("docstring") IMinimizer "

Common interface for all kind minimizers.

C++ includes: IMinimizer.h
";

%feature("docstring")  IMinimizer::IMinimizer "IMinimizer::IMinimizer()
";

%feature("docstring")  IMinimizer::~IMinimizer "virtual IMinimizer::~IMinimizer()
";

%feature("docstring")  IMinimizer::minimize "virtual void IMinimizer::minimize()=0

run minimization 
";

%feature("docstring")  IMinimizer::setParameters "virtual void IMinimizer::setParameters(const FitSuiteParameters &parameters)=0

Sets internal minimizer parameter.

Sets internal minimizer parameters using external parameter list 
";

%feature("docstring")  IMinimizer::setChiSquaredFunction "virtual void IMinimizer::setChiSquaredFunction(function_chi2_t fun_chi2, size_t nparameters)=0

Sets chi squared function to minimize. 
";

%feature("docstring")  IMinimizer::setGradientFunction "virtual void IMinimizer::setGradientFunction(function_gradient_t fun_gradient, size_t nparameters, size_t ndatasize)=0

Sets gradient function to minimize. 
";

%feature("docstring")  IMinimizer::getNumberOfVariables "virtual size_t IMinimizer::getNumberOfVariables() const =0

Returns number of variables to fit. 
";

%feature("docstring")  IMinimizer::getValueOfVariablesAtMinimum "virtual std::vector<double> IMinimizer::getValueOfVariablesAtMinimum() const =0

Returns minimum function value.

Returns values of parameters at the minimum 
";

%feature("docstring")  IMinimizer::getErrorOfVariables "virtual std::vector<double> IMinimizer::getErrorOfVariables() const =0

Returns errors of variables at minimum. 
";

%feature("docstring")  IMinimizer::printResults "virtual void IMinimizer::printResults() const =0

clear resources (parameters) for consecutives minimizations

Prints fit results 
";

%feature("docstring")  IMinimizer::getNCalls "virtual size_t IMinimizer::getNCalls() const

Returns number of calls of minimized function. 
";

%feature("docstring")  IMinimizer::getOptions "virtual MinimizerOptions* IMinimizer::getOptions()

return minimizer options 
";

%feature("docstring")  IMinimizer::getOptions "virtual const MinimizerOptions* IMinimizer::getOptions() const 
";

%feature("docstring")  IMinimizer::setOptions "virtual void IMinimizer::setOptions(const MinimizerOptions &)

set minimizer options 
";

%feature("docstring")  IMinimizer::setOptionString "virtual void IMinimizer::setOptionString(const std::string &)

set minimizer option string 
";

%feature("docstring")  IMinimizer::isGradientBasedAgorithm "virtual bool IMinimizer::isGradientBasedAgorithm()

Returns true if type of algorithm is Levenberg-Marquardt or similar. 
";

%feature("docstring")  IMinimizer::getMinimizerName "virtual std::string IMinimizer::getMinimizerName() const =0

return name of the minimizer 
";

%feature("docstring")  IMinimizer::getAlgorithmName "virtual std::string IMinimizer::getAlgorithmName() const =0

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


// File: classLimits.xml
%feature("docstring") Limits "

Limits for a fit parameter.

C++ includes: Limits.h
";

%feature("docstring")  Limits::Limits "Limits::Limits()
";

%feature("docstring")  Limits::hasLowerLimit "bool Limits::hasLowerLimit() const

if has lower limit 
";

%feature("docstring")  Limits::getLowerLimit "double Limits::getLowerLimit() const

Returns lower limit. 
";

%feature("docstring")  Limits::setLowerLimit "void Limits::setLowerLimit(double value)

Sets lower limit. 
";

%feature("docstring")  Limits::removeLowerLimit "void Limits::removeLowerLimit()

remove lower limit 
";

%feature("docstring")  Limits::hasUpperLimit "bool Limits::hasUpperLimit() const

if has upper limit 
";

%feature("docstring")  Limits::getUpperLimit "double Limits::getUpperLimit() const

Returns upper limit. 
";

%feature("docstring")  Limits::setUpperLimit "void Limits::setUpperLimit(double value)

Sets upper limit. 
";

%feature("docstring")  Limits::removeUpperLimit "void Limits::removeUpperLimit()

remove upper limit 
";

%feature("docstring")  Limits::hasLowerAndUpperLimits "bool Limits::hasLowerAndUpperLimits() const

if has lower and upper limit 
";

%feature("docstring")  Limits::setLimits "void Limits::setLimits(double xmin, double xmax)

Sets lower and upper limits. 
";

%feature("docstring")  Limits::removeLimits "void Limits::removeLimits()

remove limits 
";

%feature("docstring")  Limits::isInRange "bool Limits::isInRange(double value) const

returns true if proposed value is in limits range 
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


// File: classMinimizerOption.xml
%feature("docstring") MinimizerOption "

The  MinimizerOption class is intended to store a single option for minimization algorithm. Int, double, string values are available. Relies on https://github.com/mapbox/variant, will be switched to std::variant in C++-17.

C++ includes: MinimizerOption.h
";

%feature("docstring")  MinimizerOption::MinimizerOption "MinimizerOption::MinimizerOption(const std::string &name=std::string())
";

%feature("docstring")  MinimizerOption::MinimizerOption "MinimizerOption::MinimizerOption(const std::string &name, const T &t, const std::string &descripion=std::string())
";

%feature("docstring")  MinimizerOption::name "std::string MinimizerOption::name() const 
";

%feature("docstring")  MinimizerOption::description "std::string MinimizerOption::description() const 
";

%feature("docstring")  MinimizerOption::setDescription "void MinimizerOption::setDescription(const std::string &description)
";

%feature("docstring")  MinimizerOption::value "MinimizerOption::variant_t & MinimizerOption::value()
";

%feature("docstring")  MinimizerOption::defaultValue "MinimizerOption::variant_t & MinimizerOption::defaultValue()
";

%feature("docstring")  MinimizerOption::get "T MinimizerOption::get() const

Returns the option's value. 
";

%feature("docstring")  MinimizerOption::getDefault "T MinimizerOption::getDefault() const

Returns the option's default value (i.e. used during construction) 
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


// File: classMinuit2Minimizer.xml
%feature("docstring") Minuit2Minimizer "

The  Minuit2Minimizer class is a wrapper for ROOT Minuit2 minimizer See Minuit2 user manual https://root.cern.ch/root/htmldoc/guides/minuit2/Minuit2.pdf.

C++ includes: Minuit2Minimizer.h
";

%feature("docstring")  Minuit2Minimizer::Minuit2Minimizer "Minuit2Minimizer::Minuit2Minimizer()
";

%feature("docstring")  Minuit2Minimizer::~Minuit2Minimizer "Minuit2Minimizer::~Minuit2Minimizer()
";

%feature("docstring")  Minuit2Minimizer::setStrategy "void Minuit2Minimizer::setStrategy(int value)

Sets minimization strategy (0-low, 1-medium, 2-high minimization quality). At low quality number of function calls will be economized. Default value is 1. 
";

%feature("docstring")  Minuit2Minimizer::strategy "int Minuit2Minimizer::strategy() const 
";

%feature("docstring")  Minuit2Minimizer::setErrorDefinition "void Minuit2Minimizer::setErrorDefinition(double value)

Sets error definition factor for parameter error calculation. If objective function (OF) is the usual chisquare function and if the user wants the usual one-standard-deviation errors, then the error definition should be 1.0. If OF is a negative-log-likelihood function, then 0.5. If OF is a chisquare, but the user wants two-standard-deviation errors, 4.0. Default value is 1.0. 
";

%feature("docstring")  Minuit2Minimizer::errorDefinition "double Minuit2Minimizer::errorDefinition() const

Sets tolerance on the function value at the minimum. Minimization will stop when the estimated vertical distance to the minimum (EDM) is less than 0.001*tolerance*ErrorDef. Here ErrorDef=1.0 for chi squared fit and ErrorDef=0.5 for negative log likelihood fit. Default value is 0.01. 
";

%feature("docstring")  Minuit2Minimizer::setTolerance "void Minuit2Minimizer::setTolerance(double value)
";

%feature("docstring")  Minuit2Minimizer::tolerance "double Minuit2Minimizer::tolerance() const

Sets relative floating point arithmetic precision. Should be adjusted when the user knows that objectiove function value is not calculated to the nominal machine accuracy. Typical values are between 10^-5 and 10^-14. Default value is -1.0 (minimizer specific will be used). 
";

%feature("docstring")  Minuit2Minimizer::setPrecision "void Minuit2Minimizer::setPrecision(double value)
";

%feature("docstring")  Minuit2Minimizer::precision "double Minuit2Minimizer::precision() const 
";

%feature("docstring")  Minuit2Minimizer::setPrintLevel "void Minuit2Minimizer::setPrintLevel(int value)

Sets minimizer internal print level. Default value is 0 (silent). 
";

%feature("docstring")  Minuit2Minimizer::printLevel "int Minuit2Minimizer::printLevel() const 
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
";

%feature("docstring")  ROOTMinimizer::setParameters "void ROOTMinimizer::setParameters(const FitSuiteParameters &parameters)

Sets internal minimizer parameter.

Sets internal minimizer parameters using external parameter list 
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
";

%feature("docstring")  ROOTMinimizer::getValueOfVariablesAtMinimum "std::vector< double > ROOTMinimizer::getValueOfVariablesAtMinimum() const

Returns minimum function value.

Returns values of parameters at the minimum 
";

%feature("docstring")  ROOTMinimizer::getErrorOfVariables "std::vector< double > ROOTMinimizer::getErrorOfVariables() const

Returns errors of variables at minimum. 
";

%feature("docstring")  ROOTMinimizer::printResults "void ROOTMinimizer::printResults() const

clear resources (parameters) for consecutives minimizations

Prints fit results 
";

%feature("docstring")  ROOTMinimizer::clear "void ROOTMinimizer::clear()
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


// File: classTrivialMinimizer.xml
%feature("docstring") TrivialMinimizer "

Minimizer which calls minimization function once to test whole chain.

C++ includes: TrivialMinimizer.h
";

%feature("docstring")  TrivialMinimizer::TrivialMinimizer "TrivialMinimizer::TrivialMinimizer()
";

%feature("docstring")  TrivialMinimizer::~TrivialMinimizer "TrivialMinimizer::~TrivialMinimizer() final
";

%feature("docstring")  TrivialMinimizer::minimize "void TrivialMinimizer::minimize() final

run minimization 
";

%feature("docstring")  TrivialMinimizer::setParameters "void TrivialMinimizer::setParameters(const FitSuiteParameters &parameters) final

Sets internal minimizer parameter.

Sets internal minimizer parameters using external parameter list 
";

%feature("docstring")  TrivialMinimizer::setChiSquaredFunction "void TrivialMinimizer::setChiSquaredFunction(function_chi2_t fun_chi2, size_t) final

Sets chi squared function to minimize. 
";

%feature("docstring")  TrivialMinimizer::setGradientFunction "void TrivialMinimizer::setGradientFunction(function_gradient_t, size_t, size_t) final

Sets gradient function to minimize. 
";

%feature("docstring")  TrivialMinimizer::getNumberOfVariables "size_t TrivialMinimizer::getNumberOfVariables() const final

Returns number of variables to fit. 
";

%feature("docstring")  TrivialMinimizer::getValueOfVariablesAtMinimum "std::vector< double > TrivialMinimizer::getValueOfVariablesAtMinimum() const final

Returns value of the parameter at the minimum. 
";

%feature("docstring")  TrivialMinimizer::getErrorOfVariables "std::vector< double > TrivialMinimizer::getErrorOfVariables() const final

Returns errors of variables at minimum. 
";

%feature("docstring")  TrivialMinimizer::printResults "void TrivialMinimizer::printResults() const final

clear resources (parameters) for consecutives minimizations

Prints fit results 
";

%feature("docstring")  TrivialMinimizer::getMinimizerName "std::string TrivialMinimizer::getMinimizerName() const final

return name of the minimizer 
";

%feature("docstring")  TrivialMinimizer::getAlgorithmName "std::string TrivialMinimizer::getAlgorithmName() const final

return name of the minimization algorithm 
";

%feature("docstring")  TrivialMinimizer::getOptions "MinimizerOptions* TrivialMinimizer::getOptions() final

return minimizer options 
";

%feature("docstring")  TrivialMinimizer::getOptions "const MinimizerOptions* TrivialMinimizer::getOptions() const final
";


// File: namespace_0D14.xml


// File: namespaceAlgorithmNames.xml


// File: namespaceBA__ROOT.xml


// File: namespaceBA__ROOT_1_1Math.xml


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


// File: namespaceStringUtils.xml
%feature("docstring")  StringUtils::matchesPattern "bool StringUtils::matchesPattern(const std::string &text, const std::string &wildcardPattern)

Returns true if text matches pattern with wildcards '*' and '?'. 
";

%feature("docstring")  StringUtils::padRight "std::string StringUtils::padRight(const std::string &name, int length)

Returns string right-padded with blanks. 
";


// File: AlgorithmNames_8h.xml


// File: BasicMinimizer_8cpp.xml


// File: BasicMinimizer_8h.xml


// File: Configurable_8cpp.xml


// File: Configurable_8h.xml


// File: IMinimizer_8h.xml


// File: MinimizerFactory_8cpp.xml


// File: MinimizerFactory_8h.xml


// File: MinimizerLibrary_8cpp.xml


// File: MinimizerLibrary_8h.xml


// File: MinimizerOption_8cpp.xml


// File: MinimizerOption_8h.xml


// File: MinimizerOptions_8cpp.xml


// File: MinimizerOptions_8h.xml


// File: Minuit2Minimizer_8cpp.xml


// File: Minuit2Minimizer_8h.xml


// File: TrivialMinimizer_8cpp.xml


// File: TrivialMinimizer_8h.xml


// File: Attributes_8h.xml


// File: FitParameter_8cpp.xml


// File: FitParameter_8h.xml


// File: FitSuiteParameters_8cpp.xml


// File: FitSuiteParameters_8h.xml


// File: Limits_8cpp.xml


// File: Limits_8h.xml


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


// File: Logger_8cpp.xml


// File: Logger_8h.xml


// File: Numeric_8cpp.xml


// File: Numeric_8h.xml


// File: StringUtils_8cpp.xml


// File: StringUtils_8h.xml


// File: dir_892d84e8d1420bf45a9053cf0eede900.xml


// File: dir_7c95011753c2f8fb6f2a9c22c1fbdc50.xml


// File: dir_17bde39ef6b5d64be6f6883a061c9058.xml


// File: dir_3d2dd2c6a4dddd0587ea5f12e3139107.xml


// File: dir_c742711e288b52ad835463ef3a11378f.xml

