
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


// File: classFitKernel.xml
%feature("docstring") FitKernel "

Fitting kernel for  FitSuite.

C++ includes: FitKernel.h
";

%feature("docstring")  FitKernel::FitKernel "FitKernel::FitKernel(class FitSuite *fit_suite)
";

%feature("docstring")  FitKernel::FitKernel "FitKernel::FitKernel(const FitKernel &)=delete
";

%feature("docstring")  FitKernel::~FitKernel "FitKernel::~FitKernel()
";

%feature("docstring")  FitKernel::clear "void FitKernel::clear()

Resets most state variables, to get prepared for the next fit.

clear all data 
";

%feature("docstring")  FitKernel::addSimulationAndRealData "void FitKernel::addSimulationAndRealData(const class GISASSimulation &simulation, const OutputData< double > &real_data, double weight)

Adds pair of (simulation, real data) for consecutive simulation. 
";

%feature("docstring")  FitKernel::addFitParameter "void FitKernel::addFitParameter(const std::string &name, double value, const AttLimits &attlim=AttLimits::limitless(), double step=0.0, double error=0.0)

Adds fit parameter.

Adds fit parameter, step is calculated from initial parameter value. 
";

%feature("docstring")  FitKernel::addFitStrategy "void FitKernel::addFitStrategy(const IFitStrategy &strategy)

Adds fit strategy. 
";

%feature("docstring")  FitKernel::setMinimizer "void FitKernel::setMinimizer(class IMinimizer *minimizer)

Sets minimizer. 
";

%feature("docstring")  FitKernel::getMinimizer "IMinimizer * FitKernel::getMinimizer()

Returns minimizer. 
";

%feature("docstring")  FitKernel::runFit "void FitKernel::runFit()

Runs a fit, which may consist of several minimization rounds. 
";

%feature("docstring")  FitKernel::minimize "void FitKernel::minimize()

Runs a single minimization round (called by FitSuiteStrategy) 
";

%feature("docstring")  FitKernel::getFitObjects "FitSuiteObjects * FitKernel::getFitObjects()

Returns reference to the kit with data. 
";

%feature("docstring")  FitKernel::getFitObjects "const FitSuiteObjects * FitKernel::getFitObjects() const 
";

%feature("docstring")  FitKernel::getFitParameters "FitSuiteParameters * FitKernel::getFitParameters()

Returns reference to fit parameters. 
";

%feature("docstring")  FitKernel::getFitStrategies "FitSuiteStrategies * FitKernel::getFitStrategies()

Returns reference to fit parameters. 
";

%feature("docstring")  FitKernel::isLastIteration "bool FitKernel::isLastIteration() const

Returns true if the last iteration is done (used by observers to print summary) 
";

%feature("docstring")  FitKernel::getNCalls "size_t FitKernel::getNCalls() const

Returns current number of minimization function calls. 
";

%feature("docstring")  FitKernel::getCurrentStrategyIndex "size_t FitKernel::getCurrentStrategyIndex() const

Returns the number of current strategy. 
";

%feature("docstring")  FitKernel::printResults "void FitKernel::printResults() const

Prints fit results to stdout. 
";

%feature("docstring")  FitKernel::getOptions "FitOptions & FitKernel::getOptions()

Returns current fit options. 
";

%feature("docstring")  FitKernel::setOptions "void FitKernel::setOptions(const FitOptions &fit_options)

Sets fit options. 
";

%feature("docstring")  FitKernel::getRunTime "double FitKernel::getRunTime() const

Returns total wall time in seconds which was spend for run fit. 
";

%feature("docstring")  FitKernel::notifyObservers "void FitKernel::notifyObservers()
";

%feature("docstring")  FitKernel::isInterrupted "bool FitKernel::isInterrupted() const 
";

%feature("docstring")  FitKernel::interruptFitting "void FitKernel::interruptFitting()
";

%feature("docstring")  FitKernel::resetInterrupt "void FitKernel::resetInterrupt()
";


// File: classFitObject.xml
%feature("docstring") FitObject "

Holds simulation description and real data to run the fit.

C++ includes: FitObject.h
";

%feature("docstring")  FitObject::FitObject "FitObject::FitObject(const GISASSimulation &simulation, const OutputData< double > &real_data, double weight=1, bool adjust_detector_to_data=true)

FitObject constructor

Parameters:
-----------

simulation: 
The simulation to eun

real_data: 
The real data

weight: 
Weight of dataset in chi2 calculations

adjust_detector_to_data: 
Detector axes will be adjusted to real data axes, if true 
";

