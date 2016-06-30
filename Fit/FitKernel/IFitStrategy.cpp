// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Fit/FitKernel/IFitStrategy.cpp
//! @brief     Implements class IFitStrategy.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "IFitStrategy.h"
#include "FitKernel.h"

IFitStrategy::IFitStrategy()
    : m_kernel(nullptr)
{
}

IFitStrategy::IFitStrategy(const std::string &name)
    : INamed(name), m_kernel(nullptr)
{
}

void IFitStrategy::init(FitKernel *fit_suite)
{
    m_kernel = fit_suite;
}

void IFitStrategy::print(std::ostream &ostr) const
{
    ostr << getName();
}

IFitStrategy::IFitStrategy(const IFitStrategy &other)
    : INamed(other)
{
    m_kernel = other.m_kernel;
}

// ----------------------------------------------------------------------------

FitStrategyDefault::FitStrategyDefault()
    : IFitStrategy("DefaultFitStrategy")
{
}

IFitStrategy *FitStrategyDefault::clone() const
{
    return new FitStrategyDefault();
}

void FitStrategyDefault::execute()
{
    if( !m_kernel )
        throw NullPointerException("FitStrategyDefault::execute() -> FitSuite doesn't exists");

    // calling minimization
    m_kernel->minimize();
}
