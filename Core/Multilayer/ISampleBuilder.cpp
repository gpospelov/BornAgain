// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Multilayer/ISampleBuilder.cpp
//! @brief     Implements pure virtual base class ISampleBuilder.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "ISampleBuilder.h"
#include "FTDistributions.h"
#include "IFormFactor.h"

const IFormFactor* ISampleBuilder::getFormFactor() const
{
    return dynamic_cast<const IFormFactor*>(m_subtest_item);
}

const IFTDistribution2D* ISampleBuilder::getFTDistribution2D() const
{
    return dynamic_cast<const IFTDistribution2D*>(m_subtest_item);
}
