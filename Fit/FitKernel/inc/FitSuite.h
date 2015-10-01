// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      FitKernel/inc/FitSuite.h
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

#include "IObserver.h"
#include "FitKernel.h"

//! @class FitSuite
//! @ingroup fitting
//! @brief Main class to setup GISAS fitting in BornAgain

class BA_CORE_API_ FitSuite : public IObservable
{
public:
    FitSuite();

    // ------------------------------------------------------------------------
    // Fitting setup
    // ------------------------------------------------------------------------

    //! Assigns pair of (simulation, real data) for fitting. More than one pair can be added.
    void addSimulationAndRealData(const GISASSimulation& simulation,
                                  const OutputData<double>& real_data);

    //! Adds fit parameter
    //! @param name The name of fit parameter
    //! @param value Parameter's starting value
    //! @param attlim Limits attribute
    //! @param step Initial parameter's step (some minimizers don't use it)
    void addFitParameter(const std::string& name, double value,
                         const AttLimits& attlim=AttLimits::limitless(), double step = 0.0);

    //! Sets minimizer with given name and algorithm type
    //! @param minimizer The name of the minimizer
    //! @param algorithm Optional name of the algorithm
    //! @param options Optional string with additional minimizer settings
    void setMinimizer(const std::string& minimizer, const std::string& algorithm = std::string(),
                      const std::string& options=std::string());

    //! Sets minimizer
    void setMinimizer(IMinimizer *minimizer);

    //! Returns minimizer
    IMinimizer *getMinimizer(); // FIXME Do I need this?

    //! Initializes printing to standard output during the fitting.
    //! Prints also the summary when completed.
    //! @param print_every_nth Print every n'th iteration
    void initPrint(int print_every_nth);

    //! main method to run the fitting
    void runFit();

    // ------------------------------------------------------------------------
    // Access to the data
    // ------------------------------------------------------------------------

    //! returns real data
    //! @param i_item The index of fit object
    const OutputData<double> * getRealData(size_t i_item = 0) const;

    //! returns simulated data
    //! @param i_item The index of fit object
    const OutputData<double> * getSimulationData(size_t i_item = 0) const;

    //! returns chi2 map calculated for (real, simulated) data pair
    //! @param i_item The index of fit object
    const OutputData<double> * getChiSquaredMap(size_t i_item = 0) const;



    FitSuiteObjects *getFitObjects();

    //! Returns reference to fit parameters
    FitSuiteParameters *getFitParameters();

    //! Returns reference to fit parameters
    FitSuiteStrategies *getFitStrategies();

    //! if the last iteration is done (used by observers to print summary)
    bool isLastIteration() const;

    //! Returns current number of minimization function calls
    size_t getNCalls() const;

    //! Returns the number of current strategy
    size_t getNStrategy() const;

    void printResults() const;



private:
    FitSuite& operator=(const FitSuite& );
    FitSuite(const FitSuite& );

    boost::scoped_ptr<FitKernel> m_kernel;
};

#endif
