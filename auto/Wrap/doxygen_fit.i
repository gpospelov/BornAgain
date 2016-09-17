
// File: index.xml

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

%feature("docstring")  BasicMinimizer::~BasicMinimizer "BasicMinimizer::~BasicMinimizer()
";

%feature("docstring")  BasicMinimizer::minimize "void BasicMinimizer::minimize()

run minimization 
";

%feature("docstring")  BasicMinimizer::minimizerName "std::string BasicMinimizer::minimizerName() const

Returns name of the minimizer. 
";

%feature("docstring")  BasicMinimizer::algorithmName "std::string BasicMinimizer::algorithmName() const

Returns name of the minimization algorithm. 
";

%feature("docstring")  BasicMinimizer::setParameter "void BasicMinimizer::setParameter(size_t index, const FitParameter *par)

Sets internal minimizer parameter. 
";

%feature("docstring")  BasicMinimizer::setParameters "void BasicMinimizer::setParameters(const FitSuiteParameters &parameters)

Sets internal minimizer parameters using external parameter list. 
";

%feature("docstring")  BasicMinimizer::setChiSquaredFunction "void BasicMinimizer::setChiSquaredFunction(function_chi2_t fun_chi2, size_t nparameters)

Sets chi squared function to minimize. 
";

%feature("docstring")  BasicMinimizer::setGradientFunction "void BasicMinimizer::setGradientFunction(function_gradient_t fun_gradient, size_t nparameters, size_t ndatasize)

Sets gradient function to minimize. 
";

%feature("docstring")  BasicMinimizer::getValueOfVariablesAtMinimum "std::vector< double > BasicMinimizer::getValueOfVariablesAtMinimum() const

Returns values of parameters at the minimum. 
";

%feature("docstring")  BasicMinimizer::getErrorOfVariables "std::vector< double > BasicMinimizer::getErrorOfVariables() const

Returns errors of variables at minimum. 
";

%feature("docstring")  BasicMinimizer::reportResults "std::string BasicMinimizer::reportResults() const

Prints fit results. 
";

%feature("docstring")  BasicMinimizer::options "MinimizerOptions& BasicMinimizer::options()
";

%feature("docstring")  BasicMinimizer::options "const MinimizerOptions& BasicMinimizer::options() const 
";

%feature("docstring")  BasicMinimizer::statusToString "std::string BasicMinimizer::statusToString() const

Returns string representation of current minimizer status. 
";

%feature("docstring")  BasicMinimizer::providesError "bool BasicMinimizer::providesError() const

Returns true if minimizer provides error and error matrix. 
";

%feature("docstring")  BasicMinimizer::statusMap "std::map< std::string, std::string > BasicMinimizer::statusMap() const

Returns map of string representing different minimizer statuses. 
";

%feature("docstring")  BasicMinimizer::propagateResults "void BasicMinimizer::propagateResults(FitSuiteParameters &parameters)

Propagates results of minimization to fit parameter set. 
";


// File: classFitParameter.xml
%feature("docstring") FitParameter "

Fittable parameter with value, error, step, limits, and fixed flag.

C++ includes: FitParameter.h
";

%feature("docstring")  FitParameter::FitParameter "FitParameter::FitParameter()
";

%feature("docstring")  FitParameter::FitParameter "FitParameter::FitParameter(const std::string &name, double value, double step=0.0, const RealLimits &limits=RealLimits::limitless(), const Attributes &attr=Attributes::free(), double error=0.0)
";

%feature("docstring")  FitParameter::~FitParameter "virtual FitParameter::~FitParameter()
";

%feature("docstring")  FitParameter::getName "std::string FitParameter::getName() const 
";

%feature("docstring")  FitParameter::getStartValue "virtual double FitParameter::getStartValue() const 
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

%feature("docstring")  FitParameter::limitsToString "std::string FitParameter::limitsToString() const 
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

%feature("docstring")  FitSuiteParameters::getFitParameters "const std::vector<FitParameter*>& FitSuiteParameters::getFitParameters() const 
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

%feature("docstring")  FitSuiteParameters::valuesDifferFrom "bool FitSuiteParameters::valuesDifferFrom(const double *par_values, double tolerance) const

