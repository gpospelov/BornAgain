#ifndef FITSUITESTRATEGY_H
#define FITSUITESTRATEGY_H
// ********************************************************************
// * The BornAgain project                                            *
// * Simulation of neutron and x-ray scattering at grazing incidence  *
// *                                                                  *
// * LICENSE AND DISCLAIMER                                           *
// * Lorem ipsum dolor sit amet, consectetur adipiscing elit.  Mauris *
// * eget quam orci. Quisque  porta  varius  dui,  quis  posuere nibh *
// * mollis quis. Mauris commodo rhoncus porttitor.                   *
// ********************************************************************
//! @file   FitSuiteStrategy.h
//! @brief  Definition of FitStrategy class
//! @author Scientific Computing Group at FRM II
//! @date   29.10.2012


#include "INamed.h"
#include "Types.h"
#include "OutputData.h"
class FitSuite;

#include <string>
#include <vector>
#include <map>


//- -------------------------------------------------------------------
//! @class IFitSuiteStrategy
//! @brief Interface to concrete fit strategy.
//! Concrete implementation should manipulate with fit parameters/data
//! and then call minimizer.
//- -------------------------------------------------------------------
class IFitSuiteStrategy : public INamed
{
public:
    IFitSuiteStrategy() : m_fit_suite(0) {}
    IFitSuiteStrategy(const std::string &name) : INamed(name), m_fit_suite(0) {}

    virtual ~IFitSuiteStrategy(){}
    virtual void init(FitSuite *fit_suite) { m_fit_suite = fit_suite; }
    virtual void execute() = 0;
protected:
    FitSuite *m_fit_suite;
};


//- -------------------------------------------------------------------
//! @class FitSuiteStrategyDefault
//! @brief Default fit strategy just let FitSuite to run it's minimization round
//- -------------------------------------------------------------------
class FitSuiteStrategyDefault : public IFitSuiteStrategy
{
public:
    FitSuiteStrategyDefault() : IFitSuiteStrategy("FitSuiteStrategyDefault") { }
    virtual void execute();
};


//- -------------------------------------------------------------------
//! @class FitSuiteStrategyAdjustData
//! @brief Strategy modifies data before running minimizing round
//- -------------------------------------------------------------------
class FitSuiteStrategyAdjustData : public IFitSuiteStrategy
{
public:
    FitSuiteStrategyAdjustData(int power_of_two = 1) : IFitSuiteStrategy("FitSuiteStrategyAdjustData"), m_power_of_two(power_of_two) { }
    virtual void execute();
private:
    size_t m_power_of_two;
};


//- -------------------------------------------------------------------
//! @class FitSuiteStrategyAdjustParameters
//! @brief Strategy which fixes/releases fit parameters and call minimizer
//- -------------------------------------------------------------------
class FitSuiteStrategyAdjustParameters : public IFitSuiteStrategy
{
public:
    FitSuiteStrategyAdjustParameters(const std::string &name) : IFitSuiteStrategy(name), m_fix_all(false), m_release_all(false) { }
    FitSuiteStrategyAdjustParameters() : IFitSuiteStrategy("FitSuiteStrategyAdjustParameters"), m_fix_all(false), m_release_all(false) { }
    virtual ~FitSuiteStrategyAdjustParameters(){}
    virtual void execute();
    FitSuiteStrategyAdjustParameters &fix_all() { m_fix_all = true; return *this; }
    FitSuiteStrategyAdjustParameters &release_all() { m_release_all = true; return *this; }
    FitSuiteStrategyAdjustParameters &fix(std::string parname ) { m_pars_to_fix.push_back(parname); return *this; }
    FitSuiteStrategyAdjustParameters &release(std::string parname ) { m_pars_to_release.push_back(parname); return *this; }
private:
    bool m_fix_all;
    bool m_release_all;
    std::vector<std::string > m_pars_to_fix;
    std::vector<std::string > m_pars_to_release;
};


//- -------------------------------------------------------------------
//! @class FitSuiteStrategyBootstrap
//! @brief Helps minimizer get out of local minima by disturbing real data
//- -------------------------------------------------------------------
class FitSuiteStrategyBootstrap : public IFitSuiteStrategy
{
public:
    FitSuiteStrategyBootstrap(int n_iterations = 5) : IFitSuiteStrategy("FitStrategyBootstrap"), m_n_iterations(n_iterations) { }
    virtual ~FitSuiteStrategyBootstrap(){}
    virtual void execute();

    // to save results of minimization rounds
    class FitResult {
    public:
        int niter;
        double chi2_last;
        double chi2_noisy;
        double chi2_current;
        vdouble1d_t param_values;
        vdouble1d_t param_values_noisy;
        vdouble1d_t param_values_last;
        bool takethis;
        void clear()
        {
            niter=-1;
            chi2_last=0; chi2_noisy=0; chi2_current=0; param_values.clear(); param_values_noisy.clear(); param_values_last.clear();
        }
    };

    //! get current values of all parameters defined in FitSuite
    std::vector<double > getFitSuiteParameterValues();

    //! set new values of all parameters defined in FitSuite
    void setFitSuiteParameterValues(const std::vector<double > &parvalues);

    //! generate noisy data
    OutputData<double> *generateNoisyData(double noise_factor, const OutputData<double> &source);

private:
    int m_n_iterations;
};


#endif // FITSTRATEGY_H
