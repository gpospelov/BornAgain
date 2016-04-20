// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      FitKernel/FitKernel.h
//! @brief     Declares class FitKernel.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef FITKERNEL_H
#define FITKERNEL_H

#include "FitOptions.h"
#include "FitSuiteFunctions.h"
#include "FitSuiteObjects.h"
#include "FitSuiteParameters.h"
#include "FitSuiteStrategies.h"
#include "ChiSquaredModule.h"
#include "IObserver.h"

#include <string>
#include <memory>
#include <boost/date_time/posix_time/posix_time.hpp>
#ifndef GCCXML_SKIP_THIS
#include <atomic>
#endif

//! @class FitKernel
//! @ingroup fitting_internal
//! @brief Fitting kernel for FitSuite

class BA_CORE_API_ FitKernel
{
 public:
    FitKernel(class FitSuite *fit_suite);
    virtual ~FitKernel();

    //! Resets most state variables, to get prepared for the next fit
    void clear();

    //! Adds pair of (simulation, real data) for consecutive simulation
    void addSimulationAndRealData(const class GISASSimulation& simulation,
                                  const OutputData<double>& real_data,
                                  double weight);

    //! Adds fit parameter
    void addFitParameter(const std::string& name, double value,
                         const AttLimits& attlim=AttLimits::limitless(),
                         double step=0.0, double error=0.0);

    //! Adds fit strategy
    void addFitStrategy(const IFitStrategy &strategy);

    //! Sets minimizer
    void setMinimizer(class IMinimizer *minimizer);

    //! Returns minimizer
    class IMinimizer *getMinimizer();

    //! Runs a fit, which may consist of several minimization rounds
    virtual void runFit();

    //! Runs a single minimization round (called by FitSuiteStrategy)
    void minimize();

    //! Returns reference to the kit with data
    FitSuiteObjects *getFitObjects();
    const FitSuiteObjects *getFitObjects() const;

    //! Returns reference to fit parameters
    FitSuiteParameters *getFitParameters();

    //! Returns reference to fit parameters
    FitSuiteStrategies *getFitStrategies();

    //! Returns true if the last iteration is done (used by observers to print summary)
    bool isLastIteration() const;

    //! Returns current number of minimization function calls
    size_t getNCalls() const;

    //! Returns the number of current strategy
    size_t getCurrentStrategyIndex() const;

    //! Prints fit results to stdout
    void printResults() const;

    //! Returns current fit options
    FitOptions &getOptions();

    //! Sets fit options
    void setOptions(const FitOptions &fit_options);

    //! Returns total wall time in seconds which was spend for run fit
    double getRunTime() const;

    void notifyObservers();

    bool isInterrupted() const;

    void interruptFitting();

    void resetInterrupt();

private:
    FitKernel& operator=(const FitKernel& );
    FitKernel(const FitKernel& );

    bool check_prerequisites() const;
    void link_fit_parameters();

    FitOptions m_fit_options;
    FitSuiteObjects m_fit_objects;
    FitSuiteParameters m_fit_parameters;
    FitSuiteStrategies m_fit_strategies;
    std::unique_ptr<class IMinimizer> m_minimizer;
    FitSuiteChiSquaredFunction m_function_chi2;
    FitSuiteGradientFunction m_function_gradient;
    bool m_is_last_iteration;
#ifndef GCCXML_SKIP_THIS
    std::atomic<bool> m_is_interrupted;
#endif
    boost::posix_time::ptime m_start_time;
    boost::posix_time::ptime m_end_time;
    class FitSuite *m_fit_suite;
};

#endif // FITKERNEL_H