%feature("docstring")  FitObject::~FitObject "FitObject::~FitObject()
";

%feature("docstring")  FitObject::getRealData "const OutputData<double>* FitObject::getRealData() const

Returns real (experimental) data. 
";

%feature("docstring")  FitObject::getSimulationData "const OutputData<double>* FitObject::getSimulationData() const

Returns simulated data. 
";

%feature("docstring")  FitObject::getSimulation "const GISASSimulation* FitObject::getSimulation() const

Returns simulation. 
";

%feature("docstring")  FitObject::getWeight "double FitObject::getWeight() const

Returns weight of data set in chi2 calculations. 
";

%feature("docstring")  FitObject::getSizeOfData "size_t FitObject::getSizeOfData() const

Returns the size of the data. It is equal to the number of non-masked detector channels which will participate in chi2 calculations. 
";

%feature("docstring")  FitObject::prepareFitElements "void FitObject::prepareFitElements(std::vector< FitElement > &fit_elements, double weight, IIntensityNormalizer *normalizer=0)

Runs simulation and put results (the real and simulated intensities) into external vector. Masked channels will be excluded from the vector. 
";

%feature("docstring")  FitObject::getChiSquaredMap "const OutputData< double > * FitObject::getChiSquaredMap(std::vector< FitElement >::const_iterator first, std::vector< FitElement >::const_iterator last) const

Creates ChiSquared map from external vector. 
";

%feature("docstring")  FitObject::addParametersToExternalPool "std::string FitObject::addParametersToExternalPool(std::string path, ParameterPool *external_pool, int copy_number=-1) const

Adds parameters from local pool to external pool and recursively calls its direct children.

Adds parameters from local pool to external pool. 
";


// File: classFitOptions.xml
%feature("docstring") FitOptions "

General fitting options.

C++ includes: FitOptions.h
";

%feature("docstring")  FitOptions::FitOptions "FitOptions::FitOptions()
";

%feature("docstring")  FitOptions::~FitOptions "FitOptions::~FitOptions()
";

%feature("docstring")  FitOptions::getDerivEpsilon "double FitOptions::getDerivEpsilon() const 
";

%feature("docstring")  FitOptions::setDerivEpsilon "void FitOptions::setDerivEpsilon(double deriv_epsilon)
";

%feature("docstring")  FitOptions::getStepFactor "double FitOptions::getStepFactor() const 
";

%feature("docstring")  FitOptions::setStepFactor "void FitOptions::setStepFactor(double step_factor)
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


// File: classFitStrategyAdjustMinimizer.xml
%feature("docstring") FitStrategyAdjustMinimizer "

Strategy modifies mimimizer settings before running minimization round.

C++ includes: FitStrategyAdjustMinimizer.h
";

%feature("docstring")  FitStrategyAdjustMinimizer::FitStrategyAdjustMinimizer "FitStrategyAdjustMinimizer::FitStrategyAdjustMinimizer()
";

%feature("docstring")  FitStrategyAdjustMinimizer::FitStrategyAdjustMinimizer "FitStrategyAdjustMinimizer::FitStrategyAdjustMinimizer(const std::string &minimizer_name, const std::string &algorithm_name=std::string(), const std::string &minimizer_options=std::string())
";

%feature("docstring")  FitStrategyAdjustMinimizer::~FitStrategyAdjustMinimizer "FitStrategyAdjustMinimizer::~FitStrategyAdjustMinimizer()
";

%feature("docstring")  FitStrategyAdjustMinimizer::clone "FitStrategyAdjustMinimizer * FitStrategyAdjustMinimizer::clone() const 
";

%feature("docstring")  FitStrategyAdjustMinimizer::getMinimizer "IMinimizer * FitStrategyAdjustMinimizer::getMinimizer()
";

%feature("docstring")  FitStrategyAdjustMinimizer::setMinimizer "void FitStrategyAdjustMinimizer::setMinimizer(IMinimizer *minimizer)
";

%feature("docstring")  FitStrategyAdjustMinimizer::setMinimizer "void FitStrategyAdjustMinimizer::setMinimizer(const std::string &minimizer_name, const std::string &algorithm_name=std::string(), const std::string &minimizer_options=std::string())
";

%feature("docstring")  FitStrategyAdjustMinimizer::execute "void FitStrategyAdjustMinimizer::execute()
";

%feature("docstring")  FitStrategyAdjustMinimizer::getMinimizerOptions "MinimizerOptions * FitStrategyAdjustMinimizer::getMinimizerOptions()
";


