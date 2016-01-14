// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      FitKernel/inc/FitKernel.h
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
#include "ChiSquaredModule.h"
#include "IMinimizer.h"
#include "IObserver.h"
#include <string>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/scoped_ptr.hpp>

class GISASSimulation;
class ParameterPool;
class FitSuite;

//! @class FitKernel
//! @ingroup fitting_internal
//! @brief Fitting kernel for FitSuite

class BA_CORE_API_ FitKernel
{
 public:
    FitKernel(FitSuite *fit_suite);
    virtual ~FitKernel();

    //! clear all and prepare for the next fit
    void clear();

    //! Adds pair of (simulation, real data) for consecutive simulation
    void addSimulationAndRealData(const GISASSimulation& simulation,
                                  const OutputData<double>& real_data,
                                  double weight);

    //! Adds fit parameter
    void addFitParameter(const std::string& name, double value,
                         const AttLimits& attlim=AttLimits::limitless(),
                         double step=0.0, double error=0.0);

    //! Adds fit strategy
    void addFitStrategy(const IFitStrategy &strategy);

    //! Sets minimizer
    void setMinimizer(IMinimizer *minimizer);

    //! Returns minimizer
    IMinimizer *getMinimizer();

    //! run fitting which may consist of several minimization rounds
    virtual void runFit();

    //! run single minimization round (called by FitSuiteStrategy)
    void minimize();

    //! Returns reference to the kit with data
    FitSuiteObjects *getFitObjects();
    const FitSuiteObjects *getFitObjects() const;

    //! Returns reference to fit parameters
    FitSuiteParameters *getFitParameters();

    //! Returns reference to fit parameters
    FitSuiteStrategies *getFitStrategies();

    //! if the last iteration is done (used by observers to print summary)
    bool isLastIteration() const;

    //! Returns current number of minimization function calls
    size_t getNCalls() const;

    //! Returns the number of current strategy
    size_t getCurrentStrategyIndex() const;

    //! Prints results of the screen
    void printResults() const;

    FitOptions &getOptions();
    void setOptions(const FitOptions &fit_options);

    //! Returns total wall time in seconds which was spend for run fit
    double getRunTime() const;

    void notifyObservers();

    bool isInterrupted() const;

    void interruptFitting();

 private:
    FitKernel& operator=(const FitKernel& );
    FitKernel(const FitKernel& );

    bool check_prerequisites() const;
    void link_fit_parameters();

    FitOptions m_fit_options;
    FitSuiteObjects m_fit_objects;
    FitSuiteParameters m_fit_parameters;
    FitSuiteStrategies m_fit_strategies;
    boost::scoped_ptr<IMinimizer>  m_minimizer;
    FitSuiteChiSquaredFunction m_function_chi2;
    FitSuiteGradientFunction m_function_gradient;
    bool m_is_last_iteration;
    bool m_is_interrupted;
    boost::posix_time::ptime m_start_time;
    boost::posix_time::ptime m_end_time;
    FitSuite *m_fit_suite;
};

#endif // FITKERNEL_H


