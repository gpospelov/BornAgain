// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Multilayer/IMultiLayerBuilder.cpp
//! @brief     Implements pure virtual base class IMultiLayerBuilder.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "IMultiLayerBuilder.h"
#include "FTDistributions2D.h"
#include "IFormFactor.h"

const IFormFactor* IMultiLayerBuilder::getFormFactor() const
{
    return dynamic_cast<const IFormFactor*>(m_subtest_item);
}

const IFTDistribution2D* IMultiLayerBuilder::getFTDistribution2D() const
{
    return dynamic_cast<const IFTDistribution2D*>(m_subtest_item);
}