// File: classFitStrategyAdjustParameters.xml
%feature("docstring") FitStrategyAdjustParameters "

Strategy which fixes/releases fit parameters and call minimizer.

C++ includes: FitStrategyAdjustParameters.h
";

%feature("docstring")  FitStrategyAdjustParameters::FitStrategyAdjustParameters "FitStrategyAdjustParameters::FitStrategyAdjustParameters(const std::string &name)
";

%feature("docstring")  FitStrategyAdjustParameters::FitStrategyAdjustParameters "FitStrategyAdjustParameters::FitStrategyAdjustParameters()
";

%feature("docstring")  FitStrategyAdjustParameters::~FitStrategyAdjustParameters "virtual FitStrategyAdjustParameters::~FitStrategyAdjustParameters()
";

%feature("docstring")  FitStrategyAdjustParameters::clone "virtual FitStrategyAdjustParameters* FitStrategyAdjustParameters::clone() const 
";

%feature("docstring")  FitStrategyAdjustParameters::execute "void FitStrategyAdjustParameters::execute()

strategy which fixes/releases fit parameters and then call minimizer 
";

%feature("docstring")  FitStrategyAdjustParameters::fix_all "virtual FitStrategyAdjustParameters& FitStrategyAdjustParameters::fix_all()
";

%feature("docstring")  FitStrategyAdjustParameters::release_all "virtual FitStrategyAdjustParameters& FitStrategyAdjustParameters::release_all()
";

%feature("docstring")  FitStrategyAdjustParameters::fix "virtual FitStrategyAdjustParameters& FitStrategyAdjustParameters::fix(std::string parname)
";

%feature("docstring")  FitStrategyAdjustParameters::release "virtual FitStrategyAdjustParameters& FitStrategyAdjustParameters::release(std::string parname)
";

%feature("docstring")  FitStrategyAdjustParameters::setPreserveOriginalValues "virtual void FitStrategyAdjustParameters::setPreserveOriginalValues(bool preserve_values)
";

%feature("docstring")  FitStrategyAdjustParameters::clear "virtual void FitStrategyAdjustParameters::clear()
";


// File: classFitStrategyDefault.xml
%feature("docstring") FitStrategyDefault "

Default fit strategy just let  FitSuite to run it's minimization round.

C++ includes: IFitStrategy.h
";

%feature("docstring")  FitStrategyDefault::FitStrategyDefault "FitStrategyDefault::FitStrategyDefault()
";

%feature("docstring")  FitStrategyDefault::clone "IFitStrategy * FitStrategyDefault::clone() const 
";

%feature("docstring")  FitStrategyDefault::execute "void FitStrategyDefault::execute()
";


// File: classFitStrategyFixParameters.xml
%feature("docstring") FitStrategyFixParameters "

Strategy which fixes certain fit parameters leaving other released.

C++ includes: FitStrategyAdjustParameters.h
";

%feature("docstring")  FitStrategyFixParameters::FitStrategyFixParameters "FitStrategyFixParameters::FitStrategyFixParameters()
";

%feature("docstring")  FitStrategyFixParameters::FitStrategyFixParameters "FitStrategyFixParameters::FitStrategyFixParameters(const std::vector< std::string > &pars)
";

%feature("docstring")  FitStrategyFixParameters::~FitStrategyFixParameters "virtual FitStrategyFixParameters::~FitStrategyFixParameters()
";

%feature("docstring")  FitStrategyFixParameters::clone "virtual FitStrategyFixParameters* FitStrategyFixParameters::clone() const 
";

%feature("docstring")  FitStrategyFixParameters::clear "virtual void FitStrategyFixParameters::clear()
";

%feature("docstring")  FitStrategyFixParameters::setFixed "virtual void FitStrategyFixParameters::setFixed(const std::vector< std::string > &pars)
";


// File: classFitStrategyReleaseParameters.xml
%feature("docstring") FitStrategyReleaseParameters "

Strategy which releases certain fit parameters leaving other fixed.

C++ includes: FitStrategyAdjustParameters.h
";

%feature("docstring")  FitStrategyReleaseParameters::FitStrategyReleaseParameters "FitStrategyReleaseParameters::FitStrategyReleaseParameters()
";

%feature("docstring")  FitStrategyReleaseParameters::FitStrategyReleaseParameters "FitStrategyReleaseParameters::FitStrategyReleaseParameters(const std::vector< std::string > &pars)
";

%feature("docstring")  FitStrategyReleaseParameters::~FitStrategyReleaseParameters "virtual FitStrategyReleaseParameters::~FitStrategyReleaseParameters()
";