Returns true if parameters already have the given values. 
";

%feature("docstring")  FitSuiteParameters::reportResults "std::string FitSuiteParameters::reportResults() const 
";

%feature("docstring")  FitSuiteParameters::correlationMatrix "corr_matrix_t FitSuiteParameters::correlationMatrix() const 
";

%feature("docstring")  FitSuiteParameters::setCorrelationMatrix "void FitSuiteParameters::setCorrelationMatrix(const corr_matrix_t &matrix)
";


// File: classGeneticMinimizer.xml
%feature("docstring") GeneticMinimizer "

Wrapper for ROOT Genetic minimizer.

C++ includes: GeneticMinimizer.h
";

%feature("docstring")  GeneticMinimizer::GeneticMinimizer "GeneticMinimizer::GeneticMinimizer()
";

%feature("docstring")  GeneticMinimizer::~GeneticMinimizer "GeneticMinimizer::~GeneticMinimizer()

Sets tolerance on the function value at the minimum. Minimization will stop when the estimated vertical distance to the minimum (EDM) is less than 0.001*tolerance*ErrorDef. Here ErrorDef=1.0 for chi squared fit and ErrorDef=0.5 for negative log likelihood fit. Default value is 0.01. 
";

%feature("docstring")  GeneticMinimizer::setTolerance "void GeneticMinimizer::setTolerance(double value)
";

%feature("docstring")  GeneticMinimizer::tolerance "double GeneticMinimizer::tolerance() const 
";

%feature("docstring")  GeneticMinimizer::setPrintLevel "void GeneticMinimizer::setPrintLevel(int value)

Sets minimizer internal print level. Default value is 0 (silent). 
";

%feature("docstring")  GeneticMinimizer::printLevel "int GeneticMinimizer::printLevel() const 
";

%feature("docstring")  GeneticMinimizer::setMaxIterations "void GeneticMinimizer::setMaxIterations(int value)

Sets maximum number of iterations to try at each step. Default values is 3. 
";

%feature("docstring")  GeneticMinimizer::maxIterations "int GeneticMinimizer::maxIterations() const 
";

%feature("docstring")  GeneticMinimizer::setPopulationSize "void GeneticMinimizer::setPopulationSize(int value)

Sets population size. Default value is 300. 
";

%feature("docstring")  GeneticMinimizer::populationSize "int GeneticMinimizer::populationSize() const 
";

%feature("docstring")  GeneticMinimizer::setRandomSeed "void GeneticMinimizer::setRandomSeed(int value)

Sets random seed. Default value is 0. 
";

%feature("docstring")  GeneticMinimizer::randomSeed "int GeneticMinimizer::randomSeed() const 
";

%feature("docstring")  GeneticMinimizer::setParameter "void GeneticMinimizer::setParameter(size_t index, const FitParameter *par)

Sets minimizer parameter. Overload is required to check that parameter is properly limited. 
";

%feature("docstring")  GeneticMinimizer::statusToString "std::string GeneticMinimizer::statusToString() const

Returns string representation of current minimizer status. 
";

%feature("docstring")  GeneticMinimizer::statusMap "std::map< std::string, std::string > GeneticMinimizer::statusMap() const

Returns map of string representing different minimizer statuses. 
";


// File: classGSLLevenbergMarquardtMinimizer.xml
%feature("docstring") GSLLevenbergMarquardtMinimizer "

Wrapper for GSL Levenberg-Marquardt minimizer. http://www.gnu.org/software/gsl/manual/html_node/Nonlinear-Least_002dSquares-Fitting.html.

C++ includes: GSLLevenbergMarquardtMinimizer.h
";

%feature("docstring")  GSLLevenbergMarquardtMinimizer::GSLLevenbergMarquardtMinimizer "GSLLevenbergMarquardtMinimizer::GSLLevenbergMarquardtMinimizer()
";

%feature("docstring")  GSLLevenbergMarquardtMinimizer::~GSLLevenbergMarquardtMinimizer "GSLLevenbergMarquardtMinimizer::~GSLLevenbergMarquardtMinimizer()

