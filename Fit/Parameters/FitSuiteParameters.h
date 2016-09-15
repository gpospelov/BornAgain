// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Fit/Parameters/FitSuiteParameters.h
//! @brief     Defines class FitSuiteParameters.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef FITSUITEPARAMETERS_H
#define FITSUITEPARAMETERS_H

#include "WinDllMacros.h"
#include <vector>
#include <string>

class RealLimits;
class FitParameter;
class ParameterPool;

//! Vector of parameters, for FitSuite
//! @ingroup fitting_internal

class BA_CORE_API_ FitSuiteParameters
{
 public:
    typedef std::vector<std::vector<double>> corr_matrix_t;
    typedef std::vector<FitParameter*> container_t;

    FitSuiteParameters() {}
    ~FitSuiteParameters();

    //! Clears all defined parameters.
    void clear();

    //! Adds fit parameter.
    void addFitParameter(FitParameter* par);

    //! Returns fit parameter with given name.
    const FitParameter* getFitParameter(const std::string& name) const;
    FitParameter* getFitParameter(const std::string& name);

    //! Sets values for all defined parameters.
    void setValues(const double* pars_values);
    void setValues(const std::vector<double >& pars_values);

    //! Returns values of all defined parameters.
    std::vector<double> getValues() const;

    //! Sets errors to all parameters.
    void setErrors(const std::vector<double >& pars_errors);

    //! Returns errors of all defined parameters.
    std::vector<double> getErrors() const;

    //! Returns number of parameters.
    size_t size() const { return m_parameters.size(); }

    //! Container iterators

    container_t::iterator begin() { return m_parameters.begin(); }
    container_t::const_iterator begin() const { return m_parameters.begin(); }
    container_t::iterator end() { return m_parameters.end(); }
    container_t::const_iterator end() const { return m_parameters.end(); }

    //! Indexed access to parameters.

    const FitParameter* operator[](size_t index) const;
    FitParameter* operator[](size_t index);
    const FitParameter* operator[](std::string name) const;
    FitParameter* operator[](std::string name);

    //! Returns number of free parameters.
    size_t numberOfFreeFitParameters() const;

    //! Print defined parameters.
    void printFitParameters() const;

    //! Fix all parameters.
    void fixAll();

    //! Release all parameters.
    void releaseAll();

    //! Set fixed flag for parameters from the list.
    void setFixed(const std::vector<std::string>& pars, bool is_fixed);

    bool valuesDifferFrom(const std::vector<double>& par_values, double tolerance) const;

    std::string reportResults() const;

    corr_matrix_t correlationMatrix() const { return m_corr_matrix; }

    void setCorrelationMatrix(const corr_matrix_t &matrix) { m_corr_matrix = matrix;}

private:
    size_t check_index(size_t index) const;
    container_t m_parameters; //!< collection of fit parameters
    corr_matrix_t m_corr_matrix; //!< correlation matrix
};

#endif // FITSUITEPARAMETERS_H