%feature("docstring")  FitStrategyReleaseParameters::clone "virtual FitStrategyReleaseParameters* FitStrategyReleaseParameters::clone() const 
";

%feature("docstring")  FitStrategyReleaseParameters::clear "virtual void FitStrategyReleaseParameters::clear()
";

%feature("docstring")  FitStrategyReleaseParameters::setReleased "virtual void FitStrategyReleaseParameters::setReleased(const std::vector< std::string > &pars)
";


// File: classFitSuite.xml
%feature("docstring") FitSuite "

User interface class that wraps all fit methods.

C++ includes: FitSuite.h
";

%feature("docstring")  FitSuite::FitSuite "FitSuite::FitSuite()
";

%feature("docstring")  FitSuite::~FitSuite "FitSuite::~FitSuite()
";

%feature("docstring")  FitSuite::addSimulationAndRealData "void FitSuite::addSimulationAndRealData(const GISASSimulation &simulation, const OutputData< double > &real_data, double weight=1)

Assigns pair of (simulation, real data) for fitting. More than one pair can be added. 
";

%feature("docstring")  FitSuite::addSimulationAndRealData "void FitSuite::addSimulationAndRealData(const GISASSimulation &simulation, const IHistogram &real_data, double weight=1)

Assigns pair of (simulation, real data) for fitting. More than one pair can be added. 
";

%feature("docstring")  FitSuite::addFitParameter "void FitSuite::addFitParameter(const std::string &name, double value, const AttLimits &attlim=AttLimits::limitless(), double step=0.0)

Adds fit parameter

Parameters:
-----------

name: 
The name of fit parameter

value: 
Parameter's starting value

attlim: 
Limits attribute

step: 
Initial parameter's step (some minimizers don't use it) 
";

%feature("docstring")  FitSuite::setMinimizer "void FitSuite::setMinimizer(const std::string &minimizer_name, const std::string &algorithm_name=std::string(), const std::string &minimizer_options=std::string())

Sets minimizer with given name and algorithm type

Parameters:
-----------

minimizer_name: 
The name of the minimizer

algorithm_name: 
Optional name of the minimizer's algorithm

minimizer_options: 
Optional string with additional minimizer settings 
";

%feature("docstring")  FitSuite::setChiSquaredModule "void FitSuite::setChiSquaredModule(const IChiSquaredModule &chi2_module)

Replaces default ChiSquaredModule with new one. 
";

%feature("docstring")  FitSuite::addFitStrategy "void FitSuite::addFitStrategy(const IFitStrategy &strategy)

Adds fit strategy. 
";

%feature("docstring")  FitSuite::setMinimizer "void FitSuite::setMinimizer(class IMinimizer *minimizer)

Sets minimizer. 
";

%feature("docstring")  FitSuite::getMinimizer "IMinimizer * FitSuite::getMinimizer()

Returns minimizer. 
";

%feature("docstring")  FitSuite::initPrint "void FitSuite::initPrint(int print_every_nth)

Initializes printing to standard output during the fitting. Prints also the summary when completed.

Parameters:
-----------

print_every_nth: 
Print every n'th iteration 
";

%feature("docstring")  FitSuite::fixAllParameters "void FitSuite::fixAllParameters()

Set all parameters to fixed. 
";

%feature("docstring")  FitSuite::releaseAllParameters "void FitSuite::releaseAllParameters()

Set all parameters to released. 
";

%feature("docstring")  FitSuite::setParametersFixed "void FitSuite::setParametersFixed(const std::vector< std::string > &pars, bool is_fixed)

Set fixed flag for parameters from the list. 
";

%feature("docstring")  FitSuite::runFit "void FitSuite::runFit()

main method to run the fitting 
";

%feature("docstring")  FitSuite::getNumberOfFitObjects "int FitSuite::getNumberOfFitObjects() const

Returns number of fit objects, where fit object stands for (real, simulated) pair. 
";

%feature("docstring")  FitSuite::getRealData "IHistogram * FitSuite::getRealData(size_t i_item=0) const

returns real data histogram

Parameters:
-----------

i_item: 
The index of fit object 
";

%feature("docstring")  FitSuite::getSimulationData "IHistogram * FitSuite::getSimulationData(size_t i_item=0) const

returns simulated data histogram

Parameters:
-----------

i_item: 
The index of fit object 
";

%feature("docstring")  FitSuite::getChiSquaredMap "IHistogram * FitSuite::getChiSquaredMap(size_t i_item=0) const

