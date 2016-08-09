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

class AttLimits;
class FitParameter;
class ParameterPool;

//! @class FitSuiteParameters
//! @ingroup fitting_internal
//! @brief Holds vector of parameters for FitSuite

class BA_CORE_API_ FitSuiteParameters
{
 public:
    typedef std::vector<FitParameter*> parameters_t;
    typedef parameters_t::iterator iterator;
    typedef parameters_t::const_iterator const_iterator;

    FitSuiteParameters();
    virtual ~FitSuiteParameters();

    //! Clears all defined parameters.
    void clear();

    //! Adds fit parameter.
    void addParameter(FitParameter* par) { m_parameters.push_back( par ); }

    //! Returns all parameters
    std::vector<FitParameter*> getParameters() { return m_parameters; }

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

    //! Adds given FitParameter to container.
    void push_back(FitParameter* par) { m_parameters.push_back(par); }

    //! Returns begin of container.
    iterator begin() { return m_parameters.begin(); }
    const_iterator begin() const { return m_parameters.begin(); }

    //! Returns end of container.
    iterator end() { return m_parameters.end(); }
    const_iterator end() const { return m_parameters.end(); }

    //! Indexed access to parameters.
    const FitParameter* operator[](size_t index) const;
    FitParameter* operator[](size_t index);

    //! Access to parameters by parameter name.
    const FitParameter* operator[](std::string name) const;
    FitParameter* operator[](std::string name);

    //! Returns number of free parameters.
    size_t getNfreeParameters() const;

    //! Returns true if parameters already have the given values.
    bool valuesAreDifferent(const double* pars_valuers, double tolerance_factor=1.0) const;

    //! Print defined parameters.
    void printParameters() const;

    //! Fix all parameters.
    void fixAll();

    //! Release all parameters.
    void releaseAll();

    //! Set fixed flag for parameters from the list.
    void setParametersFixed(const std::vector<std::string> &pars, bool is_fixed);

 private:
    size_t check_index(size_t index) const;
    std::vector<FitParameter*> m_parameters; //!< collection of fit parameters
};

#endif // FITSUITEPARAMETERS_H
