// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Fit/Minimizer/BasicMinimizer.cpp
//! @brief     Implements class BasicMinimizer.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "BasicMinimizer.h"

BasicMinimizer::BasicMinimizer(const std::string &minimizerName, const std::string &algorithmName)
    : m_minimizerName(minimizerName)
    , m_algorithmName(algorithmName)
{

}

std::string BasicMinimizer::minimizerName() const
{
    return m_minimizerName;
}

std::string BasicMinimizer::algorithmName() const
{
    return m_algorithmName;
}

void BasicMinimizer::setAlgorithmName(const std::string &algorithmName)
{
    m_algorithmName = algorithmName;
}

