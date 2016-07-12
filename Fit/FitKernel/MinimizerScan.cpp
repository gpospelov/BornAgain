// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Fit/FitKernel/MinimizerScan.cpp
//! @brief     Implements class MinimizerScan.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "MinimizerScan.h"
#include <algorithm>

//! Scan minimizer find minimum of chi2 function by equidistant scanning of fit parameters.
// Only parameters with defined limits (i.e. AttLimits::limited(left, right) )
// are scanned
void MinimizerScan::minimize()
{
    construct_fcnvalues_map();

    // scanning values of fit parameters
    for(OutputData<double>::iterator it = m_fcnvalues_map->begin(); it!=m_fcnvalues_map->end(); ++it) {
        for(size_t i_axis=0; i_axis<m_fcnvalues_map->getRank(); ++i_axis) {
            size_t xbin = m_fcnvalues_map->getAxisBinIndex(it.getIndex(), i_axis);
            double value = (*m_fcnvalues_map->getAxis(i_axis))[xbin];
            std::string parname = m_fcnvalues_map->getAxis(i_axis)->getName();
            m_parameters.getParameter(parname)->setValue(value);
        }
        std::vector<double> current_values=m_parameters.getValues();
        (*it) = m_fcn(&current_values[0]); // running simulation
    }

    set_parvalues_to_minimum();
    std::vector<double> current_values=m_parameters.getValues();
    m_fcn(&current_values[0]); // running simulation once again at optimum values
}

//! Construct N dimensional space over all fit parameters with lower and upper limits
// defined.
void MinimizerScan::construct_fcnvalues_map()
{
    delete m_fcnvalues_map;
    m_fcnvalues_map = new OutputData<double>;
    for(size_t i_par=0; i_par < m_parameters.size(); i_par++ ) {
        const FitParameter *par = m_parameters[i_par];
        if( par->hasLowerLimit() && par->hasUpperLimit() ) {
            FixedBinAxis axis(par->getName(), m_nbins, par->getLowerLimit(), par->getUpperLimit());
            m_fcnvalues_map->addAxis(axis);
        }
    }
    if( !m_fcnvalues_map->getRank() ) {
        throw Exceptions::LogicErrorException("MinimizerScan::construct_parameter_map() -> Error! No parameters with TAttLimit::limited(left,right) attribute were found.");
    }
    m_fcnvalues_map->setAllTo(0.0);
}

void MinimizerScan::set_parvalues_to_minimum()
{
    assert(m_fcnvalues_map);
    OutputData<double>::iterator it = std::min_element(m_fcnvalues_map->begin(), m_fcnvalues_map->end());
    for(size_t i_axis=0; i_axis<m_fcnvalues_map->getRank(); ++i_axis) {
        size_t xbin = m_fcnvalues_map->getAxisBinIndex(it.getIndex(), i_axis);
        double value = (*m_fcnvalues_map->getAxis(i_axis))[xbin];
        std::string parname = m_fcnvalues_map->getAxis(i_axis)->getName();
        m_parameters.getParameter(parname)->setValue(value);
    }
}

double MinimizerScan::getMinValue() const
{
    assert(m_fcnvalues_map);
    return *std::min_element(m_fcnvalues_map->begin(), m_fcnvalues_map->end());
}

void MinimizerScan::setGradientFunction(function_gradient_t fun_gradient, size_t nparameters, size_t ndatasize)
{
    (void) fun_gradient;
    (void) nparameters;
    (void) ndatasize;
}

double MinimizerScan::getValueOfVariableAtMinimum(size_t index) const
{
    return m_parameters[index]->getValue();
}

void MinimizerScan::printResults() const
{
    std::cout << "--- MinimizerScan ------------------------------------" << std::endl;
    std::cout << std::setw(25) << std::left << " nbins"      << ": " << m_nbins << std::endl;
    std::cout << std::setw(25) << std::left << " Minimum value"      << ": " << getMinValue() << std::endl;
    std::cout << " Best parameters:" << std::endl;
    m_parameters.printParameters();
}

void MinimizerScan::setChiSquaredFunction(function_chi2_t fun_chi2, size_t nparameters)
{
    (void)nparameters;
    m_fcn = fun_chi2;
}

void MinimizerScan::setParameters(const FitSuiteParameters& parameters)
{
    m_parameters.clear();
    for(size_t i_par = 0; i_par<parameters.size(); ++i_par) {
        m_parameters.push_back(new FitParameter( *parameters[i_par] ) );
    }
}

std::vector<double > MinimizerScan::getValueOfVariablesAtMinimum() const
{
    return m_parameters.getValues();
}


