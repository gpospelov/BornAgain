#ifndef FITSUITEFUNCTIONS_H
#define FITSUITEFUNCTIONS_H
// ********************************************************************
// * The BornAgain project                                            *
// * Simulation of neutron and x-ray scattering at grazing incidence  *
// *                                                                  *
// * LICENSE AND DISCLAIMER                                           *
// * Lorem ipsum dolor sit amet, consectetur adipiscing elit.  Mauris *
// * eget quam orci. Quisque  porta  varius  dui,  quis  posuere nibh *
// * mollis quis. Mauris commodo rhoncus porttitor.                   *
// ********************************************************************
//! @file   FitSuiteFunctions.h
//! @brief  Definition of FitSuiteFunctions classes
//! @author Scientific Computing Group at FRM II
//! @date   20.12.2012


#include <vector>
#include <cstddef>
using std::size_t;

class FitSuite;

//- -------------------------------------------------------------------
//! @class IFitSuiteFunction
//! @brief Fitting functions interface to be used by Minimizer.
//- -------------------------------------------------------------------
class IFitSuiteFunction
{
public:
    IFitSuiteFunction() : m_fit_suite(0), m_ncall(0) {}
    virtual ~IFitSuiteFunction(){}
    virtual void init(FitSuite *fit_suite) { m_fit_suite = fit_suite; }
    virtual size_t getNCalls() const { return m_ncall; }
protected:
    FitSuite *m_fit_suite;
    size_t m_ncall;
};



//- -------------------------------------------------------------------
//! @class FitSuiteChiSquaredFunction
//! @brief Chi squared fitting function for minimizer
//- -------------------------------------------------------------------
class FitSuiteChiSquaredFunction : public IFitSuiteFunction
{
public:
    FitSuiteChiSquaredFunction(){}
    virtual ~FitSuiteChiSquaredFunction(){}
    //! evaluate method for chi2 value called directly from the minimizer
    double evaluate(const double *pars);
};


//- -------------------------------------------------------------------
//! @class FitSuiteChiSquaredFunction
//! @brief Gradient fitting function for minimizer
//- -------------------------------------------------------------------
class FitSuiteGradientFunction : public IFitSuiteFunction
{
public:
    FitSuiteGradientFunction() : m_npars(0), m_ndatasize(0), m_prev_index(-1), m_ncalls_total(0), m_ncalls_gradient(0) {}
    virtual ~FitSuiteGradientFunction(){}
    //! evaluate method for gradients and residuals called directly from the minimizer
    double evaluate(const double *pars, unsigned int index, double *gradients);
    virtual size_t getNCallsTotal() const { return m_ncalls_total; }
    virtual size_t getNCallsGradient() const { return m_ncalls_gradient; }

private:
    void verify_arrays();
    void verify_minimizer_logic(bool parameters_have_changed, int current_index);
    void calculate_residuals(const double *pars);
    void calculate_gradients(const double *pars);
    void runExperiment(const double *pars);

    size_t m_npars;
    size_t m_ndatasize;
    int m_prev_index;
    std::vector<double > m_residuals; // [m_ndatasize]
    std::vector<std::vector<double> > m_gradients; // [m_npars][m_ndatasize]
    size_t m_ncalls_total;
    size_t m_ncalls_gradient;
};



#endif // FITSUITEFUNCTIONS_H