Sets tolerance on the function value at the minimum. Default value is 0.01. 
";

%feature("docstring")  GSLLevenbergMarquardtMinimizer::setTolerance "void GSLLevenbergMarquardtMinimizer::setTolerance(double value)
";

%feature("docstring")  GSLLevenbergMarquardtMinimizer::tolerance "double GSLLevenbergMarquardtMinimizer::tolerance() const 
";

%feature("docstring")  GSLLevenbergMarquardtMinimizer::setPrintLevel "void GSLLevenbergMarquardtMinimizer::setPrintLevel(int value)

Sets minimizer internal print level. Default value is 0 (silent). 
";

%feature("docstring")  GSLLevenbergMarquardtMinimizer::printLevel "int GSLLevenbergMarquardtMinimizer::printLevel() const 
";

%feature("docstring")  GSLLevenbergMarquardtMinimizer::setMaxIterations "void GSLLevenbergMarquardtMinimizer::setMaxIterations(int value)

Sets maximum number of iterations. This is an internal minimizer setting which has no direct relation to the number of objective function calls (e.g. numberOfIteraction=5 might correspond to ~100 objective function calls). 
";

%feature("docstring")  GSLLevenbergMarquardtMinimizer::maxIterations "int GSLLevenbergMarquardtMinimizer::maxIterations() const 
";

%feature("docstring")  GSLLevenbergMarquardtMinimizer::statusToString "std::string GSLLevenbergMarquardtMinimizer::statusToString() const

Returns string representation of current minimizer status. 
";

%feature("docstring")  GSLLevenbergMarquardtMinimizer::statusMap "std::map< std::string, std::string > GSLLevenbergMarquardtMinimizer::statusMap() const

Returns map of string representing different minimizer statuses. 
";


// File: classGSLMultiMinimizer.xml
%feature("docstring") GSLMultiMinimizer "

Wrapper for GSL multi minimizer (gradient descent based) family.

C++ includes: GSLMultiMinimizer.h
";

%feature("docstring")  GSLMultiMinimizer::GSLMultiMinimizer "GSLMultiMinimizer::GSLMultiMinimizer(const std::string &algorithmName=AlgorithmNames::ConjugateFR)
";

%feature("docstring")  GSLMultiMinimizer::~GSLMultiMinimizer "GSLMultiMinimizer::~GSLMultiMinimizer()
";

%feature("docstring")  GSLMultiMinimizer::setPrintLevel "void GSLMultiMinimizer::setPrintLevel(int value)

Sets minimizer internal print level. Default value is 0 (silent). 
";

%feature("docstring")  GSLMultiMinimizer::printLevel "int GSLMultiMinimizer::printLevel() const 
";

%feature("docstring")  GSLMultiMinimizer::setMaxIterations "void GSLMultiMinimizer::setMaxIterations(int value)

Sets maximum number of iterations. This is an internal minimizer setting which has no direct relation to the number of objective function calls (e.g. numberOfIteraction=5 might correspond to ~100 objective function calls). 
";

%feature("docstring")  GSLMultiMinimizer::maxIterations "int GSLMultiMinimizer::maxIterations() const 
";

%feature("docstring")  GSLMultiMinimizer::statusToString "std::string GSLMultiMinimizer::statusToString() const

Returns string representation of current minimizer status. 
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

%feature("docstring")  IMinimizer::minimizerName "std::string IMinimizer::minimizerName() const

return name of the minimizer 
";

%feature("docstring")  IMinimizer::algorithmName "std::string IMinimizer::algorithmName() const

return name of the minimization algorithm 
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

%feature("docstring")  IMinimizer::reportResults "std::string IMinimizer::reportResults() const

Prints fit results. 
";

%feature("docstring")  IMinimizer::propagateResults "void IMinimizer::propagateResults(FitSuiteParameters &parameters)

Propagates results of minimization to fit parameter set. 
";


// File: classInfoItem.xml
%feature("docstring") InfoItem "

Simple item to hold the name and the description.

C++ includes: MinimizerInfo.h
";

