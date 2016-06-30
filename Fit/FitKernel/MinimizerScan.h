// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Fit/FitKernel/MinimizerScan.h
//! @brief     Declares class MinimizerScan.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef MINIMIZERSCAN_H
#define MINIMIZERSCAN_H

#include "IMinimizer.h"
#include "FitSuiteParameters.h"
#include "OutputData.h"


//! @class MinimizerScan
//! @ingroup fitting_internal
//! @brief Simple scan minimizer looks for minimum of chi2 function on the grid

class BA_CORE_API_ MinimizerScan : public IMinimizer
{
 public:
    MinimizerScan(int nbins = 10) : m_fcnvalues_map(0), m_nbins(nbins) { }
    virtual ~MinimizerScan() { delete m_fcnvalues_map; }

    virtual void minimize();

    virtual void setParameters(const FitSuiteParameters& parameters);

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
};

#endif // MINIMIZERSCAN_H


