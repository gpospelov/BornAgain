#ifndef FITSUITE_H
#define FITSUITE_H
// ********************************************************************
// * The BornAgain project                                            *
// * Simulation of neutron and x-ray scattering at grazing incidence  *
// *                                                                  *
// * LICENSE AND DISCLAIMER                                           *
// * Lorem ipsum dolor sit amet, consectetur adipiscing elit.  Mauris *
// * eget quam orci. Quisque  porta  varius  dui,  quis  posuere nibh *
// * mollis quis. Mauris commodo rhoncus porttitor.                   *
// ********************************************************************
//! @file   FitSuite.h
//! @brief  Definition of FitSuite class
//! @author Scientific Computing Group at FRM II
//! @date   05.10.2012


#include "IObserver.h"
#include "OutputData.h"
#include "AttLimits.h"
#include "FitParameterLinked.h"
#include "FitSuiteStrategy.h"
#include "FitSuiteKit.h"
#include "FitSuiteParameters.h"
#include "IMinimizer.h"
#include "IChiSquaredModule.h"
#include <string>

class Experiment;
class ParameterPool;



//- -------------------------------------------------------------------
//! @class FitSuite
//! @brief Main class to perform fitting
//- -------------------------------------------------------------------
class FitSuite : public IObservable
{
public:
    typedef std::vector<FitParameterLinked *> fitparameters_t;
    typedef std::vector<IFitSuiteStrategy *> fitstrategies_t;

    FitSuite();
    virtual ~FitSuite();

    //! clear all and prepare for the next fit
    void clear();


    //! add pair of (experiment, real data) for consecutive simulation
    void addExperimentAndRealData(Experiment *experiment, const OutputData<double > *real_data);

    //! add fit parameter
    void addFitParameter(const std::string &name, double value, double step, const AttLimits &attlim=AttLimits::limitless());

    //! add fit strategy
    void addFitStrategy(IFitSuiteStrategy *strategy);

    //! set minimizer
    void setMinimizer(IMinimizer *minimizer) { delete m_minimizer;  m_minimizer = minimizer; }
    //! get minimizer
    IMinimizer *getMinimizer() { return m_minimizer; }

    //! set chisquared modul
    void setChiSquaredModule(IChiSquaredModule *chi2_module){ delete m_chi2_module; m_chi2_module = chi2_module; }

    //! initialize fitting parameters
    virtual void init_fit_parameters();

    //! run single minimization round
    virtual void minimize();

    //! run fitting which may consist of several minimization rounds
    virtual void runFit();

    //! function to minimize
    double functionToMinimize(const double *pars_current_values);

    //! get chi2 module
    const IChiSquaredModule *getChiSquaredModule() const { return m_chi2_module; }

    //! if the last iteration is done (used by observers to print summary)
    bool isLastIteration() { return m_is_last_iteration; }

    //! get current number of minimization function call (number of iteration)
    int getNCall() { return m_n_call; }

    //! get the number of current strategy
    int getNStrategy() { return m_n_strategy; }

    //! return reference to the kit with data
    FitSuiteKit *getSuitKit() { return &m_suite_kit; }

    //! return number of fit parameters
    size_t getNumberOfFitParameters() const { return m_fit_parameters.size(); }

    //! get fit parameter
    FitParameter *getFitParameter(const std::string &name) { return m_fit_parameters.getParameter(name); }

    //! return reference to fit parameters
    FitSuiteParameters *getFitParameters() { return &m_fit_parameters; }

private:
    //! disabled copy constructor and assignment operator
    FitSuite &operator=(const FitSuite &other);
    FitSuite(const FitSuite &other);

    FitSuiteKit m_suite_kit; //! kit which contains pairs of <experiment,real_data> to fit
    FitSuiteParameters m_fit_parameters; //! collection of fit parameters
    fitstrategies_t m_fit_strategies; //! collection of strategies which are executed before every minimization round
    IMinimizer  *m_minimizer; //! minimization engine
    IChiSquaredModule *m_chi2_module; //! module providing chi2 calculations

    bool m_is_last_iteration; //! set to true after last iteration complete
    int m_n_call; //! current number of minimization function call
    int m_n_strategy; //! current number of fit strategy
};

#endif // FITSUITE_H