returns chi2 histogram calculated for (real, simulated) data pair

Parameters:
-----------

i_item: 
The index of fit object 
";

%feature("docstring")  FitSuite::getFitObjects "FitSuiteObjects * FitSuite::getFitObjects()

returns  FitObject (pair of simulation/real data) 
";

%feature("docstring")  FitSuite::getFitParameters "FitSuiteParameters * FitSuite::getFitParameters()

Returns reference to fit parameters. 
";

%feature("docstring")  FitSuite::getFitStrategies "FitSuiteStrategies * FitSuite::getFitStrategies()

Returns reference to fit parameters. 
";

%feature("docstring")  FitSuite::isLastIteration "bool FitSuite::isLastIteration() const

if the last iteration is done (used by observers to print summary) 
";

%feature("docstring")  FitSuite::getNumberOfIterations "size_t FitSuite::getNumberOfIterations() const

Returns current number of minimization function calls. 
";

%feature("docstring")  FitSuite::getCurrentStrategyIndex "size_t FitSuite::getCurrentStrategyIndex() const

Returns the number of current strategy. 
";

%feature("docstring")  FitSuite::printResults "void FitSuite::printResults() const 
";

%feature("docstring")  FitSuite::getChi2 "double FitSuite::getChi2() const

Returns minimum chi squared value found. 
";

%feature("docstring")  FitSuite::getOptions "FitOptions & FitSuite::getOptions()

Returns general setting of fit kernel. 
";

%feature("docstring")  FitSuite::setOptions "void FitSuite::setOptions(const FitOptions &fit_options)

Sets general setting of fit kernel. 
";

%feature("docstring")  FitSuite::interruptFitting "void FitSuite::interruptFitting()
";

%feature("docstring")  FitSuite::resetInterrupt "void FitSuite::resetInterrupt()
";

%feature("docstring")  FitSuite::isInterrupted "bool FitSuite::isInterrupted()
";

%feature("docstring")  FitSuite::getRealOutputData "const OutputData< double > * FitSuite::getRealOutputData(size_t i_item=0) const 
";

%feature("docstring")  FitSuite::getSimulationOutputData "const OutputData< double > * FitSuite::getSimulationOutputData(size_t i_item=0) const 
";

%feature("docstring")  FitSuite::getChiSquaredOutputData "const OutputData< double > * FitSuite::getChiSquaredOutputData(size_t i_item=0) const 
";


// File: classFitSuiteChiSquaredFunction.xml
%feature("docstring") FitSuiteChiSquaredFunction "

Chi squared fitting function for minimizer.

C++ includes: FitSuiteFunctions.h
";

%feature("docstring")  FitSuiteChiSquaredFunction::FitSuiteChiSquaredFunction "FitSuiteChiSquaredFunction::FitSuiteChiSquaredFunction()
";

%feature("docstring")  FitSuiteChiSquaredFunction::~FitSuiteChiSquaredFunction "virtual FitSuiteChiSquaredFunction::~FitSuiteChiSquaredFunction()
";

%feature("docstring")  FitSuiteChiSquaredFunction::evaluate "double FitSuiteChiSquaredFunction::evaluate(const double *pars)

evaluate method for chi2 value called directly from the minimizer

evaluate chi squared value 
";


// File: classFitSuiteGradientFunction.xml
%feature("docstring") FitSuiteGradientFunction "

Gradient fitting function for minimizer.

C++ includes: FitSuiteFunctions.h
";

%feature("docstring")  FitSuiteGradientFunction::FitSuiteGradientFunction "FitSuiteGradientFunction::FitSuiteGradientFunction()
";

%feature("docstring")  FitSuiteGradientFunction::~FitSuiteGradientFunction "virtual FitSuiteGradientFunction::~FitSuiteGradientFunction()
";

%feature("docstring")  FitSuiteGradientFunction::evaluate "double FitSuiteGradientFunction::evaluate(const double *pars, unsigned int index, double *gradients)

evaluate method for gradients and residuals called directly from the minimizer

evaluate residual and derivative for given data element 
";

%feature("docstring")  FitSuiteGradientFunction::getNCallsTotal "virtual size_t FitSuiteGradientFunction::getNCallsTotal() const 
";

%feature("docstring")  FitSuiteGradientFunction::getNCallsGradient "virtual size_t FitSuiteGradientFunction::getNCallsGradient() const 
";


// File: classFitSuiteObjects.xml
%feature("docstring") FitSuiteObjects "

