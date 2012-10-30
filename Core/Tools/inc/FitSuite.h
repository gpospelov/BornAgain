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
#include "FitMultiParameter.h"
#include "FitSuiteStrategy.h"
#include <string>

class Experiment;
class IMinimizer;
class ParameterPool;
class ChiSquaredModule;


//- -------------------------------------------------------------------
//! @class FitSuite
//! @brief Main class to perform fitting
//- -------------------------------------------------------------------
class FitSuite : public IObservable
{
public:
    typedef std::vector<FitMultiParameter *> fitparameters_t;
    typedef std::vector<IFitSuiteStrategy *> fitstrategies_t;

    FitSuite();
    virtual ~FitSuite();

    //! clear all and prepare for the next fit
    void clear();

    //! set experiment
    void setExperiment(Experiment *experiment) { m_experiment = experiment; }
    Experiment *getExperiment() { return m_experiment; }

    //! set minimizer
    void setMinimizer(IMinimizer *minimizer) { m_minimizer = minimizer; }
    //! get minimizer
    IMinimizer *getMinimizer() { return m_minimizer; }

    //! add fit parameter
    FitMultiParameter *addFitParameter(const std::string &name, double value, double step, const AttLimits &attlim=AttLimits::limitless());
    //! get fit parameter
    FitMultiParameter *getFitParameter(const std::string &name);

    //! add fit strategy
    void addFitStrategy(IFitSuiteStrategy *strategy);

    //! set real data
    void setRealData(const OutputData<double> &data);

    //! initialize fitting parameters
    virtual void init_fit_parameters();

    //! run single minimization round
    virtual void minimize();

    //! run fitting which may consist of several minimization rounds
    virtual void runFit();

    //! function to minimize
    double functionToMinimize(const double *pars_current_values);

    //! return iterator to the begin of vector of fit parameters
    fitparameters_t::iterator fitparams_begin() { return m_fit_params.begin(); }

    //! return iterator to the end of vector of fit parameters
    fitparameters_t::iterator fitparams_end() { return m_fit_params.end(); }

    //! get chi2 module
    const ChiSquaredModule *getChiSquaredModule() const { return m_chi2_module; }

    //! if the last iteration is done
    bool isLastIteration() { return m_is_last_iteration; }

    //! get current number of minimization function call (number of iteration)
    int getNCall() { return m_n_call; }

    //! get the number of current strategy
    int getNStrategy() { return m_n_strategy; }

private:
    Experiment *m_experiment; //! experiment with sample description
    IMinimizer  *m_minimizer; //! minimization engine
    ChiSquaredModule *m_chi2_module; //! module providing chi2 calculations
    fitparameters_t m_fit_params; //! vector of parameters to minimize
    bool m_is_last_iteration; //! set to true after last iteration complete
    int m_n_call;
    int m_n_strategy;

    fitstrategies_t m_fit_strategies;

};

#endif // FITSUITE_H
