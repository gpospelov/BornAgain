// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Scattering/ISample.cpp
//! @brief     Implements class ISample.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "Core/Scattering/ISample.h"
#include "Core/Basics/Exceptions.h"
#include "Core/Parametrization/ParameterPool.h"
#include <algorithm>
#include <sstream>

std::vector<const Material*> ISample::containedMaterials() const
{
    std::vector<const Material*> result;
    if (const Material* p_material = material())
        result.push_back(p_material);
    for (auto child : getChildren()) {
        if (const ISample* sample = dynamic_cast<const ISample*>(child)) {
            for (const Material* p_material : sample->containedMaterials())
                result.push_back(p_material);
        }
    }
    return result;
}
