// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Shapes/SlicedParticle.h
//! @brief     Defines class SlicedParticle.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2017
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   J. Burle, J. M. Fisher, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef SLICEDPARTICLE_H
#define SLICEDPARTICLE_H

#include "IFormFactor.h"
#include <memory>

//! Struct that contains information on a single homogeneous region of a particle inside
//! a single layer.
//! This information is needed for calculating the average of a material, used in the Fresnel
//! calculations.
//!
//! @ingroup intern

struct HomogeneousRegion
{
    double m_volume;
    HomogeneousMaterial m_material;
};

//! Struct that contains information on a sliced particle.
//! This information is needed for evaluating the sliced form factor and the average of a material,
//! used in the Fresnel calculations.
//!
//! @ingroup intern

struct SlicedParticle
{
    size_t m_layer_index;
    std::unique_ptr<IFormFactor> mP_slicedff;
    std::vector<HomogeneousRegion> m_regions;
};

#endif // SLICEDPARTICLE_H
