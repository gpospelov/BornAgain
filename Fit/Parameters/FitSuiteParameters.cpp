// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Fit/Parameters/FitSuiteParameters.cpp
//! @brief     Implements class FitSuiteParameters.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "FitSuiteParameters.h"
#include "FitParameter.h"
#include "Logger.h"
#include "MinimizerResultsHelper.h"
#include <algorithm>
#include <cmath>
#include <iostream>
#include <limits>
#include <stdexcept>

FitSuiteParameters::~FitSuiteParameters()
{
    clear();
}

void FitSuiteParameters::clear()
{
    for (auto par: m_parameters)
        delete par;
    m_parameters.clear();
}

void FitSuiteParameters::addFitParameter(FitParameter *par)
{
//    if(getFitParameter(par->getName()))
//        throw std::runtime_error("FitSuiteParameters::addFitParameter() -> Error. Parameter with "
//                                 "the name '"+par->getName()+"' already exist.");

    m_parameters.push_back(par);
}

//! Returns fit parameter with given name.
const FitParameter* FitSuiteParameters::getFitParameter(const std::string& name) const
{
    for (auto par: m_parameters)
        if (par->getName() == name)
            return par;
    throw std::runtime_error("FitSuiteParameters::getFitParameter() -> "
                             "Error. No parameter with name '"+name+"'");
}


FitParameter* FitSuiteParameters::getFitParameter(const std::string& name)
{
    for (auto par: m_parameters)
        if (par->getName() == name)
            return par;
    throw std::runtime_error("FitSuiteParameters::getFitParameter() -> "
                             "Error. No parameter with name '"+name+"'");
}

//! Sets values for all defined parameters
void FitSuiteParameters::setValues(const double* pars_values)
{
    if( !valuesDifferFrom(pars_values, 1.) ) {
        msglog(MSG::WARNING) << "FitSuiteParameters::setValues() -> Warning! "
                                "Small or absent change in parameter values.";
        for(size_t i_par=0; i_par<m_parameters.size(); ++i_par) {
            msglog(MSG::DEBUG2) << "npar:"<< i_par << std::setprecision(10)
                           << " current:" << m_parameters[i_par]->getValue()
                           << " new: " << pars_values[i_par]
                           << " diff:" << m_parameters[i_par]->getValue() -pars_values[i_par];
        }
    }

    size_t index(0);
    for (auto par: m_parameters) {
        if (std::isnan(pars_values[index]))
            throw std::runtime_error(
                "FitSuiteParameters::setValues() -> Error."
                " Attempt to set nan '"+par->getName() + std::string("'."));
        if (std::isinf(pars_values[index]))
            throw std::runtime_error(
                "FitSuiteParameters::setValues() -> Error. Attempt to set inf '" +
                par->getName()  + std::string("'."));
        par->setValue(pars_values[index]);
        index++;
    }
}

void FitSuiteParameters::setValues(const std::vector<double>& pars_values)
{
    if (pars_values.size() != m_parameters.size()) {
        std::ostringstream ostr;
        ostr << "FitSuiteParameters::setValues() -> Wrong size of array with parameter values "
             << pars_values.size()
             << ", number of parameters expected " << m_parameters.size() << std::endl;
        throw std::runtime_error(ostr.str());
    }
    setValues(&pars_values[0]);
}


void FitSuiteParameters::setErrors(const std::vector<double>& pars_errors)
{
    if (pars_errors.size() != m_parameters.size()) {
        std::ostringstream ostr;
        ostr << "FitSuiteParameters::setErrors() -> Wrong size of array with parameter errors "
             << pars_errors.size()
             << ", number of parameters expected " << m_parameters.size() << std::endl;
        throw std::runtime_error(ostr.str());
    }
    for (size_t i=0; i<m_parameters.size(); ++i)
        m_parameters[i]->setError(pars_errors[i]);
}


std::vector<double> FitSuiteParameters::getValues() const
{
    std::vector<double> result;
    for (auto par: m_parameters)
        result.push_back(par->getValue());
    return result;
}

std::vector<double> FitSuiteParameters::getErrors() const
{
    std::vector<double> result;
    result.resize(m_parameters.size(), 0.0);
    for (auto par: m_parameters)
        result.push_back(par->getError());
    return result;
}

FitParameter* FitSuiteParameters::operator[](std::string name)
{
    return getFitParameter(name);
}

const FitParameter* FitSuiteParameters::operator[](std::string name) const
{
    return getFitParameter(name);
}

FitParameter* FitSuiteParameters::operator[](size_t index)
{
    return m_parameters[check_index(index)];
}

const FitParameter* FitSuiteParameters::operator[](size_t index) const
{
    return m_parameters[check_index(index)];
}

size_t FitSuiteParameters::numberOfFreeFitParameters() const
// TODO: cover by test
{
    size_t result(0);
    for (auto par: m_parameters)
        if (!par->isFixed())
            result++;
    return result;
}

//! Returns true if parameters already have the given values.
bool FitSuiteParameters::valuesDifferFrom(const double* pars_values, double tol) const
{
    for (size_t i=0; i<m_parameters.size(); ++i)
        if (numbersDiffer(m_parameters[i]->getValue(), pars_values[i], tol))
            return true;
    return false;
}

std::string FitSuiteParameters::reportResults() const
{
    MinimizerResultsHelper helper;
    return helper.reportResults(this);
}

bool FitSuiteParameters::numbersDiffer(double a, double b, double tol) const
{
    constexpr double eps = std::numeric_limits<double>::epsilon();
    if (tol<1)
        throw std::runtime_error("Bug: FitSuiteParameters::numbersDiffer not intended for tol<1");
    return std::abs(a-b) > eps * std::max( tol*eps, std::abs(b) );
}

void FitSuiteParameters::printFitParameters() const
{
    int npar(0);
    for (auto par: m_parameters)
        std::cout << "   # "<< npar++ << " " << (*par) << std::endl;
}

void FitSuiteParameters::fixAll()
{
    for (auto par: m_parameters)
        par->setFixed(true);
}

void FitSuiteParameters::releaseAll()
{
    for (auto par: m_parameters)
        par->setFixed(false);
}

void FitSuiteParameters::setFixed(const std::vector<std::string>& pars, bool is_fixed)
{
    for (auto par: pars)
        getFitParameter(par)->setFixed(is_fixed);
}

size_t FitSuiteParameters::check_index(size_t index) const {
    if (index >= m_parameters.size())
        throw std::runtime_error(
            "FitSuiteParameters::check_index() -> Index out of bounds");
    return index;
}
