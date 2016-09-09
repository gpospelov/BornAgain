// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Fitting/FitSuite.h
//! @brief     Defines class FitSuite.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef FITSUITE_H
#define FITSUITE_H

#include "Attributes.h"
#include "RealLimits.h"
#include "IObserver.h"
#include "OutputData.h"

class GISASSimulation;
class IHistogram;
class IChiSquaredModule;
class IFitStrategy;
class FitSuiteObjects;
class FitSuiteParameters;
class FitSuiteStrategies;
class FitOptions;
class FitKernel;

//! @class FitSuite
//! @ingroup fitting
//! @brief User interface class that wraps all fit methods.

class BA_CORE_API_ FitSuite : public IObservable
{
public:
    FitSuite();
    FitSuite(const FitSuite&) = delete;
    ~FitSuite();
    FitSuite& operator=(const FitSuite&) = delete;

    // ------------------------------------------------------------------------
    // Fitting setup
    // ------------------------------------------------------------------------

    //! Assigns pair of (simulation, real data) for fitting. More than one pair can be added.
    void addSimulationAndRealData(const GISASSimulation& simulation,
                                  const OutputData<double>& real_data, double weight=1);

    //! Assigns pair of (simulation, real data) for fitting. More than one pair can be added.
    void addSimulationAndRealData(const GISASSimulation& simulation,
                                  const IHistogram& real_data, double weight=1);

    //! Adds fit parameter
    //! @param name The name of fit parameter
    //! @param value Parameter's starting value
    //! @param attlim Limits attribute
    //! @param step Initial parameter's step (some minimizers don't use it)
    void addFitParameter(const std::string& name, double value,
                         const RealLimits& lim=RealLimits::limitless(),
                         const Attributes& attr=Attributes::free(), double step = 0.0);

    //! Sets minimizer with given name and algorithm type
    //! @param minimizer_name The name of the minimizer
    //! @param algorithm_name Optional name of the minimizer's algorithm
    //! @param minimizer_options Optional string with additional minimizer settings
    void setMinimizer(const std::string& minimizer_name,
                      const std::string& algorithm_name = std::string(),
                      const std::string& minimizer_options=std::string());

    //! Replaces default ChiSquaredModule with new one
    void setChiSquaredModule(const IChiSquaredModule& chi2_module);

    //! Adds fit strategy
    void addFitStrategy(const IFitStrategy& strategy);

    //! Sets minimizer
    void setMinimizer(class IMinimizer* minimizer);

    //! Returns minimizer
    class IMinimizer* getMinimizer();

    //! Initializes printing to standard output during the fitting.
    //! Prints also the summary when completed.
    //! @param print_every_nth Print every n'th iteration
    void initPrint(int print_every_nth);

    //! Set all parameters to fixed
    void fixAllParameters();

    //! Set all parameters to released
    void releaseAllParameters();

    //! Set fixed flag for parameters from the list
    void setParametersFixed(const std::vector<std::string>& pars, bool is_fixed);

    //! main method to run the fitting
    void runFit();

    // ------------------------------------------------------------------------
    // Access to the data
    // ------------------------------------------------------------------------

    //! Returns number of fit objects, where fit object stands for (real, simulated) pair.
    int getNumberOfFitObjects() const;

    //! returns real data histogram
    //! @param i_item The index of fit object
    IHistogram* getRealData(size_t i_item = 0) const;

    //! returns simulated data  histogram
    //! @param i_item The index of fit object
    IHistogram* getSimulationData(size_t i_item = 0) const;

    //! returns chi2 histogram calculated for (real, simulated) data pair
    //! @param i_item The index of fit object
    IHistogram* getChiSquaredMap(size_t i_item = 0) const;

    //! returns FitObject (pair of simulation/real data)
    FitSuiteObjects* getFitObjects();

    //! Returns reference to fit parameters
    FitSuiteParameters* getFitParameters();

    //! Returns reference to fit parameters
    FitSuiteStrategies* getFitStrategies();

    //! if the last iteration is done (used by observers to print summary)
    bool isLastIteration() const;

    //! Returns current number of minimization function calls
    size_t getNumberOfIterations() const;

    //! Returns the number of current strategy
    size_t getCurrentStrategyIndex() const;

    //! Prints results of the minimization to the standard output.
    void printResults() const;

    //! Reports results of minimization in the form of multi-line string.
    std::string reportResults() const;

    //! Returns minimum chi squared value found
    double getChi2() const;

    //! Returns general setting of fit kernel
    FitOptions& getOptions();

    //! Sets general setting of fit kernel
    void setOptions(const FitOptions& fit_options);

    void interruptFitting();
    void resetInterrupt();
    bool isInterrupted();

    const OutputData<double>* getRealOutputData(size_t i_item = 0) const;
    const OutputData<double>* getSimulationOutputData(size_t i_item = 0) const;
    const OutputData<double>* getChiSquaredOutputData(size_t i_item = 0) const;

private:
    std::unique_ptr<FitKernel> m_kernel;
};

#endif // FITSUITE_H
