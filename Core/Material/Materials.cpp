// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Material/Materials.cpp
//! @brief     Implement utils for handling materials in namespace Materials
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "Materials.h"

IMaterial* Materials::createInvertedMaterial(const IMaterial* orig_material)
{
    if (!orig_material)
        return nullptr;

    const HomogeneousMagneticMaterial* magn_material =
            dynamic_cast<const HomogeneousMagneticMaterial*>(orig_material);

    if (!magn_material)
        return orig_material->clone();

    std::string new_name = orig_material->getName() + "_inv";
    return new HomogeneousMagneticMaterial(new_name,
                                           magn_material->getRefractiveIndex(),
                                          -magn_material->getMagneticField());
}
