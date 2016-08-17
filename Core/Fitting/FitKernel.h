// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Fitting/FitKernel.h
//! @brief     Defines class FitKernel.
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
#include <boost/date_time/posix_time/posix_time.hpp>
#include <functional>
#ifndef SWIG
#include <atomic>
#endif

class Attributes;
class Limits;
class GISASSimulation;
class IMinimizer;

//! Fitting kernel for FitSuite.
//! @ingroup fitting_internal

class BA_CORE_API_ FitKernel
{
 public:
    FitKernel(const std::function<void()>& notifyObservers);
    FitKernel& operator=(const FitKernel&) = delete;
    FitKernel(const FitKernel&) = delete;
    virtual ~FitKernel();

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
                         const Limits& lim, const Attributes& attr,
                         double step=0.0, double error=0.0);

    //! Adds fit strategy
    void addFitStrategy(const IFitStrategy& strategy);

    //! Sets minimizer
    void setMinimizer(IMinimizer* minimizer);

    //! Returns minimizer
    IMinimizer* getMinimizer() { return m_minimizer.get(); }

    //! Runs a fit, which may consist of several minimization rounds
    virtual void runFit();

    //! Runs a single minimization round (called by FitSuiteStrategy)
    void minimize();

    //! Returns reference to the kit with data
    FitSuiteObjects* getFitObjects() { return &m_fit_objects; }
    const FitSuiteObjects* getFitObjects() const { return &m_fit_objects; }

    //! Returns reference to fit parameters
    FitSuiteParameters* getFitParameters() { return &m_fit_parameters; }

    //! Returns reference to fit parameters
    FitSuiteStrategies* getFitStrategies() { return &m_fit_strategies; }

    //! Returns true if the last iteration is done (used by observers to print summary)
    bool isLastIteration() const { return m_is_last_iteration; }

    //! Returns current number of minimization function calls
    size_t getNCalls() const;

    //! Returns the number of current strategy
    size_t getCurrentStrategyIndex() const;

    //! Prints fit results to stdout
    void printResults() const;

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

private:
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
#ifndef SWIG
    std::atomic<bool> m_is_interrupted;
#endif
    boost::posix_time::ptime m_start_time;
    boost::posix_time::ptime m_end_time;
    std::function<void()> m_notifyObservers;
};

#endif // FITKERNEL_H
