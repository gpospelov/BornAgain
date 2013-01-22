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
#include "SafePointerVector.h"
#include "OutputData.h"

//- -------------------------------------------------------------------
//! @class MinimizerScan
//! @brief Simple scan minimizer
//- -------------------------------------------------------------------
class MinimizerScan : public IMinimizer
{
public:
    MinimizerScan(int nbins = 10) : m_parameter_map(0), m_nbins(nbins) { }
    virtual ~MinimizerScan() { delete m_parameter_map; }

    virtual void minimize();

    virtual void setParameters(const FitSuiteParameters &parameters);

    virtual void setChiSquaredFunction(function_chi2_t fun_chi2, size_t nparameters);

    virtual void setGradientFunction(function_gradient_t fun_gradient, size_t nparameters, size_t ndatasize);

    virtual size_t getNumberOfVariables() const { return m_fit_parameters.size(); }

    virtual double getMinValue() const;

    virtual double getValueOfVariableAtMinimum(size_t i) const;

    virtual void printResults() const;


    void setNbins(int nbins) { m_nbins = nbins; }
    size_t getNbins() const { return m_nbins; }

    const OutputData<double > *getOutputData() { return m_parameter_map; }

private:

    void construct_parameter_map();
    void set_parvalues_to_minimum();

    OutputData<double > *m_parameter_map;
    size_t m_nbins; //! number of bins per one parameter
    //SafePointerVector<FitParameter > m_fit_parameters;
    FitSuiteParameters m_fit_parameters;
    std::vector<double> m_parvalues_at_minimum;
    function_chi2_t m_fcn;
};

#endif // MINIMIZERSCAN_H
