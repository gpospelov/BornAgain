// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Fit/Minimizer/FitKernelImp.cpp
//! @brief     Declares class FitKernelImp.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "FitKernelImp.h"
#include "IMinimizer.h"

FitKernelImp::FitKernelImp()
{

}

FitKernelImp::~FitKernelImp()
{

}

void FitKernelImp::setMinimizer(IMinimizer *minimizer)
{
    m_minimizer.reset(minimizer);
}

void FitKernelImp::addFitParameter(FitParameter *par)
{
    m_fit_parameters.addFitParameter(par);
}

void FitKernelImp::setObjectiveFunction(function_chi2_t func)
{
    m_chi2_func = func;
}

void FitKernelImp::minimize()
{
    // order matters
    m_minimizer->setObjectiveFunction(m_chi2_func, m_fit_parameters.size());
    m_minimizer->setParameters(m_fit_parameters);

    // minimize
    try {
        m_minimizer->minimize();
    } catch (int) {}

    // set found values to the parameters
    m_minimizer->propagateResults(m_fit_parameters);


}
