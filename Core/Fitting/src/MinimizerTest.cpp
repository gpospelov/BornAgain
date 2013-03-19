// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Fitting/src/MinimizerTest.cpp
//! @brief     Implements class MinimizerTest.
//!
//! @homepage  apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke 
//
// ************************************************************************** //

#include "MinimizerTest.h"

//! run minimization
void MinimizerTest::minimize()
{
    m_min_value = m_fcn(&m_parameters.getValues()[0]);
}

//! return pointer to the parameters values at the minimum
double MinimizerTest::getValueOfVariableAtMinimum(size_t index) const
{
    return m_parameters[index]->getValue();
}

//! return value of the parameter at the minimum
std::vector<double > MinimizerTest::getValueOfVariablesAtMinimum() const
{
    return m_parameters.getValues();
}

//! ?
void MinimizerTest::setParameters(const FitSuiteParameters &parameters)
{
    m_parameters.clear();
    for(size_t i_par = 0; i_par<parameters.size(); ++i_par) {
        m_parameters.push_back(new FitParameter( *parameters[i_par] ) );
    }
}

//! ?
void MinimizerTest::printResults() const
{
    std::cout << "MinimizerTest::printResult() "  << m_min_value << std::endl;
}
