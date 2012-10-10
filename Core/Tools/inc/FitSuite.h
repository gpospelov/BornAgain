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
#include "TRange.h"
#include "FitMultiParameter.h"
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
    FitSuite();
    virtual ~FitSuite();

    //! set experiment
    void setExperiment(Experiment *experiment) { m_experiment = experiment; }

    //! set minimizer
    void setMinimizer(IMinimizer *minimizer) { m_minimizer = minimizer; }
    //! get minimizer
    IMinimizer *getMinimizer() { return m_minimizer; }

    //! add fit parameter
    FitMultiParameter *addFitParameter(const std::string &name, double value, double step, double error=0.0);
    FitMultiParameter *addFitParameter(const std::string &name, double value, double step, const TRange<double> &range);

    //! initialize fitting parameters
    virtual void init_fit_parameters();

    //! set real data
    void setRealData(const OutputData<double> &data);

    //! run fit
    virtual void runFit();

    //! function to minimize
    double functionToMinimize(const double *pars_current_values);

    //! return iterator to the begin of vector of fit parameters
    fitparameters_t::iterator fitparams_begin() { return m_fit_params.begin(); }

    //! return iterator to the end of vector of fit parameters
    fitparameters_t::iterator fitparams_end() { return m_fit_params.end(); }

    //! get chi2 module
    const ChiSquaredModule *getChiSquaredModule() const { return m_chi2_module; }

private:
    Experiment *m_experiment; //! experiment with sample description
    IMinimizer  *m_minimizer; //! minimization engine
    ChiSquaredModule *m_chi2_module; //! module providing chi2 calculations
    fitparameters_t m_fit_params; //! vector of parameters to minimize
};

#endif // FITSUITE_H
