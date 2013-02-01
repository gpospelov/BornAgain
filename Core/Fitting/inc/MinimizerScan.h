#ifndef MINIMIZERSCAN_H
#define MINIMIZERSCAN_H
// ********************************************************************
// * The BornAgain project                                            *
// * Simulation of neutron and x-ray scattering at grazing incidence  *
// *                                                                  *
// * LICENSE AND DISCLAIMER                                           *
// * Lorem ipsum dolor sit amet, consectetur adipiscing elit.  Mauris *
// * eget quam orci. Quisque  porta  varius  dui,  quis  posuere nibh *
// * mollis quis. Mauris commodo rhoncus porttitor.                   *
// ********************************************************************
//! @file   MinimizerScan.h
//! @brief  Definition of MinimizerScan class
//! @author Scientific Computing Group at FRM II
//! @date   21.01.2013

#include "IMinimizer.h"
#include "FitSuiteParameters.h"
#include "OutputData.h"


//- -------------------------------------------------------------------
//! @class MinimizerScan
//! @brief Simple scan minimizer looks for minimum of chi2 function on the grid
//- -------------------------------------------------------------------
class MinimizerScan : public IMinimizer
{
public:
    MinimizerScan(int nbins = 10) : m_fcnvalues_map(0), m_nbins(nbins), m_ncall(0) { }
    virtual ~MinimizerScan() { delete m_fcnvalues_map; }

    virtual void minimize();

    virtual void setParameters(const FitSuiteParameters &parameters);

    virtual void setChiSquaredFunction(function_chi2_t fun_chi2, size_t nparameters);

    virtual void setGradientFunction(function_gradient_t fun_gradient, size_t nparameters, size_t ndatasize);

    virtual size_t getNumberOfVariables() const { return m_parameters.size(); }

    virtual double getMinValue() const;

    virtual double getValueOfVariableAtMinimum(size_t i) const;

    virtual void printResults() const;

    void setNbins(int nbins) { m_nbins = nbins; }

    size_t getNbins() const { return m_nbins; }

    const OutputData<double > *getOutputData() { return m_fcnvalues_map; }

    virtual std::vector<double > getValueOfVariablesAtMinimum() const;

private:

    void construct_fcnvalues_map();
    void set_parvalues_to_minimum();

    OutputData<double > *m_fcnvalues_map; //! values of minimized function on the grid, axes are limited parameters
    size_t m_nbins; //! number of bins per one parameter
    FitSuiteParameters m_parameters; //! minimizer parameters
    function_chi2_t m_fcn;

    size_t m_ncall;
};

#endif // MINIMIZERSCAN_H
