// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Material/Materials.h
//! @brief     Defines namespace Materials
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef MATERIALS_H
#define MATERIALS_H

#include "HomogeneousMagneticMaterial.h"

// TODO: replace this by a member function of IMaterial

namespace Materials {

IMaterial* createInvertedMaterial(const IMaterial *material);

}

#endif // MATERIALS_H
