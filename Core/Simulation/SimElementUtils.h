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
void addElementsWithWeight(const std::vector<SimElement>& from, std::vector<SimElement>& to,
                           double weight)
{
    assert(!from.empty());
    assert(from.size() == to.size());
    auto to_it = to.begin();
    for (auto from_it = from.cbegin(); from_it != from.cend(); ++from_it, ++to_it)
        to_it->addIntensity(from_it->getIntensity() * weight);
}
}

#endif /* SIMELEMENTUTILS_H_ */