%feature("docstring")  InfoItem::InfoItem "InfoItem::InfoItem()
";

%feature("docstring")  InfoItem::InfoItem "InfoItem::InfoItem(const std::string &itemName, const std::string &itemDescription)
";

%feature("docstring")  InfoItem::name "std::string InfoItem::name() const 
";

%feature("docstring")  InfoItem::description "std::string InfoItem::description() const 
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

The  MinimizerCatalogue class contains information over all minimizers available.

C++ includes: MinimizerCatalogue.h
";

%feature("docstring")  MinimizerCatalogue::MinimizerCatalogue "MinimizerCatalogue::MinimizerCatalogue()
";

%feature("docstring")  MinimizerCatalogue::toString "std::string MinimizerCatalogue::toString() const

Returns multiline string representing catalogue content. 
";

%feature("docstring")  MinimizerCatalogue::algorithmNames "std::vector< std::string > MinimizerCatalogue::algorithmNames(const std::string &minimizerName) const

Returns list of algorithms defined for the minimizer with a given name. 
";

%feature("docstring")  MinimizerCatalogue::algorithmDescriptions "std::vector< std::string > MinimizerCatalogue::algorithmDescriptions(const std::string &minimizerName) const

Returns list of algorithm's descriptions for the minimizer with a given name . 
";


// File: classMinimizerFactory.xml
%feature("docstring") MinimizerFactory "

Factory to create minimizers.

Minimizer | Algorithms

Minuit2 | Migrad Simplex Combined Scan Fumili GSLMultiMin | SteepestDescent ConjugateFR ConjugatePR BFGS BFGS2 GSLLMA | Default GSLSimAn | Default Genetic | Default

C++ includes: MinimizerFactory.h
";


// File: classMinimizerInfo.xml
%feature("docstring") MinimizerInfo "

The  MinimizerInfo class provides info about the minimizer, including list of defined minimization algorithms.

C++ includes: MinimizerInfo.h
";

%feature("docstring")  MinimizerInfo::MinimizerInfo "MinimizerInfo::MinimizerInfo()
";

%feature("docstring")  MinimizerInfo::MinimizerInfo "MinimizerInfo::MinimizerInfo(const std::string &minimizerType, const std::string &minimizerDescription)
";

%feature("docstring")  MinimizerInfo::setAlgorithmName "void MinimizerInfo::setAlgorithmName(const std::string &algorithmName)

Sets currently active algorithm. 
";

%feature("docstring")  MinimizerInfo::algorithmName "std::string MinimizerInfo::algorithmName() const 
";

%feature("docstring")  MinimizerInfo::algorithmNames "std::vector< std::string > MinimizerInfo::algorithmNames() const

Return list of defined algorithm names. 
";

%feature("docstring")  MinimizerInfo::algorithmDescriptions "std::vector< std::string > MinimizerInfo::algorithmDescriptions() const

Returns list of string with description of all available algorithms. 
";


// File: classMinimizerOptions.xml
%feature("docstring") MinimizerOptions "

The  MinimizerOptions class holds collection of internal minimizer settings.

C++ includes: MinimizerOptions.h
";

%feature("docstring")  MinimizerOptions::toOptionString "std::string MinimizerOptions::toOptionString(const std::string &delimeter=\";\") const

Returns string with all options using given delimeter. 
";


// File: classMinimizerResultsHelper.xml
%feature("docstring") MinimizerResultsHelper "

The  MinimizerResultsHelper class contains all logic to generate reports with the result of minimization.

C++ includes: MinimizerResultsHelper.h
";

%feature("docstring")  MinimizerResultsHelper::MinimizerResultsHelper "MinimizerResultsHelper::MinimizerResultsHelper()
";

%feature("docstring")  MinimizerResultsHelper::reportResults "std::string MinimizerResultsHelper::reportResults(const BasicMinimizer *minimizer) const

Reports results of minimization in the form of multi-line string. 
";

%feature("docstring")  MinimizerResultsHelper::reportResults "std::string MinimizerResultsHelper::reportResults(const FitSuiteParameters *parameters) const

Reports fit parameters settings and final results. 
";


