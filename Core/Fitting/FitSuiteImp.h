// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Fitting/FitSuiteImp.h
//! @brief     Defines class FitSuiteImp.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef FITSUITEIMP_H
#define FITSUITEIMP_H

#include "FitOptions.h"
#include "FitSuiteFunctions.h"
#include "FitSuiteObjects.h"
#include "FitParameterSet.h"
#include "FitSuiteStrategies.h"
#include <boost/date_time/posix_time/posix_time.hpp>
#include <functional>
#ifndef SWIG
#include <atomic>
#endif

class AttLimits;
class GISASSimulation;
class IMinimizer;
class FitKernel;

//! Fitting kernel for FitSuite.
//! @ingroup fitting_internal

class BA_CORE_API_ FitSuiteImp
{
 public:
    FitSuiteImp(const std::function<void()>& notifyObservers);
    FitSuiteImp& operator=(const FitSuiteImp&) = delete;
    FitSuiteImp(const FitSuiteImp&) = delete;
    virtual ~FitSuiteImp();

    //! Resets most state variables, to get prepared for the next fit
    void clear();

    //! Adds pair of (simulation, real data) for consecutive simulation
    void addSimulationAndRealData(const GISASSimulation& simulation,
                                  const OutputData<double>& real_data,
                                  double weight);

    //! Adds fit parameter
    void addFitParameter(const std::string& name, double value);
    //! Adds fit parameter
    void addFitParameter(const std::string& name, double value,
                         const AttLimits& limits, double step = 0.0);

    //! Adds fit strategy
    void addFitStrategy(const IFitStrategy& strategy);

    //! Sets minimizer
    void setMinimizer(IMinimizer* minimizer);

    //! Returns minimizer
//    const IMinimizer *minimizer() const;

    //! Runs a fit, which may consist of several minimization rounds
    virtual void runFit();

    //! Runs a single minimization round (called by FitSuiteStrategy)
    void minimize();

    //! Returns reference to the kit with data
    FitSuiteObjects* getFitObjects() { return &m_fit_objects; }
    const FitSuiteObjects* getFitObjects() const { return &m_fit_objects; }

    //! Returns reference to fit parameters
    FitParameterSet* getFitParameters();

    //! Returns reference to fit parameters
    FitSuiteStrategies* getFitStrategies() { return &m_fit_strategies; }

    //! Returns true if the last iteration is done (used by observers to print summary)
    bool isLastIteration() const { return m_is_last_iteration; }

    //! Returns current number of minimization function calls
    size_t getNCalls() const;

    //! Returns the number of current strategy
    size_t getCurrentStrategyIndex() const;

    //! Reports results of minimization in the form of multi-line string.
    std::string reportResults() const;

    //! Returns current fit options
    FitOptions& getOptions() { return m_fit_options; }

    //! Sets fit options
    void setOptions(const FitOptions& fit_options) { m_fit_options = fit_options; }

    //! Returns total wall time in seconds which was spend for run fit
    double getRunTime() const;

    void notifyObservers() { m_notifyObservers(); }

    void interruptFitting() { m_is_interrupted = true; }
    void resetInterrupt() { m_is_interrupted = false; }
    bool isInterrupted() const { return m_is_interrupted; }

    const FitKernel* kernel() const;
//    FitKernel* kernel();

private:
    bool check_prerequisites() const;
    void link_fit_parameters();

    FitOptions m_fit_options;
    FitSuiteObjects m_fit_objects;
    FitSuiteStrategies m_fit_strategies;
    FitSuiteChiSquaredFunction m_function_chi2;
    FitSuiteGradientFunction m_function_gradient;
    bool m_is_last_iteration;
#ifndef SWIG
    std::atomic<bool> m_is_interrupted;
#endif
    boost::posix_time::ptime m_start_time;
    boost::posix_time::ptime m_end_time;
    std::function<void()> m_notifyObservers;

    std::unique_ptr<FitKernel> m_kernel;
};

#endif