The class containing vector of  FitObject (simulation and real data) to fit.

C++ includes: FitSuiteObjects.h
";

%feature("docstring")  FitSuiteObjects::FitSuiteObjects "FitSuiteObjects::FitSuiteObjects()
";

%feature("docstring")  FitSuiteObjects::~FitSuiteObjects "FitSuiteObjects::~FitSuiteObjects()
";

%feature("docstring")  FitSuiteObjects::add "void FitSuiteObjects::add(const GISASSimulation &simulation, const OutputData< double > &real_data, double weight=1.0)

Adds to kit pair of (simulation, real data) for consecutive simulation. 
";

%feature("docstring")  FitSuiteObjects::getNumberOfFitObjects "size_t FitSuiteObjects::getNumberOfFitObjects() const

Returns number of fit objects (simulation/real data pairs) 
";

%feature("docstring")  FitSuiteObjects::getSizeOfDataSet "size_t FitSuiteObjects::getSizeOfDataSet() const

Returns total number of data points (number of all non-masked channels in all fit objects)

Returns total number of data points. 
";

%feature("docstring")  FitSuiteObjects::setChiSquaredModule "void FitSuiteObjects::setChiSquaredModule(const IChiSquaredModule &chi2_module)

Replaces default ChiSquaredModule with new one. 
";

%feature("docstring")  FitSuiteObjects::getRealData "const OutputData< double > * FitSuiteObjects::getRealData(size_t i_item=0) const

Returns real data from corresponding  FitObject

Parameters:
-----------

i_item: 
Index of  FitObject
";

%feature("docstring")  FitSuiteObjects::getSimulationData "const OutputData< double > * FitSuiteObjects::getSimulationData(size_t i_item=0) const

Returns simulated data from corresponding  FitObject

Parameters:
-----------

i_item: 
Index of  FitObject
";

%feature("docstring")  FitSuiteObjects::getChiSquaredMap "const OutputData< double > * FitSuiteObjects::getChiSquaredMap(size_t i_item=0) const

Returns new chi-squared map from corresponding  FitObject

Parameters:
-----------

i_item: 
Index of  FitObject
";

%feature("docstring")  FitSuiteObjects::runSimulations "void FitSuiteObjects::runSimulations()

run all simulation defined in fit pairs

loop through all defined simulations and run them 
";

%feature("docstring")  FitSuiteObjects::getChiSquaredValue "double FitSuiteObjects::getChiSquaredValue() const

Returns chi2 calculated over whole dataset. 
";

%feature("docstring")  FitSuiteObjects::getResidualValue "double FitSuiteObjects::getResidualValue(size_t global_index)

Returns residuals for single data element

Parameters:
-----------

global_index: 
index accross all element in FitElement vector 
";

%feature("docstring")  FitSuiteObjects::addParametersToExternalPool "std::string FitSuiteObjects::addParametersToExternalPool(std::string path, ParameterPool *external_pool, int copy_number=-1) const

Adds parameters from local pool to external pool and call recursion over direct children.

Adds parameters from local pool to external pool. 
";

%feature("docstring")  FitSuiteObjects::setNfreeParameters "void FitSuiteObjects::setNfreeParameters(int nfree_parameters)
";

%feature("docstring")  FitSuiteObjects::clear "void FitSuiteObjects::clear()

clear all data 
";


// File: classFitSuiteParameters.xml
%feature("docstring") FitSuiteParameters "

Holds vector of parameters for  FitSuite.

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


// File: classFitSuitePrintObserver.xml
%feature("docstring") FitSuitePrintObserver "

Prints fit progress at the end of each  FitSuite's iteration.

C++ includes: FitSuitePrintObserver.h
";

%feature("docstring")  FitSuitePrintObserver::FitSuitePrintObserver "FitSuitePrintObserver::FitSuitePrintObserver(int print_every_nth=1)
";

%feature("docstring")  FitSuitePrintObserver::~FitSuitePrintObserver "virtual FitSuitePrintObserver::~FitSuitePrintObserver()
";

%feature("docstring")  FitSuitePrintObserver::update "void FitSuitePrintObserver::update(FitSuite *fit_suite)

Here Onserver will do actuall job when he thinks that it is a right moment. 
";


// File: classFitSuiteStrategies.xml
%feature("docstring") FitSuiteStrategies "

Collection of strategies to fit.

C++ includes: FitSuiteStrategies.h
";

%feature("docstring")  FitSuiteStrategies::FitSuiteStrategies "FitSuiteStrategies::FitSuiteStrategies()
";

