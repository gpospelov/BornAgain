// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tools/inc/Materials.h
//! @brief     Defines namespace Materials
//!
//! @homepage  http://apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef MATERIALS_H
#define MATERIALS_H

#include "HomogeneousMaterial.h"
#include "HomogeneousMagneticMaterial.h"

namespace Materials {

IMaterial *createInvertedMaterial(const IMaterial *material);


}



#endif
