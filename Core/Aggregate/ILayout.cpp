// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Aggregate/ILayout.cpp
//! @brief     Implements interface class ILayout.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2017
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "ILayout.h"

#include "IAbstractParticle.h"
#include "INodeUtils.h"


ILayout::~ILayout() =default;

double ILayout::getTotalAbundance() const
{
    double total_abundance = 0.0;
    auto particles = INodeUtils::ChildNodesOfType<IAbstractParticle>(*this);
    for (auto p_particle : particles) {
        total_abundance += p_particle->abundance();
    }
    return total_abundance;
}
