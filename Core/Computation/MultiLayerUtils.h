// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Computation/MultiLayerUtils.h
//! @brief     Defines helper functions for MultiLayer objects.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef MULTILAYERUTILS_H
#define MULTILAYERUTILS_H

#include <vector>

class MultiLayer;
class ZLimits;

namespace MultiLayerUtils {
std::vector<ZLimits> ParticleRegions(const MultiLayer& multilayer, bool use_slicing);
}

#endif // MULTILAYERUTILS_H
