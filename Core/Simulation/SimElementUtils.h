// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Simulation/SimElementUtils.h
//! @brief     Defines a set of functions to operate on simulation elements.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef SIMELEMENTUTILS_H_
#define SIMELEMENTUTILS_H_

#include <vector>

//! Set of templated utilities to operate on a vector of simulation elements
//! @ingroup simulation

namespace SimElementUtils {

template <class SimElement>
using const_iter = typename std::vector<SimElement>::const_iterator;

template <class SimElement>
using iter = typename std::vector<SimElement>::iterator;

//! Add element vector to element vector with weight
template <class SimElement>
void addElementsWithWeight(const_iter<SimElement> first, const_iter<SimElement> last,
                           iter<SimElement> result, double weight)
{
    for (auto it = first; it != last; ++it, ++result)
        result->addIntensity(it->getIntensity() * weight);
}
}

#endif /* SIMELEMENTUTILS_H_ */
