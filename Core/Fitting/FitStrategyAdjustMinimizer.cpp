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
#include "FitKernel.h"
#include "IMinimizer.h"
#include "MinimizerFactory.h"
#include "ObsoleteMinimizerOptions.h"

FitStrategyAdjustMinimizer::FitStrategyAdjustMinimizer()
    : IFitStrategy("FitStrategyAdjustMinimizer"), m_minimizer(nullptr)
{
}

FitStrategyAdjustMinimizer::FitStrategyAdjustMinimizer(const std::string &minimizer_name,
                                                       const std::string &algorithm_name,
                                                       const std::string &minimizer_options)
    : IFitStrategy("FitStrategyAdjustMinimizer"), m_minimizer(nullptr)
{
    setMinimizer(minimizer_name, algorithm_name, minimizer_options);
}

FitStrategyAdjustMinimizer::~FitStrategyAdjustMinimizer()
{
    delete m_minimizer;
}

// partial clone
FitStrategyAdjustMinimizer* FitStrategyAdjustMinimizer::clone() const
{
    FitStrategyAdjustMinimizer* result = new FitStrategyAdjustMinimizer();
    result->setName(getName());
    result->setMinimizer( MinimizerFactory::createMinimizer(m_minimizer));
    return result;
}

IMinimizer* FitStrategyAdjustMinimizer::getMinimizer()
{
    return m_minimizer;
}

void FitStrategyAdjustMinimizer::setMinimizer(IMinimizer* minimizer)
{
    m_minimizer = minimizer;
}

void FitStrategyAdjustMinimizer::setMinimizer(const std::string &minimizer_name,
                                              const std::string &algorithm_name,
                                              const std::string &minimizer_options)
{
    setMinimizer(MinimizerFactory::createMinimizer(
                     minimizer_name, algorithm_name, minimizer_options));
}

void FitStrategyAdjustMinimizer::execute()
{

    m_kernel->setMinimizer( MinimizerFactory::createMinimizer(m_minimizer) );

    m_kernel->minimize();

    //m_fit_suite->printResults();
}

ObsoleteMinimizerOptions* FitStrategyAdjustMinimizer::getMinimizerOptions()
{
//    if(!m_minimizer)
//        return nullptr;
//    return m_minimizer->getOptions();
    assert(0);
    return nullptr;
}

void FitStrategyAdjustMinimizer::print(std::ostream &ostr) const
{
    assert(0);
    ostr << "FitStrategy/AdjustMinimizer: ";
//    if(m_minimizer) {
//        ostr << m_minimizer->getMinimizerName();
//        if(m_minimizer->getAlgorithmName().size())
//            ostr << "(" << m_minimizer->getAlgorithmName() << ")";
//    }
}
