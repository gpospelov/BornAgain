// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Fitting/FitStrategyAdjustMinimizer.cpp
//! @brief     Implements class FitStrategyAdjustMinimizer.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "FitStrategyAdjustMinimizer.h"
#include "FitSuiteImp.h"
#include "IMinimizer.h"
#include "MinimizerFactory.h"

FitStrategyAdjustMinimizer::FitStrategyAdjustMinimizer()
    : IFitStrategy("FitStrategy/AdjustMinimizer")
{
}

FitStrategyAdjustMinimizer::FitStrategyAdjustMinimizer(const std::string &minimizerName,
                                                       const std::string &algorithmName,
                                                       const std::string &optionString)
    : IFitStrategy("FitStrategy/AdjustMinimizer")
    , m_minimizerName(minimizerName)
    , m_algorithmName(algorithmName)
    , m_optionString(optionString)
{
    setMinimizer(minimizerName, algorithmName, optionString);
}


FitStrategyAdjustMinimizer* FitStrategyAdjustMinimizer::clone() const
{
    FitStrategyAdjustMinimizer* result = new FitStrategyAdjustMinimizer(*this);
    return result;
}

void FitStrategyAdjustMinimizer::setMinimizer(const std::string &minimizerName,
                                              const std::string &algorithmName,
                                              const std::string &optionString)
{
    m_minimizerName = minimizerName;
    m_algorithmName = algorithmName;
    m_optionString = optionString;
}

void FitStrategyAdjustMinimizer::execute()
{
    m_kernel->setMinimizer(
        MinimizerFactory::createMinimizer(m_minimizerName, m_algorithmName, m_optionString));
    m_kernel->minimize();
}

std::string FitStrategyAdjustMinimizer::toString() const
{
    std::ostringstream ostr;
    ostr << "FitStrategy/AdjustMinimizer ("
         << m_minimizerName << ", "
         << m_algorithmName << ", "
         << m_optionString << ")";
    return ostr.str();
}

FitStrategyAdjustMinimizer::FitStrategyAdjustMinimizer(const FitStrategyAdjustMinimizer &other)
    : IFitStrategy(other)
{
    m_minimizerName = other.m_minimizerName;
    m_algorithmName = other.m_algorithmName;
    m_optionString = other.m_optionString;
}
