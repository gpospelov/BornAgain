// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Fit/Minimizer/ObjectiveFunction.h
//! @brief     Declares class ObjectiveFunction
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "ObjectiveFunction.h"
#include <stdexcept>

ObjectiveFunction::ObjectiveFunction()
    : m_ncalls(0)
{

}

void ObjectiveFunction::setObjectiveFunction(objective_function_t func)
{
    m_evaluate = func;
}

//! Evaluates the value of the function for given vector of function parameters using
//! callback mechanism.

double ObjectiveFunction::evaluate(const std::vector<double> &pars)
{
    if(!m_evaluate)
        throw std::runtime_error("ObjectiveFunction::evaluate() -> Error. "
                                 "Objective function is not set");

    ++m_ncalls;
    return m_evaluate(pars);
}