%feature("docstring")  FitSuiteStrategies::~FitSuiteStrategies "FitSuiteStrategies::~FitSuiteStrategies()
";

%feature("docstring")  FitSuiteStrategies::init "void FitSuiteStrategies::init(FitKernel *fit_suite)
";

%feature("docstring")  FitSuiteStrategies::addStrategy "void FitSuiteStrategies::addStrategy(IFitStrategy *strategy)
";

%feature("docstring")  FitSuiteStrategies::minimize "void FitSuiteStrategies::minimize()
";

%feature("docstring")  FitSuiteStrategies::getCurrentStrategyIndex "size_t FitSuiteStrategies::getCurrentStrategyIndex() const 
";

%feature("docstring")  FitSuiteStrategies::size "size_t FitSuiteStrategies::size() const 
";

%feature("docstring")  FitSuiteStrategies::clear "void FitSuiteStrategies::clear()
";

%feature("docstring")  FitSuiteStrategies::getCurrentStrategy "IFitStrategy * FitSuiteStrategies::getCurrentStrategy()
";


// File: classIFitObserver.xml
%feature("docstring") IFitObserver "

Base class for all fit observers. Calls update method in following cases: first iteration, every n-th iteration, last iteration and when fit strategy has changed.

C++ includes: IFitObserver.h
";

%feature("docstring")  IFitObserver::IFitObserver "IFitObserver::IFitObserver(int update_every_nth)
";

%feature("docstring")  IFitObserver::notify "void IFitObserver::notify(IObservable *subject)

The method used by Ovservable when he wants to be observed by this. 
";

%feature("docstring")  IFitObserver::update "void IFitObserver::update(FitSuite *fit_suite)

Here Onserver will do actuall job when he thinks that it is a right moment. 
";


// File: classIFitStrategy.xml
%feature("docstring") IFitStrategy "

Interface to concrete fit strategy.

Concrete implementation should manipulate with fit parameters/data and then call minimizer.

C++ includes: IFitStrategy.h
";

%feature("docstring")  IFitStrategy::IFitStrategy "IFitStrategy::IFitStrategy()
";

%feature("docstring")  IFitStrategy::IFitStrategy "IFitStrategy::IFitStrategy(const std::string &name)
";

%feature("docstring")  IFitStrategy::clone "virtual IFitStrategy* IFitStrategy::clone() const =0
";

%feature("docstring")  IFitStrategy::~IFitStrategy "virtual IFitStrategy::~IFitStrategy()
";

%feature("docstring")  IFitStrategy::init "void IFitStrategy::init(FitKernel *fit_suite)
";

%feature("docstring")  IFitStrategy::execute "virtual void IFitStrategy::execute()=0
";


// File: classIFitSuiteFunction.xml
%feature("docstring") IFitSuiteFunction "

Fitting functions interface to be used by Minimizer.

C++ includes: FitSuiteFunctions.h
";

%feature("docstring")  IFitSuiteFunction::IFitSuiteFunction "IFitSuiteFunction::IFitSuiteFunction()
";

%feature("docstring")  IFitSuiteFunction::~IFitSuiteFunction "virtual IFitSuiteFunction::~IFitSuiteFunction()
";

%feature("docstring")  IFitSuiteFunction::init "virtual void IFitSuiteFunction::init(FitKernel *fit_suite)
";

%feature("docstring")  IFitSuiteFunction::getNCalls "virtual size_t IFitSuiteFunction::getNCalls() const 
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

%feature("docstring")  IObserver::notify "virtual void IObserver::notify(IObservable *subject)=0

method which is used by observable subject to notify change in status 
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

Wrapper for ROOT minimizers to interface with  FitSuite.

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


// File: classScanningMinimizer.xml
%feature("docstring") ScanningMinimizer "

Simple scan minimizer looks for minimum of chi2 function on the grid.

C++ includes: ScanningMinimizer.h
";

%feature("docstring")  ScanningMinimizer::ScanningMinimizer "ScanningMinimizer::ScanningMinimizer(int nbins=10)
";

%feature("docstring")  ScanningMinimizer::~ScanningMinimizer "virtual ScanningMinimizer::~ScanningMinimizer()
";

%feature("docstring")  ScanningMinimizer::minimize "void ScanningMinimizer::minimize()

Scan minimizer find minimum of chi2 function by equidistant scanning of fit parameters. 
";

%feature("docstring")  ScanningMinimizer::setParameters "void ScanningMinimizer::setParameters(const FitSuiteParameters &parameters)

Sets internal minimizer parameters using external parameter list. 
";