// File: classMinuit2Minimizer.xml
%feature("docstring") Minuit2Minimizer "

The  Minuit2Minimizer class is a wrapper for ROOT Minuit2 minimizer See Minuit2 user manual https://root.cern.ch/root/htmldoc/guides/minuit2/Minuit2.pdf.

C++ includes: Minuit2Minimizer.h
";

%feature("docstring")  Minuit2Minimizer::Minuit2Minimizer "Minuit2Minimizer::Minuit2Minimizer(const std::string &algorithmName=AlgorithmNames::Migrad)
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

%feature("docstring")  Minuit2Minimizer::setMaxFunctionCalls "void Minuit2Minimizer::setMaxFunctionCalls(int value)

Sets maximum number of objective function calls. 
";

%feature("docstring")  Minuit2Minimizer::maxFunctionCalls "int Minuit2Minimizer::maxFunctionCalls() const 
";

%feature("docstring")  Minuit2Minimizer::statusToString "std::string Minuit2Minimizer::statusToString() const

Returns string representation of current minimizer status. 
";

%feature("docstring")  Minuit2Minimizer::statusMap "std::map< std::string, std::string > Minuit2Minimizer::statusMap() const

Returns map of string representing different minimizer statuses. 
";


// File: classMultiOption.xml
%feature("docstring") MultiOption "

