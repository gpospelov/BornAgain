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

#ifndef OBJECTIVEFUNCTION_H
#define OBJECTIVEFUNCTION_H

#include "WinDllMacros.h"
#include "KernelTypes.h"
#include <vector>
#include <functional>

//! @class ObjectiveFunction
//! @ingroup fitting_internal
//! @brief The ObjectiveFunction class represents function to minimize.

class BA_CORE_API_ ObjectiveFunction
{
public:

    ObjectiveFunction();

    void setObjectiveFunction(objective_function_t func);

    double evaluate(const std::vector<double>& pars);

    int functionCalls() const { return m_ncalls; }

private:
    objective_function_t m_evaluate;
    int m_ncalls;
};


#endif