%feature("docstring")  ScanningMinimizer::setChiSquaredFunction "void ScanningMinimizer::setChiSquaredFunction(function_chi2_t fun_chi2, size_t nparameters)

Sets chi squared function to minimize. 
";

%feature("docstring")  ScanningMinimizer::setGradientFunction "void ScanningMinimizer::setGradientFunction(function_gradient_t fun_gradient, size_t nparameters, size_t ndatasize)

Sets gradient function to minimize. 
";

%feature("docstring")  ScanningMinimizer::getNumberOfVariables "virtual size_t ScanningMinimizer::getNumberOfVariables() const

Returns number of variables to fit. 
";

%feature("docstring")  ScanningMinimizer::getMinValue "double ScanningMinimizer::getMinValue() const

Returns minimum function value. 
";

%feature("docstring")  ScanningMinimizer::getValueOfVariableAtMinimum "double ScanningMinimizer::getValueOfVariableAtMinimum(size_t i) const

Returns value of the parameter at the minimum. 
";

%feature("docstring")  ScanningMinimizer::printResults "void ScanningMinimizer::printResults() const

Prints fit results. 
";

%feature("docstring")  ScanningMinimizer::setNbins "void ScanningMinimizer::setNbins(int nbins)
";

%feature("docstring")  ScanningMinimizer::getNbins "size_t ScanningMinimizer::getNbins() const 
";

%feature("docstring")  ScanningMinimizer::getOutputData "const OutputData<double>* ScanningMinimizer::getOutputData()
";

%feature("docstring")  ScanningMinimizer::getValueOfVariablesAtMinimum "std::vector< double > ScanningMinimizer::getValueOfVariablesAtMinimum() const

Returns values of parameters at the minimum. 
";


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


// File: namespaceAlgorithmNames.xml


// File: namespaceBA__ROOT.xml


// File: namespaceBA__ROOT_1_1Math.xml


// File: namespaceMinimizerLibrary.xml


// File: namespaceMinimizerNames.xml


// File: AlgorithmNames_8h.xml


// File: IMinimizer_8cpp.xml


// File: IMinimizer_8h.xml


// File: MinimizerFactory_8cpp.xml


// File: MinimizerFactory_8h.xml


// File: MinimizerLibrary_8cpp.xml


// File: MinimizerLibrary_8h.xml


// File: MinimizerOptions_8cpp.xml


// File: MinimizerOptions_8h.xml


// File: ScanningMinimizer_8cpp.xml


// File: ScanningMinimizer_8h.xml


// File: TrivialMinimizer_8cpp.xml


// File: TrivialMinimizer_8h.xml


// File: FitParameter_8cpp.xml


// File: FitParameter_8h.xml


// File: FitParameterLinked_8cpp.xml


// File: FitParameterLinked_8h.xml


// File: FitSuiteParameters_8cpp.xml


// File: FitSuiteParameters_8h.xml


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


// File: FitKernel_8cpp.xml


// File: FitKernel_8h.xml


// File: FitObject_8cpp.xml


// File: FitObject_8h.xml


// File: FitOptions_8h.xml


// File: FitStrategyAdjustMinimizer_8cpp.xml


// File: FitStrategyAdjustMinimizer_8h.xml


// File: FitStrategyAdjustParameters_8cpp.xml


// File: FitStrategyAdjustParameters_8h.xml


// File: FitSuite_8cpp.xml


// File: FitSuite_8h.xml


// File: FitSuiteFunctions_8cpp.xml


// File: FitSuiteFunctions_8h.xml


// File: FitSuiteObjects_8cpp.xml


// File: FitSuiteObjects_8h.xml


// File: FitSuitePrintObserver_8cpp.xml


// File: FitSuitePrintObserver_8h.xml


// File: FitSuiteStrategies_8cpp.xml


// File: FitSuiteStrategies_8h.xml


// File: IFitObserver_8cpp.xml


// File: IFitObserver_8h.xml


// File: IFitStrategy_8cpp.xml


// File: IFitStrategy_8h.xml


// File: IObserver_8cpp.xml


// File: IObserver_8h.xml


// File: dir_892d84e8d1420bf45a9053cf0eede900.xml


// File: dir_7c95011753c2f8fb6f2a9c22c1fbdc50.xml


// File: dir_17bde39ef6b5d64be6f6883a061c9058.xml


// File: dir_3d2dd2c6a4dddd0587ea5f12e3139107.xml


// File: dir_2794e2b49ac7cacd65188e59851fd2d5.xml