The  MultiOption class is intended to store a single option for minimization algorithm. Int, double, string values are available. Relies on boost::variant, will be switched to std::variant in C++-17. (before was https://github.com/mapbox/variant.

C++ includes: MultiOption.h
";

%feature("docstring")  MultiOption::MultiOption "MultiOption::MultiOption(const std::string &name=std::string())
";

%feature("docstring")  MultiOption::MultiOption "MultiOption::MultiOption(const std::string &name, const T &t, const std::string &descripion=std::string())
";

%feature("docstring")  MultiOption::name "std::string MultiOption::name() const 
";

%feature("docstring")  MultiOption::description "std::string MultiOption::description() const 
";

%feature("docstring")  MultiOption::setDescription "void MultiOption::setDescription(const std::string &description)
";

%feature("docstring")  MultiOption::value "MultiOption::variant_t & MultiOption::value()
";

%feature("docstring")  MultiOption::defaultValue "MultiOption::variant_t & MultiOption::defaultValue()
";

%feature("docstring")  MultiOption::get "T MultiOption::get() const

Returns the option's value. 
";

%feature("docstring")  MultiOption::getDefault "T MultiOption::getDefault() const

Returns the option's default value (i.e. used during construction) 
";


// File: classOptionContainer.xml
%feature("docstring") OptionContainer "

The  OptionContainer class stores multi option (int,double,string) in a container.

C++ includes: OptionContainer.h
";

%feature("docstring")  OptionContainer::OptionContainer "OptionContainer::OptionContainer()
";

%feature("docstring")  OptionContainer::OptionContainer "OptionContainer::OptionContainer(const OptionContainer &other)

Returns true if option with such name already exists. 
";

%feature("docstring")  OptionContainer::addOption "OptionContainer::option_t OptionContainer::addOption(const std::string &optionName, T value, const std::string &description=std::string())
";

%feature("docstring")  OptionContainer::option "OptionContainer::option_t OptionContainer::option(const std::string &optionName)
";

%feature("docstring")  OptionContainer::option "const OptionContainer::option_t OptionContainer::option(const std::string &optionName) const 
";

%feature("docstring")  OptionContainer::optionValue "T OptionContainer::optionValue(const std::string &optionName) const 
";

%feature("docstring")  OptionContainer::setOptionValue "void OptionContainer::setOptionValue(const std::string &optionName, T value)

Sets the value of option. Option should hold same value type already. 
";

%feature("docstring")  OptionContainer::begin "iterator OptionContainer::begin()
";

%feature("docstring")  OptionContainer::begin "const_iterator OptionContainer::begin() const 
";

%feature("docstring")  OptionContainer::end "iterator OptionContainer::end()
";

%feature("docstring")  OptionContainer::end "const_iterator OptionContainer::end() const 
";

%feature("docstring")  OptionContainer::size "size_t OptionContainer::size() const 
";


// File: classRealLimits.xml
%feature("docstring") RealLimits "

Limits for a real fit parameter.

C++ includes: RealLimits.h
";

%feature("docstring")  RealLimits::RealLimits "RealLimits::RealLimits()
";

%feature("docstring")  RealLimits::hasLowerLimit "bool RealLimits::hasLowerLimit() const

if has lower limit 
";

%feature("docstring")  RealLimits::getLowerLimit "double RealLimits::getLowerLimit() const

Returns lower limit. 
";

%feature("docstring")  RealLimits::setLowerLimit "void RealLimits::setLowerLimit(double value)

Sets lower limit. 
";

%feature("docstring")  RealLimits::removeLowerLimit "void RealLimits::removeLowerLimit()

remove lower limit 
";

%feature("docstring")  RealLimits::hasUpperLimit "bool RealLimits::hasUpperLimit() const

if has upper limit 
";

%feature("docstring")  RealLimits::getUpperLimit "double RealLimits::getUpperLimit() const

Returns upper limit. 
";

%feature("docstring")  RealLimits::setUpperLimit "void RealLimits::setUpperLimit(double value)

Sets upper limit. 
";

%feature("docstring")  RealLimits::removeUpperLimit "void RealLimits::removeUpperLimit()

remove upper limit 
";

%feature("docstring")  RealLimits::hasLowerAndUpperLimits "bool RealLimits::hasLowerAndUpperLimits() const

if has lower and upper limit 
";

%feature("docstring")  RealLimits::setLimits "void RealLimits::setLimits(double xmin, double xmax)

Sets lower and upper limits. 
";

%feature("docstring")  RealLimits::removeLimits "void RealLimits::removeLimits()

remove limits 
";

%feature("docstring")  RealLimits::isInRange "bool RealLimits::isInRange(double value) const

returns true if proposed value is in limits range 
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


// File: classSimAnMinimizer.xml
%feature("docstring") SimAnMinimizer "

Wrapper for ROOT GSL simmulated annealing minimizer.

C++ includes: SimAnMinimizer.h
";

%feature("docstring")  SimAnMinimizer::SimAnMinimizer "SimAnMinimizer::SimAnMinimizer()
";

%feature("docstring")  SimAnMinimizer::~SimAnMinimizer "SimAnMinimizer::~SimAnMinimizer()
";

%feature("docstring")  SimAnMinimizer::setPrintLevel "void SimAnMinimizer::setPrintLevel(int value)

Sets minimizer internal print level. Default value is 0 (silent). 
";

%feature("docstring")  SimAnMinimizer::printLevel "int SimAnMinimizer::printLevel() const 
";

%feature("docstring")  SimAnMinimizer::setMaxIterations "void SimAnMinimizer::setMaxIterations(int value)

Sets maximum number of iterations to try at each step. Default values is 100. 
";

%feature("docstring")  SimAnMinimizer::maxIterations "int SimAnMinimizer::maxIterations() const 
";

%feature("docstring")  SimAnMinimizer::setIterationsAtEachTemp "void SimAnMinimizer::setIterationsAtEachTemp(int value)

Sets number of iterations at each temperature. Default value is 10. 
";

%feature("docstring")  SimAnMinimizer::iterationsAtEachTemp "int SimAnMinimizer::iterationsAtEachTemp() const 
";

%feature("docstring")  SimAnMinimizer::setStepSize "void SimAnMinimizer::setStepSize(double value)

Sets max step size used in random walk. Default value is 1.0. 
";

%feature("docstring")  SimAnMinimizer::stepSize "double SimAnMinimizer::stepSize() const 
";

%feature("docstring")  SimAnMinimizer::setBoltzmannK "void SimAnMinimizer::setBoltzmannK(double value)

Sets Boltzmann distribution parameter: k. Default value 1.0. 
";

%feature("docstring")  SimAnMinimizer::boltzmannK "double SimAnMinimizer::boltzmannK() const 
";

%feature("docstring")  SimAnMinimizer::setBoltzmannInitialTemp "void SimAnMinimizer::setBoltzmannInitialTemp(double value)

Sets Boltzmann distribution parameter: initial temperature. Default value 50.0. 
";

%feature("docstring")  SimAnMinimizer::boltzmannInitialTemp "double SimAnMinimizer::boltzmannInitialTemp() const 
";

%feature("docstring")  SimAnMinimizer::setBoltzmannMu "void SimAnMinimizer::setBoltzmannMu(double value)

Sets Boltzmann distribution parameter: mu. Default value 1.05. 
";

%feature("docstring")  SimAnMinimizer::boltzmannMu "double SimAnMinimizer::boltzmannMu() const 
";

%feature("docstring")  SimAnMinimizer::setBoltzmannMinTemp "void SimAnMinimizer::setBoltzmannMinTemp(double value)

Sets Boltzmann distribution parameter: minimal temperature. Default value 0.1. 
";

%feature("docstring")  SimAnMinimizer::boltzmannMinTemp "double SimAnMinimizer::boltzmannMinTemp() const 
";

%feature("docstring")  SimAnMinimizer::statusMap "std::map< std::string, std::string > SimAnMinimizer::statusMap() const

Returns map of string representing different minimizer statuses. 
";

%feature("docstring")  SimAnMinimizer::isGradientBasedAgorithm "virtual bool SimAnMinimizer::isGradientBasedAgorithm()
";


// File: classTestMinimizer.xml
%feature("docstring") TestMinimizer "

Minimizer which calls minimization function once to test whole chain.

C++ includes: TestMinimizer.h
";

%feature("docstring")  TestMinimizer::TestMinimizer "TestMinimizer::TestMinimizer()
";

%feature("docstring")  TestMinimizer::~TestMinimizer "TestMinimizer::~TestMinimizer()
";

%feature("docstring")  TestMinimizer::minimizerName "std::string TestMinimizer::minimizerName() const

return name of the minimizer 
";

%feature("docstring")  TestMinimizer::minimize "void TestMinimizer::minimize()

run minimization 
";

%feature("docstring")  TestMinimizer::setParameters "void TestMinimizer::setParameters(const FitSuiteParameters &parameters)

Sets internal minimizer parameters using external parameter list. 
";

%feature("docstring")  TestMinimizer::setChiSquaredFunction "void TestMinimizer::setChiSquaredFunction(function_chi2_t fun_chi2, size_t)

Sets chi squared function to minimize. 
";

%feature("docstring")  TestMinimizer::setGradientFunction "virtual void TestMinimizer::setGradientFunction(function_gradient_t, size_t, size_t)

Sets gradient function to minimize. 
";

%feature("docstring")  TestMinimizer::getNumberOfVariables "virtual size_t TestMinimizer::getNumberOfVariables() const

Returns number of variables to fit. 
";

%feature("docstring")  TestMinimizer::getValueOfVariableAtMinimum "double TestMinimizer::getValueOfVariableAtMinimum(size_t index) const

Returns pointer to the parameters values at the minimum. 
";

%feature("docstring")  TestMinimizer::getValueOfVariablesAtMinimum "std::vector< double > TestMinimizer::getValueOfVariablesAtMinimum() const

Returns value of the parameter at the minimum. 
";

%feature("docstring")  TestMinimizer::reportResults "std::string TestMinimizer::reportResults() const

Prints fit results. 
";

%feature("docstring")  TestMinimizer::getErrorOfVariables "std::vector< double > TestMinimizer::getErrorOfVariables() const

Returns errors of variables at minimum. 
";

%feature("docstring")  TestMinimizer::propagateResults "void TestMinimizer::propagateResults(FitSuiteParameters &)

Propagates results of minimization to fit parameter set. 
";


// File: namespace_0D11.xml


// File: namespace_0D30.xml


// File: namespace_0D32.xml


// File: namespace_0D36.xml


// File: namespaceAlgorithmNames.xml


// File: namespaceBA__ROOT.xml


// File: namespaceBA__ROOT_1_1Math.xml


// File: namespaceBA__ROOT_1_1Minuit2.xml


// File: namespaceMinimizerNames.xml


// File: namespaceMinimizerUtils.xml
%feature("docstring")  MinimizerUtils::toString "std::string MinimizerUtils::toString(const std::vector< std::string > &v, const std::string &delim=\"\")
";

%feature("docstring")  MinimizerUtils::gslErrorDescriptionMap "std::map< int, std::string > MinimizerUtils::gslErrorDescriptionMap()

Returns translation of GSL error code to string. 
";

%feature("docstring")  MinimizerUtils::gslErrorDescription "std::string MinimizerUtils::gslErrorDescription(int errorCode)
";


// File: namespaceMSG.xml
%feature("docstring")  MSG::SetLevel "BA_CORE_API_ void MSG::SetLevel(EMessageLevel level)
";

%feature("docstring")  MSG::SetLevel "BA_CORE_API_ void MSG::SetLevel(const std::string &levelname)
";


// File: namespaceOptionNames.xml


// File: namespaceStringUtils.xml
%feature("docstring")  StringUtils::matchesPattern "bool StringUtils::matchesPattern(const std::string &text, const std::string &wildcardPattern)

Returns true if text matches pattern with wildcards '*' and '?'. 
";

%feature("docstring")  StringUtils::padRight "std::string StringUtils::padRight(const std::string &name, int length)

Returns string right-padded with blanks. 
";


// File: IMinimizer_8cpp.xml


// File: IMinimizer_8h.xml


// File: MinimizerCatalogue_8cpp.xml


// File: MinimizerCatalogue_8h.xml


// File: MinimizerConstants_8h.xml


// File: MinimizerFactory_8cpp.xml


// File: MinimizerFactory_8h.xml


// File: MinimizerInfo_8cpp.xml


// File: MinimizerInfo_8h.xml


// File: MinimizerOptions_8cpp.xml


// File: MinimizerOptions_8h.xml


// File: MinimizerResultsHelper_8cpp.xml


// File: MinimizerResultsHelper_8h.xml
%feature("docstring")  to_string_with_precision "std::string to_string_with_precision(const T a_value, int precision=10, int width=0)
";

%feature("docstring")  to_string_scientific "std::string to_string_scientific(const T a_value, int n=10)
";


// File: MinimizerUtils_8cpp.xml


// File: MinimizerUtils_8h.xml


// File: MultiOption_8cpp.xml


// File: MultiOption_8h.xml


// File: OptionContainer_8cpp.xml


// File: OptionContainer_8h.xml


// File: TestMinimizer_8cpp.xml


// File: TestMinimizer_8h.xml


// File: Attributes_8h.xml


// File: FitParameter_8cpp.xml


// File: FitParameter_8h.xml


// File: FitSuiteParameters_8cpp.xml


// File: FitSuiteParameters_8h.xml


// File: RealLimits_8cpp.xml


// File: RealLimits_8h.xml


// File: BasicMinimizer_8cpp.xml


// File: BasicMinimizer_8h.xml


// File: GeneticMinimizer_8cpp.xml


// File: GeneticMinimizer_8h.xml


// File: GSLLevenbergMarquardtMinimizer_8cpp.xml


// File: GSLLevenbergMarquardtMinimizer_8h.xml


// File: GSLMultiMinimizer_8cpp.xml


// File: GSLMultiMinimizer_8h.xml


// File: Minuit2Minimizer_8cpp.xml


// File: Minuit2Minimizer_8h.xml


// File: ROOTMinimizerFunction_8h.xml


// File: SimAnMinimizer_8cpp.xml


// File: SimAnMinimizer_8h.xml


// File: Logger_8cpp.xml


// File: Logger_8h.xml


// File: StringUtils_8cpp.xml


// File: StringUtils_8h.xml


// File: dir_d0c8f8fb9032c27878972645c4679f14.xml


// File: dir_befad91b6aded329d87ab1464acca32e.xml


// File: dir_f668eca225435178269b3663d40ba22e.xml


// File: dir_1acb97a05207425a4804447756e3d919.xml


// File: dir_66d655750f7b00e32587449835def8b0.xml


// File: dir_111d40054bb7ae6116a9a4a5aab3a0b8.xml

